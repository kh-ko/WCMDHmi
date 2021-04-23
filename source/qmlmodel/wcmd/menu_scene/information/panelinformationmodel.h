#ifndef PANELINFORMATIONMODEL_H
#define PANELINFORMATIONMODEL_H

#include <QObject>

#include "source/globaldef/qmlenumdef.h"
#include "source/service/coreservice.h"

class PanelInformationModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    isEnableWC                   READ getIsEnableWC                  NOTIFY  signalEventChangedIsEnableWC           )
    Q_PROPERTY(QString company                      READ getCompany                     NOTIFY  signalEventChangedCompany              )
    Q_PROPERTY(QString model                        READ getModel                       NOTIFY  signalEventChangedModel                )
    Q_PROPERTY(int     deviceNumber                 READ getDeviceNumber                NOTIFY  signalEventChangedDeviceNumber         )
    Q_PROPERTY(QString serialNumber                 READ getSerialNumber                NOTIFY  signalEventChangedSerialNumber         )    
    Q_PROPERTY(QString dspVersion                   READ getDspVersion                  NOTIFY  signalEventChangedDspVersion           )
    Q_PROPERTY(QString hmiVersion                   READ getHmiVersion                  NOTIFY  signalEventChangedHmiVersion           )
    Q_PROPERTY(QString power                        READ getPower                       NOTIFY  signalEventChangedPower                )
    Q_PROPERTY(QString ip                           READ getIp                          NOTIFY  signalEventChangedIp                   )
    Q_PROPERTY(QString homepage                     READ getHomepage                    NOTIFY  signalEventChangedHomepage             )
    Q_PROPERTY(int     maxWeight                    READ getMaxWeight                   NOTIFY  signalEventChangedMaxWeight            )
    Q_PROPERTY(quint16 sensorLength                 READ getSensorLength                NOTIFY  signalEventChangedSensorLength         )
    Q_PROPERTY(quint16 distBtwSensor                READ getDistBtwSensor               NOTIFY  signalEventChangedDistBtwSensor        )
    Q_PROPERTY(quint16 distToWC                     READ getDistToWC                    NOTIFY  signalEventChangedDistToWC             )
    Q_PROPERTY(quint16 distBtwPhotoToSensor         READ getDistBtwPhotoToSensor        NOTIFY  signalEventChangedDistBtwPhotoToSensor )
    Q_PROPERTY(quint16 distToSorter01               READ getDistToSorter01              NOTIFY  signalEventChangedDistToSorter01       )
    Q_PROPERTY(quint16 distToSorter02               READ getDistToSorter02              NOTIFY  signalEventChangedDistToSorter02       )
    Q_PROPERTY(quint16 distToSorter03               READ getDistToSorter03              NOTIFY  signalEventChangedDistToSorter03       )
    Q_PROPERTY(quint16 distToSorter04               READ getDistToSorter04              NOTIFY  signalEventChangedDistToSorter04       )

    Q_PROPERTY(bool    isEditDeviceNumber           READ getIsEditDeviceNumber          NOTIFY  signalEventChangedIsEditDeviceNumber            )
    Q_PROPERTY(bool    isEditPower                  READ getIsEditPower                 NOTIFY  signalEventChangedIsEditPower                   )
    Q_PROPERTY(bool    isEditIp                     READ getIsEditIp                    NOTIFY  signalEventChangedIsEditIp                      )
    Q_PROPERTY(bool    isEditHomepage               READ getIsEditHomepage              NOTIFY  signalEventChangedIsEditHomepage                )
    Q_PROPERTY(bool    isEditMaxWeight              READ getIsEditMaxWeight             NOTIFY  signalEventChangedIsEditMaxWeight               )
    Q_PROPERTY(bool    isEditSensorLength           READ getIsEditSensorLength          NOTIFY  signalEventChangedIsEditSensorLength            )
    Q_PROPERTY(bool    isEditDistBtwSensor          READ getIsEditDistBtwSensor         NOTIFY  signalEventChangedIsEditDistBtwSensor           )
    Q_PROPERTY(bool    isEditDistToWC               READ getIsEditDistToWC              NOTIFY  signalEventChangedIsEditDistToWC                )
    Q_PROPERTY(bool    isEditDistBtwPhotoToSensor   READ getIsEditDistBtwPhotoToSensor  NOTIFY  signalEventChangedIsEditDistBtwPhotoToSensor    )
    Q_PROPERTY(bool    isEditDistToSorter01         READ getIsEditDistToSorter01        NOTIFY  signalEventChangedIsEditDistToSorter01          )
    Q_PROPERTY(bool    isEditDistToSorter02         READ getIsEditDistToSorter02        NOTIFY  signalEventChangedIsEditDistToSorter02          )
    Q_PROPERTY(bool    isEditDistToSorter03         READ getIsEditDistToSorter03        NOTIFY  signalEventChangedIsEditDistToSorter03          )
    Q_PROPERTY(bool    isEditDistToSorter04         READ getIsEditDistToSorter04        NOTIFY  signalEventChangedIsEditDistToSorter04          )

