#ifndef DSPCONNECTIONINFOSERVICE_H
#define DSPCONNECTIONINFOSERVICE_H

#include <QObject>

#include "source/model/dspconnectionmodel.h"
#include "source/util/fileloaderthread.h"
#include "source/util/filewriter.h"

class DspConnectionInfoService : public QObject
{
    Q_OBJECT
public:
    QString mLastSeqPath        ;
    QString mLastSeqFileName    ;
    QString mDspConnectionPath  ;
    FileLoaderThread mLastSeqFileLoad      ;
    FileLoaderThread mDspConnectionFileLoad;

    quint64 mLastSeq                                = 0;
    quint64 mMaxSeq                                 = 0;
    QList<DspConnectionModel *> mListDspConnection;

    void load();

    int  addDspConnection   (quint64 *seq, QString ip, quint16 port);
    int  editDspConnection  (quint64 seq , QString ip, quint16 port);
    int  removeDspConnection(quint64 seq);
    void factoryReset();
signals:
    void signalEventCompleteLoad();

// down layer ===================================================
signals:
    void signalCommandLastSeqLoad  (QString path, QString fileName);
    void signalCommandDspConnectionLoad(QString path, QString fileName);

public slots:
    void onSignalEventLoadedLastSeq              (QString fileName, QString content);
    void onSignalEventCompleteLoadLastSeq        (int     error  );
    void onSignalEventLoadedDspConnection        (QString fileName, QString content);
    void onSignalEventCompleteLoadDspConnection  (int     error  );

//internal layer ==================================================
public:
    quint64               generationSeq();
    DspConnectionModel  * findDspConnectionBySeq(quint64 seq);
    explicit DspConnectionInfoService(QObject *parent = nullptr);


};
#endif // DSPCONNECTIONINFOSERVICE_H
