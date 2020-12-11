#ifndef PDSETTINGDTO_H
#define PDSETTINGDTO_H
#include <QObject>
#include "source/service/defaultsetting/defaultsettingsprovider.h"
#include "source/service/dto/dsppdsettingdto.h"

class PDSettingDto
{
public:
    quint64 mSeq            =0;
    QString mName           ;
    DspPDSettingDto mDspForm;

    PDSettingDto(){}
    PDSettingDto(const PDSettingDto& copy) :
        mSeq    (copy.mSeq),
        mName   (copy.mName),
        mDspForm(copy.mDspForm){}
    ~PDSettingDto(){}

    PDSettingDto& operator=(const PDSettingDto& other)
    {
        mSeq     = other.mSeq;
        mName    = other.mName;
        mDspForm = other.mDspForm;

        return *this;
    }

    bool isEqualDspForm(DspPDSettingDto * pDto)
    {
        if(memcmp(&mDspForm.mCommSetting, &pDto->mCommSetting, sizeof(StDspDevCommSetting)) != 0)
            return false;

        if(memcmp(&mDspForm.mWCSetting, &pDto->mWCSetting, sizeof(StDspDevWCSetting)) != 0)
            return false;

        if(memcmp(&mDspForm.mMDSetting, &pDto->mMDSetting, sizeof(StDspDevMDSetting)) != 0)
            return false;

        return true;
    }

    void setDefaultValue()
    {
        mSeq  = 0;
        mName = "product";
        mDspForm.mCommSetting.mProductNum            = pDefaultSP->PD_SETTING_NUM           ;
        mDspForm.mCommSetting.mLength                = pDefaultSP->PD_SETTING_LEN           ;
        mDspForm.mCommSetting.mSpeed                 = pDefaultSP->PD_SETTING_SPEED         ;
        mDspForm.mCommSetting.mMotorAccelerationTime = pDefaultSP->PD_SETTING_MOTOR_ACCTIME ;
        mDspForm.mWCSetting.mNormalWeight            = pDefaultSP->PD_SETTING_NOR_WEIGHT    ;
        mDspForm.mWCSetting.mUnderWarningWeight      = pDefaultSP->PD_SETTING_UNDER_W_WEIGHT;
        mDspForm.mWCSetting.mOverWarningWeight       = pDefaultSP->PD_SETTING_OVER_W_WEIGHT ;
        mDspForm.mWCSetting.mUnderWeight             = pDefaultSP->PD_SETTING_UNDER_WEIGHT  ;
        mDspForm.mWCSetting.mOverWeight              = pDefaultSP->PD_SETTING_OVER_WEIGHT   ;
        mDspForm.mWCSetting.mTareWeight              = pDefaultSP->PD_SETTING_TARE_WEIGHT   ;
        mDspForm.mWCSetting.mNGMotion                = pDefaultSP->PD_SETTING_WC_NGMOTION   ;
        mDspForm.mWCSetting.mDynamicFactor           = pDefaultSP->PD_SETTING_DYNAMIC_FAC   ;
        mDspForm.mWCSetting.mEnableEtcError          = pDefaultSP->PD_SETTING_ENABLE_ETC_ERR;
        mDspForm.mMDSetting.mSenstivity              = pDefaultSP->PD_SETTING_MD_SENSTIVITY ;
        mDspForm.mMDSetting.mNGMotion                = pDefaultSP->PD_SETTING_MD_NGMOTION   ;
    }

