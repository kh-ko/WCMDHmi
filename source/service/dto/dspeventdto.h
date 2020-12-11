#ifndef DSPEVENTDTO_H
#define DSPEVENTDTO_H

#include <QObject>
#include "source/service/dsp/dspdatastorestruct.h"

class DspEventDto
{
public:
    StDspEvent mEvent;

    DspEventDto(){}
    DspEventDto(const DspEventDto& copy)
    {
        memcpy(&mEvent, &(copy.mEvent), sizeof(StDspEvent));
    }
    ~DspEventDto(){}

    DspEventDto& operator=(const DspEventDto& other)
    {
        memcpy(&mEvent, &(other.mEvent), sizeof(StDspEvent));

        return *this;
    }

    void setValue(StDspEvent * data)
    {
        memcpy(&mEvent, data, sizeof(StDspEvent));
    }

};

Q_DECLARE_METATYPE(DspEventDto);
#endif // DSPEVENTDTO_H
