#ifndef INTROSCENEMODEL_H
#define INTROSCENEMODEL_H

#include <QObject>
#include "source/globaldef/EnumDefine.h"
class IntroSceneModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int progressValue READ getProgressValue NOTIFY signalEventChangedProgressValue)
    Q_PROPERTY(int company       READ getCompany       NOTIFY signalEventChangedCompany      )

private:
    int mProgressValue = 0;
    int mCompany       = EnumDefine::Company::COMPANY_NOVASEN;

public:
    explicit IntroSceneModel(QObject *parent = nullptr);
    ~IntroSceneModel();
    int getProgressValue();
    int getCompany();
    void setProgressValue(int value);

signals:
    void signalEventChangedProgressValue(int value);
    void signalEventChangedCompany      (int value);

public slots:
    void onSignalEventStartedService();
    Q_INVOKABLE void onCommandLoadLanguage();
};

#endif // INTROSCENEMODEL_H
