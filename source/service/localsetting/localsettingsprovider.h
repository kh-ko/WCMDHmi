#ifndef LOCALSETTINGSPROVIDER_H
#define LOCALSETTINGSPROVIDER_H

#include <QObject>
#include <QDateTime>
#include <QSettings>
#include <QTimer>

#include "source/service/defaultsetting/defaultsettingsprovider.h"
#include "source/service/def/datetimeform.h"
#include "source/service/localsetting/languagehelper.h"
#include "source/service/util/exceptionutil.h"
#include "source/service/includesvcdto.h"

#define pLSettingSP LocalSettingSProvider::getInstance()

class LocalSettingSProvider : public QObject
{
    Q_OBJECT

private:
    const QString mInfoHMIVersionKey                        = "information/HmiVserion"            ;
    const QString mInfoCompanyKey                           = "information/Company"               ;
    const QString mInfoTelKey                               = "information/Tel"                   ;
    const QString mInfoHomepageKey                          = "information/Homepage"              ;
    const QString mInfoDevNumberKey                         = "information/DeviceNumber"          ;
    const QString mInfoPowerKey                             = "information/Power"                 ;
    const QString mInfoMaxWeightKey                         = "information/MaxWeight"             ;

    const QString mSecPwdKey                                = "security/Password"                 ;
    const QString mSecAdminPwdKey                           = "security/AdminPassword"            ;

    const QString mLanguageKey                              = "gui/Language"                      ;

    const QString mGUIIsDetailKey                           = "gui/IsDetail"                      ;

    const QString mGUIViewModeKey                           = "gui/ViewMode"                      ;

    const QString mGUIIsEnableWCKey                         = "gui/EnableWC"                      ;

    const QString mTRIsUnderToOverKey                       = "gui/TrendsIsUnderToOver"           ;
    const QString mTRIsTotalKey                             = "gui/TrendsIsTotal"                 ;
    const QString mTRIstotalSinceStartKey                   = "gui/TrendsIsTotalSinceStart"       ;
    const QString mTRLastNValueKey                          = "gui/TrendsLastNValue"              ;

    const QString mProcBackupLastDateKey                    = "proc/BackupLastDate"               ;

    const QString mDevCommSettingLampTimeKey                = "dspsetting/LampTime"               ;
    const QString mDevCommSettingBuzzerTimeKey              = "dspsetting/BuzzerTime"             ;
    const QString mDevCommSettingRejectorRunTimeRatioKey    = "dspsetting/RejectorRunTimeRatio"   ;
    const QString mDevCommSettingRejectorOpenTimeKey        = "dspsetting/RejectorOpenTime"       ;
    const QString mDevCommSettingSpeedConverterKey          = "dspsetting/SpeedConverter"         ;
    const QString mDevCommSettingMotorDirectionKey          = "dspsetting/MotorDirection"         ;
    const QString mDevCommSettingMotorTypeKey               = "dspsetting/MotorType"              ;
    const QString mDevCommSettingMachineModeKey             = "dspsetting/MachineMode"            ;
    const QString mDevCommSettingMotorMDRatioKey            = "dspsetting/MotorMDRatio"           ;
    const QString mDevCommSettingMotorWCRatioKey            = "dspsetting/MotorWCRatio"           ;
    const QString mDevCommSettingMotorRJRatioKey            = "dspsetting/MotorRJRatio"           ;

    const QString mDevWCSettingDisplayStabilityKey          = "dspsetting/DisplayStability"       ;
    const QString mDevWCSettingMeasureCueSignKey            = "dspsetting/MeasureCueSign"         ;
    const QString mDevWCSettingMinStaticWeightKey           = "dspsetting/MinStaticWeight"        ;
    const QString mDevWCSettingMinDynamicWeightKey          = "dspsetting/MinDynamicWeight"       ;
    const QString mDevWCSettingScalerKey                    = "dspsetting/Scaler"                 ;
    const QString mDevWCSettingStaticFactorKey              = "dspsetting/StaticFactor"           ;
    const QString mDevWCSettingWCPhotoIsOnKey               = "dspsetting/WCPhotoIsOn"            ;
    const QString mDevWCSettingStaticStandardWeightKey      = "dspsetting/StaticStandardWeight"   ;
    const QString mDevWCSettingDynamicBaseWeightKey         = "dspsetting/DynamicBaseWeight"      ;

