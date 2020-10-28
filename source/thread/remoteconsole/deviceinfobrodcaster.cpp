#include "deviceinfobrodcaster.h"

#include <QNetworkInterface>

#include "source/globaldef/EnumDefine.h"
#include "source/thread/remoteconsole/dto/devicesocketdto.h"

//#define MUTI_SENDER

void DeviceInfoBrodcastWorker::onStart()
{
    qDebug() << "[DeviceInfoBrodcastWorker::onStart]";

    mpTimer = new QTimer(this);
    mpTimer->setInterval(1000);
    connect(mpTimer, SIGNAL(timeout()), this, SLOT(onTimeTick()));
    mpTimer->start();
    open();
}

void DeviceInfoBrodcastWorker::onSockError(QAbstractSocket::SocketError error)
{
    open();

    qDebug() << "[SOCKET ERROR]" << error;
}

void DeviceInfoBrodcastWorker::onReceive()
{
    QByteArray rcvBuffer;
    QHostAddress sender;
    quint16 senderPort;

    if(mpSocket == nullptr)
    {
        qDebug() << "sock is null";
        return;
    }

    if(mpSocket->hasPendingDatagrams() == false)
    {
        return;
    }

    rcvBuffer.resize(mpSocket->pendingDatagramSize());
    mpSocket->readDatagram(rcvBuffer.data(), rcvBuffer.size(), &sender, &senderPort);
}

void DeviceInfoBrodcastWorker::onTimeTick()
{
    if(mpSocket == nullptr)
        return;

    StRConsolePacket resPacket;

    memset(&resPacket, 0x00, sizeof(StRConsolePacket));

    resPacket.mFuncCode = EnumDefine::RFuncCode::FUNC_CODE_INFO;
    resPacket.mSize = 0;
    resPacket.mDeviceNum = mDeviceNum;

    mpSocket->writeDatagram((char*)&resPacket, sizeof(StRConsolePacket), mGroupAddress, mPort);
}

void DeviceInfoBrodcastWorker::onSignalEventChangedDeviceNumber(int deviceNumber)
{
    mDeviceNum = deviceNumber;
}

DeviceInfoBrodcastWorker::DeviceInfoBrodcastWorker(QObject *parent): QObject(parent)
{
}

DeviceInfoBrodcastWorker::~DeviceInfoBrodcastWorker()
{
    close();
}

void DeviceInfoBrodcastWorker::open()
{
    close();

    mpSocket = new QUdpSocket(this);
    mGroupAddress.setAddress("239.168.0.21");
    mpSocket->setSocketOption(QAbstractSocket::MulticastTtlOption, 10);

    connect(mpSocket, &QUdpSocket::readyRead, this, &DeviceInfoBrodcastWorker::onReceive);
    connect(mpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSockError(QAbstractSocket::SocketError)));
}

void DeviceInfoBrodcastWorker::close()
{
    if(mpSocket != nullptr)
    {
        qDebug() << "[debug] DeviceInfoBrodcastWorker close ";
        disconnect(mpSocket, &QUdpSocket::readyRead, this, &DeviceInfoBrodcastWorker::onReceive);
        disconnect(mpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSockError(QAbstractSocket::SocketError)));

        mpSocket->close();
        mpSocket->deleteLater();
        mpSocket = nullptr;
    }

}
