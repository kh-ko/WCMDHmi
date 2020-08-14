#include "databasehelper.h"

#include <QApplication>

#include "source/globaldef/GlobalDefine.h"

DatabaseHelper * DatabaseHelper::mpSelf = nullptr;

DatabaseHelper* DatabaseHelper::getInstance()
{
    return mpSelf;
}


DatabaseHelper::DatabaseHelper(QObject *parent) : QObject(parent)
{
    qDebug() << "DatabaseHelper : New";

    mpSelf = this;
}

DatabaseHelper::~DatabaseHelper()
{
    qDebug() << "DatabaseHelper : Delete";

    mCPoolMutex.lock();

    QList<QString> keys = mConnectionPool.keys();
    QSqlDatabase * database;

    for(int i = 0; i < keys.size(); i ++)
    {
        database = mConnectionPool[keys[i]];

        if(database->isOpen())
            database->close();

        delete database;

        QSqlDatabase::removeDatabase(keys[i]);
    }

    mConnectionPool.clear();

    mCPoolMutex.unlock();

    closeTempFile();
}

QSqlDatabase * DatabaseHelper::getDatabaseConnection(QString connectionName)
{
    QSqlDatabase *database = nullptr;

    mCPoolMutex.lock();

    try {
        if(mConnectionPool.contains(connectionName))
        {
            database = mConnectionPool[connectionName];
        }
        else
        {
            database = new QSqlDatabase();

            *database = QSqlDatabase::addDatabase("QPSQL", connectionName);

            database->setHostName("localhost");
            database->setDatabaseName("wcmddb");
            database->setUserName("sa");
            database->setPassword("nova1002");

            if(database->open() == false){ throw 0; }

            mConnectionPool.insert(connectionName, database);
        }
    }
    catch (int ex)
    {
        qDebug() << "db open failed : " << database->lastError().text();
        delete database;
        database = nullptr;
    }

    mCPoolMutex.unlock();

    return database;
}

EnumDefine::DatabaseErrorType DatabaseHelper::addDeviceConnectionInfo(QString conName, DeviceConnectionInfo * deviceConnectionInfo)
{
#ifdef OS_WINDOW
    deviceConnectionInfo->mSeq = 0;
    return EnumDefine::DatabaseErrorType::DB_NONE_ERROR;
#else
    QString sql = "INSERT INTO public.tb_device_connection_info(ip, port) VALUES ('%1', %2);";

    try {

        QSqlDatabase *database = getDatabaseConnection(conName);

        if(database == nullptr)
        {
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }

        QSqlQuery queryInsert = database->exec(sql.arg(deviceConnectionInfo->mIp)
                                                  .arg(deviceConnectionInfo->mPort));

        if(queryInsert.lastError().isValid())
        {
            qDebug() << database->lastError().text();
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }

        deviceConnectionInfo->mSeq = queryInsert.lastInsertId().toUInt();

    }
    catch(int ex)
    {
        qDebug() << "[addDeviceConnectionInfo] occured exception";
        return (EnumDefine::DatabaseErrorType)ex;
    }

    return EnumDefine::DatabaseErrorType::DB_NONE_ERROR;
#endif
}

EnumDefine::DatabaseErrorType DatabaseHelper::editDeviceConnectionInfo(QString conName, DeviceConnectionInfo deviceConnectionInfo)
{
#ifdef OS_WINDOW
    return EnumDefine::DatabaseErrorType::DB_NONE_ERROR;
#else
    QString sql = "UPDATE public.tb_device_connection_info SET ip='%1', port=%2 WHERE seq = %3";

    try {

        QSqlDatabase *database = getDatabaseConnection(conName);

        if(database == nullptr)
        {
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }

        QSqlQuery queryEdit = database->exec(sql.arg(deviceConnectionInfo.mIp)
                                                  .arg(deviceConnectionInfo.mPort)
                                                  .arg(deviceConnectionInfo.mSeq));

        if(queryEdit.lastError().isValid())
        {
            qDebug() << database->lastError().text();
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }
    }
    catch(int ex)
    {
        qDebug() << "[editDeviceConnectionInfo] occured exception";
        return (EnumDefine::DatabaseErrorType)ex;
    }

    return EnumDefine::DatabaseErrorType::DB_NONE_ERROR;
#endif
}

EnumDefine::DatabaseErrorType DatabaseHelper::removeDeviceConnectionInfo(QString conName, quint16 seq)
{
#ifdef OS_WINDOW
    return EnumDefine::DatabaseErrorType::DB_NONE_ERROR;
#else
    QString sql = "DELETE public.tb_device_connection_info WHERE seq = %1";

    try {

        QSqlDatabase *database = getDatabaseConnection(conName);

        if(database == nullptr)
        {
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }

        QSqlQuery queryRemove = database->exec(sql.arg(seq));

        if(queryRemove.lastError().isValid())
        {
            qDebug() << database->lastError().text();
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }
    }
    catch(int ex)
    {
        qDebug() << "[removeDeviceConnectionInfo] occured exception";
        return (EnumDefine::DatabaseErrorType)ex;
    }

    return EnumDefine::DatabaseErrorType::DB_NONE_ERROR;
#endif
}

QList<DeviceConnectionInfo> DatabaseHelper::findAllConnectionInfo(QString conName)
{
#ifdef OS_WINDOW
    QList<DeviceConnectionInfo> retList;
    DeviceConnectionInfo dci;
    dci.mIp = "192.168.0.141";
    dci.mPort = 10020;
    dci.mSeq = 0;

    retList.append(dci);

    return retList;
#else
    QString sql = "SELECT * FROM public.tb_device_connection_info;";
    QList<DeviceConnectionInfo> retList;

    try {

        QSqlDatabase *database = getDatabaseConnection(conName);

        if(database == nullptr)
        {
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }

        QSqlQuery query(*database);
        query.prepare(sql);
        query.exec();

        while(query.next())
        {
            QSqlRecord record = query.record();
            DeviceConnectionInfo connectionInfo = recordToDeviceConnectionInfo(&record);

            retList.append(connectionInfo);
        }
    }
    catch(int ex)
    {
        qDebug() << "[findAllConnectionInfo] occured exception";
    }

    return retList;
#endif
}