public:
    quint64 mDspSeq                    = 0;
    bool    mIsEnableWC                = true;
    QString mCompany                   ;
    QString mModel                     ;
    int     mDeviceNumber              ;
    QString mSerialNumber              ;
    QString mDspVersion                ;
    QString mHmiVersion                ;
    QString mPower                     ;
    QString mIp                        ="";
    QString mHomepage                  ;
    int     mMaxWeight                 ;
    quint16 mSensorLength              ;
    quint16 mDistBtwSensor             ;
    quint16 mDistToWC                  ;
    quint16 mDistBtwPhotoToSensor      ;
    quint16 mDistToSorter01            ;
    quint16 mDistToSorter02            ;
    quint16 mDistToSorter03            ;
    quint16 mDistToSorter04            ;

    bool    mIsEditDeviceNumber        ;
    bool    mIsEditPower               ;
    bool    mIsEditIp                  ;
    bool    mIsEditHomepage            ;
    bool    mIsEditMaxWeight           ;
    bool    mIsEditSensorLength        ;
    bool    mIsEditDistBtwSensor       ;
    bool    mIsEditDistToWC            ;
    bool    mIsEditDistBtwPhotoToSensor;
    bool    mIsEditDistToSorter01      ;
    bool    mIsEditDistToSorter02      ;
    bool    mIsEditDistToSorter03      ;
    bool    mIsEditDistToSorter04      ;

    bool    getIsEnableWC                (){ return mIsEnableWC                ;}
    QString getCompany                   (){ return mCompany                   ;}
    QString getModel                     (){ return mModel                     ;}
    int     getDeviceNumber              (){ return mDeviceNumber              ;}
    QString getSerialNumber              (){ return mSerialNumber              ;}
    QString getDspVersion                (){ return mDspVersion                ;}
    QString getHmiVersion                (){ return mHmiVersion                ;}
    QString getPower                     (){ return mPower                     ;}
    QString getIp                        (){ return mIp                        ;}
    QString getHomepage                  (){ return mHomepage                  ;}
    int     getMaxWeight                 (){ return mMaxWeight                 ;}
    quint16 getSensorLength              (){ return mSensorLength              ;}
    quint16 getDistBtwSensor             (){ return mDistBtwSensor             ;}
    quint16 getDistToWC                  (){ return mDistToWC                  ;}
    quint16 getDistBtwPhotoToSensor      (){ return mDistBtwPhotoToSensor      ;}
    quint16 getDistToSorter01            (){ return mDistToSorter01            ;}
    quint16 getDistToSorter02            (){ return mDistToSorter02            ;}
    quint16 getDistToSorter03            (){ return mDistToSorter03            ;}
    quint16 getDistToSorter04            (){ return mDistToSorter04            ;}

    bool    getIsEditDeviceNumber        (){ return mIsEditDeviceNumber        ;}
    bool    getIsEditPower               (){ return mIsEditPower               ;}
    bool    getIsEditIp                  (){ return mIsEditIp                  ;}
    bool    getIsEditHomepage            (){ return mIsEditHomepage            ;}
    bool    getIsEditMaxWeight           (){ return mIsEditMaxWeight           ;}
    bool    getIsEditSensorLength        (){ return mIsEditSensorLength        ;}
    bool    getIsEditDistBtwSensor       (){ return mIsEditDistBtwSensor       ;}
    bool    getIsEditDistToWC            (){ return mIsEditDistToWC            ;}
    bool    getIsEditDistBtwPhotoToSensor(){ return mIsEditDistBtwPhotoToSensor;}
    bool    getIsEditDistToSorter01      (){ return mIsEditDistToSorter01      ;}
    bool    getIsEditDistToSorter02      (){ return mIsEditDistToSorter02      ;}
    bool    getIsEditDistToSorter03      (){ return mIsEditDistToSorter03      ;}
    bool    getIsEditDistToSorter04      (){ return mIsEditDistToSorter04      ;}

    void    setIsEnableWC                (bool     value){ if(value == mIsEnableWC                ) return; mIsEnableWC                 = value; emit signalEventChangedIsEnableWC                (value);}
    void    setCompany                   (QString  value){ if(value == mCompany                   ) return; mCompany                    = value; emit signalEventChangedCompany                   (value);}
    void    setModel                     (QString  value){ if(value == mModel                     ) return; mModel                      = value; emit signalEventChangedModel                     (value);}
    void    setDeviceNumber              (int      value){ if(value == mDeviceNumber              ) return; mDeviceNumber               = value; setIsEditDeviceNumber        (true);             emit signalEventChangedDeviceNumber              (value);}
    void    setSerialNumber              (QString  value){ if(value == mSerialNumber              ) return; mSerialNumber               = value; emit signalEventChangedSerialNumber              (value);}
    void    setDspVersion                (QString  value){ if(value == mDspVersion                ) return; mDspVersion                 = value; emit signalEventChangedDspVersion                (value);}
    void    setHmiVersion                (QString  value){ if(value == mHmiVersion                ) return; mHmiVersion                 = value; emit signalEventChangedHmiVersion                (value);}
    void    setPower                     (QString  value){ if(value == mPower                     ) return; mPower                      = value; setIsEditPower               (true);             emit signalEventChangedPower                     (value);}
    void    setIp                        (QString  value){ if(value == mIp                        ) return; mIp                         = value; setIsEditIp                  (true);             emit signalEventChangedIp                        (value);}
    void    setHomepage                  (QString  value){ if(value == mHomepage                  ) return; mHomepage                   = value; setIsEditHomepage            (true);             emit signalEventChangedHomepage                  (value);}
    void    setMaxWeight                 (int      value){ if(value == mMaxWeight                 ) return; mMaxWeight                  = value; setIsEditMaxWeight           (true);             emit signalEventChangedMaxWeight                 (value);}
    void    setSensorLength              (quint16  value){ if(value == mSensorLength              ) return; mSensorLength               = value; setIsEditSensorLength        (true);             emit signalEventChangedSensorLength              (value);}
    void    setDistBtwSensor             (quint16  value){ if(value == mDistBtwSensor             ) return; mDistBtwSensor              = value; setIsEditDistBtwSensor       (true);             emit signalEventChangedDistBtwSensor             (value);}
    void    setDistToWC                  (quint16  value){ if(value == mDistToWC                  ) return; mDistToWC                   = value; setIsEditDistToWC            (true);             emit signalEventChangedDistToWC                  (value);}
    void    setDistBtwPhotoToSensor      (quint16  value){ if(value == mDistBtwPhotoToSensor      ) return; mDistBtwPhotoToSensor       = value; setIsEditDistBtwPhotoToSensor(true);             emit signalEventChangedDistBtwPhotoToSensor      (value);}
    void    setDistToSorter01            (quint16  value){ if(value == mDistToSorter01            ) return; mDistToSorter01             = value; setIsEditDistToSorter01      (true);             emit signalEventChangedDistToSorter01            (value);}
    void    setDistToSorter02            (quint16  value){ if(value == mDistToSorter02            ) return; mDistToSorter02             = value; setIsEditDistToSorter02      (true);             emit signalEventChangedDistToSorter02            (value);}
    void    setDistToSorter03            (quint16  value){ if(value == mDistToSorter03            ) return; mDistToSorter03             = value; setIsEditDistToSorter03      (true);             emit signalEventChangedDistToSorter03            (value);}
    void    setDistToSorter04            (quint16  value){ if(value == mDistToSorter04            ) return; mDistToSorter04             = value; setIsEditDistToSorter04      (true);             emit signalEventChangedDistToSorter04            (value);}

    void    setIsEditDeviceNumber        (bool     value){ if(value == mIsEditDeviceNumber        ) return; mIsEditDeviceNumber         = value; emit signalEventChangedIsEditDeviceNumber        (value);}
    void    setIsEditPower               (bool     value){ if(value == mIsEditPower               ) return; mIsEditPower                = value; emit signalEventChangedIsEditPower               (value);}
    void    setIsEditIp                  (bool     value){ if(value == mIsEditIp                  ) return; mIsEditIp                   = value; emit signalEventChangedIsEditIp                  (value);}
    void    setIsEditHomepage            (bool     value){ if(value == mIsEditHomepage            ) return; mIsEditHomepage             = value; emit signalEventChangedIsEditHomepage            (value);}
    void    setIsEditMaxWeight           (bool     value){ if(value == mIsEditMaxWeight           ) return; mIsEditMaxWeight            = value; emit signalEventChangedIsEditMaxWeight           (value);}
    void    setIsEditSensorLength        (bool     value){ if(value == mIsEditSensorLength        ) return; mIsEditSensorLength         = value; emit signalEventChangedIsEditSensorLength        (value);}
    void    setIsEditDistBtwSensor       (bool     value){ if(value == mIsEditDistBtwSensor       ) return; mIsEditDistBtwSensor        = value; emit signalEventChangedIsEditDistBtwSensor       (value);}
    void    setIsEditDistToWC            (bool     value){ if(value == mIsEditDistToWC            ) return; mIsEditDistToWC             = value; emit signalEventChangedIsEditDistToWC            (value);}
    void    setIsEditDistBtwPhotoToSensor(bool     value){ if(value == mIsEditDistBtwPhotoToSensor) return; mIsEditDistBtwPhotoToSensor = value; emit signalEventChangedIsEditDistBtwPhotoToSensor(value);}
    void    setIsEditDistToSorter01      (bool     value){ if(value == mIsEditDistToSorter01      ) return; mIsEditDistToSorter01       = value; emit signalEventChangedIsEditDistToSorter01      (value);}
    void    setIsEditDistToSorter02      (bool     value){ if(value == mIsEditDistToSorter02      ) return; mIsEditDistToSorter02       = value; emit signalEventChangedIsEditDistToSorter02      (value);}
    void    setIsEditDistToSorter03      (bool     value){ if(value == mIsEditDistToSorter03      ) return; mIsEditDistToSorter03       = value; emit signalEventChangedIsEditDistToSorter03      (value);}
    void    setIsEditDistToSorter04      (bool     value){ if(value == mIsEditDistToSorter04      ) return; mIsEditDistToSorter04       = value; emit signalEventChangedIsEditDistToSorter04      (value);}

    explicit PanelInformationModel(QObject *parent = nullptr):QObject(parent)
    {
        if(pDspSP->mDspList.size() > 0)
        {
            mDspSeq = pDspSP->mDspList[0]->mSeq;
        }
        reset();
    }
    void reset()
    {
        if(mDspSeq != 0)
        {
            DspMaster * pDsp     = pDspSP->findDspMaster(mDspSeq)  ;

            DspInfoDto info      = pDsp->mRcvDataStore.getInfoDto();
            quint16 majorV       = info.mInfo.mMajorVersion        ;
            quint16 minorV       = info.mInfo.mMinorVersion        ;
            quint16 maintenanceV = info.mInfo.mMaintenanceVersion  ;

            setDspVersion(QString("%1.%2.%3").arg(majorV).arg(minorV).arg(maintenanceV));
            setIp(pDsp->mIp);
        }

        setCompany                   (pLSettingSP->mInformation.mCompany                                     );
        setModel                     (pLSettingSP->mInformation.mModel                                       );
        setSerialNumber              (pLSettingSP->mInformation.mSN                                          );
        setDeviceNumber              (pLSettingSP->mInformation.mDeviceNumber                                );
        setHmiVersion                (pLSettingSP->mInformation.mHMIVersion                                  );
        setPower                     (pLSettingSP->mInformation.mPower                                       );
        setHomepage                  (pLSettingSP->mInformation.mHomepage                                    );
        setMaxWeight                 (pLSettingSP->mInformation.mMaxWeight                                   );
        setSensorLength              (pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mSensorLength           );
        setDistBtwSensor             (pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistanceBtwSensor      );
        setDistToWC                  (pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistanceToWeightChecker);
        setDistBtwPhotoToSensor      (pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistancePhotoToSensor  );
        setDistToSorter01            (pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistToSorter01         );
        setDistToSorter02            (pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistToSorter02         );
        setDistToSorter03            (pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistToSorter03         );
        setDistToSorter04            (pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistToSorter04         );
        setIsEditPower               (false);
        setIsEditIp                  (false);
        setIsEditHomepage            (false);
        setIsEditDeviceNumber        (false);
        setIsEditMaxWeight           (false);
        setIsEditSensorLength        (false);
        setIsEditDistBtwSensor       (false);
        setIsEditDistToWC            (false);
        setIsEditDistBtwPhotoToSensor(false);
        setIsEditDistToSorter01      (false);
        setIsEditDistToSorter02      (false);
        setIsEditDistToSorter03      (false);
        setIsEditDistToSorter04      (false);
    }

