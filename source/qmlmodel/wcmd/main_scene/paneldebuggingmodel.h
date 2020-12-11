#ifndef PANELDEBUGGINGMODEL_H
#define PANELDEBUGGINGMODEL_H

#include <QObject>
#include "source/service/coreservice.h"

class PanelDebuggingModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint16 mSeq                         READ getSeq                                NOTIFY signalEventChangedSeq                               );
    Q_PROPERTY(quint16 mLength                      READ getLength                             NOTIFY signalEventChangedLength                            );
    Q_PROPERTY(quint16 mSpeed                       READ getSpeed                              NOTIFY signalEventChangedSpeed                             );
    Q_PROPERTY(quint32 mMotorAccelerationTime       READ getMotorAccelerationTime              NOTIFY signalEventChangedMotorAccelerationTime             );
    Q_PROPERTY(quint32 mUnderWeight                 READ getUnderWeight                        NOTIFY signalEventChangedUnderWeight                       );
    Q_PROPERTY(quint32 mUnderWarningWeight          READ getUnderWarningWeight                 NOTIFY signalEventChangedUnderWarningWeight                );
    Q_PROPERTY(quint32 mNormalWeight                READ getNormalWeight                       NOTIFY signalEventChangedNormalWeight                      );
    Q_PROPERTY(quint32 mOverWarningWeight           READ getOverWarningWeight                  NOTIFY signalEventChangedOverWarningWeight                 );
    Q_PROPERTY(quint32 mOverWeight                  READ getOverWeight                         NOTIFY signalEventChangedOverWeight                        );
    Q_PROPERTY(quint32 mTareWeight                  READ getTareWeight                         NOTIFY signalEventChangedTareWeight                        );
    Q_PROPERTY(quint16 mWCNGMotion                  READ getWCNGMotion                         NOTIFY signalEventChangedWCNGMotion                        );
    Q_PROPERTY(quint16 mWCEnableEtcError            READ getWCEnableEtcError                   NOTIFY signalEventChangedWCEnableEtcError                  );
    Q_PROPERTY(quint16 mMDSenstivity                READ getMDSenstivity                       NOTIFY signalEventChangedMDSenstivity                      );
    Q_PROPERTY(quint16 mMDNGMotion                  READ getMDNGMotion                         NOTIFY signalEventChangedMDNGMotion                        );
    Q_PROPERTY(quint32 mLampTime                    READ getLampTime                           NOTIFY signalEventChangedLampTime                          );
    Q_PROPERTY(quint32 mBuzzerTime                  READ getBuzzerTime                         NOTIFY signalEventChangedBuzzerTime                        );
    Q_PROPERTY(quint32 mSpeedConverter              READ getSpeedConverter                     NOTIFY signalEventChangedSpeedConverter                    );
    Q_PROPERTY(quint16 mMotorDirection              READ getMotorDirection                     NOTIFY signalEventChangedMotorDirection                    );
    Q_PROPERTY(quint16 mMotorType                   READ getMotorType                          NOTIFY signalEventChangedMotorType                         );
    Q_PROPERTY(quint16 mMotorMDRatio                READ getMotorMDRatio                       NOTIFY signalEventChangedMotorMDRatio                      );
    Q_PROPERTY(quint16 mMotorWCRatio                READ getMotorWCRatio                       NOTIFY signalEventChangedMotorWCRatio                      );
    Q_PROPERTY(quint16 mMotorRJRatio                READ getMotorRJRatio                       NOTIFY signalEventChangedMotorRJRatio                      );
    Q_PROPERTY(quint16 mMachineMode                 READ getMachineMode                        NOTIFY signalEventChangedMachineMode                       );
    Q_PROPERTY(quint16 mSensorLength                READ getSensorLength                       NOTIFY signalEventChangedSensorLength                      );
    Q_PROPERTY(quint16 mDistanceToRejector          READ getDistanceToRejector                 NOTIFY signalEventChangedDistanceToRejector                );
    Q_PROPERTY(bool    mMDPhotoIsOn                 READ getMDPhotoIsOn                        NOTIFY signalEventChangedMDPhotoIsOn                       );
    Q_PROPERTY(bool    mWCPhotoIsOn                 READ getWCPhotoIsOn                        NOTIFY signalEventChangedWCPhotoIsOn                       );
    Q_PROPERTY(quint32 mRejectorRunTimeRatio        READ getRejectorRunTimeRatio               NOTIFY signalEventChangedRejectorRunTimeRatio              );
    Q_PROPERTY(quint32 mStaticFactor                READ getStaticFactor                       NOTIFY signalEventChangedStaticFactor                      );
    Q_PROPERTY(quint32 mDynamicFactor               READ getDynamicFactor                      NOTIFY signalEventChangedDynamicFactor                     );
    Q_PROPERTY(quint32 mScaler                      READ getScaler                             NOTIFY signalEventChangedScaler                            );
    Q_PROPERTY(quint32 mDisplayStability            READ getDisplayStability                   NOTIFY signalEventChangedDisplayStability                  );
    Q_PROPERTY(quint32 mMeasureCueSign              READ getMeasureCueSign                     NOTIFY signalEventChangedMeasureCueSign                    );
    Q_PROPERTY(quint32 mMinStaticWeight             READ getMinStaticWeight                    NOTIFY signalEventChangedMinStaticWeight                   );
    Q_PROPERTY(quint32 mMinDynamicWeight            READ getMinDynamicWeight                   NOTIFY signalEventChangedMinDynamicWeight                  );
    Q_PROPERTY(quint16 mMode                        READ getMode                               NOTIFY signalEventChangedMode                              );
    Q_PROPERTY(quint16 mDistanceBtwSensor           READ getDistanceBtwSensor                  NOTIFY signalEventChangedDistanceBtwSensor                 );
    Q_PROPERTY(quint32 mDetectDetectTime            READ getDetectDetectTime                   NOTIFY signalEventChangedDetectDetectTime                  );
    Q_PROPERTY(quint32 mRunDetectTime               READ getRunDetectTime                      NOTIFY signalEventChangedRunDetectTime                     );
    Q_PROPERTY(quint16 mDistanceToWeightChecker     READ getDistanceToWeightChecker            NOTIFY signalEventChangedDistanceToWeightChecker           );
    Q_PROPERTY(quint16 mDistancePhotoToSensor       READ getDistancePhotoToSensor              NOTIFY signalEventChangedDistancePhotoToSensor             );
    Q_PROPERTY(quint32 mSignalDelayTime             READ getSignalDelayTime                    NOTIFY signalEventChangedSignalDelayTime                   );
    Q_PROPERTY(quint32 mStaticStandardWeight        READ getStaticStandardWeight               NOTIFY signalEventChangedStaticStandardWeight              );
    Q_PROPERTY(quint32 mDynamicBaseWeight           READ getDynamicBaseWeight                  NOTIFY signalEventChangedDynamicBaseWeight                 );
    Q_PROPERTY(quint16 mSensorCnt                   READ getSensorCnt                          NOTIFY signalEventChangedSensorCnt                         );
    Q_PROPERTY(quint32 mRejectorOpenTime            READ getRejectorOpenTime                   NOTIFY signalEventChangedRejectorOpenTime                  );
    Q_PROPERTY(bool    mDiffSeq                     READ getDiffSeq                            NOTIFY signalEventChangedDiffSeq                           );
    Q_PROPERTY(bool    mDiffLength                  READ getDiffLength                         NOTIFY signalEventChangedDiffLength                        );
    Q_PROPERTY(bool    mDiffSpeed                   READ getDiffSpeed                          NOTIFY signalEventChangedDiffSpeed                         );
    Q_PROPERTY(quint32 mDiffMotorAccelerationTime   READ getDiffMotorAccelerationTime          NOTIFY signalEventChangedDiffMotorAccelerationTime         );
    Q_PROPERTY(bool    mDiffUnderWeight             READ getDiffUnderWeight                    NOTIFY signalEventChangedDiffUnderWeight                   );
    Q_PROPERTY(bool    mDiffUnderWarningWeight      READ getDiffUnderWarningWeight             NOTIFY signalEventChangedDiffUnderWarningWeight            );
    Q_PROPERTY(bool    mDiffNormalWeight            READ getDiffNormalWeight                   NOTIFY signalEventChangedDiffNormalWeight                  );
    Q_PROPERTY(bool    mDiffOverWarningWeight       READ getDiffOverWarningWeight              NOTIFY signalEventChangedDiffOverWarningWeight             );
    Q_PROPERTY(bool    mDiffOverWeight              READ getDiffOverWeight                     NOTIFY signalEventChangedDiffOverWeight                    );
    Q_PROPERTY(bool    mDiffTareWeight              READ getDiffTareWeight                     NOTIFY signalEventChangedDiffTareWeight                    );
    Q_PROPERTY(bool    mDiffWCNGMotion              READ getDiffWCNGMotion                     NOTIFY signalEventChangedDiffWCNGMotion                    );
    Q_PROPERTY(bool    mDiffWCEnableEtcError        READ getDiffWCEnableEtcError               NOTIFY signalEventChangedDiffWCEnableEtcError              );
    Q_PROPERTY(bool    mDiffMDSenstivity            READ getDiffMDSenstivity                   NOTIFY signalEventChangedDiffMDSenstivity                  );
    Q_PROPERTY(bool    mDiffMDNGMotion              READ getDiffMDNGMotion                     NOTIFY signalEventChangedDiffMDNGMotion                    );
    Q_PROPERTY(bool    mDiffLampTime                READ getDiffLampTime                       NOTIFY signalEventChangedDiffLampTime                      );
    Q_PROPERTY(bool    mDiffBuzzerTime              READ getDiffBuzzerTime                     NOTIFY signalEventChangedDiffBuzzerTime                    );
    Q_PROPERTY(bool    mDiffSpeedConverter          READ getDiffSpeedConverter                 NOTIFY signalEventChangedDiffSpeedConverter                );
    Q_PROPERTY(bool    mDiffMotorDirection          READ getDiffMotorDirection                 NOTIFY signalEventChangedDiffMotorDirection                );
    Q_PROPERTY(bool    mDiffMotorType               READ getDiffMotorType                      NOTIFY signalEventChangedDiffMotorType                     );
    Q_PROPERTY(bool    mDiffMachineMode             READ getDiffMachineMode                    NOTIFY signalEventChangedDiffMachineMode                   );
    Q_PROPERTY(bool    mDiffMotorMDRatio            READ getDiffMotorMDRatio                   NOTIFY signalEventChangedDiffMotorMDRatio                  );
    Q_PROPERTY(bool    mDiffMotorWCRatio            READ getDiffMotorWCRatio                   NOTIFY signalEventChangedDiffMotorWCRatio                  );
    Q_PROPERTY(bool    mDiffMotorRJRatio            READ getDiffMotorRJRatio                   NOTIFY signalEventChangedDiffMotorRJRatio                  );
    Q_PROPERTY(bool    mDiffMDPhotoIsOn             READ getDiffMDPhotoIsOn                    NOTIFY signalEventChangedDiffMDPhotoIsOn                   );
    Q_PROPERTY(bool    mDiffWCPhotoIsOn             READ getDiffWCPhotoIsOn                    NOTIFY signalEventChangedDiffWCPhotoIsOn                   );
    Q_PROPERTY(bool    mDiffSensorLength            READ getDiffSensorLength                   NOTIFY signalEventChangedDiffSensorLength                  );
    Q_PROPERTY(bool    mDiffDistanceToRejector      READ getDiffDistanceToRejector             NOTIFY signalEventChangedDiffDistanceToRejector            );
    Q_PROPERTY(bool    mDiffRejectorRunTimeRatio    READ getDiffRejectorRunTimeRatio           NOTIFY signalEventChangedDiffRejectorRunTimeRatio          );
    Q_PROPERTY(bool    mDiffStaticFactor            READ getDiffStaticFactor                   NOTIFY signalEventChangedDiffStaticFactor                  );
    Q_PROPERTY(bool    mDiffDynamicFactor           READ getDiffDynamicFactor                  NOTIFY signalEventChangedDiffDynamicFactor                 );
    Q_PROPERTY(bool    mDiffScaler                  READ getDiffScaler                         NOTIFY signalEventChangedDiffScaler                        );
    Q_PROPERTY(bool    mDiffDisplayStability        READ getDiffDisplayStability               NOTIFY signalEventChangedDiffDisplayStability              );
    Q_PROPERTY(bool    mDiffMeasureCueSign          READ getDiffMeasureCueSign                 NOTIFY signalEventChangedDiffMeasureCueSign                );
    Q_PROPERTY(bool    mDiffMinStaticWeight         READ getDiffMinStaticWeight                NOTIFY signalEventChangedDiffMinStaticWeight               );
    Q_PROPERTY(bool    mDiffMinDynamicWeight        READ getDiffMinDynamicWeight               NOTIFY signalEventChangedDiffMinDynamicWeight              );
    Q_PROPERTY(bool    mDiffMode                    READ getDiffMode                           NOTIFY signalEventChangedDiffMode                          );
    Q_PROPERTY(bool    mDiffDistanceBtwSensor       READ getDiffDistanceBtwSensor              NOTIFY signalEventChangedDiffDistanceBtwSensor             );
    Q_PROPERTY(bool    mDiffDetectDetectTime        READ getDiffDetectDetectTime               NOTIFY signalEventChangedDiffDetectDetectTime              );
    Q_PROPERTY(bool    mDiffRunDetectTime           READ getDiffRunDetectTime                  NOTIFY signalEventChangedDiffRunDetectTime                 );
    Q_PROPERTY(bool    mDiffDistanceToWeightChecker READ getDiffDistanceToWeightChecker        NOTIFY signalEventChangedDiffDistanceToWeightChecker       );
    Q_PROPERTY(bool    mDiffDistancePhotoToSensor   READ getDiffDistancePhotoToSensor          NOTIFY signalEventChangedDiffDistancePhotoToSensor         );
    Q_PROPERTY(bool    mDiffSignalDelayTime         READ getDiffSignalDelayTime                NOTIFY signalEventChangedDiffSignalDelayTime               );
    Q_PROPERTY(bool    mDiffStaticStandardWeight    READ getDiffStaticStandardWeight           NOTIFY signalEventChangedDiffStaticStandardWeight          );
    Q_PROPERTY(bool    mDiffDynamicBaseWeight       READ getDiffDynamicBaseWeight              NOTIFY signalEventChangedDiffDynamicBaseWeight             );
    Q_PROPERTY(bool    mDiffSensorCnt               READ getDiffSensorCnt                      NOTIFY signalEventChangedDiffSensorCnt                     );
    Q_PROPERTY(bool    mDiffRejectorOpenTime        READ getDiffRejectorOpenTime               NOTIFY signalEventChangedDiffRejectorOpenTime              );

