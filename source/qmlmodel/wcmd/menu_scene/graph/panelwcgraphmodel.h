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
    Q_PROPERTY(bool     isEditable              READ      getIsEditable                  NOTIFY      signalEventChangedIsEditable             )
    Q_PROPERTY(bool     isRawGraphOn            READ      getIsRawGraphOn                NOTIFY      signalEventChangedIsRawGraphOn           )
    Q_PROPERTY(bool     isPause                 READ      getIsPause                     NOTIFY      signalEventChangedIsPause                )
    Q_PROPERTY(int      minRange                READ      getMinRange                    NOTIFY      signalEventChangedMinRange               )
    Q_PROPERTY(int      maxRange                READ      getMaxRange                    NOTIFY      signalEventChangedMaxRange               )
    Q_PROPERTY(qint32   eventValue              READ      getEventValue                  NOTIFY      signalEventChangedEventValue             )
    Q_PROPERTY(qint16   maxPDCntPerMin          READ      getMaxPDCntPerMin              NOTIFY      signalEventChangedMaxPDCntPerMin         )
    Q_PROPERTY(qint16   currPDCntPerMin         READ      getCurrPDCntPerMin             NOTIFY      signalEventChangedCurrPDCntPerMin        )
    Q_PROPERTY(qint16   pdCntPerMin             READ      getPDCntPerMin                 NOTIFY      signalEventChangedPDCntPerMin            )
    Q_PROPERTY(int      range                   READ      getRange                       NOTIFY      signalEventChangedRange                  )
    Q_PROPERTY(int      measuredStartIdx        READ      getMeasuredStartIdx            NOTIFY      signalEventChangedMeasuredStartIdx       )
    Q_PROPERTY(int      measuredCueLineIdx      READ      getMeasuredCueLineIdx          NOTIFY      signalEventChangedMeasuredCueLineIdx     )
    Q_PROPERTY(int      measuredSectionLineIdx  READ      getMeasuredSectionLineIdx      NOTIFY      signalEventChangedMeasuredSectionLineIdx )
    Q_PROPERTY(int      lineInterval            READ      getLineInterval                NOTIFY      signalEventChangedLineInterval           )
    Q_PROPERTY(int      totalRuntimePointCnt    READ      getTotalRuntimePointCnt        NOTIFY      signalEventChangedTotalRuntimePointCnt   )
    Q_PROPERTY(int      runtimePointCnt         READ      getRuntimePointCnt             NOTIFY      signalEventChangedRuntimePointCnt        )
    Q_PROPERTY(int      timingPointCnt          READ      getTimingPointCnt              NOTIFY      signalEventChangedTimingPointCnt         )
    Q_PROPERTY(bool     diffCueSignGab          READ      getDiffCueSignGab              NOTIFY      signalEventChangedDiffCueSignGab         )
    Q_PROPERTY(bool     diffSectionGab          READ      getDiffSectionGab              NOTIFY      signalEventChangedDiffSectionGab         )

    Q_PROPERTY(quint16  filterCoefficient       READ      getFilterCoefficient           NOTIFY      signalEventChangedFilterCoefficient      )
    Q_PROPERTY(quint32  measureCueSign          READ      getMeasureCueSign              NOTIFY      signalEventChangedMeasureCueSign         )
    Q_PROPERTY(quint32  measureSection          READ      getMeasureSection              NOTIFY      signalEventChangedMeasureSection         )
    Q_PROPERTY(bool     isEditFilterCoefficient READ      getIsEditFilterCoefficient     NOTIFY      signalEventChangedIsEditFilterCoefficient)
    Q_PROPERTY(bool     isEditMeasureCueSign    READ      getIsEditMeasureCueSign        NOTIFY      signalEventChangedIsEditMeasureCueSign   )
    Q_PROPERTY(bool     isEditMeasureSection    READ      getIsEditMeasureSection        NOTIFY      signalEventChangedIsEditMeasureSection   )

