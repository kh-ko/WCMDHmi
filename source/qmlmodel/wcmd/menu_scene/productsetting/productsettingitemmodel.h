#ifndef PRODUCTSETTINGITEMMODEL_H
#define PRODUCTSETTINGITEMMODEL_H

#include <QObject>
#include "source/model/productsetting.h"

class ProductSettingItemModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool                 isNull                     READ getIsNull                      NOTIFY signalEventChangedIsNull                   )
    Q_PROPERTY(bool                 isNew                      READ getIsNew                       NOTIFY signalEventChangedIsNew                    )
    Q_PROPERTY(bool                 isRemoved                  READ getIsRemoved                   NOTIFY signalEventChangedIsRemoved                )

    Q_PROPERTY(quint16              seq                        READ getSeq                         NOTIFY signalEventChangedSeq                      )
    Q_PROPERTY(bool                 selected                   READ getSelected                    NOTIFY signalEventChangedSelected                 )
    Q_PROPERTY(quint16              no                         READ getNo                          NOTIFY signalEventChangedNo                       )
    Q_PROPERTY(QString              name                       READ getName                        NOTIFY signalEventChangedName                     )
    Q_PROPERTY(quint16              length                     READ getLength                      NOTIFY signalEventChangedLength                   )
    Q_PROPERTY(quint16              speed                      READ getSpeed                       NOTIFY signalEventChangedSpeed                    )
    Q_PROPERTY(quint32              motorAcceleration          READ getMotorAcceleration           NOTIFY signalEventChangedMotorAcceleration        )
    Q_PROPERTY(quint32              underWeight                READ getUnderWeight                 NOTIFY signalEventChangedUnderWeight              )
    Q_PROPERTY(quint32              underWarningWeight         READ getUnderWarningWeight          NOTIFY signalEventChangedUnderWarningWeight       )
    Q_PROPERTY(quint32              normalWeight               READ getNormalWeight                NOTIFY signalEventChangedNormalWeight             )
    Q_PROPERTY(quint32              overWarningWeight          READ getOverWarningWeight           NOTIFY signalEventChangedOverWarningWeight        )
    Q_PROPERTY(quint32              overWeight                 READ getOverWeight                  NOTIFY signalEventChangedOverWeight               )
    Q_PROPERTY(quint32              tareWeight                 READ getTareWeight                  NOTIFY signalEventChangedTareWeight               )
    Q_PROPERTY(quint16              wcNGMotion                 READ getWCNGMotion                  NOTIFY signalEventChangedWCNGMotion               )
    Q_PROPERTY(int                  averageN                   READ getAverageN                    NOTIFY signalEventChangedAverageN                 )
    Q_PROPERTY(quint16              mdSenstivity               READ getMDSenstivity                NOTIFY signalEventChangedMDSenstivity             )
    Q_PROPERTY(quint16              mdNGMotion                 READ getMDNGMotion                  NOTIFY signalEventChangedMDNGMotion               )

    Q_PROPERTY(bool                 isEditNo                   READ getIsEditNo                    NOTIFY signalEventChangedIsEditNo                 )
    Q_PROPERTY(bool                 isEditName                 READ getIsEditName                  NOTIFY signalEventChangedIsEditName               )
    Q_PROPERTY(bool                 isEditLength               READ getIsEditLength                NOTIFY signalEventChangedIsEditLength             )
    Q_PROPERTY(bool                 isEditSpeed                READ getIsEditSpeed                 NOTIFY signalEventChangedIsEditSpeed              )
    Q_PROPERTY(bool                 isEditMotorAcceleration    READ getIsEditMotorAcceleration     NOTIFY signalEventChangedIsEditMotorAcceleration  )
    Q_PROPERTY(bool                 isEditUnderWeight          READ getIsEditUnderWeight           NOTIFY signalEventChangedIsEditUnderWeight        )
    Q_PROPERTY(bool                 isEditUnderWarningWeight   READ getIsEditUnderWarningWeight    NOTIFY signalEventChangedIsEditUnderWarningWeight )
    Q_PROPERTY(bool                 isEditNormalWeight         READ getIsEditNormalWeight          NOTIFY signalEventChangedIsEditNormalWeight       )
    Q_PROPERTY(bool                 isEditOverWarningWeight    READ getIsEditOverWarningWeight     NOTIFY signalEventChangedIsEditOverWarningWeight  )
    Q_PROPERTY(bool                 isEditOverWeight           READ getIsEditOverWeight            NOTIFY signalEventChangedIsEditOverWeight         )
    Q_PROPERTY(bool                 isEditTareWeight           READ getIsEditTareWeight            NOTIFY signalEventChangedIsEditTareWeight         )
    Q_PROPERTY(bool                 isEditWCNGMotion           READ getIsEditWCNGMotion            NOTIFY signalEventChangedIsEditWCNGMotion         )
    Q_PROPERTY(bool                 isEditAverageN             READ getIsEditAverageN              NOTIFY signalEventChangedIsEditAverageN           )
    Q_PROPERTY(bool                 isEditMDSenstivity         READ getIsEditMDSenstivity          NOTIFY signalEventChangedIsEditMDSenstivity       )
    Q_PROPERTY(bool                 isEditMDNGMotion           READ getIsEditMDNGMotion            NOTIFY signalEventChangedIsEditMDNGMotion         )

