#ifndef DSPSPROVIDER_H
#define DSPSPROVIDER_H
#include <QObject>
#include <QDateTime>
#include <QTimer>

#include "source/service/def/filedef.h"
#include "source/service/dsp/dspmaster.h"
#include "source/service/util/exceptionutil.h"
#include "source/service/util/filefolderreader.h"
#include "source/service/util/filereaderex.h"
#include "source/service/util/filewriterex.h"
#include "source/service/timer/timersprovider.h"
#include "source/service/localsetting/localsettingsprovider.h"
#include "source/service/productsetting/productsprovider.h"
#include "source/service/dsp/dspsearch.h"
#include "source/service/util/sproviderconnectutil.h"

#define pDspSP DspSProvider::getInstance()

class DspSProvider : public QObject
{
    Q_OBJECT

public :
    static DspSProvider * getInstance()
    {
        static DspSProvider *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new DspSProvider();
        }

        return mpSelf;
    }

    explicit DspSProvider(QObject *parent = nullptr):QObject(parent)
    {
    }
    ~DspSProvider()
    {
        stop();
    }

    void start(DspDevSettingDto devSetting, DspPDSettingDto pdSetting)
    {
        qDebug() << "[DspSProvider::start]";

        loadDspMaster(devSetting, pdSetting);

        if(mDspList.size() < 1)
        {
            DspConnInfoDto dto;
            dto.setDefaultValue();

            addDspMaster(dto, devSetting, pdSetting);
        }

        mFRIng = false;
        mIsRunning = true;

        ENABLE_SLOT_TIMER_TICK;
        ENABLE_SLOT_LSETTING_CHANGED_DEV_SETTING;
        ENABLE_SLOT_PDSETTING_CHANGED_CURR_PD;

        connect(&mDspSearcher, SIGNAL(signalEventFoundDsp(QString)), this, SLOT(onFoundDsp(QString)));
        qDebug() << "[DspSProvider::started]";

        emit signalEventStarted();
    }

    void stop()
    {
        mIsRunning = false;

        deLoadDspMaster();
        emit signalEventStopped();
    }

    void searchDsp()
    {
        mDspSearcher.search();
    }

    void factoryReset()
    {
        CHECK_FALSE_RETURN(mIsRunning)

        mFRIng = true;

        foreach(DspMaster * master, mDspList)
        {
            master->sendFR(1);
        }
    }

    void addDsp          (DspConnInfoDto& dto, DspDevSettingDto devSetting, DspPDSettingDto pdSetting)
    {
        CHECK_FALSE_RETURN(mIsRunning);

        addDspMaster(dto, devSetting, pdSetting);
    }

    DspMaster * findDspMaster(quint64 seq)
    {
        foreach(DspMaster * master, mDspList)
        {
            if(master->mSeq == seq)
                return master;
        }

        return nullptr;
    }

    void sendZeroCmd           (quint64 dspSeq                         ){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)) DspMaster * master = findDspMaster(dspSeq); CHECK_PTR_RETURN(master) master->sendZero           (1    );}
    void sendWCCaribCmd        (quint64 dspSeq, quint16 value          ){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)) DspMaster * master = findDspMaster(dspSeq); CHECK_PTR_RETURN(master) master->sendWCCarib        (value);}
    void sendRunCmd            (quint64 dspSeq, quint16 value          ){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)) DspMaster * master = findDspMaster(dspSeq); CHECK_PTR_RETURN(master) master->sendRun            (value);}
    void sendWCGraphOnCmd      (quint64 dspSeq, bool value             ){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)) DspMaster * master = findDspMaster(dspSeq); CHECK_PTR_RETURN(master) master->sendWCGraphOn      (value);}
    void sendMDGraphOnCmd      (quint64 dspSeq, bool value             ){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)) DspMaster * master = findDspMaster(dspSeq); CHECK_PTR_RETURN(master) master->sendMDGraphOn      (value);}
    void sendRefVoltageResetCmd(quint64 dspSeq                         ){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)) DspMaster * master = findDspMaster(dspSeq); CHECK_PTR_RETURN(master) master->sendRefVoltageReset(1    );}
    void sendDspIDCmd          (quint64 dspSeq, quint32 value          ){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)) DspMaster * master = findDspMaster(dspSeq); CHECK_PTR_RETURN(master) master->sendDevID          (value);}
    void sendResetGCntCmd      (quint64 dspSeq, quint16 value          ){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)) DspMaster * master = findDspMaster(dspSeq); CHECK_PTR_RETURN(master) master->sendResetGCnt      (value);}
    void sendDevSetting        (quint64 dspSeq, DspDevSettingDto value ){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)) DspMaster * master = findDspMaster(dspSeq); CHECK_PTR_RETURN(master) master->sendDevSetting     (value);}
    void sendPDSetting         (quint64 dspSeq, DspPDSettingDto  value ){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)) DspMaster * master = findDspMaster(dspSeq); CHECK_PTR_RETURN(master) master->sendPDSetting      (value);}

    void sendAllZeroCmd           (                       ){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)) foreach(DspMaster * master, mDspList){master->sendZero           (1    );}}
    void sendAllWCCaribCmd        (quint16 value          ){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)) foreach(DspMaster * master, mDspList){master->sendWCCarib        (value);}}
    void sendAllRunCmd            (quint16 value          ){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)) foreach(DspMaster * master, mDspList){master->sendRun            (value);}}
    void sendAllWCGraphOnCmd      (bool value             ){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)) foreach(DspMaster * master, mDspList){master->sendWCGraphOn      (value);}}
    void sendAllMDGraphOnCmd      (bool value             ){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)) foreach(DspMaster * master, mDspList){master->sendMDGraphOn      (value);}}
    void sendAllRefVoltageResetCmd(                       ){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)) foreach(DspMaster * master, mDspList){master->sendRefVoltageReset(1    );}}
    void sendAllDevSetting        (DspDevSettingDto value ){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)) foreach(DspMaster * master, mDspList){master->sendDevSetting     (value);}}
    void sendAllPDSetting         (DspPDSettingDto value  ){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)) foreach(DspMaster * master, mDspList){master->sendPDSetting      (value);}}
    void sendAllReadAlwaysData    (                       ){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)) foreach(DspMaster * master, mDspList){master->sendReadAlwaysData (     );}}

