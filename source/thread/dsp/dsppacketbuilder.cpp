#include "dsppacketbuilder.h"

#include <QDebug>

#include "source/util/myalloc.h"

DspPacketBuilder::DspPacketBuilder(QObject *parent) : QObject(parent)
{
    memset(&mDataStore, 0x00, sizeof(StDataStore));
    mDataStore.mEvent.mEventCnt = 0xffffffff;
}

bool DspPacketBuilder::compareCmdDeviceStatus(StDeviceStatus * deviceStatus)
{
    if(mDataStore.mWCGraphOnOffCmd.mWCGraphOnOff != deviceStatus->mIsWeightCheckerGraphOn ||
       mDataStore.mMDGraphOnOffCmd.mMDGraphOnOff != deviceStatus->mIsMetalDetectorGraphOn)
        return false;

    return true;
}
void DspPacketBuilder::setZeroCmd()
{
    mDataStore.mZeroCmd.mZero = 1;
}
void DspPacketBuilder::setFactoryResetCmd()
{
    mDataStore.mFactoryResetCmd.mFactoryReset = 1;
}
void DspPacketBuilder::setWeightCaribCmd(quint16 value)
{
    mDataStore.mWeightCaribCmd.mWeightCarib = value;
}
void DspPacketBuilder::setRunCmd(quint16 value)
{
    mDataStore.mRunCmd.mRun = value;
}
void DspPacketBuilder::setWCGraphOnOffCmd (bool value)
{
    mDataStore.mWCGraphOnOffCmd.mWCGraphOnOff = value ? 1 : 0;
}
void DspPacketBuilder::setMDGraphOnOffCmd(bool value)
{
    mDataStore.mMDGraphOnOffCmd.mMDGraphOnOff = value ? 1 : 0;
}
void DspPacketBuilder::setDeviceIdCmd(quint32 value)
{
    mDataStore.mDeviceIdCmd.mDeviceId = value;
}
void DspPacketBuilder::setDeviceSetting(DspSettingDto deviceSetting)
{
    //unsigned int preDynamicFactor = mDataStore.mDeviceSetting.mDynamicFactor;
    memcpy(&mDataStore.mDeviceSetting, &deviceSetting.mDeviceSetting, sizeof(StDeviceSetting));
    //mDataStore.mDeviceSetting.mDynamicFactor = preDynamicFactor;
}

void DspPacketBuilder::setProductSetting(ProductSettingDto productSetting)
{
    memcpy(&mDataStore.mProductSetting, &productSetting.mProductSetting, sizeof(StProductSetting));
    //mDataStore.mDeviceSetting.mDynamicFactor            = productSetting.mDynamicFactor;
}

bool DspPacketBuilder::setDeviceStatus(StDeviceStatus * deviceStatus)
{
    if(memcmp(&mDataStore.mDeviceStatus, deviceStatus, sizeof(StDeviceStatus)) != 0)
    {
        memcpy(&mDataStore.mDeviceStatus, deviceStatus, sizeof(StDeviceStatus));
        return true;
    }

    return false;
}

bool DspPacketBuilder::setDeviceInfo(StDeviceInfo * deviceInfo)
{
    if(memcmp(&mDataStore.mDeviceInfo, deviceInfo, sizeof(StDeviceInfo)) != 0)
    {
        memcpy(&mDataStore.mDeviceInfo, deviceInfo, sizeof(StDeviceInfo));
        return true;
    }

    return false;
}

int DspPacketBuilder::setEvent(StEventInfo * eventInfo)
{
    bool isFirst = mDataStore.mEvent.mEventCnt == 0xffffffff ? true : false;

    // HMI만 재부팅될 경우 이전 이벤트가 중복되어 발생하여, 최초 이벤트 영역수신시에는 UI로 이벤트를 보내지 않는다.
    if(isFirst)
    {
        memcpy(&mDataStore.mEvent, eventInfo, sizeof(StEventInfo));
        return 0;
    }

    int addedCnt = eventInfo->mEventCnt - mDataStore.mEvent.mEventCnt;

    if(addedCnt != 0)
    {
        qDebug() << "dsp event cnt : "  << eventInfo->mEventCnt;        memcpy(&mDataStore.mEvent, eventInfo, sizeof(StEventInfo));
    }

    return addedCnt;
}