DeviceConnectionInfo DatabaseHelper::recordToDeviceConnectionInfo(QSqlRecord * record)
{
    DeviceConnectionInfo ret;

    ret.mSeq    = record->value("seq").toUInt();
    ret.mIp     = record->value("ip").toString();
    ret.mPort   = record->value("port").toUInt();

    return ret;
}

EnumDefine::DatabaseErrorType   DatabaseHelper::addProductSetting(QString conName, ProductSetting * productSetting)
{
#ifdef OS_WINDOW
    productSetting->mSeq = 0;
    return EnumDefine::DatabaseErrorType::DB_NONE_ERROR;
#else
    QString noExistCheckSql = "SELECT * FROM public.tb_device_product_setting WHERE no = %1;";
    QString sql = "INSERT INTO public.tb_device_product_setting(is_select, no, name, length, speed, motor_acceleration_time, under_weight, under_warning_weight, normal_weight, over_warning_weight, over_weight, tare_weight, weight_ng_motion, metaldetector_senstivity, metaldetector_ng_motion, average_n) VALUES (\
                                                                       %1, %2, '%3',     %4,    %5,                      %6,           %7,                   %8,             %9,                %10,         %11,         %12,              %13,                      %14,                     %15,       %16);";

    try {

        QSqlDatabase *database = getDatabaseConnection(conName);

        if(database == nullptr)
        {
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }

        QSqlQuery queryNoCheck(*database);
        queryNoCheck.prepare(noExistCheckSql.arg(productSetting->mNo));
        queryNoCheck.exec();

        if(queryNoCheck.size() > 0)
        {
            throw (int)EnumDefine::DatabaseErrorType::ALREADY_NO_ERROR;
        }

        QSqlQuery queryInsert = database->exec(sql.arg(productSetting->mSelected ? "true" : "false")
                                                  .arg(productSetting->mNo)
                                                  .arg(productSetting->mName)
                                                  .arg(productSetting->mLength)
                                                  .arg(productSetting->mSpeed)
                                                  .arg(productSetting->mMotorAccelerationTime)
                                                  .arg(productSetting->mUnderWeight)
                                                  .arg(productSetting->mUnderWarningWeight)
                                                  .arg(productSetting->mNormalWeight)
                                                  .arg(productSetting->mOverWarningWeight)
                                                  .arg(productSetting->mOverWeight)
                                                  .arg(productSetting->mTareWeight)
                                                  .arg(productSetting->mWCNGMotion)
                                                  .arg(productSetting->mMDSenstivity)
                                                  .arg(productSetting->mMDNGMotion)
                                                  .arg(productSetting->mAverageN));

        if(queryInsert.lastError().isValid())
        {
            qDebug() << database->lastError().text();
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }

        productSetting->mSeq = queryInsert.lastInsertId().toUInt();

    }
    catch(int ex)
    {
        qDebug() << "[addProductSetting] occured exception";
        return (EnumDefine::DatabaseErrorType)ex;
    }

    return EnumDefine::DatabaseErrorType::DB_NONE_ERROR;
#endif
}
EnumDefine::DatabaseErrorType   DatabaseHelper::editProductSetting(QString conName, ProductSetting productSetting)
{
#ifdef OS_WINDOW
    return EnumDefine::DatabaseErrorType::DB_NONE_ERROR;
#else
    QString seqExistCheckSql = "SELECT * FROM public.tb_device_product_setting WHERE seq = %1;";
    QString noExistCheckSql = "SELECT * FROM public.tb_device_product_setting WHERE seq != %1 and no = %2;";
    QString sql = "UPDATE public.tb_device_product_setting SET is_select=%1, no=%2, name='%3', length=%4, speed=%5, motor_acceleration_time=%6, under_weight=%7, under_warning_weight=%8, normal_weight=%9, over_warning_weight=%10, over_weight=%11, tare_weight=%12, weight_ng_motion=%13, metaldetector_senstivity=%14, metaldetector_ng_motion=%15, average_n=%16 WHERE seq = %17";

    try {

        QSqlDatabase *database = getDatabaseConnection(conName);

        if(database == nullptr)
        {
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }

        QSqlQuery querySeqCheck(*database);
        querySeqCheck.prepare(seqExistCheckSql.arg(productSetting.mSeq));
        querySeqCheck.exec();

        if(querySeqCheck.size() < 1)
        {
            throw (int)EnumDefine::DatabaseErrorType::NOT_EXIST_SEQ;
        }

        QSqlQuery queryNoCheck(*database);
        queryNoCheck.prepare(noExistCheckSql.arg(productSetting.mNo));
        queryNoCheck.exec();

        if(queryNoCheck.size() > 0)
        {
            throw (int)EnumDefine::DatabaseErrorType::ALREADY_NO_ERROR;
        }


        QSqlQuery queryEdit = database->exec(sql.arg(productSetting.mSelected ? "true" : "false")
                                                  .arg(productSetting.mNo)
                                                  .arg(productSetting.mName)
                                                  .arg(productSetting.mLength)
                                                  .arg(productSetting.mSpeed)
                                                  .arg(productSetting.mMotorAccelerationTime)
                                                  .arg(productSetting.mUnderWeight)
                                                  .arg(productSetting.mUnderWarningWeight)
                                                  .arg(productSetting.mNormalWeight)
                                                  .arg(productSetting.mOverWarningWeight)
                                                  .arg(productSetting.mOverWeight)
                                                  .arg(productSetting.mTareWeight)
                                                  .arg(productSetting.mWCNGMotion)
                                                  .arg(productSetting.mMDSenstivity)
                                                  .arg(productSetting.mMDNGMotion)
                                                  .arg(productSetting.mAverageN)
                                                  .arg(productSetting.mSeq));

        if(queryEdit.lastError().isValid())
        {
            qDebug() << database->lastError().text();
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }
    }
    catch(int ex)
    {
        qDebug() << "[editProductSetting] occured exception";
        return (EnumDefine::DatabaseErrorType)ex;
    }

    return EnumDefine::DatabaseErrorType::DB_NONE_ERROR;
#endif
}

