#ifndef PRODUCTSETTINGITEMMODEL_H
#define PRODUCTSETTINGITEMMODEL_H

#include <QObject>
#include <QtMath>
#include "source/service/coreservice.h"

class ProductSettingItemModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool                 isNew                      READ getIsNew                       NOTIFY signalEventChangedIsNew                    )
    Q_PROPERTY(quint64              seq                        READ getSeq                         NOTIFY signalEventChangedSeq                      )
    Q_PROPERTY(quint16              no                         READ getNo                          NOTIFY signalEventChangedNo                       )
    Q_PROPERTY(QString              name                       READ getName                        NOTIFY signalEventChangedName                     )
    Q_PROPERTY(quint16              length                     READ getLength                      NOTIFY signalEventChangedLength                   )
    Q_PROPERTY(quint16              speed                      READ getSpeed                       NOTIFY signalEventChangedSpeed                    )
    Q_PROPERTY(quint32              motorAcceleration          READ getMotorAcceleration           NOTIFY signalEventChangedMotorAcceleration        )
    Q_PROPERTY(quint32              motorDeceleration          READ getMotorDeceleration           NOTIFY signalEventChangedMotorDeceleration        )
    Q_PROPERTY(quint32              groupCount                 READ getGroupCount                  NOTIFY signalEventChangedGroupCount               )
    Q_PROPERTY(quint16              groupMotion                READ getGroupMotion                 NOTIFY signalEventChangedGroupMotion              )
    Q_PROPERTY(quint16              groupLamp                  READ getGroupLamp                   NOTIFY signalEventChangedGroupLamp                )
    Q_PROPERTY(quint16              groupBuzzer                READ getGroupBuzzer                 NOTIFY signalEventChangedGroupBuzzer              )
    Q_PROPERTY(quint32              underWeight                READ getUnderWeight                 NOTIFY signalEventChangedUnderWeight              )
    Q_PROPERTY(quint32              underWarningWeight         READ getUnderWarningWeight          NOTIFY signalEventChangedUnderWarningWeight       )
    Q_PROPERTY(quint32              normalWeight               READ getNormalWeight                NOTIFY signalEventChangedNormalWeight             )
    Q_PROPERTY(quint32              overWarningWeight          READ getOverWarningWeight           NOTIFY signalEventChangedOverWarningWeight        )
    Q_PROPERTY(quint32              overWeight                 READ getOverWeight                  NOTIFY signalEventChangedOverWeight               )
    Q_PROPERTY(quint32              tareWeight                 READ getTareWeight                  NOTIFY signalEventChangedTareWeight               )
    Q_PROPERTY(quint16              wcOverMotion               READ getWCOverMotion                NOTIFY signalEventChangedWCOverMotion             )
    Q_PROPERTY(quint16              wcUnderMotion              READ getWCUnderMotion               NOTIFY signalEventChangedWCUnderMotion            )
    Q_PROPERTY(quint16              wcEtcMotion                READ getWCEtcMotion                 NOTIFY signalEventChangedWCEtcMotion              )
    Q_PROPERTY(quint16              wcNGLamp                   READ getWCNGLamp                    NOTIFY signalEventChangedWCNGLamp                 )
    Q_PROPERTY(quint16              wcNGBuzzer                 READ getWCNGBuzzer                  NOTIFY signalEventChangedWCNGBuzzer               )
    Q_PROPERTY(quint16              wcEnableEtcError           READ getWCEnableEtcError            NOTIFY signalEventChangedWCEnableEtcError         )
    Q_PROPERTY(int                  dynamicFactor              READ getDynamicFactor               NOTIFY signalEventChangedDynamicFactor            )
    Q_PROPERTY(quint16              mdSenstivity               READ getMDSenstivity                NOTIFY signalEventChangedMDSenstivity             )
    Q_PROPERTY(quint16              mdNGMotion                 READ getMDNGMotion                  NOTIFY signalEventChangedMDNGMotion               )
    Q_PROPERTY(quint16              mdNGLamp                   READ getMDNGLamp                    NOTIFY signalEventChangedMDNGLamp                 )
    Q_PROPERTY(quint16              mdNGBuzzer                 READ getMDNGBuzzer                  NOTIFY signalEventChangedMDNGBuzzer               )
    Q_PROPERTY(quint16              filterCoefficient          READ getFilterCoefficient           NOTIFY signalEventChangedFilterCoefficient        )
    Q_PROPERTY(quint16              zeroDelayTime              READ getZeroDelayTime               NOTIFY signalEventChangedZeroDelayTime            )
    Q_PROPERTY(quint32              measureCueSign             READ getMeasureCueSign              NOTIFY signalEventChangedMeasureCueSign           )
    Q_PROPERTY(quint32              measureSection             READ getMeasureSection              NOTIFY signalEventChangedMeasureSection           )
    Q_PROPERTY(qint32               maxSpeed                   READ getMaxSpeed                    NOTIFY signalEventChangedMaxSpeed                 )

    Q_PROPERTY(bool                 isEditNo                   READ getIsEditNo                    NOTIFY signalEventChangedIsEditNo                 )
    Q_PROPERTY(bool                 isEditName                 READ getIsEditName                  NOTIFY signalEventChangedIsEditName               )
    Q_PROPERTY(bool                 isEditLength               READ getIsEditLength                NOTIFY signalEventChangedIsEditLength             )
    Q_PROPERTY(bool                 isEditSpeed                READ getIsEditSpeed                 NOTIFY signalEventChangedIsEditSpeed              )
    Q_PROPERTY(bool                 isEditMotorAcceleration    READ getIsEditMotorAcceleration     NOTIFY signalEventChangedIsEditMotorAcceleration  )
    Q_PROPERTY(bool                 isEditMotorDeceleration    READ getIsEditMotorDeceleration     NOTIFY signalEventChangedIsEditMotorDeceleration  )
    Q_PROPERTY(bool                 isEditGroupCount           READ getIsEditGroupCount            NOTIFY signalEventChangedIsEditGroupCount         )
    Q_PROPERTY(bool                 isEditGroupMotion          READ getIsEditGroupMotion           NOTIFY signalEventChangedIsEditGroupMotion        )
    Q_PROPERTY(bool                 isEditGroupLamp            READ getIsEditGroupLamp             NOTIFY signalEventChangedIsEditGroupLamp          )
    Q_PROPERTY(bool                 isEditGroupBuzzer          READ getIsEditGroupBuzzer           NOTIFY signalEventChangedIsEditGroupBuzzer        )
    Q_PROPERTY(bool                 isEditUnderWeight          READ getIsEditUnderWeight           NOTIFY signalEventChangedIsEditUnderWeight        )
    Q_PROPERTY(bool                 isEditUnderWarningWeight   READ getIsEditUnderWarningWeight    NOTIFY signalEventChangedIsEditUnderWarningWeight )
    Q_PROPERTY(bool                 isEditNormalWeight         READ getIsEditNormalWeight          NOTIFY signalEventChangedIsEditNormalWeight       )
    Q_PROPERTY(bool                 isEditOverWarningWeight    READ getIsEditOverWarningWeight     NOTIFY signalEventChangedIsEditOverWarningWeight  )
    Q_PROPERTY(bool                 isEditOverWeight           READ getIsEditOverWeight            NOTIFY signalEventChangedIsEditOverWeight         )
    Q_PROPERTY(bool                 isEditTareWeight           READ getIsEditTareWeight            NOTIFY signalEventChangedIsEditTareWeight         )
    Q_PROPERTY(bool                 isEditWCOverMotion         READ getIsEditWCOverMotion          NOTIFY signalEventChangedIsEditWCOverMotion       )
    Q_PROPERTY(bool                 isEditWCUnderMotion        READ getIsEditWCUnderMotion         NOTIFY signalEventChangedIsEditWCUnderMotion      )
    Q_PROPERTY(bool                 isEditWCEtcMotion          READ getIsEditWCEtcMotion           NOTIFY signalEventChangedIsEditWCEtcMotion        )
    Q_PROPERTY(bool                 isEditWCNGLamp             READ getIsEditWCNGLamp              NOTIFY signalEventChangedIsEditWCNGLamp           )
    Q_PROPERTY(bool                 isEditWCNGBuzzer           READ getIsEditWCNGBuzzer            NOTIFY signalEventChangedIsEditWCNGBuzzer         )
    Q_PROPERTY(bool                 isEditWCEnableEtcError     READ getIsEditWCEnableEtcError      NOTIFY signalEventChangedIsEditWCEnableEtcError   )
    Q_PROPERTY(bool                 isEditDynamicFactor        READ getIsEditDynamicFactor         NOTIFY signalEventChangedIsEditDynamicFactor      )
    Q_PROPERTY(bool                 isEditMDSenstivity         READ getIsEditMDSenstivity          NOTIFY signalEventChangedIsEditMDSenstivity       )
    Q_PROPERTY(bool                 isEditMDNGMotion           READ getIsEditMDNGMotion            NOTIFY signalEventChangedIsEditMDNGMotion         )
    Q_PROPERTY(bool                 isEditMDNGLamp             READ getIsEditMDNGLamp              NOTIFY signalEventChangedIsEditMDNGLamp           )
    Q_PROPERTY(bool                 isEditMDNGBuzzer           READ getIsEditMDNGBuzzer            NOTIFY signalEventChangedIsEditMDNGBuzzer         )
    Q_PROPERTY(bool                 isEditFilterCoefficient    READ getIsEditFilterCoefficient     NOTIFY signalEventChangedIsEditFilterCoefficient  )
    Q_PROPERTY(bool                 isEditZeroDelayTime        READ getIsEditZeroDelayTime         NOTIFY signalEventChangedIsEditZeroDelayTime      )
    Q_PROPERTY(bool                 isEditMeasureCueSign       READ getIsEditMeasureCueSign        NOTIFY signalEventChangedIsEditMeasureCueSign     )
    Q_PROPERTY(bool                 isEditMeasureSection       READ getIsEditMeasureSection        NOTIFY signalEventChangedIsEditMeasureSection     )

