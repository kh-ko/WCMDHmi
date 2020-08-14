#ifndef WCMDSERVICE_H
#define WCMDSERVICE_H

#include <QObject>
#include <QMap>

#include "source/model/Information.h"
#include "source/service/dsp/dspservice.h"
#include "source/service/dspmanager.h"

class WCMDService : public QObject
{
    Q_OBJECT
private:
    const QString               mDbCon = "WCMD_DB_CON";
    const QString               mStartProcDbCon = "WCMD_START_PROC_DB_CON";
    static WCMDService *        mpSelf;
    bool                        mIsRun;
    DSPService                  mDspService;
    bool                        mIsStopService = false;

public:
    quint16                     mWorkStartYear     ;
    quint16                     mWorkStartMonth    ;
    quint16                     mWorkStartDay      ;

    EnumDefine::EventType       mLastError       = EnumDefine::EventType::WEIGHT_NORMAL_TYPE;
    QString                     mLastErrorTime   = "";
    quint32                     mLastErrorValue  = 0;

    ProductSetting              mProductSetting ;
    DeviceSetting               mDeviceSetting  ;
    Information                 mInfomation     ;
    EnumDefine::RUN_MODE        mRunMode = EnumDefine::RUN_MODE::RUN_MODE_MONITOR;

    QMap<quint16, DSPManager *> mMapDSPManager;
    QThread *mThread;

    static void         procStart();
    static WCMDService* getInstance();
    explicit            WCMDService(QObject *parent = nullptr);
                        ~WCMDService();
    bool                isRun(){ return mIsRun;}
    void                stop(){ emit signalCommandStopService();}
    QList<DSPManager *> getAllDSPManager()
    {
        QList<DSPManager *>retList;
        QList<DSPManager *>tempList;

        tempList = mMapDSPManager.values();
        for(int i = 0; i < tempList.size(); i ++)
        {
            if(tempList.at(i)->mIsDelete == false)
                retList.append(tempList.at(i));
        }

        return retList;
    }

public slots:
    // internal slot
    void onStarted();

    // from uplayer
    void onCommandSetZero                           (quint16 deviceSeq);
    void onCommandSetRun                            (quint16 deviceSeq, quint16 value);
    //void onCommandSetRunMode                        (quint16 deviceSeq, quint16 value);
    void onCommandSetWeightCheckerGraphOn           (quint16 deviceSeq, bool value);
    void onCommandSetMetalDetectorGraphOn           (quint16 deviceSeq, bool value);
    void onCommandSetMetalDetectorFilterGraphOn     (quint16 deviceSeq, bool value);
    void onCommandSetDeviceID                       (quint16 deviceSeq, quint32 value);
    void onCommandFactoryReset                      (quint16 deviceSeq);
    void onCommandWeightCarib                       (quint16 deviceSeq, quint16 value);
    void onCommandResetStatistics                   ();
    void onCommandSaveDSP                           (void * sender, int type, DeviceConnectionInfo connectionInfo);
    void onCommandSaveProductSetting                (void * sender, int type, ProductSetting value);
    void onCommandSelectProductSetting              (void * sender, quint16 productSeq);
    void onCommandSaveInformation                   (void * sender, Information value);
    void onCommandSaveDeviceSetting                 (void * sender, DeviceSetting value);

    // from down layer
    void onSignalEventCompletedFactoryReset         (quint16 deviceSeq);
    void onSignalEventChangedIsConnect              (quint16 deviceSeq, bool value);
    void onSignalEventChangedRemoteDeviceSetting    (quint16 deviceSeq, DeviceSetting value) ;
    void onSignalEventChangedRemoteProductSetting   (quint16 deviceSeq, ProductSetting value);
    void onSignalEventChangedDeviceStatus           (quint16 deviceSeq, DeviceStatus value);
    void onSignalEventChangedDeviceInfo             (quint16 deviceSeq, DeviceInfo value);
    void onSignalEventAddedEvent                    (quint16 deviceSeq, EventInfo value);
    void onSignalEventAddedWeightCheckerGraph       (quint16 deviceSeq, WeightChekerGraphData value);
    void onSignalEventAddedMetalDetectorGraph       (quint16 deviceSeq, MetalDetectorGraphData value);
    void onSignalEventAddedMetalDetectorFilterGraph (quint16 deviceSeq, MetalDetectorGraphData value);

signals:
    // internal
    void signalEventStartedService                      ();
    void signalEventFinishedService                     ();