signals:
    void signalEventStarted                         ();
    void signalEventStopped                         ();
    void signalEventChangedIsConnect                (quint64 deviceSeq, bool value);
    void signalEventCompletedFactoryReset           (bool    isSucc);

    void signalEventChangedRemoteDeviceSetting      (quint64 deviceSeq, DspDevSettingDto dto);
    void signalEventChangedRemoteProductSetting     (quint64 deviceSeq, DspPDSettingDto  dto);
    void signalEventChangedDeviceStatus             (quint64 deviceSeq, DspStatusDto     dto);
    void signalEventChangedDeviceInfo               (quint64 deviceSeq, DspInfoDto       dto);
    void signalEventAddedEvent                      (quint64 deviceSeq, DspEventDto      dto);
    void signalEventChangedRefVoltage               (quint64 deviceSeq, qint32         value);
    void signalEventAddedWeightCheckerGraph         (quint64 deviceSeq, DspWCGDto        dto);
    void signalEventAddedMetalDetectorGraph         (quint64 deviceSeq, DspMDGDto        dto);

    void signalEventFoundDsp                        (QString ip);
public slots:
    void onChangedDevSetting(DevSettingDto dto)
    {
        qDebug() << "[debug]onChangedDevSetting : ref vol = " << dto.mDspForm.mWCSetting.mRefVoltage;

        CHECK_FALSE_RETURN((mIsRunning && mFRIng == false))
        sendAllDevSetting(dto.mDspForm);
    }

    void onChangedCurrPDSetting(PDSettingDto dto)
    {
        CHECK_FALSE_RETURN((mIsRunning && mFRIng == false))
        sendAllPDSetting(dto.mDspForm);
    }

    void onTimeTick(QDateTime now)
    {
        CHECK_FALSE_RETURN(mIsRunning);

        foreach(DspMaster * master, mDspList)
        {
            master->onTimeTick(now);
        }

        if(mFRIng)
            checkDspFRState();
        else
            sendAllReadAlwaysData();
    }

