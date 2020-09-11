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
    CoreService         * mpCoreService ;
    DspStatusModel      * mpDspStatus   ;

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
        mpCoreService->onCommandFactoryReset();
    }

    Q_INVOKABLE void onCommandLoggingReset()
    {
        setIsDeviceCompleted      (true );
        setIsLocalSettingCompleted(true );

        mpCoreService->onCommandHistoryReset();
    }

//  down layer ===================================================================================
public slots:
    void onSignalEventChangedFactoryResetState(int value)
    {
        if(value == EnumDefine::FactoryResetState::FACTORYRESET_DSP_FOR_ALL || value == EnumDefine::FactoryResetState::FACTORYRESET_DSP_FOR_HIS)
        {
            setIsDeviceCompleted      (true);
        }
        else if(value == EnumDefine::FactoryResetState::FACTORYRESET_LOCAL)
        {
            setIsDeviceCompleted      (true);
            setIsLocalSettingCompleted(true);
        }
        else if(value == EnumDefine::FactoryResetState::FACTORYRESET_HISTORY)
        {
            setIsDeviceCompleted      (true);
            setIsDBCompleted          (true);
            setIsLocalSettingCompleted(true);
            emit signalEventExit();
        }
    }

//  internal layer ===================================================================================
public:
    explicit FactoryResetViewModel(QObject *parent = nullptr): QObject(parent)
    {
        mpCoreService = CoreService::getInstance();

        connect(mpCoreService,  SIGNAL(signalEventChangedFactoryResetState(int)),this, SLOT(onSignalEventChangedFactoryResetState(int)));

        onSignalEventChangedFactoryResetState(mpCoreService->mFactoryResetState);
    }
};

#endif // FACTORYRESETVIEWMODEL_H
