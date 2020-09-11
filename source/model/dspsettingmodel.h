#ifndef DEVICESETTINGMODEL_H
#define DEVICESETTINGMODEL_H

#include <QObject>

class DspSettingModel : public QObject
{
    Q_OBJECT

public:
    quint32 mLampTime               ;
    quint32 mBuzzerTime             ;
    quint32 mSpeedConverter         ;
    quint16 mMotorDirection         ;
    quint16 mSensorLength           ;
    quint16 mDistanceToRejector     ;
    bool    mMDPhotoIsOn            ;
    bool    mWCPhotoIsOn            ;
    quint32 mRejectorReadyTime      ;
    quint32 mRejectorRunTimeRatio   ;
    quint32 mStaticFactor           ;
    quint32 mScaler                 ;
    quint32 mDisplayStability       ;
    quint32 mMeasureCueSign         ;
    quint32 mMinStaticWeight        ;
    quint32 mMinDynamicWeight       ;
    quint16 mMode                   ;
    quint16 mDistanceBtwSensor      ;
    quint32 mDetectDetectTime       ;
    quint32 mRunDetectTime          ;
    quint16 mDistanceToWeightChecker;
    quint16 mDistancePhotoToSensor  ;
    quint32 mSignalDelayTime        ;
    quint32 mStaticStandardWeight   ;
    quint32 mDynamicBaseWeight      ;
    quint16 mSensorCnt              ;

