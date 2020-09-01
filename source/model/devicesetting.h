#ifndef DEVICESETTING_H
#define DEVICESETTING_H

#include <QObject>
#include <QDebug>

#include "source/globaldef/EnumDefine.h"

class DeviceSetting //: public QObject
{
 //   Q_OBJECT
public:
    EnumDefine::Language                mLanguage                   ;
    QString                             mPassword                   ;
    bool                                mIsDayMode                  ;
    bool                                mIsDebugMode                ;
    quint32                             mLampTime                   ;
    quint32                             mBuzzerTime                 ;
    quint32                             mSpeedConverter             ;
    quint16                             mMotorDirection             ;
    quint16                             mSensorLength               ;
    quint16                             mDistanceToRejector         ;
    bool                                mMDPhotoIsOn                ;
    bool                                mWCPhotoIsOn                ;
    quint32                             mRejectorReadyTime          ;
    quint32                             mRejectorRunTimeRatio       ;
    quint32                             mStaticFactor               ;
    quint32                             mDynamicFactor              ;
    quint32                             mScaler                     ;
    //quint32                             mStandardWeightSet          ;
    quint32                             mDisplayStability           ;
    quint32                             mMeasureCueSign             ;
    quint32                             mMinStaticWeight            ;
    quint32                             mMinDynamicWeight           ;
    EnumDefine::TrendsGraphOptionH      mTrendsGraphOptionH         ;
    EnumDefine::TrendsGraphOptionFilter mTrendsGraphOptionFilter    ;
    EnumDefine::TrendsGraphOptionLastN  mTrendsGraphOptionLastN     ;
    quint32                             mTrendsGraphOptionLastNValue;
    EnumDefine::SensorMode              mMode                       ;
    quint16                             mDistanceBtwSensor          ;
    quint32                             mDetectDetectTime           ;
    quint32                             mRunDetectTime              ;
    quint16                             mDistanceToWeightChecker    ;
    quint16                             mDistancePhotoToSensor      ;
    quint32                             mSignalDelayTime            ;
    quint32                             mStaticStandardWeight       ;
    quint32                             mDynamicBaseWeight          ;
    quint16                             mSensorCnt                  ;
    quint16                             mSimpleSenstivity01         ;
    quint16                             mSimpleSenstivity02         ;
    quint16                             mSimpleSenstivity03         ;
    quint16                             mSimpleSenstivity04         ;
    quint16                             mSimpleSenstivity05         ;

    DeviceSetting(){}
//    explicit DeviceSetting(QObject *parent = nullptr): QObject(parent){}
    DeviceSetting(const DeviceSetting& copy):
                         mLanguage                   (copy.mLanguage                   ),
                         mPassword                   (copy.mPassword                   ),
                         mIsDayMode                  (copy.mIsDayMode                  ),
                         mIsDebugMode                (copy.mIsDebugMode                ),
                         mLampTime                   (copy.mLampTime                   ),
                         mBuzzerTime                 (copy.mBuzzerTime                 ),
                         mSpeedConverter             (copy.mSpeedConverter             ),
                         mMotorDirection             (copy.mMotorDirection             ),
                         mSensorLength               (copy.mSensorLength               ),
                         mDistanceToRejector         (copy.mDistanceToRejector         ),
                         mMDPhotoIsOn                (copy.mMDPhotoIsOn                ),
                         mWCPhotoIsOn                (copy.mWCPhotoIsOn                ),
                         mRejectorReadyTime          (copy.mRejectorReadyTime          ),
                         mRejectorRunTimeRatio       (copy.mRejectorRunTimeRatio       ),
                         mStaticFactor               (copy.mStaticFactor               ),
                         mDynamicFactor              (copy.mDynamicFactor              ),
                         mScaler                     (copy.mScaler                     ),
//                         mStandardWeightSet          (copy.mStandardWeightSet          ),
                         mDisplayStability           (copy.mDisplayStability           ),
                         mMeasureCueSign             (copy.mMeasureCueSign             ),
                         mMinStaticWeight            (copy.mMinStaticWeight            ),
                         mMinDynamicWeight           (copy.mMinDynamicWeight           ),
                         mTrendsGraphOptionH         (copy.mTrendsGraphOptionH         ),
                         mTrendsGraphOptionFilter    (copy.mTrendsGraphOptionFilter    ),
                         mTrendsGraphOptionLastN     (copy.mTrendsGraphOptionLastN     ),
                         mTrendsGraphOptionLastNValue(copy.mTrendsGraphOptionLastNValue),
                         mMode                       (copy.mMode                       ),
                         mDistanceBtwSensor          (copy.mDistanceBtwSensor          ),
                         mDetectDetectTime           (copy.mDetectDetectTime           ),
                         mRunDetectTime              (copy.mRunDetectTime              ),
                         mDistanceToWeightChecker    (copy.mDistanceToWeightChecker    ),
                         mDistancePhotoToSensor      (copy.mDistancePhotoToSensor      ),
                         mSignalDelayTime            (copy.mSignalDelayTime            ),
                         mStaticStandardWeight       (copy.mStaticStandardWeight       ),
                         mDynamicBaseWeight          (copy.mDynamicBaseWeight          ),
                         mSensorCnt                  (copy.mSensorCnt                  ),
                         mSimpleSenstivity01         (copy.mSimpleSenstivity01         ),
                         mSimpleSenstivity02         (copy.mSimpleSenstivity02         ),
                         mSimpleSenstivity03         (copy.mSimpleSenstivity03         ),
                         mSimpleSenstivity04         (copy.mSimpleSenstivity04         ),
                         mSimpleSenstivity05         (copy.mSimpleSenstivity05         ){}

