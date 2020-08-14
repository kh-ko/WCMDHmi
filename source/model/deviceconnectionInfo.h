#ifndef DEVICECONNECTIONINFO_H
#define DEVICECONNECTIONINFO_H

#include <QObject>

class DeviceConnectionInfo// : public QObject
{
//    Q_OBJECT
public:
    quint16 mSeq;
    QString mIp;
    quint16 mPort;

    //explicit DeviceConnectionInfo(QObject *parent = nullptr): QObject(parent){}
    DeviceConnectionInfo(){}
    DeviceConnectionInfo(const DeviceConnectionInfo& copy):
                          mSeq  (copy.mSeq),
                          mIp   (copy.mIp),
                          mPort (copy.mPort){}

    ~DeviceConnectionInfo(){}

    DeviceConnectionInfo& operator=(const DeviceConnectionInfo& other)
    {
        mSeq = other.mSeq;
        mIp  = other.mIp;
        mPort= other.mPort;

        return *this;
    }
};

Q_DECLARE_METATYPE(DeviceConnectionInfo);

#endif // DEVICECONNECTIONINFO_H
