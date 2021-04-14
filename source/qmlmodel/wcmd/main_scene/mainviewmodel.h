#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include <QObject>

#include "source/service/def/datetimeform.h"
#include "source/service/coreservice.h"

class MainViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    isDetail               READ getIsDetail                NOTIFY signalEventChangedIsDetail            )
    Q_PROPERTY(int     wcViewMode             READ getWCViewMode              NOTIFY signalEventChangedWCViewMode          )
    Q_PROPERTY(bool    isEnableWC             READ getIsEnableWC              NOTIFY signalEventChangedIsEnableWC          )
    Q_PROPERTY(bool    isEnableMD             READ getIsEnableMD              NOTIFY signalEventChangedIsEnableMD          )
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
    Q_PROPERTY(qint32  wcCurrWeight           READ getWCCurrWeight            NOTIFY signalEventChangedWCCurrWeight        )
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
    Q_PROPERTY(qint16  lastErrorType          READ getLastErrorType           NOTIFY signalEventChangedLastErrorType       )
    Q_PROPERTY(QString lastErrorTime          READ getLastErrorTime           NOTIFY signalEventChangedLastErrorTime       )
    Q_PROPERTY(quint32 lastErrorValue         READ getLastErrorValue          NOTIFY signalEventChangedLastErrorValue      )
    Q_PROPERTY(quint32 groupCurrCount         READ getGroupCurrCount          NOTIFY signalEventChangedGroupCurrCount      )
    Q_PROPERTY(quint32 groupCount             READ getGroupCount              NOTIFY signalEventChangedGroupCount          )

public:
    quint32               mMinPoints[WCTR_LIMIT];
    quint32               mMaxPoints[WCTR_LIMIT];
    quint64               mDspSeq      = 0;
    quint32               mMinWeight   = 0;
    quint32               mWeightRange = 0;
    int                   mPointCnt    = 0;
    int                   mUiGraphH    = 0;

    bool    mIsDetail            ;
    int     mWCViewMode          ;
    bool    mIsEnableWC          ;
    bool    mIsEnableMD          ;
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
    quint16 mWait                = 1;
    quint16 mMDCurrSignal        = 0;
    quint32 mWCCurrWeight        = 0;
    quint16 mWCCurrEventType     = 0;
    int     mMDTotalCnt          = 0;
    int     mMDDetectCnt         = 0;
    int     mWCTotalCnt          = 0;
    int     mWCNGCnt             = 0;
    int     mWCTradeCnt          = 0;
    int     mWCOverCnt           = 0;
    int     mWCOverWarningCnt    = 0;
    int     mWCNormalCnt         = 0;
    int     mWCUnderWarningCnt   = 0;
    int     mWCUnderCnt          = 0;
    int     mWCEtcErrorCnt       = 0;
    int     mWCEtcMDErrorCnt     = 0;
    quint64 mWCTradeTotalWeight  = 0;
    qint16  mLastErrorType       = 0;
    QString mLastErrorTime       = "";
    quint32 mLastErrorValue      = 0;
    quint32 mGroupCurrCount      = 0;
    quint32 mGroupCount          = 0;

    bool    getIsDetail            (){ return mIsDetail            ;}
    int     getWCViewMode          (){ return mWCViewMode          ;}
    bool    getIsEnableWC          (){ return mIsEnableWC          ;}
    bool    getIsEnableMD          (){ return mIsEnableMD          ;}
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
    qint16  getLastErrorType       (){ return mLastErrorType       ;}
    QString getLastErrorTime       (){ return mLastErrorTime       ;}
    quint32 getLastErrorValue      (){ return mLastErrorValue      ;}
    quint32 getGroupCurrCount      (){ return mGroupCurrCount      ;}
    quint32 getGroupCount          (){ return mGroupCount          ;}

    void setIsDetail            (bool    value){ if(mIsDetail             == value)return; mIsDetail             = value; emit signalEventChangedIsDetail            (value);}
    void setWCViewMode          (int     value){ if(mWCViewMode           == value)return; mWCViewMode           = value; emit signalEventChangedWCViewMode          (value);}
    void setIsEnableWC          (bool    value){ if(mIsEnableWC           == value)return; mIsEnableWC           = value; emit signalEventChangedIsEnableWC          (value);}
    void setIsEnableMD          (bool    value){ if(mIsEnableMD           == value)return; mIsEnableMD           = value; emit signalEventChangedIsEnableMD          (value);}
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
    void setLastErrorType       (qint16  value){ if(mLastErrorType        == value)return; mLastErrorType        = value; emit signalEventChangedLastErrorType       (value);}
    void setLastErrorTime       (QString value){ if(mLastErrorTime        == value)return; mLastErrorTime        = value; emit signalEventChangedLastErrorTime       (value);}
    void setLastErrorValue      (quint32 value){ if(mLastErrorValue       == value)return; mLastErrorValue       = value; emit signalEventChangedLastErrorValue      (value);}
    void setGroupCurrCount      (quint32 value){ if(mGroupCurrCount       == value)return; mGroupCurrCount       = value; emit signalEventChangedGroupCurrCount      (value);}
    void setGroupCount          (quint32 value){ if(mGroupCount           == value)return; mGroupCount           = value; emit signalEventChangedGroupCount          (value);}

