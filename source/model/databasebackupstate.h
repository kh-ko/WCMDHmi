#ifndef DATABASEBACKUPSTATE_H
#define DATABASEBACKUPSTATE_H

#include <QObject>
#include "source/globaldef/EnumDefine.h"

class DatabaseBackupState
{
public:
    QString mHMISerialNumber      ;
    int     mHMIDeviceNumber      ;
    quint64 mTotalCount           ;
    quint64 mProgressCount        ;
    quint64 mEndSeq               ;
    bool    mIsDone               ;
    bool    mIsCancle             ;
    int     mBackupProcStartYear  ;
    int     mBackupProcStartMonth ;
    int     mBackupProcStartDay   ;
    int     mBackupProcEndYear    ;
    int     mBackupProcEndMonth   ;
    int     mBackupProcEndDay     ;
    EnumDefine::BackupResult mResult;

    DatabaseBackupState()
    {
        mTotalCount    = 0     ;
        mProgressCount = 0     ;
        mIsDone        = false ;
        mIsCancle      = false ;
        mResult = EnumDefine::BackupResult::BACKUP_NONE_ERROR;

        mBackupProcStartYear   = 0;
        mBackupProcStartMonth  = 0;
        mBackupProcStartDay    = 0;
        mBackupProcEndYear     = 0;
        mBackupProcEndMonth    = 0;
        mBackupProcEndDay      = 0;
        mEndSeq                = 0;
    }
    ~DatabaseBackupState(){}
    void reset(){
        mTotalCount    = 0     ;
        mProgressCount = 0     ;
        mIsDone        = false ;
        mIsCancle      = false ;
        mResult = EnumDefine::BackupResult::BACKUP_NONE_ERROR;

        mBackupProcStartYear   = 0;
        mBackupProcStartMonth  = 0;
        mBackupProcStartDay    = 0;
        mBackupProcEndYear     = 0;
        mBackupProcEndMonth    = 0;
        mBackupProcEndDay      = 0;
        mEndSeq                = 0;
    }

    QString                     getHMISerialNumber      (){ return mHMISerialNumber      ;}
    int                         getHMIDeviceNumber      (){ return mHMIDeviceNumber      ;}
    quint64                     getTotalCount           (){ return mTotalCount           ;}
    quint64                     getProgressCount        (){ return mProgressCount        ;}
    bool                        getIsDone               (){ return mIsDone               ;}
    bool                        getIsCancle             (){ return mIsCancle             ;}
    int                         getBackupProcStartYear  (){ return mBackupProcStartYear  ;}
    int                         getBackupProcStartMonth (){ return mBackupProcStartMonth ;}
    int                         getBackupProcStartDay   (){ return mBackupProcStartDay   ;}
    int                         getBackupProcEndYear    (){ return mBackupProcEndYear    ;}
    int                         getBackupProcEndMonth   (){ return mBackupProcEndMonth   ;}
    int                         getBackupProcEndDay     (){ return mBackupProcEndDay     ;}
    quint64                     getEndSeq               (){ return mEndSeq               ;}
    EnumDefine::BackupResult    getResult               (){ return mResult               ;}

    void    setHMISerialNumber      (QString value                 ){mHMISerialNumber= value;}
    void    setHMIDeviceNumber      (int     value                 ){mHMIDeviceNumber= value;}
    void    setTotalCount           (quint64 value                 ){ mTotalCount    = value;}
    void    setProgressCount        (quint64 value                 ){ mProgressCount = value;}
    void    setIsDone               (bool    value                 ){ mIsDone        = value;}
    void    setIsCancle             (bool    value                 ){ mIsCancle      = value;}
    void    setBackupProcStartYear  (int value                     ){mBackupProcStartYear  = value;}
    void    setBackupProcStartMonth (int value                     ){mBackupProcStartMonth = value;}
    void    setBackupProcStartDay   (int value                     ){mBackupProcStartDay   = value;}
    void    setBackupProcEndYear    (int value                     ){mBackupProcEndYear    = value;}
    void    setBackupProcEndMonth   (int value                     ){mBackupProcEndMonth   = value;}
    void    setBackupProcEndDay     (int value                     ){mBackupProcEndDay     = value;}
    void    setEndSeq               (quint64 value                 ){mEndSeq               = value;}
    void    setResult               (EnumDefine::BackupResult value){ mResult        = value;}
};

#endif // DATABASEBACKUPSTATE_H
