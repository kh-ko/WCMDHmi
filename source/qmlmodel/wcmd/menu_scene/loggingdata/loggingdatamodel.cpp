#include "loggingdatamodel.h"

#include <QDateTime>

#include "source/globaldef/GlobalDefine.h"
#include "source/helper/databasehelper.h"
#include "source/helper/localsetting.h"
#include "source/service/wcmdservice.h"

QMutex LoggingDataModel::mMutex;
QList<Event> LoggingDataModel::mListEvent;
quint64 LoggingDataModel::mTotalCnt;
quint64 LoggingDataModel::mTotalPage;
quint64 LoggingDataModel::mCurrentPageIdx;
bool    LoggingDataModel::mIsWeightEvent;
EnumDefine::SearchOption LoggingDataModel::mSelectOption;
EnumDefine::SearchFilter LoggingDataModel::mSelectFilter;
int LoggingDataModel::mStartYear;
int LoggingDataModel::mStartMonth;
int LoggingDataModel::mStartDay;
int LoggingDataModel::mStartHour;
int LoggingDataModel::mEndYear;
int LoggingDataModel::mEndMonth;
int LoggingDataModel::mEndDay;
int LoggingDataModel::mEndHour;

LoggingDataModel::LoggingDataModel(QObject *parent) : QObject(parent)
{
    connect(this, SIGNAL(signalCommandResetStatistics()), WCMDService::getInstance(), SLOT(onCommandResetStatistics()));

    clearListEvent();

    setSearching(false);
    setTotalCnt(0);
    setTotalPage(0);
    setCurrentPageIdx(0);

    setSelectFilter(EnumDefine::SearchFilter::SEARCH_FILTER_WITHOUT_TRADE);
    setToday();
}

LoggingDataModel::~LoggingDataModel()
{
    if(mThread != nullptr)
    {
        mThread->quit();
        mThread->wait();
        delete mThread;

        mThread = nullptr;
    }
}

quint64 LoggingDataModel::getTotalCnt()         { return mTotalCnt;         }
quint64 LoggingDataModel::getTotalPage()        { return mTotalPage;        }
quint64 LoggingDataModel::getCurrentPageIdx()   { return mCurrentPageIdx;   }
bool    LoggingDataModel::getIsWeightEvent()    {return mIsWeightEvent;     }
int     LoggingDataModel::getSelectOption()     { return (int)mSelectOption;}
int     LoggingDataModel::getSelectFilter()     { return (int)mSelectFilter;}
int     LoggingDataModel::getStartYear()        { return mStartYear;        }
int     LoggingDataModel::getStartMonth()       { return mStartMonth;       }
int     LoggingDataModel::getStartDay()         { return mStartDay;         }
int     LoggingDataModel::getStartHour()        { return mStartHour;        }
int     LoggingDataModel::getEndYear()          { return mEndYear;          }
int     LoggingDataModel::getEndMonth()         { return mEndMonth;         }
int     LoggingDataModel::getEndDay()           {return mEndDay;            }
int     LoggingDataModel::getEndHour()          { return mEndHour;          }
bool    LoggingDataModel::getSearching()        { return mSearching;        }
int     LoggingDataModel::getSelIdx()           { return mSelIdx;           }

void LoggingDataModel::setTotalCnt(quint64 value){/*if(value == mTotalCnt)return; */mTotalCnt = value; emit signalEventChangedTotalCnt(value);}
void LoggingDataModel::setTotalPage(quint64 value){/*if(value == mTotalPage)return; */mTotalPage = value; emit signalEventChangedTotalPage(value);}
void LoggingDataModel::setCurrentPageIdx(quint64 value){if(value == mCurrentPageIdx)return; mCurrentPageIdx = value; emit signalEventChangedCurrentPageIdx(value);}
void LoggingDataModel::setIsWeightEvent(bool value){if(value == mIsWeightEvent)return; mIsWeightEvent = value; emit signalEventChangedIsWeightEvent(value);}
void LoggingDataModel::setSelectOption(EnumDefine::SearchOption value){ if(value == mSelectOption)return; mSelectOption = value; emit signalEventChangedSelectOption(value);}
void LoggingDataModel::setSelectFilter(EnumDefine::SearchFilter value){ if(value == mSelectFilter)return; mSelectFilter = value; emit signalEventChangedSelectFilter(value);}
void LoggingDataModel::setStartYear(int value){ if(value == mStartYear)return; mStartYear = value; emit signalEventChangedStartYear(value);}
void LoggingDataModel::setStartMonth(int value){ if(value == mStartMonth)return; mStartMonth = value; emit signalEventChangedStartMonth(value);}
void LoggingDataModel::setStartDay(int value){ if(value == mStartDay)return; mStartDay = value; emit signalEventChangedStartDay(value);}
void LoggingDataModel::setStartHour(int value){ if(value == mStartHour)return; mStartHour = value; emit signalEventChangedStartHour(value);}
void LoggingDataModel::setEndYear(int value){ if(value == mEndYear)return; mEndYear = value; emit signalEventChangedEndYear(value);}
void LoggingDataModel::setEndMonth(int value){ if(value == mEndMonth)return; mEndMonth = value; emit signalEventChangedEndMonth(value);}
void LoggingDataModel::setEndDay(int value){ if(value == mEndDay)return; mEndDay = value; emit signalEventChangedEndDay(value);}
void LoggingDataModel::setEndHour(int value){ if(value == mEndHour)return; mEndHour = value; emit signalEventChangedEndHour(value);}
void LoggingDataModel::setSearching(bool value){ if(value == mSearching)return; mSearching = value; emit signalEventChangedSearching(value);}
void LoggingDataModel::setSelIdx(int value){ /*if(value == mSearching)return; */mSelIdx = value; emit signalEventChangedSelIdx(value);}

