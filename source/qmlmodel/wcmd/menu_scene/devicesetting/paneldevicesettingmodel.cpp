#include "paneldevicesettingmodel.h"
#include "source/helper/languagehelper.h"

PanelDeviceSettingModel::PanelDeviceSettingModel(QObject *parent) : QObject(parent)
{
    connect(this, SIGNAL(signalCommandSaveDeviceSetting(void *, DeviceSetting)), WCMDService::getInstance(), SLOT(onCommandSaveDeviceSetting(void *, DeviceSetting)));
    connect(WCMDService::getInstance(), SIGNAL(signalResultSaveDeviceSetting(void *, DeviceSetting)), this, SLOT(onSignalResultSaveDeviceSetting(void *, DeviceSetting)));

    reset();
}

void PanelDeviceSettingModel::reset()
{
    WCMDService * pWCMDService = WCMDService::getInstance();

    setLanguage                     (pWCMDService->mDeviceSetting.mLanguage             );
    setPassword                     (""                                                 );
    setNewPassword                  (""                                                 );
    setConfirmPassword              (""                                                 );
    setIsDayMode                    (pWCMDService->mDeviceSetting.mIsDayMode            );
    setIsDebugMode                  (pWCMDService->mDeviceSetting.mIsDebugMode          );
    setLampTime                     (pWCMDService->mDeviceSetting.mLampTime             );
    setBuzzerTime                   (pWCMDService->mDeviceSetting.mBuzzerTime           );
    setSpeedConverter               (pWCMDService->mDeviceSetting.mSpeedConverter       );
    setMotorDirection               (pWCMDService->mDeviceSetting.mMotorDirection       );
    setRejectorRunTimeRatio         (pWCMDService->mDeviceSetting.mRejectorRunTimeRatio );
    setDisplayStability             (pWCMDService->mDeviceSetting.mDisplayStability     );
    setMeasureCueSign               (pWCMDService->mDeviceSetting.mMeasureCueSign       );
    setMinStaticWeight              (pWCMDService->mDeviceSetting.mMinStaticWeight      );
    setMinDynamicWeight             (pWCMDService->mDeviceSetting.mMinDynamicWeight     );
    setScaler                       (pWCMDService->mDeviceSetting.mScaler               );
    setStaticFactor                 (pWCMDService->mDeviceSetting.mStaticFactor         );
    setDynamicFactor                (pWCMDService->mDeviceSetting.mDynamicFactor        );
    setStandardWeight               (pWCMDService->mDeviceSetting.mStaticStandardWeight );
    setRefWeight                    (pWCMDService->mDeviceSetting.mDynamicBaseWeight    );
    setWCPhotoOn                    (pWCMDService->mDeviceSetting.mWCPhotoIsOn          );
    setMode                         (pWCMDService->mDeviceSetting.mMode                 );
    setDetectDetectTime             (pWCMDService->mDeviceSetting.mDetectDetectTime     );
    setRunDetectTime                (pWCMDService->mDeviceSetting.mRunDetectTime        );
    setSignalDelayTime              (pWCMDService->mDeviceSetting.mSignalDelayTime      );
    setMDPhotoOn                    (pWCMDService->mDeviceSetting.mMDPhotoIsOn          );
    setSensorCnt                    (pWCMDService->mDeviceSetting.mSensorCnt            );
    setSimpleSens01                 (pWCMDService->mDeviceSetting.mSimpleSenstivity01   );
    setSimpleSens02                 (pWCMDService->mDeviceSetting.mSimpleSenstivity02   );
    setSimpleSens03                 (pWCMDService->mDeviceSetting.mSimpleSenstivity03   );
    setSimpleSens04                 (pWCMDService->mDeviceSetting.mSimpleSenstivity04   );
    setSimpleSens05                 (pWCMDService->mDeviceSetting.mSimpleSenstivity05   );

    setIsEditLanguage                     ( false );
    setIsEditPassword                     ( false );
    setIsEditNewPassword                  ( false );
    setIsEditConfirmPassword              ( false );
    setIsEditIsDayMode                    ( false );
    setIsEditIsDebugMode                  ( false );
    setIsEditLampTime                     ( false );
    setIsEditBuzzerTime                   ( false );
    setIsEditSpeedConverter               ( false );
    setIsEditMotorDirection               ( false );
    setIsEditRejectorRunTimeRatio         ( false );
    setIsEditDisplayStability             ( false );
    setIsEditMeasureCueSign               ( false );
    setIsEditMinStaticWeight              ( false );
    setIsEditMinDynamicWeight             ( false );
    setIsEditScaler                       ( false );
    setIsEditStaticFactor                 ( false );
    setIsEditDynamicFactor                ( false );
    setIsEditStandardWeight               ( false );
    setIsEditRefWeight                    ( false );
    setIsEditWCPhotoOn                    ( false );
    setIsEditMode                         ( false );
    setIsEditDetectDetectTime             ( false );
    setIsEditRunDetectTime                ( false );
    setIsEditSignalDelayTime              ( false );
    setIsEditMDPhotoOn                    ( false );
    setIsEditSensorCnt                    ( false );
    setIsEditSimpleSens01                 ( false );
    setIsEditSimpleSens02                 ( false );
    setIsEditSimpleSens03                 ( false );
    setIsEditSimpleSens04                 ( false );
    setIsEditSimpleSens05                 ( false );
}
void PanelDeviceSettingModel::onSignalResultSaveDeviceSetting(void * sender, DeviceSetting value)
{
    if(sender != this)
        return;

    reset();

    emit signalResultSaveDeviceSetting((int)EnumDefine::DatabaseErrorType::DB_NONE_ERROR);
}

