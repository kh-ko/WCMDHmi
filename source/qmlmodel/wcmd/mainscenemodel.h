#ifndef MAINSCENEMODEL_H
#define MAINSCENEMODEL_H

#include <QObject>
#include "source/service/coreservice.h"

class MainSceneModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString company       READ getCompany             NOTIFY signalEventChangedCompany      )
    Q_PROPERTY(QString tel           READ getTel                 NOTIFY signalEventChangedTel          )
    Q_PROPERTY(bool    isRun         READ getIsRun               NOTIFY signalEventChangedIsRun        )
    Q_PROPERTY(bool    isComm        READ getIsComm              NOTIFY signalEventChangedIsComm       )
    Q_PROPERTY(bool    isAlarm       READ getIsAlarm             NOTIFY signalEventChangedIsAlarm      )
    Q_PROPERTY(bool    IsSensorAlarm READ getIsSensorAlarm       NOTIFY signalEventChangedIsSensorAlarm)
    Q_PROPERTY(bool    IsPhotoAlarm  READ getIsPhotoAlarm        NOTIFY signalEventChangedIsPhotoAlarm )
    Q_PROPERTY(bool    IsMortorAlarm READ getIsMortorAlarm       NOTIFY signalEventChangedIsMortorAlarm)
    Q_PROPERTY(QString clock         READ getClock               NOTIFY signalEventChangedClock        )

public:
    CoreService         * mpCoreService ;
    InformationModel    * mpInformation ;
    DspStatusModel      * mpDspStatus   ;

    QString mCompany       = "";
    QString mTel           = "";
    bool    mIsRun         = false;
    bool    mIsComm        = false;
    bool    mIsAlarm       = false;
    bool    mIsSensorAlarm = false;
    bool    mIsPhotoAlarm  = false;
    bool    mIsMortorAlarm = false;
    QString mClock         = "";
    QString mPassword      = "";

    QString  getCompany      (){ return mCompany      ;}
    QString  getTel          (){ return mTel          ;}
    bool     getIsRun        (){ return mIsRun        ;}
    bool     getIsComm       (){ return mIsComm       ;}
    bool     getIsAlarm      (){ return mIsAlarm      ;}
    bool     getIsSensorAlarm(){ return mIsSensorAlarm;}
    bool     getIsPhotoAlarm (){ return mIsPhotoAlarm ;}
    bool     getIsMortorAlarm(){ return mIsMortorAlarm;}
    QString  getClock        (){ return mClock  ;}
    void     setCompany      (QString value){ if(value == getCompany())return; mCompany = value; emit signalEventChangedCompany(value);}
    void     setTel          (QString value){ if(value == getTel    ())return; mTel     = value; emit signalEventChangedTel    (value);}
    void     setIsRun        (bool    value){ if(value == getIsRun  ())return; mIsRun   = value; emit signalEventChangedIsRun  (value);}
    void     setIsComm       (bool    value){ if(value == getIsComm ())return; mIsComm  = value; emit signalEventChangedIsComm (value);}
    void     setIsAlarm      (bool    value){ if(value == getIsAlarm())return; mIsAlarm = value; emit signalEventChangedIsAlarm(value);}
    void     setIsSensorAlarm(bool    value){ if(value == mIsSensorAlarm) return; mIsSensorAlarm = value; emit signalEventChangedIsSensorAlarm(value);}
    void     setIsPhotoAlarm (bool    value){ if(value == mIsPhotoAlarm ) return; mIsPhotoAlarm  = value; emit signalEventChangedIsPhotoAlarm (value);}
    void     setIsMortorAlarm(bool    value){ if(value == mIsMortorAlarm) return; mIsMortorAlarm = value; emit signalEventChangedIsMortorAlarm(value);}
    void     setClock  (QString value){ if(value == getClock  ())return; mClock   = value; emit signalEventChangedClock  (value);}

signals:
    void signalEventChangedCompany      (QString value);
    void signalEventChangedTel          (QString value);
    void signalEventChangedIsRun        (bool    value);
    void signalEventChangedIsComm       (bool    value);
    void signalEventChangedIsAlarm      (bool    value);
    void signalEventChangedIsSensorAlarm(bool    value);
    void signalEventChangedIsPhotoAlarm (bool    value);
    void signalEventChangedIsMortorAlarm(bool    value);
    void signalEventChangedClock        (QString value);