public:

    bool         mIsNew                    ;
    PDSettingDto mModel                    ;

    bool         mIsEditNo                 ;
    bool         mIsEditName               ;
    bool         mIsEditLength             ;
    bool         mIsEditSpeed              ;
    bool         mIsEditMotorAcceleration  ;
    bool         mIsEditMotorDeceleration  ;
    bool         mIsEditGroupCount         ;
    bool         mIsEditGroupMotion        ;
    bool         mIsEditGroupLamp          ;
    bool         mIsEditGroupBuzzer        ;
    bool         mIsEditUnderWeight        ;
    bool         mIsEditUnderWarningWeight ;
    bool         mIsEditNormalWeight       ;
    bool         mIsEditOverWarningWeight  ;
    bool         mIsEditOverWeight         ;
    bool         mIsEditTareWeight         ;
    bool         mIsEditWCOverMotion       ;
    bool         mIsEditWCUnderMotion      ;
    bool         mIsEditWCEtcMotion        ;
    bool         mIsEditWCNGLamp           ;
    bool         mIsEditWCNGBuzzer         ;
    bool         mIsEditWCEnableEtcError   ;
    bool         mIsEditDynamicFactor      ;
    bool         mIsEditMDSenstivity       ;
    bool         mIsEditMDNGMotion         ;
    bool         mIsEditMDNGLamp           ;
    bool         mIsEditMDNGBuzzer         ;
    bool         mIsEditFilterCoefficient  ;
    bool         mIsEditZeroDelayTime      ;
    bool         mIsEditMeasureCueSign     ;
    bool         mIsEditMeasureSection     ;

    bool    getIsNew                   (){return mIsNew                                             ;}
    quint64 getSeq                     (){return mModel.mSeq                                        ;}
    quint16 getNo                      (){return mModel.mDspForm.mCommSetting.mProductNum           ;}
    QString getName                    (){return mModel.mName                                       ;}
    quint16 getLength                  (){return mModel.mDspForm.mCommSetting.mLength               ;}
    quint16 getSpeed                   (){return mModel.mDspForm.mCommSetting.mSpeed                ;}
    quint32 getMotorAcceleration       (){return mModel.mDspForm.mCommSetting.mMotorAccelerationTime;}
    quint32 getMotorDeceleration       (){return mModel.mDspForm.mCommSetting.mMotorDecelerationTime;}
    quint32 getGroupCount              (){return mModel.mDspForm.mCommSetting.mGroupCount           ;}
    quint16 getGroupMotion             (){return mModel.mDspForm.mCommSetting.mGroupMotion          ;}
    quint16 getGroupLamp               (){return mModel.mDspForm.mCommSetting.mGroupLamp            ;}
    quint16 getGroupBuzzer             (){return mModel.mDspForm.mCommSetting.mGroupBuzzer          ;}
    quint32 getUnderWeight             (){return mModel.mDspForm.mWCSetting.mUnderWeight            ;}
    quint32 getUnderWarningWeight      (){return mModel.mDspForm.mWCSetting.mUnderWarningWeight     ;}
    quint32 getNormalWeight            (){return mModel.mDspForm.mWCSetting.mNormalWeight           ;}
    quint32 getOverWarningWeight       (){return mModel.mDspForm.mWCSetting.mOverWarningWeight      ;}
    quint32 getOverWeight              (){return mModel.mDspForm.mWCSetting.mOverWeight             ;}
    quint32 getTareWeight              (){return mModel.mDspForm.mWCSetting.mTareWeight             ;}
    quint16 getWCOverMotion            (){return mModel.mDspForm.mWCSetting.mOverMotion             ;}
    quint16 getWCUnderMotion           (){return mModel.mDspForm.mWCSetting.mUnderMotion            ;}
    quint16 getWCEtcMotion             (){return mModel.mDspForm.mWCSetting.mEtcMotion              ;}
    quint16 getWCNGLamp                (){return mModel.mDspForm.mWCSetting.mNGLamp                 ;}
    quint16 getWCNGBuzzer              (){return mModel.mDspForm.mWCSetting.mNGBuzzer               ;}
    quint16 getWCEnableEtcError        (){return mModel.mDspForm.mWCSetting.mEnableEtcError         ;}
    int     getDynamicFactor           (){return mModel.mDspForm.mWCSetting.mDynamicFactor          ;}
    quint16 getFilterCoefficient       (){return mModel.mDspForm.mWCSetting.mFilterCoefficient      ;}
    quint16 getZeroDelayTime           (){return mModel.mDspForm.mWCSetting.mZeroDelayTime          ;}
    quint32 getMeasureCueSign          (){return mModel.mDspForm.mWCSetting.mMeasureCueSign         ;}
    quint32 getMeasureSection          (){return mModel.mDspForm.mWCSetting.mMeasureSection         ;}
    quint16 getMDSenstivity            (){return mModel.mDspForm.mMDSetting.mSenstivity             ;}
    quint16 getMDNGMotion              (){return mModel.mDspForm.mMDSetting.mNGMotion               ;}
    quint16 getMDNGLamp                (){return mModel.mDspForm.mMDSetting.mNGLamp                 ;}
    quint16 getMDNGBuzzer              (){return mModel.mDspForm.mMDSetting.mNGBuzzer               ;}
    int     getMaxSpeed                ()
    {
        double tOpen = pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter01OpenTime;
        double lR    = pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistanceToWeightChecker + pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistToSorter01;
        double lWR   = pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistToSorter01;
        double lW    = pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mSensorLength;
        double lS    = pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistancePhotoToSensor;
        double wS    = 50;
        double lP    = getLength();

        if(tOpen == 0)
            return -1;

        if(pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMachineMode != EnumDef::MACHINE_MODE_ALU)
        {
            return qFloor(((lWR - lW ) / tOpen ) *60);
        }
        else
        {
            return qFloor(((lR - lS - wS - lP ) / tOpen ) *60);
        }
    }

    bool    getIsEditNo                (){return mIsEditNo                 ;}
    bool    getIsEditName              (){return mIsEditName               ;}
    bool    getIsEditLength            (){return mIsEditLength             ;}
    bool    getIsEditSpeed             (){return mIsEditSpeed              ;}
    bool    getIsEditMotorAcceleration (){return mIsEditMotorAcceleration  ;}
    bool    getIsEditMotorDeceleration (){return mIsEditMotorDeceleration  ;}
    bool    getIsEditGroupCount        (){return mIsEditGroupCount         ;}
    bool    getIsEditGroupMotion       (){return mIsEditGroupMotion        ;}
    bool    getIsEditGroupLamp         (){return mIsEditGroupLamp          ;}
    bool    getIsEditGroupBuzzer       (){return mIsEditGroupBuzzer        ;}
    bool    getIsEditUnderWeight       (){return mIsEditUnderWeight        ;}
    bool    getIsEditUnderWarningWeight(){return mIsEditUnderWarningWeight ;}
    bool    getIsEditNormalWeight      (){return mIsEditNormalWeight       ;}
    bool    getIsEditOverWarningWeight (){return mIsEditOverWarningWeight  ;}
    bool    getIsEditOverWeight        (){return mIsEditOverWeight         ;}
    bool    getIsEditTareWeight        (){return mIsEditTareWeight         ;}
    bool    getIsEditWCOverMotion      (){return mIsEditWCOverMotion       ;}
    bool    getIsEditWCUnderMotion     (){return mIsEditWCUnderMotion      ;}
    bool    getIsEditWCEtcMotion       (){return mIsEditWCEtcMotion        ;}
    bool    getIsEditWCNGLamp          (){return mIsEditWCNGLamp           ;}
    bool    getIsEditWCNGBuzzer        (){return mIsEditWCNGBuzzer         ;}
    bool    getIsEditWCEnableEtcError  (){return mIsEditWCEnableEtcError   ;}
    bool    getIsEditDynamicFactor     (){return mIsEditDynamicFactor      ;}
    bool    getIsEditFilterCoefficient (){return mIsEditFilterCoefficient  ;}
    bool    getIsEditZeroDelayTime     (){return mIsEditZeroDelayTime      ;}
    bool    getIsEditMeasureCueSign    (){return mIsEditMeasureCueSign     ;}
    bool    getIsEditMeasureSection    (){return mIsEditMeasureSection     ;}
    bool    getIsEditMDSenstivity      (){return mIsEditMDSenstivity       ;}
    bool    getIsEditMDNGMotion        (){return mIsEditMDNGMotion         ;}
    bool    getIsEditMDNGLamp          (){return mIsEditMDNGLamp           ;}
    bool    getIsEditMDNGBuzzer        (){return mIsEditMDNGBuzzer         ;}

    void setIsNew                   (bool    value){ if(value == mIsNew                                             ) return; mIsNew                                              = value; emit signalEventChangedIsNew                    (value);}
    void setSeq                     (quint64 value){ if(value == mModel.mSeq                                        ) return; mModel.mSeq                                         = value; emit signalEventChangedSeq                      (value);}
    void setNo                      (quint16 value){ if(value == mModel.mDspForm.mCommSetting.mProductNum           ) return; mModel.mDspForm.mCommSetting.mProductNum            = value;  setIsEditNo                (true); emit signalEventChangedNo                       (value);}
    void setName                    (QString value){ if(value == mModel.mName                                       ) return; mModel.mName                                        = value;  setIsEditName              (true); emit signalEventChangedName                     (value);}
    void setLength                  (quint16 value){ if(value == mModel.mDspForm.mCommSetting.mLength               ) return; mModel.mDspForm.mCommSetting.mLength                = value;  setIsEditLength            (true); emit signalEventChangedLength                   (value); emit signalEventChangedMaxSpeed(getMaxSpeed());}
    void setSpeed                   (quint16 value){ if(value == mModel.mDspForm.mCommSetting.mSpeed                ) return; mModel.mDspForm.mCommSetting.mSpeed                 = value;  setIsEditSpeed             (true); emit signalEventChangedSpeed                    (value);}
    void setMotorAcceleration       (quint32 value){ if(value == mModel.mDspForm.mCommSetting.mMotorAccelerationTime) return; mModel.mDspForm.mCommSetting.mMotorAccelerationTime = value;  setIsEditMotorAcceleration (true); emit signalEventChangedMotorAcceleration        (value);}
    void setMotorDeceleration       (quint32 value){ if(value == mModel.mDspForm.mCommSetting.mMotorDecelerationTime) return; mModel.mDspForm.mCommSetting.mMotorDecelerationTime = value;  setIsEditMotorDeceleration (true); emit signalEventChangedMotorDeceleration        (value);}
    void setGroupCount              (quint32 value){ if(value == mModel.mDspForm.mCommSetting.mGroupCount           ) return; mModel.mDspForm.mCommSetting.mGroupCount            = value;  setIsEditGroupCount        (true); emit signalEventChangedGroupCount               (value);}
    void setGroupMotion             (quint16 value){ if(value == mModel.mDspForm.mCommSetting.mGroupMotion          ) return; mModel.mDspForm.mCommSetting.mGroupMotion           = value;  setIsEditGroupMotion       (true); emit signalEventChangedGroupMotion              (value);}
    void setGroupLamp               (quint16 value){ if(value == mModel.mDspForm.mCommSetting.mGroupLamp            ) return; mModel.mDspForm.mCommSetting.mGroupLamp             = value;  setIsEditGroupLamp         (true); emit signalEventChangedGroupLamp                (value);}
    void setGroupBuzzer             (quint16 value){ if(value == mModel.mDspForm.mCommSetting.mGroupBuzzer          ) return; mModel.mDspForm.mCommSetting.mGroupBuzzer           = value;  setIsEditGroupBuzzer       (true); emit signalEventChangedGroupBuzzer              (value);}
    void setUnderWeight             (quint32 value){ if(value == mModel.mDspForm.mWCSetting.mUnderWeight            ) return; mModel.mDspForm.mWCSetting.mUnderWeight             = value;  setIsEditUnderWeight       (true); emit signalEventChangedUnderWeight              (value);}
    void setUnderWarningWeight      (quint32 value){ if(value == mModel.mDspForm.mWCSetting.mUnderWarningWeight     ) return; mModel.mDspForm.mWCSetting.mUnderWarningWeight      = value;  setIsEditUnderWarningWeight(true); emit signalEventChangedUnderWarningWeight       (value);}
    void setNormalWeight            (quint32 value){ if(value == mModel.mDspForm.mWCSetting.mNormalWeight           ) return; mModel.mDspForm.mWCSetting.mNormalWeight            = value;  setIsEditNormalWeight      (true); emit signalEventChangedNormalWeight             (value);}
    void setOverWarningWeight       (quint32 value){ if(value == mModel.mDspForm.mWCSetting.mOverWarningWeight      ) return; mModel.mDspForm.mWCSetting.mOverWarningWeight       = value;  setIsEditOverWarningWeight (true); emit signalEventChangedOverWarningWeight        (value);}
    void setOverWeight              (quint32 value){ if(value == mModel.mDspForm.mWCSetting.mOverWeight             ) return; mModel.mDspForm.mWCSetting.mOverWeight              = value;  setIsEditOverWeight        (true); emit signalEventChangedOverWeight               (value);}
    void setTareWeight              (quint32 value){ if(value == mModel.mDspForm.mWCSetting.mTareWeight             ) return; mModel.mDspForm.mWCSetting.mTareWeight              = value;  setIsEditTareWeight        (true); emit signalEventChangedTareWeight               (value);}
    void setWCOverMotion            (quint16 value){ if(value == mModel.mDspForm.mWCSetting.mOverMotion             ) return; mModel.mDspForm.mWCSetting.mOverMotion              = value;  setIsEditWCOverMotion      (true); emit signalEventChangedWCOverMotion             (value);}
    void setWCUnderMotion           (quint16 value){ if(value == mModel.mDspForm.mWCSetting.mUnderMotion            ) return; mModel.mDspForm.mWCSetting.mUnderMotion             = value;  setIsEditWCUnderMotion     (true); emit signalEventChangedWCUnderMotion            (value);}
    void setWCEtcMotion             (quint16 value){ if(value == mModel.mDspForm.mWCSetting.mEtcMotion              ) return; mModel.mDspForm.mWCSetting.mEtcMotion               = value;  setIsEditWCEtcMotion       (true); emit signalEventChangedWCEtcMotion              (value);}
    void setWCNGLamp                (quint16 value){ if(value == mModel.mDspForm.mWCSetting.mNGLamp                 ) return; mModel.mDspForm.mWCSetting.mNGLamp                  = value;  setIsEditWCNGLamp          (true); emit signalEventChangedWCNGLamp                 (value);}
    void setWCNGBuzzer              (quint16 value){ if(value == mModel.mDspForm.mWCSetting.mNGBuzzer               ) return; mModel.mDspForm.mWCSetting.mNGBuzzer                = value;  setIsEditWCNGBuzzer        (true); emit signalEventChangedWCNGBuzzer               (value);}
    void setWCEnableEtcError        (quint16 value){ if(value == mModel.mDspForm.mWCSetting.mEnableEtcError         ) return; mModel.mDspForm.mWCSetting.mEnableEtcError          = value;  setIsEditWCEnableEtcError  (true); emit signalEventChangedWCEnableEtcError         (value);}
    void setDynamicFactor           (quint32 value){ if(value == mModel.mDspForm.mWCSetting.mDynamicFactor          ) return; mModel.mDspForm.mWCSetting.mDynamicFactor           = value;  setIsEditDynamicFactor     (true); emit signalEventChangedDynamicFactor            (value);}
    void setFilterCoefficient       (quint16 value){ if(value == mModel.mDspForm.mWCSetting.mFilterCoefficient      ) return; mModel.mDspForm.mWCSetting.mFilterCoefficient       = value;  setIsEditFilterCoefficient (true); emit signalEventChangedFilterCoefficient        (value);}
    void setZeroDelayTime           (quint16 value){ if(value == mModel.mDspForm.mWCSetting.mZeroDelayTime          ) return; mModel.mDspForm.mWCSetting.mZeroDelayTime           = value;  setIsEditZeroDelayTime     (true); emit signalEventChangedZeroDelayTime            (value);}
    void setMeasureCueSign          (quint32 value){ if(value == mModel.mDspForm.mWCSetting.mMeasureCueSign         ) return; mModel.mDspForm.mWCSetting.mMeasureCueSign          = value;  setIsEditMeasureCueSign    (true); emit signalEventChangedMeasureCueSign           (value);}
    void setMeasureSection          (quint32 value){ if(value == mModel.mDspForm.mWCSetting.mMeasureSection         ) return; mModel.mDspForm.mWCSetting.mMeasureSection          = value;  setIsEditMeasureSection    (true); emit signalEventChangedMeasureSection           (value);}
    void setWCAutoSetting           (quint16 value){ if(value == mModel.mDspForm.mWCSetting.mAutoSetting            ) return; mModel.mDspForm.mWCSetting.mAutoSetting             = value;                                                                                             }
    void setMDSenstivity            (quint16 value){ if(value == mModel.mDspForm.mMDSetting.mSenstivity             ) return; mModel.mDspForm.mMDSetting.mSenstivity              = value;  setIsEditMDSenstivity      (true); emit signalEventChangedMDSenstivity             (value);}
    void setMDNGMotion              (quint16 value){ if(value == mModel.mDspForm.mMDSetting.mNGMotion               ) return; mModel.mDspForm.mMDSetting.mNGMotion                = value;  setIsEditMDNGMotion        (true); emit signalEventChangedMDNGMotion               (value);}
    void setMDNGLamp                (quint16 value){ if(value == mModel.mDspForm.mMDSetting.mNGLamp                 ) return; mModel.mDspForm.mMDSetting.mNGLamp                  = value;  setIsEditMDNGLamp          (true); emit signalEventChangedMDNGLamp                 (value);}
    void setMDNGBuzzer              (quint16 value){ if(value == mModel.mDspForm.mMDSetting.mNGBuzzer               ) return; mModel.mDspForm.mMDSetting.mNGBuzzer                = value;  setIsEditMDNGBuzzer        (true); emit signalEventChangedMDNGBuzzer               (value);}


    void setIsEditNo                (bool    value){ if(value == mIsEditNo                 ) return; mIsEditNo                 = value; emit signalEventChangedIsEditNo                 (value);}
    void setIsEditName              (bool    value){ if(value == mIsEditName               ) return; mIsEditName               = value; emit signalEventChangedIsEditName               (value);}
    void setIsEditLength            (bool    value){ if(value == mIsEditLength             ) return; mIsEditLength             = value; emit signalEventChangedIsEditLength             (value);}
    void setIsEditSpeed             (bool    value){ if(value == mIsEditSpeed              ) return; mIsEditSpeed              = value; emit signalEventChangedIsEditSpeed              (value);}
    void setIsEditMotorAcceleration (bool    value){ if(value == mIsEditMotorAcceleration  ) return; mIsEditMotorAcceleration  = value; emit signalEventChangedIsEditMotorAcceleration  (value);}
    void setIsEditMotorDeceleration (bool    value){ if(value == mIsEditMotorDeceleration  ) return; mIsEditMotorDeceleration  = value; emit signalEventChangedIsEditMotorDeceleration  (value);}
    void setIsEditGroupCount        (bool    value){ if(value == mIsEditGroupCount         ) return; mIsEditGroupCount         = value; emit signalEventChangedIsEditGroupCount         (value);}
    void setIsEditGroupMotion       (bool    value){ if(value == mIsEditGroupMotion        ) return; mIsEditGroupMotion        = value; emit signalEventChangedIsEditGroupMotion        (value);}
    void setIsEditGroupLamp         (bool    value){ if(value == mIsEditGroupLamp          ) return; mIsEditGroupLamp          = value; emit signalEventChangedIsEditGroupLamp          (value);}
    void setIsEditGroupBuzzer       (bool    value){ if(value == mIsEditGroupBuzzer        ) return; mIsEditGroupBuzzer        = value; emit signalEventChangedIsEditGroupBuzzer        (value);}
    void setIsEditUnderWeight       (bool    value){ if(value == mIsEditUnderWeight        ) return; mIsEditUnderWeight        = value; emit signalEventChangedIsEditUnderWeight        (value);}
    void setIsEditUnderWarningWeight(bool    value){ if(value == mIsEditUnderWarningWeight ) return; mIsEditUnderWarningWeight = value; emit signalEventChangedIsEditUnderWarningWeight (value);}
    void setIsEditNormalWeight      (bool    value){ if(value == mIsEditNormalWeight       ) return; mIsEditNormalWeight       = value; emit signalEventChangedIsEditNormalWeight       (value);}
    void setIsEditOverWarningWeight (bool    value){ if(value == mIsEditOverWarningWeight  ) return; mIsEditOverWarningWeight  = value; emit signalEventChangedIsEditOverWarningWeight  (value);}
    void setIsEditOverWeight        (bool    value){ if(value == mIsEditOverWeight         ) return; mIsEditOverWeight         = value; emit signalEventChangedIsEditOverWeight         (value);}
    void setIsEditTareWeight        (bool    value){ if(value == mIsEditTareWeight         ) return; mIsEditTareWeight         = value; emit signalEventChangedIsEditTareWeight         (value);}
    void setIsEditWCOverMotion      (bool    value){ if(value == mIsEditWCOverMotion       ) return; mIsEditWCOverMotion       = value; emit signalEventChangedIsEditWCOverMotion       (value);}
    void setIsEditWCUnderMotion     (bool    value){ if(value == mIsEditWCUnderMotion      ) return; mIsEditWCUnderMotion      = value; emit signalEventChangedIsEditWCUnderMotion      (value);}
    void setIsEditWCEtcMotion       (bool    value){ if(value == mIsEditWCEtcMotion        ) return; mIsEditWCEtcMotion        = value; emit signalEventChangedIsEditWCEtcMotion        (value);}
    void setIsEditWCNGLamp          (bool    value){ if(value == mIsEditWCNGLamp           ) return; mIsEditWCNGLamp           = value; emit signalEventChangedIsEditWCNGLamp           (value);}
    void setIsEditWCNGBuzzer        (bool    value){ if(value == mIsEditWCNGBuzzer         ) return; mIsEditWCNGBuzzer         = value; emit signalEventChangedIsEditWCNGBuzzer         (value);}
    void setIsEditWCEnableEtcError  (bool    value){ if(value == mIsEditWCEnableEtcError   ) return; mIsEditWCEnableEtcError   = value; emit signalEventChangedIsEditWCEnableEtcError   (value);}
    void setIsEditDynamicFactor     (bool    value){ if(value == mIsEditDynamicFactor      ) return; mIsEditDynamicFactor      = value; emit signalEventChangedIsEditDynamicFactor      (value);}
    void setIsEditFilterCoefficient (bool    value){ if(value == mIsEditFilterCoefficient  ) return; mIsEditFilterCoefficient  = value; emit signalEventChangedIsEditFilterCoefficient  (value);}
    void setIsEditZeroDelayTime     (bool    value){ if(value == mIsEditZeroDelayTime      ) return; mIsEditZeroDelayTime      = value; emit signalEventChangedIsEditZeroDelayTime      (value);}
    void setIsEditMeasureCueSign    (bool    value){ if(value == mIsEditMeasureCueSign     ) return; mIsEditMeasureCueSign     = value; emit signalEventChangedIsEditMeasureCueSign     (value);}
    void setIsEditMeasureSection    (bool    value){ if(value == mIsEditMeasureSection     ) return; mIsEditMeasureSection     = value; emit signalEventChangedIsEditMeasureSection     (value);}
    void setIsEditMDSenstivity      (bool    value){ if(value == mIsEditMDSenstivity       ) return; mIsEditMDSenstivity       = value; emit signalEventChangedIsEditMDSenstivity       (value);}
    void setIsEditMDNGMotion        (bool    value){ if(value == mIsEditMDNGMotion         ) return; mIsEditMDNGMotion         = value; emit signalEventChangedIsEditMDNGMotion         (value);}
    void setIsEditMDNGLamp          (bool    value){ if(value == mIsEditMDNGLamp           ) return; mIsEditMDNGLamp           = value; emit signalEventChangedIsEditMDNGLamp           (value);}
    void setIsEditMDNGBuzzer        (bool    value){ if(value == mIsEditMDNGBuzzer         ) return; mIsEditMDNGBuzzer         = value; emit signalEventChangedIsEditMDNGBuzzer         (value);}

