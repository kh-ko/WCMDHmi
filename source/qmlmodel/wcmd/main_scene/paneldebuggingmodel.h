#ifndef PANELDEBUGGINGMODEL_H
#define PANELDEBUGGINGMODEL_H

#include <QObject>
#include "source/service/coreservice.h"

class DebuggingItemModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    mIsMatch     READ getIsMatch     NOTIFY signalEventChangedIsMatch    );
    Q_PROPERTY(QString mName        READ getName        NOTIFY signalEventChangedName       );
    Q_PROPERTY(qint64  mRemoteValue READ getRemoteValue NOTIFY signalEventChangedRemoteValue);
    Q_PROPERTY(qint64  mLocalValue  READ getLocalValue  NOTIFY signalEventChangedLocalValue );

public:
    QString mName        = "";
    qint64  mRemoteValue = 0;
    qint64  mLocalValue  = 0;

    bool    getIsMatch    (){ return (mRemoteValue == mLocalValue);}
    QString getName       (){ return mName                        ;}
    qint64  getRemoteValue(){ return mRemoteValue                 ;}
    qint64  getLocalValue (){ return mLocalValue                  ;}

    void    setName       (QString value){ if(mName        == value) return; mName        = value; emit signalEventChangedName       (value);}
    void    setRemoteValue(qint64  value){ if(mRemoteValue == value) return; mRemoteValue = value; emit signalEventChangedRemoteValue(value);}
    void    setLocalValue (qint64  value){ if(mLocalValue  == value) return; mLocalValue  = value; emit signalEventChangedLocalValue (value);}

    void    setValue      (qint64  rValue, qint64 lValue)
    {
        if((rValue == lValue) != (getRemoteValue() == getLocalValue()))
        {
            setRemoteValue(rValue);
            setLocalValue (lValue);

            emit signalEventChangedIsMatch(rValue == lValue);
            return;
        }

        setRemoteValue(rValue);
        setLocalValue (lValue);
    }

signals:
    void signalEventChangedIsMatch    (bool    value);
    void signalEventChangedName       (QString value);
    void signalEventChangedRemoteValue(qint64  value);
    void signalEventChangedLocalValue (qint64  value);

public:
    explicit DebuggingItemModel(QObject *parent = nullptr): QObject(parent)
    {
    }

    explicit DebuggingItemModel(QString name, QObject *parent = nullptr): QObject(parent)
    {
        setName(name);
    }

    ~DebuggingItemModel()
    {
    }
};

class PanelDebuggingModel : public QObject
{
    Q_OBJECT
public slots:
    Q_INVOKABLE int  onCommandGetItemCount()
    {
        return DEV_SIZE_DIST_SORTER_04 + 1;
    }

    Q_INVOKABLE DebuggingItemModel * onCommandGetParamItem(int idx)
    {
        return mItemList.at(idx);
    }

