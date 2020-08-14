#ifndef EVENT_H
#define EVENT_H
#include <QObject>

#include "source/globaldef/EnumDefine.h"

class Event// : public QObject
{
//    Q_OBJECT
public:
    quint64                 mSeq                = 0;
    quint16                 mDeviceSeq          = 0;
    quint16                 mYear               = 0;
    quint16                 mMonth              = 0;
    quint16                 mDay                = 0;
    quint16                 mHour               = 0;
    quint16                 mMin                = 0;
    quint16                 mSec                = 0;
    quint16                 mMsec               = 0;
    quint64                 mProgStartEventSeq  = 0;
    quint16                 mWorkStartYear      = 0;
    quint16                 mWorkStartMonth     = 0;
    quint16                 mWorkStartDay       = 0;
    EnumDefine::EventType   mEventType          = EnumDefine::EventType::WEIGHT_NORMAL_TYPE;
    quint16                 mProductSettingSeq  = 0;
    quint16                 mProductNo          = 0;
    QString                 mProductName        = "";
    quint32                 mDeviceID           = 0;
    quint32                 mUnderWeight        = 0;
    quint32                 mUnderWarningWeight = 0;
    quint32                 mNormalWeight       = 0;
    quint32                 mOverWarningWeight  = 0;
    quint32                 mOverWeight         = 0;
    quint32                 mTareWeight         = 0;
    quint16                 mMDSenstivity       = 0;
    quint32                 mWeight             = 0;


    Event(){}
//    explicit Event(QObject *parent = nullptr): QObject(parent){}
    Event(const Event& copy):
                                mSeq               (copy.mSeq               ),
                                mDeviceSeq         (copy.mDeviceSeq         ),
                                mYear              (copy.mYear              ),
                                mMonth             (copy.mMonth             ),
                                mDay               (copy.mDay               ),
                                mHour              (copy.mHour              ),
                                mMin               (copy.mMin               ),
                                mSec               (copy.mSec               ),
                                mMsec              (copy.mMsec              ),
                                mProgStartEventSeq (copy.mProgStartEventSeq ),
                                mWorkStartYear     (copy.mWorkStartYear     ),
                                mWorkStartMonth    (copy.mWorkStartMonth    ),
                                mWorkStartDay      (copy.mWorkStartDay      ),
                                mEventType         (copy.mEventType         ),
                                mProductSettingSeq (copy.mProductSettingSeq ),
                                mProductNo         (copy.mProductNo         ),
                                mProductName       (copy.mProductName       ),
                                mDeviceID          (copy.mDeviceID          ),
                                mUnderWeight       (copy.mUnderWeight       ),
                                mUnderWarningWeight(copy.mUnderWarningWeight),
                                mNormalWeight      (copy.mNormalWeight      ),
                                mOverWarningWeight (copy.mOverWarningWeight ),
                                mOverWeight        (copy.mOverWeight        ),
                                mTareWeight        (copy.mTareWeight        ),
                                mMDSenstivity      (copy.mMDSenstivity      ),
                                mWeight            (copy.mWeight            ){}

    ~Event(){}

    Event& operator=(const Event& other)
    {
        mSeq                = other.mSeq               ;
        mDeviceSeq          = other.mDeviceSeq         ;
        mYear               = other.mYear              ;
        mMonth              = other.mMonth             ;
        mDay                = other.mDay               ;
        mHour               = other.mHour              ;
        mMin                = other.mMin               ;
        mSec                = other.mSec               ;
        mMsec               = other.mMsec              ;
        mProgStartEventSeq  = other.mProgStartEventSeq ;
        mWorkStartYear      = other.mWorkStartYear     ;
        mWorkStartMonth     = other.mWorkStartMonth    ;
        mWorkStartDay       = other.mWorkStartDay      ;
        mEventType          = other.mEventType         ;
        mProductSettingSeq  = other.mProductSettingSeq ;
        mProductNo          = other.mProductNo         ;
        mProductName        = other.mProductName       ;
        mDeviceID           = other.mDeviceID          ;
        mUnderWeight        = other.mUnderWeight       ;
        mUnderWarningWeight = other.mUnderWarningWeight;
        mNormalWeight       = other.mNormalWeight      ;
        mOverWarningWeight  = other.mOverWarningWeight ;
        mOverWeight         = other.mOverWeight        ;
        mTareWeight         = other.mTareWeight        ;
        mMDSenstivity       = other.mMDSenstivity      ;
        mWeight             = other.mWeight            ;

        return *this;
    }
};

Q_DECLARE_METATYPE(Event);

#endif // EVENT_H
