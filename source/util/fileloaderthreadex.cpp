#include "fileloaderthreadex.h"
#include <QDebug>
#include "source/globaldef/EnumDefine.h"

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
            emit signalEventOpenFile(EnumDefine::FileErrorType::FILE_ERROR_NOT_EXIST, fileName);
            return;
        }
        emit signalEventOpenFile(EnumDefine::FileErrorType::FILE_ERROR_NONE, fileName);
        return;
    }

    if(mpFile->atEnd())
    {
        emit signalEventEof();
        return;
    }

    QByteArray content = mpFile->read(maxLen);

    emit signalEventReadBytes(EnumDefine::FileErrorType::FILE_ERROR_NONE, content);
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
