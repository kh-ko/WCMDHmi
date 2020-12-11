#ifndef TRENDSITEMDTO_H
#define TRENDSITEMDTO_H

#include <QObject>

class TrendsItemDto
{
public:
    quint64 mPDSeq;
    bool    mIsTrade;
    quint32 mValue;

    TrendsItemDto(){}
    TrendsItemDto(const TrendsItemDto& copy) :
        mPDSeq  (copy.mPDSeq  ),
        mIsTrade(copy.mIsTrade),
        mValue  (copy.mValue  ){}
    ~TrendsItemDto(){}

    TrendsItemDto& operator=(const TrendsItemDto& other)
    {

        mPDSeq   = other.mPDSeq  ;
        mIsTrade = other.mIsTrade;
        mValue   = other.mValue  ;

        return *this;
    }

};

Q_DECLARE_METATYPE(TrendsItemDto);
#endif // TRENDSITEMDTO_H
