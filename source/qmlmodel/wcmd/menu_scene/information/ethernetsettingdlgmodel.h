#ifndef ETHERNETSETTINGDLGMODEL_H
#define ETHERNETSETTINGDLGMODEL_H

#include <QObject>
#include <QDebug>

#include "source/globaldef/qmlenumdef.h"
#include "source/service/coreservice.h"

class EthernetSettingItemModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mDevType          READ getDevType          WRITE setDevType          NOTIFY  signalEventChangedDevType         )
    Q_PROPERTY(QString mIP               READ getIP               WRITE setIP               NOTIFY  signalEventChangedIP              )
    Q_PROPERTY(QString mSubnetMask       READ getSubnetMask       WRITE setSubnetMask       NOTIFY  signalEventChangedSubnetMask      )
    Q_PROPERTY(QString mRoute            READ getRoute            WRITE setRoute            NOTIFY  signalEventChangedRoute           )
    Q_PROPERTY(QString mMetric           READ getMetric           WRITE setMetric           NOTIFY  signalEventChangedMetric          )
    Q_PROPERTY(QString mTargetIPs        READ getTargetIPs        WRITE setTargetIPs        NOTIFY  signalEventChangedTargetIPs       )
    Q_PROPERTY(bool    mIsEditIP         READ getIsEditIP                                   NOTIFY  signalEventChangedIsEditIP        )
    Q_PROPERTY(bool    mIsEditSubnetMask READ getIsEditSubnetMask                           NOTIFY  signalEventChangedIsEditSubnetMask)
    Q_PROPERTY(bool    mIsEditRoute      READ getIsEditRoute                                NOTIFY  signalEventChangedIsEditRoute     )
    Q_PROPERTY(bool    mIsEditMetric     READ getIsEditMetric                               NOTIFY  signalEventChangedIsEditMetric    )
    Q_PROPERTY(bool    mIsEditTargetIPs  READ getIsEditTargetIPs                            NOTIFY  signalEventChangedIsEditTargetIPs )

public:
    QString mDevType         ;
    QString mIP              ;
    QString mSubnetMask      ;
    QString mRoute           ;
    QString mMetric          ;
    QString mTargetIPs       ;
    bool    mIsEditIP        ;
    bool    mIsEditSubnetMask;
    bool    mIsEditRoute     ;
    bool    mIsEditMetric    ;
    bool    mIsEditTargetIPs ;

    QString getDevType         (){ return mDevType         ;}
    QString getIP              (){ return mIP              ;}
    QString getSubnetMask      (){ return mSubnetMask      ;}
    QString getRoute           (){ return mRoute           ;}
    QString getMetric          (){ return mMetric          ;}
    QString getTargetIPs       (){ return mTargetIPs       ;}
    bool    getIsEditIP        (){ return mIsEditIP        ;}
    bool    getIsEditSubnetMask(){ return mIsEditSubnetMask;}
    bool    getIsEditRoute     (){ return mIsEditRoute     ;}
    bool    getIsEditMetric    (){ return mIsEditMetric    ;}
    bool    getIsEditTargetIPs (){ return mIsEditTargetIPs ;}

    void    setDevType         (QString value){ if(mDevType          == value) return; mDevType          = value; emit signalEventChangedDevType         (value);}
    void    setIP              (QString value){ if(mIP               == value) return; mIP               = value; setIsEditIP        (true); emit signalEventChangedIP              (value);}
    void    setSubnetMask      (QString value){ if(mSubnetMask       == value) return; mSubnetMask       = value; setIsEditSubnetMask(true); emit signalEventChangedSubnetMask      (value);}
    void    setRoute           (QString value){ if(mRoute            == value) return; mRoute            = value; setIsEditRoute     (true); emit signalEventChangedRoute           (value);}
    void    setMetric          (QString value){ if(mMetric           == value) return; mMetric           = value; setIsEditMetric    (true); emit signalEventChangedMetric          (value);}
    void    setTargetIPs       (QString value){ if(mTargetIPs        == value) return; mTargetIPs        = value; setIsEditTargetIPs (true); emit signalEventChangedTargetIPs       (value);}
    void    setIsEditIP        (bool    value){ if(mIsEditIP         == value) return; mIsEditIP         = value; emit signalEventChangedIsEditIP        (value);}
    void    setIsEditSubnetMask(bool    value){ if(mIsEditSubnetMask == value) return; mIsEditSubnetMask = value; emit signalEventChangedIsEditSubnetMask(value);}
    void    setIsEditRoute     (bool    value){ if(mIsEditRoute      == value) return; mIsEditRoute      = value; emit signalEventChangedIsEditRoute     (value);}
    void    setIsEditMetric    (bool    value){ if(mIsEditMetric     == value) return; mIsEditMetric     = value; emit signalEventChangedIsEditMetric    (value);}
    void    setIsEditTargetIPs (bool    value){ if(mIsEditTargetIPs  == value) return; mIsEditTargetIPs  = value; emit signalEventChangedIsEditTargetIPs (value);}

