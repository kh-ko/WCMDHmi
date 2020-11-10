#include "dspinterface.h"
#include "source/globaldef/GlobalDefine.h"

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
        return;
    }

    rcvBuffer.resize(mpSock->pendingDatagramSize());
    mpSock->readDatagram(rcvBuffer.data(), rcvBuffer.size(), &sender, &senderPort);
    rPacketData = (StPacket *)rcvBuffer.data();

    //qDebug() << "[debug]rcv packet : "<< rcvBuffer.toHex();

    if(rPacketData->mFuncCode == EnumDefine::FuncCode::ERROR_ACK_TYPE)
    {
        qDebug() << " packet error ack";
        qDebug() << "[ERROR PACKET] : "<< rcvBuffer.toHex();
        return;
    }

    if(rcvBuffer.size() < (int)sizeof(StPacket))
    {
        qDebug() << " packet error header size";
        qDebug() << "[ERROR PACKET] : "<< rcvBuffer.toHex();
        return;
    }

    if(rPacketData->mFuncCode == EnumDefine::FuncCode::NOTI_TYPE || rPacketData->mFuncCode == EnumDefine::FuncCode::READ_TYPE)
    {
        if(rcvBuffer.size() != (int)(sizeof(StPacket) + (rPacketData->mSize * 2)))
        {
            qDebug() << "[PACKET MISMATCH SIZE] : "<< rcvBuffer.toHex();
            return;
        }
    }

    if(rPacketData->mFuncCode == EnumDefine::FuncCode::WRITE_TYPE || rPacketData->mFuncCode == EnumDefine::FuncCode::READ_TYPE)
    {
        if(mSendQueue.remove(rPacketData) == false)
        {
            qDebug() << "[PACKET SEQ ERROR OR CONTENT SIZE] : "<< rcvBuffer.toHex();
            return;
        }
        mSentChecker = 0;
        setIsConnect(true);
    }

    if(rPacketData->mFuncCode == EnumDefine::FuncCode::WRITE_TYPE && rPacketData->mStartAddress == FactoryResetCommandAddr)
    {
        emit signalEventCompletedFactoryReset(mConnection.mDspSeq);
        return;
    }
    else if(rPacketData->mFuncCode == EnumDefine::FuncCode::NOTI_TYPE)
    {
        switch(rPacketData->mStartAddress)
        {
            case WeightCheckerGraphAddr:
            {
                QByteArray wcg((char *)rPacketData->mData, rPacketData->mSize * 2);

                int checkSize = ((StWeightCheckerGraph *)rPacketData->mData)->pointCnt * sizeof(StWeightCheckerGraphPoint);

                if(rPacketData->mSize < 1 || ((rPacketData->mSize * 2) != (checkSize + 2)))
                {
                    qDebug() << "WC Graph size error : " << rPacketData->mSize << ", pointDataSize size :" << checkSize;
                    return ;
                }

                emit signalEventAddedWeightCheckerGraph(mConnection.mDspSeq, wcg);

                break;
            }
            case MetalDetectorGraphAddr:
            {
                StMetalDetectorGraph * pTemp = (StMetalDetectorGraph *)rPacketData->mData;
                QByteArray mdrg((char *)rPacketData->mData, rPacketData->mSize * 2);

                int checkSize = (pTemp->mPointCnt * pTemp->mSensorCnt * sizeof(quint16) * 2);

                if(rPacketData->mSize < 2 || ((rPacketData->mSize * 2) != (checkSize + 4)))
                {
                    qDebug() << "MD Graph size error : " << rPacketData->mSize << ", checkSize size :" << checkSize;
                    return ;
                }

                emit signalEventAddedMetalDetectorGraph(mConnection.mDspSeq, mdrg);

                break;
            }
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
            DspSettingDto dspDto(pDeviceSetting);

            emit signalEventChangedRemoteDeviceSetting(mConnection.mDspSeq, dspDto);
        }

        if(pProductSetting != nullptr)
        {
            ProductSettingDto productSettingDto(pProductSetting/*, pDeviceSetting->mDynamicFactor*/);
            emit signalEventChangedRemoteProductSetting(mConnection.mDspSeq, productSettingDto);
        }

        if(mPacketBuilder.compareCmdDeviceStatus(pDeviceStatus) == false)
        {
            qDebug() << "cmd device status missmatch";
            qDebug() << "local wc g onoff : "  <<mPacketBuilder.mDataStore.mWCGraphOnOffCmd.mWCGraphOnOff;
            qDebug() << "remote wc g onoff : " << pDeviceStatus->mIsWeightCheckerGraphOn;
            qDebug() << "local md g onoff : "  << mPacketBuilder.mDataStore.mMDGraphOnOffCmd.mMDGraphOnOff;
            qDebug() << "remote md g onoff : " << pDeviceStatus->mIsMetalDetectorGraphOn;

            sendPacket(mPacketBuilder.createReqPacketDeviceStatusCmd());
        }

        if(mPacketBuilder.setDeviceStatus(pDeviceStatus))
        {
            DspStatusDto dspStatus(pDeviceStatus);
            emit signalEventChangedDeviceStatus(mConnection.mDspSeq, dspStatus);
        }

        if(mPacketBuilder.setDeviceInfo(pDeviceInfo))
        {
            DspInfoDto dspInfo(pDeviceInfo);
            emit signalEventChangedDeviceInfo(mConnection.mDspSeq, dspInfo);
        }

        int addEventCnt = mPacketBuilder.setEvent(pEvent);

        if(addEventCnt > 10)
            addEventCnt = 10;

        for(int i = addEventCnt - 1; i > -1; i-- )
        {
            EventDto eventDto(mPacketBuilder.getEvent(i));
            emit signalEventAddedEvent(mConnection.mDspSeq, eventDto);
        }
    }
}