public:

    ProductSetting  mProductSetting   ;

    bool    mIsNull                   ;
    bool    mIsNew                    ;
    bool    mIsRemoved                ;

    quint16 mSeq                      ;
    bool    mSelected                 ;
    quint16 mNo                       ;
    QString mName                     ;
    quint16 mLength                   ;
    quint16 mSpeed                    ;
    quint32 mMotorAcceleration        ;
    quint32 mUnderWeight              ;
    quint32 mUnderWarningWeight       ;
    quint32 mNormalWeight             ;
    quint32 mOverWarningWeight        ;
    quint32 mOverWeight               ;
    quint32 mTareWeight               ;
    quint16 mWCNGMotion               ;
    int     mAverageN                 ;
    quint16 mMDSenstivity             ;
    quint16 mMDNGMotion               ;

    bool    mIsEditNo                 ;
    bool    mIsEditName               ;
    bool    mIsEditLength             ;
    bool    mIsEditSpeed              ;
    bool    mIsEditMotorAcceleration  ;
    bool    mIsEditUnderWeight        ;
    bool    mIsEditUnderWarningWeight ;
    bool    mIsEditNormalWeight       ;
    bool    mIsEditOverWarningWeight  ;
    bool    mIsEditOverWeight         ;
    bool    mIsEditTareWeight         ;
    bool    mIsEditWCNGMotion         ;
    bool    mIsEditAverageN           ;
    bool    mIsEditMDSenstivity       ;
    bool    mIsEditMDNGMotion         ;

    bool    getIsNull                  (){return mIsNull                   ;}
    bool    getIsNew                   (){return mIsNew                    ;}
    bool    getIsRemoved               (){return mIsRemoved                ;}

    quint16 getSeq                     (){return mSeq                      ;}
    bool    getSelected                (){return mSelected                 ;}
    quint16 getNo                      (){return mNo                       ;}
    QString getName                    (){return mName                     ;}
    quint16 getLength                  (){return mLength                   ;}
    quint16 getSpeed                   (){return mSpeed                    ;}
    quint32 getMotorAcceleration       (){return mMotorAcceleration        ;}
    quint32 getUnderWeight             (){return mUnderWeight              ;}
    quint32 getUnderWarningWeight      (){return mUnderWarningWeight       ;}
    quint32 getNormalWeight            (){return mNormalWeight             ;}
    quint32 getOverWarningWeight       (){return mOverWarningWeight        ;}
    quint32 getOverWeight              (){return mOverWeight               ;}
    quint32 getTareWeight              (){return mTareWeight               ;}
    quint16 getWCNGMotion              (){return mWCNGMotion               ;}
    int     getAverageN                (){return mAverageN                 ;}
    quint16 getMDSenstivity            (){return mMDSenstivity             ;}
    quint16 getMDNGMotion              (){return mMDNGMotion               ;}

    bool    getIsEditNo                (){return mIsEditNo                 ;}
    bool    getIsEditName              (){return mIsEditName               ;}
    bool    getIsEditLength            (){return mIsEditLength             ;}
    bool    getIsEditSpeed             (){return mIsEditSpeed              ;}
    bool    getIsEditMotorAcceleration (){return mIsEditMotorAcceleration  ;}
    bool    getIsEditUnderWeight       (){return mIsEditUnderWeight        ;}
    bool    getIsEditUnderWarningWeight(){return mIsEditUnderWarningWeight ;}
    bool    getIsEditNormalWeight      (){return mIsEditNormalWeight       ;}
    bool    getIsEditOverWarningWeight (){return mIsEditOverWarningWeight  ;}
    bool    getIsEditOverWeight        (){return mIsEditOverWeight         ;}
    bool    getIsEditTareWeight        (){return mIsEditTareWeight         ;}
    bool    getIsEditWCNGMotion        (){return mIsEditWCNGMotion         ;}
    bool    getIsEditAverageN          (){return mIsEditAverageN           ;}
    bool    getIsEditMDSenstivity      (){return mIsEditMDSenstivity       ;}
    bool    getIsEditMDNGMotion        (){return mIsEditMDNGMotion         ;}

    void setIsNull                  (bool    value){ if(value == mIsNull                   ) return; mIsNull                   = value; emit signalEventChangedIsNull                   (value);}
    void setIsNew                   (bool    value){ if(value == mIsNew                    ) return; mIsNew                    = value; emit signalEventChangedIsNew                    (value);}
    void setIsRemoved               (bool    value){ if(value == mIsRemoved                ) return; mIsRemoved                = value; emit signalEventChangedIsRemoved                (value);}

    void setSeq                     (quint16 value){ if(value == mSeq                      ) return; mSeq                      = value; emit signalEventChangedSeq                      (value);}
    void setSelected                (bool    value){ if(value == mSelected                 ) return; mSelected                 = value; emit signalEventChangedSelected                 (value);}
    void setNo                      (quint16 value){ if(value == mNo                       ) return; mNo                       = value;  setIsEditNo                (true); emit signalEventChangedNo                       (value);}
    void setName                    (QString value){ if(value == mName                     ) return; mName                     = value;  setIsEditName              (true); emit signalEventChangedName                     (value);}
    void setLength                  (quint16 value){ if(value == mLength                   ) return; mLength                   = value;  setIsEditLength            (true); emit signalEventChangedLength                   (value);}
    void setSpeed                   (quint16 value){ if(value == mSpeed                    ) return; mSpeed                    = value;  setIsEditSpeed             (true); emit signalEventChangedSpeed                    (value);}
    void setMotorAcceleration       (quint32 value){ if(value == mMotorAcceleration        ) return; mMotorAcceleration        = value;  setIsEditMotorAcceleration (true); emit signalEventChangedMotorAcceleration        (value);}
    void setUnderWeight             (quint32 value){ if(value == mUnderWeight              ) return; mUnderWeight              = value;  setIsEditUnderWeight       (true); emit signalEventChangedUnderWeight              (value);}
    void setUnderWarningWeight      (quint32 value){ if(value == mUnderWarningWeight       ) return; mUnderWarningWeight       = value;  setIsEditUnderWarningWeight(true); emit signalEventChangedUnderWarningWeight       (value);}
    void setNormalWeight            (quint32 value){ if(value == mNormalWeight             ) return; mNormalWeight             = value;  setIsEditNormalWeight      (true); emit signalEventChangedNormalWeight             (value);}
    void setOverWarningWeight       (quint32 value){ if(value == mOverWarningWeight        ) return; mOverWarningWeight        = value;  setIsEditOverWarningWeight (true); emit signalEventChangedOverWarningWeight        (value);}
    void setOverWeight              (quint32 value){ if(value == mOverWeight               ) return; mOverWeight               = value;  setIsEditOverWeight        (true); emit signalEventChangedOverWeight               (value);}
    void setTareWeight              (quint32 value){ if(value == mTareWeight               ) return; mTareWeight               = value;  setIsEditTareWeight        (true); emit signalEventChangedTareWeight               (value);}
    void setWCNGMotion              (quint16 value){ if(value == mWCNGMotion               ) return; mWCNGMotion               = value;  setIsEditWCNGMotion        (true); emit signalEventChangedWCNGMotion               (value);}
    void setAverageN                (int     value){ if(value == mAverageN                 ) return; mAverageN                 = value;  setIsEditAverageN          (true); emit signalEventChangedAverageN                 (value);}
    void setMDSenstivity            (quint16 value){ if(value == mMDSenstivity             ) return; mMDSenstivity             = value;  setIsEditMDSenstivity      (true); emit signalEventChangedMDSenstivity             (value);}
    void setMDNGMotion              (quint16 value){ if(value == mMDNGMotion               ) return; mMDNGMotion               = value;  setIsEditMDNGMotion        (true); emit signalEventChangedMDNGMotion               (value);}

    void setIsEditNo                (bool    value){ if(value == mIsEditNo                 ) return; mIsEditNo                 = value; emit signalEventChangedIsEditNo                 (value);}
    void setIsEditName              (bool    value){ if(value == mIsEditName               ) return; mIsEditName               = value; emit signalEventChangedIsEditName               (value);}
    void setIsEditLength            (bool    value){ if(value == mIsEditLength             ) return; mIsEditLength             = value; emit signalEventChangedIsEditLength             (value);}
    void setIsEditSpeed             (bool    value){ if(value == mIsEditSpeed              ) return; mIsEditSpeed              = value; emit signalEventChangedIsEditSpeed              (value);}
    void setIsEditMotorAcceleration (bool    value){ if(value == mIsEditMotorAcceleration  ) return; mIsEditMotorAcceleration  = value; emit signalEventChangedIsEditMotorAcceleration  (value);}
    void setIsEditUnderWeight       (bool    value){ if(value == mIsEditUnderWeight        ) return; mIsEditUnderWeight        = value; emit signalEventChangedIsEditUnderWeight        (value);}
    void setIsEditUnderWarningWeight(bool    value){ if(value == mIsEditUnderWarningWeight ) return; mIsEditUnderWarningWeight = value; emit signalEventChangedIsEditUnderWarningWeight (value);}
    void setIsEditNormalWeight      (bool    value){ if(value == mIsEditNormalWeight       ) return; mIsEditNormalWeight       = value; emit signalEventChangedIsEditNormalWeight       (value);}
    void setIsEditOverWarningWeight (bool    value){ if(value == mIsEditOverWarningWeight  ) return; mIsEditOverWarningWeight  = value; emit signalEventChangedIsEditOverWarningWeight  (value);}
    void setIsEditOverWeight        (bool    value){ if(value == mIsEditOverWeight         ) return; mIsEditOverWeight         = value; emit signalEventChangedIsEditOverWeight         (value);}
    void setIsEditTareWeight        (bool    value){ if(value == mIsEditTareWeight         ) return; mIsEditTareWeight         = value; emit signalEventChangedIsEditTareWeight         (value);}
    void setIsEditWCNGMotion        (bool    value){ if(value == mIsEditWCNGMotion         ) return; mIsEditWCNGMotion         = value; emit signalEventChangedIsEditWCNGMotion         (value);}
    void setIsEditAverageN          (bool    value){ if(value == mIsEditAverageN           ) return; mIsEditAverageN           = value; emit signalEventChangedIsEditAverageN           (value);}
    void setIsEditMDSenstivity      (bool    value){ if(value == mIsEditMDSenstivity       ) return; mIsEditMDSenstivity       = value; emit signalEventChangedIsEditMDSenstivity       (value);}
    void setIsEditMDNGMotion        (bool    value){ if(value == mIsEditMDNGMotion         ) return; mIsEditMDNGMotion         = value; emit signalEventChangedIsEditMDNGMotion         (value);}

    explicit ProductSettingItemModel(QObject *parent = nullptr);

    void           setData(ProductSetting ps);
    ProductSetting getModifiedProductSetting();
    void           reset();
    void           setNewSetting(ProductSetting ps);