public slots:
    void onDspChangedIsConnect(quint64 dspSeq, bool value)
    {
        CHECK_FALSE_RETURN((mIsRunning && mFRIng == false))

        qDebug() << "[DspSProvider::onDspChangedIsConnect]" << value;

        emit signalEventChangedIsConnect(dspSeq , value);
    }

    void checkDspFRState()
    {
        foreach(DspMaster * master, mDspList)
        {
            if(master->mFRState == EnumDef::DSP_FR_STATE_NONE)
                return;
        }

        foreach(DspMaster * master, mDspList)
        {
            if(master->mFRState == EnumDef::DSP_FR_STATE_FAIL)
            {
                emit signalEventCompletedFactoryReset(false);
                stop();
                return;
            }
        }

        emit signalEventCompletedFactoryReset(true);
        stop();
    }
    void onDspAddedWCG             (quint64 dspSeq, DspWCGDto        dto){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)); emit signalEventAddedWeightCheckerGraph    (dspSeq,   dto);}
    void onDspAddedMDG             (quint64 dspSeq, DspMDGDto        dto){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)); emit signalEventAddedMetalDetectorGraph    (dspSeq,   dto);}
    void onDspChangedDevSetting    (quint64 dspSeq, DspDevSettingDto dto){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)); emit signalEventChangedRemoteDeviceSetting (dspSeq,   dto);}
    void onDspChangedPDSetting     (quint64 dspSeq, DspPDSettingDto  dto){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)); emit signalEventChangedRemoteProductSetting(dspSeq,   dto);}
    void onDspChangedStatus        (quint64 dspSeq, DspStatusDto     dto){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)); emit signalEventChangedDeviceStatus        (dspSeq,   dto);}
    void onDspChangedInfo          (quint64 dspSeq, DspInfoDto       dto){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)); emit signalEventChangedDeviceInfo          (dspSeq,   dto);}
    void onDspAddedEvent           (quint64 dspSeq, DspEventDto      dto){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)); emit signalEventAddedEvent                 (dspSeq,   dto);}
    void onDspChangedRefVoltage    (quint64 dspSeq, qint32         value){ CHECK_FALSE_RETURN((mIsRunning && mFRIng == false)); emit signalEventChangedRefVoltage          (dspSeq, value);}

    void onFoundDsp                (QString ip){ emit signalEventFoundDsp(ip);}

public :
    QList<DspMaster *> mDspList;

