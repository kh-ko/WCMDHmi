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
    Q_PROPERTY(quint32 mMotorDecelerationTime       READ getMotorDecelerationTime              NOTIFY signalEventChangedMotorDecelerationTime             );
    Q_PROPERTY(quint32 mGroupCount                  READ getGroupCount                         NOTIFY signalEventChangedGroupCount                        );
    Q_PROPERTY(quint16 mGroupMotion                 READ getGroupMotion                        NOTIFY signalEventChangedGroupMotion                       );
    Q_PROPERTY(quint16 mGroupLamp                   READ getGroupLamp                          NOTIFY signalEventChangedGroupLamp                         );
    Q_PROPERTY(quint16 mGroupBuzzer                 READ getGroupBuzzer                        NOTIFY signalEventChangedGroupBuzzer                       );
    Q_PROPERTY(quint32 mUnderWeight                 READ getUnderWeight                        NOTIFY signalEventChangedUnderWeight                       );
    Q_PROPERTY(quint32 mUnderWarningWeight          READ getUnderWarningWeight                 NOTIFY signalEventChangedUnderWarningWeight                );
    Q_PROPERTY(quint32 mNormalWeight                READ getNormalWeight                       NOTIFY signalEventChangedNormalWeight                      );
    Q_PROPERTY(quint32 mOverWarningWeight           READ getOverWarningWeight                  NOTIFY signalEventChangedOverWarningWeight                 );
    Q_PROPERTY(quint32 mOverWeight                  READ getOverWeight                         NOTIFY signalEventChangedOverWeight                        );
    Q_PROPERTY(quint32 mTareWeight                  READ getTareWeight                         NOTIFY signalEventChangedTareWeight                        );
    Q_PROPERTY(quint16 mWCOverMotion                READ getWCOverMotion                       NOTIFY signalEventChangedWCOverMotion                      );
    Q_PROPERTY(quint16 mWCUnderMotion               READ getWCUnderMotion                      NOTIFY signalEventChangedWCUnderMotion                     );
    Q_PROPERTY(quint16 mWCEtcMotion                 READ getWCEtcMotion                        NOTIFY signalEventChangedWCEtcMotion                       );
    Q_PROPERTY(quint16 mWCEnableEtcError            READ getWCEnableEtcError                   NOTIFY signalEventChangedWCEnableEtcError                  );
    Q_PROPERTY(quint32 mDynamicFactor               READ getDynamicFactor                      NOTIFY signalEventChangedDynamicFactor                     );
    Q_PROPERTY(quint16 mMDSenstivity                READ getMDSenstivity                       NOTIFY signalEventChangedMDSenstivity                      );
    Q_PROPERTY(quint16 mMDNGMotion                  READ getMDNGMotion                         NOTIFY signalEventChangedMDNGMotion                        );
    Q_PROPERTY(quint16 mWCNGLamp                    READ getWCNGLamp                           NOTIFY signalEventChangedWCNGLamp                          );
    Q_PROPERTY(quint16 mWCNGBuzzer                  READ getWCNGBuzzer                         NOTIFY signalEventChangedWCNGBuzzer                        );
    Q_PROPERTY(quint16 mAutoSetting                 READ getAutoSetting                        NOTIFY signalEventChangedAutoSetting                       );
    Q_PROPERTY(quint16 mFilterCoefficient           READ getFilterCoefficient                  NOTIFY signalEventChangedFilterCoefficient                 );
    Q_PROPERTY(quint32 mMeasureCueSign              READ getMeasureCueSign                     NOTIFY signalEventChangedMeasureCueSign                    );
    Q_PROPERTY(quint32 mMeasureSection              READ getMeasureSection                     NOTIFY signalEventChangedMeasureSection                    );
    Q_PROPERTY(quint16 mMDNGLamp                    READ getMDNGLamp                           NOTIFY signalEventChangedMDNGLamp                          );
    Q_PROPERTY(quint16 mMDNGBuzzer                  READ getMDNGBuzzer                         NOTIFY signalEventChangedMDNGBuzzer                        );
    Q_PROPERTY(quint32 mLampTime                    READ getLampTime                           NOTIFY signalEventChangedLampTime                          );
    Q_PROPERTY(quint32 mBuzzerTime                  READ getBuzzerTime                         NOTIFY signalEventChangedBuzzerTime                        );
    Q_PROPERTY(quint32 mSpeedConverter              READ getSpeedConverter                     NOTIFY signalEventChangedSpeedConverter                    );
    Q_PROPERTY(quint16 mMotorDirection              READ getMotorDirection                     NOTIFY signalEventChangedMotorDirection                    );
    Q_PROPERTY(quint16 mMotorType                   READ getMotorType                          NOTIFY signalEventChangedMotorType                         );
    Q_PROPERTY(quint16 mMotorMDRatio                READ getMotorMDRatio                       NOTIFY signalEventChangedMotorMDRatio                      );
    Q_PROPERTY(quint16 mMotorWCRatio                READ getMotorWCRatio                       NOTIFY signalEventChangedMotorWCRatio                      );
    Q_PROPERTY(quint16 mMotorRJRatio                READ getMotorRJRatio                       NOTIFY signalEventChangedMotorRJRatio                      );
    Q_PROPERTY(quint32 mSorter01RunTimeRatio        READ getSorter01RunTimeRatio               NOTIFY signalEventChangedSorter01RunTimeRatio              );
    Q_PROPERTY(quint32 mSorter01OpenTime            READ getSorter01OpenTime                   NOTIFY signalEventChangedSorter01OpenTime                  );
    Q_PROPERTY(quint32 mSorter02RunTimeRatio        READ getSorter02RunTimeRatio               NOTIFY signalEventChangedSorter02RunTimeRatio              );
    Q_PROPERTY(quint32 mSorter02OpenTime            READ getSorter02OpenTime                   NOTIFY signalEventChangedSorter02OpenTime                  );
    Q_PROPERTY(quint32 mSorter03RunTimeRatio        READ getSorter03RunTimeRatio               NOTIFY signalEventChangedSorter03RunTimeRatio              );
    Q_PROPERTY(quint32 mSorter03OpenTime            READ getSorter03OpenTime                   NOTIFY signalEventChangedSorter03OpenTime                  );
    Q_PROPERTY(quint32 mSorter04RunTimeRatio        READ getSorter04RunTimeRatio               NOTIFY signalEventChangedSorter04RunTimeRatio              );
    Q_PROPERTY(quint32 mSorter04OpenTime            READ getSorter04OpenTime                   NOTIFY signalEventChangedSorter04OpenTime                  );
    Q_PROPERTY(quint16 mDistToSorter01              READ getDistToSorter01                     NOTIFY signalEventChangedDistToSorter01                    );
    Q_PROPERTY(quint16 mDistToSorter02              READ getDistToSorter02                     NOTIFY signalEventChangedDistToSorter02                    );
    Q_PROPERTY(quint16 mDistToSorter03              READ getDistToSorter03                     NOTIFY signalEventChangedDistToSorter03                    );
    Q_PROPERTY(quint16 mDistToSorter04              READ getDistToSorter04                     NOTIFY signalEventChangedDistToSorter04                    );
    Q_PROPERTY(quint16 mMachineMode                 READ getMachineMode                        NOTIFY signalEventChangedMachineMode                       );
    Q_PROPERTY(quint16 mSensorLength                READ getSensorLength                       NOTIFY signalEventChangedSensorLength                      );
    Q_PROPERTY(bool    mMDPhotoIsOn                 READ getMDPhotoIsOn                        NOTIFY signalEventChangedMDPhotoIsOn                       );
    Q_PROPERTY(bool    mWCPhotoIsOn                 READ getWCPhotoIsOn                        NOTIFY signalEventChangedWCPhotoIsOn                       );
    Q_PROPERTY(quint32 mStaticFactor                READ getStaticFactor                       NOTIFY signalEventChangedStaticFactor                      );
    Q_PROPERTY(quint32 mScaler                      READ getScaler                             NOTIFY signalEventChangedScaler                            );
    Q_PROPERTY(quint32 mDisplayStability            READ getDisplayStability                   NOTIFY signalEventChangedDisplayStability                  );
    //Q_PROPERTY(quint32 mMeasureCueSign              READ getMeasureCueSign                     NOTIFY signalEventChangedMeasureCueSign                    );
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
    Q_PROPERTY(qint16  mRefVoltage                  READ getRefVoltage                         NOTIFY signalEventChangedRefVoltage                        );
    Q_PROPERTY(quint16 mGraphPointCnt               READ getGraphPointCnt                      NOTIFY signalEventChangedGraphPointCnt                     );
    Q_PROPERTY(quint16 mSensorCnt                   READ getSensorCnt                          NOTIFY signalEventChangedSensorCnt                         );
    Q_PROPERTY(bool    mDiffSeq                     READ getDiffSeq                            NOTIFY signalEventChangedDiffSeq                           );
    Q_PROPERTY(bool    mDiffLength                  READ getDiffLength                         NOTIFY signalEventChangedDiffLength                        );
    Q_PROPERTY(bool    mDiffSpeed                   READ getDiffSpeed                          NOTIFY signalEventChangedDiffSpeed                         );
    Q_PROPERTY(bool    mDiffMotorAccelerationTime   READ getDiffMotorAccelerationTime          NOTIFY signalEventChangedDiffMotorAccelerationTime         );
    Q_PROPERTY(bool    mDiffMotorDecelerationTime   READ getDiffMotorDecelerationTime          NOTIFY signalEventChangedDiffMotorDecelerationTime         );
    Q_PROPERTY(bool    mDiffGroupCount              READ getDiffGroupCount                     NOTIFY signalEventChangedDiffGroupCount                    );
    Q_PROPERTY(bool    mDiffGroupMotion             READ getDiffGroupMotion                    NOTIFY signalEventChangedDiffGroupMotion                   );
    Q_PROPERTY(bool    mDiffGroupLamp               READ getDiffGroupLamp                      NOTIFY signalEventChangedDiffGroupLamp                     );
    Q_PROPERTY(bool    mDiffGroupBuzzer             READ getDiffGroupBuzzer                    NOTIFY signalEventChangedDiffGroupBuzzer                   );
    Q_PROPERTY(bool    mDiffUnderWeight             READ getDiffUnderWeight                    NOTIFY signalEventChangedDiffUnderWeight                   );
    Q_PROPERTY(bool    mDiffUnderWarningWeight      READ getDiffUnderWarningWeight             NOTIFY signalEventChangedDiffUnderWarningWeight            );
    Q_PROPERTY(bool    mDiffNormalWeight            READ getDiffNormalWeight                   NOTIFY signalEventChangedDiffNormalWeight                  );
    Q_PROPERTY(bool    mDiffOverWarningWeight       READ getDiffOverWarningWeight              NOTIFY signalEventChangedDiffOverWarningWeight             );
    Q_PROPERTY(bool    mDiffOverWeight              READ getDiffOverWeight                     NOTIFY signalEventChangedDiffOverWeight                    );
    Q_PROPERTY(bool    mDiffTareWeight              READ getDiffTareWeight                     NOTIFY signalEventChangedDiffTareWeight                    );
    Q_PROPERTY(bool    mDiffWCOverMotion            READ getDiffWCOverMotion                   NOTIFY signalEventChangedDiffWCOverMotion                  );
    Q_PROPERTY(bool    mDiffWCUnderMotion           READ getDiffWCUnderMotion                  NOTIFY signalEventChangedDiffWCUnderMotion                 );
    Q_PROPERTY(bool    mDiffWCEtcMotion             READ getDiffWCEtcMotion                    NOTIFY signalEventChangedDiffWCEtcMotion                   );
    Q_PROPERTY(bool    mDiffWCEnableEtcError        READ getDiffWCEnableEtcError               NOTIFY signalEventChangedDiffWCEnableEtcError              );
    Q_PROPERTY(bool    mDiffDynamicFactor           READ getDiffDynamicFactor                  NOTIFY signalEventChangedDiffDynamicFactor                 );
    Q_PROPERTY(bool    mDiffMDSenstivity            READ getDiffMDSenstivity                   NOTIFY signalEventChangedDiffMDSenstivity                  );
    Q_PROPERTY(bool    mDiffMDNGMotion              READ getDiffMDNGMotion                     NOTIFY signalEventChangedDiffMDNGMotion                    );
    Q_PROPERTY(bool    mDiffWCNGLamp                READ getDiffWCNGLamp                       NOTIFY signalEventChangedDiffWCNGLamp                      );
    Q_PROPERTY(bool    mDiffWCNGBuzzer              READ getDiffWCNGBuzzer                     NOTIFY signalEventChangedDiffWCNGBuzzer                    );
    Q_PROPERTY(bool    mDiffAutoSetting             READ getDiffAutoSetting                    NOTIFY signalEventChangedDiffAutoSetting                   );
    Q_PROPERTY(bool    mDiffFilterCoefficient       READ getDiffFilterCoefficient              NOTIFY signalEventChangedDiffFilterCoefficient             );
    Q_PROPERTY(bool    mDiffMeasureCueSign          READ getDiffMeasureCueSign                 NOTIFY signalEventChangedDiffMeasureCueSign                );
    Q_PROPERTY(bool    mDiffMeasureSection          READ getDiffMeasureSection                 NOTIFY signalEventChangedDiffMeasureSection                );
    Q_PROPERTY(bool    mDiffMDNGLamp                READ getDiffMDNGLamp                       NOTIFY signalEventChangedDiffMDNGLamp                      );
    Q_PROPERTY(bool    mDiffMDNGBuzzer              READ getDiffMDNGBuzzer                     NOTIFY signalEventChangedDiffMDNGBuzzer                    );
    Q_PROPERTY(bool    mDiffLampTime                READ getDiffLampTime                       NOTIFY signalEventChangedDiffLampTime                      );
    Q_PROPERTY(bool    mDiffBuzzerTime              READ getDiffBuzzerTime                     NOTIFY signalEventChangedDiffBuzzerTime                    );
    Q_PROPERTY(bool    mDiffSpeedConverter          READ getDiffSpeedConverter                 NOTIFY signalEventChangedDiffSpeedConverter                );
    Q_PROPERTY(bool    mDiffMotorDirection          READ getDiffMotorDirection                 NOTIFY signalEventChangedDiffMotorDirection                );
    Q_PROPERTY(bool    mDiffMotorType               READ getDiffMotorType                      NOTIFY signalEventChangedDiffMotorType                     );
    Q_PROPERTY(bool    mDiffMachineMode             READ getDiffMachineMode                    NOTIFY signalEventChangedDiffMachineMode                   );
    Q_PROPERTY(bool    mDiffMotorMDRatio            READ getDiffMotorMDRatio                   NOTIFY signalEventChangedDiffMotorMDRatio                  );
    Q_PROPERTY(bool    mDiffMotorWCRatio            READ getDiffMotorWCRatio                   NOTIFY signalEventChangedDiffMotorWCRatio                  );
    Q_PROPERTY(bool    mDiffMotorRJRatio            READ getDiffMotorRJRatio                   NOTIFY signalEventChangedDiffMotorRJRatio                  );
    Q_PROPERTY(bool    mDiffDistToSorter01          READ getDiffDistToSorter01                 NOTIFY signalEventChangedDiffDistToSorter01                );
    Q_PROPERTY(bool    mDiffDistToSorter02          READ getDiffDistToSorter02                 NOTIFY signalEventChangedDiffDistToSorter02                );
    Q_PROPERTY(bool    mDiffDistToSorter03          READ getDiffDistToSorter03                 NOTIFY signalEventChangedDiffDistToSorter03                );
    Q_PROPERTY(bool    mDiffDistToSorter04          READ getDiffDistToSorter04                 NOTIFY signalEventChangedDiffDistToSorter04                );
    Q_PROPERTY(bool    mDiffSorter01RunTimeRatio    READ getDiffSorter01RunTimeRatio           NOTIFY signalEventChangedDiffSorter01RunTimeRatio          );
    Q_PROPERTY(bool    mDiffSorter01OpenTime        READ getDiffSorter01OpenTime               NOTIFY signalEventChangedDiffSorter01OpenTime              );
    Q_PROPERTY(bool    mDiffSorter02RunTimeRatio    READ getDiffSorter02RunTimeRatio           NOTIFY signalEventChangedDiffSorter02RunTimeRatio          );
    Q_PROPERTY(bool    mDiffSorter02OpenTime        READ getDiffSorter02OpenTime               NOTIFY signalEventChangedDiffSorter02OpenTime              );
    Q_PROPERTY(bool    mDiffSorter03RunTimeRatio    READ getDiffSorter03RunTimeRatio           NOTIFY signalEventChangedDiffSorter03RunTimeRatio          );
    Q_PROPERTY(bool    mDiffSorter03OpenTime        READ getDiffSorter03OpenTime               NOTIFY signalEventChangedDiffSorter03OpenTime              );
    Q_PROPERTY(bool    mDiffSorter04RunTimeRatio    READ getDiffSorter04RunTimeRatio           NOTIFY signalEventChangedDiffSorter04RunTimeRatio          );
    Q_PROPERTY(bool    mDiffSorter04OpenTime        READ getDiffSorter04OpenTime               NOTIFY signalEventChangedDiffSorter04OpenTime              );
    Q_PROPERTY(bool    mDiffMDPhotoIsOn             READ getDiffMDPhotoIsOn                    NOTIFY signalEventChangedDiffMDPhotoIsOn                   );
    Q_PROPERTY(bool    mDiffWCPhotoIsOn             READ getDiffWCPhotoIsOn                    NOTIFY signalEventChangedDiffWCPhotoIsOn                   );
    Q_PROPERTY(bool    mDiffSensorLength            READ getDiffSensorLength                   NOTIFY signalEventChangedDiffSensorLength                  );
    Q_PROPERTY(bool    mDiffStaticFactor            READ getDiffStaticFactor                   NOTIFY signalEventChangedDiffStaticFactor                  );
    Q_PROPERTY(bool    mDiffScaler                  READ getDiffScaler                         NOTIFY signalEventChangedDiffScaler                        );
    Q_PROPERTY(bool    mDiffDisplayStability        READ getDiffDisplayStability               NOTIFY signalEventChangedDiffDisplayStability              );
    //Q_PROPERTY(bool    mDiffMeasureCueSign          READ getDiffMeasureCueSign                 NOTIFY signalEventChangedDiffMeasureCueSign                );
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
    Q_PROPERTY(bool    mDiffRefVoltage              READ getDiffRefVoltage                     NOTIFY signalEventChangedDiffRefVoltage                    );
    Q_PROPERTY(bool    mDiffGraphPointCnt           READ getDiffGraphPointCnt                  NOTIFY signalEventChangedDiffGraphPointCnt                 );
    Q_PROPERTY(bool    mDiffSensorCnt               READ getDiffSensorCnt                      NOTIFY signalEventChangedDiffSensorCnt                     );

