#ifndef DSPEVENTDTO_H
#define DSPEVENTDTO_H

#include <QObject>
#include "source/service/dsp/dspdatastorestruct.h"
#include "source/service/dto/enum/enumdef.h"

class DspEventDto
{
public:
    int mMdDetectChannel = 0;
    StDspEvent mEvent;

    DspEventDto(){}
    DspEventDto(const DspEventDto& copy)
    {
        mMdDetectChannel = copy.mMdDetectChannel;
        memcpy(&mEvent, &(copy.mEvent), sizeof(StDspEvent));
    }
    ~DspEventDto(){}

    DspEventDto& operator=(const DspEventDto& other)
    {
        mMdDetectChannel = other.mMdDetectChannel;
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
