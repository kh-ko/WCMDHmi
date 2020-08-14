#ifndef PANELETCSETTINGMODEL_H
#define PANELETCSETTINGMODEL_H

#include <QObject>
#include "source/globaldef/EnumDefine.h"
#include "source/service/wcmdservice.h"
#include "source/helper/databasehelper.h"
#include "source/helper/localsetting.h"

class PanelEtcSettingModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint16 runMode          READ getRunMode               NOTIFY  signalEventChangedRunMode)
public:
    quint16 mRunMode;
    quint16 getRunMode(){return mRunMode;}
    void setRunMode(quint16 value){mRunMode = value; emit signalEventChangedRunMode(value);}
    explicit PanelEtcSettingModel(QObject *parent = nullptr):QObject(parent)
    {
        connect(this, SIGNAL(signalCommandSetRunMode(quint16, quint16)), WCMDService::getInstance(), SLOT(onCommandSetRunMode(quint16, quint16)));
        connect(this, SIGNAL(signalCommandResetStatistics()), WCMDService::getInstance(), SLOT(onCommandResetStatistics()));
        connect(WCMDService::getInstance(), SIGNAL(signalEventChangedRunMode(quint16)), this, SLOT(onSignalEventChangedRunMode(quint16)));

        quint16 runMode = (quint16)WCMDService::getInstance()->mRunMode;
        setRunMode(runMode);
    }

signals:
    void signalEventChangedRunMode(quint16 runMode);

    void signalCommandSetRunMode(quint16 deviceSeq, quint16 value);
    void signalCommandResetStatistics();

public slots:
    void onSignalEventChangedRunMode(quint16 value)
    {
        setRunMode(value);
    }

    Q_INVOKABLE void onCommandSetRunMode(int runMode)
    {
        emit signalCommandSetRunMode(0xffff, runMode);
    }

    Q_INVOKABLE void onCommandResetStatistics()
    {
        QDateTime now      = QDateTime::currentDateTime();
        quint64 lastEventSeq = DatabaseHelper::getInstance()->findLastEventSeq("EtcSetting");
        LocalSetting::getInstance()->setWorkStartSeq(now.date().year(), now.date().month(), now.date().day(), lastEventSeq);

        emit signalCommandResetStatistics();
    }


};

#endif // PANELETCSETTINGMODEL_H
