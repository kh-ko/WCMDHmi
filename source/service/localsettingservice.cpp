#include "localsettingservice.h"

#include "source/globaldef/GlobalDefine.h"
#include "source/helper/languagehelper.h"

#ifdef BUILD_COMPANY_DONGNAM
QString STR_COMPANY  = "DONG NAM MACHINERY SHOP";
QString STR_TEL      = "T 053-551-1452"         ;
QString STR_HOMEPAGE = "www.dongnam1998.com"    ;
#else
QString STR_COMPANY  = "NOVASEN"                ;
QString STR_TEL      = "T 1600-4917"            ;
QString STR_HOMEPAGE = "www.novasen.com"        ;
#endif

#ifdef BUILD_MODEL_NSWCNSAMD480
QString STR_MODEL    = "NSWCNSAMD480"           ;
#else
QString STR_MODEL    = "NSWCNSAMD"              ;
#endif

#define INFORMATION_SETTIG_PATH_HMIVERSION   "information/HmiVserion"
#define INFORMATION_SETTIG_PATH_COMPANY      "information/Company"
#define INFORMATION_SETTIG_PATH_TEL          "information/Tel"
#define INFORMATION_SETTIG_PATH_HOMEPAGE     "information/Homepage"
#define INFORMATION_SETTIG_PATH_DEVICENUMBER "information/DeviceNumber"
#define INFORMATION_SETTIG_PATH_POWER        "information/Power"
#define INFORMATION_SETTIG_PATH_MAXWEIGHT    "information/MaxWeight"

#define SECURITY_SETTIG_PATH_PWD             "security/Password"
#define SECURITY_SETTIG_PATH_ADMINPWD        "security/AdminPassword"

#define GUI_SETTIG_PATH_LANGUAGE             "gui/Language"
#define GUI_SETTIG_PATH_ISDETAIL             "gui/IsDetail"
#define GUI_SETTIG_PATH_VIEWMODE             "gui/ViewMode"
#define GUI_SETTIG_PATH_TRENDS_OPTION_H      "gui/TrendsIsUnderToOver"
#define GUI_SETTIG_PATH_TRENDS_OPTION_FILTER "gui/TrendsIsTotal"
#define GUI_SETTIG_PATH_TRENDS_OPTION_LASTN  "gui/TrendsIsTotalSinceStart"
#define GUI_SETTIG_PATH_TRENDS_LAST_N_VALUE  "gui/TrendsLastNValue"

#define PROC_SETTIG_PATH_BACKUP_LAST_DATE    "proc/BackupLastDate"

