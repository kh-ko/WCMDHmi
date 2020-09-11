#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>
#include "source/helper/languagehelper.h"
#include "source/service/coreservice.h"

class MainModel : public QObject
{
    Q_OBJECT

private:
    LanguageHelper mLanguageHelper;
    CoreService    mCoreService;

public:
    explicit MainModel(QObject *parent = nullptr): QObject(parent){mLanguageHelper.setContext(this);}
    ~MainModel(){}
};

#endif // MAINMODEL_H
