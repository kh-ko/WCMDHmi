#ifndef PANELWCSTATICCARIBRATIONMODEL_H
#define PANELWCSTATICCARIBRATIONMODEL_H

#include <QObject>
#include <QTimer>
#include "source/globaldef/qmlenumdef.h"
#include "source/service/coreservice.h"

class PanelWCStaticCaribrationModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint32  step              READ getStep             NOTIFY signalEventChangedStep          )
    Q_PROPERTY(quint32 standardWeight    READ getStandardWeight   NOTIFY signalEventChangedStandardWeight)
    Q_PROPERTY(qint32  currentWeight     READ getCurrentWeight    NOTIFY signalEventChangedCurrentWeight )

public:
    quint64 mDspSeq        = 0;
    qint32  mStep          = QmlEnumDef::STATIC_CARIB_STEP_INIT;
    quint32 mStandardWeight;
    qint32  mCurrentWeight ;

    qint32  getStep          (){ return mStep          ;}
    quint32 getStandardWeight(){ return mStandardWeight;}
    qint32  getCurrentWeight (){ return mCurrentWeight ;}

    void    setStep          (qint32  value) { if(value == mStep          ) return; mStep           = value; emit signalEventChangedStep          (value);}
    void    setStandardWeight(quint32 value) { if(value == mStandardWeight) return; mStandardWeight = value; emit signalEventChangedStandardWeight(value);}
    void    setCurrentWeight (qint32  value) { if(value == mCurrentWeight ) return; mCurrentWeight  = value; emit signalEventChangedCurrentWeight (value);}

    explicit PanelWCStaticCaribrationModel(QObject *parent = nullptr) : QObject(parent)
    {
        setStandardWeight(pLSettingSP->mDevSetting.mDspForm.mWCSetting.mStaticStandardWeight);
        setCurrentWeight(0);

        setStep(QmlEnumDef::STATIC_CARIB_STEP_INIT);

        CHECK_FALSE_RETURN((pDspSP->mDspList.size() > 0));

        mDspSeq = pDspSP->mDspList[0]->mSeq;

        ENABLE_SLOT_DSP_ADDED_EVENT;
        ENABLE_SLOT_DSP_CHANGED_DSP_STATUS;
    }

signals:
    void    signalEventChangedStep          (qint32   value);
    void    signalEventChangedStandardWeight(quint32 value);
    void    signalEventChangedCurrentWeight (qint32  value);

    void    signalCommandWeightCarib(quint16 deviceSeq, quint16 type);
    void    signalEventCompleteCalibration();

public slots:
    Q_INVOKABLE void onCommandZERO()
    {
        CHECK_FALSE_RETURN((mDspSeq != 0));

        pDspSP->sendZeroCmd(mDspSeq);

        setStep(QmlEnumDef::STATIC_CARIB_STEP_STD_WEIGHT_CHECK);
    }

    Q_INVOKABLE void onCommandSetStandardWeight(quint32 value)
    {
        DevSettingDto dto = pLSettingSP->mDevSetting;
        dto.mDspForm.mWCSetting.mStaticStandardWeight =value;

        pLSettingSP->setDevSetting(dto);
        setStandardWeight(value);
    }

    Q_INVOKABLE void onCommandConfirmStandardWeight()
    {
        setStep(QmlEnumDef::STATIC_CARIB_STEP_CARIB_READY);
    }

    Q_INVOKABLE void onCommandCaribration()
    {
        CHECK_FALSE_RETURN((mDspSeq != 0));

        pDspSP->sendWCCaribCmd(mDspSeq, EnumDef::WC_CALIB_TYPE_STATIC);

        setStep(QmlEnumDef::STATIC_CARIB_STEP_CARIB_ING);
    }

    void onAddedDspEvent(quint64 dspSeq, DspEventDto dto)
    {
        CHECK_FALSE_RETURN((mDspSeq == dspSeq));

        if(dto.mEvent.mEventType == EnumDef::ET_WEIGHT_STATIC_CARI)
        {
            setStep(QmlEnumDef::STATIC_CARIB_STEP_CARIB_COMPLETED);

            DevSettingDto devSetting = pLSettingSP->mDevSetting;
            devSetting.mDspForm.mWCSetting.mStaticFactor = dto.mEvent.mEventValue;
            pLSettingSP->setDevSetting(devSetting);

            emit signalEventCompleteCalibration();
            return;
        }
    }

    void onChangedDspStatus(quint64 dspSeq, DspStatusDto dto)
    {
        CHECK_FALSE_RETURN((mDspSeq == dspSeq));

        if(dto.mWCStatus.mCurrWeight == 0)
        {
            setCurrentWeight(0);
        }
        else
        {
            setCurrentWeight(dto.mWCStatus.mCurrWeight + pProductSP->mCurrPD.mDspForm.mWCSetting.mTareWeight);
        }
    }

};
#endif // PANELWCSTATICCARIBRATIONMODEL_H
