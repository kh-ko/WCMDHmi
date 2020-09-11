#ifndef PRODUCTSETTINGSERVICE_H
#define PRODUCTSETTINGSERVICE_H

#include <QObject>

#include "source/model/productsettingmodel.h"
#include "source/util/fileloaderthread.h"
#include "source/util/filewriter.h"

class ProductSettingService : public QObject
{
    Q_OBJECT
public:
    QString mLastSeqPath        ;
    QString mLastSeqFileName    ;
    QString mProductSettingPath ;
    QString mSelectSeqPath      ;
    QString mSelectSeqFileName  ;
    FileLoaderThread mLastSeqFileLoad       ;
    FileLoaderThread mProductSettingFileLoad;
    FileLoaderThread mSelectSeqFileLoad     ;

    quint64 mLastSeq                                = 0;
    quint64 mMaxSeq                                 = 0;
    ProductSettingModel mCurrentProductSetting      ;
    QList<ProductSettingModel *> mListProductSetting;

    void load();

    int  addProductSetting(quint64 *seq                 ,
                           quint16 no                   ,
                           QString name                 ,
                           quint16 length               ,
                           quint16 speed                ,
                           quint32 motorAccelerationTime,
                           quint32 underWeight          ,
                           quint32 underWarningWeight   ,
                           quint32 normalWeight         ,
                           quint32 overWarningWeight    ,
                           quint32 overWeight           ,
                           quint32 tareWeight           ,
                           quint16 wcNGMotion           ,
                           quint32 dynamicFactor        ,
                           quint16 mdSenstivity         ,
                           quint16 mdNGMotion           );

    int  editProductSetting(quint64 seq                  ,
                            quint16 no                   ,
                            QString name                 ,
                            quint16 length               ,
                            quint16 speed                ,
                            quint32 motorAccelerationTime,
                            quint32 underWeight          ,
                            quint32 underWarningWeight   ,
                            quint32 normalWeight         ,
                            quint32 overWarningWeight    ,
                            quint32 overWeight           ,
                            quint32 tareWeight           ,
                            quint16 wcNGMotion           ,
                            quint32 dynamicFactor        ,
                            quint16 mdSenstivity         ,
                            quint16 mdNGMotion           );

    int  removeProductSetting(quint64 seq);
    int  selectProductSetting(quint64 seq);
    ProductSettingModel * newProductSetting();
    void factoryReset();


signals:
    void signalEventCompleteLoad();

// down layer ===================================================
signals:
    void signalCommandLastSeqLoad               (QString path, QString fileName);
    void signalCommandProductSettingLoad        (QString path, QString fileName);
    void signalCommandSelectSeqLoad             (QString path, QString fileName);

public slots:
    void onSignalEventLoadedLastSeq              (QString fileName, QString content);
    void onSignalEventCompleteLoadLastSeq        (int     error  );
    void onSignalEventLoadedProductSetting       (QString fileName, QString content);
    void onSignalEventCompleteLoadProductSetting (int     error  );
    void onSignalEventLoadedSelectSeq            (QString fileName, QString content);
    void onSignalEventCompleteLoadSelectSeq      (int     error  );

//internal layer ==================================================
public:
    quint64               generationSeq();
    ProductSettingModel * findProductSettingBySeq(quint64 seq);
    ProductSettingModel * findProductSettingByNo(quint16 no);
    ProductSettingModel * findProductSettingByNoWithoutSeq(quint16 no, quint64 seq);
    explicit ProductSettingService(QObject *parent = nullptr);


};
#endif // PRODUCTSETTINGSERVICE_H
