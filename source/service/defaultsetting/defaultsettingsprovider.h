#ifndef DEFAULTSETTINGSPROVIDER_H
#define DEFAULTSETTINGSPROVIDER_H

#include <QObject>
#include <QDebug>
#include <QSerialPort>
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

    EnumDef::eCompany                 COMPANY                            = EnumDef::eCompany::COMPANY_NOVASEN;
    QString                           DSP_CONNINFO_IP                    = "192.168.0.140";
    quint16                           DSP_CONNINFO_PORT                  = 10020;
    quint16                           PD_SETTING_NUM                     = 1    ;
    quint16                           PD_SETTING_LEN                     = 250  ;
    quint16                           PD_SETTING_SPEED                   = 40   ;
    quint32                           PD_SETTING_MOTOR_ACCTIME           = 1000 ;
    quint32                           PD_SETTING_MOTOR_DECTIME           = 1000 ;
    quint32                           PD_SETTING_GROUP_COUNT             = 0    ;
    quint16                           PD_SETTING_GROUP_MOTION            = EnumDef::NG_MOTION_NON;
    quint16                           PD_SETTING_GROUP_LAMP              = 0;
    quint16                           PD_SETTING_GROUP_BUZZER            = 0;
    quint32                           PD_SETTING_NOR_WEIGHT              = 92000;
    quint32                           PD_SETTING_UNDER_W_WEIGHT          = 90000;
    quint32                           PD_SETTING_UNDER_WEIGHT            = 90000;
    quint32                           PD_SETTING_OVER_W_WEIGHT           = 94000;
    quint32                           PD_SETTING_OVER_WEIGHT             = 94000;
    quint32                           PD_SETTING_TARE_WEIGHT             = 0    ;
    EnumDef::eNGMotion                PD_SETTING_WC_NGMOTION             = EnumDef::NG_MOTION_SORTER_01;
    quint16                           PD_SETTING_WC_NG_LAMP              = 1;
    quint16                           PD_SETTING_WC_NG_BUZZER            = 1;
    quint16                           PD_SETTING_WC_ZERO_DELAY_TIME      = 0;
    quint32                           PD_SETTING_DYNAMIC_FAC             = 10000000;
    quint16                           PD_SETTING_ENABLE_ETC_ERR          = 1;
    quint16                           PD_SETTING_WC_AUTO_SETTING         = 1;
    quint16                           PD_SETTING_MD_SENSTIVITY           = 9999;
    EnumDef::eNGMotion                PD_SETTING_MD_NGMOTION             = EnumDef::NG_MOTION_SORTER_02;
    quint16                           PD_SETTING_MD_NG_LAMP              = 1;
    quint16                           PD_SETTING_MD_NG_BUZZER            = 1;
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
    EnumDef::ePDSortMode              GUI_PD_SORT_MODE                   = EnumDef::PD_SORT_NAME;
    EnumDef::eTrendsGraphOptionH      TR_OPTION_H                        = EnumDef::TRENDSOPTION_H_UNDER_TO_OVER;
    EnumDef::eTrendsGraphOptionFilter TR_OPTION_FILTER                   = EnumDef::TRENDSOPTION_FILTER_TOTAL;
    EnumDef::eTrendsGraphOptionLastN  TR_OPTION_TOTAL_SINCE_START        = EnumDef::TRENDSOPTION_TOTAL_SINCE_START;
    int                               TR_LAST_N_VALUE                    = 100;
    QString                           BACKUP_LAST_DATE                   = "2020/01/01";
    quint32                           DEV_SETTING_BUZZERTIME             = 1000                                  ;
    quint32                           DEV_SETTING_LAMPTIME               = 1000                                  ;
    quint32                           DEV_SETTING_SPEED_CONVERTER        = 2110000                               ;
    EnumDef::eMotorDirection          DEV_SETTING_MOTOR_DIR              = EnumDef::MOTOR_DIRECTION_RIGHT_TO_LEFT;
    EnumDef::eMotorType               DEV_SETTING_MOTOR_TYPE             = EnumDef::MOTORTYPE_MOTOR_MITSUBISHI   ;
    quint16                           DEV_SETTING_MOTOR_MD_RATIO         = 100                                   ;
    quint16                           DEV_SETTING_MOTOR_WC_RATIO         = 100                                   ;
    quint16                           DEV_SETTING_MOTOR_RJ_RATIO         = 100                                   ;
    quint32                           DEV_SETTING_SORTER_01_RUNTIME_RATIO= 1500                                  ;
    quint32                           DEV_SETTING_SORTER_01_OPENTIME     = 0                                     ;
    quint16                           DEV_SETTING_SORTER_01_VRRATIO      = 1                                     ;
    quint32                           DEV_SETTING_SORTER_02_RUNTIME_RATIO= 1500                                  ;
    quint32                           DEV_SETTING_SORTER_02_OPENTIME     = 0                                     ;
    quint16                           DEV_SETTING_SORTER_02_VRRATIO      = 1                                     ;
    quint32                           DEV_SETTING_SORTER_03_RUNTIME_RATIO= 1500                                  ;
    quint32                           DEV_SETTING_SORTER_03_OPENTIME     = 0                                     ;
    quint16                           DEV_SETTING_SORTER_03_VRRATIO      = 1                                     ;
    quint32                           DEV_SETTING_SORTER_04_RUNTIME_RATIO= 1500                                  ;
    quint32                           DEV_SETTING_SORTER_04_OPENTIME     = 0                                     ;
    quint16                           DEV_SETTING_SORTER_04_VRRATIO      = 1                                     ;
    EnumDef::eMachineMode             DEV_SETTING_MACHINE_MODE           = EnumDef::MACHINE_MODE_COMBI           ;
    quint32                           DEV_SETTING_DP_STABILITY           = 1                                     ;
    quint32                           DEV_SETTING_MEASURE_CUE_SIGN       = 300                                   ;
    quint32                           DEV_SETTING_MIN_STATIC_WEIGHT      = 500                                   ;
    quint32                           DEV_SETTING_MIN_DYNAMIC_WEIGHT     = 100                                   ;
    quint32                           DEV_SETTING_SCALER                 = 100                                   ;
    quint32                           DEV_SETTING_STATIC_FACTOR          = 998932                                ;
    quint16                           DEV_SETTING_WC_PHOTO_IS_ON         = true                                  ;
    quint32                           DEV_SETTING_STATIC_STANDARD_WEIGHT = 10000                                 ;
    quint32                           DEV_SETTING_DYNAMIC_BASE_WEIGHT    = 10000                                 ;
    qint16                            DEV_SETTING_REF_VOLTAGE            = 4465                                  ;
    quint16                           DEV_SETTING_WC_GRAPH_POINT_CNT     = 10                                    ;
    EnumDef::eSensorMode              DEV_SETTING_DETECT_MODE            = EnumDef::SENS_MODE_INDEPENDENT        ;
    quint32                           DEV_SETTING_DETECT_DETECT_TIME     = 500                                   ;
    quint32                           DEV_SETTING_RUN_DETECT_TIME        = 1000                                  ;
    quint32                           DEV_SETTING_SIGNAL_DELAY_TIME      = 45                                     ;
    quint16                           DEV_SETTING_MD_PHOTO_IS_ON         = true                                  ;
    quint16                           DEV_SETTING_SENSOR_CNT             = 1                                     ;
    quint16                           DEV_SETTING_SENSOR_LEN             = 540                                   ;
    quint16                           DEV_SETTING_DIST_BTW_SENSOR        = 180                                   ;
    quint16                           DEV_SETTING_DIST_TO_WC             = 650                                   ;
    quint16                           DEV_SETTING_DIST_TO_PHOTO_SENSOR   = 250                                   ;
    quint16                           DEV_SETTING_DIST_TO_SORTER_01      = 720                                   ;
    quint16                           DEV_SETTING_DIST_TO_SORTER_02      = 720                                   ;
    quint16                           DEV_SETTING_DIST_TO_SORTER_03      = 720                                   ;
    quint16                           DEV_SETTING_DIST_TO_SORTER_04      = 720                                   ;

    bool                              HMI_SETTING_SW_POWER_OFF           = true                                  ;
    bool                              HMI_SETTING_IS_DAY_MODE            = true                                  ;
    bool                              HMI_SETTING_IS_DEBUG_MODE          = false                                 ;
    quint16                           HMI_SETTING_SAMPLE_SENSTIVITY_01   = 0                                     ;
    quint16                           HMI_SETTING_SAMPLE_SENSTIVITY_02   = 0                                     ;
    quint16                           HMI_SETTING_SAMPLE_SENSTIVITY_03   = 0                                     ;
    quint16                           HMI_SETTING_SAMPLE_SENSTIVITY_04   = 0                                     ;
    quint16                           HMI_SETTING_SAMPLE_SENSTIVITY_05   = 0                                     ;

    quint16                           PD_DEFAULT_SETTING_FILTER_COEFFICIENT = 25                                 ;
    quint32                           PD_DEFAULT_SETTING_MEASURE_CUE_SIGN   = 200                                ;
    quint32                           PD_DEFAULT_SETTING_MEASURE_SECTION    = 100                                ;

    quint32                           ETC_SETTING_MAX_ERROR                     = 100                            ;
    qint32                            ETC_SETTING_MDCHECKUP_NEXT_STEP_WAIT_MSEC = 5000                           ;

    QString                           RTU_MODBUS_PORT                    = "/dev/ttyAMA0"                        ;
    QSerialPort::Parity               RTU_MODBUS_PARITY                  = QSerialPort::NoParity                 ;
    QSerialPort::BaudRate             RTU_MODBUS_BAUDRATE                = QSerialPort::Baud57600                ;
    QSerialPort::DataBits             RTU_MODBUS_DATABITS                = QSerialPort::Data8                    ;
    QSerialPort::StopBits             RTU_MODBUS_STOPBITS                = QSerialPort::OneStop                  ;

    bool                              PRINTER_IS_USE                     = false                                 ;
    QString                           PRINTER_PORT                       = "ttyUSB0"                             ;
    QSerialPort::BaudRate             PRINTER_BAUDRATE                   = QSerialPort::Baud9600                 ;
    QSerialPort::DataBits             PRINTER_DATABITS                   = QSerialPort::Data8                    ;
    QSerialPort::StopBits             PRINTER_STOPBITS                   = QSerialPort::OneStop                  ;
    QSerialPort::Parity               PRINTER_PARITY                     = QSerialPort::NoParity                 ;
    bool                              PRINTER_INCLUDE_BLANK_LINE         = true                                  ;
    bool                              PRINTER_INCLUDE_DIVIDER            = true                                  ;

    QString                           VNC_VIEW_IP                        = "121.175.173.236"                     ;
    bool                              CCP_SERVER_IS_USE                  = false                                 ;
    QString                           CCP_SERVER_URL                     = "http://121.175.173.236:17071/DevDataCollect/WriteRealTimeData";

    bool                              ADC_AUTOCALIB_IS_USE               = false                                 ;
    qint32                            ADC_AUTOCALIB_MIN_ADC              = -500                                  ;
    qint32                            ADC_AUTOCALIB_MAX_ADC              = 500                                   ;

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

            if     (key == "COMPANY"                            ){ COMPANY                            = (EnumDef::eCompany)value.toUInt()                ;}
            if     (key == "DSP_CONNINFO_IP"                    ){ DSP_CONNINFO_IP                    = value                                            ;}
            else if(key == "DSP_CONNINFO_PORT"                  ){ DSP_CONNINFO_PORT                  = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_NUM"                     ){ PD_SETTING_NUM                     = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_LEN"                     ){ PD_SETTING_LEN                     = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_SPEED"                   ){ PD_SETTING_SPEED                   = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_MOTOR_ACCTIME"           ){ PD_SETTING_MOTOR_ACCTIME           = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_MOTOR_DECTIME"           ){ PD_SETTING_MOTOR_DECTIME           = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_GROUP_COUNT"             ){ PD_SETTING_GROUP_COUNT             = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_GROUP_MOTION"            ){ PD_SETTING_GROUP_MOTION            = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_GROUP_LAMP"              ){ PD_SETTING_GROUP_LAMP              = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_GROUP_BUZZER"            ){ PD_SETTING_GROUP_BUZZER            = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_NOR_WEIGHT"              ){ PD_SETTING_NOR_WEIGHT              = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_UNDER_W_WEIGHT"          ){ PD_SETTING_UNDER_W_WEIGHT          = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_UNDER_WEIGHT"            ){ PD_SETTING_UNDER_WEIGHT            = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_OVER_W_WEIGHT"           ){ PD_SETTING_OVER_W_WEIGHT           = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_OVER_WEIGHT"             ){ PD_SETTING_OVER_WEIGHT             = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_TARE_WEIGHT"             ){ PD_SETTING_TARE_WEIGHT             = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_WC_NGMOTION"             ){ PD_SETTING_WC_NGMOTION             = (EnumDef::eNGMotion)value.toUInt()               ;}
            else if(key == "PD_SETTING_WC_NG_LAMP"              ){ PD_SETTING_WC_NG_LAMP              = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_WC_NG_BUZZER"            ){ PD_SETTING_WC_NG_BUZZER            = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_DYNAMIC_FAC"             ){ PD_SETTING_DYNAMIC_FAC             = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_ENABLE_ETC_ERR"          ){ PD_SETTING_ENABLE_ETC_ERR          = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_WC_AUTO_SETTING"         ){ PD_SETTING_WC_AUTO_SETTING         = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_WC_ZERO_DELAY_TIME"      ){ PD_SETTING_WC_ZERO_DELAY_TIME      = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_MD_SENSTIVITY"           ){ PD_SETTING_MD_SENSTIVITY           = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_MD_NGMOTION"             ){ PD_SETTING_MD_NGMOTION             = (EnumDef::eNGMotion)value.toUInt()               ;}
            else if(key == "PD_SETTING_MD_NG_LAMP"              ){ PD_SETTING_MD_NG_LAMP              = value.toUInt()                                   ;}
            else if(key == "PD_SETTING_MD_NG_BUZZER"            ){ PD_SETTING_MD_NG_BUZZER            = value.toUInt()                                   ;}
            else if(key == "INFO_COMPANY"                       ){ INFO_COMPANY                       = value                                            ;}
            else if(key == "INFO_TEL"                           ){ INFO_TEL                           = value                                            ;}
            else if(key == "INFO_HOMEPAGE"                      ){ INFO_HOMEPAGE                      = value                                            ;}
            else if(key == "INFO_MODEL"                         ){ INFO_MODEL                         = value                                            ;}
            else if(key == "INFO_DEVICE_NUM"                    ){ INFO_DEVICE_NUM                    = value.toUInt()                                   ;}
            else if(key == "INFO_HMI_VER"                       ){ INFO_HMI_VER                       = value                                            ;}
            else if(key == "INFO_POWER"                         ){ INFO_POWER                         = value                                            ;}
            else if(key == "INFO_MAX_WEIGHT"                    ){ INFO_MAX_WEIGHT                    = value.toUInt()                                   ;}
            else if(key == "SEC_PWD"                            ){ SEC_PWD                            = value                                            ;}
            else if(key == "SEC_ADMIN_PWD"                      ){ SEC_ADMIN_PWD                      = value                                            ;}
            else if(key == "LANGUAGE"                           ){ LANGUAGE                           = (EnumDef::eLang)value.toUInt()                   ;}
            else if(key == "GUI_IS_DETAIL"                      ){ GUI_IS_DETAIL                      = value.toUInt() == 1 ? true : false               ;}
            else if(key == "GUI_VIEW_MODE"                      ){ GUI_VIEW_MODE                      = (EnumDef::eViewMode)value.toUInt()               ;}
            else if(key == "GUI_PD_SORT_MODE"                   ){ GUI_PD_SORT_MODE                   = (EnumDef::ePDSortMode)value.toUInt()             ;}
            else if(key == "TR_OPTION_H"                        ){ TR_OPTION_H                        = (EnumDef::eTrendsGraphOptionH)value.toUInt()     ;}
            else if(key == "TR_OPTION_FILTER"                   ){ TR_OPTION_FILTER                   = (EnumDef::eTrendsGraphOptionFilter)value.toUInt();}
            else if(key == "TR_OPTION_TOTAL_SINCE_START"        ){ TR_OPTION_TOTAL_SINCE_START        = (EnumDef::eTrendsGraphOptionLastN) value.toUInt();}
            else if(key == "TR_LAST_N_VALUE"                    ){ TR_LAST_N_VALUE                    = value.toUInt()                                   ;}
            else if(key == "BACKUP_LAST_DATE"                   ){ BACKUP_LAST_DATE                   = value                                            ;}
            else if(key == "DEV_SETTING_BUZZERTIME"             ){ DEV_SETTING_BUZZERTIME             = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_LAMPTIME"               ){ DEV_SETTING_LAMPTIME               = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_SPEED_CONVERTER"        ){ DEV_SETTING_SPEED_CONVERTER        = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_MOTOR_DIR"              ){ DEV_SETTING_MOTOR_DIR              = (EnumDef::eMotorDirection)value.toUInt()         ;}
            else if(key == "DEV_SETTING_MOTOR_TYPE"             ){ DEV_SETTING_MOTOR_TYPE             = (EnumDef::eMotorType     )value.toUInt()         ;}
            else if(key == "DEV_SETTING_MOTOR_MD_RATIO"         ){ DEV_SETTING_MOTOR_MD_RATIO         = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_MOTOR_WC_RATIO"         ){ DEV_SETTING_MOTOR_WC_RATIO         = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_MOTOR_RJ_RATIO"         ){ DEV_SETTING_MOTOR_RJ_RATIO         = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_SORTER_01_RUNTIME_RATIO"){ DEV_SETTING_SORTER_01_RUNTIME_RATIO= value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_SORTER_01_OPENTIME"     ){ DEV_SETTING_SORTER_01_OPENTIME     = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_SORTER_01_VRRATIO"      ){ DEV_SETTING_SORTER_01_VRRATIO      = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_SORTER_02_RUNTIME_RATIO"){ DEV_SETTING_SORTER_02_RUNTIME_RATIO= value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_SORTER_02_OPENTIME"     ){ DEV_SETTING_SORTER_02_OPENTIME     = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_SORTER_02_VRRATIO"      ){ DEV_SETTING_SORTER_02_VRRATIO      = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_SORTER_03_RUNTIME_RATIO"){ DEV_SETTING_SORTER_03_RUNTIME_RATIO= value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_SORTER_03_OPENTIME"     ){ DEV_SETTING_SORTER_03_OPENTIME     = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_SORTER_03_VRRATIO"      ){ DEV_SETTING_SORTER_03_VRRATIO      = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_SORTER_04_RUNTIME_RATIO"){ DEV_SETTING_SORTER_04_RUNTIME_RATIO= value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_SORTER_04_OPENTIME"     ){ DEV_SETTING_SORTER_04_OPENTIME     = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_SORTER_04_VRRATIO"      ){ DEV_SETTING_SORTER_04_VRRATIO      = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_MACHINE_MODE"           ){ DEV_SETTING_MACHINE_MODE           = (EnumDef::eMachineMode)value.toUInt()            ;}
            else if(key == "DEV_SETTING_DP_STABILITY"           ){ DEV_SETTING_DP_STABILITY           = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_MEASURE_CUE_SIGN"       ){ DEV_SETTING_MEASURE_CUE_SIGN       = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_MIN_STATIC_WEIGHT"      ){ DEV_SETTING_MIN_STATIC_WEIGHT      = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_MIN_DYNAMIC_WEIGHT"     ){ DEV_SETTING_MIN_DYNAMIC_WEIGHT     = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_SCALER"                 ){ DEV_SETTING_SCALER                 = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_STATIC_FACTOR"          ){ DEV_SETTING_STATIC_FACTOR          = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_WC_PHOTO_IS_ON"         ){ DEV_SETTING_WC_PHOTO_IS_ON         = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_STATIC_STANDARD_WEIGHT" ){ DEV_SETTING_STATIC_STANDARD_WEIGHT = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_DYNAMIC_BASE_WEIGHT"    ){ DEV_SETTING_DYNAMIC_BASE_WEIGHT    = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_REF_VOLTAGE"            ){ DEV_SETTING_REF_VOLTAGE            = value.toInt()                                    ;}
            else if(key == "DEV_SETTING_WC_GRAPH_POINT_CNT"     ){ DEV_SETTING_WC_GRAPH_POINT_CNT     = value.toInt()                                    ;}
            else if(key == "DEV_SETTING_DETECT_MODE"            ){ DEV_SETTING_DETECT_MODE            = (EnumDef::eSensorMode)value.toUInt()             ;}
            else if(key == "DEV_SETTING_DETECT_DETECT_TIME"     ){ DEV_SETTING_DETECT_DETECT_TIME     = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_RUN_DETECT_TIME"        ){ DEV_SETTING_RUN_DETECT_TIME        = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_SIGNAL_DELAY_TIME"      ){ DEV_SETTING_SIGNAL_DELAY_TIME      = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_MD_PHOTO_IS_ON"         ){ DEV_SETTING_MD_PHOTO_IS_ON         = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_SENSOR_CNT"             ){ DEV_SETTING_SENSOR_CNT             = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_SENSOR_LEN"             ){ DEV_SETTING_SENSOR_LEN             = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_DIST_BTW_SENSOR"        ){ DEV_SETTING_DIST_BTW_SENSOR        = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_DIST_TO_WC"             ){ DEV_SETTING_DIST_TO_WC             = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_DIST_TO_PHOTO_SENSOR"   ){ DEV_SETTING_DIST_TO_PHOTO_SENSOR   = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_DIST_TO_SORTER_01"      ){ DEV_SETTING_DIST_TO_SORTER_01      = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_DIST_TO_SORTER_02"      ){ DEV_SETTING_DIST_TO_SORTER_02      = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_DIST_TO_SORTER_03"      ){ DEV_SETTING_DIST_TO_SORTER_03      = value.toUInt()                                   ;}
            else if(key == "DEV_SETTING_DIST_TO_SORTER_04"      ){ DEV_SETTING_DIST_TO_SORTER_04      = value.toUInt()                                   ;}
            else if(key == "HMI_SETTING_SW_POWER_OFF"           ){ HMI_SETTING_SW_POWER_OFF           = value.toUInt() == 1 ? true : false               ;}
            else if(key == "HMI_SETTING_IS_DAY_MODE"            ){ HMI_SETTING_IS_DAY_MODE            = value.toUInt() == 1 ? true : false               ;}
            else if(key == "HMI_SETTING_IS_DEBUG_MODE"          ){ HMI_SETTING_IS_DEBUG_MODE          = value.toUInt() == 1 ? true : false               ;}
            else if(key == "HMI_SETTING_SAMPLE_SENSTIVITY_01"   ){ HMI_SETTING_SAMPLE_SENSTIVITY_01   = value.toUInt()                                   ;}
            else if(key == "HMI_SETTING_SAMPLE_SENSTIVITY_02"   ){ HMI_SETTING_SAMPLE_SENSTIVITY_02   = value.toUInt()                                   ;}
            else if(key == "HMI_SETTING_SAMPLE_SENSTIVITY_03"   ){ HMI_SETTING_SAMPLE_SENSTIVITY_03   = value.toUInt()                                   ;}
            else if(key == "HMI_SETTING_SAMPLE_SENSTIVITY_04"   ){ HMI_SETTING_SAMPLE_SENSTIVITY_04   = value.toUInt()                                   ;}
            else if(key == "HMI_SETTING_SAMPLE_SENSTIVITY_05"   ){ HMI_SETTING_SAMPLE_SENSTIVITY_05   = value.toUInt()                                   ;}
            else if(key == "PD_DEFAULT_SETTING_FILTER_COEFFICIENT"){ PD_DEFAULT_SETTING_FILTER_COEFFICIENT = value.toUInt()                              ;}
            else if(key == "PD_DEFAULT_SETTING_MEASURE_CUE_SIGN  "){ PD_DEFAULT_SETTING_MEASURE_CUE_SIGN   = value.toUInt()                              ;}
            else if(key == "PD_DEFAULT_SETTING_MEASURE_SECTION   "){ PD_DEFAULT_SETTING_MEASURE_SECTION    = value.toUInt()                              ;}
            else if(key == "ETC_SETTING_MAX_ERROR"              ){ ETC_SETTING_MAX_ERROR              = value.toUInt()                                   ;}
            else if(key == "ETC_SETTING_MDCHECKUP_NEXT_STEP_WAIT_MSEC"){ ETC_SETTING_MDCHECKUP_NEXT_STEP_WAIT_MSEC = value.toInt()                       ;}
            else if(key == "RTU_MODBUS_PORT"                    ){ RTU_MODBUS_PORT                    = value                                            ;}
            else if(key == "RTU_MODBUS_PARITY"                  ){ RTU_MODBUS_PARITY                  = (QSerialPort::Parity  )value.toInt()             ;}
            else if(key == "RTU_MODBUS_BAUDRATE"                ){ RTU_MODBUS_BAUDRATE                = (QSerialPort::BaudRate)value.toInt()             ;}
            else if(key == "RTU_MODBUS_DATABITS"                ){ RTU_MODBUS_DATABITS                = (QSerialPort::DataBits)value.toInt()             ;}
            else if(key == "RTU_MODBUS_STOPBITS"                ){ RTU_MODBUS_STOPBITS                = (QSerialPort::StopBits)value.toInt()             ;}
            else if(key == "PRINTER_IS_USE"                     ){ PRINTER_IS_USE                     = value.toUInt() == 1 ? true : false               ;}
            else if(key == "PRINTER_PORT"                       ){ PRINTER_PORT                       = value                                            ;}
            else if(key == "PRINTER_BAUDRATE"                   ){ PRINTER_BAUDRATE                   = (QSerialPort::BaudRate  )value.toInt()           ;}
            else if(key == "PRINTER_DATABITS"                   ){ PRINTER_DATABITS                   = (QSerialPort::DataBits)value.toInt()             ;}
            else if(key == "PRINTER_STOPBITS"                   ){ PRINTER_STOPBITS                   = (QSerialPort::StopBits)value.toInt()             ;}
            else if(key == "PRINTER_PARITY"                     ){ PRINTER_PARITY                     = (QSerialPort::Parity)value.toInt()               ;}
            else if(key == "PRINTER_INCLUDE_BLANK_LINE"         ){ PRINTER_INCLUDE_BLANK_LINE         = value.toUInt() == 1 ? true : false               ;}
            else if(key == "PRINTER_INCLUDE_DIVIDER"            ){ PRINTER_INCLUDE_DIVIDER            = value.toUInt() == 1 ? true : false               ;}
            else if(key == "VNC_VIEW_IP"                        ){ VNC_VIEW_IP                        = value                                            ;}
            else if(key == "CCP_SERVER_IS_USE"                  ){ CCP_SERVER_IS_USE                  = value.toUInt() == 1 ? true : false               ;}
            else if(key == "CCP_SERVER_URL"                     ){ CCP_SERVER_URL                     = value                                            ;}
            else if(key == "ADC_AUTOCALIB_IS_USE"               ){ ADC_AUTOCALIB_IS_USE               = value.toInt()  == 1 ? true : false               ;}
            else if(key == "ADC_AUTOCALIB_MIN_ADC"              ){ ADC_AUTOCALIB_MIN_ADC              = value.toInt()                                    ;}
            else if(key == "ADC_AUTOCALIB_MAX_ADC"              ){ ADC_AUTOCALIB_MAX_ADC              = value.toInt()                                    ;}
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
