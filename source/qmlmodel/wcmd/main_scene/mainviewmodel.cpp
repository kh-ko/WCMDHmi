#include "mainviewmodel.h"
#include "source/helper/localsetting.h"

MainViewModel::MainViewModel(QObject *parent) : QObject(parent)
{
    ProductSetting tempPs;
    DeviceSetting  tempDs;
    DeviceStatus   tempDStatus;
    EventInfo      tempEi;

    bool isDetail   = LocalSetting::getInstance()->getMainViewIsDetail();
    int  wcViewMode = LocalSetting::getInstance()->getWCViewMode();

    setIsDetail(isDetail);
    setWCViewMode(wcViewMode);
    onSignalEventChangedSelectedProductSetting(tempPs);
    onSignalEventChangedDeviceSetting(tempDs);
    onSignalEventChangedDeviceStatus(0, tempDStatus);
    onSignalEventAddedEvent(0, tempEi);

    connect(this, SIGNAL(signalCommandSaveDeviceSetting(void *, DeviceSetting)), WCMDService::getInstance(), SLOT(onCommandSaveDeviceSetting(void *, DeviceSetting)  ));
    connect(this, SIGNAL(signalCommandSetZero          (quint16              )), WCMDService::getInstance(), SLOT(onCommandSetZero          (quint16              )  ));

    connect(WCMDService::getInstance(), SIGNAL(signalEventChangedProductSetting               (int, ProductSetting)     ), this, SLOT(onSignalEventChangedProductSetting        (int, ProductSetting)  ));
    connect(WCMDService::getInstance(), SIGNAL(signalEventChangedSelectedProductSetting       (ProductSetting)          ), this, SLOT(onSignalEventChangedSelectedProductSetting(ProductSetting)       ));
    connect(WCMDService::getInstance(), SIGNAL(signalEventChangedDeviceSetting                (DeviceSetting)           ), this, SLOT(onSignalEventChangedDeviceSetting         (DeviceSetting)        ));
    connect(WCMDService::getInstance(), SIGNAL(signalEventChangedDeviceStatus                 (quint16, DeviceStatus)   ), this, SLOT(onSignalEventChangedDeviceStatus          (quint16, DeviceStatus)));
    connect(WCMDService::getInstance(), SIGNAL(signalEventAddedEvent                          (quint16, EventInfo)      ), this, SLOT(onSignalEventAddedEvent                   (quint16, EventInfo)   ));
}

void MainViewModel::onCommandSetIsDetail(bool value)
{
    setIsDetail(value);
    LocalSetting::getInstance()->setMainViewIsDetail(value);
}

void  MainViewModel::onCommandSetWCViewMode         (int  value)
{
    setWCViewMode(value);
    LocalSetting::getInstance()->setWCViewMode(value);
}

int  MainViewModel::onCommandGetSnopShotPointsCnt   ()
{
    return mPointCnt;
}

void MainViewModel::onCommandCreateSnopShot        (int width, int height)
{
    quint32         min = 0;
    quint32         max = 0;
    int             uigLastIdx = -1;
    int             uigIdx = 0;
    int             graphPointsCnt;
    quint32 *       graphPoints;
    quint16         productSeq     = WCMDService::getInstance()->mProductSetting.mSeq;
    DSPManager *    dspManager = WCMDService::getInstance()->mMapDSPManager.first();
    ProductStatus * productStatus;

    mUiGraphH = height;

    if(dspManager->mListProductStatus.contains(productSeq) == false)
        return;

    productStatus = dspManager->mListProductStatus[productSeq];

    if(mWCTrendsOptionFilter == EnumDefine::TrendsGraphOptionFilter::TRENDSOPTION_FILTER_TRADE)
    {
        graphPointsCnt = productStatus->mWCTradeCnt;
        graphPoints = productStatus->mWCTrendsFilterGraph;
    }
    else
    {
        graphPointsCnt = productStatus->mWCTotalCnt;
        graphPoints = productStatus->mWCTrendsGraph;
    }

    if(mWCTrendsOptionLastN == EnumDefine::TrendsGraphOptionLastN::TRENDSOPTION_LAST_N)
    {
        if(graphPointsCnt - mWCTrendsLastNValue > 0 )
        {
            graphPoints = &graphPoints[graphPointsCnt - mWCTrendsLastNValue];
            graphPointsCnt = mWCTrendsLastNValue;
        }
    }

    min = mWCUnderWeight - ( (mWCOverWeight - mWCUnderWeight) * 0.2 ) ;
    max = mWCOverWeight + ( (mWCOverWeight - mWCUnderWeight) * 0.2  ) ;

    for(int gIdx = 0; gIdx < graphPointsCnt; gIdx ++)
    {
        if(graphPointsCnt < width)
            uigIdx = gIdx;
        else
            uigIdx = width * ((float)gIdx / (float)graphPointsCnt);

        if(uigIdx != uigLastIdx || mMinPoints[uigIdx] > graphPoints[gIdx])
        {
            mMinPoints[uigIdx] = graphPoints[gIdx];
        }

        if(uigIdx != uigLastIdx || mMinPoints[uigIdx] < graphPoints[gIdx])
        {
            mMaxPoints[uigIdx] = graphPoints[gIdx];
        }

        if(mWCTrendsOptionH == EnumDefine::TrendsGraphOptionH::TRENDSOPTION_H_MIN_TO_MAX)
        {
            if(min > graphPoints[gIdx])
                min = graphPoints[gIdx];
            if(max < graphPoints[gIdx])
                max = graphPoints[gIdx];
        }
        uigLastIdx = uigIdx;
    }

    mPointCnt = uigLastIdx + 1;

    mMinWeight = min;
    mWeightRange = max - mMinWeight;


}
int  MainViewModel::onCommandConvertWeightToY       (float weight)
{
    return mUiGraphH - (mUiGraphH * ((weight - mMinWeight) / mWeightRange));
}
float  MainViewModel::onCommandConvertPointIdxToX       (int idx, int width)
{
    if(mWCTrendsOptionLastN == EnumDefine::TrendsGraphOptionLastN::TRENDSOPTION_LAST_N && mWCTrendsLastNValue < width)
    {
        return (float)width * ((float)idx/ (float)mWCTrendsLastNValue);
    }

    return idx;
}
int  MainViewModel::onCommandGetMinPointAt          (int idx)
{
    return onCommandConvertWeightToY(mMinPoints[idx]);
}
int  MainViewModel::onCommandGetMaxPointAt          (int idx)
{
    return onCommandConvertWeightToY(mMaxPoints[idx]);
}

