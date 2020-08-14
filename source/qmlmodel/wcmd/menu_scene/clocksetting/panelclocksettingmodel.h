#ifndef PANELCLOCKSETTINGMODEL_H
#define PANELCLOCKSETTINGMODEL_H
//PanelClockSettingModel

#include <QObject>
#include <QDateTime>
#include <QDebug>

class PanelClockSettingModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int year                        READ getYear                                   NOTIFY signalEventChangedYear  )
    Q_PROPERTY(int month                       READ getMonth                                  NOTIFY signalEventChangedMonth )
    Q_PROPERTY(int day                         READ getDay                                    NOTIFY signalEventChangedDay   )
    Q_PROPERTY(int hour                        READ getHour                                   NOTIFY signalEventChangedHour  )
    Q_PROPERTY(int min                         READ getMin                                    NOTIFY signalEventChangedMin   )
    Q_PROPERTY(int sec                         READ getSec                                    NOTIFY signalEventChangedSec   )

public:
    int mYear  ;
    int mMonth ;
    int mDay   ;
    int mHour  ;
    int mMin   ;
    int mSec   ;

    int checkMaxDay(int year, int month)
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

    explicit    PanelClockSettingModel(QObject *parent = nullptr):QObject(parent)
    {
        QDateTime date = QDateTime::currentDateTime();

        setYear (date.date().year  ());
        setMonth(date.date().month ());
        setDay  (date.date().day   ());
        setHour (date.time().hour  ());
        setMin  (date.time().minute());
        setSec  (date.time().second());

    }
    ~PanelClockSettingModel(){}
    int         getYear (){ return mYear ;}
    int         getMonth(){ return mMonth;}
    int         getDay  (){ return mDay  ;}
    int         getHour (){ return mHour ;}
    int         getMin  (){ return mMin  ;}
    int         getSec  (){ return mSec  ;}

    void        setYear (int value)
    {
        if(value == mYear ) return;

        mYear  = value;

        emit signalEventChangedYear (value);

        int maxDay = checkMaxDay(mYear, mMonth);
        int calDay = maxDay < mDay ? maxDay : mDay;

        setDay(calDay);
    }
    void        setMonth(int value)
    {
        if(value == mMonth) return;

        mMonth = value;

        emit signalEventChangedMonth(value);

        int maxDay = checkMaxDay(mYear, mMonth);
        int calDay = maxDay < mDay ? maxDay : mDay;

        setDay(calDay);
    }
    void        setDay  (int value)
    {
        if(value == mDay  ) return;

        mDay   = value;

        emit signalEventChangedDay  (value);

        int maxDay = checkMaxDay(mYear, mMonth);
        int calDay = maxDay < mDay ? maxDay : mDay;

        setDay(calDay);
    }
    void        setHour (int value){ if(value == mHour ) return; mHour  = value; emit signalEventChangedHour (value);}
    void        setMin  (int value){ if(value == mMin  ) return; mMin   = value; emit signalEventChangedMin  (value);}
    void        setSec  (int value){ if(value == mSec  ) return; mSec   = value; emit signalEventChangedSec  (value);}

signals:
    void signalEventChangedYear (int value);
    void signalEventChangedMonth(int value);
    void signalEventChangedDay  (int value);
    void signalEventChangedHour (int value);
    void signalEventChangedMin  (int value);
    void signalEventChangedSec  (int value);

public slots:
    Q_INVOKABLE void onCommandSetYear (int value){setYear (value);}
    Q_INVOKABLE void onCommandSetMonth(int value){setMonth(value);}
    Q_INVOKABLE void onCommandSetDay  (int value){setDay  (value);}
    Q_INVOKABLE void onCommandSetHour (int value){setHour (value);}
    Q_INVOKABLE void onCommandSetMin  (int value){setMin  (value);}
    Q_INVOKABLE void onCommandSetSec  (int value){setSec  (value);}
    Q_INVOKABLE void onCommandApply   (         )
    {
        QString cmd;

        cmd.sprintf("sudo date %02d%02d%02d%02d%04d.%02d", getMonth(), getDay(), getHour(), getMin(), getYear(), getSec());

        qDebug() << cmd;

        system(cmd.toStdString().c_str());

        cmd.sprintf("sudo hwclock -w");

        qDebug() << cmd;

        system(cmd.toStdString().c_str());
    }

};
#endif // PANELCLOCKSETTINGMODEL_H
