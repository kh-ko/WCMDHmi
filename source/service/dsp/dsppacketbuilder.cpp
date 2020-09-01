#include "dsppacketbuilder.h"
#include "source/service/dsp/myalloc.h"

DspPacketBuilder::DspPacketBuilder(QObject *parent) : QObject(parent)
{
    memset(&mDataStore, 0x00, sizeof(StDataStore));
    mDataStore.mEvent.mEventCnt = 0xffffffff;
}

bool DspPacketBuilder::compareDeviceSetting(StDeviceSetting * pDeviceSetting)
{
    if(memcmp(&mDataStore.mDeviceSetting, pDeviceSetting, sizeof(StDeviceSetting)) == 0)
        return true;

    return false;
}
bool DspPacketBuilder::compareProductSetting(StProductSetting * pProductSetting)
{
    if(memcmp(&mDataStore.mProductSetting, pProductSetting, sizeof(StProductSetting)) == 0)
        return true;

    return false;
}

bool DspPacketBuilder::compareCmdDeviceStatus(StDeviceStatus * deviceStatus)
{
    if(//mDataStore.mDummy01.mRunMode != deviceStatus->mRunMode ||
       mDataStore.mWCGraphOnOffCmd.mWCGraphOnOff != deviceStatus->mIsWeightCheckerGraphOn ||
       mDataStore.mMDGraphOnOffCmd.mMDGraphOnOff != deviceStatus->mIsMetalDetectorGraphOn)
        return false;

    return true;
}
void DspPacketBuilder::setZeroCmd()
{
    mDataStore.mZeroCmd.mZero = 1;
}
void DspPacketBuilder::setFactoryResetCmd()
{
    mDataStore.mFactoryResetCmd.mFactoryReset = 1;
}
void DspPacketBuilder::setWeightCaribCmd(quint16 value)
{
    mDataStore.mWeightCaribCmd.mWeightCarib = value;
}
void DspPacketBuilder::setRunCmd(quint16 value)
{
    mDataStore.mRunCmd.mRun = value;
}
void DspPacketBuilder::setRunModeCmd(quint16 value)
{
    // not use
    //mDataStore.mRunModeCmd.mRunMode = (quint16)value;
}
void DspPacketBuilder::setWCGraphOnOffCmd (bool value)
{
    mDataStore.mWCGraphOnOffCmd.mWCGraphOnOff = value ? 1 : 0;
}
void DspPacketBuilder::setMDGraphOnOffCmd(bool value)
{
    mDataStore.mMDGraphOnOffCmd.mMDGraphOnOff = value ? 1 : 0;
}
void DspPacketBuilder::setMDFilterGraphOnOffCmd(bool value)
{
    mDataStore.mMDFilterGraphOnOffCmd.mMDFilterGraphOnOff = value ? 1 : 0;
}
void DspPacketBuilder::setDeviceIdCmd(quint32 value)
{
    mDataStore.mDeviceIdCmd.mDeviceId = value;
}
void DspPacketBuilder::setDeviceSetting(DeviceSetting deviceSetting)
{
    mDataStore.mDeviceSetting.mLampTime                = deviceSetting.mLampTime;
    mDataStore.mDeviceSetting.mBuzzerTime              = deviceSetting.mBuzzerTime;
    mDataStore.mDeviceSetting.mSpeedConverter          = deviceSetting.mSpeedConverter;
    mDataStore.mDeviceSetting.mMotorDirection          = deviceSetting.mMotorDirection;
    //mDataStore.mDeviceSetting.mIsDebugMode             = deviceSetting.mIsDebugMode ? 1 : 0;
    mDataStore.mDeviceSetting.mSensorLength            = deviceSetting.mSensorLength;
    mDataStore.mDeviceSetting.mDistanceToRejector      = deviceSetting.mDistanceToRejector;
    //mDataStore.mDeviceSetting.mRejectorReadyTime       = deviceSetting.mRejectorReadyTime;
    mDataStore.mDeviceSetting.mMDPhotoIsOn             = deviceSetting.mMDPhotoIsOn ? 1 : 0;
    mDataStore.mDeviceSetting.mWCPhotoIsOn             = deviceSetting.mWCPhotoIsOn ? 1 : 0;
    mDataStore.mDeviceSetting.mRejectorRunTimeRatio    = deviceSetting.mRejectorRunTimeRatio;
    mDataStore.mDeviceSetting.mStaticFactor            = deviceSetting.mStaticFactor;
    //mDataStore.mDeviceSetting.mDynamicFactor           = deviceSetting.mDynamicFactor;
    mDataStore.mDeviceSetting.mScaler                  = deviceSetting.mScaler;
    mDataStore.mDeviceSetting.mDisplayStability        = deviceSetting.mDisplayStability;
    mDataStore.mDeviceSetting.mMeasureCueSign          = deviceSetting.mMeasureCueSign;
    mDataStore.mDeviceSetting.mMinStaticWeight         = deviceSetting.mMinStaticWeight;
    mDataStore.mDeviceSetting.mMinDynamicWeight        = deviceSetting.mMinDynamicWeight;
    mDataStore.mDeviceSetting.mDetectMode              = deviceSetting.mMode;
    mDataStore.mDeviceSetting.mDistanceBtwSensor       = deviceSetting.mDistanceBtwSensor;
    mDataStore.mDeviceSetting.mDetectDetectTime        = deviceSetting.mDetectDetectTime;
    mDataStore.mDeviceSetting.mRunDetectTime           = deviceSetting.mRunDetectTime;
    mDataStore.mDeviceSetting.mDistanceToWeightChecker = deviceSetting.mDistanceToWeightChecker;
    mDataStore.mDeviceSetting.mDistancePhotoToSensor   = deviceSetting.mDistancePhotoToSensor;
    mDataStore.mDeviceSetting.mSignalDelayTime         = deviceSetting.mSignalDelayTime;
    mDataStore.mDeviceSetting.mStaticStandardWeight    = deviceSetting.mStaticStandardWeight;
    mDataStore.mDeviceSetting.mDynamicBaseWeight       = deviceSetting.mDynamicBaseWeight;
    mDataStore.mDeviceSetting.mSensorCnt               = deviceSetting.mSensorCnt;
}

