#include "dspinterface.h"
#include "source/globaldef/GlobalDefine.h"


DSPInterface::DSPInterface(DeviceConnectionInfo connectionInfo, DeviceSetting ds, ProductSetting ps, QObject *parent) : QObject(parent)
{
    qDebug() << "DSPInterface : New";

    mConnectionInfo = connectionInfo;

    mPacketBuilder.setDeviceSetting(ds);
    mPacketBuilder.setProductSetting(ps);
}

void DSPInterface::start()
{
    connectDevice();
}

DSPInterface::~DSPInterface()
{

    qDebug() << "DSPInterface : Delete";

    if(mpSock != nullptr)
    {
        if(mpSock->isOpen())
            mpSock->close();

        delete mpSock;

        mpSock = nullptr;
    }

    mSendQueue.clear();
}

void DSPInterface::setIsConnect(bool value)
{
    if(mIsConnect == value)
        return;

    mIsConnect = value;

    qDebug() << "connect :" << (mIsConnect? "true" : "false");

    emit signalEventChangedIsConnect(mConnectionInfo.mSeq, value);
}

void DSPInterface::connectDevice()
{
    if(mpSock != nullptr)
    {
        if(mpSock->isOpen())
            mpSock->close();

        delete mpSock;

        mpSock = nullptr;
    }

    mSendQueue.clear();
    mPacketSeq = 0;
    mSentChecker = 0;
    mHostAddr.setAddress(mConnectionInfo.mIp);
    mpSock = new QUdpSocket();
    mpSock->connectToHost(mHostAddr, mConnectionInfo.mPort);
    connect(mpSock, SIGNAL(readyRead()), this, SLOT(onRecevie()));
    connect(mpSock,SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSockError(QAbstractSocket::SocketError)));
    sendPacket(mPacketBuilder.createReqPacketTotalSetting(), true);
    sendPacket(mPacketBuilder.createReqPacketReadAll(), true);
}

void DSPInterface::sendPacket(StPacket * packet, bool isForce)
{
    int packetSize;

    if(packet == NULL || packet == nullptr)
    {
        return;
    }

    if(mIsConnect == false && isForce == false)
    {
        MyAlloc::free(packet);
        return;
    }

    packet->mSeq = mPacketSeq;

    if(packet->mFuncCode == EnumDefine::FuncCode::WRITE_TYPE)
    {
        packetSize = sizeof(StPacket) + (packet->mSize) *2;
    }
    else if(packet->mFuncCode == EnumDefine::FuncCode::READ_TYPE)
    {
        packetSize = sizeof(StPacket);
    }
    else
    {
        qDebug() << "[FUNC ERROR]";
        MyAlloc::free(packet);
        return;
    }

#ifdef SOCKET_DEBUG
    QByteArray qByteArray((char *)(packet), packetSize);
    qDebug() << qByteArray.toHex();
#endif

    if(mpSock->writeDatagram((char *)packet, packetSize, mHostAddr, mConnectionInfo.mPort) < 1)
    {
        QByteArray qByteArray((char *)(packet), packetSize);
#ifdef SOCKET_DEBUG
        qDebug() << "[SEND FAILED PACKET]" << qByteArray.toHex();
#endif
        qDebug() << mpSock->errorString();

        MyAlloc::free(packet);
        setIsConnect(false);
        return;
    }

    mSendQueue.add(packet);
    mPacketSeq++;
}

void DSPInterface::onSockError(QAbstractSocket::SocketError error)
{
    qDebug() << "[SOCKET ERROR]" << error;
}