EnumDefine::DatabaseErrorType DatabaseHelper::selectProductSetting(QString conName, quint16 seq)
{
#ifdef OS_WINDOW
    return EnumDefine::DatabaseErrorType::DB_NONE_ERROR;
#else
    QString seqExistCheckSql = "SELECT * FROM public.tb_device_product_setting WHERE seq = %1;";
    QString sql = "UPDATE public.tb_device_product_setting SET is_select=false; UPDATE public.tb_device_product_setting SET is_select=true WHERE seq = %1;";

    try {

        QSqlDatabase *database = getDatabaseConnection(conName);

        if(database == nullptr)
        {
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }

        QSqlQuery querySeqCheck(*database);
        querySeqCheck.prepare(seqExistCheckSql.arg(seq));
        querySeqCheck.exec();

        if(querySeqCheck.size() < 1)
        {
            throw (int)EnumDefine::DatabaseErrorType::NOT_EXIST_SEQ;
        }

        QSqlQuery query = database->exec(sql.arg(seq));

        if(query.lastError().isValid())
        {
            qDebug() << database->lastError().text();
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }
    }
    catch(int ex)
    {
        qDebug() << "[selectProductSetting] occured exception";
        return (EnumDefine::DatabaseErrorType)ex;
    }

    return EnumDefine::DatabaseErrorType::DB_NONE_ERROR;
#endif
}

EnumDefine::DatabaseErrorType   DatabaseHelper::removeProductSetting(QString conName, quint16 seq)
{
#ifdef OS_WINDOW
    return EnumDefine::DatabaseErrorType::DB_NONE_ERROR;
#else
    QString seqExistCheckSql = "SELECT * FROM public.tb_device_product_setting WHERE seq = %1;";
    QString sql = "DELETE FROM public.tb_device_product_setting WHERE seq = %1;";

    try {

        QSqlDatabase *database = getDatabaseConnection(conName);

        if(database == nullptr)
        {
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }

        QSqlQuery querySeqCheck(*database);
        querySeqCheck.prepare(seqExistCheckSql.arg(seq));
        querySeqCheck.exec();

        if(querySeqCheck.size() < 1)
        {
            throw (int)EnumDefine::DatabaseErrorType::NOT_EXIST_SEQ;
        }

        querySeqCheck.next();

        QSqlRecord record = querySeqCheck.record();

        if(record.value("is_select").toBool())
        {
            throw (int)EnumDefine::DatabaseErrorType::REMOVE_SEL_PRODUCT;
        }

        QSqlQuery queryRemove = database->exec(sql.arg(seq));

        if(queryRemove.lastError().isValid())
        {
            qDebug() << database->lastError().text();
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }
    }
    catch(int ex)
    {
        qDebug() << "[removeProductSetting] occured exception";
        return (EnumDefine::DatabaseErrorType)ex;
    }

    return EnumDefine::DatabaseErrorType::DB_NONE_ERROR;
#endif
}

QList<ProductSetting> DatabaseHelper::findAllProductSetting(QString conName){
#ifdef OS_WINDOW
    QList<ProductSetting> retList;
    ProductSetting ps;
    ps.mSeq = 0;
    ps.mSelected = true;
    retList.append(ps);

#else
    QString sql = "SELECT * FROM public.tb_device_product_setting ORDER BY no ASC;";
    QList<ProductSetting> retList;

    try {

        QSqlDatabase *database = getDatabaseConnection(conName);

        if(database == nullptr)
        {
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }

        QSqlQuery query(*database);
        query.prepare(sql);
        query.exec();

        while(query.next())
        {
            QSqlRecord record = query.record();
            ProductSetting connectionInfo = recordToProductSetting(&record);

            retList.append(connectionInfo);
        }
    }
    catch(int ex)
    {
        qDebug() << "[findAllProductSetting] occured exception";
    }

    return retList;
#endif
}

ProductSetting DatabaseHelper::findSelectedProductSetting(QString conName){
#ifdef OS_WINDOW
    ProductSetting ps;
    ps.mSeq = 0;
    ps.mSelected = true;

    return ps;

#else
    QList<ProductSetting> list;
    ProductSetting        ret;
    ret.mSelected = true;

    try {

        list = findAllProductSetting(conName);

        if(list.size() < 1)
        {
            throw 1;
        }

        for(int i = 0; i < list.size(); i ++)
        {
            if(list.at(i).mSelected == true)
                return list.at(i);
        }

        selectProductSetting(conName, list.at(0).mSeq);

        return list.at(0);
    }
    catch(int ex)
    {
        if(ex == 1)
        {
            qDebug() << "[findSelectedProductSetting] product size is 0";
        }
        else
        {
            qDebug() << "[findSelectedProductSetting] occured exception";
        }
    }

    return ret;
#endif
}

