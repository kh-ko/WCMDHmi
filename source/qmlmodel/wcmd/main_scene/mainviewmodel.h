#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include <QObject>

#include "source/service/coreservice.h"

class MainViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    isDetail               READ getIsDetail                NOTIFY signalEventChangedIsDetail            )
    Q_PROPERTY(int     wcViewMode             READ getWCViewMode              NOTIFY signalEventChangedWCViewMode          )
    Q_PROPERTY(int     wcTrendsLastNValue     READ getWCTrendsLastNValue      NOTIFY signalEventChangedWCTrendsLastNValue  )
    Q_PROPERTY(int     wcTrendsOptionH        READ getWCTrendsOptionH         NOTIFY signalEventChangedWCTrendsOptionH     )
    Q_PROPERTY(int     wcTrendsOptionFilter   READ getWCTrendsOptionFilter    NOTIFY signalEventChangedWCTrendsOptionFilter)
    Q_PROPERTY(int     wcTrendsOptionLastN    READ getWCTrendsOptionLastN     NOTIFY signalEventChangedWCTrendsOptionLastN )
    Q_PROPERTY(quint16 productNo              READ getProductNo               NOTIFY signalEventChangedProductNo           )
    Q_PROPERTY(QString productName            READ getProductName             NOTIFY signalEventChangedProductName         )
    Q_PROPERTY(quint16 mdSenstivity           READ getMDSenstivity            NOTIFY signalEventChangedMDSenstivity        )
    Q_PROPERTY(quint32 wcOverWeight           READ getWCOverWeight            NOTIFY signalEventChangedWCOverWeight        )
    Q_PROPERTY(quint32 wcOverWarningWeight    READ getWCOverWarningWeight     NOTIFY signalEventChangedWCOverWarningWeight )
    Q_PROPERTY(quint32 wcNormalWeight         READ getWCNormalWeight          NOTIFY signalEventChangedWCNormalWeight      )
    Q_PROPERTY(quint32 wcUnderWarningWeight   READ getWCUnderWarningWeight    NOTIFY signalEventChangedWCUnderWarningWeight)
    Q_PROPERTY(quint32 wcUnderWeight          READ getWCUnderWeight           NOTIFY signalEventChangedWCUnderWeight       )
    Q_PROPERTY(quint32 wcTareWeight           READ getWCTareWeight            NOTIFY signalEventChangedWCTareWeight        )
    Q_PROPERTY(quint16 wait                   READ getWait                    NOTIFY signalEventChangedWait                )
    Q_PROPERTY(quint16 mdCurrSignal           READ getMDCurrSignal            NOTIFY signalEventChangedMDCurrSignal        )
    Q_PROPERTY(quint32 wcCurrWeight           READ getWCCurrWeight            NOTIFY signalEventChangedWCCurrWeight        )
    Q_PROPERTY(quint16 wcCurrEventType        READ getWCCurrEventType         NOTIFY signalEventChangedWCCurrEventType     )
    Q_PROPERTY(int     mdTotalCnt             READ getMDTotalCnt              NOTIFY signalEventChangedMDTotalCnt          )
    Q_PROPERTY(int     mdDetectCnt            READ getMDDetectCnt             NOTIFY signalEventChangedMDDetectCnt         )
    Q_PROPERTY(int     wcTotalCnt             READ getWCTotalCnt              NOTIFY signalEventChangedWCTotalCnt          )
    Q_PROPERTY(int     wcNGCnt                READ getWCNGCnt                 NOTIFY signalEventChangedWCNGCnt             )
    Q_PROPERTY(int     wcTradeCnt             READ getWCTradeCnt              NOTIFY signalEventChangedWCTradeCnt          )
    Q_PROPERTY(int     wcOverCnt              READ getWCOverCnt               NOTIFY signalEventChangedWCOverCnt           )
    Q_PROPERTY(int     wcOverWarningCnt       READ getWCOverWarningCnt        NOTIFY signalEventChangedWCOverWarningCnt    )
    Q_PROPERTY(int     wcNormalCnt            READ getWCNormalCnt             NOTIFY signalEventChangedWCNormalCnt         )
    Q_PROPERTY(int     wcUnderWarningCnt      READ getWCUnderWarningCnt       NOTIFY signalEventChangedWCUnderWarningCnt   )
    Q_PROPERTY(int     wcUnderCnt             READ getWCUnderCnt              NOTIFY signalEventChangedWCUnderCnt          )
    Q_PROPERTY(int     wcEtcErrorCnt          READ getWCEtcErrorCnt           NOTIFY signalEventChangedWCEtcErrorCnt       )
    Q_PROPERTY(int     wCEtcMDErrorCnt        READ getWCEtcMDErrorCnt         NOTIFY signalEventChangedWCEtcMDErrorCnt     )
    Q_PROPERTY(quint64 wcTradeTotalWeight     READ getWCTradeTotalWeight      NOTIFY signalEventChangedWCTradeTotalWeight  )
    Q_PROPERTY(quint16 lastErrorType          READ getLastErrorType           NOTIFY signalEventChangedLastErrorType       )
    Q_PROPERTY(QString lastErrorTime          READ getLastErrorTime           NOTIFY signalEventChangedLastErrorTime       )
    Q_PROPERTY(quint32 lastErrorValue         READ getLastErrorValue          NOTIFY signalEventChangedLastErrorValue      )