    const QString mDevMDSettingModeKey                      = "dspsetting/Mode"                   ;
    const QString mDevMDSettingDetectDetectTimeKey          = "dspsetting/DetectDetectTime"       ;
    const QString mDevMDSettingRunDetectTimeKey             = "dspsetting/RunDetectTime"          ;
    const QString mDevMDSettingSignalDelayTimeKey           = "dspsetting/SignalDelayTime"        ;
    const QString mDevMDSettingMDPhotoIsOnKey               = "dspsetting/MDPhotoIsOn"            ;
    const QString mDevMDSettingSensorCntKey                 = "dspsetting/SensorCnt"              ;

    const QString mDevSizeSettingSensorLengthKey            = "dspsetting/SensorLength"           ;
    const QString mDevSizeSettingDistanceToRejectorKey      = "dspsetting/DistanceToRejector"     ;
    const QString mDevSizeSettingDistanceToWeightCheckerKey = "dspsetting/DistanceToWeightChecker";
    const QString mDevSizeSettingDistancePhotoToSensorKey   = "dspsetting/DistancePhotoToSensor"  ;
    const QString mDevSizeSettingDistanceBtwSensorKey       = "dspsetting/DistanceBtwSensor"      ;
    //const QString "dspsetting/RejectorReadyTime"                                                ;

    const QString mHMISettingSWPowerOffKey                  = "hmisetting/SWPowerOff"             ;
    const QString mHMISettingIsDayModeKey                   = "hmisetting/IsDayMode"              ;
    const QString mHMISettingIsDebugModeKey                 = "hmisetting/IsDebugMode"            ;
    const QString mHMISettingDynamicFactorKey               = "hmisetting/DynamicFactor"          ;
    const QString mHMISettingSimpleSenstivity01Key          = "hmisetting/SimpleSenstivity01"     ;
    const QString mHMISettingSimpleSenstivity02Key          = "hmisetting/SimpleSenstivity02"     ;
    const QString mHMISettingSimpleSenstivity03Key          = "hmisetting/SimpleSenstivity03"     ;
    const QString mHMISettingSimpleSenstivity04Key          = "hmisetting/SimpleSenstivity04"     ;
    const QString mHMISettingSimpleSenstivity05Key          = "hmisetting/SimpleSenstivity05"     ;

public:
    static LocalSettingSProvider * getInstance()
    {
        static LocalSettingSProvider *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new LocalSettingSProvider();
        }

