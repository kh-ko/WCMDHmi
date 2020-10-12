#include "coreservice.h"

CoreService * CoreService::mpSelf = nullptr;

CoreService * CoreService::getInstance()
{
    return mpSelf;
}

void CoreService::setClock(QString value)
{
    if(mClock == value) return;

    mClock = value;
    emit signalEventChangedClock(mClock);
}

void CoreService::setState(int value)
{
    qDebug() << "[CoreService::setState]" << value;

    if(mState == value) return;

    mState = value;
    emit signalEventChangedState(mState);
}

void CoreService::setFactoryResetState(int value)
{
    qDebug() << "[CoreService::setFactoryResetState]" << value;

    if(mFactoryResetState == value) return;

    mFactoryResetState = value;
    emit signalEventChangedFactoryResetState(mFactoryResetState);
}

void CoreService::onCommandStart()
{
    qDebug() << "[CoreService::onCommandStart]";

    setState(EnumDefine::ServiceState::SERVICE_STARTING);

    mProductSettingServcie.load();
}


void CoreService::onSignalEventCompleteLoadProductSetting()
{
    qDebug() << "[CoreService::onSignalEventCompleteLoadProductSetting]ProductSetting is loaded";
    mDspConnectionInfoService.load();
}

void CoreService::onSignalEventCompleteLoadDspConnection()
{
    qDebug() << "[CoreService::onSignalEventCompleteLoadDspConnection]Dsp connection info is loaded";

    for(int i = 0; i < mDspConnectionInfoService.mListDspConnection.size(); i ++)
    {
        DspStatusModel * pDspStatus = new DspStatusModel(this);

        pDspStatus->mSeq = mDspConnectionInfoService.mListDspConnection.at(i)->mSeq;

        mMapDspStatus.insert(mDspConnectionInfoService.mListDspConnection.at(i)->mSeq,pDspStatus);
    }

    mEventService.init(&mProductSettingServcie);

    if(mLocalSettingService.mHmiSetting.mIsDayMode && mEventService.isWorkingContiune())
        emit signalCommandWorkingHistoryLoadLine(mEventService.mWorkingEventHistoryPath, mEventService.mWorkingEventHistoryFileName, 1000);//  signalEventLoadWorkingHistory(mEventService.mWorkingPath, mEventService.mWorkingFileName);
    else
    {
        mEventService.workReset();
        onSignalEventEndOfLineWorkingHistory();
    }
}

void CoreService::onSignalEventLoadedLineWorkingHistory(QStringList lines)
{
    EventModel event;

    for(int i = 0; i < lines.size(); i ++)
    {
        event.setStringValue(lines.at(i));

        if(EventChecker::isWeightOrMetal(event.mEventType))
        {
            DspStatusModel * pDspStatus = mMapDspStatus[event.mDspSeq];
            pDspStatus->setSelectProductSetting(event.mProductSettingSeq);
            pDspStatus->addEvent(event.mEventType, event.mValue, true);
        }
    }

    emit signalCommandWorkingHistoryLoadLine(mEventService.mWorkingEventHistoryPath, mEventService.mWorkingEventHistoryFileName, 1000);
}

void CoreService::onSignalEventEndOfLineWorkingHistory()
{
    qDebug() << "[CoreService::onSignalEventEndOfLineWorkingHistory]Working history is loaded";

    QList<quint64> keys = mMapDspStatus.keys();

    for(int i = 0; i < keys.size(); i ++)
    {
        mMapDspStatus[keys[i]]->setSelectProductSetting(mProductSettingServcie.mCurrentProductSetting.mSeq);
    }

    for(int i = 0; i < mDspConnectionInfoService.mListDspConnection.size(); i ++)
    {
        DspConnectionDto conDto(mDspConnectionInfoService.mListDspConnection.at(i));
        ProductSettingDto psDto(&mProductSettingServcie.mCurrentProductSetting);
        DspSettingDto     dsDto(&mLocalSettingService.mDspSetting);
        emit signalCommandAddDSP(conDto, dsDto, psDto);
    }

    mEventService.addEvent(0, EnumDefine::EventType::APP_EXIT_TYPE, 0);
    mEventService.addEvent(0, EnumDefine::EventType::APP_START_TYPE, 0);

    mDeviceInfoBrodcaster.startBrodcast(&mLocalSettingService.mInformation);
    mMonitoringService.startMonitoringService();

    setState(EnumDefine::ServiceState::SERVICE_STARTED);
}