void DSPInterface::onRecevie()
{
    QByteArray rcvBuffer;
    QHostAddress sender;
    quint16 senderPort;
    StPacket *rPacketData;

    if(mpSock == nullptr)
    {
        qDebug() << "sock is null";
        return;
    }

    if(mpSock->hasPendingDatagrams() == false)
    {
        //qDebug() << "sock buff is null";
        return;
    }

    rcvBuffer.resize(mpSock->pendingDatagramSize());
    mpSock->readDatagram(rcvBuffer.data(), rcvBuffer.size(), &sender, &senderPort);
    rPacketData = (StPacket *)rcvBuffer.data();

#ifdef SOCKET_DEBUG
    qDebug() << "[PACKET] : " <<rcvBuffer.toHex();
#endif

    if(rPacketData->mFuncCode == EnumDefine::FuncCode::ERROR_ACK_TYPE)
    {
        qDebug() << " packet error ack";
        qDebug() << "[ERROR PACKET] : "<< rcvBuffer.toHex();
        return;
    }

    if(rPacketData->mFuncCode == EnumDefine::FuncCode::NOTI_TYPE || rPacketData->mFuncCode == EnumDefine::FuncCode::READ_TYPE)
    {
        if(rcvBuffer.size() != (int)(sizeof(StPacket) + (rPacketData->mSize * 2)))
        {
            qDebug() << "packet size error";
#ifdef SOCKET_DEBUG
            qDebug() << "[ERROR PACKET] : "<< rcvBuffer.toHex();
#endif

            return;
        }
    }

    if(rPacketData->mFuncCode == EnumDefine::FuncCode::WRITE_TYPE || rPacketData->mFuncCode == EnumDefine::FuncCode::READ_TYPE || rPacketData->mFuncCode == EnumDefine::FuncCode::ERROR_ACK_TYPE)
    {
        if(mSendQueue.remove(rPacketData) == false)
        {
            qDebug() << "packet seq error or content size error";
#ifdef SOCKET_DEBUG
            qDebug() << "[ERROR PACKET] : "<< rcvBuffer.toHex();
#endif
            return;
        }

        if(rPacketData->mFuncCode == EnumDefine::FuncCode::ERROR_ACK_TYPE)
        {
            qDebug() << " packet error ack";
#ifdef SOCKET_DEBUG
            qDebug() << "[ERROR PACKET] : "<< rcvBuffer.toHex();
#endif
        }

        mSentChecker = 0;

        setIsConnect(true); // 연결 상태는 NOTI 타입은 안보고 READ WRITE만 보고 판단한다. NOTI 는 누락체크 안되고 READ WRITE는 누락체크 되니깐
    }

    if(rPacketData->mFuncCode == EnumDefine::FuncCode::WRITE_TYPE && rPacketData->mStartAddress == FactoryResetCommandAddr)
    {
        emit signalEventCompletedFactorReset(mConnectionInfo.mSeq);
    }
    else if(rPacketData->mFuncCode == EnumDefine::FuncCode::NOTI_TYPE)
    {
        switch(rPacketData->mStartAddress)
        {
            case WeightCheckerGraphAddr:
            {
                WeightChekerGraphData wcg;

                if(wcg.setData(rPacketData->mSize, rPacketData->mData) == false)
                {
                    qDebug() << "[ERROR PACKET] : "<< rcvBuffer.toHex();
                    return;
                }

                emit signalEventAddedWeightCheckerGraph(mConnectionInfo.mSeq, wcg);
                break;
            }
            case MetalDetectorGraphAddr:
            {
                MetalDetectorGraphData mdrg;

                if(mdrg.setData(rPacketData->mSize, rPacketData->mData) == false)
                {
                    qDebug() << "[ERROR PACKET] : "<< rcvBuffer.toHex();
                    return;
                }
                //mdrg.setData(rPacketData->mData);

                emit signalEventAddedMetalDetectorGraph(mConnectionInfo.mSeq, mdrg);
                break;
            }
            /*case MetalDetectorFilterGraphAddr:
            {
                MetalDetectorGraphData mdfg;
                mdfg.setData(rPacketData->mData);

                emit signalEventAddedMetalDetectorFilterGraph(mConnectionInfo.mSeq, mdfg);
                break;
            }*/
        }

        return;
    }
    else if(rPacketData->mFuncCode == EnumDefine::FuncCode::READ_TYPE)
    {
        StDeviceSetting             * pDeviceSetting  = nullptr;
        StProductSetting            * pProductSetting = nullptr;
        StDeviceStatus              * pDeviceStatus   = nullptr;
        StDeviceInfo                * pDeviceInfo     = nullptr;
        StEventInfo                 * pEvent          = nullptr;


        if(rPacketData->mStartAddress == DeviceSettingAddr)
        {
            StReadAllContent *pContent  = (StReadAllContent*)(rPacketData->mData);
            pDeviceSetting              = &pContent->mDeviceSetting;
            pProductSetting             = &pContent->mProductSetting;
            pDeviceStatus               = &pContent->mDeviceStatus;
            pDeviceInfo                 = &pContent->mDeviceInfo;
            pEvent                      = &pContent->mEvent;
        }
        else if(rPacketData->mStartAddress == DeviceStatusAddr)
        {
            StReadReadAreaContent *pContent = (StReadReadAreaContent*)(rPacketData->mData);
            pDeviceStatus               = &pContent->mDeviceStatus;
            pDeviceInfo                 = &pContent->mDeviceInfo;
            pEvent                      = &pContent->mEvent;
        }

        pDeviceStatus->mMDSignal = (((qint16)pDeviceStatus->mMDSignal) < 0) ? ((qint16)pDeviceStatus->mMDSignal) * -1 : pDeviceStatus->mMDSignal;

        if(pDeviceSetting != nullptr)
        {
            emit signalEventChangedRemoteDeviceSetting(mConnectionInfo.mSeq, mPacketBuilder.createSignalObjDeviceSetting(pDeviceSetting));
        }

        if(pProductSetting != nullptr)
        {
            emit signalEventChangedRemoteProductSetting(mConnectionInfo.mSeq, mPacketBuilder.createSignalObjProductSetting(pProductSetting));
        }

        if(mPacketBuilder.compareCmdDeviceStatus(pDeviceStatus) == false)
        {
            qDebug() << "cmd device status missmatch";
            sendPacket(mPacketBuilder.createReqPacketDeviceStatusCmd());
        }

        if(mPacketBuilder.setDeviceStatus(pDeviceStatus))
        {
            DeviceStatus deviceStatus = mPacketBuilder.createSignalObjDeviceStatus();
            emit signalEventChangedDeviceStatus(mConnectionInfo.mSeq, deviceStatus);
        }

        if(mPacketBuilder.setDeviceInfo(pDeviceInfo))
        {
            DeviceInfo deviceInfo = mPacketBuilder.createSignalObjDeviceInfo();
            emit signalEventChangedDeviceInfo(mConnectionInfo.mSeq, deviceInfo);
        }

        int addEventCnt = mPacketBuilder.setEvent(pEvent);

        if(addEventCnt > 10)
            addEventCnt = 10;

        for(int i = addEventCnt - 1; i > -1; i-- )
        {
            EventInfo eventInfo = mPacketBuilder.createSignalObjEventInfo(i);
            emit signalEventAddedEvent(mConnectionInfo.mSeq, eventInfo);
        }

        //if(addEventCnt > 0)
        //{
        //    qDebug() << "[EVENT PACKET] : Cnt = " << addEventCnt << " : "<< rcvBuffer.toHex();
        //}
    }
}