int MainViewModel::onCommandSaveTrendsOption       (bool isUnderToOver, bool isTotal, bool TotalSinceStart, int lastNValue)
{
    DeviceSetting ds = WCMDService::getInstance()->mDeviceSetting;

    ds.mTrendsGraphOptionH          = isUnderToOver     ? EnumDefine::TrendsGraphOptionH::TRENDSOPTION_H_UNDER_TO_OVER : EnumDefine::TrendsGraphOptionH::TRENDSOPTION_H_MIN_TO_MAX;
    ds.mTrendsGraphOptionFilter     = isTotal           ? EnumDefine::TrendsGraphOptionFilter::TRENDSOPTION_FILTER_TOTAL : EnumDefine::TrendsGraphOptionFilter::TRENDSOPTION_FILTER_TRADE;
    ds.mTrendsGraphOptionLastN      = TotalSinceStart   ? EnumDefine::TrendsGraphOptionLastN::TRENDSOPTION_TOTAL_SINCE_START : EnumDefine::TrendsGraphOptionLastN::TRENDSOPTION_LAST_N;
    ds.mTrendsGraphOptionLastNValue = lastNValue;

    emit signalCommandSaveDeviceSetting(this, ds);

    return 0;
}

void MainViewModel::onCommandSetZero()
{
    emit signalCommandSetZero(0xffff);
}
void MainViewModel::onSignalEventChangedProductSetting        (int type, ProductSetting value)
{
    quint16 productSeq     = WCMDService::getInstance()->mProductSetting.mSeq;

    if(value.mSeq == productSeq)
    {
        onSignalEventChangedSelectedProductSetting(value);
    }
}
void MainViewModel::onSignalEventChangedSelectedProductSetting(ProductSetting value)
{
    quint16 productSeq     = WCMDService::getInstance()->mProductSetting.mSeq;
    DSPManager * dspManager = WCMDService::getInstance()->mMapDSPManager.first();

    setProductNo           (WCMDService::getInstance()->mProductSetting.mNo                );
    setProductName         (WCMDService::getInstance()->mProductSetting.mName              );
    setMDSenstivity        (WCMDService::getInstance()->mProductSetting.mMDSenstivity      );
    setWCOverWeight        (WCMDService::getInstance()->mProductSetting.mOverWeight        );
    setWCOverWarningWeight (WCMDService::getInstance()->mProductSetting.mOverWarningWeight );
    setWCNormalWeight      (WCMDService::getInstance()->mProductSetting.mNormalWeight      );
    setWCUnderWarningWeight(WCMDService::getInstance()->mProductSetting.mUnderWarningWeight);
    setWCUnderWeight       (WCMDService::getInstance()->mProductSetting.mUnderWeight       );
    setWCTareWeight        (WCMDService::getInstance()->mProductSetting.mTareWeight        );
    //setWCAverageN          (WCMDService::getInstance()->mProductSetting.mAverageN          );

    if(dspManager->mListProductStatus.contains(productSeq) == false)
        return;

    setMDTotalCnt        (dspManager->mListProductStatus[productSeq]->mWCTotalCnt);
    setMDDetectCnt       (dspManager->mListProductStatus[productSeq]->mMDDetectCnt);
    setWCTotalCnt        (dspManager->mListProductStatus[productSeq]->mWCTotalCnt);
    setWCNGCnt           (dspManager->mListProductStatus[productSeq]->mWCTotalCnt - dspManager->mListProductStatus[productSeq]->mWCTradeCnt);
    setWCTradeCnt        (dspManager->mListProductStatus[productSeq]->mWCTradeCnt);
    setWCOverCnt         (dspManager->mListProductStatus[productSeq]->mWCOverCnt);
    setWCOverWarningCnt  (dspManager->mListProductStatus[productSeq]->mWCOverWarningCnt);
    setWCNormalCnt       (dspManager->mListProductStatus[productSeq]->mWCNormalCnt);
    setWCUnderWarningCnt (dspManager->mListProductStatus[productSeq]->mWCUnderWarningCnt);
    setWCUnderCnt        (dspManager->mListProductStatus[productSeq]->mWCUnderCnt);
    setWCEtcErrorCnt     (dspManager->mListProductStatus[productSeq]->mWCEtcErrorCnt);
    setWCTradeTotalWeight(dspManager->mListProductStatus[productSeq]->mWCTradeWeight);
    setWCCurrAvgWeight   (dspManager->mListProductStatus[productSeq]->mWCCurrAvgWeight);
    setWCCurrAvgEventType(dspManager->mListProductStatus[productSeq]->mWCCurrAvgEvent);
}
void MainViewModel::onSignalEventChangedDeviceSetting         (DeviceSetting value)
{
    setWCTrendsLastNValue  (WCMDService::getInstance()->mDeviceSetting.mTrendsGraphOptionLastNValue );
    setWCTrendsOptionH     (WCMDService::getInstance()->mDeviceSetting.mTrendsGraphOptionH          );
    setWCTrendsOptionFilter(WCMDService::getInstance()->mDeviceSetting.mTrendsGraphOptionFilter     );
    setWCTrendsOptionLastN (WCMDService::getInstance()->mDeviceSetting.mTrendsGraphOptionLastN      );
}
void MainViewModel::onSignalEventChangedDeviceStatus          (quint16 deviceSeq, DeviceStatus value)
{
    DSPManager * dspManager = WCMDService::getInstance()->mMapDSPManager.first();

    setWait              (dspManager->mWait             );
    setMDCurrSignal      (dspManager->mMDCurrSignal     );
    setWCCurrWeight      (dspManager->mWCCurrWeight     );
    setWCCurrEventType   (dspManager->mWCCurrEventType  );
}
void MainViewModel::onSignalEventAddedEvent                   (quint16 deviceSeq, EventInfo value)
{
    quint16 productSeq     = WCMDService::getInstance()->mProductSetting.mSeq;
    DSPManager * dspManager = WCMDService::getInstance()->mMapDSPManager.first();

    setLastErrorType (WCMDService::getInstance()->mLastError);
    setLastErrorTime (WCMDService::getInstance()->mLastErrorTime);
    setLastErrorValue(WCMDService::getInstance()->mLastErrorValue);

    setWCCurrWeight      (dspManager->mWCCurrWeight     );
    setWCCurrEventType   (dspManager->mWCCurrEventType  );

    if(dspManager->mListProductStatus.contains(productSeq) == false)
        return;

    setMDTotalCnt        (dspManager->mListProductStatus[productSeq]->mWCTotalCnt);
    setMDDetectCnt       (dspManager->mListProductStatus[productSeq]->mMDDetectCnt);
    setWCTotalCnt        (dspManager->mListProductStatus[productSeq]->mWCTotalCnt);
    setWCNGCnt           (dspManager->mListProductStatus[productSeq]->mWCTotalCnt - dspManager->mListProductStatus[productSeq]->mWCTradeCnt);
    setWCTradeCnt        (dspManager->mListProductStatus[productSeq]->mWCTradeCnt);
    setWCOverCnt         (dspManager->mListProductStatus[productSeq]->mWCOverCnt);
    setWCOverWarningCnt  (dspManager->mListProductStatus[productSeq]->mWCOverWarningCnt);
    setWCNormalCnt       (dspManager->mListProductStatus[productSeq]->mWCNormalCnt);
    setWCUnderWarningCnt (dspManager->mListProductStatus[productSeq]->mWCUnderWarningCnt);
    setWCUnderCnt        (dspManager->mListProductStatus[productSeq]->mWCUnderCnt);
    setWCEtcErrorCnt     (dspManager->mListProductStatus[productSeq]->mWCEtcErrorCnt);
    setWCTradeTotalWeight(dspManager->mListProductStatus[productSeq]->mWCTradeWeight);
    setWCCurrAvgWeight   (dspManager->mListProductStatus[productSeq]->mWCCurrAvgWeight);
    setWCCurrAvgEventType(dspManager->mListProductStatus[productSeq]->mWCCurrAvgEvent);

    if(value.mEventType == EnumDefine::EventType::WEIGHT_UNDER_TYPE || value.mEventType == EnumDefine::EventType::WEIGHT_OVER_TYPE)
    {
        emit signalEventNotifyWCNG(value.mEventValue, value.mEventType);
    }

    if(value.mEventType == EnumDefine::EventType::METAL_DETECT_TYPE)
    {
        emit signalEventNotifyMDDetect();
    }

}
