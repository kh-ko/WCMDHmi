#ifndef DEVICEINFOBRODCASTER_H
#define DEVICEINFOBRODCASTER_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QUdpSocket>
#include "source/service/remoteconsole/dto/enum/remoteenumdef.h"
#include "source/service/remoteconsole/dto/devicesocketdto.h"

#include "source/service/timer/timersprovider.h"
#include "source/service/localsetting/localsettingsprovider.h"
#include "source/service/util/sproviderconnectutil.h"

#define pDevInfoBC DeviceInfoBrodcaster::getInstance()

class DeviceInfoBrodcaster : public QObject
{
    Q_OBJECT
public:
    static DeviceInfoBrodcaster * getInstance()
    {
        static DeviceInfoBrodcaster *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new DeviceInfoBrodcaster();
        }

        return mpSelf;
    }

    void start()
    {
        ENABLE_SLOT_TIMER_TICK;

        open();
    }

    void stop()
    {
        close();
    }

    explicit DeviceInfoBrodcaster(QObject *parent = nullptr) : QObject(parent){}
    ~DeviceInfoBrodcaster()
    {
        close();
    }

private:
    const quint16 PORT    = 31072;

    quint64      mLastSentMSec = 0;;
    QHostAddress mGroupAddress;
    QUdpSocket  *mpSocket = nullptr;

private slots:
    void onSockError(QAbstractSocket::SocketError error)
    {
        qDebug() << "[SOCKET ERROR]" << error;
        open();
    }
    void onReceive()
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

    void onTimeTick(QDateTime now)
    {
        if(mpSocket == nullptr)
            return;

        quint64 currMSec = now.toMSecsSinceEpoch();

        if(currMSec - mLastSentMSec < 1000)
        {
            return;
        }

        mLastSentMSec = currMSec;

        StRConsolePacket resPacket;

        memset(&resPacket, 0x00, sizeof(StRConsolePacket));

        resPacket.mFuncCode = RemoteEnumDef::RFUNC_CODE_INFO;
        resPacket.mSize = 0;
        resPacket.mDeviceNum = pLSettingSP->mInformation.mDeviceNumber;

        mpSocket->writeDatagram((char*)&resPacket, sizeof(StRConsolePacket), mGroupAddress, PORT);
    }

    void open()
    {
        close();

        mpSocket = new QUdpSocket(this);
        mGroupAddress.setAddress("239.168.0.21");
        mpSocket->setSocketOption(QAbstractSocket::MulticastTtlOption, 10);

        connect(mpSocket, &QUdpSocket::readyRead, this, &DeviceInfoBrodcaster::onReceive);
        connect(mpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSockError(QAbstractSocket::SocketError)));
    }

    void close()
    {
        if(mpSocket != nullptr)
        {
            qDebug() << "[debug] DeviceInfoBrodcastWorker close ";
            disconnect(mpSocket, &QUdpSocket::readyRead, this, &DeviceInfoBrodcaster::onReceive);
            disconnect(mpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSockError(QAbstractSocket::SocketError)));

            mpSocket->close();
            mpSocket->deleteLater();
            mpSocket = nullptr;
        }
    }

};

#endif // DEVICEINFOBRODCASTER_H