public:
    quint64 mDspSeq                     = 0;
    quint16 mSeq                        ;
    quint16 mLength                     ;
    quint16 mSpeed                      ;
    quint32 mMotorAccelerationTime      ;
    quint32 mMotorDecelerationTime      ;
    quint32 mGroupCount                 ;
    quint32 mGroupMotion                ;
    quint16 mGroupLamp                  ;
    quint16 mGroupBuzzer                ;
    quint32 mUnderWeight                ;
    quint32 mUnderWarningWeight         ;
    quint32 mNormalWeight               ;
    quint32 mOverWarningWeight          ;
    quint32 mOverWeight                 ;
    quint32 mTareWeight                 ;
    quint16 mWCOverMotion               ;
    quint16 mWCUnderMotion              ;
    quint16 mWCEtcMotion                ;
    quint16 mWCEnableEtcError           ;
    quint16 mAutoSetting                ;
    quint16 mFilterCoefficient          ;
    quint32 mMeasureCueSign             ;
    quint32 mMeasureSection             ;
    quint32 mDynamicFactor              ;
    quint16 mMDSenstivity               ;
    quint16 mMDNGMotion                 ;
    quint16 mWCNGLamp                   ;
    quint16 mWCNGBuzzer                 ;
    quint16 mMDNGLamp                   ;
    quint16 mMDNGBuzzer                 ;
    quint32 mLampTime                   ;
    quint32 mBuzzerTime                 ;
    quint32 mSpeedConverter             ;
    quint16 mMotorDirection             ;
    quint16 mMotorType                  ;
    quint32 mMachineMode                ;
    quint16 mMotorMDRatio               ;
    quint16 mMotorWCRatio               ;
    quint16 mMotorRJRatio               ;
    quint32 mSorter01RunTimeRatio       ;
    quint32 mSorter01OpenTime           ;
    quint32 mSorter02RunTimeRatio       ;
    quint32 mSorter02OpenTime           ;
    quint32 mSorter03RunTimeRatio       ;
    quint32 mSorter03OpenTime           ;
    quint32 mSorter04RunTimeRatio       ;
    quint32 mSorter04OpenTime           ;
    quint16 mDistToSorter01             ;
    quint16 mDistToSorter02             ;
    quint16 mDistToSorter03             ;
    quint16 mDistToSorter04             ;
    quint16 mSensorLength               ;
    bool    mMDPhotoIsOn                ;
    bool    mWCPhotoIsOn                ;
    quint32 mStaticFactor               ;
    quint32 mScaler                     ;
    quint32 mDisplayStability           ;
    //quint32 mMeasureCueSign             ;
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
    qint16  mRefVoltage                 ;
    quint16 mGraphPointCnt              ;
    quint16 mSensorCnt                  ;

    bool    mDiffSeq                    ;
    bool    mDiffLength                 ;
    bool    mDiffSpeed                  ;
    bool    mDiffMotorAccelerationTime  ;
    bool    mDiffMotorDecelerationTime  ;
    bool    mDiffGroupCount             ;
    bool    mDiffGroupMotion            ;
    bool    mDiffGroupLamp              ;
    bool    mDiffGroupBuzzer            ;
    bool    mDiffUnderWeight            ;
    bool    mDiffUnderWarningWeight     ;
    bool    mDiffNormalWeight           ;
    bool    mDiffOverWarningWeight      ;
    bool    mDiffOverWeight             ;
    bool    mDiffTareWeight             ;
    bool    mDiffWCOverMotion           ;
    bool    mDiffWCUnderMotion          ;
    bool    mDiffWCEtcMotion            ;
    bool    mDiffWCEnableEtcError       ;
    bool    mDiffMDSenstivity           ;
    bool    mDiffMDNGMotion             ;
    bool    mDiffWCNGLamp               ;
    bool    mDiffWCNGBuzzer             ;
    bool    mDiffAutoSetting            ;
    bool    mDiffFilterCoefficient      ;
    bool    mDiffMeasureCueSign         ;
    bool    mDiffMeasureSection         ;
    bool    mDiffMDNGLamp               ;
    bool    mDiffMDNGBuzzer             ;
    bool    mDiffLampTime               ;
    bool    mDiffBuzzerTime             ;
    bool    mDiffSpeedConverter         ;
    bool    mDiffMotorDirection         ;
    bool    mDiffMotorType              ;
    bool    mDiffMachineMode            ;
    bool    mDiffMotorMDRatio           ;
    bool    mDiffMotorWCRatio           ;
    bool    mDiffMotorRJRatio           ;
    bool    mDiffSorter01RunTimeRatio   ;
    bool    mDiffSorter01OpenTime       ;
    bool    mDiffSorter02RunTimeRatio   ;
    bool    mDiffSorter02OpenTime       ;
    bool    mDiffSorter03RunTimeRatio   ;
    bool    mDiffSorter03OpenTime       ;
    bool    mDiffSorter04RunTimeRatio   ;
    bool    mDiffSorter04OpenTime       ;
    bool    mDiffDistToSorter01         ;
    bool    mDiffDistToSorter02         ;
    bool    mDiffDistToSorter03         ;
    bool    mDiffDistToSorter04         ;
    bool    mDiffSensorLength           ;
    bool    mDiffMDPhotoIsOn            ;
    bool    mDiffWCPhotoIsOn            ;
    bool    mDiffStaticFactor           ;
    bool    mDiffDynamicFactor          ;
    bool    mDiffScaler                 ;
    bool    mDiffDisplayStability       ;
    //bool    mDiffMeasureCueSign         ;
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
    bool    mDiffRefVoltage             ;
    bool    mDiffGraphPointCnt          ;
    bool    mDiffSensorCnt              ;

    quint16 getSeq                        (){ return mSeq                        ;}
    quint16 getLength                     (){ return mLength                     ;}
    quint16 getSpeed                      (){ return mSpeed                      ;}
    quint32 getMotorAccelerationTime      (){ return mMotorAccelerationTime      ;}
    quint32 getMotorDecelerationTime      (){ return mMotorDecelerationTime      ;}
    quint32 getGroupCount                 (){ return mGroupCount                 ;}
    quint16 getGroupMotion                (){ return mGroupMotion                ;}
    quint16 getGroupLamp                  (){ return mGroupLamp                  ;}
    quint16 getGroupBuzzer                (){ return mGroupBuzzer                ;}
    quint32 getUnderWeight                (){ return mUnderWeight                ;}
    quint32 getUnderWarningWeight         (){ return mUnderWarningWeight         ;}
    quint32 getNormalWeight               (){ return mNormalWeight               ;}
    quint32 getOverWarningWeight          (){ return mOverWarningWeight          ;}
    quint32 getOverWeight                 (){ return mOverWeight                 ;}
    quint32 getTareWeight                 (){ return mTareWeight                 ;}
    quint16 getWCOverMotion               (){ return mWCOverMotion               ;}
    quint16 getWCUnderMotion              (){ return mWCUnderMotion              ;}
    quint16 getWCEtcMotion                (){ return mWCEtcMotion                ;}
    quint16 getWCEnableEtcError           (){ return mWCEnableEtcError           ;}
    quint32 getDynamicFactor              (){ return mDynamicFactor              ;}
    quint16 getMDSenstivity               (){ return mMDSenstivity               ;}
    quint16 getMDNGMotion                 (){ return mMDNGMotion                 ;}
    quint16 getWCNGLamp                   (){ return mWCNGLamp                   ;}
    quint16 getWCNGBuzzer                 (){ return mWCNGBuzzer                 ;}
    quint16 getAutoSetting                (){ return mAutoSetting                ;}
    quint16 getFilterCoefficient          (){ return mFilterCoefficient          ;}
    quint32 getMeasureCueSign             (){ return mMeasureCueSign             ;}
    quint32 getMeasureSection             (){ return mMeasureSection             ;}
    quint16 getMDNGLamp                   (){ return mMDNGLamp                   ;}
    quint16 getMDNGBuzzer                 (){ return mMDNGBuzzer                 ;}
    quint32 getLampTime                   (){ return mLampTime                   ;}
    quint32 getBuzzerTime                 (){ return mBuzzerTime                 ;}
    quint32 getSpeedConverter             (){ return mSpeedConverter             ;}
    quint16 getMotorDirection             (){ return mMotorDirection             ;}
    quint16 getMotorType                  (){ return mMotorType                  ;}
    quint16 getMachineMode                (){ return mMachineMode                ;}
    quint16 getMotorMDRatio               (){ return mMotorMDRatio               ;}
    quint16 getMotorWCRatio               (){ return mMotorWCRatio               ;}
    quint16 getMotorRJRatio               (){ return mMotorRJRatio               ;}
    quint32 getSorter01RunTimeRatio       (){ return mSorter01RunTimeRatio       ;}
    quint32 getSorter01OpenTime           (){ return mSorter01OpenTime           ;}
    quint32 getSorter02RunTimeRatio       (){ return mSorter02RunTimeRatio       ;}
    quint32 getSorter02OpenTime           (){ return mSorter02OpenTime           ;}
    quint32 getSorter03RunTimeRatio       (){ return mSorter03RunTimeRatio       ;}
    quint32 getSorter03OpenTime           (){ return mSorter03OpenTime           ;}
    quint32 getSorter04RunTimeRatio       (){ return mSorter04RunTimeRatio       ;}
    quint32 getSorter04OpenTime           (){ return mSorter04OpenTime           ;}
    quint16 getDistToSorter01             (){ return mDistToSorter01             ;}
    quint16 getDistToSorter02             (){ return mDistToSorter02             ;}
    quint16 getDistToSorter03             (){ return mDistToSorter03             ;}
    quint16 getDistToSorter04             (){ return mDistToSorter04             ;}
    quint16 getSensorLength               (){ return mSensorLength               ;}
    bool    getMDPhotoIsOn                (){ return mMDPhotoIsOn                ;}
    bool    getWCPhotoIsOn                (){ return mWCPhotoIsOn                ;}
    quint32 getStaticFactor               (){ return mStaticFactor               ;}
    quint32 getScaler                     (){ return mScaler                     ;}
    quint32 getDisplayStability           (){ return mDisplayStability           ;}
    //quint32 getMeasureCueSign             (){ return mMeasureCueSign             ;}
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
    qint16  getRefVoltage                 (){ return mRefVoltage                 ;}
    quint16 getGraphPointCnt              (){ return mGraphPointCnt              ;}
    quint16 getSensorCnt                  (){ return mSensorCnt                  ;}
    bool    getDiffSeq                    (){ return mDiffSeq                    ;}
    bool    getDiffLength                 (){ return mDiffLength                 ;}
    bool    getDiffSpeed                  (){ return mDiffSpeed                  ;}
    bool    getDiffMotorAccelerationTime  (){ return mDiffMotorAccelerationTime  ;}
    bool    getDiffMotorDecelerationTime  (){ return mDiffMotorDecelerationTime  ;}
    bool    getDiffGroupCount             (){ return mDiffGroupCount             ;}
    bool    getDiffGroupMotion            (){ return mDiffGroupMotion            ;}
    bool    getDiffGroupLamp              (){ return mDiffGroupLamp              ;}
    bool    getDiffGroupBuzzer            (){ return mDiffGroupBuzzer            ;}
    bool    getDiffUnderWeight            (){ return mDiffUnderWeight            ;}
    bool    getDiffUnderWarningWeight     (){ return mDiffUnderWarningWeight     ;}
    bool    getDiffNormalWeight           (){ return mDiffNormalWeight           ;}
    bool    getDiffOverWarningWeight      (){ return mDiffOverWarningWeight      ;}
    bool    getDiffOverWeight             (){ return mDiffOverWeight             ;}
    bool    getDiffTareWeight             (){ return mDiffTareWeight             ;}
    bool    getDiffWCOverMotion           (){ return mDiffWCOverMotion           ;}
    bool    getDiffWCUnderMotion          (){ return mDiffWCUnderMotion          ;}
    bool    getDiffWCEtcMotion            (){ return mDiffWCEtcMotion            ;}
    bool    getDiffWCEnableEtcError       (){ return mDiffWCEnableEtcError       ;}
    bool    getDiffDynamicFactor          (){ return mDiffDynamicFactor          ;}
    bool    getDiffMDSenstivity           (){ return mDiffMDSenstivity           ;}
    bool    getDiffMDNGMotion             (){ return mDiffMDNGMotion             ;}
    bool    getDiffWCNGLamp               (){ return mDiffWCNGLamp               ;}
    bool    getDiffWCNGBuzzer             (){ return mDiffWCNGBuzzer             ;}
    bool    getDiffAutoSetting            (){ return mDiffAutoSetting            ;}
    bool    getDiffFilterCoefficient      (){ return mDiffFilterCoefficient      ;}
    bool    getDiffMeasureCueSign         (){ return mDiffMeasureCueSign         ;}
    bool    getDiffMeasureSection         (){ return mDiffMeasureSection         ;}
    bool    getDiffMDNGLamp               (){ return mDiffMDNGLamp               ;}
    bool    getDiffMDNGBuzzer             (){ return mDiffMDNGBuzzer             ;}
    bool    getDiffLampTime               (){ return mDiffLampTime               ;}
    bool    getDiffBuzzerTime             (){ return mDiffBuzzerTime             ;}
    bool    getDiffSpeedConverter         (){ return mDiffSpeedConverter         ;}
    bool    getDiffMotorDirection         (){ return mDiffMotorDirection         ;}
    bool    getDiffMotorType              (){ return mDiffMotorType              ;}
    bool    getDiffMachineMode            (){ return mDiffMachineMode            ;}
    bool    getDiffMotorMDRatio           (){ return mDiffMotorMDRatio           ;}
    bool    getDiffMotorWCRatio           (){ return mDiffMotorWCRatio           ;}
    bool    getDiffMotorRJRatio           (){ return mDiffMotorRJRatio           ;}
    bool    getDiffSorter01RunTimeRatio   (){ return mDiffSorter01RunTimeRatio   ;}
    bool    getDiffSorter01OpenTime       (){ return mDiffSorter01OpenTime       ;}
    bool    getDiffSorter02RunTimeRatio   (){ return mDiffSorter02RunTimeRatio   ;}
    bool    getDiffSorter02OpenTime       (){ return mDiffSorter02OpenTime       ;}
    bool    getDiffSorter03RunTimeRatio   (){ return mDiffSorter03RunTimeRatio   ;}
    bool    getDiffSorter03OpenTime       (){ return mDiffSorter03OpenTime       ;}
    bool    getDiffSorter04RunTimeRatio   (){ return mDiffSorter04RunTimeRatio   ;}
    bool    getDiffSorter04OpenTime       (){ return mDiffSorter04OpenTime       ;}
    bool    getDiffDistToSorter01         (){ return mDiffDistToSorter01         ;}
    bool    getDiffDistToSorter02         (){ return mDiffDistToSorter02         ;}
    bool    getDiffDistToSorter03         (){ return mDiffDistToSorter03         ;}
    bool    getDiffDistToSorter04         (){ return mDiffDistToSorter04         ;}
    bool    getDiffSensorLength           (){ return mDiffSensorLength           ;}
    bool    getDiffMDPhotoIsOn            (){ return mDiffMDPhotoIsOn            ;}
    bool    getDiffWCPhotoIsOn            (){ return mDiffWCPhotoIsOn            ;}
    bool    getDiffStaticFactor           (){ return mDiffStaticFactor           ;}
    bool    getDiffScaler                 (){ return mDiffScaler                 ;}
    bool    getDiffDisplayStability       (){ return mDiffDisplayStability       ;}
    //bool    getDiffMeasureCueSign         (){ return mDiffMeasureCueSign         ;}
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
    bool    getDiffGraphPointCnt          (){ return mDiffGraphPointCnt          ;}
    bool    getDiffRefVoltage             (){ return mDiffRefVoltage             ;}
    bool    getDiffSensorCnt              (){ return mDiffSensorCnt              ;}

    void setSeq                        (quint16  value){ if( value == mSeq                        ) return; mSeq                        = value; emit signalEventChangedSeq                               (value);}
    void setLength                     (quint16  value){ if( value == mLength                     ) return; mLength                     = value; emit signalEventChangedLength                            (value);}
    void setSpeed                      (quint16  value){ if( value == mSpeed                      ) return; mSpeed                      = value; emit signalEventChangedSpeed                             (value);}
    void setMotorAccelerationTime      (quint32  value){ if( value == mMotorAccelerationTime      ) return; mMotorAccelerationTime      = value; emit signalEventChangedMotorAccelerationTime             (value);}
    void setMotorDecelerationTime      (quint32  value){ if( value == mMotorDecelerationTime      ) return; mMotorDecelerationTime      = value; emit signalEventChangedMotorDecelerationTime             (value);}
    void setGroupCount                 (quint32  value){ if( value == mGroupCount                 ) return; mGroupCount                 = value; emit signalEventChangedGroupCount                        (value);}
    void setGroupMotion                (quint16  value){ if( value == mGroupMotion                ) return; mGroupMotion                = value; emit signalEventChangedGroupMotion                       (value);}
    void setGroupLamp                  (quint16  value){ if( value == mGroupLamp                  ) return; mGroupLamp                  = value; emit signalEventChangedGroupLamp                         (value);}
    void setGroupBuzzer                (quint16  value){ if( value == mGroupBuzzer                ) return; mGroupBuzzer                = value; emit signalEventChangedGroupBuzzer                       (value);}
    void setUnderWeight                (quint32  value){ if( value == mUnderWeight                ) return; mUnderWeight                = value; emit signalEventChangedUnderWeight                       (value);}
    void setUnderWarningWeight         (quint32  value){ if( value == mUnderWarningWeight         ) return; mUnderWarningWeight         = value; emit signalEventChangedUnderWarningWeight                (value);}
    void setNormalWeight               (quint32  value){ if( value == mNormalWeight               ) return; mNormalWeight               = value; emit signalEventChangedNormalWeight                      (value);}
    void setOverWarningWeight          (quint32  value){ if( value == mOverWarningWeight          ) return; mOverWarningWeight          = value; emit signalEventChangedOverWarningWeight                 (value);}
    void setOverWeight                 (quint32  value){ if( value == mOverWeight                 ) return; mOverWeight                 = value; emit signalEventChangedOverWeight                        (value);}
    void setTareWeight                 (quint32  value){ if( value == mTareWeight                 ) return; mTareWeight                 = value; emit signalEventChangedTareWeight                        (value);}
    void setWCOverMotion               (quint16  value){ if( value == mWCOverMotion               ) return; mWCOverMotion               = value; emit signalEventChangedWCOverMotion                      (value);}
    void setWCUnderMotion              (quint16  value){ if( value == mWCUnderMotion              ) return; mWCUnderMotion              = value; emit signalEventChangedWCUnderMotion                     (value);}
    void setWCEtcMotion                (quint16  value){ if( value == mWCEtcMotion                ) return; mWCEtcMotion                = value; emit signalEventChangedWCEtcMotion                       (value);}
    void setWCEnableEtcError           (quint16  value){ if( value == mWCEnableEtcError           ) return; mWCEnableEtcError           = value; emit signalEventChangedWCEnableEtcError                  (value);}
    void setDynamicFactor              (quint32  value){ if( value == mDynamicFactor              ) return; mDynamicFactor              = value; emit signalEventChangedDynamicFactor                     (value);}
    void setMDSenstivity               (quint16  value){ if( value == mMDSenstivity               ) return; mMDSenstivity               = value; emit signalEventChangedMDSenstivity                      (value);}
    void setMDNGMotion                 (quint16  value){ if( value == mMDNGMotion                 ) return; mMDNGMotion                 = value; emit signalEventChangedMDNGMotion                        (value);}
    void setWCNGLamp                   (quint16  value){ if( value == mWCNGLamp                   ) return; mWCNGLamp                   = value; emit signalEventChangedWCNGLamp                          (value);}
    void setWCNGBuzzer                 (quint16  value){ if( value == mWCNGBuzzer                 ) return; mWCNGBuzzer                 = value; emit signalEventChangedWCNGBuzzer                        (value);}
    void setAutoSetting                (quint16  value){ if( value == mAutoSetting                ) return; mAutoSetting                = value; emit signalEventChangedAutoSetting                       (value);}
    void setFilterCoefficient          (quint16  value){ if( value == mFilterCoefficient          ) return; mFilterCoefficient          = value; emit signalEventChangedFilterCoefficient                 (value);}
    void setMeasureCueSign             (quint32  value){ if( value == mMeasureCueSign             ) return; mMeasureCueSign             = value; emit signalEventChangedMeasureCueSign                    (value);}
    void setMeasureSection             (quint32  value){ if( value == mMeasureSection             ) return; mMeasureSection             = value; emit signalEventChangedMeasureSection                    (value);}
    void setMDNGLamp                   (quint16  value){ if( value == mMDNGLamp                   ) return; mMDNGLamp                   = value; emit signalEventChangedMDNGLamp                          (value);}
    void setMDNGBuzzer                 (quint16  value){ if( value == mMDNGBuzzer                 ) return; mMDNGBuzzer                 = value; emit signalEventChangedMDNGBuzzer                        (value);}
    void setLampTime                   (quint32  value){ if( value == mLampTime                   ) return; mLampTime                   = value; emit signalEventChangedLampTime                          (value);}
    void setBuzzerTime                 (quint32  value){ if( value == mBuzzerTime                 ) return; mBuzzerTime                 = value; emit signalEventChangedBuzzerTime                        (value);}
    void setSpeedConverter             (quint32  value){ if( value == mSpeedConverter             ) return; mSpeedConverter             = value; emit signalEventChangedSpeedConverter                    (value);}
    void setMotorDirection             (quint16  value){ if( value == mMotorDirection             ) return; mMotorDirection             = value; emit signalEventChangedMotorDirection                    (value);}
    void setMotorType                  (quint16  value){ if( value == mMotorType                  ) return; mMotorType                  = value; emit signalEventChangedMotorType                         (value);}
    void setMachineMode                (quint16  value){ if( value == mMachineMode                ) return; mMachineMode                = value; emit signalEventChangedMachineMode                       (value);}
    void setMotorMDRatio               (quint16  value){ if( value == mMotorMDRatio               ) return; mMotorMDRatio               = value; emit signalEventChangedMotorMDRatio                      (value);}
    void setMotorWCRatio               (quint16  value){ if( value == mMotorWCRatio               ) return; mMotorWCRatio               = value; emit signalEventChangedMotorWCRatio                      (value);}
    void setMotorRJRatio               (quint16  value){ if( value == mMotorRJRatio               ) return; mMotorRJRatio               = value; emit signalEventChangedMotorRJRatio                      (value);}
    void setSorter01RunTimeRatio       (quint32  value){ if( value == mSorter01RunTimeRatio       ) return; mSorter01RunTimeRatio       = value; emit signalEventChangedSorter01RunTimeRatio              (value);}
    void setSorter01OpenTime           (quint32  value){ if( value == mSorter01OpenTime           ) return; mSorter01OpenTime           = value; emit signalEventChangedSorter01OpenTime                  (value);}
    void setSorter02RunTimeRatio       (quint32  value){ if( value == mSorter02RunTimeRatio       ) return; mSorter02RunTimeRatio       = value; emit signalEventChangedSorter02RunTimeRatio              (value);}
    void setSorter02OpenTime           (quint32  value){ if( value == mSorter02OpenTime           ) return; mSorter02OpenTime           = value; emit signalEventChangedSorter02OpenTime                  (value);}
    void setSorter03RunTimeRatio       (quint32  value){ if( value == mSorter03RunTimeRatio       ) return; mSorter03RunTimeRatio       = value; emit signalEventChangedSorter03RunTimeRatio              (value);}
    void setSorter03OpenTime           (quint32  value){ if( value == mSorter03OpenTime           ) return; mSorter03OpenTime           = value; emit signalEventChangedSorter03OpenTime                  (value);}
    void setSorter04RunTimeRatio       (quint32  value){ if( value == mSorter04RunTimeRatio       ) return; mSorter04RunTimeRatio       = value; emit signalEventChangedSorter04RunTimeRatio              (value);}
    void setSorter04OpenTime           (quint32  value){ if( value == mSorter04OpenTime           ) return; mSorter04OpenTime           = value; emit signalEventChangedSorter04OpenTime                  (value);}
    void setDistToSorter01             (quint16  value){ if( value == mDistToSorter01             ) return; mDistToSorter01             = value; emit signalEventChangedDistToSorter01                    (value);}
    void setDistToSorter02             (quint16  value){ if( value == mDistToSorter02             ) return; mDistToSorter02             = value; emit signalEventChangedDistToSorter02                    (value);}
    void setDistToSorter03             (quint16  value){ if( value == mDistToSorter03             ) return; mDistToSorter03             = value; emit signalEventChangedDistToSorter03                    (value);}
    void setDistToSorter04             (quint16  value){ if( value == mDistToSorter04             ) return; mDistToSorter04             = value; emit signalEventChangedDistToSorter04                    (value);}
    void setSensorLength               (quint16  value){ if( value == mSensorLength               ) return; mSensorLength               = value; emit signalEventChangedSensorLength                      (value);}
    void setMDPhotoIsOn                (bool     value){ if( value == mMDPhotoIsOn                ) return; mMDPhotoIsOn                = value; emit signalEventChangedMDPhotoIsOn                       (value);}
    void setWCPhotoIsOn                (bool     value){ if( value == mWCPhotoIsOn                ) return; mWCPhotoIsOn                = value; emit signalEventChangedWCPhotoIsOn                       (value);}
    void setStaticFactor               (quint32  value){ if( value == mStaticFactor               ) return; mStaticFactor               = value; emit signalEventChangedStaticFactor                      (value);}
    void setScaler                     (quint32  value){ if( value == mScaler                     ) return; mScaler                     = value; emit signalEventChangedScaler                            (value);}
    void setDisplayStability           (quint32  value){ if( value == mDisplayStability           ) return; mDisplayStability           = value; emit signalEventChangedDisplayStability                  (value);}
    //void setMeasureCueSign             (quint32  value){ if( value == mMeasureCueSign             ) return; mMeasureCueSign             = value; emit signalEventChangedMeasureCueSign                    (value);}
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
    void setRefVoltage                 (qint16   value){ if( value == mRefVoltage                 ) return; mRefVoltage                 = value; emit signalEventChangedRefVoltage                        (value);}
    void setGraphPointCnt              (quint16  value){ if( value == mGraphPointCnt              ) return; mGraphPointCnt              = value; emit signalEventChangedGraphPointCnt                     (value);}
    void setSensorCnt                  (quint16  value){ if( value == mSensorCnt                  ) return; mSensorCnt                  = value; emit signalEventChangedSensorCnt                         (value);}
    void setDiffSeq                    (bool     value){ if( value == mDiffSeq                    ) return; mDiffSeq                    = value; emit signalEventChangedDiffSeq                           (value);}
    void setDiffLength                 (bool     value){ if( value == mDiffLength                 ) return; mDiffLength                 = value; emit signalEventChangedDiffLength                        (value);}
    void setDiffSpeed                  (bool     value){ if( value == mDiffSpeed                  ) return; mDiffSpeed                  = value; emit signalEventChangedDiffSpeed                         (value);}
    void setDiffMotorAccelerationTime  (bool     value){ if( value == mDiffMotorAccelerationTime  ) return; mDiffMotorAccelerationTime  = value; emit signalEventChangedDiffMotorAccelerationTime         (value);}
    void setDiffMotorDecelerationTime  (bool     value){ if( value == mDiffMotorDecelerationTime  ) return; mDiffMotorDecelerationTime  = value; emit signalEventChangedDiffMotorDecelerationTime         (value);}
    void setDiffGroupCount             (bool     value){ if( value == mDiffGroupCount             ) return; mDiffGroupCount             = value; emit signalEventChangedDiffGroupCount                    (value);}
    void setDiffGroupMotion            (bool     value){ if( value == mDiffGroupMotion            ) return; mDiffGroupMotion            = value; emit signalEventChangedDiffGroupMotion                   (value);}
    void setDiffGroupLamp              (bool     value){ if( value == mDiffGroupLamp              ) return; mDiffGroupLamp              = value; emit signalEventChangedDiffGroupLamp                     (value);}
    void setDiffGroupBuzzer            (bool     value){ if( value == mDiffGroupBuzzer            ) return; mDiffGroupBuzzer            = value; emit signalEventChangedDiffGroupBuzzer                   (value);}
    void setDiffUnderWeight            (bool     value){ if( value == mDiffUnderWeight            ) return; mDiffUnderWeight            = value; emit signalEventChangedDiffUnderWeight                   (value);}
    void setDiffUnderWarningWeight     (bool     value){ if( value == mDiffUnderWarningWeight     ) return; mDiffUnderWarningWeight     = value; emit signalEventChangedDiffUnderWarningWeight            (value);}
    void setDiffNormalWeight           (bool     value){ if( value == mDiffNormalWeight           ) return; mDiffNormalWeight           = value; emit signalEventChangedDiffNormalWeight                  (value);}
    void setDiffOverWarningWeight      (bool     value){ if( value == mDiffOverWarningWeight      ) return; mDiffOverWarningWeight      = value; emit signalEventChangedDiffOverWarningWeight             (value);}
    void setDiffOverWeight             (bool     value){ if( value == mDiffOverWeight             ) return; mDiffOverWeight             = value; emit signalEventChangedDiffOverWeight                    (value);}
    void setDiffTareWeight             (bool     value){ if( value == mDiffTareWeight             ) return; mDiffTareWeight             = value; emit signalEventChangedDiffTareWeight                    (value);}
    void setDiffWCOverMotion           (bool     value){ if( value == mDiffWCOverMotion           ) return; mDiffWCOverMotion           = value; emit signalEventChangedDiffWCOverMotion                  (value);}
    void setDiffWCUnderMotion          (bool     value){ if( value == mDiffWCUnderMotion          ) return; mDiffWCUnderMotion          = value; emit signalEventChangedDiffWCUnderMotion                 (value);}
    void setDiffWCEtcMotion            (bool     value){ if( value == mDiffWCEtcMotion            ) return; mDiffWCEtcMotion            = value; emit signalEventChangedDiffWCEtcMotion                   (value);}
    void setDiffWCEnableEtcError       (bool     value){ if( value == mDiffWCEnableEtcError       ) return; mDiffWCEnableEtcError       = value; emit signalEventChangedDiffWCEnableEtcError              (value);}
    void setDiffDynamicFactor          (bool     value){ if( value == mDiffDynamicFactor          ) return; mDiffDynamicFactor          = value; emit signalEventChangedDiffDynamicFactor                 (value);}
    void setDiffMDSenstivity           (bool     value){ if( value == mDiffMDSenstivity           ) return; mDiffMDSenstivity           = value; emit signalEventChangedDiffMDSenstivity                  (value);}
    void setDiffMDNGMotion             (bool     value){ if( value == mDiffMDNGMotion             ) return; mDiffMDNGMotion             = value; emit signalEventChangedDiffMDNGMotion                    (value);}
    void setDiffWCNGLamp               (bool     value){ if( value == mDiffWCNGLamp               ) return; mDiffWCNGLamp               = value; emit signalEventChangedDiffWCNGLamp                      (value);}
    void setDiffWCNGBuzzer             (bool     value){ if( value == mDiffWCNGBuzzer             ) return; mDiffWCNGBuzzer             = value; emit signalEventChangedDiffWCNGBuzzer                    (value);}
    void setDiffAutoSetting            (bool     value){ if( value == mDiffAutoSetting            ) return; mDiffAutoSetting            = value; emit signalEventChangedDiffAutoSetting                   (value);}
    void setDiffFilterCoefficient      (bool     value){ if( value == mDiffFilterCoefficient      ) return; mDiffFilterCoefficient      = value; emit signalEventChangedDiffFilterCoefficient             (value);}
    void setDiffMeasureCueSign         (bool     value){ if( value == mDiffMeasureCueSign         ) return; mDiffMeasureCueSign         = value; emit signalEventChangedDiffMeasureCueSign                (value);}
    void setDiffMeasureSection         (bool     value){ if( value == mDiffMeasureSection         ) return; mDiffMeasureSection         = value; emit signalEventChangedDiffMeasureSection                (value);}
    void setDiffMDNGLamp               (bool     value){ if( value == mDiffMDNGLamp               ) return; mDiffMDNGLamp               = value; emit signalEventChangedDiffMDNGLamp                      (value);}
    void setDiffMDNGBuzzer             (bool     value){ if( value == mDiffMDNGBuzzer             ) return; mDiffMDNGBuzzer             = value; emit signalEventChangedDiffMDNGBuzzer                    (value);}
    void setDiffLampTime               (bool     value){ if( value == mDiffLampTime               ) return; mDiffLampTime               = value; emit signalEventChangedDiffLampTime                      (value);}
    void setDiffBuzzerTime             (bool     value){ if( value == mDiffBuzzerTime             ) return; mDiffBuzzerTime             = value; emit signalEventChangedDiffBuzzerTime                    (value);}
    void setDiffSpeedConverter         (bool     value){ if( value == mDiffSpeedConverter         ) return; mDiffSpeedConverter         = value; emit signalEventChangedDiffSpeedConverter                (value);}
    void setDiffMotorDirection         (bool     value){ if( value == mDiffMotorDirection         ) return; mDiffMotorDirection         = value; emit signalEventChangedDiffMotorDirection                (value);}
    void setDiffMotorType              (bool     value){ if( value == mDiffMotorType              ) return; mDiffMotorType              = value; emit signalEventChangedDiffMotorType                     (value);}
    void setDiffMachineMode            (bool     value){ if( value == mDiffMachineMode            ) return; mDiffMachineMode            = value; emit signalEventChangedDiffMachineMode                   (value);}
    void setDiffMotorMDRatio           (bool     value){ if( value == mDiffMotorMDRatio           ) return; mDiffMotorMDRatio           = value; emit signalEventChangedDiffMotorMDRatio                  (value);}
    void setDiffMotorWCRatio           (bool     value){ if( value == mDiffMotorWCRatio           ) return; mDiffMotorWCRatio           = value; emit signalEventChangedDiffMotorWCRatio                  (value);}
    void setDiffMotorRJRatio           (bool     value){ if( value == mDiffMotorRJRatio           ) return; mDiffMotorRJRatio           = value; emit signalEventChangedDiffMotorRJRatio                  (value);}
    void setDiffSorter01RunTimeRatio   (bool     value){ if( value == mDiffSorter01RunTimeRatio   ) return; mDiffSorter01RunTimeRatio   = value; emit signalEventChangedDiffSorter01RunTimeRatio          (value);}
    void setDiffSorter01OpenTime       (bool     value){ if( value == mDiffSorter01OpenTime       ) return; mDiffSorter01OpenTime       = value; emit signalEventChangedDiffSorter01OpenTime              (value);}
    void setDiffSorter02RunTimeRatio   (bool     value){ if( value == mDiffSorter02RunTimeRatio   ) return; mDiffSorter02RunTimeRatio   = value; emit signalEventChangedDiffSorter02RunTimeRatio          (value);}
    void setDiffSorter02OpenTime       (bool     value){ if( value == mDiffSorter02OpenTime       ) return; mDiffSorter02OpenTime       = value; emit signalEventChangedDiffSorter02OpenTime              (value);}
    void setDiffSorter03RunTimeRatio   (bool     value){ if( value == mDiffSorter03RunTimeRatio   ) return; mDiffSorter03RunTimeRatio   = value; emit signalEventChangedDiffSorter03RunTimeRatio          (value);}
    void setDiffSorter03OpenTime       (bool     value){ if( value == mDiffSorter03OpenTime       ) return; mDiffSorter03OpenTime       = value; emit signalEventChangedDiffSorter03OpenTime              (value);}
    void setDiffSorter04RunTimeRatio   (bool     value){ if( value == mDiffSorter04RunTimeRatio   ) return; mDiffSorter04RunTimeRatio   = value; emit signalEventChangedDiffSorter04RunTimeRatio          (value);}
    void setDiffSorter04OpenTime       (bool     value){ if( value == mDiffSorter04OpenTime       ) return; mDiffSorter04OpenTime       = value; emit signalEventChangedDiffSorter04OpenTime              (value);}
    void setDiffDistToSorter01         (bool     value){ if( value == mDiffDistToSorter01         ) return; mDiffDistToSorter01         = value; emit signalEventChangedDiffDistToSorter01                (value);}
    void setDiffDistToSorter02         (bool     value){ if( value == mDiffDistToSorter02         ) return; mDiffDistToSorter02         = value; emit signalEventChangedDiffDistToSorter02                (value);}
    void setDiffDistToSorter03         (bool     value){ if( value == mDiffDistToSorter03         ) return; mDiffDistToSorter03         = value; emit signalEventChangedDiffDistToSorter03                (value);}
    void setDiffDistToSorter04         (bool     value){ if( value == mDiffDistToSorter04         ) return; mDiffDistToSorter04         = value; emit signalEventChangedDiffDistToSorter04                (value);}
    void setDiffSensorLength           (bool     value){ if( value == mDiffSensorLength           ) return; mDiffSensorLength           = value; emit signalEventChangedDiffSensorLength                  (value);}
    void setDiffMDPhotoIsOn            (bool     value){ if( value == mDiffMDPhotoIsOn            ) return; mDiffMDPhotoIsOn            = value; emit signalEventChangedDiffMDPhotoIsOn                   (value);}
    void setDiffWCPhotoIsOn            (bool     value){ if( value == mDiffWCPhotoIsOn            ) return; mDiffWCPhotoIsOn            = value; emit signalEventChangedDiffWCPhotoIsOn                   (value);}
    void setDiffStaticFactor           (bool     value){ if( value == mDiffStaticFactor           ) return; mDiffStaticFactor           = value; emit signalEventChangedDiffStaticFactor                  (value);}
    void setDiffScaler                 (bool     value){ if( value == mDiffScaler                 ) return; mDiffScaler                 = value; emit signalEventChangedDiffScaler                        (value);}
    void setDiffDisplayStability       (bool     value){ if( value == mDiffDisplayStability       ) return; mDiffDisplayStability       = value; emit signalEventChangedDiffDisplayStability              (value);}
    //void setDiffMeasureCueSign         (bool     value){ if( value == mDiffMeasureCueSign         ) return; mDiffMeasureCueSign         = value; emit signalEventChangedDiffMeasureCueSign                (value);}
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
    void setDiffGraphPointCnt          (bool     value){ if( value == mDiffGraphPointCnt          ) return; mDiffGraphPointCnt          = value; emit signalEventChangedDiffGraphPointCnt                 (value);}
    void setDiffRefVoltage             (bool     value){ if( value == mDiffRefVoltage             ) return; mDiffRefVoltage             = value; emit signalEventChangedDiffRefVoltage                    (value);}
    void setDiffSensorCnt              (bool     value){ if( value == mDiffSensorCnt              ) return; mDiffSensorCnt              = value; emit signalEventChangedDiffSensorCnt                     (value);}

