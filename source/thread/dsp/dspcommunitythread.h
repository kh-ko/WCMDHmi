#ifndef DSPSERVICE_H
#define DSPSERVICE_H

#include <QObject>
#include <QTimer>
#include <QThread>

#include "source/globaldef/EnumDefine.h"
#include "source/globaldef/GlobalDefine.h"
#include "source/thread/dsp/dspinterface.h"
#include "source/util/myalloc.h"

class DspCommunityThread : public QObject
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
    void onFinished();
    void onTimeTick();

public:
    explicit DspCommunityThread(QObject *parent = nullptr);
    ~DspCommunityThread();
};

#endif // DSPSERVICE_H
