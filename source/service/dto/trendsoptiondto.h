#ifndef TRENDSOPTIONDTO_H
#define TRENDSOPTIONDTO_H

#include <QObject>
class TrendsOptionDto
{
public:
    int  mTrendsOptionH           = 0;
    int  mTrendsOptionFilter      = 0;
    int  mTrendsOptionLastN       = 0;;
    int  mTrendsLastNValue        = 100;

    TrendsOptionDto(){}
    TrendsOptionDto(const TrendsOptionDto& copy) :
        mTrendsOptionH     (copy.mTrendsOptionH     ),
        mTrendsOptionFilter(copy.mTrendsOptionFilter),
        mTrendsOptionLastN (copy.mTrendsOptionLastN ),
        mTrendsLastNValue  (copy.mTrendsLastNValue  ){}

    ~TrendsOptionDto(){}

    TrendsOptionDto& operator=(const TrendsOptionDto& other)
    {
        mTrendsOptionH      = other.mTrendsOptionH     ;
        mTrendsOptionFilter = other.mTrendsOptionFilter;
        mTrendsOptionLastN  = other.mTrendsOptionLastN ;
        mTrendsLastNValue   = other.mTrendsLastNValue  ;

        return *this;
    }
};
Q_DECLARE_METATYPE(TrendsOptionDto);
#endif // TRENDSOPTIONDTO_H
