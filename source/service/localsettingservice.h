#ifndef LOCALSETTINGSERVICE_H
#define LOCALSETTINGSERVICE_H

#include <QObject>
#include <QSettings>

#include "source/model/dspconnectionmodel.h"
#include "source/model/informationmodel.h"
#include "source/model/securitysettingmodel.h"
#include "source/model/guisettingmodel.h"
#include "source/model/procsettingmodel.h"
#include "source/model/dspsettingmodel.h"
#include "source/model/hmisettingmodel.h"

class LocalSettingService : public QObject
{
    Q_OBJECT
public:
    QSettings *             mpSettings;

    QString                 mOldVersion;
    InformationModel        mInformation;
    SecuritySettingModel    mSecuritySetting;
    GuiSettingModel         mGuiSetting;
    ProcSettingModel        mProcSetting;
    DspSettingModel         mDspSetting;
    HmiSettingModel         mHmiSetting;
    void loadInformation();
    void setInformation(QString company, QString tel,int deviceNumber, QString power, QString homepage, quint32 maxWeight);

    void loadSecuritySetting();
    void setSecuritySetting(QString password, QString adminPassword);

    void loadGuiSetting();
    void setGuiLanguage(int language);
    void setGuiIsDetail(bool value);
    void setGuiViewMode(int viewMode);
    void setGuiTrendsOption(int graphOptionH, int graphOptionFilter, int graphOptionLastN, int lastNValue);

    void loadProcSetting();
    void setProcBackupLastDate(int year, int month, int day);

    void loadDspSetting();
    void setDspSetting(quint32 lampTime               ,
                       quint32 buzzerTime             ,
                       quint32 speedConverter         ,
                       quint16 motorDirection         ,
                       quint16 sensorLength           ,
                       quint16 distanceToRejector     ,
                       bool    mdPhotoIsOn            ,
                       bool    wcPhotoIsOn            ,
                       quint32 rejectorReadyTime      ,
                       quint32 rejectorRunTimeRatio   ,
                       quint32 staticFactor           ,
                       quint32 scaler                 ,
                       quint32 displayStability       ,
                       quint32 measureCueSign         ,
                       quint32 minStaticWeight        ,
                       quint32 minDynamicWeight       ,
                       quint16 mode                   ,
                       quint16 distanceBtwSensor      ,
                       quint32 detectDetectTime       ,
                       quint32 runDetectTime          ,
                       quint16 distanceToWeightChecker,
                       quint16 distancePhotoToSensor  ,
                       quint32 signalDelayTime        ,
                       quint32 staticStandardWeight   ,
                       quint32 dynamicBaseWeight      ,
                       quint16 sensorCnt              ,
                       quint32 rejectorOpenTime       );

    void loadHmiSetting();
    void setHmiSetting(bool    isDayMode         ,
                       bool    isDebugMode       ,
                       quint32 dynamicFactor     ,
                       quint16 simpleSenstivity01,
                       quint16 simpleSenstivity02,
                       quint16 simpleSenstivity03,
                       quint16 simpleSenstivity04,
                       quint16 simpleSenstivity05);

    void factoryReset();
    explicit LocalSettingService(QObject *parent = nullptr);
};

#endif // LOCALSETTINGSERVICE_H