signals:
    void signalEventChangedIsEnableWC                (bool     value);
    void signalEventChangedCompany                   (QString  value);
    void signalEventChangedModel                     (QString  value);
    void signalEventChangedDeviceNumber              (int      value);
    void signalEventChangedSerialNumber              (QString  value);
    void signalEventChangedDspVersion                (QString  value);
    void signalEventChangedHmiVersion                (QString  value);
    void signalEventChangedPower                     (QString  value);
    void signalEventChangedIp                        (QString  value);
    void signalEventChangedHomepage                  (QString  value);
    void signalEventChangedMaxWeight                 (int      value);
    void signalEventChangedSensorLength              (quint16  value);
    void signalEventChangedDistBtwSensor             (quint16  value);
    void signalEventChangedDistToWC                  (quint16  value);
    void signalEventChangedDistBtwPhotoToSensor      (quint16  value);
    void signalEventChangedDistToSorter01            (quint16  value);
    void signalEventChangedDistToSorter02            (quint16  value);
    void signalEventChangedDistToSorter03            (quint16  value);
    void signalEventChangedDistToSorter04            (quint16  value);

    void signalEventChangedIsEditDeviceNumber        (bool     value);
    void signalEventChangedIsEditPower               (bool     value);
    void signalEventChangedIsEditIp                  (bool     value);
    void signalEventChangedIsEditHomepage            (bool     value);
    void signalEventChangedIsEditMaxWeight           (bool     value);
    void signalEventChangedIsEditSensorLength        (bool     value);
    void signalEventChangedIsEditDistBtwSensor       (bool     value);
    void signalEventChangedIsEditDistToWC            (bool     value);
    void signalEventChangedIsEditDistBtwPhotoToSensor(bool     value);
    void signalEventChangedIsEditDistToSorter01      (bool     value);
    void signalEventChangedIsEditDistToSorter02      (bool     value);
    void signalEventChangedIsEditDistToSorter03      (bool     value);
    void signalEventChangedIsEditDistToSorter04      (bool     value);

    void signalResultSaveDeviceSetting(int error);
    void signalResultSaveInformation(int error);



