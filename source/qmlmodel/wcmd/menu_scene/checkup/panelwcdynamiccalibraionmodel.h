#ifndef PANELWCDYNAMICCALIBRAIONMODEL_H
#define PANELWCDYNAMICCALIBRAIONMODEL_H

#include <QObject>
#include <QTimer>

#include "source/service/coreservice.h"
#include "source/globaldef/qmlenumdef.h"

class PanelWCDynamicCalibrationModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint32  step          READ getStep          NOTIFY signalEventChangedStep         )
    Q_PROPERTY(bool    isRemeasure    READ getIsRemeasure   NOTIFY signalEventChangedIsRemeasure  )
    Q_PROPERTY(quint16 pdNum          READ getPdNum         NOTIFY signalEventChangedPdNum        )
    Q_PROPERTY(QString pdName         READ getPdName        NOTIFY signalEventChangedPdName       )
    Q_PROPERTY(quint32 dynamicFactor  READ getDynamicFactor NOTIFY signalEventChangedDynamicFactor)
    Q_PROPERTY(qint32  currWeight     READ getCurrWeight    NOTIFY signalEventChangedCurrWeight   )
    Q_PROPERTY(quint32 refWeight      READ getRefWeight     NOTIFY signalEventChangedRefWeight    )
    Q_PROPERTY(quint32 movingWeight   READ getMovingWeight  NOTIFY signalEventChangedMovingWeight )
    Q_PROPERTY(quint32 tryCount       READ getTryCount      NOTIFY signalEventChangedTryCount     )
    Q_PROPERTY(quint32 tareWeight     READ getTareWeight    NOTIFY signalEventChangedTareWeight   )

public:
    quint64 mDspSeq       = 0;
    quint32  mStep        = QmlEnumDef::DYNAMIC_CARIB_STEP_INIT;
    bool    mIsRemeasure  ;
    quint16 mPdNum        ;
    QString mPdName       ;
    quint32 mDynamicFactor;
    qint32  mCurrWeight   ;
    quint32 mRefWeight    ;
    quint32 mMovingWeight ;
    quint32 mTryCount     ;
    quint32 mTareWeight   ;

    bool    getIsRemeasure  (){ return mIsRemeasure  ;}
    quint32 getStep         (){ return mStep         ;}
    quint16 getPdNum        (){ return mPdNum        ;}
    QString getPdName       (){ return mPdName       ;}
    quint32 getDynamicFactor(){ return mDynamicFactor;}
    qint32  getCurrWeight   (){ return mCurrWeight   ;}
    quint32 getRefWeight    (){ return mRefWeight    ;}
    quint32 getMovingWeight (){ return mMovingWeight ;}
    quint32 getTryCount     (){ return mTryCount     ;}
    quint32 getTareWeight   (){ return mTareWeight   ;}

    void    setIsRemeasure  (bool    value){ if(value == mIsRemeasure  ) return; mIsRemeasure   = value; emit signalEventChangedIsRemeasure  (value);}
    void    setStep         (quint32 value){ if(value == mStep         ) return; mStep          = value; emit signalEventChangedStep         (value);}
    void    setPdNum        (quint16 value){ if(value == mPdNum        ) return; mPdNum         = value; emit signalEventChangedPdNum        (value);}
    void    setPdName       (QString value){ if(value == mPdName       ) return; mPdName        = value; emit signalEventChangedPdName       (value);}
    void    setDynamicFactor(quint32 value){ if(value == mDynamicFactor) return; mDynamicFactor = value; emit signalEventChangedDynamicFactor(value);}
    void    setCurrWeight   (qint32  value){ if(value == mCurrWeight   ) return; mCurrWeight    = value; emit signalEventChangedCurrWeight   (value);}
    void    setRefWeight    (quint32 value){ if(value == mRefWeight    ) return; mRefWeight     = value; emit signalEventChangedRefWeight    (value);}
    void    setMovingWeight (quint32 value){ if(value == mMovingWeight ) return; mMovingWeight  = value; emit signalEventChangedMovingWeight (value);}
    void    setTryCount     (quint32 value){ if(value == mTryCount     ) return; mTryCount      = value; emit signalEventChangedTryCount     (value);}
    void    setTareWeight   (quint32 value){ if(value == mTareWeight   ) return; mTareWeight    = value; emit signalEventChangedTareWeight   (value);}

    explicit PanelWCDynamicCalibrationModel(QObject *parent = nullptr) : QObject(parent)
    {
        setStep((quint32)QmlEnumDef::DYNAMIC_CARIB_STEP_INIT);
        setCurrWeight(0);
        setRefWeight(0);//pLSettingSP->mDevSetting.mDspForm.mWCSetting.mDynamicBaseWeight);
        setMovingWeight(0);
        setTryCount(0);
        setTareWeight(pProductSP->mCurrPD.mDspForm.mWCSetting.mTareWeight);

        CHECK_FALSE_RETURN((pDspSP->mDspList.size() > 0));

        mDspSeq = pDspSP->mDspList[0]->mSeq;

        ENABLE_SLOT_PDSETTING_CHANGED_CURR_PD;
        ENABLE_SLOT_DSP_ADDED_EVENT;
        ENABLE_SLOT_DSP_CHANGED_DSP_STATUS;

        onChangedCurrPDSetting(pProductSP->mCurrPD);

    }
    ~PanelWCDynamicCalibrationModel()
    {
        CHECK_FALSE_RETURN((mDspSeq != 0));

        pDspSP->sendRunCmd(mDspSeq, EnumDef::RUN_MODE_STOP);
    }

