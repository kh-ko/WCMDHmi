#ifndef LOGGINGDATAMODEL_H
#define LOGGINGDATAMODEL_H

#include <QObject>
#include <QThread>
#include <QMutex>

#include "source/globaldef/EnumDefine.h"

class LoggingDataModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint64 totalCnt                     READ getTotalCnt                                    NOTIFY signalEventChangedTotalCnt)
    Q_PROPERTY(quint64 totalPage                    READ getTotalPage                                   NOTIFY signalEventChangedTotalPage)
    Q_PROPERTY(quint64 currentPageIdx               READ getCurrentPageIdx                              NOTIFY signalEventChangedCurrentPageIdx)
    Q_PROPERTY(bool isWeightEvent                   READ getIsWeightEvent       WRITE setIsWeightEvent  NOTIFY signalEventChangedIsWeightEvent)
    Q_PROPERTY(int selectOption                     READ getSelectOption                                NOTIFY signalEventChangedSelectOption)
    Q_PROPERTY(int selectFilter                     READ getSelectFilter                                NOTIFY signalEventChangedSelectFilter)
    Q_PROPERTY(int startYear                        READ getStartYear                                   NOTIFY signalEventChangedStartYear)
    Q_PROPERTY(int startMonth                       READ getStartMonth                                  NOTIFY signalEventChangedStartMonth)
    Q_PROPERTY(int startDay                         READ getStartDay                                    NOTIFY signalEventChangedStartDay)
    Q_PROPERTY(int startHour                        READ getStartHour                                   NOTIFY signalEventChangedStartHour)
    Q_PROPERTY(int endYear                          READ getEndYear                                     NOTIFY signalEventChangedEndYear)
    Q_PROPERTY(int endMonth                         READ getEndMonth                                    NOTIFY signalEventChangedEndMonth)
    Q_PROPERTY(int endDay                           READ getEndDay                                      NOTIFY signalEventChangedEndDay)
    Q_PROPERTY(int endHour                          READ getEndHour                                     NOTIFY signalEventChangedEndHour)
    Q_PROPERTY(bool searching                       READ getSearching                                   NOTIFY signalEventChangedSearching)
    Q_PROPERTY(int  setIdx                          READ getSelIdx                                      NOTIFY signalEventChangedSelIdx)


public:
    explicit    LoggingDataModel(QObject *parent = nullptr):QObject(parent){}
    quint64     getTotalCnt()      {return 0;}
    quint64     getTotalPage()     {return 0;}
    quint64     getCurrentPageIdx(){return 0;}
    bool        getIsWeightEvent() {return 0;}
    int         getSelectOption()  {return 0;}
    int         getSelectFilter()  {return 0;}
    int         getStartYear()     {return 0;}
    int         getStartMonth()    {return 0;}
    int         getStartDay()      {return 0;}
    int         getStartHour()     {return 0;}
    int         getEndYear()       {return 0;}
    int         getEndMonth()      {return 0;}
    int         getEndDay()        {return 0;}
    int         getEndHour()       {return 0;}
    bool        getSearching()     {return 0;}
    int         getSelIdx()        {return 0;}

    void        setTotalCnt(quint64 value)                     {}
    void        setTotalPage(quint64 value)                    {}
    void        setCurrentPageIdx(quint64 value)               {}
    void        setIsWeightEvent(bool value)                   {}
    void        setSelectOption(EnumDefine::SearchOption value){}
    void        setSelectFilter(EnumDefine::SearchFilter value){}
    void        setStartYear(int value)                        {}
    void        setStartMonth(int value)                       {}
    void        setStartDay(int value)                         {}
    void        setStartHour(int value)                        {}
    void        setEndYear(int value)                          {}
    void        setEndMonth(int value)                         {}
    void        setEndDay(int value)                           {}
    void        setEndHour(int value)                          {}
    void        setSearching(bool value)                       {}
    void        setSelIdx(int value)                           {}

public:
    Q_INVOKABLE void onCommandMovePage(quint64 pageNum)                           {}
    Q_INVOKABLE void onCommandSearch()                                            {}
    Q_INVOKABLE void onCommandSetSelectOption(int value)                          {}
    Q_INVOKABLE void onCommandSetSelectFilter(int value)                          {}
    Q_INVOKABLE void onCommandSetStartDate(int year, int month, int day, int hour){}
    Q_INVOKABLE void onCommandSetEndDate(int year, int month, int day, int hour)  {}
    Q_INVOKABLE int onCommandGetListCnt()                                         {return 0;}
    Q_INVOKABLE QString onCommandGetDateTimeItem(int idx)                         {return "";}
    Q_INVOKABLE QString onCommandGetProductItem(int idx)                          {return "";}
    Q_INVOKABLE int onCommandGetEventItem(int idx)                                {return 0;}
    Q_INVOKABLE QString onCommandGetWeightItem(int idx)                           {return "";}
    Q_INVOKABLE void onCommandSetSelect(int idx)                                  {}
    Q_INVOKABLE void onCommandResetStatistics()                                   {}

signals:
    void signalEventChangedTotalCnt(quint64 value);
    void signalEventChangedTotalPage(quint64 value);
    void signalEventChangedCurrentPageIdx(quint64 value);
    void signalEventChangedIsWeightEvent(bool value);
    void signalEventChangedSelectOption(int value);
    void signalEventChangedSelectFilter(int value);
    void signalEventChangedStartYear( int value );
    void signalEventChangedStartMonth( int value );
    void signalEventChangedStartDay( int value );
    void signalEventChangedStartHour( int value );
    void signalEventChangedEndYear( int value );
    void signalEventChangedEndMonth( int value );
    void signalEventChangedEndDay( int value );
    void signalEventChangedEndHour( int value );
    void signalEventChangedSearching(bool value);
    void signalEventChangedSelIdx(int value);
    void signalEventCompletedSearch();

};

#endif // LOGGINGDATAMODEL_H
