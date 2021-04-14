#ifndef ENUMDEFINE_H
#define ENUMDEFINE_H

#include <QObject>
class QmlEnumDef: public QObject{
  Q_OBJECT
  Q_ENUMS(VInputMode)
  Q_ENUMS(LoggingDataMenu)
  Q_ENUMS(BackupResult)
  Q_ENUMS(PanelType)
  Q_ENUMS(ButtonType)
  Q_ENUMS(DeviceType)
  Q_ENUMS(MenuType)
  Q_ENUMS(MDGraphViewType)
  Q_ENUMS(MDCheckUpStep)
  Q_ENUMS(MDCheckUpState)
  Q_ENUMS(StaticCaribStep)
  Q_ENUMS(SearchFilter)
  Q_ENUMS(Company)


public:
  enum VInputMode{
      INT_MODE = 0,
      FLOAT_MODE = 1,
      PASSWD_MODE = 2,
      STRING_MODE = 3,
      IP_MODE = 4,
      S_INT_MODE = 5,
      S_FLOAT_MODE = 6
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
      BACKUP_UNKNOW_ERROR = 8,
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
      PANEL_TYPE_BIG_MD         = 9,
      PANEL_TYPE_NONE           = 10

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
      MENU_CHECK_UP        = 7,
      MENU_MAX_ERROR       = 8,
  };

  enum MDGraphViewType{
      MD_GRAPH_SMALL = 0,
      MD_GRAPH_ALONE = 1
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

  enum StaticCaribStep{
      STATIC_CARIB_STEP_INIT                = 0,
      STATIC_CARIB_STEP_STD_WEIGHT_CHECK    = 1,
      STATIC_CARIB_STEP_CARIB_READY         = 2,
      STATIC_CARIB_STEP_CARIB_ING           = 3,
      STATIC_CARIB_STEP_CARIB_COMPLETED     = 4,
      STATIC_CARIB_STEP_CARIB_COMPLETED_ERR = 5
  };

  enum SearchFilter{
        SEARCH_FILTER_WITHOUT_TRADE = 0,
        SEARCH_FILTER_TOTAL         = 1
  };

  enum Company{
      COMPANY_NOVASEN = 0,
      COMPANY_DONGNAM = 1
  };
};

#endif // ENUMDEFINE_H