int CoreService::onCommandAddDSP(quint64 *outSeq, QString ip, quint16 port)
{
    qDebug() << "[CoreService::onCommandAddDSP]";

    int ret = mDspConnectionInfoService.addDspConnection(outSeq, ip, port);

    if(ret != EnumDefine::DatabaseErrorType::DB_NONE_ERROR)
        return ret;

    DspConnectionDto conDto; conDto.mDspSeq = *outSeq; conDto.mIp = ip; conDto.mPort = port;
    ProductSettingDto psDto(&mProductSettingServcie.mCurrentProductSetting);
    DspSettingDto     dsDto(&mLocalSettingService.mDspSetting);

    DspStatusModel * pDspStatus = new DspStatusModel(this); pDspStatus->mSeq = *outSeq;
    mMapDspStatus.insert(*outSeq,pDspStatus);

    emit signalCommandAddDSP(conDto, dsDto, psDto);

    return ret;
}

int CoreService::onCommandRemoveDsp(quint64  dspSeq)
{
    qDebug() << "[CoreService::onCommandRemoveDsp]";

    int ret = mDspConnectionInfoService.removeDspConnection(dspSeq);

    if(ret != EnumDefine::DatabaseErrorType::DB_NONE_ERROR)
        return ret;

    emit signalCommandRemoveDsp(dspSeq);

    return ret;
}

int CoreService::onCommandModifyDSP(quint64  dspSeq, QString ip, quint16 port)
{
    qDebug() << "[CoreService::onCommandModifyDSP]";

    int ret = mDspConnectionInfoService.editDspConnection(dspSeq, ip, port);

    if(ret != EnumDefine::DatabaseErrorType::DB_NONE_ERROR)
        return ret;

    DspConnectionDto conDto; conDto.mDspSeq = dspSeq; conDto.mIp = ip; conDto.mPort = port;
    emit signalCommandModifyDSP(conDto);

    return ret;
}

void CoreService::onCommandSendZeroCmd(quint64 dspSeq)
{
    qDebug() << "[CoreService::onCommandSendZeroCmd]";

    emit signalCommandSendZeroCmd(dspSeq);
}

void CoreService::onCommandSendWeightCaribCmd(quint64  dspSeq, quint16 value)
{
    qDebug() << "[CoreService::onCommandSendWeightCaribCmd] << value";

    emit signalCommandSendWeightCaribCmd(dspSeq, value);
}

void CoreService::onCommandSendRunCmd(quint64  dspSeq, quint16 value)
{
    qDebug() << "[CoreService::onCommandSendRunCmd]" << value;

    emit signalCommandSendRunCmd(dspSeq, value);
}

void CoreService::onCommandSendWeightCheckerGraphOnCmd(quint64  dspSeq, bool value)
{
    qDebug() << "[CoreService::onCommandSendWeightCheckerGraphOnCmd]" << value;

    emit signalCommandSendWeightCheckerGraphOnCmd(dspSeq, value);
}

void CoreService::onCommandSendMetalDetectorGraphOnCmd(quint64  dspSeq, bool value)
{
    qDebug() << "[CoreService::onCommandSendMetalDetectorGraphOnCmd]" << value;

    emit signalCommandSendMetalDetectorGraphOnCmd(dspSeq, value);
}

void CoreService::onCommandSendDeviceIDCmd(quint64  dspSeq, quint32 value)
{
    qDebug() << "[CoreService::onCommandSendDeviceIDCmd]" << value;

    emit signalCommandSendDeviceIDCmd(dspSeq, value);
}

