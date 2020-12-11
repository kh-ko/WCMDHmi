#ifndef PANELWCDYNAMICCALIBRAIONMODEL_H
#define PANELWCDYNAMICCALIBRAIONMODEL_H

#include <QObject>
#include <QTimer>

#include "source/service/coreservice.h"
#include "source/globaldef/EnumDefine.h"

class PanelWCDynamicCalibrationModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    isRemeasure    READ getIsRemeasure   NOTIFY signalEventChangedIsRemeasure )
    Q_PROPERTY(quint32 currWeight     READ getCurrWeight    NOTIFY signalEventChangedCurrWeight  )
    Q_PROPERTY(quint32 refWeight      READ getRefWeight     NOTIFY signalEventChangedRefWeight   )
    Q_PROPERTY(quint32 movingWeight   READ getMovingWeight  NOTIFY signalEventChangedMovingWeight)

public:
    quint64 mDspSeq      = 0;
    bool    mIsRemeasure ;
    quint32 mCurrWeight  ;
    quint32 mRefWeight   ;
    quint32 mMovingWeight;

    bool    getIsRemeasure (){ return mIsRemeasure ;}
    quint32 getCurrWeight  (){ return mCurrWeight  ;}
    quint32 getRefWeight   (){ return mRefWeight   ;}
    quint32 getMovingWeight(){ return mMovingWeight;}

    void    setIsRemeasure (bool    value){ if(value == mIsRemeasure ) return; mIsRemeasure  = value; emit signalEventChangedIsRemeasure (value);}
    void    setCurrWeight  (quint32 value){ if(value == mCurrWeight  ) return; mCurrWeight   = value; emit signalEventChangedCurrWeight  (value);}
    void    setRefWeight   (quint32 value){ if(value == mRefWeight   ) return; mRefWeight    = value; emit signalEventChangedRefWeight   (value);}
    void    setMovingWeight(quint32 value){ if(value == mMovingWeight) return; mMovingWeight = value; emit signalEventChangedMovingWeight(value);}

    explicit PanelWCDynamicCalibrationModel(QObject *parent = nullptr) : QObject(parent)
    {
        setCurrWeight(0);
        setRefWeight(pLSettingSP->mDevSetting.mDspForm.mWCSetting.mDynamicBaseWeight);
        setMovingWeight(0);

        CHECK_FALSE_RETURN((pDspSP->mDspList.size() > 0));

        mDspSeq = pDspSP->mDspList[0]->mSeq;

        ENABLE_SLOT_DSP_ADDED_EVENT;
        ENABLE_SLOT_DSP_CHANGED_DSP_STATUS;
    }
    ~PanelWCDynamicCalibrationModel()
    {
        CHECK_FALSE_RETURN((mDspSeq != 0));

        pDspSP->sendRunCmd(mDspSeq, EnumDefine::RunState::STOP);
    }

signals:
    void    signalEventChangedIsRemeasure (bool    value);
    void    signalEventChangedRefWeight   (quint32 value);
    void    signalEventChangedMovingWeight(quint32 value);
    void    signalEventChangedCurrWeight  (quint32 value);
    void    signalEventCompleteCalibration(             );

public slots:
    Q_INVOKABLE void onCommandCaribration()
    {
        CHECK_FALSE_RETURN((mDspSeq != 0));

        pDspSP->sendWCCaribCmd(mDspSeq, EnumDefine::WCCalibType::WC_CALIB_DYNAMIC);
    }

    Q_INVOKABLE void onCommandSetRefWeight(quint32 value)
    {
        DevSettingDto dto = pLSettingSP->mDevSetting;
        dto.mDspForm.mWCSetting.mDynamicBaseWeight =value;
        pLSettingSP->setDevSetting(dto);
        setRefWeight(value);
    }

    Q_INVOKABLE void onCommandRemeasurement()
    {
        setMovingWeight(0);

        CHECK_FALSE_RETURN((mDspSeq != 0));

        pDspSP->sendRunCmd(mDspSeq, EnumDefine::RunState::CHECKUP_RUN);
    }

    Q_INVOKABLE void onCommandClosed()
    {
        CHECK_FALSE_RETURN((mDspSeq != 0));

        pDspSP->sendRunCmd(mDspSeq, EnumDefine::RunState::STOP);
    }

public slots:
    void onAddedDspEvent(quint64 dspSeq, DspEventDto dto)
    {
        CHECK_FALSE_RETURN((mDspSeq == dspSeq));

        if( dto.mEvent.mEventType == EnumDefine::EventType::WEIGHT_NORMAL_CHECK_TYPE         ||
            dto.mEvent.mEventType == EnumDefine::EventType::WEIGHT_UNDER_WARNING_CHECK_TYPE  ||
            dto.mEvent.mEventType == EnumDefine::EventType::WEIGHT_OVER_WARNING_CHECK_TYPE   ||
            dto.mEvent.mEventType == EnumDefine::EventType::WEIGHT_UNDER_CHECK_TYPE          ||
            dto.mEvent.mEventType == EnumDefine::EventType::WEIGHT_OVER_CHECK_TYPE           ||
            dto.mEvent.mEventType == EnumDefine::EventType::WEIGHT_ETCERROR_CHECK_TYPE)
        {
            return setMovingWeight(dto.mEvent.mEventValue + pProductSP->mCurrPD.mDspForm.mWCSetting.mTareWeight);
        }

        if(dto.mEvent.mEventType == EnumDefine::EventType::WEIGHT_DYNAMIC_CARI_TYPE)
        {
            PDSettingDto setting = pProductSP->mCurrPD;
            setting.mDspForm.mWCSetting.mDynamicFactor = dto.mEvent.mEventValue;
            pProductSP->editPD(setting);

            emit signalEventCompleteCalibration();
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
            return setCurrWeight(dto.mWCStatus.mCurrWeight + pProductSP->mCurrPD.mDspForm.mWCSetting.mTareWeight);
        }
    }

};
#endif // PANELWCDYNAMICCALIBRAIONMODEL_H
