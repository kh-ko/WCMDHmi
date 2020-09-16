#ifndef CORESERVICE_H
#define CORESERVICE_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QDateTime>

#include "source/globaldef/EnumDefine.h"
#include "source/globaldef/GlobalDefine.h"
#include "source/util/fileloaderthread.h"
#include "source/model/dspstatusmodel.h"
#include "source/service/localsettingservice.h"
#include "source/service/productsettingservice.h"
#include "source/service/dspconnectioninfoservice.h"
#include "source/service/eventservice.h"
#include "source/thread/dsp/dspcommunitythread.h"

class CoreService : public QObject
{
    Q_OBJECT
public:
    static CoreService *mpSelf;
    static CoreService * getInstance();

private:
    QTimer mTimer;

public:
    QMap<quint64, DspStatusModel *> mMapDspStatus;
    LocalSettingService         mLocalSettingService;
    ProductSettingService       mProductSettingServcie;
    DspConnectionInfoService    mDspConnectionInfoService;
    EventService                mEventService;
    FileLoaderThread            mWorkingHistoryLoader;
    DspCommunityThread          mDspCommunityThread;

    QString mClock              = "";
    int     mState              = EnumDefine::ServiceState::SERVICE_INIT;
    int     mFactoryResetState  = EnumDefine::FactoryResetState::FACTORYRESET_NONE;

    void setClock            (QString value);
    void setState            (int     value);
    void setFactoryResetState(int     value);

    void onCommandStart();
    void onCommandFactoryReset();
    void onCommandHistoryReset();
    void onCommandWorkReset();

