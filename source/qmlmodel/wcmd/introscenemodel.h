#ifndef INTROSCENEMODEL_H
#define INTROSCENEMODEL_H

#include <QObject>
#include "source/service/defaultsetting/defaultsettingsprovider.h"
#include "source/globaldef/qmlenumdef.h"
#include "source/service/def/builddef.h"
#include "source/service/coreservice.h"

class IntroSceneModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int progressValue READ getProgressValue NOTIFY signalEventChangedProgressValue)
    Q_PROPERTY(int company       READ getCompany       NOTIFY signalEventChangedCompany      )

public:
    int mProgressValue = 0;
    int mCompany       = QmlEnumDef::COMPANY_NOVASEN;

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
    }

//  down layer ===================================================================================
public slots:
    void onStartedCoreService()
    {
        setProgressValue(100);

    }

//  internal layer ===================================================================================
public:
    explicit IntroSceneModel(QObject *parent = nullptr) : QObject(parent)
    {
        if(pDefaultSP->COMPANY == EnumDef::COMPANY_DONGNAM)
        {
            setCompany(QmlEnumDef::COMPANY_DONGNAM);
        }
        else if(pDefaultSP->COMPANY == EnumDef::COMPANY_SOLURAY)
        {
            setCompany(QmlEnumDef::COMPANY_SOLURAY);
        }
        else
        {
            setCompany(QmlEnumDef::COMPANY_NOVASEN);
        }

        if(pCoreService->mIsRunning)
        {
            setProgressValue(100);
            return;
        }

        ENABLE_SLOT_CORE_START;
    }
};

#endif // INTROSCENEMODEL_H
