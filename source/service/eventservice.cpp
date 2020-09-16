#include "eventservice.h"
#include <QApplication>
#include <QDateTime>
#include <QDebug>

#define PROC_SETTIG_PATH_LAST_DATETIME "lasttime/lasttime"
#define PROC_SETTIG_PATH_LAST_STARTDATE "lasttime/laststartdate"

void EventService::init(ProductSettingService * ps)
{
    qDebug() << "[EventService::init]";

    QString today = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    mLastEventYear  = today.split("-")[0].toInt();
    mLastEventMonth = today.split("-")[1].toInt();
    mLastEventDay   = today.split("-")[2].toInt();

    mProductStatisticsFileName = QString("%1-PS").arg(today);
    mProductHistoryFileName    = QString("%1-PH").arg(today);
    mEventHistoryFileName      = QString("%1-EH").arg(today);

    mTodayProductStatisticsWriter.close();
    mTodayProductHistoryWriter.close();
    mTodayEventHistoryWriter.close();

    for(int i = 0; i < mListProductStatistics.size(); i++)
    {
        delete mListProductStatistics.at(i);
    }
    mListProductStatistics.clear();

    for(int i = 0; i < mListProductHistory.size(); i++)
    {
        delete mListProductHistory.at(i);
    }
    mListProductHistory.clear();

    mpProductSettingService = ps;

    FileReader fr;
    QStringList lines = fr.readAll(mDailyHistoryPath, mProductStatisticsFileName);

    for(int i = 0; i < lines.size(); i ++)
    {
        loadProductStatistics(lines.at(i));
    }

    lines = fr.readAll(mDailyHistoryPath, mProductHistoryFileName);

    for(int i = 0; i < lines.size(); i ++)
    {
        loadProductHistory(lines.at(i));
    }

    for(int i = 0; i < mpProductSettingService->mListProductSetting.size(); i ++)
    {
        ProductSettingModel *pProductSetting = mpProductSettingService->mListProductSetting.at(i);
        ProductStatistics * pProductStatistics = findProductStatistics(pProductSetting->mSeq);

        if(pProductStatistics == nullptr)
        {
            addProductSetting(pProductSetting);
        }
    }

    selectProductSetting(&mpProductSettingService->mCurrentProductSetting);
}

void EventService::loadProductStatistics(QString content)
{
    qDebug() << "[EventService::onSignalEventLoadedLineProductStatistics]" << content;

    ProductStatistics * pProductStatistics = new ProductStatistics(this);
    pProductStatistics->setStringValue(content);
    pProductStatistics->mFileLineIdx = mListProductStatistics.size();
    mListProductStatistics.append(pProductStatistics);
}

void EventService::loadProductHistory(QString content)
{
    qDebug() << "[EventService::onSignalEventLoadedLineProductHistory]" << content;

    ProductSettingModel * pProductSetting = new ProductSettingModel(this);
    pProductSetting->setStringValue(content,",");
    mListProductHistory.append(pProductSetting);
}

void EventService::addEvent(quint64 dspSeq, quint16 eventType, quint32 value)
{
    EventModel * event = new EventModel(this);
    QDate currDate = QDateTime::currentDateTime().date();

    event->createEvent(dspSeq, mpCurrentProductStatistics->mProductSettingSeq, mListProductHistory.size() - 1, eventType, value);

    if(currDate.year() != mLastEventYear || currDate.month() != mLastEventMonth || currDate.day() != mLastEventDay)
    {
        init(mpProductSettingService);
    }

    if(mpCurrentProductStatistics != nullptr)
    {
        switch(eventType)
        {
        case EnumDefine::EventType::WEIGHT_NORMAL_TYPE         : mpCurrentProductStatistics->mNormalCnt      ++; break;
        case EnumDefine::EventType::WEIGHT_UNDER_WARNING_TYPE  : mpCurrentProductStatistics->mUnderWarningCnt++; break;
        case EnumDefine::EventType::WEIGHT_OVER_WARNING_TYPE   : mpCurrentProductStatistics->mOverWarningCnt ++; break;
        case EnumDefine::EventType::WEIGHT_UNDER_TYPE          : mpCurrentProductStatistics->mUnderCnt       ++; break;
        case EnumDefine::EventType::WEIGHT_OVER_TYPE           : mpCurrentProductStatistics->mOverCnt        ++; break;
        case EnumDefine::EventType::WEIGHT_ETCERROR_TYPE       : mpCurrentProductStatistics->mEtcCnt         ++; break;
        case EnumDefine::EventType::METAL_TRADE_TYPE           : mpCurrentProductStatistics->mMDPassCnt      ++; break;
        case EnumDefine::EventType::METAL_DETECT_TYPE          : mpCurrentProductStatistics->mMDFailCnt      ++; break;
        case EnumDefine::EventType::WEIGHT_ETC_METAL_ERROR_TYPE: mpCurrentProductStatistics->mWCMDFailCnt    ++; break;
        }
    }
    else
    {
        qDebug() << "[EventService::addEvent]not set current product statistics";
    }

    if(eventType == EnumDefine::EventType::APP_EXIT_TYPE)
    {
        if(mLastTime == "")
            return;

        event->mDateTime = mLastTime;

        QString date = mLastTime.split(" ")[0];
        QString fileName = QString("%1-%2-%3-EH").arg(date.split("/")[0]).arg(date.split("/")[1]).arg(date.split("/")[2]);

        if(fileName != mEventHistoryFileName)
        {
            FileWriter fw;
            fw.appendLine(mDailyHistoryPath,fileName,event->toString());
            return;
        }
    }
    else
    {
        mpSettings->setValue(PROC_SETTIG_PATH_LAST_DATETIME, event->mDateTime);
    }

    mTodayProductStatisticsWriter.overWriteLine(mDailyHistoryPath, mProductStatisticsFileName, mpCurrentProductStatistics->toString(), 500 * mpCurrentProductStatistics->mFileLineIdx, 500);
    mTodayEventHistoryWriter.appendLine(mDailyHistoryPath, mEventHistoryFileName, event->toString());
    mWorkingEventHistoryWriter.appendLine(mWorkingEventHistoryPath, mWorkingEventHistoryFileName,event->toString());

    delete event;
}

