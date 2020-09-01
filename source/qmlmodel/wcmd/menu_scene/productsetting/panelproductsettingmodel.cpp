#include "panelproductsettingmodel.h"

#include "source/helper/databasehelper.h"

PanelProductSettingModel::PanelProductSettingModel(QObject *parent) : QObject(parent)
{
    connect(this, SIGNAL(signalCommandSaveProductSetting    (void *, int, ProductSetting)) ,WCMDService::getInstance(), SLOT(onCommandSaveProductSetting  (void *, int, ProductSetting) ));
    connect(this, SIGNAL(signalCommandSelectProductSetting  (void *, quint16)            ) ,WCMDService::getInstance(), SLOT(onCommandSelectProductSetting(void *, quint16)             ));

    connect(&mEditViewItemModel, SIGNAL(signalEventChangedSeq    (quint16)) ,this, SLOT(onSignalEventChangedSeq  (quint16) ));

    connect(WCMDService::getInstance(), SIGNAL(signalEventChangedProductSetting        (int, ProductSetting)        ), this, SLOT(onSignalEventChangedProductSetting        (int, ProductSetting)         ));
    connect(WCMDService::getInstance(), SIGNAL(signalEventChangedSelectedProductSetting(ProductSetting)             ), this, SLOT(onSignalEventChangedSelectedProductSetting(ProductSetting)              ));
    connect(WCMDService::getInstance(), SIGNAL(signalResultSaveProductSetting          (void *, int, ProductSetting)), this, SLOT(onSignalResultSaveProductSetting          (void *, int, ProductSetting) ));

    QList<ProductSetting>listPs = DatabaseHelper::getInstance()->findAllProductSetting("QML_DB_CON");

    for(int i = 0; i < listPs.size(); i ++)
    {
        ProductSettingItemModel * pItemModel = new ProductSettingItemModel(this);
        pItemModel->setData(listPs.at(i));

        mListProductSetting.append(pItemModel);
    }

    setSelectedProductSeq(WCMDService::getInstance()->mProductSetting.mSeq);

    if(listPs.size() > 0)
    {
        mEditViewItemModel.setData(listPs.at(0));
    }
    else
    {
        mEditViewItemModel.setIsRemoved(true);
        mEditViewItemModel.reset();
    }
}

ProductSettingItemModel * PanelProductSettingModel::onCommandGetItemModel    (int idx)
{
    return mListProductSetting.at(idx);
}

ProductSettingItemModel * PanelProductSettingModel::onCommandFindItemModel   (quint16 seq)
{
    for(int i = 0 ; i < mListProductSetting.size(); i ++)
    {
        if(mListProductSetting.at(i)->mSeq == seq)
            return mListProductSetting.at(i);
    }
    return nullptr;
}

ProductSettingItemModel * PanelProductSettingModel::onCommandGetEditViewItemModel (           )
{
    return &mEditViewItemModel;
}

void PanelProductSettingModel::onCommandSetLookProduct  (quint16 seq)
{
    if(mEditViewItemModel.getSeq() == seq)
        return;

    ProductSettingItemModel * pItemModel = onCommandFindItemModel(seq);

    if(pItemModel != nullptr)
        mEditViewItemModel.setData(pItemModel->mProductSetting);
}

void PanelProductSettingModel::onCommandSetSelectProduct(quint16 seq)
{
    emit signalCommandSelectProductSetting(this, seq);//setSelectedProductSeq(seq);
}

void PanelProductSettingModel::onCommandAddProduct           (           )
{
    ProductSetting newProduct = DatabaseHelper::getInstance()->newProductSetting("QML_DB_CON");

    newProduct.mDynamicFactor = WCMDService::getInstance()->mDeviceSetting.mDynamicFactor;
    mEditViewItemModel.setNewSetting(newProduct);
    //mEditViewItemModel.setIsNew(true);
    //mEditViewItemModel.reset();
}

void PanelProductSettingModel::onCommandApplyProduct         (           )
{
    ProductSetting ps = mEditViewItemModel.getModifiedProductSetting();

    if(mEditViewItemModel.getNo() < 1)
    {
        emit signalEventResultSaveProductSetting(EnumDefine::DatabaseErrorType::EMPTY_PRODUCT_NO);
        return;
    }

    if(!(mEditViewItemModel.getUnderWeight()          <= mEditViewItemModel.getUnderWarningWeight() &&
       mEditViewItemModel.getUnderWarningWeight()   <  mEditViewItemModel.getNormalWeight() &&
       mEditViewItemModel.getNormalWeight()         <  mEditViewItemModel.getOverWarningWeight() &&
       mEditViewItemModel.getOverWarningWeight()    <=  mEditViewItemModel.getOverWeight()))
    {
        emit signalEventResultSaveProductSetting(EnumDefine::DatabaseErrorType::INVAILD_WEIGHT_CHECKER_SETTING);
        return;
    }

    if(mEditViewItemModel.getIsNew())
        emit signalCommandSaveProductSetting(this, EnumDefine::DataBaseWriteMode::ADD, ps);
    else
        emit signalCommandSaveProductSetting(this, EnumDefine::DataBaseWriteMode::EDIT, ps);
}
void PanelProductSettingModel::onCommandCancleProduct        (           )
{
    if(mEditViewItemModel.getIsNew())
    {
        if(mListProductSetting.size() > 0)
        {
            mEditViewItemModel.setData(mListProductSetting.at(0)->mProductSetting);
        }
        else
        {
            mEditViewItemModel.setIsRemoved(true);
            mEditViewItemModel.reset();
        }
    }
    else
    {
        mEditViewItemModel.reset();
    }
}
void PanelProductSettingModel::onCommandRemoveProduct        (           )
{
    ProductSetting ps = mEditViewItemModel.getModifiedProductSetting();

    emit signalCommandSaveProductSetting(this, EnumDefine::DataBaseWriteMode::REMOVE, ps);
}

void PanelProductSettingModel::onSignalEventChangedProductSetting               (int type, ProductSetting value)
{
    ProductSettingItemModel * pItem = onCommandFindItemModel(value.mSeq);

    if(type == EnumDefine::DataBaseWriteMode::REMOVE)
    {
        if(pItem != nullptr)
            mListProductSetting.removeOne(pItem);

        if(value.mSeq == mEditViewItemModel.getSeq())
        {
            mEditViewItemModel.setIsRemoved(true);
            mEditViewItemModel.reset();
        }

        emit signalEventRemoveProductSetting(value.mSeq);
    }
    else if(type == EnumDefine::DataBaseWriteMode::ADD)
    {

        ProductSettingItemModel * pItemModel = new ProductSettingItemModel(this);
        pItemModel->setData(value);

        mListProductSetting.append(pItemModel);

        emit signalEventAddProductSetting(value.mSeq);
    }
    else if(type == EnumDefine::DataBaseWriteMode::EDIT)
    {
        if(pItem != nullptr)
            pItem->setData(value);
    }


}
void PanelProductSettingModel::onSignalEventChangedSelectedProductSetting       (ProductSetting value)
{
    setSelectedProductSeq(value.mSeq);
}
void PanelProductSettingModel::onSignalResultSaveProductSetting                 (void * sender, int error, ProductSetting       value)
{
    if(sender != this)
        return;

    if(error == EnumDefine::DatabaseErrorType::DB_NONE_ERROR)
        mEditViewItemModel.setData(value);

    emit signalEventResultSaveProductSetting(error);
}

void PanelProductSettingModel::onSignalEventChangedSeq(quint16 value)
{
    emit signalEventChangedLookProductSeq(value);
}
