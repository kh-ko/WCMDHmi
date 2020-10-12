#ifndef EVENTSERVICE_H
#define EVENTSERVICE_H

#include <QObject>
#include <QSettings>
#include "source/service/productsettingservice.h"
#include "source/util/filereader.h"
#include "source/util/eventchecker.h"
#include "source/model/eventmodel.h"

class ProductStatistics: public QObject
{
    Q_OBJECT
public:
    int     mFileLineIdx = 0;

    quint64 mProductSettingSeq = 0;
    quint16 mProductNo         = 0;
    QString mProductName       = "";
    int     mUnderCnt          = 0;
    int     mUnderWarningCnt   = 0;
    int     mNormalCnt         = 0;
    int     mOverWarningCnt    = 0;
    int     mOverCnt           = 0;
    int     mEtcCnt            = 0;
    int     mWCMDFailCnt       = 0;
    int     mMDFailCnt         = 0;
    int     mMDPassCnt         = 0;

    void setStringValue(QString value)
    {
        QStringList listRow = value.split(",");

        for(int i = 0; i < listRow.size(); i++)
        {
            QString row = listRow.at(i);

            if(row.contains(":") == false)
                continue;

            QString key = row.split(":")[0];
            QString value = row.split(":")[1];

            if     (key == "ProdcutSettingSeq"){ mProductSettingSeq = value.toULongLong();}
            if     (key == "ProductName"      ){ mProductName       = value              ;}
            if     (key == "ProductNo"        ){ mProductNo         = value.toUInt()     ;}
            else if(key == "U"                ){ mUnderCnt          = value.toUInt()     ;}
            else if(key == "UW"               ){ mUnderWarningCnt   = value.toUInt()     ;}
            else if(key == "N"                ){ mNormalCnt         = value.toUInt()     ;}
            else if(key == "OW"               ){ mOverWarningCnt    = value.toUInt()     ;}
            else if(key == "O"                ){ mOverCnt           = value.toUInt()     ;}
            else if(key == "ETC"              ){ mEtcCnt            = value.toUInt()     ;}
            else if(key == "WC MD F"          ){ mWCMDFailCnt       = value.toUInt()     ;}
            else if(key == "MD F"             ){ mMDFailCnt         = value.toUInt()     ;}
            else if(key == "MD P"             ){ mMDPassCnt         = value.toUInt()     ;}
        }
    }

    QString toString(){
        return QString("ProdcutSettingSeq:%1,ProductName:%2,ProductNo:%3,U:%4,UW:%5,N:%6,OW:%7,O:%8,ETC:%9,WC MD F:%10,MD F:%11,MD P:%12")
                    .arg(mProductSettingSeq)
                    .arg(mProductName      )
                    .arg(mProductNo        )
                    .arg(mUnderCnt         )
                    .arg(mUnderWarningCnt  )
                    .arg(mNormalCnt        )
                    .arg(mOverWarningCnt   )
                    .arg(mOverCnt          )
                    .arg(mEtcCnt           )
                    .arg(mWCMDFailCnt      )
                    .arg(mMDFailCnt        )
                    .arg(mMDPassCnt        );
    }
    explicit ProductStatistics(QObject *parent = nullptr):QObject(parent){}

signals:
};

class EventService : public QObject
{
    Q_OBJECT
public:
    QSettings *             mpSettings = nullptr      ;
    bool                    mIsWorkingContinue = false;
    QString                 mLastTime                 ;
    QString                 mLastStartDate            ;
    int                     mLastEventYear            ;
    int                     mLastEventMonth           ;
    int                     mLastEventDay             ;
    QString                 mProductStatisticsFileName;
    QString                 mProductHistoryFileName   ;
    QString                 mEventHistoryFileName     ;
    ProductSettingService * mpProductSettingService;


    QString mDailyHistoryPath              ;
    QString mWorkingEventHistoryPath       ;
    QString mWorkingEventHistoryFileName   ;

    FileWriter mTodayProductStatisticsWriter;
    FileWriter mTodayProductHistoryWriter   ;
    FileWriter mTodayEventHistoryWriter     ;
    FileWriter mWorkingEventHistoryWriter   ;

    ProductStatistics *        mpCurrentProductStatistics = nullptr;
    QList<ProductStatistics *> mListProductStatistics;
    QList<ProductSettingModel *> mListProductHistory;

    void init(ProductSettingService * ps);
    void loadProductStatistics(QString content);
    void loadProductHistory(QString content);

    bool isWorkingContiune();
    void addEvent(quint64 dspSeq, quint16 eventType, quint32 value);
    void addProductHistory(ProductSettingModel * pProductSetting);
    void addProductSetting(ProductSettingModel * pProductSetting);
    void editProductSetting(ProductSettingModel * pProductSetting);
    void selectProductSetting(ProductSettingModel * pProductSetting);
    void setLastDateTime(QString dateTime);
    void factoryReset();
    void workReset();

//internal layer ==================================================
public:
    ProductStatistics * findProductStatistics(quint64 productSettingSeq);
    explicit EventService(QObject *parent = nullptr);

signals:

};

#endif // EVENTSERVICE_H
