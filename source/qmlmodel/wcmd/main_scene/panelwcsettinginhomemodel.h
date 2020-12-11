#ifndef PANELWCSETTINGINHOMEMODEL_H
#define PANELWCSETTINGINHOMEMODEL_H

#include <QObject>
#include "source/globaldef/EnumDefine.h"
#include "source/service/coreservice.h"

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

public slots:
    Q_INVOKABLE void onCommandSetUnderWeight     (quint32 value)
    {
        setUnderWeight(value);
        setUnderGap    (mNormalWeight - mUnderWeight);
    }
    Q_INVOKABLE void onCommandSetNormalWeight    (quint32 value)
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
    Q_INVOKABLE void onCommandSetOverWeight      (quint32 value)
    {
        setOverWeight  (value);
        setOverGap     (mOverWeight - mNormalWeight);
    }
    Q_INVOKABLE void onCommandSetUnderGap        (qint32  value)
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
    Q_INVOKABLE void onCommandSetOverGap         (qint32  value)
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
    Q_INVOKABLE void onCommandApply()
    {
        PDSettingDto editPD = pProductSP->mCurrPD;
        editPD.mDspForm.mWCSetting.mUnderWeight        = mUnderWeight ;
        editPD.mDspForm.mWCSetting.mUnderWarningWeight = mUnderWeight ;
        editPD.mDspForm.mWCSetting.mNormalWeight       = mNormalWeight;
        editPD.mDspForm.mWCSetting.mOverWarningWeight  = mOverWeight  ;
        editPD.mDspForm.mWCSetting.mOverWeight         = mOverWeight  ;

        int ret = pProductSP->editPD(editPD);

        if(ret == EnumDefine::DatabaseErrorType::DB_NONE_ERROR)
        {
            setIsEditUnderWeight (false);
            setIsEditNormalWeight(false);
            setIsEditOverWeight  (false);
            setIsEditUnderGap    (false);
            setIsEditOverGap     (false);
        }

        emit signalEventResultSaveProductSetting(ret);
    }

// down layer =============================================================
public slots:
    void onChangedCurrPDSetting(PDSettingDto dto)
    {
        setUnderWeight (dto.mDspForm.mWCSetting.mUnderWeight );
        setNormalWeight(dto.mDspForm.mWCSetting.mNormalWeight);
        setOverWeight  (dto.mDspForm.mWCSetting.mOverWeight  );
    }

// internal layer =============================================================
public:
    explicit PanelWCSettingInHomeModel(QObject *parent = nullptr):QObject(parent)
    {
        ENABLE_SLOT_PDSETTING_CHANGED_CURR_PD;
        onChangedCurrPDSetting(pProductSP->mCurrPD);

        setUnderGap    (mNormalWeight - mUnderWeight);
        setOverGap     (mOverWeight - mNormalWeight);

        setIsEditUnderWeight (false);
        setIsEditNormalWeight(false);
        setIsEditOverWeight  (false);
        setIsEditUnderGap    (false);
        setIsEditOverGap     (false);
    }
};

#endif // PANELWCSETTINGINHOMEMODEL_H
