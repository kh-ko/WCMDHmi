#ifndef PRODUCTSETTING_H
#define PRODUCTSETTING_H

#include <QObject>
#include <QDebug>

#include "source/globaldef/EnumDefine.h"

class ProductSetting// : public QObject
{
    //Q_OBJECT
public:
    quint16                 mSeq                  ;
    bool                    mSelected             ;
    quint16                 mNo                   ;
    QString                 mName                 ;
    quint16                 mLength               ;
    quint16                 mSpeed                ;
    quint32                 mMotorAccelerationTime;
    quint32                 mUnderWeight          ;
    quint32                 mUnderWarningWeight   ;
    quint32                 mNormalWeight         ;
    quint32                 mOverWarningWeight    ;
    quint32                 mOverWeight           ;
    quint32                 mTareWeight           ;
    EnumDefine::NGMotion    mWCNGMotion           ;
    int                     mDynamicFactor        ;
    quint16                 mMDSenstivity         ;
    EnumDefine::NGMotion    mMDNGMotion           ;

    ProductSetting(){
        mSeq                   = 0xffff;
        mSelected              = false;
        mNo                    = 999;
        mName                  = "none name";
        mLength                = 100;
        mSpeed                 = 380;
        mMotorAccelerationTime = 1000;
        mUnderWeight           = 280000;
        mUnderWarningWeight    = 280000;
        mNormalWeight          = 300000;
        mOverWarningWeight     = 320000;
        mOverWeight            = 320000;
        mTareWeight            = 10000;
        mWCNGMotion            = EnumDefine::NGMotion::NG_MOTION_REJECT_01;
        mDynamicFactor         = 9969342;
        mMDSenstivity          = 500;
        mMDNGMotion            = EnumDefine::NGMotion::NG_MOTION_REJECT_02;
    }
    //explicit ProductSetting(QObject *parent = nullptr): QObject(parent){}
    ProductSetting(const ProductSetting& copy):
                          mSeq                  (copy.mSeq                  ),
                          mSelected             (copy.mSelected             ),
                          mNo                   (copy.mNo                   ),
                          mName                 (copy.mName                 ),
                          mLength               (copy.mLength               ),
                          mSpeed                (copy.mSpeed                ),
                          mMotorAccelerationTime(copy.mMotorAccelerationTime),
                          mUnderWeight          (copy.mUnderWeight          ),
                          mUnderWarningWeight   (copy.mUnderWarningWeight   ),
                          mNormalWeight         (copy.mNormalWeight         ),
                          mOverWarningWeight    (copy.mOverWarningWeight    ),
                          mOverWeight           (copy.mOverWeight           ),
                          mTareWeight           (copy.mTareWeight           ),
                          mWCNGMotion           (copy.mWCNGMotion           ),
                          mDynamicFactor        (copy.mDynamicFactor        ),
                          mMDSenstivity         (copy.mMDSenstivity         ),
                          mMDNGMotion           (copy.mMDNGMotion           ){}

    ~ProductSetting(){}

    ProductSetting& operator=(const ProductSetting& other)
    {
        mSeq                    = other.mSeq                  ;
        mSelected               = other.mSelected             ;
        mNo                     = other.mNo                   ;
        mName                   = other.mName                 ;
        mLength                 = other.mLength               ;
        mSpeed                  = other.mSpeed                ;
        mMotorAccelerationTime  = other.mMotorAccelerationTime;
        mUnderWeight            = other.mUnderWeight          ;
        mUnderWarningWeight     = other.mUnderWarningWeight   ;
        mNormalWeight           = other.mNormalWeight         ;
        mOverWarningWeight      = other.mOverWarningWeight    ;
        mOverWeight             = other.mOverWeight           ;
        mTareWeight             = other.mTareWeight           ;
        mWCNGMotion             = other.mWCNGMotion           ;
        mDynamicFactor          = other.mDynamicFactor        ;
        mMDSenstivity           = other.mMDSenstivity         ;
        mMDNGMotion             = other.mMDNGMotion           ;

        return *this;
    }

    bool remoteSettingCompare(ProductSetting * other)
    {
        if(   mSeq                      != other->mSeq
           || mLength                   != other->mLength
           || mSpeed                    != other->mSpeed
           || mMotorAccelerationTime    != other->mMotorAccelerationTime
           || mUnderWeight              != other->mUnderWeight
           || mUnderWarningWeight       != other->mUnderWarningWeight
           || mNormalWeight             != other->mNormalWeight
           || mOverWarningWeight        != other->mOverWarningWeight
           || mOverWeight               != other->mOverWeight
           || mTareWeight               != other->mTareWeight
           || mWCNGMotion               != other->mWCNGMotion
           || mMDSenstivity             != other->mMDSenstivity
           || mMDNGMotion               != other->mMDNGMotion)
        {
            qDebug() << "Product setting missmatch";
            qDebug() << "mSeq                   "       << mSeq                     << ": "<<other->mSeq;
            qDebug() << "mLength                "       << mLength                  << ": "<<other->mLength                 ;
            qDebug() << "mSpeed                 "       << mSpeed                   << ": "<<other->mSpeed                  ;
            qDebug() << "mMotorAccelerationTime "       << mMotorAccelerationTime   << ": "<<other->mMotorAccelerationTime  ;
            qDebug() << "mUnderWeight           "       << mUnderWeight             << ": "<<other->mUnderWeight            ;
            qDebug() << "mUnderWarningWeight    "       << mUnderWarningWeight      << ": "<<other->mUnderWarningWeight     ;
            qDebug() << "mNormalWeight          "       << mNormalWeight            << ": "<<other->mNormalWeight           ;
            qDebug() << "mOverWarningWeight     "       << mOverWarningWeight       << ": "<<other->mOverWarningWeight      ;
            qDebug() << "mOverWeight            "       << mOverWeight              << ": "<<other->mOverWeight             ;
            qDebug() << "mTareWeight            "       << mTareWeight              << ": "<<other->mTareWeight             ;
            qDebug() << "mWCNGMotion            "       << mWCNGMotion              << ": "<<other->mWCNGMotion             ;
            qDebug() << "mMDSenstivity          "       << mMDSenstivity            << ": "<<other->mMDSenstivity           ;
            qDebug() << "mMDNGMotion            "       << mMDNGMotion              << ": "<<other->mMDNGMotion             ;

            return false;
        }


        return true;
    }
};

Q_DECLARE_METATYPE(ProductSetting);
#endif // PRODUCTSETTING_H
