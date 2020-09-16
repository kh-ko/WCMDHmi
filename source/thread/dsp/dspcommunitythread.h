#ifndef DSPSERVICE_H
#define DSPSERVICE_H

#include <QObject>
#include <QTimer>
#include <QThread>

#include "source/globaldef/EnumDefine.h"
#include "source/globaldef/GlobalDefine.h"
#include "source/thread/dsp/dspinterface.h"
#include "source/util/myalloc.h"

class DspCommunityThreadWorker : public QObject
{
    Q_OBJECT
private:
    QThread mThread;
    QTimer* mpTimer = nullptr;
    QList<DSPInterface *> mListDSPInterface;
    bool    mIsStop = false;
    MyAlloc mMyAlloc;

signals:
    void signalEventStarted                         (                                           );
    void signalEventStopped                         (                                           );
    void signalEventChangedIsConnect                (quint64 deviceSeq, bool value              );
    void signalEventCompletedFactoryReset           (quint64 deviceSeq                          );
    void signalEventChangedRemoteDeviceSetting      (quint64 deviceSeq, DspSettingDto value     );
    void signalEventChangedRemoteProductSetting     (quint64 deviceSeq, ProductSettingDto value );
    void signalEventChangedDeviceStatus             (quint64 deviceSeq, DspStatusDto value      );
    void signalEventChangedDeviceInfo               (quint64 deviceSeq, DspInfoDto value        );
    void signalEventAddedEvent                      (quint64 deviceSeq, EventDto value          );
    void signalEventAddedWeightCheckerGraph         (quint64 deviceSeq, WeightGraphDto value    );
    void signalEventAddedMetalDetectorGraph         (quint64 deviceSeq, MetalGraphDto value     );

public slots:
    void onCommandStopService                       ();
    void onCommandAddDSP                            (DspConnectionDto connectionInfo, DspSettingDto ds, ProductSettingDto ps);
    void onCommandRemoveDsp                         (quint64 deviceSeq                         );
    void onCommandModifyDSP                         (DspConnectionDto connectionInfo           );
    void onCommandSendZeroCmd                       (quint64 deviceSeq                         );
    void onCommandSendFactoryResetCmd               (quint64 deviceSeq                         );
    void onCommandSendWeightCaribCmd                (quint64 deviceSeq, quint16 value          );
    void onCommandSendRunCmd                        (quint64 deviceSeq, quint16 value          );
    void onCommandSendWeightCheckerGraphOnCmd       (quint64 deviceSeq, bool value             );
    void onCommandSendMetalDetectorGraphOnCmd       (quint64 deviceSeq, bool value             );
    void onCommandSendDeviceIDCmd                   (quint64 deviceSeq, quint32 value          );
    void onCommandSendDspSetting                    (quint64 deviceSeq, DspSettingDto value    );
    void onCommandSendProductSetting                (quint64 deviceSeq, ProductSettingDto value);

// down layer =========================================
    void onSignalEventChangedIsConnect              (quint64 deviceSeq, bool value              );
    void onSignalEventCompletedFactoryReset         (quint64 deviceSeq                          );
    void onSignalEventChangedRemoteDeviceSetting    (quint64 deviceSeq, DspSettingDto value     );
    void onSignalEventChangedRemoteProductSetting   (quint64 deviceSeq, ProductSettingDto value );
    void onSignalEventChangedDeviceStatus           (quint64 deviceSeq, DspStatusDto value      );
    void onSignalEventChangedDeviceInfo             (quint64 deviceSeq, DspInfoDto value        );
    void onSignalEventAddedEvent                    (quint64 deviceSeq, EventDto value          );
    void onSignalEventAddedWeightCheckerGraph       (quint64 deviceSeq, WeightGraphDto value    );
    void onSignalEventAddedMetalDetectorGraph       (quint64 deviceSeq, MetalGraphDto value     );


// internal layer =========================================
public slots:
    void onStarted();
    void onTimeTick();

public:
    explicit DspCommunityThreadWorker(QObject *parent = nullptr);
    ~DspCommunityThreadWorker();
};

