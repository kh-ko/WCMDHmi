#ifndef RTUMODBUSSLAVE_H
#define RTUMODBUSSLAVE_H

#include <QObject>
#include <QUrl>
#include <QModbusRtuSerialSlave>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

#include "source/service/timer/timersprovider.h"
#include "source/service/productsetting/productsprovider.h"
#include "source/service/dsp/dspsprovider.h"
#include "source/service/work/worksprovider.h"
#include "source/service/util/sproviderconnectutil.h"

#include "source/service/remoteconsole/dto/modbusdatastore.h"

#define pRtuModbusSlave RtuModbusSlave::getInstance()

class RtuModbusSlaveWorker : public QObject
{
    Q_OBJECT

public slots:
    void onStarted()
    {
        ENABLE_SLOT_DSP_CHANGED_DSP_STATUS;
        ENABLE_SLOT_WORK_CHANGED_STATS;
        ENABLE_SLOT_PDSETTING_CHANGED_CURR_PD;

        open();
    }

    void onChangedDspStatus(quint64 dspSeq, DspStatusDto status)
    {
        if(mpServer == nullptr)
        {
            return;
        }

        if(status.mCommStatus.mRun != EnumDef::RUN_MODE_STOP)
        {
            mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_WC_RUN_ADDR), quint16(1));
            mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_MD_RUN_ADDR), quint16(1));
        }
        else
        {
            mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_WC_RUN_ADDR), quint16(0));
            mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_MD_RUN_ADDR), quint16(0));
        }

        mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_WC_ALARM_ADDR), status.mWCStatus.mAlarm);
        mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_MD_ALARM_ADDR), status.mMDStatus.mAlarm);
    }

    void onChangedPDStats(PDStatsDto stats)
    {
        if(mpServer == nullptr)
        {
            return;
        }

        quint32 okRef = 0;

        okRef = stats.mWCNorCnt + stats.mWCUWCnt + stats.mWCOWCnt;

        mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_WC_OK_QTY_ADDR_L), quint16(LOW_WORD(okRef)));
        mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_WC_OK_QTY_ADDR_H), quint16(HIGH_WORD(okRef)));

        mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_WC_HNG_QTY_ADDR_L), quint16(LOW_WORD(stats.mWCOCnt)));
        mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_WC_HNG_QTY_ADDR_H), quint16(HIGH_WORD(stats.mWCOCnt)));

        mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_WC_LNG_QTY_ADDR_L), quint16(LOW_WORD(stats.mWCUCnt)));
        mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_WC_LNG_QTY_ADDR_H), quint16(HIGH_WORD(stats.mWCUCnt)));

        mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_MD_OK_QTY_ADDR_L), quint16(LOW_WORD(stats.mMDPassCnt)));
        mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_MD_OK_QTY_ADDR_H), quint16(HIGH_WORD(stats.mMDPassCnt)));

        mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_MD_NG_QTY_ADDR_L), quint16(LOW_WORD(stats.mMDFailCnt)));
        mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_MD_NG_QTY_ADDR_H), quint16(HIGH_WORD(stats.mMDFailCnt)));
    }

    void onChangedCurrPDSetting(PDSettingDto setting)
    {
        if(mpServer == nullptr)
        {
            return;
        }

        mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_WC_NUM_ADDR), setting.mDspForm.mCommSetting.mProductNum);

        mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_WC_OK_REF_ADDR_L), quint16(LOW_WORD(setting.mDspForm.mWCSetting.mNormalWeight)));
        mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_WC_OK_REF_ADDR_H), quint16(HIGH_WORD(setting.mDspForm.mWCSetting.mNormalWeight)));

        mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_WC_HNG_REF_ADDR_L), quint16(LOW_WORD(setting.mDspForm.mWCSetting.mOverWeight)));
        mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_WC_HNG_REF_ADDR_H), quint16(HIGH_WORD(setting.mDspForm.mWCSetting.mOverWeight)));

        mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_WC_LNG_REF_ADDR_L), quint16(LOW_WORD(setting.mDspForm.mWCSetting.mUnderWeight)));
        mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_WC_LNG_REF_ADDR_H), quint16(HIGH_WORD(setting.mDspForm.mWCSetting.mUnderWeight)));

        mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_MD_NUM_ADDR), setting.mDspForm.mCommSetting.mProductNum);

        mpServer->setData(QModbusDataUnit::InputRegisters, quint16(RMODBUS_MD_NG_REF_ADDR), setting.mDspForm.mMDSetting.mSenstivity);
    }

    void onStateChanged(QModbusDevice::State state)
    {
        qDebug() << "[RtuModbusSlave::onStateChanged]" << state;
    }

    void onModbusError(QModbusDevice::Error error)
    {
        qDebug() << "[RtuModbusSlave::onModbusError] error : " << error << ", " <<mpServer->errorString();

        close();
    }