    ~DeviceSetting(){}

    DeviceSetting& operator=(const DeviceSetting& other)
    {
        mLanguage                    = other.mLanguage                   ;
        mPassword                    = other.mPassword                   ;
        mIsDayMode                   = other.mIsDayMode                  ;
        mLampTime                    = other.mLampTime                   ;
        mBuzzerTime                  = other.mBuzzerTime                 ;
        mSpeedConverter              = other.mSpeedConverter             ;
        mMotorDirection              = other.mMotorDirection             ;
        mIsDebugMode                 = other.mIsDebugMode                ;
        mSensorLength                = other.mSensorLength               ;
        mDistanceToRejector          = other.mDistanceToRejector         ;
        mMDPhotoIsOn                 = other.mMDPhotoIsOn                ;
        mWCPhotoIsOn                 = other.mWCPhotoIsOn                ;
        mRejectorReadyTime           = other.mRejectorReadyTime          ;
        mRejectorRunTimeRatio        = other.mRejectorRunTimeRatio       ;
        mStaticFactor                = other.mStaticFactor               ;
        mDynamicFactor               = other.mDynamicFactor              ;
        mScaler                      = other.mScaler                     ;
        mDisplayStability            = other.mDisplayStability           ;
        mMeasureCueSign              = other.mMeasureCueSign             ;
        mMinStaticWeight             = other.mMinStaticWeight            ;
        mMinDynamicWeight            = other.mMinDynamicWeight           ;
        mTrendsGraphOptionH          = other.mTrendsGraphOptionH         ;
        mTrendsGraphOptionFilter     = other.mTrendsGraphOptionFilter    ;
        mTrendsGraphOptionLastN      = other.mTrendsGraphOptionLastN     ;
        mTrendsGraphOptionLastNValue = other.mTrendsGraphOptionLastNValue;
        mMode                        = other.mMode                       ;
        mDistanceBtwSensor           = other.mDistanceBtwSensor          ;
        mDetectDetectTime            = other.mDetectDetectTime           ;
        mRunDetectTime               = other.mRunDetectTime              ;
        mDistanceToWeightChecker     = other.mDistanceToWeightChecker    ;
        mDistancePhotoToSensor       = other.mDistancePhotoToSensor      ;
        mSignalDelayTime             = other.mSignalDelayTime            ;
        mStaticStandardWeight        = other.mStaticStandardWeight       ;
        mDynamicBaseWeight           = other.mDynamicBaseWeight          ;
        mSensorCnt                   = other.mSensorCnt                  ;
        mSimpleSenstivity01          = other.mSimpleSenstivity01         ;
        mSimpleSenstivity02          = other.mSimpleSenstivity02         ;
        mSimpleSenstivity03          = other.mSimpleSenstivity03         ;
        mSimpleSenstivity04          = other.mSimpleSenstivity04         ;
        mSimpleSenstivity05          = other.mSimpleSenstivity05         ;

        return *this;
    }

