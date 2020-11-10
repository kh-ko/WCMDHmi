#include "productsettingservice.h"

#include <QApplication>
#include <QDebug>

#include "source/globaldef/EnumDefine.h"

void ProductSettingService::load()
{
    qDebug() << "[ProductSettingService::load]";
    emit signalCommandLastSeqLoad(mLastSeqPath, mLastSeqFileName);
}

void ProductSettingService::onSignalEventLoadedLastSeq(QString fileName, QString content)
{
    qDebug() << "[ProductSettingService::onSignalEventLoadedLastSeq]" << content;
    mLastSeq = content.toULongLong();
}

void ProductSettingService::onSignalEventCompleteLoadLastSeq(int error)
{
    if(error == EnumDefine::FileErrorType::FILE_ERROR_NOT_EXIST)
    {
        qDebug() << "[ProductSettingService::onSignalEventLoadedLastSeq]Can not found file";
    }

    emit signalCommandProductSettingLoad  (mProductSettingPath, "*");
}

void ProductSettingService::onSignalEventLoadedProductSetting(QString fileName, QString content)
{
    qDebug() << "[ProductSettingService::onSignalEventLoadedProductSetting]" << fileName;

    if(fileName.toULongLong() == 0)
        return;

    ProductSettingModel * newProductSettingModel = new ProductSettingModel(this);
    newProductSettingModel->setStringValue(content, "\n");

    if(mMaxSeq < newProductSettingModel->mSeq)
    {
        mMaxSeq = newProductSettingModel->mSeq;
    }

    int listIdx = 0;
    for(listIdx = 0; listIdx < mListProductSetting.size(); listIdx ++)
    {
        if(mListProductSetting.at(listIdx)->mNo > newProductSettingModel->mNo)
        {
            mListProductSetting.insert(listIdx, newProductSettingModel);
            break;
        }
    }

    if(listIdx == mListProductSetting.size())
        mListProductSetting.append(newProductSettingModel);
}

void ProductSettingService::onSignalEventCompleteLoadProductSetting  (int error)
{
    if(mListProductSetting.size() == 0)
    {
        qDebug() << "[ProductSettingService::onSignalEventCompleteLoadProductSetting] empty product setting";

        quint64 seq;
        quint16 wcNgMotion = EnumDefine::NGMotion::NG_MOTION_REJECT_02;
        quint16 mdNgMotion = EnumDefine::NGMotion::NG_MOTION_REJECT_02;

        addProductSetting(&seq, 1,"product", 250, 40, 1000, 90000, 90000, 92000, 94000, 94000, 0, wcNgMotion, 1, 10000000, 9999, mdNgMotion);
    }

    emit signalCommandSelectSeqLoad(mSelectSeqPath,mSelectSeqFileName);
}


void ProductSettingService::onSignalEventLoadedSelectSeq(QString fileName, QString content)
{
    qDebug() << "[ProductSettingService::onSignalEventLoadedSelectSeq]" << content;

    ProductSettingModel * pProductSetting = nullptr;
    quint64 selectedSeq = content.toULongLong();

    pProductSetting = findProductSettingBySeq(selectedSeq);

    if(pProductSetting != nullptr)
    {
        selectProductSetting(selectedSeq);
    }
}

void ProductSettingService::onSignalEventCompleteLoadSelectSeq(int error)
{
    if(mCurrentProductSetting.mSeq == 0)
    {
        qDebug() << "[ProductSettingService::onSignalEventCompleteLoadSelectSeq] did not select product setting";

        if(mListProductSetting.size() < 1)
        {
            qDebug() << "[ProductSettingService::onSignalEventCompleteLoadSelectSeq] empty product setting";
        }
        else
        {
            qDebug() << "[ProductSettingService::onSignalEventCompleteLoadSelectSeq] select first product setting";

            selectProductSetting(mListProductSetting.at(0)->mSeq);
        }
    }

    emit signalEventCompleteLoad();
}

