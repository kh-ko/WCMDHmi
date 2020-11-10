#ifndef PRODUCTSETTINGITEMMODEL_H
#define PRODUCTSETTINGITEMMODEL_H

#include <QObject>
#include "source/service/coreservice.h"

class ProductSettingItemModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool                 isNew                      READ getIsNew                       NOTIFY signalEventChangedIsNew                    )
    Q_PROPERTY(quint64              seq                        READ getSeq                         NOTIFY signalEventChangedSeq                      )
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
    Q_PROPERTY(quint16              wcEnableEtcError           READ getWCEnableEtcError            NOTIFY signalEventChangedWCEnableEtcError         )
    Q_PROPERTY(int                  dynamicFactor              READ getDynamicFactor               NOTIFY signalEventChangedDynamicFactor            )
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
    Q_PROPERTY(bool                 isEditWCEnableEtcError     READ getIsEditWCEnableEtcError      NOTIFY signalEventChangedIsEditWCEnableEtcError   )
    Q_PROPERTY(bool                 isEditDynamicFactor        READ getIsEditDynamicFactor         NOTIFY signalEventChangedIsEditDynamicFactor      )
    Q_PROPERTY(bool                 isEditMDSenstivity         READ getIsEditMDSenstivity          NOTIFY signalEventChangedIsEditMDSenstivity       )
    Q_PROPERTY(bool                 isEditMDNGMotion           READ getIsEditMDNGMotion            NOTIFY signalEventChangedIsEditMDNGMotion         )