#define DSP_SETTING_PATH_LAMPTIME               "dspsetting/LampTime"
#define DSP_SETTING_PATH_BUZZERTIME             "dspsetting/BuzzerTime"
#define DSP_SETTING_PATH_SPEEDCONVERTOR         "dspsetting/SpeedConverter"
#define DSP_SETTING_PATH_MOTORDIRECTION         "dspsetting/MotorDirection"
#define DSP_SETTING_PATH_MOTORTYPE              "dspsetting/MotorType"
#define DSP_SETTING_PATH_MOTORMDRATIO           "dspsetting/MotorMDRatio"
#define DSP_SETTING_PATH_MOTORWCRATIO           "dspsetting/MotorWCRatio"
#define DSP_SETTING_PATH_MOTORRJRATIO           "dspsetting/MotorRJRatio"
#define DSP_SETTING_PATH_SENSORLENGTH           "dspsetting/SensorLength"
#define DSP_SETTING_PATH_DIST_TO_REJECTOR       "dspsetting/DistanceToRejector"
#define DSP_SETTING_PATH_MD_PHOTO_ON            "dspsetting/MDPhotoIsOn"
#define DSP_SETTING_PATH_WC_PHOTO_ON            "dspsetting/WCPhotoIsOn"
#define DSP_SETTING_PATH_REJECTOR_READY_TIME    "dspsetting/RejectorReadyTime"
#define DSP_SETTING_PATH_REJECTOR_RUNTIME_RATIO "dspsetting/RejectorRunTimeRatio"
#define DSP_SETTING_PATH_STATIC_FACTOR          "dspsetting/StaticFactor"
#define DSP_SETTING_PATH_SCALER                 "dspsetting/Scaler"
#define DSP_SETTING_PATH_DP_STABILITY           "dspsetting/DisplayStability"
#define DSP_SETTING_PATH_MEASURE_CUE_SIGN       "dspsetting/MeasureCueSign"
#define DSP_SETTING_PATH_MIN_STATIC_WEIGHT      "dspsetting/MinStaticWeight"
#define DSP_SETTING_PATH_MIN_DYNAMIC_WEIGHT     "dspsetting/MinDynamicWeight"
#define DSP_SETTING_PATH_MD_SENSOR_MODE         "dspsetting/Mode"
#define DSP_SETTING_PATH_DISTANCE_BTW_SENSOR    "dspsetting/DistanceBtwSensor"
#define DSP_SETTING_PATH_DETECT_DETECT_TIME     "dspsetting/DetectDetectTime"
#define DSP_SETTING_PATH_RUN_DETECT_TIME        "dspsetting/RunDetectTime"
#define DSP_SETTING_PATH_DIST_TO_WEIGHTCHECKER  "dspsetting/DistanceToWeightChecker"
#define DSP_SETTING_PATH_DIST_PHOTO_TO_SENSOR   "dspsetting/DistancePhotoToSensor"
#define DSP_SETTING_PATH_SIGNAL_DELAY_TIME      "dspsetting/SignalDelayTime"
#define DSP_SETTING_PATH_STATIC_STANDARD_WEIGHT "dspsetting/StaticStandardWeight"
#define DSP_SETTING_PATH_DYNAMIC_BASE_WEIGHT    "dspsetting/DynamicBaseWeight"
#define DSP_SETTING_PATH_SENSOR_CNT             "dspsetting/SensorCnt"
#define DSP_SETTING_PATH_REJECTOR_OPEN_TIME     "dspsetting/RejectorOpenTime"

#define HMI_SETTING_PATH_IS_DAYMODE             "hmisetting/IsDayMode"
#define HMI_SETTING_PATH_IS_DEBUGMODE           "hmisetting/IsDebugMode"
#define HMI_SETTING_PATH_DYNAMICFACTOR          "hmisetting/DynamicFactor"
#define HMI_SETTING_PATH_SIMPLE_SENSTIVITY_01   "hmisetting/SimpleSenstivity01"
#define HMI_SETTING_PATH_SIMPLE_SENSTIVITY_02   "hmisetting/SimpleSenstivity02"
#define HMI_SETTING_PATH_SIMPLE_SENSTIVITY_03   "hmisetting/SimpleSenstivity03"
#define HMI_SETTING_PATH_SIMPLE_SENSTIVITY_04   "hmisetting/SimpleSenstivity04"
#define HMI_SETTING_PATH_SIMPLE_SENSTIVITY_05   "hmisetting/SimpleSenstivity05"

void LocalSettingService::loadInformation()
{
    mOldVersion = mpSettings->value(INFORMATION_SETTIG_PATH_HMIVERSION, "0.0.0").toString();

    mInformation.setModel       (STR_MODEL                                                                );
    mInformation.setSN          (QSysInfo::machineUniqueId()                                              );
    mInformation.setHMIVersion  (BUILD_STR_VERSION                                                        );

    mInformation.setCompany     (mpSettings->value(INFORMATION_SETTIG_PATH_COMPANY      ,STR_COMPANY     ).toString());
    mInformation.setTel         (mpSettings->value(INFORMATION_SETTIG_PATH_TEL          ,STR_TEL         ).toString());
    mInformation.setHomepage    (mpSettings->value(INFORMATION_SETTIG_PATH_HOMEPAGE     ,STR_HOMEPAGE    ).toString());
    mInformation.setDeviceNumber(mpSettings->value(INFORMATION_SETTIG_PATH_DEVICENUMBER ,1               ).toInt()   );
    mInformation.setPower       (mpSettings->value(INFORMATION_SETTIG_PATH_POWER        ,"1% 220VAC 60Hz").toString());
    mInformation.setMaxWeight   (mpSettings->value(INFORMATION_SETTIG_PATH_MAXWEIGHT    ,10000           ).toInt()   );
}

