#include "deviceinfobrodcaster.h"

#include "source/globaldef/EnumDefine.h"
#include "source/thread/remoteconsole/dto/devicesocketdto.h"

void DeviceInfoBrodcastWorker::onStart()
{
    qDebug() << "[DeviceInfoBrodcastWorker::onStart]";

    mpTimer = new QTimer(this);
    mpTimer->setInterval(1000);

    connect(mpTimer, SIGNAL(timeout()), this, SLOT(onTimeTick()));
    mpTimer->start();
}

void DeviceInfoBrodcastWorker::onTimeTick()
{
    if(mpSocket == nullptr)
    {
        open();
        return;
    }

    StRConsolePacket temp;
    temp.mSize = 0;
    temp.mFuncCode = EnumDefine::RFuncCode::FUNC_CODE_INFO;
    temp.mDeviceNum = mDeviceNum;

    mpSocket->writeDatagram((char *)&temp, sizeof(StRConsolePacket), QHostAddress::Broadcast, 10022);
    //mpSocket->writeDatagram(temp02, QHostAddress::Broadcast, 10022);
}

void DeviceInfoBrodcastWorker::onSockError(QAbstractSocket::SocketError error)
{
    qDebug() << "[SOCKET ERROR]" << error;
    close();
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

    if(mpTimer != nullptr)
    {
        mpTimer->stop();
        delete mpTimer;
        mpTimer = nullptr;
    }
}

void DeviceInfoBrodcastWorker::open()
{
    mpSocket = new QUdpSocket(this);
}

void DeviceInfoBrodcastWorker::close()
{
    if(mpSocket != nullptr)
    {
        mpSocket->close();
        delete mpSocket;
        mpSocket = nullptr;
    }
}
