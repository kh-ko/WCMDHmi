#include "historybackupthread.h"

#include <QDir>
#include <QFile>
#include <QApplication>
#include <QProcess>
#include <QDebug>

#include "source/globaldef/EnumDefine.h"

HistoryBackupThread::HistoryBackupThread(QObject *parent) : QObject(parent)
{
    moveToThread(&mThread);
    mThread.start();
}

HistoryBackupThread::~HistoryBackupThread()
{
    mThread.quit();
    mThread.wait();
}

void HistoryBackupThread::onCommandBackup(int deviceNumber, int startYear, int startMonth, int startDay, int endYear, int endMonth, int endDay, bool *pCancle)
{
    QString applicationPath = QApplication::applicationDirPath();
    QString srcBaseFolder = QString("%1/database/history").arg(applicationPath);
    QString dstBaseFolder = QString("/home/pi/usb/novasen/backup/%1").arg(deviceNumber);

    mkdirBackupFolder(QString("%1").arg(deviceNumber));

    quint64 startDateNumber = (startYear * 10000) + (startMonth * 100) + startDay;
    quint64 endDateNumber   = (endYear   * 10000) + (endMonth   * 100) + endDay  ;

    int ret = EnumDefine::BackupResult::BACKUP_NONE_ERROR;
    QStringList srcFileList;
    QStringList dstFileList;

    QProcess process;
    process.start("df -h");
    process.waitForFinished(-1); // will wait forever until finished

    QString output = process.readAllStandardOutput();

    if(output.contains("/dev/sda1") == false)
    {
        emit signalEventCompleted(EnumDefine::BackupResult::USB_ERROR);
        return;
    }

    setCanclePtr(pCancle);

    setIsProc(true);

    // get backup list    
    QDir dir(srcBaseFolder);
    QStringList fileList = dir.entryList(QStringList() << "*.txt",QDir::Files,QDir::SortFlag::Name);

    for(int i = 0; i < fileList.size(); i ++)
    {
        QStringList strDate = fileList.at(i).split("-");

        if(strDate.size() < 4)
            continue;

        quint64 dateNumber = (strDate[0].toInt() * 10000) + (strDate[1].toInt() * 100) + strDate[2].toInt();

        if(dateNumber < startDateNumber || dateNumber > endDateNumber)
            continue;

        srcFileList.append(QString("%1/%2").arg(srcBaseFolder).arg(fileList.at(i)));
        dstFileList.append(QString("%1/%2").arg(dstBaseFolder).arg(fileList.at(i)));
    }

    setTotalCnt(srcFileList.size());
    for(int i = 0; i < srcFileList.size(); i ++)
    {
        if(getCancle() == true)
        {
            ret = EnumDefine::BackupResult::BACKUP_CANCLE;
            break;
        }

        QFile srcFile(srcFileList.at(i));

        if(srcFile.copy(dstFileList.at(i)) == false)
        {
            qDebug() << "[HistoryBackupThread::onCommandBackup] err = " << srcFile.errorString();
            ret = EnumDefine::BackupResult::BACKUP_UNKNOW_ERROR;
            break;
        }
        setCurrentIdx(i+1);
    }

    QString cmd;

    cmd.sprintf("sudo umount /home/pi/usb");

    system(cmd.toStdString().c_str());

    setIsProc(false);

    emit signalEventCompleted(ret);
}

void HistoryBackupThread::mkdirBackupFolder(QString deviceNum)
{
    QDir("/home/pi/usb/novasen").removeRecursively();

    QDir().mkdir("/home/pi/usb/novasen");
    QDir().mkdir("/home/pi/usb/novasen/backup");
    QDir().mkdir(QString("/home/pi/usb/novasen/backup/%1").arg(deviceNum));
}
