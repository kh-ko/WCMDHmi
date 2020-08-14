#ifndef ENUMDEFINE_H
#define ENUMDEFINE_H

#include <QObject>
class EnumDefine: public QObject{
  Q_OBJECT
  Q_ENUMS(Language)
  Q_ENUMS(RunState)
  Q_ENUMS(AlarmState)
  Q_ENUMS(CommState)
  Q_ENUMS(SensorMode)
  Q_ENUMS(DataContinueMode)
  Q_ENUMS(OS)
  Q_ENUMS(VInputMode)
  Q_ENUMS(NGMotion)
  Q_ENUMS(ConnectionType)
  Q_ENUMS(PacketCmd)
  Q_ENUMS(EventType)
  Q_ENUMS(WeightErrorType)
  Q_ENUMS(WeightAvgErrorType)
  Q_ENUMS(MetalErrorType)
  Q_ENUMS(TrendsGraphOptionH)
  Q_ENUMS(TrendsGraphOptionFilter)
  Q_ENUMS(TrendsGraphOptionLastN)
  Q_ENUMS(DataBaseWriteMode)
  Q_ENUMS(DatabaseErrorType)
  Q_ENUMS(SearchOption)
  Q_ENUMS(SearchFilter)
  Q_ENUMS(LoggingDataMenu)
  Q_ENUMS(BackupResult)
  Q_ENUMS(AlarmType)
  Q_ENUMS(WCGraphPointType)
  Q_ENUMS(ResetState)
  Q_ENUMS(PanelType)
  Q_ENUMS(ButtonType)
  Q_ENUMS(DeviceType)
  Q_ENUMS(MenuType)
  Q_ENUMS(MDGraphViewType)
  Q_ENUMS(MOTOR_DIRECTION)
  Q_ENUMS(RUN_MODE)
  Q_ENUMS(MDCheckUpStep)
  Q_ENUMS(MDCheckUpState)
  Q_ENUMS(WCCalibType)
  Q_ENUMS(WCViewMode)
  Q_ENUMS(UserLevel)
  Q_ENUMS(Company)


public:

  enum Language{
    ENG = 0,
    KOR = 1
  };

  enum RunState{
    STOP = 0,
    RUN = 1,
    CHECKUP_RUN = 2,
    DETECT_OFF_RUN = 3
  };

  enum AlarmState{
    ALARM_CLEAR = 0,
    ALARM = 1
  };

  enum CommState{
    COMM_FULL_CONNECT = 0,
    COMM_PARTIAL_CONNECT = 1,
    COMM_ERROR = 2
  };

  enum OS{
    WIN = 0,
    RASPBERRYPI = 1
  };

  enum SensorMode{
    INDEPENDENT = 0,
    NOISE_REDUCTION_MODE = 1,
    PARALLEL = 2
  };

  enum DataContinueMode{
      PROG_STARTSTOP = 0,
      DAY = 1
  };

  enum VInputMode{
      INT_MODE = 0,
      FLOAT_MODE = 1,
      PASSWD_MODE = 2,
      STRING_MODE = 3,
      IP_MODE = 4,
  };

  enum NGMotion{
      NG_MOTION_NON = 0,
      NG_MOTION_STOP = 1,
      NG_MOTION_REJECT_01 = 2,
      NG_MOTION_REJECT_02 = 3,
  };

  enum ConnectionType{
      WeightCheckerConnection = 0,
      MetalDetectorConnection = 1
  };

  enum GraphState
  {
      GRAPH_OFF = 0,
      GRAPH_ON = 1
  };

  enum FuncCode{
      READ_TYPE = 3,
      WRITE_TYPE = 16,
      NOTI_TYPE = 17,
      ERROR_ACK_TYPE = 18
  };

  enum WeightCheckerNGType
  {
      WEIGHT_NONE = 0,
      WEIGHT_NORMAL = 1,
      WEIGHT_UNDER_WARNING = 2,
      WEIGHT_OVER_WARNING = 3,
      WEIGHT_UNDER = 4,
      WEIGHT_OVER = 5,
      WEIGHT_LENGTH_CHECK = 6,
      WEIGHT_DISTANCE_CHECK = 7,
      WEIGHT_METAL_DETECT = 8
  };

  enum MetalDetectorResultType
  {
      METEAL_NONE = 0,
      METEAL_TRADE = 1,
      METEAL_DETECT = 2
  };