public slots:

    Q_INVOKABLE void onCommandSave()
    {
        DevSettingDto devSetting = pLSettingSP->mDevSetting;
        devSetting.mDspForm.mSizeSetting.mSensorLength            = mSensorLength;
        devSetting.mDspForm.mSizeSetting.mDistanceBtwSensor       = mDistBtwSensor;
        devSetting.mDspForm.mSizeSetting.mDistanceToWeightChecker = mDistToWC;
        devSetting.mDspForm.mSizeSetting.mDistancePhotoToSensor   = mDistBtwPhotoToSensor;
        devSetting.mDspForm.mSizeSetting.mDistToSorter01          = mDistToSorter01;
        devSetting.mDspForm.mSizeSetting.mDistToSorter02          = mDistToSorter02;
        devSetting.mDspForm.mSizeSetting.mDistToSorter03          = mDistToSorter03;
        devSetting.mDspForm.mSizeSetting.mDistToSorter04          = mDistToSorter04;
        pLSettingSP->setDevSetting(devSetting);

        InformationDto info = pLSettingSP->mInformation;
        info.mCompany       = mCompany;
        info.mDeviceNumber  = mDeviceNumber;
        info.mPower         = mPower;
        info.mHomepage      = mHomepage;
        info.mMaxWeight     = mMaxWeight;
        pLSettingSP->setInformation(info);

        QStringList ipPortList = mIp.split("::");
        DspNetSettingDto netSetting;

        netSetting.mSetting.mIp01 = 0;
        netSetting.mSetting.mIp02 = 0;
        netSetting.mSetting.mIp03 = 0;
        netSetting.mSetting.mIp04 = 0;
        netSetting.mSetting.mPort = pDefaultSP->DSP_CONNINFO_PORT;

        if(ipPortList.size() > 0)
        {
            QStringList ipList = ipPortList[0].split(".");
            if(ipList.size() > 0)
            {
                netSetting.mSetting.mIp01 = ipList[0].toUShort();
            }
            if(ipList.size() > 1)
            {
                netSetting.mSetting.mIp02 = ipList[1].toUShort();
            }
            if(ipList.size() > 2)
            {
                netSetting.mSetting.mIp03 = ipList[2].toUShort();
            }
            if(ipList.size() > 3)
            {
                netSetting.mSetting.mIp04 = ipList[3].toUShort();
            }
        }

        if(ipPortList.size() > 1)
        {
            netSetting.mSetting.mPort = ipPortList[1].toUShort();
        }

        pDspSP->sendNetSetting(mDspSeq, netSetting);

        reset();

        emit signalResultSaveInformation(0);
        emit signalResultSaveDeviceSetting(0);
    }
    Q_INVOKABLE void onCommandCancle(){reset();}

    Q_INVOKABLE void onCommandSetCompany                   (QString  value){setCompany              (value);}
    Q_INVOKABLE void onCommandSetModel                     (QString  value){setModel                (value);}
    Q_INVOKABLE void onCommandSetDeviceNumber              (int      value){setDeviceNumber         (value);}
    Q_INVOKABLE void onCommandSetSerialNumber              (QString  value){setSerialNumber         (value);}
    Q_INVOKABLE void onCommandSetDspVersion                (QString  value){setDspVersion           (value);}
    Q_INVOKABLE void onCommandSetHmiVersion                (QString  value){setHmiVersion           (value);}
    Q_INVOKABLE void onCommandSetPower                     (QString  value){setPower                (value);}
    Q_INVOKABLE void onCommandSetIp                        (QString  value){setIp                   (value);}
    Q_INVOKABLE void onCommandSetHomepage                  (QString  value){setHomepage             (value);}
    Q_INVOKABLE void onCommandSetMaxWeight                 (int      value){setMaxWeight            (value);}
    Q_INVOKABLE void onCommandSetSensorLength              (quint16  value){setSensorLength         (value);}
    Q_INVOKABLE void onCommandSetDistBtwSensor             (quint16  value){setDistBtwSensor        (value);}
    Q_INVOKABLE void onCommandSetDistToWC                  (quint16  value){setDistToWC             (value);}
    Q_INVOKABLE void onCommandSetDistBtwPhotoToSensor      (quint16  value){setDistBtwPhotoToSensor (value);}
    Q_INVOKABLE void onCommandSetDistToSorter01            (quint16  value){setDistToSorter01       (value);}
    Q_INVOKABLE void onCommandSetDistToSorter02            (quint16  value){setDistToSorter02       (value);}
    Q_INVOKABLE void onCommandSetDistToSorter03            (quint16  value){setDistToSorter03       (value);}
    Q_INVOKABLE void onCommandSetDistToSorter04            (quint16  value){setDistToSorter04       (value);}
    Q_INVOKABLE void onCommandRefVoltageReset              (              ){pDspSP->sendAllRefVoltageResetCmd();}

};

#endif // PANELINFORMATIONMODEL_H
