#ifndef FACTORYRESETVIEWMODEL_H
#define FACTORYRESETVIEWMODEL_H

#include <QObject>
#include <QTimer>

#include "source/globaldef/GlobalDefine.h"
#include "source/service/wcmdservice.h"
#include "source/helper/localsetting.h"
#include "source/helper/databasehelper.h"
#include "source/logger/nsdebug.h"

class FactoryResetViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool  isDeviceCompleted        READ getIsDeviceCompleted        NOTIFY signalEventChangedIsDeviceCompleted      );
    Q_PROPERTY(bool  isDBCompleted            READ getIsDBCompleted            NOTIFY signalEventChangedIsDBCompleted          );
    Q_PROPERTY(bool  isLocalSettingCompleted  READ getIsLocalSettingCompleted  NOTIFY signalEventChangedIsLocalSettingCompleted);

public:
    static void procDatabaseFactoryReset()
    {
        DatabaseHelper::getInstance()->factoryReset("FACTORY_RESET_DB_CON");
        NSDebug::factoryReset();
    }

    static void procDatabaseLoggingReset()
    {
        DatabaseHelper::getInstance()->loggingReset("FACTORY_RESET_DB_CON");
        NSDebug::factoryReset();
    }

    bool mIsOnlyEvent             = false;
    QThread *mThread              = nullptr;
    bool mIsDeviceCompleted       = false;
    bool mIsDBCompleted           = false;
    bool mIsLocalSettingCompleted = false;

    bool getIsDeviceCompleted      (){return mIsDeviceCompleted      ;}
    bool getIsDBCompleted          (){return mIsDBCompleted          ;}
    bool getIsLocalSettingCompleted(){return mIsLocalSettingCompleted;}

    void setIsDeviceCompleted      (bool     value){ if(value == mIsDeviceCompleted      ) return; mIsDeviceCompleted       = value; emit signalEventChangedIsDeviceCompleted      (value);}
    void setIsDBCompleted          (bool     value){ if(value == mIsDBCompleted          ) return; mIsDBCompleted           = value; emit signalEventChangedIsDBCompleted          (value);}
    void setIsLocalSettingCompleted(bool     value){ if(value == mIsLocalSettingCompleted) return; mIsLocalSettingCompleted = value; emit signalEventChangedIsLocalSettingCompleted(value);}

    explicit FactoryResetViewModel(QObject *parent = nullptr)
    {
        WCMDService *pWCMDService = WCMDService::getInstance();

        connect(this, SIGNAL(signalCommandSendFactoryReset(quint16)), pWCMDService, SLOT(onCommandFactoryReset(quint16)));
        connect(pWCMDService, SIGNAL(signalEventCompletedFactoryReset(quint16)), this, SLOT(onSignalEventCompletedFactoryReset(quint16)));


        //onSignalEventCompletedFactoryReset(0);
    }

signals:
    void signalEventChangedIsDeviceCompleted      (bool     value);
    void signalEventChangedIsDBCompleted          (bool     value);
    void signalEventChangedIsLocalSettingCompleted(bool     value);

    void signalCommandSendFactoryReset(quint16 deviceSeq);
    void signalEventExit();

public slots:
    Q_INVOKABLE void onCommandLoggingReset()
    {
        mIsOnlyEvent = true;
        emit signalCommandSendFactoryReset(0xffff);
    }
    Q_INVOKABLE void onCommandFactoryReset()
    {
        mIsOnlyEvent = false;
        emit signalCommandSendFactoryReset(0xffff);
    }
    void onSignalEventCompletedFactoryReset(quint16 deviceSeq)
    {
        setIsDeviceCompleted(true);
        WCMDService *pWCMDService = WCMDService::getInstance();
        pWCMDService->stop();

        if(mIsOnlyEvent)
        {
            LocalSetting::getInstance()->loggingReset();
        }
        else
        {
            LocalSetting::getInstance()->factoryReset();
        }
        setIsLocalSettingCompleted(true);

        if(mThread != nullptr)
        {
            mThread->quit();
            mThread->wait();
            delete mThread;

            mThread = nullptr;
        }

        if(mIsOnlyEvent)
        {
            mThread = QThread::create(FactoryResetViewModel::procDatabaseLoggingReset);
        }
        else
        {
            mThread = QThread::create(FactoryResetViewModel::procDatabaseFactoryReset);
        }

        connect(mThread, SIGNAL(finished()), this, SLOT(onThreadFinish()));
        mThread->start();

    }

    void onThreadFinish()
    {
        setIsDBCompleted(true);
        QTimer::singleShot(1000, this, SLOT(exit()));
    }

    void exit()
    {
        emit signalEventExit();
    }


};

#endif // FACTORYRESETVIEWMODEL_H