  enum DbHelperClient
  {
      DBCLIENT_QML = 0,
      DBCLIENT_MAINSERVICE = 1,
      DBCLIENT_ONETIME = 2,
      DBCLIENT_MAX = 3
  };

  enum EventType
  {
      EVENT_NONE_TYPE                   = -1,
      WEIGHT_NORMAL_TYPE                = 0,
      WEIGHT_UNDER_WARNING_TYPE         = 1,
      WEIGHT_OVER_WARNING_TYPE          = 2,
      WEIGHT_UNDER_TYPE                 = 3,
      WEIGHT_OVER_TYPE                  = 4,
      WEIGHT_ETCERROR_TYPE              = 5,
      APP_START_TYPE                    = 6,
      APP_EXIT_TYPE                     = 7,
      METAL_CHECKUP_TYPE                = 8,
      WEIGHT_STATIC_CARI_TYPE           = 9,
      WEIGHT_DYNAMIC_CARI_TYPE          = 10,
      RUN_TYPE                          = 11,
      STOP_TYPE                         = 12,
      METAL_TRADE_TYPE                  = 13,
      METAL_DETECT_TYPE                 = 14,
      METAL_TRADE_CHECK_TYPE            = 15,
      METAL_DETECT_CHECK_TYPE           = 16,
      WEIGHT_NORMAL_CHECK_TYPE          = 17,
      WEIGHT_UNDER_WARNING_CHECK_TYPE   = 18,
      WEIGHT_OVER_WARNING_CHECK_TYPE    = 19,
      WEIGHT_UNDER_CHECK_TYPE           = 20,
      WEIGHT_OVER_CHECK_TYPE            = 21,
      WEIGHT_ETCERROR_CHECK_TYPE        = 22,
      WEIGHT_ETC_METAL_ERROR_TYPE       = 23
  };

  enum WeightErrorType
  {
      WEIGHT_ERROR_NONE = 0,
      WEIGHT_ERROR_UNDERWARNING = 1,
      WEIGHT_ERROR_OVERWARNING = 2,
      WEIGHT_ERROR_UNDER = 3,
      WEIGHT_ERROR_OVER = 4,
      WEIGHT_ERROR_ETC = 5
  };

  enum WeightAvgErrorType
  {
      WEIGHT_AVG_ERROR_NONE = 0,
      WEIGHT_AVG_ERROR_UNDERWARNING = 1,
      WEIGHT_AVG_ERROR_OVERWARNING = 2,
      WEIGHT_AVG_ERROR_UNDER = 3,
      WEIGHT_AVG_ERROR_OVER = 4,
  };

  enum MetalErrorType
  {
      METAL_ERROR_NONE = 10,
      METAL_ERROR_DETECT = 11
  };

  enum TrendsGraphOptionH
  {
      TRENDSOPTION_H_UNDER_TO_OVER = 0,
      TRENDSOPTION_H_MIN_TO_MAX = 1
  };

  enum TrendsGraphOptionFilter
  {
      TRENDSOPTION_FILTER_TOTAL = 0,
      TRENDSOPTION_FILTER_TRADE = 1
  };

  enum TrendsGraphOptionLastN
  {
      TRENDSOPTION_TOTAL_SINCE_START = 0,
      TRENDSOPTION_LAST_N = 1
  };

  enum DataBaseWriteMode
  {
      ADD = 0,
      EDIT = 1,
      REMOVE = 2
  };

  enum DatabaseErrorType
  {
      DB_NONE_ERROR = 0,
      SQL_ERROR = 1,
      NOT_EXIST_SEQ = 2,
      ALREADY_NO_ERROR = 3,
      EMPTY_PRODUCT_NO = 4,
      ZERO_PRODUCT_LENGTH = 5,
      ZERO_PRODUCT_SEPPD = 6,
      INVAILD_WEIGHT_CHECKER_SETTING = 7,
      INVAILD_METAL_DETECTOR_SETTING = 8,
      REMOVE_SEL_PRODUCT = 9,
      PASSWORD_ERROR = 10
  };

  enum SearchOption
  {
      SEARCH_OPTION_TODAY = 0,
      SEARCH_OPTION_PERIOD = 1
  };

  enum SearchFilter
  {
      SEARCH_FILTER_WITHOUT_TRADE = 0,
      SEARCH_FILTER_TOTAL = 1
  };

  enum LoggingDataMenu{
      LOGGING_WEIGHT = 0,
      LOGGING_METAL = 1
  };

