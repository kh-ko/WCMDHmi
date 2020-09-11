#ifndef EVENTMODEL_H
#define EVENTMODEL_H

#include <QObject>
#include <QDateTime>
#include "source/globaldef/EnumDefine.h"

class EventModel : public QObject
{
    Q_OBJECT

public:
    QString mDateTime;
    quint64 mDspSeq;
    quint64 mProductSettingSeq;
    int     mProductTodayHisIdx;
    quint16 mEventType;
    quint32 mValue;

    quint16 convertToIntEvent(QString str)
    {
        if     (str == "N"              ){return EnumDefine::EventType::WEIGHT_NORMAL_TYPE             ;}
        else if(str == "UW"             ){return EnumDefine::EventType::WEIGHT_UNDER_WARNING_TYPE      ;}
        else if(str == "OW"             ){return EnumDefine::EventType::WEIGHT_OVER_WARNING_TYPE       ;}
        else if(str == "U"              ){return EnumDefine::EventType::WEIGHT_UNDER_TYPE              ;}
        else if(str == "O"              ){return EnumDefine::EventType::WEIGHT_OVER_TYPE               ;}
        else if(str == "ETC"            ){return EnumDefine::EventType::WEIGHT_ETCERROR_TYPE           ;}
        else if(str == "APP START"      ){return EnumDefine::EventType::APP_START_TYPE                 ;}
        else if(str == "APP EXIT"       ){return EnumDefine::EventType::APP_EXIT_TYPE                  ;}
        else if(str == "M CHECK"        ){return EnumDefine::EventType::METAL_CHECKUP_TYPE             ;}
        else if(str == "W STATIC CARI"  ){return EnumDefine::EventType::WEIGHT_STATIC_CARI_TYPE        ;}
        else if(str == "W DINAMIC CARI" ){return EnumDefine::EventType::WEIGHT_DYNAMIC_CARI_TYPE       ;}
        else if(str == "RUN"            ){return EnumDefine::EventType::RUN_TYPE                       ;}
        else if(str == "STOP"           ){return EnumDefine::EventType::STOP_TYPE                      ;}
        else if(str == "M P"            ){return EnumDefine::EventType::METAL_TRADE_TYPE               ;}
        else if(str == "M F"            ){return EnumDefine::EventType::METAL_DETECT_TYPE              ;}
        else if(str == "M P CHECK"      ){return EnumDefine::EventType::METAL_TRADE_CHECK_TYPE         ;}
        else if(str == "M F CHECK"      ){return EnumDefine::EventType::METAL_DETECT_CHECK_TYPE        ;}
        else if(str == "N CHECK"        ){return EnumDefine::EventType::WEIGHT_NORMAL_CHECK_TYPE       ;}
        else if(str == "UW CHECK"       ){return EnumDefine::EventType::WEIGHT_UNDER_WARNING_CHECK_TYPE;}
        else if(str == "OW CHECK"       ){return EnumDefine::EventType::WEIGHT_OVER_WARNING_CHECK_TYPE ;}
        else if(str == "U CHECK"        ){return EnumDefine::EventType::WEIGHT_UNDER_CHECK_TYPE        ;}
        else if(str == "O CHECK"        ){return EnumDefine::EventType::WEIGHT_OVER_CHECK_TYPE         ;}
        else if(str == "ETC CHECK"      ){return EnumDefine::EventType::WEIGHT_ETCERROR_CHECK_TYPE     ;}
        else if(str == "WC MD F"        ){return EnumDefine::EventType::WEIGHT_ETC_METAL_ERROR_TYPE    ;}

        return EnumDefine::EventType::EVENT_NONE_TYPE;
    }

