#ifndef PRODUCTSTATUSMODEL_H
#define PRODUCTSTATUSMODEL_H

#include <QObject>
#include "source/globaldef/EnumDefine.h"
class ProductStatusModel : public QObject
{
    Q_OBJECT

public:
    quint64  mProductSettingSeq  = 0;
    int      mMDTotalCnt         = 0;
    int      mMDDetectCnt        = 0;
    int      mWCTotalCnt         = 0;
    int      mWCNGCnt            = 0;
    int      mWCTradeCnt         = 0;
    int      mWCOverCnt          = 0;
    int      mWCOverWarningCnt   = 0;
    int      mWCNormalCnt        = 0;
    int      mWCUnderWarningCnt  = 0;
    int      mWCUnderCnt         = 0;
    int      mWCEtcErrorCnt      = 0;
    quint64  mWCTradeTotalWeight = 0;

    void setProductSettingSeq (quint64 value){ if(mProductSettingSeq  == value) return; mProductSettingSeq  = value; emit signalEventChangedProductSettingSeq (mProductSettingSeq );}
    void setMDTotalCnt        (int     value){ if(mMDTotalCnt         == value) return; mMDTotalCnt         = value; emit signalEventChangedMDTotalCnt        (mMDTotalCnt        );}
    void setMDDetectCnt       (int     value){ if(mMDDetectCnt        == value) return; mMDDetectCnt        = value; emit signalEventChangedMDDetectCnt       (mMDDetectCnt       );}
    void setWCTotalCnt        (int     value){ if(mWCTotalCnt         == value) return; mWCTotalCnt         = value; emit signalEventChangedWCTotalCnt        (mWCTotalCnt        );}
    void setWCNGCnt           (int     value){ if(mWCNGCnt            == value) return; mWCNGCnt            = value; emit signalEventChangedWCNGCnt           (mWCNGCnt           );}
    void setWCTradeCnt        (int     value){ if(mWCTradeCnt         == value) return; mWCTradeCnt         = value; emit signalEventChangedWCTradeCnt        (mWCTradeCnt        );}
    void setWCOverCnt         (int     value){ if(mWCOverCnt          == value) return; mWCOverCnt          = value; emit signalEventChangedWCOverCnt         (mWCOverCnt         );}
    void setWCOverWarningCnt  (int     value){ if(mWCOverWarningCnt   == value) return; mWCOverWarningCnt   = value; emit signalEventChangedWCOverWarningCnt  (mWCOverWarningCnt  );}
    void setWCNormalCnt       (int     value){ if(mWCNormalCnt        == value) return; mWCNormalCnt        = value; emit signalEventChangedWCNormalCnt       (mWCNormalCnt       );}
    void setWCUnderWarningCnt (int     value){ if(mWCUnderWarningCnt  == value) return; mWCUnderWarningCnt  = value; emit signalEventChangedWCUnderWarningCnt (mWCUnderWarningCnt );}
    void setWCUnderCnt        (int     value){ if(mWCUnderCnt         == value) return; mWCUnderCnt         = value; emit signalEventChangedWCUnderCnt        (mWCUnderCnt        );}
    void setWCEtcErrorCnt     (int     value){ if(mWCEtcErrorCnt      == value) return; mWCEtcErrorCnt      = value; emit signalEventChangedWCEtcErrorCnt     (mWCEtcErrorCnt     );}
    void setWCTradeTotalWeight(quint64 value){ if(mWCTradeTotalWeight == value) return; mWCTradeTotalWeight = value; emit signalEventChangedWCTradeTotalWeight(mWCTradeTotalWeight);}

signals:
    void signalEventChangedProductSettingSeq (quint64 value);
    void signalEventChangedMDTotalCnt        (int     value);
    void signalEventChangedMDDetectCnt       (int     value);
    void signalEventChangedWCTotalCnt        (int     value);
    void signalEventChangedWCNGCnt           (int     value);
    void signalEventChangedWCTradeCnt        (int     value);
    void signalEventChangedWCOverCnt         (int     value);
    void signalEventChangedWCOverWarningCnt  (int     value);
    void signalEventChangedWCNormalCnt       (int     value);
    void signalEventChangedWCUnderWarningCnt (int     value);
    void signalEventChangedWCUnderCnt        (int     value);
    void signalEventChangedWCEtcErrorCnt     (int     value);
    void signalEventChangedWCTradeTotalWeight(quint64 value);

public:
    ProductStatusModel& operator=(const ProductStatusModel& other)
    {
        setProductSettingSeq  (other.mProductSettingSeq );
        setMDTotalCnt         (other.mMDTotalCnt        );
        setMDDetectCnt        (other.mMDDetectCnt       );
        setWCTotalCnt         (other.mWCTotalCnt        );
        setWCNGCnt            (other.mWCNGCnt           );
        setWCTradeCnt         (other.mWCTradeCnt        );
        setWCOverCnt          (other.mWCOverCnt         );
        setWCOverWarningCnt   (other.mWCOverWarningCnt  );
        setWCNormalCnt        (other.mWCNormalCnt       );
        setWCUnderWarningCnt  (other.mWCUnderWarningCnt );
        setWCUnderCnt         (other.mWCUnderCnt        );
        setWCEtcErrorCnt      (other.mWCEtcErrorCnt     );
        setWCTradeTotalWeight (other.mWCTradeTotalWeight);

        return *this;
    }

