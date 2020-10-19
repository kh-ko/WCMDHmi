#include "syncserverservice.h"

void SyncServerService::onSignalEventNewConnection()
{
    QTcpSocket *pClient;

    do
    {
        pClient = mServer.nextPendingConnection();

        if(pClient == nullptr)
            break;

        SyncClient * pSyncClient = new SyncClient(pClient, mpInformation->mDeviceNumber, this);

        if(mpSyncClient != nullptr)
        {
            qDebug() << "[SyncServerService::onSignalEventNewConnection] already sync on other client";

            pSyncClient->sendAleadySync();
            delete pSyncClient;
            continue;
        }

        qDebug() << "[SyncServerService::onSignalEventNewConnection] connected client";
        openSyncClient(pSyncClient);

    }while(pClient != nullptr);
}

void SyncServerService::onSignalEventFinishedSync()
{
    closeSyncClient();
}

void SyncServerService::startSyncService(InformationModel * pInformation)
{
    mpInformation = pInformation;
    connect(&mServer, SIGNAL(newConnection()), this, SLOT(onSignalEventNewConnection()));

    mServer.listen(QHostAddress::Any, 10024);
}

void SyncServerService::openSyncClient(SyncClient * pSyncClient)
{
    mpSyncClient = pSyncClient;

    connect(mpSyncClient, SIGNAL(signalEventFinishedSync()), this, SLOT(onSignalEventFinishedSync()));
    mpSyncClient->start();
}

void SyncServerService::closeSyncClient()
{
    if(mpSyncClient != nullptr)
    {
        disconnect(mpSyncClient, SIGNAL(signalEventFinishedSync()), this, SLOT(onSignalEventFinishedSync()));
        delete mpSyncClient;
        mpSyncClient = nullptr;
    }
}

SyncServerService::SyncServerService(QObject *parent) : QObject(parent)
{

}

SyncServerService::~SyncServerService()
{
    closeSyncClient();
}


