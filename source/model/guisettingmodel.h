#ifndef GUISETTINGMODEL_H
#define GUISETTINGMODEL_H

#include <QObject>
#include "source/globaldef/EnumDefine.h"
class GuiSettingModel : public QObject
{
    Q_OBJECT

public:
    int  mLanguage                = EnumDefine::Language::ENG;
    bool mIsDetail                = false;
    int  mViewMode                = false;
    int  mTrendsOptionH           = EnumDefine::TrendsGraphOptionH::TRENDSOPTION_H_UNDER_TO_OVER;
    int  mTrendsOptionFilter      = EnumDefine::TrendsGraphOptionFilter::TRENDSOPTION_FILTER_TOTAL;
    int  mTrendsOptionLastN       = EnumDefine::TrendsGraphOptionLastN::TRENDSOPTION_TOTAL_SINCE_START;
    int  mTrendsLastNValue        = 100;
    int  mWCGraphMinRange         = 0;
    int  mWCGraphMaxRange         = 100000000;

    void setLanguage          (int  value){ if(mLanguage                == value) return; mLanguage                = value; emit signalEventChangedLanguage          (mLanguage          );}
    void setIsDetail          (bool value){ if(mIsDetail                == value) return; mIsDetail                = value; emit signalEventChangedIsDetail          (mIsDetail          );}
    void setViewMode          (int  value){ if(mViewMode                == value) return; mViewMode                = value; emit signalEventChangedViewMode          (mViewMode          );}
    void setTrendsOptionH     (int  value){ if(mTrendsOptionH           == value) return; mTrendsOptionH           = value; emit signalEventChangedTrendsOptionH     (mTrendsOptionH     );}
    void setTrendsOptionFilter(int  value){ if(mTrendsOptionFilter      == value) return; mTrendsOptionFilter      = value; emit signalEventChangedTrendsOptionFilter(mTrendsOptionFilter);}
    void setTrendsOptionLastN (int  value){ if(mTrendsOptionLastN       == value) return; mTrendsOptionLastN       = value; emit signalEventChangedTrendsOptionLastN (mTrendsOptionLastN );}
    void setTrendsLastNValue  (int  value){ if(mTrendsLastNValue        == value) return; mTrendsLastNValue        = value; emit signalEventChangedTrendsLastNValue  (mTrendsLastNValue  );}
    void setWCGraphMinRange   (int  value){ if(mWCGraphMinRange         == value) return; mWCGraphMinRange         = value; emit signalEventChangedWCGraphMinRange   (mWCGraphMinRange   );}
    void setWCGraphMaxRange   (int  value){ if(mWCGraphMaxRange         == value) return; mWCGraphMaxRange         = value; emit signalEventChangedWCGraphMaxRange   (mWCGraphMaxRange   );}

signals:
    void signalEventChangedLanguage               (int                value);
    void signalEventChangedIsDetail               (bool               value);
    void signalEventChangedViewMode               (int                value);
    void signalEventChangedTrendsOptionH          (int                value);
    void signalEventChangedTrendsOptionFilter     (int                value);
    void signalEventChangedTrendsOptionLastN      (int                value);
    void signalEventChangedTrendsLastNValue       (int                value);
    void signalEventChangedWCGraphMinRange        (int                value);
    void signalEventChangedWCGraphMaxRange        (int                value);

public:
    explicit GuiSettingModel(QObject *parent = nullptr) : QObject(parent){}
};

#endif // GUISETTINGMODEL_H
