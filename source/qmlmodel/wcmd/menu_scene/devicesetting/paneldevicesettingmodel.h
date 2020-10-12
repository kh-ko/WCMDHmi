#ifndef PANELDEVICESETTINGMODEL_H
#define PANELDEVICESETTINGMODEL_H

#include <QObject>
#include "source/service/coreservice.h"

class PanelDeviceSettingModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int     language                          READ getLanguage                      NOTIFY  signalEventChangedLanguage                  )
    Q_PROPERTY(QString password                          READ getPassword                      NOTIFY  signalEventChangedPassword                  )
    Q_PROPERTY(QString newPassword                       READ getNewPassword                   NOTIFY  signalEventChangedNewPassword               )
    Q_PROPERTY(QString confirmPassword                   READ getConfirmPassword               NOTIFY  signalEventChangedConfirmPassword           )
    Q_PROPERTY(bool    isDayMode                         READ getIsDayMode                     NOTIFY  signalEventChangedIsDayMode                 )
    Q_PROPERTY(bool    isDebugMode                       READ getIsDebugMode                   NOTIFY  signalEventChangedIsDebugMode               )
    Q_PROPERTY(quint32 lampTime                          READ getLampTime                      NOTIFY  signalEventChangedLampTime                  )
    Q_PROPERTY(quint32 buzzerTime                        READ getBuzzerTime                    NOTIFY  signalEventChangedBuzzerTime                )
    Q_PROPERTY(quint32 speedConverter                    READ getSpeedConverter                NOTIFY  signalEventChangedSpeedConverter            )
    Q_PROPERTY(quint16 motorDirection                    READ getMotorDirection                NOTIFY  signalEventChangedMotorDirection            )
    Q_PROPERTY(quint32 rejectorRunTimeRatio              READ getRejectorRunTimeRatio          NOTIFY  signalEventChangedRejectorRunTimeRatio      )
    Q_PROPERTY(quint32 displayStability                  READ getDisplayStability              NOTIFY  signalEventChangedDisplayStability          )
    Q_PROPERTY(quint32 measureCueSign                    READ getMeasureCueSign                NOTIFY  signalEventChangedMeasureCueSign            )
    Q_PROPERTY(quint32 minStaticWeight                   READ getMinStaticWeight               NOTIFY  signalEventChangedMinStaticWeight           )
    Q_PROPERTY(quint32 minDynamicWeight                  READ getMinDynamicWeight              NOTIFY  signalEventChangedMinDynamicWeight          )
    Q_PROPERTY(quint32 scaler                            READ getScaler                        NOTIFY  signalEventChangedScaler                    )
    Q_PROPERTY(quint32 staticFactor                      READ getStaticFactor                  NOTIFY  signalEventChangedStaticFactor              )
    Q_PROPERTY(quint32 dynamicFactor                     READ getDynamicFactor                 NOTIFY  signalEventChangedDynamicFactor             )
    Q_PROPERTY(quint32 standardWeight                    READ getStandardWeight                NOTIFY  signalEventChangedStandardWeight            )
    Q_PROPERTY(quint32 refWeight                         READ getRefWeight                     NOTIFY  signalEventChangedRefWeight                 )
    Q_PROPERTY(bool    wcPhotoOn                         READ getWCPhotoOn                     NOTIFY  signalEventChangedWCPhotoOn                 )
    Q_PROPERTY(quint16 mode                              READ getMode                          NOTIFY  signalEventChangedMode                      )
    Q_PROPERTY(quint32 detectDetectTime                  READ getDetectDetectTime              NOTIFY  signalEventChangedDetectDetectTime          )
    Q_PROPERTY(quint32 runDetectTime                     READ getRunDetectTime                 NOTIFY  signalEventChangedRunDetectTime             )
    Q_PROPERTY(quint32 signalDelayTime                   READ getSignalDelayTime               NOTIFY  signalEventChangedSignalDelayTime           )
    Q_PROPERTY(bool    mdPhotoOn                         READ getMDPhotoOn                     NOTIFY  signalEventChangedMDPhotoOn                 )
    Q_PROPERTY(quint16 sensorCnt                         READ getSensorCnt                     NOTIFY  signalEventChangedSensorCnt                 )
    Q_PROPERTY(quint16 simpleSens01                      READ getSimpleSens01                  NOTIFY  signalEventChangedSimpleSens01              )
    Q_PROPERTY(quint16 simpleSens02                      READ getSimpleSens02                  NOTIFY  signalEventChangedSimpleSens02              )
    Q_PROPERTY(quint16 simpleSens03                      READ getSimpleSens03                  NOTIFY  signalEventChangedSimpleSens03              )
    Q_PROPERTY(quint16 simpleSens04                      READ getSimpleSens04                  NOTIFY  signalEventChangedSimpleSens04              )
    Q_PROPERTY(quint16 simpleSens05                      READ getSimpleSens05                  NOTIFY  signalEventChangedSimpleSens05              )

    Q_PROPERTY(bool    isEditLanguage                    READ getIsEditLanguage                        NOTIFY  signalEventChangedIsEditLanguage                   )
    Q_PROPERTY(bool    isEditPassword                    READ getIsEditPassword                        NOTIFY  signalEventChangedIsEditPassword                   )
    Q_PROPERTY(bool    isEditNewPassword                 READ getIsEditNewPassword                     NOTIFY  signalEventChangedIsEditNewPassword                )
    Q_PROPERTY(bool    isEditConfirmPassword             READ getIsEditConfirmPassword                 NOTIFY  signalEventChangedIsEditConfirmPassword            )
    Q_PROPERTY(bool    isEditIsDayMode                   READ getIsEditIsDayMode                       NOTIFY  signalEventChangedIsEditIsDayMode                  )
    Q_PROPERTY(bool    isEditIsDebugMode                 READ getIsEditIsDebugMode                     NOTIFY  signalEventChangedIsEditIsDebugMode                )
    Q_PROPERTY(bool    isEditLampTime                    READ getIsEditLampTime                        NOTIFY  signalEventChangedIsEditLampTime                   )
    Q_PROPERTY(bool    isEditBuzzerTime                  READ getIsEditBuzzerTime                      NOTIFY  signalEventChangedIsEditBuzzerTime                 )
    Q_PROPERTY(bool    isEditSpeedConverter              READ getIsEditSpeedConverter                  NOTIFY  signalEventChangedIsEditSpeedConverter             )
    Q_PROPERTY(bool    isEditMotorDirection              READ getIsEditMotorDirection                  NOTIFY  signalEventChangedIsEditMotorDirection             )
    Q_PROPERTY(bool    isEditRejectorRunTimeRatio        READ getIsEditRejectorRunTimeRatio            NOTIFY  signalEventChangedIsEditRejectorRunTimeRatio       )
    Q_PROPERTY(bool    isEditDisplayStability            READ getIsEditDisplayStability                NOTIFY  signalEventChangedIsEditDisplayStability           )
    Q_PROPERTY(bool    isEditMeasureCueSign              READ getIsEditMeasureCueSign                  NOTIFY  signalEventChangedIsEditMeasureCueSign             )
    Q_PROPERTY(bool    isEditMinStaticWeight             READ getIsEditMinStaticWeight                 NOTIFY  signalEventChangedIsEditMinStaticWeight            )
    Q_PROPERTY(bool    isEditMinDynamicWeight            READ getIsEditMinDynamicWeight                NOTIFY  signalEventChangedIsEditMinDynamicWeight           )
    Q_PROPERTY(bool    isEditScaler                      READ getIsEditScaler                          NOTIFY  signalEventChangedIsEditScaler                     )
    Q_PROPERTY(bool    isEditStaticFactor                READ getIsEditStaticFactor                    NOTIFY  signalEventChangedIsEditStaticFactor               )
    Q_PROPERTY(bool    isEditDynamicFactor               READ getIsEditDynamicFactor                   NOTIFY  signalEventChangedIsEditDynamicFactor              )
    Q_PROPERTY(bool    isEditStandardWeight              READ getIsEditStandardWeight                  NOTIFY  signalEventChangedIsEditStandardWeight             )
    Q_PROPERTY(bool    isEditRefWeight                   READ getIsEditRefWeight                       NOTIFY  signalEventChangedIsEditRefWeight                  )
    Q_PROPERTY(bool    isEditWCPhotoOn                   READ getIsEditWCPhotoOn                       NOTIFY  signalEventChangedIsEditWCPhotoOn                  )
    Q_PROPERTY(bool    isEditMode                        READ getIsEditMode                            NOTIFY  signalEventChangedIsEditMode                       )
    Q_PROPERTY(bool    isEditDetectDetectTime            READ getIsEditDetectDetectTime                NOTIFY  signalEventChangedIsEditDetectDetectTime           )
    Q_PROPERTY(bool    isEditRunDetectTime               READ getIsEditRunDetectTime                   NOTIFY  signalEventChangedIsEditRunDetectTime              )
    Q_PROPERTY(bool    isEditSignalDelayTime             READ getIsEditSignalDelayTime                 NOTIFY  signalEventChangedIsEditSignalDelayTime            )
    Q_PROPERTY(bool    isEditMDPhotoOn                   READ getIsEditMDPhotoOn                       NOTIFY  signalEventChangedIsEditMDPhotoOn                  )
    Q_PROPERTY(bool    isEditSensorCnt                   READ getIsEditSensorCnt                       NOTIFY  signalEventChangedIsEditSensorCnt                  )
    Q_PROPERTY(bool    isEditSimpleSens01                READ getIsEditSimpleSens01                    NOTIFY  signalEventChangedIsEditSimpleSens01               )
    Q_PROPERTY(bool    isEditSimpleSens02                READ getIsEditSimpleSens02                    NOTIFY  signalEventChangedIsEditSimpleSens02               )
    Q_PROPERTY(bool    isEditSimpleSens03                READ getIsEditSimpleSens03                    NOTIFY  signalEventChangedIsEditSimpleSens03               )
    Q_PROPERTY(bool    isEditSimpleSens04                READ getIsEditSimpleSens04                    NOTIFY  signalEventChangedIsEditSimpleSens04               )
    Q_PROPERTY(bool    isEditSimpleSens05                READ getIsEditSimpleSens05                    NOTIFY  signalEventChangedIsEditSimpleSens05               )

