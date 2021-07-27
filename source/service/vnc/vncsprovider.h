#ifndef VNCSPROVIDER_H
#define VNCSPROVIDER_H
#include <QObject>
#include <QDebug>
#include <QThread>
#include <QProcess>

#define pVncSP VncSProvicer::getInstance()

#define ENABLE_SLOT_VNC_START                 connect(VncSProvicer::getInstance(), SIGNAL(signalEventStarted()          ), this, SLOT(onVncStartedService(   )))
#define ENABLE_SLOT_VNC_STOP                  connect(VncSProvicer::getInstance(), SIGNAL(signalEventStopped()          ), this, SLOT(onVncStoppedService(   )))
#define ENABLE_SLOT_VNC_CHANGED_STATUS        connect(VncSProvicer::getInstance(), SIGNAL(signalEventChangedStatus(bool)), this, SLOT(onVncChangedStatus(bool)))

class VncASyncWorker : public QObject
{
    Q_OBJECT


public:
    QProcess * mpProcess = nullptr;

    explicit VncASyncWorker(QObject *parent = nullptr):QObject(parent)
    {
        qDebug() << "[VncASyncWorker]Create";
    }
    ~VncASyncWorker()
    {
        qDebug() << "[VncASyncWorker]Destruction";

        closeProcess();
    }

signals:
    void signalEventChangedStatus(bool isRun);

public slots:
    void onCommandRun(QString cmd)
    {
        qDebug() << "[VncASyncWorker][onCommandRun]" << cmd;

        closeProcess();

        mpProcess = new QProcess;

        connect(mpProcess, SIGNAL(finished(int)),this, SLOT(onFinished(int)));
        connect(mpProcess, SIGNAL(error(QProcess::ProcessError)),this, SLOT(onError(QProcess::ProcessError)));

        mpProcess->start(cmd);

        emit signalEventChangedStatus(true);
    }

    void onCommandStop()
    {
        qDebug() << "[VncASyncWorker][onCommandStop]";
        closeProcess();
    }

    void onFinished(int exitCode)
    {
        closeProcess();
    }

    void onError(QProcess::ProcessError error)
    {
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

        emit signalEventChangedStatus(false);
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

        connect(this         , SIGNAL(signalCommandRun(QString)     ), mpASyncWorker, SLOT(onCommandRun(QString)));
        connect(this         , SIGNAL(signalCommandStop()           ), mpASyncWorker, SLOT(onCommandStop()      ));
        connect(mpASyncWorker, SIGNAL(signalEventChangedStatus(bool)), this, SLOT(onChangedStatus(bool)));

        mIsRunning = true;

        emit signalEventStarted();
    }

    void stop()
    {
        qDebug() << "[VncSProvicer][stop]";

        mIsRunning = false;

        if(mpASyncWorker != nullptr)
        {
            disconnect(this         , SIGNAL(signalCommandRun(QString)     ), mpASyncWorker, SLOT(onCommandRun(QString)));
            disconnect(this         , SIGNAL(signalCommandStop()           ), mpASyncWorker, SLOT(onCommandStop()      ));
            disconnect(mpASyncWorker, SIGNAL(signalEventChangedStatus(bool)), this, SLOT(onChangedStatus(bool)));

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
        qDebug() << "[VncSProvicer][disconnectPort]";
        emit signalCommandStop();
    }

    bool isRun()
    {
        qDebug() << "[VncSProvicer][isRun]";

        if(mIsRunning == false)
            return false;

        return mpASyncWorker->mpProcess != nullptr ;
    }

signals:
    void signalEventStarted();
    void signalEventStopped();
    void signalEventChangedStatus(bool isRun);

    void signalCommandRun(QString cmd);
    void signalCommandStop();

public slots:

    void onChangedStatus(bool isRun)
    {
        //qDebug() << "[ValveSProvider][onChangedValveStatus]position" << errType;
        emit signalEventChangedStatus(isRun);
    }

private :
    bool    mIsRunning = false;
    QThread         * mpASyncWorkerThread = nullptr;
    VncASyncWorker  * mpASyncWorker       = nullptr;
};
#endif // VNCSPROVIDER_H