signals:
    void    signalEventChangedStep         (quint32 value);
    void    signalEventChangedIsRemeasure  (bool    value);
    void    signalEventChangedPdNum        (quint16 value);
    void    signalEventChangedPdName       (QString value);
    void    signalEventChangedDynamicFactor(quint32 value);
    void    signalEventChangedRefWeight    (quint32 value);
    void    signalEventChangedMovingWeight (quint32 value);
    void    signalEventChangedCurrWeight   (qint32  value);
    void    signalEventChangedTryCount     (quint32 value);
    void    signalEventChangedTareWeight   (quint32 value);
    void    signalEventCompleteCalibration (             );
    void    signalEventInvalidCalibration  (quint32 value);

public slots:
    Q_INVOKABLE void onCommandPDConfirm()
    {
        qDebug() << "[khko_debug]onCommandPDConfirm";
        setStep((quint32)QmlEnumDef::DYNAMIC_CARIB_STEP_ZERO);
    }
    Q_INVOKABLE void onCommandZERO()
    {
        CHECK_FALSE_RETURN((mDspSeq != 0));

        pDspSP->sendZeroCmd(mDspSeq);
        setStep((quint32)QmlEnumDef::DYNAMIC_CARIB_STEP_STD_SETTING);
    }

    Q_INVOKABLE void onCommandCaribration()
    {
        CHECK_FALSE_RETURN((mDspSeq != 0));

        pDspSP->sendWCCaribCmd(mDspSeq, EnumDef::WC_CALIB_TYPE_DYNAMIC);
    }

    Q_INVOKABLE void onCommandSetRefWeight(quint32 value)
    {
        DevSettingDto dto = pLSettingSP->mDevSetting;
        dto.mDspForm.mWCSetting.mDynamicBaseWeight =value;
        pLSettingSP->setDevSetting(dto);
        setRefWeight(value);
        setStep((quint32)QmlEnumDef::DYNAMIC_CARIB_STEP_CARIB_ING);
    }

    Q_INVOKABLE void onCommandRemeasurement()
    {
        setMovingWeight(0);

        CHECK_FALSE_RETURN((mDspSeq != 0));

        pDspSP->sendRunCmd(mDspSeq, EnumDef::RUN_MODE_CHECKUP_RUN);
    }

    Q_INVOKABLE void onCommandClosed()
    {
        CHECK_FALSE_RETURN((mDspSeq != 0));

        pDspSP->sendRunCmd(mDspSeq, EnumDef::RUN_MODE_STOP);
    }

public slots:
    void onAddedDspEvent(quint64 dspSeq, DspEventDto dto)
    {
        qDebug() << "[debug]type = " << dto.mEvent.mEventType << ",value = " << dto.mEvent.mEventValue;
        CHECK_FALSE_RETURN((mDspSeq == dspSeq));

        if( dto.mEvent.mEventType == EnumDef::ET_WEIGHT_NORMAL_CHECK              ||
            dto.mEvent.mEventType == EnumDef::ET_WEIGHT_UNDER_WARNING_CHECK       ||
            dto.mEvent.mEventType == EnumDef::ET_WEIGHT_OVER_WARNING_CHECK        ||
            dto.mEvent.mEventType == EnumDef::ET_WEIGHT_UNDER_CHECK               ||
            dto.mEvent.mEventType == EnumDef::ET_WEIGHT_OVER_CHECK                ||
            dto.mEvent.mEventType == EnumDef::ET_WEIGHT_ETCERROR_CHECK            ||
            dto.mEvent.mEventType == EnumDef::ET_WEIGHT_ETC_METAL_ERROR_CHECK      )
        {
            return setTryCount(dto.mEvent.mEventValue);
            //return setMovingWeight(dto.mEvent.mEventValue + pProductSP->mCurrPD.mDspForm.mWCSetting.mTareWeight);
        }

        if(dto.mEvent.mEventType == EnumDef::ET_WEIGHT_DYNAMIC_CARI)
        {
            PDSettingDto setting = pProductSP->mCurrPD;

            qDebug() << "[debug] df = " << dto.mEvent.mEventValue;

            //if(dto.mEvent.mEventValue < 5000000 || dto.mEvent.mEventValue > 15000000)
            //{
            //    setting.mDspForm.mWCSetting.mDynamicFactor = 10000000;
            //    pProductSP->editPD(setting);
            //    emit signalEventInvalidCalibration();
            //}
            //else
            //{
            setting.mDspForm.mWCSetting.mDynamicFactor = dto.mEvent.mEventValue;
            pProductSP->editPD(setting);
            emit signalEventCompleteCalibration();
            if(dto.mEvent.mEventValue < 5000000 || dto.mEvent.mEventValue > 15000000)
            {
                emit signalEventInvalidCalibration(dto.mEvent.mEventValue);
            }
            //}

        }
    }

    void onChangedDspStatus(quint64 dspSeq, DspStatusDto dto)
    {
        CHECK_FALSE_RETURN((mDspSeq == dspSeq));

        if(dto.mWCStatus.mCurrWeight == 0)
        {
            setCurrWeight(0);
        }
        else
        {
            return setCurrWeight(dto.mWCStatus.mCurrWeight/* + pProductSP->mCurrPD.mDspForm.mWCSetting.mTareWeight*/);
        }
    }

    void onChangedCurrPDSetting(PDSettingDto dto)
    {
        setPdNum(dto.mDspForm.mCommSetting.mProductNum);
        setPdName(dto.mName);
        setDynamicFactor(dto.mDspForm.mWCSetting.mDynamicFactor);
    }

};
#endif // PANELWCDYNAMICCALIBRAIONMODEL_H