public:
    CoreService * mpCoreService;

    int      mLanguage                      ;
    QString  mPassword                      ;
    QString  mNewPassword                   ;
    QString  mConfirmPassword               ;
    bool     mIsDayMode                     ;
    bool     mIsDebugMode                   ;
    quint32  mLampTime                      ;
    quint32  mBuzzerTime                    ;
    quint32  mSpeedConverter                ;
    quint16  mMotorDirection                ;
    quint32  mRejectorRunTimeRatio          ;
    quint32  mDisplayStability              ;
    quint32  mMeasureCueSign                ;
    quint32  mMinStaticWeight               ;
    quint32  mMinDynamicWeight              ;
    quint32  mScaler                        ;
    quint32  mStaticFactor                  ;
    quint32  mDynamicFactor                 ;
    quint32  mStandardWeight                ;
    quint32  mRefWeight                     ;
    bool     mWCPhotoOn                     ;
    quint16  mMode                          ;
    quint32  mDetectDetectTime              ;
    quint32  mRunDetectTime                 ;
    quint32  mSignalDelayTime               ;
    bool     mMDPhotoOn                     ;
    quint16  mSensorCnt                     ;
    quint16  mSimpleSens01                  ;
    quint16  mSimpleSens02                  ;
    quint16  mSimpleSens03                  ;
    quint16  mSimpleSens04                  ;
    quint16  mSimpleSens05                  ;

    bool     mIsEditLanguage                ;
    bool     mIsEditPassword                ;
    bool     mIsEditNewPassword             ;
    bool     mIsEditConfirmPassword         ;
    bool     mIsEditIsDayMode               ;
    bool     mIsEditIsDebugMode             ;
    bool     mIsEditLampTime                ;
    bool     mIsEditBuzzerTime              ;
    bool     mIsEditSpeedConverter          ;
    bool     mIsEditMotorDirection          ;
    bool     mIsEditRejectorRunTimeRatio    ;
    bool     mIsEditDisplayStability        ;
    bool     mIsEditMeasureCueSign          ;
    bool     mIsEditMinStaticWeight         ;
    bool     mIsEditMinDynamicWeight        ;
    bool     mIsEditScaler                  ;
    bool     mIsEditStaticFactor            ;
    bool     mIsEditDynamicFactor           ;
    bool     mIsEditStandardWeight          ;
    bool     mIsEditRefWeight               ;
    bool     mIsEditWCPhotoOn               ;
    bool     mIsEditMode                    ;
    bool     mIsEditDetectDetectTime        ;
    bool     mIsEditRunDetectTime           ;
    bool     mIsEditSignalDelayTime         ;
    bool     mIsEditMDPhotoOn               ;
    bool     mIsEditSensorCnt               ;
    bool     mIsEditSimpleSens01            ;
    bool     mIsEditSimpleSens02            ;
    bool     mIsEditSimpleSens03            ;
    bool     mIsEditSimpleSens04            ;
    bool     mIsEditSimpleSens05            ;

    int      getLanguage                     (){ return mLanguage                      ;}
    QString  getPassword                     (){ return mPassword                      ;}
    QString  getNewPassword                  (){ return mNewPassword                   ;}
    QString  getConfirmPassword              (){ return mConfirmPassword               ;}
    bool     getIsDayMode                    (){ return mIsDayMode                     ;}
    bool     getIsDebugMode                  (){ return mIsDebugMode                   ;}
    quint32  getLampTime                     (){ return mLampTime                      ;}
    quint32  getBuzzerTime                   (){ return mBuzzerTime                    ;}
    quint32  getSpeedConverter               (){ return mSpeedConverter                ;}
    quint16  getMotorDirection               (){ return mMotorDirection                ;}
    quint32  getRejectorRunTimeRatio         (){ return mRejectorRunTimeRatio          ;}
    quint32  getDisplayStability             (){ return mDisplayStability              ;}
    quint32  getMeasureCueSign               (){ return mMeasureCueSign                ;}
    quint32  getMinStaticWeight              (){ return mMinStaticWeight               ;}
    quint32  getMinDynamicWeight             (){ return mMinDynamicWeight              ;}
    quint32  getScaler                       (){ return mScaler                        ;}
    quint32  getStaticFactor                 (){ return mStaticFactor                  ;}
    quint32  getDynamicFactor                (){ return mDynamicFactor                 ;}
    quint32  getStandardWeight               (){ return mStandardWeight                ;}
    quint32  getRefWeight                    (){ return mRefWeight                     ;}
    bool     getWCPhotoOn                    (){ return mWCPhotoOn                     ;}
    quint16  getMode                         (){ return mMode                          ;}
    quint32  getDetectDetectTime             (){ return mDetectDetectTime              ;}
    quint32  getRunDetectTime                (){ return mRunDetectTime                 ;}
    quint32  getSignalDelayTime              (){ return mSignalDelayTime               ;}
    bool     getMDPhotoOn                    (){ return mMDPhotoOn                     ;}
    quint16  getSensorCnt                    (){ return mSensorCnt                     ;}
    quint16  getSimpleSens01                 (){ return mSimpleSens01                  ;}
    quint16  getSimpleSens02                 (){ return mSimpleSens02                  ;}
    quint16  getSimpleSens03                 (){ return mSimpleSens03                  ;}
    quint16  getSimpleSens04                 (){ return mSimpleSens04                  ;}
    quint16  getSimpleSens05                 (){ return mSimpleSens05                  ;}

    bool     getIsEditLanguage               (){ return mIsEditLanguage                ;}
    bool     getIsEditPassword               (){ return mIsEditPassword                ;}
    bool     getIsEditNewPassword            (){ return mIsEditNewPassword             ;}
    bool     getIsEditConfirmPassword        (){ return mIsEditConfirmPassword         ;}
    bool     getIsEditIsDayMode              (){ return mIsEditIsDayMode               ;}
    bool     getIsEditIsDebugMode            (){ return mIsEditIsDebugMode             ;}
    bool     getIsEditLampTime               (){ return mIsEditLampTime                ;}
    bool     getIsEditBuzzerTime             (){ return mIsEditBuzzerTime              ;}
    bool     getIsEditSpeedConverter         (){ return mIsEditSpeedConverter          ;}
    bool     getIsEditMotorDirection         (){ return mIsEditMotorDirection          ;}
    bool     getIsEditRejectorRunTimeRatio   (){ return mIsEditRejectorRunTimeRatio    ;}
    bool     getIsEditDisplayStability       (){ return mIsEditDisplayStability        ;}
    bool     getIsEditMeasureCueSign         (){ return mIsEditMeasureCueSign          ;}
    bool     getIsEditMinStaticWeight        (){ return mIsEditMinStaticWeight         ;}
    bool     getIsEditMinDynamicWeight       (){ return mIsEditMinDynamicWeight        ;}
    bool     getIsEditScaler                 (){ return mIsEditScaler                  ;}
    bool     getIsEditStaticFactor           (){ return mIsEditStaticFactor            ;}
    bool     getIsEditDynamicFactor          (){ return mIsEditDynamicFactor           ;}
    bool     getIsEditStandardWeight         (){ return mIsEditStandardWeight          ;}
    bool     getIsEditRefWeight              (){ return mIsEditRefWeight               ;}
    bool     getIsEditWCPhotoOn              (){ return mIsEditWCPhotoOn               ;}
    bool     getIsEditMode                   (){ return mIsEditMode                    ;}
    bool     getIsEditDetectDetectTime       (){ return mIsEditDetectDetectTime        ;}
    bool     getIsEditRunDetectTime          (){ return mIsEditRunDetectTime           ;}
    bool     getIsEditSignalDelayTime        (){ return mIsEditSignalDelayTime         ;}
    bool     getIsEditMDPhotoOn              (){ return mIsEditMDPhotoOn               ;}
    bool     getIsEditSensorCnt              (){ return mIsEditSensorCnt               ;}
    bool     getIsEditSimpleSens01           (){ return mIsEditSimpleSens01            ;}
    bool     getIsEditSimpleSens02           (){ return mIsEditSimpleSens02            ;}
    bool     getIsEditSimpleSens03           (){ return mIsEditSimpleSens03            ;}
    bool     getIsEditSimpleSens04           (){ return mIsEditSimpleSens04            ;}
    bool     getIsEditSimpleSens05           (){ return mIsEditSimpleSens05            ;}

    void setLanguage                     (int      value){ if(value == mLanguage                  ) return; mLanguage                   = value; setIsEditLanguage               (true);  emit signalEventChangedLanguage                  (value);}
    void setPassword                     (QString  value){ if(value == mPassword                  ) return; mPassword                   = value; setIsEditPassword               (true);  emit signalEventChangedPassword                  (value);}
    void setNewPassword                  (QString  value){ if(value == mNewPassword               ) return; mNewPassword                = value; setIsEditNewPassword            (true);  emit signalEventChangedNewPassword               (value);}
    void setConfirmPassword              (QString  value){ if(value == mConfirmPassword           ) return; mConfirmPassword            = value; setIsEditConfirmPassword        (true);  emit signalEventChangedConfirmPassword           (value);}
    void setIsDayMode                    (bool     value){ if(value == mIsDayMode                 ) return; mIsDayMode                  = value; setIsEditIsDayMode              (true);  emit signalEventChangedIsDayMode                 (value);}
    void setIsDebugMode                  (bool     value){ if(value == mIsDebugMode               ) return; mIsDebugMode                = value; setIsEditIsDebugMode            (true);  emit signalEventChangedIsDebugMode               (value);}
    void setLampTime                     (quint32  value){ if(value == mLampTime                  ) return; mLampTime                   = value; setIsEditLampTime               (true);  emit signalEventChangedLampTime                  (value);}
    void setBuzzerTime                   (quint32  value){ if(value == mBuzzerTime                ) return; mBuzzerTime                 = value; setIsEditBuzzerTime             (true);  emit signalEventChangedBuzzerTime                (value);}
    void setSpeedConverter               (quint32  value){ if(value == mSpeedConverter            ) return; mSpeedConverter             = value; setIsEditSpeedConverter         (true);  emit signalEventChangedSpeedConverter            (value);}
    void setMotorDirection               (quint16  value){ if(value == mMotorDirection            ) return; mMotorDirection             = value; setIsEditMotorDirection         (true);  emit signalEventChangedMotorDirection            (value);}
    void setRejectorRunTimeRatio         (quint32  value){ if(value == mRejectorRunTimeRatio      ) return; mRejectorRunTimeRatio       = value; setIsEditRejectorRunTimeRatio   (true);  emit signalEventChangedRejectorRunTimeRatio      (value);}
    void setDisplayStability             (quint32  value){ if(value == mDisplayStability          ) return; mDisplayStability           = value; setIsEditDisplayStability       (true);  emit signalEventChangedDisplayStability          (value);}
    void setMeasureCueSign               (quint32  value){ if(value == mMeasureCueSign            ) return; mMeasureCueSign             = value; setIsEditMeasureCueSign         (true);  emit signalEventChangedMeasureCueSign            (value);}
    void setMinStaticWeight              (quint32  value){ if(value == mMinStaticWeight           ) return; mMinStaticWeight            = value; setIsEditMinStaticWeight        (true);  emit signalEventChangedMinStaticWeight           (value);}
    void setMinDynamicWeight             (quint32  value){ if(value == mMinDynamicWeight          ) return; mMinDynamicWeight           = value; setIsEditMinDynamicWeight       (true);  emit signalEventChangedMinDynamicWeight          (value);}
    void setScaler                       (quint32  value){ if(value == mScaler                    ) return; mScaler                     = value; setIsEditScaler                 (true);  emit signalEventChangedScaler                    (value);}
    void setStaticFactor                 (quint32  value){ if(value == mStaticFactor              ) return; mStaticFactor               = value; setIsEditStaticFactor           (true);  emit signalEventChangedStaticFactor              (value);}
    void setDynamicFactor                (quint32  value){ if(value == mDynamicFactor             ) return; mDynamicFactor              = value; setIsEditDynamicFactor          (true);  emit signalEventChangedDynamicFactor             (value);}
    void setStandardWeight               (quint32  value){ if(value == mStandardWeight            ) return; mStandardWeight             = value; setIsEditStandardWeight         (true);  emit signalEventChangedStandardWeight             (value);}
    void setRefWeight                    (quint32  value){ if(value == mRefWeight                 ) return; mRefWeight                  = value; setIsEditRefWeight              (true);  emit signalEventChangedRefWeight                 (value);}
    void setWCPhotoOn                    (bool     value){ if(value == mWCPhotoOn                 ) return; mWCPhotoOn                  = value; setIsEditWCPhotoOn              (true);  emit signalEventChangedWCPhotoOn                 (value);}
    void setMode                         (quint16  value){ if(value == mMode                      ) return; mMode                       = value; setIsEditMode                   (true);  emit signalEventChangedMode                      (value);}
    void setDetectDetectTime             (quint32  value){ if(value == mDetectDetectTime          ) return; mDetectDetectTime           = value; setIsEditDetectDetectTime       (true);  emit signalEventChangedDetectDetectTime          (value);}
    void setRunDetectTime                (quint32  value){ if(value == mRunDetectTime             ) return; mRunDetectTime              = value; setIsEditRunDetectTime          (true);  emit signalEventChangedRunDetectTime             (value);}
    void setSignalDelayTime              (quint32  value){ if(value == mSignalDelayTime           ) return; mSignalDelayTime            = value; setIsEditSignalDelayTime        (true);  emit signalEventChangedSignalDelayTime           (value);}
    void setMDPhotoOn                    (bool     value){ if(value == mMDPhotoOn                 ) return; mMDPhotoOn                  = value; setIsEditMDPhotoOn              (true);  emit signalEventChangedMDPhotoOn                 (value);}
    void setSensorCnt                    (quint16  value){ if(value == mSensorCnt                 ) return; mSensorCnt                  = value; setIsEditSensorCnt              (true);  emit signalEventChangedSensorCnt                 (value);}
    void setSimpleSens01                 (quint16  value){ if(value == mSimpleSens01              ) return; mSimpleSens01               = value; setIsEditSimpleSens01           (true);  emit signalEventChangedSimpleSens01              (value);}
    void setSimpleSens02                 (quint16  value){ if(value == mSimpleSens02              ) return; mSimpleSens02               = value; setIsEditSimpleSens02           (true);  emit signalEventChangedSimpleSens02              (value);}
    void setSimpleSens03                 (quint16  value){ if(value == mSimpleSens03              ) return; mSimpleSens03               = value; setIsEditSimpleSens03           (true);  emit signalEventChangedSimpleSens03              (value);}
    void setSimpleSens04                 (quint16  value){ if(value == mSimpleSens04              ) return; mSimpleSens04               = value; setIsEditSimpleSens04           (true);  emit signalEventChangedSimpleSens04              (value);}
    void setSimpleSens05                 (quint16  value){ if(value == mSimpleSens05              ) return; mSimpleSens05               = value; setIsEditSimpleSens05           (true);  emit signalEventChangedSimpleSens05              (value);}

    void setIsEditLanguage               (bool     value){ if(value == mIsEditLanguage            ) return; mIsEditLanguage             = value; emit signalEventChangedIsEditLanguage            (value);}
    void setIsEditPassword               (bool     value){ if(value == mIsEditPassword            ) return; mIsEditPassword             = value; emit signalEventChangedIsEditPassword            (value);}
    void setIsEditNewPassword            (bool     value){ if(value == mIsEditNewPassword         ) return; mIsEditNewPassword          = value; emit signalEventChangedIsEditNewPassword         (value);}
    void setIsEditConfirmPassword        (bool     value){ if(value == mIsEditConfirmPassword     ) return; mIsEditConfirmPassword      = value; emit signalEventChangedIsEditConfirmPassword     (value);}
    void setIsEditIsDayMode              (bool     value){ if(value == mIsEditIsDayMode           ) return; mIsEditIsDayMode            = value; emit signalEventChangedIsEditIsDayMode           (value);}
    void setIsEditIsDebugMode            (bool     value){ if(value == mIsEditIsDebugMode         ) return; mIsEditIsDebugMode          = value; emit signalEventChangedIsEditIsDebugMode         (value);}
    void setIsEditLampTime               (bool     value){ if(value == mIsEditLampTime            ) return; mIsEditLampTime             = value; emit signalEventChangedIsEditLampTime            (value);}
    void setIsEditBuzzerTime             (bool     value){ if(value == mIsEditBuzzerTime          ) return; mIsEditBuzzerTime           = value; emit signalEventChangedIsEditBuzzerTime          (value);}
    void setIsEditSpeedConverter         (bool     value){ if(value == mIsEditSpeedConverter      ) return; mIsEditSpeedConverter       = value; emit signalEventChangedIsEditSpeedConverter      (value);}
    void setIsEditMotorDirection         (bool     value){ if(value == mIsEditMotorDirection      ) return; mIsEditMotorDirection       = value; emit signalEventChangedIsEditMotorDirection      (value);}
    void setIsEditRejectorRunTimeRatio   (bool     value){ if(value == mIsEditRejectorRunTimeRatio) return; mIsEditRejectorRunTimeRatio = value; emit signalEventChangedIsEditRejectorRunTimeRatio(value);}
    void setIsEditDisplayStability       (bool     value){ if(value == mIsEditDisplayStability    ) return; mIsEditDisplayStability     = value; emit signalEventChangedIsEditDisplayStability    (value);}
    void setIsEditMeasureCueSign         (bool     value){ if(value == mIsEditMeasureCueSign      ) return; mIsEditMeasureCueSign       = value; emit signalEventChangedIsEditMeasureCueSign      (value);}
    void setIsEditMinStaticWeight        (bool     value){ if(value == mIsEditMinStaticWeight     ) return; mIsEditMinStaticWeight      = value; emit signalEventChangedIsEditMinStaticWeight     (value);}
    void setIsEditMinDynamicWeight       (bool     value){ if(value == mIsEditMinDynamicWeight    ) return; mIsEditMinDynamicWeight     = value; emit signalEventChangedIsEditMinDynamicWeight    (value);}
    void setIsEditScaler                 (bool     value){ if(value == mIsEditScaler              ) return; mIsEditScaler               = value; emit signalEventChangedIsEditScaler              (value);}
    void setIsEditStaticFactor           (bool     value){ if(value == mIsEditStaticFactor        ) return; mIsEditStaticFactor         = value; emit signalEventChangedIsEditStaticFactor        (value);}
    void setIsEditDynamicFactor          (bool     value){ if(value == mIsEditDynamicFactor       ) return; mIsEditDynamicFactor        = value; emit signalEventChangedIsEditDynamicFactor       (value);}
    void setIsEditStandardWeight         (bool     value){ if(value == mIsEditStandardWeight      ) return; mIsEditStandardWeight       = value; emit signalEventChangedIsEditStandardWeight      (value);}
    void setIsEditRefWeight              (bool     value){ if(value == mIsEditRefWeight           ) return; mIsEditRefWeight            = value; emit signalEventChangedIsEditRefWeight           (value);}
    void setIsEditWCPhotoOn              (bool     value){ if(value == mIsEditWCPhotoOn           ) return; mIsEditWCPhotoOn            = value; emit signalEventChangedIsEditWCPhotoOn           (value);}
    void setIsEditMode                   (bool     value){ if(value == mIsEditMode                ) return; mIsEditMode                 = value; emit signalEventChangedIsEditMode                (value);}
    void setIsEditDetectDetectTime       (bool     value){ if(value == mIsEditDetectDetectTime    ) return; mIsEditDetectDetectTime     = value; emit signalEventChangedIsEditDetectDetectTime    (value);}
    void setIsEditRunDetectTime          (bool     value){ if(value == mIsEditRunDetectTime       ) return; mIsEditRunDetectTime        = value; emit signalEventChangedIsEditRunDetectTime       (value);}
    void setIsEditSignalDelayTime        (bool     value){ if(value == mIsEditSignalDelayTime     ) return; mIsEditSignalDelayTime      = value; emit signalEventChangedIsEditSignalDelayTime     (value);}
    void setIsEditMDPhotoOn              (bool     value){ if(value == mIsEditMDPhotoOn           ) return; mIsEditMDPhotoOn            = value; emit signalEventChangedIsEditMDPhotoOn           (value);}
    void setIsEditSensorCnt              (bool     value){ if(value == mIsEditSensorCnt           ) return; mIsEditSensorCnt            = value; emit signalEventChangedIsEditSensorCnt           (value);}
    void setIsEditSimpleSens01           (bool     value){ if(value == mIsEditSimpleSens01        ) return; mIsEditSimpleSens01         = value; emit signalEventChangedIsEditSimpleSens01        (value);}
    void setIsEditSimpleSens02           (bool     value){ if(value == mIsEditSimpleSens02        ) return; mIsEditSimpleSens02         = value; emit signalEventChangedIsEditSimpleSens02        (value);}
    void setIsEditSimpleSens03           (bool     value){ if(value == mIsEditSimpleSens03        ) return; mIsEditSimpleSens03         = value; emit signalEventChangedIsEditSimpleSens03        (value);}
    void setIsEditSimpleSens04           (bool     value){ if(value == mIsEditSimpleSens04        ) return; mIsEditSimpleSens04         = value; emit signalEventChangedIsEditSimpleSens04        (value);}
    void setIsEditSimpleSens05           (bool     value){ if(value == mIsEditSimpleSens05        ) return; mIsEditSimpleSens05         = value; emit signalEventChangedIsEditSimpleSens05        (value);}

    void reset()
    {
        setLanguage                     (mpCoreService->mLocalSettingService.mGuiSetting.mLanguage             );
        setPassword                     (""                                                 );
        setNewPassword                  (""                                                 );
        setConfirmPassword              (""                                                 );
        setIsDayMode                    (mpCoreService->mLocalSettingService.mHmiSetting.mIsDayMode     );
        setIsDebugMode                  (mpCoreService->mLocalSettingService.mHmiSetting.mIsDebugMode          );
        setLampTime                     (mpCoreService->mLocalSettingService.mDspSetting.mLampTime             );
        setBuzzerTime                   (mpCoreService->mLocalSettingService.mDspSetting.mBuzzerTime           );
        setSpeedConverter               (mpCoreService->mLocalSettingService.mDspSetting.mSpeedConverter       );
        setMotorDirection               (mpCoreService->mLocalSettingService.mDspSetting.mMotorDirection       );
        setRejectorRunTimeRatio         (mpCoreService->mLocalSettingService.mDspSetting.mRejectorRunTimeRatio );
        setDisplayStability             (mpCoreService->mLocalSettingService.mDspSetting.mDisplayStability     );
        setMeasureCueSign               (mpCoreService->mLocalSettingService.mDspSetting.mMeasureCueSign       );
        setMinStaticWeight              (mpCoreService->mLocalSettingService.mDspSetting.mMinStaticWeight      );
        setMinDynamicWeight             (mpCoreService->mLocalSettingService.mDspSetting.mMinDynamicWeight     );
        setScaler                       (mpCoreService->mLocalSettingService.mDspSetting.mScaler               );
        setStaticFactor                 (mpCoreService->mLocalSettingService.mDspSetting.mStaticFactor         );
        setDynamicFactor                (mpCoreService->mLocalSettingService.mHmiSetting.mDynamicFactor        );
        setStandardWeight               (mpCoreService->mLocalSettingService.mDspSetting.mStaticStandardWeight );
        setRefWeight                    (mpCoreService->mLocalSettingService.mDspSetting.mDynamicBaseWeight    );
        setWCPhotoOn                    (mpCoreService->mLocalSettingService.mDspSetting.mWCPhotoIsOn          );
        setMode                         (mpCoreService->mLocalSettingService.mDspSetting.mMode                 );
        setDetectDetectTime             (mpCoreService->mLocalSettingService.mDspSetting.mDetectDetectTime     );
        setRunDetectTime                (mpCoreService->mLocalSettingService.mDspSetting.mRunDetectTime        );
        setSignalDelayTime              (mpCoreService->mLocalSettingService.mDspSetting.mSignalDelayTime      );
        setMDPhotoOn                    (mpCoreService->mLocalSettingService.mDspSetting.mMDPhotoIsOn          );
        setSensorCnt                    (mpCoreService->mLocalSettingService.mDspSetting.mSensorCnt            );
        setSimpleSens01                 (mpCoreService->mLocalSettingService.mHmiSetting.mSimpleSenstivity01   );
        setSimpleSens02                 (mpCoreService->mLocalSettingService.mHmiSetting.mSimpleSenstivity02   );
        setSimpleSens03                 (mpCoreService->mLocalSettingService.mHmiSetting.mSimpleSenstivity03   );
        setSimpleSens04                 (mpCoreService->mLocalSettingService.mHmiSetting.mSimpleSenstivity04   );
        setSimpleSens05                 (mpCoreService->mLocalSettingService.mHmiSetting.mSimpleSenstivity05   );

        setIsEditLanguage                     ( false );
        setIsEditPassword                     ( false );
        setIsEditNewPassword                  ( false );
        setIsEditConfirmPassword              ( false );
        setIsEditIsDayMode                    ( false );
        setIsEditIsDebugMode                  ( false );
        setIsEditLampTime                     ( false );
        setIsEditBuzzerTime                   ( false );
        setIsEditSpeedConverter               ( false );
        setIsEditMotorDirection               ( false );
        setIsEditRejectorRunTimeRatio         ( false );
        setIsEditDisplayStability             ( false );
        setIsEditMeasureCueSign               ( false );
        setIsEditMinStaticWeight              ( false );
        setIsEditMinDynamicWeight             ( false );
        setIsEditScaler                       ( false );
        setIsEditStaticFactor                 ( false );
        setIsEditDynamicFactor                ( false );
        setIsEditStandardWeight               ( false );
        setIsEditRefWeight                    ( false );
        setIsEditWCPhotoOn                    ( false );
        setIsEditMode                         ( false );
        setIsEditDetectDetectTime             ( false );
        setIsEditRunDetectTime                ( false );
        setIsEditSignalDelayTime              ( false );
        setIsEditMDPhotoOn                    ( false );
        setIsEditSensorCnt                    ( false );
        setIsEditSimpleSens01                 ( false );
        setIsEditSimpleSens02                 ( false );
        setIsEditSimpleSens03                 ( false );
        setIsEditSimpleSens04                 ( false );
        setIsEditSimpleSens05                 ( false );
    }
    explicit PanelDeviceSettingModel(QObject *parent = nullptr):QObject(parent)
    {
        mpCoreService = CoreService::getInstance();
        reset();
    }

