#ifndef DSPINFODTO_H
#define DSPINFODTO_H

#include <QObject>

#include "source/thread/dsp/dto/dspaddressdto.h"

class DspInfoDto
{
public:
    StDeviceInfo mDspInfo;

    DspInfoDto(){}
    DspInfoDto(const DspInfoDto& copy)
    {
        memcpy(&mDspInfo, &(copy.mDspInfo), sizeof(StDeviceInfo));
    }
    DspInfoDto(StDeviceInfo* copy)
    {
        memcpy(&mDspInfo, copy, sizeof(StDeviceInfo));
    }
    ~DspInfoDto(){}

    DspInfoDto& operator=(const DspInfoDto& other)
    {
        memcpy(&mDspInfo, &(other.mDspInfo), sizeof(StDeviceInfo));

        return *this;
    }
    DspInfoDto& operator=(StDeviceInfo* other)
    {
        memcpy(&mDspInfo, other, sizeof(StDeviceInfo));

        return *this;
    }
};

Q_DECLARE_METATYPE(DspInfoDto);
#endif // DSPINFODTO_H
