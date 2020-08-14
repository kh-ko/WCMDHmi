#ifndef PANELWCGRAPHMODEL_H
#define PANELWCGRAPHMODEL_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDir>

#include "source/service/wcmdservice.h"
#include "source/qmlmodel/wcmd/menu_scene/graph/metaldetectorgraphmodel.h"
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
    QFile                   mGraphFile;
    QTextStream             mGraphOut;

    int                     mLastPointType     = 0;
    QList<quint32>          mRunTimeGraphPoints;
    QList<quint32>          mRunTimeRawGraphPoints;
    QList<quint32>          mTempTimingGraphPoints;
    QList<quint32>          mTimingGraphPoints;

    bool                    mIsRawGraphOn           = false;
    bool                    mIsPause                = false;
    static int              mMinRange               ;//= 0;
    static int              mMaxRange               ;//= 999999;
    quint32                 mEventValue             = 0;
    int                     mRange                  = 0;
    int                     mMeasuredStartIdx       = 0;
    int                     mMeasuredIdx            = 0;
    int                     mMeasuredEndIdx         = 0;
    int                     mLineInterval           = 1000;
    int                     mTotalRuntimePointCnt   = 400;

    bool    getIsRawGraphOn         (){return mIsRawGraphOn         ; }
    bool    getIsPause              (){return mIsPause              ; }
    int     getMinRange             (){return mMinRange             ; }
    int     getMaxRange             (){return mMaxRange             ; }
    quint32 getEventValue           (){return mEventValue           ; }
    int     getRange                (){return mRange                ; }
    int     getMeasuredStartIdx     (){return mMeasuredStartIdx     ; }
    int     getMeasuredIdx          (){return mMeasuredIdx          ; }
    int     getMeasuredEndIdx       (){return mMeasuredEndIdx       ; }
    int     getLineInterval         (){return mLineInterval         ; }
    int     getTotalRuntimePointCnt (){return mTotalRuntimePointCnt ; }

    int     getRuntimePointCnt (){return mRunTimeGraphPoints.size();}
    int     getTimingPointCnt  (){return mTimingGraphPoints.size();}

    void setIsRawGraphOn    (bool value){if(value == mIsRawGraphOn    ) return; mIsRawGraphOn     = value; emit signalEventChangedIsRawGraphOn    (value);}
    void setIsPause         (bool value){if(value == mIsPause         ) return; mIsPause          = value; emit signalEventChangedIsPause         (value);}
    void setMinRange        (int  value, bool force)
    {
        if(value == mMinRange && force == false)
            return;

        mMinRange = value;

        if(mMinRange > mMaxRange)
            setMaxRange(mMinRange + 1, force);

        setLineInterval((mMaxRange - mMinRange) / 10);

        setRange(mMaxRange - mMinRange);

        emit signalEventChangedMinRange(value);
    }
    void setMaxRange        (int  value, bool force)
    {
        if(value == mMaxRange && force == false)
            return;

        mMaxRange = value;

        if(mMaxRange < mMinRange)
            setMinRange(mMaxRange-1, force);

        setLineInterval((mMaxRange - mMinRange) / 10);

        setRange(mMaxRange - mMinRange);

        emit signalEventChangedMaxRange(value);
    }
    void setEventValue      (quint32 value){if(value == mEventValue      ) return; mEventValue       = value; emit signalEventChangedEventValue      (value);}
    void setRange           (int     value){if(value == mRange           ) return; mRange            = value; emit signalEventChangedRange           (value);}
    void setMeasuredStartIdx(int     value){if(value == mMeasuredStartIdx) return; mMeasuredStartIdx = value; emit signalEventChangedMeasuredStartIdx(value);}
    void setMeasuredIdx     (int     value){if(value == mMeasuredIdx     ) return; mMeasuredIdx      = value; emit signalEventChangedMeasuredIdx     (value);}
    void setMeasuredEndIdx  (int     value){if(value == mMeasuredEndIdx  ) return; mMeasuredEndIdx   = value; emit signalEventChangedMeasuredEndIdx  (value);}
    void setLineInterval    (int     value){if(value == mLineInterval    ) return; mLineInterval     = value; emit signalEventChangedLineInterval    (value);}
    explicit PanelWCGraphModel(QObject *parent = nullptr);
    ~PanelWCGraphModel();
    void openGraphFile();
    void closeGraphFile();
    void writeGraphData(quint32 value);

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
    Q_INVOKABLE void                        onCommandRawGraphOn             (bool value);
    Q_INVOKABLE void                        onCommandIsPause                (bool value);
    Q_INVOKABLE void                        onCommandSetMinRange            (int  value);
    Q_INVOKABLE void                        onCommandSetMaxRange            (int  value);
    Q_INVOKABLE int                         onCommandGetTimingPointValue    (int  idx  );
    Q_INVOKABLE int                         onCommandGetRuntimeRawPointValue(int  idx  );
    Q_INVOKABLE int                         onCommandGetRuntimePointValue   (int  idx  );

    void onSignalEventAddedEvent(quint16 deviceSeq, EventInfo eventInfo);
    void onSignalEventAddedWeightCheckerGraph(quint16 deviceSeq, WeightChekerGraphData value);

};

#endif // PANELWCGRAPHMODEL_H
