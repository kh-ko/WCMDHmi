#ifndef PRODUCTSETTING_H
#define PRODUCTSETTING_H

#include <QObject>

class ProductSettingModel : public QObject
{
    Q_OBJECT

public:
    quint64 mSeq                  =0;
    quint16 mNo                   ;
    QString mName                 ;
    quint16 mLength               ;
    quint16 mSpeed                ;
    quint32 mMotorAccelerationTime;
    quint32 mUnderWeight          ;
    quint32 mUnderWarningWeight   ;
    quint32 mNormalWeight         ;
    quint32 mOverWarningWeight    ;
    quint32 mOverWeight           ;
    quint32 mTareWeight           ;
    quint16 mWCNGMotion           ;
    quint16 mWCEnableEtcError     =1;
    quint32 mDynamicFactor        ;
    quint16 mMDSenstivity         ;
    quint16 mMDNGMotion           ;

    void setSeq                  (quint64 value){ if( mSeq                   == value) return; mSeq                   = value; emit signalEventChangedSeq                  (mSeq                  );}
    void setNo                   (quint16 value){ if( mNo                    == value) return; mNo                    = value; emit signalEventChangedNo                   (mNo                   );}
    void setName                 (QString value){ if( mName                  == value) return; mName                  = value; emit signalEventChangedName                 (mName                 );}
    void setLength               (quint16 value){ if( mLength                == value) return; mLength                = value; emit signalEventChangedLength               (mLength               );}
    void setSpeed                (quint16 value){ if( mSpeed                 == value) return; mSpeed                 = value; emit signalEventChangedSpeed                (mSpeed                );}
    void setMotorAccelerationTime(quint32 value){ if( mMotorAccelerationTime == value) return; mMotorAccelerationTime = value; emit signalEventChangedMotorAccelerationTime(mMotorAccelerationTime);}
    void setUnderWeight          (quint32 value){ if( mUnderWeight           == value) return; mUnderWeight           = value; emit signalEventChangedUnderWeight          (mUnderWeight          );}
    void setUnderWarningWeight   (quint32 value){ if( mUnderWarningWeight    == value) return; mUnderWarningWeight    = value; emit signalEventChangedUnderWarningWeight   (mUnderWarningWeight   );}
    void setNormalWeight         (quint32 value){ if( mNormalWeight          == value) return; mNormalWeight          = value; emit signalEventChangedNormalWeight         (mNormalWeight         );}
    void setOverWarningWeight    (quint32 value){ if( mOverWarningWeight     == value) return; mOverWarningWeight     = value; emit signalEventChangedOverWarningWeight    (mOverWarningWeight    );}
    void setOverWeight           (quint32 value){ if( mOverWeight            == value) return; mOverWeight            = value; emit signalEventChangedOverWeight           (mOverWeight           );}
    void setTareWeight           (quint32 value){ if( mTareWeight            == value) return; mTareWeight            = value; emit signalEventChangedTareWeight           (mTareWeight           );}
    void setWCNGMotion           (quint16 value){ if( mWCNGMotion            == value) return; mWCNGMotion            = value; emit signalEventChangedWCNGMotion           (mWCNGMotion           );}
    void setWCEnableEtcError     (quint16 value){ if( mWCEnableEtcError      == value) return; mWCEnableEtcError      = value; emit signalEventChangedWCEnableEtcError     (mWCEnableEtcError     );}
    void setDynamicFactor        (quint32 value){ if( mDynamicFactor         == value) return; mDynamicFactor         = value; emit signalEventChangedDynamicFactor        (mDynamicFactor        );}
    void setMDSenstivity         (quint16 value){ if( mMDSenstivity          == value) return; mMDSenstivity          = value; emit signalEventChangedMDSenstivity         (mMDSenstivity         );}
    void setMDNGMotion           (quint16 value){ if( mMDNGMotion            == value) return; mMDNGMotion            = value; emit signalEventChangedMDNGMotion           (mMDNGMotion           );}