private:
    QModbusRtuSerialSlave * mpServer = nullptr;
    qint16                  PORT     = 10502;  // 502 번을 redirect로 10502번으로 연결하였음

    void open()
    {
        close();

        mpServer = new QModbusRtuSerialSlave(this);

        QModbusDataUnitMap reg;
        reg.insert(QModbusDataUnit::InputRegisters,   { QModbusDataUnit::InputRegisters, 4096, 270});

        mpServer->setMap(reg);


        qDebug() << "[debug] rtu modbus start";

        mpServer->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "/dev/ttyAMA0");
        mpServer->setConnectionParameter(QModbusDevice::SerialParityParameter  , QSerialPort::NoParity);
        mpServer->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud57600);
        mpServer->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
        mpServer->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
        mpServer->setServerAddress(1);

        connect(mpServer, SIGNAL(stateChanged(QModbusDevice::State)) , this, SLOT(onStateChanged(QModbusDevice::State)));
        connect(mpServer, SIGNAL(errorOccurred(QModbusDevice::Error)), this, SLOT(onModbusError(QModbusDevice::Error)));

        // 초기 데이타 설정
        foreach(DspMaster * master, pDspSP->mDspList)
        {
            onChangedDspStatus(master->mSeq, master->mRcvDataStore.getStatusDto());
        }
        onChangedPDStats(pWorkSP->mCurrPD);
        onChangedCurrPDSetting(pProductSP->mCurrPD);

        if(mpServer->connectDevice() == false)
        {
            qDebug() << "[RtuModbusSlave::open]connectDevice fail";
            close();
        }
    }

    void close()
    {
        if(mpServer != nullptr)
        {
            disconnect(mpServer, SIGNAL(stateChanged(QModbusDevice::State)) , this, SLOT(onStateChanged(QModbusDevice::State)));
            disconnect(mpServer, SIGNAL(errorOccurred(QModbusDevice::Error)), this, SLOT(onModbusError(QModbusDevice::Error)));

            mpServer->disconnectDevice();
            mpServer->deleteLater();
            mpServer = nullptr;
        }
    }
};

class RtuModbusSlave : public QObject
{
    Q_OBJECT
private:
    QThread * mpThread = nullptr;
    RtuModbusSlaveWorker * mpWorker = nullptr;

public:
    static RtuModbusSlave * getInstance()
    {
        static RtuModbusSlave *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new RtuModbusSlave();
        }

        return mpSelf;
    }

    explicit RtuModbusSlave(QObject *parent = nullptr) : QObject(parent)
    {

    }
    ~RtuModbusSlave()
    {
        stop();
    }

    void start()
    {
        mpThread = new QThread;
        mpWorker = new RtuModbusSlaveWorker;
        mpWorker->moveToThread(mpThread);

        connect(mpThread, &QThread::finished, mpWorker, &QObject::deleteLater);
        connect(mpThread, &QThread::started , mpWorker, &RtuModbusSlaveWorker::onStarted);

        mpThread->start();
    }

    void stop()
    {
        mpWorker= nullptr;

        if(mpThread != nullptr)
        {
            if(mpThread->isRunning())
            {
                mpThread->quit();
                mpThread->wait();
            }

            mpThread->deleteLater();
            mpThread = nullptr;
        }
    }
};

#endif // RTUMODBUSSLAVE_H