void CoreService::onCommandEditDspSetting(quint32 lampTime, quint32 buzzerTime, quint32 speedConverter, quint16 motorDirection, quint16 sensorLength, quint16 distanceToRejector,
                                          bool mdPhotoIsOn, bool wcPhotoIsOn, quint32 rejectorReadyTime, quint32 rejectorRunTimeRatio, quint32 staticFactor, quint32 scaler,
                                          quint32 displayStability, quint32 measureCueSign, quint32 minStaticWeight, quint32 minDynamicWeight, quint16 mode, quint16 distanceBtwSensor,
                                          quint32 detectDetectTime, quint32 runDetectTime, quint16 distanceToWeightChecker, quint16 distancePhotoToSensor, quint32 signalDelayTime,
                                          quint32 staticStandardWeight, quint32 dynamicBaseWeight, quint16 sensorCnt)
{
    qDebug() << "[CoreService::onCommandEditDspSetting]";

    mLocalSettingService.setDspSetting(lampTime, buzzerTime, speedConverter, motorDirection, sensorLength, distanceToRejector, mdPhotoIsOn, wcPhotoIsOn, rejectorReadyTime, rejectorRunTimeRatio,
                                       staticFactor, scaler, displayStability, measureCueSign, minStaticWeight, minDynamicWeight, mode, distanceBtwSensor, detectDetectTime, runDetectTime,
                                       distanceToWeightChecker, distancePhotoToSensor, signalDelayTime, staticStandardWeight, dynamicBaseWeight, sensorCnt);

    DspSettingDto dspDto(&mLocalSettingService.mDspSetting);
    emit signalCommandSendDspSetting(INVALID_ULONGLONG, dspDto);
}

int CoreService::onCommandAddProductSetting(quint64 *outSeq, quint16 no, QString name, quint16 length, quint16 speed, quint32 motorAccelerationTime, quint32 underWeight, quint32 underWarningWeight,
                                                 quint32 normalWeight, quint32 overWarningWeight, quint32 overWeight, quint32 tareWeight, quint16 wcNGMotion, quint32 dynamicFactor,
                                                 quint16 mdSenstivity, quint16 mdNGMotion)
{
    qDebug() << "[CoreService::onCommandAddProductSetting]";

    int ret = mProductSettingServcie.addProductSetting(outSeq, no, name, length, speed, motorAccelerationTime, underWeight, underWarningWeight, normalWeight, overWarningWeight, overWeight,
                                                       tareWeight, wcNGMotion, dynamicFactor, mdSenstivity, mdNGMotion);

    if(ret != EnumDefine::DatabaseErrorType::DB_NONE_ERROR)
        return ret;

    mEventService.addProductSetting(mProductSettingServcie.findProductSettingBySeq(*outSeq));

    return ret;
}
int CoreService::onCommandRemoveProductSetting(quint64 seq)
{
    qDebug() << "[CoreService::onCommandRemoveProductSetting]";

    return mProductSettingServcie.removeProductSetting(seq);
}
int CoreService::onCommandEditProductSetting(quint64 seq, quint16 no, QString name, quint16 length, quint16 speed, quint32 motorAccelerationTime, quint32 underWeight, quint32 underWarningWeight,
                                 quint32 normalWeight, quint32 overWarningWeight, quint32 overWeight, quint32 tareWeight, quint16 wcNGMotion, quint32 dynamicFactor,
                                 quint16 mdSenstivity, quint16 mdNGMotion)
{
    qDebug() << "[CoreService::onCommandEditProductSetting]";

    int ret = mProductSettingServcie.editProductSetting(seq, no, name, length, speed, motorAccelerationTime, underWeight, underWarningWeight, normalWeight, overWarningWeight, overWeight,
                                                        tareWeight, wcNGMotion, dynamicFactor, mdSenstivity, mdNGMotion);

    if(ret != EnumDefine::DatabaseErrorType::DB_NONE_ERROR)
        return ret;

    mEventService.editProductSetting(&mProductSettingServcie.mCurrentProductSetting);

    if(seq == mProductSettingServcie.mCurrentProductSetting.mSeq)
    {
        ProductSettingDto psDto(&mProductSettingServcie.mCurrentProductSetting);
        emit signalCommandSendProductSetting(INVALID_ULONGLONG, psDto);
    }
    return ret;
}