signals:
    void    signalEventChangedDevType         (QString value);
    void    signalEventChangedIP              (QString value);
    void    signalEventChangedSubnetMask      (QString value);
    void    signalEventChangedRoute           (QString value);
    void    signalEventChangedMetric          (QString value);
    void    signalEventChangedTargetIPs       (QString value);
    void    signalEventChangedIsEditIP        (bool    value);
    void    signalEventChangedIsEditSubnetMask(bool    value);
    void    signalEventChangedIsEditRoute     (bool    value);
    void    signalEventChangedIsEditMetric    (bool    value);
    void    signalEventChangedIsEditTargetType(bool    value);
    void    signalEventChangedIsEditTargetIPs (bool    value);

public:
    explicit EthernetSettingItemModel(QObject *parent = nullptr):QObject(parent)
    {
    }

    void resetIsEdit()
    {
        setIsEditIP        (false);
        setIsEditSubnetMask(false);
        setIsEditRoute     (false);
        setIsEditMetric    (false);
        setIsEditTargetIPs (false);
    }

    void reset()
    {
        setIP              ("");
        setSubnetMask      ("");
        setRoute           ("");
        setMetric          ("");
        setTargetIPs       ("");
        resetIsEdit        (  );
    }
};

class EthernetSettingDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    mIsEdit               READ getIsEdit           NOTIFY  signalEventChangedIsEdit    )

public:
    bool    mIsEdit = false;

    bool    getIsEdit (){ return mIsEdit;}

    void    setIsEdit(bool    value){ if(mIsEdit == value) return; mIsEdit = value; emit signalEventChangedIsEdit(value);}


signals:
    void signalEventChangedIsEdit(bool value);

private:
    QList<EthernetSettingItemModel *> mItemList;

public slots:
    Q_INVOKABLE void onCommandSetDspIPToTargetIPs(QString dev)
    {
        quint64 dspSeq= 0;
        DspMaster * pDsp = nullptr;

        if(pDspSP->mDspList.size() > 0)
        {
            dspSeq = pDspSP->mDspList[0]->mSeq;
        }

        if(dspSeq != 0)
        {
            pDsp = pDspSP->findDspMaster(dspSeq);
        }

        foreach(EthernetSettingItemModel * pItem , mItemList)
        {
            if(pItem->getDevType() == dev)
            {
                pItem->setTargetIPs(QString("%1;").arg(pDsp->mIp));
            }
        }
    }

    Q_INVOKABLE void onCommandDelTargetIPs(QString dev)
    {
        foreach(EthernetSettingItemModel * pItem , mItemList)
        {
            if(pItem->getDevType() == dev)
            {
                pItem->setTargetIPs("");
            }
        }
    }

    Q_INVOKABLE EthernetSettingItemModel * onCommandGetItem(int idx)
    {
        return mItemList[idx];
    }

    Q_INVOKABLE void onCommandLoad()
    {
        foreach(EthernetSettingItemModel * pItem , mItemList)
        {
            pItem->reset();
        }

        loadDhcpcdConf();
        loadRouteTable();

        resetIsEdit();
    }

    Q_INVOKABLE void onCommandApply()
    {
        qDebug() << "[" << Q_FUNC_INFO << "]";

        writeDhcpcdConf();
        writeRouteTable();

        resetIsEdit();
    }

public:
    explicit EthernetSettingDlgModel(QObject *parent = nullptr):QObject(parent)
    {
        EthernetSettingItemModel * pItem = new EthernetSettingItemModel(this);
        pItem->setDevType("Eth00");
        mItemList.append(pItem);

        pItem = new EthernetSettingItemModel(this);
        pItem->setDevType("Eth01");
        mItemList.append(pItem);

        pItem = new EthernetSettingItemModel(this);
        pItem->setDevType("Wlan00");
        mItemList.append(pItem);

        onCommandLoad();
    }

