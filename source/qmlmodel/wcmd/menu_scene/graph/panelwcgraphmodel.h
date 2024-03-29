#ifndef PANELWCGRAPHMODEL_H
#define PANELWCGRAPHMODEL_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDir>

#include "source/service/coreservice.h"

class PanelWCGraphModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      minRange                READ      getMinRange                    NOTIFY      signalEventChangedMinRange               )
    Q_PROPERTY(int      maxRange                READ      getMaxRange                    NOTIFY      signalEventChangedMaxRange               )
    Q_PROPERTY(int      range                   READ      getRange                       NOTIFY      signalEventChangedRange                  )
    Q_PROPERTY(int      lineInterval            READ      getLineInterval                NOTIFY      signalEventChangedLineInterval           )

    Q_PROPERTY(qint16   adcValue                READ      getAdcValue                    NOTIFY      signalEventChangedAdcValue               )
    Q_PROPERTY(qint32   eventValue              READ      getEventValue                  NOTIFY      signalEventChangedEventValue             )
    Q_PROPERTY(qint32   tareWeight              READ      getTareWeight                  NOTIFY      signalEventChangedTareWeight             )
    Q_PROPERTY(qint16   maxPDCntPerMin          READ      getMaxPDCntPerMin              NOTIFY      signalEventChangedMaxPDCntPerMin         )
    Q_PROPERTY(qint16   currPDCntPerMin         READ      getCurrPDCntPerMin             NOTIFY      signalEventChangedCurrPDCntPerMin        )
    Q_PROPERTY(qint16   pdCntPerMin             READ      getPDCntPerMin                 NOTIFY      signalEventChangedPDCntPerMin            )

    Q_PROPERTY(bool     isRawGraphOn            READ      getIsRawGraphOn                NOTIFY      signalEventChangedIsRawGraphOn           )
    Q_PROPERTY(bool     isRunTimeGraphPause     READ      getIsRunTimeGraphPause         NOTIFY      signalEventChangedIsRunTimeGraphPause    )
    Q_PROPERTY(int      runtimePointCnt         READ      getRuntimePointCnt             NOTIFY      signalEventChangedRuntimePointCnt        )

    Q_PROPERTY(bool     isTimingGraphPause      READ      getIsTimingGraphPause          NOTIFY      signalEventChangedIsTimingGraphPause     )
    Q_PROPERTY(int      measuredStartIdx        READ      getMeasuredStartIdx            NOTIFY      signalEventChangedMeasuredStartIdx       )
    Q_PROPERTY(int      measuredCueLineIdx      READ      getMeasuredCueLineIdx          NOTIFY      signalEventChangedMeasuredCueLineIdx     )
    Q_PROPERTY(int      measuredSectionLineIdx  READ      getMeasuredSectionLineIdx      NOTIFY      signalEventChangedMeasuredSectionLineIdx )
    Q_PROPERTY(int      timingPointCnt          READ      getTimingPointCnt              NOTIFY      signalEventChangedTimingPointCnt         )

    Q_PROPERTY(quint16  graphPointCnt           READ      getGraphPointCnt               NOTIFY      signalEventChangedGraphPointCnt          )
    Q_PROPERTY(quint16  autoSetting             READ      getAutoSetting                 NOTIFY      signalEventChangedAutoSetting            )
    Q_PROPERTY(qint16   filterCoefficient       READ      getFilterCoefficient           NOTIFY      signalEventChangedFilterCoefficient      )
    Q_PROPERTY(qint16   zeroDelayTime           READ      getZeroDelayTime               NOTIFY      signalEventChangedZeroDelayTime          )
    Q_PROPERTY(qint32   measureCueSign          READ      getMeasureCueSign              NOTIFY      signalEventChangedMeasureCueSign         )
    Q_PROPERTY(qint32   measureSection          READ      getMeasureSection              NOTIFY      signalEventChangedMeasureSection         )
    Q_PROPERTY(bool     isEditGraphPointCnt     READ      getIsEditGraphPointCnt         NOTIFY      signalEventChangedIsEditGraphPointCnt    )
    Q_PROPERTY(quint16  isEditAutoSetting       READ      getIsEditAutoSetting           NOTIFY      signalEventChangedIsEditAutoSetting      )
    Q_PROPERTY(bool     isEditFilterCoefficient READ      getIsEditFilterCoefficient     NOTIFY      signalEventChangedIsEditFilterCoefficient)
    Q_PROPERTY(bool     isEditZeroDelayTime     READ      getIsEditZeroDelayTime         NOTIFY      signalEventChangedIsEditZeroDelayTime    )
    Q_PROPERTY(bool     isEditMeasureCueSign    READ      getIsEditMeasureCueSign        NOTIFY      signalEventChangedIsEditMeasureCueSign   )
    Q_PROPERTY(bool     isEditMeasureSection    READ      getIsEditMeasureSection        NOTIFY      signalEventChangedIsEditMeasureSection   )

