#ifndef ENUMDEF_H
#define ENUMDEF_H
#include <QObject>

class EnumDef: public QObject{
    Q_OBJECT
    Q_ENUMS(eCompany)
    Q_ENUMS(eDspFRState)
    Q_ENUMS(eLang)
    Q_ENUMS(eViewMode)
    Q_ENUMS(eTrendsGraphOptionH)
    Q_ENUMS(eTrendsGraphOptionFilter)
    Q_ENUMS(eTrendsGraphOptionLastN)
    Q_ENUMS(eMotorDirection)
    Q_ENUMS(eMotorType)
    Q_ENUMS(eMachineMode)
    Q_ENUMS(eSensorMode)
    Q_ENUMS(ePDError)
    Q_ENUMS(eEventType)
    Q_ENUMS(eNGMotion)
    Q_ENUMS(eRunMode)
    Q_ENUMS(eWCGPointType)
    Q_ENUMS(eWCCalibType)
    Q_ENUMS(ePDSortMode)

public:
    enum eCompany{
        COMPANY_NOVASEN = 0,
        COMPANY_DONGNAM = 1,
        COMPANY_SOLURAY = 2,
    };

    enum eDspFRState {
        DSP_FR_STATE_NONE  = 0,
        DSP_FR_STATE_FAIL  = 1,
        DSP_FR_STATE_SUCC  = 2
    };

    enum eLang{
        LANG_ENG = 0,
        LANG_KOR = 1,
        LANG_CHN = 2,
    };

    enum eViewMode{
        WC_VIEWMODE_CURRENT = 0,
        WC_VIEWMODE_TRENDS  = 1,
        WC_VIEWMODE_DELTA   = 2,
    };

    enum eTrendsGraphOptionH
    {
        TRENDSOPTION_H_UNDER_TO_OVER = 0,
        TRENDSOPTION_H_MIN_TO_MAX = 1
    };

    enum eTrendsGraphOptionFilter
    {
        TRENDSOPTION_FILTER_TOTAL = 0,
        TRENDSOPTION_FILTER_TRADE = 1
    };

    enum eTrendsGraphOptionLastN
    {
        TRENDSOPTION_TOTAL_SINCE_START = 0,
        TRENDSOPTION_LAST_N = 1
    };

    enum eMotorDirection{
        MOTOR_DIRECTION_RIGHT_TO_LEFT = 0,
        MOTOR_DIRECTION_LEFT_TO_RIGHT = 1,
    };

    enum eMotorType{
        MOTORTYPE_MOTOR_MITSUBISHI = 0,
        MOTORTYPE_MOTOR_BLDC       = 1,
        MOTORTYPE_MOTOR_SCHNEIDER  = 2,
        MOTORTYPE_MOTOR_BLDC_R     = 3,
        MOTORTYPE_MOTOR_NONE       = 4,
    };

    enum eMachineMode{
        MACHINE_MODE_ALU   = 1,
        MACHINE_MODE_WC    = 2,
        MACHINE_MODE_COMBI = 3
    };

    enum eSensorMode{
      SENS_MODE_INDEPENDENT = 0,
      SENS_MODE_NOISE_REDUCTION_MODE = 1,
      SENS_MODE_EACH = 2
    };

    enum ePDError{
        PDERR_NONE          = 0,
        PDERR_FILE_WRITE    = 1,
        PDERR_NOT_EXIST     = 2,
        PDERR_SAME_PD_NUM   = 3,
        PDERR_SELECTED      = 9,
    };

    enum eEventType
    {
        ET_NONE                         = -1,
        ET_WEIGHT_NORMAL                = 0,
        ET_WEIGHT_UNDER_WARNING         = 1,
        ET_WEIGHT_OVER_WARNING          = 2,
        ET_WEIGHT_UNDER                 = 3,
        ET_WEIGHT_OVER                  = 4,
        ET_WEIGHT_ETCERROR              = 5,
        ET_APP_START                    = 6,
        ET_APP_EXIT                     = 7,
        ET_METAL_CHECKUP                = 8,
        ET_WEIGHT_STATIC_CARI           = 9,
        ET_WEIGHT_DYNAMIC_CARI          = 10,
        ET_RUN                          = 11,
        ET_STOP                         = 12,
        ET_METAL_TRADE                  = 13,
        ET_METAL_DETECT                 = 14,
        ET_METAL_TRADE_CHECK            = 15,
        ET_METAL_DETECT_CHECK           = 16,
        ET_WEIGHT_NORMAL_CHECK          = 17,
        ET_WEIGHT_UNDER_WARNING_CHECK   = 18,
        ET_WEIGHT_OVER_WARNING_CHECK    = 19,
        ET_WEIGHT_UNDER_CHECK           = 20,
        ET_WEIGHT_OVER_CHECK            = 21,
        ET_WEIGHT_ETCERROR_CHECK        = 22,
        ET_WEIGHT_ETC_METAL_ERROR       = 23,
        ET_WEIGHT_ETC_METAL_ERROR_CHECK = 24,
        ET_WEIGHT_REF_VOLTAGE           = 25,
        ET_METAL_DETECT_2               = 26,
    };

    enum eNGMotion{
        NG_MOTION_NON = 0,
        NG_MOTION_STOP = 1,
        NG_MOTION_SORTER_01 = 2,
        NG_MOTION_SORTER_02 = 3,
        NG_MOTION_SORTER_03 = 4,
        NG_MOTION_SORTER_04 = 5,
    };

    enum eRunMode{
        RUN_MODE_STOP = 0,
        RUN_MODE_RUN = 1,
        RUN_MODE_CHECKUP_RUN = 2,
        RUN_MODE_DETECT_OFF_RUN = 3,
        RUN_MODE_ALRAM_RESET = 4
    };

    enum eWCGPointType{
          WCG_POINT_TYPE_POINT = 0,
          WCG_POINT_TYPE_IN_PORTER_ON = 1,
          WCG_POINT_TYPE_IN_PORTER_OFF = 2,
          WCG_POINT_TYPE_MEASURE_START = 3,
          WCG_POINT_TYPE_MEASURE_END = 4,
          WCG_POINT_TYPE_OUT_PORTER_ON = 5,
          WCG_POINT_TYPE_OUT_PORTER_OFF = 6,
    };

    enum eWCCalibType{
            WC_CALIB_TYPE_STATIC = 0,
            WC_CALIB_TYPE_DYNAMIC = 1
    };

    enum ePDSortMode{
        PD_SORT_NAME  = 0,
        PD_SORT_NUM   = 1,
    };

};
#endif // ENUMDEF_H
