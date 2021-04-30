#ifndef PANELGROUPSETTINGINHOMEMODEL_H
#define PANELGROUPSETTINGINHOMEMODEL_H

#include <QObject>
#include "source/globaldef/qmlenumdef.h"
#include "source/service/coreservice.h"

class PanelGroupSettingInHomeModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint32  mGroupCount        READ getGroupCount            NOTIFY signalEventChangedGroupCount      )
    Q_PROPERTY(bool     mIsEditGroupCount  READ getIsEditGroupCount      NOTIFY signalEventChangedIsEditGroupCount)

public:
    quint32  mGroupCount ;
    bool     mIsEditGroupCount ;

    quint32  getGroupCount       (){ return mGroupCount       ;}
    bool     getIsEditGroupCount (){ return mIsEditGroupCount ;}

    void     setGroupCount       (quint32 value){ if( value == mGroupCount        ) return; mGroupCount         = value; setIsEditGroupCount (true); emit signalEventChangedGroupCount        (value);}
    void     setIsEditGroupCount (bool    value){ if( value == mIsEditGroupCount  ) return; mIsEditGroupCount   = value; emit signalEventChangedIsEditGroupCount  (value);}

signals:
    void signalEventChangedGroupCount       (quint32 value);
    void signalEventChangedIsEditGroupCount (bool    value);
    void signalEventResultSaveGroupSetting  (int     error);

public slots:
    Q_INVOKABLE bool onCommandComparePwd(QString value)
    {
        if(pLSettingSP->mSecuritySetting.mPwd == value)
            return true;

        return false;
    }
    Q_INVOKABLE bool onCommandCompareAdminPwd(QString value)
    {
        if(pLSettingSP->mSecuritySetting.mAdminPwd == value)
            return true;

        return false;
    }

    Q_INVOKABLE void onCommandSetGroupCount     (quint32 value)
    {
        setGroupCount(value);
    }
    Q_INVOKABLE void onCommandApply()
    {
        PDSettingDto editPD = pProductSP->mCurrPD;
        editPD.mDspForm.mCommSetting.mGroupCount = mGroupCount;

        int ret = pProductSP->editPD(editPD);

        if(ret == EnumDef::PDERR_NONE)
        {
            setIsEditGroupCount (false);
        }

        emit signalEventResultSaveGroupSetting(ret);
    }
    Q_INVOKABLE void onCommandReload()
    {
        setGroupCount(pProductSP->mCurrPD.mDspForm.mCommSetting.mGroupCount);
        setIsEditGroupCount (false);
    }


// internal layer =============================================================
public:
    explicit PanelGroupSettingInHomeModel(QObject *parent = nullptr):QObject(parent)
    {

    }
};
#endif // PANELGROUPSETTINGINHOMEMODEL_H
