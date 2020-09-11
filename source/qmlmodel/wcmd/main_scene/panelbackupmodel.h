#ifndef PANELBACKUPMODEL_H
#define PANELBACKUPMODEL_H

#include <QObject>

#include "source/util/etcutil.h"
#include "source/service/coreservice.h"
#include "source/thread/historybackupthread.h"

class PanelBackupModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool     isNeedBackup     READ getIsNeedBackup     NOTIFY signalEventChangedIsNeedBackup   );
    Q_PROPERTY(bool     isProc           READ getIsProc           NOTIFY signalEventChangedIsProc         );
    Q_PROPERTY(bool     isShowInterface  READ getIsShowInterface  NOTIFY signalEventChangedIsShowInterface);
    Q_PROPERTY(quint64  totalCnt         READ getTotalCnt         NOTIFY signalEventChangedTotalCnt       );
    Q_PROPERTY(quint64  currentIdx       READ getCurrentIdx       NOTIFY signalEventChangedCurrentIdx     );
    Q_PROPERTY(int      startYear        READ getStartYear        NOTIFY signalEventChangedStartYear      );
    Q_PROPERTY(int      startMonth       READ getStartMonth       NOTIFY signalEventChangedStartMonth     );
    Q_PROPERTY(int      startDay         READ getStartDay         NOTIFY signalEventChangedStartDay       );
    Q_PROPERTY(int      endYear          READ getEndYear          NOTIFY signalEventChangedEndYear        );
    Q_PROPERTY(int      endMonth         READ getEndMonth         NOTIFY signalEventChangedEndMonth       );
    Q_PROPERTY(int      endDay           READ getEndDay           NOTIFY signalEventChangedEndDay         );

public:
    CoreService         * mpCoreService     ;
    ProcSettingModel    * mpProcSetting     ;
    HistoryBackupThread   mBackupThread     ;
    bool    mCancle             = false;

    bool    mIsNeedBackup       = false;
    bool    mIsProc             = false;
    bool    mIsShowInterface    = false;
    quint64 mTotalCnt           = 0;
    quint64 mCurrentIdx         = 0;
    int     mStartYear          = 0;
    int     mStartMonth         = 0;
    int     mStartDay           = 0;
    int     mEndYear            = 0;
    int     mEndMonth           = 0;
    int     mEndDay             = 0;

    bool    getIsNeedBackup   (){return mIsNeedBackup   ;}
    bool    getIsProc         (){return mIsProc         ;}
    bool    getIsShowInterface(){return mIsShowInterface;}
    quint64 getTotalCnt       (){return mTotalCnt       ;}
    quint64 getCurrentIdx     (){return mCurrentIdx     ;}
    int     getStartYear      (){return mStartYear      ;}
    int     getStartMonth     (){return mStartMonth     ;}
    int     getStartDay       (){return mStartDay       ;}
    int     getEndYear        (){return mEndYear        ;}
    int     getEndMonth       (){return mEndMonth       ;}
    int     getEndDay         (){return mEndDay         ;}

    void setIsNeedBackup   (bool     value){ if(value == mIsNeedBackup   ) return; mIsNeedBackup    = value; emit signalEventChangedIsNeedBackup   (value);}
    void setIsProc         (bool     value){ if(value == mIsProc         ) return; mIsProc          = value; emit signalEventChangedIsProc         (value);}
    void setIsShowInterface(bool     value){ if(value == mIsShowInterface) return; mIsShowInterface = value; emit signalEventChangedIsShowInterface(value);}
    void setTotalCnt       (quint64  value){ if(value == mTotalCnt       ) return; mTotalCnt        = value; emit signalEventChangedTotalCnt       (value);}
    void setCurrentIdx     (quint64  value){ if(value == mCurrentIdx     ) return; mCurrentIdx      = value; emit signalEventChangedCurrentIdx     (value);}
    void setStartYear      (int      value){ if(value == mStartYear      ) return; mStartYear       = value; emit signalEventChangedStartYear      (value);}
    void setStartMonth     (int      value){ if(value == mStartMonth     ) return; mStartMonth      = value; emit signalEventChangedStartMonth     (value);}
    void setStartDay       (int      value){ if(value == mStartDay       ) return; mStartDay        = value; emit signalEventChangedStartDay       (value);}
    void setEndYear        (int      value){ if(value == mEndYear        ) return; mEndYear         = value; emit signalEventChangedEndYear        (value);}
    void setEndMonth       (int      value){ if(value == mEndMonth       ) return; mEndMonth        = value; emit signalEventChangedEndMonth       (value);}
    void setEndDay         (int      value){ if(value == mEndDay         ) return; mEndDay          = value; emit signalEventChangedEndDay         (value);}

signals:
    void signalEventChangedIsNeedBackup   (bool     value);
    void signalEventChangedIsProc         (bool     value);
    void signalEventChangedIsShowInterface(bool     value);
    void signalEventChangedTotalCnt       (quint64  value);
    void signalEventChangedCurrentIdx     (quint64  value);
    void signalEventChangedStartYear      (int      value);
    void signalEventChangedStartMonth     (int      value);
    void signalEventChangedStartDay       (int      value);
    void signalEventChangedEndYear        (int      value);
    void signalEventChangedEndMonth       (int      value);
    void signalEventChangedEndDay         (int      value);

    void signalEventComplete              (int      error);


