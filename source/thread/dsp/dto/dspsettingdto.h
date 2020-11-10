#ifndef DSPSETTINGDTO_H
#define DSPSETTINGDTO_H

#include <QObject>

#include "source/thread/dsp/dto/dspaddressdto.h"
#include "source/model/dspsettingmodel.h"

class DspSettingDto
{
public:
    StDeviceSetting mDeviceSetting;

    DspSettingDto(){}
    DspSettingDto(const DspSettingDto& copy)
    {
        memcpy(&mDeviceSetting, &(copy.mDeviceSetting), sizeof(StDeviceSetting));
    }
    DspSettingDto(StDeviceSetting* copy)
    {
        memcpy(&mDeviceSetting, copy, sizeof(StDeviceSetting));
    }
    DspSettingDto(DspSettingModel* copy)
    {
        mDeviceSetting.mLampTime                = copy->mLampTime               ;
        mDeviceSetting.mBuzzerTime              = copy->mBuzzerTime             ;
        mDeviceSetting.mSpeedConverter          = copy->mSpeedConverter         ;
        mDeviceSetting.mMotorDirection          = copy->mMotorDirection         ;
        mDeviceSetting.mMotorType               = copy->mMotorType              ;
        mDeviceSetting.mMotorMDRatio            = copy->mMotorMDRatio           ;
        mDeviceSetting.mMotorWCRatio            = copy->mMotorWCRatio           ;
        mDeviceSetting.mMotorRJRatio            = copy->mMotorRJRatio           ;
        mDeviceSetting.mSensorLength            = copy->mSensorLength           ;
        mDeviceSetting.mDistanceToRejector      = copy->mDistanceToRejector     ;
        mDeviceSetting.mMDPhotoIsOn             = copy->mMDPhotoIsOn            ;
        mDeviceSetting.mWCPhotoIsOn             = copy->mWCPhotoIsOn            ;
        mDeviceSetting.mRejectorRunTimeRatio    = copy->mRejectorRunTimeRatio   ;
        mDeviceSetting.mStaticFactor            = copy->mStaticFactor           ;
        mDeviceSetting.mScaler                  = copy->mScaler                 ;
        mDeviceSetting.mDisplayStability        = copy->mDisplayStability       ;
        mDeviceSetting.mMeasureCueSign          = copy->mMeasureCueSign         ;
        mDeviceSetting.mMinStaticWeight         = copy->mMinStaticWeight        ;
        mDeviceSetting.mMinDynamicWeight        = copy->mMinDynamicWeight       ;
        mDeviceSetting.mDetectMode              = copy->mMode                   ;
        mDeviceSetting.mDistanceBtwSensor       = copy->mDistanceBtwSensor      ;
        mDeviceSetting.mDetectDetectTime        = copy->mDetectDetectTime       ;
        mDeviceSetting.mRunDetectTime           = copy->mRunDetectTime          ;
        mDeviceSetting.mDistanceToWeightChecker = copy->mDistanceToWeightChecker;
        mDeviceSetting.mDistancePhotoToSensor   = copy->mDistancePhotoToSensor  ;
        mDeviceSetting.mSignalDelayTime         = copy->mSignalDelayTime        ;
        mDeviceSetting.mStaticStandardWeight    = copy->mStaticStandardWeight   ;
        mDeviceSetting.mDynamicBaseWeight       = copy->mDynamicBaseWeight      ;
        mDeviceSetting.mSensorCnt               = copy->mSensorCnt              ;
        mDeviceSetting.mRejectorOpenTime        = copy->mRejectorOpenTime       ;
    }
    ~DspSettingDto(){}

    DspSettingDto& operator=(const DspSettingDto& other)
    {
        memcpy(&mDeviceSetting, &(other.mDeviceSetting), sizeof(StDeviceSetting));

        return *this;
    }
    DspSettingDto& operator=(StDeviceSetting * other)
    {
        memcpy(&mDeviceSetting, other, sizeof(StDeviceSetting));

        return *this;
    }