  enum BackupResult{
      BACKUP_NONE_ERROR = 0,
      USB_ERROR = 1,
      WRITE_ERROR = 2,
      READ_ERROR = 3,
      ETC_ERROR = 4,
      BACKUP_ING = 5,
      DB_OPEN_FAIL = 6,
      BACKUP_CANCLE = 7,
      BACKUP_UNKNOW_ERROR = 8
  };

  enum AlarmType{
      NONE_ALARM    = 0,
      SENSOR_ALARM  = 0x0001,
      PHOTO_ALARM   = 0x0002,
      MOTOR_ALARM   = 0x0004
  };

  enum WCGraphPointType{
      WCGRAPH_NORMAL_POINT = 0,
      WCGRAPH_NORMAL_IN_PORTER_ON = 1,
      WCGRAPH_NORMAL_IN_PORTER_OFF = 2,
      WCGRAPH_NORMAL_MEASURE_START = 3,
      WCGRAPH_NORMAL_MEASURE_END = 4,
      WCGRAPH_NORMAL_OUT_PORTER_ON = 5,
      WCGRAPH_NORMAL_OUT_PORTER_OFF = 6,
  };

  enum ResetState{
      RESET_NONE = 0,
      RESET_ING  = 1,
      RESET_COMPLETED = 2
  };

  enum PanelType{
      PANEL_TYPE_DEFAULT        = 0,
      PANEL_TYPE_UP_PANEL       = 1,
      PANEL_TYPE_METAL          = 2,
      PANEL_TYPE_WEIGHT         = 3,
      PANEL_TYPE_SELECT         = 4,
      PANEL_TYPE_DROP_SELECT    = 5,
      PANEL_TYPE_DROP           = 6,
      PANEL_TYPE_POPUP          = 7,
      PANEL_TYPE_WEIGHT_UP      = 8,
      PANEL_TYPE_NONE           = 9

  };

  enum ButtonType{
      BUTTON_TYPE_DEFAULT       = 0,
      BUTTON_TYPE_UP_PANEL      = 1,
      BUTTON_TYPE_POPUP         = 2,
      BUTTON_TYPE_BLUE          = 3,
      BUTTON_TYPE_METAL         = 4,
  };

  enum DeviceType{
      DEVICE_METAL_DETECTOR = 0,
      DEVICE_WEIGHT_CHECKER = 1
  };

  enum MenuType{
      MENU_PRODUCT_SETTING = 0,
      MENU_LOGGING_DATA    = 1,
      MENU_DEVICE_SETTING  = 2,
      MENU_INFORMATION     = 3,
      MENU_GRAPH           = 4,
      MENU_ETC_SETTING     = 5,
      MENU_CLOCK_SETTING   = 6,
      MENU_CHECK_UP        = 7
  };

  enum MDGraphViewType{
      MD_GRAPH_SMALL = 0,
      MD_GRAPH_ALONE = 1
  };

  enum MOTOR_DIRECTION{
      MOTOR_DIRECTION_RIGHT_TO_LEFT = 0,
      MOTOR_DIRECTION_LEFT_TO_RIGHT = 1,
  };

  enum RUN_MODE{
      RUN_MODE_MONITOR      = 0,
      RUN_MODE_CHECKUP      = 1,
      RUN_MODE_EVENT_OFF    = 2
  };

  enum MDCheckUpStep{
      CHECKUP_STEP_INIT   = 0,
      CHECKUP_FE_STEP01   = 1,
      CHECKUP_FE_STEP02   = 2,
      CHECKUP_FE_STEP03   = 3,
      CHECKUP_SUS_STEP01  = 4,
      CHECKUP_SUS_STEP02  = 5,
      CHECKUP_SUS_STEP03  = 6,
      CHECKUP_RESULT_STEP = 7,
  };

  enum MDCheckUpState{
      CHECKUP_INIT = 0,
      CHECKUP_CHECKING = 1,
      CHECKUP_PASS = 2,
      CHECKUP_FAIL = 3,

  };

  enum WCCalibType{
      WC_CALIB_STATIC = 0,
      WC_CALIB_DYNAMIC = 1,
  };

  enum WCViewMode{
      WC_VIEWMODE_CURRENT = 0,
      WC_VIEWMODE_TRENDS  = 1,
      WC_VIEWMODE_DELTA   = 2,
  };

  enum UserLevel{
      USER_NORMAL =0,
      USER_ADMIN = 1,
      USER_SUPER = 2
  };

  enum Company{
      COMPANY_NOVASEN = 0,
      COMPANY_DONGNAM = 1
  };
};

#endif // ENUMDEFINE_H
