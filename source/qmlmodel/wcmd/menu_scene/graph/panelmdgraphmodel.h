#ifndef PANELMDGRAPHMODEL_H
#define PANELMDGRAPHMODEL_H

#include <QObject>

#include "source/service/coreservice.h"

#include "source/qmlmodel/wcmd/menu_scene/graph/metaldetectorgraphmodel.h"
class PanelMDGraphModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint16  sensorCnt         READ      getSensorCnt            NOTIFY      signalEventChangedSensorCnt         )
    Q_PROPERTY(bool     isRawGraphOn      READ      getIsRawGraphOn         NOTIFY      signalEventChangedsRawGraphOn       )
    Q_PROPERTY(quint16  senstivity        READ      getSenstivity           NOTIFY      signalEventChangedSenstivity        )
    Q_PROPERTY(int      range             READ      getRange                NOTIFY      signalEventChangedRange             )
    Q_PROPERTY(int      min               READ      getMin                  NOTIFY      signalEventChangedMin               )
    Q_PROPERTY(int      max               READ      getMax                  NOTIFY      signalEventChangedMax               )
    Q_PROPERTY(quint16  simpleSens01      READ      getSimpleSens01         NOTIFY      signalEventChangedSimpleSens01      )
    Q_PROPERTY(quint16  simpleSens02      READ      getSimpleSens02         NOTIFY      signalEventChangedSimpleSens02      )
    Q_PROPERTY(quint16  simpleSens03      READ      getSimpleSens03         NOTIFY      signalEventChangedSimpleSens03      )
    Q_PROPERTY(quint16  simpleSens04      READ      getSimpleSens04         NOTIFY      signalEventChangedSimpleSens04      )
    Q_PROPERTY(quint16  simpleSens05      READ      getSimpleSens05         NOTIFY      signalEventChangedSimpleSens05      )
    Q_PROPERTY(bool     isEditSenstivity  READ      getIsEditSenstivity     NOTIFY      signalEventChangedIsEditSenstivity  )