    void onChangedRemotePDSetting(quint64 seq, DspPDSettingDto remote)
    {
        CHECK_FALSE_RETURN((mDspSeq == seq));

        mItemList.at(PD_NUM                )->setValue(remote.mCommSetting.mProductNum           , pProductSP->mCurrPD.mDspForm.mCommSetting.mProductNum           );
        mItemList.at(PD_LANGTH             )->setValue(remote.mCommSetting.mLength               , pProductSP->mCurrPD.mDspForm.mCommSetting.mLength               );
        mItemList.at(PD_SPEED              )->setValue(remote.mCommSetting.mSpeed                , pProductSP->mCurrPD.mDspForm.mCommSetting.mSpeed                );
        mItemList.at(PD_MOTOR_ACC_TIME     )->setValue(remote.mCommSetting.mMotorAccelerationTime, pProductSP->mCurrPD.mDspForm.mCommSetting.mMotorAccelerationTime);
        mItemList.at(PD_MOTOR_DEC_TIME     )->setValue(remote.mCommSetting.mMotorDecelerationTime, pProductSP->mCurrPD.mDspForm.mCommSetting.mMotorDecelerationTime);
        mItemList.at(PD_G_COUNT            )->setValue(remote.mCommSetting.mGroupCount           , pProductSP->mCurrPD.mDspForm.mCommSetting.mGroupCount           );
        mItemList.at(PD_G_MOTION           )->setValue(remote.mCommSetting.mGroupMotion          , pProductSP->mCurrPD.mDspForm.mCommSetting.mGroupMotion          );
        mItemList.at(PD_G_LAMP             )->setValue(remote.mCommSetting.mGroupLamp            , pProductSP->mCurrPD.mDspForm.mCommSetting.mGroupLamp            );
        mItemList.at(PD_G_BUZZER           )->setValue(remote.mCommSetting.mGroupBuzzer          , pProductSP->mCurrPD.mDspForm.mCommSetting.mGroupBuzzer          );
        mItemList.at(PD_WC_NOR_WEIGHT      )->setValue(remote.mWCSetting.mNormalWeight           , pProductSP->mCurrPD.mDspForm.mWCSetting.mNormalWeight           );
        mItemList.at(PD_WC_UNDER_WAR_WEIGHT)->setValue(remote.mWCSetting.mUnderWarningWeight     , pProductSP->mCurrPD.mDspForm.mWCSetting.mUnderWarningWeight     );
        mItemList.at(PD_WC_OVER_WAR_WEIGHT )->setValue(remote.mWCSetting.mOverWarningWeight      , pProductSP->mCurrPD.mDspForm.mWCSetting.mOverWarningWeight      );
        mItemList.at(PD_WC_UNDER_WEIGHT    )->setValue(remote.mWCSetting.mUnderWeight            , pProductSP->mCurrPD.mDspForm.mWCSetting.mUnderWeight            );
        mItemList.at(PD_WC_OVER_WEIGHT     )->setValue(remote.mWCSetting.mOverWeight             , pProductSP->mCurrPD.mDspForm.mWCSetting.mOverWeight             );
        mItemList.at(PD_WC_TARE_WEIGHT     )->setValue(remote.mWCSetting.mTareWeight             , pProductSP->mCurrPD.mDspForm.mWCSetting.mTareWeight             );
        mItemList.at(PD_WC_DYN_FAC         )->setValue(remote.mWCSetting.mDynamicFactor          , pProductSP->mCurrPD.mDspForm.mWCSetting.mDynamicFactor          );
        mItemList.at(PD_WC_ENABLE_ETC_ERR  )->setValue(remote.mWCSetting.mEnableEtcError         , pProductSP->mCurrPD.mDspForm.mWCSetting.mEnableEtcError         );
        mItemList.at(PD_WC_NG_LAMP         )->setValue(remote.mWCSetting.mNGLamp                 , pProductSP->mCurrPD.mDspForm.mWCSetting.mNGLamp                 );
        mItemList.at(PD_WC_NGBuzzer        )->setValue(remote.mWCSetting.mNGBuzzer               , pProductSP->mCurrPD.mDspForm.mWCSetting.mNGBuzzer               );
        mItemList.at(PD_WC_FILTER_COEFF    )->setValue(remote.mWCSetting.mFilterCoefficient      , pProductSP->mCurrPD.mDspForm.mWCSetting.mFilterCoefficient      );
        mItemList.at(PD_WC_MEASURE_CUE_SIGN)->setValue(remote.mWCSetting.mMeasureCueSign         , pProductSP->mCurrPD.mDspForm.mWCSetting.mMeasureCueSign         );
        mItemList.at(PD_WC_MEASURE_SECTION )->setValue(remote.mWCSetting.mMeasureSection         , pProductSP->mCurrPD.mDspForm.mWCSetting.mMeasureSection         );
        mItemList.at(PD_WC_AUTO_SETTING    )->setValue(remote.mWCSetting.mAutoSetting            , pProductSP->mCurrPD.mDspForm.mWCSetting.mAutoSetting            );
        mItemList.at(PD_WC_UNDER_MOTION    )->setValue(remote.mWCSetting.mUnderMotion            , pProductSP->mCurrPD.mDspForm.mWCSetting.mUnderMotion            );
        mItemList.at(PD_WC_OVER_MOTION     )->setValue(remote.mWCSetting.mOverMotion             , pProductSP->mCurrPD.mDspForm.mWCSetting.mOverMotion             );
        mItemList.at(PD_WC_ETC_MOTION      )->setValue(remote.mWCSetting.mEtcMotion              , pProductSP->mCurrPD.mDspForm.mWCSetting.mEtcMotion              );
        mItemList.at(PD_MD_SENSTIVITY      )->setValue(remote.mMDSetting.mSenstivity             , pProductSP->mCurrPD.mDspForm.mMDSetting.mSenstivity             );
        mItemList.at(PD_MD_NG_MOTION       )->setValue(remote.mMDSetting.mNGMotion               , pProductSP->mCurrPD.mDspForm.mMDSetting.mNGMotion               );
        mItemList.at(PD_MD_NG_LAMP         )->setValue(remote.mMDSetting.mNGLamp                 , pProductSP->mCurrPD.mDspForm.mMDSetting.mNGLamp                 );
        mItemList.at(PD_MD_NG_BUZZER       )->setValue(remote.mMDSetting.mNGBuzzer               , pProductSP->mCurrPD.mDspForm.mMDSetting.mNGBuzzer               );

        qDebug() << Q_FUNC_INFO << "---------------";

        for (int i = PD_NUM; i < PD_MD_NG_BUZZER + 1; i ++)
        {
            DebuggingItemModel * pItem = mItemList.at(i);
            qDebug() << pItem->getName() << " : Remote value = " << pItem->getRemoteValue()  <<", Local value = " << pItem->getLocalValue();
        }
    }

