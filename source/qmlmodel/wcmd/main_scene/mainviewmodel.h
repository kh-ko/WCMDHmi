#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include <QObject>

#include "source/globaldef/GlobalDefine.h"
#include "source/service/wcmdservice.h"
class MainViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    isDetail               READ getIsDetail                NOTIFY signalEventChangedIsDetail            )
    Q_PROPERTY(int     wcViewMode             READ getWCViewMode              NOTIFY signalEventChangedWCViewMode          )

    Q_PROPERTY(quint16 wait                   READ getWait                    NOTIFY signalEventChangedWait                )

    Q_PROPERTY(quint16 productNo              READ getProductNo               NOTIFY signalEventChangedProductNo           )
    Q_PROPERTY(QString productName            READ getProductName             NOTIFY signalEventChangedProductName         )
    Q_PROPERTY(quint16 mdSenstivity           READ getMDSenstivity            NOTIFY signalEventChangedMDSenstivity        )
    Q_PROPERTY(quint32 wcOverWeight           READ getWCOverWeight            NOTIFY signalEventChangedWCOverWeight        )
    Q_PROPERTY(quint32 wcOverWarningWeight    READ getWCOverWarningWeight     NOTIFY signalEventChangedWCOverWarningWeight )
    Q_PROPERTY(quint32 wcNormalWeight         READ getWCNormalWeight          NOTIFY signalEventChangedWCNormalWeight      )
    Q_PROPERTY(quint32 wcUnderWarningWeight   READ getWCUnderWarningWeight    NOTIFY signalEventChangedWCUnderWarningWeight)
    Q_PROPERTY(quint32 wcUnderWeight          READ getWCUnderWeight           NOTIFY signalEventChangedWCUnderWeight       )
    Q_PROPERTY(quint64 wcTradeTotalWeight     READ getWCTradeTotalWeight      NOTIFY signalEventChangedWCTradeTotalWeight  )
    Q_PROPERTY(quint32 wcTareWeight           READ getWCTareWeight            NOTIFY signalEventChangedWCTareWeight        )
    Q_PROPERTY(quint16 wcAverageN             READ getWCAverageN              NOTIFY signalEventChangedWCAverageN          )

    Q_PROPERTY(int     wcTrendsLastNValue     READ getWCTrendsLastNValue      NOTIFY signalEventChangedWCTrendsLastNValue  )
    Q_PROPERTY(int     wcTrendsOptionH        READ getWCTrendsOptionH         NOTIFY signalEventChangedWCTrendsOptionH     )
    Q_PROPERTY(int     wcTrendsOptionFilter   READ getWCTrendsOptionFilter    NOTIFY signalEventChangedWCTrendsOptionFilter)
    Q_PROPERTY(int     wcTrendsOptionLastN    READ getWCTrendsOptionLastN     NOTIFY signalEventChangedWCTrendsOptionLastN )

    Q_PROPERTY(quint16 lastErrorType          READ getLastErrorType           NOTIFY signalEventChangedLastErrorType       )
    Q_PROPERTY(QString lastErrorTime          READ getLastErrorTime           NOTIFY signalEventChangedLastErrorTime       )
    Q_PROPERTY(quint32 lastErrorValue         READ getLastErrorValue          NOTIFY signalEventChangedLastErrorValue      )

    Q_PROPERTY(quint32 mdTotalCnt             READ getMDTotalCnt              NOTIFY signalEventChangedMDTotalCnt          )
    Q_PROPERTY(quint32 mdDetectCnt            READ getMDDetectCnt             NOTIFY signalEventChangedMDDetectCnt         )

    Q_PROPERTY(quint16 mdCurrSignal           READ getMDCurrSignal            NOTIFY signalEventChangedMDCurrSignal        )
    Q_PROPERTY(quint32 wcCurrWeight           READ getWCCurrWeight            NOTIFY signalEventChangedWCCurrWeight        )
    Q_PROPERTY(quint16 wcCurrEventType        READ getWCCurrEventType         NOTIFY signalEventChangedWCCurrEventType     )
    Q_PROPERTY(quint32 wcCurrAvgWeight        READ getWCCurrAvgWeight         NOTIFY signalEventChangedWCCurrAvgWeight     )
    Q_PROPERTY(quint16 wcCurrAvgEventType     READ getWCCurrAvgEventType      NOTIFY signalEventChangedWCCurrAvgEventType  )


    Q_PROPERTY(int     wcTotalCnt             READ getWCTotalCnt              NOTIFY signalEventChangedWCTotalCnt          )
    Q_PROPERTY(int     wcNGCnt                READ getWCNGCnt                 NOTIFY signalEventChangedWCNGCnt             )
    Q_PROPERTY(int     wcTradeCnt             READ getWCTradeCnt              NOTIFY signalEventChangedWCTradeCnt          )
    Q_PROPERTY(int     wcOverCnt              READ getWCOverCnt               NOTIFY signalEventChangedWCOverCnt           )
    Q_PROPERTY(int     wcOverWarningCnt       READ getWCOverWarningCnt        NOTIFY signalEventChangedWCOverWarningCnt    )
    Q_PROPERTY(int     wcNormalCnt            READ getWCNormalCnt             NOTIFY signalEventChangedWCNormalCnt         )
    Q_PROPERTY(int     wcUnderWarningCnt      READ getWCUnderWarningCnt       NOTIFY signalEventChangedWCUnderWarningCnt   )
    Q_PROPERTY(int     wcUnderCnt             READ getWCUnderCnt              NOTIFY signalEventChangedWCUnderCnt          )
    Q_PROPERTY(int     wcEtcErrorCnt          READ getWCEtcErrorCnt           NOTIFY signalEventChangedWCEtcErrorCnt       )