        return mpSelf;
    }

    QString                  mOldVersion     ;
    InformationDto           mInformation    ;
    SecurityDto              mSecuritySetting;
    EnumDef::eLang           mLanguage       ;
    bool                     mIsDetail       ;
    EnumDef::eViewMode       mViewMode       ;
    TrendsOptionDto          mTROption;      ;
    QDate                    mBackupLastDate ;
    DevSettingDto            mDevSetting     ;
    HMISettingDto            mHMISetting     ;

    explicit LocalSettingSProvider(QObject * parent = nullptr):QObject(parent)
    {
        mpSetting = new QSettings("novasen", "WCMD", this);
    }
    ~LocalSettingSProvider()
    {

    }

    void start(QObject * pContext)
    {
        mpContext = pContext;

        qDebug() << "[LocalSettingSProvider::start]";
        load();

        connect(&mLanguageLoadTimer, SIGNAL(timeout()), this, SLOT(onStartLanguageLoad()));
        mLanguageLoadTimer.setSingleShot(true);
        mLanguageLoadTimer.setInterval(100);
        mLanguageLoadTimer.start();
    }

    void stop()
    {
        disconnect(&mLanguageLoadTimer, SIGNAL(timeout()), this, SLOT(onStartLanguageLoad()));
        mLanguageLoadTimer.stop();
        mIsRunning = false;
        emit signalEventStopped();
    }

    void factoryReset()
    {
        CHECK_FALSE_RETURN(mIsRunning)

        mpSetting->clear();
        mpSetting->setValue(mInfoHMIVersionKey   ,BUILD_HMI_VERSION);

        mIsRunning = false;

        stop();
    }

    void setInformation(InformationDto dto)
    {
        CHECK_FALSE_RETURN(mIsRunning);

        internalSetInformation(dto);

        emit signalEventChangedInformation(dto);
    }

    void setSecurity(SecurityDto dto)
    {
        CHECK_FALSE_RETURN(mIsRunning);

        internalSetSecurity(dto);
    }

    void setLanuguage(EnumDef::eLang lang)
    {
        CHECK_FALSE_RETURN(mIsRunning)

        internalSetLanuguage(lang);
    }

    void setGUIIsDetail(bool value)
    {
        CHECK_FALSE_RETURN(mIsRunning)

        internalSetGUIIsDetail(value);

        emit signalEventChangedIsDetail(value);
    }

    void setGUIViewMode(EnumDef::eViewMode value)
    {
        CHECK_FALSE_RETURN(mIsRunning)

        internalSetGUIViewMode(value);

        emit signalEventChangedViewMode((int)value);
    }

    void setTROption(TrendsOptionDto dto)
    {
        CHECK_FALSE_RETURN(mIsRunning)

        internalSetTROption(dto);

        emit signalEventChangedTROption(dto);
    }

    void setBackupLastDate(QDate date)
    {
        CHECK_FALSE_RETURN(mIsRunning)

        internalSetBackupLastDate(date);

        emit signalEventChangedBackupLastDate(date);
    }

    void setDevSetting(DevSettingDto dto)
    {
        CHECK_FALSE_RETURN(mIsRunning)

        internalSetDevSetting(dto);

        emit signalEventChangedDevSetting(mDevSetting);
    }

    void setHMISetting(HMISettingDto dto)
    {
        CHECK_FALSE_RETURN(mIsRunning)

        internalSetHMISetting(dto);

        emit signalEventChangedHMISetting(mHMISetting);
    }

private slots:
    void onStartLanguageLoad()
    {
        internalSetLanuguage(mLanguage);

        qDebug() << "[LocalSettingSProvider::started]";

        mIsRunning = true;
        emit signalEventStarted();
    }

