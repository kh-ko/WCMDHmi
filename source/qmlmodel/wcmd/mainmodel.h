#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>
#include "source/helper/databasehelper.h"
#include "source/helper/languagehelper.h"
#include "source/helper/localsetting.h"
#include "source/service/wcmdservice.h"

class MainModel : public QObject
{
    Q_OBJECT

private:
    DatabaseHelper mDatabaseHelper;
    LocalSetting   mLocalSetting;
    LanguageHelper mLanguageHelper;
    WCMDService    mWCMDService;

public:
    explicit MainModel(QObject *parent = nullptr): QObject(parent){mLanguageHelper.setContext(this);}
    ~MainModel(){}
};

#endif // MAINMODEL_H
