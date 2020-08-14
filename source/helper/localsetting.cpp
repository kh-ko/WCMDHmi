#include "localsetting.h"

#include <QDebug>
#include <QDateTime>

#include "source/globaldef/GlobalDefine.h"
#include "source/globaldef/EnumDefine.h"

LocalSetting * LocalSetting::mpSelf = nullptr;

LocalSetting *   LocalSetting::getInstance (               ){ return mpSelf;                                        }

LocalSetting::LocalSetting  (QObject *parent) : QObject(parent)
{
    qDebug() << "[LocalSetting] New";
    mpSettings = new QSettings("novasen", "WCMD", this);  mpSelf = this;

    QString oldVersion = mpSettings->value("information/HMIVersion" , "" ).toString();
    mpSettings->setValue("information/HMIVersion" , "1.1.0" ); 
}
LocalSetting::~LocalSetting ()                                  { qDebug() << "[LocalSetting] Delete";  }

void LocalSetting::factoryReset()
{
    mpSettings->clear();
}

void LocalSetting::loggingReset()
{
    QString currTime = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss.zzz");

    mpSettings->setValue("etc/LastTime", "1700/01/01 01:01:01.100");
    setBackupYear  (0);
    setBackupMonth (0);
    setBackupDay   (0);
    setBackupSeq   (0);
    setLastEventSeq(0);
    setWorkStartSeq(0, 0, 0, 0);
}

