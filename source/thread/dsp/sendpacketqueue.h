#ifndef SENDPACKETQUEUE_H
#define SENDPACKETQUEUE_H

#include <QObject>
#include "source/thread/dsp/dsppacketbuilder.h"

class SendPacketQueue : public QObject
{
    Q_OBJECT
public:
    QList<StPacket *> mList;
    explicit SendPacketQueue(QObject *parent = nullptr);
    ~SendPacketQueue();
    void add(StPacket * packet);
    bool remove(StPacket * packet);
    void clear();
    int size();
signals:

};

#endif // SENDPACKETQUEUE_H
