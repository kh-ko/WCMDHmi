#ifndef PANELWCDYNAMICCALIBRAIONMODEL_H
#define PANELWCDYNAMICCALIBRAIONMODEL_H

#include <QObject>
#include <QTimer>

#include "source/service/coreservice.h"

class PanelWCDynamicCalibrationModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    isRemeasure    READ getIsRemeasure   NOTIFY signalEventChangedIsRemeasure )
    Q_PROPERTY(quint32 currWeight     READ getCurrWeight    NOTIFY signalEventChangedCurrWeight  )
    Q_PROPERTY(quint32 refWeight      READ getRefWeight     NOTIFY signalEventChangedRefWeight   )
    Q_PROPERTY(quint32 movingWeight   READ getMovingWeight  NOTIFY signalEventChangedMovingWeight)

public:
    CoreService * mpCoreService = nullptr;
    DspStatusModel * mpDspStatus = nullptr;

    bool    mIsRemeasure ;
    quint32 mCurrWeight  ;
    quint32 mRefWeight   ;
    quint32 mMovingWeight;

    bool    getIsRemeasure (){ return mIsRemeasure ;}
    quint32 getCurrWeight  (){ return mCurrWeight  ;}
    quint32 getRefWeight   (){ return mRefWeight   ;}
    quint32 getMovingWeight(){ return mMovingWeight;}

    void    setIsRemeasure (bool    value){ if(value == mIsRemeasure ) return; mIsRemeasure  = value; emit signalEventChangedIsRemeasure (value);}
    void    setCurrWeight  (quint32 value){ if(value == mCurrWeight  ) return; mCurrWeight   = value; emit signalEventChangedCurrWeight  (value);}
    void    setRefWeight   (quint32 value){ if(value == mRefWeight   ) return; mRefWeight    = value; emit signalEventChangedRefWeight   (value);}
    void    setMovingWeight(quint32 value){ if(value == mMovingWeight) return; mMovingWeight = value; emit signalEventChangedMovingWeight(value);}

    explicit PanelWCDynamicCalibrationModel(QObject *parent = nullptr) : QObject(parent)
    {
        mpCoreService = CoreService::getInstance();
        mpDspStatus = mpCoreService->mMapDspStatus.first();

        connect(mpDspStatus, SIGNAL(siganlEventAddedEvent         (quint16, quint32)), this, SLOT(onSignalEventAddEvent           (quint16, quint32)));
        connect(mpDspStatus, SIGNAL(signalEventChangedWCCurrWeight(quint32         )), this, SLOT(onSignalEventChangedWCCurrWeight(quint32         )));

        setCurrWeight(0);
        setRefWeight(mpCoreService->mLocalSettingService.mDspSetting.mDynamicBaseWeight);
        setMovingWeight(0);
    }
    ~PanelWCDynamicCalibrationModel()
    {
        mpCoreService->onCommandSendRunCmd(INVALID_ULONGLONG, EnumDefine::RunState::STOP);
    }

signals:
    void    signalEventChangedIsRemeasure (bool    value);
    void    signalEventChangedRefWeight   (quint32 value);
    void    signalEventChangedMovingWeight(quint32 value);
    void    signalEventChangedCurrWeight  (quint32 value);
    void    signalEventCompleteCalibration(             );

public slots:
    Q_INVOKABLE void onCommandCaribration()
    {
        mpCoreService->onCommandSendWeightCaribCmd(mpDspStatus->mSeq, EnumDefine::WCCalibType::WC_CALIB_DYNAMIC);
    }

    Q_INVOKABLE void onCommandSetRefWeight(quint32 value)
    {
        mpCoreService->onCommandEditDspSetting(mpCoreService->mLocalSettingService.mDspSetting.mLampTime               ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mBuzzerTime             ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mSpeedConverter         ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mMotorDirection         ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mMotorType              ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mMotorMDRatio           ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mMotorWCRatio           ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mMotorRJRatio           ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mSensorLength           ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mDistanceToRejector     ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mMDPhotoIsOn            ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mWCPhotoIsOn            ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mRejectorReadyTime      ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mRejectorRunTimeRatio   ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mStaticFactor           ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mScaler                 ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mDisplayStability       ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mMeasureCueSign         ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mMinStaticWeight        ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mMinDynamicWeight       ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mMode                   ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mDistanceBtwSensor      ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mDetectDetectTime       ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mRunDetectTime          ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mDistanceToWeightChecker,
                                               mpCoreService->mLocalSettingService.mDspSetting.mDistancePhotoToSensor  ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mSignalDelayTime        ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mStaticStandardWeight   ,
                                               value                                                                   ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mSensorCnt              ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mRejectorOpenTime       );
        setRefWeight(value);
    }

    Q_INVOKABLE void onCommandRemeasurement()
    {
        setMovingWeight(0);
        mpCoreService->onCommandSendRunCmd(INVALID_ULONGLONG, EnumDefine::RunState::CHECKUP_RUN);
    }

    Q_INVOKABLE void onCommandClosed()
    {
        mpCoreService->onCommandSendRunCmd(INVALID_ULONGLONG, EnumDefine::RunState::STOP);
    }

    void onSignalEventAddEvent(quint16 eventType, quint32 value)
    {
        if( eventType == EnumDefine::EventType::WEIGHT_NORMAL_CHECK_TYPE         ||
            eventType == EnumDefine::EventType::WEIGHT_UNDER_WARNING_CHECK_TYPE  ||
            eventType == EnumDefine::EventType::WEIGHT_OVER_WARNING_CHECK_TYPE   ||
            eventType == EnumDefine::EventType::WEIGHT_UNDER_CHECK_TYPE          ||
            eventType == EnumDefine::EventType::WEIGHT_OVER_CHECK_TYPE           ||
            eventType == EnumDefine::EventType::WEIGHT_ETCERROR_CHECK_TYPE)
        {
            return setMovingWeight(value+mpCoreService->mProductSettingServcie.mCurrentProductSetting.mTareWeight);
        }

        if(eventType == EnumDefine::EventType::WEIGHT_DYNAMIC_CARI_TYPE)
        {
            emit signalEventCompleteCalibration();
        }
    }

    void onSignalEventChangedWCCurrWeight(quint32 value)
    {
        if(value == 0)
        {
            setCurrWeight(0);
        }
        else
        {
            return setCurrWeight(value+mpCoreService->mProductSettingServcie.mCurrentProductSetting.mTareWeight);
        }
    }

};
#endif // PANELWCDYNAMICCALIBRAIONMODEL_H
