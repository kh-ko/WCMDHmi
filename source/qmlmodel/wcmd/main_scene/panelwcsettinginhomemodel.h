#ifndef PANELWCSETTINGINHOMEMODEL_H
#define PANELWCSETTINGINHOMEMODEL_H

#include <QObject>
#include "source/service/wcmdservice.h"

class PanelWCSettingInHomeModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint32  underWeight        READ getUnderWeight            NOTIFY signalEventChangedUnderWeight       )
    Q_PROPERTY(quint32  normalWeight       READ getNormalWeight           NOTIFY signalEventChangedNormalWeight      )
    Q_PROPERTY(quint32  overWeight         READ getOverWeight             NOTIFY signalEventChangedOverWeight        )
    Q_PROPERTY(qint32   underGap           READ getUnderGap               NOTIFY signalEventChangedUnderGap          )
    Q_PROPERTY(qint32   overGap            READ getOverGap                NOTIFY signalEventChangedOverGap           )

    Q_PROPERTY(bool     isEditUnderWeight  READ getIsEditUnderWeight      NOTIFY signalEventChangedIsEditUnderWeight )
    Q_PROPERTY(bool     isEditNormalWeight READ getIsEditNormalWeight     NOTIFY signalEventChangedIsEditNormalWeight)
    Q_PROPERTY(bool     isEditOverWeight   READ getIsEditOverWeight       NOTIFY signalEventChangedIsEditOverWeight  )
    Q_PROPERTY(bool     isEditUnderGap     READ getIsEditUnderGap         NOTIFY signalEventChangedIsEditUnderGap    )
    Q_PROPERTY(bool     isEditOverGap      READ getIsEditOverGap          NOTIFY signalEventChangedIsEditOverGap     )

public:
    quint32  mUnderWeight ;
    quint32  mNormalWeight;
    quint32  mOverWeight  ;
    qint32   mUnderGap    ;
    qint32   mOverGap     ;

    bool     mIsEditUnderWeight ;
    bool     mIsEditNormalWeight;
    bool     mIsEditOverWeight  ;
    bool     mIsEditUnderGap    ;
    bool     mIsEditOverGap     ;

    quint32  getUnderWeight       (){ return mUnderWeight       ;}
    quint32  getNormalWeight      (){ return mNormalWeight      ;}
    quint32  getOverWeight        (){ return mOverWeight        ;}
    qint32   getUnderGap          (){ return mUnderGap          ;}
    qint32   getOverGap           (){ return mOverGap           ;}
    bool     getIsEditUnderWeight (){ return mIsEditUnderWeight ;}
    bool     getIsEditNormalWeight(){ return mIsEditNormalWeight;}
    bool     getIsEditOverWeight  (){ return mIsEditOverWeight  ;}
    bool     getIsEditUnderGap    (){ return mIsEditUnderGap    ;}
    bool     getIsEditOverGap     (){ return mIsEditOverGap     ;}

    void     setUnderWeight       (quint32 value){ if( value == mUnderWeight        ) return; mUnderWeight         = value; setIsEditUnderWeight (true); emit signalEventChangedUnderWeight        (value);}
    void     setNormalWeight      (quint32 value){ if( value == mNormalWeight       ) return; mNormalWeight        = value; setIsEditNormalWeight(true); emit signalEventChangedNormalWeight       (value);}
    void     setOverWeight        (quint32 value){ if( value == mOverWeight         ) return; mOverWeight          = value; setIsEditOverWeight  (true); emit signalEventChangedOverWeight         (value);}
    void     setUnderGap          (qint32  value){ if( value == mUnderGap           ) return; mUnderGap            = value; setIsEditUnderGap    (true); emit signalEventChangedUnderGap           (value);}
    void     setOverGap           (qint32  value){ if( value == mOverGap            ) return; mOverGap             = value; setIsEditOverGap     (true); emit signalEventChangedOverGap            (value);}
    void     setIsEditUnderWeight (bool    value){ if( value == mIsEditUnderWeight  ) return; mIsEditUnderWeight   = value; emit signalEventChangedIsEditUnderWeight  (value);}
    void     setIsEditNormalWeight(bool    value){ if( value == mIsEditNormalWeight ) return; mIsEditNormalWeight  = value; emit signalEventChangedIsEditNormalWeight (value);}
    void     setIsEditOverWeight  (bool    value){ if( value == mIsEditOverWeight   ) return; mIsEditOverWeight    = value; emit signalEventChangedIsEditOverWeight   (value);}
    void     setIsEditUnderGap    (bool    value){ if( value == mIsEditUnderGap     ) return; mIsEditUnderGap      = value; emit signalEventChangedIsEditUnderGap     (value);}
    void     setIsEditOverGap     (bool    value){ if( value == mIsEditOverGap      ) return; mIsEditOverGap       = value; emit signalEventChangedIsEditOverGap      (value);}

    explicit PanelWCSettingInHomeModel(QObject *parent = nullptr);

signals:
    void signalEventChangedUnderWeight       (quint32 value);
    void signalEventChangedNormalWeight      (quint32 value);
    void signalEventChangedOverWeight        (quint32 value);
    void signalEventChangedUnderGap          (qint32  value);
    void signalEventChangedOverGap           (qint32  value);
    void signalEventChangedIsEditUnderWeight (bool    value);
    void signalEventChangedIsEditNormalWeight(bool    value);
    void signalEventChangedIsEditOverWeight  (bool    value);
    void signalEventChangedIsEditUnderGap    (bool    value);
    void signalEventChangedIsEditOverGap     (bool    value);
    void signalEventResultSaveProductSetting (int     error);

    void signalCommandSaveProductSetting(void * sender, int type, ProductSetting value);

public slots:
    Q_INVOKABLE void onCommandSetUnderWeight     (quint32 value);
    Q_INVOKABLE void onCommandSetNormalWeight    (quint32 value);
    Q_INVOKABLE void onCommandSetOverWeight      (quint32 value);
    Q_INVOKABLE void onCommandSetUnderGap        (qint32  value);
    Q_INVOKABLE void onCommandSetOverGap         (qint32  value);
    Q_INVOKABLE void onCommandApply              (             );

    void onSignalEventChangedSelectedProductSetting       (ProductSetting       value);
    void onSignalResultSaveProductSetting                 (void * sender, int error, ProductSetting       value);
};

#endif // PANELWCSETTINGINHOMEMODEL_H
