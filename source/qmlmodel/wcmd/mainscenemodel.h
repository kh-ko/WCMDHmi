#ifndef MAINSCENEMODEL_H
#define MAINSCENEMODEL_H

#include <QObject>
#include <QtMath>
#include "source/service/def/datetimeform.h"
#include "source/globaldef/qmlenumdef.h"
#include "source/service/coreservice.h"

class MainSceneModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    swPowerOff         READ getSWPowerOff          NOTIFY signalEventChangedSWPowerOff        )
    Q_PROPERTY(bool    isWCEnable         READ getIsWCEnable          NOTIFY signalEventChangedIsWCEnable        )
    Q_PROPERTY(bool    isMDEnable         READ getIsMDEnable          NOTIFY signalEventChangedIsMDEnable        )
    Q_PROPERTY(QString company            READ getCompany             NOTIFY signalEventChangedCompany           )
    Q_PROPERTY(QString tel                READ getTel                 NOTIFY signalEventChangedTel               )
    Q_PROPERTY(bool    isWait             READ getIsWait              NOTIFY signalEventChangedIsWait            )
    Q_PROPERTY(bool    isZeroProc         READ getIsZeroProc          NOTIFY signalEventChangedIsZeroProc        )
    Q_PROPERTY(bool    isRun              READ getIsRun               NOTIFY signalEventChangedIsRun             )
    Q_PROPERTY(bool    isComm             READ getIsComm              NOTIFY signalEventChangedIsComm            )
    Q_PROPERTY(bool    isAlarm            READ getIsAlarm             NOTIFY signalEventChangedIsAlarm           )
    Q_PROPERTY(bool    isWCSensorAlarm    READ getIsWCSensorAlarm     NOTIFY signalEventChangedIsWCSensorAlarm   )
    Q_PROPERTY(bool    isWCPhotoAlarm     READ getIsWCPhotoAlarm      NOTIFY signalEventChangedIsWCPhotoAlarm    )
    Q_PROPERTY(bool    isWCMortorAlarm    READ getIsWCMortorAlarm     NOTIFY signalEventChangedIsWCMortorAlarm   )
    Q_PROPERTY(bool    isWCRJMortorAlarm  READ getIsWCRJMortorAlarm   NOTIFY signalEventChangedIsWCRJMortorAlarm )
    Q_PROPERTY(bool    isWCMeasureAlarm   READ getIsWCMeasureAlarm    NOTIFY signalEventChangedIsWCMeasureAlarm  )
    Q_PROPERTY(bool    isMDSensorAlarm    READ getIsMDSensorAlarm     NOTIFY signalEventChangedIsMDSensorAlarm   )
    Q_PROPERTY(bool    isMDPhotoAlarm     READ getIsMDPhotoAlarm      NOTIFY signalEventChangedIsMDPhotoAlarm    )
    Q_PROPERTY(bool    isMDMortorAlarm    READ getIsMDMortorAlarm     NOTIFY signalEventChangedIsMDMortorAlarm   )
    Q_PROPERTY(bool    isMDRJMortorAlarm  READ getIsMDRJMortorAlarm   NOTIFY signalEventChangedIsMDRJMortorAlarm )
    Q_PROPERTY(bool    isMDSpeedAlarm     READ getIsMDSpeedAlarm      NOTIFY signalEventChangedIsMDSpeedAlarm    )
    Q_PROPERTY(QString clock              READ getClock               NOTIFY signalEventChangedClock             )
    Q_PROPERTY(int     weightFixedN       READ getWeightFixedN        NOTIFY signalEventChangedWeightFixedN      )