public:
    quint64 mDspSeq                     = 0;
    quint16 mSeq                        ;
    quint16 mLength                     ;
    quint16 mSpeed                      ;
    quint32 mMotorAccelerationTime      ;
    quint32 mUnderWeight                ;
    quint32 mUnderWarningWeight         ;
    quint32 mNormalWeight               ;
    quint32 mOverWarningWeight          ;
    quint32 mOverWeight                 ;
    quint32 mTareWeight                 ;
    quint16 mWCNGMotion                 ;
    quint16 mWCEnableEtcError           ;
    quint16 mMDSenstivity               ;
    quint16 mMDNGMotion                 ;
    quint32 mLampTime                   ;
    quint32 mBuzzerTime                 ;
    quint32 mSpeedConverter             ;
    quint16 mMotorDirection             ;
    quint16 mMotorType                  ;
    quint32 mMachineMode                ;
    quint16 mMotorMDRatio               ;
    quint16 mMotorWCRatio               ;
    quint16 mMotorRJRatio               ;
    quint16 mSensorLength               ;
    quint16 mDistanceToRejector         ;
    bool    mMDPhotoIsOn                ;
    bool    mWCPhotoIsOn                ;
    quint32 mRejectorRunTimeRatio       ;
    quint32 mStaticFactor               ;
    quint32 mDynamicFactor              ;
    quint32 mScaler                     ;
    quint32 mDisplayStability           ;
    quint32 mMeasureCueSign             ;
    quint32 mMinStaticWeight            ;
    quint32 mMinDynamicWeight           ;
    quint16 mMode                       ;
    quint16 mDistanceBtwSensor          ;
    quint32 mDetectDetectTime           ;
    quint32 mRunDetectTime              ;
    quint16 mDistanceToWeightChecker    ;
    quint16 mDistancePhotoToSensor      ;
    quint32 mSignalDelayTime            ;
    quint32 mStaticStandardWeight       ;
    quint32 mDynamicBaseWeight          ;
    quint16 mSensorCnt                  ;
    quint32 mRejectorOpenTime           ;

    bool    mDiffSeq                    ;
    bool    mDiffLength                 ;
    bool    mDiffSpeed                  ;
    bool    mDiffMotorAccelerationTime  ;
    bool    mDiffUnderWeight            ;
    bool    mDiffUnderWarningWeight     ;
    bool    mDiffNormalWeight           ;
    bool    mDiffOverWarningWeight      ;
    bool    mDiffOverWeight             ;
    bool    mDiffTareWeight             ;
    bool    mDiffWCNGMotion             ;
    bool    mDiffWCEnableEtcError       ;
    bool    mDiffMDSenstivity           ;
    bool    mDiffMDNGMotion             ;
    bool    mDiffLampTime               ;
    bool    mDiffBuzzerTime             ;
    bool    mDiffSpeedConverter         ;
    bool    mDiffMotorDirection         ;
    bool    mDiffMotorType              ;
    bool    mDiffMachineMode            ;
    bool    mDiffMotorMDRatio           ;
    bool    mDiffMotorWCRatio           ;
    bool    mDiffMotorRJRatio           ;
    bool    mDiffSensorLength           ;
    bool    mDiffDistanceToRejector     ;
    bool    mDiffMDPhotoIsOn            ;
    bool    mDiffWCPhotoIsOn            ;
    bool    mDiffRejectorRunTimeRatio   ;
    bool    mDiffStaticFactor           ;
    bool    mDiffDynamicFactor          ;
    bool    mDiffScaler                 ;
    bool    mDiffDisplayStability       ;
    bool    mDiffMeasureCueSign         ;
    bool    mDiffMinStaticWeight        ;
    bool    mDiffMinDynamicWeight       ;
    bool    mDiffMode                   ;
    bool    mDiffDistanceBtwSensor      ;
    bool    mDiffDetectDetectTime       ;
    bool    mDiffRunDetectTime          ;
    bool    mDiffDistanceToWeightChecker;
    bool    mDiffDistancePhotoToSensor  ;
    bool    mDiffSignalDelayTime        ;
    bool    mDiffStaticStandardWeight   ;
    bool    mDiffDynamicBaseWeight      ;
    bool    mDiffSensorCnt              ;
    bool    mDiffRejectorOpenTime       ;

    quint16 getSeq                        (){ return mSeq                        ;}
    quint16 getLength                     (){ return mLength                     ;}
    quint16 getSpeed                      (){ return mSpeed                      ;}
    quint32 getMotorAccelerationTime      (){ return mMotorAccelerationTime      ;}
    quint32 getUnderWeight                (){ return mUnderWeight                ;}
    quint32 getUnderWarningWeight         (){ return mUnderWarningWeight         ;}
    quint32 getNormalWeight               (){ return mNormalWeight               ;}
    quint32 getOverWarningWeight          (){ return mOverWarningWeight          ;}
    quint32 getOverWeight                 (){ return mOverWeight                 ;}
    quint32 getTareWeight                 (){ return mTareWeight                 ;}
    quint16 getWCNGMotion                 (){ return mWCNGMotion                 ;}
    quint16 getWCEnableEtcError           (){ return mWCEnableEtcError           ;}
    quint16 getMDSenstivity               (){ return mMDSenstivity               ;}
    quint16 getMDNGMotion                 (){ return mMDNGMotion                 ;}
    quint32 getLampTime                   (){ return mLampTime                   ;}
    quint32 getBuzzerTime                 (){ return mBuzzerTime                 ;}
    quint32 getSpeedConverter             (){ return mSpeedConverter             ;}
    quint16 getMotorDirection             (){ return mMotorDirection             ;}
    quint16 getMotorType                  (){ return mMotorType                  ;}
    quint16 getMachineMode                (){ return mMachineMode                ;}
    quint16 getMotorMDRatio               (){ return mMotorMDRatio               ;}
    quint16 getMotorWCRatio               (){ return mMotorWCRatio               ;}
    quint16 getMotorRJRatio               (){ return mMotorRJRatio               ;}
    quint16 getSensorLength               (){ return mSensorLength               ;}
    quint16 getDistanceToRejector         (){ return mDistanceToRejector         ;}
    bool    getMDPhotoIsOn                (){ return mMDPhotoIsOn                ;}
    bool    getWCPhotoIsOn                (){ return mWCPhotoIsOn                ;}
    quint32 getRejectorRunTimeRatio       (){ return mRejectorRunTimeRatio       ;}
    quint32 getStaticFactor               (){ return mStaticFactor               ;}
    quint32 getDynamicFactor              (){ return mDynamicFactor              ;}
    quint32 getScaler                     (){ return mScaler                     ;}
    quint32 getDisplayStability           (){ return mDisplayStability           ;}
    quint32 getMeasureCueSign             (){ return mMeasureCueSign             ;}
    quint32 getMinStaticWeight            (){ return mMinStaticWeight            ;}
    quint32 getMinDynamicWeight           (){ return mMinDynamicWeight           ;}
    quint16 getMode                       (){ return mMode                       ;}
    quint16 getDistanceBtwSensor          (){ return mDistanceBtwSensor          ;}
    quint32 getDetectDetectTime           (){ return mDetectDetectTime           ;}
    quint32 getRunDetectTime              (){ return mRunDetectTime              ;}
    quint16 getDistanceToWeightChecker    (){ return mDistanceToWeightChecker    ;}
    quint16 getDistancePhotoToSensor      (){ return mDistancePhotoToSensor      ;}
    quint32 getSignalDelayTime            (){ return mSignalDelayTime            ;}
    quint32 getStaticStandardWeight       (){ return mStaticStandardWeight       ;}
    quint32 getDynamicBaseWeight          (){ return mDynamicBaseWeight          ;}
    quint16 getSensorCnt                  (){ return mSensorCnt                  ;}
    quint32 getRejectorOpenTime           (){ return mRejectorOpenTime           ;}
    bool    getDiffSeq                    (){ return mDiffSeq                    ;}
    bool    getDiffLength                 (){ return mDiffLength                 ;}
    bool    getDiffSpeed                  (){ return mDiffSpeed                  ;}
    bool    getDiffMotorAccelerationTime  (){ return mDiffMotorAccelerationTime  ;}
    bool    getDiffUnderWeight            (){ return mDiffUnderWeight            ;}
    bool    getDiffUnderWarningWeight     (){ return mDiffUnderWarningWeight     ;}
    bool    getDiffNormalWeight           (){ return mDiffNormalWeight           ;}
    bool    getDiffOverWarningWeight      (){ return mDiffOverWarningWeight      ;}
    bool    getDiffOverWeight             (){ return mDiffOverWeight             ;}
    bool    getDiffTareWeight             (){ return mDiffTareWeight             ;}
    bool    getDiffWCNGMotion             (){ return mDiffWCNGMotion             ;}
    bool    getDiffWCEnableEtcError       (){ return mDiffWCEnableEtcError       ;}
    bool    getDiffMDSenstivity           (){ return mDiffMDSenstivity           ;}
    bool    getDiffMDNGMotion             (){ return mDiffMDNGMotion             ;}
    bool    getDiffLampTime               (){ return mDiffLampTime               ;}
    bool    getDiffBuzzerTime             (){ return mDiffBuzzerTime             ;}
    bool    getDiffSpeedConverter         (){ return mDiffSpeedConverter         ;}
    bool    getDiffMotorDirection         (){ return mDiffMotorDirection         ;}
    bool    getDiffMotorType              (){ return mDiffMotorType              ;}
    bool    getDiffMachineMode            (){ return mDiffMachineMode            ;}
    bool    getDiffMotorMDRatio           (){ return mDiffMotorMDRatio           ;}
    bool    getDiffMotorWCRatio           (){ return mDiffMotorWCRatio           ;}
    bool    getDiffMotorRJRatio           (){ return mDiffMotorRJRatio           ;}
    bool    getDiffSensorLength           (){ return mDiffSensorLength           ;}
    bool    getDiffDistanceToRejector     (){ return mDiffDistanceToRejector     ;}
    bool    getDiffMDPhotoIsOn            (){ return mDiffMDPhotoIsOn            ;}
    bool    getDiffWCPhotoIsOn            (){ return mDiffWCPhotoIsOn            ;}
    bool    getDiffRejectorRunTimeRatio   (){ return mDiffRejectorRunTimeRatio   ;}
    bool    getDiffStaticFactor           (){ return mDiffStaticFactor           ;}
    bool    getDiffDynamicFactor          (){ return false/*mDiffDynamicFactor*/ ;}
    bool    getDiffScaler                 (){ return mDiffScaler                 ;}
    bool    getDiffDisplayStability       (){ return mDiffDisplayStability       ;}
    bool    getDiffMeasureCueSign         (){ return mDiffMeasureCueSign         ;}
    bool    getDiffMinStaticWeight        (){ return mDiffMinStaticWeight        ;}
    bool    getDiffMinDynamicWeight       (){ return mDiffMinDynamicWeight       ;}
    bool    getDiffMode                   (){ return mDiffMode                   ;}
    bool    getDiffDistanceBtwSensor      (){ return mDiffDistanceBtwSensor      ;}
    bool    getDiffDetectDetectTime       (){ return mDiffDetectDetectTime       ;}
    bool    getDiffRunDetectTime          (){ return mDiffRunDetectTime          ;}
    bool    getDiffDistanceToWeightChecker(){ return mDiffDistanceToWeightChecker;}
    bool    getDiffDistancePhotoToSensor  (){ return mDiffDistancePhotoToSensor  ;}
    bool    getDiffSignalDelayTime        (){ return mDiffSignalDelayTime        ;}
    bool    getDiffStaticStandardWeight   (){ return mDiffStaticStandardWeight   ;}
    bool    getDiffDynamicBaseWeight      (){ return mDiffDynamicBaseWeight      ;}
    bool    getDiffSensorCnt              (){ return mDiffSensorCnt              ;}
    bool    getDiffRejectorOpenTime       (){ return mDiffRejectorOpenTime       ;}

    void setSeq                        (quint16  value){ if( value == mSeq                        ) return; mSeq                        = value; emit signalEventChangedSeq                               (value);}
    void setLength                     (quint16  value){ if( value == mLength                     ) return; mLength                     = value; emit signalEventChangedLength                            (value);}
    void setSpeed                      (quint16  value){ if( value == mSpeed                      ) return; mSpeed                      = value; emit signalEventChangedSpeed                             (value);}
    void setMotorAccelerationTime      (quint32  value){ if( value == mMotorAccelerationTime      ) return; mMotorAccelerationTime      = value; emit signalEventChangedMotorAccelerationTime             (value);}
    void setUnderWeight                (quint32  value){ if( value == mUnderWeight                ) return; mUnderWeight                = value; emit signalEventChangedUnderWeight                       (value);}
    void setUnderWarningWeight         (quint32  value){ if( value == mUnderWarningWeight         ) return; mUnderWarningWeight         = value; emit signalEventChangedUnderWarningWeight                (value);}
    void setNormalWeight               (quint32  value){ if( value == mNormalWeight               ) return; mNormalWeight               = value; emit signalEventChangedNormalWeight                      (value);}
    void setOverWarningWeight          (quint32  value){ if( value == mOverWarningWeight          ) return; mOverWarningWeight          = value; emit signalEventChangedOverWarningWeight                 (value);}
    void setOverWeight                 (quint32  value){ if( value == mOverWeight                 ) return; mOverWeight                 = value; emit signalEventChangedOverWeight                        (value);}
    void setTareWeight                 (quint32  value){ if( value == mTareWeight                 ) return; mTareWeight                 = value; emit signalEventChangedTareWeight                        (value);}
    void setWCNGMotion                 (quint16  value){ if( value == mWCNGMotion                 ) return; mWCNGMotion                 = value; emit signalEventChangedWCNGMotion                        (value);}
    void setWCEnableEtcError           (quint16  value){ if( value == mWCEnableEtcError           ) return; mWCEnableEtcError           = value; emit signalEventChangedWCEnableEtcError                  (value);}
    void setMDSenstivity               (quint16  value){ if( value == mMDSenstivity               ) return; mMDSenstivity               = value; emit signalEventChangedMDSenstivity                      (value);}
    void setMDNGMotion                 (quint16  value){ if( value == mMDNGMotion                 ) return; mMDNGMotion                 = value; emit signalEventChangedMDNGMotion                        (value);}
    void setLampTime                   (quint32  value){ if( value == mLampTime                   ) return; mLampTime                   = value; emit signalEventChangedLampTime                          (value);}
    void setBuzzerTime                 (quint32  value){ if( value == mBuzzerTime                 ) return; mBuzzerTime                 = value; emit signalEventChangedBuzzerTime                        (value);}
    void setSpeedConverter             (quint32  value){ if( value == mSpeedConverter             ) return; mSpeedConverter             = value; emit signalEventChangedSpeedConverter                    (value);}
    void setMotorDirection             (quint16  value){ if( value == mMotorDirection             ) return; mMotorDirection             = value; emit signalEventChangedMotorDirection                    (value);}
    void setMotorType                  (quint16  value){ if( value == mMotorType                  ) return; mMotorType                  = value; emit signalEventChangedMotorType                         (value);}
    void setMachineMode                (quint16  value){ if( value == mMachineMode                ) return; mMachineMode                = value; emit signalEventChangedMachineMode                       (value);}
    void setMotorMDRatio               (quint16  value){ if( value == mMotorMDRatio               ) return; mMotorMDRatio               = value; emit signalEventChangedMotorMDRatio                      (value);}
    void setMotorWCRatio               (quint16  value){ if( value == mMotorWCRatio               ) return; mMotorWCRatio               = value; emit signalEventChangedMotorWCRatio                      (value);}
    void setMotorRJRatio               (quint16  value){ if( value == mMotorRJRatio               ) return; mMotorRJRatio               = value; emit signalEventChangedMotorRJRatio                      (value);}
    void setSensorLength               (quint16  value){ if( value == mSensorLength               ) return; mSensorLength               = value; emit signalEventChangedSensorLength                      (value);}
    void setDistanceToRejector         (quint16  value){ if( value == mDistanceToRejector         ) return; mDistanceToRejector         = value; emit signalEventChangedDistanceToRejector                (value);}
    void setMDPhotoIsOn                (bool     value){ if( value == mMDPhotoIsOn                ) return; mMDPhotoIsOn                = value; emit signalEventChangedMDPhotoIsOn                       (value);}
    void setWCPhotoIsOn                (bool     value){ if( value == mWCPhotoIsOn                ) return; mWCPhotoIsOn                = value; emit signalEventChangedWCPhotoIsOn                       (value);}
    void setRejectorRunTimeRatio       (quint32  value){ if( value == mRejectorRunTimeRatio       ) return; mRejectorRunTimeRatio       = value; emit signalEventChangedRejectorRunTimeRatio              (value);}
    void setStaticFactor               (quint32  value){ if( value == mStaticFactor               ) return; mStaticFactor               = value; emit signalEventChangedStaticFactor                      (value);}
    void setDynamicFactor              (quint32  value){ if( value == mDynamicFactor              ) return; mDynamicFactor              = value; emit signalEventChangedDynamicFactor                     (value);}
    void setScaler                     (quint32  value){ if( value == mScaler                     ) return; mScaler                     = value; emit signalEventChangedScaler                            (value);}
    void setDisplayStability           (quint32  value){ if( value == mDisplayStability           ) return; mDisplayStability           = value; emit signalEventChangedDisplayStability                  (value);}
    void setMeasureCueSign             (quint32  value){ if( value == mMeasureCueSign             ) return; mMeasureCueSign             = value; emit signalEventChangedMeasureCueSign                    (value);}
    void setMinStaticWeight            (quint32  value){ if( value == mMinStaticWeight            ) return; mMinStaticWeight            = value; emit signalEventChangedMinStaticWeight                   (value);}
    void setMinDynamicWeight           (quint32  value){ if( value == mMinDynamicWeight           ) return; mMinDynamicWeight           = value; emit signalEventChangedMinDynamicWeight                  (value);}
    void setMode                       (quint16  value){ if( value == mMode                       ) return; mMode                       = value; emit signalEventChangedMode                              (value);}
    void setDistanceBtwSensor          (quint16  value){ if( value == mDistanceBtwSensor          ) return; mDistanceBtwSensor          = value; emit signalEventChangedDistanceBtwSensor                 (value);}
    void setDetectDetectTime           (quint32  value){ if( value == mDetectDetectTime           ) return; mDetectDetectTime           = value; emit signalEventChangedDetectDetectTime                  (value);}
    void setRunDetectTime              (quint32  value){ if( value == mRunDetectTime              ) return; mRunDetectTime              = value; emit signalEventChangedRunDetectTime                     (value);}
    void setDistanceToWeightChecker    (quint16  value){ if( value == mDistanceToWeightChecker    ) return; mDistanceToWeightChecker    = value; emit signalEventChangedDistanceToWeightChecker           (value);}
    void setDistancePhotoToSensor      (quint16  value){ if( value == mDistancePhotoToSensor      ) return; mDistancePhotoToSensor      = value; emit signalEventChangedDistancePhotoToSensor             (value);}
    void setSignalDelayTime            (quint32  value){ if( value == mSignalDelayTime            ) return; mSignalDelayTime            = value; emit signalEventChangedSignalDelayTime                   (value);}
    void setStaticStandardWeight       (quint32  value){ if( value == mStaticStandardWeight       ) return; mStaticStandardWeight       = value; emit signalEventChangedStaticStandardWeight              (value);}
    void setDynamicBaseWeight          (quint32  value){ if( value == mDynamicBaseWeight          ) return; mDynamicBaseWeight          = value; emit signalEventChangedDynamicBaseWeight                 (value);}
    void setSensorCnt                  (quint16  value){ if( value == mSensorCnt                  ) return; mSensorCnt                  = value; emit signalEventChangedSensorCnt                         (value);}
    void setRejectorOpenTime           (quint32  value){ if( value == mRejectorOpenTime           ) return; mRejectorOpenTime           = value; emit signalEventChangedRejectorOpenTime                  (value);}
    void setDiffSeq                    (bool     value){ if( value == mDiffSeq                    ) return; mDiffSeq                    = value; emit signalEventChangedDiffSeq                           (value);}
    void setDiffLength                 (bool     value){ if( value == mDiffLength                 ) return; mDiffLength                 = value; emit signalEventChangedDiffLength                        (value);}
    void setDiffSpeed                  (bool     value){ if( value == mDiffSpeed                  ) return; mDiffSpeed                  = value; emit signalEventChangedDiffSpeed                         (value);}
    void setDiffMotorAccelerationTime  (bool     value){ if( value == mDiffMotorAccelerationTime  ) return; mDiffMotorAccelerationTime  = value; emit signalEventChangedDiffMotorAccelerationTime         (value);}
    void setDiffUnderWeight            (bool     value){ if( value == mDiffUnderWeight            ) return; mDiffUnderWeight            = value; emit signalEventChangedDiffUnderWeight                   (value);}
    void setDiffUnderWarningWeight     (bool     value){ if( value == mDiffUnderWarningWeight     ) return; mDiffUnderWarningWeight     = value; emit signalEventChangedDiffUnderWarningWeight            (value);}
    void setDiffNormalWeight           (bool     value){ if( value == mDiffNormalWeight           ) return; mDiffNormalWeight           = value; emit signalEventChangedDiffNormalWeight                  (value);}
    void setDiffOverWarningWeight      (bool     value){ if( value == mDiffOverWarningWeight      ) return; mDiffOverWarningWeight      = value; emit signalEventChangedDiffOverWarningWeight             (value);}
    void setDiffOverWeight             (bool     value){ if( value == mDiffOverWeight             ) return; mDiffOverWeight             = value; emit signalEventChangedDiffOverWeight                    (value);}
    void setDiffTareWeight             (bool     value){ if( value == mDiffTareWeight             ) return; mDiffTareWeight             = value; emit signalEventChangedDiffTareWeight                    (value);}
    void setDiffWCNGMotion             (bool     value){ if( value == mDiffWCNGMotion             ) return; mDiffWCNGMotion             = value; emit signalEventChangedDiffWCNGMotion                    (value);}
    void setDiffWCEnableEtcError       (bool     value){ if( value == mDiffWCEnableEtcError       ) return; mDiffWCEnableEtcError       = value; emit signalEventChangedDiffWCEnableEtcError              (value);}
    void setDiffMDSenstivity           (bool     value){ if( value == mDiffMDSenstivity           ) return; mDiffMDSenstivity           = value; emit signalEventChangedDiffMDSenstivity                  (value);}
    void setDiffMDNGMotion             (bool     value){ if( value == mDiffMDNGMotion             ) return; mDiffMDNGMotion             = value; emit signalEventChangedDiffMDNGMotion                    (value);}
    void setDiffLampTime               (bool     value){ if( value == mDiffLampTime               ) return; mDiffLampTime               = value; emit signalEventChangedDiffLampTime                      (value);}
    void setDiffBuzzerTime             (bool     value){ if( value == mDiffBuzzerTime             ) return; mDiffBuzzerTime             = value; emit signalEventChangedDiffBuzzerTime                    (value);}
    void setDiffSpeedConverter         (bool     value){ if( value == mDiffSpeedConverter         ) return; mDiffSpeedConverter         = value; emit signalEventChangedDiffSpeedConverter                (value);}
    void setDiffMotorDirection         (bool     value){ if( value == mDiffMotorDirection         ) return; mDiffMotorDirection         = value; emit signalEventChangedDiffMotorDirection                (value);}
    void setDiffMotorType              (bool     value){ if( value == mDiffMotorType              ) return; mDiffMotorType              = value; emit signalEventChangedDiffMotorType                     (value);}
    void setDiffMachineMode            (bool     value){ if( value == mDiffMachineMode            ) return; mDiffMachineMode            = value; emit signalEventChangedDiffMachineMode                   (value);}
    void setDiffMotorMDRatio           (bool     value){ if( value == mDiffMotorMDRatio           ) return; mDiffMotorMDRatio           = value; emit signalEventChangedDiffMotorMDRatio                  (value);}
    void setDiffMotorWCRatio           (bool     value){ if( value == mDiffMotorWCRatio           ) return; mDiffMotorWCRatio           = value; emit signalEventChangedDiffMotorWCRatio                  (value);}
    void setDiffMotorRJRatio           (bool     value){ if( value == mDiffMotorRJRatio           ) return; mDiffMotorRJRatio           = value; emit signalEventChangedDiffMotorRJRatio                  (value);}
    void setDiffSensorLength           (bool     value){ if( value == mDiffSensorLength           ) return; mDiffSensorLength           = value; emit signalEventChangedDiffSensorLength                  (value);}
    void setDiffDistanceToRejector     (bool     value){ if( value == mDiffDistanceToRejector     ) return; mDiffDistanceToRejector     = value; emit signalEventChangedDiffDistanceToRejector            (value);}
    void setDiffMDPhotoIsOn            (bool     value){ if( value == mDiffMDPhotoIsOn            ) return; mDiffMDPhotoIsOn            = value; emit signalEventChangedDiffMDPhotoIsOn                   (value);}
    void setDiffWCPhotoIsOn            (bool     value){ if( value == mDiffWCPhotoIsOn            ) return; mDiffWCPhotoIsOn            = value; emit signalEventChangedDiffWCPhotoIsOn                   (value);}
    void setDiffRejectorRunTimeRatio   (bool     value){ if( value == mDiffRejectorRunTimeRatio   ) return; mDiffRejectorRunTimeRatio   = value; emit signalEventChangedDiffRejectorRunTimeRatio          (value);}
    void setDiffStaticFactor           (bool     value){ if( value == mDiffStaticFactor           ) return; mDiffStaticFactor           = value; emit signalEventChangedDiffStaticFactor                  (value);}
    void setDiffDynamicFactor          (bool     value){ if( value == mDiffDynamicFactor          ) return; mDiffDynamicFactor          = value; emit signalEventChangedDiffDynamicFactor                 (value);}
    void setDiffScaler                 (bool     value){ if( value == mDiffScaler                 ) return; mDiffScaler                 = value; emit signalEventChangedDiffScaler                        (value);}
    void setDiffDisplayStability       (bool     value){ if( value == mDiffDisplayStability       ) return; mDiffDisplayStability       = value; emit signalEventChangedDiffDisplayStability              (value);}
    void setDiffMeasureCueSign         (bool     value){ if( value == mDiffMeasureCueSign         ) return; mDiffMeasureCueSign         = value; emit signalEventChangedDiffMeasureCueSign                (value);}
    void setDiffMinStaticWeight        (bool     value){ if( value == mDiffMinStaticWeight        ) return; mDiffMinStaticWeight        = value; emit signalEventChangedDiffMinStaticWeight               (value);}
    void setDiffMinDynamicWeight       (bool     value){ if( value == mDiffMinDynamicWeight       ) return; mDiffMinDynamicWeight       = value; emit signalEventChangedDiffMinDynamicWeight              (value);}
    void setDiffMode                   (bool     value){ if( value == mDiffMode                   ) return; mDiffMode                   = value; emit signalEventChangedDiffMode                          (value);}
    void setDiffDistanceBtwSensor      (bool     value){ if( value == mDiffDistanceBtwSensor      ) return; mDiffDistanceBtwSensor      = value; emit signalEventChangedDiffDistanceBtwSensor             (value);}
    void setDiffDetectDetectTime       (bool     value){ if( value == mDiffDetectDetectTime       ) return; mDiffDetectDetectTime       = value; emit signalEventChangedDiffDetectDetectTime              (value);}
    void setDiffRunDetectTime          (bool     value){ if( value == mDiffRunDetectTime          ) return; mDiffRunDetectTime          = value; emit signalEventChangedDiffRunDetectTime                 (value);}
    void setDiffDistanceToWeightChecker(bool     value){ if( value == mDiffDistanceToWeightChecker) return; mDiffDistanceToWeightChecker= value; emit signalEventChangedDiffDistanceToWeightChecker       (value);}
    void setDiffDistancePhotoToSensor  (bool     value){ if( value == mDiffDistancePhotoToSensor  ) return; mDiffDistancePhotoToSensor  = value; emit signalEventChangedDiffDistancePhotoToSensor         (value);}
    void setDiffSignalDelayTime        (bool     value){ if( value == mDiffSignalDelayTime        ) return; mDiffSignalDelayTime        = value; emit signalEventChangedDiffSignalDelayTime               (value);}
    void setDiffStaticStandardWeight   (bool     value){ if( value == mDiffStaticStandardWeight   ) return; mDiffStaticStandardWeight   = value; emit signalEventChangedDiffStaticStandardWeight          (value);}
    void setDiffDynamicBaseWeight      (bool     value){ if( value == mDiffDynamicBaseWeight      ) return; mDiffDynamicBaseWeight      = value; emit signalEventChangedDiffDynamicBaseWeight             (value);}
    void setDiffSensorCnt              (bool     value){ if( value == mDiffSensorCnt              ) return; mDiffSensorCnt              = value; emit signalEventChangedDiffSensorCnt                     (value);}
    void setDiffRejectorOpenTime       (bool     value){ if( value == mDiffRejectorOpenTime       ) return; mDiffRejectorOpenTime       = value; emit signalEventChangedDiffRejectorOpenTime              (value);}

