#include "eventchecker.h"
/*
 *     switch(eventType)
    {
        case EnumDefine::EventType::WEIGHT_NORMAL_TYPE             : return;
        case EnumDefine::EventType::WEIGHT_UNDER_WARNING_TYPE      : return;
        case EnumDefine::EventType::WEIGHT_OVER_WARNING_TYPE       : return;
        case EnumDefine::EventType::WEIGHT_UNDER_TYPE              : return;
        case EnumDefine::EventType::WEIGHT_OVER_TYPE               : return;
        case EnumDefine::EventType::WEIGHT_ETCERROR_TYPE           : return;
        case EnumDefine::EventType::APP_START_TYPE                 : return;
        case EnumDefine::EventType::APP_EXIT_TYPE                  : return;
        case EnumDefine::EventType::METAL_CHECKUP_TYPE             : return;
        case EnumDefine::EventType::WEIGHT_STATIC_CARI_TYPE        : return;
        case EnumDefine::EventType::WEIGHT_DYNAMIC_CARI_TYPE       : return;
        case EnumDefine::EventType::RUN_TYPE                       : return;
        case EnumDefine::EventType::STOP_TYPE                      : return;
        case EnumDefine::EventType::METAL_TRADE_TYPE               : return;
        case EnumDefine::EventType::METAL_DETECT_TYPE              : return;
        case EnumDefine::EventType::METAL_TRADE_CHECK_TYPE         : return;
        case EnumDefine::EventType::METAL_DETECT_CHECK_TYPE        : return;
        case EnumDefine::EventType::WEIGHT_NORMAL_CHECK_TYPE       : return;
        case EnumDefine::EventType::WEIGHT_UNDER_WARNING_CHECK_TYPE: return;
        case EnumDefine::EventType::WEIGHT_OVER_WARNING_CHECK_TYPE : return;
        case EnumDefine::EventType::WEIGHT_UNDER_CHECK_TYPE        : return;
        case EnumDefine::EventType::WEIGHT_OVER_CHECK_TYPE         : return;
        case EnumDefine::EventType::WEIGHT_ETCERROR_CHECK_TYPE     : return;
        case EnumDefine::EventType::WEIGHT_ETC_METAL_ERROR_TYPE    : return;
        default: return false;
    }
 */
EventChecker::EventChecker()
{

}

bool EventChecker::IsWeightEvent(quint16 eventType)
{
    switch(eventType)
    {
        case EnumDefine::EventType::WEIGHT_NORMAL_TYPE         :
        case EnumDefine::EventType::WEIGHT_UNDER_WARNING_TYPE  :
        case EnumDefine::EventType::WEIGHT_OVER_WARNING_TYPE   :
        case EnumDefine::EventType::WEIGHT_UNDER_TYPE          :
        case EnumDefine::EventType::WEIGHT_OVER_TYPE           :
        case EnumDefine::EventType::WEIGHT_ETCERROR_TYPE       :
        case EnumDefine::EventType::WEIGHT_ETC_METAL_ERROR_TYPE:
            return true;
        default:
            return false;
    }
}

bool EventChecker::isWeightTrade(quint16 eventType)
{
    switch(eventType)
    {
        case EnumDefine::EventType::WEIGHT_NORMAL_TYPE         :
        case EnumDefine::EventType::WEIGHT_UNDER_WARNING_TYPE  :
        case EnumDefine::EventType::WEIGHT_OVER_WARNING_TYPE   :
            return true;
        default: return false;
    }
}

bool EventChecker::isWeightNGEvent(quint16 eventType)
{
    switch(eventType)
    {
        case EnumDefine::EventType::WEIGHT_UNDER_TYPE              :
        case EnumDefine::EventType::WEIGHT_OVER_TYPE               :
        case EnumDefine::EventType::WEIGHT_ETCERROR_TYPE           :
        case EnumDefine::EventType::WEIGHT_ETC_METAL_ERROR_TYPE    :
            return true;
        default: return false;
    }
}
bool EventChecker::isMetalDetectEvent(quint16 eventType)
{
    switch(eventType)
    {
        case EnumDefine::EventType::METAL_DETECT_TYPE: return true;
        default: return false;
    }
}

bool EventChecker::IsWeightOrMetal(quint16 eventType)
{
    switch(eventType)
    {
        case EnumDefine::EventType::WEIGHT_NORMAL_TYPE         :
        case EnumDefine::EventType::WEIGHT_UNDER_WARNING_TYPE  :
        case EnumDefine::EventType::WEIGHT_OVER_WARNING_TYPE   :
        case EnumDefine::EventType::WEIGHT_UNDER_TYPE          :
        case EnumDefine::EventType::WEIGHT_OVER_TYPE           :
        case EnumDefine::EventType::WEIGHT_ETCERROR_TYPE       :
        case EnumDefine::EventType::METAL_TRADE_TYPE           :
        case EnumDefine::EventType::METAL_DETECT_TYPE          :
        case EnumDefine::EventType::WEIGHT_ETC_METAL_ERROR_TYPE:
            return true;
        default:
            return false;
    }
}

bool EventChecker::IsNGEvent(quint16 eventType)
{
    switch(eventType)
    {
        case EnumDefine::EventType::WEIGHT_UNDER_TYPE          :
        case EnumDefine::EventType::WEIGHT_OVER_TYPE           :
        case EnumDefine::EventType::WEIGHT_ETCERROR_TYPE       :
        case EnumDefine::EventType::METAL_DETECT_TYPE          :
        case EnumDefine::EventType::WEIGHT_ETC_METAL_ERROR_TYPE:
            return true;
        default:
            return false;
    }
}

bool EventChecker::isCheckEvent(quint16 eventType)
{
    switch(eventType)
    {
        case EnumDefine::EventType::WEIGHT_NORMAL_TYPE             :
        case EnumDefine::EventType::WEIGHT_UNDER_WARNING_TYPE      :
        case EnumDefine::EventType::WEIGHT_OVER_WARNING_TYPE       :
        case EnumDefine::EventType::WEIGHT_UNDER_TYPE              :
        case EnumDefine::EventType::WEIGHT_OVER_TYPE               :
        case EnumDefine::EventType::WEIGHT_ETCERROR_TYPE           :
        case EnumDefine::EventType::APP_START_TYPE                 :
        case EnumDefine::EventType::APP_EXIT_TYPE                  :
        case EnumDefine::EventType::METAL_CHECKUP_TYPE             :
        case EnumDefine::EventType::WEIGHT_STATIC_CARI_TYPE        :
        case EnumDefine::EventType::WEIGHT_DYNAMIC_CARI_TYPE       :
        case EnumDefine::EventType::RUN_TYPE                       :
        case EnumDefine::EventType::STOP_TYPE                      :
        case EnumDefine::EventType::METAL_TRADE_TYPE               :
        case EnumDefine::EventType::METAL_DETECT_TYPE              :
        case EnumDefine::EventType::WEIGHT_ETC_METAL_ERROR_TYPE    :
            return false;
        default: return true;
    }
}