    DspSettingDto& operator=(DspSettingModel* other)
    {
        mDeviceSetting.mLampTime                = other->mLampTime               ;
        mDeviceSetting.mBuzzerTime              = other->mBuzzerTime             ;
        mDeviceSetting.mSpeedConverter          = other->mSpeedConverter         ;
        mDeviceSetting.mMotorDirection          = other->mMotorDirection         ;
        mDeviceSetting.mMotorType               = other->mMotorType              ;
        mDeviceSetting.mMotorMDRatio            = other->mMotorMDRatio           ;
        mDeviceSetting.mMotorWCRatio            = other->mMotorWCRatio           ;
        mDeviceSetting.mMotorRJRatio            = other->mMotorRJRatio           ;
        mDeviceSetting.mSensorLength            = other->mSensorLength           ;
        mDeviceSetting.mDistanceToRejector      = other->mDistanceToRejector     ;
        mDeviceSetting.mMDPhotoIsOn             = other->mMDPhotoIsOn            ;
        mDeviceSetting.mWCPhotoIsOn             = other->mWCPhotoIsOn            ;
        mDeviceSetting.mRejectorRunTimeRatio    = other->mRejectorRunTimeRatio   ;
        mDeviceSetting.mStaticFactor            = other->mStaticFactor           ;
        mDeviceSetting.mScaler                  = other->mScaler                 ;
        mDeviceSetting.mDisplayStability        = other->mDisplayStability       ;
        mDeviceSetting.mMeasureCueSign          = other->mMeasureCueSign         ;
        mDeviceSetting.mMinStaticWeight         = other->mMinStaticWeight        ;
        mDeviceSetting.mMinDynamicWeight        = other->mMinDynamicWeight       ;
        mDeviceSetting.mDetectMode              = other->mMode                   ;
        mDeviceSetting.mDistanceBtwSensor       = other->mDistanceBtwSensor      ;
        mDeviceSetting.mDetectDetectTime        = other->mDetectDetectTime       ;
        mDeviceSetting.mRunDetectTime           = other->mRunDetectTime          ;
        mDeviceSetting.mDistanceToWeightChecker = other->mDistanceToWeightChecker;
        mDeviceSetting.mDistancePhotoToSensor   = other->mDistancePhotoToSensor  ;
        mDeviceSetting.mSignalDelayTime         = other->mSignalDelayTime        ;
        mDeviceSetting.mStaticStandardWeight    = other->mStaticStandardWeight   ;
        mDeviceSetting.mDynamicBaseWeight       = other->mDynamicBaseWeight      ;
        mDeviceSetting.mSensorCnt               = other->mSensorCnt              ;
        mDeviceSetting.mRejectorOpenTime        = other->mRejectorOpenTime       ;
        return *this;
    }

    DspSettingModel * toDspSettingModel()
    {
        DspSettingModel * pTemp = new DspSettingModel();
        pTemp->setLampTime               (mDeviceSetting.mLampTime               );
        pTemp->setBuzzerTime             (mDeviceSetting.mBuzzerTime             );
        pTemp->setSpeedConverter         (mDeviceSetting.mSpeedConverter         );
        pTemp->setMotorDirection         (mDeviceSetting.mMotorDirection         );
        pTemp->setMotorType              (mDeviceSetting.mMotorType              );
        pTemp->setMotorMDRatio           (mDeviceSetting.mMotorMDRatio           );
        pTemp->setMotorWCRatio           (mDeviceSetting.mMotorWCRatio           );
        pTemp->setMotorRJRatio           (mDeviceSetting.mMotorRJRatio           );
        pTemp->setSensorLength           (mDeviceSetting.mSensorLength           );
        pTemp->setDistanceToRejector     (mDeviceSetting.mDistanceToRejector     );
        pTemp->setMDPhotoIsOn            (mDeviceSetting.mMDPhotoIsOn            );
        pTemp->setWCPhotoIsOn            (mDeviceSetting.mWCPhotoIsOn            );
        pTemp->setRejectorRunTimeRatio   (mDeviceSetting.mRejectorRunTimeRatio   );
        pTemp->setStaticFactor           (mDeviceSetting.mStaticFactor           );
        pTemp->setScaler                 (mDeviceSetting.mScaler                 );
        pTemp->setDisplayStability       (mDeviceSetting.mDisplayStability       );
        pTemp->setMeasureCueSign         (mDeviceSetting.mMeasureCueSign         );
        pTemp->setMinStaticWeight        (mDeviceSetting.mMinStaticWeight        );
        pTemp->setMinDynamicWeight       (mDeviceSetting.mMinDynamicWeight       );
        pTemp->setMode                   (mDeviceSetting.mDetectMode             );
        pTemp->setDistanceBtwSensor      (mDeviceSetting.mDistanceBtwSensor      );
        pTemp->setDetectDetectTime       (mDeviceSetting.mDetectDetectTime       );
        pTemp->setRunDetectTime          (mDeviceSetting.mRunDetectTime          );
        pTemp->setDistanceToWeightChecker(mDeviceSetting.mDistanceToWeightChecker);
        pTemp->setDistancePhotoToSensor  (mDeviceSetting.mDistancePhotoToSensor  );
        pTemp->setSignalDelayTime        (mDeviceSetting.mSignalDelayTime        );
        pTemp->setStaticStandardWeight   (mDeviceSetting.mStaticStandardWeight   );
        pTemp->setDynamicBaseWeight      (mDeviceSetting.mDynamicBaseWeight      );
        pTemp->setSensorCnt              (mDeviceSetting.mSensorCnt              );
        pTemp->setRejectorOpenTime       (mDeviceSetting.mRejectorOpenTime       );

        return pTemp;
    }
};

Q_DECLARE_METATYPE(DspSettingDto);

#endif // DSPSETTINGDTO_H
