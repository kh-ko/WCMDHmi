#ifndef SYNCCLIENT_H
#define SYNCCLIENT_H

#include <QObject>
#include <QTimer>
#include <QTcpSocket>
#include <QApplication>
#include <QDir>

#include "source/globaldef/EnumDefine.h"
#include "source/thread/remoteconsole/dto/devicesocketdto.h"
#include "source/util/fileloaderthreadex.h"

class SyncClient : public QObject
{
    Q_OBJECT

public:
    QTimer             mTimer;
    QTcpSocket        *mpClient = nullptr;
    QByteArray         mRcvBuffer;
    QStringList        mSyncFileList;
    qint64             mSentSize = 0;
    FileLoaderThreadEx mFileRThread;

    void sendAleadySync();
    void sendTotalSize(qint64 value);
    void sendFileName(QString value);
    void sendFileContent(QByteArray content);
    void sendSyncComplete();
    void sendPacket(int funcCode, QByteArray * pContent);
    qint64 makeSyncFileList(QString lastSyncDate);

    void start();
    explicit SyncClient(QObject *parent = nullptr): QObject(parent){}
    SyncClient(QTcpSocket * pSock, QObject *parent);
    ~SyncClient();

signals:
    void signalEventFinishedSync();
public slots:
    void onReceive  (                            );
    void onWritten  (qint64                      );
    void onSockError(QAbstractSocket::SocketError);
    void onTimeout();

    void onSignalEventOpenFile(int error, QString fileName);
    void onSignalEventEof();
    void onSignalEventReadBytes(int error, QByteArray content);
};

#endif // SYNCCLIENT_H