public:
    quint64                mDspSeq = 0;

    int                     mLastPointType     = 0;
    QList<quint32>          mRunTimeGraphPoints;
    QList<quint32>          mRunTimeRawGraphPoints;
    QList<quint32>          mTempTimingGraphPoints;
    QList<quint32>          mTimingGraphPoints;
    QList<int>              mGraphMeasureStartIdxList;
    QList<int>              mGraphMeasurePointCntList;

    bool                    mIsEditable             = false;
    bool                    mIsRawGraphOn           = false;
    bool                    mIsPause                = false;
    quint32                 mEventValue             = 0;
    quint16                 mMaxPDCntPerMin         = 0;
    quint16                 mCurrPDCntPerMin        = 0;
    quint16                 mPDCntPerMin            = 0;
    int                     mRange                  = 0;
    int                     mMeasuredStartIdx       = -1;
    int                     mMeasuredCueLineIdx     = -1;
    int                     mMeasuredSectionLineIdx = -1;
    int                     mLineInterval           = 1000;
    int                     mXTimeInterval          = 0;
    int                     mTotalRuntimePointCnt   = 400;
    bool                    mDiffCueSignGab         = false;
    bool                    mDiffSectionGab         = false;

    quint16                 mFilterCoefficient      = 0;
    quint32                 mMeasureCueSign         = 0;
    quint32                 mMeasureSection         = 0;
    bool                    mIsEditFilterCoefficient= false;
    bool                    mIsEditMeasureCueSign   = false;
    bool                    mIsEditMeasureSection   = false;

    static int * ptrMinRang(){ static int minRang = 0; return &minRang;}
    static int * ptrMaxRang(){ static int maxRang = 999999; return &maxRang;}

    bool    getIsEditable             (){return mIsEditable               ;}
    bool    getIsRawGraphOn           (){return mIsRawGraphOn             ;}
    bool    getIsPause                (){return mIsPause                  ;}
    int     getMinRange               (){return *ptrMinRang()             ;}
    int     getMaxRange               (){return *ptrMaxRang()             ;}
    qint32  getEventValue             (){return mEventValue               ;}
    qint16  getMaxPDCntPerMin         (){return mMaxPDCntPerMin           ;}
    qint16  getCurrPDCntPerMin        (){return mCurrPDCntPerMin          ;}
    qint16  getPDCntPerMin            (){return mPDCntPerMin              ;}
    int     getRange                  (){return mRange                    ;}
    int     getMeasuredStartIdx       (){return mMeasuredStartIdx         ;}
    int     getMeasuredCueLineIdx     (){return mMeasuredCueLineIdx       ;}
    int     getMeasuredSectionLineIdx (){return mMeasuredSectionLineIdx   ;}
    int     getLineInterval           (){return mLineInterval             ;}
    int     getTotalRuntimePointCnt   (){return mTotalRuntimePointCnt     ;}
    int     getRuntimePointCnt        (){return mRunTimeGraphPoints.size();}
    int     getTimingPointCnt         (){return mTimingGraphPoints.size() ;}
    bool    getDiffCueSignGab         (){return mDiffCueSignGab           ;}
    bool    getDiffSectionGab         (){return mDiffSectionGab           ;}

    quint16 getFilterCoefficient      (){return mFilterCoefficient        ;}
    quint32 getMeasureCueSign         (){return mMeasureCueSign           ;}
    quint32 getMeasureSection         (){return mMeasureSection           ;}
    bool    getIsEditFilterCoefficient(){return mIsEditFilterCoefficient  ;}
    bool    getIsEditMeasureCueSign   (){return mIsEditMeasureCueSign     ;}
    bool    getIsEditMeasureSection   (){return mIsEditMeasureSection     ;}

    void setIsEditable      (bool value){if(value == mIsEditable      ) return; mIsEditable       = value; emit signalEventChangedIsEditable      (value);}
    void setIsRawGraphOn    (bool value){if(value == mIsRawGraphOn    ) return; mIsRawGraphOn     = value; emit signalEventChangedIsRawGraphOn    (value);}
    void setIsPause         (bool value){if(value == mIsPause         ) return; mIsPause          = value; emit signalEventChangedIsPause         (value);}
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
    void setEventValue             (quint32 value){if(value == mEventValue             ) return; mEventValue              = value; emit signalEventChangedEventValue             (value);}
    void setMaxPDCntPerMin         (qint16  value){if(value == mMaxPDCntPerMin         ) return; mMaxPDCntPerMin          = value; emit signalEventChangedMaxPDCntPerMin         (value);}
    void setCurrPDCntPerMin        (qint16  value){if(value == mCurrPDCntPerMin        ) return; mCurrPDCntPerMin         = value; emit signalEventChangedCurrPDCntPerMin        (value);}
    void setPDCntPerMin            (qint16  value){if(value == mPDCntPerMin            ) return; mPDCntPerMin             = value; emit signalEventChangedPDCntPerMin            (value);}
    void setRange                  (int     value){if(value == mRange                  ) return; mRange                   = value; emit signalEventChangedRange                  (value);}
    void setMeasuredStartIdx       (int     value){if(value == mMeasuredStartIdx       ) return; mMeasuredStartIdx        = value; emit signalEventChangedMeasuredStartIdx       (value);}
    void setMeasuredCueLineIdx     (int     value){if(value == mMeasuredCueLineIdx     ) return; mMeasuredCueLineIdx      = value; emit signalEventChangedMeasuredCueLineIdx     (value);}
    void setMeasuredSectionLineIdx (int     value){if(value == mMeasuredSectionLineIdx ) return; mMeasuredSectionLineIdx  = value; emit signalEventChangedMeasuredSectionLineIdx (value);}
    void setLineInterval           (int     value){if(value == mLineInterval           ) return; mLineInterval            = value; emit signalEventChangedLineInterval           (value);}
    void setDiffCueSignGab         (bool    value){if(value == mDiffCueSignGab         ) return; mDiffCueSignGab          = value; qDebug() << "[debug]mDiffCueSignGab : " << mDiffCueSignGab; emit signalEventChangedDiffCueSignGab         (value);}
    void setDiffSectionGab         (bool    value){if(value == mDiffSectionGab         ) return; mDiffSectionGab          = value; qDebug() << "[debug]mDiffSectionGab : " << mDiffSectionGab; emit signalEventChangedDiffSectionGab         (value);}

    void setFilterCoefficient      (quint16 value){if(value == mFilterCoefficient      ) return; mFilterCoefficient       = value; setIsEditFilterCoefficient(true); emit signalEventChangedFilterCoefficient(value);}
    void setMeasureCueSign         (quint32 value){if(value == mMeasureCueSign         ) return; mMeasureCueSign          = value; setIsEditMeasureCueSign   (true); emit signalEventChangedMeasureCueSign   (value);}
    void setMeasureSection         (quint32 value){if(value == mMeasureSection         ) return; mMeasureSection          = value; setIsEditMeasureSection   (true); emit signalEventChangedMeasureSection   (value);}
    void setIsEditFilterCoefficient(bool    value){if(value == mIsEditFilterCoefficient) return; mIsEditFilterCoefficient = value; emit signalEventChangedIsEditFilterCoefficient(value);}
    void setIsEditMeasureCueSign   (bool    value){if(value == mIsEditMeasureCueSign   ) return; mIsEditMeasureCueSign    = value; emit signalEventChangedIsEditMeasureCueSign   (value);}
    void setIsEditMeasureSection   (bool    value){if(value == mIsEditMeasureSection   ) return; mIsEditMeasureSection    = value; emit signalEventChangedIsEditMeasureSection   (value);}