void LocalSetting::setInformation(Information value)
{
    //mpSettings->setValue("information/Company"    , value.mCompany    );
    //mpSettings->setValue("information/Tel"        , value.mTel        );
    //mpSettings->setValue("information/Model"      , value.mModel      );
    //mpSettings->setValue("information/SN"         , value.mSN         );
    //mpSettings->setValue("information/HMIVersion" , value.mHMIVersion );
    mpSettings->setValue("information/DeviceNumber" , value.mDeviceNumber  );
    mpSettings->setValue("information/DSPVersion" , value.mDspVersion );
    mpSettings->setValue("information/Power"      , value.mPower      );
    mpSettings->setValue("information/Homepage"   , value.mHomepage   );
    mpSettings->setValue("information/MaxWeight"  , value.mMaxWeight  );
    mpSettings->setValue("information/ServerIp"   , value.mServerIp   );
}
void LocalSetting::setDeviceSetting(DeviceSetting value)
{
    mpSettings->setValue("devicesetting/Language"                   , value.mLanguage                   );
    mpSettings->setValue("devicesetting/Password"                   , value.mPassword                   );
    mpSettings->setValue("devicesetting/IsDayMode"                  , value.mIsDayMode                  );
    mpSettings->setValue("devicesetting/LampTime"                   , value.mLampTime                   );
    mpSettings->setValue("devicesetting/BuzzerTime"                 , value.mBuzzerTime                 );
    mpSettings->setValue("devicesetting/SpeedConverter"             , value.mSpeedConverter             );
    mpSettings->setValue("devicesetting/MotorDirection"             , value.mMotorDirection             );
    mpSettings->setValue("devicesetting/IsDebugMode"                , value.mIsDebugMode                );
    mpSettings->setValue("devicesetting/SensorLength"               , value.mSensorLength               );
    mpSettings->setValue("devicesetting/DistanceToRejector"         , value.mDistanceToRejector         );
    mpSettings->setValue("devicesetting/MDPhotoIsOn"                , value.mMDPhotoIsOn                );
    mpSettings->setValue("devicesetting/WCPhotoIsOn"                , value.mWCPhotoIsOn                );
    mpSettings->setValue("devicesetting/RejectorReadyTime"          , value.mRejectorReadyTime          );
    mpSettings->setValue("devicesetting/RejectorRunTimeRatio"       , value.mRejectorRunTimeRatio       );
    mpSettings->setValue("devicesetting/StaticFactor"               , value.mStaticFactor               );
    mpSettings->setValue("devicesetting/DynamicFactor"              , value.mDynamicFactor              );
    mpSettings->setValue("devicesetting/Scaler"                     , value.mScaler                     );
    //mpSettings->setValue("devicesetting/StandardWeightSet"          , value.mStandardWeightSet          );
    mpSettings->setValue("devicesetting/DisplayStability"           , value.mDisplayStability           );
    mpSettings->setValue("devicesetting/MeasureCueSign"             , value.mMeasureCueSign             );
    mpSettings->setValue("devicesetting/MinStaticWeight"            , value.mMinStaticWeight            );
    mpSettings->setValue("devicesetting/MinDynamicWeight"           , value.mMinDynamicWeight           );
    mpSettings->setValue("devicesetting/TrendsGraphOptionH"         , value.mTrendsGraphOptionH         );
    mpSettings->setValue("devicesetting/TrendsGraphOptionFilter"    , value.mTrendsGraphOptionFilter    );
    mpSettings->setValue("devicesetting/TrendsGraphOptionLastN"     , value.mTrendsGraphOptionLastN     );
    mpSettings->setValue("devicesetting/TrendsGraphOptionLastNValue", value.mTrendsGraphOptionLastNValue);
    mpSettings->setValue("devicesetting/Mode"                       , value.mMode                       );
    mpSettings->setValue("devicesetting/DistanceBtwSensor"          , value.mDistanceBtwSensor          );
    mpSettings->setValue("devicesetting/DetectDetectTime"           , value.mDetectDetectTime           );
    mpSettings->setValue("devicesetting/RunDetectTime"              , value.mRunDetectTime              );
    mpSettings->setValue("devicesetting/DistanceToWeightChecker"    , value.mDistanceToWeightChecker    );
    mpSettings->setValue("devicesetting/DistancePhotoToSensor"      , value.mDistancePhotoToSensor      );
    mpSettings->setValue("devicesetting/SignalDelayTime"            , value.mSignalDelayTime            );
    mpSettings->setValue("devicesetting/StaticStandardWeight"       , value.mStaticStandardWeight       );
    mpSettings->setValue("devicesetting/DynamicBaseWeight"          , value.mDynamicBaseWeight          );
    mpSettings->setValue("devicesetting/SensorCnt"                  , value.mSensorCnt                  );
    mpSettings->setValue("devicesetting/mSimpleSenstivity01"        , value.mSimpleSenstivity01         );
    mpSettings->setValue("devicesetting/mSimpleSenstivity02"        , value.mSimpleSenstivity02         );
    mpSettings->setValue("devicesetting/mSimpleSenstivity03"        , value.mSimpleSenstivity03         );
    mpSettings->setValue("devicesetting/mSimpleSenstivity04"        , value.mSimpleSenstivity04         );
    mpSettings->setValue("devicesetting/mSimpleSenstivity05"        , value.mSimpleSenstivity05         );
}
void LocalSetting::setLastDateTime()
{
    QString currTime = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss.zzz");

    mpSettings->setValue("etc/LastTime", currTime);
}
void LocalSetting::setBackupYear (int value)
{
    mpSettings->setValue("backup/year", value);
}
void LocalSetting::setBackupMonth(int value)
{
    mpSettings->setValue("backup/month", value);
}
void LocalSetting::setBackupDay  (int value)
{
    mpSettings->setValue("backup/day", value);
}
void LocalSetting::setBackupSeq   (quint64 value)
{
    mpSettings->setValue("backup/seq", value);
}
void LocalSetting::setLastEventSeq(quint64 value)
{
    mpSettings->setValue("event/lastseq", value);
}
void LocalSetting::setWorkStartSeq(int year, int month, int day, quint64 workStartSeq)
{
    mpSettings->setValue("daymode/year", year);
    mpSettings->setValue("daymode/month", month);
    mpSettings->setValue("daymode/day", day);
    mpSettings->setValue("daymode/workStartSeq", workStartSeq);
}

void LocalSetting::setMainViewIsDetail(bool value)
{
    mpSettings->setValue("mainview/IsDetail", value);
}

void LocalSetting::setWCViewMode(int value)
{
   mpSettings->setValue("mainview/WCViewMode", value);
}

