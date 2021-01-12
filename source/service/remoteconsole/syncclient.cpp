#include "syncclient.h"

#include "source/globaldef/qmlenumdef.h"
#include "source/service/coreservice.h"

void SyncClient::sendAleadySync()
{
    sendPacket(RemoteEnumDef::RFUNC_CODE_RSYNC_ALREADY_SYNCING, nullptr);
}

void SyncClient::sendTotalSize(qint64 value)
{
    QByteArray content;

    content.append((char *)&value, sizeof(qint64));
    sendPacket(RemoteEnumDef::RFUNC_CODE_RSYNC_INIT, &content);
}
void SyncClient::sendFileName(QString value)
{
    QByteArray content = value.toUtf8();
    sendPacket(RemoteEnumDef::RFUNC_CODE_RSYNC_FILE_INFO, &content);
}

void SyncClient::sendFileContent(QByteArray content)
{
    sendPacket(RemoteEnumDef::RFUNC_CODE_RSYNC_FILE_CONTENT, &content);
}
void SyncClient::sendSyncComplete()
{
    sendPacket(RemoteEnumDef::RFUNC_CODE_RSYNC_COMPLETE, nullptr);
}

void SyncClient::sendPacket(int funcCode, QByteArray *pContent)
{
    StRConsolePacket packetHeader;
    QByteArray packetBuf;

    packetHeader.mDeviceNum = mDeviceNum;
    packetHeader.mFuncCode = funcCode;


    if(pContent == nullptr)
    {
        packetHeader.mSize = 0;
    }
    else
    {
        packetHeader.mSize = pContent->size();
    }

    packetBuf.append((char *)&packetHeader, sizeof(StRConsolePacket));

    if(pContent != nullptr)
    {
        packetBuf.append(*pContent);
    }

    mTimer.start();
    mpClient->write(packetBuf);

    mSentSize = packetBuf.size();
}

qint64 SyncClient::makeSyncFileList(QString lastSyncDate)
{
    int syncDateNumber = lastSyncDate == "" ? 0
                       : lastSyncDate.split(".")[0].toInt() * 10000
                       + lastSyncDate.split(".")[1].toInt() * 100
                       + lastSyncDate.split(".")[2].toInt();

    mSyncReqDate = QDate::currentDate();

    QDir dir(FileDef::HISTORY_DIR());
    QFileInfoList fileList = dir.entryInfoList(QStringList() << "*.txt",QDir::Files, QDir::SortFlag::Name);

    qint64 totalSize = 0;

    for(int i = 0; i < fileList.size(); i ++)
    {
        QString fileName = fileList.at(i).fileName();
        QStringList strSplitList = fileName.split(".")[0].split("-");

        if(strSplitList.size() < 3)
            continue;

        int dateNumber = fileName.split("-")[0].toInt() * 10000
                       + fileName.split("-")[1].toInt() * 100
                       + fileName.split("-")[2].toInt();

        if(dateNumber >= syncDateNumber)
        {
            mSyncFileList.append(fileName);
            totalSize = totalSize + fileList.at(i).size();
        }
    }

    return totalSize;
}

void SyncClient::start()
{
    connect(mpClient, SIGNAL(readyRead   (                            )), this, SLOT(onReceive  (                            )));
    connect(mpClient, SIGNAL(bytesWritten(qint64                      )), this, SLOT(onWritten  (qint64                      )));
    connect(mpClient, SIGNAL(error       (QAbstractSocket::SocketError)), this, SLOT(onSockError(QAbstractSocket::SocketError)));

    connect(&mFileRThread, SIGNAL(signalEventReadBytes(int, QByteArray)), this, SLOT(onSignalEventReadBytes(int, QByteArray)));
    connect(&mFileRThread, SIGNAL(signalEventOpenFile(int, QString)), this, SLOT(onSignalEventOpenFile(int, QString)));
    connect(&mFileRThread, SIGNAL(signalEventEof()), this, SLOT(onSignalEventEof()));

    mTimer.start();
    onReceive();
}

SyncClient::SyncClient(QTcpSocket * pSock, int deviceNum, QObject *parent): QObject(parent)
{
    mpClient = pSock;
    mDeviceNum = deviceNum;
    mTimer.setInterval(5000);
    connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

SyncClient::~SyncClient()
{
    disconnect(mpClient, SIGNAL(readyRead   (                            )), this, SLOT(onReceive  (                            )));
    disconnect(mpClient, SIGNAL(bytesWritten(qint64                      )), this, SLOT(onWritten  (qint64                      )));
    disconnect(mpClient, SIGNAL(error       (QAbstractSocket::SocketError)), this, SLOT(onSockError(QAbstractSocket::SocketError)));

    mTimer.stop();
    if(mpClient->state() != QAbstractSocket::SocketState::UnconnectedState)
    {
        mpClient->disconnectFromHost();
        mpClient->waitForDisconnected(1000);
    }
    mpClient->close();
    mpClient->deleteLater();
}

void SyncClient::onReceive()
{
    if(mpClient == nullptr)
            return;

    int headerSize = sizeof(StRConsolePacket);
    int availableSize = mpClient->bytesAvailable();

    if(mRcvBuffer.size() == 0 && availableSize < headerSize)
        return;
    else if(mRcvBuffer.size() == 0)
    {
        mRcvBuffer.append(mpClient->read(headerSize));
        availableSize = availableSize - headerSize;
    }

    StRConsolePacket * pHeader = (StRConsolePacket *)mRcvBuffer.data();

    if(availableSize < pHeader->mSize)
        return;

    mRcvBuffer.append(mpClient->read(pHeader->mSize));
    availableSize = availableSize - pHeader->mSize;

    pHeader = (StRConsolePacket *)mRcvBuffer.data();

    if(pHeader->mFuncCode != RemoteEnumDef::RFUNC_CODE_RSYNC)
    {
        emit signalEventFinishedSync();
        return;
    }

    mTimer.stop();

    QString lastSyncDate = pHeader->mSize == 0 ? "" : QString::fromUtf8(pHeader->mData, pHeader->mSize);

    qint64 totalSize = makeSyncFileList(lastSyncDate);

    sendTotalSize(totalSize);
}

void SyncClient::onWritten(qint64 value)
{
    mSentSize = mSentSize - value;

    if(mSentSize < 1)
    {
        mTimer.stop();

        if(mSyncFileList.size() == 0)
        {
            pLSettingSP->setBackupLastDate(mSyncReqDate);
            sendSyncComplete();
            emit signalEventFinishedSync();
        }
        else
        {
            mFileRThread.onCommandReadBytes(FileDef::HISTORY_DIR(), mSyncFileList[0], 3000);
        }
    }
}

void SyncClient::onSockError(QAbstractSocket::SocketError error)
{
    emit signalEventFinishedSync();
}

void SyncClient::onTimeout()
{
    emit signalEventFinishedSync();
}

void SyncClient::onSignalEventOpenFile(int error, QString fileName)
{
    if(error == FileLoaderThreadEx::FILE_LOADER_ERR_NONE)
    {
        sendFileName(fileName);
    }
    else
    {
        mSyncFileList.removeAt(0);
        onWritten(0);
    }
}

void SyncClient::onSignalEventEof()
{
    mSyncFileList.removeAt(0);
    onWritten(0);
}

void SyncClient::onSignalEventReadBytes(int error, QByteArray content)
{
    if(error == FileLoaderThreadEx::FILE_LOADER_ERR_NONE)
    {
        sendFileContent(content);
    }
    else
    {
        emit signalEventFinishedSync();
    }
}
