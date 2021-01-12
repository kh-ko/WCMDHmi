#ifndef PANELPRODUCTSETTINGMODEL_H
#define PANELPRODUCTSETTINGMODEL_H

#include <QObject>
#include <QMap>

#include "source/globaldef/qmlenumdef.h"
#include "source/service/coreservice.h"
#include "source/qmlmodel/wcmd/menu_scene/productsetting/productsettingitemmodel.h"

class PanelProductSettingModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      order                   READ getOrder                 NOTIFY signalEventChangedOrder             )
    Q_PROPERTY(bool     isEnableWC              READ getIsEnableWC            NOTIFY signalEventChangedIsEnableWC        )
    Q_PROPERTY(int      productCount            READ getProductCount          NOTIFY signalEventChangedProductCount      )
    Q_PROPERTY(quint64  lookProductSeq          READ getLookProductSeq        NOTIFY signalEventChangedLookProductSeq    )
    Q_PROPERTY(quint64  selectedProductSeq      READ getSelectedProductSeq    NOTIFY signalEventChangedSelectedProductSeq)

public:
    ProductSettingItemModel          mEditViewItemModel;
    QList<ProductSettingItemModel *> mListProductSetting;

    quint64 mLookProductSeq;
    quint64 mSelectedProductSeq;
    static int * getOrderPtr(){ static int order = 0; return &order;}
    bool    mIsEnableWC;

    int     getOrder             (){return *getOrderPtr()            ;}
    bool    getIsEnableWC        (){return mIsEnableWC               ;}
    int     getProductCount      (){return mListProductSetting.size();}
    quint64 getLookProductSeq    (){return mLookProductSeq           ;}
    quint64 getSelectedProductSeq(){return mSelectedProductSeq       ;}

    void setOrder             (int     value){ int * pOrder = getOrderPtr(); *pOrder = value;                       emit signalEventChangedOrder             (value); }
    void setIsEnableWC        (bool    value){ if(value == mIsEnableWC        )return; mIsEnableWC         = value; emit signalEventChangedIsEnableWC        (value); }
    void setLookProductSeq    (quint64 value){ if(value == mLookProductSeq    )return; mLookProductSeq     = value; emit signalEventChangedLookProductSeq    (value); }
    void setSelectedProductSeq(quint64 value){ if(value == mSelectedProductSeq)return; mSelectedProductSeq = value; emit signalEventChangedSelectedProductSeq(value); }

signals:
    void signalEventChangedOrder             (int     value);
    void signalEventChangedIsEnableWC        (bool    value);
    void signalEventChangedProductCount      (int     value);
    void signalEventChangedLookProductSeq    (quint64 value);
    void signalEventChangedSelectedProductSeq(quint64 value);
    void signalEventResultSaveProductSetting (bool isEmptyNo, bool isInvalidWC, int svcErr);

