#ifndef MONITORINGSERVICE_H
#define MONITORINGSERVICE_H

#include <QObject>
#include <QUdpSocket>

#include "source/service/productsetting/productsprovider.h"
#include "source/service/localsetting/localsettingsprovider.h"
#include "source/service/work/worksprovider.h"

#define pMonitoringSvr MonitoringServer::getInstance()

class MonitoringServer : public QObject
{
    Q_OBJECT
public:
    static MonitoringServer * getInstance()
    {
        static MonitoringServer *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new MonitoringServer();
        }

        return mpSelf;
    }

    const quint16 PORT    = 10026;

    quint64      mDspSeq = 0;
    QUdpSocket * mpSocket = nullptr;
    QHostAddress mHostAddr;

public slots:
    void onReceive();
    void onSockError(QAbstractSocket::SocketError error);

public:
    void start();
    void stop();
    explicit MonitoringServer(QObject *parent = nullptr);
    ~MonitoringServer();

private:
    void open();
    void close();

};

#endif // MONITORINGSERVICE_H
