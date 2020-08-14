#include "dspmanager.h"

DSPManager::DSPManager(DeviceSetting ds, ProductSetting ps, QObject *parent) : QObject(parent)
{
    setDeviceSetting(ds);
    setProductSetting(ps);
    //mListProductStatus.insert(ps.mSeq, new ProductStatus(ps, this));
    //mDeviceSetting = ds;
}

void DSPManager::reset(DeviceSetting ds, ProductSetting ps)
{
    mIsDelete                       =false                                  ;
    mIsConnect                      =true                                   ;

    //mRunMode                        =EnumDefine::RUN_MODE::RUN_MODE_MONITOR ;
    mRun                            =EnumDefine::RunState::STOP             ;
    mIsWeightCheckerGraphOn         =false                                  ;
    mIsMetalDetectorGraphOn         =false                                  ;
    mIsMetalDetectorFilterGraphOn   =false                                  ;
    mWCAlarm                        =EnumDefine::AlarmType::NONE_ALARM      ;
    mWCCurrWeight                   =0.0f                                   ;
    mWCCurrEventType                = EnumDefine::EventType::EVENT_NONE_TYPE;
    mMDAlarm                        =EnumDefine::AlarmType::NONE_ALARM;
    mMDCurrSignal                   = 0                                     ;
    mMDCurrEventType                = EnumDefine::EventType::EVENT_NONE_TYPE;

    mDeviceID                       = 0                                     ;
    mMajorVersion                   = 0                                     ;
    mMinorVersion                   = 0                                     ;
    mMaintenanceVersion             = 0                                     ;

    QList<ProductStatus *> listProductStatus = mListProductStatus.values();

    for(int i = 0; i < listProductStatus.size(); i ++)
    {
        listProductStatus.at(i)->reset(ps);
    }

    setDeviceSetting(ds);
    setProductSetting(ps);
}

void DSPManager::resetStatistics()
{
    QList<ProductStatus *> listProductStatus = mListProductStatus.values();

    for(int i = 0; i < listProductStatus.size(); i ++)
    {
        listProductStatus.at(i)->resetStatistics();
    }
}
void DSPManager::setIsConnect(bool value)
{
    mIsConnect = value;
}

void DSPManager::setRemoteDeviceSetting(DeviceSetting ds)
{
    mRemoteDeviceSetting = ds;

    if(mDeviceSetting.remoteSettingCompare(&ds) == false)
    {
        qDebug() << "setRemoteDeviceSetting : set alarm";

        mIsDeviceSettingAlarm = true;
    }
    else
    {
        qDebug() << "setRemoteDeviceSetting : set alarm";

        mIsDeviceSettingAlarm = false;
    }
}

void DSPManager::setRemoteProductSetting(ProductSetting ps)
{
    mRemoteProductSetting = ps;

    if(mSelectedProductSetting.remoteSettingCompare(&ps) == false)
    {
        qDebug() << "setRemoteProductSetting : set alarm";

        mIsProductSettingAlarm = true;
    }
    else
    {
        qDebug() << "setRemoteProductSetting : unset alarm";

        mIsProductSettingAlarm = false;
    }
}


void DSPManager::setDeviceStatus             (DeviceStatus value)
{
    mWait                           = value.mWait                        ;

    if(mRun == EnumDefine::RunState::STOP && value.mRun != EnumDefine::RunState::STOP)
    {
        mWCCurrWeight = 0;
        mWCCurrEventType = EnumDefine::EventType::WEIGHT_NORMAL_TYPE;
    }

    mRun                            = value.mRun                         ;
    mIsWeightCheckerGraphOn         = value.mIsWeightCheckerGraphOn      ;
    mIsMetalDetectorGraphOn         = value.mIsMetalDetectorGraphOn      ;
    mIsMetalDetectorFilterGraphOn   = value.mIsMetalDetectorFilterGraphOn;
    mWCAlarm                        = value.mWCAlarm                     ;

    // 정지상태에서만 실시간값 표기
    if(mRun == false)
    {
        mWCCurrWeight               = value.mCurrWeight                  ;
        mWCCurrEventType                = value.mWCErrorType                 ;
    }
    mMDAlarm                        = value.mMDAlarm                     ;
    mMDCurrSignal                   = value.mMDSignal                    ;
    mMDCurrEventType                = value.mMDErrorType                 ;
}
void DSPManager::setDeviceInfo               (DeviceInfo value)
{
    mDeviceID           = value.mID                ;
    mMajorVersion       = value.mMajorVersion      ;
    mMinorVersion       = value.mMinorVersion      ;
    mMaintenanceVersion = value.mMaintenanceVersion;
}
void DSPManager::addEvent                    (quint16 productSeq, EventInfo value)
{
    //qDebug() << "addEvent";

    if(mListProductStatus.contains(productSeq) == false)
        return;

    mListProductStatus[productSeq]->addEvent(value);

    if(value.mEventType == EnumDefine::EventType::WEIGHT_NORMAL_TYPE        ||
       value.mEventType == EnumDefine::EventType::WEIGHT_UNDER_WARNING_TYPE ||
       value.mEventType == EnumDefine::EventType::WEIGHT_OVER_WARNING_TYPE  ||
       value.mEventType == EnumDefine::EventType::WEIGHT_UNDER_TYPE         ||
       value.mEventType == EnumDefine::EventType::WEIGHT_OVER_TYPE          ||
       value.mEventType == EnumDefine::EventType::WEIGHT_ETCERROR_TYPE      ||
       value.mEventType == EnumDefine::EventType::WEIGHT_ETC_METAL_ERROR_TYPE)
    {
        mWCCurrWeight = value.mEventValue;
        mWCCurrEventType = value.mEventType;
        mLastMeasuredWeight = value.mEventValue;
    }
}

void DSPManager::setProductSetting           (ProductSetting value)
{
    if(mListProductStatus.contains(value.mSeq) == false)
    {
        mListProductStatus.insert(value.mSeq, new ProductStatus(value));
    }
    else
    {
        mListProductStatus[value.mSeq]->setProductSetting(value);
    }

    mSelectedProductSetting = value;
}
void DSPManager::setDeviceSetting            (DeviceSetting value)
{
    mDeviceSetting = value;
}
