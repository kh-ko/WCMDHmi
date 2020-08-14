#include "mainscenemodel.h"
#include <QDateTime>
#include "source/helper/localsetting.h"

MainSceneModel::MainSceneModel(QObject *parent) : QObject(parent)
{
    WCMDService * wcmdService = WCMDService::getInstance();

    connect(this, SIGNAL(signalCommandSetRun(quint16, quint16)),wcmdService, SLOT(onCommandSetRun(quint16, quint16)));

    connect(wcmdService, SIGNAL(signalEventChangedInformation           (Information)),                 this, SLOT(onSignalEventChangedInformation         (Information))                      );
    connect(wcmdService, SIGNAL(signalEventChangedIsConnect             (quint16, bool)),               this, SLOT(onSignalEventChangedIsConnect           (quint16, bool))                    );
    connect(wcmdService, SIGNAL(signalEventChangedRemoteDeviceSetting   (quint16, DeviceSetting)),      this, SLOT(onSignalEventChangedRemoteDeviceSetting (quint16, DeviceSetting))           );
    connect(wcmdService, SIGNAL(signalEventChangedRemoteProductSetting  (quint16, ProductSetting)),     this, SLOT(onSignalEventChangedRemoteProductSetting(quint16, ProductSetting))          );
    connect(wcmdService, SIGNAL(signalEventChangedDeviceStatus          (quint16, DeviceStatus)),       this, SLOT(onSignalEventChangedDeviceStatus        (quint16, DeviceStatus))            );
    connect(wcmdService, SIGNAL(signalEventChangedDsp                   (int, DeviceConnectionInfo)),   this, SLOT(onSignalEventChangedDsp                 (int, DeviceConnectionInfo))        );

    connect(&mTimer, SIGNAL(timeout()), this,SLOT(onUpdateTimer()));

    Information info = wcmdService->mInfomation;

    mCompany = info.mCompany;
    mTel     = info.mTel;

    QList<DSPManager *> listDsp = wcmdService->getAllDSPManager();

    setIsRun(true);
    setIsComm(true);
    setIsAlarm(false);
    setIsSensorAlarm(false);
    setIsPhotoAlarm(false);
    setIsMortorAlarm(false);

    for(int i = 0 ; i < listDsp.size(); i ++)
    {
        if(listDsp.at(i)->mRun == EnumDefine::RunState::STOP)
            setIsRun(false);

        if(listDsp.at(i)->mIsConnect == false)
            setIsComm(false);

        if(listDsp.at(i)->mMDAlarm != EnumDefine::AlarmType::NONE_ALARM || listDsp.at(i)->mWCAlarm != EnumDefine::AlarmType::NONE_ALARM)
        {
            setIsAlarm(true);
            setIsSensorAlarm((listDsp.at(i)->mMDAlarm & EnumDefine::AlarmType::SENSOR_ALARM) | (listDsp.at(i)->mWCAlarm & EnumDefine::AlarmType::SENSOR_ALARM));
            setIsPhotoAlarm((listDsp.at(i)->mMDAlarm & EnumDefine::AlarmType::PHOTO_ALARM) | (listDsp.at(i)->mWCAlarm & EnumDefine::AlarmType::PHOTO_ALARM));
            setIsMortorAlarm((listDsp.at(i)->mMDAlarm & EnumDefine::AlarmType::MOTOR_ALARM) | (listDsp.at(i)->mWCAlarm & EnumDefine::AlarmType::MOTOR_ALARM));
        }
    }

    mTimer.start(500);
}

void MainSceneModel::onSignalEventChangedInformation  (Information value)
{
    setCompany(value.mCompany);
    setTel(value.mTel);
}

void MainSceneModel::onSignalEventChangedIsConnect    (quint16 deviceSeq, bool value)
{
    WCMDService * wcmdService = WCMDService::getInstance();
    bool isConnect = true;
    QList<DSPManager *> listDsp = wcmdService->getAllDSPManager();


    for(int i = 0 ; i < listDsp.size(); i ++)
    {
        if(listDsp.at(i)->mIsConnect == false)
            isConnect  = false;
    }

    setIsComm(isConnect);
}

