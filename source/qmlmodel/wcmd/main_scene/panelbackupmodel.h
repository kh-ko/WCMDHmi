#ifndef PANELBACKUPMODEL_H
#define PANELBACKUPMODEL_H

#include <QObject>
#include <QProcess>

#include "source/globaldef/EnumDefine.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"
#include "source/thread/historybackupthread.h"

class PanelBackupModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool     isNeedBackup     READ getIsNeedBackup     NOTIFY signalEventChangedIsNeedBackup   );
    Q_PROPERTY(bool     isScanUsb        READ getIsScanUsb        NOTIFY signalEventChangedIsScanUsb      );
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
    HistoryBackupThread   mBackupThread     ;
    QString               mHistoryPath      ;
    bool    mCancle             = false;

    bool    mIsNeedBackup       = false;
    bool    mIsScanUsb          = false;
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
    bool    getIsScanUsb      (){return mIsScanUsb      ;}
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
    void setIsScanUsb      (bool     value){ if(value == mIsScanUsb      ) return; mIsScanUsb       = value; emit signalEventChangedIsScanUsb      (value);}
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
    void signalEventChangedIsScanUsb      (bool     value);
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

        year = pLSettingSP->mBackupLastDate.year();
        month = pLSettingSP->mBackupLastDate.month();
        day = pLSettingSP->mBackupLastDate.day();

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

        mCancle = false;

        int deviceNumber = pLSettingSP->mInformation.mDeviceNumber;
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
    void onSignalEventChangedIsScanUsb      (bool    value){setIsScanUsb    (value);}
    void onSignalEventChangedIsProc         (bool    value){setIsProc       (value);}
    void onSignalEventChangedTotalCnt       (quint64 value){setTotalCnt     (value);}
    void onSignalEventChangedCurrentIdx     (quint64 value){setCurrentIdx   (value);}
    void onSignalEventCompleted             (int     value)
    {
        setIsProc(false);
        checkDisk();

        QDate date(mEndYear,mEndMonth,mEndDay);

        if(value == EnumDefine::BackupResult::BACKUP_NONE_ERROR)
            pLSettingSP->setBackupLastDate(date);

        emit signalEventComplete(value);
    }

//  internal layer ===================================================================================
public:
    void checkDisk()
    {
        QProcess process;
        qint64 total;
        qint64 available;
        qint64 delSize;
        qint64 warningSize;
        process.start("df ");
        process.waitForFinished(-1); // will wait forever until finished

        QString output = process.readAllStandardOutput();
        QStringList outputLine = output.split("\n");
        QString root;

        for(int i = 0; i < outputLine.size(); i ++)
        {
            if(outputLine.at(i).startsWith("/dev/root"))
            {
                root = outputLine.at(i);
                break;
            }
        }

        QStringList colList = root.split(QRegExp("[\r\n\t ]+"), QString::SkipEmptyParts);

        total = colList.at(1).toDouble() * 1024;
        available = colList.at(3).toDouble() * 1024;

        delSize = total * 0.1 - available;
        warningSize = total * 0.2 - available;

        QStringList delFileList;
        qint64 backupDateNumber = (pLSettingSP->mBackupLastDate.year() * 10000)
                                + (pLSettingSP->mBackupLastDate.month() * 100)
                                + (pLSettingSP->mBackupLastDate.day());

        setIsNeedBackup(false);

        qDebug() << "[PanelBackupModel::checkDisk]total size = " << total;
        qDebug() << "[PanelBackupModel::checkDisk]available  size = " << available;
        qDebug() << "[PanelBackupModel::checkDisk]delSize = " << delSize;
        qDebug() << "[PanelBackupModel::checkDisk]warningSize = " << warningSize;

        if(warningSize > 0)
        {
            QDir dir(mHistoryPath);
            QStringList fileList = dir.entryList(QStringList() << "*.txt",QDir::Files,QDir::SortFlag::Name);

            for(int i = 0; i < fileList.size(); i ++)
            {
                QFileInfo fInfo(QString("%1/%2").arg(mHistoryPath).arg(fileList.at(i)));
                qint64 dateNumber = (fInfo.fileName().split("-")[0].toLongLong() * 10000) + (fInfo.fileName().split("-")[1].toLongLong() * 100) + (fInfo.fileName().split("-")[2].toLongLong());

                if(delSize > 0 )
                {                    
                    delSize = delSize - fInfo.size();
                    delFileList.append(fInfo.fileName());

                    qDebug() << "[PanelBackupModel::checkDisk]del file = " << fInfo.fileName() << ", remain del size =" << delSize;
                }

                if(warningSize > 0 )
                {
                    warningSize = warningSize - fInfo.size();

                    qDebug() << "[PanelBackupModel::checkDisk]file dateNumber = " << dateNumber << ", backupDateNumber =" <<backupDateNumber << ", remain warningSize =" << warningSize;

                    if(backupDateNumber < dateNumber)
                        setIsNeedBackup(true);
                }
            }
        }

        for(int i = 0; i < delFileList.size(); i ++)
        {
            QFile::remove(QString("%1/%2").arg(mHistoryPath).arg(delFileList.at(i)));
        }
    }

    explicit PanelBackupModel(QObject *parent = nullptr) : QObject(parent)
    {
        mHistoryPath     = FileDef::HISTORY_DIR();//mpCoreService->mEventService.mDailyHistoryPath;

        checkDisk();

        connect(this, SIGNAL(signalCommandBackup(int, int, int, int, int, int, int, bool *)), &mBackupThread, SLOT(onCommandBackup(int, int, int, int, int, int, int, bool *)));

        connect(&mBackupThread, SIGNAL(signalEventCompleted        (int    )), this, SLOT(onSignalEventCompleted             (int    )));
        connect(&mBackupThread, SIGNAL(signalEventChangedIsScanUsb (bool   )), this, SLOT(onSignalEventChangedIsScanUsb      (bool   )));
        connect(&mBackupThread, SIGNAL(signalEventChangedIsProc    (bool   )), this, SLOT(onSignalEventChangedIsProc         (bool   )));
        connect(&mBackupThread, SIGNAL(signalEventChangedTotalCnt  (quint64)), this, SLOT(onSignalEventChangedTotalCnt       (quint64)));
        connect(&mBackupThread, SIGNAL(signalEventChangedCurrentIdx(quint64)), this, SLOT(onSignalEventChangedCurrentIdx     (quint64)));
    }
};

#endif // PANELBACKUPMODEL_H
