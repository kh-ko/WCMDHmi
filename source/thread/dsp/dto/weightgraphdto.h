#ifndef WEIGHTGRAPHDTO_H
#define WEIGHTGRAPHDTO_H

#include <QObject>
#include <QDebug>

#include "source/thread/dsp/dto/dspaddressdto.h"
#include "source/util/myalloc.h"

class WeightGraphDto
{
public:
    StWeightGraphDataWrapper *mData = nullptr;

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

    WeightGraphDto(){ mData = nullptr;}
    WeightGraphDto(const WeightGraphDto& copy)
    {
        mData = copy.mData;
        addDataRef();
    }
    WeightGraphDto(StWeightCheckerGraph* copy, quint16 size)
    {
        int checkSize = copy->pointCnt * sizeof(StWeightCheckerGraphPoint);

        if(size < 1 || ((size* 2) != (checkSize + 2)))
        {
            qDebug() << "WC Graph size error : " << size << ", pointDataSize size :" << checkSize;
            return ;
        }

        mData = (StWeightGraphDataWrapper *)MyAlloc::myAlloc(sizeof(int) + (size * 2));

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

    ~WeightGraphDto()
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

Q_DECLARE_METATYPE(WeightGraphDto);
#endif // WEIGHTGRAPHDTO_H