    void setLampTime               (quint32 value){ if( mLampTime                == value) return; mLampTime                = value; emit signalEventChangedLampTime               (mLampTime               );}
    void setBuzzerTime             (quint32 value){ if( mBuzzerTime              == value) return; mBuzzerTime              = value; emit signalEventChangedBuzzerTime             (mBuzzerTime             );}
    void setSpeedConverter         (quint32 value){ if( mSpeedConverter          == value) return; mSpeedConverter          = value; emit signalEventChangedSpeedConverter         (mSpeedConverter         );}
    void setMotorDirection         (quint16 value){ if( mMotorDirection          == value) return; mMotorDirection          = value; emit signalEventChangedMotorDirection         (mMotorDirection         );}
    void setSensorLength           (quint16 value){ if( mSensorLength            == value) return; mSensorLength            = value; emit signalEventChangedSensorLength           (mSensorLength           );}
    void setDistanceToRejector     (quint16 value){ if( mDistanceToRejector      == value) return; mDistanceToRejector      = value; emit signalEventChangedDistanceToRejector     (mDistanceToRejector     );}
    void setMDPhotoIsOn            (bool    value){ if( mMDPhotoIsOn             == value) return; mMDPhotoIsOn             = value; emit signalEventChangedMDPhotoIsOn            (mMDPhotoIsOn            );}
    void setWCPhotoIsOn            (bool    value){ if( mWCPhotoIsOn             == value) return; mWCPhotoIsOn             = value; emit signalEventChangedWCPhotoIsOn            (mWCPhotoIsOn            );}
    void setRejectorReadyTime      (quint32 value){ if( mRejectorReadyTime       == value) return; mRejectorReadyTime       = value; emit signalEventChangedRejectorReadyTime      (mRejectorReadyTime      );}
    void setRejectorRunTimeRatio   (quint32 value){ if( mRejectorRunTimeRatio    == value) return; mRejectorRunTimeRatio    = value; emit signalEventChangedRejectorRunTimeRatio   (mRejectorRunTimeRatio   );}
    void setStaticFactor           (quint32 value){ if( mStaticFactor            == value) return; mStaticFactor            = value; emit signalEventChangedStaticFactor           (mStaticFactor           );}
    void setScaler                 (quint32 value){ if( mScaler                  == value) return; mScaler                  = value; emit signalEventChangedScaler                 (mScaler                 );}
    void setDisplayStability       (quint32 value){ if( mDisplayStability        == value) return; mDisplayStability        = value; emit signalEventChangedDisplayStability       (mDisplayStability       );}
    void setMeasureCueSign         (quint32 value){ if( mMeasureCueSign          == value) return; mMeasureCueSign          = value; emit signalEventChangedMeasureCueSign         (mMeasureCueSign         );}
    void setMinStaticWeight        (quint32 value){ if( mMinStaticWeight         == value) return; mMinStaticWeight         = value; emit signalEventChangedMinStaticWeight        (mMinStaticWeight        );}
    void setMinDynamicWeight       (quint32 value){ if( mMinDynamicWeight        == value) return; mMinDynamicWeight        = value; emit signalEventChangedMinDynamicWeight       (mMinDynamicWeight       );}
    void setMode                   (quint16 value){ if( mMode                    == value) return; mMode                    = value; emit signalEventChangedMode                   (mMode                   );}
    void setDistanceBtwSensor      (quint16 value){ if( mDistanceBtwSensor       == value) return; mDistanceBtwSensor       = value; emit signalEventChangedDistanceBtwSensor      (mDistanceBtwSensor      );}
    void setDetectDetectTime       (quint32 value){ if( mDetectDetectTime        == value) return; mDetectDetectTime        = value; emit signalEventChangedDetectDetectTime       (mDetectDetectTime       );}
    void setRunDetectTime          (quint32 value){ if( mRunDetectTime           == value) return; mRunDetectTime           = value; emit signalEventChangedRunDetectTime          (mRunDetectTime          );}
    void setDistanceToWeightChecker(quint16 value){ if( mDistanceToWeightChecker == value) return; mDistanceToWeightChecker = value; emit signalEventChangedDistanceToWeightChecker(mDistanceToWeightChecker);}
    void setDistancePhotoToSensor  (quint16 value){ if( mDistancePhotoToSensor   == value) return; mDistancePhotoToSensor   = value; emit signalEventChangedDistancePhotoToSensor  (mDistancePhotoToSensor  );}
    void setSignalDelayTime        (quint32 value){ if( mSignalDelayTime         == value) return; mSignalDelayTime         = value; emit signalEventChangedSignalDelayTime        (mSignalDelayTime        );}
    void setStaticStandardWeight   (quint32 value){ if( mStaticStandardWeight    == value) return; mStaticStandardWeight    = value; emit signalEventChangedStaticStandardWeight   (mStaticStandardWeight   );}
    void setDynamicBaseWeight      (quint32 value){ if( mDynamicBaseWeight       == value) return; mDynamicBaseWeight       = value; emit signalEventChangedDynamicBaseWeight      (mDynamicBaseWeight      );}
    void setSensorCnt              (quint16 value){ if( mSensorCnt               == value) return; mSensorCnt               = value; emit signalEventChangedSensorCnt              (mSensorCnt              );}

signals:
    void signalEventChangedLampTime               (quint32 value);
    void signalEventChangedBuzzerTime             (quint32 value);
    void signalEventChangedSpeedConverter         (quint32 value);
    void signalEventChangedMotorDirection         (quint16 value);
    void signalEventChangedSensorLength           (quint16 value);
    void signalEventChangedDistanceToRejector     (quint16 value);
    void signalEventChangedMDPhotoIsOn            (bool    value);
    void signalEventChangedWCPhotoIsOn            (bool    value);
    void signalEventChangedRejectorReadyTime      (quint32 value);
    void signalEventChangedRejectorRunTimeRatio   (quint32 value);
    void signalEventChangedStaticFactor           (quint32 value);
    void signalEventChangedScaler                 (quint32 value);
    void signalEventChangedDisplayStability       (quint32 value);
    void signalEventChangedMeasureCueSign         (quint32 value);
    void signalEventChangedMinStaticWeight        (quint32 value);
    void signalEventChangedMinDynamicWeight       (quint32 value);
    void signalEventChangedMode                   (quint16 value);
    void signalEventChangedDistanceBtwSensor      (quint16 value);
    void signalEventChangedDetectDetectTime       (quint32 value);
    void signalEventChangedRunDetectTime          (quint32 value);
    void signalEventChangedDistanceToWeightChecker(quint16 value);
    void signalEventChangedDistancePhotoToSensor  (quint16 value);
    void signalEventChangedSignalDelayTime        (quint32 value);
    void signalEventChangedStaticStandardWeight   (quint32 value);
    void signalEventChangedDynamicBaseWeight      (quint32 value);
    void signalEventChangedSensorCnt              (quint16 value);

public:
    DspSettingModel& operator=(DspSettingModel * other)
    {
        setLampTime               (other->mLampTime               );
        setBuzzerTime             (other->mBuzzerTime             );
        setSpeedConverter         (other->mSpeedConverter         );
        setMotorDirection         (other->mMotorDirection         );
        setSensorLength           (other->mSensorLength           );
        setDistanceToRejector     (other->mDistanceToRejector     );
        setMDPhotoIsOn            (other->mMDPhotoIsOn            );
        setWCPhotoIsOn            (other->mWCPhotoIsOn            );
        setRejectorReadyTime      (other->mRejectorReadyTime      );
        setRejectorRunTimeRatio   (other->mRejectorRunTimeRatio   );
        setStaticFactor           (other->mStaticFactor           );
        setScaler                 (other->mScaler                 );
        setDisplayStability       (other->mDisplayStability       );
        setMeasureCueSign         (other->mMeasureCueSign         );
        setMinStaticWeight        (other->mMinStaticWeight        );
        setMinDynamicWeight       (other->mMinDynamicWeight       );
        setMode                   (other->mMode                   );
        setDistanceBtwSensor      (other->mDistanceBtwSensor      );
        setDetectDetectTime       (other->mDetectDetectTime       );
        setRunDetectTime          (other->mRunDetectTime          );
        setDistanceToWeightChecker(other->mDistanceToWeightChecker);
        setDistancePhotoToSensor  (other->mDistancePhotoToSensor  );
        setSignalDelayTime        (other->mSignalDelayTime        );
        setStaticStandardWeight   (other->mStaticStandardWeight   );
        setDynamicBaseWeight      (other->mDynamicBaseWeight      );
        setSensorCnt              (other->mSensorCnt              );

        return *this;
    }