    void addEvent(quint16 eventType, quint32 value)
    {
        switch(eventType)
        {
            case EnumDefine::EventType::WEIGHT_NORMAL_TYPE         :setWCTotalCnt(mWCTotalCnt + 1); setWCTradeCnt(mWCTradeCnt + 1); setWCNormalCnt      (mWCNormalCnt       + 1); setWCTradeTotalWeight(mWCTradeTotalWeight + (quint64)value); break;
            case EnumDefine::EventType::WEIGHT_UNDER_WARNING_TYPE  :setWCTotalCnt(mWCTotalCnt + 1); setWCTradeCnt(mWCTradeCnt + 1); setWCUnderWarningCnt(mWCUnderWarningCnt + 1); setWCTradeTotalWeight(mWCTradeTotalWeight + (quint64)value); break;
            case EnumDefine::EventType::WEIGHT_OVER_WARNING_TYPE   :setWCTotalCnt(mWCTotalCnt + 1); setWCTradeCnt(mWCTradeCnt + 1); setWCOverWarningCnt (mWCOverWarningCnt  + 1); setWCTradeTotalWeight(mWCTradeTotalWeight + (quint64)value); break;
            case EnumDefine::EventType::WEIGHT_UNDER_TYPE          :setWCTotalCnt(mWCTotalCnt + 1); setWCNGCnt   (mWCNGCnt    + 1); setWCUnderCnt       (mWCUnderCnt        + 1); break;
            case EnumDefine::EventType::WEIGHT_OVER_TYPE           :setWCTotalCnt(mWCTotalCnt + 1); setWCNGCnt   (mWCNGCnt    + 1); setWCOverCnt        (mWCOverCnt         + 1); break;
            case EnumDefine::EventType::WEIGHT_ETCERROR_TYPE       :setWCTotalCnt(mWCTotalCnt + 1); setWCNGCnt   (mWCNGCnt    + 1); setWCEtcErrorCnt    (mWCEtcErrorCnt     + 1); break;
            case EnumDefine::EventType::WEIGHT_ETC_METAL_ERROR_TYPE:setWCTotalCnt(mWCTotalCnt + 1); setWCNGCnt   (mWCNGCnt    + 1); setWCEtcErrorCnt    (mWCEtcErrorCnt     + 1); break;
            case EnumDefine::EventType::METAL_DETECT_TYPE          :setMDDetectCnt(mMDDetectCnt + 1);break;
        }
    }

    void reset()
    {
        setMDTotalCnt         (0);
        setMDDetectCnt        (0);
        setWCTotalCnt         (0);
        setWCNGCnt            (0);
        setWCTradeCnt         (0);
        setWCOverCnt          (0);
        setWCOverWarningCnt   (0);
        setWCNormalCnt        (0);
        setWCUnderWarningCnt  (0);
        setWCUnderCnt         (0);
        setWCEtcErrorCnt      (0);
        setWCTradeTotalWeight (0);
    }
    explicit ProductStatusModel(QObject *parent = nullptr) : QObject(parent){}
};

#endif // PRODUCTSTATUSMODEL_H