signals:
    void signalEventChangedIsNull                   (bool    value);
    void signalEventChangedIsNew                    (bool    value);
    void signalEventChangedIsRemoved                (bool    value);

    void signalEventChangedSeq                      (quint16 value);
    void signalEventChangedSelected                 (bool    value);
    void signalEventChangedNo                       (quint16 value);
    void signalEventChangedName                     (QString value);
    void signalEventChangedLength                   (quint16 value);
    void signalEventChangedSpeed                    (quint16 value);
    void signalEventChangedMotorAcceleration        (quint32 value);
    void signalEventChangedUnderWeight              (quint32 value);
    void signalEventChangedUnderWarningWeight       (quint32 value);
    void signalEventChangedNormalWeight             (quint32 value);
    void signalEventChangedOverWarningWeight        (quint32 value);
    void signalEventChangedOverWeight               (quint32 value);
    void signalEventChangedTareWeight               (quint32 value);
    void signalEventChangedWCNGMotion               (quint16 value);
    void signalEventChangedAverageN                 (int     value);
    void signalEventChangedMDSenstivity             (quint16 value);
    void signalEventChangedMDNGMotion               (quint16 value);

    void signalEventChangedIsEditNo                 (bool    value);
    void signalEventChangedIsEditName               (bool    value);
    void signalEventChangedIsEditLength             (bool    value);
    void signalEventChangedIsEditSpeed              (bool    value);
    void signalEventChangedIsEditMotorAcceleration  (bool    value);
    void signalEventChangedIsEditUnderWeight        (bool    value);
    void signalEventChangedIsEditUnderWarningWeight (bool    value);
    void signalEventChangedIsEditNormalWeight       (bool    value);
    void signalEventChangedIsEditOverWarningWeight  (bool    value);
    void signalEventChangedIsEditOverWeight         (bool    value);
    void signalEventChangedIsEditTareWeight         (bool    value);
    void signalEventChangedIsEditWCNGMotion         (bool    value);
    void signalEventChangedIsEditAverageN           (bool    value);
    void signalEventChangedIsEditMDSenstivity       (bool    value);
    void signalEventChangedIsEditMDNGMotion         (bool    value);

