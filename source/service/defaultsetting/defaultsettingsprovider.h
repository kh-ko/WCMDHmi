#ifndef DEFAULTSETTINGSPROVIDER_H
#define DEFAULTSETTINGSPROVIDER_H

#include <QObject>
#include <QDebug>
#include <QDateTime>


#include "source/service/def/builddef.h"
#include "source/service/def/filedef.h"
#include "source/service/dto/enum/enumdef.h"
#include "source/service/util/filereaderex.h"

#define pDefaultSP DefaultSettingSProvider::getInstance()

class DefaultSettingSProvider : public QObject
{
    Q_OBJECT
public:
    static DefaultSettingSProvider * getInstance()
    {
        static DefaultSettingSProvider *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new DefaultSettingSProvider();
        }

        return mpSelf;
    }

    explicit DefaultSettingSProvider(QObject *parent = nullptr):QObject(parent)
    {
    }

    ~DefaultSettingSProvider()
    {
    }

    bool                              IS_DONGNAM                         = false;
    QString                           DSP_CONNINFO_IP                    = "192.168.0.140";
    quint16                           DSP_CONNINFO_PORT                  = 10020;
    quint16                           PD_SETTING_NUM                     = 1    ;
    quint16                           PD_SETTING_LEN                     = 250  ;
    quint16                           PD_SETTING_SPEED                   = 40   ;
    quint32                           PD_SETTING_MOTOR_ACCTIME           = 1000 ;
    quint32                           PD_SETTING_NOR_WEIGHT              = 92000;
    quint32                           PD_SETTING_UNDER_W_WEIGHT          = 90000;
    quint32                           PD_SETTING_UNDER_WEIGHT            = 90000;
    quint32                           PD_SETTING_OVER_W_WEIGHT           = 94000;
    quint32                           PD_SETTING_OVER_WEIGHT             = 94000;
    quint32                           PD_SETTING_TARE_WEIGHT             = 0    ;
    EnumDef::eNGMotion                PD_SETTING_WC_NGMOTION             = EnumDef::NG_MOTION_REJECT_01;
    quint32                           PD_SETTING_DYNAMIC_FAC             = 10000000;
    quint16                           PD_SETTING_ENABLE_ETC_ERR          = 1;
    quint16                           PD_SETTING_MD_SENSTIVITY           = 9999;
    EnumDef::eNGMotion                PD_SETTING_MD_NGMOTION             = EnumDef::NG_MOTION_REJECT_02;
    QString                           INFO_COMPANY                       = "NOVASEN"        ; //"DONG NAM MACHINERY SHOP";
    QString                           INFO_TEL                           = "T 1600-4917"    ; //"T 053-551-1452";
    QString                           INFO_HOMEPAGE                      = "www.novasen.com"; //"www.dongnam1998.com";
    QString                           INFO_MODEL                         = "NSWCNSAMD480"; // "NSAMD480"
    int                               INFO_DEVICE_NUM                    = 1;
    QString                           INFO_HMI_VER                       = BUILD_HMI_VERSION;
    QString                           INFO_POWER                         = "1% 220VAC 60Hz";
    quint32                           INFO_MAX_WEIGHT                    = 10000;
    QString                           SEC_PWD                            = "1111";
    QString                           SEC_ADMIN_PWD                      = "7071";
    EnumDef::eLang                    LANGUAGE                           = EnumDef::LANG_KOR;
    bool                              GUI_IS_DETAIL                      = false;
    EnumDef::eViewMode                GUI_VIEW_MODE                      = EnumDef::WC_VIEWMODE_CURRENT;
    EnumDef::eTrendsGraphOptionH      TR_OPTION_H                        = EnumDef::TRENDSOPTION_H_UNDER_TO_OVER;
    EnumDef::eTrendsGraphOptionFilter TR_OPTION_FILTER                   = EnumDef::TRENDSOPTION_FILTER_TOTAL;
    EnumDef::eTrendsGraphOptionLastN  TR_OPTION_TOTAL_SINCE_START        = EnumDef::TRENDSOPTION_TOTAL_SINCE_START;
    int                               TR_LAST_N_VALUE                    = 100;
    QString                           BACKUP_LAST_DATE                   = "2020/01/01";
    quint32                           DEV_SETTING_BUZZERTIME             = 1000                                  ;
    quint32                           DEV_SETTING_LAMPTIME               = 1000                                  ;
    quint32                           DEV_SETTING_RJ_RUN_TIME_RATIO      = 1500                                  ;
    quint32                           DEV_SETTING_RJ_OPENTIME            = 400                                   ;
    quint32                           DEV_SETTING_SPEED_CONVERTER        = 2070000                               ;
    EnumDef::eMotorDirection          DEV_SETTING_MOTOR_DIR              = EnumDef::MOTOR_DIRECTION_RIGHT_TO_LEFT;
    EnumDef::eMotorType               DEV_SETTING_MOTOR_TYPE             = EnumDef::MOTORTYPE_MOTOR_3_PHASE      ;
    quint16                           DEV_SETTING_MOTOR_MD_RATIO         = 100                                   ;
    quint16                           DEV_SETTING_MOTOR_WC_RATIO         = 100                                   ;
    quint16                           DEV_SETTING_MOTOR_RJ_RATIO         = 100                                   ;
    EnumDef::eMachineMode             DEV_SETTING_MACHINE_MODE           = EnumDef::MACHINE_MODE_COMBI           ;
    quint32                           DEV_SETTING_DP_STABILITY           = 1                                     ;
    quint32                           DEV_SETTING_MEASURE_CUE_SIGN       = 300                                   ;
    quint32                           DEV_SETTING_MIN_STATIC_WEIGHT      = 5000                                  ;
    quint32                           DEV_SETTING_MIN_DYNAMIC_WEIGHT     = 10000                                 ;
    quint32                           DEV_SETTING_SCALER                 = 200                                   ;
    quint32                           DEV_SETTING_STATIC_FACTOR          = 998932                                ;
    quint16                           DEV_SETTING_WC_PHOTO_IS_ON         = true                                  ;
    quint32                           DEV_SETTING_STATIC_STANDARD_WEIGHT = 10000                                 ;
    quint32                           DEV_SETTING_DYNAMIC_BASE_WEIGHT    = 10000                                 ;
    EnumDef::eSensorMode              DEV_SETTING_DETECT_MODE            = EnumDef::SENS_MODE_INDEPENDENT        ;
    quint32                           DEV_SETTING_DETECT_DETECT_TIME     = 500                                   ;
    quint32                           DEV_SETTING_RUN_DETECT_TIME        = 1000                                  ;
    quint32                           DEV_SETTING_SIGNAL_DELAY_TIME      = 0                                     ;
    quint16                           DEV_SETTING_MD_PHOTO_IS_ON         = true                                  ;
    quint16                           DEV_SETTING_SENSOR_CNT             = 1                                     ;
    quint16                           DEV_SETTING_SENSOR_LEN             = 540                                   ;
    quint16                           DEV_SETTING_DIST_TO_RJ             = 720                                   ;
    quint16                           DEV_SETTING_DIST_BTW_SENSOR        = 180                                   ;
    quint16                           DEV_SETTING_DIST_TO_WC             = 650                                   ;
    quint16                           DEV_SETTING_DIST_TO_PHOTO_SENSOR   = 250                                   ;
    bool                              HMI_SETTING_SW_POWER_OFF           = true                                  ;
    bool                              HMI_SETTING_IS_DAY_MODE            = true                                  ;
    bool                              HMI_SETTING_IS_DEBUG_MODE          = false                                 ;
    quint32                           HMI_SETTING_DYNAMIC_FACTOR         = 10000000                              ;
    quint16                           HMI_SETTING_SAMPLE_SENSTIVITY_01   = 0                                     ;
    quint16                           HMI_SETTING_SAMPLE_SENSTIVITY_02   = 0                                     ;
    quint16                           HMI_SETTING_SAMPLE_SENSTIVITY_03   = 0                                     ;
    quint16                           HMI_SETTING_SAMPLE_SENSTIVITY_04   = 0                                     ;
    quint16                           HMI_SETTING_SAMPLE_SENSTIVITY_05   = 0                                     ;