ProductSetting DatabaseHelper::newProductSetting(QString conName){
#ifdef OS_WINDOW
    ProductSetting ps;
    ps.mSeq = 0xffff;

    return ps;

#else
    QString sql = "SELECT * FROM public.tb_device_product_setting ORDER BY no ASC;";
    quint16 newProductNo = 1;

    ProductSetting newProductSetting;

    try {

        QSqlDatabase *database = getDatabaseConnection(conName);

        if(database == nullptr)
        {
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }

        QSqlQuery query(*database);
        query.prepare(sql);
        query.exec();

        while(query.next())
        {
            QSqlRecord record = query.record();
            newProductSetting = recordToProductSetting(&record);

            if(newProductNo  == newProductSetting.mNo)
            {
                newProductNo++;
            }
        }

        newProductSetting.mNo = newProductNo;
    }
    catch(int ex)
    {
        qDebug() << "[newProductSetting] occured exception";
    }

    return newProductSetting;
#endif
}

ProductSetting DatabaseHelper::recordToProductSetting(QSqlRecord * record)
{
    ProductSetting ret;

    ret.mSeq                   = record->value("seq").toUInt();
    ret.mSelected              = record->value("is_select").toBool();
    ret.mNo                    = record->value("no").toUInt();
    ret.mName                  = record->value("name").toString();
    ret.mLength                = record->value("length").toUInt();
    ret.mSpeed                 = record->value("speed").toUInt();
    ret.mMotorAccelerationTime = record->value("motor_acceleration_time").toUInt();
    ret.mUnderWeight           = record->value("under_weight").toUInt();
    ret.mUnderWarningWeight    = record->value("under_warning_weight").toUInt();
    ret.mNormalWeight          = record->value("normal_weight").toUInt();
    ret.mOverWarningWeight     = record->value("over_warning_weight").toUInt();
    ret.mOverWeight            = record->value("over_weight").toUInt();
    ret.mTareWeight            = record->value("tare_weight").toUInt();
    ret.mWCNGMotion            = (EnumDefine::NGMotion)record->value("weight_ng_motion").toUInt();
    ret.mMDSenstivity          = record->value("metaldetector_senstivity").toUInt();
    ret.mMDNGMotion            = (EnumDefine::NGMotion)record->value("metaldetector_ng_motion").toUInt();
    ret.mAverageN              = record->value("average_n").toInt();

    return ret;
}

EnumDefine::DatabaseErrorType DatabaseHelper::addEvent(QString conName, Event * event)
{
#ifdef OS_WINDOW
    event->mSeq = 0;
    return EnumDefine::DatabaseErrorType::DB_NONE_ERROR;
#else
    QString delSql = "DELETE FROM public.tb_event WHERE seq = %1";
    QString sql = "INSERT INTO public.tb_event(\
                   device_seq, year, month, day, hour, min, sec, msec, prog_start_event_seq, work_start_year, work_start_month, work_start_day, event_type, product_setting_seq, product_no, product_name, device_id, under_weight, under_warning_weight, normal_weight, over_warning_weight, over_weight, tare_weight, md_senstivity, weight, datetime)VALUES (\
                   %1,           %2,    %3,  %4,   %5,  %6,  %7,   %8,                   %9,             %10,              %11,            %12,        %13,                 %14,        %15,         '%16',       %17,          %18,                 %19,            %20,                 %21,         %22,         %23,           %24,   %25,    '%26');";

    try {

        qDebug() << "[addEvent]start";

        QString dateTimeFmt("%1/%2/%3 %4:%5:%6");
        QString dateTime = dateTimeFmt.arg(event->mYear).arg(event->mMonth).arg(event->mDay).arg(event->mHour).arg(event->mMin).arg(event->mSec);
        QSqlDatabase *database = getDatabaseConnection(conName);

        if(database == nullptr)
        {
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }

        QSqlQuery queryInsert = database->exec(sql.arg(event->mDeviceSeq         )
                                                  .arg(event->mYear              )
                                                  .arg(event->mMonth             )
                                                  .arg(event->mDay               )
                                                  .arg(event->mHour              )
                                                  .arg(event->mMin               )
                                                  .arg(event->mSec               )
                                                  .arg(event->mMsec              )
                                                  .arg(event->mProgStartEventSeq )
                                                  .arg(event->mWorkStartYear     )
                                                  .arg(event->mWorkStartMonth    )
                                                  .arg(event->mWorkStartDay      )
                                                  .arg(event->mEventType         )
                                                  .arg(event->mProductSettingSeq )
                                                  .arg(event->mProductNo         )
                                                  .arg(event->mProductName       )
                                                  .arg(event->mDeviceID          )
                                                  .arg(event->mUnderWeight       )
                                                  .arg(event->mUnderWarningWeight)
                                                  .arg(event->mNormalWeight      )
                                                  .arg(event->mOverWarningWeight )
                                                  .arg(event->mOverWeight        )
                                                  .arg(event->mTareWeight        )
                                                  .arg(event->mMDSenstivity      )
                                                  .arg(event->mWeight            )
                                                  .arg(dateTime));

        if(queryInsert.lastError().isValid())
        {
            qDebug() << database->lastError().text();
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }

        event->mSeq = queryInsert.lastInsertId().toULongLong();


        if(event->mSeq > mMaxEventCount)
            QSqlQuery queryDelete = database->exec(delSql.arg(event->mSeq - mMaxEventCount));

        if(queryInsert.lastError().isValid())
        {
            qDebug() << database->lastError().text();
        }

        qDebug() << "[addEvent]end";

    }
    catch(int ex)
    {
        qDebug() << "[addProductSetting] occured exception";
        return (EnumDefine::DatabaseErrorType)ex;
    }

    return EnumDefine::DatabaseErrorType::DB_NONE_ERROR;
#endif
}
void DatabaseHelper::addEventToTempFile(QString conName, Event event)
{
    /*
#ifdef OS_WINDOW
    return;
#else
    mTempFileMutex.lock();

    mTempFileRecordCnt ++;

    try {

        if(mTempFile.isOpen() == false)
        {
            openTempFile();
        }

        if(mTempFile.isOpen() == false)
            throw 0;

        mTempOut << event.mDeviceSeq          << ",";
        mTempOut << event.mYear               << ",";
        mTempOut << event.mMonth              << ",";
        mTempOut << event.mDay                << ",";
        mTempOut << event.mHour               << ",";
        mTempOut << event.mMin                << ",";
        mTempOut << event.mSec                << ",";
        mTempOut << event.mMsec               << ",";
        mTempOut << event.mProgStartEventSeq  << ",";
        mTempOut << event.mWorkStartYear      << ",";
        mTempOut << event.mWorkStartMonth     << ",";
        mTempOut << event.mWorkStartDay       << ",";
        mTempOut << event.mEventType          << ",";
        mTempOut << event.mProductSettingSeq  << ",";
        mTempOut << event.mProductNo          << ",";
        mTempOut << event.mProductName        << ",";
        mTempOut << event.mDeviceID           << ",";
        mTempOut << event.mUnderWeight        << ",";
        mTempOut << event.mUnderWarningWeight << ",";
        mTempOut << event.mNormalWeight       << ",";
        mTempOut << event.mOverWarningWeight  << ",";
        mTempOut << event.mOverWeight         << ",";
        mTempOut << event.mTareWeight         << ",";
        mTempOut << event.mMDSenstivity       << ",";
        mTempOut << event.mWeight             << "\n";

        mTempOut.flush();
    }
    catch(int ex)
    {
        qDebug() << "[addEventToTempFile] occured exception";
    }

    mTempFileMutex.unlock();

    // 한꺼번에 옮길 경우 시간이 너무 지체될수 있으므로 수시로 DB로 데이터를 옮긴다.
    if(mTempFileRecordCnt > 500)
    {
        restoreEventFromTempFile(conName);
    }
#endif
*/
}

