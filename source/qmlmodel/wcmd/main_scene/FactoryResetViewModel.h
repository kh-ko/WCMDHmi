#ifndef FACTORYRESETVIEWMODEL_H
#define FACTORYRESETVIEWMODEL_H

#include <QObject>
#include <QTimer>

#include "source/service/coreservice.h"

class FactoryResetViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool  isDeviceCompleted        READ getIsDeviceCompleted        NOTIFY signalEventChangedIsDeviceCompleted      );
    Q_PROPERTY(bool  isDBCompleted            READ getIsDBCompleted            NOTIFY signalEventChangedIsDBCompleted          );
    Q_PROPERTY(bool  isLocalSettingCompleted  READ getIsLocalSettingCompleted  NOTIFY signalEventChangedIsLocalSettingCompleted);

public:

    bool mIsDeviceCompleted       = false;
    bool mIsDBCompleted           = false;
    bool mIsLocalSettingCompleted = false;

    bool getIsDeviceCompleted      (){return mIsDeviceCompleted      ;}
    bool getIsDBCompleted          (){return mIsDBCompleted          ;}
    bool getIsLocalSettingCompleted(){return mIsLocalSettingCompleted;}

    void setIsDeviceCompleted      (bool     value){ if(value == mIsDeviceCompleted      ) return; mIsDeviceCompleted       = value; emit signalEventChangedIsDeviceCompleted      (value);}
    void setIsDBCompleted          (bool     value){ if(value == mIsDBCompleted          ) return; mIsDBCompleted           = value; emit signalEventChangedIsDBCompleted          (value);}
    void setIsLocalSettingCompleted(bool     value){ if(value == mIsLocalSettingCompleted) return; mIsLocalSettingCompleted = value; emit signalEventChangedIsLocalSettingCompleted(value);}

signals:
    void signalEventChangedIsDeviceCompleted      (bool     value);
    void signalEventChangedIsDBCompleted          (bool     value);
    void signalEventChangedIsLocalSettingCompleted(bool     value);

    void signalEventExit                          (              );

public slots:
    Q_INVOKABLE void onCommandFactoryReset()
    {
        pEventHisSP->factoryReset();
        pLSettingSP->factoryReset();
        pProductSP->factoryReset();
        pWorkSP->factoryReset();
        pDspSP->factoryReset();
    }

    Q_INVOKABLE void onCommandLoggingReset()
    {
        pEventHisSP->factoryReset();
        pWorkSP->factoryReset();
        emit signalEventExit();
    }

//  down layer ===================================================================================
public slots:
    void onCompletedDspFR(bool isSucc)
    {
        qDebug() << "[FactoryResetViewModel::onCompletedDspFR]" << isSucc;
        emit signalEventExit();
    }

//  internal layer ===================================================================================
public:
    explicit FactoryResetViewModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_DSP_COMPLETED_FR;
    }
};

#endif // FACTORYRESETVIEWMODEL_H
