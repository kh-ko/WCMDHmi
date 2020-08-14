#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QMap>

#include "source/globaldef/GlobalDefine.h"
#include "source/globaldef/EnumDefine.h"
#include "source/model/devicesetting.h"
#include "source/model/productsetting.h"
#include "source/model/devicestatus.h"
#include "source/model/deviceinfo.h"
#include "source/model/Information.h"
#include "source/model/eventinfo.h"
#include "source/model/weightcheckergraphdata.h"
#include "source/model/metaldetectorgraphdata.h"
#include "source/model/productstatus.h"

class DSPManager : public QObject
{
    Q_OBJECT
public:
    bool                    mIsDelete                       =false                                  ;
    bool                    mIsConnect                      =true                                   ;
    bool                    mIsDeviceSettingAlarm           =false                                  ;
    bool                    mIsProductSettingAlarm          =false                                  ;
    quint16                 mWait                           =0                                      ;
    EnumDefine::RunState    mRun                            =EnumDefine::RunState::STOP             ;
    bool                    mIsWeightCheckerGraphOn         =false                                  ;
    bool                    mIsMetalDetectorGraphOn         =false                                  ;
    bool                    mIsMetalDetectorFilterGraphOn   =false                                  ;
    EnumDefine::AlarmType   mWCAlarm                        =EnumDefine::AlarmType::NONE_ALARM      ;
    quint32                 mWCCurrWeight                   =0.0f                                   ;
    quint32                 mLastMeasuredWeight             =0.0f                                   ;
    EnumDefine::EventType   mWCCurrEventType                = EnumDefine::EventType::EVENT_NONE_TYPE;
    EnumDefine::AlarmType   mMDAlarm                        =EnumDefine::AlarmType::NONE_ALARM;
    quint16                 mMDCurrSignal                   = 0                                     ;
    EnumDefine::EventType   mMDCurrEventType                = EnumDefine::EventType::EVENT_NONE_TYPE;

    quint32                 mDeviceID                       = 0                                     ;
    quint16                 mMajorVersion                   = 0                                     ;
    quint16                 mMinorVersion                   = 0                                     ;
    quint16                 mMaintenanceVersion             = 0                                     ;

    DeviceSetting           mDeviceSetting;
    ProductSetting          mSelectedProductSetting;
    DeviceSetting           mRemoteDeviceSetting;
    ProductSetting          mRemoteProductSetting;
    QMap<quint16, ProductStatus *>   mListProductStatus     ;

    explicit DSPManager              (DeviceSetting ds, ProductSetting ps, QObject *parent = nullptr);
    void reset                       (DeviceSetting ds, ProductSetting ps)                           ;
    void resetStatistics             ()                                                              ;
    void setIsConnect                (bool value)                                                    ;
    void setRemoteDeviceSetting      (DeviceSetting ds)                                              ;
    void setRemoteProductSetting     (ProductSetting ps)                                             ;
    void setDeviceStatus             (DeviceStatus value)                                            ;
    void setDeviceInfo               (DeviceInfo value)                                              ;
    void addEvent                    (quint16 productSeq, EventInfo value)                           ;
    void startFactorReset            ()                                                              ;
    void endFactorReset              ()                                                              ;

    void setProductSetting           (ProductSetting value)                                          ;
    void setDeviceSetting            (DeviceSetting value)                                           ;

};

#endif // DEVICEMANAGER_H
