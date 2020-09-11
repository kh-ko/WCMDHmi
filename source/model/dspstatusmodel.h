#ifndef DSPSTATUSMODEL_H
#define DSPSTATUSMODEL_H

#include <QObject>
#include <QDebug>
#include <QDateTime>
#include "source/globaldef/EnumDefine.h"
#include "source/util/eventchecker.h"
#include "source/model/productstatusmodel.h"
#include "source/model/lasterrormodel.h"
#include "source/model/productsettingmodel.h"
#include "source/model/dspsettingmodel.h"
#include "source/thread/dsp/dto/dspstatusdto.h"
#include "source/thread/dsp/dto/dspinfodto.h"

class WeightTrendsItem
{
public:
    quint64 mProductSettingSeq;
    bool    mIsTrade;
    quint32 mValue;
};

class WeightTrends
{
public:
    int mCount = 0;
    WeightTrendsItem mArray[1000000];
};

class DspStatusModel : public QObject
{
    Q_OBJECT

public:
    int                         mCurrentProductListIdx = 0;
    ProductStatusModel          mCurrentProductStatus;
    QList<ProductStatusModel*>  mListProductStatus;
    WeightTrends                mTrends;
    LastErrorModel              mLastError;
    ProductSettingModel         mProductSetting;
    DspSettingModel             mDspSetting;

    quint64 mSeq                    = 0;
    bool    mFactoryReset           = false;
    quint16 mRun                    = EnumDefine::RunState::STOP;
    bool    mIsComm                 = true ;
    bool    mIsAlarm                = false;
    bool    mIsSensorAlarm          = false;
    bool    mIsPhotoAlarm           = false;
    bool    mIsMortorAlarm          = false;
    bool    mIsDspSettingAlarm      = false;
    bool    mIsProductSettingAlarm  = false;
    quint32 mID                     =     0;
    QString mVersion                =    "";
    quint16 mWait                   =     1;
    quint16 mMDCurrSignal           =     0;
    quint32 mWCCurrWeight           =     0;
    quint16 mWCCurrEventType        = EnumDefine::EventType::WEIGHT_NORMAL_TYPE;

    void addEvent          (quint16 eventType, quint32 value, bool isSkipSignal)
    {
        if(EventChecker::IsWeightEvent(eventType))
        {
            if(mRun != EnumDefine::RunState::STOP)
            {
                setWCCurrWeight   (value);
                setWCCurrEventType(eventType);
            }

            mTrends.mArray[mTrends.mCount].mProductSettingSeq = mCurrentProductStatus.mProductSettingSeq;
            mTrends.mArray[mTrends.mCount].mIsTrade           = EventChecker::isWeightTrade(eventType);
            mTrends.mArray[mTrends.mCount].mValue             = value;
            mTrends.mCount++;
        }

        if(EventChecker::IsWeightOrMetal(eventType))
        {
            mCurrentProductStatus.addEvent(eventType, value);
            mListProductStatus.at(mCurrentProductListIdx)->addEvent(eventType, value);
        }

        if(isSkipSignal)
            return;

        if(EventChecker::IsNGEvent(eventType))
        {
            mLastError.setTime(QDateTime::currentDateTime().toString("hh:mm:ss"));
            mLastError.setEventType(eventType);
            mLastError.setValue(value);
        }

        emit siganlEventAddedEvent(eventType, value);
    }

