#ifndef DEVSETTINGDTO_H
#define DEVSETTINGDTO_H
#include <QObject>
#include "source/service/dto/dspdevsettingdto.h"

class DevSettingDto
{
public:
    DspDevSettingDto mDspForm;

    DevSettingDto(){}
    DevSettingDto(const DevSettingDto& copy) : mDspForm(copy.mDspForm){}
    ~DevSettingDto(){}

    DevSettingDto& operator=(const DevSettingDto& other)
    {
        mDspForm = other.mDspForm;

        return *this;
    }

    bool isEqualDspForm(DspDevSettingDto * pDto)
    {
        if(memcmp(&mDspForm.mCommSetting, &pDto->mCommSetting, sizeof(StDspDevCommSetting)) != 0)
            return false;

        if(memcmp(&mDspForm.mWCSetting, &pDto->mWCSetting, sizeof(StDspDevWCSetting)) != 0)
            return false;

        if(memcmp(&mDspForm.mMDSetting, &pDto->mMDSetting, sizeof(StDspDevMDSetting)) != 0)
            return false;

        if(memcmp(&mDspForm.mSizeSetting, &pDto->mSizeSetting, sizeof(StDspDevSizeSetting)) != 0)
            return false;

        return true;
    }
};

Q_DECLARE_METATYPE(DevSettingDto);
#endif // DEVSETTINGDTO_H
