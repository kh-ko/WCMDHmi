#include "historybackupthread.h"

#include <QDir>
#include <QFile>
#include <QApplication>
#include <QProcess>
#include <QDebug>


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
    if(QFile::exists("/dev/sda1") == false)
    {
        backupComplete(QmlEnumDef::BackupResult::USB_ERROR);
        return;
    }

    startUsbCheckTimer();

    mDevNum = deviceNumber;
    mFYear  = startYear;
    mFMonth = startMonth;
    mFDay   = startDay;
    mTYear  = endYear;
    mTMonth = endMonth;
    mTDay   = endDay;

    setIsScanUsb(true);
    setIsProc(true);
    setCanclePtr(pCancle);

    return;
}

void HistoryBackupThread::checkUsb()
{
    if(getCancle())
    {
        backupComplete(QmlEnumDef::BACKUP_CANCLE);
        return;
    }

    QProcess process;
    process.start("df -h");
    process.waitForFinished(-1); // will wait forever until finished

    QString output = process.readAllStandardOutput();

    if(output.contains("/dev/sda1") == false && (QDateTime::currentMSecsSinceEpoch() - mCheckStartMSec) > (60 * 1000 * 5))
    {
        backupComplete(QmlEnumDef::USB_ERROR);
        return;
    }

    if(output.contains("/dev/sda1") == true)
    {
        stopUsbCheckTimer();
        backupProc();
    }
}

void HistoryBackupThread::mkdirBackupFolder(QString deviceNum)
{
    QDir("/home/pi/usb/novasen").removeRecursively();

    QDir().mkdir("/home/pi/usb/novasen");
    QDir().mkdir("/home/pi/usb/novasen/backup");
    QDir().mkdir(QString("/home/pi/usb/novasen/backup/%1").arg(deviceNum));
}

void HistoryBackupThread::stopUsbCheckTimer()
{
    if(mpTimer != nullptr)
    {
        mpTimer->stop();
        mpTimer->deleteLater();
        mpTimer = nullptr;
    }
    mCheckStartMSec = 0;
    setIsScanUsb(false);
}

void HistoryBackupThread::startUsbCheckTimer()
{
    stopUsbCheckTimer();

    setIsScanUsb(true);
    mpTimer = new QTimer(this);
    mpTimer->setInterval(100);
    connect(mpTimer, SIGNAL(timeout()), this, SLOT(checkUsb()));
    mpTimer->start();
    mCheckStartMSec = QDateTime::currentMSecsSinceEpoch();
}

void HistoryBackupThread::backupProc()
{
    QString applicationPath = QApplication::applicationDirPath();
    QString srcBaseFolder = QString("%1/database/history").arg(applicationPath);
    QString dstBaseFolder = QString("/home/pi/usb/novasen/backup/%1").arg(mDevNum);

    mkdirBackupFolder(QString("%1").arg(mDevNum));

    quint64 startDateNumber = (mFYear * 10000) + (mFMonth * 100) + mFDay;
    quint64 endDateNumber   = (mTYear   * 10000) + (mTMonth   * 100) + mTDay  ;

    QmlEnumDef::BackupResult ret = QmlEnumDef::BACKUP_NONE_ERROR;
    QStringList srcFileList;
    QStringList dstFileList;

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
            ret = QmlEnumDef::BACKUP_CANCLE;
            break;
        }

        QFile srcFile(srcFileList.at(i));

        if(srcFile.copy(dstFileList.at(i)) == false)
        {
            qDebug() << "[HistoryBackupThread::onCommandBackup] err = " << srcFile.errorString();
            ret = QmlEnumDef::BACKUP_UNKNOW_ERROR;
            break;
        }
        setCurrentIdx(i+1);
    }

    QString cmd;

    cmd.sprintf("sudo umount /home/pi/usb");

    system(cmd.toStdString().c_str());

    backupComplete(ret);


}

void HistoryBackupThread::backupComplete(QmlEnumDef::BackupResult result)
{
    mDevNum          = 0;
    mFYear           = 0;
    mFMonth          = 0;
    mFDay            = 0;
    mTYear           = 0;
    mTMonth          = 0;
    mTDay            = 0;
    mTotalCnt        = 0;
    mCurrentIdx      = 0;

    stopUsbCheckTimer();
    setIsProc(false);

    emit signalEventCompleted(result);
}