QList<Event> DatabaseHelper::findAllEventAfterSeq(QString conName, quint64 seq)
{
    QString sql = "SELECT * FROM public.tb_event WHERE seq > %1 ORDER BY seq ASC;";
    QList<Event> retList;
#ifdef OS_WINDOW
    return retList;
#else
    restoreEventFromTempFile(conName);

    try {

        QSqlDatabase *database = getDatabaseConnection(conName);

        if(database == nullptr)
        {
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }

        QSqlQuery query(*database);
        query.prepare(sql.arg(seq));
        query.exec();

        while(query.next())
        {
            QSqlRecord record = query.record();
            Event event = recordToEvent(&record);

            retList.append(event);
        }
    }
    catch(int ex)
    {
        qDebug() << "[findAllEventByDate] occured exception";
    }

    return retList;
#endif
}

QList<Event> DatabaseHelper::findAllEventByPeriod(QString conName, bool isTotal, bool isWeightEvent, int startYear, int startMonth, int startDay, int startHour, int endYear, int endMonth, int endDay, int endHour, int cntPerPage, quint64 pageIdx, quint64 * outTotalCnt, quint64 * outTotalPage)
{
#ifdef OS_WINDOW
    QList<Event> retList;
    return retList;
#else
    quint64 totalCnt = 0;
    //int minEventType = 0;
    //int maxEventType = 0;
    //int withoutEventType = 100;
    QString strWhere;
    QString countSql = "SELECT COUNT(*) FROM public.tb_event WHERE datetime >= '%1/%2/%3 %4:00:00' and datetime <= '%5/%6/%7 %8:59:59' and %9;";    // event_type >= %9 and event_type <= %10 and event_type != %11;";
    QString searchSql = "SELECT * FROM public.tb_event WHERE datetime >= '%1/%2/%3 %4:00:00' and datetime <= '%5/%6/%7 %8:59:59' and %9 ORDER BY seq DESC LIMIT %10 OFFSET %11;";
    QList<Event> retList;

    *outTotalPage = 0;
    *outTotalCnt = 0;

    if(isWeightEvent)
    {
        QString strWCWhereFmt("(event_type >= %1 and event_type <= %2 and event_type != %3) or event_type = %4");

        if(isTotal)
        {
            strWhere = strWCWhereFmt.arg((int)EnumDefine::EventType::WEIGHT_NORMAL_TYPE)
                                    .arg((int)EnumDefine::EventType::STOP_TYPE)
                                    .arg((int)EnumDefine::EventType::METAL_CHECKUP_TYPE)
                                    .arg((int)EnumDefine::EventType::WEIGHT_ETC_METAL_ERROR_TYPE);
        }
        else
        {
            strWhere = strWCWhereFmt.arg((int)EnumDefine::EventType::WEIGHT_UNDER_WARNING_TYPE)
                                    .arg((int)EnumDefine::EventType::STOP_TYPE)
                                    .arg((int)EnumDefine::EventType::METAL_CHECKUP_TYPE)
                                    .arg((int)EnumDefine::EventType::WEIGHT_ETC_METAL_ERROR_TYPE);
        }
    }
    else
    {
        QString strMDWhereFmt("event_type >= %1 and event_type <= %2 and event_type != %3 and event_type != %4 and event_type != %5");

        if(isTotal)
        {
            strWhere = strMDWhereFmt.arg((int)EnumDefine::EventType::APP_START_TYPE)
                                    .arg((int)EnumDefine::EventType::METAL_DETECT_TYPE)
                                    .arg((int)EnumDefine::EventType::WEIGHT_STATIC_CARI_TYPE)
                                    .arg((int)EnumDefine::EventType::WEIGHT_DYNAMIC_CARI_TYPE)
                                    .arg((int)EnumDefine::EventType::WEIGHT_NORMAL_TYPE);
        }
        else
        {
            strWhere = strMDWhereFmt.arg((int)EnumDefine::EventType::APP_START_TYPE)
                                    .arg((int)EnumDefine::EventType::METAL_DETECT_TYPE)
                                    .arg((int)EnumDefine::EventType::WEIGHT_STATIC_CARI_TYPE)
                                    .arg((int)EnumDefine::EventType::WEIGHT_DYNAMIC_CARI_TYPE)
                                    .arg((int)EnumDefine::EventType::METAL_TRADE_TYPE);
        }
    }

    restoreEventFromTempFile(conName);

    try {

        QSqlDatabase *database = getDatabaseConnection(conName);

        if(database == nullptr)
        {
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }

        QSqlQuery countQuery(*database);
        countQuery.prepare(countSql.arg(startYear )
                                   .arg(startMonth)
                                   .arg(startDay  )
                                   .arg(startHour )
                                   .arg(endYear   )
                                   .arg(endMonth  )
                                   .arg(endDay    )
                                   .arg(endHour   )
                                   .arg(strWhere  ));
        countQuery.exec();

        if(countQuery.size() < 1)
        {
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }

        countQuery.next();

        totalCnt = countQuery.record().value("count").toULongLong();

        *outTotalCnt = totalCnt;
        totalCnt = totalCnt < 1 ? 0 : totalCnt - 1;

        *outTotalPage = (totalCnt / cntPerPage) + 1;

        //qDebug() << searchSql.arg(startYear).arg(endYear).arg(startMonth).arg(endMonth).arg(startDay).arg(endDay).arg(startHour).arg(endHour).arg(strWhere).arg(cntPerPage).arg(pageIdx * cntPerPage);
        QSqlQuery searchQuery(*database);
        searchQuery.prepare(searchSql.arg(startYear )
                                     .arg(startMonth)
                                     .arg(startDay  )
                                     .arg(startHour )
                                     .arg(endYear   )
                                     .arg(endMonth  )
                                     .arg(endDay    )
                                     .arg(endHour   )
                                     .arg(strWhere  )
                                     .arg(cntPerPage)
                                     .arg(pageIdx * cntPerPage));

        searchQuery.exec();


        while(searchQuery.next())
        {
            QSqlRecord record = searchQuery.record();
            Event event = recordToEvent(&record);

            retList.append(event);
        }
    }
    catch(int ex)
    {
        qDebug() << "[findAllEventByPeriod] occured exception";
    }

    return retList;
#endif
}

