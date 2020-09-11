#ifndef FILELOADERTHREAD_H
#define FILELOADERTHREAD_H

#include <QObject>
#include <QThread>
#include <QDir>
#include <QFile>
#include <QTextStream>

class FileLoaderThread : public QObject
{
    Q_OBJECT
public:
    QThread mThread;
    QFile   *mpFile = nullptr;
    QTextStream *mpOutStream = nullptr;

    explicit FileLoaderThread(QObject *parent = nullptr);
    ~FileLoaderThread();

signals:
    void signalEventLoadedFile  (QString fileName, QString content);
    void signalEventCompleteLoad(int error);
    void signalEventEndOfLine();
    void signalEventLoadedLine(QString content);

public slots:
    void onCommandLoadLine(QString path, QString fileName);
    void onCommandLoadAll(QString path, QString fileName);

};

#endif // FILELOADERTHREAD_H