void LocalSettingService::setInformation(QString company, QString tel,int deviceNumber, QString power, QString homepage, quint32 maxWeight)
{
    mpSettings->setValue(INFORMATION_SETTIG_PATH_HMIVERSION   ,BUILD_STR_VERSION);
    mpSettings->setValue(INFORMATION_SETTIG_PATH_COMPANY      ,company          );
    mpSettings->setValue(INFORMATION_SETTIG_PATH_TEL          ,tel              );
    mpSettings->setValue(INFORMATION_SETTIG_PATH_HOMEPAGE     ,homepage         );
    mpSettings->setValue(INFORMATION_SETTIG_PATH_DEVICENUMBER ,deviceNumber     );
    mpSettings->setValue(INFORMATION_SETTIG_PATH_POWER        ,power            );
    mpSettings->setValue(INFORMATION_SETTIG_PATH_MAXWEIGHT    ,maxWeight        );

    mInformation.setCompany     (company        );
    mInformation.setTel         (tel            );
    mInformation.setHomepage    (homepage       );
    mInformation.setDeviceNumber(deviceNumber   );
    mInformation.setPower       (power          );
    mInformation.setMaxWeight   (maxWeight      );
}

void LocalSettingService::loadSecuritySetting()
{
    mSecuritySetting.setPassword     (mpSettings->value(SECURITY_SETTIG_PATH_PWD      ,"1111"     ).toString());
    mSecuritySetting.setAdminPassword(mpSettings->value(SECURITY_SETTIG_PATH_ADMINPWD ,"7071"     ).toString());
}

void LocalSettingService::setSecuritySetting(QString password, QString adminPassword)
{
    mpSettings->setValue(SECURITY_SETTIG_PATH_PWD      ,password     );
    mpSettings->setValue(SECURITY_SETTIG_PATH_ADMINPWD ,adminPassword);

    mSecuritySetting.setPassword     (password     );
    mSecuritySetting.setAdminPassword(adminPassword);
}

void LocalSettingService::loadGuiSetting()
{
    mGuiSetting.setLanguage          (mpSettings->value(GUI_SETTIG_PATH_LANGUAGE            , EnumDefine::Language::ENG                                         ).toInt ());
    mGuiSetting.setIsDetail          (mpSettings->value(GUI_SETTIG_PATH_ISDETAIL            , false                                                             ).toBool());
    mGuiSetting.setViewMode          (mpSettings->value(GUI_SETTIG_PATH_VIEWMODE            , EnumDefine::WCViewMode::WC_VIEWMODE_CURRENT                       ).toInt ());
    mGuiSetting.setTrendsOptionH     (mpSettings->value(GUI_SETTIG_PATH_TRENDS_OPTION_H     , EnumDefine::TrendsGraphOptionH::TRENDSOPTION_H_UNDER_TO_OVER      ).toInt ());
    mGuiSetting.setTrendsOptionFilter(mpSettings->value(GUI_SETTIG_PATH_TRENDS_OPTION_FILTER, EnumDefine::TrendsGraphOptionFilter::TRENDSOPTION_FILTER_TOTAL    ).toInt ());
    mGuiSetting.setTrendsOptionLastN (mpSettings->value(GUI_SETTIG_PATH_TRENDS_OPTION_LASTN , EnumDefine::TrendsGraphOptionLastN::TRENDSOPTION_TOTAL_SINCE_START).toInt ());
    mGuiSetting.setTrendsLastNValue  (mpSettings->value(GUI_SETTIG_PATH_TRENDS_LAST_N_VALUE , 100                                                               ).toInt ());
}

void LocalSettingService::setGuiLanguage(int language)
{
    mpSettings->setValue(GUI_SETTIG_PATH_LANGUAGE, language);
    mGuiSetting.setLanguage(language);

    LanguageHelper::getInstance()->loadLanguage((EnumDefine::Language)language);
}

void LocalSettingService::setGuiIsDetail(bool value)
{
    mpSettings->setValue(GUI_SETTIG_PATH_ISDETAIL, value);
    mGuiSetting.setIsDetail(value);
}

