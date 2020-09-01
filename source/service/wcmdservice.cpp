#include "wcmdservice.h"
#include <QDateTime>
#include <QDebug>

#include "source/globaldef/GlobalDefine.h"
#include "source/helper/databasehelper.h"
#include "source/helper/localsetting.h"

WCMDService *  WCMDService::mpSelf = nullptr;

WCMDService* WCMDService::getInstance()
{
    return mpSelf;
}

WCMDService::WCMDService(QObject *parent) : QObject(parent)
{
    qDebug() << "WCMDService : New";

    QDateTime now      = QDateTime::currentDateTime();
    mIsRun = false;

    // 전체 갯수
    // 백업한 날짜 부터 해서 갯수


    //moveToThread(&mThread);
    //mThread.start();

    //connect(&mThread, SIGNAL(started()), this, SLOT(onStarted()));
    //connect(&mThread, SIGNAL(finished()), this, SLOT(onFinished()));
    mWorkStartYear     = now.date().year();
    mWorkStartMonth    = now.date().month();
    mWorkStartDay      = now.date().day();

    mProductSetting = DatabaseHelper::getInstance()->findSelectedProductSetting(mDbCon);
    mDeviceSetting  = LocalSetting::getInstance()->getDeviceSetting();
    mInfomation     = LocalSetting::getInstance()->getInformation();

    connect(this, SIGNAL(signalCommandStopService                       (                                                   )), &mDspService, SLOT(onCommandStopService                       (                                                   )));
    connect(this, SIGNAL(signalCommandAddDSP                            (DeviceConnectionInfo, DeviceSetting, ProductSetting)), &mDspService, SLOT(onCommandAddDSP                            (DeviceConnectionInfo, DeviceSetting, ProductSetting)));
    connect(this, SIGNAL(signalCommandRemoveDSP                         (quint16)                                            ), &mDspService, SLOT(onCommandRemoveDsp                         (quint16)                                            ));
    connect(this, SIGNAL(signalCommandModifyDSP                         (DeviceConnectionInfo)                               ), &mDspService, SLOT(onCommandModifyDSP                         (DeviceConnectionInfo)                               ));
    connect(this, SIGNAL(signalCommandSendZeroCmd                       (quint16)                                            ), &mDspService, SLOT(onCommandSendZeroCmd                       (quint16)                                            ));
    connect(this, SIGNAL(signalCommandSendRunCmd                        (quint16, quint16)                                   ), &mDspService, SLOT(onCommandSendRunCmd                        (quint16, quint16)                                   ));
    //connect(this, SIGNAL(signalCommandSendRunModeCmd                    (quint16, quint16)                                   ), &mDspService, SLOT(onCommandSendRunModeCmd                    (quint16, quint16)                                   ));
    connect(this, SIGNAL(signalCommandSendWeightCheckerGraphOnCmd       (quint16, bool)                                      ), &mDspService, SLOT(onCommandSendWeightCheckerGraphOnCmd       (quint16, bool)                                      ));
    connect(this, SIGNAL(signalCommandSendMetalDetectorGraphOnCmd       (quint16, bool)                                      ), &mDspService, SLOT(onCommandSendMetalDetectorGraphOnCmd       (quint16, bool)                                      ));
    connect(this, SIGNAL(signalCommandSendMetalDetectorFilterGraphOnCmd (quint16, bool)                                      ), &mDspService, SLOT(onCommandSendMetalDetectorFilterGraphOnCmd (quint16, bool)                                      ));
    connect(this, SIGNAL(signalCommandSendDeviceIDCmd                   (quint16, quint32)                                   ), &mDspService, SLOT(onCommandSendDeviceIDCmd                   (quint16, quint32)                                   ));
    connect(this, SIGNAL(signalCommandSendFactoryResetCmd               (quint16)                                            ), &mDspService, SLOT(onCommandSendFactoryResetCmd               (quint16)                                            ));
    connect(this, SIGNAL(signalCommandSendWeightCaribCmd                (quint16, quint16)                                   ), &mDspService, SLOT(onCommandSendWeightCaribCmd                (quint16, quint16)                                            ));
    connect(this, SIGNAL(signalCommandSendDeviceSetting                 (quint16, DeviceSetting)                             ), &mDspService, SLOT(onCommandSendDeviceSetting                 (quint16, DeviceSetting)                             ));
    connect(this, SIGNAL(signalCommandSendProductSetting                (quint16, ProductSetting)                            ), &mDspService, SLOT(onCommandSendProductSetting                (quint16, ProductSetting)                            ));

    connect(&mDspService, SIGNAL(signalEventCompletedFactoryReset        (quint16)                        ), this, SLOT(onSignalEventCompletedFactoryReset         (quint16)                        ));
    connect(&mDspService, SIGNAL(signalEventChangedIsConnect             (quint16, bool)                  ), this, SLOT(onSignalEventChangedIsConnect              (quint16, bool)                  ));
    connect(&mDspService, SIGNAL(signalEventChangedRemoteDeviceSetting   (quint16, DeviceSetting)         ), this, SLOT(onSignalEventChangedRemoteDeviceSetting    (quint16, DeviceSetting)         ));
    connect(&mDspService, SIGNAL(signalEventChangedRemoteProductSetting  (quint16, ProductSetting)        ), this, SLOT(onSignalEventChangedRemoteProductSetting   (quint16, ProductSetting)        ));
    connect(&mDspService, SIGNAL(signalEventChangedDeviceStatus          (quint16, DeviceStatus)          ), this, SLOT(onSignalEventChangedDeviceStatus           (quint16, DeviceStatus)          ));
    connect(&mDspService, SIGNAL(signalEventChangedDeviceInfo            (quint16, DeviceInfo)            ), this, SLOT(onSignalEventChangedDeviceInfo             (quint16, DeviceInfo)            ));
    connect(&mDspService, SIGNAL(signalEventAddedEvent                   (quint16, EventInfo)             ), this, SLOT(onSignalEventAddedEvent                    (quint16, EventInfo)             ));
    connect(&mDspService, SIGNAL(signalEventAddedWeightCheckerGraph      (quint16, WeightChekerGraphData) ), this, SLOT(onSignalEventAddedWeightCheckerGraph       (quint16, WeightChekerGraphData )));
    connect(&mDspService, SIGNAL(signalEventAddedMetalDetectorGraph      (quint16, MetalDetectorGraphData)), this, SLOT(onSignalEventAddedMetalDetectorGraph       (quint16, MetalDetectorGraphData)));
    connect(&mDspService, SIGNAL(signalEventAddedMetalDetectorFilterGraph(quint16, MetalDetectorGraphData)), this, SLOT(onSignalEventAddedMetalDetectorFilterGraph (quint16, MetalDetectorGraphData)));

    QList<DeviceConnectionInfo> listDsp = DatabaseHelper::getInstance()->findAllConnectionInfo(mDbCon);

    qDebug() << "dsp size :" << listDsp.size();

    for(int i = 0; i < listDsp.size(); i ++)
    {
        DeviceConnectionInfo dci = listDsp.at(i);

        if(mMapDSPManager.contains(dci.mSeq))
        {
            mMapDSPManager[dci.mSeq]->reset(mDeviceSetting, mProductSetting);
        }
        else
        {
            mMapDSPManager.insert(dci.mSeq, new DSPManager(mDeviceSetting, mProductSetting, mpSelf));
        }
    }

    mpSelf = this;

    mThread = QThread::create(WCMDService::procStart);

    connect(mThread, SIGNAL(finished()), this, SLOT(onStarted()));
    mThread->start();
}

