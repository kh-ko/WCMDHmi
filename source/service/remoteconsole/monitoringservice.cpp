#include "monitoringservice.h"

#include "source/service/remoteconsole/dto/enum/remoteenumdef.h"
#include "source/service/remoteconsole/dto/devicesocketdto.h"
#include "source/service/coreservice.h"

void MonitoringServer::onReceive()
{
    QByteArray rcvBuffer;
    QHostAddress sender;
    quint16 senderPort;
    StRConsolePacket * rPacketData;
    StPacketRStatusRes resPacket;

    if(mpSocket == nullptr)
        return;

    if(mpSocket->hasPendingDatagrams() == false)
    {
        qDebug() << "[MonitoringService::onReceive]hasPendingDatagrams";
        return;
    }

    if(mpSocket->pendingDatagramSize() != sizeof(StRConsolePacket))
    {
        qDebug() << "[MonitoringService::onReceive]pendingDatagramSize";
        open();
        return;
    }

    rcvBuffer.resize(mpSocket->pendingDatagramSize());
    mpSocket->readDatagram(rcvBuffer.data(), rcvBuffer.size(), &sender, &senderPort);
    rPacketData = (StRConsolePacket *)rcvBuffer.data();

    if(rcvBuffer.size() != sizeof(StRConsolePacket))
    {
        qDebug() << "[MonitoringService::onRecevie]packet error size";
        qDebug() << "[MonitoringService::onRecevie]ERROR PACKET : "<< rcvBuffer.toHex();
        return;
    }
    if(rPacketData->mFuncCode != RemoteEnumDef::RFUNC_CODE_MONITOR_STATUS)
    {
        qDebug() << "[MonitoringService::onRecevie]func code error";
        qDebug() << "[MonitoringService::onRecevie]ERROR PACKET : "<< rcvBuffer.toHex();
        return;
    }

    memset(&resPacket, 0x00, sizeof(StPacketRStatusRes));

    QByteArray tempProductName   = pProductSP->mCurrPD.mName.toUtf8();

    resPacket.mHeader.mFuncCode = RemoteEnumDef::RFUNC_CODE_MONITOR_STATUS;
    resPacket.mHeader.mSize = sizeof(StPacketRStatusRes) - sizeof(StRConsolePacket);
    resPacket.mHeader.mDeviceNum = pLSettingSP->mInformation.mDeviceNumber;
    resPacket.mProductNo         = pProductSP->mCurrPD.mDspForm.mCommSetting.mProductNum;
    memcpy(resPacket.mProductName, tempProductName.data(), tempProductName.size());
    resPacket.mMdSenstivity      = pProductSP->mCurrPD.mDspForm.mMDSetting.mSenstivity;
    resPacket.mTareWeight        = pProductSP->mCurrPD.mDspForm.mWCSetting.mTareWeight;
    resPacket.mUnderWeight       = pProductSP->mCurrPD.mDspForm.mWCSetting.mUnderWeight;
    resPacket.mUnderWaringWeight = pProductSP->mCurrPD.mDspForm.mWCSetting.mUnderWarningWeight;
    resPacket.mNormalWeight      = pProductSP->mCurrPD.mDspForm.mWCSetting.mNormalWeight;
    resPacket.mOverWaringWeight  = pProductSP->mCurrPD.mDspForm.mWCSetting.mOverWarningWeight;
    resPacket.mOverWeight        = pProductSP->mCurrPD.mDspForm.mWCSetting.mOverWeight;
    resPacket.mMDPassCnt         = pWorkSP->mCurrPD.mMDPassCnt;
    resPacket.mMDNgCnt           = pWorkSP->mCurrPD.mMDFailCnt;
    resPacket.mWCUnderCnt        = pWorkSP->mCurrPD.mWCUCnt;
    resPacket.mWCUnderWaringCnt  = pWorkSP->mCurrPD.mWCUWCnt;
    resPacket.mWCNoramlCnt       = pWorkSP->mCurrPD.mWCNorCnt;
    resPacket.mWCOverWaringCnt   = pWorkSP->mCurrPD.mWCOWCnt;
    resPacket.mWCOverCnt         = pWorkSP->mCurrPD.mWCOCnt;
    resPacket.mWCEtcErrCnt       = pWorkSP->mCurrPD.mWCEtcCnt;
    resPacket.mWCEtcMDErrCnt     = pWorkSP->mCurrPD.mWCMDCnt;
    resPacket.mTradeTotalWeight  = pWorkSP->mCurrPD.mWCTradeTotalWeight;
    resPacket.mMachineMode       = pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMachineMode;

    if(mDspSeq != 0)
    {
        DspMaster * pMaster = pDspSP->findDspMaster(mDspSeq);

        if(pMaster != nullptr)
        {
            DspStatusDto status = pMaster->mRcvDataStore.getStatusDto();

            resPacket.mIsRun             = status.mCommStatus.mRun != EnumDef::RUN_MODE_STOP;
            resPacket.mIsComm            = pMaster->mIsConnect;
            resPacket.mIsAlarm           = status.getAlarm() || pMaster->mIsDevSettingAlarm || pMaster->mIsPDSettingAlarm;
            resPacket.mMdSignal          = status.mMDStatus.mSignal;
            resPacket.mWcEventType       = status.mWCStatus.mErrorType;
            resPacket.mCurrWeight        = status.mWCStatus.mCurrWeight;
        }
    }

    mpSocket->writeDatagram((char*)&resPacket, sizeof(StPacketRStatusRes), sender, senderPort);
}

void MonitoringServer::onSockError(QAbstractSocket::SocketError error)
{
    qDebug() << "[SOCKET ERROR]" << error;

    open();
}

void MonitoringServer::start()
{
    qDebug() << "[MonitoringService::start]";

    if(pDspSP->mDspList.size() > 0)
        mDspSeq = pDspSP->mDspList[0]->mSeq;

    open();
}

void MonitoringServer::stop()
{
    qDebug() << "[MonitoringService::stop]";

    close();
}

MonitoringServer::MonitoringServer(QObject *parent) : QObject(parent)
{

}

MonitoringServer::~MonitoringServer()
{
    close();
}


void MonitoringServer::open()
{
    close();

    mpSocket = new QUdpSocket(this);
    mpSocket->bind(PORT, QUdpSocket::ShareAddress);
    connect(mpSocket, SIGNAL(readyRead()), this, SLOT(onReceive()));
    connect(mpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSockError(QAbstractSocket::SocketError)));
}

void MonitoringServer::close()
{
    if(mpSocket == nullptr)
        return;

    disconnect(mpSocket, SIGNAL(readyRead()), this, SLOT(onReceive()));
    disconnect(mpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSockError(QAbstractSocket::SocketError)));
    mpSocket->close();
    mpSocket->deleteLater();
    mpSocket = nullptr;
}