int CoreService::onCommandSelectProductSetting(quint64 seq)
{
    qDebug() << "[CoreService::onCommandSelectProductSetting]";

    int ret = EnumDefine::DatabaseErrorType::DB_NONE_ERROR;

    if(mProductSettingServcie.mCurrentProductSetting.mSeq == seq)
        return ret;

    ret = mProductSettingServcie.selectProductSetting(seq);

    if(ret != EnumDefine::DatabaseErrorType::DB_NONE_ERROR)
        return ret;

    mEventService.selectProductSetting(&mProductSettingServcie.mCurrentProductSetting);

    QList<quint64> keys = mMapDspStatus.keys();

    for(int i = 0; i < keys.size(); i ++)
    {
        mMapDspStatus[keys[i]]->setSelectProductSetting(mProductSettingServcie.mCurrentProductSetting.mSeq);
    }

    ProductSettingDto psDto(&mProductSettingServcie.mCurrentProductSetting);
    emit signalCommandSendProductSetting(INVALID_ULONGLONG, psDto);

    return ret;
}

void CoreService::onSignalEventChangedIsConnect(quint64 dspSeq, bool value)
{
    qDebug() << "[CoreService::onSignalEventChangedIsConnect]" << value;

    mMapDspStatus[dspSeq]->setIsComm(value);
}

void CoreService::onSignalEventChangedRemoteDeviceSetting (quint64 dspSeq, DspSettingDto value)
{
    qDebug() << "[CoreService::onSignalEventChangedRemoteDeviceSetting]";

    DspSettingModel * pTemp = value.toDspSettingModel();
    mMapDspStatus[dspSeq]->setRemoteDspSetting(pTemp, mLocalSettingService.mDspSetting.isEqual(pTemp));
    delete pTemp;
}

void CoreService::onSignalEventChangedRemoteProductSetting(quint64 dspSeq, ProductSettingDto value)
{
    qDebug() << "[CoreService::onSignalEventChangedRemoteProductSetting]";

    ProductSettingModel * pTemp = value.toProductSettingModel();
    mMapDspStatus[dspSeq]->setRemoteProductSetting(pTemp, mProductSettingServcie.mCurrentProductSetting.isEqual(pTemp));
    delete pTemp;
}

void CoreService::onSignalEventChangedDeviceStatus(quint64 dspSeq, DspStatusDto value)
{
    DspStatusModel *pDspStatus = mMapDspStatus[dspSeq];

    if((value.mDspStatus.mRun == EnumDefine::RunState::STOP && pDspStatus->mRun != EnumDefine::RunState::STOP) || (value.mDspStatus.mRun != EnumDefine::RunState::STOP && pDspStatus->mRun == EnumDefine::RunState::STOP))
    {
        mEventService.addEvent(dspSeq, value.mDspStatus.mRun != EnumDefine::RunState::STOP ? EnumDefine::EventType::RUN_TYPE : EnumDefine::EventType::STOP_TYPE, 0);
    }

    mMapDspStatus[dspSeq]->setDspStatus(value);
}

void CoreService::onSignalEventChangedDeviceInfo(quint64 dspSeq, DspInfoDto value)
{
    //qDebug() << "[CoreService::onSignalEventChangedDeviceInfo]";

    mMapDspStatus[dspSeq]->setDspInfo(value);
}