int  ProductSettingService::addProductSetting(quint64 *seq                 ,
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
                                              quint16 wcEnableEtcError     ,
                                              quint32 dynamicFactor        ,
                                              quint16 mdSenstivity         ,
                                              quint16 mdNGMotion           )
{
    qDebug() << "[ProductSettingService::addProductSetting]";

    FileWriter fw;

    if(findProductSettingByNo(no) != nullptr)
    {
        qDebug() << "[ProductSettingService::addProductSetting]already exist product_no : " << no;
        return EnumDefine::DatabaseErrorType::ALREADY_NO_ERROR;
    }

    *seq =generationSeq();

    ProductSettingModel * ps = new ProductSettingModel(this);
    ps->mSeq                   = *seq                 ;
    ps->mNo                    = no                   ;
    ps->mName                  = name                 ;
    ps->mLength                = length               ;
    ps->mSpeed                 = speed                ;
    ps->mMotorAccelerationTime = motorAccelerationTime;
    ps->mUnderWeight           = underWeight          ;
    ps->mUnderWarningWeight    = underWarningWeight   ;
    ps->mNormalWeight          = normalWeight         ;
    ps->mOverWarningWeight     = overWarningWeight    ;
    ps->mOverWeight            = overWeight           ;
    ps->mTareWeight            = tareWeight           ;
    ps->mWCNGMotion            = wcNGMotion           ;
    ps->mWCEnableEtcError      = wcEnableEtcError     ;
    ps->mDynamicFactor         = dynamicFactor        ;
    ps->mMDSenstivity          = mdSenstivity         ;
    ps->mMDNGMotion            = mdNGMotion           ;

    if(fw.newWrite(mProductSettingPath, QString("%1").arg(ps->mSeq), ps->toString("\n")) == true)
    {
        if(mMaxSeq < ps->mSeq)
            mMaxSeq = ps->mSeq;

        int listIdx = 0;
        for(listIdx = 0; listIdx < mListProductSetting.size(); listIdx ++)
        {
            if(mListProductSetting.at(listIdx)->mNo > ps->mNo)
            {
                mListProductSetting.insert(listIdx, ps);
                break;
            }
        }

        if(listIdx == mListProductSetting.size())
            mListProductSetting.append(ps);
    }
    else
    {
        qDebug() << "[ProductSettingService::addProductSetting]can not file write";

        delete ps;
        return EnumDefine::DatabaseErrorType::SQL_ERROR;
    }
    return EnumDefine::DatabaseErrorType::DB_NONE_ERROR;
}

int  ProductSettingService::editProductSetting(quint64 seq                  ,
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
                                               quint16 wcEnableEtcError     ,
                                               quint32 dynamicFactor        ,
                                               quint16 mdSenstivity         ,
                                               quint16 mdNGMotion           )
{
    qDebug() << "[ProductSettingService::editProductSetting]";

    int retError = EnumDefine::DatabaseErrorType::DB_NONE_ERROR;
    FileWriter fw;
    ProductSettingModel *ps = findProductSettingBySeq(seq);

    if(ps == nullptr)
    {
        qDebug() << "[ProductSettingService::editProductSetting]not exist product_seq" << seq;
        return EnumDefine::DatabaseErrorType::NOT_EXIST_SEQ;
    }

    if(findProductSettingByNoWithoutSeq(no, seq) != nullptr)
    {
        qDebug() << "[ProductSettingService::editProductSetting]already exist product_no : " << no;
        return EnumDefine::DatabaseErrorType::ALREADY_NO_ERROR;
    }

    ProductSettingModel * tempPs = new ProductSettingModel(this);
    tempPs->mSeq                   = seq                 ;
    tempPs->mNo                    = no                   ;
    tempPs->mName                  = name                 ;
    tempPs->mLength                = length               ;
    tempPs->mSpeed                 = speed                ;
    tempPs->mMotorAccelerationTime = motorAccelerationTime;
    tempPs->mUnderWeight           = underWeight          ;
    tempPs->mUnderWarningWeight    = underWarningWeight   ;
    tempPs->mNormalWeight          = normalWeight         ;
    tempPs->mOverWarningWeight     = overWarningWeight    ;
    tempPs->mOverWeight            = overWeight           ;
    tempPs->mTareWeight            = tareWeight           ;
    tempPs->mWCNGMotion            = wcNGMotion           ;
    tempPs->mWCEnableEtcError      = wcEnableEtcError     ;
    tempPs->mDynamicFactor         = dynamicFactor        ;
    tempPs->mMDSenstivity          = mdSenstivity         ;
    tempPs->mMDNGMotion            = mdNGMotion           ;

    if(fw.newWrite(mProductSettingPath, QString("%1").arg(tempPs->mSeq), tempPs->toString("\n")) == true)
    {
        ps->setSeq                  (seq                  );
        ps->setNo                   (no                   );
        ps->setName                 (name                 );
        ps->setLength               (length               );
        ps->setSpeed                (speed                );
        ps->setMotorAccelerationTime(motorAccelerationTime);
        ps->setUnderWeight          (underWeight          );
        ps->setUnderWarningWeight   (underWarningWeight   );
        ps->setNormalWeight         (normalWeight         );
        ps->setOverWarningWeight    (overWarningWeight    );
        ps->setOverWeight           (overWeight           );
        ps->setTareWeight           (tareWeight           );
        ps->setWCNGMotion           (wcNGMotion           );
        ps->setWCEnableEtcError     (wcEnableEtcError     );
        ps->setDynamicFactor        (dynamicFactor        );
        ps->setMDSenstivity         (mdSenstivity         );
        ps->setMDNGMotion           (mdNGMotion           );

        if(mCurrentProductSetting.mSeq == seq)
        {
            mCurrentProductSetting = ps;
        }
    }
    else
    {
        qDebug() << "[ProductSettingService::editProductSetting]can not file write";
        retError = EnumDefine::DatabaseErrorType::SQL_ERROR;
    }

    delete tempPs;
    return retError;
}

