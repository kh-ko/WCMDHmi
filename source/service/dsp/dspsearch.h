#ifndef DSPSEARCH_H
#define DSPSEARCH_H

#include <QObject>
#include <QDateTime>
#include <QUdpSocket>

#include "source/service/dsp/dspsendqueue.h"
#include "source/service/dsp/dspdatastore.h"

class DspSearch : public QObject
{
    Q_OBJECT

public :

    explicit DspSearch(QObject *parent = nullptr):QObject(parent)
    {
    }
    ~DspSearch()
    {
        stopSearch();
    }

    void search()
    {
        DspSendQueueItem dummy;
        dummy.mPacket.setFuncCode(DSP_FUNCCODE_MULTIBLOCK_READ);
        dummy.mPacket.addReadBlock(DSP_GROUP_ID_COMM_STATUS, 0);

        stopSearch();

        mpSock = new QUdpSocket(this);
        mpSock->bind(45454, QUdpSocket::ShareAddress);

        connect(mpSock, SIGNAL(readyRead()), this, SLOT(onRecevie()));

        QByteArray dummyBuff = dummy.mPacket.createSendBuffer();

        qDebug() << "[debug] search dummy packet = " << dummyBuff.toHex();

        mpSock->writeDatagram(dummyBuff, QHostAddress::Broadcast, 10020);
    }

    void stopSearch()
    {
        if(mpSock != nullptr)
        {
            disconnect(mpSock, SIGNAL(readyRead()), this, SLOT(onRecevie()));

            if(mpSock->isOpen())
                mpSock->close();

            mpSock->deleteLater();

            mpSock = nullptr;
        }
    }


signals:
    void signalEventFoundDsp(QString ip);


private slots:
    void onRecevie()
    {
        QByteArray      rcvBuffer;
        QHostAddress    sender;
        quint16         senderPort;
        QString         ip;

        if(mpSock == nullptr)
        {

            return;
        }

        if(mpSock->hasPendingDatagrams() == false)
        {
            return;
        }

        rcvBuffer.resize(mpSock->pendingDatagramSize());
        mpSock->readDatagram(rcvBuffer.data(), rcvBuffer.size(), &sender, &senderPort);


        qDebug() << "[DspSearch::onRecevie]found ip =" << sender.toString();

        emit signalEventFoundDsp(ip);
    }

private:
    QUdpSocket *    mpSock          = nullptr;

};

#endif // DSPSEARCH_H
