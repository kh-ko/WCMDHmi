#include "nsdebug.h"

#include <QDebug>
#include <QDateTime>
#include <QDir>
#include <iostream>

NSDebug * NSDebug::mpSelf = nullptr;
NSDebug::NSDebug(QObject *parent) : QObject(parent)
{

}

void NSDebug::startService()
{
    if(mpSelf == nullptr)
    {
        mpSelf = new NSDebug();

        if (QDir("log").exists() == false)
        {
            QDir().mkdir("log");
        }
        else
        {
            QDir dir("log");
            QStringList fileList = dir.entryList(QStringList() << "*.txt",QDir::Files,QDir::SortFlag::Name);

            if(fileList.size() > 100)
            {
                for(int i = 0; i < fileList.size() - 100; i++)
                {
                    QFile::remove(QString("log/%1").arg(fileList.at(i)));
                }
            }
        }

        QString currTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
        QString fileName = "log/log_%1.txt";
        mpSelf->mfile.setFileName(fileName.arg(currTime));

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
            mpSelf->mOut << "[" << currTime << "][" << function << "]"<< msg << "\n";

        consoleOut << "[" << currTime << "][" << function << "]"<< msg << "\n";
    }

    if(mpSelf->mfile.isOpen())
        mpSelf->mOut.flush();


    mpSelf->mutex.unlock();
}


void NSDebug::factoryReset()
{
    mpSelf->mutex.lock();

    mpSelf->mOut.setDevice(nullptr);
    mpSelf->mfile.close();
    QDir("log").removeRecursively();

    mpSelf->mutex.unlock();
}