public:
    quint64 mDspSeq            = 0;

    bool    mSWPowerOff        = false;
    bool    mIsWCEnable        = true;
    bool    mIsMDEnable        = true;
    QString mCompany           = "";
    QString mTel               = "";
    bool    mIsWait            = false;
    bool    mIsZeroProc        = false;
    bool    mIsRun             = false;
    bool    mIsComm            = false;
    bool    mIsAlarm           = false;
    bool    mIsWCSensorAlarm   = false;
    bool    mIsWCPhotoAlarm    = false;
    bool    mIsWCMortorAlarm   = false;
    bool    mIsWCRJMortorAlarm = false;
    bool    mIsWCMeasureAlarm  = false;
    bool    mIsMDSensorAlarm   = false;
    bool    mIsMDPhotoAlarm    = false;
    bool    mIsMDMortorAlarm   = false;
    bool    mIsMDRJMortorAlarm = false;
    bool    mIsMDSpeedAlarm    = false;

    QString mClock             = "";
    QString mPassword          = "";
    int     mWeightFixedN      = 1;

    bool     getSWPowerOff       (){ return mSWPowerOff       ;}
    bool     getIsWCEnable       (){ return mIsWCEnable       ;}
    bool     getIsMDEnable       (){ return mIsMDEnable       ;}
    QString  getCompany          (){ return mCompany          ;}
    QString  getTel              (){ return mTel              ;}
    bool     getIsWait           (){ return mIsWait           ;}
    bool     getIsZeroProc       (){ return mIsZeroProc       ;}
    bool     getIsRun            (){ return mIsRun            ;}
    bool     getIsComm           (){ return mIsComm           ;}
    bool     getIsAlarm          (){ return (mIsAlarm || mIsMDSpeedAlarm);}
    bool     getIsWCSensorAlarm  (){ return mIsWCSensorAlarm  ;}
    bool     getIsWCPhotoAlarm   (){ return mIsWCPhotoAlarm   ;}
    bool     getIsWCMortorAlarm  (){ return mIsWCMortorAlarm  ;}
    bool     getIsWCRJMortorAlarm(){ return mIsWCRJMortorAlarm;}
    bool     getIsWCMeasureAlarm (){ return mIsWCMeasureAlarm ;}
    bool     getIsMDSensorAlarm  (){ return mIsMDSensorAlarm  ;}
    bool     getIsMDPhotoAlarm   (){ return mIsMDPhotoAlarm   ;}
    bool     getIsMDMortorAlarm  (){ return mIsMDMortorAlarm  ;}
    bool     getIsMDRJMortorAlarm(){ return mIsMDRJMortorAlarm;}
    bool     getIsMDSpeedAlarm   (){ return mIsMDSpeedAlarm   ;}
    QString  getClock            (){ return mClock            ;}
    int      getWeightFixedN     (){ return mWeightFixedN     ;}

    void     setSWPowerOff       (bool    value){ if(value == mSWPowerOff       )return; mSWPowerOff        = value; emit signalEventChangedSWPowerOff       (value);}
    void     setIsWCEnable       (bool    value){ if(value == mIsWCEnable       )return; mIsWCEnable        = value; emit signalEventChangedIsWCEnable       (value);}
    void     setIsMDEnable       (bool    value){ if(value == mIsMDEnable       )return; mIsMDEnable        = value; emit signalEventChangedIsMDEnable       (value);}
    void     setCompany          (QString value){ if(value == getCompany()      )return; mCompany           = value; emit signalEventChangedCompany          (value);}
    void     setIsWait           (bool    value){ if(value == getIsWait()       )return; mIsWait            = value; emit signalEventChangedIsWait           (value);}
    void     setIsZeroProc       (bool    value){ if(value == mIsZeroProc       )return; mIsZeroProc        = value; emit signalEventChangedIsZeroProc       (value);}
    void     setTel              (QString value){ if(value == getTel    ()      )return; mTel               = value; emit signalEventChangedTel              (value);}
    void     setIsRun            (bool    value){ if(value == getIsRun  ()      )return; mIsRun             = value; emit signalEventChangedIsRun            (value);}
    void     setIsComm           (bool    value){ if(value == getIsComm ()      )return; mIsComm            = value; emit signalEventChangedIsComm           (value);}
    void     setIsAlarm          (bool    value){ if(value == mIsAlarm          )return; mIsAlarm           = value; emit signalEventChangedIsAlarm          (getIsAlarm());}
    void     setIsWCSensorAlarm  (bool    value){ if(value == mIsWCSensorAlarm  )return; mIsWCSensorAlarm   = value; emit signalEventChangedIsWCSensorAlarm  (value);}
    void     setIsWCPhotoAlarm   (bool    value){ if(value == mIsWCPhotoAlarm   )return; mIsWCPhotoAlarm    = value; emit signalEventChangedIsWCPhotoAlarm   (value);}
    void     setIsWCMortorAlarm  (bool    value){ if(value == mIsWCMortorAlarm  )return; mIsWCMortorAlarm   = value; emit signalEventChangedIsWCMortorAlarm  (value);}
    void     setIsWCRJMortorAlarm(bool    value){ if(value == mIsWCRJMortorAlarm)return; mIsWCRJMortorAlarm = value; emit signalEventChangedIsWCRJMortorAlarm(value);}
    void     setIsWCMeasureAlarm (bool    value){ if(value == mIsWCMeasureAlarm )return; mIsWCMeasureAlarm  = value; emit signalEventChangedIsWCMeasureAlarm (value);}
    void     setIsMDSensorAlarm  (bool    value){ if(value == mIsMDSensorAlarm  )return; mIsMDSensorAlarm   = value; emit signalEventChangedIsMDSensorAlarm  (value);}
    void     setIsMDPhotoAlarm   (bool    value){ if(value == mIsMDPhotoAlarm   )return; mIsMDPhotoAlarm    = value; emit signalEventChangedIsMDPhotoAlarm   (value);}
    void     setIsMDMortorAlarm  (bool    value){ if(value == mIsMDMortorAlarm  )return; mIsMDMortorAlarm   = value; emit signalEventChangedIsMDMortorAlarm  (value);}
    void     setIsMDRJMortorAlarm(bool    value){ if(value == mIsMDRJMortorAlarm)return; mIsMDRJMortorAlarm = value; emit signalEventChangedIsMDRJMortorAlarm(value);}
    void     setIsMDSpeedAlarm   (bool    value){ if(value == mIsMDSpeedAlarm   )return; mIsMDSpeedAlarm    = value; emit signalEventChangedIsMDSpeedAlarm   (value);}
    void     setClock            (QString value){ if(value == getClock  ()      )return; mClock             = value; emit signalEventChangedClock            (value);}
    void     setWeightFixedN     (int     value){ if(value == mWeightFixedN     )return; mWeightFixedN      = value; emit signalEventChangedWeightFixedN     (value);}
