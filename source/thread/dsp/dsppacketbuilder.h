#ifndef DSPPACKETBUILDER_H
#define DSPPACKETBUILDER_H

#include <QObject>

#include "source/globaldef/EnumDefine.h"
#include "source/thread/dsp/dto/dspaddressdto.h"
#include "source/thread/dsp/dto/dspsettingdto.h"
#include "source/thread/dsp/dto/productsettingdto.h"
#include "source/thread/dsp/dto/dspstatusdto.h"
#include "source/thread/dsp/dto/dspinfodto.h"
#include "source/thread/dsp/dto/eventdto.h"

class DspPacketBuilder : public QObject
{
    Q_OBJECT
public:
    StDataStore         mDataStore;
    explicit            DspPacketBuilder(QObject *parent = nullptr);
    bool                compareDeviceSetting                (StDeviceSetting * pDeviceSetting);
    bool                compareProductSetting               (StProductSetting * pProductSetting);
    bool                compareCmdDeviceStatus              (StDeviceStatus * deviceStatus);
    void                setZeroCmd                          ();
    void                setFactoryResetCmd                  ();
    void                setWeightCaribCmd                   (quint16 value);
    void                setRunCmd                           (quint16 value);
    void                setRunModeCmd                       (quint16 value);
    void                setWCGraphOnOffCmd                  (bool value);
    void                setMDGraphOnOffCmd                  (bool value);
    void                setMDFilterGraphOnOffCmd            (bool value);
    void                setDeviceIdCmd                      (quint32 value);
    void                setDeviceSetting                    (DspSettingDto deviceSetting);
    void                setProductSetting                   (ProductSettingDto productSetting);
    bool                setDeviceStatus                     (StDeviceStatus * deviceStatus);
    bool                setDeviceInfo                       (StDeviceInfo * deviceInfo);
    int                 setEvent                            (StEventInfo * eventInfo);
    StPacket *          createReqPacketZeroCmd              ();
    StPacket *          createReqPacketFactoryResetCmd      ();
    StPacket *          createReqPacketWeightCaribCmd       ();
    StPacket *          createReqPacketRunCmd               ();
    StPacket *          createReqPacketRunModeCmd           ();
    StPacket *          createReqPacketWCGraphOnOffCmd      ();
    StPacket *          createReqPacketMDGraphOnOffCmd      ();
    StPacket *          createReqPacketMDFilterGraphOnOffCmd();
    StPacket *          createReqPacketDeviceIdCmd          ();
    StPacket *          createReqPacketDeviceStatusCmd      ();
    StPacket *          createReqPacketDeviceSetting        ();
    StPacket *          createReqPacketProductSetting       ();
    StPacket *          createReqPacketTotalSetting         ();
    StPacket *          createReqWritePacket                (int mallocSize, quint64 startAddr, char * content);
    StPacket *          createReqPacketReadDeviceStatus     ();
    StPacket *          createReqPacketReadDeviceInfo       ();
    StPacket *          createReqPacketReadEvent            ();
    StPacket *          createReqPacketReadReadArea         ();
    StPacket *          createReqPacketReadAll              ();
    StPacket *          createReqReadPacket                 (int contentSize, quint64 startAddr);

    StEvent  *          getEvent                            (int idx);
};

#endif // DSPPACKETBUILDER_H
