#ifndef HISTORYBACKUPTHREAD_H
#define HISTORYBACKUPTHREAD_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <QDateTime>

#include "source/globaldef/EnumDefine.h"

class HistoryBackupThread : public QObject
{
    Q_OBJECT
public:
    QThread  mThread          ;
    QTimer * mpTimer          = nullptr;
    bool *   mpCancle         = nullptr;
    bool     mIsScanUsb       = false;
    bool     mIsProc          = false;
    int      mDevNum          = 0;
    int      mFYear           = 0;
    int      mFMonth          = 0;
    int      mFDay            = 0;
    int      mTYear           = 0;
    int      mTMonth          = 0;
    int      mTDay            = 0;
    qint64   mCheckStartMSec  = 0;
    quint64  mTotalCnt        = 1;
    quint64  mCurrentIdx      = 1;

    void setIsScanUsb (bool    value){ if(mIsScanUsb  == value) return; mIsScanUsb  = value; emit signalEventChangedIsScanUsb (mIsScanUsb );}
    void setIsProc    (bool    value){ if(mIsProc     == value) return; mIsProc     = value; emit signalEventChangedIsProc    (mIsProc    );}
    void setTotalCnt  (quint64 value){ if(mTotalCnt   == value) return; mTotalCnt   = value; emit signalEventChangedTotalCnt  (mTotalCnt  );}
    void setCurrentIdx(quint64 value){ if(mCurrentIdx == value) return; mCurrentIdx = value; emit signalEventChangedCurrentIdx(mCurrentIdx);}

    void setCanclePtr(bool * pCancle){mpCancle = pCancle;}
    bool getCancle(){ return * mpCancle;}
    void mkdirBackupFolder(QString deviceNum);
    explicit HistoryBackupThread(QObject *parent = nullptr);
    ~HistoryBackupThread();

signals:
    void signalEventCompleted             (int     value);
    void signalEventChangedIsScanUsb      (bool    value);
    void signalEventChangedIsProc         (bool    value);
    void signalEventChangedTotalCnt       (quint64 value);
    void signalEventChangedCurrentIdx     (quint64 value);


public slots:
    void onCommandBackup(int deviceNumber, int startYear, int startMonth, int startDay, int endYear, int endMonth, int endDay, bool *pCancle);
    void checkUsb();

private:
    void startUsbCheckTimer();
    void stopUsbCheckTimer();
    void backupProc();
    void backupComplete(EnumDefine::BackupResult result);
};

#endif // HISTORYBACKUPTHREAD_H
