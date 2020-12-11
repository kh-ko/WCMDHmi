#ifndef DSPSENDQUEUEITEM_H
#define DSPSENDQUEUEITEM_H

#include <QObject>
#include <QDebug>
#include "source/service/dsp/packet/dsppacket.h"


class DspSendQueueItem: QObject
{
    Q_OBJECT
public:
    bool         mIsFRPacket = false;
    DspPacket    mPacket;

    explicit DspSendQueueItem(QObject *parent = nullptr) : QObject(parent){
    }
    ~DspSendQueueItem(){}
};
#endif // DSPSENDQUEUEITEM_H
