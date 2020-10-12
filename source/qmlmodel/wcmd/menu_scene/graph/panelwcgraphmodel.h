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
    CoreService * mpCoreService;
    DspStatusModel * mpDspStatus;
    GuiSettingModel * mpGuiSetting;

    int                     mLastPointType     = 0;
    QList<quint32>          mRunTimeGraphPoints;
    QList<quint32>          mRunTimeRawGraphPoints;
    QList<quint32>          mTempTimingGraphPoints;
    QList<quint32>          mTimingGraphPoints;

    bool                    mIsRawGraphOn           = false;
    bool                    mIsPause                = false;
    //int                     mMinRange               ;//= 0;
    //int                     mMaxRange               ;//= 999999;
    quint32                 mEventValue             = 0;
    int                     mRange                  = 0;
    int                     mMeasuredStartIdx       = 0;
    int                     mMeasuredIdx            = 0;
    int                     mMeasuredEndIdx         = 0;
    int                     mLineInterval           = 1000;
    int                     mTotalRuntimePointCnt   = 400;

    bool    getIsRawGraphOn         (){return mIsRawGraphOn                 ; }
    bool    getIsPause              (){return mIsPause                      ; }
    int     getMinRange             (){return mpGuiSetting->mWCGraphMinRange; }
    int     getMaxRange             (){return mpGuiSetting->mWCGraphMaxRange; }
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

        mpGuiSetting->setWCGraphMinRange(value);

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

        mpGuiSetting->setWCGraphMaxRange(value);

        if(getMaxRange() < getMinRange())
            setMinRange(getMaxRange()-1, force);

        setLineInterval((getMaxRange() - getMinRange()) / 10);

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
    void onSignalEventChangedWCCurrWeight(quint32 value)
    {
        setEventValue(value);
    }

    void onSignalEventAddedWeightCheckerGraph(quint64 deviceSeq, QByteArray value)
    {
        StWeightCheckerGraph * pGData = (StWeightCheckerGraph *)value.data();

        mTotalRuntimePointCnt = pGData->pointCnt * 40;

        for(int i = 0; i < pGData->pointCnt; i ++)
        {
            if(pGData->points[i].mPointType == 4)
            {
                setMeasuredIdx(getMeasuredStartIdx() + pGData->points[i].mRawValue);
                continue;
            }

            if(mTotalRuntimePointCnt == mRunTimeRawGraphPoints.size())
            {
                mRunTimeRawGraphPoints.removeAt(0);
                mRunTimeGraphPoints.removeAt(0);
            }
            mRunTimeRawGraphPoints.append(pGData->points[i].mRawValue);
            mRunTimeGraphPoints.append(pGData->points[i].mFilterValue);

            if(pGData->points[i].mPointType != 0)
            {
                if(mLastPointType == 0)
                {
                    mTempTimingGraphPoints.clear();
                }

                mTempTimingGraphPoints.append(pGData->points[i].mFilterValue);

                if(pGData->points[i].mPointType == 2)
                {
                    setMeasuredStartIdx(mTempTimingGraphPoints.size() - 1);
                }

                if(pGData->points[i].mPointType == 3)
                {
                    setMeasuredEndIdx(mTempTimingGraphPoints.size() - 1);
                }
            }
            else if( mLastPointType != 0)
            {
                mTimingGraphPoints = mTempTimingGraphPoints;
                emit signalEventChangedTimingGraph();
            }

            mLastPointType = pGData->points[i].mPointType;
        }

        if(getIsPause() == false)
            emit signalEventChangedGraph();
    }

public :
    explicit PanelWCGraphModel(QObject *parent = nullptr):QObject(parent)
    {
        mpCoreService = CoreService::getInstance();
        mpDspStatus = mpCoreService->mMapDspStatus.first();
        mpGuiSetting = &(mpCoreService->mLocalSettingService.mGuiSetting);
        quint32 maxRange = (mpCoreService->mProductSettingServcie.mCurrentProductSetting.mOverWeight * 1.2);

        if(getMaxRange() == 100000000)
        {
            maxRange = ((maxRange + 500) / 1000) * 1000;
            setMaxRange(maxRange, true);
        }
        else
        {
            setMaxRange(getMaxRange(), true);
        }
        connect(mpCoreService, SIGNAL(signalEventAddedWeightCheckerGraph (quint64, QByteArray)), this, SLOT(onSignalEventAddedWeightCheckerGraph(quint64, QByteArray)));
        connect(mpDspStatus  , SIGNAL(signalEventChangedWCCurrWeight     (quint32                )), this, SLOT(onSignalEventChangedWCCurrWeight    (quint32                )));

        mpCoreService->onCommandSendWeightCheckerGraphOnCmd(mpDspStatus->mSeq, true);
    }
    ~PanelWCGraphModel()
    {
        mpCoreService->onCommandSendWeightCheckerGraphOnCmd(mpDspStatus->mSeq, false);
    }
};

#endif // PANELWCGRAPHMODEL_H
