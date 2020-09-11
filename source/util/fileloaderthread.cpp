#include "fileloaderthread.h"
#include <QDebug>
#include "source/globaldef/EnumDefine.h"

FileLoaderThread::FileLoaderThread(QObject *parent) : QObject(parent)
{
    moveToThread(&mThread);
    mThread.start();
}

FileLoaderThread::~FileLoaderThread()
{
    if(mpFile != nullptr)
    {
        if(mpOutStream != nullptr)
            delete mpOutStream;

        if(mpFile->isOpen())
            mpFile->close();
        delete mpFile;
        mpFile = nullptr;
    }

    mThread.quit();
    mThread.wait();
}

void FileLoaderThread::onCommandLoadAll(QString path, QString fileName)
{
    int retError = EnumDefine::FileErrorType::FILE_ERROR_NONE;
    QStringList fileList;
    QDir dir(path);

    if(fileName == "*")
    {
        fileList = dir.entryList(QStringList() << "*.txt", QDir::Files,QDir::SortFlag::Name);
    }
    else
    {
        if(QFile::exists(QString("%1/%2.txt").arg(path).arg(fileName)))
        {
            fileList.append(QString("%1.txt").arg(fileName));
        }
    }

    if(fileList.size() == 0)
    {
        retError = EnumDefine::FileErrorType::FILE_ERROR_NOT_EXIST;
    }

    for(int i = 0; i < fileList.size(); i++)
    {
        QString fullPath = QString("%1/%2").arg(path).arg(fileList.at(i));
        QFile file(fullPath);
        file.open(QIODevice::ReadOnly | QIODevice::Text );

        if(file.isOpen() == false)
        {
            qDebug() << "[onCommandLoadAll] file name =" << fullPath << ",occured exception, file name = " <<  file.errorString();
            continue;
        }

        QTextStream out(&file);
        QString content = out.readAll();

        file.close();

        emit signalEventLoadedFile(fileList.at(i).split(".")[0], content);
    }

    emit signalEventCompleteLoad(retError);
}

void FileLoaderThread::onCommandLoadLine(QString path, QString fileName)
{
    if(mpFile == nullptr)
    {
        mpFile = new QFile(QString("%1/%2.txt").arg(path).arg(fileName),this);
        mpFile->open(QIODevice::ReadOnly | QIODevice::Text );

        if(mpFile->isOpen() == false)
        {
            qDebug() << "[onCommandLoadLine] file name =" << QString("%1/%2").arg(path).arg(fileName) << ",occured exception, file name = " <<  mpFile->errorString();
            delete mpFile;
            mpFile = nullptr;
            emit signalEventEndOfLine();
            return;
        }

        mpOutStream = new QTextStream();
        mpOutStream->setDevice(mpFile);
    }

    if(mpOutStream->atEnd())
    {
        delete mpOutStream;
        mpOutStream=nullptr;
        mpFile->close();
        delete mpFile;
        mpFile = nullptr;
        emit signalEventEndOfLine();
        return;
    }

    emit signalEventLoadedLine(mpOutStream->readLine());
}
