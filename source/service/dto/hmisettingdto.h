#ifndef HMISETTINGDTO_H
#define HMISETTINGDTO_H

#include <QObject>

class HMISettingDto
{
public:
    bool    mSWPowerOff         = false;
    bool    mIsDayMode          = false;
    bool    mIsDebugMode        = false;
    //quint32 mDynamicFactor      = 10000000;
    quint16 mSimpleSenstivity01 = 0;
    quint16 mSimpleSenstivity02 = 0;
    quint16 mSimpleSenstivity03 = 0;
    quint16 mSimpleSenstivity04 = 0;
    quint16 mSimpleSenstivity05 = 0;

    HMISettingDto(){}
    HMISettingDto(const HMISettingDto& copy) :
        mSWPowerOff        (copy.mSWPowerOff        ),
        mIsDayMode         (copy.mIsDayMode         ),
        mIsDebugMode       (copy.mIsDebugMode       ),
        //mDynamicFactor     (copy.mDynamicFactor     ),
        mSimpleSenstivity01(copy.mSimpleSenstivity01),
        mSimpleSenstivity02(copy.mSimpleSenstivity02),
        mSimpleSenstivity03(copy.mSimpleSenstivity03),
        mSimpleSenstivity04(copy.mSimpleSenstivity04),
        mSimpleSenstivity05(copy.mSimpleSenstivity05){}
    ~HMISettingDto(){}

    HMISettingDto& operator=(const HMISettingDto& other)
    {
        mSWPowerOff         = other.mSWPowerOff        ;
        mIsDayMode          = other.mIsDayMode         ;
        mIsDebugMode        = other.mIsDebugMode       ;
        //mDynamicFactor      = other.mDynamicFactor     ;
        mSimpleSenstivity01 = other.mSimpleSenstivity01;
        mSimpleSenstivity02 = other.mSimpleSenstivity02;
        mSimpleSenstivity03 = other.mSimpleSenstivity03;
        mSimpleSenstivity04 = other.mSimpleSenstivity04;
        mSimpleSenstivity05 = other.mSimpleSenstivity05;

        return *this;
    }
};
Q_DECLARE_METATYPE(HMISettingDto);
#endif // HMISETTINGDTO_H