private :
    quint64 mLastSeq = 0;
    bool    mIsRunning = false;
    bool    mFRIng = false;
    DspSearch mDspSearcher;

    void loadDspMaster(DspDevSettingDto devSetting, DspPDSettingDto pdSetting)
    {
        quint64 maxSeq = 0;

        FileFolderReader folder;

        folder.open(FileDef::DSP_CONNINFO_DIR(), "*.txt");

        for(int i = 0; i < folder.fileCount(); i ++)
        {
            DspConnInfoDto dto;

            if(dto.setValue(folder.readFile(i)))
            {
                qDebug() << "[DspSProvider::loadDspMaster]" << dto.toString();

                if(maxSeq < dto.mDspSeq) maxSeq = dto.mDspSeq;
                createDspMaster(dto, devSetting, pdSetting);
            }
            else
            {
                qDebug() << "[DspSProvider::loadDspMaster]invaild value";
            }
        }

        mLastSeq = readFileLastSeq();

        if(mLastSeq < maxSeq)
        {
            mLastSeq = maxSeq;
            writeFileLastSeq(mLastSeq);
        }
    }
    void createDspMaster(DspConnInfoDto dto, DspDevSettingDto devSetting, DspPDSettingDto pdSetting)
    {
       CHECK_FALSE_RETURN((findDspMaster(dto.mDspSeq) == nullptr));

        DspMaster * master = new DspMaster(dto.mDspSeq, dto.mIp, dto.mPort, devSetting, pdSetting, this);

        connect(master, SIGNAL(signalEventChangedIsConnect      (quint64, bool            )), this, SLOT(onDspChangedIsConnect     (quint64, bool             )));
        connect(master, SIGNAL(signalEventAddedWCG              (quint64, DspWCGDto       )), this, SLOT(onDspAddedWCG             (quint64, DspWCGDto        )));
        connect(master, SIGNAL(signalEventAddedMDG              (quint64, DspMDGDto       )), this, SLOT(onDspAddedMDG             (quint64, DspMDGDto        )));
        connect(master, SIGNAL(signalEventChangedDevSetting     (quint64, DspDevSettingDto)), this, SLOT(onDspChangedDevSetting    (quint64, DspDevSettingDto )));
        connect(master, SIGNAL(signalEventChangedPDSetting      (quint64, DspPDSettingDto )), this, SLOT(onDspChangedPDSetting     (quint64, DspPDSettingDto  )));
        connect(master, SIGNAL(signalEventChangedStatus         (quint64, DspStatusDto    )), this, SLOT(onDspChangedStatus        (quint64, DspStatusDto     )));
        connect(master, SIGNAL(signalEventChangedInfo           (quint64, DspInfoDto      )), this, SLOT(onDspChangedInfo          (quint64, DspInfoDto       )));
        connect(master, SIGNAL(signalEventAddedEvent            (quint64, DspEventDto     )), this, SLOT(onDspAddedEvent           (quint64, DspEventDto      )));
        connect(master, SIGNAL(signalEventChangedRefVoltage     (quint64, qint32          )), this, SLOT(onDspChangedRefVoltage    (quint64, qint32           )));

        mDspList.append(master);
    }

    void addDspMaster(DspConnInfoDto& dto, DspDevSettingDto devSetting, DspPDSettingDto pdSetting)
    {
        mLastSeq++;
        dto.mDspSeq = mLastSeq;

        writeFileLastSeq(mLastSeq);

        CHECK_FALSE_RETURN(writeFileDspConnInfo(dto))

        createDspMaster(dto, devSetting, pdSetting);

    }

    void deLoadDspMaster()
    {
        foreach(DspMaster * master, mDspList)
        {
            disconnect(master, SIGNAL(signalEventChangedIsConnect      (quint64, bool            )), this, SLOT(onDspChangedIsConnect     (quint64, bool             )));
            disconnect(master, SIGNAL(signalEventAddedWCG              (quint64, DspWCGDto       )), this, SLOT(onDspAddedWCG             (quint64, DspWCGDto        )));
            disconnect(master, SIGNAL(signalEventAddedMDG              (quint64, DspMDGDto       )), this, SLOT(onDspAddedMDG             (quint64, DspMDGDto        )));
            disconnect(master, SIGNAL(signalEventChangedDevSetting     (quint64, DspDevSettingDto)), this, SLOT(onDspChangedDevSetting    (quint64, DspDevSettingDto )));
            disconnect(master, SIGNAL(signalEventChangedPDSetting      (quint64, DspPDSettingDto )), this, SLOT(onDspChangedPDSetting     (quint64, DspPDSettingDto  )));
            disconnect(master, SIGNAL(signalEventChangedStatus         (quint64, DspStatusDto    )), this, SLOT(onDspChangedStatus        (quint64, DspStatusDto     )));
            disconnect(master, SIGNAL(signalEventChangedInfo           (quint64, DspInfoDto      )), this, SLOT(onDspChangedInfo          (quint64, DspInfoDto       )));
            disconnect(master, SIGNAL(signalEventAddedEvent            (quint64, DspEventDto     )), this, SLOT(onDspAddedEvent           (quint64, DspEventDto      )));
            disconnect(master, SIGNAL(signalEventChangedRefVoltage     (quint64, qint32          )), this, SLOT(onDspChangedRefVoltage    (quint64, qint32           )));

            delete master;
        }

        mDspList.clear();
    }

    quint64 readFileLastSeq()
    {
        return FileReaderEx::readAll(FileDef::DSP_CONNINFO_SEQ_DIR(), FileDef::DSP_CONNINFO_SEQ_FILENAME()).toULongLong();
    }

    void writeFileLastSeq(quint64 seq)
    {
        FileWriterEx::newWrite(FileDef::DSP_CONNINFO_SEQ_DIR(), FileDef::DSP_CONNINFO_SEQ_FILENAME(), QString("%1").arg(seq));
    }

    bool writeFileDspConnInfo(DspConnInfoDto dto)
    {
        return FileWriterEx::newWrite(FileDef::DSP_CONNINFO_DIR(), QString("%1.txt").arg(dto.mDspSeq), dto.toString());
    }

};

#endif // DSPSPROVIDER_H
