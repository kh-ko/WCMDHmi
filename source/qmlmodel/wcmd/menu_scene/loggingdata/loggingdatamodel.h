#ifndef LOGGINGDATAMODEL_H
#define LOGGINGDATAMODEL_H

#include <QObject>
#include <QThread>
#include <QMutex>

#include "source/globaldef/qmlenumdef.h"
#include "source/service/coreservice.h"
#include "source/util/etcutil.h"

#define EVENT_PAGE_CNT_PER_SCREEN 9
#define EVENT_LIST_CNT_PER_PAGE 26

class LoggingDataItem
{
public:
    QString mDateTime;
    quint64 mProductSeq;
    int     mEventType;
    quint32 mValue;
};

class LoggingDataModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int     totalCnt       READ getTotalCnt                                    NOTIFY signalEventChangedTotalCnt)
    Q_PROPERTY(int     totalPage      READ getTotalPage                                   NOTIFY signalEventChangedTotalPage)
    Q_PROPERTY(int     currentPageIdx READ getCurrentPageIdx                              NOTIFY signalEventChangedCurrentPageIdx)
    Q_PROPERTY(bool    isWeightEvent  READ getIsWeightEvent       WRITE setIsWeightEvent  NOTIFY signalEventChangedIsWeightEvent)
    Q_PROPERTY(int     selectFilter   READ getSelectFilter                                NOTIFY signalEventChangedSelectFilter)
    Q_PROPERTY(int     startYear      READ getStartYear                                   NOTIFY signalEventChangedStartYear)
    Q_PROPERTY(int     startMonth     READ getStartMonth                                  NOTIFY signalEventChangedStartMonth)
    Q_PROPERTY(int     startDay       READ getStartDay                                    NOTIFY signalEventChangedStartDay)
    Q_PROPERTY(bool    searching      READ getSearching                                   NOTIFY signalEventChangedSearching)
    Q_PROPERTY(int     setIdx         READ getSelIdx                                      NOTIFY signalEventChangedSelIdx)

public:
    QThread       *mpLoaderThread = nullptr;
    FileReaderEx  *mpFileLoader   = nullptr;

    QString mFileName;
    LoggingDataItem  mListItem[1000000];

    int         mTotalCnt      ;
    int         mTotalPage     ;
    int         mCurrentPageIdx;
    bool        mIsWeightEvent ;
    int         mSelectOption  ;
    int         mSelectFilter  ;
    int         mStartYear     ;
    int         mStartMonth    ;
    int         mStartDay      ;
    int         mStartHour     ;
    int         mEndYear       ;
    int         mEndMonth      ;
    int         mEndDay        ;
    int         mEndHour       ;
    bool        mSearching     ;
    int         mSelIdx        ;

    int         getTotalCnt      (){return mTotalCnt      ;}
    int         getTotalPage     (){return mTotalPage     ;}
    int         getCurrentPageIdx(){return mCurrentPageIdx;}
    bool        getIsWeightEvent (){return mIsWeightEvent ;}
    int         getSelectFilter  (){return mSelectFilter  ;}
    int         getStartYear     (){return mStartYear     ;}
    int         getStartMonth    (){return mStartMonth    ;}
    int         getStartDay      (){return mStartDay      ;}
    bool        getSearching     (){return mSearching     ;}
    int         getSelIdx        (){return mSelIdx        ;}

    void        setTotalCnt      (int     value){ mTotalCnt       = value; emit signalEventChangedTotalCnt      (mTotalCnt      );}
    void        setTotalPage     (int     value){ mTotalPage      = value; emit signalEventChangedTotalPage     (mTotalPage     );}
    void        setCurrentPageIdx(int     value){ mCurrentPageIdx = value; emit signalEventChangedCurrentPageIdx(mCurrentPageIdx);}
    void        setIsWeightEvent (bool    value){ mIsWeightEvent  = value; emit signalEventChangedIsWeightEvent (mIsWeightEvent );}
    void        setSelectFilter  (int     value){ mSelectFilter   = value; emit signalEventChangedSelectFilter  (mSelectFilter  );}
    void        setStartYear     (int     value){ mStartYear      = value; emit signalEventChangedStartYear     (mStartYear     );}
    void        setStartMonth    (int     value){ mStartMonth     = value; emit signalEventChangedStartMonth    (mStartMonth    );}
    void        setStartDay      (int     value){ mStartDay       = value; emit signalEventChangedStartDay      (mStartDay      );}
    void        setSearching     (bool    value){ mSearching      = value; emit signalEventChangedSearching     (mSearching     );}
    void        setSelIdx        (int     value){ mSelIdx         = value; emit signalEventChangedSelIdx        (mSelIdx        );}