int  ProductSettingService::removeProductSetting(quint64 seq)
{
    qDebug() << "[ProductSettingService::removeProductSetting]";

    int retError = EnumDefine::DatabaseErrorType::DB_NONE_ERROR;
    FileWriter fw;
    ProductSettingModel *ps = findProductSettingBySeq(seq);

    if(ps == nullptr)
    {
        qDebug() << "[ProductSettingService::removeProductSetting]not exist product_seq" << seq;
        return EnumDefine::DatabaseErrorType::NOT_EXIST_SEQ;
    }

    if(seq == mCurrentProductSetting.mSeq)
    {
        qDebug() << "[ProductSettingService::removeProductSetting]can not remove selected setting";
        return EnumDefine::DatabaseErrorType::REMOVE_SEL_PRODUCT;
    }

    fw.remove(mProductSettingPath, QString("%1").arg(seq));

    for(int i = 0; i < mListProductSetting.size(); i ++)
    {
        if(mListProductSetting.at(i)->mSeq == seq)
        {
            delete mListProductSetting.at(i);
            mListProductSetting.removeAt(i);
            break;
        }
    }

    return retError;
}

int  ProductSettingService::selectProductSetting(quint64 seq)
{
    qDebug() << "[ProductSettingService::selectProductSetting]";

    int retError = EnumDefine::DatabaseErrorType::DB_NONE_ERROR;

    if(mCurrentProductSetting.mSeq == seq)
        return retError;

    FileWriter fw;
    ProductSettingModel *ps = findProductSettingBySeq(seq);

    if(ps == nullptr)
    {
        qDebug() << "[ProductSettingService::selectProductSetting]not exist product_seq" << seq;

        return EnumDefine::DatabaseErrorType::NOT_EXIST_SEQ;
    }


    if(fw.newWrite(mSelectSeqPath, mSelectSeqFileName, QString("%1").arg(seq)) == false)
    {
        qDebug() << "[ProductSettingService::selectProductSetting]can not write file" << seq;
    }
    else
    {
        mCurrentProductSetting = ps;
    }

    return retError;
}

ProductSettingModel * ProductSettingService::newProductSetting()
{
    int newNo;
    ProductSettingModel * newProduct = new ProductSettingModel(this);

    for(newNo = 1; newNo <= mListProductSetting.size(); newNo ++)
    {
        if((newNo) < mListProductSetting.at(newNo - 1)->mNo)
        {
            break;
        }
    }

    newProduct->setNo                   (newNo);
    newProduct->setName                 ("Product"                                                                     );
    newProduct->setLength               (mListProductSetting.at(mListProductSetting.size() - 1)->mLength               );
    newProduct->setSpeed                (mListProductSetting.at(mListProductSetting.size() - 1)->mSpeed                );
    newProduct->setMotorAccelerationTime(mListProductSetting.at(mListProductSetting.size() - 1)->mMotorAccelerationTime);
    newProduct->setUnderWeight          (mListProductSetting.at(mListProductSetting.size() - 1)->mUnderWeight          );
    newProduct->setUnderWarningWeight   (mListProductSetting.at(mListProductSetting.size() - 1)->mUnderWarningWeight   );
    newProduct->setNormalWeight         (mListProductSetting.at(mListProductSetting.size() - 1)->mNormalWeight         );
    newProduct->setOverWarningWeight    (mListProductSetting.at(mListProductSetting.size() - 1)->mOverWarningWeight    );
    newProduct->setOverWeight           (mListProductSetting.at(mListProductSetting.size() - 1)->mOverWeight           );
    newProduct->setTareWeight           (mListProductSetting.at(mListProductSetting.size() - 1)->mTareWeight           );
    newProduct->setWCNGMotion           (mListProductSetting.at(mListProductSetting.size() - 1)->mWCNGMotion           );
    newProduct->setWCEnableEtcError     (mListProductSetting.at(mListProductSetting.size() - 1)->mWCEnableEtcError     );
    newProduct->setDynamicFactor        (mListProductSetting.at(mListProductSetting.size() - 1)->mDynamicFactor        );
    newProduct->setMDSenstivity         (mListProductSetting.at(mListProductSetting.size() - 1)->mMDSenstivity         );
    newProduct->setMDNGMotion           (mListProductSetting.at(mListProductSetting.size() - 1)->mMDNGMotion           );

    return newProduct;
}
void ProductSettingService::factoryReset()
{
    qDebug() << "[ProductSettingService::factoryReset]";

    QDir(mLastSeqPath).removeRecursively();
    QDir(mProductSettingPath).removeRecursively();
    QDir(mSelectSeqPath).removeRecursively();
}
quint64 ProductSettingService::generationSeq()
{
    mLastSeq ++;

    FileWriter fw;

    if(mMaxSeq >= mLastSeq)
        mLastSeq = mMaxSeq + 1;

    if(fw.newWrite(mLastSeqPath, mLastSeqFileName, QString("%1").arg(mLastSeq)) == false)
    {
        qDebug() << "[ProductSettingService::generationSeq]can not write file";
    }

    qDebug() << "[ProductSettingService::generationSeq]seq :" << mLastSeq;

    return mLastSeq;
}

