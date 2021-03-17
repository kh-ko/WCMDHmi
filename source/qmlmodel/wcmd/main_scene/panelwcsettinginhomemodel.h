#ifndef PANELWCSETTINGINHOMEMODEL_H
#define PANELWCSETTINGINHOMEMODEL_H

#include <QObject>
#include "source/globaldef/qmlenumdef.h"
#include "source/service/coreservice.h"

class PanelWCSettingInHomeModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint32  currWeight         READ getCurrWeight             NOTIFY signalEventChangedCurrWeight        )
    Q_PROPERTY(quint32  underWeight        READ getUnderWeight            NOTIFY signalEventChangedUnderWeight       )
    Q_PROPERTY(quint32  normalWeight       READ getNormalWeight           NOTIFY signalEventChangedNormalWeight      )
    Q_PROPERTY(quint32  overWeight         READ getOverWeight             NOTIFY signalEventChangedOverWeight        )
    Q_PROPERTY(qint32   underGap           READ getUnderGap               NOTIFY signalEventChangedUnderGap          )
    Q_PROPERTY(qint32   overGap            READ getOverGap                NOTIFY signalEventChangedOverGap           )

    Q_PROPERTY(bool     isEditUnderWeight  READ getIsEditUnderWeight      NOTIFY signalEventChangedIsEditUnderWeight )
    Q_PROPERTY(bool     isEditNormalWeight READ getIsEditNormalWeight     NOTIFY signalEventChangedIsEditNormalWeight)
    Q_PROPERTY(bool     isEditOverWeight   READ getIsEditOverWeight       NOTIFY signalEventChangedIsEditOverWeight  )
    Q_PROPERTY(bool     isEditUnderGap     READ getIsEditUnderGap         NOTIFY signalEventChangedIsEditUnderGap    )
    Q_PROPERTY(bool     mOverGap           READ getIsEditOverGap          NOTIFY signalEventChangedIsEditOverGap     )

public:
    quint64  mDspSeq      ;
    qint32   mCurrWeight  ;
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

    qint32   getCurrWeight        ()
    {
        if((qint32)pLSettingSP->mDevSetting.mDspForm.mWCSetting.mMinStaticWeight > mCurrWeight) return 0;

        return mCurrWeight;
    }
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

    void     setCurrWeight        (qint32  value){ if( value == mCurrWeight         ) return; mCurrWeight          = value; emit signalEventChangedCurrWeight        (value);}
    void     setUnderWeight       (quint32 value){ if( value == mUnderWeight        ) return; mUnderWeight         = value; setIsEditUnderWeight (true); emit signalEventChangedUnderWeight (value);}
    void     setNormalWeight      (quint32 value){ if( value == mNormalWeight       ) return; mNormalWeight        = value; setIsEditNormalWeight(true); emit signalEventChangedNormalWeight(value);}
    void     setOverWeight        (quint32 value){ if( value == mOverWeight         ) return; mOverWeight          = value; setIsEditOverWeight  (true); emit signalEventChangedOverWeight  (value);}
    void     setUnderGap          (qint32  value){ if( value == mUnderGap           ) return; mUnderGap            = value; setIsEditUnderGap    (true); emit signalEventChangedUnderGap    (value);}
    void     setOverGap           (qint32  value){ if( value == mOverGap            ) return; mOverGap             = value; setIsEditOverGap     (true); emit signalEventChangedOverGap     (value);}
    void     setIsEditUnderWeight (bool    value){ if( value == mIsEditUnderWeight  ) return; mIsEditUnderWeight   = value; emit signalEventChangedIsEditUnderWeight  (value);}
    void     setIsEditNormalWeight(bool    value){ if( value == mIsEditNormalWeight ) return; mIsEditNormalWeight  = value; emit signalEventChangedIsEditNormalWeight (value);}
    void     setIsEditOverWeight  (bool    value){ if( value == mIsEditOverWeight   ) return; mIsEditOverWeight    = value; emit signalEventChangedIsEditOverWeight   (value);}
    void     setIsEditUnderGap    (bool    value){ if( value == mIsEditUnderGap     ) return; mIsEditUnderGap      = value; emit signalEventChangedIsEditUnderGap     (value);}
    void     setIsEditOverGap     (bool    value){ if( value == mIsEditOverGap      ) return; mIsEditOverGap       = value; emit signalEventChangedIsEditOverGap      (value);}

signals:
    void signalEventChangedCurrWeight        (qint32  value);
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

        if(ret == EnumDef::PDERR_NONE)
        {
            setIsEditUnderWeight (false);
            setIsEditNormalWeight(false);
            setIsEditOverWeight  (false);
            setIsEditUnderGap    (false);
            setIsEditOverGap     (false);
        }

        emit signalEventResultSaveProductSetting(ret);
    }

    Q_INVOKABLE qint32 onCommandCurrWeight()
    {
        qint32 currWeight;
        if(pDspSP->mDspList.size() > 0)
        {
            DspStatusDto status = pDspSP->mDspList[0]->mRcvDataStore.getStatusDto();
            currWeight = status.mWCStatus.mCurrWeight;
            if(currWeight >= (qint32)pLSettingSP->mDevSetting.mDspForm.mWCSetting.mMinStaticWeight)
            {
                return status.mWCStatus.mCurrWeight;
            }
        }

        return 0;
    }

// down layer =============================================================
public slots:
    void onChangedCurrPDSetting(PDSettingDto dto)
    {
        setUnderWeight (dto.mDspForm.mWCSetting.mUnderWeight );
        setNormalWeight(dto.mDspForm.mWCSetting.mNormalWeight);
        setOverWeight  (dto.mDspForm.mWCSetting.mOverWeight  );
    }

    void onChangedDspStatus(quint64 dspSeq, DspStatusDto dto)
    {
        CHECK_FALSE_RETURN((mDspSeq == dspSeq));

        setCurrWeight(dto.mWCStatus.mCurrWeight);
    }

// internal layer =============================================================
public:
    explicit PanelWCSettingInHomeModel(QObject *parent = nullptr):QObject(parent)
    {
        if(pDspSP->mDspList.size() > 0)
        {
            mDspSeq = pDspSP->mDspList[0]->mSeq;
        }

        ENABLE_SLOT_DSP_CHANGED_DSP_STATUS;
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
