#ifndef PANELINFORMATIONMODEL_H
#define PANELINFORMATIONMODEL_H

#include <QObject>
#include "source/service/wcmdservice.h"

class PanelInformationModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString company                      READ getCompany                     NOTIFY  signalEventChangedCompany              )
    Q_PROPERTY(QString model                        READ getModel                       NOTIFY  signalEventChangedModel                )
    Q_PROPERTY(int     deviceNumber                 READ getDeviceNumber                NOTIFY  signalEventChangedDeviceNumber         )
    Q_PROPERTY(QString serialNumber                 READ getSerialNumber                NOTIFY  signalEventChangedSerialNumber         )    
    Q_PROPERTY(QString dspVersion                   READ getDspVersion                  NOTIFY  signalEventChangedDspVersion           )
    Q_PROPERTY(QString hmiVersion                   READ getHmiVersion                  NOTIFY  signalEventChangedHmiVersion           )
    Q_PROPERTY(QString power                        READ getPower                       NOTIFY  signalEventChangedPower                )
    Q_PROPERTY(QString homepage                     READ getHomepage                    NOTIFY  signalEventChangedHomepage             )
    Q_PROPERTY(int     maxWeight                    READ getMaxWeight                   NOTIFY  signalEventChangedMaxWeight            )
    Q_PROPERTY(quint16 sensorLength                 READ getSensorLength                NOTIFY  signalEventChangedSensorLength         )
    Q_PROPERTY(quint16 distToRejector               READ getDistToRejector              NOTIFY  signalEventChangedDistToRejector       )
    Q_PROPERTY(quint16 distBtwSensor                READ getDistBtwSensor               NOTIFY  signalEventChangedDistBtwSensor        )
    Q_PROPERTY(quint16 distToWC                     READ getDistToWC                    NOTIFY  signalEventChangedDistToWC             )
    Q_PROPERTY(quint16 distBtwPhotoToSensor         READ getDistBtwPhotoToSensor        NOTIFY  signalEventChangedDistBtwPhotoToSensor )

    Q_PROPERTY(bool    isEditDeviceNumber           READ getIsEditDeviceNumber          NOTIFY  signalEventChangedIsEditDeviceNumber            )
    Q_PROPERTY(bool    isEditPower                  READ getIsEditPower                 NOTIFY  signalEventChangedIsEditPower                   )
    Q_PROPERTY(bool    isEditHomepage               READ getIsEditHomepage              NOTIFY  signalEventChangedIsEditHomepage                )
    Q_PROPERTY(bool    isEditMaxWeight              READ getIsEditMaxWeight             NOTIFY  signalEventChangedIsEditMaxWeight               )
    Q_PROPERTY(bool    isEditSensorLength           READ getIsEditSensorLength          NOTIFY  signalEventChangedIsEditSensorLength            )
    Q_PROPERTY(bool    isEditDistToRejector         READ getIsEditDistToRejector        NOTIFY  signalEventChangedIsEditDistToRejector          )
    Q_PROPERTY(bool    isEditDistBtwSensor          READ getIsEditDistBtwSensor         NOTIFY  signalEventChangedIsEditDistBtwSensor           )
    Q_PROPERTY(bool    isEditDistToWC               READ getIsEditDistToWC              NOTIFY  signalEventChangedIsEditDistToWC                )
    Q_PROPERTY(bool    isEditDistBtwPhotoToSensor   READ getIsEditDistBtwPhotoToSensor  NOTIFY  signalEventChangedIsEditDistBtwPhotoToSensor    )