void CoreService::onSignalEventAddedEvent(quint64 dspSeq, EventDto value)
{
    if(value.mEvent.mEventType == EnumDefine::EventType::WEIGHT_DYNAMIC_CARI_TYPE)
    {
        onCommandEditProductSetting(mProductSettingServcie.mCurrentProductSetting.mSeq                  ,
                                    mProductSettingServcie.mCurrentProductSetting.mNo                   ,
                                    mProductSettingServcie.mCurrentProductSetting.mName                 ,
                                    mProductSettingServcie.mCurrentProductSetting.mLength               ,
                                    mProductSettingServcie.mCurrentProductSetting.mSpeed                ,
                                    mProductSettingServcie.mCurrentProductSetting.mMotorAccelerationTime,
                                    mProductSettingServcie.mCurrentProductSetting.mUnderWeight          ,
                                    mProductSettingServcie.mCurrentProductSetting.mUnderWarningWeight   ,
                                    mProductSettingServcie.mCurrentProductSetting.mNormalWeight         ,
                                    mProductSettingServcie.mCurrentProductSetting.mOverWarningWeight    ,
                                    mProductSettingServcie.mCurrentProductSetting.mOverWeight           ,
                                    mProductSettingServcie.mCurrentProductSetting.mTareWeight           ,
                                    mProductSettingServcie.mCurrentProductSetting.mWCNGMotion           ,
                                    value.mEvent.mEventValue                                            ,
                                    mProductSettingServcie.mCurrentProductSetting.mMDSenstivity         ,
                                    mProductSettingServcie.mCurrentProductSetting.mMDNGMotion           );
    }
    else if(value.mEvent.mEventType == EnumDefine::EventType::WEIGHT_STATIC_CARI_TYPE)
    {
        onCommandEditDspSetting(mLocalSettingService.mDspSetting.mLampTime               ,
                                mLocalSettingService.mDspSetting.mBuzzerTime             ,
                                mLocalSettingService.mDspSetting.mSpeedConverter         ,
                                mLocalSettingService.mDspSetting.mMotorDirection         ,
                                mLocalSettingService.mDspSetting.mSensorLength           ,
                                mLocalSettingService.mDspSetting.mDistanceToRejector     ,
                                mLocalSettingService.mDspSetting.mMDPhotoIsOn            ,
                                mLocalSettingService.mDspSetting.mWCPhotoIsOn            ,
                                mLocalSettingService.mDspSetting.mRejectorReadyTime      ,
                                mLocalSettingService.mDspSetting.mRejectorRunTimeRatio   ,
                                value.mEvent.mEventValue                                 ,
                                mLocalSettingService.mDspSetting.mScaler                 ,
                                mLocalSettingService.mDspSetting.mDisplayStability       ,
                                mLocalSettingService.mDspSetting.mMeasureCueSign         ,
                                mLocalSettingService.mDspSetting.mMinStaticWeight        ,
                                mLocalSettingService.mDspSetting.mMinDynamicWeight       ,
                                mLocalSettingService.mDspSetting.mMode                   ,
                                mLocalSettingService.mDspSetting.mDistanceBtwSensor      ,
                                mLocalSettingService.mDspSetting.mDetectDetectTime       ,
                                mLocalSettingService.mDspSetting.mRunDetectTime          ,
                                mLocalSettingService.mDspSetting.mDistanceToWeightChecker,
                                mLocalSettingService.mDspSetting.mDistancePhotoToSensor  ,
                                mLocalSettingService.mDspSetting.mSignalDelayTime        ,
                                mLocalSettingService.mDspSetting.mStaticStandardWeight   ,
                                mLocalSettingService.mDspSetting.mDynamicBaseWeight      ,
                                mLocalSettingService.mDspSetting.mSensorCnt              );
    }

    mMapDspStatus[dspSeq]->addEvent(value.mEvent.mEventType, value.mEvent.mEventValue, false);

    if(EventChecker::isCheckEvent(value.mEvent.mEventType) == false)
        mEventService.addEvent(dspSeq, value.mEvent.mEventType, value.mEvent.mEventValue);
}

void CoreService::onSignalEventAddedWeightCheckerGraph(quint64 dspSeq, QByteArray value)
{
    emit signalEventAddedWeightCheckerGraph(dspSeq, value);
}

void CoreService::onSignalEventAddedMetalDetectorGraph(quint64 dspSeq, QByteArray value)
{
    emit signalEventAddedMetalDetectorGraph(dspSeq, value);
}

void CoreService::onCommandFactoryReset()
{
    qDebug() << "[CoreService::onCommandFactoryReset]";

    setFactoryResetState(EnumDefine::FactoryResetState::FACTORYRESET_START_ALL);
    emit signalCommandSendFactoryResetCmd(INVALID_ULONGLONG);
}

