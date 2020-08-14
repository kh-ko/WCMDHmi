#ifndef DSPSERVICE_H
#define DSPSERVICE_H

#include <QObject>
#include <QTimer>
#include <QThread>

#include "source/globaldef/EnumDefine.h"
#include "source/model/deviceconnectionInfo.h"
#include "source/model/productsetting.h"
#include "source/model/devicesetting.h"
#include "source/model/devicestatus.h"
#include "source/model/deviceinfo.h"
#include "source/model/eventinfo.h"
#include "source/model/weightcheckergraphdata.h"
#include "source/model/metaldetectorgraphdata.h"
#include "source/service/dsp/dspinterface.h"
#include "source/service/dsp/myalloc.h"

class DSPService : public QObject
{
    Q_OBJECT
private:
    MyAlloc mMyMlloc;
    QThread mThread;
    QTimer* mpTimer = nullptr;
    QList<DSPInterface *> mListDSPInterface;
    bool    mIsStop = false;

public:
    explicit DSPService(QObject *parent = nullptr);
    ~DSPService();

public slots:
    // internal slot
    void onStarted();
    void onFinished();
    void onTimeTick();

    // qml slot
    void onCommandStopService                       ();
    void onCommandAddDSP                            (DeviceConnectionInfo connectionInfo, DeviceSetting ds, ProductSetting ps);
    void onCommandRemoveDsp                         (quint16 deviceSeq);
    void onCommandModifyDSP                         (DeviceConnectionInfo dci);
    void onCommandSendZeroCmd                       (quint16 deviceSeq);
    void onCommandSendFactoryResetCmd               (quint16 deviceSeq);
    void onCommandSendWeightCaribCmd                (quint16 deviceSeq, quint16 value);
    void onCommandSendRunCmd                        (quint16 deviceSeq, quint16 value);
    //void onCommandSendRunModeCmd                    (quint16 deviceSeq, quint16 value);
    void onCommandSendWeightCheckerGraphOnCmd       (quint16 deviceSeq, bool value);
    void onCommandSendMetalDetectorGraphOnCmd       (quint16 deviceSeq, bool value);
    void onCommandSendMetalDetectorFilterGraphOnCmd (quint16 deviceSeq, bool value);
    void onCommandSendDeviceIDCmd                   (quint16 deviceSeq, quint32 value);
    void onCommandSendDeviceSetting                 (quint16 deviceSeq, DeviceSetting value);
    void onCommandSendProductSetting                (quint16 deviceSeq, ProductSetting value);

    // dsp slot
    void onSignalEventChangedIsConnect                (quint16 deviceSeq, bool value)                     ;
    void onSignalEventCompletedFactoryReset           (quint16 deviceSeq)                                 ;
    void onSignalEventChangedRemoteDeviceSetting      (quint16 deviceSeq, DeviceSetting value)            ;
    void onSignalEventChangedRemoteProductSetting     (quint16 deviceSeq, ProductSetting value)           ;
    void onSignalEventChangedDeviceStatus             (quint16 deviceSeq, DeviceStatus value)             ;
    void onSignalEventChangedDeviceInfo               (quint16 deviceSeq, DeviceInfo value)               ;
    void onSignalEventAddedEvent                      (quint16 deviceSeq, EventInfo value)                ;
    void onSignalEventAddedWeightCheckerGraph         (quint16 deviceSeq, WeightChekerGraphData value)    ;
    void onSignalEventAddedMetalDetectorGraph         (quint16 deviceSeq, MetalDetectorGraphData value)   ;
    void onSignalEventAddedMetalDetectorFilterGraph   (quint16 deviceSeq, MetalDetectorGraphData value)   ;


signals:
    // signal dsp
    void signalTimeTick();
    void signalCommandModifyConnectInfo                 (DeviceConnectionInfo connectInfo)        ;
    void signalCommandSendZeroCmd                       (quint16 deviceSeq)                       ;
    void signalCommandSendFactoryResetCmd               (quint16 deviceSeq)                       ;
    void signalCommandSendWeightCaribCmd                (quint16 deviceSeq, quint16 value)        ;
    void signalCommandSendRunCmd                        (quint16 deviceSeq, quint16 value)        ;
    //void signalCommandSendRunModeCmd                    (quint16 deviceSeq, quint16 value)        ;
    void signalCommandSendWeightCheckerGraphOnCmd       (quint16 deviceSeq, bool value)           ;
    void signalCommandSendMetalDetectorGraphOnCmd       (quint16 deviceSeq, bool value)           ;
    void signalCommandSendMetalDetectorFilterGraphOnCmd (quint16 deviceSeq, bool value)           ;
    void signalCommandSendDeviceIDCmd                   (quint16 deviceSeq, quint32 value)        ;
    void signalCommandSendDeviceSetting                 (quint16 deviceSeq, DeviceSetting value)  ;
    void signalCommandSendProductSetting                (quint16 deviceSeq, ProductSetting value) ;

    // signal qml
    void signalEventChangedIsConnect                    (quint16 deviceSeq, bool value)                  ;
    void signalEventCompletedFactoryReset               (quint16 deviceSeq)                              ;
    void signalEventChangedRemoteDeviceSetting          (quint16 deviceSeq, DeviceSetting value)         ;
    void signalEventChangedRemoteProductSetting         (quint16 deviceSeq, ProductSetting value)        ;
    void signalEventChangedDeviceStatus                 (quint16 deviceSeq, DeviceStatus value)          ;
    void signalEventChangedDeviceInfo                   (quint16 deviceSeq, DeviceInfo value)            ;
    void signalEventAddedEvent                          (quint16 deviceSeq, EventInfo value)             ;
    void signalEventAddedWeightCheckerGraph             (quint16 deviceSeq, WeightChekerGraphData value) ;
    void signalEventAddedMetalDetectorGraph             (quint16 deviceSeq, MetalDetectorGraphData value);
    void signalEventAddedMetalDetectorFilterGraph       (quint16 deviceSeq, MetalDetectorGraphData value);
};

#endif // DSPSERVICE_H