public:
    QString mCompany                   ;
    QString mModel                     ;
    int     mDeviceNumber              ;
    QString mSerialNumber              ;
    QString mDspVersion                ;
    QString mHmiVersion                ;
    QString mPower                     ;
    QString mHomepage                  ;
    int     mMaxWeight                 ;
    quint16 mSensorLength              ;
    quint16 mDistToRejector            ;
    quint16 mDistBtwSensor             ;
    quint16 mDistToWC                  ;
    quint16 mDistBtwPhotoToSensor      ;

    bool    mIsEditDeviceNumber        ;
    bool    mIsEditPower               ;
    bool    mIsEditHomepage            ;
    bool    mIsEditMaxWeight           ;
    bool    mIsEditSensorLength        ;
    bool    mIsEditDistToRejector      ;
    bool    mIsEditDistBtwSensor       ;
    bool    mIsEditDistToWC            ;
    bool    mIsEditDistBtwPhotoToSensor;

    QString getCompany                   (){ return mCompany                   ;}
    QString getModel                     (){ return mModel                     ;}
    int     getDeviceNumber              (){ return mDeviceNumber              ;}
    QString getSerialNumber              (){ return mSerialNumber              ;}
    QString getDspVersion                (){ return mDspVersion                ;}
    QString getHmiVersion                (){ return mHmiVersion                ;}
    QString getPower                     (){ return mPower                     ;}
    QString getHomepage                  (){ return mHomepage                  ;}
    int     getMaxWeight                 (){ return mMaxWeight                 ;}
    quint16 getSensorLength              (){ return mSensorLength              ;}
    quint16 getDistToRejector            (){ return mDistToRejector            ;}
    quint16 getDistBtwSensor             (){ return mDistBtwSensor             ;}
    quint16 getDistToWC                  (){ return mDistToWC                  ;}
    quint16 getDistBtwPhotoToSensor      (){ return mDistBtwPhotoToSensor      ;}

    bool    getIsEditDeviceNumber        (){ return mIsEditDeviceNumber        ;}
    bool    getIsEditPower               (){ return mIsEditPower               ;}
    bool    getIsEditHomepage            (){ return mIsEditHomepage            ;}
    bool    getIsEditMaxWeight           (){ return mIsEditMaxWeight           ;}
    bool    getIsEditSensorLength        (){ return mIsEditSensorLength        ;}
    bool    getIsEditDistToRejector      (){ return mIsEditDistToRejector      ;}
    bool    getIsEditDistBtwSensor       (){ return mIsEditDistBtwSensor       ;}
    bool    getIsEditDistToWC            (){ return mIsEditDistToWC            ;}
    bool    getIsEditDistBtwPhotoToSensor(){ return mIsEditDistBtwPhotoToSensor;}

    void    setCompany                   (QString  value){ if(value == mCompany                   ) return; mCompany                    = value; emit signalEventChangedCompany                   (value);}
    void    setModel                     (QString  value){ if(value == mModel                     ) return; mModel                      = value; emit signalEventChangedModel                     (value);}
    void    setDeviceNumber              (int      value){ if(value == mDeviceNumber              ) return; mDeviceNumber               = value; setIsEditDeviceNumber        (true);             emit signalEventChangedDeviceNumber              (value);}
    void    setSerialNumber              (QString  value){ if(value == mSerialNumber              ) return; mSerialNumber               = value; emit signalEventChangedSerialNumber              (value);}
    void    setDspVersion                (QString  value){ if(value == mDspVersion                ) return; mDspVersion                 = value; emit signalEventChangedDspVersion                (value);}
    void    setHmiVersion                (QString  value){ if(value == mHmiVersion                ) return; mHmiVersion                 = value; emit signalEventChangedHmiVersion                (value);}
    void    setPower                     (QString  value){ if(value == mPower                     ) return; mPower                      = value; setIsEditPower               (true);             emit signalEventChangedPower                     (value);}
    void    setHomepage                  (QString  value){ if(value == mHomepage                  ) return; mHomepage                   = value; setIsEditHomepage            (true);             emit signalEventChangedHomepage                  (value);}
    void    setMaxWeight                 (int      value){ if(value == mMaxWeight                 ) return; mMaxWeight                  = value; setIsEditMaxWeight           (true);             emit signalEventChangedMaxWeight                 (value);}
    void    setSensorLength              (quint16  value){ if(value == mSensorLength              ) return; mSensorLength               = value; setIsEditSensorLength        (true);             emit signalEventChangedSensorLength              (value);}
    void    setDistToRejector            (quint16  value){ if(value == mDistToRejector            ) return; mDistToRejector             = value; setIsEditDistToRejector      (true);             emit signalEventChangedDistToRejector            (value);}
    void    setDistBtwSensor             (quint16  value){ if(value == mDistBtwSensor             ) return; mDistBtwSensor              = value; setIsEditDistBtwSensor       (true);             emit signalEventChangedDistBtwSensor             (value);}
    void    setDistToWC                  (quint16  value){ if(value == mDistToWC                  ) return; mDistToWC                   = value; setIsEditDistToWC            (true);             emit signalEventChangedDistToWC                  (value);}
    void    setDistBtwPhotoToSensor      (quint16  value){ if(value == mDistBtwPhotoToSensor      ) return; mDistBtwPhotoToSensor       = value; setIsEditDistBtwPhotoToSensor(true);             emit signalEventChangedDistBtwPhotoToSensor      (value);}

    void    setIsEditDeviceNumber        (bool     value){ if(value == mIsEditDeviceNumber        ) return; mIsEditDeviceNumber         = value; emit signalEventChangedIsEditDeviceNumber        (value);}
    void    setIsEditPower               (bool     value){ if(value == mIsEditPower               ) return; mIsEditPower                = value; emit signalEventChangedIsEditPower               (value);}
    void    setIsEditHomepage            (bool     value){ if(value == mIsEditHomepage            ) return; mIsEditHomepage             = value; emit signalEventChangedIsEditHomepage            (value);}
    void    setIsEditMaxWeight           (bool     value){ if(value == mIsEditMaxWeight           ) return; mIsEditMaxWeight            = value; emit signalEventChangedIsEditMaxWeight           (value);}
    void    setIsEditSensorLength        (bool     value){ if(value == mIsEditSensorLength        ) return; mIsEditSensorLength         = value; emit signalEventChangedIsEditSensorLength        (value);}
    void    setIsEditDistToRejector      (bool     value){ if(value == mIsEditDistToRejector      ) return; mIsEditDistToRejector       = value; emit signalEventChangedIsEditDistToRejector      (value);}
    void    setIsEditDistBtwSensor       (bool     value){ if(value == mIsEditDistBtwSensor       ) return; mIsEditDistBtwSensor        = value; emit signalEventChangedIsEditDistBtwSensor       (value);}
    void    setIsEditDistToWC            (bool     value){ if(value == mIsEditDistToWC            ) return; mIsEditDistToWC             = value; emit signalEventChangedIsEditDistToWC            (value);}
    void    setIsEditDistBtwPhotoToSensor(bool     value){ if(value == mIsEditDistBtwPhotoToSensor) return; mIsEditDistBtwPhotoToSensor = value; emit signalEventChangedIsEditDistBtwPhotoToSensor(value);}

    explicit PanelInformationModel(QObject *parent = nullptr);
    void reset();