    void setStringValue(QString value, QString divider)
    {
        QStringList listRow = value.split(divider);

        for(int i = 0; i < listRow.size(); i++)
        {
            QString row = listRow.at(i);

            if(row.contains(":") == false)
                continue;

            QString key = row.split(":")[0];
            QString value = row.split(":")[1];

            if     (key == "Seq"                  ){ mSeq                   = value.toULongLong();}
            else if(key == "No"                   ){ mNo                    = value.toUInt()     ;}
            else if(key == "Name"                 ){ mName                  = value              ;}
            else if(key == "Length"               ){ mLength                = value.toUInt()     ;}
            else if(key == "Speed"                ){ mSpeed                 = value.toUInt()     ;}
            else if(key == "MotorAccelerationTime"){ mMotorAccelerationTime = value.toUInt()     ;}
            else if(key == "UnderWeight"          ){ mUnderWeight           = value.toUInt()     ;}
            else if(key == "UnderWarningWeight"   ){ mUnderWarningWeight    = value.toUInt()     ;}
            else if(key == "NormalWeight"         ){ mNormalWeight          = value.toUInt()     ;}
            else if(key == "OverWarningWeight"    ){ mOverWarningWeight     = value.toUInt()     ;}
            else if(key == "OverWeight"           ){ mOverWeight            = value.toUInt()     ;}
            else if(key == "TareWeight"           ){ mTareWeight            = value.toUInt()     ;}
            else if(key == "WCNGMotion"           ){ mWCNGMotion            = value.toUInt()     ;}
            else if(key == "WCEnableEtcError"     ){ mWCEnableEtcError      = value.toUInt()     ;}
            else if(key == "DynamicFactor"        ){ mDynamicFactor         = value.toUInt()     ;}
            else if(key == "MDSenstivity"         ){ mMDSenstivity          = value.toUInt()     ;}
            else if(key == "MDNGMotion"           ){ mMDNGMotion            = value.toUInt()     ;}
        }
    }
    QString toString(QString divider){
        return QString("Seq:%1%2No:%3%4Name:%5%6Length:%7%8Speed:%9%10MotorAccelerationTime:%11%12UnderWeight:%13%14UnderWarningWeight:%15%16NormalWeight:%17%18OverWarningWeight:%19%20OverWeight:%21%22TareWeight:%23%24WCNGMotion:%25%26WCEnableEtcError:%27%28DynamicFactor:%29%30MDSenstivity:%31%32MDNGMotion:%33")
                .arg(mSeq                  ).arg(divider)
                .arg(mNo                   ).arg(divider)
                .arg(mName                 ).arg(divider)
                .arg(mLength               ).arg(divider)
                .arg(mSpeed                ).arg(divider)
                .arg(mMotorAccelerationTime).arg(divider)
                .arg(mUnderWeight          ).arg(divider)
                .arg(mUnderWarningWeight   ).arg(divider)
                .arg(mNormalWeight         ).arg(divider)
                .arg(mOverWarningWeight    ).arg(divider)
                .arg(mOverWeight           ).arg(divider)
                .arg(mTareWeight           ).arg(divider)
                .arg(mWCNGMotion           ).arg(divider)
                .arg(mWCEnableEtcError     ).arg(divider)
                .arg(mDynamicFactor        ).arg(divider)
                .arg(mMDSenstivity         ).arg(divider)
                .arg(mMDNGMotion           );
    }
signals:
    void signalEventChangedSeq                  (quint64 value);
    void signalEventChangedNo                   (quint16 value);
    void signalEventChangedName                 (QString value);
    void signalEventChangedLength               (quint16 value);
    void signalEventChangedSpeed                (quint16 value);
    void signalEventChangedMotorAccelerationTime(quint32 value);
    void signalEventChangedUnderWeight          (quint32 value);
    void signalEventChangedUnderWarningWeight   (quint32 value);
    void signalEventChangedNormalWeight         (quint32 value);
    void signalEventChangedOverWarningWeight    (quint32 value);
    void signalEventChangedOverWeight           (quint32 value);
    void signalEventChangedTareWeight           (quint32 value);
    void signalEventChangedWCNGMotion           (quint16 value);
    void signalEventChangedWCEnableEtcError     (quint16 value);
    void signalEventChangedDynamicFactor        (quint32 value);
    void signalEventChangedMDSenstivity         (quint16 value);
    void signalEventChangedMDNGMotion           (quint16 value);

public:
    ProductSettingModel& operator=(ProductSettingModel * other)
    {
        setSeq                  (other->mSeq                  );
        setNo                   (other->mNo                   );
        setName                 (other->mName                 );
        setLength               (other->mLength               );
        setSpeed                (other->mSpeed                );
        setMotorAccelerationTime(other->mMotorAccelerationTime);
        setUnderWeight          (other->mUnderWeight          );
        setUnderWarningWeight   (other->mUnderWarningWeight   );
        setNormalWeight         (other->mNormalWeight         );
        setOverWarningWeight    (other->mOverWarningWeight    );
        setOverWeight           (other->mOverWeight           );
        setTareWeight           (other->mTareWeight           );
        setWCNGMotion           (other->mWCNGMotion           );
        setWCEnableEtcError     (other->mWCEnableEtcError     );
        setDynamicFactor        (other->mDynamicFactor        );
        setMDSenstivity         (other->mMDSenstivity         );
        setMDNGMotion           (other->mMDNGMotion           );

        return *this;
    }

    bool isEqual(ProductSettingModel * value)
    {
        if(mNo                    == value->mNo                    &&
           mLength                == value->mLength                &&
           mSpeed                 == value->mSpeed                 &&
           mMotorAccelerationTime == value->mMotorAccelerationTime &&
           mUnderWeight           == value->mUnderWeight           &&
           mUnderWarningWeight    == value->mUnderWarningWeight    &&
           mNormalWeight          == value->mNormalWeight          &&
           mOverWarningWeight     == value->mOverWarningWeight     &&
           mOverWeight            == value->mOverWeight            &&
           mTareWeight            == value->mTareWeight            &&
           mWCNGMotion            == value->mWCNGMotion            &&
           mWCEnableEtcError      == value->mWCEnableEtcError      &&
           mDynamicFactor         == value->mDynamicFactor         &&
           mMDSenstivity          == value->mMDSenstivity          &&
           mMDNGMotion            == value->mMDNGMotion            )
            return true;

        return false;
    }

    explicit ProductSettingModel(QObject *parent = nullptr) : QObject(parent){}
};

#endif // PRODUCTSETTING_H
