#include "nsdebug.h"

#include <QDebug>
#include <QDateTime>
#include <QDir>
#include <iostream>
#include <QApplication>

NSDebug * NSDebug::mpSelf = nullptr;
NSDebug::NSDebug(QObject *parent) : QObject(parent)
{

}

void NSDebug::startService()
{
    QString applicationPath = QApplication::applicationDirPath();

    if(mpSelf == nullptr)
    {
        mpSelf = new NSDebug();

        if (QDir(QString("%1/log").arg(applicationPath)).exists() == false)
        {
            QDir().mkdir(QString("%1/log").arg(applicationPath));
        }
        else
        {
            QDir dir(QString("%1/log").arg(applicationPath));
            QStringList fileList = dir.entryList(QStringList() << "*.txt",QDir::Files,QDir::SortFlag::Name);

            if(fileList.size() > 100)
            {
                for(int i = 0; i < fileList.size() - 100; i++)
                {
                    QFile::remove(QString("%1/log/%2").arg(applicationPath).arg(fileList.at(i)));
                }
            }
        }

        QString currTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
        QString fileName = "%1/log/log_%2.txt";
        mpSelf->mfile.setFileName(fileName.arg(applicationPath).arg(currTime));

        mpSelf->mfile.open(QIODevice::WriteOnly | QIODevice::Text);
        if(mpSelf->mfile.isOpen() == false)
        {
            QString error =  mpSelf->mfile.errorString();
            return;
        }

        mpSelf->mOut.setDevice(&(mpSelf->mfile));
    }
}
void NSDebug::stopService()
{
    if(mpSelf == nullptr)return;

    mpSelf->mfile.close();

    delete mpSelf;
    mpSelf = nullptr;


}

void NSDebug::debugMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    mpSelf->mutex.lock();
    QTextStream consoleOut(stdout);
    QString currTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";


    if(file[0] == 'q')
    {
        if(mpSelf->mfile.isOpen())
            mpSelf->mOut << "[" << currTime << "][" << file << "][" << function << "]"<< msg << "\n";

        consoleOut << "[" << currTime << "][" << file << "][" << function << "]"<< msg << "\n";
    }
    else
    {
        if(mpSelf->mfile.isOpen())
            mpSelf->mOut << "[" << currTime << "]"<< msg << "\n";

        consoleOut << "[" << currTime << "]"<< msg << "\n";
    }

    if(mpSelf->mfile.isOpen())
        mpSelf->mOut.flush();


    mpSelf->mutex.unlock();
}


void NSDebug::factoryReset()
{
    mpSelf->mutex.lock();

    QString applicationPath = QApplication::applicationDirPath();

    mpSelf->mOut.setDevice(nullptr);
    mpSelf->mfile.close();
    QDir(QString("%1/log").arg(applicationPath)).removeRecursively();

    mpSelf->mutex.unlock();
}