public:
    CoreService         * mpCoreService     ;
    InformationModel    * mpInformation     ;
    GuiSettingModel     * mpGuiSetting      ;
    ProductSettingModel * mpProductSetting  ;
    DspStatusModel      * mpDspStatus       ;
    ProductStatusModel  * mpProductStatus   ;
    LastErrorModel      * mpLastError       ;
    quint32               mMinPoints[TRENDS_POINT_BUFF_CNT];
    quint32               mMaxPoints[TRENDS_POINT_BUFF_CNT];
    quint32               mMinWeight;
    quint32               mWeightRange;
    int                   mPointCnt;
    int                   mUiGraphH;

    bool    mIsDetail            ;
    int     mWCViewMode          ;
    int     mWCTrendsLastNValue  ;
    int     mWCTrendsOptionH     ;
    int     mWCTrendsOptionFilter;
    int     mWCTrendsOptionLastN ;
    quint16 mProductNo           ;
    QString mProductName         ;
    quint16 mMDSenstivity        ;
    quint32 mWCOverWeight        ;
    quint32 mWCOverWarningWeight ;
    quint32 mWCNormalWeight      ;
    quint32 mWCUnderWarningWeight;
    quint32 mWCUnderWeight       ;
    quint32 mWCTareWeight        ;
    quint16 mWait                ;
    quint16 mMDCurrSignal        ;
    quint32 mWCCurrWeight        ;
    quint16 mWCCurrEventType     ;
    int     mMDTotalCnt          ;
    int     mMDDetectCnt         ;
    int     mWCTotalCnt          ;
    int     mWCNGCnt             ;
    int     mWCTradeCnt          ;
    int     mWCOverCnt           ;
    int     mWCOverWarningCnt    ;
    int     mWCNormalCnt         ;
    int     mWCUnderWarningCnt   ;
    int     mWCUnderCnt          ;
    int     mWCEtcErrorCnt       ;
    int     mWCEtcMDErrorCnt     ;
    quint64 mWCTradeTotalWeight  ;
    quint16 mLastErrorType       ;
    QString mLastErrorTime       ;
    quint32 mLastErrorValue      ;

    bool    getIsDetail            (){ return mIsDetail            ;}
    int     getWCViewMode          (){ return mWCViewMode          ;}
    int     getWCTrendsLastNValue  (){ return mWCTrendsLastNValue  ;}
    int     getWCTrendsOptionH     (){ return mWCTrendsOptionH     ;}
    int     getWCTrendsOptionFilter(){ return mWCTrendsOptionFilter;}
    int     getWCTrendsOptionLastN (){ return mWCTrendsOptionLastN ;}
    quint16 getProductNo           (){ return mProductNo           ;}
    QString getProductName         (){ return mProductName         ;}
    quint16 getMDSenstivity        (){ return mMDSenstivity        ;}
    quint32 getWCOverWeight        (){ return mWCOverWeight        ;}
    quint32 getWCOverWarningWeight (){ return mWCOverWarningWeight ;}
    quint32 getWCNormalWeight      (){ return mWCNormalWeight      ;}
    quint32 getWCUnderWarningWeight(){ return mWCUnderWarningWeight;}
    quint32 getWCUnderWeight       (){ return mWCUnderWeight       ;}
    quint32 getWCTareWeight        (){ return mWCTareWeight        ;}
    quint16 getWait                (){ return mWait                ;}
    quint16 getMDCurrSignal        (){ return mMDCurrSignal        ;}
    quint32 getWCCurrWeight        (){ return mWCCurrWeight        ;}
    quint16 getWCCurrEventType     (){ return mWCCurrEventType     ;}
    int     getMDTotalCnt          (){ return mMDTotalCnt          ;}
    int     getMDDetectCnt         (){ return mMDDetectCnt         ;}
    int     getWCTotalCnt          (){ return mWCTotalCnt          ;}
    int     getWCNGCnt             (){ return mWCNGCnt             ;}
    int     getWCTradeCnt          (){ return mWCTradeCnt          ;}
    int     getWCOverCnt           (){ return mWCOverCnt           ;}
    int     getWCOverWarningCnt    (){ return mWCOverWarningCnt    ;}
    int     getWCNormalCnt         (){ return mWCNormalCnt         ;}
    int     getWCUnderWarningCnt   (){ return mWCUnderWarningCnt   ;}
    int     getWCUnderCnt          (){ return mWCUnderCnt          ;}
    int     getWCEtcErrorCnt       (){ return mWCEtcErrorCnt       ;}
    int     getWCEtcMDErrorCnt     (){ return mWCEtcMDErrorCnt     ;}
    quint64 getWCTradeTotalWeight  (){ return mWCTradeTotalWeight  ;}
    quint16 getLastErrorType       (){ return mLastErrorType       ;}
    QString getLastErrorTime       (){ return mLastErrorTime       ;}
    quint32 getLastErrorValue      (){ return mLastErrorValue      ;}

    void setIsDetail            (bool    value){ if(mIsDetail             == value)return; mIsDetail             = value; emit signalEventChangedIsDetail            (value);}
    void setWCViewMode          (int     value){ if(mWCViewMode           == value)return; mWCViewMode           = value; emit signalEventChangedWCViewMode          (value);}
    void setWCTrendsLastNValue  (int     value){ if(mWCTrendsLastNValue   == value)return; mWCTrendsLastNValue   = value; emit signalEventChangedWCTrendsLastNValue  (value);}
    void setWCTrendsOptionH     (int     value){ if(mWCTrendsOptionH      == value)return; mWCTrendsOptionH      = value; emit signalEventChangedWCTrendsOptionH     (value);}
    void setWCTrendsOptionFilter(int     value){ if(mWCTrendsOptionFilter == value)return; mWCTrendsOptionFilter = value; emit signalEventChangedWCTrendsOptionFilter(value);}
    void setWCTrendsOptionLastN (int     value){ if(mWCTrendsOptionLastN  == value)return; mWCTrendsOptionLastN  = value; emit signalEventChangedWCTrendsOptionLastN (value);}
    void setProductNo           (quint16 value){ if(mProductNo            == value)return; mProductNo            = value; emit signalEventChangedProductNo           (value);}
    void setProductName         (QString value){ if(mProductName          == value)return; mProductName          = value; emit signalEventChangedProductName         (value);}
    void setMDSenstivity        (quint16 value){ if(mMDSenstivity         == value)return; mMDSenstivity         = value; emit signalEventChangedMDSenstivity        (value);}
    void setWCOverWeight        (quint32 value){ if(mWCOverWeight         == value)return; mWCOverWeight         = value; emit signalEventChangedWCOverWeight        (value);}
    void setWCOverWarningWeight (quint32 value){ if(mWCOverWarningWeight  == value)return; mWCOverWarningWeight  = value; emit signalEventChangedWCOverWarningWeight (value);}
    void setWCNormalWeight      (quint32 value){ if(mWCNormalWeight       == value)return; mWCNormalWeight       = value; emit signalEventChangedWCNormalWeight      (value);}
    void setWCUnderWarningWeight(quint32 value){ if(mWCUnderWarningWeight == value)return; mWCUnderWarningWeight = value; emit signalEventChangedWCUnderWarningWeight(value);}
    void setWCUnderWeight       (quint32 value){ if(mWCUnderWeight        == value)return; mWCUnderWeight        = value; emit signalEventChangedWCUnderWeight       (value);}
    void setWCTareWeight        (quint32 value){ if(mWCTareWeight         == value)return; mWCTareWeight         = value; emit signalEventChangedWCTareWeight        (value);}
    void setWait                (quint16 value){ if(mWait                 == value)return; mWait                 = value; emit signalEventChangedWait                (value);}
    void setMDCurrSignal        (quint16 value){ if(mMDCurrSignal         == value)return; mMDCurrSignal         = value; emit signalEventChangedMDCurrSignal        (value);}
    void setWCCurrWeight        (quint32 value){ if(mWCCurrWeight         == value)return; mWCCurrWeight         = value; emit signalEventChangedWCCurrWeight        (value);}
    void setWCCurrEventType     (quint16 value){ if(mWCCurrEventType      == value)return; mWCCurrEventType      = value; emit signalEventChangedWCCurrEventType     (value);}
    void setMDTotalCnt          (int     value){ if(mMDTotalCnt           == value)return; mMDTotalCnt           = value; emit signalEventChangedMDTotalCnt          (value);}
    void setMDDetectCnt         (int     value){ if(mMDDetectCnt          == value)return; mMDDetectCnt          = value; emit signalEventChangedMDDetectCnt         (value);}
    void setWCTotalCnt          (int     value){ if(mWCTotalCnt           == value)return; mWCTotalCnt           = value; emit signalEventChangedWCTotalCnt          (value);}
    void setWCNGCnt             (int     value){ if(mWCNGCnt              == value)return; mWCNGCnt              = value; emit signalEventChangedWCNGCnt             (value);}
    void setWCTradeCnt          (int     value){ if(mWCTradeCnt           == value)return; mWCTradeCnt           = value; emit signalEventChangedWCTradeCnt          (value);}
    void setWCOverCnt           (int     value){ if(mWCOverCnt            == value)return; mWCOverCnt            = value; emit signalEventChangedWCOverCnt           (value);}
    void setWCOverWarningCnt    (int     value){ if(mWCOverWarningCnt     == value)return; mWCOverWarningCnt     = value; emit signalEventChangedWCOverWarningCnt    (value);}
    void setWCNormalCnt         (int     value){ if(mWCNormalCnt          == value)return; mWCNormalCnt          = value; emit signalEventChangedWCNormalCnt         (value);}
    void setWCUnderWarningCnt   (int     value){ if(mWCUnderWarningCnt    == value)return; mWCUnderWarningCnt    = value; emit signalEventChangedWCUnderWarningCnt   (value);}
    void setWCUnderCnt          (int     value){ if(mWCUnderCnt           == value)return; mWCUnderCnt           = value; emit signalEventChangedWCUnderCnt          (value);}
    void setWCEtcErrorCnt       (int     value){ if(mWCEtcErrorCnt        == value)return; mWCEtcErrorCnt        = value; emit signalEventChangedWCEtcErrorCnt       (value);}
    void setWCEtcMDErrorCnt     (int     value){ if(mWCEtcMDErrorCnt      == value)return; mWCEtcMDErrorCnt      = value; emit signalEventChangedWCEtcMDErrorCnt     (value);}
    void setWCTradeTotalWeight  (quint64 value){ if(mWCTradeTotalWeight   == value)return; mWCTradeTotalWeight   = value; emit signalEventChangedWCTradeTotalWeight  (value);}
    void setLastErrorType       (quint16 value){ if(mLastErrorType        == value)return; mLastErrorType        = value; emit signalEventChangedLastErrorType       (value);}
    void setLastErrorTime       (QString value){ if(mLastErrorTime        == value)return; mLastErrorTime        = value; emit signalEventChangedLastErrorTime       (value);}
    void setLastErrorValue      (quint32 value){ if(mLastErrorValue       == value)return; mLastErrorValue       = value; emit signalEventChangedLastErrorValue      (value);}