int LoggingDataModel::onCommandGetListCnt()
{
    return mListEvent.size();
}

QString LoggingDataModel::onCommandGetDateTimeItem(int idx)
{
    QString dateTime = "%1/%2/%3 %4:%5:%6.%7";

    if(idx >= onCommandGetListCnt())
    {
        return "";
    }

    Event event = mListEvent.at(idx);

    return dateTime.arg(QString::number(event.mYear).rightJustified(4, '0')).arg(QString::number(event.mMonth).rightJustified(2, '0')).arg(QString::number(event.mDay).rightJustified(2, '0'))
                   .arg(QString::number(event.mHour).rightJustified(2, '0')).arg(QString::number(event.mMin).rightJustified(2, '0')).arg(QString::number(event.mSec).rightJustified(2, '0')).arg(QString::number(event.mMsec).rightJustified(3, '0'));
}

QString LoggingDataModel::onCommandGetProductItem(int idx)
{
    QString productName = "%1 %2";

    if(idx >= onCommandGetListCnt())
    {
        return "";
    }

    Event event = mListEvent.at(idx);

    if(event.mProductNo > 0)
    {
        return productName.arg(QString::number(event.mProductNo).rightJustified(3, '0')).arg(event.mProductName);
    }
    else
        return "";
}

int LoggingDataModel::onCommandGetEventItem(int idx)
{
    if(idx >= onCommandGetListCnt())
    {
        return 0;
    }

    Event event = mListEvent.at(idx);

    return event.mEventType;
}

QString LoggingDataModel::onCommandGetWeightItem(int idx)
{
    if(idx >= onCommandGetListCnt())
    {
        return 0;
    }

    Event event = mListEvent.at(idx);

    //if(event.mEventType < EnumDefine::EventType::WEIGHT_NORMAL_TYPE &&  event.mEventType > EnumDefine::EventType::WEIGHT_ETCERROR_TYPE)
    //    return 0;

    if(  event.mEventType == EnumDefine::EventType::WEIGHT_NORMAL_TYPE
       ||event.mEventType == EnumDefine::EventType::WEIGHT_UNDER_WARNING_TYPE
       ||event.mEventType == EnumDefine::EventType::WEIGHT_OVER_WARNING_TYPE
       ||event.mEventType == EnumDefine::EventType::WEIGHT_UNDER_TYPE
       ||event.mEventType == EnumDefine::EventType::WEIGHT_OVER_TYPE
       ||event.mEventType == EnumDefine::EventType::WEIGHT_ETCERROR_TYPE
       ||event.mEventType == EnumDefine::EventType::WEIGHT_ETC_METAL_ERROR_TYPE)
    {
        QString fmt("%1%2");
        return fmt.arg(QString::number((float)event.mWeight / 1000.0, 'f', 1)).arg(" g");
    }
    else if(event.mEventType == EnumDefine::EventType::METAL_CHECKUP_TYPE)
    {
        return (event.mWeight & 0x01) == 0 ? "FAIL" : "PASS";
    }
    else if(event.mEventType == EnumDefine::EventType::METAL_TRADE_TYPE || event.mEventType == EnumDefine::EventType::METAL_DETECT_TYPE)
    {
        QString fmt("%1%2");
        return fmt.arg(QString::number(event.mWeight)).arg(" mv");
    }

    return "-   ";
}

void LoggingDataModel::onCommandSetSelect(int idx)
{
    setSelIdx(idx);
}

