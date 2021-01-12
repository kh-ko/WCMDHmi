#ifndef PANELFULLMDMODEL_H
#define PANELFULLMDMODEL_H

#include <QObject>

#include "source/service/def/datetimeform.h"
#include "source/service/coreservice.h"

class PanelFullMDModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint16 mPDSeq          READ getPDSeq          NOTIFY signalEventChangedPDSeq         )
    Q_PROPERTY(quint16 mPDNum          READ getPDNum          NOTIFY signalEventChangedPDNum         )
    Q_PROPERTY(QString mPDName         READ getPDName         NOTIFY signalEventChangedPDName        )
    Q_PROPERTY(quint16 mSenstivity     READ getSenstivity     NOTIFY signalEventChangedSenstivity    )
    Q_PROPERTY(quint16 mTempSenstivity READ getTempSenstivity NOTIFY signalEventChangedTempSenstivity)
    Q_PROPERTY(quint16 mCurrSignal     READ getCurrSignal     NOTIFY signalEventChangedCurrSignal    )
    Q_PROPERTY(int     mTotalCnt       READ getTotalCnt       NOTIFY signalEventChangedTotalCnt      )
    Q_PROPERTY(int     mDetectCnt      READ getDetectCnt      NOTIFY signalEventChangedDetectCnt     )
    Q_PROPERTY(int     mGraphMaxCnt    READ getGraphMaxCnt    NOTIFY signalEventChangedGraphMaxCnt   )

public:
    quint64 mDspSeq         = 0;
    qint64  mEditTime       = 0;
    //QList<quint32> *        mpMDTrends(){static QList<quint32> trends; return &trends;}

    quint64 mPDSeq          ;
    quint16 mPDNum          ;
    QString mPDName         ;
    quint16 mSenstivity     ;
    quint16 mTempSenstivity ;
    quint16 mCurrSignal     = 0;
    int     mTotalCnt       = 0;
    int     mDetectCnt      = 0;
    int     mGraphMaxCnt    = MDTR_LIMIT;

    quint64 getPDSeq         (){ return mPDSeq         ;}
    quint16 getPDNum         (){ return mPDNum         ;}
    QString getPDName        (){ return mPDName        ;}
    quint16 getSenstivity    (){ return mSenstivity    ;}
    quint16 getTempSenstivity(){ return mTempSenstivity;}
    quint16 getCurrSignal    (){ return mCurrSignal    ;}
    int     getTotalCnt      (){ return mTotalCnt      ;}
    int     getDetectCnt     (){ return mDetectCnt     ;}
    int     getGraphMaxCnt   (){ return mGraphMaxCnt   ;}

    void setPDSeq         (quint64 value){ if( mPDSeq          == value ) return; mPDSeq          = value; emit signalEventChangedPDSeq         (mPDSeq         ); }
    void setPDNum         (quint16 value){ if( mPDNum          == value ) return; mPDNum          = value; emit signalEventChangedPDNum         (mPDNum         ); }
    void setPDName        (QString value){ if( mPDName         == value ) return; mPDName         = value; emit signalEventChangedPDName        (mPDName        ); }
    void setSenstivity    (quint16 value){ if( mSenstivity     == value ) return; mSenstivity     = value; emit signalEventChangedSenstivity    (mSenstivity    ); setTempSenstivity(value); }
    void setTempSenstivity(quint16 value){ if( mTempSenstivity == value ) return; mTempSenstivity = value; emit signalEventChangedTempSenstivity(mTempSenstivity); }
    void setCurrSignal    (quint16 value){ if( mCurrSignal     == value ) return; mCurrSignal     = value; emit signalEventChangedCurrSignal    (mCurrSignal    ); }
    void setTotalCnt      (int     value){ if( mTotalCnt       == value ) return; mTotalCnt       = value; emit signalEventChangedTotalCnt      (mTotalCnt      ); }
    void setDetectCnt     (int     value){ if( mDetectCnt      == value ) return; mDetectCnt      = value; emit signalEventChangedDetectCnt     (mDetectCnt     ); }
    void setGraphMaxCnt   (int     value){ if( mGraphMaxCnt    == value ) return; mGraphMaxCnt    = value; emit signalEventChangedGraphMaxCnt   (mGraphMaxCnt   ); }

