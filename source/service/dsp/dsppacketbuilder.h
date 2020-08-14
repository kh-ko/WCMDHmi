#ifndef DSPPACKETBUILDER_H
#define DSPPACKETBUILDER_H

#include <QObject>

#include "source/model/devicesetting.h"
#include "source/model/productsetting.h"
#include "source/model/devicestatus.h"
#include "source/model/deviceinfo.h"
#include "source/model/eventinfo.h"

#pragma pack(push, 1)
struct StZeroCommand{
    quint16 mZero;
};
struct StFactoryResetCommand{
    quint16 mFactoryReset;
};
struct StWeightCaribrationCommand{
    quint16 mWeightCarib;
};
struct StRunCommand{
    quint16 mRun;
};
struct StRunModeCommand{
    quint16 mRunMode;
};
struct StWCGraphOnOffCommand{
    quint16 mWCGraphOnOff;
};
struct StMDGraphOnOffCommand{
    quint16 mMDGraphOnOff;
};
struct StMDFilterGraphOnOffCommand{
    quint16 mMDFilterGraphOnOff;
};
struct StDeviceIdCommand{
    quint32 mDeviceId;
};
struct StDeviceSetting{
    quint32 mLampTime               ;
    quint32 mBuzzerTime             ;
    quint32 mSpeedConverter         ;
    quint16 mMotorDirection         ;
    //quint16 mIsDebugMode            ;
    quint16 mSensorLength           ;
    quint16 mDistanceToRejector     ;
    //quint32 mRejectorReadyTime      ;
    quint16 mMDPhotoIsOn            ;
    quint16 mWCPhotoIsOn            ;
    quint32 mRejectorRunTimeRatio   ;
    quint32 mStaticFactor           ;
    quint32 mDynamicFactor          ;
    quint32 mScaler                 ;
    quint32 mDisplayStability       ;
    quint32 mMeasureCueSign         ;
    quint32 mMinStaticWeight        ;
    quint32 mMinDynamicWeight       ;
    quint16 mDetectMode             ;
    quint16 mDistanceBtwSensor      ;
    quint32 mDetectDetectTime       ;
    quint32 mRunDetectTime          ;
    quint16 mDistanceToWeightChecker;
    quint16 mDistancePhotoToSensor  ;
    quint32 mSignalDelayTime        ;
    quint32 mStaticStandardWeight   ;
    quint32 mDynamicBaseWeight      ;
    quint16 mSensorCnt              ;
};
struct StProductSetting{
    quint16 mProductSeq             ;
    quint16 mLength                 ;
    quint16 mSpeed                  ;
    quint32 mMotorAccelerationTime  ;
    quint32 mNormalWeight           ;
    quint32 mUnderWarningWeight     ;
    quint32 mOverWarningWeight      ;
    quint32 mUnderWeight            ;
    quint32 mOverWeight             ;
    quint32 mTareWeight             ;
    quint16 mWeightCheckerNGMotion  ;
    quint16 mMetalDetectorSenstivity;
    quint16 mMetalDetectorNGMotion  ;
};
struct StDeviceStatus{
    quint16 mWait                           ;
    quint16 mRun                            ;
    quint16 mIsWeightCheckerGraphOn         ;
    quint16 mIsMetalDetectorGraphOn         ;
    quint16 mIsMetalDetectorFilterGraphOn   ;
    quint16 mWCAlarm                        ;
    quint32 mCurrWeight                     ;
    quint16 mWCErrorType                    ;
    quint16 mMDAlarm                        ;
    quint16 mMDSignal                       ;
    quint16 mMDErrorType                    ;
};
struct StDeviceInfo{
    quint32 mID                             ;
    quint16 mMajorVersion                   ;
    quint16 mMinorVersion                   ;
    quint16 mMaintenanceVersion             ;
};
struct StEvent{
    quint32 mEventValue                     ;
    quint16 mEventType                      ;
};
struct StEventInfo{
    quint32 mEventCnt                       ;
    StEvent mListEvent[10]                  ;
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
    quint16 mPointType;
    qint32  mRawValue;
    qint32  mFilterValue;
};

struct StWeightCheckerGraph{
  quint16 pointCnt;
  StWeightCheckerGraphPoint points[0];

};
struct StPacket{
    char mSeq;
    char mFuncCode;
    quint16 mStartAddress;
    quint16 mSize;
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

class DspPacketBuilder : public QObject
{
    Q_OBJECT
public:
    StDataStore     mDataStore;
    explicit        DspPacketBuilder(QObject *parent = nullptr);
    bool            compareDeviceSetting                (StDeviceSetting * pDeviceSetting);
    bool            compareProductSetting               (StProductSetting * pProductSetting);
    bool            compareCmdDeviceStatus              (StDeviceStatus * deviceStatus);
    void            setZeroCmd                          ();
    void            setFactoryResetCmd                  ();
    void            setWeightCaribCmd                   (quint16 value);
    void            setRunCmd                           (quint16 value);
    void            setRunModeCmd                       (quint16 value);
    void            setWCGraphOnOffCmd                  (bool value);
    void            setMDGraphOnOffCmd                  (bool value);
    void            setMDFilterGraphOnOffCmd            (bool value);
    void            setDeviceIdCmd                      (quint32 value);
    void            setDeviceSetting                    (DeviceSetting deviceSetting);
    void            setProductSetting                   (ProductSetting productSetting);
    bool            setDeviceStatus                     (StDeviceStatus * deviceStatus);
    bool            setDeviceInfo                       (StDeviceInfo * deviceInfo);
    int             setEvent                            (StEventInfo * eventInfo);
    StPacket *      createReqPacketZeroCmd              ();
    StPacket *      createReqPacketFactoryResetCmd      ();
    StPacket *      createReqPacketWeightCaribCmd       ();
    StPacket *      createReqPacketRunCmd               ();
    StPacket *      createReqPacketRunModeCmd           ();
    StPacket *      createReqPacketWCGraphOnOffCmd      ();
    StPacket *      createReqPacketMDGraphOnOffCmd      ();
    StPacket *      createReqPacketMDFilterGraphOnOffCmd();
    StPacket *      createReqPacketDeviceIdCmd          ();
    StPacket *      createReqPacketDeviceStatusCmd      ();
    StPacket *      createReqPacketDeviceSetting        ();
    StPacket *      createReqPacketProductSetting       ();
    StPacket *      createReqPacketTotalSetting         ();
    StPacket *      createReqWritePacket                (int mallocSize, quint64 startAddr, char * content);
    StPacket *      createReqPacketReadDeviceStatus     ();
    StPacket *      createReqPacketReadDeviceInfo       ();
    StPacket *      createReqPacketReadEvent            ();
    StPacket *      createReqPacketReadReadArea         ();
    StPacket *      createReqPacketReadAll              ();
    StPacket *      createReqReadPacket                 (int contentSize, quint64 startAddr);
    DeviceSetting   createSignalObjDeviceSetting        (StDeviceSetting * pstDeviceSetting);
    ProductSetting  createSignalObjProductSetting       (StProductSetting * pstProductSetting);
    DeviceStatus    createSignalObjDeviceStatus         ();
    DeviceInfo      createSignalObjDeviceInfo           ();
    EventInfo       createSignalObjEventInfo            (int idx);

};

#endif // DSPPACKETBUILDER_H
