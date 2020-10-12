#ifndef MONITORINGSERVICE_H
#define MONITORINGSERVICE_H

#include <QObject>
#include <QUdpSocket>

#include "source/model/informationmodel.h"
#include "source/model/procsettingmodel.h"
#include "source/model/dspstatusmodel.h"
#include "source/model/productstatusmodel.h"

class MonitoringService : public QObject
{
    Q_OBJECT
public:
    InformationModel    * mpInformation     ;
    ProductSettingModel * mpProductSetting  ;
    DspStatusModel      * mpDspStatus       ;
    ProductStatusModel  * mpProductStatus   ;

    QUdpSocket * mpSocket = nullptr;
    quint16      mPort    = 10026;
    QHostAddress mHostAddr;

public slots:
    void onReceive();
    void onSockError(QAbstractSocket::SocketError error);

public:
    void startMonitoringService();
    explicit MonitoringService(QObject *parent = nullptr);
    ~MonitoringService();

private:
    void open();
    void close();

};

#endif // MONITORINGSERVICE_H
