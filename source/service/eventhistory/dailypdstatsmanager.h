#ifndef DAILYPDSTATSMANAGER_H
#define DAILYPDSTATSMANAGER_H

#include <QObject>
#include <QDateTime>
#include <QApplication>
#include "source/service/productsetting/productsprovider.h"
#include "source/service/def/filedef.h"
#include "source/service/def/datetimeform.h"
#include "source/service/util/filereaderex.h"
#include "source/service/util/filewriterex.h"

class PDStatsItem
{
public:
    int        mLineIdx = 0;
    PDStatsDto mStats;

    PDStatsItem(){}

    PDStatsItem(PDSettingDto setting,int lineIdx)
    {
        mStats.reset();

        mLineIdx     = lineIdx;
        mStats.mSeq  = setting.mSeq;
        mStats.mNum  = setting.mDspForm.mCommSetting.mProductNum;
        mStats.mName = setting.mName;
    }

    PDStatsItem(PDStatsDto stats,int fileIdx)
    {
        mLineIdx     = fileIdx;
        mStats = stats;
        mStats.reset();
    }

    bool setValue(QString strStats,int fileIdx)
    {
        mLineIdx     = fileIdx;
        return mStats.setValue(strStats);
    }
};

class DailyPDStatsManager : public QObject
{
    Q_OBJECT

public:
    FileReaderEx       * mpReader       = nullptr;
    FileWriterEx       * mpWriter       = nullptr;

    PDStatsItem *        mpCurrItem     = nullptr;
    QList<PDStatsItem *> mPDStatsList           ;

    explicit DailyPDStatsManager(QObject * parent = nullptr):QObject(parent)
    {
    }
    ~DailyPDStatsManager()
    {
        close();
    }

    void open(QDate today)
    {
        QString line;

        close();

        FileReaderEx reader;

        if(reader.open(FileDef::HISTORY_DIR(), QString("%1-PS.txt").arg(today.toString(DATE_FILE_NAME_FMT))) == true)
        {
            while(reader.readLine(line))
            {
                PDStatsItem *pPDStatsItem = new PDStatsItem();
                pPDStatsItem->setValue(line, mPDStatsList.size());
                mPDStatsList.append(pPDStatsItem);
            }
        }

        reader.close();

        mpWriter = new FileWriterEx(this);
        mpWriter->open(FileDef::HISTORY_DIR(), QString("%1-PS.txt").arg(today.toString(DATE_FILE_NAME_FMT)), FileWriterEx::FILE_OPEN_OVERWRITE);

        foreach(PDSettingDto * pSetting, pProductSP->mPDList)
        {
            PDStatsItem * pItem = findPDStats(pSetting->mSeq);

            if(pItem != nullptr)
            {
                editPDStatsItem(*pSetting);
            }
            else
            {
                addPDStatsItem(*pSetting);
            }
        }

        mpCurrItem = findPDStats(pProductSP->mCurrPD.mSeq);
    }

    void close()
    {
        if(mpWriter != nullptr)
        {
            mpWriter->close();
            delete mpWriter;
            mpWriter = nullptr;
        }

        foreach(PDStatsItem * pItem, mPDStatsList)
        {
            delete pItem;
        }

        mPDStatsList.clear();
    }

    void writePDStatsItem(PDStatsItem * pItem)
    {
        CHECK_FALSE_RETURN((mpWriter != nullptr));

        mpWriter->overWriteLine(pItem->mStats.toString(), pItem->mLineIdx, 500);
    }

    void addPDStatsItem(PDSettingDto setting)
    {
        CHECK_FALSE_RETURN((mpWriter != nullptr));

        PDStatsItem *pItem = new PDStatsItem(setting, mPDStatsList.size());
        mPDStatsList.append(pItem);

        writePDStatsItem(pItem);
    }

    void editPDStatsItem(PDSettingDto setting)
    {
        PDStatsItem * pItem = findPDStats(setting.mSeq);

        CHECK_PTR_RETURN(pItem);

        pItem->mStats.mSeq  = setting.mSeq;
        pItem->mStats.mNum  = setting.mDspForm.mCommSetting.mProductNum;
        pItem->mStats.mName = setting.mName;

        writePDStatsItem(pItem);
    }

    void addEvent(EventDto event)
    {

        if(mpCurrItem == nullptr || mpCurrItem->mStats.mSeq != event.mPDSeq)
        {
            mpCurrItem = findPDStats(event.mPDSeq);
        }

        if(mpCurrItem == nullptr)
        {
            qDebug() << "[DailyPDStatsManager::addEvent] mpCurrItem == null";
            return;
        }

        if(event.isWCEvent())
        {
            switch (event.mEType)
            {
                case EnumDef::ET_WEIGHT_NORMAL         : mpCurrItem->mStats.mWCTotalCnt++; mpCurrItem->mStats.mWCTradeCnt ++; mpCurrItem->mStats.mWCNorCnt ++; break;
                case EnumDef::ET_WEIGHT_UNDER_WARNING  : mpCurrItem->mStats.mWCTotalCnt++; mpCurrItem->mStats.mWCTradeCnt ++; mpCurrItem->mStats.mWCUWCnt  ++; break;
                case EnumDef::ET_WEIGHT_OVER_WARNING   : mpCurrItem->mStats.mWCTotalCnt++; mpCurrItem->mStats.mWCTradeCnt ++; mpCurrItem->mStats.mWCOWCnt  ++; break;
                case EnumDef::ET_WEIGHT_UNDER          : mpCurrItem->mStats.mWCTotalCnt++; mpCurrItem->mStats.mWCUCnt     ++;                              break;
                case EnumDef::ET_WEIGHT_OVER           : mpCurrItem->mStats.mWCTotalCnt++; mpCurrItem->mStats.mWCOCnt     ++;                              break;
                case EnumDef::ET_WEIGHT_ETCERROR       : mpCurrItem->mStats.mWCTotalCnt++; mpCurrItem->mStats.mWCEtcCnt   ++;                              break;
                case EnumDef::ET_WEIGHT_ETC_METAL_ERROR: mpCurrItem->mStats.mWCTotalCnt++; mpCurrItem->mStats.mWCMDCnt    ++;                              break;
            }
        }
        else if(event.isMDEvent())
        {
            switch (event.mEType)
            {
                case EnumDef::ET_METAL_TRADE  : mpCurrItem->mStats.mMDTotalCnt++; mpCurrItem->mStats.mMDPassCnt ++; break;
                case EnumDef::ET_METAL_DETECT : mpCurrItem->mStats.mMDTotalCnt++; mpCurrItem->mStats.mMDFailCnt ++; break;
            }
        }

        writePDStatsItem(mpCurrItem);
    }

private:
    PDStatsItem * findPDStats(quint64 seq)
    {
        foreach(PDStatsItem * pItem, mPDStatsList)
        {
            if(pItem->mStats.mSeq == seq)
                return pItem;
        }

        return nullptr;
    }
};
#endif // DAILYPDSTATSMANAGER_H
