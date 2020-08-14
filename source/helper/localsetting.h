#ifndef LOCALSETTING_H
#define LOCALSETTING_H

#include <QObject>
#include <QMutex>
#include <QSettings>

#include "source/model/Information.h"
#include "source/model/devicesetting.h"
#include "source/model/wccaribrationinfo.h"

class LocalSetting : public QObject
{
    Q_OBJECT
private:
    static LocalSetting * mpSelf;

    QMutex mMutex;
    QSettings *mpSettings;
public:
    static LocalSetting *   getInstance ();

    explicit LocalSetting(QObject *parent = nullptr);
    ~LocalSetting();

    void            loggingReset();
    void            factoryReset();

    void            setInformation(Information value);
    void            setDeviceSetting(DeviceSetting value);
    void            setLastDateTime();
    void            setBackupYear  (int     value);
    void            setBackupMonth (int     value);
    void            setBackupDay   (int     value);
    void            setBackupSeq   (quint64 value);
    void            setLastEventSeq(quint64 value);

    void            setWorkStartSeq(int year, int month, int day, quint64 workStartSeq);
    void            setMainViewIsDetail(bool value);
    void            setWCViewMode(int value);
    Information     getInformation();
    DeviceSetting   getDeviceSetting();
    QDateTime       getLastDateTime();
    int             getBackupYear();
    int             getBackupMonth();
    int             getBackupDay();
    quint64         getBackupSeq   ();
    quint64         getLastEventSeq();
    quint64         getWorkStartSeq(int year, int month, int day);
    bool            getMainViewIsDetail();
    int             getWCViewMode();
};

#endif // LOCALSETTING_H
