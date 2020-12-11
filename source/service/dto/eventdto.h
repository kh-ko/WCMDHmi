#ifndef EVENTDTO_H
#define EVENTDTO_H

#include <QObject>
#include <QDateTime>
#include "source/service/def/datetimeform.h"
#include "source/service/dto/enum/enumdef.h"
class EventDto
{
public:
    QDateTime  mDateTime;
    quint64    mDspSeq  ;
    quint64    mPDSeq   ;
    int        mPDHisIdx;
    quint16    mEType   ;
    quint32    mEValue  ;

    static bool isWCEvent(quint16 eventType)
    {
        switch(eventType)
        {
            case EnumDef::ET_WEIGHT_NORMAL         :
            case EnumDef::ET_WEIGHT_UNDER_WARNING  :
            case EnumDef::ET_WEIGHT_OVER_WARNING   :
            case EnumDef::ET_WEIGHT_UNDER          :
            case EnumDef::ET_WEIGHT_OVER           :
            case EnumDef::ET_WEIGHT_ETCERROR       :
            case EnumDef::ET_WEIGHT_ETC_METAL_ERROR:
                return true;
            default:
                return false;
        }
    }

    static bool isWeightTrade(quint16 eventType)
    {
        switch(eventType)
        {
            case EnumDef::ET_WEIGHT_NORMAL         :
            case EnumDef::ET_WEIGHT_UNDER_WARNING  :
            case EnumDef::ET_WEIGHT_OVER_WARNING   :
                return true;
            default: return false;
        }
    }

    static bool isTrade(quint16 eventType)
    {
        switch(eventType)
        {
            case EnumDef::ET_WEIGHT_NORMAL         :
            case EnumDef::ET_WEIGHT_UNDER_WARNING  :
            case EnumDef::ET_WEIGHT_OVER_WARNING   :
            case EnumDef::ET_METAL_TRADE           :
                return true;
            default: return false;
        }
    }

    static bool isWeightNGEvent(quint16 eventType)
    {
        switch(eventType)
        {
            case EnumDef::ET_WEIGHT_UNDER              :
            case EnumDef::ET_WEIGHT_OVER               :
            case EnumDef::ET_WEIGHT_ETCERROR           :
            case EnumDef::ET_WEIGHT_ETC_METAL_ERROR    :
                return true;
            default: return false;
        }
    }

    static bool isMetalDetectEvent(quint16 eventType)
    {
        switch(eventType)
        {
            case EnumDef::ET_METAL_DETECT: return true;
            default: return false;
        }
    }

    static bool isMDEvent(quint16 eventType)
    {
        switch(eventType)
        {
            case EnumDef::ET_METAL_TRADE:
            case EnumDef::ET_METAL_DETECT: return true;
            default: return false;
        }
    }


    static bool isWeightOrMetal(quint16 eventType)
    {
        switch(eventType)
        {
            case EnumDef::ET_WEIGHT_NORMAL         :
            case EnumDef::ET_WEIGHT_UNDER_WARNING  :
            case EnumDef::ET_WEIGHT_OVER_WARNING   :
            case EnumDef::ET_WEIGHT_UNDER          :
            case EnumDef::ET_WEIGHT_OVER           :
            case EnumDef::ET_WEIGHT_ETCERROR       :
            case EnumDef::ET_METAL_TRADE           :
            case EnumDef::ET_METAL_DETECT          :
            case EnumDef::ET_WEIGHT_ETC_METAL_ERROR:
                return true;
            default:
                return false;
        }
    }

    static bool isMetalCheckup(quint16 eventType)
    {
        return eventType == EnumDef::ET_METAL_CHECKUP;
    }

    static bool isWeightCarib(quint16 eventType)
    {
        return (eventType == EnumDef::ET_WEIGHT_STATIC_CARI || eventType == EnumDef::ET_WEIGHT_DYNAMIC_CARI);
    }

    static bool isNGEvent(quint16 eventType)
    {
        switch(eventType)
        {
            case EnumDef::ET_WEIGHT_UNDER          :
            case EnumDef::ET_WEIGHT_OVER           :
            case EnumDef::ET_WEIGHT_ETCERROR       :
            case EnumDef::ET_METAL_DETECT          :
            case EnumDef::ET_WEIGHT_ETC_METAL_ERROR:
                return true;
            default:
                return false;
        }
    }

