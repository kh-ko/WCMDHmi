#ifndef HMISETTINGMODEL_H
#define HMISETTINGMODEL_H

#include <QObject>

class HmiSettingModel : public QObject
{
    Q_OBJECT

public:
    bool    mIsDayMode          = false;
    bool    mIsDebugMode        = false;
    quint32 mDynamicFactor      = 10000000;
    quint16 mSimpleSenstivity01 = 0;
    quint16 mSimpleSenstivity02 = 0;
    quint16 mSimpleSenstivity03 = 0;
    quint16 mSimpleSenstivity04 = 0;
    quint16 mSimpleSenstivity05 = 0;

    void setIsDayMode         (bool    value){ if( mIsDayMode          == value) return; mIsDayMode          = value; emit signalEventChangedIsDayMode         (mIsDayMode         );}
    void setIsDebugMode       (bool    value){ if( mIsDebugMode        == value) return; mIsDebugMode        = value; emit signalEventChangedIsDebugMode       (mIsDebugMode       );}
    void setDynamicFactor     (quint32 value){ if( mDynamicFactor      == value) return; mDynamicFactor      = value; emit signalEventChangedDynamicFactor     (mDynamicFactor     );}
    void setSimpleSenstivity01(quint16 value){ if( mSimpleSenstivity01 == value) return; mSimpleSenstivity01 = value; emit signalEventChangedSimpleSenstivity01(mSimpleSenstivity01);}
    void setSimpleSenstivity02(quint16 value){ if( mSimpleSenstivity02 == value) return; mSimpleSenstivity02 = value; emit signalEventChangedSimpleSenstivity02(mSimpleSenstivity02);}
    void setSimpleSenstivity03(quint16 value){ if( mSimpleSenstivity03 == value) return; mSimpleSenstivity03 = value; emit signalEventChangedSimpleSenstivity03(mSimpleSenstivity03);}
    void setSimpleSenstivity04(quint16 value){ if( mSimpleSenstivity04 == value) return; mSimpleSenstivity04 = value; emit signalEventChangedSimpleSenstivity04(mSimpleSenstivity04);}
    void setSimpleSenstivity05(quint16 value){ if( mSimpleSenstivity05 == value) return; mSimpleSenstivity05 = value; emit signalEventChangedSimpleSenstivity05(mSimpleSenstivity05);}

signals:
    void signalEventChangedIsDayMode         (bool    value);
    void signalEventChangedIsDebugMode       (bool    value);
    void signalEventChangedDynamicFactor     (quint32 value);
    void signalEventChangedSimpleSenstivity01(quint16 value);
    void signalEventChangedSimpleSenstivity02(quint16 value);
    void signalEventChangedSimpleSenstivity03(quint16 value);
    void signalEventChangedSimpleSenstivity04(quint16 value);
    void signalEventChangedSimpleSenstivity05(quint16 value);

public:
    explicit HmiSettingModel(QObject *parent = nullptr) : QObject(parent){}
};

#endif // HMISETTINGMODEL_H
