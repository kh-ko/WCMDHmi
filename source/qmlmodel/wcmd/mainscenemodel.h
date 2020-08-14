#ifndef MAINSCENEMODEL_H
#define MAINSCENEMODEL_H

#include <QObject>
#include "source/service/wcmdservice.h"
#include "source/model/Information.h"
#include "source/model/devicestatus.h"

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

private:
    QTimer mTimer;

public:
    QString mCompany;
    QString mTel    ;
    bool    mIsRun  ;
    bool    mIsComm ;
    bool    mIsAlarm;
    bool    mIsSensorAlarm;
    bool    mIsPhotoAlarm ;
    bool    mIsMortorAlarm;
    QString mClock  ;
    QString mPassword;

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
    explicit MainSceneModel(QObject *parent = nullptr);

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

    void signalCommandSetRun      (quint16 deviceSeq, quint16 value);

public slots:
    void onSignalEventChangedInformation            (Information value);
    void onSignalEventChangedIsConnect              (quint16 deviceSeq, bool value);
    void onSignalEventChangedRemoteDeviceSetting    (quint16 deviceSeq, DeviceSetting value);
    void onSignalEventChangedRemoteProductSetting   (quint16 deviceSeq, ProductSetting value);
    void onSignalEventChangedDeviceStatus           (quint16 deviceSeq, DeviceStatus value);
    void onSignalEventChangedDsp                    (int type, DeviceConnectionInfo value);

    void onUpdateTimer                    ();

public slots:
    Q_INVOKABLE bool onCommandComparePwd(QString value);
    Q_INVOKABLE bool onCommandCompareAdminPwd(QString value);
    Q_INVOKABLE void onCommandSetRun(bool value);
};

#endif // MAINSCENEMODEL_H