signals:
    void signalEventChangedIsNull                   (bool    value);
    void signalEventChangedIsNew                    (bool    value);
    void signalEventChangedIsRemoved                (bool    value);

    void signalEventChangedSeq                      (quint64 value);
    void signalEventChangedSelected                 (bool    value);
    void signalEventChangedNo                       (quint16 value);
    void signalEventChangedName                     (QString value);
    void signalEventChangedLength                   (quint16 value);
    void signalEventChangedSpeed                    (quint16 value);
    void signalEventChangedMotorAcceleration        (quint32 value);
    void signalEventChangedMotorDeceleration        (quint32 value);
    void signalEventChangedGroupCount               (quint32 value);
    void signalEventChangedGroupMotion              (quint16 value);
    void signalEventChangedGroupLamp                (quint16 value);
    void signalEventChangedGroupBuzzer              (quint16 value);
    void signalEventChangedUnderWeight              (quint32 value);
    void signalEventChangedUnderWarningWeight       (quint32 value);
    void signalEventChangedNormalWeight             (quint32 value);
    void signalEventChangedOverWarningWeight        (quint32 value);
    void signalEventChangedOverWeight               (quint32 value);
    void signalEventChangedTareWeight               (quint32 value);
    void signalEventChangedWCOverMotion             (quint16 value);
    void signalEventChangedWCUnderMotion            (quint16 value);
    void signalEventChangedWCEtcMotion              (quint16 value);
    void signalEventChangedWCNGLamp                 (quint16 value);
    void signalEventChangedWCNGBuzzer               (quint16 value);
    void signalEventChangedWCEnableEtcError         (quint16 value);
    void signalEventChangedDynamicFactor            (int     value);
    void signalEventChangedFilterCoefficient        (quint16 value);
    void signalEventChangedZeroDelayTime            (quint16 value);
    void signalEventChangedMeasureCueSign           (quint32 value);
    void signalEventChangedMeasureSection           (quint32 value);
    void signalEventChangedMDSenstivity             (quint16 value);
    void signalEventChangedMDNGMotion               (quint16 value);
    void signalEventChangedMDNGLamp                 (quint16 value);
    void signalEventChangedMDNGBuzzer               (quint16 value);
    void signalEventChangedMaxSpeed                 (int     value);

    void signalEventChangedIsEditNo                 (bool    value);
    void signalEventChangedIsEditName               (bool    value);
    void signalEventChangedIsEditLength             (bool    value);
    void signalEventChangedIsEditSpeed              (bool    value);
    void signalEventChangedIsEditMotorAcceleration  (bool    value);
    void signalEventChangedIsEditMotorDeceleration  (bool    value);
    void signalEventChangedIsEditGroupCount         (bool    value);
    void signalEventChangedIsEditGroupMotion        (bool    value);
    void signalEventChangedIsEditGroupLamp          (bool    value);
    void signalEventChangedIsEditGroupBuzzer        (bool    value);
    void signalEventChangedIsEditUnderWeight        (bool    value);
    void signalEventChangedIsEditUnderWarningWeight (bool    value);
    void signalEventChangedIsEditNormalWeight       (bool    value);
    void signalEventChangedIsEditOverWarningWeight  (bool    value);
    void signalEventChangedIsEditOverWeight         (bool    value);
    void signalEventChangedIsEditTareWeight         (bool    value);
    void signalEventChangedIsEditWCOverMotion       (bool    value);
    void signalEventChangedIsEditWCUnderMotion      (bool    value);
    void signalEventChangedIsEditWCEtcMotion        (bool    value);
    void signalEventChangedIsEditWCNGLamp           (bool    value);
    void signalEventChangedIsEditWCNGBuzzer         (bool    value);
    void signalEventChangedIsEditWCEnableEtcError   (bool    value);
    void signalEventChangedIsEditDynamicFactor      (bool    value);
    void signalEventChangedIsEditFilterCoefficient  (bool    value);
    void signalEventChangedIsEditZeroDelayTime      (bool    value);
    void signalEventChangedIsEditMeasureCueSign     (bool    value);
    void signalEventChangedIsEditMeasureSection     (bool    value);
    void signalEventChangedIsEditMDSenstivity       (bool    value);
    void signalEventChangedIsEditMDNGMotion         (bool    value);
    void signalEventChangedIsEditMDNGLamp           (bool    value);
    void signalEventChangedIsEditMDNGBuzzer         (bool    value);

