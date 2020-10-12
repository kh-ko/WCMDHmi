#ifndef DSPINTERFACE_H
#define DSPINTERFACE_H

#include <QObject>
#include <QUdpSocket>

#include "source/globaldef/EnumDefine.h"
#include "source/model/dspconnectionmodel.h"
#include "source/model/dspsettingmodel.h"
#include "source/model/productsettingmodel.h"
#include "source/thread/dsp/dto/dspconnectiondto.h"
#include "source/thread/dsp/dto/dspsettingdto.h"
#include "source/thread/dsp/dto/dspstatusdto.h"
#include "source/thread/dsp/dto/dspinfodto.h"
#include "source/thread/dsp/dto/eventdto.h"
#include "source/thread/dsp/dto/productsettingdto.h"
#include "source/thread/dsp/dto/weightgraphdto.h"
#include "source/thread/dsp/dto/metalgraphdto.h"
#include "source/thread/dsp/dsppacketbuilder.h"
#include "source/thread/dsp/sendpacketqueue.h"

class DSPInterface : public QObject
{
    Q_OBJECT
private:
    bool                    mIsConnect = true;
    bool                    mIsFactoryReset = false;
    quint8                  mPacketSeq;
    int                     mSentChecker;
    quint32                 mTickTimer;
    QHostAddress            mHostAddr;
    QUdpSocket *            mpSock = nullptr;
    SendPacketQueue         mSendQueue;

public:
    DspConnectionDto        mConnection;
    DspPacketBuilder        mPacketBuilder;

public slots:
    void onSockError                                (QAbstractSocket::SocketError error);
    void onRecevie                                  ();

signals:
    void signalEventChangedIsConnect                (quint64 deviceSeq, bool value              );
    void signalEventChangedRemoteDeviceSetting      (quint64 deviceSeq, DspSettingDto value     );
    void signalEventChangedRemoteProductSetting     (quint64 deviceSeq, ProductSettingDto value );
    void signalEventChangedDeviceStatus             (quint64 deviceSeq, DspStatusDto value      );
    void signalEventChangedDeviceInfo               (quint64 deviceSeq, DspInfoDto value        );
    void signalEventAddedEvent                      (quint64 deviceSeq, EventDto value          );
    void signalEventAddedWeightCheckerGraph         (quint64 deviceSeq, QByteArray value        );
    void signalEventAddedMetalDetectorGraph         (quint64 deviceSeq, QByteArray value        );
    void signalEventCompletedFactoryReset           (quint64 deviceSeq                          );

public:
    void onCommandStart                             (                                );
    void onCommandTimeTick                          (                                );
    void onCommandModifyConnectInfo                 (DspConnectionDto connectInfo    );
    void onCommandSendZeroCmd                       (                                );
    void onCommandSendFactoryResetCmd               (                                );
    void onCommandSendWeightCaribCmd                (quint16 value                   );
    void onCommandSendRunCmd                        (quint16 value                   );
    void onCommandSendWeightCheckerGraphOnCmd       (bool value                      );
    void onCommandSendMetalDetectorGraphOnCmd       (bool value                      );
    void onCommandSendDeviceIDCmd                   (quint32 value                   );
    void onCommandSendDeviceSetting                 (DspSettingDto value             );
    void onCommandSendProductSetting                (ProductSettingDto value         );

    explicit DSPInterface(DspConnectionDto connectionInfo, DspSettingDto ds, ProductSettingDto ps, QObject *parent = nullptr);
    ~DSPInterface();

private:
    void setIsConnect(bool value);
    void connectDevice();
    void sendPacket(StPacket * packet, bool isForce = false);
};

#endif // DSPINTERFACE_H