signals:
    void signalEventChangedLanguage                     (int      value);
    void signalEventChangedPassword                     (QString  value);
    void signalEventChangedNewPassword                  (QString  value);
    void signalEventChangedConfirmPassword              (QString  value);
    void signalEventChangedIsDayMode                    (bool     value);
    void signalEventChangedIsDebugMode                  (bool     value);
    void signalEventChangedLampTime                     (quint32  value);
    void signalEventChangedBuzzerTime                   (quint32  value);
    void signalEventChangedSpeedConverter               (quint32  value);
    void signalEventChangedMotorDirection               (quint16  value);
    void signalEventChangedRejectorRunTimeRatio         (quint32  value);
    void signalEventChangedDisplayStability             (quint32  value);
    void signalEventChangedMeasureCueSign               (quint32  value);
    void signalEventChangedMinStaticWeight              (quint32  value);
    void signalEventChangedMinDynamicWeight             (quint32  value);
    void signalEventChangedScaler                       (quint32  value);
    void signalEventChangedStaticFactor                 (quint32  value);
    void signalEventChangedDynamicFactor                (quint32  value);
    void signalEventChangedStandardWeight               (quint32  value);
    void signalEventChangedRefWeight                    (quint32  value);
    void signalEventChangedWCPhotoOn                    (bool     value);
    void signalEventChangedMode                         (quint16  value);
    void signalEventChangedDetectDetectTime             (quint32  value);
    void signalEventChangedRunDetectTime                (quint32  value);
    void signalEventChangedSignalDelayTime              (quint32  value);
    void signalEventChangedMDPhotoOn                    (bool     value);
    void signalEventChangedSensorCnt                    (quint16  value);
    void signalEventChangedSimpleSens01                 (quint16  value);
    void signalEventChangedSimpleSens02                 (quint16  value);
    void signalEventChangedSimpleSens03                 (quint16  value);
    void signalEventChangedSimpleSens04                 (quint16  value);
    void signalEventChangedSimpleSens05                 (quint16  value);

    void signalEventChangedIsEditLanguage               (bool     value);
    void signalEventChangedIsEditPassword               (bool     value);
    void signalEventChangedIsEditNewPassword            (bool     value);
    void signalEventChangedIsEditConfirmPassword        (bool     value);
    void signalEventChangedIsEditIsDayMode              (bool     value);
    void signalEventChangedIsEditIsDebugMode            (bool     value);
    void signalEventChangedIsEditLampTime               (bool     value);
    void signalEventChangedIsEditBuzzerTime             (bool     value);
    void signalEventChangedIsEditSpeedConverter         (bool     value);
    void signalEventChangedIsEditMotorDirection         (bool     value);
    void signalEventChangedIsEditRejectorRunTimeRatio   (bool     value);
    void signalEventChangedIsEditDisplayStability       (bool     value);
    void signalEventChangedIsEditMeasureCueSign         (bool     value);
    void signalEventChangedIsEditMinStaticWeight        (bool     value);
    void signalEventChangedIsEditMinDynamicWeight       (bool     value);
    void signalEventChangedIsEditScaler                 (bool     value);
    void signalEventChangedIsEditStaticFactor           (bool     value);
    void signalEventChangedIsEditDynamicFactor          (bool     value);
    void signalEventChangedIsEditStandardWeight         (bool     value);
    void signalEventChangedIsEditRefWeight              (bool     value);
    void signalEventChangedIsEditWCPhotoOn              (bool     value);
    void signalEventChangedIsEditMode                   (bool     value);
    void signalEventChangedIsEditDetectDetectTime       (bool     value);
    void signalEventChangedIsEditRunDetectTime          (bool     value);
    void signalEventChangedIsEditSignalDelayTime        (bool     value);
    void signalEventChangedIsEditMDPhotoOn              (bool     value);
    void signalEventChangedIsEditSensorCnt              (bool     value);
    void signalEventChangedIsEditSimpleSens01           (bool     value);
    void signalEventChangedIsEditSimpleSens02           (bool     value);
    void signalEventChangedIsEditSimpleSens03           (bool     value);
    void signalEventChangedIsEditSimpleSens04           (bool     value);
    void signalEventChangedIsEditSimpleSens05           (bool     value);

    void signalResultSaveDeviceSetting(int error);

