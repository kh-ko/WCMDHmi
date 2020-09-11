#ifndef PROCSETTINGMODEL_H
#define PROCSETTINGMODEL_H

#include <QObject>

class ProcSettingModel : public QObject
{
    Q_OBJECT

public:
    QString mLastDateTime;
    int mLastBackupYear  ;
    int mLastBackupMonth ;
    int mLastBackupDay   ;

    void setLastDateTime   (QString value){ if(mLastDateTime    == value) return; mLastDateTime    = value; emit signalEventChangedLastDateTime   (mLastDateTime   );}
    void setLastBackupYear (int     value){ if(mLastBackupYear  == value) return; mLastBackupYear  = value; emit signalEventChangedLastBackupYear (mLastBackupYear );}
    void setLastBackupMonth(int     value){ if(mLastBackupMonth == value) return; mLastBackupMonth = value; emit signalEventChangedLastBackupMonth(mLastBackupMonth);}
    void setLastBackupDay  (int     value){ if(mLastBackupDay   == value) return; mLastBackupDay   = value; emit signalEventChangedLastBackupDay  (mLastBackupDay  );}

signals:
    void signalEventChangedLastDateTime   (QString value);
    void signalEventChangedLastBackupYear (int     value);
    void signalEventChangedLastBackupMonth(int     value);
    void signalEventChangedLastBackupDay  (int     value);

public:
    explicit ProcSettingModel(QObject *parent = nullptr) : QObject(parent){}
};

#endif // PROCSETTINGMODEL_H