public:
    quint64         mDspSeq = 0;

    static bool *   ptrIsFirst(){ static bool isFirst = true   ; return &isFirst;}
    static int *    ptrMinRang(){ static int  minRang = 0      ; return &minRang;}
    static int *    ptrMaxRang(){ static int  maxRang = 1000000; return &maxRang;}

    int             mRange                  = 0;
    int             mLineInterval           = 1000;

    qint16          mAdcValue               = 0;
    quint32         mEventValue             = 0;
    quint32         mTareWeight             = 0;
    quint16         mMaxPDCntPerMin         = 0;
    quint16         mCurrPDCntPerMin        = 0;
    quint16         mPDCntPerMin            = 0;

    bool            mIsRawGraphOn           = false;
    bool            mIsRunTimeGraphPause    = false;
    QList<quint32>  mRunTimeGraphPoints;
    QList<quint32>  mRunTimeRawGraphPoints;
    int             mTotalRuntimePointCnt   = 400;

    bool            mIsTimingGraphPause     = false;
    int             mMeasuredStartIdx       = -1;
    int             mMeasuredCueLineIdx     = -1;
    int             mMeasuredSectionLineIdx = -1;
    bool            mIsTimingGraphBuffering = false;
    int             mLastPointType          = 0;
    int             mXTimeInterval          = 10;
    quint16         mGraphPointCnt          = 10;
    quint16         mAutoSetting            = 0;
    quint16         mFilterCoefficient      = 0;
    quint16         mZeroDelayTime          = 0;
    quint32         mMeasureCueSign         = 0;
    quint32         mMeasureSection         = 0;

    bool            mIsEditGraphPointCnt    = false;
    bool            mIsEditAutoSetting      = false;
    bool            mIsEditFilterCoefficient= false;
    bool            mIsEditZeroDelayTime    = false;
    bool            mIsEditMeasureCueSign   = false;
    bool            mIsEditMeasureSection   = false;
    int             mTempMeasuredStartIdx       = -1;
    int             mTempMeasuredCueLineIdx     = -1;
    int             mTempMeasuredSectionLineIdx = -1;
    QList<quint32>  mTempTimingGraphPoints;
    QList<int>      mTempGraphMeasureStartIdxList;
    QList<int>      mTempGraphMeasurePointCntList;
    QList<quint32>  mTimingGraphPoints;
    QList<int>      mGraphMeasureStartIdxList;
    QList<int>      mGraphMeasurePointCntList;

    bool     getIsFirst                 (){return *ptrIsFirst()             ;}
    int      getMinRange                (){return *ptrMinRang()             ;}
    int      getMaxRange                (){return *ptrMaxRang()             ;}
    int      getRange                   (){return mRange                    ;}
    int      getLineInterval            (){return mLineInterval             ;}

    qint16   getAdcValue                (){return mAdcValue                 ;}
    qint32   getEventValue              (){return mEventValue               ;}
    qint32   getTareWeight              (){return mTareWeight               ;}
    qint16   getMaxPDCntPerMin          (){return mMaxPDCntPerMin           ;}
    qint16   getCurrPDCntPerMin         (){return mCurrPDCntPerMin          ;}
    qint16   getPDCntPerMin             (){return mPDCntPerMin              ;}

    bool     getIsRawGraphOn            (){return mIsRawGraphOn             ;}
    bool     getIsRunTimeGraphPause     (){return mIsRunTimeGraphPause      ;}
    int      getRuntimePointCnt         (){return mRunTimeGraphPoints.size();}

    bool     getIsTimingGraphPause      (){return mIsTimingGraphPause       ;}
    bool     getIsTimingGraphBuffering  (){return mIsTimingGraphBuffering   ;}
    int      getMeasuredStartIdx        (){return mMeasuredStartIdx         ;}
    int      getMeasuredCueLineIdx      (){return mMeasuredCueLineIdx       ;}
    int      getMeasuredSectionLineIdx  (){return mMeasuredSectionLineIdx   ;}
    int      getTimingPointCnt          (){return mTimingGraphPoints.size() ;}

    quint16  getGraphPointCnt           (){return mGraphPointCnt            ;}
    quint16  getAutoSetting             (){return mAutoSetting              ;}
    quint16  getFilterCoefficient       (){return mFilterCoefficient        ;}
    quint16  getZeroDelayTime           (){return mZeroDelayTime            ;}
    quint32  getMeasureCueSign          (){return mMeasureCueSign           ;}
    quint32  getMeasureSection          (){return mMeasureSection           ;}
    bool     getIsEditGraphPointCnt     (){return mIsEditGraphPointCnt      ;}
    bool     getIsEditAutoSetting       (){return mIsEditAutoSetting        ;}
    bool     getIsEditFilterCoefficient (){return mIsEditFilterCoefficient  ;}
    bool     getIsEditZeroDelayTime     (){return mIsEditZeroDelayTime      ;}
    bool     getIsEditMeasureCueSign    (){return mIsEditMeasureCueSign     ;}
    bool     getIsEditMeasureSection    (){return mIsEditMeasureSection     ;}

    void setIsFirst         (bool value)
    {
        (*ptrIsFirst()) = value;
    }

    void setMinRange        (int  value, bool force)
    {
        if(value == getMinRange() && force == false)
            return;

        (*ptrMinRang()) = value;

        if(getMinRange() > getMaxRange())
            setMaxRange(getMinRange() + 1, force);

        setLineInterval((getMaxRange() - getMinRange()) / 10);

        setRange(getMaxRange() - getMinRange());

        emit signalEventChangedMinRange(value);
    }
    void setMaxRange        (int  value, bool force)
    {
        if(value == getMaxRange() && force == false)
            return;

        (*ptrMaxRang()) = value;

        if(getMaxRange() < getMinRange())
            setMinRange(getMaxRange()-1, force);

        int newInterval = (getMaxRange() - getMinRange()) < 0 ? -1 * (getMaxRange() - getMinRange()) : (getMaxRange() - getMinRange());
        setLineInterval(newInterval / 10);

        setRange(getMaxRange() - getMinRange());

        emit signalEventChangedMaxRange(value);
    }
    void setRange                  (int     value){if(value == mRange                  ) return; mRange                   = value; emit signalEventChangedRange                  (value);}
    void setLineInterval           (int     value){if(value == mLineInterval           ) return; mLineInterval            = value; emit signalEventChangedLineInterval           (value);}

    void setAdcValue               (qint16  value){if(value == mAdcValue               ) return; mAdcValue                = value; emit signalEventChangedAdcValue               (value);}
    void setEventValue             (quint32 value){if(value == mEventValue             ) return; mEventValue              = value; emit signalEventChangedEventValue             (value);}
    void setTareWeight             (quint32 value){if(value == mTareWeight             ) return; mTareWeight              = value; emit signalEventChangedTareWeight             (value);}
    void setMaxPDCntPerMin         (qint16  value){if(value == mMaxPDCntPerMin         ) return; mMaxPDCntPerMin          = value; emit signalEventChangedMaxPDCntPerMin         (value);}
    void setCurrPDCntPerMin        (qint16  value){if(value == mCurrPDCntPerMin        ) return; mCurrPDCntPerMin         = value; emit signalEventChangedCurrPDCntPerMin        (value);}
    void setPDCntPerMin            (qint16  value){if(value == mPDCntPerMin            ) return; mPDCntPerMin             = value; emit signalEventChangedPDCntPerMin            (value);}

    void setIsRawGraphOn           (bool    value){if(value == mIsRawGraphOn           ) return; mIsRawGraphOn            = value; emit signalEventChangedIsRawGraphOn           (value);}
    void setIsRunTimeGraphPause    (bool    value){if(value == mIsRunTimeGraphPause    ) return; mIsRunTimeGraphPause     = value; emit signalEventChangedIsRunTimeGraphPause    (value);}

    void setTimingGraphPause       (bool    value){if(value == mIsTimingGraphPause     ) return; mIsTimingGraphPause      = value; emit signalEventChangedIsTimingGraphPause     (value);}
    void setTimingGraphBuffering   (bool    value){if(value == mIsTimingGraphBuffering ) return; mIsTimingGraphBuffering  = value; emit signalEventChangedIsTimingGraphBuffering (value);}
    void setMeasuredStartIdx       (int     value){if(value == mMeasuredStartIdx       ) return; mMeasuredStartIdx        = value; emit signalEventChangedMeasuredStartIdx       (value);}
    void setMeasuredCueLineIdx     (int     value){if(value == mMeasuredCueLineIdx     ) return; mMeasuredCueLineIdx      = value; emit signalEventChangedMeasuredCueLineIdx     (value);}
    void setMeasuredSectionLineIdx (int     value){if(value == mMeasuredSectionLineIdx ) return; mMeasuredSectionLineIdx  = value; emit signalEventChangedMeasuredSectionLineIdx (value);}
    void setGraphPointCnt          (int     value){if(value == mGraphPointCnt          ) return; mGraphPointCnt           = value; setIsEditGraphPointCnt(true)   ;  emit signalEventChangedGraphPointCnt    (value);}
    void setAutoSetting            (quint16 value){if(value == mAutoSetting            ) return; mAutoSetting             = value; setIsEditAutoSetting(true)     ;  emit signalEventChangedAutoSetting      (value);}
    void setFilterCoefficient      (quint16 value){if(value == mFilterCoefficient      ) return; mFilterCoefficient       = value; setIsEditFilterCoefficient(true); emit signalEventChangedFilterCoefficient(value);}
    void setZeroDelayTime          (quint16 value){if(value == mZeroDelayTime          ) return; mZeroDelayTime           = value; setIsEditZeroDelayTime(true)   ;  emit signalEventChangedZeroDelayTime    (value);}
    void setMeasureCueSign         (quint32 value)
    {
        mMeasureCueSign          = value;
        setIsEditMeasureCueSign   (true);
        emit signalEventChangedMeasureCueSign   (value);

        if(mMeasuredStartIdx > 0)
        {
            setMeasuredCueLineIdx(mMeasuredStartIdx + (value / mXTimeInterval));
            setMeasuredSectionLineIdx(mMeasuredCueLineIdx + (mMeasureSection / mXTimeInterval));
        }
    }
    void setMeasureSection         (quint32 value)
    {
        mMeasureSection          = value;
        setIsEditMeasureSection   (true);
        emit signalEventChangedMeasureSection   (value);

        if(mMeasuredStartIdx > 0)
        {
            setMeasuredSectionLineIdx(mMeasuredCueLineIdx + (value / mXTimeInterval));
        }
    }
    void setIsEditGraphPointCnt    (bool    value){if(value == mIsEditGraphPointCnt    ) return; mIsEditGraphPointCnt     = value; emit signalEventChangedIsEditGraphPointCnt    (value);}
    void setIsEditAutoSetting      (bool    value){if(value == mIsEditAutoSetting      ) return; mIsEditAutoSetting       = value; emit signalEventChangedIsEditAutoSetting      (value);}
    void setIsEditFilterCoefficient(bool    value){if(value == mIsEditFilterCoefficient) return; mIsEditFilterCoefficient = value; emit signalEventChangedIsEditFilterCoefficient(value);}
    void setIsEditZeroDelayTime    (bool    value){if(value == mIsEditZeroDelayTime    ) return; mIsEditZeroDelayTime     = value; emit signalEventChangedIsEditZeroDelayTime    (value);}
    void setIsEditMeasureCueSign   (bool    value){if(value == mIsEditMeasureCueSign   ) return; mIsEditMeasureCueSign    = value; emit signalEventChangedIsEditMeasureCueSign   (value);}
    void setIsEditMeasureSection   (bool    value){if(value == mIsEditMeasureSection   ) return; mIsEditMeasureSection    = value; emit signalEventChangedIsEditMeasureSection   (value);}

