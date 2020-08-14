#include "panelwcgraphmodel.h"

int PanelWCGraphModel::mMinRange = 0;
int PanelWCGraphModel::mMaxRange = 100000000;

PanelWCGraphModel::PanelWCGraphModel(QObject *parent) : QObject(parent)
{
    quint32 maxRange = (WCMDService::getInstance()->mProductSetting.mOverWeight * 1.2);

    if(mMaxRange == 100000000)
    {
        maxRange = ((maxRange + 500) / 1000) * 1000;
        setMaxRange(maxRange, true);
    }
    else
    {
        setMaxRange(mMaxRange, true);
    }

    connect(this, SIGNAL(signalCommandSetWeightCheckerGraphOn(quint16, bool)), WCMDService::getInstance(), SLOT(onCommandSetWeightCheckerGraphOn(quint16, bool)));

    connect(WCMDService::getInstance(), SIGNAL(signalEventAddedWeightCheckerGraph      (quint16, WeightChekerGraphData) ), this, SLOT(onSignalEventAddedWeightCheckerGraph  (quint16, WeightChekerGraphData)));
    connect(WCMDService::getInstance(), SIGNAL(signalEventAddedEvent                   (quint16, EventInfo            ) ), this, SLOT(onSignalEventAddedEvent               (quint16, EventInfo            )));

    emit signalCommandSetWeightCheckerGraphOn(0xffff, true);

    //openGraphFile();
}

PanelWCGraphModel::~PanelWCGraphModel()
{
    emit signalCommandSetWeightCheckerGraphOn(0xffff, false);

    //closeGraphFile();
}

void PanelWCGraphModel::onCommandRawGraphOn   (bool value){ setIsRawGraphOn(value);}
void PanelWCGraphModel::onCommandIsPause      (bool value){ setIsPause     (value);}
void PanelWCGraphModel::onCommandSetMinRange  (int value ){ setMinRange    (value, false);}
void PanelWCGraphModel::onCommandSetMaxRange  (int value ){ setMaxRange    (value, false);}

int PanelWCGraphModel::onCommandGetTimingPointValue(int idx)
{
    return mTimingGraphPoints.at(idx) - mMinRange;
}

int PanelWCGraphModel::onCommandGetRuntimeRawPointValue(int idx)
{
    return mRunTimeRawGraphPoints.at(idx) - mMinRange;
}

int PanelWCGraphModel::onCommandGetRuntimePointValue(int idx)
{
    return mRunTimeGraphPoints.at(idx) - mMinRange;
}

void PanelWCGraphModel::onSignalEventAddedEvent(quint16 deviceSeq, EventInfo eventInfo)
{
    setEventValue(eventInfo.mEventValue);
}

void PanelWCGraphModel::onSignalEventAddedWeightCheckerGraph(quint16 deviceSeq, WeightChekerGraphData value)
{
    mTotalRuntimePointCnt = value.mData->mPointCnt * 40;

    for(int i = 0; i < value.mData->mPointCnt; i ++)
    {
        //writeGraphData(value.mData->mArrayPoints[i].value);
        //qDebug() << "[points type]" << value.mData->mArrayPoints[i].type;

        if(value.mData->mArrayPoints[i].type == 4)
        {
            //qDebug() << "measured idx =" << value.mData->mArrayPoints[i].rawValue;

            setMeasuredIdx(getMeasuredStartIdx() + value.mData->mArrayPoints[i].rawValue);
            continue;
        }

        if(mTotalRuntimePointCnt == mRunTimeRawGraphPoints.size())
        {
            mRunTimeRawGraphPoints.removeAt(0);
            mRunTimeGraphPoints.removeAt(0);
        }
        mRunTimeRawGraphPoints.append(value.mData->mArrayPoints[i].rawValue);
        mRunTimeGraphPoints.append(value.mData->mArrayPoints[i].value);

        if(value.mData->mArrayPoints[i].type != 0)
        {
            if(mLastPointType == 0)
            {
                mTempTimingGraphPoints.clear();
            }

            mTempTimingGraphPoints.append(value.mData->mArrayPoints[i].value);

            if(value.mData->mArrayPoints[i].type == 2)
            {
                setMeasuredStartIdx(mTempTimingGraphPoints.size() - 1);

                //qDebug() << "start idx =" << getMeasuredStartIdx();
            }

            if(value.mData->mArrayPoints[i].type == 3)
            {
                setMeasuredEndIdx(mTempTimingGraphPoints.size() - 1);

                //qDebug() << "end idx =" << getMeasuredEndIdx();
            }
        }
        else if( mLastPointType != 0)
        {
            mTimingGraphPoints = mTempTimingGraphPoints;

            //for(int j = 0; j < mTimingGraphPoints.size(); j ++)
            //{
            //    qDebug() << "[" << j << "]" << mTimingGraphPoints.at(j);
            //}
            emit signalEventChangedTimingGraph();
        }

        mLastPointType = value.mData->mArrayPoints[i].type;
    }

    if(getIsPause() == false)
        emit signalEventChangedGraph();
}


void PanelWCGraphModel::openGraphFile()
{
    if (QDir("graph").exists() == false)
    {
        QDir().mkdir("graph");
    }

    QString currTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
    QString fileName = "graph/runtime_%1.txt";
    mGraphFile.setFileName(fileName.arg(currTime));
    mGraphFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);

    if(mGraphFile.isOpen() == false)
    {
        qDebug() <<  mGraphFile.errorString();
        return;
    }

    mGraphOut.setDevice(&mGraphFile);
}

void PanelWCGraphModel::closeGraphFile()
{
    if(mGraphFile.isOpen())
    {
        mGraphFile.close();
    }
    mGraphOut.setDevice(nullptr);
}

void PanelWCGraphModel::writeGraphData(quint32 value)
{
    mGraphOut << value << "\n";
    mGraphOut.flush();
}
