#ifndef DSPMASTER_H
#define DSPMASTER_H

#include <QObject>
#include <QDateTime>
#include <QUdpSocket>

#include "source/service/dsp/dspsendqueue.h"
#include "source/service/dsp/dspdatastore.h"
#include "source/service/util/exceptionutil.h"

class DspMaster : public QObject
{
    Q_OBJECT

public :
    quint64              mSeq               = 0;
    bool                 mIsDevSettingAlarm = false;
    bool                 mIsPDSettingAlarm  = false;
    QString              mIp                = "";
    quint16              mPort              = 0;
    bool                 mIsConnect         = true;
    EnumDef::eDspFRState mFRState = EnumDef::DSP_FR_STATE_NONE;
    DspDataStore         mSndDataStore   ;
    DspDataStore         mRcvDataStore   ;

    explicit DspMaster(quint64 seq, QString ip, quint16 port, DspDevSettingDto devSetting, DspPDSettingDto  pdSetting, QObject *parent = nullptr):QObject(parent)
    {
        mSeq  = seq ;
        mIp   = ip  ;
        mPort = port;

        // 초기 셋팅값을 모두 설정해주어야 최초 connect 시 바로 설정값을 내려 보낼수 있다.
        // data stroe에 setxx 을 호출하면 data store에서는 byte swap하여 값을 가지고 있음.
        mSndDataStore.setDevCommSetting(&devSetting.mCommSetting);
        mSndDataStore.setDevWCSetting  (&devSetting.mWCSetting  );
        mSndDataStore.setDevMDSetting  (&devSetting.mMDSetting  );
        mSndDataStore.setDevSizeSetting(&devSetting.mSizeSetting);
        mSndDataStore.setPDCommSetting (&pdSetting.mCommSetting );
        mSndDataStore.setPDWCSetting   (&pdSetting.mWCSetting   );
        mSndDataStore.setPDMDSetting   (&pdSetting.mMDSetting   );
    }
    ~DspMaster()
    {
        disconnectDsp();
    }