void CoreService::onSignalEventCompletedFactoryReset(quint64 dspSeq)
{
    qDebug() << "[CoreService::onSignalEventCompletedFactoryReset]";

    QList<quint64> keys = mMapDspStatus.keys();

    if(mMapDspStatus.contains(dspSeq))
        mMapDspStatus[dspSeq]->setFactoryReset(true);

    for(int i = 0; i < keys.size(); i ++)
    {
        if(mMapDspStatus[dspSeq]->mFactoryReset == false)
            return;
    }

    if(mFactoryResetState == EnumDefine::FactoryResetState::FACTORYRESET_START_ALL)
        setFactoryResetState(EnumDefine::FactoryResetState::FACTORYRESET_DSP_FOR_ALL);
    else
        setFactoryResetState(EnumDefine::FactoryResetState::FACTORYRESET_DSP_FOR_HIS);

    emit signalCommandDspCommunityStop();
}

void CoreService::onSignalCommandDspCommunityStop()
{
    qDebug() << "[CoreService::onSignalCommandDspCommunityStop]";

    if(mFactoryResetState == EnumDefine::FactoryResetState::FACTORYRESET_DSP_FOR_ALL)
    {
        mLocalSettingService.factoryReset();

        setFactoryResetState(EnumDefine::FactoryResetState::FACTORYRESET_LOCAL);

        mDspConnectionInfoService.factoryReset();
        mProductSettingServcie.factoryReset();
        mEventService.factoryReset();
    }
    else
    {
        mEventService.factoryReset();
    }
    setFactoryResetState(EnumDefine::FactoryResetState::FACTORYRESET_HISTORY);
}

void CoreService::onCommandHistoryReset()
{
    qDebug() << "[CoreService::onCommandHistoryReset]";

    setFactoryResetState(EnumDefine::FactoryResetState::FACTORYRESET_START_ONLY_HIS);
    emit signalCommandDspCommunityStop();
}

void CoreService::onCommandWorkReset()
{
    qDebug() << "[CoreService::onCommandWorkReset]";

    mEventService.workReset();
    QList<quint64> keys = mMapDspStatus.keys();

    for(int i = 0; i < keys.size(); i ++)
    {
        mMapDspStatus[keys[i]]->reset();
    }
}

