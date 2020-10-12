#include "monitoringservice.h"
#include "source/thread/remoteconsole/dto/devicesocketdto.h"
#include "source/service/coreservice.h"

void MonitoringService::onReceive()
{
    QByteArray rcvBuffer;
    QHostAddress sender;
    quint16 senderPort;
    StRConsolePacket * rPacketData;
    StPacketRStatusRes resPacket;

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
    if(rPacketData->mFuncCode != EnumDefine::RFuncCode::FUNC_CODE_MONITOR_STATUS)
    {
        qDebug() << "[MonitoringService::onRecevie]func code error";
        qDebug() << "[MonitoringService::onRecevie]ERROR PACKET : "<< rcvBuffer.toHex();
        return;
    }

    memset(&resPacket, 0x00, sizeof(StPacketRStatusRes));

    QByteArray tempProductName   = mpProductSetting->mName.toUtf8();

    resPacket.mHeader.mFuncCode = EnumDefine::RFuncCode::FUNC_CODE_MONITOR_STATUS;
    resPacket.mHeader.mSize = sizeof(StPacketRStatusRes) - sizeof(StRConsolePacket);
    resPacket.mHeader.mDeviceNum = mpInformation->mDeviceNumber;
    resPacket.mIsRun             = mpDspStatus->mRun;
    resPacket.mIsComm            = mpDspStatus->mIsComm;
    resPacket.mIsAlarm           = mpDspStatus->mIsAlarm;
    resPacket.mProductNo         = mpProductSetting->mNo;
    memcpy(resPacket.mProductName, tempProductName.data(), tempProductName.size());
    resPacket.mMdSignal          = mpDspStatus->mMDCurrSignal;
    resPacket.mWcEventType       = mpDspStatus->mWCCurrEventType;
    resPacket.mCurrWeight        = mpDspStatus->mWCCurrWeight;
    resPacket.mMdSenstivity      = mpProductSetting->mMDSenstivity;
    resPacket.mTareWeight        = mpProductSetting->mTareWeight;
    resPacket.mUnderWeight       = mpProductSetting->mUnderWeight;
    resPacket.mUnderWaringWeight = mpProductSetting->mUnderWarningWeight;
    resPacket.mNormalWeight      = mpProductSetting->mNormalWeight;
    resPacket.mOverWaringWeight  = mpProductSetting->mOverWarningWeight;
    resPacket.mOverWeight        = mpProductSetting->mOverWeight;
    resPacket.mMDNgCnt           = mpProductStatus->mMDDetectCnt;
    resPacket.mWCUnderCnt        = mpProductStatus->mWCUnderCnt;
    resPacket.mWCUnderWaringCnt  = mpProductStatus->mWCUnderWarningCnt;
    resPacket.mWCNoramlCnt       = mpProductStatus->mWCNormalCnt;
    resPacket.mWCOverWaringCnt   = mpProductStatus->mWCOverWarningCnt;
    resPacket.mWCOverCnt         = mpProductStatus->mWCOverCnt;
    resPacket.mWCEtcErrCnt       = mpProductStatus->mWCEtcErrorCnt;
    resPacket.mTradeTotalWeight  = mpProductStatus->mWCTradeTotalWeight;

    qDebug() << "[MonitoringService::onReceive]send";

    mpSocket->writeDatagram((char*)&resPacket, sizeof(StPacketRStatusRes), sender, senderPort);
}

void MonitoringService::onSockError(QAbstractSocket::SocketError error)
{
    qDebug() << "[SOCKET ERROR]" << error;

    open();
}

void MonitoringService::startMonitoringService()
{
    qDebug() << "[MonitoringService::startMonitoringService]";

    CoreService * pCoreService    = CoreService::getInstance();
    mpDspStatus      = pCoreService->mMapDspStatus.first();
    mpProductStatus  = &(mpDspStatus->mCurrentProductStatus);
    mpProductSetting = &(pCoreService->mProductSettingServcie.mCurrentProductSetting);
    mpInformation    = &(pCoreService->mLocalSettingService.mInformation);
    open();
}

MonitoringService::MonitoringService(QObject *parent) : QObject(parent)
{

}

MonitoringService::~MonitoringService()
{
    close();
}


void MonitoringService::open()
{
    close();

    mpSocket = new QUdpSocket(this);
    mpSocket->bind(mPort, QUdpSocket::ShareAddress);
    connect(mpSocket, SIGNAL(readyRead()), this, SLOT(onReceive()));
    connect(mpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSockError(QAbstractSocket::SocketError)));
}

void MonitoringService::close()
{
    if(mpSocket == nullptr)
        return;

    disconnect(mpSocket, SIGNAL(readyRead()), this, SLOT(onReceive()));
    disconnect(mpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSockError(QAbstractSocket::SocketError)));
    mpSocket->close();
    mpSocket->deleteLater();
    mpSocket = nullptr;
}