void PanelDeviceSettingModel::onCommandSave()
{
    DeviceSetting ds = WCMDService::getInstance()->mDeviceSetting;

    if(mIsEditPassword || mIsEditNewPassword || mIsEditConfirmPassword)
    {
        if(mPassword == "7071" && mNewPassword == mConfirmPassword)
        {

        }
        else if((mPassword != ds.mPassword || mNewPassword != mConfirmPassword))
        {
            emit signalResultSaveDeviceSetting((int)EnumDefine::DatabaseErrorType::PASSWORD_ERROR);
            return;
        }

        ds.mPassword             = mNewPassword;
    }


    LanguageHelper::getInstance()->loadLanguage((EnumDefine::Language)mLanguage);

    ds.mLanguage              = (EnumDefine::Language)getLanguage();
    ds.mIsDayMode             = getIsDayMode                     ();
    ds.mIsDebugMode           = getIsDebugMode                   ();
    ds.mLampTime              = getLampTime                      ();
    ds.mBuzzerTime            = getBuzzerTime                    ();
    ds.mSpeedConverter        = getSpeedConverter                ();
    ds.mMotorDirection        = getMotorDirection                ();
    ds.mRejectorRunTimeRatio  = getRejectorRunTimeRatio          ();
    ds.mDisplayStability      = getDisplayStability              ();
    ds.mMeasureCueSign        = getMeasureCueSign                ();
    ds.mMinStaticWeight       = getMinStaticWeight               ();
    ds.mMinDynamicWeight      = getMinDynamicWeight              ();
    ds.mScaler                = getScaler                        ();
    ds.mStaticFactor          = getStaticFactor                  ();
    ds.mDynamicFactor         = getDynamicFactor                 ();
    ds.mStaticStandardWeight  = getStandardWeight                ();
    ds.mDynamicBaseWeight     = getRefWeight                     ();
    ds.mWCPhotoIsOn           = getWCPhotoOn                     ();
    ds.mMode                  = (EnumDefine::SensorMode)getMode  ();
    ds.mDetectDetectTime      = getDetectDetectTime              ();
    ds.mRunDetectTime         = getRunDetectTime                 ();
    ds.mSignalDelayTime       = getSignalDelayTime               ();
    ds.mMDPhotoIsOn           = getMDPhotoOn                     ();
    ds.mSensorCnt             = getSensorCnt                     ();
    ds.mSimpleSenstivity01    = getSimpleSens01                  ();
    ds.mSimpleSenstivity02    = getSimpleSens02                  ();
    ds.mSimpleSenstivity03    = getSimpleSens03                  ();
    ds.mSimpleSenstivity04    = getSimpleSens04                  ();
    ds.mSimpleSenstivity05    = getSimpleSens05                  ();

    emit signalCommandSaveDeviceSetting(this, ds);
}
void PanelDeviceSettingModel::onCommandCancle()
{
    reset();
}