signals:
    void signalEventChangedRange                  (int     value);
    void signalEventChangedMinRange               (int     value);
    void signalEventChangedMaxRange               (int     value);
    void signalEventChangedLineInterval           (int     value);
    void signalEventChangedAdcValue               (qint16  value);
    void signalEventChangedEventValue             (qint32  value);
    void signalEventChangedTareWeight             (qint32  value);
    void signalEventChangedMaxPDCntPerMin         (qint16  value);
    void signalEventChangedCurrPDCntPerMin        (qint16  value);
    void signalEventChangedPDCntPerMin            (qint16  value);
    void signalEventChangedIsRawGraphOn           (bool    value);
    void signalEventChangedIsRunTimeGraphPause    (bool    value);
    void signalEventChangedRuntimePointCnt        (int     value);
    void signalEventChangedIsTimingGraphPause     (bool    value);
    void signalEventChangedIsTimingGraphBuffering (bool    value);
    void signalEventChangedMeasuredStartIdx       (int     value);
    void signalEventChangedMeasuredCueLineIdx     (int     value);
    void signalEventChangedMeasuredSectionLineIdx (int     value);
    void signalEventChangedTimingPointCnt         (int     value);
    void signalEventChangedGraphPointCnt          (quint16 value);
    void signalEventChangedAutoSetting            (quint16 value);
    void signalEventChangedFilterCoefficient      (quint16 value);
    void signalEventChangedZeroDelayTime          (quint16 value);
    void signalEventChangedMeasureCueSign         (quint32 value);
    void signalEventChangedMeasureSection         (quint32 value);
    void signalEventChangedIsEditGraphPointCnt    (bool    value);
    void signalEventChangedIsEditAutoSetting      (bool    value);
    void signalEventChangedIsEditFilterCoefficient(bool    value);
    void signalEventChangedIsEditZeroDelayTime    (bool    value);
    void signalEventChangedIsEditMeasureCueSign   (bool    value);
    void signalEventChangedIsEditMeasureSection   (bool    value);

    void signalEventChangedGraph            (          );

    void signalEventChangedTimingGraph      (          );

    void signalCommandSetWeightCheckerGraphOn( quint16 deviceSeq, bool value);

