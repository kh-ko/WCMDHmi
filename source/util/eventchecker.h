#ifndef EVENTCHECKER_H
#define EVENTCHECKER_H

#include "source/globaldef/EnumDefine.h"

class EventChecker
{
public:
    EventChecker();
    static bool isWeightEvent(quint16 eventType);
    static bool isMetalEvent(quint16 eventType);
    static bool isTrade(quint16 eventType);
    static bool isWeightTrade(quint16 eventType);
    static bool isWeightNGEvent(quint16 eventType);
    static bool isMetalDetectEvent(quint16 eventType);
    static bool isWeightOrMetal(quint16 eventType);
    static bool isMetalCheckup(quint16 eventType);
    static bool isWeightCari(quint16 eventType);
    static bool isNGEvent(quint16 eventType);
    static bool isCheckEvent(quint16 eventType);
};
#endif // EVENTCHECKER_H