public:
    CoreService * mpCoreService;
    DspStatusModel * mpDspStatus;

    QList<MetalDetectorGraphModel*> mListMDGraphModel;
    quint16                 mSensorCnt          = 8;
    bool                    mIsRawGraphOn       = false;
    quint16                 mSenstivity         = 300;
    int                     mRange              = 600;
    int                     mMin                = 0;
    int                     mMax                = 0;
    quint16                 mSimpleSens01       = 0;
    quint16                 mSimpleSens02       = 0;
    quint16                 mSimpleSens03       = 0;
    quint16                 mSimpleSens04       = 0;
    quint16                 mSimpleSens05       = 0;
    bool                    mIsEditSenstivity   = false;

    quint16 getSensorCnt        (){return mSensorCnt        ;}
    bool    getIsRawGraphOn     (){return mIsRawGraphOn     ;}
    quint16 getSenstivity       (){return mSenstivity       ;}
    int     getRange            (){return mRange            ;}
    int     getMin              (){return mMin              ;}
    int     getMax              (){return mMax              ;}
    quint16 getSimpleSens01     (){return mSimpleSens01     ;}
    quint16 getSimpleSens02     (){return mSimpleSens02     ;}
    quint16 getSimpleSens03     (){return mSimpleSens03     ;}
    quint16 getSimpleSens04     (){return mSimpleSens04     ;}
    quint16 getSimpleSens05     (){return mSimpleSens05     ;}
    bool    getIsEditSenstivity (){ return mIsEditSenstivity;}

    void setSensorCnt       (quint16 value){ if(value == mSensorCnt         ) return; mSensorCnt        = value; emit signalEventChangedSensorCnt       (value);}
    void setIsRawGraphOn    (bool    value){ if(value == mIsRawGraphOn      ) return; mIsRawGraphOn     = value; emit signalEventChangedsRawGraphOn     (value);}
    void setSenstivity      (quint16 value){ if(value == mSenstivity        ) return; mSenstivity       = value; emit signalEventChangedSenstivity      (value);}
    void setRange           (int     value){ if(value == mRange             ) return; mRange            = value; emit signalEventChangedRange           (value);}
    void setMin             (int     value){ if(value == mMin               ) return; mMin              = value; emit signalEventChangedMin             (value);}
    void setMax             (int     value){ if(value == mMax               ) return; mMax              = value; emit signalEventChangedMax             (value);}
    void setIsEditSenstivity(bool    value){ if( value == mIsEditSenstivity ) return; mIsEditSenstivity = value; emit signalEventChangedIsEditSenstivity(value);}

    explicit PanelMDGraphModel(QObject *parent = nullptr):QObject(parent)
    {
        mpCoreService = CoreService::getInstance();
        mpDspStatus   = mpCoreService->mMapDspStatus.first();

        connect(&(mpCoreService->mProductSettingServcie.mCurrentProductSetting), SIGNAL(signalEventChangedMDSenstivity(quint16)), this, SLOT(onSignalEventChangedMDSenstivity(quint16)));
        connect(mpCoreService, SIGNAL(signalEventAddedMetalDetectorGraph (quint64, MetalGraphDto)), this, SLOT(onSgnalEventAddedMetalDetectorGraph (quint64, MetalGraphDto)));

        mSimpleSens01 = mpCoreService->mLocalSettingService.mHmiSetting.mSimpleSenstivity01;
        mSimpleSens02 = mpCoreService->mLocalSettingService.mHmiSetting.mSimpleSenstivity02;
        mSimpleSens03 = mpCoreService->mLocalSettingService.mHmiSetting.mSimpleSenstivity03;
        mSimpleSens04 = mpCoreService->mLocalSettingService.mHmiSetting.mSimpleSenstivity04;
        mSimpleSens05 = mpCoreService->mLocalSettingService.mHmiSetting.mSimpleSenstivity05;

        for(int i = 0; i < 8; i ++)
        {
            MetalDetectorGraphModel * tempModel = new MetalDetectorGraphModel(this);

            tempModel->setIsRawGraphOn(mIsRawGraphOn);
            tempModel->setRange(mRange);
            tempModel->setSenstivity(mSenstivity);

            mListMDGraphModel.append(tempModel);
        }

        mpCoreService->onCommandSendMetalDetectorGraphOnCmd(mpDspStatus->mSeq, true);
    }
    ~PanelMDGraphModel()
    {
        mpCoreService->onCommandSendMetalDetectorGraphOnCmd(mpDspStatus->mSeq, false);
    }

signals:
    void signalEventChangedSensorCnt         (quint16 value                );
    void signalEventChangedsRawGraphOn       (bool    value                );
    void signalEventChangedSenstivity        (quint16 value                );
    void signalEventChangedRange             (int     value                );
    void signalEventChangedMin               (int     value                );
    void signalEventChangedMax               (int     value                );
    void signalEventGraphUpdate              (                             );
    void signalEventChangedIsEditSenstivity  (bool    value                );
    void signalEventChangedSimpleSens01      (                             );
    void signalEventChangedSimpleSens02      (                             );
    void signalEventChangedSimpleSens03      (                             );
    void signalEventChangedSimpleSens04      (                             );
    void signalEventChangedSimpleSens05      (                             );
    void signalResultSaveProductSetting      (int error                    );