void DSPInterface::onTimeTick()
{
    if(mIsConnect == false)
    {
        connectDevice();
        return;
    }

    mSentChecker ++;
    mTickTimer ++;

    if(mSentChecker > 3){ setIsConnect(false); connectDevice();}
    else if(mIsConnect)
    {
        sendPacket(mPacketBuilder.createReqPacketReadReadArea());
    }
}

void DSPInterface::onCommandModifyConnectInfo(DeviceConnectionInfo connectInfo)
{
    if(connectInfo.mSeq != mConnectionInfo.mSeq)
        return;

    mConnectionInfo = connectInfo;

    connectDevice();

}
void DSPInterface::onCommandSendZeroCmd (quint16 deviceSeq)
{
    if(deviceSeq != mConnectionInfo.mSeq && deviceSeq != 0xffff)
        return;

    mPacketBuilder.setZeroCmd();
    sendPacket(mPacketBuilder.createReqPacketZeroCmd());
}
void DSPInterface::onCommandSendFactoryResetCmd(quint16 deviceSeq)
{
    if(deviceSeq != mConnectionInfo.mSeq && deviceSeq != 0xffff)
        return;

    mPacketBuilder.setFactoryResetCmd();
    sendPacket(mPacketBuilder.createReqPacketFactoryResetCmd());
}

