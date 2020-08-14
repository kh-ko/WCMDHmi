#ifndef EVENTINFO_H
#define EVENTINFO_H

#include <QObject>

#include "source/globaldef/EnumDefine.h"

class EventInfo// : public QObject
{
 //   Q_OBJECT
public:
    EnumDefine::EventType     mEventType  ;
    quint32                   mEventValue ;

    EventInfo(){}
//    explicit EventInfo(QObject *parent = nullptr): QObject(parent){}
    EventInfo(const EventInfo& copy):
                        mEventType  (copy.mEventType    ),
                        mEventValue (copy.mEventValue   ){}

    ~EventInfo(){}

    EventInfo& operator=(const EventInfo& other)
    {
        mEventType  = other.mEventType ;
        mEventValue = other.mEventValue;

        return *this;
    }
};

Q_DECLARE_METATYPE(EventInfo);
#endif // EVENTINFO_H