quint64 DatabaseHelper::findLastEventSeq(QString conName)
{
#ifdef OS_WINDOW
    return 0;
#else
    QString sql = "SELECT * FROM public.tb_event ORDER BY seq DESC LIMIT 1;";
    Event event;

    restoreEventFromTempFile(conName);

    try {

        QSqlDatabase *database = getDatabaseConnection(conName);

        if(database == nullptr)
        {
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }

        QSqlQuery query(*database);
        query.prepare(sql);
        query.exec();

        while(query.next())
        {
            QSqlRecord record = query.record();
            return record.value("seq").toULongLong();
        }
    }
    catch(int ex)
    {
        qDebug() << "[findAllEventByDate] occured exception";
    }

    return 0;
#endif
}

Event DatabaseHelper::recordToEvent(QSqlRecord * record)
{
    Event ret;

    ret.mSeq                = record->value("seq").toULongLong();
    ret.mDeviceSeq          = record->value("device_seq").toUInt();
    ret.mYear               = record->value("year").toUInt();
    ret.mMonth              = record->value("month").toUInt();
    ret.mDay                = record->value("day").toUInt();
    ret.mHour               = record->value("hour").toUInt();
    ret.mMin                = record->value("min").toUInt();
    ret.mSec                = record->value("sec").toUInt();
    ret.mMsec               = record->value("msec").toUInt();
    ret.mProgStartEventSeq  = record->value("prog_start_event_seq").toULongLong();
    ret.mWorkStartYear      = record->value("work_start_year").toUInt();
    ret.mWorkStartMonth     = record->value("work_start_month").toUInt();
    ret.mWorkStartDay       = record->value("work_start_day").toUInt();
    ret.mEventType          = (EnumDefine::EventType)record->value("event_type").toUInt();
    ret.mProductSettingSeq  = record->value("product_setting_seq").toUInt();
    ret.mProductNo          = record->value("product_no").toUInt();
    ret.mProductName        = record->value("product_name").toString();
    ret.mDeviceID           = record->value("device_id").toUInt();
    ret.mUnderWeight        = record->value("under_weight").toUInt();
    ret.mUnderWarningWeight = record->value("under_warning_weight").toUInt();
    ret.mNormalWeight       = record->value("normal_weight").toUInt();
    ret.mOverWarningWeight  = record->value("over_warning_weight ").toUInt();
    ret.mOverWeight         = record->value("over_weight").toUInt();
    ret.mTareWeight         = record->value("tare_weight").toUInt();
    ret.mMDSenstivity       = record->value("md_senstivity").toUInt();
    ret.mWeight             = record->value("weight").toUInt();

    return ret;
}

void DatabaseHelper::restoreEventFromTempFile(QString conName)
{/*
    mTempFileMutex.lock();

    mTempFileRecordCnt = 0;

    closeTempFile();

    QString applicationPath = QApplication::applicationDirPath();
    QString sql = "copy tb_event(device_seq, year, month, day, hour, min, sec, msec, prog_start_event_seq, work_start_year, work_start_month, work_start_day, event_type, product_setting_seq, product_no, product_name, device_id, under_weight, under_warning_weight, normal_weight, over_warning_weight, over_weight, tare_weight, md_senstivity, weight) from '%1/db_temp/event.dat' with delimiter ','";

    QFile checkFile("db_temp/event.dat");

    if(checkFile.size() == 0)
    {
        mTempFileMutex.unlock();
        return;
    }

    if(checkFile.size() < 10)
    {
        checkFile.resize(0);
        mTempFileMutex.unlock();
        return;
    }

    try {

        QSqlDatabase *database = getDatabaseConnection(conName);

        if(database == nullptr)
        {
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }

        QSqlQuery query = database->exec(sql.arg(applicationPath));

        if(query.lastError().isValid())
        {
            qDebug() << database->lastError().text();
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }
    }
    catch(int ex)
    {
        mTempFileMutex.unlock();
        qDebug() << "[restoreEventFromTempFile] occured exception";
        return ;
    }

    checkFile.resize(0);

    mTempFileMutex.unlock();
    */
}