    void onChangedRemoteDevSetting(quint64 seq, DspDevSettingDto remote)
    {
        CHECK_FALSE_RETURN((mDspSeq == seq));

        mItemList.at(DEV_LAMP_TIME             )->setValue(remote.mCommSetting.mLampTime               , pLSettingSP->mDevSetting.mDspForm.mCommSetting.mLampTime               );
        mItemList.at(DEV_BUZZER_TIME           )->setValue(remote.mCommSetting.mBuzzerTime             , pLSettingSP->mDevSetting.mDspForm.mCommSetting.mBuzzerTime             );
        mItemList.at(DEV_SPEED_CONVERTER       )->setValue(remote.mCommSetting.mSpeedConverter         , pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSpeedConverter         );
        mItemList.at(DEV_MOTOR_DIR             )->setValue(remote.mCommSetting.mMotorDirection         , pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMotorDirection         );
        mItemList.at(DEV_MOTOR_TYPE            )->setValue(remote.mCommSetting.mMotorType              , pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMotorType              );
        mItemList.at(DEV_MOTOR_MD_RATIO        )->setValue(remote.mCommSetting.mMotorMDRatio           , pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMotorMDRatio           );
        mItemList.at(DEV_MOTOR_WC_RATIO        )->setValue(remote.mCommSetting.mMotorWCRatio           , pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMotorWCRatio           );
        mItemList.at(DEV_MOTOR_RJ_RATIO        )->setValue(remote.mCommSetting.mMotorRJRatio           , pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMotorRJRatio           );
        mItemList.at(DEV_MACHINE_MODE          )->setValue(remote.mCommSetting.mMachineMode            , pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMachineMode            );
        mItemList.at(DEV_SORTER01_RUNTIME_RATIO)->setValue(remote.mCommSetting.mSorter01RunTimeRatio   , pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter01RunTimeRatio   );
        mItemList.at(DEV_SORTER01_OPEN_TIME    )->setValue(remote.mCommSetting.mSorter01OpenTime       , pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter01OpenTime       );
        mItemList.at(DEV_SORTER02_RUNTIME_RATIO)->setValue(remote.mCommSetting.mSorter02RunTimeRatio   , pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter02RunTimeRatio   );
        mItemList.at(DEV_SORTER02_OPEN_TIME    )->setValue(remote.mCommSetting.mSorter02OpenTime       , pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter02OpenTime       );
        mItemList.at(DEV_SORTER03_RUNTIME_RATIO)->setValue(remote.mCommSetting.mSorter03RunTimeRatio   , pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter03RunTimeRatio   );
        mItemList.at(DEV_SORTER03_OPEN_TIME    )->setValue(remote.mCommSetting.mSorter03OpenTime       , pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter03OpenTime       );
        mItemList.at(DEV_SORTER04_RUNTIME_RATIO)->setValue(remote.mCommSetting.mSorter04RunTimeRatio   , pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter04RunTimeRatio   );
        mItemList.at(DEV_SORTER04_OPEN_TIME    )->setValue(remote.mCommSetting.mSorter04OpenTime       , pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter04OpenTime       );
        mItemList.at(DEV_SORTER01_VR_RATIO     )->setValue(remote.mCommSetting.mSorter01VRRatio        , pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter01VRRatio        );
        mItemList.at(DEV_SORTER02_VR_RATIO     )->setValue(remote.mCommSetting.mSorter02VRRatio        , pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter02VRRatio        );
        mItemList.at(DEV_SORTER03_VR_RATIO     )->setValue(remote.mCommSetting.mSorter03VRRatio        , pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter03VRRatio        );
        mItemList.at(DEV_SORTER04_VR_RATIO     )->setValue(remote.mCommSetting.mSorter04VRRatio        , pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter04VRRatio        );
        mItemList.at(DEV_WC_DP_STABILITY       )->setValue(remote.mWCSetting.mDisplayStability         , pLSettingSP->mDevSetting.mDspForm.mWCSetting.mDisplayStability         );
        mItemList.at(DEV_WC_MEASURE_CUE_SIGN   )->setValue(remote.mWCSetting.mMeasureCueSign           , pLSettingSP->mDevSetting.mDspForm.mWCSetting.mMeasureCueSign           );
        mItemList.at(DEV_WC_MIN_STATIC_WEIGHT  )->setValue(remote.mWCSetting.mMinStaticWeight          , pLSettingSP->mDevSetting.mDspForm.mWCSetting.mMinStaticWeight          );
        mItemList.at(DEV_WC_MIN_DYN_WEIGHT     )->setValue(remote.mWCSetting.mMinDynamicWeight         , pLSettingSP->mDevSetting.mDspForm.mWCSetting.mMinDynamicWeight         );
        mItemList.at(DEV_WC_SCALER             )->setValue(remote.mWCSetting.mScaler                   , pLSettingSP->mDevSetting.mDspForm.mWCSetting.mScaler                   );
        mItemList.at(DEV_WC_STATIC_FACTOR      )->setValue(remote.mWCSetting.mStaticFactor             , pLSettingSP->mDevSetting.mDspForm.mWCSetting.mStaticFactor             );
        mItemList.at(DEV_WC_PHOTO_IS_ON        )->setValue(remote.mWCSetting.mPhotoIsOn                , pLSettingSP->mDevSetting.mDspForm.mWCSetting.mPhotoIsOn                );
        mItemList.at(DEV_WC_STATIC_STD_WEIGHT  )->setValue(remote.mWCSetting.mStaticStandardWeight     , pLSettingSP->mDevSetting.mDspForm.mWCSetting.mStaticStandardWeight     );
        mItemList.at(DEV_WC_DYN_BASE_WEIGHT    )->setValue(remote.mWCSetting.mDynamicBaseWeight        , pLSettingSP->mDevSetting.mDspForm.mWCSetting.mDynamicBaseWeight        );
        mItemList.at(DEV_WC_REF_VLOTAGE        )->setValue(remote.mWCSetting.mRefVoltage               , pLSettingSP->mDevSetting.mDspForm.mWCSetting.mRefVoltage               );
        mItemList.at(DEV_WC_GRAPH_POINT_CNT    )->setValue(remote.mWCSetting.mGraphPointCnt            , pLSettingSP->mDevSetting.mDspForm.mWCSetting.mGraphPointCnt            );
        mItemList.at(DEV_MD_DETECT_MODE        )->setValue(remote.mMDSetting.mDetectMode               , pLSettingSP->mDevSetting.mDspForm.mMDSetting.mDetectMode               );
        mItemList.at(DEV_MD_DETECT_DETECT_TIME )->setValue(remote.mMDSetting.mDetectDetectTime         , pLSettingSP->mDevSetting.mDspForm.mMDSetting.mDetectDetectTime         );
        mItemList.at(DEV_MD_RUN_DETECT_TIME    )->setValue(remote.mMDSetting.mRunDetectTime            , pLSettingSP->mDevSetting.mDspForm.mMDSetting.mRunDetectTime            );
        mItemList.at(DEV_MD_SIGNAL_DELAY_TIME  )->setValue(remote.mMDSetting.mSignalDelayTime          , pLSettingSP->mDevSetting.mDspForm.mMDSetting.mSignalDelayTime          );
        mItemList.at(DEV_MD_PHOTO_IS_ON        )->setValue(remote.mMDSetting.mPhotoIsOn                , pLSettingSP->mDevSetting.mDspForm.mMDSetting.mPhotoIsOn                );
        mItemList.at(DEV_MD_SENSOR_CNT         )->setValue(remote.mMDSetting.mSensorCnt                , pLSettingSP->mDevSetting.mDspForm.mMDSetting.mSensorCnt                );
        mItemList.at(DEV_SIZE_SENSOR_LEN       )->setValue(remote.mSizeSetting.mSensorLength           , pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mSensorLength           );
        mItemList.at(DEV_SIZE_DIST_BTW_SENSOR  )->setValue(remote.mSizeSetting.mDistanceBtwSensor      , pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistanceBtwSensor      );
        mItemList.at(DEV_SIZE_DIST_TO_WC       )->setValue(remote.mSizeSetting.mDistanceToWeightChecker, pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistanceToWeightChecker);
        mItemList.at(DEV_SIZE_DIST_PHOTO_SENSOR)->setValue(remote.mSizeSetting.mDistancePhotoToSensor  , pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistancePhotoToSensor  );
        mItemList.at(DEV_SIZE_DIST_SORTER_01   )->setValue(remote.mSizeSetting.mDistToSorter01         , pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistToSorter01         );
        mItemList.at(DEV_SIZE_DIST_SORTER_02   )->setValue(remote.mSizeSetting.mDistToSorter02         , pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistToSorter02         );
        mItemList.at(DEV_SIZE_DIST_SORTER_03   )->setValue(remote.mSizeSetting.mDistToSorter03         , pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistToSorter03         );
        mItemList.at(DEV_SIZE_DIST_SORTER_04   )->setValue(remote.mSizeSetting.mDistToSorter04         , pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistToSorter04         );

        qDebug() << Q_FUNC_INFO << "---------------";

        for (int i = DEV_LAMP_TIME; i < DEV_SIZE_DIST_SORTER_04 + 1; i ++)
        {
            DebuggingItemModel * pItem = mItemList.at(i);
            qDebug() << pItem->getName() << " : Remote value = " << pItem->getRemoteValue()  <<", Local value = " << pItem->getLocalValue();
        }
    }

public:
    explicit PanelDebuggingModel(QObject *parent = nullptr):QObject(parent)
    {
        CHECK_FALSE_RETURN((pDspSP->mDspList.size() > 0));

        mDspSeq = pDspSP->mDspList[0]->mSeq;

        ENABLE_SLOT_DSP_CHANGED_REMOTE_DEVSETTING;
        ENABLE_SLOT_DSP_CHANGED_REMOTE_PDSETTING;

        CHECK_FALSE_RETURN((mDspSeq != 0));

        for(int i = 0; i < DEV_SIZE_DIST_SORTER_04 + 1; i ++)
        {
            mItemList.append(new DebuggingItemModel(mItemNames.at(i)));
        }

        DspMaster * pMaster = pDspSP->findDspMaster(mDspSeq);

        if(pMaster != nullptr)
        {
            onChangedRemoteDevSetting(mDspSeq, pMaster->mRcvDataStore.getDevSettingDto());
            onChangedRemotePDSetting(mDspSeq, pMaster->mRcvDataStore.getPDSettingDto());
        }

    }
private:
    quint64 mDspSeq                     = 0;
    QList<DebuggingItemModel *> mItemList;