public:
    ProductSettingService * mpProductService;

    bool    mIsNew                    ;
    ProductSettingModel mModel        ;

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
    bool    mIsEditWCEnableEtcError   ;
    bool    mIsEditDynamicFactor      ;
    bool    mIsEditMDSenstivity       ;
    bool    mIsEditMDNGMotion         ;

    bool    getIsNew                   (){return mIsNew                           ;}
    quint64 getSeq                     (){return mModel.mSeq                      ;}
    quint16 getNo                      (){return mModel.mNo                       ;}
    QString getName                    (){return mModel.mName                     ;}
    quint16 getLength                  (){return mModel.mLength                   ;}
    quint16 getSpeed                   (){return mModel.mSpeed                    ;}
    quint32 getMotorAcceleration       (){return mModel.mMotorAccelerationTime    ;}
    quint32 getUnderWeight             (){return mModel.mUnderWeight              ;}
    quint32 getUnderWarningWeight      (){return mModel.mUnderWarningWeight       ;}
    quint32 getNormalWeight            (){return mModel.mNormalWeight             ;}
    quint32 getOverWarningWeight       (){return mModel.mOverWarningWeight        ;}
    quint32 getOverWeight              (){return mModel.mOverWeight               ;}
    quint32 getTareWeight              (){return mModel.mTareWeight               ;}
    quint16 getWCNGMotion              (){return mModel.mWCNGMotion               ;}
    quint16 getWCEnableEtcError        (){return mModel.mWCEnableEtcError         ;}
    int     getDynamicFactor           (){return mModel.mDynamicFactor            ;}
    quint16 getMDSenstivity            (){return mModel.mMDSenstivity             ;}
    quint16 getMDNGMotion              (){return mModel.mMDNGMotion               ;}

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
    bool    getIsEditWCEnableEtcError  (){return mIsEditWCEnableEtcError   ;}
    bool    getIsEditDynamicFactor     (){return mIsEditDynamicFactor      ;}
    bool    getIsEditMDSenstivity      (){return mIsEditMDSenstivity       ;}
    bool    getIsEditMDNGMotion        (){return mIsEditMDNGMotion         ;}

    void setIsNew                   (bool    value){ if(value == mIsNew                           ) return; mIsNew                           = value; emit signalEventChangedIsNew                    (value);}
    void setSeq                     (quint64 value){ if(value == mModel.mSeq                      ) return; mModel.mSeq                      = value; emit signalEventChangedSeq                      (value);}
    void setNo                      (quint16 value){ if(value == mModel.mNo                       ) return; mModel.mNo                       = value;  setIsEditNo                (true); emit signalEventChangedNo                       (value);}
    void setName                    (QString value){ if(value == mModel.mName                     ) return; mModel.mName                     = value;  setIsEditName              (true); emit signalEventChangedName                     (value);}
    void setLength                  (quint16 value){ if(value == mModel.mLength                   ) return; mModel.mLength                   = value;  setIsEditLength            (true); emit signalEventChangedLength                   (value);}
    void setSpeed                   (quint16 value){ if(value == mModel.mSpeed                    ) return; mModel.mSpeed                    = value;  setIsEditSpeed             (true); emit signalEventChangedSpeed                    (value);}
    void setMotorAcceleration       (quint32 value){ if(value == mModel.mMotorAccelerationTime    ) return; mModel.mMotorAccelerationTime    = value;  setIsEditMotorAcceleration (true); emit signalEventChangedMotorAcceleration        (value);}
    void setUnderWeight             (quint32 value){ if(value == mModel.mUnderWeight              ) return; mModel.mUnderWeight              = value;  setIsEditUnderWeight       (true); emit signalEventChangedUnderWeight              (value);}
    void setUnderWarningWeight      (quint32 value){ if(value == mModel.mUnderWarningWeight       ) return; mModel.mUnderWarningWeight       = value;  setIsEditUnderWarningWeight(true); emit signalEventChangedUnderWarningWeight       (value);}
    void setNormalWeight            (quint32 value){ if(value == mModel.mNormalWeight             ) return; mModel.mNormalWeight             = value;  setIsEditNormalWeight      (true); emit signalEventChangedNormalWeight             (value);}
    void setOverWarningWeight       (quint32 value){ if(value == mModel.mOverWarningWeight        ) return; mModel.mOverWarningWeight        = value;  setIsEditOverWarningWeight (true); emit signalEventChangedOverWarningWeight        (value);}
    void setOverWeight              (quint32 value){ if(value == mModel.mOverWeight               ) return; mModel.mOverWeight               = value;  setIsEditOverWeight        (true); emit signalEventChangedOverWeight               (value);}
    void setTareWeight              (quint32 value){ if(value == mModel.mTareWeight               ) return; mModel.mTareWeight               = value;  setIsEditTareWeight        (true); emit signalEventChangedTareWeight               (value);}
    void setWCNGMotion              (quint16 value){ if(value == mModel.mWCNGMotion               ) return; mModel.mWCNGMotion               = value;  setIsEditWCNGMotion        (true); emit signalEventChangedWCNGMotion               (value);}
    void setWCEnableEtcError        (quint16 value){ if(value == mModel.mWCEnableEtcError         ) return; mModel.mWCEnableEtcError         = value;  setIsEditWCEnableEtcError  (true); emit signalEventChangedWCEnableEtcError         (value);}
    void setDynamicFactor           (quint32 value){ if(value == mModel.mDynamicFactor            ) return; mModel.mDynamicFactor            = value;  setIsEditDynamicFactor     (true); emit signalEventChangedDynamicFactor            (value);}
    void setMDSenstivity            (quint16 value){ if(value == mModel.mMDSenstivity             ) return; mModel.mMDSenstivity             = value;  setIsEditMDSenstivity      (true); emit signalEventChangedMDSenstivity             (value);}
    void setMDNGMotion              (quint16 value){ if(value == mModel.mMDNGMotion               ) return; mModel.mMDNGMotion               = value;  setIsEditMDNGMotion        (true); emit signalEventChangedMDNGMotion               (value);}

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
    void setIsEditWCEnableEtcError  (bool    value){ if(value == mIsEditWCEnableEtcError   ) return; mIsEditWCEnableEtcError   = value; emit signalEventChangedIsEditWCEnableEtcError   (value);}
    void setIsEditDynamicFactor     (bool    value){ if(value == mIsEditDynamicFactor      ) return; mIsEditDynamicFactor      = value; emit signalEventChangedIsEditDynamicFactor      (value);}
    void setIsEditMDSenstivity      (bool    value){ if(value == mIsEditMDSenstivity       ) return; mIsEditMDSenstivity       = value; emit signalEventChangedIsEditMDSenstivity       (value);}
    void setIsEditMDNGMotion        (bool    value){ if(value == mIsEditMDNGMotion         ) return; mIsEditMDNGMotion         = value; emit signalEventChangedIsEditMDNGMotion         (value);}

signals:
    void signalEventChangedIsNull                   (bool    value);
    void signalEventChangedIsNew                    (bool    value);
    void signalEventChangedIsRemoved                (bool    value);

    void signalEventChangedSeq                      (quint64 value);
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
    void signalEventChangedWCEnableEtcError         (quint16 value);
    void signalEventChangedDynamicFactor            (int     value);
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
    void signalEventChangedIsEditWCEnableEtcError   (bool    value);
    void signalEventChangedIsEditDynamicFactor      (bool    value);
    void signalEventChangedIsEditMDSenstivity       (bool    value);
    void signalEventChangedIsEditMDNGMotion         (bool    value);

public slots:
    Q_INVOKABLE void onCommandSetSeq                     (quint64 value){ setSeq               (value);}
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
    Q_INVOKABLE void onCommandSetWCEnableEtcError        (bool    value){ qDebug() << "[debug]value = " << value; setWCEnableEtcError  (value == true ? 1 : 0);}
    Q_INVOKABLE void onCommandSetDynamicFactor           (int     value){ setDynamicFactor     (value);}
    Q_INVOKABLE void onCommandSetMDSenstivity            (quint16 value){ setMDSenstivity      (value);}
    Q_INVOKABLE void onCommandSetMDNGMotion              (quint16 value){ setMDNGMotion        (value);}

