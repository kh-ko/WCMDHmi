#ifndef SEARCHSSIDDLGMODEL_H
#define SEARCHSSIDDLGMODEL_H

#include <QObject>
#include <QDebug>

#include "source/globaldef/qmlenumdef.h"
#include "source/service/coreservice.h"

class SearchSSIDDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    isScanning           READ getIsScanning           NOTIFY  signalEventChangedIsScanning          )
    Q_PROPERTY(bool    isConnectingInternet READ getIsConnectingInternet NOTIFY  signalEventChangedIsConnectingInternet)

public:
    bool    mIsScanning           = true;
    bool    mIsConnectingInternet = false;

    bool    getIsScanning          (){ return mIsScanning          ;}
    bool    getIsConnectingInternet(){ return mIsConnectingInternet;}

    void setIsScanning          (bool    value){ if(mIsScanning           == value) return; mIsScanning           = value; emit signalEventChangedIsScanning          (value);}
    void setIsConnectingInternet(bool    value)
    {
        if(mIsConnectingInternet == value) return;

        mIsConnectingInternet = value;

        qDebug() << "[SearchSSIDDlgModel][setIsConnectingInternet]" << value;

        emit signalEventChangedIsConnectingInternet(value);
    }

private:
    ApPointDto mSelectAP;

signals:
    void signalEventFoundAP(QString SSID, QString authType);
    void signalEventConnectedAP();
    void signalEventChangedIsScanning          (bool value);
    void signalEventChangedIsConnectingInternet(bool value);


public slots:
    Q_INVOKABLE void onCommandScanAP()
    {
        setIsScanning(true);
        setIsConnectingInternet(false);
        scanAPList();
    }

    Q_INVOKABLE void onCommandSelectAP(QString ssid, QString auth)
    {
        mSelectAP.mSSID = ssid;
        mSelectAP.mAUTH = auth;
    }

    Q_INVOKABLE void onCommandSetPSK(QString psk)
    {
        mSelectAP.mPSK = QString("\"%1\"").arg(psk);

        onCommandApply();
    }


    Q_INVOKABLE void onCommandApply()
    {
        qDebug() << "[SearchSSIDDlgModel][onCommandApply] ssid = " << mSelectAP.mSSID << ", psk = " << mSelectAP.mPSK << ", auth = " << mSelectAP.mAUTH;

        if(mSelectAP.mSSID == "")
            return;

        setIsConnectingInternet(true);

        pVncSP->selectAP(mSelectAP);

    }

    void onVncFoundAP(ApPointDto ap)
    {
        setIsScanning(false);

        emit signalEventFoundAP(ap.mSSID, ap.mAUTH);
    }

    void onVncChangedIsConnInternet(bool value)
    {
        if(value == true && mIsConnectingInternet)
        {
            qDebug() << "[SearchSSIDDlgModel][onVncChangedIsConnInternet]: signalEventConnectedAP" ;
            setIsConnectingInternet(false);
            emit signalEventConnectedAP();
        }
    }
public:
    explicit SearchSSIDDlgModel(QObject *parent = nullptr):QObject(parent)
    {
        ENABLE_SLOT_VNC_FOUND_AP;
        ENABLE_SLOT_VNC_CHANGED_IS_CONN_INTERNET;
    }

    void scanAPList()
    {
        pVncSP->scanAP();
    }
};

#endif // SEARCHSSIDDLGMODEL_H
