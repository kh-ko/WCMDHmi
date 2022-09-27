#ifndef PRINTERSPROVIDER_H
#define PRINTERSPROVIDER_H

#include <QObject>
#include <QUrl>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

#include "source/service/def/datetimeform.h"
#include "source/service/timer/timersprovider.h"
#include "source/service/productsetting/productsprovider.h"
#include "source/service/dsp/dspsprovider.h"
#include "source/service/work/worksprovider.h"
#include "source/service/util/sproviderconnectutil.h"

#include "source/service/remoteconsole/dto/modbusdatastore.h"

#define pPrinterSP PrinterSProvider::getInstance()

class PrinterWorker : public QObject
{
    Q_OBJECT

private:
    QSerialPort * mpComport = nullptr;

    bool mIsConnected = false;

public:
    bool getIsConnected(){ return mIsConnected;}

    void setIsConnected(bool value){ if(mIsConnected == value)return; mIsConnected = value; emit signalEventChangedIsConnected(value);}

    explicit PrinterWorker(QObject *parent = nullptr) : QObject(parent)
    {

    }
    ~PrinterWorker()
    {
        close();
    }

signals:
    void signalEventChangedIsConnected(bool value);

public slots:
    void onStarted()
    {
        open();
    }

    void onPrintConnect()
    {
        if(mpComport != nullptr)
            return;

        open();
    }

    void onPrintData(QString msg)
    {
        if(getIsConnected() == false)
            open();

        char headerData[]  = {0x1B, 0x40, 0x1B, 0x3D, 0x01, 0x1B, 0x52, 0x0D, 0x1B, 0x74,
                              0x10, 0x1B, 0x4D, 0x00, 0x1D, 0x21, 0x00};
        char metalData[]   = {0x1B, 0x45, 0x01, 0xB1, 0xDD, 0xBC, 0xD3, 0x1B, 0x45, 0x00,
                              0x0A};
        char newLineData[] = {0x20, 0x0A, 0x20, 0x0A, 0x20, 0x0A, 0x20, 0x0A, 0x20, 0x0A,
                              0x20, 0x0A};
        char dividerData[] = {0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D,
                              0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D,
                              0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D,
                              0x2D, 0x2D};
        char tailData[]    = {0x0A, 0x1B, 0x64, 0x00};

        QByteArray packet;

        packet.append(headerData,17);
        packet.append(msg.toUtf8());
        packet.append(metalData,11);
        packet.append(newLineData,12);
        packet.append(dividerData,32);
        packet.append(tailData,4);

        if(mpComport == nullptr)
            return;

        mpComport->clearError();

        qint64 bytesWritten = mpComport->write(packet);

        if (bytesWritten == -1 || bytesWritten != packet.size() || mpComport->waitForBytesWritten(1000) == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]write error(1) : " << mpComport->errorString() << ":" << msg;
            close();
            return;
        }

        if(mpComport->error() != QSerialPort::NoError)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]write error(2) : " << mpComport->errorString() << ":" << msg;
            close();
            return;
        }

        //qDebug() << "[" << Q_FUNC_INFO << "]print : " << packet.toHex();
    }

private:
    void open()
    {
        qDebug() << "[" << Q_FUNC_INFO << "]";
        close();

        mpComport = new QSerialPort(this);

        mpComport->setPortName(pDefaultSP->PRINTER_PORT    );
        mpComport->setBaudRate(pDefaultSP->PRINTER_BAUDRATE);
        mpComport->setDataBits(pDefaultSP->PRINTER_DATABITS);
        mpComport->setStopBits(pDefaultSP->PRINTER_STOPBITS);
        mpComport->setParity  (pDefaultSP->PRINTER_PARITY  );

        if(mpComport->open(QIODevice::ReadWrite) == false)
        {
            close();
            qDebug() << "[" << Q_FUNC_INFO << "] connecting failed";
        }
        else
        {
            qDebug() << "[" << Q_FUNC_INFO << "] connected";
            setIsConnected(true);
        }
    }

    void close()
    {
        if(mpComport != nullptr)
        {
            mpComport->close();
            delete mpComport;
            mpComport = nullptr;
        }

        setIsConnected(false);
    }
};

class PrinterSProvider : public QObject
{
    Q_OBJECT
private:
    QThread * mpThread = nullptr;
    PrinterWorker * mpWorker = nullptr;
    bool mIsConnected = false;

signals:
    // external signals
    void signalEventChangedIsConnected(bool value);

    // internal signals
    void signalPrintData(QString msg);
    void signalPrintConnect();

public:
    bool getIsConnected(){ return mIsConnected;}
    void setIsConnected(bool value){if(mIsConnected == value)return; mIsConnected = value; emit signalEventChangedIsConnected(value);}

    static PrinterSProvider * getInstance()
    {
        static PrinterSProvider *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new PrinterSProvider();
        }

        return mpSelf;
    }

    explicit PrinterSProvider(QObject *parent = nullptr) : QObject(parent)
    {

    }
    ~PrinterSProvider()
    {
        stop();
    }

    void start()
    {
        mpThread = new QThread;
        mpWorker = new PrinterWorker;
        mpWorker->moveToThread(mpThread);

        connect(mpThread, &QThread::finished, mpWorker, &QObject::deleteLater);
        connect(mpThread, &QThread::started , mpWorker, &PrinterWorker::onStarted);
        connect(this, SIGNAL(signalPrintData(QString)), mpWorker, SLOT(onPrintData(QString)));
        connect(this, SIGNAL(signalPrintConnect())    , mpWorker, SLOT(onPrintConnect())    );
        connect(mpWorker, SIGNAL(signalEventChangedIsConnected(bool)) , this, SLOT(onPrinterChangedIsConnected(bool)));

        mpThread->start();

        ENABLE_SLOT_TIMER_TICK;
        ENABLE_SLOT_EVENTHIS_ADDED_EVENT;
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

public slots:
    void onTimeTick(QDateTime dateTime)
    {
//        if(getIsConnected() == false)
//        {
//            emit signalPrintConnect();
//        }
    }

    void onAddedEventHistory(EventDto dto)
    {
        if(EventDto::isMetalDetectEvent(dto.mEType))
        {
            //qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.toString();
            emit signalPrintData(QString("%1 [%2] ").arg(dto.mDateTime.toString(DATE_TIME_PRINT_FMT)).arg(dto.mPDSeq, 3, 10, QChar('0')));
        }
    }

    void onPrinterChangedIsConnected(bool value)
    {
        setIsConnected(value);
    }
};
#endif // PRINTERSPROVIDER_H