public:
    bool    mIsDetail;
    int     mWCViewMode;

    quint32 mMinPoints[TRENDS_POINT_BUFF_CNT];
    quint32 mMaxPoints[TRENDS_POINT_BUFF_CNT];
    quint32 mMinWeight;
    quint32 mWeightRange;
    int     mPointCnt;
    int     mUiGraphH;

    quint16 mWait                ;

    quint16 mProductNo           ;
    QString mProductName         ;
    quint16 mMDSenstivity        ;
    quint32 mWCOverWeight        ;
    quint32 mWCOverWarningWeight ;
    quint32 mWCNormalWeight      ;
    quint32 mWCUnderWarningWeight;
    quint32 mWCUnderWeight       ;
    quint32 mWCTareWeight        ;
    quint16 mWCAverageN          ;

    int     mWCTrendsLastNValue  ;
    int     mWCTrendsOptionH     ;
    int     mWCTrendsOptionFilter;
    int     mWCTrendsOptionLastN ;

    quint16 mLastErrorType       ;
    QString mLastErrorTime       ;
    quint32 mLastErrorValue      ;

    quint32 mMDTotalCnt          ;
    quint32 mMDDetectCnt         ;
    int     mWCTotalCnt          ;
    int     mWCNGCnt             ;
    int     mWCTradeCnt          ;
    int     mWCOverCnt           ;
    int     mWCOverWarningCnt    ;
    int     mWCNormalCnt         ;
    int     mWCUnderWarningCnt   ;
    int     mWCUnderCnt          ;
    int     mWCEtcErrorCnt       ;
    quint64 mWCTradeTotalWeight  ;

    quint16 mMDCurrSignal        ;
    quint32 mWCCurrWeight        ;
    quint16 mWCCurrEventType     ;
    quint32 mWCCurrAvgWeight     ;
    quint16 mWCCurrAvgEventType  ;

    bool    getIsDetail            (){ return mIsDetail            ;}
    int     getWCViewMode          (){ return mWCViewMode          ;}
    quint16 getWait                (){ return mWait                ;}
    quint16 getProductNo           (){ return mProductNo           ;}
    QString getProductName         (){ return mProductName         ;}
    quint16 getLastErrorType       (){ return mLastErrorType       ;}
    QString getLastErrorTime       (){ return mLastErrorTime       ;}
    quint32 getLastErrorValue      (){ return mLastErrorValue      ;}
    quint32 getMDTotalCnt          (){ return mMDTotalCnt          ;}
    quint32 getMDDetectCnt         (){ return mMDDetectCnt         ;}
    quint16 getMDSenstivity        (){ return mMDSenstivity        ;}
    quint16 getMDCurrSignal        (){ return mMDCurrSignal        ;}
    quint32 getWCCurrWeight        (){ return mWCCurrWeight        ;}
    quint16 getWCCurrEventType     (){ return mWCCurrEventType     ;}
    quint32 getWCCurrAvgWeight     (){ return mWCCurrAvgWeight     ;}
    quint16 getWCCurrAvgEventType  (){ return mWCCurrAvgEventType  ;}
    quint16 getWCAverageN          (){ return mWCAverageN          ;}
    int     getWCTrendsLastNValue  (){ return mWCTrendsLastNValue  ;}
    int     getWCTrendsOptionH     (){ return mWCTrendsOptionH     ;}
    int     getWCTrendsOptionFilter(){ return mWCTrendsOptionFilter;}
    int     getWCTrendsOptionLastN (){ return mWCTrendsOptionLastN ;}
    int     getWCTotalCnt          (){ return mWCTotalCnt          ;}
    int     getWCNGCnt             (){ return mWCNGCnt             ;}
    int     getWCTradeCnt          (){ return mWCTradeCnt          ;}
    int     getWCOverCnt           (){ return mWCOverCnt           ;}
    int     getWCOverWarningCnt    (){ return mWCOverWarningCnt    ;}
    int     getWCNormalCnt         (){ return mWCNormalCnt         ;}
    int     getWCUnderWarningCnt   (){ return mWCUnderWarningCnt   ;}
    int     getWCUnderCnt          (){ return mWCUnderCnt          ;}
    int     getWCEtcErrorCnt       (){ return mWCEtcErrorCnt       ;}
    quint32 getWCOverWeight        (){ return mWCOverWeight        ;}
    quint32 getWCOverWarningWeight (){ return mWCOverWarningWeight ;}
    quint32 getWCNormalWeight      (){ return mWCNormalWeight      ;}
    quint32 getWCUnderWarningWeight(){ return mWCUnderWarningWeight;}
    quint32 getWCUnderWeight       (){ return mWCUnderWeight       ;}
    quint64 getWCTradeTotalWeight  (){ return mWCTradeTotalWeight  ;}
    quint32 getWCTareWeight        (){ return mWCTareWeight        ;}

    void setIsDetail            (bool    value){ if(mIsDetail             == value)return; mIsDetail             = value; emit signalEventChangedIsDetail            (value);}
    void setWCViewMode          (int     value){ if(mWCViewMode           == value)return; mWCViewMode           = value; emit signalEventChangedWCViewMode          (value);}
    void setWait                (quint16 value){ if(mWait                 == value)return; mWait                 = value; emit signalEventChangedWait                (value);}
    void setProductNo           (quint16 value){ if(mProductNo            == value)return; mProductNo            = value; emit signalEventChangedProductNo           (value);}
    void setProductName         (QString value){ if(mProductName          == value)return; mProductName          = value; emit signalEventChangedProductName         (value);}
    void setLastErrorType       (quint16 value){ if(mLastErrorType        == value)return; mLastErrorType        = value; emit signalEventChangedLastErrorType       (value);}
    void setLastErrorTime       (QString value){ if(mLastErrorTime        == value)return; mLastErrorTime        = value; emit signalEventChangedLastErrorTime       (value);}
    void setLastErrorValue      (quint32 value){ if(mLastErrorValue       == value)return; mLastErrorValue       = value; emit signalEventChangedLastErrorValue      (value);}
    void setMDTotalCnt          (quint32 value){ if(mMDTotalCnt           == value)return; mMDTotalCnt           = value; emit signalEventChangedMDTotalCnt          (value);}
    void setMDDetectCnt         (quint32 value){ if(mMDDetectCnt          == value)return; mMDDetectCnt          = value; emit signalEventChangedMDDetectCnt         (value);}
    void setMDSenstivity        (quint16 value){ if(mMDSenstivity         == value)return; mMDSenstivity         = value; emit signalEventChangedMDSenstivity        (value);}
    void setMDCurrSignal        (quint16 value){ if(mMDCurrSignal         == value)return; mMDCurrSignal         = value; emit signalEventChangedMDCurrSignal        (value);}
    void setWCCurrWeight        (quint32 value)
    {
        if(mWCCurrWeight == value)
            return;

        if(value > 9999900)
        {
            mWCCurrWeight = 9999900;
        }
        else
        {
            mWCCurrWeight = value;
        }

        emit signalEventChangedWCCurrWeight(mWCCurrWeight);
    }
    void setWCCurrEventType     (quint16 value){ if(mWCCurrEventType      == value)return; mWCCurrEventType      = value; emit signalEventChangedWCCurrEventType     (value);}
    void setWCCurrAvgWeight     (quint32 value)
    {
        if(mWCCurrAvgWeight == value)
            return;

        if(value > 9999900)
        {
            mWCCurrAvgWeight = 9999900;
        }
        else
        {
            mWCCurrAvgWeight = value;
        }

        emit signalEventChangedWCCurrAvgWeight     (mWCCurrAvgWeight);
    }
    void setWCCurrAvgEventType  (quint16 value){ if(mWCCurrAvgEventType   == value)return; mWCCurrAvgEventType   = value; emit signalEventChangedWCCurrAvgEventType  (value);}
    void setWCAverageN          (quint16 value){ if(mWCAverageN           == value)return; mWCAverageN           = value; emit signalEventChangedWCAverageN          (value);}
    void setWCTrendsLastNValue  (int     value){ if(mWCTrendsLastNValue   == value)return; mWCTrendsLastNValue   = value; emit signalEventChangedWCTrendsLastNValue  (value);}
    void setWCTrendsOptionH     (int     value){ if(mWCTrendsOptionH      == value)return; mWCTrendsOptionH      = value; emit signalEventChangedWCTrendsOptionH     (value);}
    void setWCTrendsOptionFilter(int     value){ if(mWCTrendsOptionFilter == value)return; mWCTrendsOptionFilter = value; emit signalEventChangedWCTrendsOptionFilter(value);}
    void setWCTrendsOptionLastN (int     value){ if(mWCTrendsOptionLastN  == value)return; mWCTrendsOptionLastN  = value; emit signalEventChangedWCTrendsOptionLastN (value);}
    void setWCTotalCnt          (int     value){ if(mWCTotalCnt           == value)return; mWCTotalCnt           = value; emit signalEventChangedWCTotalCnt          (value);}
    void setWCNGCnt             (int     value){ if(mWCNGCnt              == value)return; mWCNGCnt              = value; emit signalEventChangedWCNGCnt             (value);}
    void setWCTradeCnt          (int     value){ if(mWCTradeCnt           == value)return; mWCTradeCnt           = value; emit signalEventChangedWCTradeCnt          (value);}
    void setWCOverCnt           (int     value){ if(mWCOverCnt            == value)return; mWCOverCnt            = value; emit signalEventChangedWCOverCnt           (value);}
    void setWCOverWarningCnt    (int     value){ if(mWCOverWarningCnt     == value)return; mWCOverWarningCnt     = value; emit signalEventChangedWCOverWarningCnt    (value);}
    void setWCNormalCnt         (int     value){ if(mWCNormalCnt          == value)return; mWCNormalCnt          = value; emit signalEventChangedWCNormalCnt         (value);}
    void setWCUnderWarningCnt   (int     value){ if(mWCUnderWarningCnt    == value)return; mWCUnderWarningCnt    = value; emit signalEventChangedWCUnderWarningCnt   (value);}
    void setWCUnderCnt          (int     value){ if(mWCUnderCnt           == value)return; mWCUnderCnt           = value; emit signalEventChangedWCUnderCnt          (value);}
    void setWCEtcErrorCnt       (int     value){ if(mWCEtcErrorCnt        == value)return; mWCEtcErrorCnt        = value; emit signalEventChangedWCEtcErrorCnt       (value);}
    void setWCOverWeight        (quint32 value){ if(mWCOverWeight         == value)return; mWCOverWeight         = value; emit signalEventChangedWCOverWeight        (value);}
    void setWCOverWarningWeight (quint32 value){ if(mWCOverWarningWeight  == value)return; mWCOverWarningWeight  = value; emit signalEventChangedWCOverWarningWeight (value);}
    void setWCNormalWeight      (quint32 value){ if(mWCNormalWeight       == value)return; mWCNormalWeight       = value; emit signalEventChangedWCNormalWeight      (value);}
    void setWCUnderWarningWeight(quint32 value){ if(mWCUnderWarningWeight == value)return; mWCUnderWarningWeight = value; emit signalEventChangedWCUnderWarningWeight(value);}
    void setWCUnderWeight       (quint32 value){ if(mWCUnderWeight        == value)return; mWCUnderWeight        = value; emit signalEventChangedWCUnderWeight       (value);}
    void setWCTradeTotalWeight  (quint64 value){ if(mWCTradeTotalWeight   == value)return; mWCTradeTotalWeight   = value; emit signalEventChangedWCTradeTotalWeight  (value);}
    void setWCTareWeight        (quint32 value){ if(mWCTareWeight         == value)return; mWCTareWeight         = value; emit signalEventChangedWCTareWeight        (value);}

    explicit MainViewModel(QObject *parent = nullptr);