    QString convertToStrEvent(int event)
    {
        switch(event)
        {
        case EnumDefine::EventType::WEIGHT_NORMAL_TYPE             : return "N"             ;
        case EnumDefine::EventType::WEIGHT_UNDER_WARNING_TYPE      : return "UW"            ;
        case EnumDefine::EventType::WEIGHT_OVER_WARNING_TYPE       : return "OW"            ;
        case EnumDefine::EventType::WEIGHT_UNDER_TYPE              : return "U"             ;
        case EnumDefine::EventType::WEIGHT_OVER_TYPE               : return "O"             ;
        case EnumDefine::EventType::WEIGHT_ETCERROR_TYPE           : return "ETC"           ;
        case EnumDefine::EventType::APP_START_TYPE                 : return "APP START"     ;
        case EnumDefine::EventType::APP_EXIT_TYPE                  : return "APP EXIT"      ;
        case EnumDefine::EventType::METAL_CHECKUP_TYPE             : return "M CHECK"       ;
        case EnumDefine::EventType::WEIGHT_STATIC_CARI_TYPE        : return "W STATIC CARI" ;
        case EnumDefine::EventType::WEIGHT_DYNAMIC_CARI_TYPE       : return "W DINAMIC CARI";
        case EnumDefine::EventType::RUN_TYPE                       : return "RUN"           ;
        case EnumDefine::EventType::STOP_TYPE                      : return "STOP"          ;
        case EnumDefine::EventType::METAL_TRADE_TYPE               : return "M P"           ;
        case EnumDefine::EventType::METAL_DETECT_TYPE              : return "M F"           ;
        case EnumDefine::EventType::METAL_TRADE_CHECK_TYPE         : return "M P CHECK"     ;
        case EnumDefine::EventType::METAL_DETECT_CHECK_TYPE        : return "M F CHECK"     ;
        case EnumDefine::EventType::WEIGHT_NORMAL_CHECK_TYPE       : return "N CHECK"       ;
        case EnumDefine::EventType::WEIGHT_UNDER_WARNING_CHECK_TYPE: return "UW CHECK"      ;
        case EnumDefine::EventType::WEIGHT_OVER_WARNING_CHECK_TYPE : return "OW CHECK"      ;
        case EnumDefine::EventType::WEIGHT_UNDER_CHECK_TYPE        : return "U CHECK"       ;
        case EnumDefine::EventType::WEIGHT_OVER_CHECK_TYPE         : return "O CHECK"       ;
        case EnumDefine::EventType::WEIGHT_ETCERROR_CHECK_TYPE     : return "ETC CHECK"     ;
        case EnumDefine::EventType::WEIGHT_ETC_METAL_ERROR_TYPE    : return "WC MD F"       ;
        default : return "NONE";
        }
    }

    void setStringValue(QString value)
    {
        QStringList listRow = value.split(",");

        for(int i = 0; i < listRow.size(); i++)
        {
            QString row = listRow.at(i);

            if(row.contains(":") == false)
                continue;

            QString key = row.split(":")[0];
            QString value = row.split(":")[1];

            if     (key == "DT"        ){ mDateTime             = value                   ;}
            else if(key == "DSP_SEQ"   ){ mDspSeq               = value.toULongLong()     ;}
            else if(key == "PD_SEQ"    ){ mProductSettingSeq    = value.toULongLong()     ;}
            else if(key == "PDHIS_IDX" ){ mProductTodayHisIdx   = value.toInt()           ;}
            else if(key == "EVENT"     ){ mEventType            = convertToIntEvent(value);}
            else if(key == "VALUE"     ){ mValue                = value.toUInt()          ;}
        }
    }

    QString toString(){
        return QString("DT:%1,DSP_SEQ:%2,PD_SEQ:%3,PDHIS_IDX:%4,EVENT:%5,VALUE:%6")
                .arg(mDateTime)
                .arg(mDspSeq)
                .arg(mProductSettingSeq)
                .arg(mProductTodayHisIdx)
                .arg(convertToStrEvent(mEventType))
                .arg(mValue);
    }

public:
    void createEvent(quint64 dspSeq, quint64 productSettingSeq, int productTodayHisIdx, quint16 eventType, quint32 value)
    {
        mDateTime = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss.zzz");
        mDspSeq = dspSeq;
        mProductSettingSeq = productSettingSeq;
        mProductTodayHisIdx = productTodayHisIdx;
        mEventType = eventType;
        mValue = value;
    }
    explicit EventModel(QObject *parent = nullptr) : QObject(parent){}
};


#endif // EVENTMODEL_H
