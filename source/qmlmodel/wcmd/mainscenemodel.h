#ifndef MAINSCENEMODEL_H
#define MAINSCENEMODEL_H

#include <QObject>
#include "source/service/def/datetimeform.h"
#include "source/globaldef/EnumDefine.h"
#include "source/service/coreservice.h"

class MainSceneModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    swPowerOff    READ getSWPowerOff          NOTIFY signalEventChangedSWPowerOff   )
    Q_PROPERTY(bool    isWCEnable    READ getIsWCEnable          NOTIFY signalEventChangedIsWCEnable   )
    Q_PROPERTY(QString company       READ getCompany             NOTIFY signalEventChangedCompany      )
    Q_PROPERTY(QString tel           READ getTel                 NOTIFY signalEventChangedTel          )
    Q_PROPERTY(bool    isRun         READ getIsRun               NOTIFY signalEventChangedIsRun        )
    Q_PROPERTY(bool    isComm        READ getIsComm              NOTIFY signalEventChangedIsComm       )
    Q_PROPERTY(bool    isAlarm       READ getIsAlarm             NOTIFY signalEventChangedIsAlarm      )
    Q_PROPERTY(bool    IsSensorAlarm READ getIsSensorAlarm       NOTIFY signalEventChangedIsSensorAlarm)
    Q_PROPERTY(bool    IsPhotoAlarm  READ getIsPhotoAlarm        NOTIFY signalEventChangedIsPhotoAlarm )
    Q_PROPERTY(bool    IsMortorAlarm READ getIsMortorAlarm       NOTIFY signalEventChangedIsMortorAlarm)
    Q_PROPERTY(QString clock         READ getClock               NOTIFY signalEventChangedClock        )

public:
    quint64 mDspSeq        = 0;

    bool    mSWPowerOff    = false;
    bool    mIsWCEnable    = true;
    QString mCompany       = "";
    QString mTel           = "";
    bool    mIsRun         = false;
    bool    mIsComm        = false;
    bool    mIsAlarm       = false;
    bool    mIsSensorAlarm = false;
    bool    mIsPhotoAlarm  = false;
    bool    mIsMortorAlarm = false;
    QString mClock         = "";
    QString mPassword      = "";

    bool     getSWPowerOff   (){ return mSWPowerOff   ;}
    bool     getIsWCEnable   (){ return mIsWCEnable   ;}
    QString  getCompany      (){ return mCompany      ;}
    QString  getTel          (){ return mTel          ;}
    bool     getIsRun        (){ return mIsRun        ;}
    bool     getIsComm       (){ return mIsComm       ;}
    bool     getIsAlarm      (){ return mIsAlarm      ;}
    bool     getIsSensorAlarm(){ return mIsSensorAlarm;}
    bool     getIsPhotoAlarm (){ return mIsPhotoAlarm ;}
    bool     getIsMortorAlarm(){ return mIsMortorAlarm;}
    QString  getClock        (){ return mClock        ;}

    void     setSWPowerOff   (bool    value){ if(value == mSWPowerOff )return; mSWPowerOff = value; emit signalEventChangedSWPowerOff(value);}
    void     setIsWCEnable   (bool    value){ if(value == mIsWCEnable )return; mIsWCEnable = value; emit signalEventChangedIsWCEnable(value);}
    void     setCompany      (QString value){ if(value == getCompany())return; mCompany    = value; emit signalEventChangedCompany   (value);}
    void     setTel          (QString value){ if(value == getTel    ())return; mTel        = value; emit signalEventChangedTel       (value);}
    void     setIsRun        (bool    value){ if(value == getIsRun  ())return; mIsRun      = value; emit signalEventChangedIsRun     (value);}
    void     setIsComm       (bool    value){ if(value == getIsComm ())return; mIsComm     = value; emit signalEventChangedIsComm    (value);}
    void     setIsAlarm      (bool    value){ if(value == getIsAlarm())return; mIsAlarm    = value; emit signalEventChangedIsAlarm   (value);}
    void     setIsSensorAlarm(bool    value){ if(value == mIsSensorAlarm) return; mIsSensorAlarm = value; emit signalEventChangedIsSensorAlarm(value);}
    void     setIsPhotoAlarm (bool    value){ if(value == mIsPhotoAlarm ) return; mIsPhotoAlarm  = value; emit signalEventChangedIsPhotoAlarm (value);}
    void     setIsMortorAlarm(bool    value){ if(value == mIsMortorAlarm) return; mIsMortorAlarm = value; emit signalEventChangedIsMortorAlarm(value);}
    void     setClock  (QString value){ if(value == getClock  ())return; mClock   = value; emit signalEventChangedClock  (value);}