signals:
    void signalEventChangedSeq                               (quint16  value);
    void signalEventChangedLength                            (quint16  value);
    void signalEventChangedSpeed                             (quint16  value);
    void signalEventChangedMotorAccelerationTime             (quint32  value);
    void signalEventChangedMotorDecelerationTime             (quint32  value);
    void signalEventChangedGroupCount                        (quint32  value);
    void signalEventChangedGroupMotion                       (quint16  value);
    void signalEventChangedGroupLamp                         (quint16  value);
    void signalEventChangedGroupBuzzer                       (quint16  value);
    void signalEventChangedUnderWeight                       (quint32  value);
    void signalEventChangedUnderWarningWeight                (quint32  value);
    void signalEventChangedNormalWeight                      (quint32  value);
    void signalEventChangedOverWarningWeight                 (quint32  value);
    void signalEventChangedOverWeight                        (quint32  value);
    void signalEventChangedTareWeight                        (quint32  value);
    void signalEventChangedWCOverMotion                      (quint16  value);
    void signalEventChangedWCUnderMotion                     (quint16  value);
    void signalEventChangedWCEtcMotion                       (quint16  value);
    void signalEventChangedWCEnableEtcError                  (quint16  value);
    void signalEventChangedDynamicFactor                     (quint32  value);
    void signalEventChangedMDSenstivity                      (quint16  value);
    void signalEventChangedMDNGMotion                        (quint16  value);
    void signalEventChangedWCNGLamp                          (quint16  value);
    void signalEventChangedWCNGBuzzer                        (quint16  value);
    void signalEventChangedAutoSetting                       (quint16  value);
    void signalEventChangedFilterCoefficient                 (quint16  value);
    void signalEventChangedMeasureCueSign                    (quint32  value);
    void signalEventChangedMeasureSection                    (quint32  value);
    void signalEventChangedMDNGLamp                          (quint16  value);
    void signalEventChangedMDNGBuzzer                        (quint16  value);
    void signalEventChangedLampTime                          (quint32  value);
    void signalEventChangedBuzzerTime                        (quint32  value);
    void signalEventChangedSpeedConverter                    (quint32  value);
    void signalEventChangedMotorDirection                    (quint16  value);
    void signalEventChangedMotorType                         (quint16  value);
    void signalEventChangedMachineMode                       (quint32  value);
    void signalEventChangedMotorMDRatio                      (quint16  value);
    void signalEventChangedMotorWCRatio                      (quint16  value);
    void signalEventChangedMotorRJRatio                      (quint16  value);
    void signalEventChangedSorter01RunTimeRatio              (quint32  value);
    void signalEventChangedSorter01OpenTime                  (quint32  value);
    void signalEventChangedSorter02RunTimeRatio              (quint32  value);
    void signalEventChangedSorter02OpenTime                  (quint32  value);
    void signalEventChangedSorter03RunTimeRatio              (quint32  value);
    void signalEventChangedSorter03OpenTime                  (quint32  value);
    void signalEventChangedSorter04RunTimeRatio              (quint32  value);
    void signalEventChangedSorter04OpenTime                  (quint32  value);
    void signalEventChangedDistToSorter01                    (quint16  value);
    void signalEventChangedDistToSorter02                    (quint16  value);
    void signalEventChangedDistToSorter03                    (quint16  value);
    void signalEventChangedDistToSorter04                    (quint16  value);
    void signalEventChangedSensorLength                      (quint16  value);
    void signalEventChangedMDPhotoIsOn                       (bool     value);
    void signalEventChangedWCPhotoIsOn                       (bool     value);
    void signalEventChangedStaticFactor                      (quint32  value);
    void signalEventChangedScaler                            (quint32  value);
    void signalEventChangedDisplayStability                  (quint32  value);
    //void signalEventChangedMeasureCueSign                    (quint32  value);
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
    void signalEventChangedRefVoltage                        (qint16   value);
    void signalEventChangedGraphPointCnt                     (quint16  value);
    void signalEventChangedSensorCnt                         (quint16  value);

    void signalEventChangedDiffSeq                           (bool     value);
    void signalEventChangedDiffLength                        (bool     value);
    void signalEventChangedDiffMotorAccelerationTime         (bool     value);
    void signalEventChangedDiffMotorDecelerationTime         (bool     value);
    void signalEventChangedDiffGroupCount                    (bool     value);
    void signalEventChangedDiffGroupMotion                   (bool     value);
    void signalEventChangedDiffGroupLamp                     (bool     value);
    void signalEventChangedDiffGroupBuzzer                   (bool     value);
    void signalEventChangedDiffSpeed                         (bool     value);
    void signalEventChangedDiffUnderWeight                   (bool     value);
    void signalEventChangedDiffUnderWarningWeight            (bool     value);
    void signalEventChangedDiffNormalWeight                  (bool     value);
    void signalEventChangedDiffOverWarningWeight             (bool     value);
    void signalEventChangedDiffOverWeight                    (bool     value);
    void signalEventChangedDiffTareWeight                    (bool     value);
    void signalEventChangedDiffWCOverMotion                  (bool     value);
    void signalEventChangedDiffWCUnderMotion                 (bool     value);
    void signalEventChangedDiffWCEtcMotion                   (bool     value);
    void signalEventChangedDiffWCEnableEtcError              (bool     value);
    void signalEventChangedDiffDynamicFactor                 (bool     value);
    void signalEventChangedDiffMDSenstivity                  (bool     value);
    void signalEventChangedDiffMDNGMotion                    (bool     value);
    void signalEventChangedDiffWCNGLamp                      (bool     value);
    void signalEventChangedDiffWCNGBuzzer                    (bool     value);
    void signalEventChangedDiffAutoSetting                   (bool     value);
    void signalEventChangedDiffFilterCoefficient             (bool     value);
    void signalEventChangedDiffMeasureCueSign                (bool     value);
    void signalEventChangedDiffMeasureSection                (bool     value);
    void signalEventChangedDiffMDNGLamp                      (bool     value);
    void signalEventChangedDiffMDNGBuzzer                    (bool     value);
    void signalEventChangedDiffLampTime                      (bool     value);
    void signalEventChangedDiffBuzzerTime                    (bool     value);
    void signalEventChangedDiffSpeedConverter                (bool     value);
    void signalEventChangedDiffMotorDirection                (bool     value);
    void signalEventChangedDiffMotorType                     (bool     value);
    void signalEventChangedDiffMachineMode                   (bool     value);
    void signalEventChangedDiffMotorMDRatio                  (bool     value);
    void signalEventChangedDiffMotorWCRatio                  (bool     value);
    void signalEventChangedDiffMotorRJRatio                  (bool     value);
    void signalEventChangedDiffSorter01RunTimeRatio          (bool     value);
    void signalEventChangedDiffSorter01OpenTime              (bool     value);
    void signalEventChangedDiffSorter02RunTimeRatio          (bool     value);
    void signalEventChangedDiffSorter02OpenTime              (bool     value);
    void signalEventChangedDiffSorter03RunTimeRatio          (bool     value);
    void signalEventChangedDiffSorter03OpenTime              (bool     value);
    void signalEventChangedDiffSorter04RunTimeRatio          (bool     value);
    void signalEventChangedDiffSorter04OpenTime              (bool     value);
    void signalEventChangedDiffDistToSorter01                (bool     value);
    void signalEventChangedDiffDistToSorter02                (bool     value);
    void signalEventChangedDiffDistToSorter03                (bool     value);
    void signalEventChangedDiffDistToSorter04                (bool     value);
    void signalEventChangedDiffSensorLength                  (bool     value);
    void signalEventChangedDiffMDPhotoIsOn                   (bool     value);
    void signalEventChangedDiffWCPhotoIsOn                   (bool     value);
    void signalEventChangedDiffStaticFactor                  (bool     value);
    void signalEventChangedDiffScaler                        (bool     value);
    void signalEventChangedDiffDisplayStability              (bool     value);
    //void signalEventChangedDiffMeasureCueSign                (bool     value);
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
    void signalEventChangedDiffRefVoltage                    (bool     value);
    void signalEventChangedDiffGraphPointCnt                 (bool     value);
    void signalEventChangedDiffSensorCnt                     (bool     value);