void DspPacketBuilder::setProductSetting(ProductSetting productSetting)
{
    mDataStore.mProductSetting.mProductSeq              = productSetting.mNo;
    mDataStore.mProductSetting.mLength                  = productSetting.mLength;
    mDataStore.mProductSetting.mSpeed                   = productSetting.mSpeed;
    mDataStore.mProductSetting.mMotorAccelerationTime   = productSetting.mMotorAccelerationTime;
    mDataStore.mProductSetting.mNormalWeight            = productSetting.mNormalWeight;
    mDataStore.mProductSetting.mUnderWarningWeight      = productSetting.mUnderWarningWeight;
    mDataStore.mProductSetting.mOverWarningWeight       = productSetting.mOverWarningWeight;
    mDataStore.mProductSetting.mUnderWeight             = productSetting.mUnderWeight;
    mDataStore.mProductSetting.mOverWeight              = productSetting.mOverWeight;
    mDataStore.mProductSetting.mTareWeight              = productSetting.mTareWeight;
    mDataStore.mProductSetting.mWeightCheckerNGMotion   = productSetting.mWCNGMotion;
    mDataStore.mProductSetting.mMetalDetectorSenstivity = productSetting.mMDSenstivity;
    mDataStore.mProductSetting.mMetalDetectorNGMotion   = productSetting.mMDNGMotion;

    mDataStore.mDeviceSetting.mDynamicFactor            = productSetting.mDynamicFactor;
}

bool DspPacketBuilder::setDeviceStatus(StDeviceStatus * deviceStatus)
{
    if(memcmp(&mDataStore.mDeviceStatus, deviceStatus, sizeof(StDeviceStatus)) != 0)
    {
        memcpy(&mDataStore.mDeviceStatus, deviceStatus, sizeof(StDeviceStatus));
        return true;
    }

    return false;
}

bool DspPacketBuilder::setDeviceInfo(StDeviceInfo * deviceInfo)
{
    if(memcmp(&mDataStore.mDeviceInfo, deviceInfo, sizeof(StDeviceInfo)) != 0)
    {
        memcpy(&mDataStore.mDeviceInfo, deviceInfo, sizeof(StDeviceInfo));
        return true;
    }

    return false;
}