void DatabaseHelper::backup(QString conName, DatabaseBackupState * backupState)
{
    quint64 startSeq;
    quint64 endSeq;
    quint64 progressCnt = 0;
#ifdef OS_WINDOW
    backupState->setResult(EnumDefine::BackupResult::BACKUP_NONE_ERROR);
#else
    backupState->setResult(EnumDefine::BackupResult::BACKUP_UNKNOW_ERROR);

    restoreEventFromTempFile(conName);

    if(QFile::exists("/dev/sda1") == false)
    {
        backupState->setResult(EnumDefine::BackupResult::USB_ERROR);
        return;
    }

    QString currTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
    QString fileName = "/home/pi/usb/event_backup_%1.dat";

    if(QFile::exists(fileName.arg(currTime)))
    {
        QFile::remove(fileName.arg(currTime));
    }

    QFile file(fileName.arg(currTime));
    QTextStream outStream;

    file.open(QIODevice::WriteOnly | QIODevice::Text);
    outStream.setDevice(&file);

    QString endSeqSql   = "SELECT seq FROM public.tb_event WHERE '%1/%2/%3 0:0:0' <= datetime and '%4/%5/%6 23:59:59' >= datetime ORDER BY seq DESC LIMIT 1;";
    QString startSeqSql = "SELECT seq FROM public.tb_event WHERE '%1/%2/%3 0:0:0' <= datetime and '%4/%5/%6 23:59:59' >= datetime ORDER BY seq ASC LIMIT 1;";
    QString searchSql   = "SELECT *   FROM public.tb_event WHERE seq >= %1 and seq <= %2 ORDER BY seq ASC;";

    try {

        QSqlDatabase *database = getDatabaseConnection(conName);

        if(database == nullptr)
        {
            backupState->setResult(EnumDefine::BackupResult::DB_OPEN_FAIL);
            throw 0;
        }

        QSqlQuery startSeqQuery(*database);
        startSeqQuery.prepare(startSeqSql.arg(backupState->getBackupProcStartYear ())
                                     .arg(backupState->getBackupProcStartMonth())
                                     .arg(backupState->getBackupProcStartDay  ())
                                     .arg(backupState->getBackupProcEndYear   ())
                                     .arg(backupState->getBackupProcEndMonth  ())
                                     .arg(backupState->getBackupProcEndDay    ()));


        startSeqQuery.exec();

        if(startSeqQuery.size() < 1)
        {
            backupState->setResult(EnumDefine::BackupResult::READ_ERROR);
            throw 0;
        }

        startSeqQuery.next();
        startSeq = startSeqQuery.record().value("seq").toULongLong();

        QSqlQuery endSeqQuery(*database);
        endSeqQuery.prepare(endSeqSql.arg(backupState->getBackupProcStartYear ())
                                   .arg(backupState->getBackupProcStartMonth())
                                   .arg(backupState->getBackupProcStartDay  ())
                                   .arg(backupState->getBackupProcEndYear   ())
                                   .arg(backupState->getBackupProcEndMonth  ())
                                   .arg(backupState->getBackupProcEndDay    ()));
        endSeqQuery.exec();

        if(endSeqQuery.size() < 1)
        {
            backupState->setResult(EnumDefine::BackupResult::READ_ERROR);
            throw 0;
        }

        endSeqQuery.next();
        endSeq = endSeqQuery.record().value("seq").toULongLong();

        backupState->setTotalCount(endSeq - startSeq);

        QSqlQuery searchQuery(*database);

        searchQuery.exec();

        outStream << "{\"device_id\":\""     << backupState->getHMISerialNumber() << "\"";
        outStream << ",\"device_number\":" << backupState->getHMIDeviceNumber();
        outStream << ",\"start_year\":"    << backupState->getBackupProcStartYear();
        outStream << ",\"start_month\":"   << backupState->getBackupProcStartMonth();
        outStream << ",\"start_day\":"     << backupState->getBackupProcStartDay();
        outStream << ",\"end_year\":"      << backupState->getBackupProcEndYear();
        outStream << ",\"end_month\":"     << backupState->getBackupProcEndMonth();
        outStream << ",\"end_day\":"       << backupState->getBackupProcEndDay();
        outStream << ",\"total_count\":"   << backupState->getTotalCount() << "}\n";
        outStream.flush();

        for(quint64 seq = startSeq; seq < endSeq + 1; seq += 100)
        {
            if(backupState->getIsCancle() == true)
            {
                file.close();
                backupState->setResult(EnumDefine::BackupResult::BACKUP_CANCLE);
                return;
            }

            quint64 tempEndSeq = seq + 99;
            if(tempEndSeq > endSeq)
            {
                tempEndSeq = endSeq;
            }

            QSqlQuery searchQuery(*database);
            searchQuery.prepare(searchSql.arg(seq).arg(tempEndSeq));

            searchQuery.exec();

            if(searchQuery.size() < 1)
            {
                continue;
            }

            while(searchQuery.next())
            {
                QSqlRecord record = searchQuery.record();

                backupState->setEndSeq(record.value("seq").toULongLong());

                outStream << "{\"seq\":"                 << record.value("seq").toULongLong();
                outStream << ",\"datetime\":\""          << record.value("datetime").toString() << "\"";
                outStream << ",\"device_seq\":"          << record.value("device_seq").toUInt();
                outStream << ",\"year\":"                << record.value("year").toUInt();
                outStream << ",\"month\":"               << record.value("month").toUInt();
                outStream << ",\"day\":"                 << record.value("day").toUInt();
                outStream << ",\"hour\":"                << record.value("hour").toUInt();
                outStream << ",\"min\":"                 << record.value("min").toUInt();
                outStream << ",\"sec\":"                 << record.value("sec").toUInt();
                outStream << ",\"msec\":"                << record.value("msec").toUInt();
                outStream << ",\"prog_start_event_seq\":"<< record.value("prog_start_event_seq").toULongLong();
                outStream << ",\"work_start_year\":"     << record.value("work_start_year").toUInt();
                outStream << ",\"work_start_month\":"    << record.value("work_start_month").toUInt();
                outStream << ",\"work_start_day\":"      << record.value("work_start_day").toUInt();
                outStream << ",\"event_type\":"          << record.value("event_type").toUInt();
                outStream << ",\"product_setting_seq\":" << record.value("product_setting_seq").toUInt();
                outStream << ",\"product_no\":"          << record.value("product_no").toUInt();
                outStream << ",\"product_name\":\""      << record.value("product_name").toString() << "\"";
                outStream << ",\"device_id\":"           << record.value("device_id").toUInt();
                outStream << ",\"under_weight\":"        << record.value("under_weight").toUInt();
                outStream << ",\"under_warning_weight\":"<< record.value("under_warning_weight").toUInt();
                outStream << ",\"normal_weight\":"       << record.value("normal_weight").toFloat();
                outStream << ",\"over_warning_weight\":" << record.value("over_warning_weight").toUInt();
                outStream << ",\"over_weight\":"         << record.value("over_weight").toUInt();
                outStream << ",\"tare_weight\":"         << record.value("tare_weight").toUInt();
                outStream << ",\"md_senstivity\":"       << record.value("md_senstivity").toUInt();
                outStream << ",\"weight\":"             << record.value("weight").toUInt();
                outStream << "}\n";
                outStream.flush();
            }

            progressCnt = progressCnt + 100;
            backupState->setProgressCount(progressCnt);
        }

        file.close();
        QString cmd;

        cmd.sprintf("sudo umount /home/pi/usb");

        qDebug() << cmd;

        system(cmd.toStdString().c_str());

        backupState->setResult(EnumDefine::BackupResult::BACKUP_NONE_ERROR);
    }
    catch(int ex)
    {
    }
#endif
}