public slots:
    Q_INVOKABLE void onCommandSetSeq                     (quint64 value){ setSeq               (value);}
    Q_INVOKABLE void onCommandSetNo                      (quint16 value){ setNo                (value);}
    Q_INVOKABLE void onCommandSetName                    (QString value){ setName              (value);}
    Q_INVOKABLE void onCommandSetLength                  (quint16 value){ setLength            (value);}
    Q_INVOKABLE void onCommandSetSpeed                   (quint16 value){ setSpeed             (value);}
    Q_INVOKABLE void onCommandSetMotorAcceleration       (quint32 value){ setMotorAcceleration (value);}
    Q_INVOKABLE void onCommandSetMotorDeceleration       (quint32 value){ setMotorDeceleration (value);}
    Q_INVOKABLE void onCommandSetGroupCount              (quint32 value){ setGroupCount        (value);}
    Q_INVOKABLE void onCommandSetGroupMotion             (quint16 value){ setGroupMotion       (value);}
    Q_INVOKABLE void onCommandSetGroupLamp               (quint16 value){ setGroupLamp         (value);}
    Q_INVOKABLE void onCommandSetGroupBuzzer             (quint16 value){ setGroupBuzzer       (value);}
    Q_INVOKABLE void onCommandSetUnderWeight             (quint32 value){ setUnderWeight       (value); setUnderWarningWeight(value);}
    Q_INVOKABLE void onCommandSetUnderWarningWeight      (quint32 value){ setUnderWarningWeight(value);}
    Q_INVOKABLE void onCommandSetNormalWeight            (quint32 value){ setNormalWeight      (value);}
    Q_INVOKABLE void onCommandSetOverWarningWeight       (quint32 value){ setOverWarningWeight (value);}
    Q_INVOKABLE void onCommandSetOverWeight              (quint32 value){ setOverWeight        (value); setOverWarningWeight (value);}
    Q_INVOKABLE void onCommandSetTareWeight              (quint32 value){ setTareWeight        (value);}
    Q_INVOKABLE void onCommandSetWCOverMotion            (quint16 value){ setWCOverMotion      (value);}
    Q_INVOKABLE void onCommandSetWCUnderMotion           (quint16 value){ setWCUnderMotion     (value);}
    Q_INVOKABLE void onCommandSetWCEtcMotion             (quint16 value){ setWCEtcMotion       (value);}
    Q_INVOKABLE void onCommandSetWCNGLamp                (quint16 value){ setWCNGLamp          (value);}
    Q_INVOKABLE void onCommandSetWCNGBuzzer              (quint16 value){ setWCNGBuzzer        (value);}
    Q_INVOKABLE void onCommandSetWCEnableEtcError        (bool    value){ setWCEnableEtcError  (value == true ? 1 : 0);}
    Q_INVOKABLE void onCommandSetDynamicFactor           (int     value){ setDynamicFactor     (value);}
    Q_INVOKABLE void onCommandSetFilterCoefficient       (quint16 value){ setFilterCoefficient (value);}
    Q_INVOKABLE void onCommandSetZeroDelayTime           (quint16 value){ setZeroDelayTime     (value);}
    Q_INVOKABLE void onCommandSetMeasureCueSign          (quint32 value){ setMeasureCueSign    (value);}
    Q_INVOKABLE void onCommandSetMeasureSection          (quint32 value){ setMeasureSection    (value);}
    Q_INVOKABLE void onCommandSetMDSenstivity            (quint16 value){ setMDSenstivity      (value);}
    Q_INVOKABLE void onCommandSetMDNGMotion              (quint16 value){ setMDNGMotion        (value);}
    Q_INVOKABLE void onCommandSetMDNGLamp                (quint16 value){ setMDNGLamp          (value);}
    Q_INVOKABLE void onCommandSetMDNGBuzzer              (quint16 value){ setMDNGBuzzer        (value);}

