#ifndef PANELCHECKUPMODEL_H
#define PANELCHECKUPMODEL_H

#include <QObject>
#include "source/globaldef/EnumDefine.h"
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
    CoreService * mpCoreService = nullptr;
    DspStatusModel * mpDspStatus = nullptr;

    int     mStep            = 0;
    QString mChekcupDateTime = "";
    bool    mIsPass          = false;
    int     mFeStep01State   = EnumDefine::MDCheckUpState::CHECKUP_INIT;
    int     mFeStep02State   = EnumDefine::MDCheckUpState::CHECKUP_INIT;
    int     mFeStep03State   = EnumDefine::MDCheckUpState::CHECKUP_INIT;
    int     mSusStep01State  = EnumDefine::MDCheckUpState::CHECKUP_INIT;
    int     mSusStep02State  = EnumDefine::MDCheckUpState::CHECKUP_INIT;
    int     mSusStep03State  = EnumDefine::MDCheckUpState::CHECKUP_INIT;

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
        mpCoreService = CoreService::getInstance();
        mpDspStatus = mpCoreService->mMapDspStatus.first();

        connect(mpDspStatus, SIGNAL(siganlEventAddedEvent(quint16, quint32)), this, SLOT(onSignalEventAddEvent(quint16, quint32)));
    }

    ~PanelMDCheckupModel()
    {
        mpCoreService->onCommandSendRunCmd(INVALID_ULONGLONG, EnumDefine::RunState::STOP);
    }

    void reset()
    {
        setStep           (0);
        setChekcupDateTime("");
        setIsPass         (false);
        setFeStep01State  ((int)EnumDefine::MDCheckUpState::CHECKUP_INIT);
        setFeStep02State  ((int)EnumDefine::MDCheckUpState::CHECKUP_INIT);
        setFeStep03State  ((int)EnumDefine::MDCheckUpState::CHECKUP_INIT);
        setSusStep01State ((int)EnumDefine::MDCheckUpState::CHECKUP_INIT);
        setSusStep02State ((int)EnumDefine::MDCheckUpState::CHECKUP_INIT);
        setSusStep03State ((int)EnumDefine::MDCheckUpState::CHECKUP_INIT);
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
        mpCoreService->onCommandSendRunCmd(INVALID_ULONGLONG, EnumDefine::RunState::CHECKUP_RUN);
    }
    Q_INVOKABLE void onCommandCancle()
    {
        reset();
        mpCoreService->onCommandSendRunCmd(INVALID_ULONGLONG, EnumDefine::RunState::STOP);
    }
    Q_INVOKABLE void onCommandStartNextStep()
    {
        if(getStep() == EnumDefine::MDCheckUpStep::CHECKUP_RESULT_STEP)
        {
            reset();
            return;
        }

        setStep(getStep() + 1);

        switch(mStep)
        {
        case EnumDefine::MDCheckUpStep::CHECKUP_FE_STEP01:
            setFeStep01State((int)EnumDefine::MDCheckUpState::CHECKUP_CHECKING);
            mpCoreService->onCommandSendRunCmd(INVALID_ULONGLONG, EnumDefine::RunState::CHECKUP_RUN);
            break;

        case EnumDefine::MDCheckUpStep::CHECKUP_FE_STEP02:
            setFeStep02State((int)EnumDefine::MDCheckUpState::CHECKUP_CHECKING);
            break;

        case EnumDefine::MDCheckUpStep::CHECKUP_FE_STEP03:
            setFeStep03State((int)EnumDefine::MDCheckUpState::CHECKUP_CHECKING);
            break;

        case EnumDefine::MDCheckUpStep::CHECKUP_SUS_STEP01:
            setSusStep01State((int)EnumDefine::MDCheckUpState::CHECKUP_CHECKING);
            break;

        case EnumDefine::MDCheckUpStep::CHECKUP_SUS_STEP02:
            setSusStep02State((int)EnumDefine::MDCheckUpState::CHECKUP_CHECKING);
            break;

        case EnumDefine::MDCheckUpStep::CHECKUP_SUS_STEP03:
            setSusStep03State((int)EnumDefine::MDCheckUpState::CHECKUP_CHECKING);
            break;
        case EnumDefine::MDCheckUpStep::CHECKUP_RESULT_STEP:
            {
                EventDto event;
                QDateTime now = QDateTime::currentDateTime();

                setIsPass(getFeStep01State() == (int)EnumDefine::MDCheckUpState::CHECKUP_PASS &&
                          getFeStep02State() == (int)EnumDefine::MDCheckUpState::CHECKUP_PASS &&
                          getFeStep03State() == (int)EnumDefine::MDCheckUpState::CHECKUP_PASS &&
                          getSusStep01State() == (int)EnumDefine::MDCheckUpState::CHECKUP_PASS &&
                          getSusStep02State() == (int)EnumDefine::MDCheckUpState::CHECKUP_PASS &&
                          getSusStep03State() == (int)EnumDefine::MDCheckUpState::CHECKUP_PASS);

                setChekcupDateTime(now.toString("yyyy/MM/dd hh:mm:ss"));

                event.mEvent.mEventValue = getIsPass() ? (0x01 << 6) : 0x00 ;

                if(getFeStep01State() == EnumDefine::MDCheckUpState::CHECKUP_PASS)
                {
                    event.mEvent.mEventValue = event.mEvent.mEventValue | (0x01 << 5);
                }

                if(getFeStep02State() == EnumDefine::MDCheckUpState::CHECKUP_PASS)
                {
                    event.mEvent.mEventValue = event.mEvent.mEventValue | (0x01 << 4);
                }

                if(getFeStep03State() == EnumDefine::MDCheckUpState::CHECKUP_PASS)
                {
                    event.mEvent.mEventValue = event.mEvent.mEventValue | (0x01 << 3);
                }

                if(getSusStep01State() == EnumDefine::MDCheckUpState::CHECKUP_PASS)
                {
                    event.mEvent.mEventValue = event.mEvent.mEventValue | (0x01 << 2);
                }

                if(getSusStep02State() == EnumDefine::MDCheckUpState::CHECKUP_PASS)
                {
                    event.mEvent.mEventValue = event.mEvent.mEventValue | (0x01 << 1);
                }

                if(getSusStep03State() == EnumDefine::MDCheckUpState::CHECKUP_PASS)
                {
                    event.mEvent.mEventValue = event.mEvent.mEventValue | (0x01);
                }

                event.mEvent.mEventType = EnumDefine::EventType::METAL_CHECKUP_TYPE;

                mpCoreService->onSignalEventAddedEvent(mpDspStatus->mSeq, event);

            }
            mpCoreService->onCommandSendRunCmd(INVALID_ULONGLONG, EnumDefine::RunState::STOP);
            break;
        }
    }
    Q_INVOKABLE void onCommandTimeout()
    {
        switch(mStep)
        {
        case EnumDefine::MDCheckUpStep::CHECKUP_FE_STEP01:
            setFeStep01State((int)EnumDefine::MDCheckUpState::CHECKUP_FAIL);
            emit signalEventStepComplete();
            break;

        case EnumDefine::MDCheckUpStep::CHECKUP_FE_STEP02:
            setFeStep02State((int)EnumDefine::MDCheckUpState::CHECKUP_FAIL);
            emit signalEventStepComplete();
            break;

        case EnumDefine::MDCheckUpStep::CHECKUP_FE_STEP03:
            setFeStep03State((int)EnumDefine::MDCheckUpState::CHECKUP_FAIL);
            emit signalEventStepComplete();
            break;

        case EnumDefine::MDCheckUpStep::CHECKUP_SUS_STEP01:
            setSusStep01State((int)EnumDefine::MDCheckUpState::CHECKUP_FAIL);
            emit signalEventStepComplete();
            break;

        case EnumDefine::MDCheckUpStep::CHECKUP_SUS_STEP02:
            setSusStep02State((int)EnumDefine::MDCheckUpState::CHECKUP_FAIL);
            emit signalEventStepComplete();
            break;

        case EnumDefine::MDCheckUpStep::CHECKUP_SUS_STEP03:
            setSusStep03State((int)EnumDefine::MDCheckUpState::CHECKUP_FAIL);
            emit signalEventStepComplete();
            break;
        }
    }

    void onSignalEventAddEvent(quint16 eventType, quint32 eventValue)
    {
        EnumDefine::MDCheckUpState result;

        if(eventType == EnumDefine::EventType::METAL_DETECT_CHECK_TYPE)
        {
            qDebug() << "MD CHECK UP PASS !";
            result = EnumDefine::MDCheckUpState::CHECKUP_PASS;
        }
        else if(eventType == EnumDefine::EventType::METAL_TRADE_CHECK_TYPE)
        {
            qDebug() << "MD CHECK UP FAIL !";
            result = EnumDefine::MDCheckUpState::CHECKUP_FAIL;
        }
        else
        {
            return;
        }

        switch(mStep)
        {
        case EnumDefine::MDCheckUpStep::CHECKUP_FE_STEP01:
            setFeStep01State(result);
            break;

        case EnumDefine::MDCheckUpStep::CHECKUP_FE_STEP02:
            setFeStep02State(result);
            break;

        case EnumDefine::MDCheckUpStep::CHECKUP_FE_STEP03:
            setFeStep03State(result);
            break;

        case EnumDefine::MDCheckUpStep::CHECKUP_SUS_STEP01:
            setSusStep01State(result);
            break;

        case EnumDefine::MDCheckUpStep::CHECKUP_SUS_STEP02:
            setSusStep02State(result);
            break;

        case EnumDefine::MDCheckUpStep::CHECKUP_SUS_STEP03:
            setSusStep03State(result);
            break;
        }
        emit signalEventStepComplete();
    }

};

#endif // PANELCHECKUPMODEL_H
