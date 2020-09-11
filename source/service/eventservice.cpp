#include "eventservice.h"
#include <QApplication>
#include <QDateTime>
#include <QDebug>

#define PROC_SETTIG_PATH_LAST_DATETIME "lasttime/lasttime"

void EventService::init(ProductSettingService * ps)
{
    qDebug() << "[EventService::init]";

    mpProductSettingService = ps;
    emit signalCommandProductStatisticsLoadLine(mTodayProductStatisticsPath, mTodayProductStatisticsFileName);
}

void EventService::onSignalEventLoadedLineProductStatistics(QString content)
{
    qDebug() << "[EventService::onSignalEventLoadedLineProductStatistics]" << content;

    ProductStatistics * pProductStatistics = new ProductStatistics(this);
    pProductStatistics->setStringValue(content);
    pProductStatistics->mFileLineIdx = mListProductStatistics.size();
    mListProductStatistics.append(pProductStatistics);

    emit signalCommandProductStatisticsLoadLine(mTodayProductStatisticsPath, mTodayProductStatisticsFileName);
}

void EventService::onSignalEventEndOfLineProductStatistics()
{
    emit signalCommandProductHistoryLoadLine(mTodayProductHistoryPath, mTodayProductHistoryFileName);
}

void EventService::onSignalEventLoadedLineProductHistory(QString content)
{
    qDebug() << "[EventService::onSignalEventLoadedLineProductHistory]" << content;

    ProductSettingModel * pProductSetting = new ProductSettingModel(this);
    pProductSetting->setStringValue(content,",");
    mListProductHistory.append(pProductSetting);

    emit signalCommandProductHistoryLoadLine(mTodayProductHistoryPath, mTodayProductHistoryFileName);
}

void EventService::onSignalEventEndOfLineProductHistory()
{
    for(int i = 0; i < mpProductSettingService->mListProductSetting.size(); i ++)
    {
        ProductSettingModel *pProductSetting = mpProductSettingService->mListProductSetting.at(i);
        ProductStatistics * pProductStatistics = findProductStatistics(pProductSetting->mSeq);

        if(pProductStatistics == nullptr)
        {
            addProductSetting(pProductSetting);
        }
    }

    emit signalEventCompleteInit();
}

void EventService::addEvent(quint64 dspSeq, quint16 eventType, quint32 value)
{
    EventModel event;
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

    event.createEvent(dspSeq, mpCurrentProductStatistics->mProductSettingSeq, mListProductHistory.size() - 1, eventType, value);

    if(eventType == EnumDefine::EventType::APP_EXIT_TYPE)
    {
        if(mLastTime == "")
            return;

        event.mDateTime = mLastTime;
    }
    else
    {
        mpSettings->setValue(PROC_SETTIG_PATH_LAST_DATETIME, event.mDateTime);
    }

    // file write
    mTodayProductStatisticsWriter.overWriteLine(mTodayProductStatisticsPath, mTodayProductStatisticsFileName, mpCurrentProductStatistics->toString(), 500 * mpCurrentProductStatistics->mFileLineIdx, 500);
    mTodayEventHistoryWriter.appendLine(mTodayEventHistoryPath, mTodayEventHistoryFileName, event.toString());
    mWorkingEventHistoryWriter.appendLine(mWorkingEventHistoryPath, mWorkingEventHistoryFileName,event.toString());
}

void EventService::addProductHistory(ProductSettingModel * pProductSetting)
{
    qDebug() << "[EventService::addProductHistory]";

    ProductSettingModel * temp = new ProductSettingModel(this);
    *temp = pProductSetting;
    mListProductHistory.append(temp);

    // file write
    mTodayProductHistoryWriter.appendLine(mTodayProductHistoryPath, mTodayProductHistoryFileName,temp->toString(","));
}

void EventService::addProductSetting(ProductSettingModel * pProductSetting)
{
    qDebug() << "[EventService::addProductSetting]";

    ProductStatistics * pProductStatistics = new ProductStatistics(this);
    pProductStatistics->mProductSettingSeq = pProductSetting->mSeq;

    pProductStatistics->mFileLineIdx = mListProductStatistics.size();
    mListProductStatistics.append(pProductStatistics);

    // file write
    mTodayProductStatisticsWriter.overWriteLine(mTodayProductStatisticsPath, mTodayProductStatisticsFileName, pProductStatistics->toString(), 500 * pProductStatistics->mFileLineIdx, 500);
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
    QDir(mTodayProductStatisticsPath).removeRecursively();
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

EventService::EventService(QObject *parent) : QObject(parent)
{
    qDebug() << "[EventService::Create]";

    QString today = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString applicationPath = QApplication::applicationDirPath();


    mpSettings = new QSettings("novasen", "WCMD_LASTTIME", this);
    mLastTime = mpSettings->value(PROC_SETTIG_PATH_LAST_DATETIME, "").toString();

    mTodayProductStatisticsPath     = QString("%1/database/history"        ).arg(applicationPath);
    mTodayProductHistoryPath        = QString("%1/database/history"        ).arg(applicationPath);
    mTodayEventHistoryPath          = QString("%1/database/history"        ).arg(applicationPath);
    mWorkingEventHistoryPath        = QString("%1/database/history/working").arg(applicationPath);
    mTodayProductStatisticsFileName = QString("%1-PS").arg(today);
    mTodayProductHistoryFileName    = QString("%1-PH").arg(today);
    mTodayEventHistoryFileName      = QString("%1-EH").arg(today);
    mWorkingEventHistoryFileName    = QString("%1-EH").arg(today);

    connect(this, SIGNAL(signalCommandProductStatisticsLoadLine(QString, QString)), &mTodayProductStatisticsLoader, SLOT(onCommandLoadLine(QString, QString)));
    connect(this, SIGNAL(signalCommandProductHistoryLoadLine   (QString, QString)), &mTodayProductHistoryLoader   , SLOT(onCommandLoadLine(QString, QString)));

    connect(&mTodayProductStatisticsLoader, SIGNAL(signalEventLoadedLine(QString)), this, SLOT(onSignalEventLoadedLineProductStatistics(QString)));
    connect(&mTodayProductStatisticsLoader, SIGNAL(signalEventEndOfLine (       )), this, SLOT(onSignalEventEndOfLineProductStatistics (       )));
    connect(&mTodayProductHistoryLoader   , SIGNAL(signalEventLoadedLine(QString)), this, SLOT(onSignalEventLoadedLineProductHistory   (QString)));
    connect(&mTodayProductHistoryLoader   , SIGNAL(signalEventEndOfLine (       )), this, SLOT(onSignalEventEndOfLineProductHistory    (       )));
}