public slots:
    Q_INVOKABLE void onCommandZERO()
    {
        CHECK_FALSE_RETURN((mDspSeq != 0));

        pDspSP->sendZeroCmd(mDspSeq);
    }

    Q_INVOKABLE void                        onCommandRawGraphOn                 (bool value){setIsRawGraphOn         (value);}
    Q_INVOKABLE void                        onCommandIsRuntimeGraphPause        (bool value){setIsRunTimeGraphPause  (value);}
    Q_INVOKABLE void                        onCommandSetMinRange                (int  value){setMinRange             (value, false);}
    Q_INVOKABLE void                        onCommandSetMaxRange                (int  value){setMaxRange             (value, false);}
    Q_INVOKABLE int                         onCommandGetTimingPointValue        (int  idx  ){ return mTimingGraphPoints.at(idx) - getMinRange();    }
    Q_INVOKABLE int                         onCommandMeasureAreaCnt             (          ){ return mGraphMeasureStartIdxList.size();              }
    Q_INVOKABLE int                         onCommandGetGraphMeasurePointCntList(int  idx  ){ return mGraphMeasurePointCntList.at(idx);             }
    Q_INVOKABLE int                         onCommandGetGraphMeasureStartIdxList(int  idx  ){ return mGraphMeasureStartIdxList.at(idx);             }
    Q_INVOKABLE int                         onCommandGetRuntimeRawPointValue    (int  idx  ){ return mRunTimeRawGraphPoints.at(idx) - getMinRange();}
    Q_INVOKABLE int                         onCommandGetRuntimePointValue       (int  idx  ){ return mRunTimeGraphPoints.at(idx) - getMinRange();   }
    Q_INVOKABLE int                         onCommandApply                      (          ){
        DevSettingDto devSetting = pLSettingSP->mDevSetting;
        PDSettingDto pdSetting = pProductSP->mCurrPD;

        pdSetting.mDspForm.mWCSetting.mAutoSetting        = mAutoSetting;
        pdSetting.mDspForm.mWCSetting.mFilterCoefficient  = mFilterCoefficient;
        pdSetting.mDspForm.mWCSetting.mZeroDelayTime      = mZeroDelayTime;
        pdSetting.mDspForm.mWCSetting.mMeasureCueSign     = mMeasureCueSign;
        pdSetting.mDspForm.mWCSetting.mMeasureSection     = mMeasureSection;

        int ret = pProductSP->editPD(pdSetting);

        setIsEditAutoSetting(false);
        setIsEditFilterCoefficient(false);
        setIsEditZeroDelayTime(false);
        setIsEditMeasureCueSign(false);
        setIsEditMeasureSection(false);

        devSetting.mDspForm.mWCSetting.mGraphPointCnt = mGraphPointCnt;

        pLSettingSP->setDevSetting(devSetting);

        setIsEditGraphPointCnt(false);

        mXTimeInterval = 100 / mGraphPointCnt;

        return ret;
    }

    Q_INVOKABLE void onCommandCancel()
    {
        loadPDSetting();
        loadDevSetting();

        if(mXTimeInterval != 0)
        {
            setMeasuredCueLineIdx(getMeasuredStartIdx() + (mMeasureCueSign / mXTimeInterval));
            setMeasuredSectionLineIdx(getMeasuredCueLineIdx() + (mMeasureSection / mXTimeInterval));
        }
    }

    Q_INVOKABLE void onCommandSetGraphPointCnt(int cnt)
    {
        setGraphPointCnt(cnt);
    }

    Q_INVOKABLE void onCommandSetAutoSetting(quint16 value)
    {
        setAutoSetting(value);
    }

    Q_INVOKABLE void onCommandSetFilterCoefficient(quint16 value)
    {
        setFilterCoefficient(value);
    }
    Q_INVOKABLE void onCommandSetZeroDelayTime(quint16 value)
    {
        setZeroDelayTime(value);
    }

    Q_INVOKABLE void onCommandSetMeasureCueSignLineIdx(int value)
    {
        if(value < mMeasuredStartIdx)
            value = mMeasuredStartIdx + 1;

        value = value - mMeasuredStartIdx;

        setMeasureCueSign(value * mXTimeInterval);
    }

    Q_INVOKABLE void onCommandSetMeasureSectionLineIdx(int value)
    {
        if(value < mMeasuredCueLineIdx)
            value = mMeasuredCueLineIdx + 1;

        //setMeasuredSectionLineIdx(value);

        value = value - mMeasuredCueLineIdx;

        setMeasureSection(value * mXTimeInterval);
    }

    Q_INVOKABLE void onCommandSetMeasureCueSign(quint32 value)
    {
        setMeasureCueSign(value);
    }

    Q_INVOKABLE void onCommandSetMeasureSection(quint32 value)
    {
        setMeasureSection(value);
    }

    Q_INVOKABLE void onCommandSetTimingGraphPlayPause()
    {
        setTimingGraphPause(!mIsTimingGraphPause);
    }

