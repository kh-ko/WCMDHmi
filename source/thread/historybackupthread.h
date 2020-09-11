#ifndef HISTORYBACKUPTHREAD_H
#define HISTORYBACKUPTHREAD_H

#include <QObject>
#include <QThread>

class HistoryBackupThread : public QObject
{
    Q_OBJECT
public:
    QThread  mThread     ;
    bool *   mpCancle    = nullptr;
    bool     mIsProc     = false;
    quint64  mTotalCnt   = 1;
    quint64  mCurrentIdx = 1;

    void setIsProc    (bool    value){ if(mIsProc     == value) return; mIsProc     = value; emit signalEventChangedIsProc    (mIsProc    );}
    void setTotalCnt  (quint64 value){ if(mTotalCnt   == value) return; mTotalCnt   = value; emit signalEventChangedTotalCnt  (mTotalCnt  );}
    void setCurrentIdx(quint64 value){ if(mCurrentIdx == value) return; mCurrentIdx = value; emit signalEventChangedCurrentIdx(mCurrentIdx);}

    void setCanclePtr(bool * pCancle){mpCancle = pCancle;}
    bool getCancle(){ return * mpCancle;}
    explicit HistoryBackupThread(QObject *parent = nullptr);
    ~HistoryBackupThread();

signals:
    void signalEventCompleted             (int     value);
    void signalEventChangedIsProc         (bool    value);
    void signalEventChangedTotalCnt       (quint64 value);
    void signalEventChangedCurrentIdx     (quint64 value);


public slots:
    void onCommandBackup(int deviceNumber, int startYear, int startMonth, int startDay, int endYear, int endMonth, int endDay, bool *pCancle);
};

#endif // HISTORYBACKUPTHREAD_H
