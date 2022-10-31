#ifndef EVENTHISSPROVIDER_H
#define EVENTHISSPROVIDER_H

#include <QObject>
#include <QDateTime>
#include <QApplication>
#include <QDir>
#include "source/service/includesvcdto.h"
#include "source/service/productsetting/productsprovider.h"
#include "source/service/dsp/dspsprovider.h"
#include "source/service/eventhistory/dailypdstatsmanager.h"
#include "source/service/eventhistory/dailypdhismanager.h"
#include "source/service/eventhistory/dailyeventhismanager.h"
#include "source/service/util/exceptionutil.h"
#include "source/service/util/sproviderconnectutil.h"

#define pEventHisSP EventHistorySProvider::getInstance()

class EventHistorySProvider : public QObject
{
    Q_OBJECT
public:
    static EventHistorySProvider * getInstance()
    {
        static EventHistorySProvider *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new EventHistorySProvider();
        }

        return mpSelf;
    }

    bool        mIsRunning = false;
    QDate       mLastDate;
    QSettings * mpSetting = nullptr;

    DailyEventHisManager mEHManager;
    DailyPDHisManager    mPHManager; // open 할때 마다 제품 리스트 확인하여 없으면 추가
    DailyPDStatsManager  mPSManager; // open 할때 마다 현재 제품 추가

    explicit EventHistorySProvider(QObject * parent = nullptr):QObject(parent)
    {
        mpSetting = new QSettings("novasen", "WCMD_LASTTIME", this);
    }
    ~EventHistorySProvider()
    {
        stop();
    }

    void start(QDateTime now)
    {
        qint64 lastProcMSec = mpSetting->value("lasttime/last_proc_msec", 0).toULongLong();

        setLastDate(now);

        mLastDate = now.date();

        if(lastProcMSec != 0)
        {
            QDateTime exitDateTime = QDateTime::fromMSecsSinceEpoch(lastProcMSec);
            mEHManager.addAppExitEventHis(exitDateTime);
        }
        mEHManager.addAppStartEventHis(now);

        open(now.date());

        mIsRunning = true;

        ENABLE_SLOT_TIMER_TICK;
        ENABLE_SLOT_DSP_ADDED_EVENT;
        ENABLE_SLOT_PDSETTING_CHANGED_CURR_PD;
        ENABLE_SLOT_PDSETTING_ADD_PD;

        emit signalEventStarted();
    }

    void stop()
    {
        close();
        mIsRunning = false;
        emit signalEventStopped();
    }

    void factoryReset()
    {
        close();
        mpSetting->clear();
        QDir(FileDef::HISTORY_DIR()).removeRecursively();
        stop();
    }

signals:
    void signalEventStarted();
    void signalEventStopped();
    void siganlEventAddedEventHistory(EventDto dto);


public slots:
    void onTimeTick(QDateTime now)
    {
        CHECK_FALSE_RETURN(mIsRunning);

        setLastDate(now);

        if(mLastDate != now.date())
        {
            mLastDate = now.date();
            close();
            open(now.date());
        }

    }
    void onChangedCurrPDSetting(PDSettingDto dto)
    {
        CHECK_FALSE_RETURN(mIsRunning);

        mPHManager.addPDHis(dto);
        mPSManager.editPDStatsItem(dto);
    }

    void onAddedPDSetting(PDSettingDto dto)
    {
        mPSManager.addPDStatsItem(dto);
    }

    void onAddedDspEvent(quint64 dspSeq, DspEventDto dto)
    {
        CHECK_FALSE_RETURN(mIsRunning);

        QDateTime now = QDateTime::currentDateTime();
        onTimeTick(now);

        EventDto convertEvent;

        convertEvent.mDateTime = now;
        convertEvent.mDspSeq   = dspSeq;
        convertEvent.mPDSeq    = pProductSP->mCurrPD.mSeq;
        convertEvent.mPDNum    = pProductSP->mCurrPD.mDspForm.mCommSetting.mProductNum;
        convertEvent.mPDHisIdx = mPHManager.mEventCnt;
        convertEvent.mEType    = dto.mEvent.mEventType;
        convertEvent.mEValue   = dto.mEvent.mEventValue;

        mEHManager.addEventHis(convertEvent);
        mPSManager.addEvent(convertEvent);

        emit siganlEventAddedEventHistory(convertEvent);
    }

private:
    void open(QDate today)
    {
        mPHManager.open(today);
        mPSManager.open(today);
        mEHManager.open(today);
    }

    void close()
    {
        mPHManager.close();
        mPSManager.close();
        mEHManager.close();
    }

    void setLastDate(QDateTime now)
    {
        mpSetting->setValue("lasttime/last_proc_msec", now.toMSecsSinceEpoch());
    }

};

#endif // EVENTHISSPROVIDER_H