void LocalSettingService::setGuiViewMode(int viewMode)
{
    mpSettings->setValue(GUI_SETTIG_PATH_VIEWMODE, viewMode);
    mGuiSetting.setViewMode(viewMode);
}
void LocalSettingService::setGuiTrendsOption(int optionH, int optionFilter, int optionLastN, int lastNValue)
{
    mpSettings->setValue(GUI_SETTIG_PATH_TRENDS_OPTION_H     , optionH     );
    mpSettings->setValue(GUI_SETTIG_PATH_TRENDS_OPTION_FILTER, optionFilter);
    mpSettings->setValue(GUI_SETTIG_PATH_TRENDS_OPTION_LASTN , optionLastN );
    mpSettings->setValue(GUI_SETTIG_PATH_TRENDS_LAST_N_VALUE , lastNValue  );

    mGuiSetting.setTrendsOptionH     (optionH     );
    mGuiSetting.setTrendsOptionFilter(optionFilter);
    mGuiSetting.setTrendsOptionLastN (optionLastN );
    mGuiSetting.setTrendsLastNValue  (lastNValue  );
}

void LocalSettingService::loadProcSetting()
{
    QStringList strLastBackupDate = mpSettings->value(PROC_SETTIG_PATH_BACKUP_LAST_DATE, "2020/1/1").toString().split("/");

    int year  = strLastBackupDate[0].toInt();
    int month = strLastBackupDate[1].toInt();
    int day   = strLastBackupDate[2].toInt();

    mProcSetting.setLastBackupYear (year);
    mProcSetting.setLastBackupMonth(month);
    mProcSetting.setLastBackupDay  (day);
}

void LocalSettingService::setProcBackupLastDate(int year, int month, int day)
{
    QString strLastBackupDate = QString("%1/%2/%3");

    mpSettings->setValue(PROC_SETTIG_PATH_BACKUP_LAST_DATE, strLastBackupDate.arg(year).arg(month).arg(day));

    mProcSetting.setLastBackupYear (year);
    mProcSetting.setLastBackupMonth(month);
    mProcSetting.setLastBackupDay  (day);
}

