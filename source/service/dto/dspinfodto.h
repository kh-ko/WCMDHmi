#ifndef DSPINFODTO_H
#define DSPINFODTO_H

#include <QObject>
#include "source/service/dsp/dspdatastorestruct.h"

class DspInfoDto
{
public:
    StDspInfo    mInfo;

    DspInfoDto(){}
    DspInfoDto(const DspInfoDto& copy)
    {
        memcpy(&mInfo, &(copy.mInfo), sizeof(StDspInfo));
    }
    ~DspInfoDto(){}

    DspInfoDto& operator=(const DspInfoDto& other)
    {
        memcpy(&mInfo, &(other.mInfo), sizeof(StDspInfo));

        return *this;
    }

    void setValue(StDspInfo * pInfo)
    {
        memcpy(&mInfo, pInfo, sizeof(StDspInfo));
    }

};

Q_DECLARE_METATYPE(DspInfoDto);
#endif // DSPINFODTO_H
