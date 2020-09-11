#ifndef LASTERRORMODEL_H
#define LASTERRORMODEL_H

#include <QObject>
#include "source/globaldef/EnumDefine.h"

class LastErrorModel : public QObject
{
    Q_OBJECT

public:
    quint16 mEventType  = EnumDefine::EventType::WEIGHT_NORMAL_TYPE;
    QString mTime       = "";
    quint32 mValue      = 0 ;

    void setEventType(quint16 value){ if(value == mEventType) return; mEventType = value; emit signalEventChangedEventType(mEventType);}
    void setTime     (QString value){ if(value == mTime     ) return; mTime      = value; emit signalEventChangedTime     (mTime     );}
    void setValue    (quint32 value){ if(value == mValue    ) return; mValue     = value; emit signalEventChangedValue    (mValue    );}

signals:
    void signalEventChangedEventType(quint16 value);
    void signalEventChangedTime     (QString value);
    void signalEventChangedValue    (quint32 value);

public:
    void reset()
    {
        setEventType(EnumDefine::EventType::WEIGHT_NORMAL_TYPE);
        setTime     ("");
        setValue    (0);
    }
    explicit LastErrorModel(QObject *parent = nullptr) : QObject(parent){}
};

#endif // LASTERRORMODEL_H