WCMDService::~WCMDService()
{
    qDebug() << "WCMDService : Delete";

    mIsRun = false;
}

void WCMDService::procStart()
{
    QDateTime now      = QDateTime::currentDateTime();
    quint64 startWorkSeq = LocalSetting::getInstance()->getWorkStartSeq(now.date().year(), now.date().month(), now.date().day());

    if(mpSelf->mDeviceSetting.mIsDayMode && startWorkSeq != INVALID_ULONGLONG)
    {
        qDebug() << "procStart() : load today event[" << startWorkSeq << "]";
        QList<Event> mListEvent = DatabaseHelper::getInstance()->findAllEventAfterSeq(mpSelf->mStartProcDbCon, startWorkSeq);

        for(int i = 0; i < mListEvent.size(); i++)
        {
            Event event = mListEvent.at(i);

            if(event.mEventType == EnumDefine::EventType::WEIGHT_NORMAL_TYPE
               ||event.mEventType == EnumDefine::EventType::WEIGHT_UNDER_WARNING_TYPE
               ||event.mEventType == EnumDefine::EventType::WEIGHT_OVER_WARNING_TYPE
               ||event.mEventType == EnumDefine::EventType::WEIGHT_UNDER_TYPE
               ||event.mEventType == EnumDefine::EventType::WEIGHT_OVER_TYPE
               ||event.mEventType == EnumDefine::EventType::WEIGHT_ETCERROR_TYPE
               ||event.mEventType == EnumDefine::EventType::METAL_TRADE_TYPE
               ||event.mEventType == EnumDefine::EventType::METAL_DETECT_TYPE
               ||event.mEventType == EnumDefine::EventType::WEIGHT_ETC_METAL_ERROR_TYPE  )
            {
                EventInfo eventInfo;
                eventInfo.mEventType  = event.mEventType;
                eventInfo.mEventValue = event.mWeight;

                if(mpSelf->mMapDSPManager.contains(event.mDeviceSeq))
                {
                    mpSelf->mMapDSPManager[event.mDeviceSeq]->addEvent(event.mProductSettingSeq, eventInfo);
                }
            }
        }
    }
    //else // DB에서 이력을 가져올때 temp파일을 로드 한다. day 모드가 아니라면 이력을 가져오지 않으므로 명시적으로 temp파일을 로드하도록 하자.
    //{
    //    qDebug() << "procStart() : import pre event";
    //
    //    DatabaseHelper::getInstance()->restoreEventFromTempFile(mpSelf->mStartProcDbCon);
    //}

    QDateTime lastDateTime = LocalSetting::getInstance()->getLastDateTime();
    Event progEndEvent;
    Event progStartEvent;
    progEndEvent.mYear           = lastDateTime.date().year();
    progEndEvent.mMonth          = lastDateTime.date().month();
    progEndEvent.mDay            = lastDateTime.date().day();
    progEndEvent.mHour           = lastDateTime.time().hour();
    progEndEvent.mMin            = lastDateTime.time().minute();
    progEndEvent.mSec            = lastDateTime.time().second();
    progEndEvent.mMsec           = lastDateTime.time().msec();
    progEndEvent.mWorkStartYear  = lastDateTime.date().year();
    progEndEvent.mWorkStartMonth = lastDateTime.date().month();
    progEndEvent.mWorkStartDay   = lastDateTime.date().day();
    progEndEvent.mEventType      = EnumDefine::EventType::APP_EXIT_TYPE;

    if(progEndEvent.mYear > 2019)
    {
        DatabaseHelper::getInstance()->addEvent(mpSelf->mStartProcDbCon, &progEndEvent);
        LocalSetting::getInstance()->setLastEventSeq(progEndEvent.mSeq);
    }

    LocalSetting::getInstance()->setLastDateTime();

    progStartEvent.mYear           = now.date().year();
    progStartEvent.mMonth          = now.date().month();
    progStartEvent.mDay            = now.date().day();
    progStartEvent.mHour           = now.time().hour();
    progStartEvent.mMin            = now.time().minute();
    progStartEvent.mSec            = now.time().second();
    progStartEvent.mMsec           = now.time().msec();
    progStartEvent.mWorkStartYear  = now.date().year();
    progStartEvent.mWorkStartMonth = now.date().month();
    progStartEvent.mWorkStartDay   = now.date().day();
    progStartEvent.mEventType      = EnumDefine::EventType::APP_START_TYPE;

    DatabaseHelper::getInstance()->addEvent(mpSelf->mStartProcDbCon, &progStartEvent);
    LocalSetting::getInstance()->setLastEventSeq(progStartEvent.mSeq);

    if(startWorkSeq == INVALID_ULONGLONG)
    {
        qDebug() << "procStart() : today start seq = " << progStartEvent.mSeq;

        LocalSetting::getInstance()->setWorkStartSeq(now.date().year(), now.date().month(), now.date().day(), progStartEvent.mSeq);
    }
    mpSelf->mIsRun = true;

}
// internal slot
void WCMDService::onStarted()
{
    QList<DeviceConnectionInfo> listDsp = DatabaseHelper::getInstance()->findAllConnectionInfo(mDbCon);

    for(int i = 0; i < listDsp.size(); i ++)
    {
        DeviceConnectionInfo dci = listDsp.at(i);

        emit signalCommandAddDSP(dci, mDeviceSetting, mProductSetting);
    }

    emit signalEventStartedService();
}

