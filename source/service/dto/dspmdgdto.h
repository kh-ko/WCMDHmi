#ifndef DSPMDGDTO_H
#define DSPMDGDTO_H
#include <QObject>
#include "source/service/dsp/dspdatastorestruct.h"

class DspMDGDto
{
public:
    QByteArray mGraphData;

    DspMDGDto(){}
    DspMDGDto(const DspMDGDto& copy) :
        mGraphData(copy.mGraphData){}
    ~DspMDGDto(){}

    DspMDGDto& operator=(const DspMDGDto& other)
    {
        mGraphData = other.mGraphData;

        return *this;
    }

    void setValue(QByteArray data)
    {
        mGraphData = data;
    }
};

Q_DECLARE_METATYPE(DspMDGDto);
#endif // DSPMDGDTO_H