signals:
    void signalEventChangedIsEditable             (bool    value);
    void signalEventChangedIsRawGraphOn           (bool    value);
    void signalEventChangedIsPause                (bool    value);
    void signalEventChangedMinRange               (int     value);
    void signalEventChangedMaxRange               (int     value);
    void signalEventChangedEventValue             (quint32 value);
    void signalEventChangedMaxPDCntPerMin         (qint16  value);
    void signalEventChangedCurrPDCntPerMin        (qint16  value);
    void signalEventChangedPDCntPerMin            (qint16  value);
    void signalEventChangedRange                  (int     value);
    void signalEventChangedMeasuredStartIdx       (int     value);
    void signalEventChangedMeasuredCueLineIdx     (int     value);
    void signalEventChangedMeasuredSectionLineIdx (int     value);
    void signalEventChangedLineInterval           (int     value);
    void signalEventChangedTotalRuntimePointCnt   (int     value);
    void signalEventChangedRuntimePointCnt        (int     value);
    void signalEventChangedTimingPointCnt         (int     value);
    void signalEventChangedDiffCueSignGab         (bool    value);
    void signalEventChangedDiffSectionGab         (bool    value);
    void signalEventChangedFilterCoefficient      (quint16 value);
    void signalEventChangedMeasureCueSign         (quint32 value);
    void signalEventChangedMeasureSection         (quint32 value);
    void signalEventChangedIsEditFilterCoefficient(bool    value);
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

    Q_INVOKABLE void                        onCommandRawGraphOn             (bool value){setIsRawGraphOn(value);}
    Q_INVOKABLE void                        onCommandIsPause                (bool value){setIsPause     (value);}
    Q_INVOKABLE void                        onCommandSetMinRange            (int  value){setMinRange    (value, false);}
    Q_INVOKABLE void                        onCommandSetMaxRange            (int  value){setMaxRange    (value, false);}
    Q_INVOKABLE int                         onCommandGetTimingPointValue    (int  idx  )
    {
        return mTimingGraphPoints.at(idx) - getMinRange();
    }

    Q_INVOKABLE int onCommandMeasureAreaCnt()
    {
        return mGraphMeasureStartIdxList.size();
    }

    Q_INVOKABLE int onCommandGetGraphMeasurePointCntList(int idx)
    {
        return mGraphMeasurePointCntList.at(idx);
    }

    Q_INVOKABLE int onCommandGetGraphMeasureStartIdxList(int idx)
    {
        return mGraphMeasureStartIdxList.at(idx);
    }

    Q_INVOKABLE int                         onCommandGetRuntimeRawPointValue(int  idx  )
    {
        return mRunTimeRawGraphPoints.at(idx) - getMinRange();
    }
    Q_INVOKABLE int                         onCommandGetRuntimePointValue   (int  idx  )
    {
        return mRunTimeGraphPoints.at(idx) - getMinRange();
    }

    Q_INVOKABLE int onCommandApply()
    {
        PDSettingDto dto = pProductSP->mCurrPD;

        dto.mDspForm.mWCSetting.mFilterCoefficient  = mFilterCoefficient;
        dto.mDspForm.mWCSetting.mMeasureCueSign     = mMeasureCueSign;
        dto.mDspForm.mWCSetting.mMeasureSection     = mMeasureSection;

        int ret = pProductSP->editPD(dto);

        setIsEditFilterCoefficient(false);
        setIsEditMeasureCueSign(false);
        setIsEditMeasureSection(false);

        return ret;
    }

    Q_INVOKABLE void onCommandCancel()
    {
        loadPDSetting();

        if(mXTimeInterval != 0)
        {
            setMeasuredCueLineIdx(getMeasuredStartIdx() + (mMeasureCueSign / mXTimeInterval));
            setMeasuredSectionLineIdx(getMeasuredCueLineIdx() + (mMeasureSection / mXTimeInterval));
        }
    }

    Q_INVOKABLE void onCommandSetFilterCoefficient(quint16 value)
    {
        setFilterCoefficient(value);
    }


    Q_INVOKABLE void onCommandSetMeasureCueSignLineIdx(int value)
    {
        qDebug() << "[debug] onCommandSetMeasureSectionLineIdx : value = " << value;

        if(mIsEditable == false) return;

        if(mXTimeInterval == 0)
        {
            qDebug() << "[debug] onCommandSetMeasureCueSignLineIdx : Invaild x time interval = " << mXTimeInterval;
            return;
        }

        if(value < mMeasuredStartIdx)
            value = mMeasuredStartIdx + 1;

        setMeasuredSectionLineIdx(value + mMeasuredSectionLineIdx - mMeasuredCueLineIdx);
        setMeasuredCueLineIdx(value);

        value = value - mMeasuredStartIdx;

        qDebug() << "[debug] onCommandSetMeasureSectionLineIdx : x time interval = " << mXTimeInterval;
        qDebug() << "[debug] onCommandSetMeasureSectionLineIdx : gab value = " << value;

        setMeasureCueSign(value * mXTimeInterval);

    }

    Q_INVOKABLE void onCommandSetMeasureSectionLineIdx(int value)
    {
        qDebug() << "[debug] onCommandSetMeasureSectionLineIdx : value = " << value;

        if(mIsEditable == false) return;

        if(mXTimeInterval == 0)
        {
            qDebug() << "[debug] onCommandSetMeasureSectionLineIdx : Invaild x time interval = " << mXTimeInterval;
            return;
        }

        if(value < mMeasuredCueLineIdx)
            value = mMeasuredCueLineIdx + 1;

        setMeasuredSectionLineIdx(value);

        value = value - mMeasuredCueLineIdx;

        qDebug() << "[debug] onCommandSetMeasureSectionLineIdx : x time interval = " << mXTimeInterval;
        qDebug() << "[debug] onCommandSetMeasureSectionLineIdx : gab value = " << value;

        setMeasureSection(value * mXTimeInterval);
    }

    Q_INVOKABLE void onCommandSetMeasureCueSign(quint32 value)
    {
        if(mIsEditable == false)
            setMeasureCueSign(value);
        else
            onCommandSetMeasureCueSignLineIdx(getMeasuredStartIdx() + (value / mXTimeInterval));
    }

    Q_INVOKABLE void onCommandSetMeasureSection(quint32 value)
    {
        if(mIsEditable == false)
            setMeasureSection(value);
        else
            onCommandSetMeasureSectionLineIdx(getMeasuredCueLineIdx() + (value / mXTimeInterval));
    }

