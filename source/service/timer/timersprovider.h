#ifndef TIMERSPROVIDER_H
#define TIMERSPROVIDER_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QThread>
#include <QDebug>

#define pTimerSP TimerSProvider::getInstance()

class TimeChecker : public QObject
{
    Q_OBJECT

    QTimer * mpTimer;
public:
    explicit TimeChecker(QObject * parent = nullptr):QObject(parent)
    {
    }
    ~TimeChecker()
    {
        mpTimer->stop();
        delete mpTimer;
    }

public slots:
    void onStart()
    {
        mpTimer = new QTimer(this);
        mpTimer->setInterval(100);
        connect(mpTimer, SIGNAL(timeout()), this, SLOT(onTimeTick()));

        mpTimer->start();
    }

    void onTimeTick()
    {
        //[debug]
        static qint64 lastMSec = 0;

        qint64 now = QDateTime::currentMSecsSinceEpoch();
        if(now - lastMSec > 200)
        {
            qDebug() << "[debug]TimeChecker msec : " << (now - lastMSec);
        }

        lastMSec = now;
        //[debug]
    }

};
class TimerSProvider : public QObject
{
    Q_OBJECT

private:
    qint64 mMSec = 0; //[debug]
    QTimer mTimer;
public:
    static TimerSProvider * getInstance()
    {
        static TimerSProvider *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new TimerSProvider();
        }

        return mpSelf;
    }

    QThread *mpTh = nullptr; // [debug]
    TimeChecker * mpTimeChecker = nullptr; // [debug]

    bool mIsRunning = false;

    explicit TimerSProvider(QObject * parent = nullptr):QObject(parent)
    {
        mTimer.setInterval(100);

        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeTick()));
    }
    ~TimerSProvider()
    {
        mpTh->quit(); // [debug]
        mpTh->wait(); // [debug]
    }

    void start()
    {
        mIsRunning = true;
        mTimer.start();
        emit signalEventStarted();

        // [debug]
        mpTh = new QThread;
        mpTimeChecker = new TimeChecker;
        mpTimeChecker->moveToThread(mpTh);
        mpTh->start();
        connect(mpTh, &QThread::finished, mpTimeChecker, &QObject::deleteLater);
        connect(this, SIGNAL(signalCommandStart()), mpTimeChecker, SLOT(onStart()));

        emit signalCommandStart();
        // [debug]



    }

    void stop()
    {
        mTimer.stop();
        mIsRunning = false;
        emit signalEventStopped();
    }

signals:
    void signalEventStarted        ();
    void signalEventStopped        ();

    void signalCommandStart(); // [debug]
    void signalTimeTick(QDateTime now);

private slots:
    void onTimeTick()
    {
        qint64 currMSec = QDateTime::currentMSecsSinceEpoch();
        if(currMSec - mMSec > 1000)
            qDebug() << "[debug] TimerSProvider msec : "<< currMSec - mMSec;

        mMSec = currMSec;

        emit signalTimeTick(QDateTime::currentDateTime());
    }
};
#endif // TIMERSPROVIDER_H