public slots:
    Q_INVOKABLE void onCommandRawGraphOn(bool value)
    {
        setIsRawGraphOn(value);

        for(int i = 0; i < mListMDGraphModel.size(); i ++)
        {
            mListMDGraphModel.at(i)->setIsRawGraphOn(value);
        }
    }
    Q_INVOKABLE MetalDetectorGraphModel * onCommandGetGraphModel(int idx)
    {
        return mListMDGraphModel.at(idx);
    }
    Q_INVOKABLE void onCommandSetRange(int value)
    {
        setRange(value);

        for(int i = 0; i < mListMDGraphModel.size(); i ++)
        {
            mListMDGraphModel.at(i)->setRange(mRange);
        }
    }
    Q_INVOKABLE void onCommandSetSenstivity(quint16 value)
    {
        setSenstivity(value);
        setIsEditSenstivity(true);

        for(int i = 0; i < mListMDGraphModel.size(); i ++)
        {
            mListMDGraphModel.at(i)->setSenstivity(getSenstivity());
        }
    }
    Q_INVOKABLE void onCommandSetSimpleSens01(){onCommandSetSenstivity(mSimpleSens01);}
    Q_INVOKABLE void onCommandSetSimpleSens02(){onCommandSetSenstivity(mSimpleSens02);}
    Q_INVOKABLE void onCommandSetSimpleSens03(){onCommandSetSenstivity(mSimpleSens03);}
    Q_INVOKABLE void onCommandSetSimpleSens04(){onCommandSetSenstivity(mSimpleSens04);}
    Q_INVOKABLE void onCommandSetSimpleSens05(){onCommandSetSenstivity(mSimpleSens05);}
    Q_INVOKABLE void onCommandApply()
    {
        int ret = mpCoreService->onCommandEditProductSetting(mpCoreService->mProductSettingServcie.mCurrentProductSetting.mSeq                  ,
                                                             mpCoreService->mProductSettingServcie.mCurrentProductSetting.mNo                   ,
                                                             mpCoreService->mProductSettingServcie.mCurrentProductSetting.mName                 ,
                                                             mpCoreService->mProductSettingServcie.mCurrentProductSetting.mLength               ,
                                                             mpCoreService->mProductSettingServcie.mCurrentProductSetting.mSpeed                ,
                                                             mpCoreService->mProductSettingServcie.mCurrentProductSetting.mMotorAccelerationTime,
                                                             mpCoreService->mProductSettingServcie.mCurrentProductSetting.mUnderWeight          ,
                                                             mpCoreService->mProductSettingServcie.mCurrentProductSetting.mUnderWarningWeight   ,
                                                             mpCoreService->mProductSettingServcie.mCurrentProductSetting.mNormalWeight         ,
                                                             mpCoreService->mProductSettingServcie.mCurrentProductSetting.mOverWarningWeight    ,
                                                             mpCoreService->mProductSettingServcie.mCurrentProductSetting.mOverWeight           ,
                                                             mpCoreService->mProductSettingServcie.mCurrentProductSetting.mTareWeight           ,
                                                             mpCoreService->mProductSettingServcie.mCurrentProductSetting.mWCNGMotion           ,
                                                             mpCoreService->mProductSettingServcie.mCurrentProductSetting.mDynamicFactor        ,
                                                             mSenstivity                                                                        ,
                                                             mpCoreService->mProductSettingServcie.mCurrentProductSetting.mMDNGMotion           );
        setIsEditSenstivity(false);

        emit signalResultSaveProductSetting(ret);
    }

    void onSignalEventChangedMDSenstivity(quint16 value)
    {
        setSenstivity(mpCoreService->mProductSettingServcie.mCurrentProductSetting.mMDSenstivity);

        for(int i = 0; i < mListMDGraphModel.size(); i ++)
        {
            mListMDGraphModel.at(i)->setSenstivity(mpCoreService->mProductSettingServcie.mCurrentProductSetting.mMDSenstivity);
        }
    }
    void onSgnalEventAddedMetalDetectorGraph(quint64 deviceSeq, MetalGraphDto value)
    {
        int min = 0;
        int max = 0;

        setSensorCnt(value.mData->mData.mSensorCnt);

        for(int i = 0; i < value.mData->mData.mSensorCnt; i ++)
        {
            mListMDGraphModel.at(i)->addPoints(value.mData->mData.mPointCnt, &(value.mData->mData.mArrayPoints[(value.mData->mData.mPointCnt * 2) * i]));
        }


        for(int i = 0; i < value.mData->mData.mSensorCnt; i ++)
        {
            if(min > mListMDGraphModel.at(i)->getMin())
            {
                min = mListMDGraphModel.at(i)->getMin();
            }

            if(max < mListMDGraphModel.at(i)->getMax())
            {
                max = mListMDGraphModel.at(i)->getMax();
            }
        }

        setMax(max);
        setMin(min);

        emit signalEventGraphUpdate();
    }

};

#endif // PANELMDGRAPHMODEL_H
