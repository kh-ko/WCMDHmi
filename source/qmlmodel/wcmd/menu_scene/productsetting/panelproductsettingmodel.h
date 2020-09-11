#ifndef PANELPRODUCTSETTINGMODEL_H
#define PANELPRODUCTSETTINGMODEL_H

#include <QObject>
#include <QMap>

#include "source/service/coreservice.h"

#include "source/qmlmodel/wcmd/menu_scene/productsetting/productsettingitemmodel.h"

class PanelProductSettingModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      productCount            READ getProductCount          NOTIFY signalEventChangedProductCount      )
    Q_PROPERTY(quint64  lookProductSeq          READ getLookProductSeq        NOTIFY signalEventChangedLookProductSeq    )
    Q_PROPERTY(quint64  selectedProductSeq      READ getSelectedProductSeq    NOTIFY signalEventChangedSelectedProductSeq)

public:
    CoreService * mpCoreService;
    ProductSettingService * mpPSService;

    ProductSettingItemModel          mEditViewItemModel;
    QList<ProductSettingItemModel *> mListProductSetting;

    quint64 mLookProductSeq;
    quint64 mSelectedProductSeq;

    int     getProductCount      (){return mListProductSetting.size();}
    quint64 getLookProductSeq    (){return mLookProductSeq           ;}
    quint64 getSelectedProductSeq(){return mSelectedProductSeq       ;}

    void setLookProductSeq    (quint64 value){ if(value == mLookProductSeq    )return; mLookProductSeq     = value; emit signalEventChangedLookProductSeq    (value); }
    void setSelectedProductSeq(quint64 value){ if(value == mSelectedProductSeq)return; mSelectedProductSeq = value; emit signalEventChangedSelectedProductSeq(value); }

signals:
    void signalEventChangedProductCount      (int     value);
    void signalEventChangedLookProductSeq    (quint64 value);
    void signalEventChangedSelectedProductSeq(quint64 value);
    void signalEventResultSaveProductSetting (int     error);

