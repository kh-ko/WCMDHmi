#ifndef DSPWCGDTO_H
#define DSPWCGDTO_H
#include <QObject>
#include "source/service/dsp/dspdatastorestruct.h"

class DspWCGDto
{
public:
    QByteArray mGraphData;

    DspWCGDto(){}
    DspWCGDto(const DspWCGDto& copy) :
        mGraphData(copy.mGraphData){}
    ~DspWCGDto(){}

    DspWCGDto& operator=(const DspWCGDto& other)
    {
        mGraphData = other.mGraphData;

        return *this;
    }

    void dataResize(int size)
    {
        mGraphData.resize(size);
    }

    void setValue(StDspWCG * data)
    {
        mGraphData.append((char *)data, data->mPointCnt * sizeof(StDspWCGPoint));
    }
};

Q_DECLARE_METATYPE(DspWCGDto);
#endif // DSPWCGDTO_H