public slots:
    void onChangedDspStatus(quint64 dspSeq, DspStatusDto dto)
    {
        CHECK_FALSE_RETURN((dspSeq == mDspSeq));

        setEventValue     (dto.mWCStatus.mCurrWeight     );
        setMaxPDCntPerMin (dto.mWCStatus.mMaxPDCntPerMin );
        setCurrPDCntPerMin(dto.mWCStatus.mCurrPDCntPerMin);
        setPDCntPerMin    (dto.mWCStatus.mPDCntPerMin    );
    }

    void onAddedWCG(quint64 dspSeq, DspWCGDto dto)
    {
        CHECK_FALSE_RETURN((mDspSeq == dspSeq));

        writeGraphData(dto);

        StDspWCG * pGData = (StDspWCG *)dto.mGraphData.data();

        mTotalRuntimePointCnt = pGData->mPointCnt * 20;

        for(int i = 0; i < pGData->mPointCnt; i ++)
        {
            if(mTotalRuntimePointCnt == mRunTimeRawGraphPoints.size())
            {
                mRunTimeRawGraphPoints.removeAt(0);
                mRunTimeGraphPoints.removeAt(0);
            }
            mRunTimeRawGraphPoints.append(pGData->mPoints[i].mRawValue);
            mRunTimeGraphPoints.append(pGData->mPoints[i].mFilterValue);

            if(pGData->mPoints[i].mPointType != 0)
            {
                mTempTimingGraphPoints.append(pGData->mPoints[i].mFilterValue);

                if(pGData->mPoints[i].mPointType == 3)
                {
                    if(mLastPointType != 3)
                    {
                        mGraphMeasureStartIdxList.append(mTempTimingGraphPoints.size() - 1);
                        mGraphMeasurePointCntList.append(1);
                    }
                    else
                    {
                        mGraphMeasurePointCntList[mGraphMeasurePointCntList.size() - 1] = mGraphMeasurePointCntList[mGraphMeasurePointCntList.size() - 1] + 1;
                    }
                }
                setIsEditable(false);
            }
            else if(pGData->mPoints[i].mPointType == 0 && mTempTimingGraphPoints.size() > 0)
            {
                setIsEditable(true);
            }

            if(mLastPointType == 0 && pGData->mPoints[i].mPointType == 1)
            {
                resetTimingGraph();
            }
            else if(mMeasuredStartIdx == -1 && pGData->mPoints[i].mPointType == 2)
            {
                setMeasuredStartIdx(mTempTimingGraphPoints.size() - 1);
                qDebug() << "[debug] setMeasuredStartIdx = " << mTempTimingGraphPoints.size() - 1;
            }
            else if(mLastPointType != 3 && pGData->mPoints[i].mPointType == 3)
            {
                setMeasuredCueLineIdx(mTempTimingGraphPoints.size() - 1);
                qDebug() << "[debug] setMeasuredCueLineIdx = " << mTempTimingGraphPoints.size() - 1;
            }
            else if(mLastPointType != 4 && pGData->mPoints[i].mPointType == 4)
            {
                setMeasuredSectionLineIdx(mTempTimingGraphPoints.size() - 1);
            }
            else if(mLastPointType != 0 && pGData->mPoints[i].mPointType == 0)
            {
                int xCueSignGab = (mMeasuredCueLineIdx - mMeasuredStartIdx);
                int xSectionGab = (mMeasuredSectionLineIdx - mMeasuredCueLineIdx);

                if(xCueSignGab <= 0 || xSectionGab <= 0)
                {
                    qDebug() << "[debug] xCueSignGab = " << xCueSignGab << ", xSectionGab = " << xSectionGab;
                }

                qDebug() << "[debug] missmatch xCueSignGab = " << mMeasureCueSign << "%" << xCueSignGab;

                if(mMeasureCueSign % xCueSignGab != 0)
                {
                    setDiffCueSignGab(true);
                }
                else
                {
                    setDiffCueSignGab(false);
                }

                qDebug() << "[debug] missmatch xSectionGab = " << mMeasureSection << "%" << xSectionGab;

                if(mMeasureSection % xSectionGab != 0)
                {
                    setDiffSectionGab(true);
                }
                else
                {
                    setDiffSectionGab(false);
                }

                mXTimeInterval = 10;

                /*
                int xGab = (mMeasuredCueLineIdx - mMeasuredStartIdx);

                if(xGab < 0)
                {
                    qDebug() << "[debug] xGab = " << xGab;
                    mXTimeInterval = 0;
                }
                else
                {
                    if((mMeasureCueSign % xGab) != 0)
                    {
                        qDebug() << "[debug] invalid xTimeGab = " << mMeasureCueSign << "%" << xGab;

                    }
                    else
                    {
                        mXTimeInterval = mMeasureCueSign/xGab;
                    }
                }
                */
                mTimingGraphPoints = mTempTimingGraphPoints;
                emit signalEventChangedTimingPointCnt(mTimingGraphPoints.size());
                emit signalEventChangedTimingGraph();
            }

            if(mLastPointType != pGData->mPoints[i].mPointType)
            {
                qDebug() << "[debug] changed point type :" << pGData->mPoints[i].mPointType;
            }

            mLastPointType = pGData->mPoints[i].mPointType;
        }

        if(getIsPause() == false)
            emit signalEventChangedGraph();
    }