    void sendZero(unsigned short value)
    {
        DspSendQueueItem * pItem = new (DspSendQueueItem);
        mSndDataStore.setCmdZero(value);

        pItem->mPacket.setFuncCode(DSP_FUNCCODE_MULTIBLOCK_WRITE);
        pItem->mPacket.addWriteBlock(mSndDataStore.mCommandBlock.mTag.mGroupID, DSP_COMMANDBLOCK_STARTADDR_ZERO, 1, mSndDataStore.mCommandBlock.mTag.mDataPtr);
        if(mSendQueue.push(pItem))
        {
            sendPacketInQueue();
        }
        else
        {
            delete pItem;
        }
    }
    void sendFR(unsigned short value)
    {
        DspSendQueueItem * pItem = new (DspSendQueueItem);
        pItem->mIsFRPacket = true;
        mSndDataStore.setCmdFR(value);

        pItem->mPacket.setFuncCode(DSP_FUNCCODE_MULTIBLOCK_WRITE);
        pItem->mPacket.addWriteBlock(mSndDataStore.mCommandBlock.mTag.mGroupID, DSP_COMMANDBLOCK_STARTADDR_FR, 1, mSndDataStore.mCommandBlock.mTag.mDataPtr);
        if(mSendQueue.push(pItem))
        {
            sendPacketInQueue();
        }
        else
        {
            delete pItem;
        }
    }
    void sendWCCarib(unsigned short value)
    {
        DspSendQueueItem * pItem = new (DspSendQueueItem);
        mSndDataStore.setCmdWCCarib(value);

        pItem->mPacket.setFuncCode(DSP_FUNCCODE_MULTIBLOCK_WRITE);
        pItem->mPacket.addWriteBlock(mSndDataStore.mCommandBlock.mTag.mGroupID, DSP_COMMANDBLOCK_STARTADDR_WCCARIB, 1, mSndDataStore.mCommandBlock.mTag.mDataPtr);
        if(mSendQueue.push(pItem))
        {
            sendPacketInQueue();
        }
        else
        {
            delete pItem;
        }
    }
    void sendRun(unsigned short value)
    {
        DspSendQueueItem * pItem = new (DspSendQueueItem);
        mSndDataStore.setCmdRun(value);

        qDebug() << "[DspModbusMaster::sendRun]";
        pItem->mPacket.setFuncCode(DSP_FUNCCODE_MULTIBLOCK_WRITE);
        pItem->mPacket.addWriteBlock(mSndDataStore.mCommandBlock .mTag.mGroupID, DSP_COMMANDBLOCK_STARTADDR_RUN, 1, mSndDataStore.mCommandBlock.mTag.mDataPtr);
        if(mSendQueue.push(pItem))
        {
            sendPacketInQueue();
        }
        else
        {
            delete pItem;
        }
    }
    void sendWCGraphOn(unsigned short value)
    {
        DspSendQueueItem * pItem = new (DspSendQueueItem);
        mSndDataStore.setCmdWCGraphOn(value);

        pItem->mPacket.setFuncCode(DSP_FUNCCODE_MULTIBLOCK_WRITE);
        pItem->mPacket.addWriteBlock(mSndDataStore.mCommandBlock .mTag.mGroupID, DSP_COMMANDBLOCK_STARTADDR_WCGON, 1, mSndDataStore.mCommandBlock.mTag.mDataPtr);
        if(mSendQueue.push(pItem))
        {
            sendPacketInQueue();
        }
        else
        {
            delete pItem;
        }
    }
    void sendMDGraphOn(unsigned short value)
    {
        DspSendQueueItem * pItem = new (DspSendQueueItem);
        mSndDataStore.setCmdMDGraphOn(value);

        pItem->mPacket.setFuncCode(DSP_FUNCCODE_MULTIBLOCK_WRITE);
        pItem->mPacket.addWriteBlock(mSndDataStore.mCommandBlock .mTag.mGroupID, DSP_COMMANDBLOCK_STARTADDR_MDGON, 1, mSndDataStore.mCommandBlock.mTag.mDataPtr);
        if(mSendQueue.push(pItem))
        {
            sendPacketInQueue();
        }
        else
        {
            delete pItem;
        }
    }
    void sendRefVoltageReset(unsigned short value)
    {
        DspSendQueueItem * pItem = new (DspSendQueueItem);
        mSndDataStore.setCmdRefVoltageReset(value);

        pItem->mPacket.setFuncCode(DSP_FUNCCODE_MULTIBLOCK_WRITE);
        pItem->mPacket.addWriteBlock(mSndDataStore.mCommandBlock .mTag.mGroupID, DSP_COMMANDBLOCK_STARTADDR_REF_V_RESET, 1, mSndDataStore.mCommandBlock.mTag.mDataPtr);
        if(mSendQueue.push(pItem))
        {
            sendPacketInQueue();
        }
        else
        {
            delete pItem;
        }
    }
    void sendDevID(unsigned int value)
    {
        DspSendQueueItem * pItem = new (DspSendQueueItem);
        mSndDataStore.setCmdDeviceID(value);

        pItem->mPacket.setFuncCode(DSP_FUNCCODE_MULTIBLOCK_WRITE);
        pItem->mPacket.addWriteBlock(mSndDataStore.mCommandBlock .mTag.mGroupID, DSP_COMMANDBLOCK_STARTADDR_DEVID, 2, mSndDataStore.mCommandBlock.mTag.mDataPtr);
        if(mSendQueue.push(pItem))
        {
            sendPacketInQueue();
        }
        else
        {
            delete pItem;
        }
    }

    void sendResetGCnt(unsigned short value)
    {
        DspSendQueueItem * pItem = new (DspSendQueueItem);
        mSndDataStore.setCmdResetGroupCurrCount(value);

        pItem->mPacket.setFuncCode(DSP_FUNCCODE_MULTIBLOCK_WRITE);
        pItem->mPacket.addWriteBlock(mSndDataStore.mCommandBlock .mTag.mGroupID, DSP_COMMANDBLOCK_STARTADDR_GROUP_CURR_COUNT, 1, mSndDataStore.mCommandBlock.mTag.mDataPtr);
        if(mSendQueue.push(pItem))
        {
            sendPacketInQueue();
        }
        else
        {
            delete pItem;
        }
    }

