#ifndef FILECOPYLOCAL_H
#define FILECOPYLOCAL_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include "source/service/util/filewriterex.h"

class FileCopyLocal : public QObject
{
    Q_OBJECT
public:
    QStringList mSrcList;
    QStringList mDstList;

    int  mCopyIdx  = 0;

    explicit FileCopyLocal(QObject *parent = nullptr) : QObject(parent){}
    ~FileCopyLocal(){}
    void cancel()
    {
        setCancel(true);
    }

signals:
    void signalEventProgress(int procIdx, int totalCnt);
    void signalEventComplete(bool isSucc);

public slots:
    void onCommandCopyFolder(QString dst, QString src, QString fromFileName)
    {
        makeCopyList(dst, src, fromFileName);

        for(int i = 0; (i < mSrcList.size()) && getCancel() == false; i ++)
        {
            if(QFile::exists(mDstList[i]))
            {
                QFile::remove(mDstList[i]);
            }
            if(QFile::copy(mSrcList[i], mDstList[i]) == false)
            {
                qDebug() << "[FileCopyLocal::onCommandCopyFolder] copy failed : src = " << mSrcList[i] << ", dst = " << mDstList[i];
            }
            emit signalEventProgress(i, mSrcList.size());
        }
        emit signalEventComplete(true);
    }

private:
    bool mCancel = false;

    void setCancel(bool value)
    {
        mCancel = value;
    }

    bool getCancel()
    {
        return mCancel;
    }

    void makeCopyList(QString dst, QString src, QString fromFileName)
    {
        QDir sourceDir(src);
        QDir targetDir(dst);

        if(!targetDir.exists())
        {
            FileWriterEx::mkdirRecursively(dst);
        }

        QFileInfoList fileInfoList = sourceDir.entryInfoList();

        foreach(QFileInfo fileInfo, fileInfoList)
        {
            if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
                continue;

            if(fileInfo.isDir())
            {
                makeCopyList(QString("%1/%2").arg(dst).arg(fileInfo.fileName()), QString("%1/%2").arg(src).arg(fileInfo.fileName()), fromFileName);
            }
            else
            {
                if(fromFileName <= fileInfo.fileName())
                {
                    mSrcList.append(QString("%1/%2").arg(src).arg(fileInfo.fileName()));
                    mDstList.append(QString("%1/%2").arg(dst).arg(fileInfo.fileName()));
                }
            }
        }
    }
};

#endif // FILECOPYLOCAL_H
