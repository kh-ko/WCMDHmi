#ifndef WCCARIBRATIONINFO_H
#define WCCARIBRATIONINFO_H
#include <QObject>

#include "source/globaldef/EnumDefine.h"

class WCCaribrationInfo// : public QObject
{
 //   Q_OBJECT
public:
    quint32 mStandardWeight;

    WCCaribrationInfo(){}
 //   explicit DeviceInfo(QObject *parent = nullptr): QObject(parent){}
    WCCaribrationInfo(const WCCaribrationInfo& copy):
                        mStandardWeight(copy.mStandardWeight){}

    ~WCCaribrationInfo(){}

    WCCaribrationInfo& operator=(const WCCaribrationInfo& other)
    {
        mStandardWeight = other.mStandardWeight;

        return *this;
    }
};

Q_DECLARE_METATYPE(WCCaribrationInfo);

#endif // WCCARIBRATIONINFO_H
