#ifndef CORESERVICE_H
#define CORESERVICE_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QDateTime>


#include "source/service/dsp/dspsprovider.h"
#include "source/service/localsetting/localsettingsprovider.h"
#include "source/service/productsetting/productsprovider.h"
#include "source/service/work/worksprovider.h"
#include "source/service/timer/timersprovider.h"
#include "source/service/defaultsetting/defaultsettingsprovider.h"
#include "source/service/util/sproviderconnectutil.h"
#include "source/service/remoteconsole/deviceinfobrodcaster.h"
#include "source/service/remoteconsole/monitoringservice.h"
#include "source/service/remoteconsole/syncserverservice.h"
#include "source/service/remoteconsole/tcpmodbusslave.h"
#include "source/service/remoteconsole/rtumodbusslave.h"
#include "source/service/remoteconsole/httpclientservice.h"
#include "source/service/vnc/vncsprovider.h"
#include "source/service/printer/printersprovider.h"

#define pCoreService CoreService::getInstance()

class CoreService : public QObject
{
    Q_OBJECT
public:
    static CoreService * getInstance()
    {
        static CoreService *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new CoreService();
        }

        return mpSelf;
    }

public:
    bool                        mIsRunning = false;

    void start(QObject * context)
    {
        ENABLE_SLOT_WORK_START;
        ENABLE_SLOT_LSETTING_START;

        pDefaultSP->start();
        pLSettingSP->start(context);
    }
    void stop()
    {
        pPrinterSP->stop();
        pHttpClientSvc->stop();
        pVncSP->stop();
        pDevInfoBC->stop();
        pSyncgSvr->stop();
        pMonitoringSvr->stop();
        pTcpModbusSlave->stop();
        pRtuModbusSlave->stop();

        pDspSP->stop();
        pWorkSP->stop();
        pProductSP->stop();
        pLSettingSP->stop();

        mIsRunning = false;
    }

signals:
    void signalEventStarted();
    void signalEventStopped();

public slots:
    void onStartedLocalSettingSProvider()
    {
        pProductSP->start();
        pDspSP->start(pLSettingSP->mDevSetting.mDspForm, pProductSP->mCurrPD.mDspForm);
        pWorkSP->asyncStart(QDateTime::currentDateTime().date(), pLSettingSP->mHMISetting.mIsDayMode, pProductSP->mPDList);
    }
    void onStartedWorkSProvider()
    {
        mIsRunning = true;
        pEventHisSP->start(QDateTime::currentDateTime());
        pTimerSP->start();

        pDevInfoBC->start();
        pSyncgSvr->start();
        pMonitoringSvr->start();
        pTcpModbusSlave->start();
        pRtuModbusSlave->start();
        pVncSP->start();

        if(pDefaultSP->CCP_SERVER_IS_USE)
            pHttpClientSvc->start();

        if(pDefaultSP->PRINTER_IS_USE)
        {
            pPrinterSP->setIncludeBlankLine(pDefaultSP->PRINTER_INCLUDE_BLANK_LINE);
            pPrinterSP->setIncludeDivider(pDefaultSP->PRINTER_INCLUDE_DIVIDER);
            pPrinterSP->start();
        }

        emit signalEventStarted();
    }

public:
    explicit CoreService(QObject *parent = nullptr):QObject(parent)
    {
    }
    ~CoreService()
    {
        stop();
    }

};

#endif // CORESERVICE_H