public :
    explicit PanelWCGraphModel(QObject *parent = nullptr):QObject(parent)
    {
        quint32 maxRange = (pProductSP->mCurrPD.mDspForm.mWCSetting.mOverWeight * 1.2);

        loadPDSetting();


        if(getMaxRange() == 100000000)
        {
            maxRange = ((maxRange + 500) / 1000) * 1000;
            setMaxRange(maxRange, true);
        }
        else
        {
            setMaxRange(getMaxRange(), true);
        }

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

    void resetTimingGraph()
    {
        mXTimeInterval = 0;
        mTimingGraphPoints.clear();
        mTempTimingGraphPoints.clear();
        mGraphMeasureStartIdxList.clear();
        mGraphMeasurePointCntList.clear();
        setMeasuredStartIdx(-1);
        setMeasuredCueLineIdx(-1);
        setMeasuredSectionLineIdx(-1);
    }

    void loadPDSetting()
    {
        setFilterCoefficient(pProductSP->mCurrPD.mDspForm.mWCSetting.mFilterCoefficient);
        setMeasureCueSign   (pProductSP->mCurrPD.mDspForm.mWCSetting.mMeasureCueSign);
        setMeasureSection   (pProductSP->mCurrPD.mDspForm.mWCSetting.mMeasureSection);

        setIsEditFilterCoefficient(false);
        setIsEditMeasureCueSign(false);
        setIsEditMeasureSection(false);
    }

private:
    bool mLastIsRawGraphOn = false;
    FileWriterEx * mpFileWriter = nullptr;

    void openFile()
    {
        closeFile();

        mpFileWriter = new FileWriterEx(this);
        mpFileWriter->open(FileDef::WC_GRAPH_DIR(), FileDef::WC_GRAPH_FILENAME(), FileWriterEx::FILE_OPEN_NEWWRITE);
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
                if(mpFileWriter->newWrite(QString("%1,%2\n").arg((int)(pGData->mPoints[i].mFilterValue)).arg((int)(pGData->mPoints[i].mRawValue))) == false)
                {
                    qDebug() << "[PanelWCGraphModel::writeGraphData] graph write error!";
                    closeFile();
                }
            }
        }
    }
};

#endif // PANELWCGRAPHMODEL_H
