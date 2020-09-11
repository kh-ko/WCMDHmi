#ifndef EVENTDTO_H
#define EVENTDTO_H

#include <QObject>

#include "source/thread/dsp/dto/dspaddressdto.h"

class EventDto
{
public:
    StEvent mEvent;

    EventDto(){}
    EventDto(const EventDto& copy)
    {
        memcpy(&mEvent, &(copy.mEvent), sizeof(StEvent));
    }
    EventDto(StEvent * copy)
    {
        memcpy(&mEvent, copy, sizeof(StEvent));
    }
    ~EventDto(){}

    EventDto& operator=(const EventDto& other)
    {
        memcpy(&mEvent, &(other.mEvent), sizeof(StEvent));

        return *this;
    }
    EventDto& operator=(StEvent * other)
    {
        memcpy(&mEvent, other, sizeof(StEvent));

        return *this;
    }
};

Q_DECLARE_METATYPE(EventDto);
#endif // EVENTDTO_H