signals:
    void signalEventChangedIsDetail            (bool    value);
    void signalEventChangedWCViewMode          (int     value);
    void signalEventChangedWCTrendsLastNValue  (int     value);
    void signalEventChangedWCTrendsOptionH     (int     value);
    void signalEventChangedWCTrendsOptionFilter(int     value);
    void signalEventChangedWCTrendsOptionLastN (int     value);
    void signalEventChangedProductNo           (quint16 value);
    void signalEventChangedProductName         (QString value);
    void signalEventChangedMDSenstivity        (quint16 value);
    void signalEventChangedWCOverWeight        (quint32 value);
    void signalEventChangedWCOverWarningWeight (quint32 value);
    void signalEventChangedWCNormalWeight      (quint32 value);
    void signalEventChangedWCUnderWarningWeight(quint32 value);
    void signalEventChangedWCUnderWeight       (quint32 value);
    void signalEventChangedWCTareWeight        (quint32 value);
    void signalEventChangedWait                (quint16 value);
    void signalEventChangedMDCurrSignal        (quint16 value);
    void signalEventChangedWCCurrWeight        (quint32 value);
    void signalEventChangedWCCurrEventType     (quint16 value);
    void signalEventChangedMDTotalCnt          (int     value);
    void signalEventChangedMDDetectCnt         (int     value);
    void signalEventChangedWCTotalCnt          (int     value);
    void signalEventChangedWCNGCnt             (int     value);
    void signalEventChangedWCTradeCnt          (int     value);
    void signalEventChangedWCOverCnt           (int     value);
    void signalEventChangedWCOverWarningCnt    (int     value);
    void signalEventChangedWCNormalCnt         (int     value);
    void signalEventChangedWCUnderWarningCnt   (int     value);
    void signalEventChangedWCUnderCnt          (int     value);
    void signalEventChangedWCEtcErrorCnt       (int     value);
    void signalEventChangedWCEtcMDErrorCnt     (int     value);
    void signalEventChangedWCTradeTotalWeight  (quint64 value);
    void signalEventChangedLastErrorType       (quint16 value);
    void signalEventChangedLastErrorTime       (QString value);
    void signalEventChangedLastErrorValue      (quint32 value);

    void signalEventNotifyWCNG                 (quint32 value, quint16 eventType);
    void signalEventNotifyMDDetect             (                                );

