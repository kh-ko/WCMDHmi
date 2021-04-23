#ifndef SEARCHDSPDLGMODEL_H
#define SEARCHDSPDLGMODEL_H

#include <QObject>

#include "source/globaldef/qmlenumdef.h"
#include "source/service/coreservice.h"

class SearchDspDlgModel : public QObject
{
    Q_OBJECT

signals:
    void signalEventAddedIp(QString ip);

public slots:
    void onFoundDsp(QString ip)
    {
        emit signalEventAddedIp(ip);
    }
public:
    explicit SearchDspDlgModel(QObject *parent = nullptr):QObject(parent)
    {
        ENABLE_SLOT_DSP_FOUND_DSP;

        pDspSP->searchDsp();
    }
};

#endif // SEARCHDSPDLGMODEL_H
