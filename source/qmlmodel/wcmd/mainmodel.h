#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>
#include "source/service/coreservice.h"

class MainModel : public QObject
{
    Q_OBJECT

private:

public:
    explicit MainModel(QObject *parent = nullptr): QObject(parent){pCoreService->start(this);}
    ~MainModel(){}
};

#endif // MAINMODEL_H