    bool remoteSettingCompare(DeviceSetting * other)
    {
        if(mLampTime                    != other->mLampTime
         ||mBuzzerTime                  != other->mBuzzerTime
         ||mSpeedConverter              != other->mSpeedConverter
         ||mMotorDirection              != other->mMotorDirection
         ||mSensorLength                != other->mSensorLength
         ||mDistanceToRejector          != other->mDistanceToRejector
         ||mMDPhotoIsOn                 != other->mMDPhotoIsOn
         ||mWCPhotoIsOn                 != other->mWCPhotoIsOn
         ||mRejectorRunTimeRatio        != other->mRejectorRunTimeRatio
         ||mStaticFactor                != other->mStaticFactor
         //||mDynamicFactor               != other->mDynamicFactor
         ||mScaler                      != other->mScaler
         ||mDisplayStability            != other->mDisplayStability
         ||mMeasureCueSign              != other->mMeasureCueSign
         ||mMinStaticWeight             != other->mMinStaticWeight
         ||mMinDynamicWeight            != other->mMinDynamicWeight
         ||mMode                        != other->mMode
         ||mDistanceBtwSensor           != other->mDistanceBtwSensor
         ||mDetectDetectTime            != other->mDetectDetectTime
         ||mRunDetectTime               != other->mRunDetectTime
         ||mDistanceToWeightChecker     != other->mDistanceToWeightChecker
         ||mDistancePhotoToSensor       != other->mDistancePhotoToSensor
         ||mStaticStandardWeight        != other->mStaticStandardWeight
         ||mDynamicBaseWeight           != other->mDynamicBaseWeight
         ||mSignalDelayTime             != other->mSignalDelayTime
         ||mSensorCnt                   != other->mSensorCnt)
        {
            qDebug() << "Device setting mismatch";
            qDebug() << "mLampTime               "   << mLampTime                  << ": "<<other->mLampTime                 ;
            qDebug() << "mBuzzerTime             "   << mBuzzerTime                << ": "<<other->mBuzzerTime               ;
            qDebug() << "mSpeedConverter         "   << mSpeedConverter            << ": "<<other->mSpeedConverter           ;
            qDebug() << "mMotorDirection         "   << mMotorDirection            << ": "<<other->mMotorDirection           ;
            //qDebug() << "mIsDebugMode            "   << mIsDebugMode               << ": "<<other->mIsDebugMode              ;
            qDebug() << "mSensorLength           "   << mSensorLength              << ": "<<other->mSensorLength             ;
            qDebug() << "mDistanceToRejector     "   << mDistanceToRejector        << ": "<<other->mDistanceToRejector       ;
            qDebug() << "mMDPhotoIsOn            "   << mMDPhotoIsOn               << ": "<<other->mMDPhotoIsOn              ;
            qDebug() << "mWCPhotoIsOn            "   << mWCPhotoIsOn               << ": "<<other->mWCPhotoIsOn              ;
            qDebug() << "mRejectorRunTimeRatio   "   << mRejectorRunTimeRatio      << ": "<<other->mRejectorRunTimeRatio     ;
            qDebug() << "mStaticFactor           "   << mStaticFactor              << ": "<<other->mStaticFactor             ;
            //qDebug() << "mDynamicFactor          "   << mDynamicFactor             << ": "<<other->mDynamicFactor            ;
            qDebug() << "mScaler                 "   << mScaler                    << ": "<<other->mScaler                   ;
            qDebug() << "mDisplayStability       "   << mDisplayStability          << ": "<<other->mDisplayStability         ;
            qDebug() << "mMeasureCueSign         "   << mMeasureCueSign            << ": "<<other->mMeasureCueSign           ;
            qDebug() << "mMinStaticWeight        "   << mMinStaticWeight           << ": "<<other->mMinStaticWeight          ;
            qDebug() << "mMinDynamicWeight       "   << mMinDynamicWeight          << ": "<<other->mMinDynamicWeight         ;
            qDebug() << "mMode                   "   << mMode                      << ": "<<other->mMode                     ;
            qDebug() << "mDistanceBtwSensor      "   << mDistanceBtwSensor         << ": "<<other->mDistanceBtwSensor        ;
            qDebug() << "mDetectDetectTime       "   << mDetectDetectTime          << ": "<<other->mDetectDetectTime         ;
            qDebug() << "mRunDetectTime          "   << mRunDetectTime             << ": "<<other->mRunDetectTime            ;
            qDebug() << "mDistanceToWeightChecker"   << mDistanceToWeightChecker   << ": "<<other->mDistanceToWeightChecker  ;
            qDebug() << "mDistancePhotoToSensor  "   << mDistancePhotoToSensor     << ": "<<other->mDistancePhotoToSensor    ;
            qDebug() << "mStaticStandardWeight   "   << mStaticStandardWeight      << ": "<<other->mStaticStandardWeight     ;
            qDebug() << "mDynamicBaseWeight      "   << mDynamicBaseWeight         << ": "<<other->mDynamicBaseWeight        ;
            qDebug() << "mSignalDelayTime        "   << mSignalDelayTime           << ": "<<other->mSignalDelayTime          ;
            qDebug() << "mSensorCnt              "   << mSensorCnt                 << ": "<<other->mSensorCnt                ;

            return false;
        }
        return true;
    }
};

Q_DECLARE_METATYPE(DeviceSetting);
#endif // DEVICESETTING_H