signals:
    void signalEventChangedPDSeq         (quint64 value);
    void signalEventChangedPDNum         (quint16 value);
    void signalEventChangedPDName        (QString value);
    void signalEventChangedSenstivity    (quint16 value);
    void signalEventChangedTempSenstivity(quint16 value);
    void signalEventChangedCurrSignal    (quint16 value);
    void signalEventChangedTotalCnt      (int     value);
    void signalEventChangedDetectCnt     (int     value);
    void signalEventChangedGraphMaxCnt   (int     value);

    void signalEventAddedValue           (quint16 type, quint32 value);
    void signalEventTimeTick             (             );

public slots:
    Q_INVOKABLE void  onCommandSetTempSenstivity(quint16 value)
    {
        mEditTime = QDateTime::currentMSecsSinceEpoch();
        setTempSenstivity(value);
    }
    Q_INVOKABLE void   onCommandApplySenstivity()
    {
        setSenstivity(mTempSenstivity);

        PDSettingDto setting = pProductSP->mCurrPD;
        setting.mDspForm.mMDSetting.mSenstivity = mTempSenstivity;

        pProductSP->editPD(setting);
    }
    Q_INVOKABLE bool onCommandComparePwd(QString value)
    {
        if(pLSettingSP->mSecuritySetting.mPwd == value)
            return true;

        return false;
    }
    Q_INVOKABLE bool onCommandCompareAdminPwd(QString value)
    {
        if(pLSettingSP->mSecuritySetting.mAdminPwd == value)
            return true;

        return false;
    }
    Q_INVOKABLE int onCommandGetTRCount()
    {
        return pWorkSP->mTRManager.mMDTrends.size();
    }
    Q_INVOKABLE bool onCommandGetTRIsTradeEvent(int idx)
    {
        if(idx < pWorkSP->mTRManager.mMDTrends.size())
            return pWorkSP->mTRManager.mMDTrends[idx].mIsTrade;

        return true;
    }
    Q_INVOKABLE quint32 onCommandGetTRValue(int idx)
    {
        return pWorkSP->mTRManager.mMDTrends[idx].mValue;
    }


//  down layer ===================================================================================
public slots:
    void onChangedCurrPDSetting(PDSettingDto dto)
    {
        setPDSeq(dto.mSeq);
        setPDName(dto.mName);
        setPDNum(dto.mDspForm.mCommSetting.mProductNum);
        setSenstivity(dto.mDspForm.mMDSetting.mSenstivity);
    }

    void onChangedDspStatus(quint64 dspSeq, DspStatusDto dto)
    {
        CHECK_FALSE_RETURN((mDspSeq == dspSeq));

        setCurrSignal(dto.mMDStatus.mSignal);
    }

    void onAddedDspEvent(quint64 dspSeq, DspEventDto dto)
    {
        CHECK_FALSE_RETURN((mDspSeq == dspSeq));

        if(EventDto::isMDEvent(dto.mEvent.mEventType))
        {
            emit signalEventAddedValue(dto.mEvent.mEventType, dto.mEvent.mEventValue);
        }
    }

    void onChangedPDStats(PDStatsDto dto)
    {
        setTotalCnt(dto.mMDTotalCnt);
        setDetectCnt(dto.mMDFailCnt);
    }

    void onTimeTick(QDateTime now)
    {
        CHECK_FALSE_RETURN((mEditTime != 0));

        if(now.toMSecsSinceEpoch() - mEditTime > 15000)
        {
            setTempSenstivity(mSenstivity);
            mEditTime = 0;
        }
    }


//  internal layer ===================================================================================
public:
    explicit PanelFullMDModel(QObject *parent = nullptr): QObject(parent)
    {
        if(pDspSP->mDspList.size() > 0)
        {
            mDspSeq = pDspSP->mDspList[0]->mSeq;
        }

        ENABLE_SLOT_PDSETTING_CHANGED_CURR_PD;

        ENABLE_SLOT_WORK_CHANGED_STATS;

        ENABLE_SLOT_DSP_CHANGED_DSP_STATUS;
        ENABLE_SLOT_DSP_ADDED_EVENT;
        ENABLE_SLOT_TIMER_TICK;

        onChangedCurrPDSetting(pProductSP->mCurrPD);
        onChangedPDStats(pWorkSP->mCurrPD);

        onCommandSetTempSenstivity(mSenstivity);
    }
    ~PanelFullMDModel()
    {
    }
};
#endif // PANELFULLMDMODEL_H