// qml slot
void WCMDService::onCommandSetZero                           (quint16 deviceSeq){emit signalCommandSendZeroCmd(deviceSeq);}
void WCMDService::onCommandSetRun                            (quint16 deviceSeq, quint16 value){emit signalCommandSendRunCmd(deviceSeq, value);}
//void WCMDService::onCommandSetRunMode                        (quint16 deviceSeq, quint16 value){mRunMode = (EnumDefine::RUN_MODE)value; emit signalEventChangedRunMode(value); emit signalCommandSendRunModeCmd(0xffff /*deviceSeq*/, value);}
void WCMDService::onCommandSetWeightCheckerGraphOn           (quint16 deviceSeq, bool value){emit signalCommandSendWeightCheckerGraphOnCmd(deviceSeq, value);}
void WCMDService::onCommandSetMetalDetectorGraphOn           (quint16 deviceSeq, bool value){emit signalCommandSendMetalDetectorGraphOnCmd(deviceSeq, value);}
void WCMDService::onCommandSetMetalDetectorFilterGraphOn     (quint16 deviceSeq, bool value){emit signalCommandSendMetalDetectorFilterGraphOnCmd(deviceSeq, value);}
void WCMDService::onCommandSetDeviceID                       (quint16 deviceSeq, quint32 value){emit signalCommandSendDeviceIDCmd(deviceSeq, value);}

