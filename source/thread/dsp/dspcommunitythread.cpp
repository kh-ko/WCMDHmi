#include "dspcommunitythread.h"

#include <QDebug>
#include <QDateTime>

void DspCommunityThreadWorker::onStarted()
{
    qDebug() << "[DspCommunityThread::onStarted]";

    mpTimer = new QTimer(this);
    mpTimer->setInterval(100);

    connect(mpTimer, SIGNAL(timeout()), this, SLOT(onTimeTick()));
    mpTimer->start();

    emit signalEventStarted();
}

void DspCommunityThreadWorker::onTimeTick()
{
    for(int i = 0; i < mListDSPInterface.size(); i ++)
    {
        mListDSPInterface.at(i)->onCommandTimeTick();
    }
}

void DspCommunityThreadWorker::onCommandStopService()
{
    qDebug() << "[DspCommunityThread::onCommandStopService]";

    for(int i = 0; i < mListDSPInterface.size(); i ++)
    {
        delete mListDSPInterface.at(i);
    }

    mListDSPInterface.clear();

    emit signalEventStopped();
}

void DspCommunityThreadWorker::onCommandAddDSP(DspConnectionDto connectionInfo, DspSettingDto ds, ProductSettingDto ps)
{
    qDebug() << "[DspCommunityThread::onCommandAddDSP]ip =" << connectionInfo.mIp;

    DSPInterface * dspInterface  = new DSPInterface(connectionInfo, ds, ps, this);

    connect(dspInterface, SIGNAL(signalEventChangedIsConnect                (quint64, bool              )), this, SLOT(onSignalEventChangedIsConnect                (quint64, bool              )));
    connect(dspInterface, SIGNAL(signalEventChangedRemoteDeviceSetting      (quint64, DspSettingDto     )), this, SLOT(onSignalEventChangedRemoteDeviceSetting      (quint64, DspSettingDto     )));
    connect(dspInterface, SIGNAL(signalEventChangedRemoteProductSetting     (quint64, ProductSettingDto )), this, SLOT(onSignalEventChangedRemoteProductSetting     (quint64, ProductSettingDto )));
    connect(dspInterface, SIGNAL(signalEventChangedDeviceStatus             (quint64, DspStatusDto      )), this, SLOT(onSignalEventChangedDeviceStatus             (quint64, DspStatusDto      )));
    connect(dspInterface, SIGNAL(signalEventChangedDeviceInfo               (quint64, DspInfoDto        )), this, SLOT(onSignalEventChangedDeviceInfo               (quint64, DspInfoDto        )));
    connect(dspInterface, SIGNAL(signalEventAddedEvent                      (quint64, EventDto          )), this, SLOT(onSignalEventAddedEvent                      (quint64, EventDto          )));
    connect(dspInterface, SIGNAL(signalEventAddedWeightCheckerGraph         (quint64, WeightGraphDto    )), this, SLOT(onSignalEventAddedWeightCheckerGraph         (quint64, WeightGraphDto    )));
    connect(dspInterface, SIGNAL(signalEventAddedMetalDetectorGraph         (quint64, MetalGraphDto     )), this, SLOT(onSignalEventAddedMetalDetectorGraph         (quint64, MetalGraphDto     )));
    connect(dspInterface, SIGNAL(signalEventCompletedFactoryReset            (quint64                   )), this, SLOT(onSignalEventCompletedFactoryReset            (quint64                    )));

    mListDSPInterface.append(dspInterface);
    dspInterface->onCommandStart();
}