    bool setValue(QString value, QString divider)
    {
        int findFieldCnt = 0;

        QStringList fieldList = value.split(divider);

        foreach(QString field ,fieldList)
        {
            if(field.contains(":") == false)
                continue;

            int splitIdx  = field.indexOf(":");
            QString key   = field.left(splitIdx);
            QString value = field.mid(splitIdx+1);

            if     (key == "Seq"                  ){ findFieldCnt++; mSeq                                         = value.toULongLong();}
            else if(key == "No"                   ){ findFieldCnt++; mDspForm.mCommSetting.mProductNum            = value.toUInt()     ;}
            else if(key == "Name"                 ){ findFieldCnt++; mName                                        = value              ;}
            else if(key == "Length"               ){ findFieldCnt++; mDspForm.mCommSetting.mLength                = value.toUInt()     ;}
            else if(key == "Speed"                ){ findFieldCnt++; mDspForm.mCommSetting.mSpeed                 = value.toUInt()     ;}
            else if(key == "MotorAccelerationTime"){ findFieldCnt++; mDspForm.mCommSetting.mMotorAccelerationTime = value.toUInt()     ;}
            else if(key == "UnderWeight"          ){ findFieldCnt++; mDspForm.mWCSetting.mUnderWeight             = value.toUInt()     ;}
            else if(key == "UnderWarningWeight"   ){ findFieldCnt++; mDspForm.mWCSetting.mUnderWarningWeight      = value.toUInt()     ;}
            else if(key == "NormalWeight"         ){ findFieldCnt++; mDspForm.mWCSetting.mNormalWeight            = value.toUInt()     ;}
            else if(key == "OverWarningWeight"    ){ findFieldCnt++; mDspForm.mWCSetting.mOverWarningWeight       = value.toUInt()     ;}
            else if(key == "OverWeight"           ){ findFieldCnt++; mDspForm.mWCSetting.mOverWeight              = value.toUInt()     ;}
            else if(key == "TareWeight"           ){ findFieldCnt++; mDspForm.mWCSetting.mTareWeight              = value.toUInt()     ;}
            else if(key == "WCNGMotion"           ){ findFieldCnt++; mDspForm.mWCSetting.mNGMotion                = value.toUInt()     ;}
            else if(key == "WCEnableEtcError"     ){ findFieldCnt++; mDspForm.mWCSetting.mEnableEtcError          = value.toUInt()     ;}
            else if(key == "DynamicFactor"        ){ findFieldCnt++; mDspForm.mWCSetting.mDynamicFactor           = value.toUInt()     ;}
            else if(key == "MDSenstivity"         ){ findFieldCnt++; mDspForm.mMDSetting.mSenstivity              = value.toUInt()     ;}
            else if(key == "MDNGMotion"           ){ findFieldCnt++; mDspForm.mMDSetting.mNGMotion                = value.toUInt()     ;}
        }

        return findFieldCnt == 0 ? false : true;
    }

    QString toString(QString divider){
        return QString("Seq:%1%2No:%3%4Name:%5%6Length:%7%8Speed:%9%10MotorAccelerationTime:%11%12UnderWeight:%13%14UnderWarningWeight:%15%16NormalWeight:%17%18OverWarningWeight:%19%20OverWeight:%21%22TareWeight:%23%24WCNGMotion:%25%26WCEnableEtcError:%27%28DynamicFactor:%29%30MDSenstivity:%31%32MDNGMotion:%33")
                .arg(mSeq                                        ).arg(divider)
                .arg(mDspForm.mCommSetting.mProductNum           ).arg(divider)
                .arg(mName                                       ).arg(divider)
                .arg(mDspForm.mCommSetting.mLength               ).arg(divider)
                .arg(mDspForm.mCommSetting.mSpeed                ).arg(divider)
                .arg(mDspForm.mCommSetting.mMotorAccelerationTime).arg(divider)
                .arg(mDspForm.mWCSetting.mUnderWeight            ).arg(divider)
                .arg(mDspForm.mWCSetting.mUnderWarningWeight     ).arg(divider)
                .arg(mDspForm.mWCSetting.mNormalWeight           ).arg(divider)
                .arg(mDspForm.mWCSetting.mOverWarningWeight      ).arg(divider)
                .arg(mDspForm.mWCSetting.mOverWeight             ).arg(divider)
                .arg(mDspForm.mWCSetting.mTareWeight             ).arg(divider)
                .arg(mDspForm.mWCSetting.mNGMotion               ).arg(divider)
                .arg(mDspForm.mWCSetting.mEnableEtcError         ).arg(divider)
                .arg(mDspForm.mWCSetting.mDynamicFactor          ).arg(divider)
                .arg(mDspForm.mMDSetting.mSenstivity             ).arg(divider)
                .arg(mDspForm.mMDSetting.mNGMotion               );
    }
};

Q_DECLARE_METATYPE(PDSettingDto);

#endif // PDSETTINGDTO_H