void WCMDService::onCommandFactoryReset                      (quint16 deviceSeq)               { emit signalCommandSendFactoryResetCmd(deviceSeq       );}
void WCMDService::onCommandWeightCarib                       (quint16 deviceSeq, quint16 value){ emit signalCommandSendWeightCaribCmd (deviceSeq, value);}
void WCMDService::onCommandResetStatistics                   (                 )
{
    EventInfo ei;

    ei.mEventType = EnumDefine::EventType::EVENT_NONE_TYPE;
    ei.mEventValue = 0;

    QList<DSPManager *> list = mMapDSPManager.values();

    for(int i = 0; i < list.size(); i ++)
    {
        list.at(i)->resetStatistics();
    }
    emit signalEventAddedEvent(0xffff, ei);
}
void WCMDService::onCommandSaveDSP                           (void * sender, int type, DeviceConnectionInfo connectionInfo)
{
    EnumDefine::DatabaseErrorType retError = EnumDefine::DatabaseErrorType::DB_NONE_ERROR;

    if(type == EnumDefine::DataBaseWriteMode::ADD)
    {
        retError = DatabaseHelper::getInstance()->addDeviceConnectionInfo(mDbCon, &connectionInfo);

        if(retError == EnumDefine::DatabaseErrorType::DB_NONE_ERROR)
        {
            if(mMapDSPManager.contains(connectionInfo.mSeq))
            {
                mMapDSPManager[connectionInfo.mSeq]->reset(mDeviceSetting, mProductSetting);
            }
            else
            {
                mMapDSPManager.insert(connectionInfo.mSeq, new DSPManager(mDeviceSetting, mProductSetting, this));
            }
            emit signalCommandAddDSP(connectionInfo, mDeviceSetting, mProductSetting);
        }
    }
    else if(type == EnumDefine::DataBaseWriteMode::EDIT)
    {
        retError = DatabaseHelper::getInstance()->editDeviceConnectionInfo(mDbCon,connectionInfo);

        if(retError == EnumDefine::DatabaseErrorType::DB_NONE_ERROR)
        {
            emit signalCommandModifyDSP(connectionInfo);
        }
    }
    else if(type == EnumDefine::DataBaseWriteMode::REMOVE)
    {
        retError = DatabaseHelper::getInstance()->removeDeviceConnectionInfo(mDbCon, connectionInfo.mSeq);

        if(retError == EnumDefine::DatabaseErrorType::DB_NONE_ERROR)
        {
            if(mMapDSPManager.contains(connectionInfo.mSeq))
            {
                mMapDSPManager[connectionInfo.mSeq]->mIsDelete = true;
            }
            emit signalCommandRemoveDSP(connectionInfo.mSeq);
        }
    }

    emit signalResultSaveDsp(sender, retError, connectionInfo);

    if(retError == EnumDefine::DatabaseErrorType::DB_NONE_ERROR)
    {
        emit signalEventChangedDsp(type, connectionInfo);
    }
}

