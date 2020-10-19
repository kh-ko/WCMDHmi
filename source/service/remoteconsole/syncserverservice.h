#ifndef SYNCSERVERSERVICE_H
#define SYNCSERVERSERVICE_H

#include <QObject>
#include <QTcpServer>

#include "source/service/remoteconsole/syncclient.h"
#include "source/model/informationmodel.h"

class SyncServerService : public QObject
{
    Q_OBJECT
public:
    QTcpServer mServer;
    SyncClient * mpSyncClient = nullptr;
    InformationModel * mpInformation = nullptr;

public slots:
    void onSignalEventNewConnection();
    void onSignalEventFinishedSync();

public:
    void startSyncService(InformationModel * pInformation);
    void openSyncClient(SyncClient * pSyncClient);
    void closeSyncClient();
    void setDeviceNum(int deviceNum);
    explicit SyncServerService(QObject *parent = nullptr);
    ~SyncServerService();

signals:

};

#endif // SYNCSERVERSERVICE_H
