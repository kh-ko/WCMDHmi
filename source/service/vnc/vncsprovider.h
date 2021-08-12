#ifndef VNCSPROVIDER_H
#define VNCSPROVIDER_H
#include <QObject>
#include <QDebug>
#include <QThread>
#include <QProcess>
#include <QTimer>

#include "source/service/dto/appointdto.h"
#include "source/service/localsetting/localsettingsprovider.h"

#define pVncSP VncSProvicer::getInstance()

#define ENABLE_SLOT_VNC_START                    connect(VncSProvicer::getInstance(), SIGNAL(signalEventStarted()                     ), this, SLOT(onVncStartedService(   )        ))
#define ENABLE_SLOT_VNC_STOP                     connect(VncSProvicer::getInstance(), SIGNAL(signalEventStopped()                     ), this, SLOT(onVncStoppedService(   )        ))
#define ENABLE_SLOT_VNC_FOUND_AP                 connect(VncSProvicer::getInstance(), SIGNAL(signalEventFoundAP(ApPointDto)           ), this, SLOT(onVncFoundAP(ApPointDto)        ))
#define ENABLE_SLOT_VNC_CHANGED_IS_CONN_INTERNET connect(VncSProvicer::getInstance(), SIGNAL(signalEventChangedIsConnectInternet(bool)), this, SLOT(onVncChangedIsConnInternet(bool)))
#define ENABLE_SLOT_VNC_CHANGED_IS_CONN_VIEW     connect(VncSProvicer::getInstance(), SIGNAL(signalEventChangedIsConnectView(bool)    ), this, SLOT(onVncChangedIsConnView(bool)    ))

class VncASyncWorker : public QObject
{
    Q_OBJECT


public:
    QProcess * mpProcess = nullptr;
    QTimer * mpTimer = nullptr;
    bool mIsConnectInternet = false;
    bool mIsConnectVNCView  = false;

    explicit VncASyncWorker(QObject *parent = nullptr):QObject(parent)
    {
        qDebug() << "[VncASyncWorker]Create";
    }
    ~VncASyncWorker()
    {
        qDebug() << "[VncASyncWorker]Destruction";

        closeProcess();

        mpTimer->stop();
        delete mpTimer;
    }
    void setIsConnectInternet(bool value)
    {
        if(value == mIsConnectInternet)
            return;

        if(value == false)
            closeProcess();

        mIsConnectInternet = value;

        qDebug() << "[VncASyncWorker][setIsConnectInternet]" << value;

        emit signalEventChangedIsConnectInternet(value);
    }
    void setIsConnectVNCView(bool value)
    {
        if(value == mIsConnectVNCView)
            return;

        mIsConnectVNCView = value;

        qDebug() << "[VncASyncWorker][setIsConnectVNCView]" << value;

        emit signalEventChangedIsConnectView(value);
    }

signals:
    void signalEventFoundAP(ApPointDto ap);
    void signalEventChangedIsConnectInternet(bool isConnect);
    void signalEventChangedIsConnectView(bool isConnect);

public slots:
    void onStart()
    {
        qDebug() << "[VncASyncWorker][onStart]";

        mpTimer = new QTimer(this);
        mpTimer->setInterval(10000);
        connect(mpTimer, SIGNAL(timeout()), this, SLOT(onTimeTick()));

        mpTimer->start();
    }

    void onTimeTick()
    {
        QProcess proc;

        QString cmd = QString("ping %1 -w 1").arg(pLSettingSP->mVNCViewIP);

        proc.start(cmd);

        proc.waitForFinished(-1);

        QString output = proc.readAllStandardOutput();

        if(output.contains("1 received"))
        {
            qDebug() << "[VncASyncWorker][onTimeTick] Connected";
            setIsConnectInternet(true);
        }
        else
        {
            qDebug() << "[VncASyncWorker][onTimeTick] disconnect";
            setIsConnectInternet(false);
        }
    }

    void onCommandScanAP()
    {
        QProcess proc;
        QList<ApPointDto> apList;

        qDebug() << "[VncASyncWorker][onCommandScan]";

        QString cmd = "sudo iwlist wlan0 scan";

        proc.start(cmd);
        proc.waitForFinished(-1);

        QString output = proc.readAllStandardOutput();

        QStringList outputLine = output.split("\n");
        QString root;

        for(int i = 0; i < outputLine.size(); i ++)
        {
            QString line = outputLine.at(i);
            line = line.trimmed();

            if(line.startsWith("ESSID:"))
            {
                ApPointDto ap;
                ap.mSSID = line.split(":")[1];

                for(int findIdx = i+1; findIdx < outputLine.size(); findIdx++)
                {
                    line = outputLine.at(findIdx);
                    line = line.trimmed();

                    if(line.startsWith("Cell"))
                    {
                        break;
                    }
                    else if(line.startsWith("Authentication"))
                    {
                        QString auth = line.split(":")[1];

                        ap.mAUTH = auth.trimmed();
                    }
                    i = findIdx;
                }

                emit signalEventFoundAP(ap);
            }
        }
    }

