#ifndef INFORMATIONDTO_H
#define INFORMATIONDTO_H

#include <QObject>

class InformationDto
{
public:
    QString mCompany      = "";
    QString mTel          = "";
    QString mModel        = "";
    QString mSN           = "";
    int     mDeviceNumber = 0 ;
    QString mHMIVersion   = "";
    QString mPower        = "";
    QString mHomepage     = "";
    quint32 mMaxWeight    = 0 ;

    InformationDto(){}
    InformationDto(const InformationDto& copy) :
        mCompany     (copy.mCompany     ),
        mTel         (copy.mTel         ),
        mModel       (copy.mModel       ),
        mSN          (copy.mSN          ),
        mDeviceNumber(copy.mDeviceNumber),
        mHMIVersion  (copy.mHMIVersion  ),
        mPower       (copy.mPower       ),
        mHomepage    (copy.mHomepage    ),
        mMaxWeight   (copy.mMaxWeight   ){}
    ~InformationDto(){}

    InformationDto& operator=(const InformationDto& other)
    {
        mCompany      = other.mCompany     ;
        mTel          = other.mTel         ;
        mModel        = other.mModel       ;
        mSN           = other.mSN          ;
        mDeviceNumber = other.mDeviceNumber;
        mHMIVersion   = other.mHMIVersion  ;
        mPower        = other.mPower       ;
        mHomepage     = other.mHomepage    ;
        mMaxWeight    = other.mMaxWeight   ;

        return *this;
    }
};
Q_DECLARE_METATYPE(InformationDto);
#endif // INFORMATIONDTO_H