    enum DebugItem{
        PD_NUM                     = 0,
        PD_LANGTH                  = PD_NUM                     + 1,
        PD_SPEED                   = PD_LANGTH                  + 1,
        PD_MOTOR_ACC_TIME          = PD_SPEED                   + 1,
        PD_MOTOR_DEC_TIME          = PD_MOTOR_ACC_TIME          + 1,
        PD_G_COUNT                 = PD_MOTOR_DEC_TIME          + 1,
        PD_G_MOTION                = PD_G_COUNT                 + 1,
        PD_G_LAMP                  = PD_G_MOTION                + 1,
        PD_G_BUZZER                = PD_G_LAMP                  + 1,
        PD_WC_NOR_WEIGHT           = PD_G_BUZZER                + 1,
        PD_WC_UNDER_WAR_WEIGHT     = PD_WC_NOR_WEIGHT           + 1,
        PD_WC_OVER_WAR_WEIGHT      = PD_WC_UNDER_WAR_WEIGHT     + 1,
        PD_WC_UNDER_WEIGHT         = PD_WC_OVER_WAR_WEIGHT      + 1,
        PD_WC_OVER_WEIGHT          = PD_WC_UNDER_WEIGHT         + 1,
        PD_WC_TARE_WEIGHT          = PD_WC_OVER_WEIGHT          + 1,
        PD_WC_DYN_FAC              = PD_WC_TARE_WEIGHT          + 1,
        PD_WC_ENABLE_ETC_ERR       = PD_WC_DYN_FAC              + 1,
        PD_WC_NG_LAMP              = PD_WC_ENABLE_ETC_ERR       + 1,
        PD_WC_NGBuzzer             = PD_WC_NG_LAMP              + 1,
        PD_WC_FILTER_COEFF         = PD_WC_NGBuzzer             + 1,
        PD_WC_MEASURE_CUE_SIGN     = PD_WC_FILTER_COEFF         + 1,
        PD_WC_MEASURE_SECTION      = PD_WC_MEASURE_CUE_SIGN     + 1,
        PD_WC_AUTO_SETTING         = PD_WC_MEASURE_SECTION      + 1,
        PD_WC_UNDER_MOTION         = PD_WC_AUTO_SETTING         + 1,
        PD_WC_OVER_MOTION          = PD_WC_UNDER_MOTION         + 1,
        PD_WC_ETC_MOTION           = PD_WC_OVER_MOTION          + 1,
        PD_MD_SENSTIVITY           = PD_WC_ETC_MOTION           + 1,
        PD_MD_NG_MOTION            = PD_MD_SENSTIVITY           + 1,
        PD_MD_NG_LAMP              = PD_MD_NG_MOTION            + 1,
        PD_MD_NG_BUZZER            = PD_MD_NG_LAMP              + 1,
        DEV_LAMP_TIME              = PD_MD_NG_BUZZER            + 1,
        DEV_BUZZER_TIME            = DEV_LAMP_TIME              + 1,
        DEV_SPEED_CONVERTER        = DEV_BUZZER_TIME            + 1,
        DEV_MOTOR_DIR              = DEV_SPEED_CONVERTER        + 1,
        DEV_MOTOR_TYPE             = DEV_MOTOR_DIR              + 1,
        DEV_MOTOR_MD_RATIO         = DEV_MOTOR_TYPE             + 1,
        DEV_MOTOR_WC_RATIO         = DEV_MOTOR_MD_RATIO         + 1,
        DEV_MOTOR_RJ_RATIO         = DEV_MOTOR_WC_RATIO         + 1,
        DEV_MACHINE_MODE           = DEV_MOTOR_RJ_RATIO         + 1,
        DEV_SORTER01_RUNTIME_RATIO = DEV_MACHINE_MODE           + 1,
        DEV_SORTER01_OPEN_TIME     = DEV_SORTER01_RUNTIME_RATIO + 1,
        DEV_SORTER02_RUNTIME_RATIO = DEV_SORTER01_OPEN_TIME     + 1,
        DEV_SORTER02_OPEN_TIME     = DEV_SORTER02_RUNTIME_RATIO + 1,
        DEV_SORTER03_RUNTIME_RATIO = DEV_SORTER02_OPEN_TIME     + 1,
        DEV_SORTER03_OPEN_TIME     = DEV_SORTER03_RUNTIME_RATIO + 1,
        DEV_SORTER04_RUNTIME_RATIO = DEV_SORTER03_OPEN_TIME     + 1,
        DEV_SORTER04_OPEN_TIME     = DEV_SORTER04_RUNTIME_RATIO + 1,
        DEV_SORTER01_VR_RATIO      = DEV_SORTER04_OPEN_TIME     + 1,
        DEV_SORTER02_VR_RATIO      = DEV_SORTER01_VR_RATIO      + 1,
        DEV_SORTER03_VR_RATIO      = DEV_SORTER02_VR_RATIO      + 1,
        DEV_SORTER04_VR_RATIO      = DEV_SORTER03_VR_RATIO      + 1,
        DEV_WC_DP_STABILITY        = DEV_SORTER04_VR_RATIO      + 1,
        DEV_WC_MEASURE_CUE_SIGN    = DEV_WC_DP_STABILITY        + 1,
        DEV_WC_MIN_STATIC_WEIGHT   = DEV_WC_MEASURE_CUE_SIGN    + 1,
        DEV_WC_MIN_DYN_WEIGHT      = DEV_WC_MIN_STATIC_WEIGHT   + 1,
        DEV_WC_SCALER              = DEV_WC_MIN_DYN_WEIGHT      + 1,
        DEV_WC_STATIC_FACTOR       = DEV_WC_SCALER              + 1,
        DEV_WC_PHOTO_IS_ON         = DEV_WC_STATIC_FACTOR       + 1,
        DEV_WC_STATIC_STD_WEIGHT   = DEV_WC_PHOTO_IS_ON         + 1,
        DEV_WC_DYN_BASE_WEIGHT     = DEV_WC_STATIC_STD_WEIGHT   + 1,
        DEV_WC_REF_VLOTAGE         = DEV_WC_DYN_BASE_WEIGHT     + 1,
        DEV_WC_GRAPH_POINT_CNT     = DEV_WC_REF_VLOTAGE         + 1,
        DEV_MD_DETECT_MODE         = DEV_WC_GRAPH_POINT_CNT     + 1,
        DEV_MD_DETECT_DETECT_TIME  = DEV_MD_DETECT_MODE         + 1,
        DEV_MD_RUN_DETECT_TIME     = DEV_MD_DETECT_DETECT_TIME  + 1,
        DEV_MD_SIGNAL_DELAY_TIME   = DEV_MD_RUN_DETECT_TIME     + 1,
        DEV_MD_PHOTO_IS_ON         = DEV_MD_SIGNAL_DELAY_TIME   + 1,
        DEV_MD_SENSOR_CNT          = DEV_MD_PHOTO_IS_ON         + 1,
        DEV_SIZE_SENSOR_LEN        = DEV_MD_SENSOR_CNT          + 1,
        DEV_SIZE_DIST_BTW_SENSOR   = DEV_SIZE_SENSOR_LEN        + 1,
        DEV_SIZE_DIST_TO_WC        = DEV_SIZE_DIST_BTW_SENSOR   + 1,
        DEV_SIZE_DIST_PHOTO_SENSOR = DEV_SIZE_DIST_TO_WC        + 1,
        DEV_SIZE_DIST_SORTER_01    = DEV_SIZE_DIST_PHOTO_SENSOR + 1,
        DEV_SIZE_DIST_SORTER_02    = DEV_SIZE_DIST_SORTER_01    + 1,
        DEV_SIZE_DIST_SORTER_03    = DEV_SIZE_DIST_SORTER_02    + 1,
        DEV_SIZE_DIST_SORTER_04    = DEV_SIZE_DIST_SORTER_03    + 1
    };