    void onCommandSelectAP(ApPointDto cfg)
    {
        QProcess proc;

        qDebug() << "[VncASyncWorker][onCommandSelect]";

        QString cmd = "sudo chmod 666 /etc/wpa_supplicant/wpa_supplicant.conf";

        proc.start(cmd);

        proc.waitForFinished(-1);

        QFile file;
        file.setFileName("/etc/wpa_supplicant/wpa_supplicant.conf");
        file.open(QFile::ReadWrite);

        if(file.isOpen() == false)
        {
            qDebug() << "[VncASyncWorker][onCommandSelect]write failed";
            return;
        }

        QTextStream outStream;
        outStream.setDevice(&file);

        QString content = outStream.readAll();

        outStream.setDevice(nullptr);

        content = content.split("network=")[0];

        QString newContent;

        if(cfg.mAUTH != "")
        {
            newContent = QString("%1network={\nssid=%2\npsk=%3\n}").arg(content).arg(cfg.mSSID).arg(cfg.mPSK);
        }
        else
        {
            newContent = QString("%1network={\nssid=%2\nkey_mgmt=NONE\n}").arg(content).arg(cfg.mSSID);
        }
        file.resize(0);
        file.write(newContent.toUtf8());
        file.flush();
        file.close();

        QProcess reconnectProc;
        QString reconnectCmd = "wpa_cli -i wlan0 reconfigure";

        setIsConnectInternet(false);

        reconnectProc.start(reconnectCmd);

        reconnectProc.waitForFinished(-1);

        QString cmdResult = reconnectProc.readAllStandardOutput();

        qDebug() << "[VncASyncWorker][onCommandSelect]reconnect result : " << cmdResult;
    }

    void onCommandRun(QString cmd)
    {
        qDebug() << "[VncASyncWorker][onCommandRun]" << cmd;

        if(mIsConnectVNCView)
            return;

        if(mIsConnectInternet == false)
            return;

        closeProcess();

        mpProcess = new QProcess;

        connect(mpProcess, SIGNAL(finished(int)),this, SLOT(onFinished(int)));
        connect(mpProcess, SIGNAL(error(QProcess::ProcessError)),this, SLOT(onError(QProcess::ProcessError)));

        setIsConnectVNCView(true);

        mpProcess->start(cmd);
    }

    void onCommandStop()
    {
        qDebug() << "[VncASyncWorker][onCommandStop]";
        closeProcess();
    }

    void onFinished(int exitCode)
    {
        qDebug() << "[VncASyncWorker][onFinished]" << exitCode;
        closeProcess();
    }

    void onError(QProcess::ProcessError error)
    {
        qDebug() << "[VncASyncWorker][onError]" << error;
        closeProcess();
    }

private:
    void closeProcess()
    {
        QString readData;

        qDebug() << "[VncASyncWorker][closeProcess]";

        if(mpProcess != nullptr)
        {
            disconnect(mpProcess, SIGNAL(finished(int)),this, SLOT(onFinished(int)));
            disconnect(mpProcess, SIGNAL(error(QProcess::ProcessError)),this, SLOT(onError(QProcess::ProcessError)));

            mpProcess->close();
            mpProcess = nullptr;
        }

        setIsConnectVNCView(false);
    }
};

class VncSProvicer : public QObject
{
    Q_OBJECT

public :
    static VncSProvicer * getInstance()
    {
        static VncSProvicer *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new VncSProvicer();
        }

