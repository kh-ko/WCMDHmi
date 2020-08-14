#include "dspservice.h"

#include <QDebug>
#include <QDateTime>

#include "source/helper/localsetting.h"

DSPService::DSPService(QObject *parent) : QObject(parent)
{
    qDebug() << "DSPService : New";

    moveToThread(&mThread);
    mThread.start();

    connect(&mThread, SIGNAL(started()), this, SLOT(onStarted()));
    connect(&mThread, SIGNAL(finished()), this, SLOT(onFinished()));
}

DSPService::~DSPService()
{
    qDebug() << "DSPService : Delete";

    mThread.quit();
    mThread.wait();
}

void DSPService::onStarted()
{
    qDebug() << "OnStared";

    mpTimer = new QTimer(this);
    mpTimer->setInterval(100);

    connect(mpTimer, SIGNAL(timeout()), this, SLOT(onTimeTick()));
    mpTimer->start();
}

void DSPService::onFinished()
{
    qDebug() << "OnFinished";
}

void DSPService::onTimeTick()
{
    if(mIsStop == false)
        emit signalTimeTick();
}

void DSPService::onCommandStopService()
{
    mIsStop = true;
}

void DSPService::onCommandAddDSP(DeviceConnectionInfo connectionInfo, DeviceSetting ds, ProductSetting ps)
{
    DSPInterface * pInterface = new DSPInterface(connectionInfo, ds, ps, this);
    connect(this, SIGNAL(signalTimeTick()), pInterface, SLOT(onTimeTick()));
    connect(this, SIGNAL(signalCommandModifyConnectInfo                (DeviceConnectionInfo)   ), pInterface, SLOT(onCommandModifyConnectInfo                 (DeviceConnectionInfo)    ));
    connect(this, SIGNAL(signalCommandSendZeroCmd                      (quint16)                ), pInterface, SLOT(onCommandSendZeroCmd                       (quint16)                 ));
    connect(this, SIGNAL(signalCommandSendFactoryResetCmd              (quint16)                ), pInterface, SLOT(onCommandSendFactoryResetCmd               (quint16)                 ));
    connect(this, SIGNAL(signalCommandSendWeightCaribCmd               (quint16, quint16)       ), pInterface, SLOT(onCommandSendWeightCaribCmd                (quint16, quint16)        ));
    connect(this, SIGNAL(signalCommandSendRunCmd                       (quint16, quint16)       ), pInterface, SLOT(onCommandSendRunCmd                        (quint16, quint16)        ));
    //connect(this, SIGNAL(signalCommandSendRunModeCmd                   (quint16, quint16)       ), pInterface, SLOT(onCommandSendRunModeCmd                    (quint16, quint16)        ));
    connect(this, SIGNAL(signalCommandSendWeightCheckerGraphOnCmd      (quint16, bool)          ), pInterface, SLOT(onCommandSendWeightCheckerGraphOnCmd       (quint16, bool)           ));
    connect(this, SIGNAL(signalCommandSendMetalDetectorGraphOnCmd      (quint16, bool)          ), pInterface, SLOT(onCommandSendMetalDetectorGraphOnCmd       (quint16, bool)           ));
    connect(this, SIGNAL(signalCommandSendMetalDetectorFilterGraphOnCmd(quint16, bool)          ), pInterface, SLOT(onCommandSendMetalDetectorFilterGraphOnCmd (quint16, bool)           ));
    connect(this, SIGNAL(signalCommandSendDeviceIDCmd                  (quint16, quint32)       ), pInterface, SLOT(onCommandSendDeviceIDCmd                   (quint16, quint32)        ));
    connect(this, SIGNAL(signalCommandSendDeviceSetting                (quint16, DeviceSetting) ), pInterface, SLOT(onCommandSendDeviceSetting                 (quint16, DeviceSetting)  ));
    connect(this, SIGNAL(signalCommandSendProductSetting               (quint16, ProductSetting)), pInterface, SLOT(onCommandSendProductSetting                (quint16, ProductSetting) ));

    connect(pInterface, SIGNAL(signalEventChangedIsConnect                (quint16, bool )                  ), this, SLOT(onSignalEventChangedIsConnect                (quint16 , bool )                  ));
    connect(pInterface, SIGNAL(signalEventCompletedFactorReset            (quint16)                         ), this, SLOT(onSignalEventCompletedFactoryReset           (quint16)                          ));
    connect(pInterface, SIGNAL(signalEventChangedRemoteDeviceSetting      (quint16, DeviceSetting)          ), this, SLOT(onSignalEventChangedRemoteDeviceSetting      (quint16, DeviceSetting)           ));
    connect(pInterface, SIGNAL(signalEventChangedRemoteProductSetting     (quint16, ProductSetting)         ), this, SLOT(onSignalEventChangedRemoteProductSetting     (quint16, ProductSetting)          ));
    connect(pInterface, SIGNAL(signalEventChangedDeviceStatus             (quint16, DeviceStatus )          ), this, SLOT(onSignalEventChangedDeviceStatus             (quint16 , DeviceStatus )          ));
    connect(pInterface, SIGNAL(signalEventChangedDeviceInfo               (quint16, DeviceInfo )            ), this, SLOT(onSignalEventChangedDeviceInfo               (quint16 , DeviceInfo )            ));
    connect(pInterface, SIGNAL(signalEventAddedEvent                      (quint16, EventInfo )             ), this, SLOT(onSignalEventAddedEvent                      (quint16 , EventInfo )             ));
    connect(pInterface, SIGNAL(signalEventAddedWeightCheckerGraph         (quint16, WeightChekerGraphData ) ), this, SLOT(onSignalEventAddedWeightCheckerGraph         (quint16 , WeightChekerGraphData ) ));
    connect(pInterface, SIGNAL(signalEventAddedMetalDetectorGraph         (quint16, MetalDetectorGraphData )), this, SLOT(onSignalEventAddedMetalDetectorGraph         (quint16 , MetalDetectorGraphData )));
    connect(pInterface, SIGNAL(signalEventAddedMetalDetectorFilterGraph   (quint16, MetalDetectorGraphData )), this, SLOT(onSignalEventAddedMetalDetectorFilterGraph   (quint16 , MetalDetectorGraphData )));
    mListDSPInterface.append(pInterface);

    pInterface->start();
}

