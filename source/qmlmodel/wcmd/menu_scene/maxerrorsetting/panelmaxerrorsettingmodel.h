#ifndef PANELMAXERRORSETTINGMODEL_H
#define PANELMAXERRORSETTINGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/globaldef/qmlenumdef.h"
#include "source/service/coreservice.h"


class PanelMaxErrorSettingModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int     mTimes              READ getTimes            NOTIFY signalEventChangedTimes         )
    Q_PROPERTY(quint32 mAverage            READ getAverage          NOTIFY signalEventChangedAverage       )
    Q_PROPERTY(quint32 mMax                READ getMax              NOTIFY signalEventChangedMax           )
    Q_PROPERTY(quint32 mMin                READ getMin              NOTIFY signalEventChangedMin           )
    Q_PROPERTY(quint32 mMaxError           READ getMaxError         NOTIFY signalEventChangedMaxError      )
    Q_PROPERTY(quint32 mSD                 READ getSD               NOTIFY signalEventChangedSD            )
    Q_PROPERTY(bool    mIsEditMaxError     READ getIsEditMaxError   NOTIFY signalEventChangedIsEditMaxError)


    class MeasureItem{

    };
public:
    quint64 mDspSeq        = 0;
    quint32 mTotalWeight   = 0;
    QList<quint32> mWeightList;

    int     mTimes          = 0;
    quint32 mAverage        = 0;
    quint32 mMax            = 0;
    quint32 mMin            = 0;
    quint32 mMaxError       = 0;
    quint32 mSD             = 0;
    bool    mIsEditMaxError = false;

    int     getTimes         (){ return mTimes         ;}
    quint32 getAverage       (){ return mAverage       ;}
    quint32 getMax           (){ return mMax           ;}
    quint32 getMin           (){ return mMin           ;}
    quint32 getMaxError      (){ return mMaxError      ;}
    quint32 getSD            (){ return mSD            ;}
    bool    getIsEditMaxError(){ return mIsEditMaxError;}

    void    setTimes         (int     value) { if(value == mTimes         ) return; mTimes          = value; emit signalEventChangedTimes         (value);}
    void    setAverage       (quint32 value) { if(value == mAverage       ) return; mAverage        = value; emit signalEventChangedAverage       (value);}
    void    setMax           (quint32 value) { if(value == mMax           ) return; mMax            = value; emit signalEventChangedMax           (value);}
    void    setMin           (quint32 value) { if(value == mMin           ) return; mMin            = value; emit signalEventChangedMin           (value);}
    void    setMaxError      (quint32 value) { if(value == mMaxError      ) return; mMaxError       = value; emit signalEventChangedMaxError      (value);}
    void    setSD            (quint32 value) { if(value == mSD            ) return; mSD             = value; emit signalEventChangedSD            (value);}
    void    setIsEditMaxError(bool    value) { if(value == mIsEditMaxError) return; mIsEditMaxError = value; emit signalEventChangedIsEditMaxError(value);}

    explicit PanelMaxErrorSettingModel(QObject *parent = nullptr) : QObject(parent)
    {
        CHECK_FALSE_RETURN((pDspSP->mDspList.size() > 0));

        mDspSeq = pDspSP->mDspList[0]->mSeq;

        ENABLE_SLOT_DSP_ADDED_EVENT;

        setMaxError(pLSettingSP->mMaxError);
    }

    ~PanelMaxErrorSettingModel()
    {
        CHECK_FALSE_RETURN((mDspSeq != 0));

        pDspSP->sendRunCmd(mDspSeq, EnumDef::RUN_MODE_STOP);
    }

signals:
    void    signalEventChangedTimes         (int     value);
    void    signalEventChangedAverage       (quint32 value);
    void    signalEventChangedMax           (quint32 value);
    void    signalEventChangedMin           (quint32 value);
    void    signalEventChangedMaxError      (quint32 value);
    void    signalEventChangedSD            (quint32 value);
    void    signalEventChangedIsEditMaxError(bool    value);
    void    signalEventAddedEvent           (quint32 value);
    void    signalEventRefreshedList        (             );

public slots:
    Q_INVOKABLE void onCommandEditMaxError(int value)
    {
        setMaxError(value);
        setIsEditMaxError(true);
    }

    Q_INVOKABLE void onCommandApply()
    {
        setIsEditMaxError(false);
        pLSettingSP->setMaxError(mMaxError);
    }

    Q_INVOKABLE void onCommandStart()
    {
        CHECK_FALSE_RETURN((mDspSeq != 0));

        pDspSP->sendRunCmd(mDspSeq, EnumDef::RUN_MODE_CHECKUP_RUN);

        setTimes(0);
        setAverage(0);
        setMax(0);
        setMin(0);
        setSD(0);
        mTotalWeight = 0;
        mWeightList.clear();

        emit signalEventRefreshedList();
    }

    Q_INVOKABLE void onCommandStop()
    {
        CHECK_FALSE_RETURN((mDspSeq != 0));

        pDspSP->sendRunCmd(mDspSeq, EnumDef::RUN_MODE_STOP);
    }

    Q_INVOKABLE int onCommandGetListCnt()
    {
        return mWeightList.size();
    }

    Q_INVOKABLE quint32 onCommandGetWeight(int i)
    {
        return mWeightList[i];
    }

    Q_INVOKABLE void onCommandSortList()
    {
        for(int i = 0; i < mWeightList.size() - 1; i ++)
        {
            for(int j = 0; j < mWeightList.size() - i - 1; j ++)
            {
                int gab = mWeightList[j] - mAverage;
                int nextGab = mWeightList[j+1] - mAverage;

                int absGab = gab < 0 ? -1 * gab : gab;
                int nextAbsGab = nextGab < 0 ? -1 * nextGab : nextGab;

                if(absGab < nextAbsGab)
                {
                    int weight = mWeightList[j + 1];

                    mWeightList[j + 1] = mWeightList[j];
                    mWeightList[j] = weight;
                }
            }
        }

        emit signalEventRefreshedList();
    }


    void onAddedDspEvent(quint64 dspSeq, DspEventDto dto)
    {
        CHECK_FALSE_RETURN((mDspSeq == dspSeq));

        if(EventDto::isWeightCheckEvent(dto.mEvent.mEventType) && (dto.mEvent.mEventType != EnumDef::ET_WEIGHT_ETCERROR_CHECK && dto.mEvent.mEventType != EnumDef::ET_WEIGHT_ETC_METAL_ERROR_CHECK))
        {
            setTimes(mTimes + 1);

            quint32 weight = dto.mEvent.mEventValue;

            mWeightList.append(weight);
            mTotalWeight = mTotalWeight + weight;
            setAverage(mTotalWeight / mWeightList.size());
            calSD();

            if(mMax < weight)
                setMax(weight);

            if(mTimes == 1 || mMin > weight)
                setMin(weight);

            signalEventAddedEvent(weight);
            return;
        }
    }

private:
    void calSD()
    {
        double deviationSum               = 0;
        double variance                   = 0;

        foreach(quint32 value, mWeightList)
        {
            deviationSum += (value - mAverage) * (value - mAverage);
        }

        variance = deviationSum / (double) mWeightList.size();

        setSD(qSqrt(variance));
    }
};
#endif // PANELMAXERRORSETTINGMODEL_H