private:
    void resetIsEdit()
    {
        foreach(EthernetSettingItemModel * pItem , mItemList)
        {
            pItem->resetIsEdit();
        }
    }

    void loadDhcpcdConf()
    {
        EthernetSettingItemModel * pItem = nullptr;
        QString metric = "metric";
        QString ip     = "inform";
        QString router = "static routers=";

        qDebug() << "[" << Q_FUNC_INFO << "]";

        QProcess proc;

        QString cmd = "sudo chmod 666 /etc/dhcpcd.conf";

        proc.start(cmd);

        proc.waitForFinished(-1);

        QFile file;
        file.setFileName("/etc/dhcpcd.conf");
        file.open(QFile::ReadOnly);

        if(file.isOpen() == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]" << "open failed";
            return;
        }

        QTextStream outStream;
        outStream.setDevice(&file);

        while(!outStream.atEnd())
        {
            QString line;
            line = outStream.readLine().trimmed();

            if(line.startsWith("#"))
            {
                continue;
            }

            if(line.length() < 1)
            {
                pItem = nullptr;
                continue;
            }

            else if(line.startsWith("interface eth0"))
            {
                pItem = mItemList[0];
            }
            else if(line.startsWith("interface eth1"))
            {
                pItem = mItemList[1];
            }
            else if(line.startsWith("interface wlan0"))
            {
                pItem = mItemList[2];
            }

            if(pItem != nullptr)
            {
                if(line.startsWith(metric))
                {
                    pItem->setMetric(line.mid(metric.length()).trimmed());
                }
                else if(line.startsWith(ip))
                {
                    pItem->setIP(line.mid(ip.length()).trimmed());
                }
                else if(line.startsWith(router))
                {
                    pItem->setRoute(line.mid(router.length()).trimmed());
                }
            }

        }
        outStream.setDevice(nullptr);
        file.close();
    }

    void loadRouteTable()
    {
        QString dev = "";
        QString ip  = "";

        QString eth0List  = "";
        QString eth1List  = "";
        QString wlan0List = "";


        qDebug() << "[" << Q_FUNC_INFO << "]";

        QProcess proc;

        QString cmd = "sudo chmod 666 /lib/dhcpcd/dhcpcd-hooks/40-route";

        proc.start(cmd);

        proc.waitForFinished(-1);

        QFile file;
        file.setFileName("//lib/dhcpcd/dhcpcd-hooks/40-route");
        file.open(QFile::ReadOnly);

        if(file.isOpen() == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]" << "open failed";
            return;
        }

        QTextStream outStream;
        outStream.setDevice(&file);

        while(!outStream.atEnd())
        {
            QString line;
            QStringList lineCols;
            line = outStream.readLine().trimmed();

            lineCols  = line.split(" ");

            if(line.startsWith("#"))
            {
                continue;
            }
            else if(line.endsWith("eth0"))
            {
                eth0List.append(QString("%1;").arg(lineCols[3]));
            }
            else if(line.endsWith("eth1"))
            {
                eth1List.append(QString("%1;").arg(lineCols[3]));
            }
            else if(line.endsWith("wlan0"))
            {
                wlan0List.append(QString("%1;").arg(lineCols[3]));
            }

        }
        outStream.setDevice(nullptr);
        file.close();

        mItemList[0]->setTargetIPs(eth0List);
        mItemList[1]->setTargetIPs(eth1List);
        mItemList[2]->setTargetIPs(wlan0List);
    }

    void writeDhcpcdConf()
    {
        bool isOldRead = false;
        QStringList readeLine;

        QString metric = "metric";
        QString ip     = "inform";
        QString router = "static routers=";

        qDebug() << "[" << Q_FUNC_INFO << "]";

        QProcess proc;

        QString cmd = "sudo chmod 666 /etc/dhcpcd.conf";

        proc.start(cmd);

        proc.waitForFinished(-1);

        QFile file;
        file.setFileName("/etc/dhcpcd.conf");
        file.open(QFile::ReadWrite);

        if(file.isOpen() == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]" << "open failed";
            return;
        }

        QTextStream outStream;
        outStream.setDevice(&file);

        while(!outStream.atEnd())
        {
            QString line;
            line = outStream.readLine().trimmed();

            if(line.length() < 1)
            {
                isOldRead = false;
            }

            if(line.startsWith("interface eth0") || line.startsWith("interface eth1") || line.startsWith("interface wlan0"))
            {
                isOldRead = true;
            }

            if(isOldRead == false)
            {
                readeLine.append(line);
            }
        }
        outStream.setDevice(nullptr);
        file.resize(0);

        QString lastLine = "";
        foreach(QString line, readeLine)
        {
            line = line.trimmed();

            if(lastLine.length() == 0 && line.length() == 0)
                continue;

            file.write(QString("%1\n").arg(line).toUtf8());

            lastLine = line;
        }

        if((mItemList[2]->getMetric().length() > 0) || (mItemList[2]->getIP().length() > 0) || (mItemList[2]->getRoute().length() > 0))
        {
            if(lastLine.length() > 0)
            {
                file.write(QString("\n").toUtf8());
            }

            lastLine = " ";

            file.write(QString("\ninterface wlan0").toUtf8());
            if(mItemList[2]->getMetric().length() > 0)
                file.write(QString("\nmetric %1").arg(mItemList[2]->getMetric()).toUtf8());
            if(mItemList[2]->getIP().length() > 0)
                file.write(QString("\ninform %1").arg(mItemList[2]->getIP()).toUtf8());
            if(mItemList[2]->getRoute().length() > 0)
                file.write(QString("\nstatic routers=%1").arg(mItemList[2]->getRoute()).toUtf8());
        }

        if((mItemList[1]->getMetric().length() > 0) || (mItemList[1]->getIP().length() > 0) || (mItemList[1]->getRoute().length() > 0))
        {
            if(lastLine.length() > 0)
            {
                file.write(QString("\n").toUtf8());
            }

            lastLine = " ";

            file.write(QString("\ninterface eth1").toUtf8());
            if(mItemList[1]->getMetric().length() > 0)
                file.write(QString("\nmetric %1").arg(mItemList[1]->getMetric()).toUtf8());
            if(mItemList[1]->getIP().length() > 0)
                file.write(QString("\ninform %1").arg(mItemList[1]->getIP()).toUtf8());
            if(mItemList[1]->getRoute().length() > 0)
                file.write(QString("\nstatic routers=%1").arg(mItemList[1]->getRoute()).toUtf8());
        }

        if((mItemList[0]->getMetric().length() > 0) || (mItemList[0]->getIP().length() > 0) || (mItemList[0]->getRoute().length() > 0))
        {
            if(lastLine.length() > 0)
            {
                file.write(QString("\n").toUtf8());
            }

            lastLine = " ";

            file.write(QString("\ninterface eth0").toUtf8());
            if(mItemList[0]->getMetric().length() > 0)
                file.write(QString("\nmetric %1").arg(mItemList[0]->getMetric()).toUtf8());
            if(mItemList[0]->getIP().length() > 0)
                file.write(QString("\ninform %1").arg(mItemList[0]->getIP()).toUtf8());
            if(mItemList[0]->getRoute().length() > 0)
                file.write(QString("\nstatic routers=%1").arg(mItemList[0]->getRoute()).toUtf8());
        }

        file.close();
    }

    void writeRouteTable()
    {
        QStringList readeLine;

        QStringList eth0List = mItemList[0]->getTargetIPs().split(";");
        QStringList eth1List = mItemList[1]->getTargetIPs().split(";");
        QStringList wlanList = mItemList[2]->getTargetIPs().split(";");

        qDebug() << "[" << Q_FUNC_INFO << "]";

        QProcess proc;

        QString cmd = "sudo chmod 666 /lib/dhcpcd/dhcpcd-hooks/40-route";

        proc.start(cmd);

        proc.waitForFinished(-1);

        QFile file;
        file.setFileName("/lib/dhcpcd/dhcpcd-hooks/40-route");
        file.open(QFile::ReadWrite);

        if(file.isOpen() == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]" << "open failed";
            return;
        }

        file.resize(0);

        foreach(QString route, eth0List)
        {
            if(route.trimmed().length() > 0)
                file.write(QString("route add -host %1 dev eth0\n").arg(route).toUtf8());
        }

        foreach(QString route, eth1List)
        {
            if(route.trimmed().length() > 0)
                file.write(QString("route add -host %1 dev eth1\n").arg(route).toUtf8());
        }

        foreach(QString route, wlanList)
        {
            if(route.trimmed().length() > 0)
                file.write(QString("route add -host %1 dev wlan0\n").arg(route).toUtf8());
        }

        file.close();
    }
};



#endif // ETHERNETSETTINGDLGMODEL_H
