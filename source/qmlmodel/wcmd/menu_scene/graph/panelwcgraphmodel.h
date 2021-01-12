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
    Q_PROPERTY(bool     isRawGraphOn         READ      getIsRawGraphOn             NOTIFY      signalEventChangedIsRawGraphOn           )
    Q_PROPERTY(bool     isPause              READ      getIsPause                  NOTIFY      signalEventChangedIsPause                )
    Q_PROPERTY(int      minRange             READ      getMinRange                 NOTIFY      signalEventChangedMinRange               )
    Q_PROPERTY(int      maxRange             READ      getMaxRange                 NOTIFY      signalEventChangedMaxRange               )
    Q_PROPERTY(quint32  eventValue           READ      getEventValue               NOTIFY      signalEventChangedEventValue             )
    Q_PROPERTY(int      range                READ      getRange                    NOTIFY      signalEventChangedRange                  )
    Q_PROPERTY(int      measuredStartIdx     READ      getMeasuredStartIdx         NOTIFY      signalEventChangedMeasuredStartIdx       )
    Q_PROPERTY(int      measuredIdx          READ      getMeasuredIdx              NOTIFY      signalEventChangedMeasuredIdx            )
    Q_PROPERTY(int      measuredEndIdx       READ      getMeasuredEndIdx           NOTIFY      signalEventChangedMeasuredEndIdx         )
    Q_PROPERTY(int      lineInterval         READ      getLineInterval             NOTIFY      signalEventChangedLineInterval           )
    Q_PROPERTY(int      totalRuntimePointCnt READ      getTotalRuntimePointCnt     NOTIFY      signalEventChangedTotalRuntimePointCnt   )

    Q_PROPERTY(int      runtimePointCnt      READ      getRuntimePointCnt          NOTIFY      signalEventChangedRuntimePointCnt        )
    Q_PROPERTY(int      timingPointCnt       READ      getTimingPointCnt           NOTIFY      signalEventChangedTimingPointCnt         )

public:
    quint64                mDspSeq = 0;

    int                     mLastPointType     = 0;
    QList<quint32>          mRunTimeGraphPoints;
    QList<quint32>          mRunTimeRawGraphPoints;
    QList<quint32>          mTempTimingGraphPoints;
    QList<quint32>          mTimingGraphPoints;

    bool                    mIsRawGraphOn           = false;
    bool                    mIsPause                = false;
    quint32                 mEventValue             = 0;
    int                     mRange                  = 0;
    int                     mMeasuredStartIdx       = 0;
    int                     mMeasuredIdx            = 0;
    int                     mMeasuredEndIdx         = 0;
    int                     mLineInterval           = 1000;
    int                     mTotalRuntimePointCnt   = 400;

    static int * ptrMinRang(){ static int minRang = 0; return &minRang;}
    static int * ptrMaxRang(){ static int maxRang = 999999; return &maxRang;}

    bool    getIsRawGraphOn         (){return mIsRawGraphOn                 ; }
    bool    getIsPause              (){return mIsPause                      ; }
    int     getMinRange             (){return *ptrMinRang(); }
    int     getMaxRange             (){return *ptrMaxRang(); }
    quint32 getEventValue           (){return mEventValue                   ; }
    int     getRange                (){return mRange                        ; }
    int     getMeasuredStartIdx     (){return mMeasuredStartIdx             ; }
    int     getMeasuredIdx          (){return mMeasuredIdx                  ; }
    int     getMeasuredEndIdx       (){return mMeasuredEndIdx               ; }
    int     getLineInterval         (){return mLineInterval                 ; }
    int     getTotalRuntimePointCnt (){return mTotalRuntimePointCnt         ; }

    int     getRuntimePointCnt (){return mRunTimeGraphPoints.size();}
    int     getTimingPointCnt  (){return mTimingGraphPoints.size();}

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
    void setEventValue      (quint32 value){if(value == mEventValue      ) return; mEventValue       = value; emit signalEventChangedEventValue      (value);}
    void setRange           (int     value){if(value == mRange           ) return; mRange            = value; emit signalEventChangedRange           (value);}
    void setMeasuredStartIdx(int     value){if(value == mMeasuredStartIdx) return; mMeasuredStartIdx = value; emit signalEventChangedMeasuredStartIdx(value);}
    void setMeasuredIdx     (int     value){if(value == mMeasuredIdx     ) return; mMeasuredIdx      = value; emit signalEventChangedMeasuredIdx     (value);}
    void setMeasuredEndIdx  (int     value){if(value == mMeasuredEndIdx  ) return; mMeasuredEndIdx   = value; emit signalEventChangedMeasuredEndIdx  (value);}
    void setLineInterval    (int     value){if(value == mLineInterval    ) return; mLineInterval     = value; emit signalEventChangedLineInterval    (value);}

