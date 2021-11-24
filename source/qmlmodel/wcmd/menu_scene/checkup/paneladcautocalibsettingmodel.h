#ifndef PANELADCAUTOCALIBSETTINGMODEL_H
#define PANELADCAUTOCALIBSETTINGMODEL_H

#include <QObject>
#include <QTimer>
#include "source/globaldef/qmlenumdef.h"
#include "source/service/coreservice.h"

class PanelADCAutoCalibSettingModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    mIsUse            READ getIsUse           NOTIFY signalEventChangedIsUse        )
    Q_PROPERTY(qint32  mMinCheckValue    READ getMinCheckValue   NOTIFY signalEventChangedMinCheckValue)
    Q_PROPERTY(qint32  mMaxCheckValue    READ getMaxCheckValue   NOTIFY signalEventChangedMaxCheckValue)

public:
    bool    mIsUse         = 0;
    qint32  mMinCheckValue = 0;
    qint32  mMaxCheckValue = 0;

    bool    getIsUse        (){ return mIsUse        ;}
    qint32  getMinCheckValue(){ return mMinCheckValue;}
    qint32  getMaxCheckValue(){ return mMaxCheckValue;}

    void    setIsUse        (bool   value) { if(value == mIsUse        ) return; mIsUse         = value; emit signalEventChangedIsUse        (value);}
    void    setMinCheckValue(qint32 value) { if(value == mMinCheckValue) return; mMinCheckValue = value; emit signalEventChangedMinCheckValue(value);}
    void    setMaxCheckValue(qint32 value) { if(value == mMaxCheckValue) return; mMaxCheckValue = value; emit signalEventChangedMaxCheckValue(value);}

    explicit PanelADCAutoCalibSettingModel(QObject *parent = nullptr) : QObject(parent)
    {
        setIsUse        (pLSettingSP->mADCAutoCalibSetting.mIsUse);
        setMinCheckValue(pLSettingSP->mADCAutoCalibSetting.mMinADC);
        setMaxCheckValue(pLSettingSP->mADCAutoCalibSetting.mMaxADC);
    }

signals:
    void    signalEventChangedIsUse        (bool   value);
    void    signalEventChangedMinCheckValue(qint32 value);
    void    signalEventChangedMaxCheckValue(qint32 value);

    void    signalCommandWeightCarib(quint16 deviceSeq, quint16 type);
    void    signalEventCompleteCalibration();

public slots:
    Q_INVOKABLE void onCommandSetIsUse(bool value)
    {
        setIsUse(value);
    }

    Q_INVOKABLE void onCommandSetMinCheckValue(qint32 value)
    {
        setMinCheckValue(value);
    }

    Q_INVOKABLE void onCommandSetMaxCheckValue(qint32 value)
    {
        setMaxCheckValue(value);
    }

    Q_INVOKABLE void onCommandApply()
    {
        ADCAutoCalibSettingDto dto;
        dto.mIsUse = getIsUse();
        dto.mMinADC = getMinCheckValue();
        dto.mMaxADC = getMaxCheckValue();

        pLSettingSP->setADCAutoCalibSetting(dto);
    }

};
#endif // PANELADCAUTOCALIBSETTINGMODEL_H
