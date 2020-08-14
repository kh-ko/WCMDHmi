#include "panelinformationmodel.h"

PanelInformationModel::PanelInformationModel(QObject *parent) : QObject(parent)
{
    connect(this, SIGNAL(signalCommandSaveDeviceSetting(void *, DeviceSetting)), WCMDService::getInstance(), SLOT(onCommandSaveDeviceSetting(void *, DeviceSetting)));
    connect(this, SIGNAL(signalCommandSaveInformation(void *, Information)), WCMDService::getInstance(), SLOT(onCommandSaveInformation(void *, Information)));

    connect(WCMDService::getInstance(), SIGNAL(signalResultSaveDeviceSetting(void *, DeviceSetting)), this, SLOT(onSignalResultSaveDeviceSetting(void *, DeviceSetting)));
    connect(WCMDService::getInstance(), SIGNAL(signalResultSaveInformation(void *, Information)), this, SLOT(onSignalResultSaveInformation(void *, Information)));

    reset();
}

void PanelInformationModel::reset()
{
    Information info = WCMDService::getInstance()->mInfomation;
    DeviceSetting ds = WCMDService::getInstance()->mDeviceSetting;

    setCompany                   (info.mCompany);
    setModel                     (info.mModel);
    setSerialNumber              (info.mSN);
    setDeviceNumber              (info.mDeviceNumber);
    setDspVersion                (info.mDspVersion);
    setHmiVersion                (info.mHMIVersion);
    setPower                     (info.mPower);
    setHomepage                  (info.mHomepage);
    setMaxWeight                 (info.mMaxWeight);
    setSensorLength              (ds.mSensorLength              );
    setDistToRejector            (ds.mDistanceToRejector        );
    setDistBtwSensor             (ds.mDistanceBtwSensor         );
    setDistToWC                  (ds.mDistanceToWeightChecker   );
    setDistBtwPhotoToSensor      (ds.mDistancePhotoToSensor     );

    setIsEditPower               (false);
    setIsEditHomepage            (false);
    setIsEditDeviceNumber        (false);
    setIsEditMaxWeight           (false);
    setIsEditSensorLength        (false);
    setIsEditDistToRejector      (false);
    setIsEditDistBtwSensor       (false);
    setIsEditDistToWC            (false);
    setIsEditDistBtwPhotoToSensor(false);
}
void PanelInformationModel::onSignalResultSaveInformation(void * sender, Information value)
{
    if(sender != this)
        return;

    reset();

    emit signalResultSaveInformation((int)EnumDefine::DatabaseErrorType::DB_NONE_ERROR);
}

void PanelInformationModel::onSignalResultSaveDeviceSetting(void * sender, DeviceSetting value)
{
    if(sender != this)
        return;

    reset();

    emit signalResultSaveDeviceSetting((int)EnumDefine::DatabaseErrorType::DB_NONE_ERROR);
}

void PanelInformationModel::onCommandSave()
{
    Information info = WCMDService::getInstance()->mInfomation;
    DeviceSetting ds = WCMDService::getInstance()->mDeviceSetting;

    info.mPower = mPower;
    info.mHomepage = mHomepage;
    info.mMaxWeight = mMaxWeight;
    info.mDeviceNumber = mDeviceNumber;

    ds.mSensorLength            = getSensorLength        ();
    ds.mDistanceToRejector      = getDistToRejector      ();
    ds.mDistanceBtwSensor       = getDistBtwSensor       ();
    ds.mDistanceToWeightChecker = getDistToWC            ();
    ds.mDistancePhotoToSensor   = getDistBtwPhotoToSensor();

    emit signalCommandSaveDeviceSetting(this, ds);
    emit signalCommandSaveInformation(this, info);
}
void PanelInformationModel::onCommandCancle()
{
    reset();
}