    void setFactoryReset         (bool                       value){ if(value == mFactoryReset          ) return; mFactoryReset            = value; emit signalEventChangedFactoryReset         (mFactoryReset          );}
    void setRun                  (quint16                    value){ if(value == mRun                   ) return; mRun                     = value; emit signalEventChangedRun                  (mRun                   );}
    void setIsComm               (bool                       value){ if(value == mIsComm                ) return; mIsComm                  = value; emit signalEventChangedIsComm               (mIsComm                );}
    void setIsAlarm              (bool                       value){ if(value == mIsAlarm               ) return; mIsAlarm                 = value; emit signalEventChangedIsAlarm              (mIsAlarm               );}
    void setIsSensorAlarm        (bool value)
    {
        if(value == mIsSensorAlarm) return;

        mIsSensorAlarm = value;

        emit signalEventChangedIsSensorAlarm(mIsSensorAlarm);

        setIsAlarm(mIsSensorAlarm || mIsPhotoAlarm || mIsMortorAlarm || mIsDspSettingAlarm || mIsProductSettingAlarm);
    }
    void setIsPhotoAlarm         (bool value)
    {
        if(value == mIsPhotoAlarm) return;

        mIsPhotoAlarm = value;

        emit signalEventChangedIsPhotoAlarm(mIsPhotoAlarm);

        setIsAlarm(mIsSensorAlarm || mIsPhotoAlarm || mIsMortorAlarm || mIsDspSettingAlarm || mIsProductSettingAlarm);
    }
    void setIsMortorAlarm        (bool value)
    {
        if(value == mIsMortorAlarm) return;

        mIsMortorAlarm = value;

        emit signalEventChangedIsMortorAlarm(mIsMortorAlarm);

        setIsAlarm(mIsSensorAlarm || mIsPhotoAlarm || mIsMortorAlarm || mIsDspSettingAlarm || mIsProductSettingAlarm);
    }
    void setIsDspSettingAlarm(bool value)
    {
        if(value == mIsDspSettingAlarm) return;

        mIsDspSettingAlarm = value;

        emit signalEventChangedIsDspSettingAlarm(mIsDspSettingAlarm);

        setIsAlarm(mIsSensorAlarm || mIsPhotoAlarm || mIsMortorAlarm || mIsDspSettingAlarm || mIsProductSettingAlarm);
    }
    void setIsProductSettingAlarm(bool value)
    {
        if(value == mIsProductSettingAlarm ) return;

        mIsProductSettingAlarm   = value;

        emit signalEventChangedIsProductSettingAlarm(mIsProductSettingAlarm);

        setIsAlarm(mIsSensorAlarm || mIsPhotoAlarm || mIsMortorAlarm || mIsDspSettingAlarm || mIsProductSettingAlarm);
    }
    void setWait                 (quint16                    value){ if(value == mWait                  ) return; mWait                    = value; emit signalEventChangedWait                 (mWait                  );}
    void setMDCurrSignal         (quint16                    value){ if(value == mMDCurrSignal          ) return; mMDCurrSignal            = value; emit signalEventChangedMDCurrSignal         (mMDCurrSignal          );}
    void setWCCurrWeight         (quint32                    value){ if(value == mWCCurrWeight          ) return; mWCCurrWeight            = value; emit signalEventChangedWCCurrWeight         (mWCCurrWeight          );}
    void setWCCurrEventType      (quint16                    value){ if(value == mWCCurrEventType       ) return; mWCCurrEventType         = value; emit signalEventChangedWCCurrEventType      (mWCCurrEventType       );}

signals:
    void signalEventChangedProductSetting       ();
    void signalEventChangedDeviceSetting        ();
    void siganlEventAddedEvent                  (quint16 eventType, quint32 value);
    void signalEventChangedFactoryReset         (bool    value);
    void signalEventChangedRun                  (quint16 value);
    void signalEventChangedIsComm               (bool    value);
    void signalEventChangedIsAlarm              (bool    value);
    void signalEventChangedIsSensorAlarm        (bool    value);
    void signalEventChangedIsPhotoAlarm         (bool    value);
    void signalEventChangedIsMortorAlarm        (bool    value);
    void signalEventChangedIsDspSettingAlarm    (bool    value);
    void signalEventChangedIsProductSettingAlarm(bool    value);
    void signalEventChangedWait                 (quint16 value);
    void signalEventChangedMDCurrSignal         (quint16 value);
    void signalEventChangedWCCurrWeight         (quint32 value);
    void signalEventChangedWCCurrEventType      (quint16 value);

public:
    void setSelectProductSetting(quint64 productSettingSeq)
    {
        int idx = 0;

        if(mCurrentProductStatus.mProductSettingSeq == productSettingSeq)
            return;

        for(idx = 0; idx < mListProductStatus.size(); idx ++)
        {
            if(mListProductStatus.at(idx)->mProductSettingSeq == productSettingSeq)
            {
                mCurrentProductListIdx = idx;
                mCurrentProductStatus = *mListProductStatus.at(idx);
            }
        }

        if(idx == mListProductStatus.size())
        {
            ProductStatusModel * ps = new ProductStatusModel(this);
            ps->setProductSettingSeq(productSettingSeq);

            mCurrentProductListIdx = mListProductStatus.size();
            mCurrentProductStatus = *ps;
            mListProductStatus.append(ps);
        }
    }

    void setRemoteDspSetting(DspSettingModel * value, bool isEqualLocalSetting)
    {
        mDspSetting = value;
        emit signalEventChangedDeviceSetting();

        setIsDspSettingAlarm(!isEqualLocalSetting);
    }

    void setRemoteProductSetting(ProductSettingModel * value, bool isEqualLocalSetting)
    {
        mProductSetting = value;
        emit signalEventChangedProductSetting();

        setIsProductSettingAlarm(!isEqualLocalSetting);
    }

    void setDspStatus(DspStatusDto value)
    {
        if(value.mDspStatus.mRun == EnumDefine::RunState::STOP)
        {
            setWCCurrWeight   (value.mDspStatus.mCurrWeight);
            setWCCurrEventType(value.mDspStatus.mWCErrorType);
        }

        if((value.mDspStatus.mRun == EnumDefine::RunState::STOP && mRun != EnumDefine::RunState::STOP) || (value.mDspStatus.mRun != EnumDefine::RunState::STOP && mRun == EnumDefine::RunState::STOP))
        {
            setWCCurrWeight   (0);
            setWCCurrEventType(EnumDefine::EventType::WEIGHT_NORMAL_TYPE);
        }

        setRun            (value.mDspStatus.mRun);
        setIsSensorAlarm  (value.mDspStatus.mMDAlarm & EnumDefine::AlarmType::SENSOR_ALARM || value.mDspStatus.mWCAlarm & EnumDefine::AlarmType::SENSOR_ALARM);
        setIsPhotoAlarm   (value.mDspStatus.mMDAlarm & EnumDefine::AlarmType::PHOTO_ALARM  || value.mDspStatus.mWCAlarm & EnumDefine::AlarmType::PHOTO_ALARM );
        setIsMortorAlarm  (value.mDspStatus.mMDAlarm & EnumDefine::AlarmType::MOTOR_ALARM  || value.mDspStatus.mWCAlarm & EnumDefine::AlarmType::MOTOR_ALARM );
        setWait           (value.mDspStatus.mWait);
        setMDCurrSignal   (value.mDspStatus.mMDSignal);
    }

    void setDspInfo(DspInfoDto value)
    {
        mID = value.mDspInfo.mID;
        mVersion = QString("%1.%2.%3").arg(value.mDspInfo.mMajorVersion).arg(value.mDspInfo.mMinorVersion).arg(value.mDspInfo.mMaintenanceVersion);
    }

    void reset()
    {
        mCurrentProductStatus.reset();

        for(int i = 0; i < mListProductStatus.size(); i ++)
        {
            mListProductStatus[i]->reset();
        }
        mTrends.mCount = 0;
        mLastError.reset();
    }

    explicit DspStatusModel(QObject *parent = nullptr) : QObject(parent){}
};
#endif // DSPSTATUSMODEL_H