signals:
    void signalEventChangedSeq                               (quint16  value);
    void signalEventChangedLength                            (quint16  value);
    void signalEventChangedSpeed                             (quint16  value);
    void signalEventChangedMotorAccelerationTime             (quint32  value);
    void signalEventChangedUnderWeight                       (quint32  value);
    void signalEventChangedUnderWarningWeight                (quint32  value);
    void signalEventChangedNormalWeight                      (quint32  value);
    void signalEventChangedOverWarningWeight                 (quint32  value);
    void signalEventChangedOverWeight                        (quint32  value);
    void signalEventChangedTareWeight                        (quint32  value);
    void signalEventChangedWCNGMotion                        (quint16  value);
    void signalEventChangedWCEnableEtcError                  (quint16  value);
    void signalEventChangedMDSenstivity                      (quint16  value);
    void signalEventChangedMDNGMotion                        (quint16  value);
    void signalEventChangedLampTime                          (quint32  value);
    void signalEventChangedBuzzerTime                        (quint32  value);
    void signalEventChangedSpeedConverter                    (quint32  value);
    void signalEventChangedMotorDirection                    (quint16  value);
    void signalEventChangedMotorType                         (quint16  value);
    void signalEventChangedMachineMode                       (quint32  value);
    void signalEventChangedMotorMDRatio                      (quint16  value);
    void signalEventChangedMotorWCRatio                      (quint16  value);
    void signalEventChangedMotorRJRatio                      (quint16  value);
    void signalEventChangedSensorLength                      (quint16  value);
    void signalEventChangedDistanceToRejector                (quint16  value);
    void signalEventChangedMDPhotoIsOn                       (bool     value);
    void signalEventChangedWCPhotoIsOn                       (bool     value);
    void signalEventChangedRejectorRunTimeRatio              (quint32  value);
    void signalEventChangedStaticFactor                      (quint32  value);
    void signalEventChangedDynamicFactor                     (quint32  value);
    void signalEventChangedScaler                            (quint32  value);
    void signalEventChangedDisplayStability                  (quint32  value);
    void signalEventChangedMeasureCueSign                    (quint32  value);
    void signalEventChangedMinStaticWeight                   (quint32  value);
    void signalEventChangedMinDynamicWeight                  (quint32  value);
    void signalEventChangedMode                              (quint16  value);
    void signalEventChangedDistanceBtwSensor                 (quint16  value);
    void signalEventChangedDetectDetectTime                  (quint32  value);
    void signalEventChangedRunDetectTime                     (quint32  value);
    void signalEventChangedDistanceToWeightChecker           (quint16  value);
    void signalEventChangedDistancePhotoToSensor             (quint16  value);
    void signalEventChangedSignalDelayTime                   (quint32  value);
    void signalEventChangedStaticStandardWeight              (quint32  value);
    void signalEventChangedDynamicBaseWeight                 (quint32  value);
    void signalEventChangedSensorCnt                         (quint16  value);
    void signalEventChangedRejectorOpenTime                  (quint32  value);

    void signalEventChangedDiffSeq                           (bool     value);
    void signalEventChangedDiffLength                        (bool     value);
    void signalEventChangedDiffMotorAccelerationTime         (bool     value);
    void signalEventChangedDiffSpeed                         (bool     value);
    void signalEventChangedDiffUnderWeight                   (bool     value);
    void signalEventChangedDiffUnderWarningWeight            (bool     value);
    void signalEventChangedDiffNormalWeight                  (bool     value);
    void signalEventChangedDiffOverWarningWeight             (bool     value);
    void signalEventChangedDiffOverWeight                    (bool     value);
    void signalEventChangedDiffTareWeight                    (bool     value);
    void signalEventChangedDiffWCNGMotion                    (bool     value);
    void signalEventChangedDiffWCEnableEtcError              (bool     value);
    void signalEventChangedDiffMDSenstivity                  (bool     value);
    void signalEventChangedDiffMDNGMotion                    (bool     value);
    void signalEventChangedDiffLampTime                      (bool     value);
    void signalEventChangedDiffBuzzerTime                    (bool     value);
    void signalEventChangedDiffSpeedConverter                (bool     value);
    void signalEventChangedDiffMotorDirection                (bool     value);
    void signalEventChangedDiffMotorType                     (bool     value);
    void signalEventChangedDiffMachineMode                   (bool     value);
    void signalEventChangedDiffMotorMDRatio                  (bool     value);
    void signalEventChangedDiffMotorWCRatio                  (bool     value);
    void signalEventChangedDiffMotorRJRatio                  (bool     value);
    void signalEventChangedDiffSensorLength                  (bool     value);
    void signalEventChangedDiffDistanceToRejector            (bool     value);
    void signalEventChangedDiffMDPhotoIsOn                   (bool     value);
    void signalEventChangedDiffWCPhotoIsOn                   (bool     value);
    void signalEventChangedDiffRejectorRunTimeRatio          (bool     value);
    void signalEventChangedDiffStaticFactor                  (bool     value);
    void signalEventChangedDiffDynamicFactor                 (bool     value);
    void signalEventChangedDiffScaler                        (bool     value);
    void signalEventChangedDiffDisplayStability              (bool     value);
    void signalEventChangedDiffMeasureCueSign                (bool     value);
    void signalEventChangedDiffMinStaticWeight               (bool     value);
    void signalEventChangedDiffMinDynamicWeight              (bool     value);
    void signalEventChangedDiffMode                          (bool     value);
    void signalEventChangedDiffDistanceBtwSensor             (bool     value);
    void signalEventChangedDiffDetectDetectTime              (bool     value);
    void signalEventChangedDiffRunDetectTime                 (bool     value);
    void signalEventChangedDiffDistanceToWeightChecker       (bool     value);
    void signalEventChangedDiffDistancePhotoToSensor         (bool     value);
    void signalEventChangedDiffSignalDelayTime               (bool     value);
    void signalEventChangedDiffStaticStandardWeight          (bool     value);
    void signalEventChangedDiffDynamicBaseWeight             (bool     value);
    void signalEventChangedDiffSensorCnt                     (bool     value);
    void signalEventChangedDiffRejectorOpenTime              (bool     value);

