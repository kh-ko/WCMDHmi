#include "sendpacketqueue.h"
#include "source/util/myalloc.h"

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
        return false;

    if(mList.at(0)->mSeq != packet->mSeq)
        return false;

    if(mList.at(0)->mSize != packet->mSize)
        return false;

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