    void sendPDSetting(DspPDSettingDto  pdSetting)
    {
        DspSendQueueItem * pItem = new (DspSendQueueItem);
        mSndDataStore.setPDCommSetting (&pdSetting.mCommSetting );
        mSndDataStore.setPDWCSetting   (&pdSetting.mWCSetting   );
        mSndDataStore.setPDMDSetting   (&pdSetting.mMDSetting   );

        pItem->mPacket.setFuncCode(DSP_FUNCCODE_MULTIBLOCK_WRITE);
        pItem->mPacket.addWriteBlock(mSndDataStore.mPDCommSettingBlock .mTag.mGroupID, mSndDataStore.mPDCommSettingBlock .mTag.mWordLen, mSndDataStore.mPDCommSettingBlock .mTag.mDataPtr);
        pItem->mPacket.addWriteBlock(mSndDataStore.mPDWCSettingBlock   .mTag.mGroupID, mSndDataStore.mPDWCSettingBlock   .mTag.mWordLen, mSndDataStore.mPDWCSettingBlock   .mTag.mDataPtr);
        pItem->mPacket.addWriteBlock(mSndDataStore.mPDMDSettingBlock   .mTag.mGroupID, mSndDataStore.mPDMDSettingBlock   .mTag.mWordLen, mSndDataStore.mPDMDSettingBlock   .mTag.mDataPtr);
        if(mSendQueue.push(pItem))
        {
            sendPacketInQueue();
        }
        else
        {
            delete pItem;
        }

        sendReadAll();
    }

    void sendNetSetting(DspNetSettingDto netSetting)
    {
        DspSendQueueItem * pItem = new (DspSendQueueItem);

        pItem->mPacket.setFuncCode(DSP_FUNCCODE_MULTIBLOCK_WRITE);
        pItem->mPacket.addWriteBlock(DSP_GROUP_ID_DEV_COMMSETTING, sizeof(StDspDevCommSetting)/2, sizeof(StDspDevNetSetting)/2, (char *)&netSetting.mSetting, false);

        //qDebug() << "[debug]" << pItem->mPacket.createSendBuffer().toHex();

        if(mSendQueue.push(pItem))
        {
            sendPacketInQueue();
        }
        else
        {
            delete pItem;
        }

        mIp = QString("%1.%2.%3.%4").arg(netSetting.mSetting.mIp01).arg(netSetting.mSetting.mIp02).arg(netSetting.mSetting.mIp03).arg(netSetting.mSetting.mIp04);
        //mPort = netSetting.mSetting.mPort;
        //mHostAddr.setAddress(mIp);
    }