void LoggingDataModel::onCommandSetSelectOption(int value)
{
    if(EnumDefine::SearchOption::SEARCH_OPTION_TODAY == value)
    {
        setToday();
    }
    else
        setSelectOption(EnumDefine::SearchOption::SEARCH_OPTION_PERIOD);
}

void LoggingDataModel::onCommandSetSelectFilter(int value)
{
    setSelectFilter((EnumDefine::SearchFilter) value);
}

void LoggingDataModel::onCommandSetStartDate(int year, int month, int day, int hour)
{
    int maxDay = checkMaxDay(year, month);
    int calDay = maxDay < day ? maxDay : day;

    setStartYear(year);
    setStartMonth(month);
    setStartDay(calDay);
    setStartHour(hour);

    if((year > mEndYear) || (year == mEndYear && month > mEndMonth) || (year == mEndYear && month == mEndMonth && calDay > mEndDay) || (year == mEndYear && month == mEndMonth && calDay == mEndDay && hour > mEndHour))
    {
        setEndYear(year);
        setEndMonth(month);
        setEndDay(calDay);
        setEndHour(hour);
    }
}

void LoggingDataModel::onCommandSetEndDate(int year, int month, int day, int hour)
{
    int maxDay = checkMaxDay(year, month);
    int calDay = maxDay < day ? maxDay : day;

    setEndYear(year);
    setEndMonth(month);
    setEndDay(calDay);
    setEndHour(hour);

    if((year < mStartYear) || (year == mStartYear && month < mStartMonth) || (year == mStartYear && month == mStartMonth && calDay < mStartDay) || (year == mStartYear && month == mStartMonth && calDay == mStartDay && hour < mStartHour))
    {
        setStartYear(year);
        setStartMonth(month);
        setStartDay(calDay);
        setStartHour(hour);
    }
}

void LoggingDataModel::onCommandMovePage(quint64 pageIdx)
{
    setCurrentPageIdx(pageIdx);

    setSearching(true);

    if(mThread != nullptr)
    {
        mThread->quit();
        mThread->wait();
        delete mThread;

        mThread = nullptr;
    }

    mThread = QThread::create(LoggingDataModel::procSearchResult);

    connect(mThread, SIGNAL(finished()), this, SLOT(onThreadFinish()));
    mThread->start();
}

void LoggingDataModel::onCommandSearch()
{
    setCurrentPageIdx(0);

    setSearching(true);

    if(mThread != nullptr)
    {
        mThread->quit();
        mThread->wait();
        delete mThread;

        mThread = nullptr;
    }

    mThread = QThread::create(LoggingDataModel::procSearchResult);

    connect(mThread, SIGNAL(finished()), this, SLOT(onThreadFinish()));
    mThread->start();
}

void LoggingDataModel::onCommandResetStatistics()
{
    QDateTime now      = QDateTime::currentDateTime();
    quint64 lastEventSeq = DatabaseHelper::getInstance()->findLastEventSeq("DP_RESET_DB_CON");
    LocalSetting::getInstance()->setWorkStartSeq(now.date().year(), now.date().month(), now.date().day(), lastEventSeq);

    emit signalCommandResetStatistics();
}

int LoggingDataModel::checkMaxDay(int year, int month)
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

void LoggingDataModel::setToday()
{
    QDate date = QDate::currentDate();

    setSelectOption(EnumDefine::SearchOption::SEARCH_OPTION_TODAY);
    setStartYear(date.year());
    setStartMonth(date.month());
    setStartDay(date.day());
    setStartHour(0);
    setEndYear(date.year());
    setEndMonth(date.month());
    setEndDay(date.day());
    setEndHour(23);
}


void LoggingDataModel::clearListEvent()
{
    mMutex.lock();

    mListEvent.clear();

    mMutex.unlock();
}

void LoggingDataModel::procSearchResult()
{
    QList<Event> listEvent = DatabaseHelper::getInstance()->findAllEventByPeriod("LOGGINGDATA_DB_CON", mSelectFilter == EnumDefine::SearchFilter::SEARCH_FILTER_TOTAL, mIsWeightEvent, mStartYear, mStartMonth, mStartDay, mStartHour, mEndYear, mEndMonth , mEndDay, mEndHour, EVENT_LIST_CNT_PER_PAGE, mCurrentPageIdx, &mTotalCnt, &mTotalPage);

    clearListEvent();

    mMutex.lock();

    for(int i = 0; i < listEvent.size(); i ++)
    {
        mListEvent.append(listEvent.at(i));
    }

    mMutex.unlock();
}

void LoggingDataModel::onThreadFinish()
{
    setTotalCnt(mTotalCnt);
    setTotalPage(mTotalPage);
    setSearching(false);
    setSelIdx(-1);
    emit signalEventCompletedSearch();
}