public:
    void reset()
    {
        setData(mModel.mSeq);
    }

    void setData(quint64 seq)
    {
        PDSettingDto * pPDSetting = pProductSP->findPD(seq);

        if(pPDSetting == nullptr)
        {
            setSeq                     (0 );
            setNo                      (0 );
            setName                    ("");
            setLength                  (0 );
            setSpeed                   (0 );
            setMotorAcceleration       (0 );
            setMotorDeceleration       (0 );
            setGroupCount              (0 );
            setGroupMotion             (0 );
            setGroupLamp               (0 );
            setGroupBuzzer             (0 );
            setUnderWeight             (0 );
            setUnderWarningWeight      (0 );
            setNormalWeight            (0 );
            setOverWarningWeight       (0 );
            setOverWeight              (0 );
            setTareWeight              (0 );
            setWCUnderMotion           (0 );
            setWCOverMotion            (0 );
            setWCEtcMotion             (0 );
            setWCNGLamp                (0 );
            setWCNGBuzzer              (0 );
            setWCEnableEtcError        (1 );
            setDynamicFactor           (0 );
            setFilterCoefficient       (0 );
            setZeroDelayTime           (0 );
            setMeasureCueSign          (0 );
            setMeasureSection          (0 );
            setMDSenstivity            (0 );
            setMDNGMotion              (0 );
            setMDNGLamp                (0 );
            setMDNGBuzzer              (0 );
            setWCAutoSetting           (false);
        }
        else
        {
            setSeq               (pPDSetting->mSeq          );
            setNo                (pPDSetting->mDspForm.mCommSetting.mProductNum );
            setName              (pPDSetting->mName         );
            setLength            (pPDSetting->mDspForm.mCommSetting.mLength               );
            setSpeed             (pPDSetting->mDspForm.mCommSetting.mSpeed                );
            setMotorAcceleration (pPDSetting->mDspForm.mCommSetting.mMotorAccelerationTime);
            setMotorDeceleration (pPDSetting->mDspForm.mCommSetting.mMotorDecelerationTime);
            setGroupCount        (pPDSetting->mDspForm.mCommSetting.mGroupCount           );
            setGroupMotion       (pPDSetting->mDspForm.mCommSetting.mGroupMotion          );
            setGroupLamp         (pPDSetting->mDspForm.mCommSetting.mGroupLamp            );
            setGroupBuzzer       (pPDSetting->mDspForm.mCommSetting.mGroupBuzzer          );
            setUnderWeight       (pPDSetting->mDspForm.mWCSetting.mUnderWeight            );
            setUnderWarningWeight(pPDSetting->mDspForm.mWCSetting.mUnderWarningWeight     );
            setNormalWeight      (pPDSetting->mDspForm.mWCSetting.mNormalWeight           );
            setOverWarningWeight (pPDSetting->mDspForm.mWCSetting.mOverWarningWeight      );
            setOverWeight        (pPDSetting->mDspForm.mWCSetting.mOverWeight             );
            setTareWeight        (pPDSetting->mDspForm.mWCSetting.mTareWeight             );
            setWCOverMotion      (pPDSetting->mDspForm.mWCSetting.mOverMotion             );
            setWCUnderMotion     (pPDSetting->mDspForm.mWCSetting.mUnderMotion            );
            setWCEtcMotion       (pPDSetting->mDspForm.mWCSetting.mEtcMotion              );
            setWCNGLamp          (pPDSetting->mDspForm.mWCSetting.mNGLamp                 );
            setWCNGBuzzer        (pPDSetting->mDspForm.mWCSetting.mNGBuzzer               );
            setWCEnableEtcError  (pPDSetting->mDspForm.mWCSetting.mEnableEtcError         );
            setDynamicFactor     (pPDSetting->mDspForm.mWCSetting.mDynamicFactor          );
            setFilterCoefficient (pPDSetting->mDspForm.mWCSetting.mFilterCoefficient      );
            setZeroDelayTime     (pPDSetting->mDspForm.mWCSetting.mZeroDelayTime          );
            setMeasureCueSign    (pPDSetting->mDspForm.mWCSetting.mMeasureCueSign         );
            setMeasureSection    (pPDSetting->mDspForm.mWCSetting.mMeasureSection         );
            setWCAutoSetting     (pPDSetting->mDspForm.mWCSetting.mAutoSetting            );
            setMDSenstivity      (pPDSetting->mDspForm.mMDSetting.mSenstivity             );
            setMDNGMotion        (pPDSetting->mDspForm.mMDSetting.mNGMotion               );
            setMDNGLamp          (pPDSetting->mDspForm.mMDSetting.mNGLamp                 );
            setMDNGBuzzer        (pPDSetting->mDspForm.mMDSetting.mNGBuzzer               );
        }

        setIsNew                   (false);
        setIsEditNo                (false);
        setIsEditName              (false);
        setIsEditLength            (false);
        setIsEditSpeed             (false);
        setIsEditMotorAcceleration (false);
        setIsEditMotorDeceleration (false);
        setIsEditGroupCount        (false);
        setIsEditGroupMotion       (false);
        setIsEditGroupLamp         (false);
        setIsEditGroupBuzzer       (false);
        setIsEditUnderWeight       (false);
        setIsEditUnderWarningWeight(false);
        setIsEditNormalWeight      (false);
        setIsEditOverWarningWeight (false);
        setIsEditOverWeight        (false);
        setIsEditTareWeight        (false);
        setIsEditWCOverMotion      (false);
        setIsEditWCUnderMotion     (false);
        setIsEditWCEtcMotion       (false);
        setIsEditWCNGLamp          (false);
        setIsEditWCNGBuzzer        (false);
        setIsEditWCEnableEtcError  (false);
        setIsEditDynamicFactor     (false);
        setIsEditFilterCoefficient (false);
        setIsEditZeroDelayTime     (false);
        setIsEditMeasureCueSign    (false);
        setIsEditMeasureSection    (false);
        setIsEditMDSenstivity      (false);
        setIsEditMDNGMotion        (false);
        setIsEditMDNGLamp          (false);
        setIsEditMDNGBuzzer        (false);
    }

    void setNewSetting(PDSettingDto newProduct)
    {
        setSeq               (newProduct.mSeq                                        );
        setNo                (newProduct.mDspForm.mCommSetting.mProductNum           );
        setName              (newProduct.mName                                       );
        setLength            (newProduct.mDspForm.mCommSetting.mLength               );
        setSpeed             (newProduct.mDspForm.mCommSetting.mSpeed                );
        setMotorAcceleration (newProduct.mDspForm.mCommSetting.mMotorAccelerationTime);
        setMotorDeceleration (newProduct.mDspForm.mCommSetting.mMotorDecelerationTime);
        setGroupCount        (newProduct.mDspForm.mCommSetting.mGroupCount           );
        setGroupMotion       (newProduct.mDspForm.mCommSetting.mGroupMotion          );
        setGroupLamp         (newProduct.mDspForm.mCommSetting.mGroupLamp            );
        setGroupBuzzer       (newProduct.mDspForm.mCommSetting.mGroupBuzzer          );
        setUnderWeight       (newProduct.mDspForm.mWCSetting.mUnderWeight            );
        setUnderWarningWeight(newProduct.mDspForm.mWCSetting.mUnderWarningWeight     );
        setNormalWeight      (newProduct.mDspForm.mWCSetting.mNormalWeight           );
        setOverWarningWeight (newProduct.mDspForm.mWCSetting.mOverWarningWeight      );
        setOverWeight        (newProduct.mDspForm.mWCSetting.mOverWeight             );
        setTareWeight        (newProduct.mDspForm.mWCSetting.mTareWeight             );
        setWCOverMotion      (newProduct.mDspForm.mWCSetting.mOverMotion             );
        setWCUnderMotion     (newProduct.mDspForm.mWCSetting.mUnderMotion            );
        setWCEtcMotion       (newProduct.mDspForm.mWCSetting.mEtcMotion              );
        setWCNGLamp          (newProduct.mDspForm.mWCSetting.mNGLamp                 );
        setWCNGBuzzer        (newProduct.mDspForm.mWCSetting.mNGBuzzer               );
        setWCEnableEtcError  (newProduct.mDspForm.mWCSetting.mEnableEtcError         );
        setDynamicFactor     (newProduct.mDspForm.mWCSetting.mDynamicFactor          );
        setFilterCoefficient (newProduct.mDspForm.mWCSetting.mFilterCoefficient      );
        setZeroDelayTime     (newProduct.mDspForm.mWCSetting.mZeroDelayTime          );
        setMeasureCueSign    (newProduct.mDspForm.mWCSetting.mMeasureCueSign         );
        setMeasureSection    (newProduct.mDspForm.mWCSetting.mMeasureSection         );
        setWCAutoSetting     (newProduct.mDspForm.mWCSetting.mAutoSetting            );
        setMDSenstivity      (newProduct.mDspForm.mMDSetting.mSenstivity             );
        setMDNGMotion        (newProduct.mDspForm.mMDSetting.mNGMotion               );
        setMDNGLamp          (newProduct.mDspForm.mMDSetting.mNGLamp                 );
        setMDNGBuzzer        (newProduct.mDspForm.mMDSetting.mNGBuzzer               );

        setIsNew                   (true);
        setIsEditNo                (true);
        setIsEditName              (true);
        setIsEditLength            (true);
        setIsEditSpeed             (true);
        setIsEditMotorAcceleration (true);
        setIsEditMotorDeceleration (true);
        setIsEditGroupCount        (true);
        setIsEditGroupMotion       (true);
        setIsEditGroupLamp         (true);
        setIsEditGroupBuzzer       (true);
        setIsEditUnderWeight       (true);
        setIsEditUnderWarningWeight(true);
        setIsEditNormalWeight      (true);
        setIsEditOverWarningWeight (true);
        setIsEditOverWeight        (true);
        setIsEditTareWeight        (true);
        setIsEditWCOverMotion      (true);
        setIsEditWCUnderMotion     (true);
        setIsEditWCEtcMotion       (true);
        setIsEditWCNGLamp          (true);
        setIsEditWCNGBuzzer        (true);
        setIsEditWCEnableEtcError  (true);
        setIsEditDynamicFactor     (true);
        setIsEditFilterCoefficient (true);
        setIsEditZeroDelayTime     (true);
        setIsEditMeasureCueSign    (true);
        setIsEditMeasureSection    (true);
        setIsEditMDSenstivity      (true);
        setIsEditMDNGMotion        (true);
        setIsEditMDNGLamp          (true);
        setIsEditMDNGBuzzer        (true);
    }
    explicit ProductSettingItemModel(QObject *parent = nullptr):QObject(parent){}

};

#endif // PRODUCTSETTINGITEMMODEL_H
