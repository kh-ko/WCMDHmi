#ifndef SYNCSERVERSERVICE_H
#define SYNCSERVERSERVICE_H

#include <QObject>
#include <QTcpServer>

#include "source/service/remoteconsole/syncclient.h"
#include "source/service/localsetting/localsettingsprovider.h"

#define pSyncgSvr SyncServer::getInstance()

class SyncServer : public QObject
{
    Q_OBJECT
public:
    static SyncServer * getInstance()
    {
        static SyncServer *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new SyncServer();
        }

        return mpSelf;
    }
    const quint16 PORT = 10024;
    QTcpServer mServer;
    SyncClient * mpSyncClient = nullptr;

public slots:
    void onSignalEventNewConnection();
    void onSignalEventFinishedSync();

public:
    void start();
    void stop();
    void openSyncClient(SyncClient * pSyncClient);
    void closeSyncClient();
    void setDeviceNum(int deviceNum);
    explicit SyncServer(QObject *parent = nullptr);
    ~SyncServer();

signals:

};

#endif // SYNCSERVERSERVICE_H