public slots:
    Q_INVOKABLE void  onCommandSetIsDetail(bool value)
    {
        mpCoreService->mLocalSettingService.setGuiIsDetail(value);
    }
    Q_INVOKABLE void  onCommandSetWCViewMode(int  value)
    {
        mpCoreService->mLocalSettingService.setGuiViewMode(value);
    }
    Q_INVOKABLE int   onCommandSaveTrendsOption(bool isUnderToOver, bool isTotal, bool TotalSinceStart, int lastNValue)
    {
        int optionH      = isUnderToOver  ? EnumDefine::TrendsGraphOptionH::TRENDSOPTION_H_UNDER_TO_OVER : EnumDefine::TrendsGraphOptionH::TRENDSOPTION_H_MIN_TO_MAX;
        int optionFilter = isTotal        ? EnumDefine::TrendsGraphOptionFilter::TRENDSOPTION_FILTER_TOTAL : EnumDefine::TrendsGraphOptionFilter::TRENDSOPTION_FILTER_TRADE;
        int optionLastN  = TotalSinceStart? EnumDefine::TrendsGraphOptionLastN::TRENDSOPTION_TOTAL_SINCE_START : EnumDefine::TrendsGraphOptionLastN::TRENDSOPTION_LAST_N;

        mpCoreService->mLocalSettingService.setGuiTrendsOption(optionH, optionFilter, optionLastN, lastNValue);
    }
    Q_INVOKABLE int   onCommandGetSnopShotPointsCnt  ()
    {
        return mPointCnt;
    }
    Q_INVOKABLE void  onCommandCreateSnopShot(int width, int height)
    {
        quint32         min = 0;
        quint32         max = 0;
        int             productTrendsIdx;
        int             uigLastIdx = -1;
        int             uigIdx = 0;
        int             graphPointsCnt;

        mUiGraphH = height;

        if(mWCTrendsOptionFilter == EnumDefine::TrendsGraphOptionFilter::TRENDSOPTION_FILTER_TRADE)
        {
            graphPointsCnt = mWCTradeCnt;
        }
        else
        {
            graphPointsCnt = mWCTotalCnt;
        }

        if(mWCTrendsOptionLastN == EnumDefine::TrendsGraphOptionLastN::TRENDSOPTION_LAST_N)
        {
            if(graphPointsCnt - mWCTrendsLastNValue > 0 )
            {
                graphPointsCnt = mWCTrendsLastNValue;
            }
        }

        min = mWCUnderWeight - ( (mWCOverWeight - mWCUnderWeight) * 0.2 ) ;
        max = mWCOverWeight + ( (mWCOverWeight - mWCUnderWeight) * 0.2  ) ;

        productTrendsIdx = graphPointsCnt - 1;
        mPointCnt = 0;

        for(int idx = mpDspStatus->mTrends.mCount - 1; idx > -1; idx --)
        {
            quint32 value       = mpDspStatus->mTrends.mArray[idx].mValue;
            quint64 productSeq  = mpDspStatus->mTrends.mArray[idx].mProductSettingSeq;
            bool    isTrade     = mpDspStatus->mTrends.mArray[idx].mIsTrade;

            if(productSeq != mpProductSetting->mSeq)
            {
                continue;
            }

            if(isTrade == false && mWCTrendsOptionFilter == EnumDefine::TrendsGraphOptionFilter::TRENDSOPTION_FILTER_TRADE)
            {
                continue;
            }

            if(productTrendsIdx < 0)
                break;

            if(graphPointsCnt < width)
                uigIdx = productTrendsIdx;
            else
                uigIdx = width * ((float)productTrendsIdx / (float)graphPointsCnt);

            if(uigIdx != uigLastIdx || mMinPoints[uigIdx] > value)
            {
                mMinPoints[uigIdx] = value;
            }

            if(uigIdx != uigLastIdx || mMinPoints[uigIdx] < value)
            {
                mMaxPoints[uigIdx] = value;
            }

            if(mWCTrendsOptionH == EnumDefine::TrendsGraphOptionH::TRENDSOPTION_H_MIN_TO_MAX)
            {
                if(min > value)
                    min = value;
                if(max < value)
                    max = value;
            }
            uigLastIdx = uigIdx;

            if(mPointCnt < (uigLastIdx + 1))
            {
                mPointCnt = uigLastIdx + 1;
            }
            productTrendsIdx--;
        }
        mMinWeight = min;
        mWeightRange = max - mMinWeight;
    }

    Q_INVOKABLE int   onCommandConvertWeightToY(float weight)
    {
        return mUiGraphH - (mUiGraphH * ((weight - mMinWeight) / mWeightRange));
    }

    Q_INVOKABLE float onCommandConvertPointIdxToX(int idx, int width)
    {
        if(mWCTrendsOptionLastN == EnumDefine::TrendsGraphOptionLastN::TRENDSOPTION_LAST_N && mWCTrendsLastNValue < width)
        {
            return (float)width * ((float)idx/ (float)mWCTrendsLastNValue);
        }

        return idx;
    }

    Q_INVOKABLE int   onCommandGetMinPointAt         (int idx)
    {
        return onCommandConvertWeightToY(mMinPoints[idx]);
    }

    Q_INVOKABLE int   onCommandGetMaxPointAt         (int idx)
    {
        return onCommandConvertWeightToY(mMaxPoints[idx]);
    }

    Q_INVOKABLE void  onCommandSetZero()
    {
        mpCoreService->onCommandSendZeroCmd(mpDspStatus->mSeq);
    }

