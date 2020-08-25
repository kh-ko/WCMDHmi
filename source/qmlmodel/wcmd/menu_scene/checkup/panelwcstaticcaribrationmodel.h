#ifndef PANELWCSTATICCARIBRATIONMODEL_H
#define PANELWCSTATICCARIBRATIONMODEL_H

#include <QObject>
#include <QTimer>
#include "source/globaldef/EnumDefine.h"
#include "source/service/wcmdservice.h"
#include "source/helper/databasehelper.h"
#include "source/helper/localsetting.h"

class PanelWCStaticCaribrationModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    isBusy            READ getIsBusy           NOTIFY signalEventChangedIsBusy        )
    Q_PROPERTY(quint32 standardWeight    READ getStandardWeight   NOTIFY signalEventChangedStandardWeight)
    Q_PROPERTY(quint32 currentWeight     READ getCurrentWeight    NOTIFY signalEventChangedCurrentWeight )

public:
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
        WCMDService * pWCMDService = WCMDService::getInstance();
        DSPManager  * pDspManager  = pWCMDService->mMapDSPManager.first();

        connect(this, SIGNAL(signalCommandWeightCarib(quint16, quint16)), pWCMDService, SLOT(onCommandWeightCarib(quint16, quint16)));
        connect(this, SIGNAL(signalCommandSaveDeviceSetting(void *, DeviceSetting)), pWCMDService, SLOT(onCommandSaveDeviceSetting(void *, DeviceSetting)));

        connect(pWCMDService, SIGNAL(signalEventAddedEvent(quint16, EventInfo)), this, SLOT(onSignalEventAddEvent(quint16, EventInfo)));
        connect(pWCMDService, SIGNAL(signalEventChangedDeviceStatus(quint16, DeviceStatus)), this, SLOT(onSignalEventChangedDeviceStatus(quint16, DeviceStatus)));

        if(pDspManager == nullptr)
        {
            qDebug() << "PanelWCStaticCaribrationModel() : erro -> not exist dsp";
           setCurrentWeight(0);
           return;
        }

        setStandardWeight(pWCMDService->mDeviceSetting.mStaticStandardWeight);
        setCurrentWeight(0);

        setIsBusy(false);
    }

signals:
    void    signalEventChangedIsBusy        (bool    value);
    void    signalEventChangedStandardWeight(quint32 value);
    void    signalEventChangedCurrentWeight (quint32 value);

    void    signalCommandWeightCarib(quint16 deviceSeq, quint16 type);
    void    signalCommandSaveDeviceSetting(void * sender, DeviceSetting ds);
    void    signalEventCompleteCalibration();

public slots:
    Q_INVOKABLE void onCommandCaribration()
    {
        qDebug() << "command static calibration";

        setIsBusy(true);
        emit signalCommandWeightCarib(0xffff, EnumDefine::WCCalibType::WC_CALIB_STATIC);
    }

    Q_INVOKABLE void onCommandSetStandardWeight(quint32 value)
    {
        DeviceSetting ds = WCMDService::getInstance()->mDeviceSetting;

        ds.mStaticStandardWeight = value;

        emit signalCommandSaveDeviceSetting(this, ds);
        setStandardWeight(value);
    }

    void onSignalEventChangedDeviceStatus(quint16 deviceSeq, DeviceStatus ds)
    {
        if(ds.mCurrWeight == 0)
        {
            setCurrentWeight(0);
        }
        else
        {
            setCurrentWeight(ds.mCurrWeight + WCMDService::getInstance()->mProductSetting.mTareWeight);
        }
    }

    void onSignalEventAddEvent(quint16 deviceSeq, EventInfo eventInfo)
    {
        if(eventInfo.mEventType != EnumDefine::EventType::WEIGHT_STATIC_CARI_TYPE)
        {
            return;
        }

        qDebug() << "static calibration complete : " << eventInfo.mEventValue;
        setIsBusy(false);

        emit signalEventCompleteCalibration();
        //ViewManager.toast.show(qsTr("Calibration is complete."))

        /*
        WCMDService * pWCMDService = WCMDService::getInstance();

        DeviceSetting ds = pWCMDService->mDeviceSetting;
        ds.mStaticFactor = eventInfo.mEventValue;


        emit signalCommandSaveDeviceSetting(this, ds);*/
    }

};
#endif // PANELWCSTATICCARIBRATIONMODEL_H
