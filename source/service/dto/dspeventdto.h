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
        memcpy(&mEvent, &(copy.mEvent), sizeof(StDspEvent));
        if(copy.mEvent.mEventType == (int)EnumDef::ET_METAL_DETECT)
        {
            mMdDetectChannel = 1;
        }
        else if(copy.mEvent.mEventType == (int)EnumDef::ET_METAL_DETECT_2)
        {
            mMdDetectChannel = 2;
            mEvent.mEventType = (int)EnumDef::ET_METAL_DETECT;
        }
        else
        {
            mMdDetectChannel = 0;
        }
    }
    ~DspEventDto(){}

    DspEventDto& operator=(const DspEventDto& other)
    {
        memcpy(&mEvent, &(other.mEvent), sizeof(StDspEvent));
        if(other.mEvent.mEventType == (int)EnumDef::ET_METAL_DETECT)
        {
            mMdDetectChannel = 1;
        }
        else if(other.mEvent.mEventType == (int)EnumDef::ET_METAL_DETECT_2)
        {
            mMdDetectChannel = 2;
            mEvent.mEventType = (int)EnumDef::ET_METAL_DETECT;
        }
        else
        {
            mMdDetectChannel = 0;
        }

        return *this;
    }

    void setValue(StDspEvent * data)
    {
        memcpy(&mEvent, data, sizeof(StDspEvent));
    }

};

Q_DECLARE_METATYPE(DspEventDto);
#endif // DSPEVENTDTO_H
