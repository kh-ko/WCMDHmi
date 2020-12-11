#ifndef DSPCONNINFODTO_H
#define DSPCONNINFODTO_H
#include <QObject>
#include <QDebug>

#include "source/service/defaultsetting/defaultsettingsprovider.h"
#include "source/service/dsp/dspdatastorestruct.h"

class DspConnInfoDto
{
public:
    quint64 mDspSeq;
    QString mIp    ;
    quint16 mPort  ;

    DspConnInfoDto(){}
    DspConnInfoDto(const DspConnInfoDto& copy) :
        mDspSeq(copy.mDspSeq),
        mIp    (copy.mIp    ),
        mPort  (copy.mPort  ){}
    ~DspConnInfoDto(){}

    DspConnInfoDto& operator=(const DspConnInfoDto& other)
    {
        mDspSeq = other.mDspSeq;
        mIp     = other.mIp    ;
        mPort   = other.mPort  ;

        return *this;
    }

    bool setValue(QString value)
    {
        quint64 seq  = 0;
        QString ip   = "";
        quint16 port = 0;

        QStringList fieldList = value.split("\n");

        foreach(QString field ,fieldList)
        {
            if(field.contains(":") == false)
                continue;

            int splitIdx  = field.indexOf(":");
            QString key   = field.left(splitIdx);
            QString value = field.mid(splitIdx+1);

            if     (key.contains("Seq" )){ seq  = value.toULongLong();}
            else if(key.contains("Ip"  )){ ip   = value              ;}
            else if(key.contains("Port")){ port = value.toUShort()   ;}
        }

        if(seq != 0 && port != 0 && ip.split(".").size() == 4)
        {
            setValue(seq, ip, port);
            return true;
        }

        return false;
    }
    void setValue(quint64 seq, QString ip, quint16 port)
    {
        mDspSeq = seq;
        mIp     = ip    ;
        mPort   = port  ;
    }

    void setDefaultValue()
    {
        setValue(1, pDefaultSP->DSP_CONNINFO_IP, pDefaultSP->DSP_CONNINFO_PORT);
    }

    QString toString(){
        return QString("Seq:%1\nIp:%2\nPort:%3").arg(mDspSeq).arg(mIp).arg(mPort);
    }
};

Q_DECLARE_METATYPE(DspConnInfoDto);
#endif // DSPCONNINFODTO_H