// down layer ================================================================================
public slots:
    void onChangedRemotePDSetting(quint64 seq, DspPDSettingDto remote)
    {
        CHECK_FALSE_RETURN((mDspSeq == seq));

        setSeq                        (remote.mCommSetting.mProductNum           ); setDiffSeq                    (remote.mCommSetting.mProductNum            != pProductSP->mCurrPD.mDspForm.mCommSetting.mProductNum           );
        setLength                     (remote.mCommSetting.mLength               ); setDiffLength                 (remote.mCommSetting.mLength                != pProductSP->mCurrPD.mDspForm.mCommSetting.mLength               );
        setSpeed                      (remote.mCommSetting.mSpeed                ); setDiffSpeed                  (remote.mCommSetting.mSpeed                 != pProductSP->mCurrPD.mDspForm.mCommSetting.mSpeed                );
        setMotorAccelerationTime      (remote.mCommSetting.mMotorAccelerationTime); setDiffMotorAccelerationTime  (remote.mCommSetting.mMotorAccelerationTime != pProductSP->mCurrPD.mDspForm.mCommSetting.mMotorAccelerationTime);
        setUnderWeight                (remote.mWCSetting.mUnderWeight            ); setDiffUnderWeight            (remote.mWCSetting.mUnderWeight             != pProductSP->mCurrPD.mDspForm.mWCSetting.mUnderWeight            );
        setUnderWarningWeight         (remote.mWCSetting.mUnderWarningWeight     ); setDiffUnderWarningWeight     (remote.mWCSetting.mUnderWarningWeight      != pProductSP->mCurrPD.mDspForm.mWCSetting.mUnderWarningWeight     );
        setNormalWeight               (remote.mWCSetting.mNormalWeight           ); setDiffNormalWeight           (remote.mWCSetting.mNormalWeight            != pProductSP->mCurrPD.mDspForm.mWCSetting.mNormalWeight           );
        setOverWarningWeight          (remote.mWCSetting.mOverWarningWeight      ); setDiffOverWarningWeight      (remote.mWCSetting.mOverWarningWeight       != pProductSP->mCurrPD.mDspForm.mWCSetting.mOverWarningWeight      );
        setOverWeight                 (remote.mWCSetting.mOverWeight             ); setDiffOverWeight             (remote.mWCSetting.mOverWeight              != pProductSP->mCurrPD.mDspForm.mWCSetting.mOverWeight             );
        setTareWeight                 (remote.mWCSetting.mTareWeight             ); setDiffTareWeight             (remote.mWCSetting.mTareWeight              != pProductSP->mCurrPD.mDspForm.mWCSetting.mTareWeight             );
        setWCNGMotion                 (remote.mWCSetting.mNGMotion               ); setDiffWCNGMotion             (remote.mWCSetting.mNGMotion                != pProductSP->mCurrPD.mDspForm.mWCSetting.mNGMotion               );
        setWCEnableEtcError           (remote.mWCSetting.mEnableEtcError         ); setDiffWCEnableEtcError       (remote.mWCSetting.mEnableEtcError          != pProductSP->mCurrPD.mDspForm.mWCSetting.mEnableEtcError         );
        setDynamicFactor              (remote.mWCSetting.mDynamicFactor          ); setDiffDynamicFactor          (remote.mWCSetting.mDynamicFactor           != pProductSP->mCurrPD.mDspForm.mWCSetting.mDynamicFactor          );
        setMDSenstivity               (remote.mMDSetting.mSenstivity             ); setDiffMDSenstivity           (remote.mMDSetting.mSenstivity              != pProductSP->mCurrPD.mDspForm.mMDSetting.mSenstivity             );
        setMDNGMotion                 (remote.mMDSetting.mNGMotion               ); setDiffMDNGMotion             (remote.mMDSetting.mNGMotion                != pProductSP->mCurrPD.mDspForm.mMDSetting.mNGMotion               );

    }

    void onChangedRemoteDevSetting(quint64 seq, DspDevSettingDto remote)
    {
        CHECK_FALSE_RETURN((mDspSeq == seq));

        setLampTime                   (remote.mCommSetting.mLampTime               ); setDiffLampTime               (remote.mCommSetting.mLampTime                != pLSettingSP->mDevSetting.mDspForm.mCommSetting.mLampTime               );
        setBuzzerTime                 (remote.mCommSetting.mBuzzerTime             ); setDiffBuzzerTime             (remote.mCommSetting.mBuzzerTime              != pLSettingSP->mDevSetting.mDspForm.mCommSetting.mBuzzerTime             );
        setSpeedConverter             (remote.mCommSetting.mSpeedConverter         ); setDiffSpeedConverter         (remote.mCommSetting.mSpeedConverter          != pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSpeedConverter         );
        setMotorDirection             (remote.mCommSetting.mMotorDirection         ); setDiffMotorDirection         (remote.mCommSetting.mMotorDirection          != pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMotorDirection         );
        setMotorType                  (remote.mCommSetting.mMotorType              ); setDiffMotorType              (remote.mCommSetting.mMotorType               != pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMotorType              );
        setMachineMode                (remote.mCommSetting.mMachineMode            ); setDiffMachineMode            (remote.mCommSetting.mMachineMode             != pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMachineMode            );
        setMotorMDRatio               (remote.mCommSetting.mMotorMDRatio           ); setDiffMotorMDRatio           (remote.mCommSetting.mMotorMDRatio            != pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMotorMDRatio           );
        setMotorWCRatio               (remote.mCommSetting.mMotorWCRatio           ); setDiffMotorWCRatio           (remote.mCommSetting.mMotorWCRatio            != pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMotorWCRatio           );
        setMotorRJRatio               (remote.mCommSetting.mMotorRJRatio           ); setDiffMotorRJRatio           (remote.mCommSetting.mMotorRJRatio            != pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMotorRJRatio           );
        setSensorLength               (remote.mSizeSetting.mSensorLength           ); setDiffSensorLength           (remote.mSizeSetting.mSensorLength            != pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mSensorLength           );
        setDistanceToRejector         (remote.mSizeSetting.mDistanceToRejector     ); setDiffDistanceToRejector     (remote.mSizeSetting.mDistanceToRejector      != pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistanceToRejector     );
        setMDPhotoIsOn                (remote.mMDSetting.mPhotoIsOn==1?true:false  ); setDiffMDPhotoIsOn            (remote.mMDSetting.mPhotoIsOn                 != pLSettingSP->mDevSetting.mDspForm.mMDSetting.mPhotoIsOn                );
        setWCPhotoIsOn                (remote.mWCSetting.mPhotoIsOn==1?true:false  ); setDiffWCPhotoIsOn            (remote.mWCSetting.mPhotoIsOn                 != pLSettingSP->mDevSetting.mDspForm.mWCSetting.mPhotoIsOn                );
        setRejectorRunTimeRatio       (remote.mCommSetting.mRejectorRunTimeRatio   ); setDiffRejectorRunTimeRatio   (remote.mCommSetting.mRejectorRunTimeRatio    != pLSettingSP->mDevSetting.mDspForm.mCommSetting.mRejectorRunTimeRatio   );
        setStaticFactor               (remote.mWCSetting.mStaticFactor             ); setDiffStaticFactor           (remote.mWCSetting.mStaticFactor              != pLSettingSP->mDevSetting.mDspForm.mWCSetting.mStaticFactor             );
        setScaler                     (remote.mWCSetting.mScaler                   ); setDiffScaler                 (remote.mWCSetting.mScaler                    != pLSettingSP->mDevSetting.mDspForm.mWCSetting.mScaler                   );
        setDisplayStability           (remote.mWCSetting.mDisplayStability         ); setDiffDisplayStability       (remote.mWCSetting.mDisplayStability          != pLSettingSP->mDevSetting.mDspForm.mWCSetting.mDisplayStability         );
        setMeasureCueSign             (remote.mWCSetting.mMeasureCueSign           ); setDiffMeasureCueSign         (remote.mWCSetting.mMeasureCueSign            != pLSettingSP->mDevSetting.mDspForm.mWCSetting.mMeasureCueSign           );
        setMinStaticWeight            (remote.mWCSetting.mMinStaticWeight          ); setDiffMinStaticWeight        (remote.mWCSetting.mMinStaticWeight           != pLSettingSP->mDevSetting.mDspForm.mWCSetting.mMinStaticWeight          );
        setMinDynamicWeight           (remote.mWCSetting.mMinDynamicWeight         ); setDiffMinDynamicWeight       (remote.mWCSetting.mMinDynamicWeight          != pLSettingSP->mDevSetting.mDspForm.mWCSetting.mMinDynamicWeight         );
        setMode                       (remote.mMDSetting.mDetectMode               ); setDiffMode                   (remote.mMDSetting.mDetectMode                != pLSettingSP->mDevSetting.mDspForm.mMDSetting.mDetectMode               );
        setDistanceBtwSensor          (remote.mSizeSetting.mDistanceBtwSensor      ); setDiffDistanceBtwSensor      (remote.mSizeSetting.mDistanceBtwSensor       != pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistanceBtwSensor      );
        setDetectDetectTime           (remote.mMDSetting.mDetectDetectTime         ); setDiffDetectDetectTime       (remote.mMDSetting.mDetectDetectTime          != pLSettingSP->mDevSetting.mDspForm.mMDSetting.mDetectDetectTime         );
        setRunDetectTime              (remote.mMDSetting.mRunDetectTime            ); setDiffRunDetectTime          (remote.mMDSetting.mRunDetectTime             != pLSettingSP->mDevSetting.mDspForm.mMDSetting.mRunDetectTime            );
        setDistanceToWeightChecker    (remote.mSizeSetting.mDistanceToWeightChecker); setDiffDistanceToWeightChecker(remote.mSizeSetting.mDistanceToWeightChecker != pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistanceToWeightChecker);
        setDistancePhotoToSensor      (remote.mSizeSetting.mDistancePhotoToSensor  ); setDiffDistancePhotoToSensor  (remote.mSizeSetting.mDistancePhotoToSensor   != pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistancePhotoToSensor  );
        setSignalDelayTime            (remote.mMDSetting.mSignalDelayTime          ); setDiffSignalDelayTime        (remote.mMDSetting.mSignalDelayTime           != pLSettingSP->mDevSetting.mDspForm.mMDSetting.mSignalDelayTime          );
        setStaticStandardWeight       (remote.mWCSetting.mStaticStandardWeight     ); setDiffStaticStandardWeight   (remote.mWCSetting.mStaticStandardWeight      != pLSettingSP->mDevSetting.mDspForm.mWCSetting.mStaticStandardWeight     );
        setDynamicBaseWeight          (remote.mWCSetting.mDynamicBaseWeight        ); setDiffDynamicBaseWeight      (remote.mWCSetting.mDynamicBaseWeight         != pLSettingSP->mDevSetting.mDspForm.mWCSetting.mDynamicBaseWeight        );
        setSensorCnt                  (remote.mMDSetting.mSensorCnt                ); setDiffSensorCnt              (remote.mMDSetting.mSensorCnt                 != pLSettingSP->mDevSetting.mDspForm.mMDSetting.mSensorCnt                );
        setRejectorOpenTime           (remote.mCommSetting.mRejectorOpenTime       ); setDiffRejectorOpenTime       (remote.mCommSetting.mRejectorOpenTime        != pLSettingSP->mDevSetting.mDspForm.mCommSetting.mRejectorOpenTime       );

        qDebug() <<"Remote mCommSetting.mLampTime                 = " << remote.mCommSetting.mLampTime                <<"Local mCommSetting.mLampTime                 = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mLampTime               ;
        qDebug() <<"Remote mCommSetting.mBuzzerTime               = " << remote.mCommSetting.mBuzzerTime              <<"Local mCommSetting.mBuzzerTime               = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mBuzzerTime             ;
        qDebug() <<"Remote mCommSetting.mSpeedConverter           = " << remote.mCommSetting.mSpeedConverter          <<"Local mCommSetting.mSpeedConverter           = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSpeedConverter         ;
        qDebug() <<"Remote mCommSetting.mMotorDirection           = " << remote.mCommSetting.mMotorDirection          <<"Local mCommSetting.mMotorDirection           = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMotorDirection         ;
        qDebug() <<"Remote mCommSetting.mMotorType                = " << remote.mCommSetting.mMotorType               <<"Local mCommSetting.mMotorType                = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMotorType              ;
        qDebug() <<"Remote mCommSetting.mMachineMode              = " << remote.mCommSetting.mMachineMode             <<"Local mCommSetting.mMachineMode              = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMachineMode            ;
        qDebug() <<"Remote mCommSetting.mMotorMDRatio             = " << remote.mCommSetting.mMotorMDRatio            <<"Local mCommSetting.mMotorMDRatio             = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMotorMDRatio           ;
        qDebug() <<"Remote mCommSetting.mMotorWCRatio             = " << remote.mCommSetting.mMotorWCRatio            <<"Local mCommSetting.mMotorWCRatio             = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMotorWCRatio           ;
        qDebug() <<"Remote mCommSetting.mMotorRJRatio             = " << remote.mCommSetting.mMotorRJRatio            <<"Local mCommSetting.mMotorRJRatio             = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMotorRJRatio           ;
        qDebug() <<"Remote mSizeSetting.mSensorLength             = " << remote.mSizeSetting.mSensorLength            <<"Local mSizeSetting.mSensorLength             = " << pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mSensorLength           ;
        qDebug() <<"Remote mSizeSetting.mDistanceToRejector       = " << remote.mSizeSetting.mDistanceToRejector      <<"Local mSizeSetting.mDistanceToRejector       = " << pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistanceToRejector     ;
        qDebug() <<"Remote mMDSetting.mPhotoIsOn                  = " << remote.mMDSetting.mPhotoIsOn                 <<"Local mMDSetting.mPhotoIsOn                  = " << pLSettingSP->mDevSetting.mDspForm.mMDSetting.mPhotoIsOn                ;
        qDebug() <<"Remote mWCSetting.mPhotoIsOn                  = " << remote.mWCSetting.mPhotoIsOn                 <<"Local mWCSetting.mPhotoIsOn                  = " << pLSettingSP->mDevSetting.mDspForm.mWCSetting.mPhotoIsOn                ;
        qDebug() <<"Remote mCommSetting.mRejectorRunTimeRatio     = " << remote.mCommSetting.mRejectorRunTimeRatio    <<"Local mCommSetting.mRejectorRunTimeRatio     = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mRejectorRunTimeRatio   ;
        qDebug() <<"Remote mWCSetting.mStaticFactor               = " << remote.mWCSetting.mStaticFactor              <<"Local mWCSetting.mStaticFactor               = " << pLSettingSP->mDevSetting.mDspForm.mWCSetting.mStaticFactor             ;
        qDebug() <<"Remote mWCSetting.mScaler                     = " << remote.mWCSetting.mScaler                    <<"Local mWCSetting.mScaler                     = " << pLSettingSP->mDevSetting.mDspForm.mWCSetting.mScaler                   ;
        qDebug() <<"Remote mWCSetting.mDisplayStability           = " << remote.mWCSetting.mDisplayStability          <<"Local mWCSetting.mDisplayStability           = " << pLSettingSP->mDevSetting.mDspForm.mWCSetting.mDisplayStability         ;
        qDebug() <<"Remote mWCSetting.mMeasureCueSign             = " << remote.mWCSetting.mMeasureCueSign            <<"Local mWCSetting.mMeasureCueSign             = " << pLSettingSP->mDevSetting.mDspForm.mWCSetting.mMeasureCueSign           ;
        qDebug() <<"Remote mWCSetting.mMinStaticWeight            = " << remote.mWCSetting.mMinStaticWeight           <<"Local mWCSetting.mMinStaticWeight            = " << pLSettingSP->mDevSetting.mDspForm.mWCSetting.mMinStaticWeight          ;
        qDebug() <<"Remote mWCSetting.mMinDynamicWeight           = " << remote.mWCSetting.mMinDynamicWeight          <<"Local mWCSetting.mMinDynamicWeight           = " << pLSettingSP->mDevSetting.mDspForm.mWCSetting.mMinDynamicWeight         ;
        qDebug() <<"Remote mMDSetting.mDetectMode                 = " << remote.mMDSetting.mDetectMode                <<"Local mMDSetting.mDetectMode                 = " << pLSettingSP->mDevSetting.mDspForm.mMDSetting.mDetectMode               ;
        qDebug() <<"Remote mSizeSetting.mDistanceBtwSensor        = " << remote.mSizeSetting.mDistanceBtwSensor       <<"Local mSizeSetting.mDistanceBtwSensor        = " << pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistanceBtwSensor      ;
        qDebug() <<"Remote mMDSetting.mDetectDetectTime           = " << remote.mMDSetting.mDetectDetectTime          <<"Local mMDSetting.mDetectDetectTime           = " << pLSettingSP->mDevSetting.mDspForm.mMDSetting.mDetectDetectTime         ;
        qDebug() <<"Remote mMDSetting.mRunDetectTime              = " << remote.mMDSetting.mRunDetectTime             <<"Local mMDSetting.mRunDetectTime              = " << pLSettingSP->mDevSetting.mDspForm.mMDSetting.mRunDetectTime            ;
        qDebug() <<"Remote mSizeSetting.mDistanceToWeightChecker  = " << remote.mSizeSetting.mDistanceToWeightChecker <<"Local mSizeSetting.mDistanceToWeightChecker  = " << pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistanceToWeightChecker;
        qDebug() <<"Remote mSizeSetting.mDistancePhotoToSensor    = " << remote.mSizeSetting.mDistancePhotoToSensor   <<"Local mSizeSetting.mDistancePhotoToSensor    = " << pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistancePhotoToSensor  ;
        qDebug() <<"Remote mMDSetting.mSignalDelayTime            = " << remote.mMDSetting.mSignalDelayTime           <<"Local mMDSetting.mSignalDelayTime            = " << pLSettingSP->mDevSetting.mDspForm.mMDSetting.mSignalDelayTime          ;
        qDebug() <<"Remote mWCSetting.mStaticStandardWeight       = " << remote.mWCSetting.mStaticStandardWeight      <<"Local mWCSetting.mStaticStandardWeight       = " << pLSettingSP->mDevSetting.mDspForm.mWCSetting.mStaticStandardWeight     ;
        qDebug() <<"Remote mWCSetting.mDynamicBaseWeight          = " << remote.mWCSetting.mDynamicBaseWeight         <<"Local mWCSetting.mDynamicBaseWeight          = " << pLSettingSP->mDevSetting.mDspForm.mWCSetting.mDynamicBaseWeight        ;
        qDebug() <<"Remote mMDSetting.mSensorCnt                  = " << remote.mMDSetting.mSensorCnt                 <<"Local mMDSetting.mSensorCnt                  = " << pLSettingSP->mDevSetting.mDspForm.mMDSetting.mSensorCnt                ;
        qDebug() <<"Remote mCommSetting.mRejectorOpenTime         = " << remote.mCommSetting.mRejectorOpenTime        <<"Local mCommSetting.mRejectorOpenTime         = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mRejectorOpenTime       ;
    }


// internal layer ===================================================================================
public:
    explicit PanelDebuggingModel(QObject *parent = nullptr):QObject(parent)
    {
        CHECK_FALSE_RETURN((pDspSP->mDspList.size() > 0));

        mDspSeq = pDspSP->mDspList[0]->mSeq;

        ENABLE_SLOT_DSP_CHANGED_REMOTE_DEVSETTING;
        ENABLE_SLOT_DSP_CHANGED_REMOTE_PDSETTING;

        CHECK_FALSE_RETURN((mDspSeq != 0));

        DspMaster * pMaster = pDspSP->findDspMaster(mDspSeq);

        if(pMaster != nullptr)
        {
            onChangedRemoteDevSetting(mDspSeq, pMaster->mRcvDataStore.getDevSettingDto());
            onChangedRemotePDSetting(mDspSeq, pMaster->mRcvDataStore.getPDSettingDto());
        }

    }
};

#endif // PANELDEBUGGINGMODEL_H