void MainSceneModel::onSignalEventChangedDeviceStatus (quint16 deviceSeq, DeviceStatus value)
{
    /*
    WCMDService * wcmdService = WCMDService::getInstance();
    bool isAlarm = false;
    bool isRun = true;
    QList<DSPManager *> listDsp = wcmdService->getAllDSPManager();


    for(int i = 0 ; i < listDsp.size(); i ++)
    {
        if(listDsp.at(i)->mIsRun == false)
            isRun = false;

        if(listDsp.at(i)->mMDAlarm != EnumDefine::AlarmType::NONE_ALARM || listDsp.at(i)->mWCAlarm != EnumDefine::AlarmType::NONE_ALARM)
            isAlarm  = true;
    }

    setIsAlarm(isAlarm);
    setIsRun(isRun);
    */

    DeviceConnectionInfo tempDci;
    onSignalEventChangedDsp(0xffff,tempDci);
}

void MainSceneModel::onSignalEventChangedRemoteDeviceSetting    (quint16 deviceSeq, DeviceSetting value)
{
    DeviceConnectionInfo tempDci;
    onSignalEventChangedDsp(0xffff,tempDci);
}
void MainSceneModel::onSignalEventChangedRemoteProductSetting   (quint16 deviceSeq, ProductSetting value)
{
    DeviceConnectionInfo tempDci;
    onSignalEventChangedDsp(0xffff,tempDci);
}

void MainSceneModel::onSignalEventChangedDsp          (int type, DeviceConnectionInfo value)
{
    WCMDService * wcmdService = WCMDService::getInstance();
    QList<DSPManager *> listDsp = wcmdService->getAllDSPManager();

    setIsRun(true);
    setIsComm(true);
    setIsAlarm(false);
    setIsSensorAlarm(false);
    setIsPhotoAlarm(false);
    setIsMortorAlarm(false);

    for(int i = 0 ; i < listDsp.size(); i ++)
    {
        if(listDsp.at(i)->mRun == EnumDefine::RunState::STOP)
            setIsRun(false);

        if(listDsp.at(i)->mIsConnect == false)
            setIsComm(false);

        if(listDsp.at(i)->mMDAlarm != EnumDefine::AlarmType::NONE_ALARM
        || listDsp.at(i)->mWCAlarm != EnumDefine::AlarmType::NONE_ALARM
        || listDsp.at(i)->mIsDeviceSettingAlarm == true
        || listDsp.at(i)->mIsProductSettingAlarm == true)
        {
            setIsAlarm(true);

            setIsSensorAlarm((listDsp.at(i)->mMDAlarm & EnumDefine::AlarmType::SENSOR_ALARM) | (listDsp.at(i)->mWCAlarm & EnumDefine::AlarmType::SENSOR_ALARM));
            setIsPhotoAlarm((listDsp.at(i)->mMDAlarm & EnumDefine::AlarmType::PHOTO_ALARM) | (listDsp.at(i)->mWCAlarm & EnumDefine::AlarmType::PHOTO_ALARM));
            setIsMortorAlarm((listDsp.at(i)->mMDAlarm & EnumDefine::AlarmType::MOTOR_ALARM) | (listDsp.at(i)->mWCAlarm & EnumDefine::AlarmType::MOTOR_ALARM));
        }
    }
}

void MainSceneModel::onUpdateTimer()
{
    QString currTime = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
    setClock(currTime);

    LocalSetting::getInstance()->setLastDateTime();
}

bool MainSceneModel::onCommandComparePwd(QString value)
{
    QString pwd =  LocalSetting::getInstance()->getDeviceSetting().mPassword;

    if(value == pwd)
        return true;

    return false;
}

bool MainSceneModel::onCommandCompareAdminPwd(QString value)
{
    if(value == "7071")
        return true;

    return false;
}

void MainSceneModel::onCommandSetRun(bool value)
{
    bool isCheckup = false;

    WCMDService * wcmdService = WCMDService::getInstance();
    QList<DSPManager *> listDsp = wcmdService->getAllDSPManager();

    if(value == false)
    {
        emit signalCommandSetRun(0xffff, EnumDefine::RunState::STOP);
        return;
    }

    for(int i = 0 ; i < listDsp.size(); i ++)
    {
        if(listDsp.at(i)->mRun == EnumDefine::RunState::CHECKUP_RUN)
            isCheckup = true;
    }

    if(isCheckup)
    {
        qDebug() << "onCommandSetRun() in checkup mode";
        return;
    }

    if(wcmdService->mDeviceSetting.mIsDebugMode)
    {
        emit signalCommandSetRun(0xffff, EnumDefine::RunState::DETECT_OFF_RUN);
    }
    else
    {
        emit signalCommandSetRun(0xffff, EnumDefine::RunState::RUN);
    }

}
