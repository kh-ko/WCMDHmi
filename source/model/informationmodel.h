#ifndef INFORMATIONMODEL_H
#define INFORMATIONMODEL_H

#include <QObject>

class InformationModel : public QObject
{
    Q_OBJECT

public:
    QString mCompany     = "";
    QString mTel         = "";
    QString mModel       = "";
    QString mSN          = "";
    int     mDeviceNumber= 0 ;
    QString mHMIVersion  = "";
    QString mPower       = "";
    QString mHomepage    = "";
    quint32 mMaxWeight   = 0 ;
    int     mHMIMajorVer = 0 ;
    int     mHMIMinorVer = 0 ;
    int     mHMIPatchVer = 0 ;

    void setCompany     (QString value){ if(value == mCompany     ) return; mCompany      = value; emit signalEventChangedCompany     (value);}
    void setTel         (QString value){ if(value == mTel         ) return; mTel          = value; emit signalEventChangedTel         (value);}
    void setModel       (QString value){ if(value == mModel       ) return; mModel        = value; emit signalEventChangedModel       (value);}
    void setSN          (QString value){ if(value == mSN          ) return; mSN           = value; emit signalEventChangedSN          (value);}
    void setDeviceNumber(int     value){ if(value == mDeviceNumber) return; mDeviceNumber = value; emit signalEventChangedDeviceNumber(value);}
    void setHMIVersion  (QString value)
    {
        if(value == mHMIVersion  )
            return;

        mHMIVersion   = value;
        mHMIMajorVer  = 0;
        mHMIMinorVer  = 0;
        mHMIPatchVer  = 0;

        if(mHMIVersion.contains(".") == false)
            return;

        QStringList listVer = mHMIVersion.split(".");

        if(listVer.size() > 0){mHMIMajorVer = listVer[0].toInt();}
        if(listVer.size() > 1){mHMIMinorVer = listVer[1].toInt();}
        if(listVer.size() > 2){mHMIPatchVer = listVer[2].toInt();}

        emit signalEventChangedHMIVersion  (value);
    }
    void setPower       (QString value){ if(value == mPower       ) return; mPower        = value; emit signalEventChangedPower       (value);}
    void setHomepage    (QString value){ if(value == mHomepage    ) return; mHomepage     = value; emit signalEventChangedHomepage    (value);}
    void setMaxWeight   (quint32 value){ if(value == mMaxWeight   ) return; mMaxWeight    = value; emit signalEventChangedMaxWeight   (value);}

signals:
    void signalEventChangedCompany     (QString  value);
    void signalEventChangedTel         (QString  value);
    void signalEventChangedModel       (QString  value);
    void signalEventChangedSN          (QString  value);
    void signalEventChangedDeviceNumber(int      value);
    void signalEventChangedHMIVersion  (QString  value);
    void signalEventChangedPower       (QString  value);
    void signalEventChangedHomepage    (QString  value);
    void signalEventChangedMaxWeight   (quint32  value);

public:
    explicit InformationModel(QObject *parent = nullptr) : QObject(parent){}
};

#endif // INFORMATIONMODEL_H
