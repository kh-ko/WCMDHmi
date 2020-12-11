#ifndef DATASTORESTRUCT_H
#define DATASTORESTRUCT_H

#pragma pack(push, 1)
struct StDspCommand{
    unsigned short mZero      ;
    unsigned short mFR        ;
    unsigned short mWCCarib   ;
    unsigned short mRun       ;
    unsigned short mReserved01;
    unsigned short mWCGraphOn ;
    unsigned short mMDGraphOn ;
    unsigned short mReserved02;
    unsigned int   mDeviceID  ;
};

struct StDspDevCommSetting{
    unsigned int   mLampTime               ;
    unsigned int   mBuzzerTime             ;
    unsigned int   mRejectorRunTimeRatio   ;
    unsigned int   mRejectorOpenTime       ;
    unsigned int   mSpeedConverter         ;
    unsigned short mMotorDirection         ;
    unsigned short mMotorType              ;
    unsigned short mMotorMDRatio           ;
    unsigned short mMotorWCRatio           ;
    unsigned short mMotorRJRatio           ;
    unsigned short mMachineMode            ; // 1 = alu, 2 = wc, 3 = combi
};

struct StDspDevWCSetting{
    unsigned int   mDisplayStability       ;
    unsigned int   mMeasureCueSign         ;
    unsigned int   mMinStaticWeight        ;
    unsigned int   mMinDynamicWeight       ;
    unsigned int   mScaler                 ;
    unsigned int   mStaticFactor           ;
    unsigned short mPhotoIsOn              ;
    unsigned int   mStaticStandardWeight   ;
    unsigned int   mDynamicBaseWeight      ;
};

struct StDspDevMDSetting{
    unsigned short mDetectMode      ;
    unsigned int   mDetectDetectTime;
    unsigned int   mRunDetectTime   ;
    unsigned int   mSignalDelayTime ;
    unsigned short mPhotoIsOn       ;
    unsigned short mSensorCnt       ;
};

struct StDspDevSizeSetting{
    unsigned short mSensorLength           ;
    unsigned short mDistanceToRejector     ;
    unsigned short mDistanceBtwSensor      ;
    unsigned short mDistanceToWeightChecker;
    unsigned short mDistancePhotoToSensor  ;
};

struct StDspPDCommSetting{
    unsigned short mProductNum             ;
    unsigned short mLength                 ;
    unsigned short mSpeed                  ;
    unsigned int   mMotorAccelerationTime  ;
    unsigned int   mTargetCount            ; // [add]
};

struct StDspPDWCSetting{
    unsigned int   mNormalWeight           ;
    unsigned int   mUnderWarningWeight     ;
    unsigned int   mOverWarningWeight      ;
    unsigned int   mUnderWeight            ;
    unsigned int   mOverWeight             ;
    unsigned int   mTareWeight             ;
    unsigned short mNGMotion               ;
    unsigned int   mDynamicFactor          ;
    unsigned short mEnableEtcError         ;
};

struct StDspPDMDSetting{
    unsigned short mSenstivity;
    unsigned short mNGMotion  ;
};

struct StDspCommStatus{
    unsigned short mRun;
};

struct StDspWCStatus{
    unsigned short mWait      ;
    unsigned short mAlarm     ;
    unsigned int   mCurrWeight;
    unsigned short mErrorType ;
    unsigned short mIsGraphOn ;
};

struct StDspMDStatus{
    unsigned short mAlarm    ;
    unsigned short mSignal   ;
    unsigned short mErrorType;
    unsigned short mIsGraphOn;
};

struct StDspInfo{
    unsigned int   mID                ;
    unsigned short mMajorVersion      ;
    unsigned short mMinorVersion      ;
    unsigned short mMaintenanceVersion;
};

struct StDspEvent{
    unsigned int   mEventValue ;
    unsigned short mEventType  ;
};

struct StDspEventList{
    unsigned int mEventCnt     ;
    StDspEvent   mListEvent[10];
};

struct StDspWCGPoint
{
    unsigned short mPointType   ;
    unsigned int   mRawValue    ;
    unsigned int   mFilterValue ;
};

struct StDspWCG{
  unsigned short mPointCnt;
  StDspWCGPoint mPoints[0];
};

struct StDspMDG{
    unsigned short mSensorCnt       ;
    unsigned short mPointCnt        ;
    short          mArrayPoints[0]  ;
};
#pragma pack(pop)
#endif // DATASTORESTRUCT_H