public slots:
    Q_INVOKABLE void onCommandSetOrder(int order)
    {
        loadProductList(order);
        setOrder(order);
    }

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
        pProductSP->selectPD(seq);
    }
    Q_INVOKABLE void onCommandAddProduct()
    {
        PDSettingDto dto = pProductSP->getDummyPD();
        //dto.mDspForm.mWCSetting.mDynamicFactor = pLSettingSP->mHMISetting.mDynamicFactor;
        mEditViewItemModel.setNewSetting(dto);
    }
    Q_INVOKABLE void onCommandApplyProduct()
    {
        if(mEditViewItemModel.getNo() < 1)
        {
            emit signalEventResultSaveProductSetting(true, false, 0);
            return;
        }

        if(!(mEditViewItemModel.getUnderWeight()          <= mEditViewItemModel.getUnderWarningWeight() &&
           mEditViewItemModel.getUnderWarningWeight()   <  mEditViewItemModel.getNormalWeight() &&
           mEditViewItemModel.getNormalWeight()         <  mEditViewItemModel.getOverWarningWeight() &&
           mEditViewItemModel.getOverWarningWeight()    <=  mEditViewItemModel.getOverWeight()))
        {
            emit signalEventResultSaveProductSetting(false, true, 0);
            return;
        }

        int ret;

        if(mEditViewItemModel.mModel.mDspForm.mWCSetting.mEnableEtcError == 0)
        {
            mEditViewItemModel.setUnderWeight       (100     );
            mEditViewItemModel.setUnderWarningWeight(100     );
            mEditViewItemModel.setNormalWeight      (200     );
            mEditViewItemModel.setOverWarningWeight (99999900);
            mEditViewItemModel.setOverWeight        (99999900);
            mEditViewItemModel.setTareWeight        (0       );
        }

        PDSettingDto newSetting = mEditViewItemModel.mModel;

        qDebug()<< "[debug]" << newSetting.toString(",");

        if(mEditViewItemModel.getIsNew())
        {
            ret = pProductSP->addPD(newSetting);
        }
        else
        {
            ret = pProductSP->editPD(newSetting);
        }

        if(ret == EnumDef::PDERR_NONE)
        {
            loadProductList(getOrder());
            mEditViewItemModel.setSeq(0);
            onCommandSetLookProduct(newSetting.mSeq);
        }

        signalEventResultSaveProductSetting(false, false, ret);
    }
    Q_INVOKABLE void onCommandCancleProduct()
    {
        mEditViewItemModel.setData(0);
        onCommandSetLookProduct(getLookProductSeq());
    }
    Q_INVOKABLE void onCommandRemoveProduct()
    {
        int ret = pProductSP->removePD(mEditViewItemModel.mModel.mSeq);

        if(ret == EnumDef::PDERR_NONE)
        {
            loadProductList(getOrder());
            mEditViewItemModel.setSeq(0);
            onCommandSetLookProduct(getLookProductSeq());
        }
        signalEventResultSaveProductSetting(false, false, ret);
    }

public slots:
    void onChangedCurrPDSetting(PDSettingDto dto){ setSelectedProductSeq(dto.mSeq);}
    void onChangedDevSetting(DevSettingDto dto){setIsEnableWC(dto.mDspForm.mCommSetting.mMachineMode != EnumDef::MACHINE_MODE_ALU);}

public:
    void loadProductList(int order)
    {
        for(int i = 0; i < mListProductSetting.size(); i ++)
        {
            delete mListProductSetting.at(i);
        }

        mListProductSetting.clear();

        for(int i = 0; i < pProductSP->mPDList.size(); i ++)
        {
            ProductSettingItemModel * pPDModel = new ProductSettingItemModel(this);
            pPDModel->setData(pProductSP->mPDList[i]->mSeq);
            addToList(pPDModel, order);
        }
    }
    explicit PanelProductSettingModel(QObject *parent = nullptr):QObject(parent)
    {
        ENABLE_SLOT_PDSETTING_CHANGED_CURR_PD;
        ENABLE_SLOT_LSETTING_CHANGED_DEV_SETTING;

        loadProductList(getOrder());
        onChangedCurrPDSetting(pProductSP->mCurrPD);
        onCommandSetLookProduct(pProductSP->mCurrPD.mSeq);
        onChangedDevSetting(pLSettingSP->mDevSetting);

    }

private:
    void addToList(ProductSettingItemModel * pNew, int order)
    {
        for(int i = 0; i < mListProductSetting.size(); i ++)
        {
            ProductSettingItemModel * pOld = mListProductSetting[i];

            if(order == 0) // 이룸순
            {
                if(pOld->mModel.mName == pNew->mModel.mName)
                {
                    if(pOld->mModel.mDspForm.mCommSetting.mProductNum > pNew->mModel.mDspForm.mCommSetting.mProductNum)
                    {
                        mListProductSetting.insert(i, pNew);
                        return;
                    }
                }

                if(pOld->mModel.mName > pNew->mModel.mName)
                {
                    mListProductSetting.insert(i, pNew);
                    return;
                }
            }
            else
            {
                if(pOld->mModel.mDspForm.mCommSetting.mProductNum > pNew->mModel.mDspForm.mCommSetting.mProductNum)
                {
                    mListProductSetting.insert(i, pNew);
                    return;
                }
            }
        }

        mListProductSetting.append(pNew);
    }
};

#endif // PANELPRODUCTSETTINGMODEL_H
