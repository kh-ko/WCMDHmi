#ifndef ADCAUTOCALIBSETTINGDTO_H
#define ADCAUTOCALIBSETTINGDTO_H
#include <QObject>

class ADCAutoCalibSettingDto
{
public:
    bool   mIsUse   ;
    qint32 mMinADC  ;
    qint32 mMaxADC  ;

    ADCAutoCalibSettingDto(){}
    ADCAutoCalibSettingDto(const ADCAutoCalibSettingDto& copy) :
        mIsUse (copy.mIsUse ),
        mMinADC(copy.mMinADC),
        mMaxADC(copy.mMaxADC){}
    ~ADCAutoCalibSettingDto(){}

    ADCAutoCalibSettingDto& operator=(const ADCAutoCalibSettingDto& other)
    {
        mIsUse  = other.mIsUse ;
        mMinADC = other.mMinADC;
        mMaxADC = other.mMaxADC;

        return *this;
    }
};
Q_DECLARE_METATYPE(ADCAutoCalibSettingDto);
#endif // ADCAUTOCALIBSETTINGDTO_H