private:
    LanguageHelper mLanguageHelper;
    QTimer         mLanguageLoadTimer;
    QObject      * mpContext = nullptr;
    QSettings    * mpSetting   = nullptr;
    bool           mIsRunning  = false;

    void load()
    {
        qDebug() << "[LocalSettingSProvider::load]";

        mOldVersion                                                = mpSetting->value(mInfoHMIVersionKey                       , "0.0.0"                                                ).toString();

        mInformation.mCompany                                      = mpSetting->value(mInfoCompanyKey                          , pDefaultSP->INFO_COMPANY                               ).toString();
        mInformation.mTel                                          = mpSetting->value(mInfoTelKey                              , pDefaultSP->INFO_TEL                                   ).toString();
        mInformation.mModel                                        = pDefaultSP->INFO_MODEL;
        mInformation.mSN                                           = QSysInfo::machineUniqueId()                                                                                                    ;
        mInformation.mDeviceNumber                                 = mpSetting->value(mInfoDevNumberKey                        , pDefaultSP->INFO_DEVICE_NUM                                        ).toInt()   ;
        mInformation.mHMIVersion                                   = pDefaultSP->INFO_HMI_VER;
        mInformation.mPower                                        = mpSetting->value(mInfoPowerKey                            , pDefaultSP->INFO_POWER                                             ).toString();
        mInformation.mHomepage                                     = mpSetting->value(mInfoHomepageKey                         , pDefaultSP->INFO_HOMEPAGE                                          ).toString();
        mInformation.mMaxWeight                                    = mpSetting->value(mInfoMaxWeightKey                        , pDefaultSP->INFO_MAX_WEIGHT                                        ).toInt()   ;

        mSecuritySetting.mPwd                                      = mpSetting->value(mSecPwdKey                               , pDefaultSP->SEC_PWD                                                ).toString();
        mSecuritySetting.mAdminPwd                                 = mpSetting->value(mSecAdminPwdKey                          , pDefaultSP->SEC_ADMIN_PWD                                          ).toString();

        mLanguage                                                  = (EnumDef::eLang)mpSetting->value(mLanguageKey             , pDefaultSP->LANGUAGE                                               ).toInt()   ;

        mIsDetail                                                  = mpSetting->value(mGUIIsDetailKey                          , pDefaultSP->GUI_IS_DETAIL                                          ).toBool()  ;

        mViewMode                                                  = (EnumDef::eViewMode)mpSetting->value(mGUIViewModeKey      , pDefaultSP->GUI_VIEW_MODE                                          ).toInt()   ;

        mTROption.mTrendsOptionH                                   = mpSetting->value(mTRIsUnderToOverKey                      , pDefaultSP->TR_OPTION_H                                            ).toInt()   ;
        mTROption.mTrendsOptionFilter                              = mpSetting->value(mTRIsTotalKey                            , pDefaultSP->TR_OPTION_FILTER                                       ).toInt()   ;
        mTROption.mTrendsOptionLastN                               = mpSetting->value(mTRIstotalSinceStartKey                  , pDefaultSP->TR_OPTION_TOTAL_SINCE_START                            ).toInt()   ;
        mTROption.mTrendsLastNValue                                = mpSetting->value(mTRLastNValueKey                         , pDefaultSP->TR_LAST_N_VALUE                                        ).toInt()   ;

        QString date                                               = mpSetting->value(mProcBackupLastDateKey                   , pDefaultSP->BACKUP_LAST_DATE                                       ).toString();
        if(date.length() != 10)
            date = "2020/01/01";
        mBackupLastDate                                            = QDate::fromString(date, DATE_FMT);

        mDevSetting.mDspForm.mCommSetting.mBuzzerTime              = mpSetting->value(mDevCommSettingBuzzerTimeKey             , pDefaultSP->DEV_SETTING_BUZZERTIME                                 ).toInt()   ;
        mDevSetting.mDspForm.mCommSetting.mLampTime                = mpSetting->value(mDevCommSettingLampTimeKey               , pDefaultSP->DEV_SETTING_LAMPTIME                                   ).toInt()   ;
        mDevSetting.mDspForm.mCommSetting.mRejectorRunTimeRatio    = mpSetting->value(mDevCommSettingRejectorRunTimeRatioKey   , pDefaultSP->DEV_SETTING_RJ_RUN_TIME_RATIO                          ).toInt()   ;
        mDevSetting.mDspForm.mCommSetting.mRejectorOpenTime        = mpSetting->value(mDevCommSettingRejectorOpenTimeKey       , pDefaultSP->DEV_SETTING_RJ_OPENTIME                                ).toInt()   ;
        mDevSetting.mDspForm.mCommSetting.mSpeedConverter          = mpSetting->value(mDevCommSettingSpeedConverterKey         , pDefaultSP->DEV_SETTING_SPEED_CONVERTER                            ).toInt()   ;
        mDevSetting.mDspForm.mCommSetting.mMotorDirection          = mpSetting->value(mDevCommSettingMotorDirectionKey         , pDefaultSP->DEV_SETTING_MOTOR_DIR                                  ).toInt()   ;
        mDevSetting.mDspForm.mCommSetting.mMotorType               = mpSetting->value(mDevCommSettingMotorTypeKey              , pDefaultSP->DEV_SETTING_MOTOR_TYPE                                 ).toInt()   ;
        mDevSetting.mDspForm.mCommSetting.mMachineMode             = mpSetting->value(mDevCommSettingMachineModeKey            , pDefaultSP->DEV_SETTING_MACHINE_MODE                               ).toInt()   ;
        mDevSetting.mDspForm.mCommSetting.mMotorMDRatio            = mpSetting->value(mDevCommSettingMotorMDRatioKey           , pDefaultSP->DEV_SETTING_MOTOR_MD_RATIO                             ).toInt()   ;
        mDevSetting.mDspForm.mCommSetting.mMotorWCRatio            = mpSetting->value(mDevCommSettingMotorWCRatioKey           , pDefaultSP->DEV_SETTING_MOTOR_WC_RATIO                             ).toInt()   ;
        mDevSetting.mDspForm.mCommSetting.mMotorRJRatio            = mpSetting->value(mDevCommSettingMotorRJRatioKey           , pDefaultSP->DEV_SETTING_MOTOR_RJ_RATIO                             ).toInt()   ;

        mDevSetting.mDspForm.mWCSetting.mDisplayStability          = mpSetting->value(mDevWCSettingDisplayStabilityKey         , pDefaultSP->DEV_SETTING_DP_STABILITY                               ).toInt()   ;
        mDevSetting.mDspForm.mWCSetting.mMeasureCueSign            = mpSetting->value(mDevWCSettingMeasureCueSignKey           , pDefaultSP->DEV_SETTING_MEASURE_CUE_SIGN                           ).toInt()   ;
        mDevSetting.mDspForm.mWCSetting.mMinStaticWeight           = mpSetting->value(mDevWCSettingMinStaticWeightKey          , pDefaultSP->DEV_SETTING_MIN_STATIC_WEIGHT                          ).toInt()   ;
        mDevSetting.mDspForm.mWCSetting.mMinDynamicWeight          = mpSetting->value(mDevWCSettingMinDynamicWeightKey         , pDefaultSP->DEV_SETTING_MIN_DYNAMIC_WEIGHT                         ).toInt()   ;
        mDevSetting.mDspForm.mWCSetting.mScaler                    = mpSetting->value(mDevWCSettingScalerKey                   , pDefaultSP->DEV_SETTING_SCALER                                     ).toInt()   ;
        mDevSetting.mDspForm.mWCSetting.mStaticFactor              = mpSetting->value(mDevWCSettingStaticFactorKey             , pDefaultSP->DEV_SETTING_STATIC_FACTOR                              ).toInt()   ;
        mDevSetting.mDspForm.mWCSetting.mPhotoIsOn                 = mpSetting->value(mDevWCSettingWCPhotoIsOnKey              , pDefaultSP->DEV_SETTING_WC_PHOTO_IS_ON                             ).toBool() == true ? 1 : 0  ;
        mDevSetting.mDspForm.mWCSetting.mStaticStandardWeight      = mpSetting->value(mDevWCSettingStaticStandardWeightKey     , pDefaultSP->DEV_SETTING_STATIC_STANDARD_WEIGHT                     ).toInt()   ;
        mDevSetting.mDspForm.mWCSetting.mDynamicBaseWeight         = mpSetting->value(mDevWCSettingDynamicBaseWeightKey        , pDefaultSP->DEV_SETTING_DYNAMIC_BASE_WEIGHT                        ).toInt()   ;

        mDevSetting.mDspForm.mMDSetting.mDetectMode                = mpSetting->value(mDevMDSettingModeKey                     , pDefaultSP->DEV_SETTING_DETECT_MODE                                ).toInt()   ;
        mDevSetting.mDspForm.mMDSetting.mDetectDetectTime          = mpSetting->value(mDevMDSettingDetectDetectTimeKey         , pDefaultSP->DEV_SETTING_DETECT_DETECT_TIME                         ).toInt()   ;
        mDevSetting.mDspForm.mMDSetting.mRunDetectTime             = mpSetting->value(mDevMDSettingRunDetectTimeKey            , pDefaultSP->DEV_SETTING_RUN_DETECT_TIME                            ).toInt()   ;
        mDevSetting.mDspForm.mMDSetting.mSignalDelayTime           = mpSetting->value(mDevMDSettingSignalDelayTimeKey          , pDefaultSP->DEV_SETTING_SIGNAL_DELAY_TIME                          ).toInt()   ;
        mDevSetting.mDspForm.mMDSetting.mPhotoIsOn                 = mpSetting->value(mDevMDSettingMDPhotoIsOnKey              , pDefaultSP->DEV_SETTING_MD_PHOTO_IS_ON                             ).toBool() == true ? 1 : 0  ;
        mDevSetting.mDspForm.mMDSetting.mSensorCnt                 = mpSetting->value(mDevMDSettingSensorCntKey                , pDefaultSP->DEV_SETTING_SENSOR_CNT                                 ).toInt()   ;

        mDevSetting.mDspForm.mSizeSetting.mSensorLength            = mpSetting->value(mDevSizeSettingSensorLengthKey           , pDefaultSP->DEV_SETTING_SENSOR_LEN                                 ).toInt()   ;
        mDevSetting.mDspForm.mSizeSetting.mDistanceToRejector      = mpSetting->value(mDevSizeSettingDistanceToRejectorKey     , pDefaultSP->DEV_SETTING_DIST_TO_RJ                                 ).toInt()   ;
        mDevSetting.mDspForm.mSizeSetting.mDistanceBtwSensor       = mpSetting->value(mDevSizeSettingDistanceBtwSensorKey      , pDefaultSP->DEV_SETTING_DIST_BTW_SENSOR                            ).toInt()   ;
        mDevSetting.mDspForm.mSizeSetting.mDistanceToWeightChecker = mpSetting->value(mDevSizeSettingDistanceToWeightCheckerKey, pDefaultSP->DEV_SETTING_DIST_TO_WC                                 ).toInt()   ;
        mDevSetting.mDspForm.mSizeSetting.mDistancePhotoToSensor   = mpSetting->value(mDevSizeSettingDistancePhotoToSensorKey  , pDefaultSP->DEV_SETTING_DIST_TO_PHOTO_SENSOR                       ).toInt()   ;

        mHMISetting.mSWPowerOff                                    = mpSetting->value(mHMISettingSWPowerOffKey                 , pDefaultSP->HMI_SETTING_SW_POWER_OFF                               ).toBool()  ;
        mHMISetting.mIsDayMode                                     = mpSetting->value(mHMISettingIsDayModeKey                  , pDefaultSP->HMI_SETTING_IS_DAY_MODE                                ).toBool()  ;
        mHMISetting.mIsDebugMode                                   = mpSetting->value(mHMISettingIsDebugModeKey                , pDefaultSP->HMI_SETTING_IS_DEBUG_MODE                              ).toBool()  ;
        mHMISetting.mDynamicFactor                                 = mpSetting->value(mHMISettingDynamicFactorKey              , pDefaultSP->HMI_SETTING_DYNAMIC_FACTOR                             ).toInt()   ;
        mHMISetting.mSimpleSenstivity01                            = mpSetting->value(mHMISettingSimpleSenstivity01Key         , pDefaultSP->HMI_SETTING_SAMPLE_SENSTIVITY_01                       ).toInt()   ;
        mHMISetting.mSimpleSenstivity02                            = mpSetting->value(mHMISettingSimpleSenstivity02Key         , pDefaultSP->HMI_SETTING_SAMPLE_SENSTIVITY_02                       ).toInt()   ;
        mHMISetting.mSimpleSenstivity03                            = mpSetting->value(mHMISettingSimpleSenstivity03Key         , pDefaultSP->HMI_SETTING_SAMPLE_SENSTIVITY_03                       ).toInt()   ;
        mHMISetting.mSimpleSenstivity04                            = mpSetting->value(mHMISettingSimpleSenstivity04Key         , pDefaultSP->HMI_SETTING_SAMPLE_SENSTIVITY_04                       ).toInt()   ;
        mHMISetting.mSimpleSenstivity05                            = mpSetting->value(mHMISettingSimpleSenstivity05Key         , pDefaultSP->HMI_SETTING_SAMPLE_SENSTIVITY_05                       ).toInt()   ;

        internalSetInformation    (mInformation);
        internalSetSecurity       (mSecuritySetting);
        internalSetLanuguage      (mLanguage);
        internalSetGUIIsDetail    (mIsDetail);
        internalSetGUIViewMode    (mViewMode);
        internalSetTROption       (mTROption);
        internalSetBackupLastDate (mBackupLastDate);
        internalSetDevSetting     (mDevSetting);
        internalSetHMISetting     (mHMISetting);
    }

    void internalSetInformation(InformationDto dto)
    {
        mInformation = dto;

        mpSetting->setValue(mInfoCompanyKey  , mInformation.mCompany     );
        mpSetting->setValue(mInfoTelKey      , mInformation.mTel         );
        mpSetting->setValue(mInfoDevNumberKey, mInformation.mDeviceNumber);
        mpSetting->setValue(mInfoPowerKey    , mInformation.mPower       );
        mpSetting->setValue(mInfoHomepageKey , mInformation.mHomepage    );
        mpSetting->setValue(mInfoMaxWeightKey, mInformation.mMaxWeight   );
    }

    void internalSetSecurity(SecurityDto dto)
    {
        mSecuritySetting = dto;

        mpSetting->setValue(mSecPwdKey     , dto.mPwd);
        mpSetting->setValue(mSecAdminPwdKey, dto.mAdminPwd    );
    }

    void internalSetLanuguage(EnumDef::eLang lang)
    {
        mLanguage = lang;

        mpSetting->setValue(mLanguageKey, lang);

        mLanguageHelper.setLanguage(mpContext, lang);
    }

    void internalSetGUIIsDetail(bool value)
    {
        mIsDetail = value;

        mpSetting->setValue(mGUIIsDetailKey, value);
    }

    void internalSetGUIViewMode(EnumDef::eViewMode value)
    {
        mViewMode = value;

        mpSetting->setValue(mGUIViewModeKey, value);
    }

    void internalSetTROption(TrendsOptionDto dto)
    {
        mTROption = dto;

        mpSetting->setValue(mTRIsUnderToOverKey    , dto.mTrendsOptionH     );
        mpSetting->setValue(mTRIsTotalKey          , dto.mTrendsOptionFilter);
        mpSetting->setValue(mTRIstotalSinceStartKey, dto.mTrendsOptionLastN );
        mpSetting->setValue(mTRLastNValueKey       , dto.mTrendsLastNValue  );
    }

    void internalSetBackupLastDate(QDate date)
    {
        mBackupLastDate = date;

        mpSetting->setValue(mProcBackupLastDateKey, date.toString(DATE_FMT));
    }

    void internalSetDevSetting(DevSettingDto dto)
    {
        mDevSetting = dto;

        mpSetting->setValue(mDevCommSettingBuzzerTimeKey             , dto.mDspForm.mCommSetting.mBuzzerTime             );
        mpSetting->setValue(mDevCommSettingLampTimeKey               , dto.mDspForm.mCommSetting.mLampTime               );
        mpSetting->setValue(mDevCommSettingRejectorRunTimeRatioKey   , dto.mDspForm.mCommSetting.mRejectorRunTimeRatio   );
        mpSetting->setValue(mDevCommSettingRejectorOpenTimeKey       , dto.mDspForm.mCommSetting.mRejectorOpenTime       );
        mpSetting->setValue(mDevCommSettingSpeedConverterKey         , dto.mDspForm.mCommSetting.mSpeedConverter         );
        mpSetting->setValue(mDevCommSettingMotorDirectionKey         , dto.mDspForm.mCommSetting.mMotorDirection         );
        mpSetting->setValue(mDevCommSettingMotorTypeKey              , dto.mDspForm.mCommSetting.mMotorType              );
        mpSetting->setValue(mDevCommSettingMachineModeKey            , dto.mDspForm.mCommSetting.mMachineMode            );
        mpSetting->setValue(mDevCommSettingMotorMDRatioKey           , dto.mDspForm.mCommSetting.mMotorMDRatio           );
        mpSetting->setValue(mDevCommSettingMotorWCRatioKey           , dto.mDspForm.mCommSetting.mMotorWCRatio           );
        mpSetting->setValue(mDevCommSettingMotorRJRatioKey           , dto.mDspForm.mCommSetting.mMotorRJRatio           );

        mpSetting->setValue(mDevWCSettingDisplayStabilityKey         , dto.mDspForm.mWCSetting.mDisplayStability         );
        mpSetting->setValue(mDevWCSettingMeasureCueSignKey           , dto.mDspForm.mWCSetting.mMeasureCueSign           );
        mpSetting->setValue(mDevWCSettingMinStaticWeightKey          , dto.mDspForm.mWCSetting.mMinStaticWeight          );
        mpSetting->setValue(mDevWCSettingMinDynamicWeightKey         , dto.mDspForm.mWCSetting.mMinDynamicWeight         );
        mpSetting->setValue(mDevWCSettingScalerKey                   , dto.mDspForm.mWCSetting.mScaler                   );
        mpSetting->setValue(mDevWCSettingStaticFactorKey             , dto.mDspForm.mWCSetting.mStaticFactor             );
        mpSetting->setValue(mDevWCSettingWCPhotoIsOnKey              , dto.mDspForm.mWCSetting.mPhotoIsOn == 1 ? true : false);
        mpSetting->setValue(mDevWCSettingStaticStandardWeightKey     , dto.mDspForm.mWCSetting.mStaticStandardWeight     );
        mpSetting->setValue(mDevWCSettingDynamicBaseWeightKey        , dto.mDspForm.mWCSetting.mDynamicBaseWeight        );

        mpSetting->setValue(mDevMDSettingModeKey                     , dto.mDspForm.mMDSetting.mDetectMode               );
        mpSetting->setValue(mDevMDSettingDetectDetectTimeKey         , dto.mDspForm.mMDSetting.mDetectDetectTime         );
        mpSetting->setValue(mDevMDSettingRunDetectTimeKey            , dto.mDspForm.mMDSetting.mRunDetectTime            );
        mpSetting->setValue(mDevMDSettingSignalDelayTimeKey          , dto.mDspForm.mMDSetting.mSignalDelayTime          );
        mpSetting->setValue(mDevMDSettingMDPhotoIsOnKey              , dto.mDspForm.mMDSetting.mPhotoIsOn == 1 ? true : false);
        mpSetting->setValue(mDevMDSettingSensorCntKey                , dto.mDspForm.mMDSetting.mSensorCnt                );

        mpSetting->setValue(mDevSizeSettingSensorLengthKey           , dto.mDspForm.mSizeSetting.mSensorLength           );
        mpSetting->setValue(mDevSizeSettingDistanceToRejectorKey     , dto.mDspForm.mSizeSetting.mDistanceToRejector     );
        mpSetting->setValue(mDevSizeSettingDistanceBtwSensorKey      , dto.mDspForm.mSizeSetting.mDistanceBtwSensor      );
        mpSetting->setValue(mDevSizeSettingDistanceToWeightCheckerKey, dto.mDspForm.mSizeSetting.mDistanceToWeightChecker);
        mpSetting->setValue(mDevSizeSettingDistancePhotoToSensorKey  , dto.mDspForm.mSizeSetting.mDistancePhotoToSensor  );
    }

    void internalSetHMISetting(HMISettingDto dto)
    {
        mHMISetting = dto;

        mpSetting->setValue(mHMISettingSWPowerOffKey                 , dto.mSWPowerOff        );
        mpSetting->setValue(mHMISettingIsDayModeKey                  , dto.mIsDayMode         );
        mpSetting->setValue(mHMISettingIsDebugModeKey                , dto.mIsDebugMode       );
        mpSetting->setValue(mHMISettingDynamicFactorKey              , dto.mDynamicFactor     );
        mpSetting->setValue(mHMISettingSimpleSenstivity01Key         , dto.mSimpleSenstivity01);
        mpSetting->setValue(mHMISettingSimpleSenstivity02Key         , dto.mSimpleSenstivity02);
        mpSetting->setValue(mHMISettingSimpleSenstivity03Key         , dto.mSimpleSenstivity03);
        mpSetting->setValue(mHMISettingSimpleSenstivity04Key         , dto.mSimpleSenstivity04);
        mpSetting->setValue(mHMISettingSimpleSenstivity05Key         , dto.mSimpleSenstivity05);
    }
signals:
    void signalEventStarted        ();
    void signalEventStopped        ();

    void signalEventChangedIsDetail(bool value);
    void signalEventChangedViewMode(int value);
    void signalEventChangedIsEnableWC(bool value);
    void signalEventChangedTROption(TrendsOptionDto dto);
    void signalEventChangedInformation(InformationDto dto);
    void signalEventChangedBackupLastDate(QDate date);
    void signalEventChangedDevSetting(DevSettingDto dto);
    void signalEventChangedHMISetting(HMISettingDto dto);
};
#endif // LOCALSETTINGSPROVIDER_H