signals:
    void signalEventChangedIsDetail            (bool    value);
    void signalEventChangedWCViewMode          (int     value);
    void signalEventChangedWait                (quint16 value);
    void signalEventChangedProductNo           (quint16 value);
    void signalEventChangedProductName         (QString value);
    void signalEventChangedLastErrorType       (quint16 value);
    void signalEventChangedLastErrorTime       (QString value);
    void signalEventChangedLastErrorValue      (quint32 value);
    void signalEventChangedMDTotalCnt          (quint32 value);
    void signalEventChangedMDDetectCnt         (quint32 value);
    void signalEventChangedMDSenstivity        (quint16 value);
    void signalEventChangedMDCurrSignal        (quint16 value);
    void signalEventChangedWCCurrWeight        (quint32 value);
    void signalEventChangedWCCurrEventType     (quint16 value);
    void signalEventChangedWCCurrAvgWeight     (quint32 value);
    void signalEventChangedWCCurrAvgEventType  (quint16 value);
    void signalEventChangedWCAverageN          (quint16 value);
    void signalEventChangedWCTrendsLastNValue  (int     value);
    void signalEventChangedWCTrendsOptionH     (int     value);
    void signalEventChangedWCTrendsOptionFilter(int     value);
    void signalEventChangedWCTrendsOptionLastN (int     value);
    void signalEventChangedWCTotalCnt          (int     value);
    void signalEventChangedWCNGCnt             (int     value);
    void signalEventChangedWCTradeCnt          (int     value);
    void signalEventChangedWCOverCnt           (int     value);
    void signalEventChangedWCOverWarningCnt    (int     value);
    void signalEventChangedWCNormalCnt         (int     value);
    void signalEventChangedWCUnderWarningCnt   (int     value);
    void signalEventChangedWCUnderCnt          (int     value);
    void signalEventChangedWCEtcErrorCnt       (int     value);
    void signalEventChangedWCOverWeight        (quint32 value);
    void signalEventChangedWCOverWarningWeight (quint32 value);
    void signalEventChangedWCNormalWeight      (quint32 value);
    void signalEventChangedWCUnderWarningWeight(quint32 value);
    void signalEventChangedWCUnderWeight       (quint32 value);
    void signalEventChangedWCTradeTotalWeight  (quint64 value);
    void signalEventChangedWCTareWeight        (quint32 value);
    void signalEventNotifyWCNG                 (quint32 value, quint16 eventType);
    void signalEventNotifyMDDetect             (             );

    void signalCommandSetZero(quint16 deviceSeq);
    void signalCommandSaveDeviceSetting(void * sender, DeviceSetting value);

