#ifndef PANELWCDYNAMICCALIBRAIONMODEL_H
#define PANELWCDYNAMICCALIBRAIONMODEL_H

#include <QObject>
#include <QTimer>
#include "source/globaldef/EnumDefine.h"
#include "source/service/wcmdservice.h"
#include "source/helper/databasehelper.h"
#include "source/helper/localsetting.h"

class PanelWCDynamicCalibrationModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    isRemeasure    READ getIsRemeasure   NOTIFY signalEventChangedIsRemeasure )
    Q_PROPERTY(quint32 currWeight     READ getCurrWeight    NOTIFY signalEventChangedCurrWeight  )
    Q_PROPERTY(quint32 refWeight      READ getRefWeight     NOTIFY signalEventChangedRefWeight   )
    Q_PROPERTY(quint32 movingWeight   READ getMovingWeight  NOTIFY signalEventChangedMovingWeight)

public:
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

        WCMDService * pWCMDService = WCMDService::getInstance();
        DSPManager  * pDspManager  = pWCMDService->mMapDSPManager.first();

        connect(this, SIGNAL(signalCommandWeightCarib(quint16, quint16)), pWCMDService, SLOT(onCommandWeightCarib(quint16, quint16)));
        connect(this, SIGNAL(signalCommandSaveDeviceSetting(void *, DeviceSetting)), pWCMDService, SLOT(onCommandSaveDeviceSetting(void *, DeviceSetting)));
        connect(this, SIGNAL(signalCommandSetRun(quint16, quint16)), pWCMDService, SLOT(onCommandSetRun(quint16, quint16)));

        connect(pWCMDService, SIGNAL(signalEventAddedEvent         (quint16, EventInfo)),    this, SLOT(onSignalEventAddEvent           (quint16, EventInfo   )));
        connect(pWCMDService, SIGNAL(signalEventChangedDeviceStatus(quint16, DeviceStatus)), this, SLOT(onSignalEventChangedDeviceStatus(quint16, DeviceStatus)));

        if(pDspManager == nullptr)
        {
            qDebug() << "PanelWCDynamicCalibrationModel() : erro -> not exist dsp";
           setMovingWeight(0);
           return;
        }
        setCurrWeight(0);
        setRefWeight(pWCMDService->mDeviceSetting.mDynamicBaseWeight);
        setMovingWeight(0);
    }
    ~PanelWCDynamicCalibrationModel()
    {
        emit signalCommandSetRun(0xffff, (quint16)EnumDefine::RunState::STOP);
    }

signals:
    void    signalEventChangedIsRemeasure (bool    value);
    void    signalEventChangedRefWeight   (quint32 value);
    void    signalEventChangedMovingWeight(quint32 value);
    void    signalEventChangedCurrWeight  (quint32 value);
    void    signalEventCompleteCalibration(             );
    void    signalCommandSetRun(quint16 deviceSeq, quint16 value);
    void    signalCommandWeightCarib(quint16 deviceSeq, quint16 type);
    void    signalCommandSaveDeviceSetting(void * sender, DeviceSetting ds);

public slots:
    Q_INVOKABLE void onCommandCaribration()
    {
        qDebug() << "command dynamic calibration";

        emit signalCommandWeightCarib(0xffff, EnumDefine::WCCalibType::WC_CALIB_DYNAMIC);
    }

    Q_INVOKABLE void onCommandSetRefWeight(quint32 value)
    {
        DeviceSetting ds = WCMDService::getInstance()->mDeviceSetting;

        ds.mDynamicBaseWeight = value;

        emit signalCommandSaveDeviceSetting(this, ds);
        setRefWeight(value);
    }

    Q_INVOKABLE void onCommandRemeasurement()
    {
        setMovingWeight(0);

        emit signalCommandSetRun(0xffff, EnumDefine::RunState::CHECKUP_RUN);
    }

    Q_INVOKABLE void onCommandClosed()
    {
        emit signalCommandSetRun(0xffff, (quint16)EnumDefine::RunState::STOP);
    }

    void onSignalEventAddEvent(quint16 deviceSeq, EventInfo eventInfo)
    {
        if( eventInfo.mEventType == EnumDefine::EventType::WEIGHT_NORMAL_CHECK_TYPE         ||
            eventInfo.mEventType == EnumDefine::EventType::WEIGHT_UNDER_WARNING_CHECK_TYPE  ||
            eventInfo.mEventType == EnumDefine::EventType::WEIGHT_OVER_WARNING_CHECK_TYPE   ||
            eventInfo.mEventType == EnumDefine::EventType::WEIGHT_UNDER_CHECK_TYPE          ||
            eventInfo.mEventType == EnumDefine::EventType::WEIGHT_OVER_CHECK_TYPE           ||
            eventInfo.mEventType == EnumDefine::EventType::WEIGHT_ETCERROR_CHECK_TYPE)
        {
            return setMovingWeight(eventInfo.mEventValue+WCMDService::getInstance()->mProductSetting.mTareWeight);
        }

        if(eventInfo.mEventType == EnumDefine::EventType::WEIGHT_DYNAMIC_CARI_TYPE)
        {
            emit signalEventCompleteCalibration();
        }
    }

    void onSignalEventChangedDeviceStatus(quint16 deviceSeq, DeviceStatus ds)
    {
        if(ds.mCurrWeight == 0)
        {
            setCurrWeight(0);
        }
        else
        {
            setCurrWeight(ds.mCurrWeight + WCMDService::getInstance()->mProductSetting.mTareWeight);
        }
    }

};
#endif // PANELWCDYNAMICCALIBRAIONMODEL_H