int DspPacketBuilder::setEvent(StEventInfo * eventInfo)
{
    bool isFirst = mDataStore.mEvent.mEventCnt == 0xffffffff ? true : false;

    // HMI만 재부팅될 경우 이전 이벤트가 중복되어 발생하여, 최초 이벤트 영역수신시에는 UI로 이벤트를 보내지 않는다.
    if(isFirst)
    {
        memcpy(&mDataStore.mEvent, eventInfo, sizeof(StEventInfo));
        return 0;
    }

    int addedCnt = eventInfo->mEventCnt - mDataStore.mEvent.mEventCnt;

    if(addedCnt != 0)
    {
        qDebug() << "dsp event cnt : "  << eventInfo->mEventCnt;
        memcpy(&mDataStore.mEvent, eventInfo, sizeof(StEventInfo));
    }

    return addedCnt;
}

StPacket *  DspPacketBuilder::createReqPacketZeroCmd              (){ return createReqWritePacket(sizeof(StZeroCommand),                             ZeroCommandAddr,              (char *)(&(mDataStore.mZeroCmd))); }
StPacket *  DspPacketBuilder::createReqPacketFactoryResetCmd      (){ return createReqWritePacket(sizeof(StFactoryResetCommand),                     FactoryResetCommandAddr,      (char *)(&(mDataStore.mFactoryResetCmd))); }
StPacket *  DspPacketBuilder::createReqPacketWeightCaribCmd       (){ return createReqWritePacket(sizeof(StWeightCaribrationCommand),                WeightCaribCommandAddr,       (char *)(&(mDataStore.mWeightCaribCmd ))); }
StPacket *  DspPacketBuilder::createReqPacketRunCmd               (){ return createReqWritePacket(sizeof(StRunCommand),                              RunCommandAddr,               (char *)(&(mDataStore.mRunCmd))); }
//StPacket *  DspPacketBuilder::createReqPacketRunModeCmd           (){ return createReqWritePacket(sizeof(StRunModeCommand),                          RunModeCommandAddr,           (char *)(&(mDataStore.mRunModeCmd))); }
StPacket *  DspPacketBuilder::createReqPacketWCGraphOnOffCmd      (){ return createReqWritePacket(sizeof(StWCGraphOnOffCommand),                     WCGraphOnOffCommandAddr,      (char *)(&(mDataStore.mWCGraphOnOffCmd))); }
StPacket *  DspPacketBuilder::createReqPacketMDGraphOnOffCmd      (){ return createReqWritePacket(sizeof(StMDGraphOnOffCommand),                     MDGraphOnOffCommandAddr,      (char *)(&(mDataStore.mMDGraphOnOffCmd))); }
StPacket *  DspPacketBuilder::createReqPacketMDFilterGraphOnOffCmd(){ return createReqWritePacket(sizeof(StMDFilterGraphOnOffCommand),               MDFilterGraphOnOffCommandAddr,(char *)(&(mDataStore.mMDFilterGraphOnOffCmd))); }
StPacket *  DspPacketBuilder::createReqPacketDeviceIdCmd          (){ return createReqWritePacket(sizeof(StDeviceIdCommand),                         DeviceIdCommandAddr,          (char *)(&(mDataStore.mDeviceIdCmd))); }
StPacket *  DspPacketBuilder::createReqPacketDeviceStatusCmd      (){ return createReqWritePacket(sizeof(StWCGraphOnOffCommand) + sizeof(StMDGraphOnOffCommand), WCGraphOnOffCommandAddr, (char *)(&(mDataStore.mWCGraphOnOffCmd))); }
StPacket *  DspPacketBuilder::createReqPacketDeviceSetting        (){ return createReqWritePacket(sizeof(StDeviceSetting),                           DeviceSettingAddr,            (char *)(&(mDataStore.mDeviceSetting))); }
StPacket *  DspPacketBuilder::createReqPacketProductSetting       (){ return createReqWritePacket(sizeof(StProductSetting),                          ProductSettingAddr,           (char *)(&(mDataStore.mProductSetting))); }
StPacket *  DspPacketBuilder::createReqPacketTotalSetting         (){ return createReqWritePacket(sizeof(StProductSetting)+sizeof(StDeviceSetting),  DeviceSettingAddr,            (char *)(&(mDataStore.mDeviceSetting))); }
StPacket *  DspPacketBuilder::createReqWritePacket(int contentSize, quint64 startAddr, char * content)
{
    int mallocSize = sizeof(StPacket) + contentSize;
    StPacket * packet = (StPacket *)MyAlloc::alloc(mallocSize);//malloc(mallocSize);

    if(packet == nullptr)
        return packet;

    packet->mFuncCode = EnumDefine::FuncCode::WRITE_TYPE;
    packet->mStartAddress = startAddr;
    packet->mSize = contentSize/2;
    memcpy( &(packet->mData), content, contentSize);
    return packet;
}

