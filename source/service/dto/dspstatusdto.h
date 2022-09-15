#ifndef DSPSTATUSDTO_H
#define DSPSTATUSDTO_H
#include <QObject>
#include "source/service/dsp/dspdatastorestruct.h"

class DspStatusDto
{
public:
    StDspCommStatus mCommStatus;
    StDspWCStatus   mWCStatus  ;
    StDspMDStatus   mMDStatus  ;

    DspStatusDto(){}
    DspStatusDto(const DspStatusDto& copy)
    {
        memcpy(&mCommStatus, &copy.mCommStatus, sizeof(StDspCommStatus));
        memcpy(&mWCStatus,   &copy.mWCStatus  , sizeof(StDspWCStatus  ));
        memcpy(&mMDStatus,   &copy.mMDStatus  , sizeof(StDspMDStatus  ));
    }
    ~DspStatusDto(){}

    DspStatusDto& operator=(const DspStatusDto& other)
    {
        memcpy(&mCommStatus, &other.mCommStatus, sizeof(StDspCommStatus));
        memcpy(&mWCStatus,   &other.mWCStatus  , sizeof(StDspWCStatus  ));
        memcpy(&mMDStatus,   &other.mMDStatus  , sizeof(StDspMDStatus  ));

        return *this;
    }

    void setValue(StDspCommStatus * pCommStatus, StDspWCStatus * pWCStatus, StDspMDStatus * pMDStatus)
    {
        memcpy(&mCommStatus, pCommStatus, sizeof(StDspCommStatus));
        memcpy(&mWCStatus  , pWCStatus  , sizeof(StDspWCStatus  ));
        memcpy(&mMDStatus  , pMDStatus  , sizeof(StDspMDStatus  ));
    }

    bool getAlarm()
    {
        if(mWCStatus.mAlarm != 0 || mMDStatus.mAlarm != 0)
            return true;

        return false;
    }

    bool getIsWCSensorAlarm()
    {
        return ((mWCStatus.mAlarm & 0x01) == 0x01);
    }
    bool getIsWCPhotoAlarm()
    {
        return ((mWCStatus.mAlarm & 0x02) == 0x02);
    }
    bool getIsWCMortorAlarm()
    {
        return ((mWCStatus.mAlarm & 0x04) == 0x04);
    }
    bool getIsWCRJMortorAlarm()
    {
        return ((mWCStatus.mAlarm & 0x08) == 0x08);
    }
    bool getIsWCMeasureAlarm()
    {
        return ((mWCStatus.mAlarm & 0x10) == 0x10);
    }
    bool getIsMDSensorAlarm()
    {
        return ((mMDStatus.mAlarm & 0x01) == 0x01);
    }
    bool getIsMDPhotoAlarm()
    {
        return ((mMDStatus.mAlarm & 0x02) == 0x02);
    }
    bool getIsMDMortorAlarm()
    {
        return ((mMDStatus.mAlarm & 0x04) == 0x04);
    }
    bool getIsMDRJMortorAlarm()
    {
        return ((mMDStatus.mAlarm & 0x08) == 0x08);
    }
    bool getIsEEPROMAlarm()
    {
        return ((mMDStatus.mAlarm & 0x10) == 0x10);
    }
};

Q_DECLARE_METATYPE(DspStatusDto);
#endif // DSPSTATUSDTO_H