public slots:
    Q_INVOKABLE void onCommandSetSeq                     (quint16 value){ setSeq               (value);}
    Q_INVOKABLE void onCommandSetSelected                (bool    value){ setSelected          (value);}
    Q_INVOKABLE void onCommandSetNo                      (quint16 value){ setNo                (value);}
    Q_INVOKABLE void onCommandSetName                    (QString value){ setName              (value);}
    Q_INVOKABLE void onCommandSetLength                  (quint16 value){ setLength            (value);}
    Q_INVOKABLE void onCommandSetSpeed                   (quint16 value){ setSpeed             (value);}
    Q_INVOKABLE void onCommandSetMotorAcceleration       (quint32 value){ setMotorAcceleration (value);}
    Q_INVOKABLE void onCommandSetUnderWeight             (quint32 value){ setUnderWeight       (value); setUnderWarningWeight(value);}
    Q_INVOKABLE void onCommandSetUnderWarningWeight      (quint32 value){ setUnderWarningWeight(value);}
    Q_INVOKABLE void onCommandSetNormalWeight            (quint32 value){ setNormalWeight      (value);}
    Q_INVOKABLE void onCommandSetOverWarningWeight       (quint32 value){ setOverWarningWeight (value);}
    Q_INVOKABLE void onCommandSetOverWeight              (quint32 value){ setOverWeight        (value); setOverWarningWeight (value);}
    Q_INVOKABLE void onCommandSetTareWeight              (quint32 value){ setTareWeight        (value);}
    Q_INVOKABLE void onCommandSetWCNGMotion              (quint16 value){ setWCNGMotion        (value);}
    Q_INVOKABLE void onCommandSetAverageN                (int     value){ setAverageN          (value);}
    Q_INVOKABLE void onCommandSetMDSenstivity            (quint16 value){ setMDSenstivity      (value);}
    Q_INVOKABLE void onCommandSetMDNGMotion              (quint16 value){ setMDNGMotion        (value);}

};

#endif // PRODUCTSETTINGITEMMODEL_H