signals:
    void signalEventChangedIsRawGraphOn         (bool    value);
    void signalEventChangedIsPause              (bool    value);
    void signalEventChangedMinRange             (int     value);
    void signalEventChangedMaxRange             (int     value);
    void signalEventChangedEventValue           (quint32 value);
    void signalEventChangedRange                (int     value);
    void signalEventChangedMeasuredStartIdx     (int     value);
    void signalEventChangedMeasuredIdx          (int     value);
    void signalEventChangedMeasuredEndIdx       (int     value);
    void signalEventChangedLineInterval         (int     value);
    void signalEventChangedTotalRuntimePointCnt (int     value);
    void signalEventChangedRuntimePointCnt      (int     value);
    void signalEventChangedTimingPointCnt       (int     value);

    void signalEventChangedGraph            (          );
    void signalEventChangedTimingGraph      (          );

    void signalCommandSetWeightCheckerGraphOn( quint16 deviceSeq, bool value);

public slots:
    Q_INVOKABLE void                        onCommandRawGraphOn             (bool value){setIsRawGraphOn(value);}
    Q_INVOKABLE void                        onCommandIsPause                (bool value){setIsPause     (value);}
    Q_INVOKABLE void                        onCommandSetMinRange            (int  value){setMinRange    (value, false);}
    Q_INVOKABLE void                        onCommandSetMaxRange            (int  value){setMaxRange    (value, false);}
    Q_INVOKABLE int                         onCommandGetTimingPointValue    (int  idx  )
    {
        return mTimingGraphPoints.at(idx) - getMinRange();
    }
    Q_INVOKABLE int                         onCommandGetRuntimeRawPointValue(int  idx  )
    {
        return mRunTimeRawGraphPoints.at(idx) - getMinRange();
    }
    Q_INVOKABLE int                         onCommandGetRuntimePointValue   (int  idx  )
    {
        return mRunTimeGraphPoints.at(idx) - getMinRange();
    }
public slots:
    void onChangedDspStatus(quint64 dspSeq, DspStatusDto dto)
    {
        CHECK_FALSE_RETURN((dspSeq == mDspSeq));

        setEventValue(dto.mWCStatus.mCurrWeight);
    }

    void onAddedWCG(quint64 dspSeq, DspWCGDto dto)
    {
        CHECK_FALSE_RETURN((mDspSeq == dspSeq));

        writeGraphData(dto);

        StDspWCG * pGData = (StDspWCG *)dto.mGraphData.data();

        qDebug() << "[debug] point cnt = " << pGData->mPointCnt;

        mTotalRuntimePointCnt = pGData->mPointCnt * 40;

        for(int i = 0; i < pGData->mPointCnt; i ++)
        {
            if(pGData->mPoints[i].mPointType == 4)
            {
                setMeasuredIdx(getMeasuredStartIdx() + pGData->mPoints[i].mRawValue);
                continue;
            }

            if(mTotalRuntimePointCnt == mRunTimeRawGraphPoints.size())
            {
                mRunTimeRawGraphPoints.removeAt(0);
                mRunTimeGraphPoints.removeAt(0);
            }
            mRunTimeRawGraphPoints.append(pGData->mPoints[i].mRawValue);
            mRunTimeGraphPoints.append(pGData->mPoints[i].mFilterValue);

            if(pGData->mPoints[i].mPointType != 0)
            {
                if(mLastPointType == 0)
                {
                    mTempTimingGraphPoints.clear();
                }

                mTempTimingGraphPoints.append(pGData->mPoints[i].mFilterValue);

                if(pGData->mPoints[i].mPointType == 2)
                {
                    setMeasuredStartIdx(mTempTimingGraphPoints.size() - 1);
                }

                if(pGData->mPoints[i].mPointType == 3)
                {
                    setMeasuredEndIdx(mTempTimingGraphPoints.size() - 1);
                }
            }
            else if( mLastPointType != 0)
            {
                mTimingGraphPoints = mTempTimingGraphPoints;
                emit signalEventChangedTimingGraph();
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
