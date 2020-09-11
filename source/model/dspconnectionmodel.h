#ifndef DSPCONNECTIONMODEL_H
#define DSPCONNECTIONMODEL_H

#include <QObject>
#include <QMap>

class DspConnectionModel : public QObject
{
    Q_OBJECT

public:
    quint64 mSeq;
    QString mIp;
    quint16 mPort;

    void setStringValue(QString value)
    {
        QStringList listRow = value.split("\n");

        for(int i = 0; i < listRow.size(); i++)
        {
            QString row = listRow.at(i);

            if(row.contains(":") == false)
                continue;

            QString key = row.split(":")[0];
            QString value = row.split(":")[1];

            if     (key == "Seq"                  ){ mSeq                   = value.toULongLong();}
            else if(key == "Ip"                   ){ mIp                    = value              ;}
            else if(key == "Port"                 ){ mPort                  = value.toUInt()     ;}
        }
    }
    QString toString(){
        return QString("Seq:%1\nIp:%2\nPort:%3").arg(mSeq).arg(mIp).arg(mPort);
    }

public:

    explicit DspConnectionModel(QObject *parent = nullptr) : QObject(parent){}
};
#endif // DSPCONNECTIONMODEL_H