        return mpSelf;
    }

    explicit VncSProvicer(QObject *parent = nullptr):QObject(parent)
    {
        qDebug() << "[VncSProvicer]Create";
    }
    ~VncSProvicer()
    {
        qDebug() << "[VncSProvicer]Destruction";
        stop();
    }

    void start()
    {
        qDebug() << "[VncSProvicer][start]";
        mpASyncWorkerThread = new QThread;
        mpASyncWorker       = new VncASyncWorker;
        mpASyncWorker->moveToThread(mpASyncWorkerThread);
        mpASyncWorkerThread->start();
        connect(mpASyncWorkerThread, &QThread::finished, mpASyncWorker, &QObject::deleteLater);
        connect(mpASyncWorkerThread, &QThread::started , mpASyncWorker, &VncASyncWorker::onStart);

        connect(this         , SIGNAL(signalCommandRun(QString)        ), mpASyncWorker, SLOT(onCommandRun(QString)          ));
        connect(this         , SIGNAL(signalCommandStop()              ), mpASyncWorker, SLOT(onCommandStop()                ));
        connect(this         , SIGNAL(signalCommandScanAP()            ), mpASyncWorker, SLOT(onCommandScanAP()              ));
        connect(this         , SIGNAL(signalCommandSelectAP(ApPointDto)), mpASyncWorker, SLOT(onCommandSelectAP(ApPointDto)  ));
        connect(mpASyncWorker, SIGNAL(signalEventFoundAP(ApPointDto)           ), this, SLOT(onFoundAP(ApPointDto)           ));
        connect(mpASyncWorker, SIGNAL(signalEventChangedIsConnectInternet(bool)), this, SLOT(onChangedIsConnectInternet(bool)));
        connect(mpASyncWorker, SIGNAL(signalEventChangedIsConnectView(bool)    ), this, SLOT(onChangedIsConnectView(bool)    ));

        mIsRunning = true;

        emit signalEventStarted();
    }

    void stop()
    {
        qDebug() << "[VncSProvicer][stop]";

        mIsRunning = false;

        if(mpASyncWorker != nullptr)
        {
            disconnect(this         , SIGNAL(signalCommandRun(QString)        ), mpASyncWorker, SLOT(onCommandRun(QString)          ));
            disconnect(this         , SIGNAL(signalCommandStop()              ), mpASyncWorker, SLOT(onCommandStop()                ));
            disconnect(this         , SIGNAL(signalCommandScanAP()            ), mpASyncWorker, SLOT(onCommandScanAP()              ));
            disconnect(this         , SIGNAL(signalCommandSelectAP(ApPointDto)), mpASyncWorker, SLOT(onCommandSelectAP(ApPointDto)  ));
            disconnect(mpASyncWorker, SIGNAL(signalEventFoundAP(ApPointDto)           ), this, SLOT(onFoundAP(ApPointDto)           ));
            disconnect(mpASyncWorker, SIGNAL(signalEventChangedIsConnectInternet(bool)), this, SLOT(onChangedIsConnectInternet(bool)));
            disconnect(mpASyncWorker, SIGNAL(signalEventChangedIsConnectView(bool)    ), this, SLOT(onChangedIsConnectView(bool)    ));

            mpASyncWorker= nullptr;
         }

        if(mpASyncWorkerThread != nullptr)
        {
            if(mpASyncWorkerThread->isRunning())
            {
                mpASyncWorkerThread->quit();
                mpASyncWorkerThread->wait();
            }

            mpASyncWorkerThread->deleteLater();

            mpASyncWorkerThread = nullptr;
        }

        emit signalEventStopped();
    }

    void runCmd(QString cmd)
    {
        if(mIsRunning == false)
            return;

        qDebug() << "[VncSProvicer][connectPort]";
        emit signalCommandRun(cmd);
    }

    void stopCmd()
    {
        if(mIsRunning == false)
            return;
        qDebug() << "[VncSProvicer][stopCmd]";
        emit signalCommandStop();
    }

    void scanAP()
    {
        if(mIsRunning == false)
            return;
        qDebug() << "[VncSProvicer][scanAP]";
        emit signalCommandScanAP();
    }

    void selectAP(ApPointDto dto)
    {
        if(mIsRunning == false)
            return;
        qDebug() << "[VncSProvicer][selectAP]";

        emit signalCommandSelectAP(dto);
    }

    bool isConnInternet()
    {
        qDebug() << "[VncSProvicer][isConnInternet]";

        if(mIsRunning == false)
            return false;

        return mpASyncWorker->mIsConnectInternet;
    }

    bool isRun()
    {
        qDebug() << "[VncSProvicer][isRun]";

        if(mIsRunning == false)
            return false;

        return mpASyncWorker->mIsConnectVNCView;
    }

signals:
    void signalEventStarted();
    void signalEventStopped();
    void signalEventFoundAP(ApPointDto value);
    void signalEventChangedIsConnectInternet(bool value);
    void signalEventChangedIsConnectView(bool value);

    void signalCommandRun(QString value);
    void signalCommandStop();
    void signalCommandScanAP();
    void signalCommandSelectAP(ApPointDto value);

public slots:
    void onFoundAP(ApPointDto ap)
    {
        qDebug() << "[VncSProvicer][onFoundAP]";
        emit signalEventFoundAP(ap);
    }

    void onChangedIsConnectInternet(bool isConn)
    {
        emit signalEventChangedIsConnectInternet(isConn);
    }

    void onChangedIsConnectView(bool isConn)
    {
        emit signalEventChangedIsConnectView(isConn);
    }

private :
    bool    mIsRunning = false;
    QThread         * mpASyncWorkerThread = nullptr;
    VncASyncWorker  * mpASyncWorker       = nullptr;
};
#endif // VNCSPROVIDER_H
