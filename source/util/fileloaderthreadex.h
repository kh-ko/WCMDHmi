#ifndef FILELOADERTHREADEX_H
#define FILELOADERTHREADEX_H
#include <QObject>
#include <QThread>
#include <QDir>
#include <QFile>
#include <QTextStream>

class FileLoaderThreadExWorker : public QObject
{
    Q_OBJECT
public:
    QFile   *mpFile = nullptr;

    explicit FileLoaderThreadExWorker(QObject *parent = nullptr);
    ~FileLoaderThreadExWorker();
    void close();

public slots:
    void onCommandReadBytes(QString path, QString fileName, int maxLen);

signals:
    void signalEventReadBytes  (int error, QByteArray content);
    void signalEventOpenFile(int error, QString fileName);
    void signalEventEof();
};

class FileLoaderThreadEx : public QObject
{
    Q_OBJECT
public:
    FileLoaderThreadExWorker * mpWoker;
    QThread mThread;

    explicit FileLoaderThreadEx(QObject *parent = nullptr) : QObject(parent)
    {
        mpWoker = new FileLoaderThreadExWorker;
        mpWoker->moveToThread(&mThread);

        connect(&mThread, &QThread::finished, mpWoker, &QObject::deleteLater);
        connect(this, SIGNAL(signalCommandReadBytes(QString, QString, int)), mpWoker, SLOT(onCommandReadBytes(QString, QString, int)));

        connect(mpWoker, SIGNAL(signalEventReadBytes(int, QByteArray)), this, SLOT(onSignalEventReadBytes(int, QByteArray)));
        connect(mpWoker, SIGNAL(signalEventOpenFile (int, QString   )), this, SLOT(onSignalEventOpenFile (int, QString   )));
        connect(mpWoker, SIGNAL(signalEventEof      (               )), this, SLOT(onSignalEventEof      (               )));

        mThread.start();
    }
    ~FileLoaderThreadEx()
    {
        mThread.quit();
        mThread.wait();
    }

signals:
    void signalEventReadBytes  (int error, QByteArray content);
    void signalEventOpenFile(int error, QString fileName);
    void signalEventEof();

public slots:
    void onCommandReadBytes(QString path, QString fileName, int maxLen){emit signalCommandReadBytes(path, fileName, maxLen);}

signals:
    void signalCommandReadBytes(QString path, QString fileName, int maxLen);

public slots:
    void onSignalEventReadBytes(int error, QByteArray content ){ emit signalEventReadBytes(error, content );}
    void onSignalEventOpenFile (int error, QString    fileName){ emit signalEventOpenFile (error, fileName);}
    void onSignalEventEof      (                              ){ emit signalEventEof      (               );}
};

#endif // FILELOADERTHREADEX_H
