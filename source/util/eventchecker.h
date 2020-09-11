#ifndef EVENTCHECKER_H
#define EVENTCHECKER_H

#include "source/globaldef/EnumDefine.h"

class EventChecker
{
public:
    EventChecker();
    static bool IsWeightEvent(quint16 eventType);
    static bool isWeightTrade(quint16 eventType);
    static bool isWeightNGEvent(quint16 eventType);
    static bool isMetalDetectEvent(quint16 eventType);
    static bool IsWeightOrMetal(quint16 eventType);
    static bool IsNGEvent(quint16 eventType);
    static bool isCheckEvent(quint16 eventType);
};
#endif // EVENTCHECKER_H