void LocalSettingService::loadDspSetting()
{
    mDspSetting.setLampTime               (mpSettings->value(DSP_SETTING_PATH_LAMPTIME              , 1000                                                      ).toInt ());
    mDspSetting.setBuzzerTime             (mpSettings->value(DSP_SETTING_PATH_BUZZERTIME            , 1000                                                      ).toInt ());
    mDspSetting.setSpeedConverter         (mpSettings->value(DSP_SETTING_PATH_SPEEDCONVERTOR        , 2070000                                                   ).toInt ());
    mDspSetting.setMotorDirection         (mpSettings->value(DSP_SETTING_PATH_MOTORDIRECTION        , EnumDefine::MOTOR_DIRECTION::MOTOR_DIRECTION_RIGHT_TO_LEFT).toInt ());
    mDspSetting.setMotorType              (mpSettings->value(DSP_SETTING_PATH_MOTORTYPE             , EnumDefine::MotorType::MOTOR_3_PHASE                      ).toInt ());
    mDspSetting.setMotorMDRatio           (mpSettings->value(DSP_SETTING_PATH_MOTORMDRATIO          , 100                                                       ).toInt ());
    mDspSetting.setMotorWCRatio           (mpSettings->value(DSP_SETTING_PATH_MOTORWCRATIO          , 100                                                       ).toInt ());
    mDspSetting.setMotorRJRatio           (mpSettings->value(DSP_SETTING_PATH_MOTORRJRATIO          , 100                                                       ).toInt ());
    mDspSetting.setSensorLength           (mpSettings->value(DSP_SETTING_PATH_SENSORLENGTH          , 540                                                       ).toInt ());
    mDspSetting.setDistanceToRejector     (mpSettings->value(DSP_SETTING_PATH_DIST_TO_REJECTOR      , 720                                                       ).toInt ());
    mDspSetting.setMDPhotoIsOn            (mpSettings->value(DSP_SETTING_PATH_MD_PHOTO_ON           , true                                                      ).toBool());
    mDspSetting.setWCPhotoIsOn            (mpSettings->value(DSP_SETTING_PATH_WC_PHOTO_ON           , true                                                      ).toBool());
    mDspSetting.setRejectorReadyTime      (mpSettings->value(DSP_SETTING_PATH_REJECTOR_READY_TIME   , 100                                                       ).toInt ());
    mDspSetting.setRejectorRunTimeRatio   (mpSettings->value(DSP_SETTING_PATH_REJECTOR_RUNTIME_RATIO, 1500                                                      ).toInt ());
    mDspSetting.setStaticFactor           (mpSettings->value(DSP_SETTING_PATH_STATIC_FACTOR         , 998932                                                    ).toInt ());
    mDspSetting.setScaler                 (mpSettings->value(DSP_SETTING_PATH_SCALER                , 200                                                       ).toInt ());
    mDspSetting.setDisplayStability       (mpSettings->value(DSP_SETTING_PATH_DP_STABILITY          , 1                                                         ).toInt ());
    mDspSetting.setMeasureCueSign         (mpSettings->value(DSP_SETTING_PATH_MEASURE_CUE_SIGN      , 300                                                       ).toInt ());
    mDspSetting.setMinStaticWeight        (mpSettings->value(DSP_SETTING_PATH_MIN_STATIC_WEIGHT     , 5000                                                      ).toInt ());
    mDspSetting.setMinDynamicWeight       (mpSettings->value(DSP_SETTING_PATH_MIN_DYNAMIC_WEIGHT    , 10000                                                      ).toInt ());
    mDspSetting.setMode                   (mpSettings->value(DSP_SETTING_PATH_MD_SENSOR_MODE        , EnumDefine::SensorMode::INDEPENDENT                       ).toInt ());
    mDspSetting.setDistanceBtwSensor      (mpSettings->value(DSP_SETTING_PATH_DISTANCE_BTW_SENSOR   , 180                                                       ).toInt ());
    mDspSetting.setDetectDetectTime       (mpSettings->value(DSP_SETTING_PATH_DETECT_DETECT_TIME    , 500                                                       ).toInt ());
    mDspSetting.setRunDetectTime          (mpSettings->value(DSP_SETTING_PATH_RUN_DETECT_TIME       , 1000                                                      ).toInt ());
    mDspSetting.setDistanceToWeightChecker(mpSettings->value(DSP_SETTING_PATH_DIST_TO_WEIGHTCHECKER , 650                                                       ).toInt ());
    mDspSetting.setDistancePhotoToSensor  (mpSettings->value(DSP_SETTING_PATH_DIST_PHOTO_TO_SENSOR  , 250                                                       ).toInt ());
    mDspSetting.setSignalDelayTime        (mpSettings->value(DSP_SETTING_PATH_SIGNAL_DELAY_TIME     , 0                                                         ).toInt ());
    mDspSetting.setStaticStandardWeight   (mpSettings->value(DSP_SETTING_PATH_STATIC_STANDARD_WEIGHT, 10000                                                     ).toInt ());
    mDspSetting.setDynamicBaseWeight      (mpSettings->value(DSP_SETTING_PATH_DYNAMIC_BASE_WEIGHT   , 10000                                                     ).toInt ());
    mDspSetting.setSensorCnt              (mpSettings->value(DSP_SETTING_PATH_SENSOR_CNT            , 1                                                         ).toInt ());
    mDspSetting.setRejectorOpenTime       (mpSettings->value(DSP_SETTING_PATH_REJECTOR_OPEN_TIME    , 400                                                       ).toInt ());
}

