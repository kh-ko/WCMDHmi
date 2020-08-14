#ifndef PRODUCTSTATUS_H
#define PRODUCTSTATUS_H

#include <QObject>
#include <QDebug>

#include "source/globaldef/GlobalDefine.h"
#include "source/globaldef/EnumDefine.h"
#include "source/model/devicesetting.h"
#include "source/model/productsetting.h"
#include "source/model/devicestatus.h"
#include "source/model/deviceinfo.h"
#include "source/model/Information.h"
#include "source/model/eventinfo.h"
#include "source/model/weightcheckergraphdata.h"
#include "source/model/metaldetectorgraphdata.h"

class ProductStatus : public QObject
{
    Q_OBJECT
public:
    int                       mMDTradeCnt          = 0;
    int                       mMDDetectCnt         = 0;
    //quint32                 mMDTotalCnt          = 0;

    int                     mWCUnderCnt          = 0;
    double                  mWCUnderRate         = 0;
    int                     mWCUnderWarningCnt   = 0;
    int                     mWCNormalCnt         = 0;
    int                     mWCOverWarningCnt    = 0;
    int                     mWCOverCnt           = 0;
    int                     mWCEtcErrorCnt       = 0;
    int                     mWCTotalCnt          = 0;
    int                     mWCTradeCnt          = 0;
    quint64                 mWCTradeWeight       = 0;

    quint64                 mWCCurrAvgTotalWeight =0;
    quint32                 mWCCurrAvgWeight     = 0;
    EnumDefine::EventType   mWCCurrAvgEvent      = EnumDefine::EventType::EVENT_NONE_TYPE;

    QList<quint32>          mAvgList;
    quint32                 mWCTrendsGraph[TRENDS_POINT_BUFF_CNT];
    quint32                 mWCTrendsFilterGraph[TRENDS_POINT_BUFF_CNT];

    ProductSetting          mProductSetting;

    explicit ProductStatus(ProductSetting ps, QObject *parent = nullptr): QObject(parent){mProductSetting = ps;}
    void setProductSetting(ProductSetting ps)
    {
        mProductSetting = ps;
        mAvgList.clear();
        mWCCurrAvgWeight = 0;
        mWCCurrAvgTotalWeight = 0;
        mWCCurrAvgEvent      = EnumDefine::EventType::EVENT_NONE_TYPE;

    }

    void reset(ProductSetting ps)
    {
        mMDTradeCnt          = 0;
        mMDDetectCnt         = 0;

        mWCUnderCnt          = 0;
        mWCUnderRate         = 0;
        mWCUnderWarningCnt   = 0;
        mWCNormalCnt         = 0;
        mWCOverWarningCnt    = 0;
        mWCOverCnt           = 0;
        mWCEtcErrorCnt       = 0;
        mWCTotalCnt          = 0;
        mWCTradeCnt          = 0;
        mWCTradeWeight       = 0;

        mAvgList.clear();
        mWCCurrAvgWeight     = 0;
        mWCCurrAvgTotalWeight= 0;
        mWCCurrAvgEvent      = EnumDefine::EventType::EVENT_NONE_TYPE;

        mProductSetting = ps;
    }

    void resetStatistics()
    {
        mMDTradeCnt          = 0;
        mMDDetectCnt         = 0;

        mWCUnderCnt          = 0;
        mWCUnderRate         = 0;
        mWCUnderWarningCnt   = 0;
        mWCNormalCnt         = 0;
        mWCOverWarningCnt    = 0;
        mWCOverCnt           = 0;
        mWCEtcErrorCnt       = 0;
        mWCTotalCnt          = 0;
        mWCTradeCnt          = 0;
        mWCTradeWeight       = 0;

        mAvgList.clear();
        mWCCurrAvgWeight     = 0;
        mWCCurrAvgTotalWeight= 0;
        mWCCurrAvgEvent      = EnumDefine::EventType::EVENT_NONE_TYPE;
    }

