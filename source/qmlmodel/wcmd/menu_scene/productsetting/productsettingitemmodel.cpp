#include "productsettingitemmodel.h"

ProductSettingItemModel::ProductSettingItemModel(QObject *parent) : QObject(parent)
{
}

ProductSetting ProductSettingItemModel::getModifiedProductSetting()
{
    ProductSetting ps;

    ps.mSeq                   =                       getSeq                ();
    ps.mSelected              =                       getSelected           ();
    ps.mNo                    =                       getNo                 ();
    ps.mName                  =                       getName               ();
    ps.mLength                =                       getLength             ();
    ps.mSpeed                 =                       getSpeed              ();
    ps.mMotorAccelerationTime =                       getMotorAcceleration  ();
    ps.mUnderWeight           =                       getUnderWeight        ();
    ps.mUnderWarningWeight    =                       getUnderWarningWeight ();
    ps.mNormalWeight          =                       getNormalWeight       ();
    ps.mOverWarningWeight     =                       getOverWarningWeight  ();
    ps.mOverWeight            =                       getOverWeight         ();
    ps.mTareWeight            =                       getTareWeight         ();
    ps.mWCNGMotion            = (EnumDefine::NGMotion)getWCNGMotion         ();
    ps.mDynamicFactor         =                       getDynamicFactor      ();
    ps.mMDSenstivity          =                       getMDSenstivity       ();
    ps.mMDNGMotion            = (EnumDefine::NGMotion)getMDNGMotion         ();

    return ps;
}

void ProductSettingItemModel::setData(ProductSetting ps)
{
    mProductSetting = ps;

    setIsNull                  (false);
    setIsNew                   (false);
    setIsRemoved               (false);

    reset();
}

void ProductSettingItemModel::setNewSetting(ProductSetting ps)
{
    setIsNew(true);

    setSeq                     (0                        );
    setSelected                (ps.mSelected             );
    setNo                      (ps.mNo                   );
    setName                    (ps.mName                 );
    setLength                  (ps.mLength               );
    setSpeed                   (ps.mSpeed                );
    setMotorAcceleration       (ps.mMotorAccelerationTime);
    setUnderWeight             (ps.mUnderWeight          );
    setUnderWarningWeight      (ps.mUnderWarningWeight   );
    setNormalWeight            (ps.mNormalWeight         );
    setOverWarningWeight       (ps.mOverWarningWeight    );
    setOverWeight              (ps.mOverWeight           );
    setTareWeight              (ps.mTareWeight           );
    setWCNGMotion              (ps.mWCNGMotion           );
    setDynamicFactor           (ps.mDynamicFactor        );
    setMDSenstivity            (ps.mMDSenstivity         );
    setMDNGMotion              (ps.mMDNGMotion           );

    setIsEditNo                (true);
    setIsEditName              (true);
    setIsEditLength            (true);
    setIsEditSpeed             (true);
    setIsEditMotorAcceleration (true);
    setIsEditUnderWeight       (true);
    setIsEditUnderWarningWeight(true);
    setIsEditNormalWeight      (true);
    setIsEditOverWarningWeight (true);
    setIsEditOverWeight        (true);
    setIsEditTareWeight        (true);
    setIsEditWCNGMotion        (true);
    setIsEditDynamicFactor     (true);
    setIsEditMDSenstivity      (true);
    setIsEditMDNGMotion        (true);

}
void ProductSettingItemModel::reset()
{
    if(getIsRemoved())
    {
        setSeq                     (0 );
        setSelected                (0 );
        setNo                      (0 );
        setName                    ("");
        setLength                  (0 );
        setSpeed                   (0 );
        setMotorAcceleration       (0 );
        setUnderWeight             (0 );
        setUnderWarningWeight      (0 );
        setNormalWeight            (0 );
        setOverWarningWeight       (0 );
        setOverWeight              (0 );
        setTareWeight              (0 );
        setWCNGMotion              (0 );
        setDynamicFactor           (0 );
        setMDSenstivity            (0 );
        setMDNGMotion              (0 );

        setIsEditNo                (false);
        setIsEditName              (false);
        setIsEditLength            (false);
        setIsEditSpeed             (false);
        setIsEditMotorAcceleration (false);
        setIsEditUnderWeight       (false);
        setIsEditUnderWarningWeight(false);
        setIsEditNormalWeight      (false);
        setIsEditOverWarningWeight (false);
        setIsEditOverWeight        (false);
        setIsEditTareWeight        (false);
        setIsEditWCNGMotion        (false);
        setIsEditDynamicFactor     (false);
        setIsEditMDSenstivity      (false);
        setIsEditMDNGMotion        (false);
    }
    else
    {
        setSeq                     (mProductSetting.mSeq               );
        setSelected                (mProductSetting.mSelected          );
        setNo                      (mProductSetting.mNo                );
        setName                    (mProductSetting.mName              );
        setLength                  (mProductSetting.mLength            );
        setSpeed                   (mProductSetting.mSpeed             );
        setMotorAcceleration       (mProductSetting.mMotorAccelerationTime);
        setUnderWeight             (mProductSetting.mUnderWeight       );
        setUnderWarningWeight      (mProductSetting.mUnderWarningWeight);
        setNormalWeight            (mProductSetting.mNormalWeight      );
        setOverWarningWeight       (mProductSetting.mOverWarningWeight );
        setOverWeight              (mProductSetting.mOverWeight        );
        setTareWeight              (mProductSetting.mTareWeight        );
        setWCNGMotion              (mProductSetting.mWCNGMotion        );
        setDynamicFactor           (mProductSetting.mDynamicFactor     );
        setMDSenstivity            (mProductSetting.mMDSenstivity      );
        setMDNGMotion              (mProductSetting.mMDNGMotion        );

        setIsEditNo                (false);
        setIsEditName              (false);
        setIsEditLength            (false);
        setIsEditSpeed             (false);
        setIsEditMotorAcceleration (false);
        setIsEditUnderWeight       (false);
        setIsEditUnderWarningWeight(false);
        setIsEditNormalWeight      (false);
        setIsEditOverWarningWeight (false);
        setIsEditOverWeight        (false);
        setIsEditTareWeight        (false);
        setIsEditWCNGMotion        (false);
        setIsEditDynamicFactor     (false);
        setIsEditMDSenstivity      (false);
        setIsEditMDNGMotion        (false);
    }
}


