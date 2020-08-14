#include "panelwcsettinginhomemodel.h"

PanelWCSettingInHomeModel::PanelWCSettingInHomeModel(QObject *parent) : QObject(parent)
{
    connect(this, SIGNAL(signalCommandSaveProductSetting    (void *, int, ProductSetting)) ,WCMDService::getInstance(), SLOT(onCommandSaveProductSetting  (void *, int, ProductSetting) ));

   // connect(WCMDService::getInstance(), SIGNAL(signalEventChanged(ProductSetting)             ), this, SLOT(onSignalEventChangedSelectedProductSetting(ProductSetting)              ));
    connect(WCMDService::getInstance(), SIGNAL(signalResultSaveProductSetting          (void *, int, ProductSetting)), this, SLOT(onSignalResultSaveProductSetting          (void *, int, ProductSetting) ));

    ProductSetting ps = WCMDService::getInstance()->mProductSetting;

    setUnderWeight (ps.mUnderWeight);
    setNormalWeight(ps.mNormalWeight);
    setOverWeight  (ps.mOverWeight);
    setUnderGap    (mNormalWeight - mUnderWeight);
    setOverGap     (mOverWeight - mNormalWeight);

    setIsEditUnderWeight (false);
    setIsEditNormalWeight(false);
    setIsEditOverWeight  (false);
    setIsEditUnderGap    (false);
    setIsEditOverGap     (false);
}

void PanelWCSettingInHomeModel::onCommandSetUnderWeight     (quint32 value)
{
    setUnderWeight(value);
    setUnderGap    (mNormalWeight - mUnderWeight);
}
void PanelWCSettingInHomeModel::onCommandSetNormalWeight    (quint32 value)
{
    setNormalWeight(value);

    if((int)value < mUnderGap)
    {
        setUnderWeight (0);
        setUnderGap    (mNormalWeight - mUnderWeight);
    }
    else
    {
        setUnderWeight (mNormalWeight - mUnderGap);
    }

    if(value + mOverGap > 99999900)
    {
        setOverWeight  (99999900);
        setOverGap    (mOverWeight - mNormalWeight);
    }
    else
    {
        setOverWeight  (mNormalWeight + mOverGap);
    }
}

void PanelWCSettingInHomeModel::onCommandSetOverWeight      (quint32 value)
{
    setOverWeight  (value);
    setOverGap     (mOverWeight - mNormalWeight);
}
void PanelWCSettingInHomeModel::onCommandSetUnderGap        (qint32 value)
{
    if((int)mNormalWeight < value)
    {
        setUnderWeight (0);
        setUnderGap    (mNormalWeight - mUnderWeight);
    }
    else
    {
        setUnderGap    (value);
        setUnderWeight(mNormalWeight - mUnderGap);
    }


}
void PanelWCSettingInHomeModel::onCommandSetOverGap         (qint32 value)
{
    if(mNormalWeight + value > 99999900)
    {
        setOverWeight  (99999900);
        setOverGap    (mOverWeight - mNormalWeight);
    }
    else
    {
        setOverGap    (value);
        setOverWeight(mNormalWeight + mOverGap);
    }
}

void PanelWCSettingInHomeModel::onCommandApply()
{
    if(!(mUnderWeight < mNormalWeight && mNormalWeight < mOverWeight))
    {
        emit signalEventResultSaveProductSetting(EnumDefine::DatabaseErrorType::INVAILD_WEIGHT_CHECKER_SETTING);
        return;
    }

    ProductSetting ps = WCMDService::getInstance()->mProductSetting;

    ps.mUnderWeight = mUnderWeight;
    ps.mUnderWarningWeight = mUnderWeight;
    ps.mNormalWeight = mNormalWeight;
    ps.mOverWarningWeight = mOverWeight;
    ps.mOverWeight = mOverWeight;

    emit signalCommandSaveProductSetting(this, (int)EnumDefine::DataBaseWriteMode::EDIT, ps);
}
void PanelWCSettingInHomeModel::onSignalEventChangedSelectedProductSetting       (ProductSetting       value)
{

}
void PanelWCSettingInHomeModel::onSignalResultSaveProductSetting                 (void * sender, int error, ProductSetting       value)
{
    if(sender != this)
        return;

    setUnderWeight (value.mUnderWeight);
    setNormalWeight(value.mNormalWeight);
    setOverWeight  (value.mOverWeight);
    setUnderGap    (mNormalWeight - mUnderWeight);
    setOverGap     (mOverWeight - mNormalWeight);

    setIsEditUnderWeight (false);
    setIsEditNormalWeight(false);
    setIsEditOverWeight  (false);
    setIsEditUnderGap    (false);
    setIsEditOverGap     (false);

    emit signalEventResultSaveProductSetting(error);
}