    ~ProductStatus(){}
    void addEvent(EventInfo value)
    {
        switch(value.mEventType)
        {
            case EnumDefine::EventType::WEIGHT_UNDER_TYPE:
                mWCUnderCnt++;
                mWCTrendsGraph[mWCTotalCnt++] = value.mEventValue;
                mWCUnderRate        = (float)(mWCUnderCnt * 100)/(float)mWCTotalCnt;
            break;

            case EnumDefine::EventType::WEIGHT_UNDER_WARNING_TYPE:
                mWCUnderWarningCnt++;
                mWCTrendsGraph[mWCTotalCnt++] = value.mEventValue;
                mWCTrendsFilterGraph[mWCTradeCnt++] = value.mEventValue;
                mWCTradeWeight = mWCTradeWeight + value.mEventValue;
            break;

            case EnumDefine::EventType::WEIGHT_NORMAL_TYPE:
                mWCNormalCnt++;
                mWCTrendsGraph[mWCTotalCnt++] = value.mEventValue;
                mWCTrendsFilterGraph[mWCTradeCnt++] = value.mEventValue;
                mWCTradeWeight = mWCTradeWeight + value.mEventValue;
            break;

            case EnumDefine::EventType::WEIGHT_OVER_WARNING_TYPE:
                mWCOverWarningCnt++;
                mWCTrendsGraph[mWCTotalCnt++] = value.mEventValue;
                mWCTrendsFilterGraph[mWCTradeCnt++] = value.mEventValue;
                mWCTradeWeight = mWCTradeWeight + value.mEventValue;
            break;

            case EnumDefine::EventType::WEIGHT_OVER_TYPE:
                mWCOverCnt++;
                mWCTrendsGraph[mWCTotalCnt++] = value.mEventValue;
            break;

            case EnumDefine::EventType::WEIGHT_ETCERROR_TYPE:
            case EnumDefine::EventType::WEIGHT_ETC_METAL_ERROR_TYPE:
                mWCEtcErrorCnt++;
                mWCTrendsGraph[mWCTotalCnt++] = value.mEventValue;
            break;

            case EnumDefine::EventType::METAL_DETECT_TYPE:
                mMDDetectCnt++;
            return;

            case EnumDefine::EventType::METAL_TRADE_TYPE:
                mMDTradeCnt++;
            return;

            default:
            return;
        }

        qDebug() << "product event cnt : "  << mWCTotalCnt;
        //qDebug() << "AvgWeight =[start]=:";

        mAvgList.append(value.mEventValue);

        mWCCurrAvgTotalWeight = mWCCurrAvgTotalWeight + value.mEventValue;

        if(mAvgList.size() > mProductSetting.mAverageN)
        {
            mWCCurrAvgTotalWeight = mWCCurrAvgTotalWeight - mAvgList.at(0);
            mAvgList.removeAt(0);
        }

        mWCCurrAvgWeight = mWCCurrAvgTotalWeight / mAvgList.size();


        if(mWCCurrAvgWeight < mProductSetting.mUnderWeight)
        {
            mWCCurrAvgEvent = EnumDefine::EventType::WEIGHT_UNDER_TYPE;
        }
        else if(mWCCurrAvgWeight < mProductSetting.mUnderWarningWeight)
        {
            mWCCurrAvgEvent = EnumDefine::EventType::WEIGHT_UNDER_WARNING_TYPE;
        }
        else if(mWCCurrAvgWeight > mProductSetting.mOverWeight)
        {
            mWCCurrAvgEvent = EnumDefine::EventType::WEIGHT_OVER_TYPE;
        }
        else if(mWCCurrAvgWeight > mProductSetting.mOverWarningWeight)
        {
            mWCCurrAvgEvent = EnumDefine::EventType::WEIGHT_OVER_WARNING_TYPE;
        }
        else
        {
            mWCCurrAvgEvent = EnumDefine::EventType::WEIGHT_NORMAL_TYPE;
        }
    }
};

#endif // PRODUCTSTATUS_H