    // to uplayer

    void signalEventChangedDsp                          (int type, DeviceConnectionInfo value);
    void signalEventChangedProductSetting               (int type, ProductSetting       value);
    void signalEventChangedSelectedProductSetting       (ProductSetting       value);
    void signalEventChangedInformation                  (Information          value);
    void signalEventChangedDeviceSetting                (DeviceSetting        value);
    void signalEventChangedRunMode                      (quint16 runMode);

    void signalResultSaveDsp                            (void * sender, int error, DeviceConnectionInfo value);
    void signalResultSaveProductSetting                 (void * sender, int error, ProductSetting       value);
    void signalResultSelectProductSetting               (void * sender, int error, ProductSetting       value);
    void signalResultSaveInformation                    (void * sender, Information          value);
    void signalResultSaveDeviceSetting                  (void * sender, DeviceSetting        value);

    void signalEventCompletedFactoryReset               (quint16 deviceSeq);
    void signalEventChangedIsConnect                    (quint16 deviceSeq, bool value);
    void signalEventChangedRemoteDeviceSetting          (quint16 deviceSeq, DeviceSetting value) ;
    void signalEventChangedRemoteProductSetting         (quint16 deviceSeq, ProductSetting value);
    void signalEventChangedDeviceStatus                 (quint16 deviceSeq, DeviceStatus value);
    void signalEventChangedDeviceInfo                   (quint16 deviceSeq, DeviceInfo   value);
    void signalEventAddedEvent                          (quint16 deviceSeq, EventInfo    value);
    void signalEventAddedWeightCheckerGraph             (quint16 deviceSeq, WeightChekerGraphData value);
    void signalEventAddedMetalDetectorGraph             (quint16 deviceSeq, MetalDetectorGraphData value);
    void signalEventAddedMetalDetectorFilterGraph       (quint16 deviceSeq, MetalDetectorGraphData value);

    // to dsp
    void signalCommandStopService                       ();
    void signalCommandAddDSP                            (DeviceConnectionInfo dci, DeviceSetting ds, ProductSetting ps);
    void signalCommandRemoveDSP                         (quint16 deviceSeq);
    void signalCommandModifyDSP                         (DeviceConnectionInfo dci);
    void signalCommandSendZeroCmd                       (quint16 deviceSeq);
    void signalCommandSendRunCmd                        (quint16 deviceSeq, quint16 value);
    //void signalCommandSendRunModeCmd                    (quint16 deviceSeq, quint16 value);
    void signalCommandSendWeightCheckerGraphOnCmd       (quint16 deviceSeq, bool value);
    void signalCommandSendMetalDetectorGraphOnCmd       (quint16 deviceSeq, bool value);
    void signalCommandSendMetalDetectorFilterGraphOnCmd (quint16 deviceSeq, bool value);
    void signalCommandSendDeviceIDCmd                   (quint16 deviceSeq, quint32 value);
    void signalCommandSendFactoryResetCmd               (quint16 deviceSeq);
    void signalCommandSendWeightCaribCmd                (quint16 deviceSeq, quint16 value);
    void signalCommandSendDeviceSetting                 (quint16 deviceSeq, DeviceSetting value);
    void signalCommandSendProductSetting                (quint16 deviceSeq, ProductSetting value);


};

#endif // WCMDSERVICE_H
