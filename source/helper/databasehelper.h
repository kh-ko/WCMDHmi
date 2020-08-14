#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QObject>
#include <QtSql>

#include "source/globaldef/EnumDefine.h"
#include "source/model/deviceconnectionInfo.h"
#include "source/model/productsetting.h"
#include "source/model/event.h"
#include "source/model/databasebackupstate.h"

class DatabaseHelper : public QObject
{
    Q_OBJECT
private:
    static DatabaseHelper * mpSelf;
    QMutex mCPoolMutex;
    QMap<QString, QSqlDatabase *> mConnectionPool;

    //bool    mIsBackupNeed = false;
    quint64 mMaxEventCount = 5000000;
    int    mTempFileRecordCnt = 0;
    QMutex mTempFileMutex;
    QFile mTempFile;
    QTextStream mTempOut;

public:
    static DatabaseHelper* getInstance();
    explicit DatabaseHelper(QObject *parent = nullptr);
    quint64 getMaxEventCount(){return mMaxEventCount;}
    ~DatabaseHelper();
    QSqlDatabase * getDatabaseConnection(QString connectionName);

    EnumDefine::DatabaseErrorType   addDeviceConnectionInfo(QString conName, DeviceConnectionInfo * deviceConnectionInfo);
    EnumDefine::DatabaseErrorType   editDeviceConnectionInfo(QString conName, DeviceConnectionInfo deviceConnectionInfo);
    EnumDefine::DatabaseErrorType   removeDeviceConnectionInfo(QString conName, quint16 seq);
    QList<DeviceConnectionInfo>     findAllConnectionInfo(QString conName);
    DeviceConnectionInfo            recordToDeviceConnectionInfo(QSqlRecord * record);

    EnumDefine::DatabaseErrorType   addProductSetting(QString conName, ProductSetting * productSetting);
    EnumDefine::DatabaseErrorType   editProductSetting(QString conName, ProductSetting productSetting);
    EnumDefine::DatabaseErrorType   selectProductSetting(QString conName, quint16 seq);
    EnumDefine::DatabaseErrorType   removeProductSetting(QString conName, quint16 seq);
    QList<ProductSetting>           findAllProductSetting(QString conName);
    ProductSetting                  findSelectedProductSetting(QString conName);
    ProductSetting                  newProductSetting(QString conName);
    ProductSetting                  recordToProductSetting(QSqlRecord * record);

    //EnumDefine::DatabaseErrorType   addEvent(QString conName, Event * event);
    //EnumDefine::DatabaseErrorType editProductEvent(QString conName, Event event);
    //EnumDefine::DatabaseErrorType removeProductSetting(QString conName, quint64 seq);
    EnumDefine::DatabaseErrorType   addEvent(QString conName, Event * event);
    void                            addEventToTempFile(QString conName, Event event);
    QList<Event>                    findAllEventAfterSeq(QString conName, quint64 seq);
    QList<Event>                    findAllEventByPeriod(QString conName, bool isTotal, bool isWeightEvent, int startYear, int startMonth, int startDay, int startHour, int endYear, int endMonth, int endDay, int endHour, int cntPerPage, quint64 pageIdx, quint64 * outTotalCnt, quint64 * outTotalPage);
    quint64                         findLastEventSeq(QString conName);
    Event                           recordToEvent(QSqlRecord * record);

    void                            restoreEventFromTempFile(QString conName);
    void                            backup(QString conName, DatabaseBackupState * backupState);
    void                            loggingReset(QString conName);
    void                            factoryReset(QString conName);
    void                            setMaxCount(QString conName, quint64 count, int backupYear, int backupMonth, int backupDay);
    quint64                         countEventAfterDate(QString conName, int year, int month, int day);

    void openTempFile();
    void closeTempFile();
signals:

};

#endif // DATABASEHELPER_H
