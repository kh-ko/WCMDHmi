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

    PDSettingDto(){ setDefaultValue(); }
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
        mDspForm.mCommSetting.mProductNum            = pDefaultSP->PD_SETTING_NUM                       ;
        mDspForm.mCommSetting.mLength                = pDefaultSP->PD_SETTING_LEN                       ;
        mDspForm.mCommSetting.mSpeed                 = pDefaultSP->PD_SETTING_SPEED                     ;
        mDspForm.mCommSetting.mMotorAccelerationTime = pDefaultSP->PD_SETTING_MOTOR_ACCTIME             ;
        mDspForm.mCommSetting.mMotorDecelerationTime = pDefaultSP->PD_SETTING_MOTOR_DECTIME             ;
        mDspForm.mCommSetting.mGroupCount            = pDefaultSP->PD_SETTING_GROUP_COUNT               ;
        mDspForm.mCommSetting.mGroupMotion           = pDefaultSP->PD_SETTING_GROUP_MOTION              ;
        mDspForm.mCommSetting.mGroupLamp             = pDefaultSP->PD_SETTING_GROUP_LAMP                ;
        mDspForm.mCommSetting.mGroupBuzzer           = pDefaultSP->PD_SETTING_GROUP_BUZZER              ;
        mDspForm.mWCSetting.mNormalWeight            = pDefaultSP->PD_SETTING_NOR_WEIGHT                ;
        mDspForm.mWCSetting.mUnderWarningWeight      = pDefaultSP->PD_SETTING_UNDER_W_WEIGHT            ;
        mDspForm.mWCSetting.mOverWarningWeight       = pDefaultSP->PD_SETTING_OVER_W_WEIGHT             ;
        mDspForm.mWCSetting.mUnderWeight             = pDefaultSP->PD_SETTING_UNDER_WEIGHT              ;
        mDspForm.mWCSetting.mOverWeight              = pDefaultSP->PD_SETTING_OVER_WEIGHT               ;
        mDspForm.mWCSetting.mTareWeight              = pDefaultSP->PD_SETTING_TARE_WEIGHT               ;
        mDspForm.mWCSetting.mOverMotion              = pDefaultSP->PD_SETTING_WC_NGMOTION               ;
        mDspForm.mWCSetting.mUnderMotion             = pDefaultSP->PD_SETTING_WC_NGMOTION               ;
        mDspForm.mWCSetting.mEtcMotion               = pDefaultSP->PD_SETTING_WC_NGMOTION               ;
        mDspForm.mWCSetting.mNGLamp                  = pDefaultSP->PD_SETTING_WC_NG_LAMP                ;
        mDspForm.mWCSetting.mNGBuzzer                = pDefaultSP->PD_SETTING_WC_NG_BUZZER              ;
        mDspForm.mWCSetting.mZeroDelayTime           = pDefaultSP->PD_SETTING_WC_ZERO_DELAY_TIME        ;
        mDspForm.mWCSetting.mDynamicFactor           = pDefaultSP->PD_SETTING_DYNAMIC_FAC               ;
        mDspForm.mWCSetting.mEnableEtcError          = pDefaultSP->PD_SETTING_ENABLE_ETC_ERR            ;
        mDspForm.mWCSetting.mFilterCoefficient       = pDefaultSP->PD_DEFAULT_SETTING_FILTER_COEFFICIENT;
        mDspForm.mWCSetting.mMeasureCueSign          = pDefaultSP->PD_DEFAULT_SETTING_MEASURE_CUE_SIGN  ;
        mDspForm.mWCSetting.mMeasureSection          = pDefaultSP->PD_DEFAULT_SETTING_MEASURE_SECTION   ;
        mDspForm.mWCSetting.mAutoSetting             = pDefaultSP->PD_SETTING_WC_AUTO_SETTING           ;
        mDspForm.mMDSetting.mSenstivity              = pDefaultSP->PD_SETTING_MD_SENSTIVITY             ;
        mDspForm.mMDSetting.mNGMotion                = pDefaultSP->PD_SETTING_MD_NGMOTION               ;
        mDspForm.mMDSetting.mNGLamp                  = pDefaultSP->PD_SETTING_MD_NG_LAMP                ;
        mDspForm.mMDSetting.mNGBuzzer                = pDefaultSP->PD_SETTING_MD_NG_BUZZER              ;
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
            else if(key == "MotorDecelerationTime"){ findFieldCnt++; mDspForm.mCommSetting.mMotorDecelerationTime = value.toUInt()     ;}
            else if(key == "GroupCount"           ){ findFieldCnt++; mDspForm.mCommSetting.mGroupCount            = value.toUInt()     ;}
            else if(key == "GroupMotion"          ){ findFieldCnt++; mDspForm.mCommSetting.mGroupMotion           = value.toUInt()     ;}
            else if(key == "GroupLamp"            ){ findFieldCnt++; mDspForm.mCommSetting.mGroupLamp             = value.toUInt()     ;}
            else if(key == "GroupBuzzer"          ){ findFieldCnt++; mDspForm.mCommSetting.mGroupBuzzer           = value.toUInt()     ;}
            else if(key == "UnderWeight"          ){ findFieldCnt++; mDspForm.mWCSetting.mUnderWeight             = value.toUInt()     ;}
            else if(key == "UnderWarningWeight"   ){ findFieldCnt++; mDspForm.mWCSetting.mUnderWarningWeight      = value.toUInt()     ;}
            else if(key == "NormalWeight"         ){ findFieldCnt++; mDspForm.mWCSetting.mNormalWeight            = value.toUInt()     ;}
            else if(key == "OverWarningWeight"    ){ findFieldCnt++; mDspForm.mWCSetting.mOverWarningWeight       = value.toUInt()     ;}
            else if(key == "OverWeight"           ){ findFieldCnt++; mDspForm.mWCSetting.mOverWeight              = value.toUInt()     ;}
            else if(key == "TareWeight"           ){ findFieldCnt++; mDspForm.mWCSetting.mTareWeight              = value.toUInt()     ;}
            else if(key == "WCOverMotion"         ){ findFieldCnt++; mDspForm.mWCSetting.mOverMotion              = value.toUInt()     ;}
            else if(key == "WCUnderMotion"        ){ findFieldCnt++; mDspForm.mWCSetting.mUnderMotion             = value.toUInt()     ;}
            else if(key == "WCEtcMotion"          ){ findFieldCnt++; mDspForm.mWCSetting.mEtcMotion               = value.toUInt()     ;}
            else if(key == "WCEnableEtcError"     ){ findFieldCnt++; mDspForm.mWCSetting.mEnableEtcError          = value.toUInt()     ;}
            else if(key == "DynamicFactor"        ){ findFieldCnt++; mDspForm.mWCSetting.mDynamicFactor           = value.toUInt()     ;}
            else if(key == "WCNGLamp"             ){ findFieldCnt++; mDspForm.mWCSetting.mNGLamp                  = value.toUInt()     ;}
            else if(key == "WCNGBuzzer"           ){ findFieldCnt++; mDspForm.mWCSetting.mNGBuzzer                = value.toUInt()     ;}
            else if(key == "MDSenstivity"         ){ findFieldCnt++; mDspForm.mMDSetting.mSenstivity              = value.toUInt()     ;}
            else if(key == "MDNGMotion"           ){ findFieldCnt++; mDspForm.mMDSetting.mNGMotion                = value.toUInt()     ;}
            else if(key == "MDNGLamp"             ){ findFieldCnt++; mDspForm.mMDSetting.mNGLamp                  = value.toUInt()     ;}
            else if(key == "MDNGBuzzer"           ){ findFieldCnt++; mDspForm.mMDSetting.mNGBuzzer                = value.toUInt()     ;}
            else if(key == "FilterCoefficient"    ){ findFieldCnt++; mDspForm.mWCSetting.mFilterCoefficient       = value.toUInt()     ;}
            else if(key == "MeasureCueSign"       ){ findFieldCnt++; mDspForm.mWCSetting.mMeasureCueSign          = value.toUInt()     ;}
            else if(key == "MeasureSection"       ){ findFieldCnt++; mDspForm.mWCSetting.mMeasureSection          = value.toUInt()     ;}
            else if(key == "AutoSetting"          ){ findFieldCnt++; mDspForm.mWCSetting.mAutoSetting             = value.toUInt()     ;}
            else if(key == "ZeroDelayTime"        ){ findFieldCnt++; mDspForm.mWCSetting.mZeroDelayTime           = value.toUInt()     ;}
        }

        return findFieldCnt == 0 ? false : true;
    }

    QString toString(QString divider){
        return QString("Seq:%1%2No:%3%4Name:%5%6Length:%7%8Speed:%9%10MotorAccelerationTime:%11%12"
                       "MotorDecelerationTime:%13%14"
                       "GroupCount:%15%16"
                       "GroupMotion:%17%18"
                       "GroupLamp:%19%20"
                       "GroupBuzzer:%21%22"
                       "UnderWeight:%23%24"
                       "UnderWarningWeight:%25%26"
                       "NormalWeight:%27%28"
                       "OverWarningWeight:%29%30"
                       "OverWeight:%31%32"
                       "TareWeight:%33%34"
                       "WCOverMotion:%35%36"
                       "WCUnderMotion:%37%38"
                       "WCEtcMotion:%39%40"
                       "WCNGLamp:%41%42"
                       "WCNGBuzzer:%43%44"
                       "WCEnableEtcError:%45%46"
                       "DynamicFactor:%47%48"
                       "MDSenstivity:%49%50"
                       "MDNGMotion:%51%52"
                       "MDNGLamp:%53%54"
                       "MDNGBuzzer:%55%56"
                       "FilterCoefficient:%57%58"
                       "MeasureCueSign:%59%60"
                       "MeasureSection:%61%62"
                       "AutoSetting:%63%64"
                       "ZeroDelayTime:%65")
                .arg(mSeq                                        ).arg(divider)
                .arg(mDspForm.mCommSetting.mProductNum           ).arg(divider)
                .arg(mName                                       ).arg(divider)
                .arg(mDspForm.mCommSetting.mLength               ).arg(divider)
                .arg(mDspForm.mCommSetting.mSpeed                ).arg(divider)
                .arg(mDspForm.mCommSetting.mMotorAccelerationTime).arg(divider)
                .arg(mDspForm.mCommSetting.mMotorDecelerationTime).arg(divider)
                .arg(mDspForm.mCommSetting.mGroupCount           ).arg(divider)
                .arg(mDspForm.mCommSetting.mGroupMotion          ).arg(divider)
                .arg(mDspForm.mCommSetting.mGroupLamp            ).arg(divider)
                .arg(mDspForm.mCommSetting.mGroupBuzzer          ).arg(divider)
                .arg(mDspForm.mWCSetting.mUnderWeight            ).arg(divider)
                .arg(mDspForm.mWCSetting.mUnderWarningWeight     ).arg(divider)
                .arg(mDspForm.mWCSetting.mNormalWeight           ).arg(divider)
                .arg(mDspForm.mWCSetting.mOverWarningWeight      ).arg(divider)
                .arg(mDspForm.mWCSetting.mOverWeight             ).arg(divider)
                .arg(mDspForm.mWCSetting.mTareWeight             ).arg(divider)
                .arg(mDspForm.mWCSetting.mOverMotion             ).arg(divider)
                .arg(mDspForm.mWCSetting.mUnderMotion            ).arg(divider)
                .arg(mDspForm.mWCSetting.mEtcMotion              ).arg(divider)
                .arg(mDspForm.mWCSetting.mNGLamp                 ).arg(divider)
                .arg(mDspForm.mWCSetting.mNGBuzzer               ).arg(divider)
                .arg(mDspForm.mWCSetting.mEnableEtcError         ).arg(divider)
                .arg(mDspForm.mWCSetting.mDynamicFactor          ).arg(divider)
                .arg(mDspForm.mMDSetting.mSenstivity             ).arg(divider)
                .arg(mDspForm.mMDSetting.mNGMotion               ).arg(divider)
                .arg(mDspForm.mMDSetting.mNGLamp                 ).arg(divider)
                .arg(mDspForm.mMDSetting.mNGBuzzer               ).arg(divider)
                .arg(mDspForm.mWCSetting.mFilterCoefficient      ).arg(divider)
                .arg(mDspForm.mWCSetting.mMeasureCueSign         ).arg(divider)
                .arg(mDspForm.mWCSetting.mMeasureSection         ).arg(divider)
                .arg(mDspForm.mWCSetting.mAutoSetting            ).arg(divider)
                .arg(mDspForm.mWCSetting.mZeroDelayTime          );
    }
};

Q_DECLARE_METATYPE(PDSettingDto);

#endif // PDSETTINGDTO_H