void DspCommunityThreadWorker::onCommandRemoveDsp(quint64 deviceSeq)
{
    qDebug() << "[DspCommunityThread::onCommandRemoveDsp]deviceSeq =" << deviceSeq;

    for(int i = 0; i < mListDSPInterface.size(); i ++)
    {
        if(mListDSPInterface.at(i)->mConnection.mDspSeq == deviceSeq)
        {
            delete mListDSPInterface.at(i);
            mListDSPInterface.removeAt(i);
        }
    }
}
void DspCommunityThreadWorker::onCommandModifyDSP(DspConnectionDto connectionInfo)
{
    qDebug() << "[DspCommunityThread::onCommandModifyDSP]";

    for(int i = 0; i < mListDSPInterface.size(); i ++)
    {
        DSPInterface * pInterface = mListDSPInterface.at(i);

        if(pInterface->mConnection.mDspSeq == connectionInfo.mDspSeq)
        {
            pInterface->onCommandModifyConnectInfo(connectionInfo);
        }
    }
}
void DspCommunityThreadWorker::onCommandSendZeroCmd(quint64 deviceSeq)
{
    qDebug() << "[DspCommunityThread::onCommandSendZeroCmd]";

    for(int i = 0; i < mListDSPInterface.size(); i ++)
    {
        DSPInterface * pInterface = mListDSPInterface.at(i);

        if(pInterface->mConnection.mDspSeq == deviceSeq || deviceSeq == INVALID_ULONGLONG)
        {
            pInterface->onCommandSendZeroCmd();
        }
    }
}
void DspCommunityThreadWorker::onCommandSendFactoryResetCmd(quint64 deviceSeq)
{
    qDebug() << "[DspCommunityThread::onCommandSendFactoryResetCmd]";

    for(int i = 0; i < mListDSPInterface.size(); i ++)
    {
        DSPInterface * pInterface = mListDSPInterface.at(i);

        if(pInterface->mConnection.mDspSeq == deviceSeq || deviceSeq == INVALID_ULONGLONG)
        {
            pInterface->onCommandSendFactoryResetCmd();
        }
    }
}

void DspCommunityThreadWorker::onCommandSendWeightCaribCmd(quint64 deviceSeq, quint16 value)
{
    qDebug() << "[DspCommunityThread::onCommandSendWeightCaribCmd]";

    for(int i = 0; i < mListDSPInterface.size(); i ++)
    {
        DSPInterface * pInterface = mListDSPInterface.at(i);

        if(pInterface->mConnection.mDspSeq == deviceSeq || deviceSeq == INVALID_ULONGLONG)
        {
            pInterface->onCommandSendWeightCaribCmd(value);
        }
    }
}
void DspCommunityThreadWorker::onCommandSendRunCmd(quint64 deviceSeq, quint16 value)
{
    qDebug() << "[DspCommunityThread::onCommandSendRunCmd]";

    for(int i = 0; i < mListDSPInterface.size(); i ++)
    {
        DSPInterface * pInterface = mListDSPInterface.at(i);

        if(pInterface->mConnection.mDspSeq == deviceSeq || deviceSeq == INVALID_ULONGLONG)
        {
            pInterface->onCommandSendRunCmd(value);
        }
    }
}
void DspCommunityThreadWorker::onCommandSendWeightCheckerGraphOnCmd(quint64 deviceSeq, bool value)
{
    qDebug() << "[DspCommunityThread::onCommandSendWeightCheckerGraphOnCmd]";

    for(int i = 0; i < mListDSPInterface.size(); i ++)
    {
        DSPInterface * pInterface = mListDSPInterface.at(i);

        if(pInterface->mConnection.mDspSeq == deviceSeq || deviceSeq == INVALID_ULONGLONG)
        {
            pInterface->onCommandSendWeightCheckerGraphOnCmd(value);
        }
    }
}
void DspCommunityThreadWorker::onCommandSendMetalDetectorGraphOnCmd       (quint64 deviceSeq, bool value)
{
    qDebug() << "[DspCommunityThread::onCommandSendMetalDetectorGraphOnCmd]";

    for(int i = 0; i < mListDSPInterface.size(); i ++)
    {
        DSPInterface * pInterface = mListDSPInterface.at(i);

        if(pInterface->mConnection.mDspSeq == deviceSeq || deviceSeq == INVALID_ULONGLONG)
        {
            pInterface->onCommandSendMetalDetectorGraphOnCmd(value);
        }
    }
}
void DspCommunityThreadWorker::onCommandSendDeviceIDCmd                   (quint64 deviceSeq, quint32 value)
{
    qDebug() << "[DspCommunityThread::onCommandSendDeviceIDCmd] id = " << value;

    for(int i = 0; i < mListDSPInterface.size(); i ++)
    {
        DSPInterface * pInterface = mListDSPInterface.at(i);

        if(pInterface->mConnection.mDspSeq == deviceSeq || deviceSeq == INVALID_ULONGLONG)
        {
            pInterface->onCommandSendDeviceIDCmd(value);
        }
    }
}
void DspCommunityThreadWorker::onCommandSendDspSetting                    (quint64 deviceSeq, DspSettingDto value)
{
    qDebug() << "[DspCommunityThread::onCommandSendDspSetting]";

    for(int i = 0; i < mListDSPInterface.size(); i ++)
    {
        DSPInterface * pInterface = mListDSPInterface.at(i);

        if(pInterface->mConnection.mDspSeq == deviceSeq || deviceSeq == INVALID_ULONGLONG)
        {
            pInterface->onCommandSendDeviceSetting(value);
        }
    }
}
void DspCommunityThreadWorker::onCommandSendProductSetting                (quint64 deviceSeq, ProductSettingDto value)
{
    qDebug() << "[DspCommunityThread::onCommandSendProductSetting]";

    for(int i = 0; i < mListDSPInterface.size(); i ++)
    {
        DSPInterface * pInterface = mListDSPInterface.at(i);

        if(pInterface->mConnection.mDspSeq == deviceSeq || deviceSeq == INVALID_ULONGLONG)
        {
            pInterface->onCommandSendProductSetting(value);
        }
    }
}

