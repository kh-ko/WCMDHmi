#include "fileloaderthreadex.h"
#include <QDebug>
#include "source/globaldef/qmlenumdef.h"

FileLoaderThreadExWorker::FileLoaderThreadExWorker(QObject *parent) : QObject(parent){}
FileLoaderThreadExWorker::~FileLoaderThreadExWorker()
{
    qDebug() << "FileLoaderThreadWorkerEx::delete";

    close();
}

void FileLoaderThreadExWorker::onCommandReadBytes(QString path, QString fileName, int maxLen)
{
    QString fullName = QString("%1/%2").arg(path).arg(fileName);


    if(mpFile == nullptr || mpFile->fileName() != fullName)
    {
        close();

        mpFile = new QFile(QString("%1/%2").arg(path).arg(fileName),this);
        mpFile->open(QIODevice::ReadOnly);

        if(mpFile->isOpen() == false)
        {
            qDebug() << "[FileLoaderThreadExWorker::onCommandReadBytes] file name =" << QString("%1/%2").arg(path).arg(fileName) << ",occured exception, file name = " <<  mpFile->errorString();
            delete mpFile;
            mpFile = nullptr;
            emit signalEventOpenFile(FileLoaderThreadEx::FILE_LOADER_ERR_NOT_EXIST, fileName);
            return;
        }
        emit signalEventOpenFile(FileLoaderThreadEx::FILE_LOADER_ERR_NONE, fileName);
        return;
    }

    if(mpFile->atEnd())
    {
        emit signalEventEof();
        return;
    }

    QByteArray content = mpFile->read(maxLen);

    emit signalEventReadBytes(FileLoaderThreadEx::FILE_LOADER_ERR_NONE, content);
}

void FileLoaderThreadExWorker::close()
{
    if(mpFile != nullptr)
    {
        if(mpFile->isOpen())
            mpFile->close();
        delete mpFile;
        mpFile = nullptr;
    }
}
