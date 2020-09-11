#ifndef PANELETCSETTINGMODEL_H
#define PANELETCSETTINGMODEL_H

#include <QObject>
#include "source/globaldef/EnumDefine.h"

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

    }


};

#endif // PANELETCSETTINGMODEL_H