public:
    void start()
    {
        QStringList lines = FileReaderEx::readAllLine(FileDef::DEFAULT_SETTING_DIR(), FileDef::DEFAULT_SETTING_FILENAME());

        foreach(QString line ,lines)
        {
            if(line.contains(":") == false)
                continue;

            int splitIdx  = line.indexOf(":");
            QString key   = line.left(splitIdx);
            QString value = line.mid(splitIdx+1);

            if     (key == "IS_DONGNAM"                        ){ IS_DONGNAM                         = value.toInt() == 1 ? true : false                ;}
            if     (key == "DSP_CONNINFO_IP"                   ){ DSP_CONNINFO_IP                    = value                                            ;}
            else if(key == "DSP_CONNINFO_PORT"                 ){ DSP_CONNINFO_PORT                  = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_NUM"                    ){ PD_SETTING_NUM                     = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_LEN"                    ){ PD_SETTING_LEN                     = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_SPEED"                  ){ PD_SETTING_SPEED                   = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_MOTOR_ACCTIME"          ){ PD_SETTING_MOTOR_ACCTIME           = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_NOR_WEIGHT"             ){ PD_SETTING_NOR_WEIGHT              = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_UNDER_W_WEIGHT"         ){ PD_SETTING_UNDER_W_WEIGHT          = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_UNDER_WEIGHT"           ){ PD_SETTING_UNDER_WEIGHT            = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_OVER_W_WEIGHT"          ){ PD_SETTING_OVER_W_WEIGHT           = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_OVER_WEIGHT"            ){ PD_SETTING_OVER_WEIGHT             = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_TARE_WEIGHT"            ){ PD_SETTING_TARE_WEIGHT             = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_WC_NGMOTION"            ){ PD_SETTING_WC_NGMOTION             = (EnumDef::eNGMotion)value.toUInt()               ;}
            else if(key == "PD_SETTING_DYNAMIC_FAC"            ){ PD_SETTING_DYNAMIC_FAC             = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_ENABLE_ETC_ERR"         ){ PD_SETTING_ENABLE_ETC_ERR          = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_MD_SENSTIVITY"          ){ PD_SETTING_MD_SENSTIVITY           = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_MD_NGMOTION"            ){ PD_SETTING_MD_NGMOTION             = (EnumDef::eNGMotion)value.toUInt()               ;}
            else if(key == "INFO_COMPANY"                      ){ INFO_COMPANY                       = value                                            ;}
            else if(key == "INFO_TEL"                          ){ INFO_TEL                           = value                                            ;}
            else if(key == "INFO_HOMEPAGE"                     ){ INFO_HOMEPAGE                      = value                                            ;}
            else if(key == "INFO_MODEL"                        ){ INFO_MODEL                         = value                                            ;}
            else if(key == "INFO_DEVICE_NUM"                   ){ INFO_DEVICE_NUM                    = value.toUInt()                                   ;}
            else if(key == "INFO_HMI_VER"                      ){ INFO_HMI_VER                       = value                                            ;}
            else if(key == "INFO_POWER"                        ){ INFO_POWER                         = value                                            ;}
            else if(key == "INFO_MAX_WEIGHT"                   ){ INFO_MAX_WEIGHT                    = value.toUInt()                                   ;}
            else if(key == "SEC_PWD"                           ){ SEC_PWD                            = value                                            ;}
            else if(key == "SEC_ADMIN_PWD"                     ){ SEC_ADMIN_PWD                      = value                                            ;}
            else if(key == "LANGUAGE"                          ){ LANGUAGE                           = (EnumDef::eLang)value.toUInt()                   ;}
            else if(key == "GUI_IS_DETAIL"                     ){ GUI_IS_DETAIL                      = value.toUInt() == 1 ? true : false               ;}
            else if(key == "GUI_VIEW_MODE"                     ){ GUI_VIEW_MODE                      = (EnumDef::eViewMode)value.toUInt()               ;}
            else if(key == "TR_OPTION_H"                       ){ TR_OPTION_H                        = (EnumDef::eTrendsGraphOptionH)value.toUInt()     ;}
            else if(key == "TR_OPTION_FILTER"                  ){ TR_OPTION_FILTER                   = (EnumDef::eTrendsGraphOptionFilter)value.toUInt();}
            else if(key == "TR_OPTION_TOTAL_SINCE_START"       ){ TR_OPTION_TOTAL_SINCE_START        = (EnumDef::eTrendsGraphOptionLastN) value.toUInt();}
            else if(key == "TR_LAST_N_VALUE"                   ){ TR_LAST_N_VALUE                    = value.toUInt()                                   ;}
            else if(key == "BACKUP_LAST_DATE"                  ){ BACKUP_LAST_DATE                   = value                                            ;}
            else if(key == "DEV_SETTING_BUZZERTIME"            ){ DEV_SETTING_BUZZERTIME             = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_LAMPTIME"              ){ DEV_SETTING_LAMPTIME               = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_RJ_RUN_TIME_RATIO"     ){ DEV_SETTING_RJ_RUN_TIME_RATIO      = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_RJ_OPENTIME"           ){ DEV_SETTING_RJ_OPENTIME            = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_SPEED_CONVERTER"       ){ DEV_SETTING_SPEED_CONVERTER        = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_MOTOR_DIR"             ){ DEV_SETTING_MOTOR_DIR              = (EnumDef::eMotorDirection)value.toUInt()         ;}
            else if(key == "DEV_SETTING_MOTOR_TYPE"            ){ DEV_SETTING_MOTOR_TYPE             = (EnumDef::eMotorType     )value.toUInt()         ;}
            else if(key == "DEV_SETTING_MOTOR_MD_RATIO"        ){ DEV_SETTING_MOTOR_MD_RATIO         = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_MOTOR_WC_RATIO"        ){ DEV_SETTING_MOTOR_WC_RATIO         = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_MOTOR_RJ_RATIO"        ){ DEV_SETTING_MOTOR_RJ_RATIO         = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_MACHINE_MODE"          ){ DEV_SETTING_MACHINE_MODE           = (EnumDef::eMachineMode)value.toUInt()            ;}
            else if(key == "DEV_SETTING_DP_STABILITY"          ){ DEV_SETTING_DP_STABILITY           = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_MEASURE_CUE_SIGN"      ){ DEV_SETTING_MEASURE_CUE_SIGN       = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_MIN_STATIC_WEIGHT"     ){ DEV_SETTING_MIN_STATIC_WEIGHT      = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_MIN_DYNAMIC_WEIGHT"    ){ DEV_SETTING_MIN_DYNAMIC_WEIGHT     = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_SCALER"                ){ DEV_SETTING_SCALER                 = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_STATIC_FACTOR"         ){ DEV_SETTING_STATIC_FACTOR          = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_WC_PHOTO_IS_ON"        ){ DEV_SETTING_WC_PHOTO_IS_ON         = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_STATIC_STANDARD_WEIGHT"){ DEV_SETTING_STATIC_STANDARD_WEIGHT = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_DYNAMIC_BASE_WEIGHT"   ){ DEV_SETTING_DYNAMIC_BASE_WEIGHT    = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_DETECT_MODE"           ){ DEV_SETTING_DETECT_MODE            = (EnumDef::eSensorMode)value.toUInt()             ;}
            else if(key == "DEV_SETTING_DETECT_DETECT_TIME"    ){ DEV_SETTING_DETECT_DETECT_TIME     = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_RUN_DETECT_TIME"       ){ DEV_SETTING_RUN_DETECT_TIME        = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_SIGNAL_DELAY_TIME"     ){ DEV_SETTING_SIGNAL_DELAY_TIME      = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_MD_PHOTO_IS_ON"        ){ DEV_SETTING_MD_PHOTO_IS_ON         = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_SENSOR_CNT"            ){ DEV_SETTING_SENSOR_CNT             = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_SENSOR_LEN"            ){ DEV_SETTING_SENSOR_LEN             = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_DIST_TO_RJ"            ){ DEV_SETTING_DIST_TO_RJ             = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_DIST_BTW_SENSOR"       ){ DEV_SETTING_DIST_BTW_SENSOR        = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_DIST_TO_WC"            ){ DEV_SETTING_DIST_TO_WC             = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_DIST_TO_PHOTO_SENSOR"  ){ DEV_SETTING_DIST_TO_PHOTO_SENSOR   = value.toUInt()                                   ;}
            else if(key == "HMI_SETTING_SW_POWER_OFF"          ){ HMI_SETTING_SW_POWER_OFF           = value.toUInt() == 1 ? true : false               ;}
            else if(key == "HMI_SETTING_IS_DAY_MODE"           ){ HMI_SETTING_IS_DAY_MODE            = value.toUInt() == 1 ? true : false               ;}
            else if(key == "HMI_SETTING_IS_DEBUG_MODE"         ){ HMI_SETTING_IS_DEBUG_MODE          = value.toUInt() == 1 ? true : false               ;}
            else if(key == "HMI_SETTING_DYNAMIC_FACTOR"        ){ HMI_SETTING_DYNAMIC_FACTOR         = value.toUInt()                                   ;}
            else if(key == "HMI_SETTING_SAMPLE_SENSTIVITY_01"  ){ HMI_SETTING_SAMPLE_SENSTIVITY_01   = value.toUInt()                                   ;}
            else if(key == "HMI_SETTING_SAMPLE_SENSTIVITY_02"  ){ HMI_SETTING_SAMPLE_SENSTIVITY_02   = value.toUInt()                                   ;}
            else if(key == "HMI_SETTING_SAMPLE_SENSTIVITY_03"  ){ HMI_SETTING_SAMPLE_SENSTIVITY_03   = value.toUInt()                                   ;}
            else if(key == "HMI_SETTING_SAMPLE_SENSTIVITY_04"  ){ HMI_SETTING_SAMPLE_SENSTIVITY_04   = value.toUInt()                                   ;}
            else if(key == "HMI_SETTING_SAMPLE_SENSTIVITY_05"  ){ HMI_SETTING_SAMPLE_SENSTIVITY_05   = value.toUInt()                                   ;}
        }

        emit signalEventStarted();
    }
    void stop()
    {
        emit signalEventStopped();
    }

signals:
    void signalEventStarted();
    void signalEventStopped();

};


#endif // DEFAULTSETTINGSPROVIDER_H