void DSPInterface::onCommandSendWeightCaribCmd(quint16 deviceSeq, quint16 value)
{
    if(deviceSeq != mConnectionInfo.mSeq && deviceSeq != 0xffff)
        return;

    mPacketBuilder.setWeightCaribCmd(value);
    sendPacket(mPacketBuilder.createReqPacketWeightCaribCmd());
}
void DSPInterface::onCommandSendRunCmd(quint16 deviceSeq, quint16 value)
{
    if(deviceSeq != mConnectionInfo.mSeq && deviceSeq != 0xffff)
        return;

    mPacketBuilder.setRunCmd(value);
    sendPacket(mPacketBuilder.createReqPacketRunCmd());
}
/*
void DSPInterface::onCommandSendRunModeCmd(quint16 deviceSeq, quint16 value)
{
    if(deviceSeq != mConnectionInfo.mSeq && deviceSeq != 0xffff)
        return;

    mPacketBuilder.setRunModeCmd(value);
    sendPacket(mPacketBuilder.createReqPacketRunModeCmd());
}*/
void DSPInterface::onCommandSendWeightCheckerGraphOnCmd(quint16 deviceSeq, bool value)
{
    if(deviceSeq != mConnectionInfo.mSeq && deviceSeq != 0xffff)
        return;

    mPacketBuilder.setWCGraphOnOffCmd(value);
    sendPacket(mPacketBuilder.createReqPacketWCGraphOnOffCmd());
}
void DSPInterface::onCommandSendMetalDetectorGraphOnCmd(quint16 deviceSeq, bool value)
{
    if(deviceSeq != mConnectionInfo.mSeq && deviceSeq != 0xffff)
        return;

    mPacketBuilder.setMDGraphOnOffCmd(value);
    sendPacket(mPacketBuilder.createReqPacketMDGraphOnOffCmd());
}
void DSPInterface::onCommandSendMetalDetectorFilterGraphOnCmd(quint16 deviceSeq, bool value)
{
    if(deviceSeq != mConnectionInfo.mSeq && deviceSeq != 0xffff)
        return;

    mPacketBuilder.setMDFilterGraphOnOffCmd(value);
    sendPacket(mPacketBuilder.createReqPacketMDFilterGraphOnOffCmd());
}
void DSPInterface::onCommandSendDeviceIDCmd(quint16 deviceSeq, quint32 value)
{
    if(deviceSeq != mConnectionInfo.mSeq && deviceSeq != 0xffff)
        return;

    mPacketBuilder.setDeviceIdCmd(value);
    sendPacket(mPacketBuilder.createReqPacketDeviceIdCmd());
}
void DSPInterface::onCommandSendDeviceSetting(quint16 deviceSeq, DeviceSetting value)
{
    if(deviceSeq != mConnectionInfo.mSeq && deviceSeq != 0xffff)
        return;

    mPacketBuilder.setDeviceSetting(value);
    sendPacket(mPacketBuilder.createReqPacketDeviceSetting());
    sendPacket(mPacketBuilder.createReqPacketReadAll());
}
void DSPInterface::onCommandSendProductSetting(quint16 deviceSeq, ProductSetting value)
{
    if(deviceSeq != mConnectionInfo.mSeq && deviceSeq != 0xffff)
        return;

    mPacketBuilder.setProductSetting(value);
    sendPacket(mPacketBuilder.createReqPacketTotalSetting());
    sendPacket(mPacketBuilder.createReqPacketReadAll());
}
