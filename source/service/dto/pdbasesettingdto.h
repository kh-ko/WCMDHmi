#ifndef PDBASESETTINGDTO_H
#define PDBASESETTINGDTO_H

#include <QObject>

class PdBaseSettingDto
{
public:
    quint32 mMeasureCueSign   ;
    quint16 mFilterCoefficient;
    quint32 mMeasureSection   ;

    PdBaseSettingDto(){}
    PdBaseSettingDto(const PdBaseSettingDto& copy) :
        mMeasureCueSign   (copy.mMeasureCueSign   ),
        mFilterCoefficient(copy.mFilterCoefficient),
        mMeasureSection   (copy.mMeasureSection   ){}
    ~PdBaseSettingDto(){}

    PdBaseSettingDto& operator=(const PdBaseSettingDto& other)
    {
        mMeasureCueSign    = other.mMeasureCueSign   ;
        mFilterCoefficient = other.mFilterCoefficient;
        mMeasureSection    = other.mMeasureSection   ;

        return *this;
    }
};
Q_DECLARE_METATYPE(PdBaseSettingDto);

#endif // PDBASESETTINGDTO_H