StPacket *  DspPacketBuilder::createReqPacketReadDeviceStatus     (){ return createReqReadPacket(sizeof(StDeviceStatus),                                                    DeviceStatusAddr );}
StPacket *  DspPacketBuilder::createReqPacketReadDeviceInfo       (){ return createReqReadPacket(sizeof(StDeviceInfo),                                                      DeviceInfoAddr   );}
StPacket *  DspPacketBuilder::createReqPacketReadEvent            (){ return createReqReadPacket(sizeof(StEventInfo),                                                       EventInfoAddr    );}
StPacket *  DspPacketBuilder::createReqPacketReadReadArea         (){ return createReqReadPacket(sizeof(StDeviceStatus)+sizeof(StDeviceInfo)+sizeof(StEventInfo),           DeviceStatusAddr );}
StPacket *  DspPacketBuilder::createReqPacketReadAll              (){ return createReqReadPacket(sizeof(StDeviceSetting)+sizeof(StProductSetting) + sizeof(StDeviceStatus)+sizeof(StDeviceInfo)+sizeof(StEventInfo) , DeviceSettingAddr);}
StPacket *  DspPacketBuilder::createReqReadPacket                 (int contentSize, quint64 startAddr)
{
    StPacket * packet = (StPacket *)MyAlloc::alloc(sizeof(StPacket)); //malloc(sizeof(StPacket));

    if(packet == nullptr)
        return packet;

    packet->mFuncCode = EnumDefine::FuncCode::READ_TYPE;
    packet->mStartAddress = startAddr;
    packet->mSize = contentSize/2;
    return packet;
}

DeviceSetting    DspPacketBuilder::createSignalObjDeviceSetting        (StDeviceSetting * pstDeviceSetting)
{
    DeviceSetting ds;

    ds.mLampTime                    = pstDeviceSetting->mLampTime               ;
    ds.mBuzzerTime                  = pstDeviceSetting->mBuzzerTime             ;
    ds.mSpeedConverter              = pstDeviceSetting->mSpeedConverter         ;
    ds.mMotorDirection              = pstDeviceSetting->mMotorDirection         ;
    //ds.mIsDebugMode                 = pstDeviceSetting->mIsDebugMode == 0 ? false : true;
    ds.mSensorLength                = pstDeviceSetting->mSensorLength           ;
    ds.mDistanceToRejector          = pstDeviceSetting->mDistanceToRejector     ;
    ds.mMDPhotoIsOn                 = pstDeviceSetting->mMDPhotoIsOn == 0 ? false : true;
    ds.mWCPhotoIsOn                 = pstDeviceSetting->mWCPhotoIsOn == 0 ? false : true;
    //ds.mRejectorReadyTime           = pstDeviceSetting->mRejectorReadyTime      ;
    ds.mRejectorRunTimeRatio        = pstDeviceSetting->mRejectorRunTimeRatio   ;
    ds.mStaticFactor                = pstDeviceSetting->mStaticFactor           ;
    ds.mDynamicFactor               = pstDeviceSetting->mDynamicFactor          ;
    ds.mScaler                      = pstDeviceSetting->mScaler                 ;
    ds.mDisplayStability            = pstDeviceSetting->mDisplayStability       ;
    ds.mMeasureCueSign              = pstDeviceSetting->mMeasureCueSign         ;
    ds.mMinStaticWeight             = pstDeviceSetting->mMinStaticWeight        ;
    ds.mMinDynamicWeight            = pstDeviceSetting->mMinDynamicWeight       ;
    ds.mMode                        = (EnumDefine::SensorMode)mDataStore.mDeviceSetting.mDetectMode             ;
    ds.mDistanceBtwSensor           = pstDeviceSetting->mDistanceBtwSensor      ;
    ds.mDetectDetectTime            = pstDeviceSetting->mDetectDetectTime       ;
    ds.mRunDetectTime               = pstDeviceSetting->mRunDetectTime          ;
    ds.mDistanceToWeightChecker     = pstDeviceSetting->mDistanceToWeightChecker;
    ds.mDistancePhotoToSensor       = pstDeviceSetting->mDistancePhotoToSensor  ;
    ds.mSignalDelayTime             = pstDeviceSetting->mSignalDelayTime        ;
    ds.mStaticStandardWeight        = pstDeviceSetting->mStaticStandardWeight   ;
    ds.mDynamicBaseWeight           = pstDeviceSetting->mDynamicBaseWeight      ;
    ds.mSensorCnt                   = pstDeviceSetting->mSensorCnt              ;

    return ds;
}

