#ifndef FILEREADEREX_H
#define FILEREADEREX_H
#include <QObject>
#include <QDebug>
#include <QThread>
#include <QDir>
#include <QFile>
#include <QTextStream>

class FileReaderEx : public QObject
{
    Q_OBJECT
public:
    enum eFileError {
        FILE_ERR_NONE        = 0,
        FILE_ERR_CANNOT_OPEN = 1,
        FILE_ERR_NOT_EXIST   = 2
    };

    QFile       *mpFile = nullptr;
    QTextStream *mpOutStream = nullptr;

    static QString readAll(QString path, QString fileName)
    {
        QFile       file;
        QTextStream outStream;

        file.setFileName(QString("%1/%2").arg(path).arg(fileName));
        file.open(QIODevice::ReadOnly);

        if(file.isOpen() == false)
        {
            qDebug() << "[FileReaderEx::readAll] file name =" << QString("%1/%2").arg(path).arg(fileName) << ",occured exception, file name = " <<  file.errorString();
            return "";
        }

        outStream.setDevice(&file);

        return outStream.readAll();
    }

    static QStringList readAllLine(QString path, QString fileName)
    {
        QStringList retLines;
        QFile       file;
        QTextStream outStream;

        file.setFileName(QString("%1/%2").arg(path).arg(fileName));
        file.open(QIODevice::ReadOnly);

        if(file.isOpen() == false)
        {
            qDebug() << "[FileReaderEx::readAll] file name =" << QString("%1/%2").arg(path).arg(fileName) << ",occured exception, file name = " <<  file.errorString();
            return retLines;
        }

        outStream.setDevice(&file);
        retLines = outStream.readAll().split("\n");

        if(retLines.size() > 0 && retLines[retLines.size() - 1].length() == 0)
            retLines.removeLast();

        return retLines;
    }

    explicit FileReaderEx(QObject *parent = nullptr) : QObject(parent){}

    ~FileReaderEx()
    {
        close();
    }

    bool open(QString path, QString fileName)
    {
        close();

        QString fullName = QString("%1/%2").arg(path).arg(fileName);

        mpFile = new QFile(QString("%1/%2").arg(path).arg(fileName),this);
        mpFile->open(QIODevice::ReadOnly);

        if(mpFile->isOpen() == false)
        {
            qDebug() << "[FileReaderEx::open] file name =" << QString("%1/%2").arg(path).arg(fileName) << ",occured exception, file name = " <<  mpFile->errorString();
            close();
            return false;
        }

        mpOutStream = new QTextStream();
        mpOutStream->setDevice(mpFile);

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

        if(mpOutStream != nullptr)
        {
            mpOutStream->setDevice(nullptr);
            delete mpOutStream;
            mpOutStream = nullptr;
        }
    }

    bool readLine(QString & out)
    {
        if(mpFile == nullptr)
        {
            qDebug() << "[FileReaderEx::readLine] file not opened";
            return false;
        }

        if(mpOutStream->atEnd())
        {
            return false;
        }

        out = mpOutStream->readLine();

        return true;
    }
    QStringList readAllLine()
    {
        QStringList retLines;

        if(mpFile == nullptr)
        {
            qDebug() << "[FileReaderEx::readAllLine] file not opened";
            return retLines;
        }

        if(mpOutStream->atEnd())
        {
            return retLines;
        }

        retLines = mpOutStream->readAll().split("\n");

        if(retLines.size() > 0 && retLines[retLines.size() - 1].length() == 0)
            retLines.removeLast();

        return retLines;
    }
    QStringList readMultiLine(int lineCnt)
    {
        QStringList retLines;

        if(mpFile == nullptr)
        {
            qDebug() << "[FileReaderEx::readAllLine] file not opened";
            return retLines;
        }

        if(mpOutStream->atEnd())
        {
            return retLines;
        }

        for(int i = 0; i < lineCnt; i ++)
        {
            if(mpOutStream->atEnd())
                break;

            retLines.append(mpOutStream->readLine());
        }

        return retLines;
    }

public slots:
    void onCommandOpen(QString path, QString fileName)
    {
        if(open(path, fileName) == false)
        {
            emit signalEventError(eFileError::FILE_ERR_CANNOT_OPEN);
        }
    }
    void onCommandClose()
    {
        close();
    }
    void onCommandReadLine()
    {
        QString retString;
        if(readLine(retString) == false)
        {
            emit signalEventReadLine(true, retString);
        }

        emit signalEventReadLine(false, retString);
    }
    void onCommandReadAllLine()
    {
        QStringList retLines = readAllLine();

        emit signalEventReadAllLine(retLines);
    }
    void onCommandReadMultiLine(int lineCnt)
    {
        QStringList retLines = readMultiLine(lineCnt);

        emit signalEventReadMultiLine(retLines);
    }

signals:
    void signalEventReadLine(bool isEof, QString line);
    void signalEventReadAllLine(QStringList lines);
    void signalEventReadMultiLine(QStringList lines);
    void signalEventError(int error);
};

#endif // FILEREADEREX_H
