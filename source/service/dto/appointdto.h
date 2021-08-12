#ifndef APPOINTDTO_H
#define APPOINTDTO_H
#include <QObject>

class ApPointDto
{
public:
    QString mSSID    = "";
    QString mPSK     = "";
    QString mAUTH    = "";
    ApPointDto(){}
    ApPointDto(const ApPointDto& copy) :
        mSSID(copy.mSSID),
        mPSK (copy.mPSK ),
        mAUTH(copy.mAUTH){}

    ~ApPointDto(){}

    ApPointDto& operator=(const ApPointDto& other)
    {
        mSSID = other.mSSID;
        mPSK  = other.mPSK ;
        mAUTH = other.mAUTH;

        return *this;
    }
};
Q_DECLARE_METATYPE(ApPointDto);

#endif // APPOINTDTO_H