signals:
    void signalEventChangedSWPowerOff       (bool    value);
    void signalEventChangedIsWCEnable       (bool    value);
    void signalEventChangedIsMDEnable       (bool    value);
    void signalEventChangedCompany          (QString value);
    void signalEventChangedTel              (QString value);
    void signalEventChangedIsWait           (bool    value);
    void signalEventChangedIsZeroProc       (bool    value);
    void signalEventChangedIsRun            (bool    value);
    void signalEventChangedIsComm           (bool    value);
    void signalEventChangedIsAlarm          (bool    value);
    void signalEventChangedIsWCSensorAlarm  (bool    value);
    void signalEventChangedIsWCPhotoAlarm   (bool    value);
    void signalEventChangedIsWCMortorAlarm  (bool    value);
    void signalEventChangedIsWCRJMortorAlarm(bool    value);
    void signalEventChangedIsWCMeasureAlarm (bool    value);
    void signalEventChangedIsMDSensorAlarm  (bool    value);
    void signalEventChangedIsMDPhotoAlarm   (bool    value);
    void signalEventChangedIsMDMortorAlarm  (bool    value);
    void signalEventChangedIsMDRJMortorAlarm(bool    value);
    void signalEventChangedIsMDSpeedAlarm   (bool    value);
    void signalEventChangedClock            (QString value);
    void signalEventChangedWeightFixedN     (int     value);

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

        quint16 runValue = value == false ? EnumDef::RUN_MODE_STOP : EnumDef::RUN_MODE_RUN;

        DspMaster * pDsp = pDspSP->findDspMaster(mDspSeq);

        /*if(pDsp->mRcvDataStore.mCommStatusBlock.mData.mRun == EnumDef::RUN_MODE_STOP && value == false)
            return;
        else */if(pDsp->mRcvDataStore.mCommStatusBlock.mData.mRun != EnumDef::RUN_MODE_STOP && value == true)
            return;

        if(value && pLSettingSP->mHMISetting.mIsDebugMode)
        {
            runValue = EnumDef::RUN_MODE_DETECT_OFF_RUN;
        }

        pDspSP->sendRunCmd(mDspSeq, runValue);
    }

    Q_INVOKABLE void onCommandResetGroupCount()
    {
        CHECK_FALSE_RETURN((mDspSeq != 0));

        DspMaster * pDsp = pDspSP->findDspMaster(mDspSeq);

        CHECK_PTR_RETURN(pDsp);

        pDspSP->sendResetGCntCmd(mDspSeq, 1);
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

        setIsRun            ( dto.mCommStatus.mRun != EnumDef::RUN_MODE_STOP                   );

        setIsAlarm          ( dto.getAlarm() || pDsp->mIsDevSettingAlarm || pDsp->mIsPDSettingAlarm || mIsMDSpeedAlarm);
        setIsWCSensorAlarm  ( dto.getIsWCSensorAlarm  ());
        setIsWCPhotoAlarm   ( dto.getIsWCPhotoAlarm   ());
        setIsWCMortorAlarm  ( dto.getIsWCMortorAlarm  ());
        setIsWCRJMortorAlarm( dto.getIsWCRJMortorAlarm());
        setIsWCMeasureAlarm ( dto.getIsWCMeasureAlarm ());
        setIsMDSensorAlarm  ( dto.getIsMDSensorAlarm  ());
        setIsMDPhotoAlarm   ( dto.getIsMDPhotoAlarm   ());
        setIsMDMortorAlarm  ( dto.getIsMDMortorAlarm  ());
        setIsMDRJMortorAlarm( dto.getIsMDRJMortorAlarm());

        setIsZeroProc       ( dto.mWCStatus.mZeroProc == 1);
        setIsWait           ( dto.mWCStatus.mWait == 1    );

    }

    void onChangedDspIsConnect(quint64 dspSeq, bool value)
    {
        CHECK_FALSE_RETURN((dspSeq != 0));

        DspMaster * pDsp = pDspSP->findDspMaster(mDspSeq);

        setIsComm(pDsp->mIsConnect);
    }
    void onChangedRefVoltage(quint64 dspSeq, qint32 value)
    {
        qDebug() << "[debug]onChangedRefVoltage = " << value;
        CHECK_FALSE_RETURN((dspSeq != 0));

        DevSettingDto dto;
        dto = pLSettingSP->mDevSetting;
        dto.mDspForm.mWCSetting.mRefVoltage = (qint16)value;

        qDebug() << "[debug]onChangedRefVoltage : setDevSetting";
        pLSettingSP->setDevSetting(dto);
    }

    void onChangedDevSetting(DevSettingDto dto)
    {
        setIsWCEnable(dto.mDspForm.mCommSetting.mMachineMode != EnumDef::MACHINE_MODE_ALU);
        setIsMDEnable(dto.mDspForm.mCommSetting.mMachineMode != EnumDef::MACHINE_MODE_WC);

        setIsMDSpeedAlarm(isSpeedAlarm());
        emit signalEventChangedIsAlarm(getIsAlarm());

        if(dto.mDspForm.mWCSetting.mScaler%10 != 0)
        {
            setWeightFixedN(3);
        }
        else if(dto.mDspForm.mWCSetting.mScaler%100 != 0)
        {
            setWeightFixedN(2);
        }
        else
        {
            setWeightFixedN(1);
        }
    }
    void onChangedHMISetting(HMISettingDto dto)
    {
        setSWPowerOff(dto.mSWPowerOff);
    }

    void onChangedCurrPDSetting(PDSettingDto dto)
    {
        setIsMDSpeedAlarm(isSpeedAlarm());
        emit signalEventChangedIsAlarm(getIsAlarm());
    }