//  down layer ===================================================================================
public slots:
    void onSignalEventChangedIsDetail              (bool    value){ setIsDetail            (value);}
    void onSignalEventChangedWCViewMode            (int     value){ setWCViewMode          (value);}
    void onSignalEventChangedWCTrendsLastNValue    (int     value){ setWCTrendsLastNValue  (value);}
    void onSignalEventChangedWCTrendsOptionH       (int     value){ setWCTrendsOptionH     (value);}
    void onSignalEventChangedWCTrendsOptionFilter  (int     value){ setWCTrendsOptionFilter(value);}
    void onSignalEventChangedWCTrendsOptionLastN   (int     value){ setWCTrendsOptionLastN (value);}
    void onSignalEventChangedProductNo             (quint16 value){ setProductNo           (value);}
    void onSignalEventChangedProductName           (QString value){ setProductName         (value);}
    void onSignalEventChangedMDSenstivity          (quint16 value){ setMDSenstivity        (value);}
    void onSignalEventChangedWCOverWeight          (quint32 value){ setWCOverWeight        (value);}
    void onSignalEventChangedWCOverWarningWeight   (quint32 value){ setWCOverWarningWeight (value);}
    void onSignalEventChangedWCNormalWeight        (quint32 value){ setWCNormalWeight      (value);}
    void onSignalEventChangedWCUnderWarningWeight  (quint32 value){ setWCUnderWarningWeight(value);}
    void onSignalEventChangedWCUnderWeight         (quint32 value){ setWCUnderWeight       (value);}
    void onSignalEventChangedWCTareWeight          (quint32 value){ setWCTareWeight        (value);}
    void onSignalEventChangedWait                  (quint16 value){ setWait                (value);}
    void onSignalEventChangedMDCurrSignal          (quint16 value){ setMDCurrSignal        (value);}
    void onSignalEventChangedWCCurrWeight          (quint32 value){ setWCCurrWeight        (value);}
    void onSignalEventChangedWCCurrEventType       (quint16 value){ setWCCurrEventType     (value);}
    void onSignalEventAddedEvent(quint16 eventType, quint32 value){
        if(EventChecker::isWeightNGEvent   (eventType))emit signalEventNotifyWCNG    (value, eventType);
        if(EventChecker::isMetalDetectEvent(eventType))emit signalEventNotifyMDDetect(                );
    }
    void onSignalEventChangedMDTotalCnt            (int     value){ setMDTotalCnt          (value);}
    void onSignalEventChangedMDDetectCnt           (int     value){ setMDDetectCnt         (value);}
    void onSignalEventChangedWCTotalCnt            (int     value){ setWCTotalCnt          (value);}
    void onSignalEventChangedWCNGCnt               (int     value){ setWCNGCnt             (value);}
    void onSignalEventChangedWCTradeCnt            (int     value){ setWCTradeCnt          (value);}
    void onSignalEventChangedWCOverCnt             (int     value){ setWCOverCnt           (value);}
    void onSignalEventChangedWCOverWarningCnt      (int     value){ setWCOverWarningCnt    (value);}
    void onSignalEventChangedWCNormalCnt           (int     value){ setWCNormalCnt         (value);}
    void onSignalEventChangedWCUnderWarningCnt     (int     value){ setWCUnderWarningCnt   (value);}
    void onSignalEventChangedWCUnderCnt            (int     value){ setWCUnderCnt          (value);}
    void onSignalEventChangedWCEtcErrorCnt         (int     value){ setWCEtcErrorCnt       (value);}
    void onSignalEventChangedWCEtcMDErrorCnt       (int     value){ setWCEtcMDErrorCnt     (value);}
    void onSignalEventChangedWCTradeTotalWeight    (quint64 value){ setWCTradeTotalWeight  (value);}
    void onSignalEventChangedLastErrorType         (quint16 value){ setLastErrorType       (value);}
    void onSignalEventChangedLastErrorTime         (QString value){ setLastErrorTime       (value);}
    void onSignalEventChangedLastErrorValue        (quint32 value){ setLastErrorValue      (value);}