public slots:
    void onChangedDspStatus(quint64 dspSeq, DspStatusDto dto)
    {
        CHECK_FALSE_RETURN((dspSeq == mDspSeq));

        setEventValue     (dto.mWCStatus.mCurrWeight     );
        setMaxPDCntPerMin (dto.mWCStatus.mMaxPDCntPerMin );
        setCurrPDCntPerMin(dto.mWCStatus.mCurrPDCntPerMin);
        setPDCntPerMin    (dto.mWCStatus.mPDCntPerMin    );
        setAdcValue       (dto.mWCStatus.mADC            );

        if(pProductSP->mCurrPD.mDspForm.mWCSetting.mAutoSetting)
        {
            if(   dto.mWCStatus.mFilterCoefficient != pProductSP->mCurrPD.mDspForm.mWCSetting.mFilterCoefficient
               || dto.mWCStatus.mMeasureCueSign    != pProductSP->mCurrPD.mDspForm.mWCSetting.mMeasureCueSign
               || dto.mWCStatus.mMeasureSection    != pProductSP->mCurrPD.mDspForm.mWCSetting.mMeasureSection   )
            {
                PDSettingDto pdSetting =  pProductSP->mCurrPD;
                pdSetting.mDspForm.mWCSetting.mFilterCoefficient = dto.mWCStatus.mFilterCoefficient;
                pdSetting.mDspForm.mWCSetting.mMeasureCueSign    = dto.mWCStatus.mMeasureCueSign   ;
                pdSetting.mDspForm.mWCSetting.mMeasureSection    = dto.mWCStatus.mMeasureSection   ;

                pProductSP->editPD(pdSetting);

                loadPDSetting();
            }
        }
    }

    void onAddedWCG(quint64 dspSeq, DspWCGDto dto)
    {
        CHECK_FALSE_RETURN((mDspSeq == dspSeq));

        writeGraphData(dto);

        StDspWCG * pGData = (StDspWCG *)dto.mGraphData.data();

        mTotalRuntimePointCnt = pGData->mPointCnt * 20;

        for(int i = 0; i < pGData->mPointCnt; i ++)
        {
            while(mRunTimeRawGraphPoints.size()+ 1 > mTotalRuntimePointCnt)
            {
                mRunTimeRawGraphPoints.removeAt(0);
                mRunTimeGraphPoints.removeAt(0);
            }

            mRunTimeRawGraphPoints.append(pGData->mPoints[i].mRawValue - pProductSP->mCurrPD.mDspForm.mWCSetting.mTareWeight);
            mRunTimeGraphPoints.append(pGData->mPoints[i].mFilterValue - pProductSP->mCurrPD.mDspForm.mWCSetting.mTareWeight);

            if((mLastPointType == 3 && pGData->mPoints[i].mPointType != 3 && mTempGraphMeasureStartIdxList.size() > 4)
              ||(mLastPointType != 0 && pGData->mPoints[i].mPointType == 0))
            {
                updateTimingGraph();
            }

            if(pGData->mPoints[i].mPointType != 0)
            {
                mTempTimingGraphPoints.append(pGData->mPoints[i].mFilterValue - pProductSP->mCurrPD.mDspForm.mWCSetting.mTareWeight);
            }

            if(pGData->mPoints[i].mPointType == 3)
            {
                if(mLastPointType != 3)
                {
                    mTempGraphMeasureStartIdxList.append(mTempTimingGraphPoints.size() - 1);
                    mTempGraphMeasurePointCntList.append(1);
                    mTempMeasuredCueLineIdx = mTempTimingGraphPoints.size() - 1;
                    mTempMeasuredSectionLineIdx = mTempMeasuredCueLineIdx + (mMeasureSection / mXTimeInterval);
                    mTempMeasuredStartIdx = mTempMeasuredCueLineIdx  - (mMeasureCueSign / mXTimeInterval);
                }
                else
                {
                    mTempGraphMeasurePointCntList[mTempGraphMeasurePointCntList.size() - 1] = mTempGraphMeasurePointCntList[mTempGraphMeasurePointCntList.size() - 1] + 1;
                }
            }

            if(mLastPointType != pGData->mPoints[i].mPointType)
            {
                qDebug() << "[debug] changed point type :" << pGData->mPoints[i].mPointType;
            }

            mLastPointType = pGData->mPoints[i].mPointType;
        }

        emit signalEventChangedGraph();
    }

