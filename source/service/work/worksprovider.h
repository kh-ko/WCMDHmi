#ifndef WORKSPROVIDER_H
#define WORKSPROVIDER_H

#include <QObject>
#include <QDateTime>
#include <QApplication>
#include "source/service/util/exceptionutil.h"
#include "source/service/def/filedef.h"
#include "source/service/util/filereaderex.h"
#include "source/service/util/filewriterex.h"
#include "source/service/includesvcdto.h"
#include "source/service/productsetting/productsprovider.h"
#include "source/service/dsp/dspsprovider.h"
#include "source/service/eventhistory/eventhissprovider.h"
#include "source/service/util/sproviderconnectutil.h"
#include "source/service/work/TrendsManager.h"
#define pWorkSP WorkSProvider::getInstance()

class WorkSProvider : public QObject
{
    Q_OBJECT
public:
    static WorkSProvider * getInstance()
    {
        static WorkSProvider *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new WorkSProvider();
        }

        return mpSelf;
    }


    bool                 mIsRunning   = false;
    PDStatsDto           mCurrPD      ;
    PDSettingDto         mSelPDSetting;
    QList<PDStatsDto *>  mPDStatsList ;
    EventDto             mLastErrEvent;
    TrendsManager        mTRManager;

    QThread            * mpReaderThread = nullptr;
    FileReaderEx       * mpReader       = nullptr;
    FileWriterEx       * mpWriter       = nullptr;

    explicit WorkSProvider(QObject * parent = nullptr):QObject(parent)
    {

    }
    ~WorkSProvider()
    {
        stop();
    }

    void asyncStart(QDate startDate, bool isDayMode, QList<PDSettingDto *> pdSettingList)
    {
        foreach(PDSettingDto * pSetting, pdSettingList)
        {
            createPDStats(*pSetting);
        }

        if(QFile::exists(QString("%1/%2").arg(FileDef::WORK_DIR()).arg(FileDef::WORK_FILENAME())))
        {
            QFile file(QString("%1/%2").arg(FileDef::WORK_DIR()).arg(FileDef::WORK_FILENAME()));

            qDebug() << "[WorkSProvider::asyncStart]birth date = " << file.fileTime(QFileDevice::FileBirthTime).date().toString() << ", startDate = " << startDate.toString();

            if(file.fileTime(QFileDevice::FileBirthTime).date() != startDate || !isDayMode)
            {
                QFile::remove(QString("%1/%2").arg(FileDef::WORK_DIR()).arg(FileDef::WORK_FILENAME()));
            }
        }

        if(QFile::exists(QString("%1/%2").arg(FileDef::WORK_DIR()).arg(FileDef::WORK_FILENAME())) == false)
        {
            onEndedRead();
        }
        else
        {
            openReader();
            readFile();
        }
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

        QDir(FileDef::WORK_DIR()).removeRecursively();

        stop();
    }

    void clearStats()
    {
        // 일단 열어놓은 자원을 닫고
        close();

        // 파일 지우고 변수 값 지운다.
        QDir(FileDef::WORK_DIR()).removeRecursively();

        mCurrPD.reset();

        foreach(PDStatsDto *stats, mPDStatsList)
        {
            stats->clearValue();
        }

        mTRManager.clear();

        // 다시 write 자원 열고 현재 제품값 설정한다.
        openWriter();
        onChangedCurrPDSetting(pProductSP->mCurrPD);


        mLastErrEvent.reset();
        emit signalEventChangedLastErr(mLastErrEvent);

    }
    PDStatsDto * findPDStats(quint64 pdSeq)
    {
        foreach(PDStatsDto * ptr, mPDStatsList)
        {
            if(ptr->mSeq == pdSeq)
                return ptr;
        }

        return nullptr;
    }

signals:
    void signalEventStarted();
    void signalEventStopped();
    void signalEventChangedPDStats(PDStatsDto);
    void signalEventChangedLastErr(EventDto  );

    void signalCommandOpen(QString, QString);
    void signalCommandReadMultiLine(int lineCnt);

