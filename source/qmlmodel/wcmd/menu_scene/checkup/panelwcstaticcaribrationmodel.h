#ifndef PANELWCSTATICCARIBRATIONMODEL_H
#define PANELWCSTATICCARIBRATIONMODEL_H

#include <QObject>
#include <QTimer>
#include "source/globaldef/qmlenumdef.h"
#include "source/service/coreservice.h"

class PanelWCStaticCaribrationModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    isBusy            READ getIsBusy           NOTIFY signalEventChangedIsBusy        )
    Q_PROPERTY(quint32 standardWeight    READ getStandardWeight   NOTIFY signalEventChangedStandardWeight)
    Q_PROPERTY(qint32  currentWeight     READ getCurrentWeight    NOTIFY signalEventChangedCurrentWeight )

public:
    quint64 mDspSeq        = 0;
    bool    mIsBusy        ;
    quint32 mStandardWeight;
    qint32  mCurrentWeight ;

    bool    getIsBusy        (){ return mIsBusy        ;}
    quint32 getStandardWeight(){ return mStandardWeight;}
    qint32  getCurrentWeight (){ return mCurrentWeight ;}

    void    setIsBusy        (bool    value) { if(value == mIsBusy)         return; mIsBusy         = value; emit signalEventChangedIsBusy        (value);}
    void    setStandardWeight(quint32 value) { if(value == mStandardWeight) return; mStandardWeight = value; emit signalEventChangedStandardWeight(value);}
    void    setCurrentWeight (qint32  value) { if(value == mCurrentWeight ) return; mCurrentWeight  = value; emit signalEventChangedCurrentWeight (value);}

    explicit PanelWCStaticCaribrationModel(QObject *parent = nullptr) : QObject(parent)
    {
        setStandardWeight(pLSettingSP->mDevSetting.mDspForm.mWCSetting.mStaticStandardWeight);
        setCurrentWeight(0);

        setIsBusy(false);

        CHECK_FALSE_RETURN((pDspSP->mDspList.size() > 0));

        mDspSeq = pDspSP->mDspList[0]->mSeq;

        ENABLE_SLOT_DSP_ADDED_EVENT;
        ENABLE_SLOT_DSP_CHANGED_DSP_STATUS;
    }

signals:
    void    signalEventChangedIsBusy        (bool    value);
    void    signalEventChangedStandardWeight(quint32 value);
    void    signalEventChangedCurrentWeight (qint32  value);

    void    signalCommandWeightCarib(quint16 deviceSeq, quint16 type);
    void    signalEventCompleteCalibration();

public slots:
    Q_INVOKABLE void onCommandZERO()
    {
        CHECK_FALSE_RETURN((mDspSeq != 0));

        pDspSP->sendZeroCmd(mDspSeq);
        //pDspSP->sendWCCaribCmd(mDspSeq, EnumDef::WC_CALIB_TYPE_DYNAMIC);
    }

    Q_INVOKABLE void onCommandCaribration()
    {
        setIsBusy(true);

        CHECK_FALSE_RETURN((mDspSeq != 0));

        pDspSP->sendWCCaribCmd(mDspSeq, EnumDef::WC_CALIB_TYPE_STATIC);
    }

    Q_INVOKABLE void onCommandSetStandardWeight(quint32 value)
    {
        DevSettingDto dto = pLSettingSP->mDevSetting;
        dto.mDspForm.mWCSetting.mStaticStandardWeight =value;

        pLSettingSP->setDevSetting(dto);
        setStandardWeight(value);
    }

    void onAddedDspEvent(quint64 dspSeq, DspEventDto dto)
    {
        CHECK_FALSE_RETURN((mDspSeq == dspSeq));

        if(dto.mEvent.mEventType == EnumDef::ET_WEIGHT_STATIC_CARI)
        {
            setIsBusy(false);

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
