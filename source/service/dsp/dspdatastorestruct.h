#ifndef DATASTORESTRUCT_H
#define DATASTORESTRUCT_H

#pragma pack(push, 1)
struct StDspCommand{
    unsigned short mZero               ;
    unsigned short mFR                 ;
    unsigned short mWCCarib            ;
    unsigned short mRun                ;
    unsigned short mResetGroupCurrCount; // [edit]
    unsigned short mWCGraphOn          ;
    unsigned short mMDGraphOn          ;
    unsigned short mRefVoltageReset    ; //[add]
    unsigned int   mDeviceID           ;
};

struct StDspDevNetSetting{
    unsigned short mIp01                   ;
    unsigned short mIp02                   ;
    unsigned short mIp03                   ;
    unsigned short mIp04                   ;
    unsigned short mPort                   ;
};

struct StDspDevCommSetting{
    unsigned int   mLampTime               ;
    unsigned int   mBuzzerTime             ;
    unsigned int   mDummy01                ;
    unsigned int   mDummy02                ;
    unsigned int   mSpeedConverter         ;
    unsigned short mMotorDirection         ;
    unsigned short mMotorType              ;
    unsigned short mMotorMDRatio           ;
    unsigned short mMotorWCRatio           ;
    unsigned short mMotorRJRatio           ;
    unsigned short mMachineMode            ;
    unsigned int   mSorter01RunTimeRatio   ;
    unsigned int   mSorter01OpenTime       ;
    unsigned int   mSorter02RunTimeRatio   ;
    unsigned int   mSorter02OpenTime       ;
    unsigned int   mSorter03RunTimeRatio   ;
    unsigned int   mSorter03OpenTime       ;
    unsigned int   mSorter04RunTimeRatio   ;
    unsigned int   mSorter04OpenTime       ;
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
             short mRefVoltage             ; // [add]
    unsigned short mGraphPointCnt          ;
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
    unsigned short mDummy                  ;
    unsigned short mDistanceBtwSensor      ;
    unsigned short mDistanceToWeightChecker;
    unsigned short mDistancePhotoToSensor  ;
    unsigned short mDistToSorter01         ;
    unsigned short mDistToSorter02         ;
    unsigned short mDistToSorter03         ;
    unsigned short mDistToSorter04         ;
};

struct StDspPDCommSetting{
    unsigned short mProductNum             ;
    unsigned short mLength                 ;
    unsigned short mSpeed                  ;
    unsigned int   mMotorAccelerationTime  ;
    unsigned int   mMotorDecelerationTime  ;
    unsigned int   mGroupCount             ;
    unsigned short mGroupMotion            ;
    unsigned short mGroupLamp              ;
    unsigned short mGroupBuzzer            ;
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
    unsigned short mNGLamp                 ;
    unsigned short mNGBuzzer               ;
    unsigned short mFilterCoefficient      ;
    unsigned int   mMeasureCueSign         ;
    unsigned int   mMeasureSection         ;
    unsigned short mAutoSetting            ;
};

struct StDspPDMDSetting{
    unsigned short mSenstivity;
    unsigned short mNGMotion  ;
    unsigned short mNGLamp    ;
    unsigned short mNGBuzzer  ;
};

struct StDspCommStatus{
    unsigned short mRun;
    unsigned int   mGroupCurrCount;
};

struct StDspWCStatus{
    unsigned short mWait             ;
    unsigned short mAlarm            ;
    unsigned int   mCurrWeight       ;
    unsigned short mErrorType        ;
    unsigned short mIsGraphOn        ;
    unsigned short mMaxPDCntPerMin   ; // 분당
    unsigned short mCurrPDCntPerMin  ; // 순간 분당속도
    unsigned short mPDCntPerMin      ; // 분당 생산량
             short mADC              ;
             short mZeroProc         ; // [add]
    unsigned short mFilterCoefficient;
    unsigned int   mMeasureCueSign   ;
    unsigned int   mMeasureSection   ;
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
