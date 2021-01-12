#ifndef PANELPDSELECTMODEL_H
#define PANELPDSELECTMODEL_H

#include <QObject>

#include "source/globaldef/qmlenumdef.h"
#include "source/service/coreservice.h"

class PanelPDSelectModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      order                   READ getOrder                 NOTIFY signalEventChangedOrder             )

public:
    QList<PDSettingDto> mPDList;

    static int * getOrderPtr(){ static int order = 0; return &order;}

    int  getOrder()
    {
        return *getOrderPtr();
    }

    void setOrder(int value)
    {
        int * pOrder = getOrderPtr();
        *pOrder = value;

        emit signalEventChangedOrder(value);
    }

signals:
    void signalEventChangedOrder             (int     value);

public slots:
    Q_INVOKABLE void onCommandSetOrder(int order)
    {
        loadProductList(order);
        setOrder(order);
    }

    Q_INVOKABLE int onCommandGetPDListSize()
    {
        return mPDList.size();
    }

    Q_INVOKABLE quint64 onCommandGetPDSeq(int idx)
    {
        if(idx < mPDList.size())
            return mPDList[idx].mSeq;
        return 0;
    }

    Q_INVOKABLE quint16 onCommandGetPDNum(int idx)
    {
        if(idx < mPDList.size())
            return mPDList[idx].mDspForm.mCommSetting.mProductNum;
        return 0;
    }

    Q_INVOKABLE QString onCommandGetPDName(int idx)
    {
        if(idx < mPDList.size())
            return mPDList[idx].mName;
        return "";
    }
    Q_INVOKABLE void onCommandSetSelectProduct(quint64 seq)
    {
        pProductSP->selectPD(seq);
    }

public:
    void loadProductList(int order)
    {
        mPDList.clear();

        for(int i = 0; i < pProductSP->mPDList.size(); i ++)
        {
            addToList(pProductSP->mPDList[i], order);
        }
    }
    explicit PanelPDSelectModel(QObject *parent = nullptr):QObject(parent)
    {
        loadProductList(getOrder());
    }

private:
    void addToList(PDSettingDto* pNew, int order)
    {
        for(int i = 0; i < mPDList.size(); i ++)
        {
            PDSettingDto old = mPDList[i];

            if(order == 0) // 이룸순
            {
                if(old.mName == pNew->mName)
                {
                    if(old.mDspForm.mCommSetting.mProductNum > pNew->mDspForm.mCommSetting.mProductNum)
                    {
                        mPDList.insert(i, *pNew);
                        return;
                    }
                }

                if(old.mName > pNew->mName)
                {
                    mPDList.insert(i, *pNew);
                    return;
                }
            }
            else
            {
                if(old.mDspForm.mCommSetting.mProductNum > pNew->mDspForm.mCommSetting.mProductNum)
                {
                    mPDList.insert(i, *pNew);
                    return;
                }
            }
        }

        mPDList.append(*pNew);
    }
};

#endif // PANELPDSELECTMODEL_H
