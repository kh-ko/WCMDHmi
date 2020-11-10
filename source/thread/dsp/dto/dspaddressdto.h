#ifndef DSPADDRESSDTO_H
#define DSPADDRESSDTO_H

#pragma pack(push, 1)
struct StZeroCommand{
    unsigned short mZero;
};
struct StFactoryResetCommand{
    unsigned short mFactoryReset;
};
struct StWeightCaribrationCommand{
    unsigned short mWeightCarib;
};
struct StRunCommand{
    unsigned short mRun;
};
struct StRunModeCommand{
    unsigned short mRunMode;
};
struct StWCGraphOnOffCommand{
    unsigned short mWCGraphOnOff;
};
struct StMDGraphOnOffCommand{
    unsigned short mMDGraphOnOff;
};
struct StMDFilterGraphOnOffCommand{
    unsigned short mMDFilterGraphOnOff;
};
struct StDeviceIdCommand{
    unsigned int   mDeviceId;
};
struct StDeviceSetting{
    unsigned int   mLampTime               ;
    unsigned int   mBuzzerTime             ;
    unsigned int   mSpeedConverter         ;
    unsigned short mMotorDirection         ;
    unsigned short mSensorLength           ;
    unsigned short mDistanceToRejector     ;
    unsigned short mMDPhotoIsOn            ;
    unsigned short mWCPhotoIsOn            ;
    unsigned int   mRejectorRunTimeRatio   ;
    unsigned int   mStaticFactor           ;
    unsigned int   mDummy                  ;
    unsigned int   mScaler                 ;
    unsigned int   mDisplayStability       ;
    unsigned int   mMeasureCueSign         ;
    unsigned int   mMinStaticWeight        ;
    unsigned int   mMinDynamicWeight       ;
    unsigned short mDetectMode             ;
    unsigned short mDistanceBtwSensor      ;
    unsigned int   mDetectDetectTime       ;
    unsigned int   mRunDetectTime          ;
    unsigned short mDistanceToWeightChecker;
    unsigned short mDistancePhotoToSensor  ;
    unsigned int   mSignalDelayTime        ;
    unsigned int   mStaticStandardWeight   ;
    unsigned int   mDynamicBaseWeight      ;
    unsigned short mSensorCnt              ;
    unsigned int   mRejectorOpenTime       ;
    unsigned short mMotorType              ;
    unsigned short mMotorMDRatio           ;
    unsigned short mMotorWCRatio           ;
    unsigned short mMotorRJRatio           ;
};
struct StProductSetting{
    unsigned short mProductSeq             ;
    unsigned short mLength                 ;
    unsigned short mSpeed                  ;
    unsigned int   mMotorAccelerationTime  ;
    unsigned int   mNormalWeight           ;
    unsigned int   mUnderWarningWeight     ;
    unsigned int   mOverWarningWeight      ;
    unsigned int   mUnderWeight            ;
    unsigned int   mOverWeight             ;
    unsigned int   mTareWeight             ;
    unsigned short mWeightCheckerNGMotion  ;
    unsigned short mMetalDetectorSenstivity;
    unsigned short mMetalDetectorNGMotion  ;
    unsigned int   mDynamicFactor          ;
    unsigned short mWCEnableEtcError       ;
};
struct StDeviceStatus{
    unsigned short mWait                           ;
    unsigned short mRun                            ;
    unsigned short mIsWeightCheckerGraphOn         ;
    unsigned short mIsMetalDetectorGraphOn         ;
    unsigned short mIsMetalDetectorFilterGraphOn   ;
    unsigned short mWCAlarm                        ;
    unsigned int   mCurrWeight                     ;
    unsigned short mWCErrorType                    ;
    unsigned short mMDAlarm                        ;
    unsigned short mMDSignal                       ;
    unsigned short mMDErrorType                    ;
};
struct StDeviceInfo{
    unsigned int   mID                             ;
    unsigned short mMajorVersion                   ;
    unsigned short mMinorVersion                   ;
    unsigned short mMaintenanceVersion             ;
};
struct StEvent{
    unsigned int   mEventValue                     ;
    unsigned short mEventType                      ;
};
struct StEventInfo{
    unsigned int mEventCnt                         ;
    StEvent      mListEvent[10]                    ;
};