StPacket *  DspPacketBuilder::createReqPacketZeroCmd              (){ return createReqWritePacket(sizeof(StZeroCommand),                             ZeroCommandAddr,              (char *)(&(mDataStore.mZeroCmd))); }
StPacket *  DspPacketBuilder::createReqPacketFactoryResetCmd      (){ return createReqWritePacket(sizeof(StFactoryResetCommand),                     FactoryResetCommandAddr,      (char *)(&(mDataStore.mFactoryResetCmd))); }
StPacket *  DspPacketBuilder::createReqPacketWeightCaribCmd       (){ return createReqWritePacket(sizeof(StWeightCaribrationCommand),                WeightCaribCommandAddr,       (char *)(&(mDataStore.mWeightCaribCmd ))); }
StPacket *  DspPacketBuilder::createReqPacketRunCmd               (){ return createReqWritePacket(sizeof(StRunCommand),                              RunCommandAddr,               (char *)(&(mDataStore.mRunCmd))); }
StPacket *  DspPacketBuilder::createReqPacketWCGraphOnOffCmd      (){ return createReqWritePacket(sizeof(StWCGraphOnOffCommand),                     WCGraphOnOffCommandAddr,      (char *)(&(mDataStore.mWCGraphOnOffCmd))); }
StPacket *  DspPacketBuilder::createReqPacketMDGraphOnOffCmd      (){ return createReqWritePacket(sizeof(StMDGraphOnOffCommand),                     MDGraphOnOffCommandAddr,      (char *)(&(mDataStore.mMDGraphOnOffCmd))); }
StPacket *  DspPacketBuilder::createReqPacketDeviceIdCmd          (){ return createReqWritePacket(sizeof(StDeviceIdCommand),                         DeviceIdCommandAddr,          (char *)(&(mDataStore.mDeviceIdCmd))); }
StPacket *  DspPacketBuilder::createReqPacketDeviceStatusCmd      (){ return createReqWritePacket(sizeof(StWCGraphOnOffCommand) + sizeof(StMDGraphOnOffCommand), WCGraphOnOffCommandAddr, (char *)(&(mDataStore.mWCGraphOnOffCmd))); }
StPacket *  DspPacketBuilder::createReqPacketDeviceSetting        (){ return createReqWritePacket(sizeof(StDeviceSetting),                           DeviceSettingAddr,            (char *)(&(mDataStore.mDeviceSetting))); }
StPacket *  DspPacketBuilder::createReqPacketProductSetting       (){ return createReqWritePacket(sizeof(StProductSetting),                          ProductSettingAddr,           (char *)(&(mDataStore.mProductSetting))); }
StPacket *  DspPacketBuilder::createReqPacketTotalSetting         (){ return createReqWritePacket(sizeof(StProductSetting)+sizeof(StDeviceSetting),  DeviceSettingAddr,            (char *)(&(mDataStore.mDeviceSetting))); }
StPacket *  DspPacketBuilder::createReqWritePacket(int contentSize, quint64 startAddr, char * content)
{
    int mallocSize = sizeof(StPacket) + contentSize;
    StPacket * packet = (StPacket *)MyAlloc::myAlloc(mallocSize);

    if(packet == nullptr)
        return packet;

    packet->mFuncCode = EnumDefine::FuncCode::WRITE_TYPE;
    packet->mStartAddress = startAddr;
    packet->mSize = contentSize/2;
    memcpy( &(packet->mData), content, contentSize);
    return packet;
}

StPacket *  DspPacketBuilder::createReqPacketReadDeviceStatus     (){ return createReqReadPacket(sizeof(StDeviceStatus),                                                    DeviceStatusAddr );}
StPacket *  DspPacketBuilder::createReqPacketReadDeviceInfo       (){ return createReqReadPacket(sizeof(StDeviceInfo),                                                      DeviceInfoAddr   );}
StPacket *  DspPacketBuilder::createReqPacketReadEvent            (){ return createReqReadPacket(sizeof(StEventInfo),                                                       EventInfoAddr    );}
StPacket *  DspPacketBuilder::createReqPacketReadReadArea         (){ return createReqReadPacket(sizeof(StDeviceStatus)+sizeof(StDeviceInfo)+sizeof(StEventInfo),           DeviceStatusAddr );}
StPacket *  DspPacketBuilder::createReqPacketReadAll              (){ return createReqReadPacket(sizeof(StDeviceSetting)+sizeof(StProductSetting) + sizeof(StDeviceStatus)+sizeof(StDeviceInfo)+sizeof(StEventInfo) , DeviceSettingAddr);}
StPacket *  DspPacketBuilder::createReqReadPacket                 (int contentSize, quint64 startAddr)
{
    StPacket * packet = (StPacket *)MyAlloc::myAlloc(sizeof(StPacket)); //malloc(sizeof(StPacket));

    if(packet == nullptr)
        return packet;

    packet->mFuncCode = EnumDefine::FuncCode::READ_TYPE;
    packet->mStartAddress = startAddr;
    packet->mSize = contentSize/2;
    return packet;
}

StEvent* DspPacketBuilder::getEvent(int idx)
{
    return &(mDataStore.mEvent.mListEvent[idx]);
}