signals:
    void signalEventChangedTotalCnt(int value);
    void signalEventChangedTotalPage(int value);
    void signalEventChangedCurrentPageIdx(int value);
    void signalEventChangedIsWeightEvent(bool value);
    void signalEventChangedSelectFilter(int value);
    void signalEventChangedStartYear( int value );
    void signalEventChangedStartMonth( int value );
    void signalEventChangedStartDay( int value );
    void signalEventChangedSearching(bool value);
    void signalEventChangedSelIdx(int value);
    void signalEventCompletedSearch();

public slots:
    Q_INVOKABLE void onCommandMovePage(int pageNum)
    {
        setCurrentPageIdx(pageNum);
        emit signalEventCompletedSearch();
    }
    Q_INVOKABLE void onCommandSearch()
    {
        setSearching(true);
        setTotalCnt(0);
        setTotalPage(0);
        setCurrentPageIdx(0);

        QString year  = QString::number(mStartYear).rightJustified(4, '0');
        QString monty = QString::number(mStartMonth).rightJustified(2, '0');
        QString day   = QString::number(mStartDay).rightJustified(2, '0');

        openFile(QString("%1-%2-%3-EH.txt").arg(year).arg(monty).arg(day));
        readFile();
    }
    Q_INVOKABLE void onCommandSetSelectFilter(int value)
    {
        setSelectFilter((QmlEnumDef::SearchFilter) value);
    }
    Q_INVOKABLE void onCommandSetStartDate(int year, int month, int day)
    {
        int maxDay = EtcUtil::checkMaxDay(year, month);
        int calDay = maxDay < day ? maxDay : day;

        setStartYear(year);
        setStartMonth(month);
        setStartDay(calDay);
    }
    Q_INVOKABLE int onCommandGetListCnt()
    {
        int lastIdx = getTotalCnt();
        int startIdx = getCurrentPageIdx() * EVENT_LIST_CNT_PER_PAGE;

        if(lastIdx - startIdx >= EVENT_LIST_CNT_PER_PAGE)
            return EVENT_LIST_CNT_PER_PAGE;
        else
            return lastIdx - startIdx;
    }
    Q_INVOKABLE QString onCommandGetDateTimeItem(int idx)
    {
        if(idx > getTotalCnt() - 1 || idx < 0)
            return "";

        int listIdx =  (getTotalCnt() - 1) - ((getCurrentPageIdx() * EVENT_LIST_CNT_PER_PAGE) + idx);

        return mListItem[listIdx].mDateTime;
    }
    Q_INVOKABLE QString onCommandGetProductItem(int idx)
    {
        if(idx > getTotalCnt() - 1 || idx < 0)
            return "";

        int listIdx =  (getTotalCnt() - 1) - ((getCurrentPageIdx() * EVENT_LIST_CNT_PER_PAGE) + idx);

        quint16 eventType = mListItem[listIdx].mEventType;

        PDSettingDto *pPDSetting = pProductSP->findPD(mListItem[listIdx].mProductSeq);

        if(pPDSetting == nullptr || (!EventDto::isWeightOrMetal(eventType) && !EventDto::isWeightCarib(eventType) && !EventDto::isMetalCheckup(eventType)))
            return "";

        return pPDSetting->mName;
    }
    Q_INVOKABLE int onCommandGetEventItem(int idx)
    {
        if(idx > getTotalCnt() - 1 || idx < 0)
            return EnumDef::ET_NONE;

        int listIdx =  (getTotalCnt() - 1) - ((getCurrentPageIdx() * EVENT_LIST_CNT_PER_PAGE) + idx);

        return mListItem[listIdx].mEventType;
    }
    Q_INVOKABLE QString onCommandGetWeightItem(int idx)
    {
        if(idx > getTotalCnt() - 1 || idx < 0)
            return "";

        int listIdx =  (getTotalCnt() - 1) - ((getCurrentPageIdx() * EVENT_LIST_CNT_PER_PAGE) + idx);

        quint16 eventType = mListItem[listIdx].mEventType;

        if(EventDto::isWCEvent(eventType))
        {
            QString fmt("%1%2");
            return fmt.arg(QString::number((float)mListItem[listIdx].mValue / 1000.0, 'f', 1)).arg(" g");
        }
        else if(EventDto::isMetalCheckup(eventType))
        {
            return (mListItem[listIdx].mValue & (0x01 << 6)) == 0 ? "FAIL" : "PASS";
        }
        else if(EventDto::isMetalDetectEvent(eventType))
        {
            QString fmt("%1%2");
            return fmt.arg(QString::number(mListItem[listIdx].mValue)).arg(" mv");
        }

        return "-   ";
    }
    Q_INVOKABLE void    onCommandSetSelect(int idx)
    {
        setSelIdx(idx);
    }
    Q_INVOKABLE void    onCommandResetStatistics()
    {
        pWorkSP->clearStats();
    }

