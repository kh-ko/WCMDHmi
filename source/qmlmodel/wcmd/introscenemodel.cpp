#include "introscenemodel.h"

#include <QDebug>

#include "source/globaldef/EnumDefine.h"
#include "source/helper/databasehelper.h"
#include "source/helper/languagehelper.h"
#include "source/helper/localsetting.h"

#include "source/service/wcmdservice.h"

IntroSceneModel::IntroSceneModel(QObject *parent) : QObject(parent)
{
    qDebug() << "IntroSceneModel : New";

    Information info = LocalSetting::getInstance()->getInformation();

    if(info.mCompany == "NOVASEN")
    {
        mCompany = EnumDefine::Company::COMPANY_NOVASEN;
    }
    if(info.mCompany == "DONG NAM MACHINERY SHOP")
    {
        mCompany = EnumDefine::Company::COMPANY_DONGNAM;
    }

    if(WCMDService::getInstance()->isRun())
    {
        setProgressValue(100);
        return;
    }

    qDebug() << "IntroSceneModel : mCompany = " << mCompany;

    connect(WCMDService::getInstance(), SIGNAL(signalEventStartedService()), this, SLOT(onSignalEventStartedService()));
}

IntroSceneModel::~IntroSceneModel()
{
    qDebug() << "IntroSceneModel : Delete";
}

int IntroSceneModel::getProgressValue()
{
    return mProgressValue;
}

int IntroSceneModel::getCompany()
{
    return mCompany;
}

void IntroSceneModel::setProgressValue(int value)
{
    mProgressValue = value; emit signalEventChangedProgressValue(mProgressValue);
}

void IntroSceneModel::onCommandLoadLanguage()
{
    EnumDefine::Language language = LocalSetting::getInstance()->getDeviceSetting().mLanguage;
    LanguageHelper::getInstance()->loadLanguage(language);
}
void IntroSceneModel::onSignalEventStartedService()
{
    setProgressValue(100);

}