ProductSettingModel * ProductSettingService::findProductSettingBySeq(quint64 seq)
{
    for(int i = 0; i < mListProductSetting.size(); i ++)
    {
        if(mListProductSetting.at(i)->mSeq == seq)
            return mListProductSetting.at(i);
    }

    return nullptr;
}

ProductSettingModel * ProductSettingService::findProductSettingByNo(quint16 no)
{
    for(int i = 0; i < mListProductSetting.size(); i ++)
    {
        if(mListProductSetting.at(i)->mNo == no)
            return mListProductSetting.at(i);
    }

    return nullptr;
}

ProductSettingModel * ProductSettingService::findProductSettingByNoWithoutSeq(quint16 no, quint64 seq)
{
    for(int i = 0; i < mListProductSetting.size(); i ++)
    {
        if(mListProductSetting.at(i)->mNo == no && mListProductSetting.at(i)->mSeq != seq)
            return mListProductSetting.at(i);
    }

    return nullptr;
}

ProductSettingService::ProductSettingService(QObject *parent) : QObject(parent)
{
    qDebug() << "[ProductSettingService::Create]";

    QString applicationPath = QApplication::applicationDirPath();

    mLastSeqPath        = QString("%1/database/product/last_seq"    ).arg(applicationPath);
    mLastSeqFileName    = QString("last_seq");
    mProductSettingPath = QString("%1/database/product/product_setting").arg(applicationPath);
    mSelectSeqPath      = QString("%1/database/product/select_seq" ).arg(applicationPath);
    mSelectSeqFileName  = QString("select_seq" );

    connect(this, SIGNAL(signalCommandLastSeqLoad        (QString, QString)), &mLastSeqFileLoad       , SLOT(onCommandLoadAll(QString, QString)));
    connect(this, SIGNAL(signalCommandProductSettingLoad (QString, QString)), &mProductSettingFileLoad, SLOT(onCommandLoadAll(QString, QString)));
    connect(this, SIGNAL(signalCommandSelectSeqLoad      (QString, QString)), &mSelectSeqFileLoad     , SLOT(onCommandLoadAll(QString, QString)));

    connect(&mLastSeqFileLoad       , SIGNAL(signalEventLoadedFile  (QString, QString)), this, SLOT(onSignalEventLoadedLastSeq             (QString, QString)));
    connect(&mLastSeqFileLoad       , SIGNAL(signalEventCompleteLoad(int             )), this, SLOT(onSignalEventCompleteLoadLastSeq       (int             )));
    connect(&mProductSettingFileLoad, SIGNAL(signalEventLoadedFile  (QString, QString)), this, SLOT(onSignalEventLoadedProductSetting      (QString, QString)));
    connect(&mProductSettingFileLoad, SIGNAL(signalEventCompleteLoad(int             )), this, SLOT(onSignalEventCompleteLoadProductSetting(int             )));
    connect(&mSelectSeqFileLoad     , SIGNAL(signalEventLoadedFile  (QString, QString)), this, SLOT(onSignalEventLoadedSelectSeq            (QString, QString)));
    connect(&mSelectSeqFileLoad     , SIGNAL(signalEventCompleteLoad(int             )), this, SLOT(onSignalEventCompleteLoadSelectSeq      (int             )));
}
