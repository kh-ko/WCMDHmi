#ifndef PRODUCTSETTINGDTO_H
#define PRODUCTSETTINGDTO_H

#include <QObject>

#include "source/thread/dsp/dto/dspaddressdto.h"
#include "source/model/productsettingmodel.h"

class ProductSettingDto
{
public:
    StProductSetting mProductSetting;
    //quint32          mDynamicFactor;

    ProductSettingDto(){}
    ProductSettingDto(const ProductSettingDto& copy)
    {
        memcpy(&mProductSetting, &(copy.mProductSetting), sizeof(StProductSetting));
    }
    ProductSettingDto(StProductSetting * copy)
    {
        memcpy(&mProductSetting, copy, sizeof(StProductSetting));
    }
    ProductSettingDto(ProductSettingModel* copy)
    {
        mProductSetting.mProductSeq              = copy->mNo                   ;
        mProductSetting.mLength                  = copy->mLength               ;
        mProductSetting.mSpeed                   = copy->mSpeed                ;
        mProductSetting.mMotorAccelerationTime   = copy->mMotorAccelerationTime;
        mProductSetting.mNormalWeight            = copy->mNormalWeight         ;
        mProductSetting.mUnderWarningWeight      = copy->mUnderWarningWeight   ;
        mProductSetting.mOverWarningWeight       = copy->mOverWarningWeight    ;
        mProductSetting.mUnderWeight             = copy->mUnderWeight          ;
        mProductSetting.mOverWeight              = copy->mOverWeight           ;
        mProductSetting.mTareWeight              = copy->mTareWeight           ;
        mProductSetting.mWeightCheckerNGMotion   = copy->mWCNGMotion           ;
        mProductSetting.mWCEnableEtcError        = copy->mWCEnableEtcError     ;
        mProductSetting.mMetalDetectorSenstivity = copy->mMDSenstivity         ;
        mProductSetting.mMetalDetectorNGMotion   = copy->mMDNGMotion           ;
        mProductSetting.mDynamicFactor           = copy->mDynamicFactor        ;
    }
    ~ProductSettingDto(){}

    ProductSettingDto& operator=(const ProductSettingDto& other)
    {
        memcpy(&mProductSetting, &(other.mProductSetting), sizeof(StProductSetting));
        //mDynamicFactor = other.mDynamicFactor;
        return *this;
    }

    ProductSettingDto& operator=(ProductSettingModel* other)
    {
        mProductSetting.mProductSeq              = other->mNo                   ;
        mProductSetting.mLength                  = other->mLength               ;
        mProductSetting.mSpeed                   = other->mSpeed                ;
        mProductSetting.mMotorAccelerationTime   = other->mMotorAccelerationTime;
        mProductSetting.mNormalWeight            = other->mNormalWeight         ;
        mProductSetting.mUnderWarningWeight      = other->mUnderWarningWeight   ;
        mProductSetting.mOverWarningWeight       = other->mOverWarningWeight    ;
        mProductSetting.mUnderWeight             = other->mUnderWeight          ;
        mProductSetting.mOverWeight              = other->mOverWeight           ;
        mProductSetting.mTareWeight              = other->mTareWeight           ;
        mProductSetting.mWeightCheckerNGMotion   = other->mWCNGMotion           ;
        mProductSetting.mWCEnableEtcError        = other->mWCEnableEtcError     ;
        mProductSetting.mMetalDetectorSenstivity = other->mMDSenstivity         ;
        mProductSetting.mMetalDetectorNGMotion   = other->mMDNGMotion           ;
        mProductSetting.mDynamicFactor           = other->mDynamicFactor        ;
        return *this;
    }

    ProductSettingModel * toProductSettingModel()
    {
        ProductSettingModel * pTemp = new ProductSettingModel();

        pTemp->setNo                    (mProductSetting.mProductSeq             );
        pTemp->setLength                (mProductSetting.mLength                 );
        pTemp->setSpeed                 (mProductSetting.mSpeed                  );
        pTemp->setMotorAccelerationTime (mProductSetting.mMotorAccelerationTime  );
        pTemp->setNormalWeight          (mProductSetting.mNormalWeight           );
        pTemp->setUnderWarningWeight    (mProductSetting.mUnderWarningWeight     );
        pTemp->setOverWarningWeight     (mProductSetting.mOverWarningWeight      );
        pTemp->setUnderWeight           (mProductSetting.mUnderWeight            );
        pTemp->setOverWeight            (mProductSetting.mOverWeight             );
        pTemp->setTareWeight            (mProductSetting.mTareWeight             );
        pTemp->setWCNGMotion            (mProductSetting.mWeightCheckerNGMotion  );
        pTemp->setWCEnableEtcError      (mProductSetting.mWCEnableEtcError       );
        pTemp->setMDSenstivity          (mProductSetting.mMetalDetectorSenstivity);
        pTemp->setMDNGMotion            (mProductSetting.mMetalDetectorNGMotion  );
        pTemp->setDynamicFactor         (mProductSetting.mDynamicFactor          );

        return pTemp;
    }
};

Q_DECLARE_METATYPE(ProductSettingDto);
#endif // PRODUCTSETTINGDTO_H