public slots:
    Q_INVOKABLE bool onCommandComparePwd(QString value)
    {
        if(mpCoreService->mLocalSettingService.mSecuritySetting.mPassword == value)
            return true;

        return false;
    }

    Q_INVOKABLE bool onCommandCompareAdminPwd(QString value)
    {
        if(mpCoreService->mLocalSettingService.mSecuritySetting.mAdminPassword == value)
            return true;

        return false;
    }

    Q_INVOKABLE void onCommandSetRun(bool value)
    {
        quint16 runValue = value == false ? EnumDefine::RunState::STOP : EnumDefine::RunState::RUN;

        if(mpDspStatus->mRun == EnumDefine::RunState::STOP && value == false)
            return;
        else if(mpDspStatus->mRun != EnumDefine::RunState::STOP && value == true)
            return;

        if(value && mpCoreService->mLocalSettingService.mHmiSetting.mIsDebugMode)
        {
            runValue = EnumDefine::RunState::DETECT_OFF_RUN;
        }

        mpCoreService->onCommandSendRunCmd(mpDspStatus->mSeq, runValue);
    }

//  down layer ===================================================================================
public slots:
    void onSignalEventChangedCompany      (QString value){ setCompany      ( value                              ); }
    void onSignalEventChangedTel          (QString value){ setTel          ( value                              ); }
    void onSignalEventChangedRun          (quint16 value){ setIsRun        ( value != EnumDefine::RunState::STOP); }
    void onSignalEventChangedIsComm       (bool    value){ setIsComm       ( value                              ); }
    void onSignalEventChangedIsAlarm      (bool    value){ setIsAlarm      ( value                              ); }
    void onSignalEventChangedIsSensorAlarm(bool    value){ setIsSensorAlarm( value                              ); }
    void onSignalEventChangedIsPhotoAlarm (bool    value){ setIsPhotoAlarm ( value                              ); }
    void onSignalEventChangedIsMortorAlarm(bool    value){ setIsMortorAlarm( value                              ); }
    void onSignalEventChangedClock        (QString value){ setClock        ( value                              ); }

//  internal layer ===================================================================================
public:
    explicit MainSceneModel(QObject *parent = nullptr): QObject(parent)
    {
        mpCoreService = CoreService::getInstance();

        mpDspStatus   = mpCoreService->mMapDspStatus.first();
        mpInformation = &(mpCoreService->mLocalSettingService.mInformation);

        connect(mpInformation,  SIGNAL(signalEventChangedCompany        (QString)),this, SLOT(onSignalEventChangedCompany       (QString)));
        connect(mpInformation,  SIGNAL(signalEventChangedTel            (QString)),this, SLOT(onSignalEventChangedTel           (QString)));
        connect(mpDspStatus  ,  SIGNAL(signalEventChangedRun            (quint16)),this, SLOT(onSignalEventChangedRun           (quint16)));
        connect(mpDspStatus  ,  SIGNAL(signalEventChangedIsComm         (bool   )),this, SLOT(onSignalEventChangedIsComm        (bool   )));
        connect(mpDspStatus  ,  SIGNAL(signalEventChangedIsAlarm        (bool   )),this, SLOT(onSignalEventChangedIsAlarm       (bool   )));
        connect(mpDspStatus  ,  SIGNAL(signalEventChangedIsSensorAlarm  (bool   )),this, SLOT(onSignalEventChangedIsSensorAlarm (bool   )));
        connect(mpDspStatus  ,  SIGNAL(signalEventChangedIsPhotoAlarm   (bool   )),this, SLOT(onSignalEventChangedIsPhotoAlarm  (bool   )));
        connect(mpDspStatus  ,  SIGNAL(signalEventChangedIsMortorAlarm  (bool   )),this, SLOT(onSignalEventChangedIsMortorAlarm (bool   )));
        connect(mpCoreService,  SIGNAL(signalEventChangedClock          (QString)),this, SLOT(onSignalEventChangedClock         (QString)));

        onSignalEventChangedCompany       (mpInformation->mCompany    );
        onSignalEventChangedTel           (mpInformation->mTel        );
        onSignalEventChangedRun           (mpDspStatus->mRun          );
        onSignalEventChangedIsComm        (mpDspStatus->mIsComm       );
        onSignalEventChangedIsAlarm       (mpDspStatus->mIsAlarm      );
        onSignalEventChangedIsSensorAlarm (mpDspStatus->mIsSensorAlarm);
        onSignalEventChangedIsPhotoAlarm  (mpDspStatus->mIsPhotoAlarm );
        onSignalEventChangedIsMortorAlarm (mpDspStatus->mIsMortorAlarm);
    }
};

#endif // MAINSCENEMODEL_H
