#ifndef PANELCHECKUPMODEL_H
#define PANELCHECKUPMODEL_H

#include <QObject>
#include "source/service/def/datetimeform.h"
#include "source/globaldef/qmlenumdef.h"
#include "source/service/coreservice.h"

class PanelMDCheckupModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int     step              READ getStep             NOTIFY signalEventChangedStep            )
    Q_PROPERTY(QString chekcupDateTime   READ getChekcupDateTime  NOTIFY signalEventChangedChekcupDateTime )
    Q_PROPERTY(bool    isPass            READ getIsPass           NOTIFY signalEventChangedIsPass          )
    Q_PROPERTY(int     feStep01State     READ getFeStep01State    NOTIFY signalEventChangedFeStep01State   )
    Q_PROPERTY(int     feStep02State     READ getFeStep02State    NOTIFY signalEventChangedFeStep02State   )
    Q_PROPERTY(int     feStep03State     READ getFeStep03State    NOTIFY signalEventChangedFeStep03State   )
    Q_PROPERTY(int     susStep01State    READ getSusStep01State   NOTIFY signalEventChangedSusStep01State  )
    Q_PROPERTY(int     susStep02State    READ getSusStep02State   NOTIFY signalEventChangedSusStep02State  )
    Q_PROPERTY(int     susStep03State    READ getSusStep03State   NOTIFY signalEventChangedSusStep03State  )

public:
    quint64 mDspSeq          = 0;
    int     mStep            = 0;
    QString mChekcupDateTime = "";
    bool    mIsPass          = false;
    int     mFeStep01State   = QmlEnumDef::CHECKUP_INIT;
    int     mFeStep02State   = QmlEnumDef::CHECKUP_INIT;
    int     mFeStep03State   = QmlEnumDef::CHECKUP_INIT;
    int     mSusStep01State  = QmlEnumDef::CHECKUP_INIT;
    int     mSusStep02State  = QmlEnumDef::CHECKUP_INIT;
    int     mSusStep03State  = QmlEnumDef::CHECKUP_INIT;

    int     getStep           (){ return mStep           ;}
    QString getChekcupDateTime(){ return mChekcupDateTime;}
    bool    getIsPass         (){ return mIsPass         ;}
    int     getFeStep01State  (){ return mFeStep01State  ;}
    int     getFeStep02State  (){ return mFeStep02State  ;}
    int     getFeStep03State  (){ return mFeStep03State  ;}
    int     getSusStep01State (){ return mSusStep01State ;}
    int     getSusStep02State (){ return mSusStep02State ;}
    int     getSusStep03State (){ return mSusStep03State ;}

    void    setStep           (int      value) { if(value == mStep           ) return; mStep            = value; emit signalEventChangedStep           (value);}
    void    setChekcupDateTime(QString  value) { if(value == mChekcupDateTime) return; mChekcupDateTime = value; emit signalEventChangedChekcupDateTime(value);}
    void    setIsPass         (bool     value) { if(value == mIsPass         ) return; mIsPass          = value; emit signalEventChangedIsPass         (value);}
    void    setFeStep01State  (int      value) { if(value == mFeStep01State  ) return; mFeStep01State   = value; emit signalEventChangedFeStep01State  (value);}
    void    setFeStep02State  (int      value) { if(value == mFeStep02State  ) return; mFeStep02State   = value; emit signalEventChangedFeStep02State  (value);}
    void    setFeStep03State  (int      value) { if(value == mFeStep03State  ) return; mFeStep03State   = value; emit signalEventChangedFeStep03State  (value);}
    void    setSusStep01State (int      value) { if(value == mSusStep01State ) return; mSusStep01State  = value; emit signalEventChangedSusStep01State (value);}
    void    setSusStep02State (int      value) { if(value == mSusStep02State ) return; mSusStep02State  = value; emit signalEventChangedSusStep02State (value);}
    void    setSusStep03State (int      value) { if(value == mSusStep03State ) return; mSusStep03State  = value; emit signalEventChangedSusStep03State (value);}

    explicit PanelMDCheckupModel(QObject *parent = nullptr) : QObject(parent)
    {
        CHECK_FALSE_RETURN((pDspSP->mDspList.size() > 0));

        mDspSeq = pDspSP->mDspList[0]->mSeq;

        ENABLE_SLOT_DSP_ADDED_EVENT;
    }

    ~PanelMDCheckupModel()
    {
        CHECK_FALSE_RETURN((mDspSeq != 0));

        pDspSP->sendRunCmd(mDspSeq, EnumDef::RUN_MODE_STOP);
    }

    void reset()
    {
        setStep           (0);
        setChekcupDateTime("");
        setIsPass         (false);
        setFeStep01State  ((int)QmlEnumDef::CHECKUP_INIT);
        setFeStep02State  ((int)QmlEnumDef::CHECKUP_INIT);
        setFeStep03State  ((int)QmlEnumDef::CHECKUP_INIT);
        setSusStep01State ((int)QmlEnumDef::CHECKUP_INIT);
        setSusStep02State ((int)QmlEnumDef::CHECKUP_INIT);
        setSusStep03State ((int)QmlEnumDef::CHECKUP_INIT);
    }