signals:
    void signalEventChangedCompany                   (QString  value);
    void signalEventChangedModel                     (QString  value);
    void signalEventChangedDeviceNumber              (int      value);
    void signalEventChangedSerialNumber              (QString  value);
    void signalEventChangedDspVersion                (QString  value);
    void signalEventChangedHmiVersion                (QString  value);
    void signalEventChangedPower                     (QString  value);
    void signalEventChangedHomepage                  (QString  value);
    void signalEventChangedMaxWeight                 (int      value);
    void signalEventChangedSensorLength              (quint16  value);
    void signalEventChangedDistToRejector            (quint16  value);
    void signalEventChangedDistBtwSensor             (quint16  value);
    void signalEventChangedDistToWC                  (quint16  value);
    void signalEventChangedDistBtwPhotoToSensor      (quint16  value);

    void signalEventChangedIsEditDeviceNumber        (bool     value);
    void signalEventChangedIsEditPower               (bool     value);
    void signalEventChangedIsEditHomepage            (bool     value);
    void signalEventChangedIsEditMaxWeight           (bool     value);
    void signalEventChangedIsEditSensorLength        (bool     value);
    void signalEventChangedIsEditDistToRejector      (bool     value);
    void signalEventChangedIsEditDistBtwSensor       (bool     value);
    void signalEventChangedIsEditDistToWC            (bool     value);
    void signalEventChangedIsEditDistBtwPhotoToSensor(bool     value);

    void signalResultSaveDeviceSetting(int error);
    void signalResultSaveInformation(int error);


    void signalCommandSaveDeviceSetting(void * sender, DeviceSetting value);
    void signalCommandSaveInformation(void * sender, Information value);

public slots:
    void onSignalResultSaveDeviceSetting(void * sender, DeviceSetting value);
    void onSignalResultSaveInformation(void * sender, Information value);

    Q_INVOKABLE void onCommandSave();
    Q_INVOKABLE void onCommandCancle();

    Q_INVOKABLE void onCommandSetCompany                   (QString  value){setCompany              (value);}
    Q_INVOKABLE void onCommandSetModel                     (QString  value){setModel                (value);}
    Q_INVOKABLE void onCommandSetDeviceNumber              (int      value){setDeviceNumber         (value);}
    Q_INVOKABLE void onCommandSetSerialNumber              (QString  value){setSerialNumber         (value);}
    Q_INVOKABLE void onCommandSetDspVersion                (QString  value){setDspVersion           (value);}
    Q_INVOKABLE void onCommandSetHmiVersion                (QString  value){setHmiVersion           (value);}
    Q_INVOKABLE void onCommandSetPower                     (QString  value){setPower                (value);}
    Q_INVOKABLE void onCommandSetHomepage                  (QString  value){setHomepage             (value);}
    Q_INVOKABLE void onCommandSetMaxWeight                 (int      value){setMaxWeight            (value);}
    Q_INVOKABLE void onCommandSetSensorLength              (quint16  value){setSensorLength         (value);}
    Q_INVOKABLE void onCommandSetDistToRejector            (quint16  value){setDistToRejector       (value);}
    Q_INVOKABLE void onCommandSetDistBtwSensor             (quint16  value){setDistBtwSensor        (value);}
    Q_INVOKABLE void onCommandSetDistToWC                  (quint16  value){setDistToWC             (value);}
    Q_INVOKABLE void onCommandSetDistBtwPhotoToSensor      (quint16  value){setDistBtwPhotoToSensor (value);}

};

#endif // PANELINFORMATIONMODEL_H
