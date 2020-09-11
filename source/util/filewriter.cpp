#include "filewriter.h"

#include <QDebug>

bool FileWriter::appendLine(QString path, QString fileName, QString content)
{
     mkdirRecursively(path);

    if(mFile.isOpen() == false)
    {
        mFile.setFileName(QString("%1/%2.txt").arg(path).arg(fileName));
        mFile.open(QIODevice::ReadWrite | QIODevice::Append);

        if(mFile.isOpen() == false)
        {
            qDebug() << "[FileWriter::appendLine]can not overWriteLine : " << path << "/" << fileName  ;
            return false;
        }

        mStream.setDevice(&mFile);
    }

    mStream << content << "\n";
    mStream.flush();

    return true;
}

bool FileWriter::overWriteLine(QString path, QString fileName, QString content, qint64 startOffset, qint64 len)
{
    mkdirRecursively(path);

    if(mFile.isOpen() == false)
    {
        mFile.setFileName(QString("%1/%2.txt").arg(path).arg(fileName));
        mFile.open(QIODevice::ReadWrite);

        if(mFile.isOpen() == false)
        {
            qDebug() << "[FileWriter::appendLine]can not overWriteLine : " << path << "/" << fileName  ;
            return false;
        }
    }

    content.resize(len,' ');
    content.replace(content.size()-1 ,1, '\n');

    mFile.seek(startOffset);
    mFile.write(content.toUtf8(), len);
    mFile.flush();
    return true;
}

bool FileWriter::newWrite(QString path, QString fileName, QString content)
{
    mkdirRecursively(path);

    mFile.setFileName(QString("%1/%2.txt").arg(path).arg(fileName));
    mFile.open(QIODevice::WriteOnly);

    if(mFile.isOpen() == false)
    {
        qDebug() << "[FileWriter::appendLine]can not new write : " << path << "/" << fileName  ;
        return false;
    }

    mStream.setDevice(&mFile);
    mStream << content;
    mStream.flush();

    return true;
}

bool FileWriter::remove(QString path, QString fileName)
{
    if(QFile::exists(QString("%1/%2.txt").arg(path).arg(fileName)) == false)
    {
        qDebug() << "[FileWriter::appendLine]can not remove : " << path << "/" << fileName  ;
        return false;
    }

    return QFile::remove(QString("%1/%2.txt").arg(path).arg(fileName));
    return true;
}

void FileWriter::close()
{
    if(mFile.isOpen() == false)
        mFile.close();
}

FileWriter::FileWriter(QObject *parent) : QObject(parent)
{

}

FileWriter::~FileWriter()
{
    if(mFile.isOpen())
        mFile.close();
}

void FileWriter::mkdirRecursively(QString path)
{
    if(QDir().exists(path))
        return;

    QStringList folderList = path.split("/");
    QString     pathName = QString("");

    for(int i = 0; i < folderList.size(); i ++)
    {
        QString folderName = folderList.at(i);

        if(folderName == nullptr || folderName.length() == 0)
            continue;

        if(pathName.length() == 0)
        {
#if defined(Q_OS_WIN)
            pathName = QString("%1").arg(folderName);
#else
            pathName = QString("/%1").arg(folderName);
#endif
        }
        else
            pathName = QString("%1/%2").arg(pathName).arg(folderName);

        if(QDir().exists(pathName))
            continue;

        QDir().mkdir(pathName);
    }
}
