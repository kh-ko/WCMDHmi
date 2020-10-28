#ifndef DEVICEINFOBRODCASTER_H
#define DEVICEINFOBRODCASTER_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QUdpSocket>
#include "source/model/informationmodel.h"

class DeviceInfoBrodcastWorker : public QObject
{
    Q_OBJECT
public:
    QTimer      *mpTimer;
    QHostAddress mGroupAddress;
    quint16      mPort    = 31072;
    int         mDeviceNum;
    QUdpSocket *mpSocket = nullptr;

public slots:
    void onStart();
    void onSockError(QAbstractSocket::SocketError error);
    void onReceive();
    void onTimeTick();
    void onSignalEventChangedDeviceNumber(int deviceNumber);
public :

    explicit DeviceInfoBrodcastWorker(QObject *parent = nullptr);
    ~DeviceInfoBrodcastWorker();
    void open();
    void close();
};

class DeviceInfoBrodcaster : public QObject
{
    Q_OBJECT
public:
    DeviceInfoBrodcastWorker * mpWoker = nullptr;
    QThread mThread;

    void startBrodcast(InformationModel * pInformation)
    {
        mpWoker = new DeviceInfoBrodcastWorker;
        mpWoker->mDeviceNum = pInformation->mDeviceNumber;
        mpWoker->moveToThread(&mThread);

        connect(&mThread, &QThread::finished, mpWoker, &QObject::deleteLater);
        connect(&mThread, &QThread::started,  mpWoker, &DeviceInfoBrodcastWorker::onStart);
        connect(pInformation, SIGNAL(signalEventChangedDeviceNumber(int)), mpWoker, SLOT(onSignalEventChangedDeviceNumber(int)));

        mThread.start();
    }
    explicit DeviceInfoBrodcaster(QObject *parent = nullptr) : QObject(parent){}
    ~DeviceInfoBrodcaster()
    {
        if(mThread.isRunning())
        {
            mThread.quit();
            mThread.wait();
        }
    }

signals:

};

#endif // DEVICEINFOBRODCASTER_H