signals:
    void    signalEventChangedStep           (int      value);
    void    signalEventChangedChekcupDateTime(QString  value);
    void    signalEventChangedIsPass         (bool     value);
    void    signalEventChangedFeStep01State  (int      value);
    void    signalEventChangedFeStep02State  (int      value);
    void    signalEventChangedFeStep03State  (int      value);
    void    signalEventChangedSusStep01State (int      value);
    void    signalEventChangedSusStep02State (int      value);
    void    signalEventChangedSusStep03State (int      value);

    void    signalEventStepComplete();

public slots:
    Q_INVOKABLE void onCommandStart()
    {
        CHECK_FALSE_RETURN((mDspSeq != 0));

        pDspSP->sendRunCmd(mDspSeq, EnumDef::RUN_MODE_CHECKUP_RUN);
    }
    Q_INVOKABLE void onCommandCancle()
    {
        reset();

        CHECK_FALSE_RETURN((mDspSeq != 0));

        pDspSP->sendRunCmd(mDspSeq, EnumDef::RUN_MODE_STOP);
    }
    Q_INVOKABLE void onCommandStartNextStep()
    {
        CHECK_FALSE_RETURN((mDspSeq != 0));

        if(getStep() == QmlEnumDef::CHECKUP_RESULT_STEP)
        {
            reset();
            return;
        }

        setStep(getStep() + 1);

        switch(mStep)
        {
        case QmlEnumDef::CHECKUP_FE_STEP01:
            setFeStep01State((int)QmlEnumDef::CHECKUP_CHECKING);
            pDspSP->sendRunCmd(mDspSeq, EnumDef::RUN_MODE_CHECKUP_RUN);
            break;

        case QmlEnumDef::CHECKUP_FE_STEP02:
            setFeStep02State((int)QmlEnumDef::CHECKUP_CHECKING);
            break;

        case QmlEnumDef::CHECKUP_FE_STEP03:
            setFeStep03State((int)QmlEnumDef::CHECKUP_CHECKING);
            break;

        case QmlEnumDef::CHECKUP_SUS_STEP01:
            setSusStep01State((int)QmlEnumDef::CHECKUP_CHECKING);
            break;

        case QmlEnumDef::CHECKUP_SUS_STEP02:
            setSusStep02State((int)QmlEnumDef::CHECKUP_CHECKING);
            break;

        case QmlEnumDef::CHECKUP_SUS_STEP03:
            setSusStep03State((int)QmlEnumDef::CHECKUP_CHECKING);
            break;
        case QmlEnumDef::CHECKUP_RESULT_STEP:
            {
                DspEventDto event;
                QDateTime now = QDateTime::currentDateTime();

                setIsPass(getFeStep01State() ==  (int)QmlEnumDef::CHECKUP_PASS &&
                          getFeStep02State() ==  (int)QmlEnumDef::CHECKUP_PASS &&
                          getFeStep03State() ==  (int)QmlEnumDef::CHECKUP_PASS &&
                          getSusStep01State() == (int)QmlEnumDef::CHECKUP_PASS &&
                          getSusStep02State() == (int)QmlEnumDef::CHECKUP_PASS &&
                          getSusStep03State() == (int)QmlEnumDef::CHECKUP_PASS);

                setChekcupDateTime(now.toString(DATE_TIME_FMT));

                event.mEvent.mEventValue = getIsPass() ? (0x01 << 6) : 0x00 ;

                if(getFeStep01State() == QmlEnumDef::CHECKUP_PASS)
                {
                    event.mEvent.mEventValue = event.mEvent.mEventValue | (0x01 << 5);
                }

                if(getFeStep02State() == QmlEnumDef::CHECKUP_PASS)
                {
                    event.mEvent.mEventValue = event.mEvent.mEventValue | (0x01 << 4);
                }

                if(getFeStep03State() == QmlEnumDef::CHECKUP_PASS)
                {
                    event.mEvent.mEventValue = event.mEvent.mEventValue | (0x01 << 3);
                }

                if(getSusStep01State() == QmlEnumDef::CHECKUP_PASS)
                {
                    event.mEvent.mEventValue = event.mEvent.mEventValue | (0x01 << 2);
                }

                if(getSusStep02State() == QmlEnumDef::CHECKUP_PASS)
                {
                    event.mEvent.mEventValue = event.mEvent.mEventValue | (0x01 << 1);
                }

                if(getSusStep03State() == QmlEnumDef::CHECKUP_PASS)
                {
                    event.mEvent.mEventValue = event.mEvent.mEventValue | (0x01);
                }

                event.mEvent.mEventType = EnumDef::ET_METAL_CHECKUP;

                if(mDspSeq != 0)
                    pEventHisSP->onAddedDspEvent(mDspSeq, event);
            }
            if(mDspSeq != 0)
                pDspSP->sendRunCmd(mDspSeq, EnumDef::RUN_MODE_STOP);

            break;
        }
    }
    Q_INVOKABLE void onCommandTimeout()
    {
        switch(mStep)
        {
        case QmlEnumDef::CHECKUP_FE_STEP01:
            setFeStep01State((int)QmlEnumDef::CHECKUP_FAIL);
            emit signalEventStepComplete();
            break;

        case QmlEnumDef::CHECKUP_FE_STEP02:
            setFeStep02State((int)QmlEnumDef::CHECKUP_FAIL);
            emit signalEventStepComplete();
            break;

        case QmlEnumDef::CHECKUP_FE_STEP03:
            setFeStep03State((int)QmlEnumDef::CHECKUP_FAIL);
            emit signalEventStepComplete();
            break;

        case QmlEnumDef::CHECKUP_SUS_STEP01:
            setSusStep01State((int)QmlEnumDef::CHECKUP_FAIL);
            emit signalEventStepComplete();
            break;

        case QmlEnumDef::CHECKUP_SUS_STEP02:
            setSusStep02State((int)QmlEnumDef::CHECKUP_FAIL);
            emit signalEventStepComplete();
            break;

        case QmlEnumDef::CHECKUP_SUS_STEP03:
            setSusStep03State((int)QmlEnumDef::CHECKUP_FAIL);
            emit signalEventStepComplete();
            break;
        }
    }

    void onAddedDspEvent(quint64 dspSeq, DspEventDto dto)
    {
        CHECK_FALSE_RETURN((mDspSeq == dspSeq));

        QmlEnumDef::MDCheckUpState result;

        if(dto.mEvent.mEventType == EnumDef::ET_METAL_DETECT_CHECK)
        {
            qDebug() << "MD CHECK UP PASS !";
            result = QmlEnumDef::CHECKUP_PASS;
        }
        else if(dto.mEvent.mEventType == EnumDef::ET_METAL_TRADE_CHECK)
        {
            qDebug() << "MD CHECK UP FAIL !";
            result = QmlEnumDef::CHECKUP_FAIL;
        }
        else
        {
            return;
        }

        switch(mStep)
        {
        case QmlEnumDef::CHECKUP_FE_STEP01:
            setFeStep01State(result);
            break;

        case QmlEnumDef::CHECKUP_FE_STEP02:
            setFeStep02State(result);
            break;

        case QmlEnumDef::CHECKUP_FE_STEP03:
            setFeStep03State(result);
            break;

        case QmlEnumDef::CHECKUP_SUS_STEP01:
            setSusStep01State(result);
            break;

        case QmlEnumDef::CHECKUP_SUS_STEP02:
            setSusStep02State(result);
            break;

        case QmlEnumDef::CHECKUP_SUS_STEP03:
            setSusStep03State(result);
            break;
        }
        emit signalEventStepComplete();
    }

};

#endif // PANELCHECKUPMODEL_H