void WCMDService::onCommandSaveProductSetting(void * sender, int type, ProductSetting value)
{
    EnumDefine::DatabaseErrorType retError = EnumDefine::DatabaseErrorType::DB_NONE_ERROR;

    if(type == EnumDefine::DataBaseWriteMode::ADD)
    {
        retError = DatabaseHelper::getInstance()->addProductSetting(mDbCon, &value);
    }
    else if(type == EnumDefine::DataBaseWriteMode::EDIT)
    {
        retError = DatabaseHelper::getInstance()->editProductSetting(mDbCon, value);

        if(retError == EnumDefine::DatabaseErrorType::DB_NONE_ERROR && value.mSeq == mProductSetting.mSeq)
        {
            mProductSetting = DatabaseHelper::getInstance()->findSelectedProductSetting(mDbCon);

            QList<DSPManager *> list = mMapDSPManager.values();

            for(int i = 0; i < list.size(); i ++)
            {
                if(list.at(i)->mIsDelete == false)
                    list.at(i)->setProductSetting(mProductSetting);
            }

            emit signalCommandSendProductSetting(0xffff, mProductSetting);
        }
    }
    else if(type == EnumDefine::DataBaseWriteMode::REMOVE)
    {
        retError = DatabaseHelper::getInstance()->removeProductSetting(mDbCon, value.mSeq);
    }

    emit signalResultSaveProductSetting(sender, retError, value);

    if(retError == EnumDefine::DatabaseErrorType::DB_NONE_ERROR)
    {
        emit signalEventChangedProductSetting(type, value);
    }
}

void WCMDService::onCommandSelectProductSetting(void * sender, quint16 productSeq)
{
    EnumDefine::DatabaseErrorType retError = EnumDefine::DatabaseErrorType::DB_NONE_ERROR;

    retError = DatabaseHelper::getInstance()->selectProductSetting(mDbCon, productSeq);

    if(retError == EnumDefine::DatabaseErrorType::DB_NONE_ERROR)
    {
        mProductSetting = DatabaseHelper::getInstance()->findSelectedProductSetting(mDbCon);

        QList<DSPManager *> list = mMapDSPManager.values();

        for(int i = 0; i < list.size(); i ++)
        {
            if(list.at(i)->mIsDelete == false)
                list.at(i)->setProductSetting(mProductSetting);
        }

        emit signalCommandSendProductSetting(0xffff, mProductSetting);
    }

    emit signalResultSelectProductSetting(sender, retError, mProductSetting);

    if(retError == EnumDefine::DatabaseErrorType::DB_NONE_ERROR)
    {
        emit signalEventChangedSelectedProductSetting(mProductSetting);
    }
}

void WCMDService::onCommandSaveInformation                   (void * sender, Information value)
{
    LocalSetting::getInstance()->setInformation(value);

    mInfomation = LocalSetting::getInstance()->getInformation();

    emit signalResultSaveInformation(sender, mInfomation);
    emit signalEventChangedInformation(mInfomation);
}
void WCMDService::onCommandSaveDeviceSetting                 (void * sender, DeviceSetting value)
{
    LocalSetting::getInstance()->setDeviceSetting(value);

    mDeviceSetting = LocalSetting::getInstance()->getDeviceSetting();

    QList<DSPManager *> list = mMapDSPManager.values();

    for(int i = 0; i < list.size(); i ++)
    {
        if(list.at(i)->mIsDelete == false)
            list.at(i)->setDeviceSetting(mDeviceSetting);
    }

    emit signalCommandSendDeviceSetting(0xffff, mDeviceSetting);

    emit signalResultSaveDeviceSetting(sender, mDeviceSetting);
    emit signalEventChangedDeviceSetting(mDeviceSetting);
}

// dsp slot
void WCMDService::onSignalEventCompletedFactoryReset         (quint16 deviceSeq)
{
    emit signalEventCompletedFactoryReset(deviceSeq);
}

void WCMDService::onSignalEventChangedIsConnect              (quint16 deviceSeq, bool value)
{

    if(mMapDSPManager.contains(deviceSeq))
        mMapDSPManager[deviceSeq]->setIsConnect(value);

    emit signalEventChangedIsConnect(deviceSeq, value);
}