    bool isEqual(DspSettingModel * value)
    {
        if(mLampTime                == value->mLampTime               &&
           mBuzzerTime              == value->mBuzzerTime             &&
           mSpeedConverter          == value->mSpeedConverter         &&
           mMotorDirection          == value->mMotorDirection         &&
           mSensorLength            == value->mSensorLength           &&
           mDistanceToRejector      == value->mDistanceToRejector     &&
           mMDPhotoIsOn             == value->mMDPhotoIsOn            &&
           mWCPhotoIsOn             == value->mWCPhotoIsOn            &&
           mRejectorRunTimeRatio    == value->mRejectorRunTimeRatio   &&
           mStaticFactor            == value->mStaticFactor           &&
           mScaler                  == value->mScaler                 &&
           mDisplayStability        == value->mDisplayStability       &&
           mMeasureCueSign          == value->mMeasureCueSign         &&
           mMinStaticWeight         == value->mMinStaticWeight        &&
           mMinDynamicWeight        == value->mMinDynamicWeight       &&
           mMode                    == value->mMode                   &&
           mDistanceBtwSensor       == value->mDistanceBtwSensor      &&
           mDetectDetectTime        == value->mDetectDetectTime       &&
           mRunDetectTime           == value->mRunDetectTime          &&
           mDistanceToWeightChecker == value->mDistanceToWeightChecker&&
           mDistancePhotoToSensor   == value->mDistancePhotoToSensor  &&
           mSignalDelayTime         == value->mSignalDelayTime        &&
           mStaticStandardWeight    == value->mStaticStandardWeight   &&
           mDynamicBaseWeight       == value->mDynamicBaseWeight      &&
           mSensorCnt               == value->mSensorCnt              )
            return true;

        return false;
    }

    explicit DspSettingModel(QObject *parent = nullptr) : QObject(parent){}
};

#endif // DEVICESETTINGMODEL_H