    void sendDevSetting(DspDevSettingDto devSetting)
    {
        DspSendQueueItem * pItem = new (DspSendQueueItem);
        mSndDataStore.setDevCommSetting(&devSetting.mCommSetting);
        mSndDataStore.setDevWCSetting  (&devSetting.mWCSetting  );
        mSndDataStore.setDevMDSetting  (&devSetting.mMDSetting  );
        mSndDataStore.setDevSizeSetting(&devSetting.mSizeSetting);

        pItem->mPacket.setFuncCode(DSP_FUNCCODE_MULTIBLOCK_WRITE);
        pItem->mPacket.addWriteBlock(mSndDataStore.mDevCommSettingBlock.mTag.mGroupID, mSndDataStore.mDevCommSettingBlock.mTag.mWordLen, mSndDataStore.mDevCommSettingBlock.mTag.mDataPtr);
        pItem->mPacket.addWriteBlock(mSndDataStore.mDevWCSettingBlock  .mTag.mGroupID, mSndDataStore.mDevWCSettingBlock  .mTag.mWordLen, mSndDataStore.mDevWCSettingBlock  .mTag.mDataPtr);
        pItem->mPacket.addWriteBlock(mSndDataStore.mDevMDSettingBlock  .mTag.mGroupID, mSndDataStore.mDevMDSettingBlock  .mTag.mWordLen, mSndDataStore.mDevMDSettingBlock  .mTag.mDataPtr);
        pItem->mPacket.addWriteBlock(mSndDataStore.mDevSizeSettingBlock.mTag.mGroupID, mSndDataStore.mDevSizeSettingBlock.mTag.mWordLen, mSndDataStore.mDevSizeSettingBlock.mTag.mDataPtr);
        if(mSendQueue.push(pItem))
        {
            sendPacketInQueue();
        }
        else
        {
            delete pItem;
        }

        sendReadAll();
    }
    void sendTotalSetting()
    {
        DspSendQueueItem * pItem = new (DspSendQueueItem);

        pItem->mPacket.setFuncCode(DSP_FUNCCODE_MULTIBLOCK_WRITE);
        pItem->mPacket.addWriteBlock(mSndDataStore.mDevCommSettingBlock.mTag.mGroupID, mSndDataStore.mDevCommSettingBlock.mTag.mWordLen, mSndDataStore.mDevCommSettingBlock.mTag.mDataPtr);
        pItem->mPacket.addWriteBlock(mSndDataStore.mDevWCSettingBlock  .mTag.mGroupID, mSndDataStore.mDevWCSettingBlock  .mTag.mWordLen, mSndDataStore.mDevWCSettingBlock  .mTag.mDataPtr);
        pItem->mPacket.addWriteBlock(mSndDataStore.mDevMDSettingBlock  .mTag.mGroupID, mSndDataStore.mDevMDSettingBlock  .mTag.mWordLen, mSndDataStore.mDevMDSettingBlock  .mTag.mDataPtr);
        pItem->mPacket.addWriteBlock(mSndDataStore.mDevSizeSettingBlock.mTag.mGroupID, mSndDataStore.mDevSizeSettingBlock.mTag.mWordLen, mSndDataStore.mDevSizeSettingBlock.mTag.mDataPtr);
        pItem->mPacket.addWriteBlock(mSndDataStore.mPDCommSettingBlock .mTag.mGroupID, mSndDataStore.mPDCommSettingBlock .mTag.mWordLen, mSndDataStore.mPDCommSettingBlock .mTag.mDataPtr);
        pItem->mPacket.addWriteBlock(mSndDataStore.mPDWCSettingBlock   .mTag.mGroupID, mSndDataStore.mPDWCSettingBlock   .mTag.mWordLen, mSndDataStore.mPDWCSettingBlock   .mTag.mDataPtr);
        pItem->mPacket.addWriteBlock(mSndDataStore.mPDMDSettingBlock   .mTag.mGroupID, mSndDataStore.mPDMDSettingBlock   .mTag.mWordLen, mSndDataStore.mPDMDSettingBlock   .mTag.mDataPtr);

        if(mSendQueue.push(pItem))
        {
            sendPacketInQueue();
        }
        else
        {
            delete pItem;
        }
    }
    void sendReadAll()
    {
        DspSendQueueItem * pItem = new (DspSendQueueItem);

        pItem->mPacket.setFuncCode(DSP_FUNCCODE_MULTIBLOCK_READ);
        pItem->mPacket.addReadBlock(mSndDataStore.mDevCommSettingBlock.mTag.mGroupID, mSndDataStore.mDevCommSettingBlock.mTag.mWordLen);
        pItem->mPacket.addReadBlock(mSndDataStore.mDevWCSettingBlock  .mTag.mGroupID, mSndDataStore.mDevWCSettingBlock  .mTag.mWordLen);
        pItem->mPacket.addReadBlock(mSndDataStore.mDevMDSettingBlock  .mTag.mGroupID, mSndDataStore.mDevMDSettingBlock  .mTag.mWordLen);
        pItem->mPacket.addReadBlock(mSndDataStore.mDevSizeSettingBlock.mTag.mGroupID, mSndDataStore.mDevSizeSettingBlock.mTag.mWordLen);
        pItem->mPacket.addReadBlock(mSndDataStore.mPDCommSettingBlock .mTag.mGroupID, mSndDataStore.mPDCommSettingBlock .mTag.mWordLen);
        pItem->mPacket.addReadBlock(mSndDataStore.mPDWCSettingBlock   .mTag.mGroupID, mSndDataStore.mPDWCSettingBlock   .mTag.mWordLen);
        pItem->mPacket.addReadBlock(mSndDataStore.mPDMDSettingBlock   .mTag.mGroupID, mSndDataStore.mPDMDSettingBlock   .mTag.mWordLen);
        pItem->mPacket.addReadBlock(mSndDataStore.mCommStatusBlock    .mTag.mGroupID, mSndDataStore.mCommStatusBlock    .mTag.mWordLen);
        pItem->mPacket.addReadBlock(mSndDataStore.mWCStatusBlock      .mTag.mGroupID, mSndDataStore.mWCStatusBlock      .mTag.mWordLen);
        pItem->mPacket.addReadBlock(mSndDataStore.mMDStatusBlock      .mTag.mGroupID, mSndDataStore.mMDStatusBlock      .mTag.mWordLen);
        pItem->mPacket.addReadBlock(mSndDataStore.mDevInfoBlock       .mTag.mGroupID, mSndDataStore.mDevInfoBlock       .mTag.mWordLen);
        pItem->mPacket.addReadBlock(mSndDataStore.mEventListBlock     .mTag.mGroupID, mSndDataStore.mEventListBlock     .mTag.mWordLen);
        if(mSendQueue.push(pItem))
        {
            sendPacketInQueue();
        }
        else
        {
            delete pItem;
        }
    }
    void sendReadAlwaysData()
    {
        DspSendQueueItem * pItem = new (DspSendQueueItem);

        pItem->mPacket.setFuncCode(DSP_FUNCCODE_MULTIBLOCK_READ);
        pItem->mPacket.addReadBlock(mSndDataStore.mCommStatusBlock.mTag.mGroupID, mSndDataStore.mCommStatusBlock.mTag.mWordLen);
        pItem->mPacket.addReadBlock(mSndDataStore.mWCStatusBlock  .mTag.mGroupID, mSndDataStore.mWCStatusBlock  .mTag.mWordLen);
        pItem->mPacket.addReadBlock(mSndDataStore.mMDStatusBlock  .mTag.mGroupID, mSndDataStore.mMDStatusBlock  .mTag.mWordLen);
        pItem->mPacket.addReadBlock(mSndDataStore.mDevInfoBlock   .mTag.mGroupID, mSndDataStore.mDevInfoBlock   .mTag.mWordLen);
        pItem->mPacket.addReadBlock(mSndDataStore.mEventListBlock .mTag.mGroupID, mSndDataStore.mEventListBlock .mTag.mWordLen);
        if(mSendQueue.push(pItem, true))
        {
            sendPacketInQueue();
        }
        else
        {
            delete pItem;
        }
    }
    void changeNet(QString ip, quint16 port)
    {
        mIp = ip;
        mPort = port;
        disconnectDsp();
        connectDsp();
    }

