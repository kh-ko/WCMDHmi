#ifndef DSPPDSETTINGDTO_H
#define DSPPDSETTINGDTO_H
#include <QObject>
#include "source/service/dsp/dspdatastorestruct.h"

class DspPDSettingDto
{
public:
    StDspPDCommSetting mCommSetting;
    StDspPDWCSetting   mWCSetting;
    StDspPDMDSetting   mMDSetting;

    DspPDSettingDto()
    {
        memset(&mCommSetting, 0x00, sizeof(StDspPDCommSetting));
        memset(&mWCSetting,   0x00, sizeof(StDspPDWCSetting  ));
        memset(&mMDSetting,   0x00, sizeof(StDspPDMDSetting  ));
    }

    DspPDSettingDto(const DspPDSettingDto& copy)
    {
        memcpy(&mCommSetting, &copy.mCommSetting, sizeof(StDspPDCommSetting));
        memcpy(&mWCSetting,   &copy.mWCSetting  , sizeof(StDspPDWCSetting  ));
        memcpy(&mMDSetting,   &copy.mMDSetting  , sizeof(StDspPDMDSetting  ));
    }
    ~DspPDSettingDto(){}

    DspPDSettingDto& operator=(const DspPDSettingDto& other)
    {
        memcpy(&mCommSetting, &other.mCommSetting, sizeof(StDspPDCommSetting));
        memcpy(&mWCSetting,   &other.mWCSetting  , sizeof(StDspPDWCSetting  ));
        memcpy(&mMDSetting,   &other.mMDSetting  , sizeof(StDspPDMDSetting  ));

        return *this;
    }

    void setValue(StDspPDCommSetting * pCommSetting, StDspPDWCSetting * pWCSetting, StDspPDMDSetting * pMDSetting)
    {
        memcpy(&mCommSetting, pCommSetting, sizeof(StDspPDCommSetting));
        memcpy(&mWCSetting,   pWCSetting  , sizeof(StDspPDWCSetting  ));
        memcpy(&mMDSetting,   pMDSetting  , sizeof(StDspPDMDSetting  ));
    }
};

Q_DECLARE_METATYPE(DspPDSettingDto);
#endif // DSPPDSETTINGDTO_H
