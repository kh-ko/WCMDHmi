#ifndef FILEWRITEREX_H
#define FILEWRITEREX_H
#include <QObject>
#include <QDebug>
#include <QThread>
#include <QDir>
#include <QFile>
#include <QTextStream>

class FileWriterEx : public QObject
{
    Q_OBJECT
public:
    enum eOpenMode {
        FILE_OPEN_NEWWRITE    = 0,
        FILE_OPEN_OVERWRITE   = 1,
        FILE_OPEN_APPENDWRITE = 2
    };

    QFile       *mpFile = nullptr;

    static bool newWrite(QString path, QString fileName, QString content)
    {
        mkdirRecursively(path);

        QFile file;
        file.setFileName(QString("%1/%2").arg(path).arg(fileName));
        file.open(QFile::WriteOnly);

        if(file.isOpen() == false)
        {
            qDebug() << "[FileWriterEx::newWrite] file name =" << QString("%1/%2").arg(path).arg(fileName) << ",occured exception, file name = " <<  file.errorString();
            return false;
        }

        file.write(content.toUtf8());
        file.flush();
        file.close();
        return true;
    }

    static bool appendLine(QString path, QString fileName, QString content)
    {
        QFile file;

        mkdirRecursively(path);

        file.setFileName(QString("%1/%2").arg(path).arg(fileName));
        file.open(QFile::WriteOnly | QFile::Append);

        if(file.isOpen() == false)
        {
            qDebug() << "[FileWriterEx::appendLine]can not appendLine : " << path << "/" << fileName  ;
            return false;
        }
        QString writeLine = QString("%1\n").arg(content);

        file.write(writeLine.toUtf8());
        file.flush();

        return true;
    }

    static void mkdirRecursively(QString path){
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

    explicit FileWriterEx(QObject *parent = nullptr) : QObject(parent){}
    ~FileWriterEx()
    {
        close();
    }

    bool open(QString path, QString fileName, eOpenMode flags)
    {
        mkdirRecursively(path);

        close();

        QString fullName = QString("%1/%2").arg(path).arg(fileName);

        mpFile = new QFile(QString("%1/%2").arg(path).arg(fileName),this);

        switch(flags)
        {
        case FILE_OPEN_NEWWRITE:
            mpFile->open(QFile::WriteOnly);
            break;

        case FILE_OPEN_OVERWRITE:
            mpFile->open(QFile::ReadWrite);
            break;

        case FILE_OPEN_APPENDWRITE:
            mpFile->open(QFile::WriteOnly | QFile::Append);
            break;
        }

        if(mpFile->isOpen() == false)
        {
            qDebug() << "[FileWriterEx::open] file name =" << QString("%1/%2").arg(path).arg(fileName) << ",occured exception, file name = " <<  mpFile->errorString();
            close();
            return false;
        }

        return true;
    }

    void close()
    {
        if(mpFile != nullptr)
        {
            if(mpFile->isOpen())
                mpFile->close();
            delete mpFile;
            mpFile = nullptr;
        }
    }

    bool appendLine(QString line)
    {
        if(mpFile == nullptr)
        {
            qDebug() << "[FileWriterEx::writeLine] file not opened";
            return false;
        }

        QString writeLine = QString("%1\n").arg(line);

        mpFile->write(writeLine.toUtf8());
        mpFile->flush();
        return true;
    }

    bool overWriteLine(QString line, qint64 lineOffset, int lineLen)
    {
        if(mpFile == nullptr)
        {
            qDebug() << "[FileWriterEx::overWriteLine] file not opened";
            return false;
        }

        line.resize(lineLen,' ');

        QByteArray temp = line.toUtf8();
        temp[lineLen -1] = '\n';

        mpFile->seek(lineLen * lineOffset);
        mpFile->write(temp.data(), lineLen);
        mpFile->flush();
        return true;
    }

    bool newWrite(QString content)
    {
        if(mpFile == nullptr)
        {
            qDebug() << "[FileWriterEx::newWrite] file not opened";
            return false;
        }

        QByteArray temp = content.toUtf8();

        mpFile->write(temp);
        mpFile->flush();
        return true;
    }

};
#endif // FILEWRITEREX_H