public:
    void reset()
    {
        setData(mModel.mSeq);
    }

    void setData(quint64 seq)
    {
        mpProductService = &(CoreService::getInstance()->mProductSettingServcie);

        ProductSettingModel * ps = mpProductService->findProductSettingBySeq(seq);

        if(ps == nullptr)
        {
            setSeq                     (0 );
            setNo                      (0 );
            setName                    ("");
            setLength                  (0 );
            setSpeed                   (0 );
            setMotorAcceleration       (0 );
            setUnderWeight             (0 );
            setUnderWarningWeight      (0 );
            setNormalWeight            (0 );
            setOverWarningWeight       (0 );
            setOverWeight              (0 );
            setTareWeight              (0 );
            setWCNGMotion              (0 );
            setWCEnableEtcError        (1 );
            setDynamicFactor           (0 );
            setMDSenstivity            (0 );
            setMDNGMotion              (0 );
        }
        else
        {
            qDebug() << "[debug]mWCEnableEtcError: " << ps->mWCEnableEtcError;

            setSeq               (ps->mSeq                  );
            setNo                (ps->mNo                   );
            setName              (ps->mName                 );
            setLength            (ps->mLength               );
            setSpeed             (ps->mSpeed                );
            setMotorAcceleration (ps->mMotorAccelerationTime);
            setUnderWeight       (ps->mUnderWeight          );
            setUnderWarningWeight(ps->mUnderWarningWeight   );
            setNormalWeight      (ps->mNormalWeight         );
            setOverWarningWeight (ps->mOverWarningWeight    );
            setOverWeight        (ps->mOverWeight           );
            setTareWeight        (ps->mTareWeight           );
            setWCNGMotion        (ps->mWCNGMotion           );
            setWCEnableEtcError  (ps->mWCEnableEtcError     );
            setDynamicFactor     (ps->mDynamicFactor        );
            setMDSenstivity      (ps->mMDSenstivity         );
            setMDNGMotion        (ps->mMDNGMotion           );
        }

        setIsNew                   (false);
        setIsEditNo                (false);
        setIsEditName              (false);
        setIsEditLength            (false);
        setIsEditSpeed             (false);
        setIsEditMotorAcceleration (false);
        setIsEditUnderWeight       (false);
        setIsEditUnderWarningWeight(false);
        setIsEditNormalWeight      (false);
        setIsEditOverWarningWeight (false);
        setIsEditOverWeight        (false);
        setIsEditTareWeight        (false);
        setIsEditWCNGMotion        (false);
        setIsEditWCEnableEtcError  (false);
        setIsEditDynamicFactor     (false);
        setIsEditMDSenstivity      (false);
        setIsEditMDNGMotion        (false);
    }

    void setNewSetting(ProductSettingModel * pNewProduct)
    {
        setSeq               (pNewProduct->mSeq                  );
        setNo                (pNewProduct->mNo                   );
        setName              (pNewProduct->mName                 );
        setLength            (pNewProduct->mLength               );
        setSpeed             (pNewProduct->mSpeed                );
        setMotorAcceleration (pNewProduct->mMotorAccelerationTime);
        setUnderWeight       (pNewProduct->mUnderWeight          );
        setUnderWarningWeight(pNewProduct->mUnderWarningWeight   );
        setNormalWeight      (pNewProduct->mNormalWeight         );
        setOverWarningWeight (pNewProduct->mOverWarningWeight    );
        setOverWeight        (pNewProduct->mOverWeight           );
        setTareWeight        (pNewProduct->mTareWeight           );
        setWCNGMotion        (pNewProduct->mWCNGMotion           );
        setWCEnableEtcError  (pNewProduct->mWCEnableEtcError     );
        setDynamicFactor     (pNewProduct->mDynamicFactor        );
        setMDSenstivity      (pNewProduct->mMDSenstivity         );
        setMDNGMotion        (pNewProduct->mMDNGMotion           );

        setIsNew                   (true);
        setIsEditNo                (true);
        setIsEditName              (true);
        setIsEditLength            (true);
        setIsEditSpeed             (true);
        setIsEditMotorAcceleration (true);
        setIsEditUnderWeight       (true);
        setIsEditUnderWarningWeight(true);
        setIsEditNormalWeight      (true);
        setIsEditOverWarningWeight (true);
        setIsEditOverWeight        (true);
        setIsEditTareWeight        (true);
        setIsEditWCNGMotion        (true);
        setIsEditWCEnableEtcError  (true);
        setIsEditDynamicFactor     (true);
        setIsEditMDSenstivity      (true);
        setIsEditMDNGMotion        (true);
    }
    explicit ProductSettingItemModel(QObject *parent = nullptr):QObject(parent){}

};

#endif // PRODUCTSETTINGITEMMODEL_H
