#include "syncserverservice.h"
#include "source/service/localsetting/localsettingsprovider.h"
void SyncServer::onSignalEventNewConnection()
{
    QTcpSocket *pClient;

    do
    {
        pClient = mServer.nextPendingConnection();

        if(pClient == nullptr)
            break;

        SyncClient * pSyncClient = new SyncClient(pClient, pLSettingSP->mInformation.mDeviceNumber, this);

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

void SyncServer::onSignalEventFinishedSync()
{
    closeSyncClient();
}

void SyncServer::start()
{
    connect(&mServer, SIGNAL(newConnection()), this, SLOT(onSignalEventNewConnection()));

    mServer.listen(QHostAddress::Any, PORT);
}

void SyncServer::stop()
{
    closeSyncClient();
}

void SyncServer::openSyncClient(SyncClient * pSyncClient)
{
    mpSyncClient = pSyncClient;

    connect(mpSyncClient, SIGNAL(signalEventFinishedSync()), this, SLOT(onSignalEventFinishedSync()));
    mpSyncClient->start();
}

void SyncServer::closeSyncClient()
{
    if(mpSyncClient != nullptr)
    {
        disconnect(mpSyncClient, SIGNAL(signalEventFinishedSync()), this, SLOT(onSignalEventFinishedSync()));
        delete mpSyncClient;
        mpSyncClient = nullptr;
    }
}

SyncServer::SyncServer(QObject *parent) : QObject(parent)
{

}

SyncServer::~SyncServer()
{
    closeSyncClient();
}