public slots:
    void onChangedCurrPDSetting(PDSettingDto dto)
    {
        CHECK_FALSE_RETURN(mIsRunning);

        PDStatsDto * pNewStats = findPDStats(dto.mSeq);

        if(pNewStats == nullptr)
            createPDStats(dto);

        swapCurrPD(dto.mSeq);

        emit signalEventChangedPDStats(mCurrPD);
    }

    void onAddedEventHistory(EventDto dto)
    {
        CHECK_FALSE_RETURN(mIsRunning);

        if(dto.isWCEvent())
        {
            procWCEvent(dto);
        }
        else if(dto.isMDEvent())
        {
            procMDEvent(dto);
        }

        write(dto.toString());

        if((dto.isWeightNGEvent() && dto.mEType != EnumDef::ET_WEIGHT_ETC_METAL_ERROR) || dto.isMetalDetectEvent())
        {
            mLastErrEvent = dto;
            emit signalEventChangedLastErr(mLastErrEvent);
        }

        emit signalEventChangedPDStats(mCurrPD);
    }

private slots:
    void onReadFile(QStringList lines)
    {
        foreach(QString line, lines)
        {
            EventDto dto;
            if(dto.setValue(line) == false)
                continue;

            if(dto.isWCEvent())
            {
                procWCEvent(dto);
            }
            else if(dto.isMDEvent())
            {
                procMDEvent(dto);
            }
        }

        if(lines.size() < 3000)
        {
            onEndedRead();
            return;
        }

        readFile();
    }

    void onEndedRead()
    {
        closeReader();

        openWriter();

        swapCurrPD(pProductSP->mCurrPD.mSeq);

        ENABLE_SLOT_PDSETTING_CHANGED_CURR_PD;
        ENABLE_SLOT_EVENTHIS_ADDED_EVENT;

        mIsRunning = true;

        emit signalEventStarted();
    }