CoreService::CoreService(QObject *parent) : QObject(parent)
{
    qDebug() << "[CoreService::Create]";
    mpSelf = this;

    connect(&mTimer                   , SIGNAL(timeout()), this,SLOT(onUpdateTimer()));
    connect(&mProductSettingServcie   , SIGNAL(signalEventCompleteLoad(       )), this, SLOT(onSignalEventCompleteLoadProductSetting (       )));
    connect(&mDspConnectionInfoService, SIGNAL(signalEventCompleteLoad(       )), this, SLOT(onSignalEventCompleteLoadDspConnection  (       )));

    connect(this, SIGNAL(signalCommandWorkingHistoryLoadLine   (QString, QString, int)), &mWorkingHistoryLoader   , SLOT(onCommandLoadMultiLine   (QString, QString, int)));
    connect(&mWorkingHistoryLoader    , SIGNAL(signalEventLoadedMultiLine(QStringList)), this, SLOT(onSignalEventLoadedLineWorkingHistory   (QStringList)));
    connect(&mWorkingHistoryLoader    , SIGNAL(signalEventEndOfLine   (       )), this, SLOT(onSignalEventEndOfLineWorkingHistory    (       )));

    connect(this, SIGNAL(signalCommandDspCommunityStop              (                          )), &mDspCommunityThread, SLOT(onCommandStopService                   (                          )));
    connect(this, SIGNAL(signalCommandAddDSP(DspConnectionDto, DspSettingDto, ProductSettingDto)), &mDspCommunityThread, SLOT(onCommandAddDSP(DspConnectionDto, DspSettingDto, ProductSettingDto)));
    connect(this, SIGNAL(signalCommandRemoveDsp                     (quint64                   )), &mDspCommunityThread, SLOT(onCommandRemoveDsp                     (quint64                   )));
    connect(this, SIGNAL(signalCommandModifyDSP                     (DspConnectionDto          )), &mDspCommunityThread, SLOT(onCommandModifyDSP                     (DspConnectionDto          )));
    connect(this, SIGNAL(signalCommandSendZeroCmd                   (quint64                   )), &mDspCommunityThread, SLOT(onCommandSendZeroCmd                   (quint64                   )));
    connect(this, SIGNAL(signalCommandSendFactoryResetCmd           (quint64                   )), &mDspCommunityThread, SLOT(onCommandSendFactoryResetCmd           (quint64                   )));
    connect(this, SIGNAL(signalCommandSendWeightCaribCmd            (quint64, quint16          )), &mDspCommunityThread, SLOT(onCommandSendWeightCaribCmd            (quint64, quint16          )));
    connect(this, SIGNAL(signalCommandSendRunCmd                    (quint64, quint16          )), &mDspCommunityThread, SLOT(onCommandSendRunCmd                    (quint64, quint16          )));
    connect(this, SIGNAL(signalCommandSendWeightCheckerGraphOnCmd   (quint64, bool             )), &mDspCommunityThread, SLOT(onCommandSendWeightCheckerGraphOnCmd   (quint64, bool             )));
    connect(this, SIGNAL(signalCommandSendMetalDetectorGraphOnCmd   (quint64, bool             )), &mDspCommunityThread, SLOT(onCommandSendMetalDetectorGraphOnCmd   (quint64, bool             )));
    connect(this, SIGNAL(signalCommandSendDeviceIDCmd               (quint64, quint32          )), &mDspCommunityThread, SLOT(onCommandSendDeviceIDCmd               (quint64, quint32          )));
    connect(this, SIGNAL(signalCommandSendDspSetting                (quint64, DspSettingDto    )), &mDspCommunityThread, SLOT(onCommandSendDspSetting                (quint64, DspSettingDto    )));
    connect(this, SIGNAL(signalCommandSendProductSetting            (quint64, ProductSettingDto)), &mDspCommunityThread, SLOT(onCommandSendProductSetting            (quint64, ProductSettingDto)));

    connect(&mDspCommunityThread, SIGNAL(signalEventStopped                    (                           )), this, SLOT(onSignalCommandDspCommunityStop         (                           )));
    connect(&mDspCommunityThread, SIGNAL(signalEventChangedIsConnect           (quint64, bool              )), this, SLOT(onSignalEventChangedIsConnect           (quint64, bool              )));
    connect(&mDspCommunityThread, SIGNAL(signalEventCompletedFactoryReset      (quint64                    )), this, SLOT(onSignalEventCompletedFactoryReset      (quint64                    )));
    connect(&mDspCommunityThread, SIGNAL(signalEventChangedRemoteDeviceSetting (quint64, DspSettingDto     )), this, SLOT(onSignalEventChangedRemoteDeviceSetting (quint64, DspSettingDto     )));
    connect(&mDspCommunityThread, SIGNAL(signalEventChangedRemoteProductSetting(quint64, ProductSettingDto )), this, SLOT(onSignalEventChangedRemoteProductSetting(quint64, ProductSettingDto )));
    connect(&mDspCommunityThread, SIGNAL(signalEventChangedDeviceStatus        (quint64, DspStatusDto      )), this, SLOT(onSignalEventChangedDeviceStatus        (quint64, DspStatusDto      )));
    connect(&mDspCommunityThread, SIGNAL(signalEventChangedDeviceInfo          (quint64, DspInfoDto        )), this, SLOT(onSignalEventChangedDeviceInfo          (quint64, DspInfoDto        )));
    connect(&mDspCommunityThread, SIGNAL(signalEventAddedEvent                 (quint64, EventDto          )), this, SLOT(onSignalEventAddedEvent                 (quint64, EventDto          )));
    connect(&mDspCommunityThread, SIGNAL(signalEventAddedWeightCheckerGraph    (quint64, QByteArray        )), this, SLOT(onSignalEventAddedWeightCheckerGraph    (quint64, QByteArray        )));
    connect(&mDspCommunityThread, SIGNAL(signalEventAddedMetalDetectorGraph    (quint64, QByteArray        )), this, SLOT(onSignalEventAddedMetalDetectorGraph    (quint64, QByteArray        )));

    mTimer.start(500);
}

void CoreService::onUpdateTimer()
{
    QString currTimeSec = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
    QString currTimeMsec = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss.zzz");

    mEventService.setLastDateTime(currTimeMsec);
    //mLocalSettingService.setProcLastTime(currTimeMsec);
    setClock(currTimeSec);
}
