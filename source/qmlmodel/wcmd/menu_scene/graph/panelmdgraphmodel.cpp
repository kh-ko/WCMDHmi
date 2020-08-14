#include "panelmdgraphmodel.h"

PanelMDGraphModel::PanelMDGraphModel(QObject *parent) : QObject(parent)
{
    ProductSetting tempPs;
    DeviceSetting  tempDs = WCMDService::getInstance()->mDeviceSetting;

    onSignalEventChangedSelectedProductSetting(tempPs);

    connect(this, SIGNAL(signalCommandSetMetalDetectorGraphOn(quint16, bool)), WCMDService::getInstance(), SLOT(onCommandSetMetalDetectorGraphOn(quint16, bool)));
    connect(this, SIGNAL(signalCommandSaveProductSetting(void *, int, ProductSetting)), WCMDService::getInstance(), SLOT(onCommandSaveProductSetting(void *, int, ProductSetting)));

    connect(WCMDService::getInstance(), SIGNAL(signalEventChangedProductSetting        (int, ProductSetting)           ),   this, SLOT(onSignalEventChangedProductSetting        (int, ProductSetting)            ));
    connect(WCMDService::getInstance(), SIGNAL(signalEventChangedSelectedProductSetting(ProductSetting)                ),   this, SLOT(onSignalEventChangedSelectedProductSetting(ProductSetting)                 ));
    connect(WCMDService::getInstance(), SIGNAL(signalEventAddedMetalDetectorGraph      (quint16, MetalDetectorGraphData) ), this, SLOT(onSignalEventAddedMetalDetectorGraph      (quint16, MetalDetectorGraphData)));
    connect(WCMDService::getInstance(), SIGNAL(signalResultSaveProductSetting          (void *, int, ProductSetting)          ),   this, SLOT(onSignalResultSaveProductSetting          (void *, int, ProductSetting)            ));

    mSimpleSens01 = tempDs.mSimpleSenstivity01;
    mSimpleSens02 = tempDs.mSimpleSenstivity02;
    mSimpleSens03 = tempDs.mSimpleSenstivity03;
    mSimpleSens04 = tempDs.mSimpleSenstivity04;
    mSimpleSens05 = tempDs.mSimpleSenstivity05;

    for(int i = 0; i < 8; i ++)
    {
        MetalDetectorGraphModel * tempModel = new MetalDetectorGraphModel(this);

        tempModel->setIsRawGraphOn(mIsRawGraphOn);
        tempModel->setRange(mRange);
        tempModel->setSenstivity(mSenstivity);

        mListMDGraphModel.append(tempModel);
    }

    emit signalCommandSetMetalDetectorGraphOn(0xffff, true);
}

PanelMDGraphModel::~PanelMDGraphModel()
{
    emit signalCommandSetMetalDetectorGraphOn(0xffff, false);
}

void PanelMDGraphModel::onCommandRawGraphOn   (bool value)
{
    setIsRawGraphOn(value);

    for(int i = 0; i < mListMDGraphModel.size(); i ++)
    {
        mListMDGraphModel.at(i)->setIsRawGraphOn(value);
    }
}

MetalDetectorGraphModel *   PanelMDGraphModel::onCommandGetGraphModel(int idx   )
{
    return mListMDGraphModel.at(idx);
}

void PanelMDGraphModel::onCommandSetRange     (int value )
{
    setRange(value);

    for(int i = 0; i < mListMDGraphModel.size(); i ++)
    {
        mListMDGraphModel.at(i)->setRange(mRange);
    }
}

void PanelMDGraphModel::onCommandSetSenstivity(quint16 value)
{
    setSenstivity(value);
    setIsEditSenstivity(true);

    for(int i = 0; i < mListMDGraphModel.size(); i ++)
    {
        mListMDGraphModel.at(i)->setSenstivity(getSenstivity());
    }
}

void PanelMDGraphModel::onCommandSetSimpleSens01(){onCommandSetSenstivity(mSimpleSens01);}
void PanelMDGraphModel::onCommandSetSimpleSens02(){onCommandSetSenstivity(mSimpleSens02);}
void PanelMDGraphModel::onCommandSetSimpleSens03(){onCommandSetSenstivity(mSimpleSens03);}
void PanelMDGraphModel::onCommandSetSimpleSens04(){onCommandSetSenstivity(mSimpleSens04);}
void PanelMDGraphModel::onCommandSetSimpleSens05(){onCommandSetSenstivity(mSimpleSens05);}

void PanelMDGraphModel::onCommandApply        (             )
{
    ProductSetting ps = WCMDService::getInstance()->mProductSetting;
    ps.mMDSenstivity = getSenstivity();

    emit signalCommandSaveProductSetting(this, EnumDefine::DataBaseWriteMode::EDIT, ps);
    setIsEditSenstivity(false);
}

void PanelMDGraphModel::onSignalEventChangedProductSetting               (int type, ProductSetting value)
{
    onSignalEventChangedSelectedProductSetting(value);
}

void PanelMDGraphModel::onSignalEventChangedSelectedProductSetting       (ProductSetting  value)
{
    setSenstivity(WCMDService::getInstance()->mProductSetting.mMDSenstivity);

    for(int i = 0; i < mListMDGraphModel.size(); i ++)
    {
        mListMDGraphModel.at(i)->setSenstivity(WCMDService::getInstance()->mProductSetting.mMDSenstivity);
    }
}

void PanelMDGraphModel::onSignalEventAddedMetalDetectorGraph( quint16 deviceSeq, MetalDetectorGraphData value)
{
    int min = 0;
    int max = 0;

    setSensorCnt(value.mData->mSensorCnt);

    for(int i = 0; i < value.mData->mSensorCnt; i ++)
    {
        mListMDGraphModel.at(i)->addPoints(value.mData->mPointCnt, &(value.mData->mArrayPoints[(value.mData->mPointCnt * 2) * i]));
    }


    for(int i = 0; i < value.mData->mSensorCnt; i ++)
    {
        if(min > mListMDGraphModel.at(i)->getMin())
        {
            min = mListMDGraphModel.at(i)->getMin();
        }

        if(max < mListMDGraphModel.at(i)->getMax())
        {
            max = mListMDGraphModel.at(i)->getMax();
        }
    }

    setMax(max);
    setMin(min);

    emit signalEventGraphUpdate();
}

void PanelMDGraphModel::onSignalResultSaveProductSetting(void * sender, int error, ProductSetting ps)
{
    emit signalResultSaveProductSetting(error);
}
