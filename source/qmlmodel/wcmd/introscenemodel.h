#ifndef INTROSCENEMODEL_H
#define INTROSCENEMODEL_H

#include <QObject>
#include "source/service/coreservice.h"
#include "source/helper/languagehelper.h"

class IntroSceneModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int progressValue READ getProgressValue NOTIFY signalEventChangedProgressValue)
    Q_PROPERTY(int company       READ getCompany       NOTIFY signalEventChangedCompany      )

public:
    CoreService         * mpCoreService ;
    InformationModel    * mpInformation ;
    GuiSettingModel     * mpGuiSetting  ;

    int mProgressValue = 0;
    int mCompany       = EnumDefine::Company::COMPANY_NOVASEN;

    int getProgressValue(){ return mProgressValue;}
    int getCompany()      { return mCompany      ;}
    void setProgressValue(int     value){ if(mProgressValue == value) return; mProgressValue = value; emit signalEventChangedProgressValue(mProgressValue);}
    void setCompany      (int     value){ if(mCompany       == value) return; mCompany       = value; emit signalEventChangedCompany      (mCompany      );}

signals:
    void signalEventChangedProgressValue(int value);
    void signalEventChangedCompany      (int value);

public slots:
    Q_INVOKABLE void onCommandLoadLanguage()
    {
        LanguageHelper::getInstance()->loadLanguage((EnumDefine::Language)mpGuiSetting->mLanguage);
    }

//  down layer ===================================================================================
public slots:
    void onSignalEventChangedState(int value)
    {
        if(value != EnumDefine::ServiceState::SERVICE_INIT && value != EnumDefine::ServiceState::SERVICE_STARTING)
        {
            setProgressValue(100);
        }
    }

//  internal layer ===================================================================================
public:
    explicit IntroSceneModel(QObject *parent = nullptr) : QObject(parent)
    {
        mpCoreService = CoreService::getInstance();

        mpGuiSetting  = &(mpCoreService->mLocalSettingService.mGuiSetting );
        mpInformation = &(mpCoreService->mLocalSettingService.mInformation);
#ifdef BUILD_COMPANY_DONGNAM
        setCompany(EnumDefine::Company::COMPANY_DONGNAM);
#else
        setCompany(EnumDefine::Company::COMPANY_NOVASEN);
#endif
        connect(mpCoreService,  SIGNAL(signalEventChangedState  (int)    ),this, SLOT(onSignalEventChangedState  (int    )));

        onSignalEventChangedState  (mpCoreService->mState  );

        if(/*mUpgradeThread.isNeedUpgrade()*/ false)
        {

        }
        else
        {
            mpCoreService->onCommandStart();
        }
    }
};

#endif // INTROSCENEMODEL_H
