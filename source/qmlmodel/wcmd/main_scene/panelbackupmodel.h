#ifndef PANELBACKUPMODEL_H
#define PANELBACKUPMODEL_H

#include <QObject>
#include "source/model/databasebackupstate.h"
#include "source/globaldef/EnumDefine.h"
class PanelBackupModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool     isNeedBackup     READ getIsNeedBackup     NOTIFY signalEventChangedIsNeedBackup   );
    Q_PROPERTY(bool     isProc           READ getIsProc           NOTIFY signalEventChangedIsProc         );
    Q_PROPERTY(bool     isShowInterface  READ getIsShowInterface  NOTIFY signalEventChangedIsShowInterface);
    Q_PROPERTY(quint64  totalCnt         READ getTotalCnt         NOTIFY signalEventChangedTotalCnt       );
    Q_PROPERTY(quint64  currentIdx       READ getCurrentIdx       NOTIFY signalEventChangedCurrentIdx     );
    Q_PROPERTY(int      startYear        READ getStartYear        NOTIFY signalEventChangedStartYear      );
    Q_PROPERTY(int      startMonth       READ getStartMonth       NOTIFY signalEventChangedStartMonth     );
    Q_PROPERTY(int      startDay         READ getStartDay         NOTIFY signalEventChangedStartDay       );
    Q_PROPERTY(int      endYear          READ getEndYear          NOTIFY signalEventChangedEndYear        );
    Q_PROPERTY(int      endMonth         READ getEndMonth         NOTIFY signalEventChangedEndMonth       );
    Q_PROPERTY(int      endDay           READ getEndDay           NOTIFY signalEventChangedEndDay         );

public:
    static void    procBackup();
    static DatabaseBackupState      mBackupState;

    QThread *mThread            = nullptr;
    bool    mIsNeedBackup       = false;
    bool    mIsProc             = false;
    bool    mIsShowInterface    = false;
    quint64 mTotalCnt           = 0;
    quint64 mCurrentIdx         = 0;
    int     mStartYear          = 0;
    int     mStartMonth         = 0;
    int     mStartDay           = 0;
    int     mEndYear            = 0;
    int     mEndMonth           = 0;
    int     mEndDay             = 0;

    bool    getIsNeedBackup   (){return mIsNeedBackup         ;}
    bool    getIsProc         (){return mIsProc         ;}
    bool    getIsShowInterface(){return mIsShowInterface;}
    quint64 getTotalCnt       (){return mTotalCnt       ;}
    quint64 getCurrentIdx     (){return mCurrentIdx     ;}
    int     getStartYear      (){return mStartYear      ;}
    int     getStartMonth     (){return mStartMonth     ;}
    int     getStartDay       (){return mStartDay       ;}
    int     getEndYear        (){return mEndYear        ;}
    int     getEndMonth       (){return mEndMonth       ;}
    int     getEndDay         (){return mEndDay         ;}

    void setIsNeedBackup   (bool     value){ if(value == mIsNeedBackup   ) return; mIsNeedBackup    = value; emit signalEventChangedIsNeedBackup   (value);}
    void setIsProc         (bool     value){ if(value == mIsProc         ) return; mIsProc          = value; emit signalEventChangedIsProc         (value);}
    void setIsShowInterface(bool     value){ if(value == mIsShowInterface) return; mIsShowInterface = value; emit signalEventChangedIsShowInterface(value);}
    void setTotalCnt       (quint64  value){ if(value == mTotalCnt       ) return; mTotalCnt        = value; emit signalEventChangedTotalCnt       (value);}
    void setCurrentIdx     (quint64  value){ if(value == mCurrentIdx     ) return; mCurrentIdx      = value; emit signalEventChangedCurrentIdx     (value);}
    void setStartYear      (int      value){ if(value == mStartYear      ) return; mStartYear       = value; emit signalEventChangedStartYear      (value);}
    void setStartMonth     (int      value){ if(value == mStartMonth     ) return; mStartMonth      = value; emit signalEventChangedStartMonth     (value);}
    void setStartDay       (int      value){ if(value == mStartDay       ) return; mStartDay        = value; emit signalEventChangedStartDay       (value);}
    void setEndYear        (int      value){ if(value == mEndYear        ) return; mEndYear         = value; emit signalEventChangedEndYear        (value);}
    void setEndMonth       (int      value){ if(value == mEndMonth       ) return; mEndMonth        = value; emit signalEventChangedEndMonth       (value);}
    void setEndDay         (int      value){ if(value == mEndDay         ) return; mEndDay          = value; emit signalEventChangedEndDay         (value);}

    explicit PanelBackupModel(QObject *parent = nullptr);
    int checkMaxDay(int year, int month);

signals:
    void signalEventChangedIsNeedBackup   (bool     value);
    void signalEventChangedIsProc         (bool     value);
    void signalEventChangedIsShowInterface(bool     value);
    void signalEventChangedTotalCnt       (quint64  value);
    void signalEventChangedCurrentIdx     (quint64  value);
    void signalEventChangedStartYear      (int      value);
    void signalEventChangedStartMonth     (int      value);
    void signalEventChangedStartDay       (int      value);
    void signalEventChangedEndYear        (int      value);
    void signalEventChangedEndMonth       (int      value);
    void signalEventChangedEndDay         (int      value);

    void signalEventComplete              (int      error);

    void signalCommandSetIsNeedBackup     (bool     value);

public slots:
    void onCommandShowInterface();
    void onCommandCloseInterface();
    void onCommandSetStartDate(int year, int month, int day);
    void onCommandSetEndDate(int year, int month, int day);
    void onCommandBackup();
    void onCommandCancle();
    void onCommandUpdate();

    void onThreadFinish();


};

#endif // PANELBACKUPMODEL_H