//  internal layer ===================================================================================
public:
    explicit MainViewModel(QObject *parent = nullptr): QObject(parent)
    {
        mpCoreService    = CoreService::getInstance();
        mpDspStatus      = mpCoreService->mMapDspStatus.first();
        mpProductStatus  = &(mpDspStatus->mCurrentProductStatus);
        mpLastError      = &(mpDspStatus->mLastError);
        mpProductSetting = &(mpCoreService->mProductSettingServcie.mCurrentProductSetting);
        mpGuiSetting     = &(mpCoreService->mLocalSettingService.mGuiSetting);

        connect(mpGuiSetting        , SIGNAL(signalEventChangedIsDetail             (bool   )), this, SLOT(onSignalEventChangedIsDetail            (bool   )));
        connect(mpGuiSetting        , SIGNAL(signalEventChangedViewMode             (int    )), this, SLOT(onSignalEventChangedWCViewMode          (int    )));
        connect(mpGuiSetting        , SIGNAL(signalEventChangedTrendsLastNValue     (int    )), this, SLOT(onSignalEventChangedWCTrendsLastNValue  (int    )));
        connect(mpGuiSetting        , SIGNAL(signalEventChangedTrendsOptionH        (int    )), this, SLOT(onSignalEventChangedWCTrendsOptionH     (int    )));
        connect(mpGuiSetting        , SIGNAL(signalEventChangedTrendsOptionFilter   (int    )), this, SLOT(onSignalEventChangedWCTrendsOptionFilter(int    )));
        connect(mpGuiSetting        , SIGNAL(signalEventChangedTrendsOptionLastN    (int    )), this, SLOT(onSignalEventChangedWCTrendsOptionLastN (int    )));

        connect(mpProductSetting    , SIGNAL(signalEventChangedNo                   (quint16)), this, SLOT(onSignalEventChangedProductNo           (quint16)));
        connect(mpProductSetting    , SIGNAL(signalEventChangedName                 (QString)), this, SLOT(onSignalEventChangedProductName         (QString)));
        connect(mpProductSetting    , SIGNAL(signalEventChangedMDSenstivity         (quint16)), this, SLOT(onSignalEventChangedMDSenstivity        (quint16)));
        connect(mpProductSetting    , SIGNAL(signalEventChangedOverWeight           (quint32)), this, SLOT(onSignalEventChangedWCOverWeight        (quint32)));
        connect(mpProductSetting    , SIGNAL(signalEventChangedOverWarningWeight    (quint32)), this, SLOT(onSignalEventChangedWCOverWarningWeight (quint32)));
        connect(mpProductSetting    , SIGNAL(signalEventChangedNormalWeight         (quint32)), this, SLOT(onSignalEventChangedWCNormalWeight      (quint32)));
        connect(mpProductSetting    , SIGNAL(signalEventChangedUnderWarningWeight   (quint32)), this, SLOT(onSignalEventChangedWCUnderWarningWeight(quint32)));
        connect(mpProductSetting    , SIGNAL(signalEventChangedUnderWeight          (quint32)), this, SLOT(onSignalEventChangedWCUnderWeight       (quint32)));
        connect(mpProductSetting    , SIGNAL(signalEventChangedTareWeight           (quint32)), this, SLOT(onSignalEventChangedWCTareWeight        (quint32)));

        connect(mpDspStatus         , SIGNAL(signalEventChangedWait                 (quint16)), this, SLOT(onSignalEventChangedWait                (quint16)));
        connect(mpDspStatus         , SIGNAL(signalEventChangedMDCurrSignal         (quint16)), this, SLOT(onSignalEventChangedMDCurrSignal        (quint16)));
        connect(mpDspStatus         , SIGNAL(signalEventChangedWCCurrWeight         (quint32)), this, SLOT(onSignalEventChangedWCCurrWeight        (quint32)));
        connect(mpDspStatus         , SIGNAL(signalEventChangedWCCurrEventType      (quint16)), this, SLOT(onSignalEventChangedWCCurrEventType     (quint16)));
        connect(mpDspStatus         , SIGNAL(siganlEventAddedEvent         (quint16, quint32)), this, SLOT(onSignalEventAddedEvent         (quint16, quint32)));

        connect(mpProductStatus     , SIGNAL(signalEventChangedMDTotalCnt           (int    )), this, SLOT(onSignalEventChangedMDTotalCnt          (int    )));
        connect(mpProductStatus     , SIGNAL(signalEventChangedMDDetectCnt          (int    )), this, SLOT(onSignalEventChangedMDDetectCnt         (int    )));
        connect(mpProductStatus     , SIGNAL(signalEventChangedWCTotalCnt           (int    )), this, SLOT(onSignalEventChangedWCTotalCnt          (int    )));
        connect(mpProductStatus     , SIGNAL(signalEventChangedWCNGCnt              (int    )), this, SLOT(onSignalEventChangedWCNGCnt             (int    )));
        connect(mpProductStatus     , SIGNAL(signalEventChangedWCTradeCnt           (int    )), this, SLOT(onSignalEventChangedWCTradeCnt          (int    )));
        connect(mpProductStatus     , SIGNAL(signalEventChangedWCOverCnt            (int    )), this, SLOT(onSignalEventChangedWCOverCnt           (int    )));
        connect(mpProductStatus     , SIGNAL(signalEventChangedWCOverWarningCnt     (int    )), this, SLOT(onSignalEventChangedWCOverWarningCnt    (int    )));
        connect(mpProductStatus     , SIGNAL(signalEventChangedWCNormalCnt          (int    )), this, SLOT(onSignalEventChangedWCNormalCnt         (int    )));
        connect(mpProductStatus     , SIGNAL(signalEventChangedWCUnderWarningCnt    (int    )), this, SLOT(onSignalEventChangedWCUnderWarningCnt   (int    )));
        connect(mpProductStatus     , SIGNAL(signalEventChangedWCUnderCnt           (int    )), this, SLOT(onSignalEventChangedWCUnderCnt          (int    )));
        connect(mpProductStatus     , SIGNAL(signalEventChangedWCEtcErrorCnt        (int    )), this, SLOT(onSignalEventChangedWCEtcErrorCnt       (int    )));
        connect(mpProductStatus     , SIGNAL(signalEventChangedWCEtcMDErrorCnt      (int    )), this, SLOT(onSignalEventChangedWCEtcMDErrorCnt     (int    )));
        connect(mpProductStatus     , SIGNAL(signalEventChangedWCTradeTotalWeight   (quint64)), this, SLOT(onSignalEventChangedWCTradeTotalWeight  (quint64)));


        connect(mpLastError         , SIGNAL(signalEventChangedEventType            (quint16)), this, SLOT(onSignalEventChangedLastErrorType       (quint16)));
        connect(mpLastError         , SIGNAL(signalEventChangedTime                 (QString)), this, SLOT(onSignalEventChangedLastErrorTime       (QString)));
        connect(mpLastError         , SIGNAL(signalEventChangedValue                (quint32)), this, SLOT(onSignalEventChangedLastErrorValue      (quint32)));

        onSignalEventChangedIsDetail              (mpGuiSetting->mIsDetail              );
        onSignalEventChangedWCViewMode            (mpGuiSetting->mViewMode              );
        onSignalEventChangedWCTrendsLastNValue    (mpGuiSetting->mTrendsLastNValue      );
        onSignalEventChangedWCTrendsOptionH       (mpGuiSetting->mTrendsOptionH         );
        onSignalEventChangedWCTrendsOptionFilter  (mpGuiSetting->mTrendsOptionFilter    );
        onSignalEventChangedWCTrendsOptionLastN   (mpGuiSetting->mTrendsOptionLastN     );

        onSignalEventChangedProductNo             (mpProductSetting->mNo                );
        onSignalEventChangedProductName           (mpProductSetting->mName              );
        onSignalEventChangedMDSenstivity          (mpProductSetting->mMDSenstivity      );
        onSignalEventChangedWCOverWeight          (mpProductSetting->mOverWeight        );
        onSignalEventChangedWCOverWarningWeight   (mpProductSetting->mOverWarningWeight );
        onSignalEventChangedWCNormalWeight        (mpProductSetting->mNormalWeight      );
        onSignalEventChangedWCUnderWarningWeight  (mpProductSetting->mUnderWarningWeight);
        onSignalEventChangedWCUnderWeight         (mpProductSetting->mUnderWeight       );
        onSignalEventChangedWCTareWeight          (mpProductSetting->mTareWeight        );

        onSignalEventChangedWait                  (mpDspStatus->mWait                   );
        onSignalEventChangedMDCurrSignal          (mpDspStatus->mMDCurrSignal           );
        onSignalEventChangedWCCurrWeight          (mpDspStatus->mWCCurrWeight           );
        onSignalEventChangedWCCurrEventType       (mpDspStatus->mWCCurrEventType        );

        onSignalEventChangedMDTotalCnt            (mpProductStatus->mMDTotalCnt         );
        onSignalEventChangedMDDetectCnt           (mpProductStatus->mMDDetectCnt        );
        onSignalEventChangedWCTotalCnt            (mpProductStatus->mWCTotalCnt         );
        onSignalEventChangedWCNGCnt               (mpProductStatus->mWCNGCnt            );
        onSignalEventChangedWCTradeCnt            (mpProductStatus->mWCTradeCnt         );
        onSignalEventChangedWCOverCnt             (mpProductStatus->mWCOverCnt          );
        onSignalEventChangedWCOverWarningCnt      (mpProductStatus->mWCOverWarningCnt   );
        onSignalEventChangedWCNormalCnt           (mpProductStatus->mWCNormalCnt        );
        onSignalEventChangedWCUnderWarningCnt     (mpProductStatus->mWCUnderWarningCnt  );
        onSignalEventChangedWCUnderCnt            (mpProductStatus->mWCUnderCnt         );
        onSignalEventChangedWCEtcErrorCnt         (mpProductStatus->mWCEtcErrorCnt      );
        onSignalEventChangedWCEtcMDErrorCnt       (mpProductStatus->mWCEtcMDErrorCnt    );
        onSignalEventChangedWCTradeTotalWeight    (mpProductStatus->mWCTradeTotalWeight );

        onSignalEventChangedLastErrorType         (mpLastError->mEventType              );
        onSignalEventChangedLastErrorTime         (mpLastError->mTime                   );
        onSignalEventChangedLastErrorValue        (mpLastError->mValue                  );
    }
};

#endif // MAINVIEWMODEL_H