// down layer ================================================================================
public slots:
    void onChangedRemotePDSetting(quint64 seq, DspPDSettingDto remote)
    {
        CHECK_FALSE_RETURN((mDspSeq == seq));

        setSeq                        (remote.mCommSetting.mProductNum           ); setDiffSeq                    (remote.mCommSetting.mProductNum            != pProductSP->mCurrPD.mDspForm.mCommSetting.mProductNum           );
        setLength                     (remote.mCommSetting.mLength               ); setDiffLength                 (remote.mCommSetting.mLength                != pProductSP->mCurrPD.mDspForm.mCommSetting.mLength               );
        setSpeed                      (remote.mCommSetting.mSpeed                ); setDiffSpeed                  (remote.mCommSetting.mSpeed                 != pProductSP->mCurrPD.mDspForm.mCommSetting.mSpeed                );
        setMotorAccelerationTime      (remote.mCommSetting.mMotorAccelerationTime); setDiffMotorAccelerationTime  (remote.mCommSetting.mMotorAccelerationTime != pProductSP->mCurrPD.mDspForm.mCommSetting.mMotorAccelerationTime);
        setMotorDecelerationTime      (remote.mCommSetting.mMotorDecelerationTime); setDiffMotorDecelerationTime  (remote.mCommSetting.mMotorDecelerationTime != pProductSP->mCurrPD.mDspForm.mCommSetting.mMotorDecelerationTime);
        setGroupCount                 (remote.mCommSetting.mGroupCount           ); setDiffGroupCount             (remote.mCommSetting.mGroupCount            != pProductSP->mCurrPD.mDspForm.mCommSetting.mGroupCount           );
        setGroupMotion                (remote.mCommSetting.mGroupMotion          ); setDiffGroupMotion            (remote.mCommSetting.mGroupMotion           != pProductSP->mCurrPD.mDspForm.mCommSetting.mGroupMotion          );
        setGroupLamp                  (remote.mCommSetting.mGroupLamp            ); setDiffGroupLamp              (remote.mCommSetting.mGroupLamp             != pProductSP->mCurrPD.mDspForm.mCommSetting.mGroupLamp            );
        setGroupBuzzer                (remote.mCommSetting.mGroupBuzzer          ); setDiffGroupBuzzer            (remote.mCommSetting.mGroupBuzzer           != pProductSP->mCurrPD.mDspForm.mCommSetting.mGroupBuzzer          );
        setUnderWeight                (remote.mWCSetting.mUnderWeight            ); setDiffUnderWeight            (remote.mWCSetting.mUnderWeight             != pProductSP->mCurrPD.mDspForm.mWCSetting.mUnderWeight            );
        setUnderWarningWeight         (remote.mWCSetting.mUnderWarningWeight     ); setDiffUnderWarningWeight     (remote.mWCSetting.mUnderWarningWeight      != pProductSP->mCurrPD.mDspForm.mWCSetting.mUnderWarningWeight     );
        setNormalWeight               (remote.mWCSetting.mNormalWeight           ); setDiffNormalWeight           (remote.mWCSetting.mNormalWeight            != pProductSP->mCurrPD.mDspForm.mWCSetting.mNormalWeight           );
        setOverWarningWeight          (remote.mWCSetting.mOverWarningWeight      ); setDiffOverWarningWeight      (remote.mWCSetting.mOverWarningWeight       != pProductSP->mCurrPD.mDspForm.mWCSetting.mOverWarningWeight      );
        setOverWeight                 (remote.mWCSetting.mOverWeight             ); setDiffOverWeight             (remote.mWCSetting.mOverWeight              != pProductSP->mCurrPD.mDspForm.mWCSetting.mOverWeight             );
        setTareWeight                 (remote.mWCSetting.mTareWeight             ); setDiffTareWeight             (remote.mWCSetting.mTareWeight              != pProductSP->mCurrPD.mDspForm.mWCSetting.mTareWeight             );
        setWCOverMotion               (remote.mWCSetting.mOverMotion             ); setDiffWCOverMotion           (remote.mWCSetting.mOverMotion              != pProductSP->mCurrPD.mDspForm.mWCSetting.mOverMotion             );
        setWCUnderMotion              (remote.mWCSetting.mUnderMotion            ); setDiffWCUnderMotion          (remote.mWCSetting.mUnderMotion             != pProductSP->mCurrPD.mDspForm.mWCSetting.mUnderMotion            );
        setWCEtcMotion                (remote.mWCSetting.mEtcMotion              ); setDiffWCEtcMotion            (remote.mWCSetting.mEtcMotion               != pProductSP->mCurrPD.mDspForm.mWCSetting.mEtcMotion              );
        setWCEnableEtcError           (remote.mWCSetting.mEnableEtcError         ); setDiffWCEnableEtcError       (remote.mWCSetting.mEnableEtcError          != pProductSP->mCurrPD.mDspForm.mWCSetting.mEnableEtcError         );
        setDynamicFactor              (remote.mWCSetting.mDynamicFactor          ); setDiffDynamicFactor          (remote.mWCSetting.mDynamicFactor           != pProductSP->mCurrPD.mDspForm.mWCSetting.mDynamicFactor          );
        setWCNGLamp                   (remote.mWCSetting.mNGLamp                 ); setDiffWCNGLamp               (remote.mWCSetting.mNGLamp                  != pProductSP->mCurrPD.mDspForm.mWCSetting.mNGLamp                 );
        setWCNGBuzzer                 (remote.mWCSetting.mNGBuzzer               ); setDiffWCNGBuzzer             (remote.mWCSetting.mNGBuzzer                != pProductSP->mCurrPD.mDspForm.mWCSetting.mNGBuzzer               );
        setAutoSetting                (remote.mWCSetting.mAutoSetting            ); setDiffAutoSetting            (remote.mWCSetting.mAutoSetting             != pProductSP->mCurrPD.mDspForm.mWCSetting.mAutoSetting            );
        setFilterCoefficient          (remote.mWCSetting.mFilterCoefficient      ); setDiffFilterCoefficient      (remote.mWCSetting.mFilterCoefficient       != pProductSP->mCurrPD.mDspForm.mWCSetting.mFilterCoefficient      );
        setMeasureCueSign             (remote.mWCSetting.mMeasureCueSign         ); setDiffMeasureCueSign         (remote.mWCSetting.mMeasureCueSign          != pProductSP->mCurrPD.mDspForm.mWCSetting.mMeasureCueSign         );
        setMeasureSection             (remote.mWCSetting.mMeasureSection         ); setDiffMeasureSection         (remote.mWCSetting.mMeasureSection          != pProductSP->mCurrPD.mDspForm.mWCSetting.mMeasureSection         );
        setMDSenstivity               (remote.mMDSetting.mSenstivity             ); setDiffMDSenstivity           (remote.mMDSetting.mSenstivity              != pProductSP->mCurrPD.mDspForm.mMDSetting.mSenstivity             );
        setMDNGMotion                 (remote.mMDSetting.mNGMotion               ); setDiffMDNGMotion             (remote.mMDSetting.mNGMotion                != pProductSP->mCurrPD.mDspForm.mMDSetting.mNGMotion               );
        setMDNGLamp                   (remote.mMDSetting.mNGLamp                 ); setDiffMDNGLamp               (remote.mMDSetting.mNGLamp                  != pProductSP->mCurrPD.mDspForm.mMDSetting.mNGLamp                 );
        setMDNGBuzzer                 (remote.mMDSetting.mNGBuzzer               ); setDiffMDNGBuzzer             (remote.mMDSetting.mNGBuzzer                != pProductSP->mCurrPD.mDspForm.mMDSetting.mNGBuzzer               );
        qDebug() <<"Remote mCommSetting.mProductNum             = " << remote.mCommSetting.mProductNum            <<"Local mCommSetting.mProductNum            = " << pProductSP->mCurrPD.mDspForm.mCommSetting.mProductNum           ;
        qDebug() <<"Remote mCommSetting.mLength                 = " << remote.mCommSetting.mLength                <<"Local mCommSetting.mLength                = " << pProductSP->mCurrPD.mDspForm.mCommSetting.mLength               ;
        qDebug() <<"Remote mCommSetting.mSpeed                  = " << remote.mCommSetting.mSpeed                 <<"Local mCommSetting.mSpeed                 = " << pProductSP->mCurrPD.mDspForm.mCommSetting.mSpeed                ;
        qDebug() <<"Remote mCommSetting.mMotorAccelerationTime  = " << remote.mCommSetting.mMotorAccelerationTime <<"Local mCommSetting.mMotorAccelerationTime = " << pProductSP->mCurrPD.mDspForm.mCommSetting.mMotorAccelerationTime;
        qDebug() <<"Remote mCommSetting.mMotorDecelerationTime  = " << remote.mCommSetting.mMotorDecelerationTime <<"Local mCommSetting.mMotorDecelerationTime = " << pProductSP->mCurrPD.mDspForm.mCommSetting.mMotorDecelerationTime;
        qDebug() <<"Remote mCommSetting.mGroupCount             = " << remote.mCommSetting.mGroupCount            <<"Local mCommSetting.mGroupCount            = " << pProductSP->mCurrPD.mDspForm.mCommSetting.mGroupCount           ;
        qDebug() <<"Remote mCommSetting.mGroupMotion            = " << remote.mCommSetting.mGroupMotion           <<"Local mCommSetting.mGroupMotion           = " << pProductSP->mCurrPD.mDspForm.mCommSetting.mGroupMotion          ;
        qDebug() <<"Remote mCommSetting.mGroupLamp              = " << remote.mCommSetting.mGroupLamp             <<"Local mCommSetting.mGroupLamp             = " << pProductSP->mCurrPD.mDspForm.mCommSetting.mGroupLamp            ;
        qDebug() <<"Remote mCommSetting.mGroupBuzzer            = " << remote.mCommSetting.mGroupBuzzer           <<"Local mCommSetting.mGroupBuzzer           = " << pProductSP->mCurrPD.mDspForm.mCommSetting.mGroupBuzzer          ;
        qDebug() <<"Remote mWCSetting.mUnderWeight              = " << remote.mWCSetting.mUnderWeight             <<"Local mWCSetting.mUnderWeight             = " << pProductSP->mCurrPD.mDspForm.mWCSetting.mUnderWeight            ;
        qDebug() <<"Remote mWCSetting.mUnderWarningWeight       = " << remote.mWCSetting.mUnderWarningWeight      <<"Local mWCSetting.mUnderWarningWeight      = " << pProductSP->mCurrPD.mDspForm.mWCSetting.mUnderWarningWeight     ;
        qDebug() <<"Remote mWCSetting.mNormalWeight             = " << remote.mWCSetting.mNormalWeight            <<"Local mWCSetting.mNormalWeight            = " << pProductSP->mCurrPD.mDspForm.mWCSetting.mNormalWeight           ;
        qDebug() <<"Remote mWCSetting.mOverWarningWeight        = " << remote.mWCSetting.mOverWarningWeight       <<"Local mWCSetting.mOverWarningWeight       = " << pProductSP->mCurrPD.mDspForm.mWCSetting.mOverWarningWeight      ;
        qDebug() <<"Remote mWCSetting.mOverWeight               = " << remote.mWCSetting.mOverWeight              <<"Local mWCSetting.mOverWeight              = " << pProductSP->mCurrPD.mDspForm.mWCSetting.mOverWeight             ;
        qDebug() <<"Remote mWCSetting.mTareWeight               = " << remote.mWCSetting.mTareWeight              <<"Local mWCSetting.mTareWeight              = " << pProductSP->mCurrPD.mDspForm.mWCSetting.mTareWeight             ;
        qDebug() <<"Remote mWCSetting.mOverMotion               = " << remote.mWCSetting.mOverMotion              <<"Local mWCSetting.mOverMotion              = " << pProductSP->mCurrPD.mDspForm.mWCSetting.mOverMotion             ;
        qDebug() <<"Remote mWCSetting.mUnderMotion              = " << remote.mWCSetting.mUnderMotion             <<"Local mWCSetting.mUnderMotion             = " << pProductSP->mCurrPD.mDspForm.mWCSetting.mUnderMotion            ;
        qDebug() <<"Remote mWCSetting.mEtcMotion                = " << remote.mWCSetting.mEtcMotion               <<"Local mWCSetting.mEtcMotion               = " << pProductSP->mCurrPD.mDspForm.mWCSetting.mEtcMotion              ;
        qDebug() <<"Remote.mWCSetting.mNGLamp                   = " << remote.mWCSetting.mNGLamp                  <<"Local mWCSetting.mNGLamp                  = " << pProductSP->mCurrPD.mDspForm.mWCSetting.mNGLamp                 ;
        qDebug() <<"Remote.mWCSetting.mNGBuzzer                 = " << remote.mWCSetting.mNGBuzzer                <<"Local mWCSetting.mNGBuzzer                = " << pProductSP->mCurrPD.mDspForm.mWCSetting.mNGBuzzer               ;
        qDebug() <<"Remote.mWCSetting.mAutoSetting              = " << remote.mWCSetting.mAutoSetting             <<"Local mWCSetting.mAutoSetting             = " << pProductSP->mCurrPD.mDspForm.mWCSetting.mAutoSetting            ;
        qDebug() <<"Remote.mWCSetting.mFilterCoefficient        = " << remote.mWCSetting.mFilterCoefficient       <<"Local mWCSetting.mFilterCoefficient       = " << pProductSP->mCurrPD.mDspForm.mWCSetting.mFilterCoefficient      ;
        qDebug() <<"Remote.mWCSetting.mMeasureCueSign           = " << remote.mWCSetting.mMeasureCueSign          <<"Local mWCSetting.mMeasureCueSign          = " << pProductSP->mCurrPD.mDspForm.mWCSetting.mMeasureCueSign         ;
        qDebug() <<"Remote.mWCSetting.mMeasureSection           = " << remote.mWCSetting.mMeasureSection          <<"Local mWCSetting.mMeasureSection          = " << pProductSP->mCurrPD.mDspForm.mWCSetting.mMeasureSection         ;
        qDebug() <<"Remote mWCSetting.mEnableEtcError           = " << remote.mWCSetting.mEnableEtcError          <<"Local mWCSetting.mEnableEtcError          = " << pProductSP->mCurrPD.mDspForm.mWCSetting.mEnableEtcError         ;
        qDebug() <<"Remote mWCSetting.mDynamicFactor            = " << remote.mWCSetting.mDynamicFactor           <<"Local mWCSetting.mDynamicFactor           = " << pProductSP->mCurrPD.mDspForm.mWCSetting.mDynamicFactor          ;
        qDebug() <<"Remote mMDSetting.mSenstivity               = " << remote.mMDSetting.mSenstivity              <<"Local mMDSetting.mSenstivity              = " << pProductSP->mCurrPD.mDspForm.mMDSetting.mSenstivity             ;
        qDebug() <<"Remote mMDSetting.mNGMotion                 = " << remote.mMDSetting.mNGMotion                <<"Local mMDSetting.mNGMotion                = " << pProductSP->mCurrPD.mDspForm.mMDSetting.mNGMotion               ;
        qDebug() <<"Remote.mMDSetting.mNGLamp                   = " << remote.mMDSetting.mNGLamp                  <<"Local mMDSetting.mNGLamp                  = " << pProductSP->mCurrPD.mDspForm.mMDSetting.mNGLamp                 ;
        qDebug() <<"Remote.mMDSetting.mNGBuzzer                 = " << remote.mMDSetting.mNGBuzzer                <<"Local mMDSetting.mNGBuzzer                = " << pProductSP->mCurrPD.mDspForm.mMDSetting.mNGBuzzer               ;
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
        setSorter01RunTimeRatio       (remote.mCommSetting.mSorter01RunTimeRatio   ); setDiffSorter01RunTimeRatio   (remote.mCommSetting.mSorter01RunTimeRatio    != pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter01RunTimeRatio   );
        setSorter01OpenTime           (remote.mCommSetting.mSorter01OpenTime       ); setDiffSorter01OpenTime       (remote.mCommSetting.mSorter01OpenTime        != pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter01OpenTime       );
        setSorter02RunTimeRatio       (remote.mCommSetting.mSorter02RunTimeRatio   ); setDiffSorter02RunTimeRatio   (remote.mCommSetting.mSorter02RunTimeRatio    != pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter02RunTimeRatio   );
        setSorter02OpenTime           (remote.mCommSetting.mSorter02OpenTime       ); setDiffSorter02OpenTime       (remote.mCommSetting.mSorter02OpenTime        != pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter02OpenTime       );
        setSorter03RunTimeRatio       (remote.mCommSetting.mSorter03RunTimeRatio   ); setDiffSorter03RunTimeRatio   (remote.mCommSetting.mSorter03RunTimeRatio    != pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter03RunTimeRatio   );
        setSorter03OpenTime           (remote.mCommSetting.mSorter03OpenTime       ); setDiffSorter03OpenTime       (remote.mCommSetting.mSorter03OpenTime        != pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter03OpenTime       );
        setSorter04RunTimeRatio       (remote.mCommSetting.mSorter04RunTimeRatio   ); setDiffSorter04RunTimeRatio   (remote.mCommSetting.mSorter04RunTimeRatio    != pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter04RunTimeRatio   );
        setSorter04OpenTime           (remote.mCommSetting.mSorter04OpenTime       ); setDiffSorter04OpenTime       (remote.mCommSetting.mSorter04OpenTime        != pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter04OpenTime       );
        setDistToSorter01             (remote.mSizeSetting.mDistToSorter01         ); setDiffDistToSorter01         (remote.mSizeSetting.mDistToSorter01          != pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistToSorter01         );
        setDistToSorter02             (remote.mSizeSetting.mDistToSorter02         ); setDiffDistToSorter02         (remote.mSizeSetting.mDistToSorter02          != pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistToSorter02         );
        setDistToSorter03             (remote.mSizeSetting.mDistToSorter03         ); setDiffDistToSorter03         (remote.mSizeSetting.mDistToSorter03          != pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistToSorter03         );
        setDistToSorter04             (remote.mSizeSetting.mDistToSorter04         ); setDiffDistToSorter04         (remote.mSizeSetting.mDistToSorter04          != pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistToSorter04         );
        setSensorLength               (remote.mSizeSetting.mSensorLength           ); setDiffSensorLength           (remote.mSizeSetting.mSensorLength            != pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mSensorLength           );
        setMDPhotoIsOn                (remote.mMDSetting.mPhotoIsOn==1?true:false  ); setDiffMDPhotoIsOn            (remote.mMDSetting.mPhotoIsOn                 != pLSettingSP->mDevSetting.mDspForm.mMDSetting.mPhotoIsOn                );
        setWCPhotoIsOn                (remote.mWCSetting.mPhotoIsOn==1?true:false  ); setDiffWCPhotoIsOn            (remote.mWCSetting.mPhotoIsOn                 != pLSettingSP->mDevSetting.mDspForm.mWCSetting.mPhotoIsOn                );
        setStaticFactor               (remote.mWCSetting.mStaticFactor             ); setDiffStaticFactor           (remote.mWCSetting.mStaticFactor              != pLSettingSP->mDevSetting.mDspForm.mWCSetting.mStaticFactor             );
        setScaler                     (remote.mWCSetting.mScaler                   ); setDiffScaler                 (remote.mWCSetting.mScaler                    != pLSettingSP->mDevSetting.mDspForm.mWCSetting.mScaler                   );
        setDisplayStability           (remote.mWCSetting.mDisplayStability         ); setDiffDisplayStability       (remote.mWCSetting.mDisplayStability          != pLSettingSP->mDevSetting.mDspForm.mWCSetting.mDisplayStability         );
        //setMeasureCueSign             (remote.mWCSetting.mMeasureCueSign           ); setDiffMeasureCueSign         (remote.mWCSetting.mMeasureCueSign            != pLSettingSP->mDevSetting.mDspForm.mWCSetting.mMeasureCueSign           );
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
        setRefVoltage                 (remote.mWCSetting.mRefVoltage               ); setDiffRefVoltage             (remote.mWCSetting.mRefVoltage                != pLSettingSP->mDevSetting.mDspForm.mWCSetting.mRefVoltage               );
        setGraphPointCnt              (remote.mWCSetting.mGraphPointCnt            ); setDiffGraphPointCnt          (remote.mWCSetting.mGraphPointCnt             != pLSettingSP->mDevSetting.mDspForm.mWCSetting.mGraphPointCnt            );
        setSensorCnt                  (remote.mMDSetting.mSensorCnt                ); setDiffSensorCnt              (remote.mMDSetting.mSensorCnt                 != pLSettingSP->mDevSetting.mDspForm.mMDSetting.mSensorCnt                );

        qDebug() <<"Remote mCommSetting.mLampTime                 = " << remote.mCommSetting.mLampTime                <<"Local mCommSetting.mLampTime                 = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mLampTime               ;
        qDebug() <<"Remote mCommSetting.mBuzzerTime               = " << remote.mCommSetting.mBuzzerTime              <<"Local mCommSetting.mBuzzerTime               = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mBuzzerTime             ;
        qDebug() <<"Remote mCommSetting.mSpeedConverter           = " << remote.mCommSetting.mSpeedConverter          <<"Local mCommSetting.mSpeedConverter           = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSpeedConverter         ;
        qDebug() <<"Remote mCommSetting.mMotorDirection           = " << remote.mCommSetting.mMotorDirection          <<"Local mCommSetting.mMotorDirection           = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMotorDirection         ;
        qDebug() <<"Remote mCommSetting.mMotorType                = " << remote.mCommSetting.mMotorType               <<"Local mCommSetting.mMotorType                = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMotorType              ;
        qDebug() <<"Remote mCommSetting.mMachineMode              = " << remote.mCommSetting.mMachineMode             <<"Local mCommSetting.mMachineMode              = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMachineMode            ;
        qDebug() <<"Remote mCommSetting.mMotorMDRatio             = " << remote.mCommSetting.mMotorMDRatio            <<"Local mCommSetting.mMotorMDRatio             = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMotorMDRatio           ;
        qDebug() <<"Remote mCommSetting.mMotorWCRatio             = " << remote.mCommSetting.mMotorWCRatio            <<"Local mCommSetting.mMotorWCRatio             = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMotorWCRatio           ;
        qDebug() <<"Remote mCommSetting.mMotorRJRatio             = " << remote.mCommSetting.mMotorRJRatio            <<"Local mCommSetting.mMotorRJRatio             = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMotorRJRatio           ;
        qDebug() <<"Remote mCommSetting.mSorter01RunTimeRatio     = " << remote.mCommSetting.mSorter01RunTimeRatio    <<"Local mCommSetting.mSorter01RunTimeRatio     = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter01RunTimeRatio   ;
        qDebug() <<"Remote mCommSetting.mSorter01OpenTime         = " << remote.mCommSetting.mSorter01OpenTime        <<"Local mCommSetting.mSorter01OpenTime         = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter01OpenTime       ;
        qDebug() <<"Remote mCommSetting.mSorter02RunTimeRatio     = " << remote.mCommSetting.mSorter02RunTimeRatio    <<"Local mCommSetting.mSorter02RunTimeRatio     = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter02RunTimeRatio   ;
        qDebug() <<"Remote mCommSetting.mSorter02OpenTime         = " << remote.mCommSetting.mSorter02OpenTime        <<"Local mCommSetting.mSorter02OpenTime         = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter02OpenTime       ;
        qDebug() <<"Remote mCommSetting.mSorter03RunTimeRatio     = " << remote.mCommSetting.mSorter03RunTimeRatio    <<"Local mCommSetting.mSorter03RunTimeRatio     = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter03RunTimeRatio   ;
        qDebug() <<"Remote mCommSetting.mSorter03OpenTime         = " << remote.mCommSetting.mSorter03OpenTime        <<"Local mCommSetting.mSorter03OpenTime         = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter03OpenTime       ;
        qDebug() <<"Remote mCommSetting.mSorter04RunTimeRatio     = " << remote.mCommSetting.mSorter04RunTimeRatio    <<"Local mCommSetting.mSorter04RunTimeRatio     = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter04RunTimeRatio   ;
        qDebug() <<"Remote mCommSetting.mSorter04OpenTime         = " << remote.mCommSetting.mSorter04OpenTime        <<"Local mCommSetting.mSorter04OpenTime         = " << pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter04OpenTime       ;
        qDebug() <<"Remote mSizeSetting.mDistToSorter01           = " << remote.mSizeSetting.mDistToSorter01          <<"Local mSizeSetting.mDistToSorter01           = " << pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistToSorter01         ;
        qDebug() <<"Remote mSizeSetting.mDistToSorter02           = " << remote.mSizeSetting.mDistToSorter02          <<"Local mSizeSetting.mDistToSorter02           = " << pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistToSorter02         ;
        qDebug() <<"Remote mSizeSetting.mDistToSorter03           = " << remote.mSizeSetting.mDistToSorter03          <<"Local mSizeSetting.mDistToSorter03           = " << pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistToSorter03         ;
        qDebug() <<"Remote mSizeSetting.mDistToSorter04           = " << remote.mSizeSetting.mDistToSorter04          <<"Local mSizeSetting.mDistToSorter04           = " << pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistToSorter04         ;
        qDebug() <<"Remote mSizeSetting.mSensorLength             = " << remote.mSizeSetting.mSensorLength            <<"Local mSizeSetting.mSensorLength             = " << pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mSensorLength           ;
        qDebug() <<"Remote mMDSetting.mPhotoIsOn                  = " << remote.mMDSetting.mPhotoIsOn                 <<"Local mMDSetting.mPhotoIsOn                  = " << pLSettingSP->mDevSetting.mDspForm.mMDSetting.mPhotoIsOn                ;
        qDebug() <<"Remote mWCSetting.mPhotoIsOn                  = " << remote.mWCSetting.mPhotoIsOn                 <<"Local mWCSetting.mPhotoIsOn                  = " << pLSettingSP->mDevSetting.mDspForm.mWCSetting.mPhotoIsOn                ;
        qDebug() <<"Remote mWCSetting.mStaticFactor               = " << remote.mWCSetting.mStaticFactor              <<"Local mWCSetting.mStaticFactor               = " << pLSettingSP->mDevSetting.mDspForm.mWCSetting.mStaticFactor             ;
        qDebug() <<"Remote mWCSetting.mScaler                     = " << remote.mWCSetting.mScaler                    <<"Local mWCSetting.mScaler                     = " << pLSettingSP->mDevSetting.mDspForm.mWCSetting.mScaler                   ;
        qDebug() <<"Remote mWCSetting.mDisplayStability           = " << remote.mWCSetting.mDisplayStability          <<"Local mWCSetting.mDisplayStability           = " << pLSettingSP->mDevSetting.mDspForm.mWCSetting.mDisplayStability         ;
        //qDebug() <<"Remote mWCSetting.mMeasureCueSign             = " << remote.mWCSetting.mMeasureCueSign            <<"Local mWCSetting.mMeasureCueSign             = " << pLSettingSP->mDevSetting.mDspForm.mWCSetting.mMeasureCueSign           ;
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
        qDebug() <<"Remote mWCSetting.mRefVoltage                 = " << remote.mWCSetting.mRefVoltage                <<"Local mWCSetting.mRefVoltage                 = " << pLSettingSP->mDevSetting.mDspForm.mWCSetting.mRefVoltage               ;
        qDebug() <<"Remote mWCSetting.mGraphPointCnt              = " << remote.mWCSetting.mGraphPointCnt             <<"Local mWCSetting.mGraphPointCnt              = " << pLSettingSP->mDevSetting.mDspForm.mWCSetting.mGraphPointCnt            ;
        qDebug() <<"Remote mMDSetting.mSensorCnt                  = " << remote.mMDSetting.mSensorCnt                 <<"Local mMDSetting.mSensorCnt                  = " << pLSettingSP->mDevSetting.mDspForm.mMDSetting.mSensorCnt                ;
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