public slots:
    Q_INVOKABLE ProductSettingItemModel * onCommandGetItemModel(int idx)
    {
        return mListProductSetting.at(idx);
    }
    Q_INVOKABLE ProductSettingItemModel * onCommandFindItemModel(quint64 seq)
    {
        for(int i = 0 ; i < mListProductSetting.size(); i ++)
        {
            if(mListProductSetting.at(i)->getSeq() == seq)
                return mListProductSetting.at(i);
        }
        return nullptr;
    }
    Q_INVOKABLE ProductSettingItemModel * onCommandGetEditViewItemModel()
    {
        return &mEditViewItemModel;
    }
    Q_INVOKABLE void onCommandSetLookProduct(quint64 seq)
    {
        if(mEditViewItemModel.getSeq() == seq)
            return;

        setLookProductSeq(seq);

        mEditViewItemModel.setData(seq);
    }
    Q_INVOKABLE void onCommandSetSelectProduct(quint64 seq)
    {
        if(getSelectedProductSeq() == seq)
            return;

        mpCoreService->onCommandSelectProductSetting(seq);
    }
    Q_INVOKABLE void onCommandAddProduct()
    {
        ProductSettingModel *pNewProduct = mpPSService->newProductSetting();
        pNewProduct->mDynamicFactor = mpCoreService->mLocalSettingService.mHmiSetting.mDynamicFactor;
        mEditViewItemModel.setNewSetting(pNewProduct);

        delete pNewProduct;
    }
    Q_INVOKABLE void onCommandApplyProduct()
    {
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

        int ret;
        quint64 outSeq;

        if(mEditViewItemModel.getIsNew())
        {

            ret = mpCoreService->onCommandAddProductSetting(&outSeq                                         ,
                                                            mEditViewItemModel.mModel.mNo                   ,
                                                            mEditViewItemModel.mModel.mName                 ,
                                                            mEditViewItemModel.mModel.mLength               ,
                                                            mEditViewItemModel.mModel.mSpeed                ,
                                                            mEditViewItemModel.mModel.mMotorAccelerationTime,
                                                            mEditViewItemModel.mModel.mUnderWeight          ,
                                                            mEditViewItemModel.mModel.mUnderWarningWeight   ,
                                                            mEditViewItemModel.mModel.mNormalWeight         ,
                                                            mEditViewItemModel.mModel.mOverWarningWeight    ,
                                                            mEditViewItemModel.mModel.mOverWeight           ,
                                                            mEditViewItemModel.mModel.mTareWeight           ,
                                                            mEditViewItemModel.mModel.mWCNGMotion           ,
                                                            mEditViewItemModel.mModel.mDynamicFactor        ,
                                                            mEditViewItemModel.mModel.mMDSenstivity         ,
                                                            mEditViewItemModel.mModel.mMDNGMotion           );
        }
        else
        {
            outSeq = mEditViewItemModel.mModel.mSeq;
            ret = mpCoreService->onCommandEditProductSetting(mEditViewItemModel.mModel.mSeq                  ,
                                                             mEditViewItemModel.mModel.mNo                   ,
                                                             mEditViewItemModel.mModel.mName                 ,
                                                             mEditViewItemModel.mModel.mLength               ,
                                                             mEditViewItemModel.mModel.mSpeed                ,
                                                             mEditViewItemModel.mModel.mMotorAccelerationTime,
                                                             mEditViewItemModel.mModel.mUnderWeight          ,
                                                             mEditViewItemModel.mModel.mUnderWarningWeight   ,
                                                             mEditViewItemModel.mModel.mNormalWeight         ,
                                                             mEditViewItemModel.mModel.mOverWarningWeight    ,
                                                             mEditViewItemModel.mModel.mOverWeight           ,
                                                             mEditViewItemModel.mModel.mTareWeight           ,
                                                             mEditViewItemModel.mModel.mWCNGMotion           ,
                                                             mEditViewItemModel.mModel.mDynamicFactor        ,
                                                             mEditViewItemModel.mModel.mMDSenstivity         ,
                                                             mEditViewItemModel.mModel.mMDNGMotion           );
        }

        if(ret == EnumDefine::DatabaseErrorType::DB_NONE_ERROR)
        {
            loadProductList();
            mEditViewItemModel.setSeq(0);
            onCommandSetLookProduct(outSeq);
        }

        signalEventResultSaveProductSetting(ret);
    }
    Q_INVOKABLE void onCommandCancleProduct()
    {
        onCommandSetLookProduct(getLookProductSeq());
    }
    Q_INVOKABLE void onCommandRemoveProduct()
    {
        int ret = mpCoreService->onCommandRemoveProductSetting(mEditViewItemModel.mModel.mSeq);

        if(ret == EnumDefine::DatabaseErrorType::DB_NONE_ERROR)
        {
            loadProductList();
            mEditViewItemModel.setSeq(0);
            onCommandSetLookProduct(getLookProductSeq());
        }
        signalEventResultSaveProductSetting(ret);
    }

public slots:
    void onSignalEventChangedSelectedProductSeq(quint64 value){ setSelectedProductSeq(value);}

public:
    void loadProductList()
    {
        for(int i = 0; i < mListProductSetting.size(); i ++)
        {
            delete mListProductSetting.at(i);
        }

        mListProductSetting.clear();

        for(int i = 0; i < mpPSService->mListProductSetting.size(); i ++)
        {
            ProductSettingItemModel * pItemModel = new ProductSettingItemModel(this);
            pItemModel->setData(mpPSService->mListProductSetting.at(i)->mSeq);

            mListProductSetting.append(pItemModel);
        }
    }
    explicit PanelProductSettingModel(QObject *parent = nullptr):QObject(parent)
    {
        mpCoreService = CoreService::getInstance();
        mpPSService   = &(mpCoreService->mProductSettingServcie);

        connect(&(mpPSService->mCurrentProductSetting), SIGNAL(signalEventChangedSeq(quint64)) ,this, SLOT(onSignalEventChangedSelectedProductSeq(quint64)));

        loadProductList();
        onSignalEventChangedSelectedProductSeq(mpPSService->mCurrentProductSetting.mSeq);
        onCommandSetLookProduct(mpPSService->mCurrentProductSetting.mSeq);
    }
};

#endif // PANELPRODUCTSETTINGMODEL_H
