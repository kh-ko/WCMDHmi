#ifndef PANELWCSTATICCARIBRATIONMODEL_H
#define PANELWCSTATICCARIBRATIONMODEL_H

#include <QObject>
#include <QTimer>
#include "source/service/coreservice.h"

class PanelWCStaticCaribrationModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    isBusy            READ getIsBusy           NOTIFY signalEventChangedIsBusy        )
    Q_PROPERTY(quint32 standardWeight    READ getStandardWeight   NOTIFY signalEventChangedStandardWeight)
    Q_PROPERTY(quint32 currentWeight     READ getCurrentWeight    NOTIFY signalEventChangedCurrentWeight )

public:
    CoreService * mpCoreService = nullptr;
    DspStatusModel * mpDspStatus = nullptr;

    bool    mIsBusy        ;
    quint32 mStandardWeight;
    quint32 mCurrentWeight ;

    bool    getIsBusy        (){ return mIsBusy        ;}
    quint32 getStandardWeight(){ return mStandardWeight;}
    quint32 getCurrentWeight (){ return mCurrentWeight ;}

    void    setIsBusy        (bool    value) { if(value == mIsBusy)         return; mIsBusy         = value; emit signalEventChangedIsBusy        (value);}
    void    setStandardWeight(quint32 value) { if(value == mStandardWeight) return; mStandardWeight = value; emit signalEventChangedStandardWeight(value);}
    void    setCurrentWeight (quint32 value) { if(value == mCurrentWeight ) return; mCurrentWeight  = value; emit signalEventChangedCurrentWeight (value);}

    explicit PanelWCStaticCaribrationModel(QObject *parent = nullptr) : QObject(parent)
    {
        mpCoreService = CoreService::getInstance();
        mpDspStatus = mpCoreService->mMapDspStatus.first();

        connect(mpDspStatus, SIGNAL(siganlEventAddedEvent         (quint16, quint32)), this, SLOT(onSignalEventAddEvent           (quint16, quint32)));
        connect(mpDspStatus, SIGNAL(signalEventChangedWCCurrWeight(quint32         )), this, SLOT(onSignalEventChangedWCCurrWeight(quint32        )));

        setStandardWeight(mpCoreService->mLocalSettingService.mDspSetting.mStaticStandardWeight);
        setCurrentWeight(0);

        setIsBusy(false);
    }

signals:
    void    signalEventChangedIsBusy        (bool    value);
    void    signalEventChangedStandardWeight(quint32 value);
    void    signalEventChangedCurrentWeight (quint32 value);

    void    signalCommandWeightCarib(quint16 deviceSeq, quint16 type);
    void    signalEventCompleteCalibration();

public slots:
    Q_INVOKABLE void onCommandCaribration()
    {
        setIsBusy(true);
        mpCoreService->onCommandSendWeightCaribCmd(mpDspStatus->mSeq, EnumDefine::WCCalibType::WC_CALIB_STATIC);
    }

    Q_INVOKABLE void onCommandSetStandardWeight(quint32 value)
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
                                               value                                                                   ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mDynamicBaseWeight      ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mSensorCnt              ,
                                               mpCoreService->mLocalSettingService.mDspSetting.mRejectorOpenTime       );
        setStandardWeight(value);
    }

    void onSignalEventAddEvent(quint16 eventType, quint32 value)
    {

        if(eventType== EnumDefine::EventType::WEIGHT_STATIC_CARI_TYPE)
        {
            setIsBusy(false);
            emit signalEventCompleteCalibration();
            return;
        }
    }

    void onSignalEventChangedWCCurrWeight(quint32 value)
    {
        if(value == 0)
        {
            setCurrentWeight(0);
        }
        else
        {
            setCurrentWeight(value+mpCoreService->mProductSettingServcie.mCurrentProductSetting.mTareWeight);
        }
    }

};
#endif // PANELWCSTATICCARIBRATIONMODEL_H