void LocalSettingService::setDspSetting(quint32 lampTime               ,
                                        quint32 buzzerTime             ,
                                        quint32 speedConverter         ,
                                        quint16 motorDirection         ,
                                        quint16 motorType              ,
                                        quint16 motorMDRatio           ,
                                        quint16 motorWCRatio           ,
                                        quint16 motorRJRatio           ,
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
                                        quint32 rejectorOpenTime       )
{
    mpSettings->setValue(DSP_SETTING_PATH_LAMPTIME              , lampTime               );
    mpSettings->setValue(DSP_SETTING_PATH_BUZZERTIME            , buzzerTime             );
    mpSettings->setValue(DSP_SETTING_PATH_SPEEDCONVERTOR        , speedConverter         );
    mpSettings->setValue(DSP_SETTING_PATH_MOTORDIRECTION        , motorDirection         );
    mpSettings->setValue(DSP_SETTING_PATH_MOTORTYPE             , motorType              );
    mpSettings->setValue(DSP_SETTING_PATH_MOTORMDRATIO          , motorMDRatio           );
    mpSettings->setValue(DSP_SETTING_PATH_MOTORWCRATIO          , motorWCRatio           );
    mpSettings->setValue(DSP_SETTING_PATH_MOTORRJRATIO          , motorRJRatio           );
    mpSettings->setValue(DSP_SETTING_PATH_SENSORLENGTH          , sensorLength           );
    mpSettings->setValue(DSP_SETTING_PATH_DIST_TO_REJECTOR      , distanceToRejector     );
    mpSettings->setValue(DSP_SETTING_PATH_MD_PHOTO_ON           , mdPhotoIsOn            );
    mpSettings->setValue(DSP_SETTING_PATH_WC_PHOTO_ON           , wcPhotoIsOn            );
    mpSettings->setValue(DSP_SETTING_PATH_REJECTOR_READY_TIME   , rejectorReadyTime      );
    mpSettings->setValue(DSP_SETTING_PATH_REJECTOR_RUNTIME_RATIO, rejectorRunTimeRatio   );
    mpSettings->setValue(DSP_SETTING_PATH_STATIC_FACTOR         , staticFactor           );
    mpSettings->setValue(DSP_SETTING_PATH_SCALER                , scaler                 );
    mpSettings->setValue(DSP_SETTING_PATH_DP_STABILITY          , displayStability       );
    mpSettings->setValue(DSP_SETTING_PATH_MEASURE_CUE_SIGN      , measureCueSign         );
    mpSettings->setValue(DSP_SETTING_PATH_MIN_STATIC_WEIGHT     , minStaticWeight        );
    mpSettings->setValue(DSP_SETTING_PATH_MIN_DYNAMIC_WEIGHT    , minDynamicWeight       );
    mpSettings->setValue(DSP_SETTING_PATH_MD_SENSOR_MODE        , mode                   );
    mpSettings->setValue(DSP_SETTING_PATH_DISTANCE_BTW_SENSOR   , distanceBtwSensor      );
    mpSettings->setValue(DSP_SETTING_PATH_DETECT_DETECT_TIME    , detectDetectTime       );
    mpSettings->setValue(DSP_SETTING_PATH_RUN_DETECT_TIME       , runDetectTime          );
    mpSettings->setValue(DSP_SETTING_PATH_DIST_TO_WEIGHTCHECKER , distanceToWeightChecker);
    mpSettings->setValue(DSP_SETTING_PATH_DIST_PHOTO_TO_SENSOR  , distancePhotoToSensor  );
    mpSettings->setValue(DSP_SETTING_PATH_SIGNAL_DELAY_TIME     , signalDelayTime        );
    mpSettings->setValue(DSP_SETTING_PATH_STATIC_STANDARD_WEIGHT, staticStandardWeight   );
    mpSettings->setValue(DSP_SETTING_PATH_DYNAMIC_BASE_WEIGHT   , dynamicBaseWeight      );
    mpSettings->setValue(DSP_SETTING_PATH_SENSOR_CNT            , sensorCnt              );
    mpSettings->setValue(DSP_SETTING_PATH_REJECTOR_OPEN_TIME    , rejectorOpenTime       );

    mDspSetting.setLampTime               (lampTime               );
    mDspSetting.setBuzzerTime             (buzzerTime             );
    mDspSetting.setSpeedConverter         (speedConverter         );
    mDspSetting.setMotorDirection         (motorDirection         );
    mDspSetting.setMotorType              (motorType              );
    mDspSetting.setMotorMDRatio           (motorMDRatio           );
    mDspSetting.setMotorWCRatio           (motorWCRatio           );
    mDspSetting.setMotorRJRatio           (motorRJRatio           );
    mDspSetting.setSensorLength           (sensorLength           );
    mDspSetting.setDistanceToRejector     (distanceToRejector     );
    mDspSetting.setMDPhotoIsOn            (mdPhotoIsOn            );
    mDspSetting.setWCPhotoIsOn            (wcPhotoIsOn            );
    mDspSetting.setRejectorReadyTime      (rejectorReadyTime      );
    mDspSetting.setRejectorRunTimeRatio   (rejectorRunTimeRatio   );
    mDspSetting.setStaticFactor           (staticFactor           );
    mDspSetting.setScaler                 (scaler                 );
    mDspSetting.setDisplayStability       (displayStability       );
    mDspSetting.setMeasureCueSign         (measureCueSign         );
    mDspSetting.setMinStaticWeight        (minStaticWeight        );
    mDspSetting.setMinDynamicWeight       (minDynamicWeight       );
    mDspSetting.setMode                   (mode                   );
    mDspSetting.setDistanceBtwSensor      (distanceBtwSensor      );
    mDspSetting.setDetectDetectTime       (detectDetectTime       );
    mDspSetting.setRunDetectTime          (runDetectTime          );
    mDspSetting.setDistanceToWeightChecker(distanceToWeightChecker);
    mDspSetting.setDistancePhotoToSensor  (distancePhotoToSensor  );
    mDspSetting.setSignalDelayTime        (signalDelayTime        );
    mDspSetting.setStaticStandardWeight   (staticStandardWeight   );
    mDspSetting.setDynamicBaseWeight      (dynamicBaseWeight      );
    mDspSetting.setSensorCnt              (sensorCnt              );
    mDspSetting.setRejectorOpenTime       (rejectorOpenTime       );
}