void EventService::addProductHistory(ProductSettingModel * pProductSetting)
{
    qDebug() << "[EventService::addProductHistory]";

    ProductSettingModel * temp = new ProductSettingModel(this);
    *temp = pProductSetting;
    mListProductHistory.append(temp);

    // file write
    mTodayProductHistoryWriter.appendLine(mDailyHistoryPath, mProductHistoryFileName,temp->toString(","));
}

void EventService::addProductSetting(ProductSettingModel * pProductSetting)
{
    qDebug() << "[EventService::addProductSetting]";

    ProductStatistics * pProductStatistics = new ProductStatistics(this);
    pProductStatistics->mProductSettingSeq = pProductSetting->mSeq;

    pProductStatistics->mFileLineIdx = mListProductStatistics.size();
    mListProductStatistics.append(pProductStatistics);

    // file write
    mTodayProductStatisticsWriter.overWriteLine(mDailyHistoryPath, mProductStatisticsFileName, pProductStatistics->toString(), 500 * pProductStatistics->mFileLineIdx, 500);
}

void EventService::editProductSetting(ProductSettingModel * pProductSetting)
{
    qDebug() << "[EventService::editProductSetting]";

    if(pProductSetting->mSeq == mpCurrentProductStatistics->mProductSettingSeq)
    {
        addProductHistory(pProductSetting);
    }
}

void EventService::selectProductSetting(ProductSettingModel * pProductSetting)
{
    qDebug() << "[EventService::selectProductSetting]";

    mpCurrentProductStatistics = findProductStatistics(pProductSetting->mSeq);

    if(mpCurrentProductStatistics == nullptr)
    {
        qDebug() << "[EventService::selectProductSetting]can not found ProductStatistics";
        return;
    }
    addProductHistory(pProductSetting);
}

void EventService::setLastDateTime(QString dateTime)
{
    mpSettings->setValue(PROC_SETTIG_PATH_LAST_DATETIME, dateTime);
}
void EventService::factoryReset()
{
    qDebug() << "[EventService::factoryReset]";
    mpSettings->clear();
    mTodayProductStatisticsWriter.close();
    mTodayProductHistoryWriter.close();
    mTodayEventHistoryWriter.close();
    mWorkingEventHistoryWriter.close();
    QDir(mDailyHistoryPath).removeRecursively();
}

void EventService::workReset()
{
    qDebug() << "[EventService::workReset]";
    mWorkingEventHistoryWriter.close();
    QDir(mWorkingEventHistoryPath).removeRecursively();
}

ProductStatistics * EventService::findProductStatistics(quint64 productSettingSeq)
{
    for(int i = 0; i < mListProductStatistics.size(); i ++)
    {
        ProductStatistics * pProductStatistics = mListProductStatistics.at(i);

        if(pProductStatistics->mProductSettingSeq == productSettingSeq)
            return pProductStatistics;
    }

    return nullptr;
}

bool EventService::isWorkingContiune()
{
    return mIsWorkingContinue;
}

EventService::EventService(QObject *parent) : QObject(parent)
{
    qDebug() << "[EventService::Create]";
    QString today = QDateTime::currentDateTime().date().toString("yyyy/MM/dd");
    QString applicationPath = QApplication::applicationDirPath();

    mpSettings = new QSettings("novasen", "WCMD_LASTTIME", this);
    mLastTime = mpSettings->value(PROC_SETTIG_PATH_LAST_DATETIME, "").toString();
    mLastStartDate = mpSettings->value(PROC_SETTIG_PATH_LAST_STARTDATE, "").toString();

    mpSettings->setValue(PROC_SETTIG_PATH_LAST_STARTDATE, today);

    mDailyHistoryPath               = QString("%1/database/history"        ).arg(applicationPath);
    mWorkingEventHistoryPath        = QString("%1/database/history/working").arg(applicationPath);

    mWorkingEventHistoryFileName    = QString("WORKING-EH");

    if(mLastStartDate == today)
        mIsWorkingContinue = true;
}