signals:
    void signalCommandOpen(QString path, QString fileName);
    void signalCommandReadMultiLine(int lineCnt);

public  slots:
    void onReadMultiLine(QStringList lines)
    {
        if(sender() == nullptr)
            return;

        for(int i = 0; i < lines.size(); i ++)
        {
            if(mTotalCnt > 999999)
                break;

            EventDto event;
            if(event.setValue(lines.at(i)) == false)
                continue;

            if(event.isCheckEvent())
                continue;

            if(getIsWeightEvent() && (event.isMDEvent() || event.isMetalCheckup()))
                continue;

            if(!getIsWeightEvent() && (event.isWCEvent() || event.isWeightCarib()))
                continue;

            if(getSelectFilter() == QmlEnumDef::SearchFilter::SEARCH_FILTER_WITHOUT_TRADE && event.isTrade())
                continue;

             mListItem[getTotalCnt()].mDateTime     = event.mDateTime.toString(TIME_FMT);
             mListItem[getTotalCnt()].mProductSeq   = event.mPDSeq;
             mListItem[getTotalCnt()].mEventType    = event.mEType;
             mListItem[getTotalCnt()].mValue        = event.mEValue;

             mTotalCnt = mTotalCnt + 1;
        }

        setTotalCnt(mTotalCnt);

        if(lines.size() < 3000)
        {
            setTotalPage((getTotalCnt()/EVENT_LIST_CNT_PER_PAGE) + (getTotalCnt()%EVENT_LIST_CNT_PER_PAGE != 0 ? 1 : 0));
            setSearching(false);
            closeFile();
            emit signalEventCompletedSearch();
        }
        else
        {
            readFile();
        }
    }

public:
    explicit    LoggingDataModel(QObject *parent = nullptr):QObject(parent)
    {
        QDate date = QDate::currentDate();

        setSelectFilter(QmlEnumDef::SearchFilter::SEARCH_FILTER_WITHOUT_TRADE);

        setStartYear(date.year());
        setStartMonth(date.month());
        setStartDay(date.day());

        onCommandSearch();
    }
    ~LoggingDataModel(){
        closeFile();
    }

private:
    void openFile(QString fileName)
    {
        closeFile();

        mpLoaderThread = new QThread;
        mpFileLoader   = new FileReaderEx;
        mpFileLoader->moveToThread(mpLoaderThread);
        mpLoaderThread->start();

        connect(mpLoaderThread, &QThread::finished, mpFileLoader, &QObject::deleteLater);
        connect(this, SIGNAL(signalCommandOpen(QString, QString)), mpFileLoader, SLOT(onCommandOpen(QString, QString)));
        connect(this, SIGNAL(signalCommandReadMultiLine(int)), mpFileLoader, SLOT(onCommandReadMultiLine(int)));
        connect(mpFileLoader, SIGNAL(signalEventReadMultiLine(QStringList)), this, SLOT(onReadMultiLine(QStringList)));

        emit signalCommandOpen(FileDef::HISTORY_DIR(), fileName);
    }

    void closeFile()
    {
        if(mpFileLoader != nullptr)
        {

            disconnect(this, SIGNAL(signalCommandOpen(QString, QString)), mpFileLoader, SLOT(onCommandOpen(QString, QString)));
            disconnect(this, SIGNAL(signalCommandReadMultiLine(int)), mpFileLoader, SLOT(onCommandReadMultiLine(int)));
            disconnect(mpFileLoader, nullptr, nullptr, nullptr);
            mpFileLoader= nullptr;
        }

        if(mpLoaderThread != nullptr)
        {
            if(mpLoaderThread->isRunning())
            {
                mpLoaderThread->quit();
                mpLoaderThread->wait();
            }

            mpLoaderThread->deleteLater();

            mpLoaderThread = nullptr;
        }
    }

    void readFile()
    {
        emit signalCommandReadMultiLine(3000);
    }
};

#endif // LOGGINGDATAMODEL_H