    static bool isCheckEvent(quint16 eventType)
    {
        switch(eventType)
        {
            case EnumDef::ET_WEIGHT_NORMAL             :
            case EnumDef::ET_WEIGHT_UNDER_WARNING      :
            case EnumDef::ET_WEIGHT_OVER_WARNING       :
            case EnumDef::ET_WEIGHT_UNDER              :
            case EnumDef::ET_WEIGHT_OVER               :
            case EnumDef::ET_WEIGHT_ETCERROR           :
            case EnumDef::ET_APP_START                 :
            case EnumDef::ET_APP_EXIT                  :
            case EnumDef::ET_METAL_CHECKUP             :
            case EnumDef::ET_WEIGHT_STATIC_CARI        :
            case EnumDef::ET_WEIGHT_DYNAMIC_CARI       :
            case EnumDef::ET_RUN                       :
            case EnumDef::ET_STOP                      :
            case EnumDef::ET_METAL_TRADE               :
            case EnumDef::ET_METAL_DETECT              :
            case EnumDef::ET_WEIGHT_ETC_METAL_ERROR    :
                return false;
            default: return true;
        }
    }

    static int convertToIntEvent(QString str)
    {
        if     (str == "N"              ){return EnumDef::ET_WEIGHT_NORMAL             ;}
        else if(str == "UW"             ){return EnumDef::ET_WEIGHT_UNDER_WARNING      ;}
        else if(str == "OW"             ){return EnumDef::ET_WEIGHT_OVER_WARNING       ;}
        else if(str == "U"              ){return EnumDef::ET_WEIGHT_UNDER              ;}
        else if(str == "O"              ){return EnumDef::ET_WEIGHT_OVER               ;}
        else if(str == "ETC"            ){return EnumDef::ET_WEIGHT_ETCERROR           ;}
        else if(str == "APP START"      ){return EnumDef::ET_APP_START                 ;}
        else if(str == "APP EXIT"       ){return EnumDef::ET_APP_EXIT                  ;}
        else if(str == "M CHECK"        ){return EnumDef::ET_METAL_CHECKUP             ;}
        else if(str == "W STATIC CARI"  ){return EnumDef::ET_WEIGHT_STATIC_CARI        ;}
        else if(str == "W DINAMIC CARI" ){return EnumDef::ET_WEIGHT_DYNAMIC_CARI       ;}
        else if(str == "RUN"            ){return EnumDef::ET_RUN                       ;}
        else if(str == "STOP"           ){return EnumDef::ET_STOP                      ;}
        else if(str == "M P"            ){return EnumDef::ET_METAL_TRADE               ;}
        else if(str == "M F"            ){return EnumDef::ET_METAL_DETECT              ;}
        else if(str == "M P CHECK"      ){return EnumDef::ET_METAL_TRADE_CHECK         ;}
        else if(str == "M F CHECK"      ){return EnumDef::ET_METAL_DETECT_CHECK        ;}
        else if(str == "N CHECK"        ){return EnumDef::ET_WEIGHT_NORMAL_CHECK       ;}
        else if(str == "UW CHECK"       ){return EnumDef::ET_WEIGHT_UNDER_WARNING_CHECK;}
        else if(str == "OW CHECK"       ){return EnumDef::ET_WEIGHT_OVER_WARNING_CHECK ;}
        else if(str == "U CHECK"        ){return EnumDef::ET_WEIGHT_UNDER_CHECK        ;}
        else if(str == "O CHECK"        ){return EnumDef::ET_WEIGHT_OVER_CHECK         ;}
        else if(str == "ETC CHECK"      ){return EnumDef::ET_WEIGHT_ETCERROR_CHECK     ;}
        else if(str == "WC MD F"        ){return EnumDef::ET_WEIGHT_ETC_METAL_ERROR    ;}
        else                             {return EnumDef::ET_NONE                      ;}
    }

    static QString convertToStrEvent(int event)
    {
        switch(event)
        {
        case EnumDef::ET_WEIGHT_NORMAL             : return "N"             ;
        case EnumDef::ET_WEIGHT_UNDER_WARNING      : return "UW"            ;
        case EnumDef::ET_WEIGHT_OVER_WARNING       : return "OW"            ;
        case EnumDef::ET_WEIGHT_UNDER              : return "U"             ;
        case EnumDef::ET_WEIGHT_OVER               : return "O"             ;
        case EnumDef::ET_WEIGHT_ETCERROR           : return "ETC"           ;
        case EnumDef::ET_APP_START                 : return "APP START"     ;
        case EnumDef::ET_APP_EXIT                  : return "APP EXIT"      ;
        case EnumDef::ET_METAL_CHECKUP             : return "M CHECK"       ;
        case EnumDef::ET_WEIGHT_STATIC_CARI        : return "W STATIC CARI" ;
        case EnumDef::ET_WEIGHT_DYNAMIC_CARI       : return "W DINAMIC CARI";
        case EnumDef::ET_RUN                       : return "RUN"           ;
        case EnumDef::ET_STOP                      : return "STOP"          ;
        case EnumDef::ET_METAL_TRADE               : return "M P"           ;
        case EnumDef::ET_METAL_DETECT              : return "M F"           ;
        case EnumDef::ET_METAL_TRADE_CHECK         : return "M P CHECK"     ;
        case EnumDef::ET_METAL_DETECT_CHECK        : return "M F CHECK"     ;
        case EnumDef::ET_WEIGHT_NORMAL_CHECK       : return "N CHECK"       ;
        case EnumDef::ET_WEIGHT_UNDER_WARNING_CHECK: return "UW CHECK"      ;
        case EnumDef::ET_WEIGHT_OVER_WARNING_CHECK : return "OW CHECK"      ;
        case EnumDef::ET_WEIGHT_UNDER_CHECK        : return "U CHECK"       ;
        case EnumDef::ET_WEIGHT_OVER_CHECK         : return "O CHECK"       ;
        case EnumDef::ET_WEIGHT_ETCERROR_CHECK     : return "ETC CHECK"     ;
        case EnumDef::ET_WEIGHT_ETC_METAL_ERROR    : return "WC MD F"       ;
        default : return "NONE";
        }
    }