public :
    explicit PanelWCGraphModel(QObject *parent = nullptr):QObject(parent)
    {
        qint32 maxRange = (pProductSP->mCurrPD.mDspForm.mWCSetting.mOverWeight * 1.2);
        qint32 minRange = (pProductSP->mCurrPD.mDspForm.mWCSetting.mTareWeight) * -1;

        loadPDSetting();
        loadDevSetting();

        setTareWeight(pProductSP->mCurrPD.mDspForm.mWCSetting.mTareWeight);

        if(getIsFirst())
        {
            maxRange = ((maxRange + 500) / 1000) * 1000;
            setMaxRange(maxRange, true);
            setMinRange(minRange, true);
        }
        else
        {
            setMaxRange(getMaxRange(), true);
        }

        setIsFirst(false);

        CHECK_FALSE_RETURN((pDspSP->mDspList.size() > 0));

        mDspSeq = pDspSP->mDspList[0]->mSeq;

        ENABLE_SLOT_DSP_ADDED_WCG;
        ENABLE_SLOT_DSP_CHANGED_DSP_STATUS;

        pDspSP->sendWCGraphOnCmd(mDspSeq, true);
    }
    ~PanelWCGraphModel()
    {
        CHECK_FALSE_RETURN((mDspSeq != 0));

        closeFile();
        pDspSP->sendWCGraphOnCmd(mDspSeq, false);
    }

    void updateTimingGraph()
    {
        if(mIsTimingGraphPause)
        {
            mTempTimingGraphPoints.clear();
            mTempGraphMeasureStartIdxList.clear();
            mTempGraphMeasurePointCntList.clear();
            return;
        }

        mTimingGraphPoints = mTempTimingGraphPoints;
        mGraphMeasureStartIdxList = mTempGraphMeasureStartIdxList;
        mGraphMeasurePointCntList = mTempGraphMeasurePointCntList;
        setMeasuredCueLineIdx(mTempMeasuredCueLineIdx);
        setMeasuredSectionLineIdx(mTempMeasuredSectionLineIdx);
        setMeasuredStartIdx(mTempMeasuredStartIdx);

        mTempTimingGraphPoints.clear();
        mTempGraphMeasureStartIdxList.clear();
        mTempGraphMeasurePointCntList.clear();

        emit signalEventChangedTimingPointCnt(mTimingGraphPoints.size());
        emit signalEventChangedTimingGraph();
    }

    void loadPDSetting()
    {
        setAutoSetting      (pProductSP->mCurrPD.mDspForm.mWCSetting.mAutoSetting);
        setFilterCoefficient(pProductSP->mCurrPD.mDspForm.mWCSetting.mFilterCoefficient);
        setZeroDelayTime    (pProductSP->mCurrPD.mDspForm.mWCSetting.mZeroDelayTime);
        setMeasureCueSign   (pProductSP->mCurrPD.mDspForm.mWCSetting.mMeasureCueSign);
        setMeasureSection   (pProductSP->mCurrPD.mDspForm.mWCSetting.mMeasureSection);

        setIsEditAutoSetting(false);
        setIsEditFilterCoefficient(false);
        setIsEditZeroDelayTime(false);
        setIsEditMeasureCueSign(false);
        setIsEditMeasureSection(false);
    }

    void loadDevSetting()
    {
        setGraphPointCnt(pLSettingSP->mDevSetting.mDspForm.mWCSetting.mGraphPointCnt);

        setIsEditGraphPointCnt(false);

        mXTimeInterval = 100 / mGraphPointCnt;
    }

