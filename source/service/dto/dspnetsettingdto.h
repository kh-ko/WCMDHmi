#ifndef DSPNETSETTINGDTO_H
#define DSPNETSETTINGDTO_H
#include <QObject>
#include "source/service/dsp/dspdatastorestruct.h"

class DspNetSettingDto
{
public:
    StDspDevNetSetting mSetting;

    DspNetSettingDto(){}
    DspNetSettingDto(const DspNetSettingDto& copy)
    {
        memcpy(&mSetting, &copy.mSetting, sizeof(StDspDevNetSetting));
    }
    ~DspNetSettingDto(){}

    DspNetSettingDto& operator=(const DspNetSettingDto& other)
    {
        memcpy(&mSetting, &other.mSetting, sizeof(StDspDevNetSetting));

        return *this;
    }
};

Q_DECLARE_METATYPE(DspNetSettingDto);
#endif // DSPNETSETTINGDTO_H