//  internal layer ===================================================================================
public:
    explicit MainSceneModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_LSETTING_CHANGED_INFO;
        onChangedInformation(pLSettingSP->mInformation);

        ENABLE_SLOT_LSETTING_CHANGED_DEV_SETTING;
        onChangedDevSetting(pLSettingSP->mDevSetting);

        ENABLE_SLOT_LSETTING_CHANGED_HMI_SETTING;
        onChangedHMISetting(pLSettingSP->mHMISetting);

        ENABLE_SLOT_PDSETTING_CHANGED_CURR_PD;
        onChangedCurrPDSetting(pProductSP->mCurrPD);

        ENABLE_SLOT_TIMER_TICK;

        ENABLE_SLOT_DSP_CHANGED_DSP_STATUS;

        ENABLE_SLOT_DSP_CHANGED_ISCONNECT;

        ENABLE_SLOT_DSP_CHANGED_REF_VLOTAGE;

        CHECK_FALSE_RETURN((pDspSP->mDspList.size() > 0));

        mDspSeq = pDspSP->mDspList[0]->mSeq;

        DspMaster * pDsp = pDspSP->findDspMaster(mDspSeq);
        onChangedDspStatus(mDspSeq, pDsp->mRcvDataStore.getStatusDto());
        onChangedDspIsConnect(mDspSeq, pDsp->mIsConnect);
    }

private:
    int isSpeedAlarm()
    {
        int maxSpeed = 100;
        double tOpen = pLSettingSP->mDevSetting.mDspForm.mCommSetting.mSorter01OpenTime;
        double lR    = pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistanceToWeightChecker + pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistToSorter01;
        double lWR   = pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistToSorter01;
        double lW    = pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mSensorLength;
        double lS    = pLSettingSP->mDevSetting.mDspForm.mSizeSetting.mDistancePhotoToSensor;
        double wS    = 50;
        double lP    = pProductSP->mCurrPD.mDspForm.mCommSetting.mLength;

        if(tOpen == 0)
        {
            return false;
        }

        if(getIsWCEnable())
        {
            maxSpeed = qFloor(((lWR - lW ) / tOpen ) *60);
        }
        else
        {
            maxSpeed = qFloor(((lR - lS - wS - lP ) / tOpen ) *60);
        }

        if(pProductSP->mCurrPD.mDspForm.mCommSetting.mSpeed > maxSpeed)
            return true;

        return false;
    }
};

#endif // MAINSCENEMODEL_H
