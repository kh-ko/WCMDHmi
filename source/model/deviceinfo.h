#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QObject>

#include "source/globaldef/EnumDefine.h"

class DeviceInfo// : public QObject
{
 //   Q_OBJECT
public:
    quint32 mID                ;
    quint16 mMajorVersion      ;
    quint16 mMinorVersion      ;
    quint16 mMaintenanceVersion;

    DeviceInfo(){}
 //   explicit DeviceInfo(QObject *parent = nullptr): QObject(parent){}
    DeviceInfo(const DeviceInfo& copy):
                        mID                 (copy.mID                ),
                        mMajorVersion       (copy.mMajorVersion      ),
                        mMinorVersion       (copy.mMinorVersion      ),
                        mMaintenanceVersion (copy.mMaintenanceVersion){}

    ~DeviceInfo(){}

    DeviceInfo& operator=(const DeviceInfo& other)
    {
        mID                 = other.mID                ;
        mMajorVersion       = other.mMajorVersion      ;
        mMinorVersion       = other.mMinorVersion      ;
        mMaintenanceVersion = other.mMaintenanceVersion;

        return *this;
    }
};

Q_DECLARE_METATYPE(DeviceInfo);

#endif // DEVICEINFO_H