    int  onCommandAddDSP                            (quint64 *outSeq, QString ip, quint16 port);
    int  onCommandRemoveDsp                         (quint64  dspSeq                          );
    int  onCommandModifyDSP                         (quint64  dspSeq, QString ip, quint16 port);
    void onCommandSendZeroCmd                       (quint64  dspSeq                         );
    void onCommandSendWeightCaribCmd                (quint64  dspSeq, quint16 value          );
    void onCommandSendRunCmd                        (quint64  dspSeq, quint16 value          );
    void onCommandSendWeightCheckerGraphOnCmd       (quint64  dspSeq, bool value             );
    void onCommandSendMetalDetectorGraphOnCmd       (quint64  dspSeq, bool value             );
    void onCommandSendDeviceIDCmd                   (quint64  dspSeq, quint32 value          );
    void onCommandEditDspSetting                    (quint32 lampTime               ,
                                                     quint32 buzzerTime             ,
                                                     quint32 speedConverter         ,
                                                     quint16 motorDirection         ,
                                                     quint16 sensorLength           ,
                                                     quint16 distanceToRejector     ,
                                                     bool    mdPhotoIsOn            ,
                                                     bool    wcPhotoIsOn            ,
                                                     quint32 rejectorReadyTime      ,
                                                     quint32 rejectorRunTimeRatio   ,
                                                     quint32 staticFactor           ,
                                                     quint32 scaler                 ,
                                                     quint32 displayStability       ,
                                                     quint32 measureCueSign         ,
                                                     quint32 minStaticWeight        ,
                                                     quint32 minDynamicWeight       ,
                                                     quint16 mode                   ,
                                                     quint16 distanceBtwSensor      ,
                                                     quint32 detectDetectTime       ,
                                                     quint32 runDetectTime          ,
                                                     quint16 distanceToWeightChecker,
                                                     quint16 distancePhotoToSensor  ,
                                                     quint32 signalDelayTime        ,
                                                     quint32 staticStandardWeight   ,
                                                     quint32 dynamicBaseWeight      ,
                                                     quint16 sensorCnt              );
    int  onCommandAddProductSetting                 (quint64 *outSeq              ,
                                                     quint16 no                   ,
                                                     QString name                 ,
                                                     quint16 length               ,
                                                     quint16 speed                ,
                                                     quint32 motorAccelerationTime,
                                                     quint32 underWeight          ,
                                                     quint32 underWarningWeight   ,
                                                     quint32 normalWeight         ,
                                                     quint32 overWarningWeight    ,
                                                     quint32 overWeight           ,
                                                     quint32 tareWeight           ,
                                                     quint16 wcNGMotion           ,
                                                     quint32 dynamicFactor        ,
                                                     quint16 mdSenstivity         ,
                                                     quint16 mdNGMotion           );
    int  onCommandRemoveProductSetting              (quint64 seq                  );
    int  onCommandEditProductSetting                (quint64 seq                  ,
                                                     quint16 no                   ,
                                                     QString name                 ,
                                                     quint16 length               ,
                                                     quint16 speed                ,
                                                     quint32 motorAccelerationTime,
                                                     quint32 underWeight          ,
                                                     quint32 underWarningWeight   ,
                                                     quint32 normalWeight         ,
                                                     quint32 overWarningWeight    ,
                                                     quint32 overWeight           ,
                                                     quint32 tareWeight           ,
                                                     quint16 wcNGMotion           ,
                                                     quint32 dynamicFactor        ,
                                                     quint16 mdSenstivity         ,
                                                     quint16 mdNGMotion           );
    int  onCommandSelectProductSetting               (quint64 seq                 );
signals:
    void signalEventChangedClock            (QString value);
    void signalEventChangedState            (int value    );
    void signalEventChangedFactoryResetState(int value    );
    void signalEventAddedWeightCheckerGraph (quint64 dspSeq, WeightGraphDto    value);
    void signalEventAddedMetalDetectorGraph (quint64 dspSeq, MetalGraphDto     value);

// down layer
signals:
    void signalCommandDspCommunityStop              (                          );
    void signalCommandAddDSP(DspConnectionDto con, DspSettingDto ds, ProductSettingDto ps);
    void signalCommandRemoveDsp                     (quint64 dspSeq                         );
    void signalCommandModifyDSP                     (DspConnectionDto value                 );
    void signalCommandSendZeroCmd                   (quint64 dspSeq                         );
    void signalCommandSendFactoryResetCmd           (quint64 dspSeq                         );
    void signalCommandSendWeightCaribCmd            (quint64 dspSeq, quint16 value          );
    void signalCommandSendRunCmd                    (quint64 dspSeq, quint16 value          );
    void signalCommandSendWeightCheckerGraphOnCmd   (quint64 dspSeq, bool value             );
    void signalCommandSendMetalDetectorGraphOnCmd   (quint64 dspSeq, bool value             );
    void signalCommandSendDeviceIDCmd               (quint64 dspSeq, quint32 value          );
    void signalCommandSendDspSetting                (quint64 dspSeq, DspSettingDto value    );
    void signalCommandSendProductSetting            (quint64 dspSeq, ProductSettingDto value);

public slots:
    void onSignalCommandDspCommunityStop         (                           );
    void onSignalEventChangedIsConnect           (quint64, bool              );
    void onSignalEventChangedRemoteDeviceSetting (quint64 dspSeq, DspSettingDto     value);
    void onSignalEventChangedRemoteProductSetting(quint64 dspSeq, ProductSettingDto value);
    void onSignalEventChangedDeviceStatus        (quint64 dspSeq, DspStatusDto      value);
    void onSignalEventChangedDeviceInfo          (quint64 dspSeq, DspInfoDto        value);
    void onSignalEventAddedEvent                 (quint64 dspSeq, EventDto          value);
    void onSignalEventAddedWeightCheckerGraph    (quint64 dspSeq, WeightGraphDto    value);
    void onSignalEventAddedMetalDetectorGraph    (quint64 dspSeq, MetalGraphDto     value);
    void onSignalEventCompletedFactoryReset      (quint64 dspSeq                    );

//  internal layer ===================================================================================
signals:
    void signalCommandWorkingHistoryLoadLine (QString path, QString fileName, int lineCnt);

public slots:
    void onSignalEventCompleteLoadProductSetting();
    void onSignalEventCompleteLoadDspConnection();
    void onSignalEventLoadedLineWorkingHistory(QStringList lines);
    void onSignalEventEndOfLineWorkingHistory();
public:
    explicit CoreService(QObject *parent = nullptr);

public slots:
    void onUpdateTimer();

};

#endif // CORESERVICE_H
