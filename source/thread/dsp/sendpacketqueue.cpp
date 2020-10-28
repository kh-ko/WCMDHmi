#include "sendpacketqueue.h"
#include "source/util/myalloc.h"

#include <QDebug>

SendPacketQueue::SendPacketQueue(QObject *parent) : QObject(parent)
{

}

SendPacketQueue::~SendPacketQueue()
{
    clear();
}
void SendPacketQueue::add(StPacket * packet)
{
    mList.append(packet);
}

bool SendPacketQueue::remove(StPacket * packet)
{

    if(mList.size() < 1)
    {
        qDebug() << "[SendPacketQueue::remove]packet queue is null ";
        return false;
    }

    if(mList.at(0)->mSeq != packet->mSeq)
    {
        qDebug() << "[SendPacketQueue::remove]seq error : queue seq = " << (quint8)(mList.at(0)->mSeq) << ", packet seq" << (quint8)(packet->mSeq);
        return false;
    }

    if(mList.at(0)->mSize != packet->mSize)
    {
        qDebug() << "[SendPacketQueue::remove]size error : queue size = " << mList.at(0)->mSize << ", packet size" << packet->mSize;
        return false;
    }

    MyAlloc::myFree(mList.at(0));
    mList.removeAt(0);

    return true;
}

void SendPacketQueue::clear()
{
    for(int i = 0; i < mList.size(); i ++)
    {
        MyAlloc::myFree(mList.at(i));
    }

    mList.clear();
}
int SendPacketQueue::size()
{
    return mList.size();
}
