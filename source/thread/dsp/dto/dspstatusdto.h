#ifndef DSPSTATUSDTO_H
#define DSPSTATUSDTO_H

#include <QObject>

#include "source/thread/dsp/dto/dspaddressdto.h"

class DspStatusDto
{
public:
    StDeviceStatus mDspStatus;

    DspStatusDto(){}
    DspStatusDto(const DspStatusDto& copy)
    {
        memcpy(&mDspStatus, &(copy.mDspStatus), sizeof(StDeviceStatus));
    }
    DspStatusDto(StDeviceStatus* copy)
    {
        memcpy(&mDspStatus, copy, sizeof(StDeviceStatus));
    }
    ~DspStatusDto(){}

    DspStatusDto& operator=(const DspStatusDto& other)
    {
        memcpy(&mDspStatus, &(other.mDspStatus), sizeof(StDeviceStatus));

        return *this;
    }
    DspStatusDto& operator=(StDeviceStatus * other)
    {
        memcpy(&mDspStatus, other, sizeof(StDeviceStatus));

        return *this;
    }
};

Q_DECLARE_METATYPE(DspStatusDto);
#endif // DSPSTATUSDTO_H