void DatabaseHelper::loggingReset(QString conName)
{
#ifdef OS_WINDOW
#else

    QString sql = "truncate table tb_event restart identity;";

    try {

        QSqlDatabase *database = getDatabaseConnection(conName);

        if(database == nullptr)
        {
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }

        mTempFileMutex.lock();

        closeTempFile();
        QFile checkFile("db_temp/event.dat");
        checkFile.resize(0);

        mTempFileMutex.unlock();

        QSqlQuery queryInsert = database->exec(sql);

        if(queryInsert.lastError().isValid())
        {
            qDebug() << database->lastError().text();
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }
    }
    catch(int ex)
    {
        qDebug() << "[factoryReset] occured exception";
    }
#endif
}

void DatabaseHelper::factoryReset(QString conName)
{
#ifdef OS_WINDOW
#else

    QString sql = "truncate table tb_device_connection_info restart identity;truncate table tb_device_product_setting restart identity;truncate table tb_event restart identity;";

    try {

        QSqlDatabase *database = getDatabaseConnection(conName);

        if(database == nullptr)
        {
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }

        mTempFileMutex.lock();

        closeTempFile();
        QFile checkFile("db_temp/event.dat");
        checkFile.resize(0);

        mTempFileMutex.unlock();

        QSqlQuery queryInsert = database->exec(sql);

        if(queryInsert.lastError().isValid())
        {
            qDebug() << database->lastError().text();
            throw (int)EnumDefine::DatabaseErrorType::SQL_ERROR;
        }

        DeviceConnectionInfo dci;
        dci.mIp = "192.168.0.140";
        dci.mPort = 10020;

        addDeviceConnectionInfo(conName, &dci);

        ProductSetting ps;
        ps.mNo = 1;
        ps.mName = "Product";
        ps.mSelected = true;
        ps.mLength = 220;
        ps.mSpeed = 25;
        ps.mMotorAccelerationTime = 500;
        ps.mUnderWeight = 12000;
        ps.mUnderWarningWeight = 12000;
        ps.mNormalWeight = 14000;
        ps.mOverWarningWeight = 16000;
        ps.mOverWeight = 16000;
        ps.mTareWeight = 0;
        ps.mWCNGMotion = EnumDefine::NGMotion::NG_MOTION_REJECT_02;
        ps.mAverageN = 1;
        ps.mMDSenstivity = 140;
        ps.mMDNGMotion = EnumDefine::NGMotion::NG_MOTION_REJECT_01;

        addProductSetting(conName, &ps);
    }
    catch(int ex)
    {
        qDebug() << "[factoryReset] occured exception";
    }
#endif
}

void DatabaseHelper::openTempFile()
{
    if (QDir("db_temp").exists() == false)
    {
        QDir().mkdir("db_temp");
    }

    QString fileName = "db_temp/event.dat";
    mTempFile.setFileName(fileName);
    mTempFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);

    if(mTempFile.isOpen() == false)
    {
        qDebug() <<  mTempFile.errorString();
        return;
    }

    mTempOut.setDevice(&mTempFile);
}

void DatabaseHelper::closeTempFile()
{
    if(mTempFile.isOpen())
    {
        mTempFile.close();
    }
    mTempOut.setDevice(nullptr);
}