Information     LocalSetting::getInformation()
{
    qDebug() << "getInformation";
    Information info;

#ifdef BUILD_DONGNAM
    info.mCompany      = "DONG NAM MACHINERY SHOP"; //= mpSettings->value("information/Company"      ,"DONG NAM MACHINERY SHOP"     ).toString();
    info.mTel          = "T 053-551-1452";//mpSettings->value("information/Tel"          ,"T 053-551-1452").toString();
    info.mHomepage     = "www.dongnam1998.com"; //mpSettings->value("information/Homepage"     ,"www.dongnam1998.com").toString();
#else
    info.mCompany      = QString("NOVASEN");
    info.mTel          = QString("T 1600-4917");
    info.mHomepage     = QString("www.novasen.com");
#endif
    info.mModel        = "NSWCNSAMD480";
    info.mSN           = QString(QSysInfo::machineUniqueId() );
    info.mDeviceNumber = mpSettings->value("information/DeviceNumber" , 1  ).toInt();
    info.mDspVersion   = mpSettings->value("information/DSPVersion"   ,"").toString();
    info.mHMIVersion   = mpSettings->value("information/HMIVersion" , "" ).toString();
    info.mPower        = mpSettings->value("information/Power"        ,"1% 220VAC 60Hz").toString();

    info.mMaxWeight    = mpSettings->value("information/MaxWeight"    ,10000).toInt();
    info.mServerIp     = mpSettings->value("information/ServerIp"     ,"192.168.0.1").toString();

    return info;

}
DeviceSetting   LocalSetting::getDeviceSetting()
{
    DeviceSetting ds;

    ds.mLanguage                    = (EnumDefine::Language)mpSettings->value("devicesetting/Language", EnumDefine::Language::ENG      ).toInt();
    ds.mPassword                    = mpSettings->value("devicesetting/Password"                   , "1111"                            ).toString();
    ds.mIsDayMode                   = mpSettings->value("devicesetting/IsDayMode"                  , false                             ).toBool();
    ds.mLampTime                    = mpSettings->value("devicesetting/LampTime"                   , 1000                              ).toUInt();
    ds.mBuzzerTime                  = mpSettings->value("devicesetting/BuzzerTime"                 , 1000                              ).toUInt();
    ds.mSpeedConverter              = mpSettings->value("devicesetting/SpeedConverter"             , 2070000                           ).toUInt();
    ds.mMotorDirection              = mpSettings->value("devicesetting/MotorDirection"             , EnumDefine::MOTOR_DIRECTION::MOTOR_DIRECTION_RIGHT_TO_LEFT).toUInt();
    ds.mIsDebugMode                 = mpSettings->value("devicesetting/IsDebugMode"                , false                             ).toBool();
    ds.mSensorLength                = mpSettings->value("devicesetting/SensorLength"               , 540                               ).toUInt();
    ds.mDistanceToRejector          = mpSettings->value("devicesetting/DistanceToRejector"         , 720                               ).toUInt();
    ds.mMDPhotoIsOn                 = mpSettings->value("devicesetting/MDPhotoIsOn"                , true                              ).toBool();
    ds.mWCPhotoIsOn                 = mpSettings->value("devicesetting/WCPhotoIsOn"                , true                              ).toBool();
    ds.mRejectorReadyTime           = mpSettings->value("devicesetting/RejectorReadyTime"          , 100                               ).toUInt();
    ds.mRejectorRunTimeRatio        = mpSettings->value("devicesetting/RejectorRunTimeRatio"       , 500                               ).toUInt();
    ds.mStaticFactor                = mpSettings->value("devicesetting/StaticFactor"               , 3028163                           ).toUInt();
    ds.mDynamicFactor               = mpSettings->value("devicesetting/DynamicFactor"              , 9969342                           ).toUInt();
    ds.mScaler                      = mpSettings->value("devicesetting/Scaler"                     , 200                               ).toUInt();
    //ds.mStandardWeightSet           = mpSettings->value("devicesetting/StandardWeightSet"          , 1000000                           ).toUInt();
    ds.mDisplayStability            = mpSettings->value("devicesetting/DisplayStability"           , 1                                 ).toUInt();
    ds.mMeasureCueSign              = mpSettings->value("devicesetting/MeasureCueSign"             , 300                                ).toUInt();
    ds.mMinStaticWeight             = mpSettings->value("devicesetting/MinStaticWeight"            , 3000                              ).toUInt();
    ds.mMinDynamicWeight            = mpSettings->value("devicesetting/MinDynamicWeight"           , 5000                             ).toUInt();
    ds.mTrendsGraphOptionH          = (EnumDefine::TrendsGraphOptionH)mpSettings->value("devicesetting/TrendsGraphOptionH", EnumDefine::TrendsGraphOptionH::TRENDSOPTION_H_UNDER_TO_OVER).toUInt();
    ds.mTrendsGraphOptionFilter     = (EnumDefine::TrendsGraphOptionFilter)mpSettings->value("devicesetting/TrendsGraphOptionFilter", EnumDefine::TrendsGraphOptionFilter::TRENDSOPTION_FILTER_TOTAL).toUInt();
    ds.mTrendsGraphOptionLastN      = (EnumDefine::TrendsGraphOptionLastN)mpSettings->value("devicesetting/TrendsGraphOptionLastN", EnumDefine::TrendsGraphOptionLastN::TRENDSOPTION_TOTAL_SINCE_START).toUInt();
    ds.mTrendsGraphOptionLastNValue = mpSettings->value("devicesetting/TrendsGraphOptionLastNValue", 100                               ).toUInt();
    ds.mMode                        = (EnumDefine::SensorMode)mpSettings->value("devicesetting/Mode", EnumDefine::SensorMode::INDEPENDENT).toUInt();
    ds.mDistanceBtwSensor           = mpSettings->value("devicesetting/DistanceBtwSensor"          , 180                               ).toUInt();
    ds.mDetectDetectTime            = mpSettings->value("devicesetting/DetectDetectTime"           , 500                               ).toUInt();
    ds.mRunDetectTime               = mpSettings->value("devicesetting/RunDetectTime"              , 1000                              ).toUInt();
    ds.mDistanceToWeightChecker     = mpSettings->value("devicesetting/DistanceToWeightChecker"    , 350                              ).toUInt();
    ds.mDistancePhotoToSensor       = mpSettings->value("devicesetting/DistancePhotoToSensor"      , 250                               ).toUInt();
    ds.mSignalDelayTime             = mpSettings->value("devicesetting/SignalDelayTime"            , 0                                 ).toUInt();
    ds.mStaticStandardWeight        = mpSettings->value("devicesetting/StaticStandardWeight"       , 10000                             ).toUInt();
    ds.mDynamicBaseWeight           = mpSettings->value("devicesetting/DynamicBaseWeight"          , 10000                             ).toUInt();
    ds.mSensorCnt                   = mpSettings->value("devicesetting/SensorCnt"                  , 1                                 ).toUInt();
    ds.mSimpleSenstivity01          = mpSettings->value("devicesetting/mSimpleSenstivity01"        , 0                                 ).toUInt();
    ds.mSimpleSenstivity02          = mpSettings->value("devicesetting/mSimpleSenstivity02"        , 0                                 ).toUInt();
    ds.mSimpleSenstivity03          = mpSettings->value("devicesetting/mSimpleSenstivity03"        , 0                                 ).toUInt();
    ds.mSimpleSenstivity04          = mpSettings->value("devicesetting/mSimpleSenstivity04"        , 0                                 ).toUInt();
    ds.mSimpleSenstivity05          = mpSettings->value("devicesetting/mSimpleSenstivity05"        , 0                                 ).toUInt();

    return ds;
}
QDateTime       LocalSetting::getLastDateTime()
{
    QDateTime date;

    QString dateStr = mpSettings->value("etc/LastTime", "1700/01/01 01:01:01.100").toString();
    date = QDateTime::fromString(dateStr,"yyyy/MM/dd hh:mm:ss.zzz");

    return date;
}
int LocalSetting::getBackupYear()
{
    return mpSettings->value("backup/year", 0).toInt();
}
int LocalSetting::getBackupMonth()
{
    return mpSettings->value("backup/month", 0).toInt();
}
int LocalSetting::getBackupDay()
{
    return mpSettings->value("backup/day", 0).toInt();
}
quint64 LocalSetting::getBackupSeq()
{
    return mpSettings->value("backup/seq", 0).toULongLong();
}
quint64 LocalSetting::getLastEventSeq()
{
    return mpSettings->value("event/lastseq", 0).toULongLong();
}
quint64 LocalSetting::getWorkStartSeq(int year, int month, int day)
{
    int savedYear;
    int savedMonth;
    int savedDay;
    quint64 saveSeq;

    savedYear = mpSettings->value("daymode/year", 0).toInt();
    savedMonth = mpSettings->value("daymode/month", 0).toInt();
    savedDay = mpSettings->value("daymode/day", 0).toInt();
    saveSeq = mpSettings->value("daymode/workStartSeq", 0).toULongLong();

    if(savedYear == year && savedMonth == month && savedDay == day)
    {
        return saveSeq;
    }

    return INVALID_ULONGLONG;
}

bool LocalSetting::getMainViewIsDetail()
{
    return mpSettings->value("mainview/IsDetail", 0).toBool();
}

int LocalSetting::getWCViewMode()
{
   return mpSettings->value("mainview/WCViewMode", EnumDefine::WCViewMode::WC_VIEWMODE_CURRENT).toInt();
}