ProductSetting    DspPacketBuilder::createSignalObjProductSetting       (StProductSetting *pstProductSetting)
{
    ProductSetting ps;

    ps.mNo                      = pstProductSetting->mProductSeq             ;
    ps.mLength                  = pstProductSetting->mLength                 ;
    ps.mSpeed                   = pstProductSetting->mSpeed                  ;
    ps.mMotorAccelerationTime   = pstProductSetting->mMotorAccelerationTime  ;
    ps.mUnderWeight             = pstProductSetting->mUnderWeight            ;
    ps.mUnderWarningWeight      = pstProductSetting->mUnderWarningWeight     ;
    ps.mNormalWeight            = pstProductSetting->mNormalWeight           ;
    ps.mOverWarningWeight       = pstProductSetting->mOverWarningWeight      ;
    ps.mOverWeight              = pstProductSetting->mOverWeight             ;
    ps.mTareWeight              = pstProductSetting->mTareWeight             ;
    ps.mWCNGMotion              = (EnumDefine::NGMotion)pstProductSetting->mWeightCheckerNGMotion  ;
    ps.mMDSenstivity            = pstProductSetting->mMetalDetectorSenstivity;
    ps.mMDNGMotion              = (EnumDefine::NGMotion)pstProductSetting->mMetalDetectorNGMotion  ;

    return ps;
}

DeviceStatus    DspPacketBuilder::createSignalObjDeviceStatus         ()
{
    DeviceStatus deviceStatus;

    deviceStatus.mWait                         = mDataStore.mDeviceStatus.mWait                                 ;
    deviceStatus.mRun                          = (EnumDefine::RunState)mDataStore.mDeviceStatus.mRun            ;
    deviceStatus.mIsWeightCheckerGraphOn       = mDataStore.mDeviceStatus.mIsWeightCheckerGraphOn               ;
    deviceStatus.mIsMetalDetectorGraphOn       = mDataStore.mDeviceStatus.mIsMetalDetectorGraphOn               ;
    deviceStatus.mIsMetalDetectorFilterGraphOn = mDataStore.mDeviceStatus.mIsMetalDetectorFilterGraphOn         ;
    deviceStatus.mWCAlarm                      = (EnumDefine::AlarmType)mDataStore.mDeviceStatus.mWCAlarm       ;
    deviceStatus.mCurrWeight                   = mDataStore.mDeviceStatus.mCurrWeight                           ;
    deviceStatus.mWCErrorType                  = (EnumDefine::EventType)mDataStore.mDeviceStatus.mWCErrorType   ;
    deviceStatus.mMDAlarm                      = (EnumDefine::AlarmType)mDataStore.mDeviceStatus.mMDAlarm       ;
    deviceStatus.mMDSignal                     = mDataStore.mDeviceStatus.mMDSignal                             ;
    deviceStatus.mMDErrorType                  = (EnumDefine::EventType)mDataStore.mDeviceStatus.mMDErrorType   ;

    return deviceStatus;
}

DeviceInfo      DspPacketBuilder::createSignalObjDeviceInfo           ()
{
    DeviceInfo deviceInfo;

    deviceInfo.mID                              = mDataStore.mDeviceInfo.mID                                    ;
    deviceInfo.mMajorVersion                    = mDataStore.mDeviceInfo.mMajorVersion                          ;
    deviceInfo.mMinorVersion                    = mDataStore.mDeviceInfo.mMinorVersion                          ;
    deviceInfo.mMaintenanceVersion              = mDataStore.mDeviceInfo.mMaintenanceVersion                    ;

    return deviceInfo;
}

EventInfo       DspPacketBuilder::createSignalObjEventInfo            (int idx)
{
    EventInfo eventInfo;

    eventInfo.mEventType  = (EnumDefine::EventType)mDataStore.mEvent.mListEvent[idx].mEventType     ;
    eventInfo.mEventValue = mDataStore.mEvent.mListEvent[idx].mEventValue                           ;

    return eventInfo;
}