    EventDto(){}
    EventDto(const EventDto& copy) :
        mDateTime(copy.mDateTime),
        mDspSeq  (copy.mDspSeq  ),
        mPDSeq   (copy.mPDSeq   ),
        mPDHisIdx(copy.mPDHisIdx),
        mEType   (copy.mEType   ),
        mEValue  (copy.mEValue  ){}
    ~EventDto(){}

    EventDto& operator=(const EventDto& other)
    {
        mDateTime = other.mDateTime;
        mDspSeq   = other.mDspSeq  ;
        mPDSeq    = other.mPDSeq   ;
        mPDHisIdx = other.mPDHisIdx;
        mEType    = other.mEType   ;
        mEValue   = other.mEValue  ;

        return *this;
    }

    bool setValue(QString value)
    {
        int findFieldCnt = 0;

        QStringList fieldList = value.split(",");

        foreach(QString field ,fieldList)
        {
            if(field.contains(":") == false)
                continue;

            int splitIdx  = field.indexOf(":");
            QString key   = field.left(splitIdx);
            QString value = field.mid(splitIdx+1);

            if     (key.contains("DT"       ) ){ findFieldCnt++; mDateTime = QDateTime::fromString(value, DATE_TIME_MSEC_FMT);}
            else if(key.contains("DSP_SEQ"  ) ){ findFieldCnt++; mDspSeq   = value.toULongLong()     ;}
            else if(key.contains("PD_SEQ"   ) ){ findFieldCnt++; mPDSeq    = value.toULongLong()     ;}
            else if(key.contains("PDHIS_IDX") ){ findFieldCnt++; mPDHisIdx = value.toInt()           ;}
            else if(key.contains("EVENT"    ) ){ findFieldCnt++; mEType    = convertToIntEvent(value);}
            else if(key.contains("VALUE"    ) ){ findFieldCnt++; mEValue   = value.toUInt()          ;}
        }

        return findFieldCnt == 0 ? false : true;
    }

    QString toString(){
        return QString("DT:%1,DSP_SEQ:%2,PD_SEQ:%3,PDHIS_IDX:%4,EVENT:%5,VALUE:%6")
                .arg(mDateTime.toString(DATE_TIME_MSEC_FMT))
                .arg(mDspSeq)
                .arg(mPDSeq)
                .arg(mPDHisIdx)
                .arg(convertToStrEvent(mEType))
                .arg(mEValue);
    }

    bool isStartEvent()
    {
        if(mEType == EnumDef::ET_APP_START)
            return true;

        return false;
    }

    bool isWCEvent()
    {
        return isWCEvent(mEType);
    }

    bool isMDEvent()
    {
        return isMDEvent(mEType);
    }

    bool isNGEvent()
    {
        return isNGEvent(mEType);
    }

    bool isWCTrade()
    {
        switch(mEType)
        {
            case EnumDef::ET_WEIGHT_NORMAL         :
            case EnumDef::ET_WEIGHT_UNDER_WARNING  :
            case EnumDef::ET_WEIGHT_OVER_WARNING   :
                return true;
            default: return false;
        }
    }

    bool isWeightNGEvent()
    {
        return isWeightNGEvent(mEType);
    }

    bool isMetalDetectEvent()
    {
        return isMetalDetectEvent(mEType);
    }

    bool isCheckEvent()
    {
        return isCheckEvent(mEType);
    }

    bool isMetalCheckup()
    {
        return isMetalCheckup(mEType);
    }

    bool isWeightCarib()
    {
        return isWeightCarib(mEType);
    }

    bool isTrade()
    {
        return isTrade(mEType);
    }
};
Q_DECLARE_METATYPE(EventDto);
#endif // EVENTDTO_H
