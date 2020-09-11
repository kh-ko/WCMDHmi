#ifndef SECURITYSETTINGMODEL_H
#define SECURITYSETTINGMODEL_H
#include <QObject>

class SecuritySettingModel : public QObject
{
    Q_OBJECT

public:
    QString mPassword       = "1111";
    QString mAdminPassword  = "0701";

    void setPassword     (QString value){ if(value == mPassword     ) return; mPassword      = value; emit signalEventChangedPassword     (mPassword     );}
    void setAdminPassword(QString value){ if(value == mAdminPassword) return; mAdminPassword = value; emit signalEventChangedAdminPassword(mAdminPassword);}

signals:
    void signalEventChangedPassword     (QString value);
    void signalEventChangedAdminPassword(QString value);

public:
    explicit SecuritySettingModel(QObject *parent = nullptr) : QObject(parent){}
};
#endif // SECURITYSETTINGMODEL_H