public slots:
    void onCommandShowInterface()
    {
        if(getIsProc())
        {
            setIsShowInterface(true);
            return;
        }

        QDate endDate = QDate::currentDate();

        int year;
        int month;
        int day;

        year = mpProcSetting->mLastBackupYear;
        month = mpProcSetting->mLastBackupMonth;
        day = mpProcSetting->mLastBackupDay;

        onCommandSetStartDate(year , month, day);
        onCommandSetEndDate(endDate.year(), endDate.month(), endDate.day());

        setIsShowInterface(true);
    }
    void onCommandCloseInterface()
    {
        setIsShowInterface(false);
    }
    void onCommandSetStartDate(int year, int month, int day)
    {
        int maxDay = EtcUtil::checkMaxDay(year, month);
        int calDay = maxDay < day ? maxDay : day;

        setStartYear(year);
        setStartMonth(month);
        setStartDay(calDay);

        if((year > mEndYear) || (year == mEndYear && month > mEndMonth) || (year == mEndYear && month == mEndMonth && calDay > mEndDay) || (year == mEndYear && month == mEndMonth && calDay == mEndDay))
        {
            onCommandSetEndDate(year, month, calDay);
        }
    }
    void onCommandSetEndDate(int year, int month, int day)
    {
        QDate date = QDate::currentDate();
        int maxDay = EtcUtil::checkMaxDay(year, month);
        int calDay = maxDay < day ? maxDay : day;

        if((year > date.year()) || (year == date.year() && month > date.month()) || (year == date.year() && month == date.month() && calDay > date.day()))
        {
            setEndYear (date.year());
            setEndMonth(date.month());
            setEndDay  (date.day());

            setStartYear (date.year() );
            setStartMonth(date.month());
            setStartDay  (date.day()  );
        }
        else
        {
            setEndYear(year);
            setEndMonth(month);
            setEndDay(calDay);

            if((year < mStartYear) || (year == mStartYear && month < mStartMonth) || (year == mStartYear && month == mStartMonth && calDay < mStartDay) || (year == mStartYear && month == mStartMonth && calDay == mStartDay))
            {
                setStartYear(year);
                setStartMonth(month);
                setStartDay(calDay);
            }
        }
    }
    void onCommandBackup()
    {
        qDebug() << "onCommandBackup()";

        if(getIsProc())
        {
            emit signalEventComplete(EnumDefine::BackupResult::BACKUP_ING);
            return;
        }

        setIsProc(true);
        setIsShowInterface(false);

        int deviceNumber = mpCoreService->mLocalSettingService.mInformation.mDeviceNumber;
        emit signalCommandBackup(deviceNumber, mStartYear, mStartMonth, mStartDay, mEndYear, mEndMonth, mEndDay, &mCancle);
    }
    void onCommandCancle()
    {
        mCancle = true;
    }
    void onCommandUpdate(){}

// down layer =======================================================================================
signals:
    void signalCommandBackup(int deviceNumber, int startYear, int startMonth, int startDay, int endYear, int endMonth, int endDay, bool *pCancle);

public slots:
    void onSignalEventChangedIsProc         (bool    value){setIsProc       (value);}
    void onSignalEventChangedTotalCnt       (quint64 value){setTotalCnt     (value);}
    void onSignalEventChangedCurrentIdx     (quint64 value){setCurrentIdx   (value);}
    void onSignalEventCompleted             (int     value)
    {
        if(value == EnumDefine::BackupResult::BACKUP_NONE_ERROR)
            mpCoreService->mLocalSettingService.setProcBackupLastDate(mEndYear, mEndMonth, mEndDay);

        emit signalEventComplete(value);
    }

//  internal layer ===================================================================================
public:
    explicit PanelBackupModel(QObject *parent = nullptr) : QObject(parent)
    {
        mpCoreService    = CoreService::getInstance();
        mpProcSetting     = &(mpCoreService->mLocalSettingService.mProcSetting);

        connect(this, SIGNAL(signalCommandBackup(int, int, int, int, int, int, int, bool *)), &mBackupThread, SLOT(onCommandBackup(int, int, int, int, int, int, int, bool *)));

        connect(&mBackupThread, SIGNAL(signalEventCompleted        (int    )), this, SLOT(onSignalEventCompleted             (int    )));
        connect(&mBackupThread, SIGNAL(signalEventChangedIsProc    (bool   )), this, SLOT(onSignalEventChangedIsProc         (bool   )));
        connect(&mBackupThread, SIGNAL(signalEventChangedTotalCnt  (quint64)), this, SLOT(onSignalEventChangedTotalCnt       (quint64)));
        connect(&mBackupThread, SIGNAL(signalEventChangedCurrentIdx(quint64)), this, SLOT(onSignalEventChangedCurrentIdx     (quint64)));
    }
};

#endif // PANELBACKUPMODEL_H
