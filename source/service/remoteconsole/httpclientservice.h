#ifndef HTTPCLIENTSERVICE_H
#define HTTPCLIENTSERVICE_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "source/service/productsetting/productsprovider.h"
#include "source/service/localsetting/localsettingsprovider.h"
#include "source/service/work/worksprovider.h"

#define pHttpClientSvc HttpClientService::getInstance()

class HttpClientWorker : public QObject
{
    Q_OBJECT
private:
    QTimer * mpTimer = nullptr;
    QNetworkAccessManager *mNetManager = nullptr;
    QNetworkReply* mReply = nullptr;
    int mPostTryCnt = 0;

public slots:
    void onStarted()
    {
        //ENABLE_SLOT_DSP_CHANGED_DSP_STATUS;
        //ENABLE_SLOT_WORK_CHANGED_STATS;
        //ENABLE_SLOT_PDSETTING_CHANGED_CURR_PD;

        mpTimer = new QTimer(this);
        mpTimer->setInterval(1000);
        connect(mpTimer, SIGNAL(timeout()), this, SLOT(onTimeTick()));

        mpTimer->start();

        mNetManager = new QNetworkAccessManager(this);
    }

    void onChangedDspStatus(quint64 dspSeq, DspStatusDto status)
    {

    }

    void onChangedPDStats(PDStatsDto stats)
    {

    }

    void onChangedCurrPDSetting(PDSettingDto setting)
    {

    }

    void onTimeTick()
    {
        QUrl url = QUrl(pDefaultSP->CCP_SERVER_URL);//"http://121.175.173.236:17071/DevDataCollect/WriteRealTimeData");
        QString devType = "Combi";
        QString devStats = "{}";

        qDebug() << "[HttpClientWorker]";

        switch(pLSettingSP->mDevSetting.mDspForm.mCommSetting.mMachineMode)
        {
        case 1:
            devType = "Metal Detector";
            devStats = QString("{\"totalCnt\":%1, \"mdNGCnt\":%2}").arg(pWorkSP->mCurrPD.mMDTotalCnt).arg(pWorkSP->mCurrPD.mMDFailCnt);
            break;

        case 2:
            devType = "Weight Checker";
            devStats = QString("{\"totalCnt\":%1, \"wcOverNGCnt\":%2, \"wcUnderNGCnt\":%3, \"wcEtcNGCnt\":%4}")
                                .arg(pWorkSP->mCurrPD.mWCTotalCnt)
                                .arg(pWorkSP->mCurrPD.mWCOCnt)
                                .arg(pWorkSP->mCurrPD.mWCUCnt)
                                .arg(pWorkSP->mCurrPD.mWCEtcCnt);
            break;

        default:
            devStats = QString("{\"totalCnt\":%1, \"mdNGCnt\":%2, \"wcOverNGCnt\":%3, \"wcUnderNGCnt\":%4, \"wcEtcNGCnt\":%5}")
                                .arg(pWorkSP->mCurrPD.mWCTotalCnt)
                                .arg(pWorkSP->mCurrPD.mMDFailCnt)
                                .arg(pWorkSP->mCurrPD.mWCOCnt)
                                .arg(pWorkSP->mCurrPD.mWCUCnt)
                                .arg(pWorkSP->mCurrPD.mWCEtcCnt);
            break;
        }

        QVariantMap feed;
        feed.insert("DevNum",pLSettingSP->mInformation.mDeviceNumber);
        feed.insert("DevType",devType);
        feed.insert("Stats",devStats);
        QByteArray payload=QJsonDocument::fromVariant(feed).toJson();

        /*
        QJsonObject param;
        param.insert("DevNum", pLSettingSP->mInformation.mDeviceNumber);
        param.insert("DevType", devType);
        param.insert("Stats", devStats);
        */
        QNetworkRequest request(url);

        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");//"application/x-www-form-urlencoded");

        if(mReply != nullptr)
        {
            if(mReply->isFinished())
            {
                qDebug() << "[HttpClientWorker]" << mReply->error();
                mReply->deleteLater();
                mReply = nullptr;
                mPostTryCnt = 0;
            }
            else
            {
                mPostTryCnt ++;

                if(mPostTryCnt > 10)
                {
                    mReply->abort();
                    mReply->deleteLater();
                    mReply = nullptr;
                    mPostTryCnt = 0;
                }
                else
                    return;
            }
        }

        mReply = mNetManager->post(request, payload/*QJsonDocument(param).toJson(QJsonDocument::Compact)*/);

        //if(reply->error() == QNetworkReply::NoError)
        //reply->abort();
        //reply->deleteLater();
    }

public:
    explicit HttpClientWorker(QObject * parent = nullptr):QObject(parent)
    {
    }
    ~HttpClientWorker()
    {
        if(mpTimer != nullptr)
        {
            mpTimer->stop();
            delete mpTimer;
        }

        if(mReply != nullptr)
        {
            if(mReply->isFinished())
            {
                mReply->abort();
            }

            mReply->deleteLater();
            mReply = nullptr;
            mPostTryCnt = 0;
        }

        if(mNetManager != nullptr)
        {
            delete mNetManager;
            mNetManager = nullptr;
        }
    }
};

class HttpClientService : public QObject
{
    Q_OBJECT

private:
    QThread * mpThread = nullptr;
    HttpClientWorker * mpWorker = nullptr;

public:
    static HttpClientService * getInstance()
    {
        static HttpClientService *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new HttpClientService();
        }

        return mpSelf;
    }


public:
    explicit HttpClientService(QObject *parent = nullptr)
    {

    }
    ~HttpClientService()
    {

    }

    void start()
    {
        mpThread = new QThread;
        mpWorker = new HttpClientWorker;
        mpWorker->moveToThread(mpThread);

        connect(mpThread, &QThread::finished, mpWorker, &QObject::deleteLater);
        connect(mpThread, &QThread::started , mpWorker, &HttpClientWorker::onStarted);

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
private:

};
#endif // HTTPCLIENTSERVICE_H