    void onTimeTick(QDateTime now)
    {

        //[debug]
        static qint64 lastMSec = 0;

        if(now.toMSecsSinceEpoch() - lastMSec > 200)
        {
           // qDebug() << "[DspMaster::onTimeTick]delayed msec : " << (now.toMSecsSinceEpoch() - lastMSec);
        }

        lastMSec = now.toMSecsSinceEpoch();
        //[debug]

        if(mpSock == nullptr)
        {
            connectDsp();
            return;
        }

        // 패킷을 보낸시간이 1초이상 지연되면 timeout으로 판단하고 연결을 종료한다. (연결을 종료하면 다음 루프에서 다시 연결을 시도하면서 새로 싱크 맞춘다)
        if(mSendQueue.compareSentTime(now) > 200)
        {
            if(mSendQueue.getTryCnt() > 29)
            {
                onSocketError(QAbstractSocket::SocketError::SocketTimeoutError);
            }
            else
            {
                qDebug() << "[DspMaster::onTimeTick]retry send";
                sendPacketInQueue(true);
            }
            return;
        }
    }

signals:
    void signalEventChangedIsConnect(quint64 dspSeq, bool value);
    void signalEventReceivePacket(quint64 dspSeq, int error);
    void signalEventAddedWCG(quint64 dspSeq, DspWCGDto dto);
    void signalEventAddedMDG(quint64 dspSeq, DspMDGDto dto);
    void signalEventChangedDevSetting(quint64 dspSeq, DspDevSettingDto dto);
    void signalEventChangedPDSetting(quint64 dspSeq, DspPDSettingDto dto);
    void signalEventChangedStatus(quint64 dspSeq, DspStatusDto dto);
    void signalEventChangedInfo(quint64 dspSeq, DspInfoDto dto);
    void signalEventAddedEvent(quint64 dspSeq, DspEventDto dto);
    void signalEventChangedRefVoltage(quint64 dspSeq, qint32 value);


private slots:
    void onRecevie()
    {
        QByteArray      rcvBuffer;
        QHostAddress    sender;
        quint16         senderPort;
        DspPacket       rcvPacket;

        if(mpSock == nullptr)
        {
            qDebug() << "[DspModbusMaster::onRecevie]sock is null";
            return;
        }

        if(mpSock->hasPendingDatagrams() == false)
        {
            return;
        }

        rcvBuffer.resize(mpSock->pendingDatagramSize());
        mpSock->readDatagram(rcvBuffer.data(), rcvBuffer.size(), &sender, &senderPort);

        if(rcvPacket.setDatagram(rcvBuffer) == false)
        {
            return;
        }

        //qDebug() << "[debug] rcv packet = " << rcvBuffer.toHex();

        if(rcvPacket.getFuncCode() == DSP_FUNCCODE_MULTIBLOCK_READ || rcvPacket.getFuncCode() == DSP_FUNCCODE_MULTIBLOCK_WRITE)
        {
            if(mSendQueue.checkAckPacket(&rcvPacket) == false)
                return;

            DspSendQueueItem * pItem = mSendQueue.pop();

            if(pItem->mIsFRPacket == true)
            {
                mFRState = EnumDef::DSP_FR_STATE_SUCC;
            }
            delete pItem;
        }

        setIsConnect(true);

        switch(rcvPacket.getFuncCode())
        {
        case DSP_FUNCCODE_MULTIBLOCK_NOTI:
            procNotiData(&rcvPacket);
            return;

        case DSP_FUNCCODE_MULTIBLOCK_READ:
            procReadData(&rcvPacket);
        }

        sendPacketInQueue();
    }

