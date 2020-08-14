#ifndef WEIGHTCHECKERGRAPHDATA_H
#define WEIGHTCHECKERGRAPHDATA_H

#include <QObject>
#include <QDebug>
#include "source/globaldef/EnumDefine.h"
#include "source/service/dsp/myalloc.h"

#pragma pack(push, 1)
struct WeightChekerGraphPoint{
    quint16 type;
    quint32 rawValue;
    quint32 value;
};

struct _WeightChekerGraphData{
    int mRef;
    quint16 mPointCnt;
    WeightChekerGraphPoint mArrayPoints[0];
};
#pragma pack(pop)


class WeightChekerGraphData// : public QObject
{
    //Q_OBJECT

public:
    _WeightChekerGraphData *mData;
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

public:
    /*explicit WeightChekerGraphData(QObject *parent = nullptr): QObject(parent)
    {
        mData = nullptr;
    }*/

    WeightChekerGraphData()
    {
        mData = nullptr;
    }

    WeightChekerGraphData(const WeightChekerGraphData& copy)
    {
        mData = copy.mData;
        addDataRef();
    }

    ~WeightChekerGraphData()
    {
        if(mData != nullptr)
        {
            delDataRef();

            if(getDataRef() == 0)
            {
                MyAlloc::free(mData);
                //free(mData);
            }
        }
    }

    bool setData(quint16 size, char * data){
        quint16 pointCnt;
        int allocSize = 0;
        memcpy(&pointCnt, data, 2);

        allocSize = pointCnt * sizeof(WeightChekerGraphPoint);

        if(size < 1 || ((size* 2) != (allocSize + 2)))
        {
            qDebug() << "WC Graph size error : " << size << ", alloc size :" << (allocSize + 2);
            return false;
        }

        //qDebug() << "setData";
        mData = (_WeightChekerGraphData *)MyAlloc::alloc(sizeof(_WeightChekerGraphData) + (pointCnt * sizeof(WeightChekerGraphPoint)));

        if(mData == nullptr || mData == NULL)
        {
            qDebug() << "alloc failed";
            return false;
        }
        //mData = (_WeightChekerGraphData *)malloc( sizeof(_WeightChekerGraphData) + (pointCnt * sizeof(WeightChekerGraphPoint)));
        mData->mRef = 0;
        mData->mPointCnt = pointCnt;
        memcpy(mData->mArrayPoints, data + 2, (pointCnt * sizeof(WeightChekerGraphPoint)));

        addDataRef();

        return true;
    }
};

Q_DECLARE_METATYPE(WeightChekerGraphData);

#endif // WEIGHTCHECKERGRAPHDATA_H