public slots:
    Q_INVOKABLE void  onCommandSetIsDetail           (bool value);
    Q_INVOKABLE void  onCommandSetWCViewMode         (int  value);
    Q_INVOKABLE int   onCommandGetSnopShotPointsCnt  ();
    Q_INVOKABLE void  onCommandCreateSnopShot        (int width, int height);
    Q_INVOKABLE int   onCommandConvertWeightToY      (float weight);
    Q_INVOKABLE float onCommandConvertPointIdxToX    (int idx, int width);
    Q_INVOKABLE int   onCommandGetMinPointAt         (int idx);
    Q_INVOKABLE int   onCommandGetMaxPointAt         (int idx);
    Q_INVOKABLE int   onCommandSaveTrendsOption      (bool isUnderToOver, bool isTotal, bool TotalSinceStart, int lastNValue);
    Q_INVOKABLE void  onCommandSetZero();

    void onSignalEventChangedProductSetting               (int type, ProductSetting value);
    void onSignalEventChangedSelectedProductSetting       (ProductSetting  value);
    void onSignalEventChangedDeviceSetting                (DeviceSetting   value);
    void onSignalEventChangedDeviceStatus                 (quint16 deviceSeq, DeviceStatus value);
    void onSignalEventAddedEvent                          (quint16 deviceSeq, EventInfo  value );
};

#endif // MAINVIEWMODEL_H