signals:
    void signalEventChangedIsDetail            (bool    value);
    void signalEventChangedWCViewMode          (int     value);
    void signalEventChangedIsEnableWC          (bool    value);
    void signalEventChangedIsEnableMD          (bool    value);
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
    void signalEventChangedLastErrorType       (qint16  value);
    void signalEventChangedLastErrorTime       (QString value);
    void signalEventChangedLastErrorValue      (quint32 value);
    void signalEventChangedGroupCurrCount      (quint32 value);
    void signalEventChangedGroupCount          (quint32 value);

    void signalEventNotifyWCNG                 (qint32 value, quint16 eventType);
    void signalEventNotifyMDDetect             (                                );

public slots:
    Q_INVOKABLE void  onCommandSetIsDetail(bool value)
    {
        pLSettingSP->setGUIIsDetail(value);
    }

    Q_INVOKABLE void onCommandSetWCViewMode(int value)
    {
        pLSettingSP->setGUIViewMode((EnumDef::eViewMode) value);
    }

    Q_INVOKABLE int   onCommandSaveTrendsOption(bool isUnderToOver, bool isTotal, bool TotalSinceStart, int lastNValue)
    {
        TrendsOptionDto dto;

        dto.mTrendsOptionH      = isUnderToOver  ? EnumDef::TRENDSOPTION_H_UNDER_TO_OVER : EnumDef::TRENDSOPTION_H_MIN_TO_MAX;
        dto.mTrendsOptionFilter = isTotal        ? EnumDef::TRENDSOPTION_FILTER_TOTAL : EnumDef::TRENDSOPTION_FILTER_TRADE;
        dto.mTrendsOptionLastN  = TotalSinceStart? EnumDef::TRENDSOPTION_TOTAL_SINCE_START : EnumDef::TRENDSOPTION_LAST_N;
        dto.mTrendsLastNValue   = lastNValue;

        LocalSettingSProvider::getInstance()->setTROption(dto);

        return 0;
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

        if(mWCTrendsOptionFilter == EnumDef::TRENDSOPTION_FILTER_TRADE)
        {
            graphPointsCnt = mWCTradeCnt;
        }
        else
        {
            graphPointsCnt = mWCTotalCnt;
        }

        if(mWCTrendsOptionLastN == EnumDef::TRENDSOPTION_LAST_N)
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

        for(int idx = pWorkSP->mTRManager.mWCTrendsCnt - 1; idx > -1; idx --)
        {
            quint32 value       = pWorkSP->mTRManager.mWCTrends[idx].mValue;
            quint64 productSeq  = pWorkSP->mTRManager.mWCTrends[idx].mPDSeq;
            bool    isTrade     = pWorkSP->mTRManager.mWCTrends[idx].mIsTrade;

            if(productSeq != pProductSP->mCurrPD.mSeq)
            {
                continue;
            }

            if(isTrade == false && mWCTrendsOptionFilter == EnumDef::TRENDSOPTION_FILTER_TRADE)
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

            if(mWCTrendsOptionH == EnumDef::TRENDSOPTION_H_MIN_TO_MAX)
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
        if(mWCTrendsOptionLastN == EnumDef::TRENDSOPTION_LAST_N && mWCTrendsLastNValue < width)
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
        CHECK_FALSE_RETURN((mDspSeq != 0));

        pDspSP->sendZeroCmd(mDspSeq);
    }

    Q_INVOKABLE void onCommandResetGroupCount()
    {
        CHECK_FALSE_RETURN((mDspSeq != 0));

        pDspSP->sendResetGCntCmd(mDspSeq, 1);
    }

    Q_INVOKABLE void onCommandSetTare(quint32 value)
    {
        PDSettingDto setting = pProductSP->mCurrPD;
        setting.mDspForm.mWCSetting.mTareWeight = value;

        pProductSP->editPD(setting);
    }



//  down layer ===================================================================================
public slots:
    void onChangedGuiIsDetail(bool value)
    {
        setIsDetail(value);
    }
    void onChangedViewMode(int value)
    {
        setWCViewMode(value);
    }
    void onChangedTROption(TrendsOptionDto value)
    {
        setWCTrendsLastNValue(value.mTrendsLastNValue);
        setWCTrendsOptionH     (value.mTrendsOptionH);
        setWCTrendsOptionFilter(value.mTrendsOptionFilter);
        setWCTrendsOptionLastN (value.mTrendsOptionLastN);
    }

    void onChangedDevSetting(DevSettingDto dto)
    {
        setIsEnableWC(dto.mDspForm.mCommSetting.mMachineMode != EnumDef::MACHINE_MODE_ALU);
        setIsEnableMD(dto.mDspForm.mCommSetting.mMachineMode != EnumDef::MACHINE_MODE_WC);
    }
    void onChangedCurrPDSetting(PDSettingDto dto)
    {
        setProductNo           (dto.mDspForm.mCommSetting.mProductNum      );
        setProductName         (dto.mName                                  );
        setMDSenstivity        (dto.mDspForm.mMDSetting.mSenstivity        );
        setWCOverWeight        (dto.mDspForm.mWCSetting.mOverWeight        );
        setWCOverWarningWeight (dto.mDspForm.mWCSetting.mOverWarningWeight );
        setWCNormalWeight      (dto.mDspForm.mWCSetting.mNormalWeight      );
        setWCUnderWarningWeight(dto.mDspForm.mWCSetting.mUnderWarningWeight);
        setWCUnderWeight       (dto.mDspForm.mWCSetting.mUnderWeight       );
        setWCTareWeight        (dto.mDspForm.mWCSetting.mTareWeight        );
        setGroupCount          (dto.mDspForm.mCommSetting.mGroupCount      );
    }

    void onChangedLastErr(EventDto dto)
    {
        setLastErrorType       (dto.mEType);
        setLastErrorTime       (dto.mDateTime.toString(TIME_FMT));
        setLastErrorValue      (dto.mEValue);
    }

    void onChangedDspStatus(quint64 dspSeq, DspStatusDto dto)
    {
        CHECK_FALSE_RETURN((mDspSeq == dspSeq));

        setWait                (dto.mWCStatus.mWait);
        setMDCurrSignal        (dto.mMDStatus.mSignal);
        setWCCurrWeight        (dto.mWCStatus.mCurrWeight);
        setWCCurrEventType     (dto.mWCStatus.mErrorType);
        setGroupCurrCount      (dto.mCommStatus.mGroupCurrCount);
    }

    void onAddedDspEvent(quint64 dspSeq, DspEventDto dto)
    {
        CHECK_FALSE_RETURN((mDspSeq == dspSeq));

        if(EventDto::isWeightNGEvent   (dto.mEvent.mEventType))emit signalEventNotifyWCNG    (dto.mEvent.mEventValue, dto.mEvent.mEventType);
        if(EventDto::isMetalDetectEvent(dto.mEvent.mEventType))emit signalEventNotifyMDDetect(                                             );
    }

    void onChangedPDStats(PDStatsDto dto)
    {
        setMDTotalCnt          (dto.mMDTotalCnt);
        setMDDetectCnt         (dto.mMDFailCnt);

        setWCNGCnt             (dto.mWCEtcCnt + dto.mWCMDCnt + dto.mWCOCnt + dto.mWCUCnt);
        setWCTradeCnt          (dto.mWCTradeCnt);
        setWCOverCnt           (dto.mWCOCnt);
        setWCOverWarningCnt    (dto.mWCOWCnt);
        setWCNormalCnt         (dto.mWCNorCnt);
        setWCUnderWarningCnt   (dto.mWCUWCnt);
        setWCUnderCnt          (dto.mWCUCnt);
        setWCEtcErrorCnt       (dto.mWCEtcCnt);
        setWCEtcMDErrorCnt     (dto.mWCMDCnt);
        setWCTradeTotalWeight  (dto.mWCTradeTotalWeight);
        setWCTotalCnt          (dto.mWCTotalCnt);

    }


//  internal layer ===================================================================================
public:
    explicit MainViewModel(QObject *parent = nullptr): QObject(parent)
    {
        if(pDspSP->mDspList.size() > 0)
        {
            mDspSeq = pDspSP->mDspList[0]->mSeq;
        }

        ENABLE_SLOT_LSETTING_CHANGED_ISDETAIL;
        ENABLE_SLOT_LSETTING_CHANGED_VIEWMODE;
        ENABLE_SLOT_LSETTING_CHANGED_TR_OPTION;
        ENABLE_SLOT_LSETTING_CHANGED_DEV_SETTING;

        ENABLE_SLOT_PDSETTING_CHANGED_CURR_PD;

        ENABLE_SLOT_WORK_CHANGED_LASTERR;
        ENABLE_SLOT_WORK_CHANGED_STATS;

        ENABLE_SLOT_DSP_CHANGED_DSP_STATUS;
        ENABLE_SLOT_DSP_ADDED_EVENT;

        onChangedGuiIsDetail(pLSettingSP->mIsDetail);
        onChangedViewMode(pLSettingSP->mViewMode);
        onChangedTROption(pLSettingSP->mTROption);
        onChangedDevSetting(pLSettingSP->mDevSetting);
        onChangedCurrPDSetting(pProductSP->mCurrPD);
        onChangedPDStats(pWorkSP->mCurrPD);
        onChangedLastErr(pWorkSP->mLastErrEvent);

        if(mDspSeq != 0)
        {
            DspMaster * pMaster = pDspSP->findDspMaster(mDspSeq);

            if(pMaster != nullptr)
            {
                DspStatusDto status = pMaster->mRcvDataStore.getStatusDto();
                onChangedDspStatus(mDspSeq, status);
            }
        }
    }
};

#endif // MAINVIEWMODEL_H
