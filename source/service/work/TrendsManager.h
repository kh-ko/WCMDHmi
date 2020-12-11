#ifndef TRENDSMANAGER_H
#define TRENDSMANAGER_H

#include <QObject>
#include <QDateTime>
#include <QApplication>
#include "source/service/util/exceptionutil.h"
#include "source/service/includesvcdto.h"

#define WCTR_LIMIT 1000000
#define MDTR_LIMIT 24

class TrendsManager : public QObject
{
    Q_OBJECT

public:
    int mWCTrendsCnt = 0;

    TrendsItemDto mWCTrends[WCTR_LIMIT];
    QList<TrendsItemDto> mMDTrends;


    explicit TrendsManager(QObject * parent = nullptr):QObject(parent)
    {
    }
    ~TrendsManager()
    {
    }

    void addWCTrends(EventDto dto)
    {
        CHECK_FALSE_RETURN(dto.isWCEvent())

        if(mWCTrendsCnt > WCTR_LIMIT - 1)
        {
            mWCTrendsCnt = 0;
        }

        mWCTrends[mWCTrendsCnt].mPDSeq   = dto.mPDSeq     ;
        mWCTrends[mWCTrendsCnt].mIsTrade = dto.isWCTrade();
        mWCTrends[mWCTrendsCnt].mValue   = dto.mEValue    ;

        mWCTrendsCnt ++;
    }

    void addMDTrends(EventDto dto)
    {
        CHECK_FALSE_RETURN(dto.isMDEvent())

        if(mMDTrends.size() > MDTR_LIMIT - 1)
        {
            mMDTrends.removeAt(0);
        }

        TrendsItemDto item;
        item.mPDSeq = dto.mPDSeq;
        item.mIsTrade = !dto.isMetalDetectEvent();
        item.mValue = dto.mEValue;

        mMDTrends.append(item);
    }

    void clear()
    {
        clearMDTrends();
        clearWCTrends();
    }
    void clearMDTrends()
    {
        mMDTrends.clear();
    }

    void clearWCTrends()
    {
        mWCTrendsCnt = 0;
    }
};
#endif // TRENDSMANAGER_H
