#ifndef DSPDEVSETTINGDTO_H
#define DSPDEVSETTINGDTO_H
#include <QObject>
#include "source/service/dsp/dspdatastorestruct.h"

class DspDevSettingDto
{
public:
    StDspDevCommSetting mCommSetting;
    StDspDevWCSetting   mWCSetting;
    StDspDevMDSetting   mMDSetting;
    StDspDevSizeSetting mSizeSetting;

    DspDevSettingDto(){}
    DspDevSettingDto(const DspDevSettingDto& copy)
    {
        memcpy(&mCommSetting, &copy.mCommSetting, sizeof(StDspDevCommSetting));
        memcpy(&mWCSetting,   &copy.mWCSetting  , sizeof(StDspDevWCSetting  ));
        memcpy(&mMDSetting,   &copy.mMDSetting  , sizeof(StDspDevMDSetting  ));
        memcpy(&mSizeSetting, &copy.mSizeSetting, sizeof(StDspDevSizeSetting));
    }
    ~DspDevSettingDto(){}

    DspDevSettingDto& operator=(const DspDevSettingDto& other)
    {
        memcpy(&mCommSetting, &other.mCommSetting, sizeof(StDspDevCommSetting));
        memcpy(&mWCSetting,   &other.mWCSetting  , sizeof(StDspDevWCSetting  ));
        memcpy(&mMDSetting,   &other.mMDSetting  , sizeof(StDspDevMDSetting  ));
        memcpy(&mSizeSetting, &other.mSizeSetting, sizeof(StDspDevSizeSetting));

        return *this;
    }

    void setValue(StDspDevCommSetting * pCommSetting, StDspDevWCSetting * pWCSetting, StDspDevMDSetting * pMDSetting, StDspDevSizeSetting * pSizeSetting)
    {
        memcpy(&mCommSetting, pCommSetting, sizeof(StDspDevCommSetting));
        memcpy(&mWCSetting,   pWCSetting  , sizeof(StDspDevWCSetting  ));
        memcpy(&mMDSetting,   pMDSetting  , sizeof(StDspDevMDSetting  ));
        memcpy(&mSizeSetting, pSizeSetting, sizeof(StDspDevSizeSetting));
    }
};

Q_DECLARE_METATYPE(DspDevSettingDto);

#endif // DSPDEVSETTINGDTO_H
