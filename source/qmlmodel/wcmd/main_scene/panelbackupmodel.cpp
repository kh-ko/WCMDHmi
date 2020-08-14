#include "panelbackupmodel.h"

#include <QDate>
#include "source/helper/databasehelper.h"
#include "source/helper/localsetting.h"
#include "source/service/wcmdservice.h"

DatabaseBackupState      PanelBackupModel::mBackupState;

PanelBackupModel::PanelBackupModel(QObject *parent) : QObject(parent)
{
    if(LocalSetting::getInstance()->getBackupSeq() < LocalSetting::getInstance()->getLastEventSeq() - (DatabaseHelper::getInstance()->getMaxEventCount() * 0.8))
    {
        setIsNeedBackup(true);
    }
    else
    {
        setIsNeedBackup(false);
    }
}

void PanelBackupModel::onCommandShowInterface()
{
    if(getIsProc())
    {
        setIsShowInterface(true);
        return;
    }

    QDate date = QDate::currentDate();

    int year;
    int month;
    int day;

    year = LocalSetting::getInstance()->getBackupYear();
    month = LocalSetting::getInstance()->getBackupMonth();
    day = LocalSetting::getInstance()->getBackupDay();

    if(year == 0)
    {
        year = 2020;
        month = 1;
        day = 1;
    }

    onCommandSetStartDate(year , month, day);
    onCommandSetEndDate(date.year(), date.month(), date.day());

    setIsShowInterface(true);
}

void PanelBackupModel::onCommandCloseInterface()
{
    setIsShowInterface(false);
}

void PanelBackupModel::onCommandSetStartDate(int year, int month, int day)
{
    int maxDay = checkMaxDay(year, month);
    int calDay = maxDay < day ? maxDay : day;

    setStartYear(year);
    setStartMonth(month);
    setStartDay(calDay);

    if((year > mEndYear) || (year == mEndYear && month > mEndMonth) || (year == mEndYear && month == mEndMonth && calDay > mEndDay) || (year == mEndYear && month == mEndMonth && calDay == mEndDay))
    {
        onCommandSetEndDate(year, month, calDay);
    }
}
void PanelBackupModel::onCommandSetEndDate(int year, int month, int day)
{
    QDate date = QDate::currentDate();
    int maxDay = checkMaxDay(year, month);
    int calDay = maxDay < day ? maxDay : day;

    if((year > date.year()) || (year == date.year() && month > date.month()) || (year == date.year() && month == date.month() && calDay > date.day()))
    {
        setEndYear (date.year());
        setEndMonth(date.month());
        setEndDay  (date.day());

        setStartYear (date.year() );
        setStartMonth(date.month());
        setStartDay  (date.day()  );
    }
    else
    {
        setEndYear(year);
        setEndMonth(month);
        setEndDay(calDay);

        if((year < mStartYear) || (year == mStartYear && month < mStartMonth) || (year == mStartYear && month == mStartMonth && calDay < mStartDay) || (year == mStartYear && month == mStartMonth && calDay == mStartDay))
        {
            setStartYear(year);
            setStartMonth(month);
            setStartDay(calDay);
        }
    }
}

void PanelBackupModel::onCommandBackup()
{
    qDebug() << "onCommandBackup()";

    if(getIsProc())
    {
        emit signalEventComplete(EnumDefine::BackupResult::BACKUP_ING);
        return;
    }

    if(mThread != nullptr)
    {
        mThread->quit();
        mThread->wait();
        delete mThread;

        mThread = nullptr;
    }

    mThread = QThread::create(PanelBackupModel::procBackup);

    setIsProc(true);

    setTotalCnt(100);
    setCurrentIdx(0);
    setIsShowInterface(false);

    Information info = LocalSetting::getInstance()->getInformation();

    mBackupState.reset();
    mBackupState.setHMISerialNumber     (info.mSN          );
    mBackupState.setHMIDeviceNumber     (info.mDeviceNumber);
    mBackupState.setBackupProcStartYear (getStartYear()    );
    mBackupState.setBackupProcStartMonth(getStartMonth()   );
    mBackupState.setBackupProcStartDay  (getStartDay()     );
    mBackupState.setBackupProcEndYear   (getEndYear()      );
    mBackupState.setBackupProcEndMonth  (getEndMonth()     );
    mBackupState.setBackupProcEndDay    (getEndDay()       );

    connect(mThread, SIGNAL(finished()), this, SLOT(onThreadFinish()));
    mThread->start(QThread::LowestPriority);
}
void PanelBackupModel::onCommandCancle()
{
    mBackupState.setIsCancle(true);
}

void PanelBackupModel::onCommandUpdate()
{
    setTotalCnt(mBackupState.getTotalCount());
    setCurrentIdx(mBackupState.getProgressCount());
}

void PanelBackupModel::onThreadFinish()
{
    setIsProc(false);

    if(mBackupState.getResult() == EnumDefine::BackupResult::BACKUP_NONE_ERROR)
    {
        LocalSetting::getInstance()->setBackupYear(mBackupState.getBackupProcEndYear());
        LocalSetting::getInstance()->setBackupMonth(mBackupState.getBackupProcEndMonth());
        LocalSetting::getInstance()->setBackupDay(mBackupState.getBackupProcEndDay());
        LocalSetting::getInstance()->setBackupSeq(mBackupState.getEndSeq());
    }

    if(LocalSetting::getInstance()->getBackupSeq() < LocalSetting::getInstance()->getLastEventSeq() - (DatabaseHelper::getInstance()->getMaxEventCount() * 0.8))
    {
        setIsNeedBackup(true);
    }
    else
    {
        setIsNeedBackup(false);
    }

    emit signalEventComplete(mBackupState.getResult());
}


void PanelBackupModel::procBackup()
{
    DatabaseHelper::getInstance()->backup("backup_connection", &mBackupState);
}


int PanelBackupModel::checkMaxDay(int year, int month)
{
    if(month == 2)
    {
        if((year % 4) == 0 && ((year % 100) != 0 || (year % 400) == 0))
        {
            return 29;
        }
        else
        {
            return 28;
        }
    }
    else if(month == 4 || month == 6 || month == 9 || month == 11)
    {
        return 30;
    }
    else
    {
        return 31;
    }
}

