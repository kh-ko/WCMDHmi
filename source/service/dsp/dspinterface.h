#ifndef DSPINTERFACE_H
#define DSPINTERFACE_H

#include <QObject>
#include <QUdpSocket>

#include "source/globaldef/EnumDefine.h"
#include "source/model/deviceconnectionInfo.h"
#include "source/model/devicesetting.h"
#include "source/model/productsetting.h"
#include "source/model/weightcheckergraphdata.h"
#include "source/model/metaldetectorgraphdata.h"
#include "source/service/dsp/dsppacketbuilder.h"
#include "source/service/dsp/sendpacketqueue.h"

class DSPInterface : public QObject
{
    Q_OBJECT
private:
    bool                    mIsConnect = true;
    quint8                  mPacketSeq;
    int                     mSentChecker;
    quint32                 mTickTimer;
    QHostAddress            mHostAddr;
    QUdpSocket *            mpSock = nullptr;
    SendPacketQueue         mSendQueue;

    void connectDevice();
    void sendPacket(StPacket * packet, bool isForce = false);

public:
    DeviceConnectionInfo mConnectionInfo;
    DspPacketBuilder     mPacketBuilder;

    explicit DSPInterface(DeviceConnectionInfo connectionInfo, DeviceSetting ds, ProductSetting ps, QObject *parent = nullptr);
    ~DSPInterface();
    void start();
    void setIsConnect(bool value);

public slots:
    void onSockError                                (QAbstractSocket::SocketError error);
    void onRecevie                                  ();
    void onTimeTick                                 ();
    void onCommandModifyConnectInfo                 (DeviceConnectionInfo connectInfo);
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

signals:
    void signalEventChangedIsConnect                (quint16 deviceSeq, bool value)                     ;
    void signalEventChangedRemoteDeviceSetting      (quint16 deviceSeq, DeviceSetting value)            ;
    void signalEventChangedRemoteProductSetting     (quint16 deviceSeq, ProductSetting value)           ;
    void signalEventChangedDeviceStatus             (quint16 deviceSeq, DeviceStatus value)             ;
    void signalEventChangedDeviceInfo               (quint16 deviceSeq, DeviceInfo value)               ;
    void signalEventAddedEvent                      (quint16 deviceSeq, EventInfo value)                ;
    void signalEventAddedWeightCheckerGraph         (quint16 deviceSeq, WeightChekerGraphData value)    ;
    void signalEventAddedMetalDetectorGraph         (quint16 deviceSeq, MetalDetectorGraphData value)   ;
    void signalEventAddedMetalDetectorFilterGraph   (quint16 deviceSeq, MetalDetectorGraphData value)   ;
    void signalEventCompletedFactorReset            (quint16 deviceSeq);
};

#endif // DSPINTERFACE_H