void WCMDService::onSignalEventChangedRemoteDeviceSetting      (quint16 deviceSeq, DeviceSetting value)
{
    if(mMapDSPManager.contains(deviceSeq))
    {
        mMapDSPManager[deviceSeq]->setRemoteDeviceSetting(value);
    }
    emit signalEventChangedRemoteDeviceSetting      (deviceSeq, value);
}
void WCMDService::onSignalEventChangedRemoteProductSetting     (quint16 deviceSeq, ProductSetting value)
{
    if(mMapDSPManager.contains(deviceSeq))
    {
        mMapDSPManager[deviceSeq]->setRemoteProductSetting(value);
    }

    emit signalEventChangedRemoteProductSetting     (deviceSeq, value);
}

void WCMDService::onSignalEventChangedDeviceStatus           (quint16 deviceSeq, DeviceStatus value)
{
    QDateTime now      = QDateTime::currentDateTime();

    if(mMapDSPManager.contains(deviceSeq))
    {
        if(((value.mRun == EnumDefine::RunState::STOP) && (mMapDSPManager[deviceSeq]->mRun != EnumDefine::RunState::STOP)) ||
           ((value.mRun != EnumDefine::RunState::STOP) && (mMapDSPManager[deviceSeq]->mRun == EnumDefine::RunState::STOP)))
        {
            Event event;
            event.mDeviceSeq           = deviceSeq;
            event.mYear                = now.date().year();
            event.mMonth               = now.date().month();
            event.mDay                 = now.date().day();
            event.mHour                = now.time().hour();
            event.mMin                 = now.time().minute();
            event.mSec                 = now.time().second();
            event.mMsec                = now.time().msec();
            //event.mProgStartEventSeq
            event.mWorkStartYear       = mWorkStartYear;
            event.mWorkStartMonth      = mWorkStartMonth;
            event.mWorkStartDay        = mWorkStartDay;
            event.mEventType           = value.mRun != EnumDefine::RunState::STOP ? EnumDefine::EventType::RUN_TYPE : EnumDefine::EventType::STOP_TYPE;

            LocalSetting::getInstance()->setLastDateTime();
            DatabaseHelper::getInstance()->addEvent(mDbCon, &event);
            LocalSetting::getInstance()->setLastEventSeq(event.mSeq);
        }
        mMapDSPManager[deviceSeq]->setDeviceStatus(value);
    }
    emit signalEventChangedDeviceStatus(deviceSeq, value);
}
void WCMDService::onSignalEventChangedDeviceInfo             (quint16 deviceSeq, DeviceInfo value)
{
    mMapDSPManager[deviceSeq]->setDeviceInfo(value);

    qDebug() << "onSignalEventChangedDeviceInfo"<< value.mID << ","<<value.mMajorVersion <<","<< value.mMinorVersion;

    QString dspVersion("%1.%2.%3");
    mInfomation.mDspVersion = dspVersion.arg(value.mMajorVersion).arg(value.mMinorVersion).arg(value.mMaintenanceVersion);

    onCommandSaveInformation(this, mInfomation);

    emit signalEventChangedDeviceInfo(deviceSeq, value);
}
void WCMDService::onSignalEventAddedEvent                    (quint16 deviceSeq, EventInfo value)
{
    QDateTime now      = QDateTime::currentDateTime();

    qDebug() << "onSignalEventAddedEvent: " << value.mEventType;

    if((value.mEventType > EnumDefine::EventType::WEIGHT_OVER_WARNING_TYPE && value.mEventType < EnumDefine::EventType::APP_START_TYPE)
       || value.mEventType == EnumDefine::EventType::METAL_DETECT_TYPE)
    {
        mLastError = value.mEventType;
        mLastErrorTime = QDateTime::currentDateTime().toString("hh:mm:ss");
        mLastErrorValue = value.mEventValue;
    }

    if(mMapDSPManager.contains(deviceSeq))
    {
        if(value.mEventType == EnumDefine::EventType::WEIGHT_NORMAL_TYPE        ||
           value.mEventType == EnumDefine::EventType::WEIGHT_UNDER_WARNING_TYPE ||
           value.mEventType == EnumDefine::EventType::WEIGHT_OVER_WARNING_TYPE  ||
           value.mEventType == EnumDefine::EventType::WEIGHT_UNDER_TYPE         ||
           value.mEventType == EnumDefine::EventType::WEIGHT_OVER_TYPE          ||
           value.mEventType == EnumDefine::EventType::WEIGHT_ETCERROR_TYPE      ||
           value.mEventType == EnumDefine::EventType::WEIGHT_ETC_METAL_ERROR_TYPE||
           value.mEventType == EnumDefine::EventType::METAL_TRADE_TYPE          ||
           value.mEventType == EnumDefine::EventType::METAL_DETECT_TYPE         )
        mMapDSPManager[deviceSeq]->addEvent(mProductSetting.mSeq, value);
    }

    Event event;
    event.mDeviceSeq           = deviceSeq;
    event.mYear                = now.date().year();
    event.mMonth               = now.date().month();
    event.mDay                 = now.date().day();
    event.mHour                = now.time().hour();
    event.mMin                 = now.time().minute();
    event.mSec                 = now.time().second();
    event.mMsec                = now.time().msec();
    //event.mProgStartEventSeq
    event.mWorkStartYear       = mWorkStartYear;
    event.mWorkStartMonth      = mWorkStartMonth;
    event.mWorkStartDay        = mWorkStartDay;
    event.mEventType           = value.mEventType;
    event.mProductSettingSeq   = mProductSetting.mSeq;
    event.mProductNo           = mProductSetting.mNo;
    event.mProductName         = mProductSetting.mName;
    //event.mDeviceID
    event.mUnderWeight         = mProductSetting.mUnderWeight;
    event.mUnderWarningWeight  = mProductSetting.mUnderWarningWeight;
    event.mNormalWeight        = mProductSetting.mNormalWeight;
    event.mOverWarningWeight   = mProductSetting.mOverWarningWeight;
    event.mOverWeight          = mProductSetting.mOverWeight;
    event.mTareWeight          = mProductSetting.mTareWeight;
    event.mMDSenstivity        = mProductSetting.mMDSenstivity;
    event.mWeight              = value.mEventValue;

    if(value.mEventType == EnumDefine::EventType::WEIGHT_NORMAL_TYPE        ||
       value.mEventType == EnumDefine::EventType::WEIGHT_UNDER_WARNING_TYPE ||
       value.mEventType == EnumDefine::EventType::WEIGHT_OVER_WARNING_TYPE  ||
       value.mEventType == EnumDefine::EventType::WEIGHT_UNDER_TYPE         ||
       value.mEventType == EnumDefine::EventType::WEIGHT_OVER_TYPE          ||
       value.mEventType == EnumDefine::EventType::WEIGHT_ETCERROR_TYPE      ||
       value.mEventType == EnumDefine::EventType::WEIGHT_ETC_METAL_ERROR_TYPE||
       value.mEventType == EnumDefine::EventType::METAL_TRADE_TYPE          ||
       value.mEventType == EnumDefine::EventType::METAL_DETECT_TYPE         ||
       value.mEventType == EnumDefine::EventType::WEIGHT_STATIC_CARI_TYPE   ||
       value.mEventType == EnumDefine::EventType::WEIGHT_DYNAMIC_CARI_TYPE)
    {

        DatabaseHelper::getInstance()->addEvent(mDbCon, &event);
        LocalSetting::getInstance()->setLastEventSeq(event.mSeq);
    }

    LocalSetting::getInstance()->setLastDateTime();

    emit signalEventAddedEvent(deviceSeq, value);

    if(value.mEventType == EnumDefine::EventType::WEIGHT_STATIC_CARI_TYPE   || value.mEventType == EnumDefine::EventType::WEIGHT_DYNAMIC_CARI_TYPE)
    {
        if(value.mEventType == EnumDefine::EventType::WEIGHT_STATIC_CARI_TYPE)
        {
            DeviceSetting ds = mDeviceSetting;
            ds.mStaticFactor = value.mEventValue;
            onCommandSaveDeviceSetting(this, ds);
        }
        else
        {
            ProductSetting ps = mProductSetting;
            ps.mDynamicFactor = value.mEventValue;
            onCommandSaveProductSetting(this, EnumDefine::DataBaseWriteMode::EDIT, ps);
        }
    }
}
void WCMDService::onSignalEventAddedWeightCheckerGraph       (quint16 deviceSeq, WeightChekerGraphData value)
{
    emit signalEventAddedWeightCheckerGraph(deviceSeq, value);
}
void WCMDService::onSignalEventAddedMetalDetectorGraph       (quint16 deviceSeq, MetalDetectorGraphData value)
{
    emit signalEventAddedMetalDetectorGraph(deviceSeq, value);
}
void WCMDService::onSignalEventAddedMetalDetectorFilterGraph (quint16 deviceSeq, MetalDetectorGraphData value)
{
    emit signalEventAddedMetalDetectorFilterGraph(deviceSeq, value);
}