void DSPService::onCommandRemoveDsp(quint16 deviceSeq)
{
    for(int i = 0; i < mListDSPInterface.size(); i ++)
    {
        if(mListDSPInterface.at(i)->mConnectionInfo.mSeq == deviceSeq)
        {
            delete mListDSPInterface.at(i);
            mListDSPInterface.removeAt(i);
        }
    }
}
void DSPService::onCommandModifyDSP                         (DeviceConnectionInfo dci)                         { if(mIsStop) return; emit signalCommandModifyConnectInfo                (dci);             }
void DSPService::onCommandSendZeroCmd                       (quint16 deviceSeq)                                { if(mIsStop) return; emit signalCommandSendZeroCmd                      (deviceSeq);       }
void DSPService::onCommandSendFactoryResetCmd               (quint16 deviceSeq)                                { if(mIsStop) return; emit signalCommandSendFactoryResetCmd              (deviceSeq);       }
void DSPService::onCommandSendWeightCaribCmd                (quint16 deviceSeq, quint16 value)                 { if(mIsStop) return; emit signalCommandSendWeightCaribCmd               (deviceSeq, value);}
void DSPService::onCommandSendRunCmd                        (quint16 deviceSeq, quint16 value)                 { if(mIsStop) return; emit signalCommandSendRunCmd                       (deviceSeq, value);}
//void DSPService::onCommandSendRunModeCmd                    (quint16 deviceSeq, quint16 value)                 { emit signalCommandSendRunModeCmd                   (deviceSeq, value);}
void DSPService::onCommandSendWeightCheckerGraphOnCmd       (quint16 deviceSeq, bool value)                    { if(mIsStop) return; emit signalCommandSendWeightCheckerGraphOnCmd      (deviceSeq, value);}
void DSPService::onCommandSendMetalDetectorGraphOnCmd       (quint16 deviceSeq, bool value)                    { if(mIsStop) return; emit signalCommandSendMetalDetectorGraphOnCmd      (deviceSeq, value);}
void DSPService::onCommandSendMetalDetectorFilterGraphOnCmd (quint16 deviceSeq, bool value)                    { if(mIsStop) return; emit signalCommandSendMetalDetectorFilterGraphOnCmd(deviceSeq, value);}
void DSPService::onCommandSendDeviceIDCmd                   (quint16 deviceSeq, quint32 value)                 { if(mIsStop) return; emit signalCommandSendDeviceIDCmd                  (deviceSeq, value);}
void DSPService::onCommandSendDeviceSetting                 (quint16 deviceSeq, DeviceSetting value)           { if(mIsStop) return; emit signalCommandSendDeviceSetting                (deviceSeq, value);}
void DSPService::onCommandSendProductSetting                (quint16 deviceSeq, ProductSetting value)          { if(mIsStop) return; emit signalCommandSendProductSetting               (deviceSeq, value);}

void DSPService::onSignalEventChangedIsConnect                (quint16 deviceSeq, bool value)                  { if(mIsStop) return; emit signalEventChangedIsConnect               (deviceSeq, value);}
void DSPService::onSignalEventCompletedFactoryReset           (quint16 deviceSeq)                              { if(mIsStop) return; emit signalEventCompletedFactoryReset          (deviceSeq);       }
void DSPService::onSignalEventChangedRemoteDeviceSetting      (quint16 deviceSeq, DeviceSetting value)         { if(mIsStop) return; emit signalEventChangedRemoteDeviceSetting     (deviceSeq, value);}
void DSPService::onSignalEventChangedRemoteProductSetting     (quint16 deviceSeq, ProductSetting value)        { if(mIsStop) return; emit signalEventChangedRemoteProductSetting    (deviceSeq, value);}
void DSPService::onSignalEventChangedDeviceStatus             (quint16 deviceSeq, DeviceStatus value)          { if(mIsStop) return; emit signalEventChangedDeviceStatus            (deviceSeq, value);}
void DSPService::onSignalEventChangedDeviceInfo               (quint16 deviceSeq, DeviceInfo value)            { if(mIsStop) return; emit signalEventChangedDeviceInfo              (deviceSeq, value);}
void DSPService::onSignalEventAddedEvent                      (quint16 deviceSeq, EventInfo value)             { if(mIsStop) return; emit signalEventAddedEvent                     (deviceSeq, value);}
void DSPService::onSignalEventAddedWeightCheckerGraph         (quint16 deviceSeq, WeightChekerGraphData value) { if(mIsStop) return; emit signalEventAddedWeightCheckerGraph        (deviceSeq, value);}
void DSPService::onSignalEventAddedMetalDetectorGraph         (quint16 deviceSeq, MetalDetectorGraphData value){ if(mIsStop) return; emit signalEventAddedMetalDetectorGraph        (deviceSeq, value);}
void DSPService::onSignalEventAddedMetalDetectorFilterGraph   (quint16 deviceSeq, MetalDetectorGraphData value){ if(mIsStop) return; emit signalEventAddedMetalDetectorFilterGraph  (deviceSeq, value);}