void LocalSettingService::loadHmiSetting()
{
    mHmiSetting.setIsDayMode         (mpSettings->value(HMI_SETTING_PATH_IS_DAYMODE          , true    ).toBool());
    mHmiSetting.setIsDebugMode       (mpSettings->value(HMI_SETTING_PATH_IS_DEBUGMODE        , false   ).toBool());
    mHmiSetting.setDynamicFactor     (mpSettings->value(HMI_SETTING_PATH_DYNAMICFACTOR       , 10000000).toInt ());
    mHmiSetting.setSimpleSenstivity01(mpSettings->value(HMI_SETTING_PATH_SIMPLE_SENSTIVITY_01, 0       ).toInt ());
    mHmiSetting.setSimpleSenstivity02(mpSettings->value(HMI_SETTING_PATH_SIMPLE_SENSTIVITY_02, 0       ).toInt ());
    mHmiSetting.setSimpleSenstivity03(mpSettings->value(HMI_SETTING_PATH_SIMPLE_SENSTIVITY_03, 0       ).toInt ());
    mHmiSetting.setSimpleSenstivity04(mpSettings->value(HMI_SETTING_PATH_SIMPLE_SENSTIVITY_04, 0       ).toInt ());
    mHmiSetting.setSimpleSenstivity05(mpSettings->value(HMI_SETTING_PATH_SIMPLE_SENSTIVITY_05, 0       ).toInt ());
}

void LocalSettingService::setHmiSetting(bool    isDayMode         ,
                                        bool    isDebugMode       ,
                                        quint32 dynamicFactor     ,
                                        quint16 simpleSenstivity01,
                                        quint16 simpleSenstivity02,
                                        quint16 simpleSenstivity03,
                                        quint16 simpleSenstivity04,
                                        quint16 simpleSenstivity05)
{
    mpSettings->setValue(HMI_SETTING_PATH_IS_DAYMODE          , isDayMode         );
    mpSettings->setValue(HMI_SETTING_PATH_IS_DEBUGMODE        , isDebugMode       );
    mpSettings->setValue(HMI_SETTING_PATH_DYNAMICFACTOR       , dynamicFactor     );
    mpSettings->setValue(HMI_SETTING_PATH_SIMPLE_SENSTIVITY_01, simpleSenstivity01);
    mpSettings->setValue(HMI_SETTING_PATH_SIMPLE_SENSTIVITY_02, simpleSenstivity02);
    mpSettings->setValue(HMI_SETTING_PATH_SIMPLE_SENSTIVITY_03, simpleSenstivity03);
    mpSettings->setValue(HMI_SETTING_PATH_SIMPLE_SENSTIVITY_04, simpleSenstivity04);
    mpSettings->setValue(HMI_SETTING_PATH_SIMPLE_SENSTIVITY_05, simpleSenstivity05);

    mHmiSetting.setIsDayMode         (isDayMode         );
    mHmiSetting.setIsDebugMode       (isDebugMode       );
    mHmiSetting.setDynamicFactor     (dynamicFactor     );
    mHmiSetting.setSimpleSenstivity01(simpleSenstivity01);
    mHmiSetting.setSimpleSenstivity02(simpleSenstivity02);
    mHmiSetting.setSimpleSenstivity03(simpleSenstivity03);
    mHmiSetting.setSimpleSenstivity04(simpleSenstivity04);
    mHmiSetting.setSimpleSenstivity05(simpleSenstivity05);
}

