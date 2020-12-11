#ifndef FILEFOLDERREADER_H
#define FILEFOLDERREADER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QDir>
#include <QFile>
#include <QTextStream>

class FileFolderReader : public QObject
{
    Q_OBJECT
public:
    QStringList  mFileList;
    QString      mFolderPath;

    explicit FileFolderReader(QObject *parent = nullptr) : QObject(parent){}
    ~FileFolderReader()
    {
    }

    void open(QString folderPath, QString filter)
    {
        mFolderPath = folderPath;
        QDir dir(mFolderPath);

        mFileList.clear();

        mFileList = dir.entryList(QStringList() << filter, QDir::Files,QDir::SortFlag::Name);
    }

    void close()
    {
    }

    int fileCount(){ return mFileList.size();}

    QString readFile(int idx)
    {
        if(mFileList.size() - 1 < idx)
            return "";

        QFile       file;
        QTextStream outStream;

        file.setFileName(QString("%1/%2").arg(mFolderPath).arg(mFileList[idx]));
        file.open(QIODevice::ReadOnly);

        if(file.isOpen() == false)
        {
            qDebug() << "[FileFolderReader::readFile] file name =" << mFileList[idx] << ",occured exception, file name = " <<  file.errorString();
            return "";
        }

        outStream.setDevice(&file);

        return outStream.readAll();
    }
};

#endif // FILEFOLDERREADER_H