    void onSocketError(QAbstractSocket::SocketError error)
    {
        qDebug() << "[DspModbusMaster::onSocketError]" << error;

        disconnectDsp();
    }

private:
    QHostAddress    mHostAddr       ;
    QUdpSocket *    mpSock          = nullptr;
    DspSendQueue    mSendQueue      ;


    void setIsConnect(bool value)
    {
        if(mIsConnect == value)
            return;

        qDebug() << "[DspMaster::setIsConnect]" << value;

        mIsConnect = value;

        emit signalEventChangedIsConnect(mSeq, value);
    }

    void connectDsp()
    {
        qDebug() << "[DspMaster::connectDsp]";

        mSendQueue.clear();

        mHostAddr.setAddress(mIp);
        mpSock = new QUdpSocket();
        mpSock->connectToHost(mHostAddr, mPort);

        if(mpSock->localAddress().toString().contains("0.0.0.0"))
        {
            onSocketError(QAbstractSocket::SocketError::SocketAddressNotAvailableError);
            return;
        }

        connect(mpSock, SIGNAL(readyRead()), this, SLOT(onRecevie()));
        connect(mpSock,SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));

        sendTotalSetting();
        sendReadAll();

    }

    void disconnectDsp()
    {
        DspSendQueueItem * pItem = mSendQueue.pop();

        if(mpSock != nullptr)
        {
            disconnect(mpSock, SIGNAL(readyRead()), this, SLOT(onRecevie()));
            disconnect(mpSock,SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));

            if(mpSock->isOpen())
                mpSock->close();

            mpSock->deleteLater();

            mpSock = nullptr;
        }

        while(pItem != nullptr)
        {
            if(pItem->mIsFRPacket == true)
            {
                mFRState = EnumDef::DSP_FR_STATE_FAIL;
            }
            delete pItem;
            pItem = mSendQueue.pop();
        }

        setIsConnect(false);
    }

    void sendPacketInQueue(bool isRetry = false)
    {
        if(mpSock == nullptr)
        {
            return;
        }

        if(mSendQueue.size() < 1)
            return;

        // 보낸 패킷에 대한 응답을 기다리고 있는 중이면 다음 패킷을 보내지 않고 응답이 오면 보내도록 한다.
        if(mSendQueue.isWait() && isRetry == false)
            return;

        //QByteArray sendBuf = mSendQueue.getSendPacketBuffer();

        //if(sendBuf.at(7) == 0x66)
        //    qDebug() << "[debug] snd packet = " << sendBuf.toHex();

        if(mpSock->writeDatagram(mSendQueue.getSendPacketBuffer(), mHostAddr, mPort) < 1)
        {
            onSocketError(QAbstractSocket::SocketError::OperationError);
            return;
        }
    }

    void procNotiData(DspPacket * pPacket)
    {
        CHECK_FALSE_RETURN(mRcvDataStore.setNotiDataFromPacket(pPacket))

        if(mRcvDataStore.mWCGBlock.mTag.mIsUpdated)
        {
            DspWCGDto dto = mRcvDataStore.getWCGDto();

            emit signalEventAddedWCG(mSeq, dto);
        }
        if(mRcvDataStore.mMDGBlock.mTag.mIsUpdated)
        {
            DspMDGDto dto = mRcvDataStore.getMDGDto();

            emit signalEventAddedMDG(mSeq, dto);
        }
    }

    void procReadData(DspPacket * pPacket)
    {
        static bool lastRun = false;

        mRcvDataStore.setDataFromPacket(pPacket);

        if(mRcvDataStore.mDevCommSettingBlock.mTag.mIsUpdated ||
           mRcvDataStore.mDevWCSettingBlock.mTag.mIsUpdated   ||
           mRcvDataStore.mDevMDSettingBlock.mTag.mIsUpdated   ||
           mRcvDataStore.mDevSizeSettingBlock.mTag.mIsUpdated)
        {
            DspDevSettingDto dto = mRcvDataStore.getDevSettingDto();

            mIsDevSettingAlarm = !compareDevSetting();

            emit signalEventChangedDevSetting(mSeq, dto);
        }
        if(mRcvDataStore.mPDCommSettingBlock.mTag.mIsUpdated ||
           mRcvDataStore.mPDWCSettingBlock.mTag.mIsUpdated   ||
           mRcvDataStore.mPDMDSettingBlock.mTag.mIsUpdated    )
        {
            DspPDSettingDto dto = mRcvDataStore.getPDSettingDto();

            mIsPDSettingAlarm = !comparePDSetting();

            emit signalEventChangedPDSetting(mSeq, dto);
        }
        if(mRcvDataStore.mCommStatusBlock.mTag.mIsUpdated ||
           mRcvDataStore.mWCStatusBlock.mTag.mIsUpdated   ||
           mRcvDataStore.mMDStatusBlock.mTag.mIsUpdated    )
        {
            DspStatusDto dto = mRcvDataStore.getStatusDto();

            if(mSndDataStore.mCommandBlock.mData.mWCGraphOn != dto.mWCStatus.mIsGraphOn)
            {
                qDebug() << "[debug] diff wd graph status";
                sendWCGraphOn(mSndDataStore.getCmdWCGraphOn());
            }
            if(mSndDataStore.mCommandBlock.mData.mMDGraphOn != dto.mMDStatus.mIsGraphOn )
            {
                 qDebug() << "[debug] diff md graph status";
                sendMDGraphOn(mSndDataStore.getCmdMDGraphOn());
            }

            bool bRun = (dto.mCommStatus.mRun > (int)EnumDef::RUN_MODE_STOP && dto.mCommStatus.mRun < (int)EnumDef::RUN_MODE_ALRAM_RESET ) ? true : false;

            if(lastRun != bRun)
            {
                DspEventDto runEventDto;
                runEventDto.mEvent.mEventType = bRun ? EnumDef::ET_RUN : EnumDef::ET_STOP;
                runEventDto.mEvent.mEventValue = 0;
                emit signalEventAddedEvent(mSeq, runEventDto);
            }

            lastRun = bRun;

            emit signalEventChangedStatus(mSeq, dto);
        }
        if(mRcvDataStore.mDevInfoBlock.mTag.mIsUpdated)
        {
            DspInfoDto dto = mRcvDataStore.getInfoDto();

            emit signalEventChangedInfo(mSeq, dto);
        }
        if(mRcvDataStore.mEventListBlock.mTag.mIsUpdated &&  mRcvDataStore.mAddedEventCnt > 0)
        {
            if(mRcvDataStore.mAddedEventCnt > 10)
                mRcvDataStore.mAddedEventCnt = 10;

            for(int i = mRcvDataStore.mAddedEventCnt - 1; i > -1; i-- )
            {
                DspEventDto dto = mRcvDataStore.getEventDto(i);

                //qDebug() << "[debug]onRecevie : event Type = " << dto.mEvent.mEventType;

                if(dto.mEvent.mEventType == EnumDef::ET_WEIGHT_REF_VOLTAGE)
                {
                    emit signalEventChangedRefVoltage(mSeq, dto.mEvent.mEventValue);
                }
                else
                {
                    if(dto.mEvent.mEventType == (int)EnumDef::ET_METAL_DETECT)
                    {
                        dto.mMdDetectChannel = 1;
                    }
                    else if(dto.mEvent.mEventType == (int)EnumDef::ET_METAL_DETECT_2)
                    {
                        dto.mMdDetectChannel = 2;
                        dto.mEvent.mEventType = (int)EnumDef::ET_METAL_DETECT;
                    }
                    emit signalEventAddedEvent(mSeq, dto);
                }
            }
        }
    }

    bool compareDevSetting()
    {
        if(memcmp(mRcvDataStore.mDevCommSettingBlock.mTag.mDataPtr, mSndDataStore.mDevCommSettingBlock.mTag.mDataPtr, mSndDataStore.mDevCommSettingBlock.mTag.mWordLen * 2) != 0)
            return false;

        if(memcmp(mRcvDataStore.mDevWCSettingBlock.mTag.mDataPtr, mSndDataStore.mDevWCSettingBlock.mTag.mDataPtr, mSndDataStore.mDevWCSettingBlock.mTag.mWordLen * 2) != 0)
            return false;

        if(memcmp(mRcvDataStore.mDevMDSettingBlock.mTag.mDataPtr, mSndDataStore.mDevMDSettingBlock.mTag.mDataPtr, mSndDataStore.mDevMDSettingBlock.mTag.mWordLen * 2) != 0)
            return false;

        if(memcmp(mRcvDataStore.mDevSizeSettingBlock.mTag.mDataPtr, mSndDataStore.mDevSizeSettingBlock.mTag.mDataPtr, mSndDataStore.mDevSizeSettingBlock.mTag.mWordLen * 2) != 0)
            return false;

        return true;
    }

    bool comparePDSetting()
    {
        if(memcmp(mRcvDataStore.mPDCommSettingBlock.mTag.mDataPtr, mSndDataStore.mPDCommSettingBlock.mTag.mDataPtr, mSndDataStore.mPDCommSettingBlock.mTag.mWordLen * 2) != 0)
            return false;

        if(memcmp(mRcvDataStore.mPDWCSettingBlock.mTag.mDataPtr, mSndDataStore.mPDWCSettingBlock.mTag.mDataPtr, mSndDataStore.mPDWCSettingBlock.mTag.mWordLen * 2) != 0)
            return false;

        if(memcmp(mRcvDataStore.mPDMDSettingBlock.mTag.mDataPtr, mSndDataStore.mPDMDSettingBlock.mTag.mDataPtr, mSndDataStore.mPDMDSettingBlock.mTag.mWordLen * 2) != 0)
            return false;

        return true;
    }

};
#endif // DSPMASTER_H
