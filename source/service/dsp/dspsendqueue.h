#ifndef DSPSENDQUEUE_H
#define DSPSENDQUEUE_H

#include <QObject>
#include <QDebug>
#include <QDateTime>
#include "source/service/dsp/dspsendqueueitem.h"

class DspSendQueue : public QObject
{
    Q_OBJECT

public:
    int                       mTryCnt           ;
    quint64                   mSentTime      = 0;
    char                      mTransactionID = 0;
    QList<DspSendQueueItem *> mQueue            ;

    explicit DspSendQueue(QObject * parent = nullptr):QObject(parent){}

    quint64 compareSentTime(QDateTime now)
    {
        if(mSentTime == 0)
            return 0;

        return now.toMSecsSinceEpoch() - mSentTime;
    }

    int getTryCnt()
    {
        return mTryCnt;
    }

    bool isWait()
    {
        return (mSentTime != 0);
    }
    int size()
    {
        return mQueue.size();
    }

    void clear()
    {
        mTryCnt = 0;
        mSentTime = 0;
        mTransactionID = 0;

        foreach(DspSendQueueItem * pQueueItem, mQueue)
        {
            delete pQueueItem;
        }

        mQueue.clear();
    }
    bool push(DspSendQueueItem * pNewItem, bool checkSame = false)
    {
        if(checkSame && mQueue.size() > 0)
        {
            foreach(DspSendQueueItem * pQueueItem, mQueue)
            {
                if(pNewItem->mPacket.isEqual(pQueueItem->mPacket))
                    return false;
            }
        }
        mQueue.append(pNewItem);
        return true;
    }
    QByteArray getSendPacketBuffer()
    {
        DspSendQueueItem * pItem;

        if(mQueue.size() < 1)
        {
            QByteArray temp;
            qDebug() << "[DspSendQueue::get] queue size is zero";
            return temp;
        }

        pItem = mQueue.at(0);

        pItem->mPacket.setTransactionID(mTransactionID);

        mTryCnt++;
        mSentTime = QDateTime::currentMSecsSinceEpoch();

        return pItem->mPacket.createSendBuffer();
    }

    bool checkAckPacket(DspPacket * pPacket)
    {
        DspSendQueueItem * pItem;

        if(mQueue.size() < 1)
        {
            qDebug() << "[DspSendQueue::compareSentPacket] queue size is zero";
            return false;
        }

        pItem = mQueue.at(0);

        if(pPacket->getTransactionID() != pItem->mPacket.getTransactionID())
        {
            qDebug() << "[DspSendQueue::compareSentPacket] TransactionID not match";
            return false;
        }

        return true;
    }

    DspSendQueueItem * pop()
    {
        DspSendQueueItem * pItem;

        if(mQueue.size() < 1)
        {
            qDebug() << "[DspSendQueue::compareSentPacket] queue size is zero";
            return nullptr;
        }

        pItem =  mQueue.at(0);

        mTryCnt = 0;
        mSentTime = 0;
        mTransactionID++;

        mQueue.removeAt(0);

        return pItem;
    }
};
#endif // DSPSENDQUEUE_H