    QStringList mItemNames =
            {"Product number"                     ,    //PD_NUM
             "Product length"                     ,    //PD_LANGTH
             "Product speed"                      ,    //PD_SPEED
             "Product motor acc time"             ,    //PD_MOTOR_ACC_TIME
             "Product motro dec time"             ,    //PD_MOTOR_DEC_TIME
             "Product group count"                ,    //PD_G_COUNT
             "Product group motion"               ,    //PD_G_MOTION
             "Product group lamp"                 ,    //PD_G_LAMP
             "Product group buzzer"               ,    //PD_G_BUZZER
             "Product WC normal wieght"           ,    //PD_WC_NOR_WEIGHT
             "Product WC under warning weight"    ,    //PD_WC_UNDER_WAR_WEIGHT
             "Product WC over warning weight"     ,    //PD_WC_OVER_WAR_WEIGHT
             "Product WC under weight"            ,    //PD_WC_UNDER_WEIGHT
             "Product WC over weight"             ,    //PD_WC_OVER_WEIGHT
             "Product WC tare weight"             ,    //PD_WC_TARE_WEIGHT
             "Product WC dynamic factor"          ,    //PD_WC_DYN_FAC
             "Product WC enable etc error"        ,    //PD_WC_ENABLE_ETC_ERR
             "Product WC NG lamp"                 ,    //PD_WC_NG_LAMP
             "Product WC NG buzzer"               ,    //PD_WC_NGBuzzer
             "Product WC filter coefficient"      ,    //PD_WC_FILTER_COEFF
             "Product WC measure cue sign"        ,    //PD_WC_MEASURE_CUE_SIGN
             "Product WC measure section"         ,    //PD_WC_MEASURE_SECTION
             "Product WC auto setting"            ,    //PD_WC_AUTO_SETTING
             "Product WC under motion"            ,    //PD_WC_UNDER_MOTION
             "Product WC over motion"             ,    //PD_WC_OVER_MOTION
             "Product WC etc motino"              ,    //PD_WC_ETC_MOTION
             "Product MD senstivity"              ,    //PD_MD_SENSTIVITY
             "Product MD NG motion"               ,    //PD_MD_NG_MOTION
             "Product MD NG lamp"                 ,    //PD_MD_NG_LAMP
             "Product MD NG buzzer"               ,    //PD_MD_NG_BUZZER
             "Dev lamp time"                      ,    //DEV_LAMP_TIME
             "Dev buzzer time"                    ,    //DEV_BUZZER_TIME
             "Dev speed converter"                ,    //DEV_SPEED_CONVERTER
             "Dev motor direction"                ,    //DEV_MOTOR_DIR
             "Dev motor type"                     ,    //DEV_MOTOR_TYPE
             "Dev motor MD ratio"                 ,    //DEV_MOTOR_MD_RATIO
             "Dev motor WC ratio"                 ,    //DEV_MOTOR_WC_RATIO
             "Dev motor sorter ratio"             ,    //DEV_MOTOR_RJ_RATIO
             "Dev machine mode"                   ,    //DEV_MACHINE_MODE
             "Dev sorter 01 runtime ratio"        ,    //DEV_SORTER01_RUNTIME_RATIO
             "Dev sorter 01 open time"            ,    //DEV_SORTER01_OPEN_TIME
             "Dev sorter 02 runtime ratio"        ,    //DEV_SORTER02_RUNTIME_RATIO
             "Dev sorter 02 open time"            ,    //DEV_SORTER02_OPEN_TIME
             "Dev sorter 03 runtime ratio"        ,    //DEV_SORTER03_RUNTIME_RATIO
             "Dev sorter 03 open time"            ,    //DEV_SORTER03_OPEN_TIME
             "Dev sorter 04 runtime ratio"        ,    //DEV_SORTER04_RUNTIME_RATIO
             "Dev sorter 04 open time"            ,    //DEV_SORTER04_OPEN_TIME
             "Dev sorter 01 VR ratio"             ,    //DEV_SORTER01_VR_RATIO
             "Dev sorter 02 VR ratio"             ,    //DEV_SORTER02_VR_RATIO
             "Dev sorter 03 VR ratio"             ,    //DEV_SORTER03_VR_RATIO
             "Dev sorter 04 VR ratio"             ,    //DEV_SORTER04_VR_RATIO
             "Dev WC display stability"           ,    //DEV_WC_DP_STABILITY
             "Dev WC measure cue sign"            ,    //DEV_WC_MEASURE_CUE_SIGN
             "Dev WC minimum static weight"       ,    //DEV_WC_MIN_STATIC_WEIGHT
             "Dev WC minimum dynamic weight"      ,    //DEV_WC_MIN_DYN_WEIGHT
             "Dev WC scaler"                      ,    //DEV_WC_SCALER
             "Dev WC static factor"               ,    //DEV_WC_STATIC_FACTOR
             "Dev WC photo is no"                 ,    //DEV_WC_PHOTO_IS_ON
             "Dev WC static standard weight"      ,    //DEV_WC_STATIC_STD_WEIGHT
             "Dev WC dynamic base weight"         ,    //DEV_WC_DYN_BASE_WEIGHT
             "Dev WC reference voltage"           ,    //DEV_WC_REF_VLOTAGE
             "Dev WC graph point count"           ,    //DEV_WC_GRAPH_POINT_CNT
             "Dev MD detect mode"                 ,    //DEV_MD_DETECT_MODE
             "Dev MD detect detect time"          ,    //DEV_MD_DETECT_DETECT_TIME
             "Dev MD run detect time"             ,    //DEV_MD_RUN_DETECT_TIME
             "Dev MD signal delay time"           ,    //DEV_MD_SIGNAL_DELAY_TIME
             "Dev MD photo is on"                 ,    //DEV_MD_PHOTO_IS_ON
             "Dev MD sensor count"                ,    //DEV_MD_SENSOR_CNT
             "Dev size sensor length"             ,    //DEV_SIZE_SENSOR_LEN
             "Dev size distance between sensor"   ,    //DEV_SIZE_DIST_BTW_SENSOR
             "Dev size distance to weight checker",    //DEV_SIZE_DIST_TO_WC
             "Dev size distance photo sensor"     ,    //DEV_SIZE_DIST_PHOTO_SENSOR
             "Dev size distance sorter 01"        ,    //DEV_SIZE_DIST_SORTER_01
             "Dev size distance sorter 02"        ,    //DEV_SIZE_DIST_SORTER_02
             "Dev size distance sorter 03"        ,    //DEV_SIZE_DIST_SORTER_03
             "Dev size distance sorter 04"        };   //DEV_SIZE_DIST_SORTER_04
};
#endif // PANELDEBUGGINGMODEL_H
