#ifndef METALGRAPHDTO_H
#define METALGRAPHDTO_H

#include <QObject>
#include <QDebug>

#include "source/thread/dsp/dto/dspaddressdto.h"
#include "source/util/myalloc.h"

class MetalGraphDto
{
public:
    StMetalGraphDataWrapper *mData = nullptr;

    void addDataRef()
    {
        if(mData != nullptr){mData->mRef++;}
    }

    void delDataRef()
    {
        if(mData != nullptr){mData->mRef--;}
    }

    int getDataRef()
    {
        if(mData != nullptr){ return mData->mRef;}

        return 0;
    }

    MetalGraphDto(){ mData = nullptr;}
    MetalGraphDto(const MetalGraphDto& copy)
    {
        mData = copy.mData;
        addDataRef();
    }
    MetalGraphDto(StMetalDetectorGraph* copy, quint16 size)
    {
        int checkSize = (copy->mPointCnt * copy->mSensorCnt * sizeof(quint16) * 2);

        if(size < 1 || ((size * 2) != (checkSize + 4)))
        {
            qDebug() << "MD Graph size error : " << size << ", checkSize size :" << checkSize;
            return ;
        }

        mData = (StMetalGraphDataWrapper *)MyAlloc::myAlloc(sizeof(int) + (size * 2));

        if(mData == nullptr || mData == NULL)
        {
            qDebug() << "alloc failed";
            mData = nullptr;
            return;
        }

        mData->mRef = 0;
        memcpy(&mData->mData, copy, (size * 2));

        addDataRef();
    }

    ~MetalGraphDto()
    {
        if(mData != nullptr)
        {
            delDataRef();

            if(getDataRef() == 0)
            {
                MyAlloc::myFree(mData);
            }
        }
    }
};

Q_DECLARE_METATYPE(MetalGraphDto);
#endif // METALGRAPHDTO_H