public slots:

    Q_INVOKABLE void onCommandSave()
    {
        if(mIsEditPassword || mIsEditNewPassword || mIsEditConfirmPassword)
        {
            if((mPassword != mpCoreService->mLocalSettingService.mSecuritySetting.mPassword && mPassword != mpCoreService->mLocalSettingService.mSecuritySetting.mAdminPassword)|| mNewPassword != mConfirmPassword)
            {
                emit signalResultSaveDeviceSetting((int)EnumDefine::DatabaseErrorType::PASSWORD_ERROR);
                return;
            }

            mpCoreService->mLocalSettingService.setSecuritySetting(mNewPassword, mpCoreService->mLocalSettingService.mSecuritySetting.mAdminPassword);
        }

        mpCoreService->onCommandEditDspSetting(mLampTime                                                               ,
                                               mBuzzerTime                                                             ,
                                               mSpeedConverter                                                         ,
                                               mMotorDirection                                                         ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mSensorLength           ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mDistanceToRejector     ,
                                               mMDPhotoOn                                                              ,
                                               mWCPhotoOn                                                              ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mRejectorReadyTime      ,
                                               mRejectorRunTimeRatio                                                   ,
                                               mStaticFactor                                                           ,
                                               mScaler                                                                 ,
                                               mDisplayStability                                                       ,
                                               mMeasureCueSign                                                         ,
                                               mMinStaticWeight                                                        ,
                                               mMinDynamicWeight                                                       ,
                                               mMode                                                                   ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mDistanceBtwSensor      ,
                                               mDetectDetectTime                                                       ,
                                               mRunDetectTime                                                          ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mDistanceToWeightChecker,
                                               mpCoreService->mLocalSettingService.mDspSetting.mDistancePhotoToSensor  ,
                                               mSignalDelayTime                                                        ,
                                               mStandardWeight                                                         ,
                                               mRefWeight                                                              ,
                                               mSensorCnt                                                              );
        mpCoreService->mLocalSettingService.setGuiLanguage(mLanguage);        
        mpCoreService->mLocalSettingService.setHmiSetting(mIsDayMode, mIsDebugMode, mDynamicFactor, mSimpleSens01, mSimpleSens02, mSimpleSens03, mSimpleSens04, mSimpleSens05);

        reset();

        emit signalResultSaveDeviceSetting((int)EnumDefine::DatabaseErrorType::DB_NONE_ERROR);
    }
    Q_INVOKABLE void onCommandCancle(){ reset(); }

    Q_INVOKABLE void onCommandSetLanguage                     (int      value){setLanguage                     (value);}
    Q_INVOKABLE void onCommandSetPassword                     (QString  value){setPassword                     (value);}
    Q_INVOKABLE void onCommandSetNewPassword                  (QString  value){setNewPassword                  (value);}
    Q_INVOKABLE void onCommandSetConfirmPassword              (QString  value){setConfirmPassword              (value);}
    Q_INVOKABLE void onCommandSetIsDayMode                    (bool     value){setIsDayMode                    (value);}
    Q_INVOKABLE void onCommandSetIsDebugMode                  (bool     value){setIsDebugMode                  (value);}
    Q_INVOKABLE void onCommandSetLampTime                     (quint32  value){setLampTime                     (value);}
    Q_INVOKABLE void onCommandSetBuzzerTime                   (quint32  value){setBuzzerTime                   (value);}
    Q_INVOKABLE void onCommandSetSpeedConverter               (quint32  value){setSpeedConverter               (value);}
    Q_INVOKABLE void onCommandSetMotorDirection               (quint16  value){setMotorDirection               (value);}
    Q_INVOKABLE void onCommandSetRejectorRunTimeRatio         (quint32  value){setRejectorRunTimeRatio         (value);}
    Q_INVOKABLE void onCommandSetDisplayStability             (quint32  value){setDisplayStability             (value);}
    Q_INVOKABLE void onCommandSetMeasureCueSign               (quint32  value){setMeasureCueSign               (value);}
    Q_INVOKABLE void onCommandSetMinStaticWeight              (quint32  value){setMinStaticWeight              (value);}
    Q_INVOKABLE void onCommandSetMinDynamicWeight             (quint32  value){setMinDynamicWeight             (value);}
    Q_INVOKABLE void onCommandSetScaler                       (quint32  value){setScaler                       (value);}
    Q_INVOKABLE void onCommandSetStaticFactor                 (quint32  value){setStaticFactor                 (value);}
    Q_INVOKABLE void onCommandSetDynamicFactor                (quint32  value){setDynamicFactor                (value);}
    Q_INVOKABLE void onCommandSetStandardWeight               (quint32  value){setStandardWeight               (value);}
    Q_INVOKABLE void onCommandSetRefWeight                    (quint32  value){setRefWeight                    (value);}
    Q_INVOKABLE void onCommandSetWCPhotoOn                    (bool     value){setWCPhotoOn                    (value);}
    Q_INVOKABLE void onCommandSetMode                         (quint16  value){setMode                         (value);}
    Q_INVOKABLE void onCommandSetDetectDetectTime             (quint32  value){setDetectDetectTime             (value);}
    Q_INVOKABLE void onCommandSetRunDetectTime                (quint32  value){setRunDetectTime                (value);}
    Q_INVOKABLE void onCommandSetSignalDelayTime              (quint32  value){setSignalDelayTime              (value);}
    Q_INVOKABLE void onCommandSetMDPhotoOn                    (bool     value){setMDPhotoOn                    (value);}
    Q_INVOKABLE void onCommandSetSensorCnt                    (quint16  value){setSensorCnt                    (value);}
    Q_INVOKABLE void onCommandSetSimpleSens01                 (quint16  value){setSimpleSens01                 (value);}
    Q_INVOKABLE void onCommandSetSimpleSens02                 (quint16  value){setSimpleSens02                 (value);}
    Q_INVOKABLE void onCommandSetSimpleSens03                 (quint16  value){setSimpleSens03                 (value);}
    Q_INVOKABLE void onCommandSetSimpleSens04                 (quint16  value){setSimpleSens04                 (value);}
    Q_INVOKABLE void onCommandSetSimpleSens05                 (quint16  value){setSimpleSens05                 (value);}

};

#endif // PANELDEVICESETTINGMODEL_H