class DspCommunityThread : public QObject
{
    Q_OBJECT
public:
    DspCommunityThreadWorker * mpWorker;
    QThread mThread;

    explicit DspCommunityThread(QObject *parent = nullptr) : QObject(parent)
    {
        mpWorker = new DspCommunityThreadWorker;
        mpWorker->moveToThread(&mThread);

        connect(&mThread, &QThread::finished, mpWorker, &QObject::deleteLater);
        connect(&mThread, &QThread::started, mpWorker, &DspCommunityThreadWorker::onStarted);

        connect(mpWorker, SIGNAL(signalEventStarted                    (                           )), this, SLOT(onSignalEventStarted                         (                           )));
        connect(mpWorker, SIGNAL(signalEventStopped                    (                           )), this, SLOT(onSignalEventStopped                         (                           )));
        connect(mpWorker, SIGNAL(signalEventChangedIsConnect           (quint64, bool              )), this, SLOT(onSignalEventChangedIsConnect                (quint64, bool              )));
        connect(mpWorker, SIGNAL(signalEventCompletedFactoryReset      (quint64                    )), this, SLOT(onSignalEventCompletedFactoryReset           (quint64                    )));
        connect(mpWorker, SIGNAL(signalEventChangedRemoteDeviceSetting (quint64, DspSettingDto     )), this, SLOT(onSignalEventChangedRemoteDeviceSetting      (quint64, DspSettingDto     )));
        connect(mpWorker, SIGNAL(signalEventChangedRemoteProductSetting(quint64, ProductSettingDto )), this, SLOT(onSignalEventChangedRemoteProductSetting     (quint64, ProductSettingDto )));
        connect(mpWorker, SIGNAL(signalEventChangedDeviceStatus        (quint64, DspStatusDto      )), this, SLOT(onSignalEventChangedDeviceStatus             (quint64, DspStatusDto      )));
        connect(mpWorker, SIGNAL(signalEventChangedDeviceInfo          (quint64, DspInfoDto        )), this, SLOT(onSignalEventChangedDeviceInfo               (quint64, DspInfoDto        )));
        connect(mpWorker, SIGNAL(signalEventAddedEvent                 (quint64, EventDto          )), this, SLOT(onSignalEventAddedEvent                      (quint64, EventDto          )));
        connect(mpWorker, SIGNAL(signalEventAddedWeightCheckerGraph    (quint64, WeightGraphDto    )), this, SLOT(onSignalEventAddedWeightCheckerGraph         (quint64, WeightGraphDto    )));
        connect(mpWorker, SIGNAL(signalEventAddedMetalDetectorGraph    (quint64, MetalGraphDto     )), this, SLOT(onSignalEventAddedMetalDetectorGraph         (quint64, MetalGraphDto     )));

        connect(this, SIGNAL(signalCommandStopService                (                          )), mpWorker, SLOT(onCommandStopService                (                          )));
        connect(this, SIGNAL(signalCommandAddDSP                     (DspConnectionDto, DspSettingDto, ProductSettingDto)), mpWorker, SLOT(onCommandAddDSP(DspConnectionDto, DspSettingDto, ProductSettingDto)));
        connect(this, SIGNAL(signalCommandRemoveDsp                  (quint64                   )), mpWorker, SLOT(onCommandRemoveDsp                  (quint64                   )));
        connect(this, SIGNAL(signalCommandModifyDSP                  (DspConnectionDto          )), mpWorker, SLOT(onCommandModifyDSP                  (DspConnectionDto          )));
        connect(this, SIGNAL(signalCommandSendZeroCmd                (quint64                   )), mpWorker, SLOT(onCommandSendZeroCmd                (quint64                   )));
        connect(this, SIGNAL(signalCommandSendFactoryResetCmd        (quint64                   )), mpWorker, SLOT(onCommandSendFactoryResetCmd        (quint64                   )));
        connect(this, SIGNAL(signalCommandSendWeightCaribCmd         (quint64, quint16          )), mpWorker, SLOT(onCommandSendWeightCaribCmd         (quint64, quint16          )));
        connect(this, SIGNAL(signalCommandSendRunCmd                 (quint64, quint16          )), mpWorker, SLOT(onCommandSendRunCmd                 (quint64, quint16          )));
        connect(this, SIGNAL(signalCommandSendWeightCheckerGraphOnCmd(quint64, bool             )), mpWorker, SLOT(onCommandSendWeightCheckerGraphOnCmd(quint64, bool             )));
        connect(this, SIGNAL(signalCommandSendMetalDetectorGraphOnCmd(quint64, bool             )), mpWorker, SLOT(onCommandSendMetalDetectorGraphOnCmd(quint64, bool             )));
        connect(this, SIGNAL(signalCommandSendDeviceIDCmd            (quint64, quint32          )), mpWorker, SLOT(onCommandSendDeviceIDCmd            (quint64, quint32          )));
        connect(this, SIGNAL(signalCommandSendDspSetting             (quint64, DspSettingDto    )), mpWorker, SLOT(onCommandSendDspSetting             (quint64, DspSettingDto    )));
        connect(this, SIGNAL(signalCommandSendProductSetting         (quint64, ProductSettingDto)), mpWorker, SLOT(onCommandSendProductSetting         (quint64, ProductSettingDto)));

        mThread.start();
    }
    ~DspCommunityThread()
    {
        mThread.quit();
        mThread.wait();
    }

signals:
    void signalEventStarted                         (                                           );
    void signalEventStopped                         (                                           );
    void signalEventChangedIsConnect                (quint64 deviceSeq, bool value              );
    void signalEventCompletedFactoryReset           (quint64 deviceSeq                          );
    void signalEventChangedRemoteDeviceSetting      (quint64 deviceSeq, DspSettingDto value     );
    void signalEventChangedRemoteProductSetting     (quint64 deviceSeq, ProductSettingDto value );
    void signalEventChangedDeviceStatus             (quint64 deviceSeq, DspStatusDto value      );
    void signalEventChangedDeviceInfo               (quint64 deviceSeq, DspInfoDto value        );
    void signalEventAddedEvent                      (quint64 deviceSeq, EventDto value          );
    void signalEventAddedWeightCheckerGraph         (quint64 deviceSeq, WeightGraphDto value    );
    void signalEventAddedMetalDetectorGraph         (quint64 deviceSeq, MetalGraphDto value     );

public slots:
    void onCommandStopService                       (                                          ){ emit signalCommandStopService();}
    void onCommandAddDSP                            (DspConnectionDto connectionInfo, DspSettingDto ds, ProductSettingDto ps){emit signalCommandAddDSP(connectionInfo, ds, ps);}
    void onCommandRemoveDsp                         (quint64 deviceSeq                         ){ emit signalCommandRemoveDsp                  (deviceSeq       );}
    void onCommandModifyDSP                         (DspConnectionDto connectionInfo           ){ emit signalCommandModifyDSP                  (connectionInfo  );}
    void onCommandSendZeroCmd                       (quint64 deviceSeq                         ){ emit signalCommandSendZeroCmd                (deviceSeq       );}
    void onCommandSendFactoryResetCmd               (quint64 deviceSeq                         ){ emit signalCommandSendFactoryResetCmd        (deviceSeq       );}
    void onCommandSendWeightCaribCmd                (quint64 deviceSeq, quint16 value          ){ emit signalCommandSendWeightCaribCmd         (deviceSeq, value);}
    void onCommandSendRunCmd                        (quint64 deviceSeq, quint16 value          ){ emit signalCommandSendRunCmd                 (deviceSeq, value);}
    void onCommandSendWeightCheckerGraphOnCmd       (quint64 deviceSeq, bool value             ){ emit signalCommandSendWeightCheckerGraphOnCmd(deviceSeq, value);}
    void onCommandSendMetalDetectorGraphOnCmd       (quint64 deviceSeq, bool value             ){ emit signalCommandSendMetalDetectorGraphOnCmd(deviceSeq, value);}
    void onCommandSendDeviceIDCmd                   (quint64 deviceSeq, quint32 value          ){ emit signalCommandSendDeviceIDCmd            (deviceSeq, value);}
    void onCommandSendDspSetting                    (quint64 deviceSeq, DspSettingDto value    ){ emit signalCommandSendDspSetting             (deviceSeq, value);}
    void onCommandSendProductSetting                (quint64 deviceSeq, ProductSettingDto value){ emit signalCommandSendProductSetting         (deviceSeq, value);}

/////////////////////////////////////////////////
public slots:
    void onSignalEventStarted                         (                                           ){ emit signalEventStarted                    (                );}
    void onSignalEventStopped                         (                                           ){ emit signalEventStopped                    (                );}
    void onSignalEventChangedIsConnect                (quint64 deviceSeq, bool value              ){ emit signalEventChangedIsConnect           (deviceSeq, value);}
    void onSignalEventCompletedFactoryReset           (quint64 deviceSeq                          ){ emit signalEventCompletedFactoryReset      (deviceSeq       );}
    void onSignalEventChangedRemoteDeviceSetting      (quint64 deviceSeq, DspSettingDto value     ){ emit signalEventChangedRemoteDeviceSetting (deviceSeq, value);}
    void onSignalEventChangedRemoteProductSetting     (quint64 deviceSeq, ProductSettingDto value ){ emit signalEventChangedRemoteProductSetting(deviceSeq, value);}
    void onSignalEventChangedDeviceStatus             (quint64 deviceSeq, DspStatusDto value      ){ emit signalEventChangedDeviceStatus        (deviceSeq, value);}
    void onSignalEventChangedDeviceInfo               (quint64 deviceSeq, DspInfoDto value        ){ emit signalEventChangedDeviceInfo          (deviceSeq, value);}
    void onSignalEventAddedEvent                      (quint64 deviceSeq, EventDto value          ){ emit signalEventAddedEvent                 (deviceSeq, value);}
    void onSignalEventAddedWeightCheckerGraph         (quint64 deviceSeq, WeightGraphDto value    ){ emit signalEventAddedWeightCheckerGraph    (deviceSeq, value);}
    void onSignalEventAddedMetalDetectorGraph         (quint64 deviceSeq, MetalGraphDto value     ){ emit signalEventAddedMetalDetectorGraph    (deviceSeq, value);}

signals:
    void signalCommandStopService                       ();
    void signalCommandAddDSP                            (DspConnectionDto connectionInfo, DspSettingDto ds, ProductSettingDto ps);
    void signalCommandRemoveDsp                         (quint64 deviceSeq                         );
    void signalCommandModifyDSP                         (DspConnectionDto connectionInfo           );
    void signalCommandSendZeroCmd                       (quint64 deviceSeq                         );
    void signalCommandSendFactoryResetCmd               (quint64 deviceSeq                         );
    void signalCommandSendWeightCaribCmd                (quint64 deviceSeq, quint16 value          );
    void signalCommandSendRunCmd                        (quint64 deviceSeq, quint16 value          );
    void signalCommandSendWeightCheckerGraphOnCmd       (quint64 deviceSeq, bool value             );
    void signalCommandSendMetalDetectorGraphOnCmd       (quint64 deviceSeq, bool value             );
    void signalCommandSendDeviceIDCmd                   (quint64 deviceSeq, quint32 value          );
    void signalCommandSendDspSetting                    (quint64 deviceSeq, DspSettingDto value    );
    void signalCommandSendProductSetting                (quint64 deviceSeq, ProductSettingDto value);
};
#endif // DSPSERVICE_H
