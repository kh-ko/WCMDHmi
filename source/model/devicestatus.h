#ifndef DEVICESTATUS_H
#define DEVICESTATUS_H

#include <QObject>

#include "source/globaldef/EnumDefine.h"

class DeviceStatus// : public QObject
{
 //   Q_OBJECT
public:
    quint16                 mWait                        ;
    EnumDefine::RunState    mRun                         ;
    bool                    mIsWeightCheckerGraphOn      ;
    bool                    mIsMetalDetectorGraphOn      ;
    bool                    mIsMetalDetectorFilterGraphOn;
    EnumDefine::AlarmType   mWCAlarm                     ;
    quint32                 mCurrWeight                  ;
    EnumDefine::EventType   mWCErrorType                 ;
    EnumDefine::AlarmType   mMDAlarm                     ;
    quint16                 mMDSignal                    ;
    EnumDefine::EventType   mMDErrorType                 ;

    DeviceStatus(){}
    //explicit DeviceStatus(QObject *parent = nullptr): QObject(parent){}
    DeviceStatus(const DeviceStatus& copy):
                        mWait                         (copy.mWait                        ),
                        mRun                          (copy.mRun                         ),
                        mIsWeightCheckerGraphOn       (copy.mIsWeightCheckerGraphOn      ),
                        mIsMetalDetectorGraphOn       (copy.mIsMetalDetectorGraphOn      ),
                        mIsMetalDetectorFilterGraphOn (copy.mIsMetalDetectorFilterGraphOn),
                        mWCAlarm                      (copy.mWCAlarm                     ),
                        mCurrWeight                   (copy.mCurrWeight                  ),
                        mWCErrorType                  (copy.mWCErrorType                 ),
                        mMDAlarm                      (copy.mMDAlarm                     ),
                        mMDSignal                     (copy.mMDSignal                    ),
                        mMDErrorType                  (copy.mMDErrorType                 ){}

    ~DeviceStatus(){}

    DeviceStatus& operator=(const DeviceStatus& other)
    {
        mWait                         = other.mWait                     ;
        mRun                          = other.mRun                       ;
        mIsWeightCheckerGraphOn       = other.mIsWeightCheckerGraphOn      ;
        mIsMetalDetectorGraphOn       = other.mIsMetalDetectorGraphOn      ;
        mIsMetalDetectorFilterGraphOn = other.mIsMetalDetectorFilterGraphOn;
        mWCAlarm                      = other.mWCAlarm                     ;
        mCurrWeight                   = other.mCurrWeight                  ;
        mWCErrorType                  = other.mWCErrorType                 ;
        mMDAlarm                      = other.mMDAlarm                     ;
        mMDSignal                     = other.mMDSignal                    ;
        mMDErrorType                  = other.mMDErrorType                 ;

        return *this;
    }
};

Q_DECLARE_METATYPE(DeviceStatus);

#endif // DEVICESTATUS_H