// dsp slot
void DspCommunityThreadWorker::onSignalEventChangedIsConnect              (quint64 deviceSeq, bool value              ){emit signalEventChangedIsConnect           (deviceSeq, value);}
void DspCommunityThreadWorker::onSignalEventCompletedFactoryReset         (quint64 deviceSeq                          ){emit signalEventCompletedFactoryReset      (deviceSeq       );}
void DspCommunityThreadWorker::onSignalEventChangedRemoteDeviceSetting    (quint64 deviceSeq, DspSettingDto value     ){emit signalEventChangedRemoteDeviceSetting (deviceSeq, value);}
void DspCommunityThreadWorker::onSignalEventChangedRemoteProductSetting   (quint64 deviceSeq, ProductSettingDto value ){emit signalEventChangedRemoteProductSetting(deviceSeq, value);}
void DspCommunityThreadWorker::onSignalEventChangedDeviceStatus           (quint64 deviceSeq, DspStatusDto value      ){emit signalEventChangedDeviceStatus        (deviceSeq, value);}
void DspCommunityThreadWorker::onSignalEventChangedDeviceInfo             (quint64 deviceSeq, DspInfoDto value        ){emit signalEventChangedDeviceInfo          (deviceSeq, value);}
void DspCommunityThreadWorker::onSignalEventAddedEvent                    (quint64 deviceSeq, EventDto value          ){emit signalEventAddedEvent                 (deviceSeq, value);}
void DspCommunityThreadWorker::onSignalEventAddedWeightCheckerGraph       (quint64 deviceSeq, WeightGraphDto value    ){emit signalEventAddedWeightCheckerGraph    (deviceSeq, value);}
void DspCommunityThreadWorker::onSignalEventAddedMetalDetectorGraph       (quint64 deviceSeq, MetalGraphDto value     ){emit signalEventAddedMetalDetectorGraph    (deviceSeq, value);}

DspCommunityThreadWorker::DspCommunityThreadWorker(QObject *parent) : QObject(parent)
{
    qDebug() << "[DspCommunityThread::Create]";
}

DspCommunityThreadWorker::~DspCommunityThreadWorker()
{
    qDebug() << "[DspCommunityThread::Delete]";
    mpTimer->stop();
    delete mpTimer;
}