private:
    bool mLastIsRawGraphOn = false;
    FileWriterEx * mpFileWriter = nullptr;

    void openFile()
    {
        closeFile();

        mpFileWriter = new FileWriterEx(this);
        mpFileWriter->open(FileDef::WC_GRAPH_DIR(), QString("%1.txt").arg(QDateTime::currentDateTime().toString(DATE_TIME_FILE_NAME_FMT))/*FileDef::WC_GRAPH_FILENAME()*/, FileWriterEx::FILE_OPEN_NEWWRITE);
    }

    void closeFile()
    {
        if(mpFileWriter != nullptr)
        {
            mpFileWriter->close();
            delete mpFileWriter;
            mpFileWriter = nullptr;
        }
    }

    void writeGraphData(DspWCGDto dto)
    {
        if(mLastIsRawGraphOn != mIsRawGraphOn)
        {
            if(mIsRawGraphOn)
                openFile();
            else
                closeFile();
        }

        mLastIsRawGraphOn = mIsRawGraphOn;

        if(mpFileWriter != nullptr)
        {
            StDspWCG * pGData = (StDspWCG *)dto.mGraphData.data();

            for(int i = 0; i < pGData->mPointCnt; i ++)
            {
                if(mpFileWriter->newWrite(QString("%1,%2,%3\n").arg((int)(pGData->mPoints[i].mFilterValue)).arg((int)(pGData->mPoints[i].mRawValue)).arg((int)(pGData->mPoints[i].mPointType))) == false)
                {
                    qDebug() << "[PanelWCGraphModel::writeGraphData] graph write error!";
                    closeFile();
                }
            }
        }
    }
};

#endif // PANELWCGRAPHMODEL_H
