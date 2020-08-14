#ifndef METALDETECTORGRAPHDATA_H
#define METALDETECTORGRAPHDATA_H

#include <QObject>
#include <QDebug>

#include "source/globaldef/EnumDefine.h"
#include "source/service/dsp/myalloc.h"
#pragma pack(push, 1)

struct _MetalDetectorGraphData{
    int mRef;
    quint16 mSensorCnt;
    quint16 mPointCnt;
    qint16  mArrayPoints[0];
};
#pragma pack(pop)


class MetalDetectorGraphData// : public QObject
{
//   Q_OBJECT

public:
    _MetalDetectorGraphData *mData;
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
    /*explicit MetalDetectorGraphData(QObject *parent = nullptr)//: QObject(parent)
    {
        mData = nullptr;
    }*/

    MetalDetectorGraphData()//: QObject(parent)
    {
        mData = nullptr;
    }

    MetalDetectorGraphData(const MetalDetectorGraphData& copy)
    {
        mData = copy.mData;
        addDataRef();
    }

    ~MetalDetectorGraphData()
    {
        if(mData != nullptr)
        {
            delDataRef();

            if(getDataRef() == 0)
            {
                MyAlloc::free(mData);
            }
        }
    }

    bool setData(quint16 size, char * data){
        quint16 checkSize;
        quint16 pointCnt;
        quint16 sensorCnt;
        memcpy(&sensorCnt, data, 2);
        memcpy(&pointCnt, data + 2, 2);

        checkSize = (pointCnt * sensorCnt * sizeof(quint16) * 2);

        if(size < 2 || (size*2) != checkSize + 4)
        {
            qDebug() << "MD Graph size error";
            return false;
        }

        mData = (_MetalDetectorGraphData *)MyAlloc::alloc( sizeof(_MetalDetectorGraphData) + (pointCnt * sensorCnt * sizeof(quint16) * 2)); // malloc( sizeof(_MetalDetectorGraphData) + (pointCnt * sensorCnt * sizeof(quint16) * 2));
        mData->mRef = 0;
        mData->mSensorCnt = sensorCnt;
        mData->mPointCnt = pointCnt;
        memcpy(mData->mArrayPoints, data + 4, (pointCnt * sensorCnt * sizeof(quint16) * 2));

        addDataRef();

        return true;
    }
};

Q_DECLARE_METATYPE(MetalDetectorGraphData);

#endif // METALDETECTORGRAPHDATA_H
