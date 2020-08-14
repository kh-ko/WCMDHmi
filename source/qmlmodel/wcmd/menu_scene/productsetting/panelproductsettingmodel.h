#ifndef PANELPRODUCTSETTINGMODEL_H
#define PANELPRODUCTSETTINGMODEL_H

#include <QObject>
#include <QMap>

#include "source/service/wcmdservice.h"
#include "source/qmlmodel/wcmd/menu_scene/productsetting/productsettingitemmodel.h"

class PanelProductSettingModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      productCount            READ getProductCount          NOTIFY signalEventChangedProductCount      )
    Q_PROPERTY(quint16  lookProductSeq          READ getLookProductSeq        NOTIFY signalEventChangedLookProductSeq    )
    Q_PROPERTY(quint16  selectedProductSeq      READ getSelectedProductSeq    NOTIFY signalEventChangedSelectedProductSeq)

public:
    ProductSettingItemModel                mEditViewItemModel;
    QList<ProductSettingItemModel *>       mListProductSetting;

    quint16 mSelectedProductSeq;

    int     getProductCount      (){return mListProductSetting.size()    ;}
    quint16 getLookProductSeq    (){return mEditViewItemModel.getSeq() ;}
    quint16 getSelectedProductSeq(){return mSelectedProductSeq           ;}

    void setSelectedProductSeq(quint16 value){ if(value == mSelectedProductSeq)return; mSelectedProductSeq = value; emit signalEventChangedSelectedProductSeq(value);}
    explicit PanelProductSettingModel(QObject *parent = nullptr);

signals:
    void signalEventChangedProductCount      (int     value);
    void signalEventChangedLookProductSeq    (quint16 value);
    void signalEventChangedSelectedProductSeq(quint16 value);

    void signalEventResultSaveProductSetting  (int error   );
    void signalEventRemoveProductSetting      (quint16 seq );
    void signalEventAddProductSetting         (quint16 seq );

    /*
     * void onCommandSaveProductSetting                (void * sender, int type, ProductSetting value);
    void onCommandSelectProductSetting              (void * sender, quint16 productSeq);
*/
    void signalCommandSaveProductSetting(void * sender, int type, ProductSetting value);
    void signalCommandSelectProductSetting(void * sender, quint16 productSeq);

public slots:
    Q_INVOKABLE ProductSettingItemModel *   onCommandGetItemModel         (int     idx);
    Q_INVOKABLE ProductSettingItemModel *   onCommandFindItemModel        (quint16 seq);
    Q_INVOKABLE ProductSettingItemModel *   onCommandGetEditViewItemModel (           );
    Q_INVOKABLE void                        onCommandSetLookProduct       (quint16 seq);
    Q_INVOKABLE void                        onCommandSetSelectProduct     (quint16 seq);
    Q_INVOKABLE void                        onCommandAddProduct           (           );
    Q_INVOKABLE void                        onCommandApplyProduct         (           );
    Q_INVOKABLE void                        onCommandCancleProduct        (           );
    Q_INVOKABLE void                        onCommandRemoveProduct        (           );

    void onSignalEventChangedProductSetting               (int type, ProductSetting       value);
    void onSignalEventChangedSelectedProductSetting       (ProductSetting       value);

    void onSignalResultSaveProductSetting                 (void * sender, int error, ProductSetting       value);

    void onSignalEventChangedSeq                          (quint16 value);
};

#endif // PANELPRODUCTSETTINGMODEL_H
