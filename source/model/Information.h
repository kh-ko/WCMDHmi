#ifndef INFORMATION_H
#define INFORMATION_H

#include <QObject>

#include "source/globaldef/EnumDefine.h"

class Information //: //public QObject
{
    //Q_OBJECT
public:
    QString mCompany     ;
    QString mTel         ;
    QString mModel       ;
    QString mSN          ;
    int     mDeviceNumber;
    QString mDspVersion  ;
    QString mHMIVersion  ;
    QString mPower       ;
    QString mHomepage    ;
    int     mMaxWeight   ;
    QString mServerIp    ;

    Information(){}
    //explicit Information(QObject *parent = nullptr): QObject(parent){}
    Information(const Information& copy):
                         mCompany      (copy.mCompany      ),
                         mTel          (copy.mTel          ),
                         mModel        (copy.mModel        ),
                         mSN           (copy.mSN           ),
                         mDeviceNumber (copy.mDeviceNumber ),
                         mDspVersion   (copy.mDspVersion   ),
                         mHMIVersion   (copy.mHMIVersion   ),
                         mPower        (copy.mPower        ),
                         mHomepage     (copy.mHomepage     ),
                         mMaxWeight    (copy.mMaxWeight    ),
                         mServerIp     (copy.mServerIp     ){}

    ~Information(){}

    Information& operator=(const Information& other)
    {
        mCompany      = other.mCompany     ;
        mTel          = other.mTel         ;
        mModel        = other.mModel       ;
        mSN           = other.mSN          ;
        mDeviceNumber = other.mDeviceNumber;
        mDspVersion   = other.mDspVersion  ;
        mHMIVersion   = other.mHMIVersion  ;
        mPower        = other.mPower       ;
        mHomepage     = other.mHomepage    ;
        mMaxWeight    = other.mMaxWeight   ;
        mServerIp     = other.mServerIp    ;

        return *this;
    }
};

Q_DECLARE_METATYPE(Information);
#endif // INFORMATION_H
