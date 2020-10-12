#ifndef SYNCSERVERSERVICE_H
#define SYNCSERVERSERVICE_H

#include <QObject>
#include <QTcpServer>

#include "source/service/remoteconsole/syncclient.h"

class SyncServerService : public QObject
{
    Q_OBJECT
public:
    QTcpServer mServer;
    SyncClient * mpSyncClient = nullptr;

public slots:
    void onSignalEventNewConnection();
    void onSignalEventFinishedSync();

public:
    void openSyncClient(SyncClient * pSyncClient);
    void closeSyncClient();
    explicit SyncServerService(QObject *parent = nullptr);
    ~SyncServerService();

signals:

};

#endif // SYNCSERVERSERVICE_H
