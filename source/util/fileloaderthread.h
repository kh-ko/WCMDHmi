#ifndef FILELOADERTHREAD_H
#define FILELOADERTHREAD_H

#include <QObject>
#include <QThread>
#include <QDir>
#include <QFile>
#include <QTextStream>

class FileLoakerThreadWorker : public QObject
{
    Q_OBJECT
public:
    QFile   *mpFile = nullptr;
    QTextStream *mpOutStream = nullptr;

    explicit FileLoakerThreadWorker(QObject *parent = nullptr);
    ~FileLoakerThreadWorker();

public slots:
    void onCommandLoadAll(QString path, QString fileName);
    void onCommandLoadLine(QString path, QString fileName);
    void onCommandLoadMultiLine(QString path, QString fileName, int lineCnt);

signals:
    void signalEventLoadedFile  (QString fileName, QString content);
    void signalEventCompleteLoad(int error);
    void signalEventEndOfLine();
    void signalEventLoadedLine(QString content);
    void signalEventLoadedMultiLine(QStringList lines);
};

class FileLoaderThread : public QObject
{
    Q_OBJECT
public:
    FileLoakerThreadWorker * mpWoker;
    QThread mThread;

    explicit FileLoaderThread(QObject *parent = nullptr) : QObject(parent)
    {
        mpWoker = new FileLoakerThreadWorker;
        mpWoker->moveToThread(&mThread);

        connect(&mThread, &QThread::finished, mpWoker, &QObject::deleteLater);
        connect(this, SIGNAL(signalCommandLoadLine      (QString, QString     )), mpWoker, SLOT(onCommandLoadLine     (QString, QString     )));
        connect(this, SIGNAL(signalCommandLoadMultiLine (QString, QString, int)), mpWoker, SLOT(onCommandLoadMultiLine(QString, QString, int)));
        connect(this, SIGNAL(signalCommandLoadAll       (QString, QString     )), mpWoker, SLOT(onCommandLoadAll      (QString, QString     )));

        connect(mpWoker, SIGNAL(signalEventLoadedFile       (QString, QString)), this, SLOT(onSignalEventLoadedFile       (QString, QString)));
        connect(mpWoker, SIGNAL(signalEventCompleteLoad     (int             )), this, SLOT(onSignalEventCompleteLoad     (int             )));
        connect(mpWoker, SIGNAL(signalEventEndOfLine        (                )), this, SLOT(onSignalEventEndOfLine        (                )));
        connect(mpWoker, SIGNAL(signalEventLoadedLine       (QString         )), this, SLOT(onSignalEventLoadedLine       (QString         )));
        connect(mpWoker, SIGNAL(signalEventLoadedMultiLine  (QStringList     )), this, SLOT(onSignalEventLoadedMultiLine  (QStringList     )));

        mThread.start();
    }
    ~FileLoaderThread()
    {
        mThread.quit();
        mThread.wait();
    }

signals:
    void signalEventLoadedFile  (QString fileName, QString content);
    void signalEventCompleteLoad(int error);
    void signalEventEndOfLine();
    void signalEventLoadedLine(QString content);
    void signalEventLoadedMultiLine(QStringList lines);

public slots:
    void onCommandLoadLine(QString path, QString fileName){emit signalCommandLoadLine(path, fileName);}
    void onCommandLoadMultiLine(QString path, QString fileName, int lineCnt){emit signalCommandLoadMultiLine(path, fileName, lineCnt);}
    void onCommandLoadAll(QString path, QString fileName){emit signalCommandLoadAll(path, fileName);}

signals:
    void signalCommandLoadLine(QString path, QString fileName);
    void signalCommandLoadMultiLine(QString path, QString fileName, int lineCnt);
    void signalCommandLoadAll(QString path, QString fileName);

public slots:
    void onSignalEventLoadedFile      (QString fileName, QString content){emit signalEventLoadedFile(fileName, content);}
    void onSignalEventCompleteLoad    (int error                        ){emit signalEventCompleteLoad(error);}
    void onSignalEventEndOfLine       (                                 ){emit signalEventEndOfLine();}
    void onSignalEventLoadedLine      (QString content                  ){emit signalEventLoadedLine(content);}
    void onSignalEventLoadedMultiLine (QStringList lines                ){emit signalEventLoadedMultiLine(lines);}
};

#endif // FILELOADERTHREAD_H