signals:
    void signalEventChangedSWPowerOff   (bool    value);
    void signalEventChangedIsWCEnable   (bool    value);
    void signalEventChangedCompany      (QString value);
    void signalEventChangedTel          (QString value);
    void signalEventChangedIsRun        (bool    value);
    void signalEventChangedIsComm       (bool    value);
    void signalEventChangedIsAlarm      (bool    value);
    void signalEventChangedIsSensorAlarm(bool    value);
    void signalEventChangedIsPhotoAlarm (bool    value);
    void signalEventChangedIsMortorAlarm(bool    value);
    void signalEventChangedClock        (QString value);

public slots:
    Q_INVOKABLE bool onCommandComparePwd(QString value)
    {
        if(pLSettingSP->mSecuritySetting.mPwd == value)
            return true;

        return false;
    }

    Q_INVOKABLE bool onCommandCompareAdminPwd(QString value)
    {
        if(pLSettingSP->mSecuritySetting.mAdminPwd == value)
            return true;

        return false;
    }

    Q_INVOKABLE void onCommandSetRun(bool value)
    {
        CHECK_FALSE_RETURN((mDspSeq != 0));

        quint16 runValue = value == false ? EnumDefine::RunState::STOP : EnumDefine::RunState::RUN;

        DspMaster * pDsp = pDspSP->findDspMaster(mDspSeq);

        /*if(pDsp->mRcvDataStore.mCommStatusBlock.mData.mRun == EnumDefine::RunState::STOP && value == false)
            return;
        else */if(pDsp->mRcvDataStore.mCommStatusBlock.mData.mRun != EnumDefine::RunState::STOP && value == true)
            return;

        if(value && pLSettingSP->mHMISetting.mIsDebugMode)
        {
            runValue = EnumDefine::RunState::DETECT_OFF_RUN;
        }

        pDspSP->sendRunCmd(mDspSeq, runValue);
    }

    Q_INVOKABLE void onCommandShutdown()
    {
        QString cmd;

        cmd.sprintf("sudo shutdown now");

        system(cmd.toStdString().c_str());
    }

//  down layer ===================================================================================
public slots:
    void onChangedInformation(InformationDto dto)
    {
        setCompany(dto.mCompany);
        setTel    (dto.mTel    );
    }

    void onTimeTick(QDateTime now)
    {
        setClock(now.toString(DATE_TIME_FMT));
    }

    void onChangedDspStatus(quint64 dspSeq, DspStatusDto dto)
    {
        CHECK_FALSE_RETURN((dspSeq != 0));

        DspMaster * pDsp = pDspSP->findDspMaster(mDspSeq);

        setIsRun        ( dto.mCommStatus.mRun != EnumDefine::RunState::STOP                   );

        setIsAlarm      ( dto.getAlarm() || pDsp->mIsDevSettingAlarm || pDsp->mIsPDSettingAlarm);
        setIsSensorAlarm( dto.getSensorAlarm()                                                 );
        setIsPhotoAlarm ( dto.getPhotoAlarm ()                                                 );
        setIsMortorAlarm( dto.getMotorAlarm ()                                                 );
    }

    void onChangedDspIsConnect(quint64 dspSeq, bool value)
    {
        CHECK_FALSE_RETURN((dspSeq != 0));

        DspMaster * pDsp = pDspSP->findDspMaster(mDspSeq);

        setIsComm(pDsp->mIsConnect);
    }

    void onChangedDevSetting(DevSettingDto dto)
    {
        setIsWCEnable(dto.mDspForm.mCommSetting.mMachineMode != EnumDef::MACHINE_MODE_ALU);
    }
    void onChangedHMISetting(HMISettingDto dto)
    {
        setSWPowerOff(dto.mSWPowerOff);
    }

//  internal layer ===================================================================================
public:
    explicit MainSceneModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_LSETTING_CHANGED_INFO;
        onChangedInformation(pLSettingSP->mInformation);

        ENABLE_SLOT_LSETTING_CHANGED_DEV_SETTING;
        onChangedDevSetting(pLSettingSP->mDevSetting);

        ENABLE_SLOT_LSETTING_CHANGED_HMI_SETTINGT;
        onChangedHMISetting(pLSettingSP->mHMISetting);

        ENABLE_SLOT_TIMER_TICK;

        ENABLE_SLOT_DSP_CHANGED_DSP_STATUS;

        ENABLE_SLOT_DSP_CHANGED_ISCONNECT;

        CHECK_FALSE_RETURN((pDspSP->mDspList.size() > 0));

        mDspSeq = pDspSP->mDspList[0]->mSeq;

        DspMaster * pDsp = pDspSP->findDspMaster(mDspSeq);
        onChangedDspStatus(mDspSeq, pDsp->mRcvDataStore.getStatusDto());
        onChangedDspIsConnect(mDspSeq, pDsp->mIsConnect);
    }
};

#endif // MAINSCENEMODEL_H