struct StDataStore{
    StZeroCommand               mZeroCmd                ;
    StFactoryResetCommand       mFactoryResetCmd        ;
    StWeightCaribrationCommand  mWeightCaribCmd         ;
    StRunCommand                mRunCmd                 ;
    StRunModeCommand            mDummy01                ;
    StWCGraphOnOffCommand       mWCGraphOnOffCmd        ;
    StMDGraphOnOffCommand       mMDGraphOnOffCmd        ;
    StMDFilterGraphOnOffCommand mMDFilterGraphOnOffCmd  ;
    StDeviceIdCommand           mDeviceIdCmd            ;
    StDeviceSetting             mDeviceSetting          ;
    StProductSetting            mProductSetting         ;
    StDeviceStatus              mDeviceStatus           ;
    StDeviceInfo                mDeviceInfo             ;
    StEventInfo                 mEvent                  ;
};

struct StWeightCheckerGraphPoint
{
    unsigned short mPointType   ;
    unsigned int   mRawValue    ;
    unsigned int   mFilterValue ;
};

struct StWeightCheckerGraph{
  unsigned short pointCnt;
  StWeightCheckerGraphPoint points[0];

};

struct StWeightGraphDataWrapper
{
public:
    int mRef;
    StWeightCheckerGraph mData;
};

struct StMetalDetectorGraph{
    unsigned short mSensorCnt       ;
    unsigned short mPointCnt        ;
    short          mArrayPoints[0]  ;
};

struct StMetalGraphDataWrapper{
    int mRef;
    StMetalDetectorGraph mData;
};


struct StPacket{
    char mSeq;
    char mFuncCode;
    unsigned short mStartAddress;
    unsigned short mSize;
    char mData[0];
};

struct StReadReadAreaContent
{
    StDeviceStatus              mDeviceStatus           ;
    StDeviceInfo                mDeviceInfo             ;
    StEventInfo                 mEvent                  ;
};

struct StReadAllContent
{
    StDeviceSetting             mDeviceSetting          ;
    StProductSetting            mProductSetting         ;
    StDeviceStatus              mDeviceStatus           ;
    StDeviceInfo                mDeviceInfo             ;
    StEventInfo                 mEvent                  ;
};

#pragma pack(pop)

#define ZeroCommandAddr                 ((quint64)((char *)(&(((StDataStore *)(0x02))->mZeroCmd                 ))))/2
#define FactoryResetCommandAddr         ((quint64)((char *)(&(((StDataStore *)(0x02))->mFactoryResetCmd         ))))/2
#define WeightCaribCommandAddr          ((quint64)((char *)(&(((StDataStore *)(0x02))->mWeightCaribCmd          ))))/2
#define RunCommandAddr                  ((quint64)((char *)(&(((StDataStore *)(0x02))->mRunCmd                  ))))/2
#define RunModeCommandAddr              ((quint64)((char *)(&(((StDataStore *)(0x02))->mRunModeCmd              ))))/2
#define WCGraphOnOffCommandAddr         ((quint64)((char *)(&(((StDataStore *)(0x02))->mWCGraphOnOffCmd         ))))/2
#define MDGraphOnOffCommandAddr         ((quint64)((char *)(&(((StDataStore *)(0x02))->mMDGraphOnOffCmd         ))))/2
#define MDFilterGraphOnOffCommandAddr   ((quint64)((char *)(&(((StDataStore *)(0x02))->mMDFilterGraphOnOffCmd   ))))/2
#define DeviceIdCommandAddr             ((quint64)((char *)(&(((StDataStore *)(0x02))->mDeviceIdCmd             ))))/2
#define DeviceSettingAddr               ((quint64)((char *)(&(((StDataStore *)(0x02))->mDeviceSetting           ))))/2
#define ProductSettingAddr              ((quint64)((char *)(&(((StDataStore *)(0x02))->mProductSetting          ))))/2
#define DeviceStatusAddr                ((quint64)((char *)(&(((StDataStore *)(0x02))->mDeviceStatus            ))))/2
#define DeviceInfoAddr                  ((quint64)((char *)(&(((StDataStore *)(0x02))->mDeviceInfo              ))))/2
#define EventInfoAddr                   ((quint64)((char *)(&(((StDataStore *)(0x02))->mEvent                   ))))/2

#define WeightCheckerGraphAddr          0x1000
#define MetalDetectorGraphAddr          0x2000
#define MetalDetectorFilterGraphAddr    0x3000
#endif // DSPADDRESSDTO_H