void LocalSettingService::factoryReset()
{
    mpSettings->clear();
    mpSettings->setValue(INFORMATION_SETTIG_PATH_HMIVERSION   ,BUILD_STR_VERSION);
}

LocalSettingService::LocalSettingService(QObject *parent) : QObject(parent)
{
    mpSettings = new QSettings("novasen", "WCMD", this);

    loadInformation();
    loadSecuritySetting();
    loadGuiSetting();
    loadProcSetting();
    loadDspSetting();
    loadHmiSetting();

    setInformation(mInformation.mCompany     ,
                   mInformation.mTel         ,
                   mInformation.mDeviceNumber,
                   mInformation.mPower       ,
                   mInformation.mHomepage    ,
                   mInformation.mMaxWeight   );

    setSecuritySetting( mSecuritySetting.mPassword,
                        mSecuritySetting.mAdminPassword);

    setGuiLanguage(mGuiSetting.mLanguage);
    setGuiIsDetail(mGuiSetting.mIsDetail);
    setGuiViewMode(mGuiSetting.mViewMode);
    setGuiTrendsOption(mGuiSetting.mTrendsOptionH, mGuiSetting.mTrendsOptionFilter, mGuiSetting.mTrendsOptionLastN, mGuiSetting.mTrendsLastNValue);

    setProcBackupLastDate(mProcSetting.mLastBackupYear, mProcSetting.mLastBackupMonth, mProcSetting.mLastBackupDay);

    setDspSetting(mDspSetting.mLampTime               ,
                  mDspSetting.mBuzzerTime             ,
                  mDspSetting.mSpeedConverter         ,
                  mDspSetting.mMotorDirection         ,
                  mDspSetting.mMotorType              ,
                  mDspSetting.mMotorMDRatio           ,
                  mDspSetting.mMotorWCRatio           ,
                  mDspSetting.mMotorRJRatio           ,
                  mDspSetting.mSensorLength           ,
                  mDspSetting.mDistanceToRejector     ,
                  mDspSetting.mMDPhotoIsOn            ,
                  mDspSetting.mWCPhotoIsOn            ,
                  mDspSetting.mRejectorReadyTime      ,
                  mDspSetting.mRejectorRunTimeRatio   ,
                  mDspSetting.mStaticFactor           ,
                  mDspSetting.mScaler                 ,
                  mDspSetting.mDisplayStability       ,
                  mDspSetting.mMeasureCueSign         ,
                  mDspSetting.mMinStaticWeight        ,
                  mDspSetting.mMinDynamicWeight       ,
                  mDspSetting.mMode                   ,
                  mDspSetting.mDistanceBtwSensor      ,
                  mDspSetting.mDetectDetectTime       ,
                  mDspSetting.mRunDetectTime          ,
                  mDspSetting.mDistanceToWeightChecker,
                  mDspSetting.mDistancePhotoToSensor  ,
                  mDspSetting.mSignalDelayTime        ,
                  mDspSetting.mStaticStandardWeight   ,
                  mDspSetting.mDynamicBaseWeight      ,
                  mDspSetting.mSensorCnt              ,
                  mDspSetting.mRejectorOpenTime       );

    setHmiSetting(mHmiSetting.mIsDayMode         ,
                  mHmiSetting.mIsDebugMode       ,
                  mHmiSetting.mDynamicFactor     ,
                  mHmiSetting.mSimpleSenstivity01,
                  mHmiSetting.mSimpleSenstivity02,
                  mHmiSetting.mSimpleSenstivity03,
                  mHmiSetting.mSimpleSenstivity04,
                  mHmiSetting.mSimpleSenstivity05);
}