void DSPInterface::onCommandStart()
{
    connectDevice();
}
void DSPInterface::onCommandTimeTick()
{
    if(mIsConnect == false)
    {
        connectDevice();
        return;
    }

    mSentChecker ++;
    mTickTimer ++;

    if(mSentChecker > 10)
    {
        setIsConnect(false);
        connectDevice();
        return;
    }

    sendPacket(mPacketBuilder.createReqPacketReadReadArea());
}

void DSPInterface::onCommandModifyConnectInfo(DspConnectionDto connectionDto)
{
    mConnection = connectionDto;
    setIsConnect(false);
    connectDevice();
}

void DSPInterface::onCommandSendZeroCmd()
{
    mPacketBuilder.setZeroCmd();
    sendPacket(mPacketBuilder.createReqPacketZeroCmd());
}
void DSPInterface::onCommandSendFactoryResetCmd()
{
    mIsFactoryReset = true;
    mPacketBuilder.setFactoryResetCmd();
    sendPacket(mPacketBuilder.createReqPacketFactoryResetCmd());
}
void DSPInterface::onCommandSendWeightCaribCmd(quint16 value)
{
    mPacketBuilder.setWeightCaribCmd(value);
    sendPacket(mPacketBuilder.createReqPacketWeightCaribCmd());
}
void DSPInterface::onCommandSendRunCmd(quint16 value)
{
    mPacketBuilder.setRunCmd(value);
    sendPacket(mPacketBuilder.createReqPacketRunCmd());
}
void DSPInterface::onCommandSendWeightCheckerGraphOnCmd(bool value)
{
    mPacketBuilder.setWCGraphOnOffCmd(value);
    sendPacket(mPacketBuilder.createReqPacketWCGraphOnOffCmd());
}
void DSPInterface::onCommandSendMetalDetectorGraphOnCmd(bool value)
{
    mPacketBuilder.setMDGraphOnOffCmd(value);
    sendPacket(mPacketBuilder.createReqPacketMDGraphOnOffCmd());
}
void DSPInterface::onCommandSendDeviceIDCmd(quint32 value)
{
    mPacketBuilder.setDeviceIdCmd(value);
    sendPacket(mPacketBuilder.createReqPacketDeviceIdCmd());
}
void DSPInterface::onCommandSendDeviceSetting(DspSettingDto value)
{
    mPacketBuilder.setDeviceSetting(value);
    sendPacket(mPacketBuilder.createReqPacketDeviceSetting());
    sendPacket(mPacketBuilder.createReqPacketReadAll());
}
void DSPInterface::onCommandSendProductSetting(ProductSettingDto value)
{
    mPacketBuilder.setProductSetting(value);
    sendPacket(mPacketBuilder.createReqPacketTotalSetting());
    sendPacket(mPacketBuilder.createReqPacketReadAll());
}

DSPInterface::DSPInterface(DspConnectionDto connectionInfo, DspSettingDto ds, ProductSettingDto ps, QObject *parent):QObject(parent)
{
    mConnection = connectionInfo;

    mPacketBuilder.setDeviceSetting(ds);
    mPacketBuilder.setProductSetting(ps);
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

    emit signalEventChangedIsConnect(mConnection.mDspSeq, value);
}

void DSPInterface::connectDevice()
{
    if(mpSock != nullptr)
    {
        if(mpSock->isOpen())
            mpSock->close();

        mpSock->deleteLater();

        mpSock = nullptr;
    }

    mSendQueue.clear();
    mPacketSeq = 0;
    mSentChecker = 0;


    mHostAddr.setAddress(mConnection.mIp);
    mpSock = new QUdpSocket();
    mpSock->connectToHost(mHostAddr, mConnection.mPort);

    if(mpSock->localAddress().toString().contains("0.0.0.0"))
    {
        if(mpSock->isOpen())
            mpSock->close();

        mpSock->deleteLater();

        mpSock = nullptr;

        qDebug() << "null ip ";

        return;
    }

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

    if(mpSock == nullptr)
    {
        MyAlloc::myFree(packet);
        return;
    }

    if(mIsConnect == false && isForce == false)
    {
        MyAlloc::myFree(packet);
        return;
    }

    if(mIsFactoryReset == true && packet->mStartAddress != FactoryResetCommandAddr)
    {
        MyAlloc::myFree(packet);
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
        MyAlloc::myFree(packet);
        return;
    }

    //qDebug() << "[debug]send packet size="<< packetSize;
    //qDebug() << "[debug]send addr size="<< packet->mSize;
    //QByteArray qByteArray((char *)(packet), packetSize);
    //qDebug() << "[debug]send packet="<< qByteArray.toHex();

    if(mpSock->writeDatagram((char *)packet, packetSize, mHostAddr, mConnection.mPort) < 1)
    {
        QByteArray qByteArray((char *)(packet), packetSize);
#ifdef SOCKET_DEBUG
        qDebug() << "[SEND FAILED PACKET]" << qByteArray.toHex();
#endif
        qDebug() << mpSock->errorString();

        MyAlloc::myFree(packet);
        setIsConnect(false);
        return;
    }

    mSendQueue.add(packet);
    mPacketSeq++;
}