private:
    void createPDStats(PDSettingDto pdSetting)
    {
        PDStatsDto * pStats = new PDStatsDto();
        pStats->mSeq  = pdSetting.mSeq;
        pStats->mNum  = pdSetting.mDspForm.mCommSetting.mProductNum;
        pStats->mName = pdSetting.mName;
        mPDStatsList.append(pStats);
    }

    void close()
    {
        closeReader();
        closeWriter();
    }

    void openReader()
    {
        close();

        mpReaderThread = new QThread;
        mpReader   = new FileReaderEx;
        mpReader->moveToThread(mpReaderThread);
        mpReaderThread->start();

        connect(mpReaderThread, &QThread::finished, mpReader, &QObject::deleteLater);
        connect(this, SIGNAL(signalCommandOpen(QString, QString)), mpReader, SLOT(onCommandOpen(QString, QString)));
        connect(this, SIGNAL(signalCommandReadMultiLine(int)), mpReader, SLOT(onCommandReadMultiLine(int)));
        connect(mpReader, SIGNAL(signalEventReadMultiLine(QStringList)), this, SLOT(onReadFile(QStringList)));

        emit signalCommandOpen(FileDef::WORK_DIR(), FileDef::WORK_FILENAME());
    }

    void closeReader()
    {
        if(mpReader != nullptr)
        {
            disconnect(this, SIGNAL(signalCommandOpen(QString, QString)), mpReader, SLOT(onCommandOpen(QString, QString)));
            disconnect(this, SIGNAL(signalCommandReadMultiLine(int)), mpReader, SLOT(onCommandReadMultiLine(int)));
            disconnect(mpReader, SIGNAL(signalEventReadMultiLine(QStringList)), this, SLOT(onReadFile(QStringList)));
            mpReader= nullptr;
        }

        if(mpReaderThread != nullptr)
        {
            if(mpReaderThread->isRunning())
            {
                mpReaderThread->quit();
                mpReaderThread->wait();
            }

            mpReaderThread->deleteLater();

            mpReaderThread = nullptr;
        }
    }

    void readFile()
    {
        emit signalCommandReadMultiLine(3000);
    }

    void openWriter()
    {
        close();

        mpWriter = new FileWriterEx(this);

        if(mpWriter->open(FileDef::WORK_DIR(), FileDef::WORK_FILENAME(), FileWriterEx::eOpenMode::FILE_OPEN_APPENDWRITE) == false)
            closeWriter();
    }

    void closeWriter()
    {
        if(mpWriter != nullptr)
        {
            mpWriter->close();
            delete mpWriter;
            mpWriter = nullptr;
        }
    }

    void write(QString line)
    {
        CHECK_FALSE_RETURN((mpWriter != nullptr))

        mpWriter->appendLine(line);
    }


    void procWCEvent(EventDto event)
    {
        // 현재 선택된 제품이 없거나, 선택된 제품과 다른 이벤트가 들어오면 해당 제품을 찾고, 아니면 현재 제품 정보를 갱신한다.
        if(mCurrPD.mSeq == 0 || mCurrPD.mSeq != event.mPDSeq)
        {
            swapCurrPD(event.mPDSeq);
        }

        CHECK_FALSE_RETURN((mCurrPD.mSeq != 0))

        switch (event.mEType)
        {
            case EnumDef::ET_WEIGHT_NORMAL         : mCurrPD.mWCTotalCnt++; mCurrPD.mWCTradeCnt ++; mCurrPD.mWCNorCnt ++; mCurrPD.mWCTradeTotalWeight += (quint64)event.mEValue; break;
            case EnumDef::ET_WEIGHT_UNDER_WARNING  : mCurrPD.mWCTotalCnt++; mCurrPD.mWCTradeCnt ++; mCurrPD.mWCUWCnt  ++; mCurrPD.mWCTradeTotalWeight += (quint64)event.mEValue; break;
            case EnumDef::ET_WEIGHT_OVER_WARNING   : mCurrPD.mWCTotalCnt++; mCurrPD.mWCTradeCnt ++; mCurrPD.mWCOWCnt  ++; mCurrPD.mWCTradeTotalWeight += (quint64)event.mEValue; break;
            case EnumDef::ET_WEIGHT_UNDER          : mCurrPD.mWCTotalCnt++; mCurrPD.mWCUCnt     ++;                                                                              break;
            case EnumDef::ET_WEIGHT_OVER           : mCurrPD.mWCTotalCnt++; mCurrPD.mWCOCnt     ++;                                                                              break;
            case EnumDef::ET_WEIGHT_ETCERROR       : mCurrPD.mWCTotalCnt++; mCurrPD.mWCEtcCnt   ++;                                                                              break;
            case EnumDef::ET_WEIGHT_ETC_METAL_ERROR: mCurrPD.mWCTotalCnt++; mCurrPD.mWCMDCnt    ++;                                                                              break;
        }

        mTRManager.addWCTrends(event);
    }

    void procMDEvent(EventDto event)
    {
        // 현재 선택된 제품이 없거나, 선택된 제품과 다른 이벤트가 들어오면 해당 제품을 찾고, 아니면 현재 제품 정보를 갱신한다.
        if(mCurrPD.mSeq == 0 || mCurrPD.mSeq != event.mPDSeq)
        {
            swapCurrPD(event.mPDSeq);
        }

        CHECK_FALSE_RETURN((mCurrPD.mSeq != 0))

        switch (event.mEType)
        {
            case EnumDef::ET_METAL_TRADE  : mCurrPD.mMDTotalCnt++; mCurrPD.mMDPassCnt ++; break;
            case EnumDef::ET_METAL_DETECT : mCurrPD.mMDTotalCnt++; mCurrPD.mMDFailCnt ++; break;
        }

         mTRManager.addMDTrends(event);
    }

    void swapCurrPD(quint64 pdSeq)
    {
        PDStatsDto * pOldPDStats = nullptr;
        PDStatsDto * pNewPDStats = nullptr;

        if(pdSeq != mCurrPD.mSeq)
        {
            // 제품이 바뀌면 metal trends는 모두 삭제한다.
            mTRManager.clearMDTrends();
        }

        if(mCurrPD.mSeq != 0)
            pOldPDStats = findPDStats(mCurrPD.mSeq);

        pNewPDStats = findPDStats(pdSeq);

        if(pOldPDStats != nullptr)
        {
            *pOldPDStats = mCurrPD;
        }

        mCurrPD.reset();

        if(pNewPDStats != nullptr)
        {
            mCurrPD = *pNewPDStats;
        }
    }

};

#endif // WORKSPROVIDER_H
