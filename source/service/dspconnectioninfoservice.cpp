#include "dspconnectioninfoservice.h"
#include <QApplication>
#include <QDebug>

#include "source/globaldef/EnumDefine.h"

void DspConnectionInfoService::load()
{
    qDebug() << "[DspConnectionInfoService::load]";
    emit signalCommandLastSeqLoad(mLastSeqPath, mLastSeqFileName);
}

void DspConnectionInfoService::onSignalEventLoadedLastSeq(QString fileName, QString content)
{
    qDebug() << "[DspConnectionInfoService::onSignalEventLoadedLastSeq]" << content;
    mLastSeq = content.toULongLong();
}

void DspConnectionInfoService::onSignalEventCompleteLoadLastSeq(int error)
{
    qDebug() << "[DspConnectionInfoService::onSignalEventCompleteLoadLastSeq]" ;

    if(error == EnumDefine::FileErrorType::FILE_ERROR_NOT_EXIST)
    {
        qDebug() << "[DspConnectionInfoService::onSignalEventCompleteLoadLastSeq]file read error" ;
    }

    emit signalCommandDspConnectionLoad(mDspConnectionPath, "*");
}

void DspConnectionInfoService::onSignalEventLoadedDspConnection(QString fileName, QString content)
{
    qDebug() << "[DspConnectionInfoService::onSignalEventLoadedDspConnection] fName : " << fileName << ", content :" << content;

    if(fileName.toULongLong() == 0)
        return;

    DspConnectionModel * newDspConnectionModel = new DspConnectionModel(this);
    newDspConnectionModel->setStringValue(content);

    if(mMaxSeq < newDspConnectionModel->mSeq)
    {
        mMaxSeq = newDspConnectionModel->mSeq;
    }

    int listIdx = 0;
    for(listIdx = 0; listIdx < mListDspConnection.size(); listIdx ++)
    {
        if(mListDspConnection.at(listIdx)->mSeq > newDspConnectionModel->mSeq)
        {
            mListDspConnection.insert(listIdx, newDspConnectionModel);
            break;
        }
    }

    if(listIdx == mListDspConnection.size())
        mListDspConnection.append(newDspConnectionModel);
}

void DspConnectionInfoService::onSignalEventCompleteLoadDspConnection(int error)
{
    qDebug() << "[DspConnectionInfoService::onSignalEventCompleteLoadDspConnection]";

    if(mListDspConnection.size() == 0)
    {
        qDebug() << "[DspConnectionInfoService::onSignalEventCompleteLoadDspConnection] can not found dsp connection file";

        quint64 seq;

        addDspConnection(&seq, "192.168.0.140", 10020);
    }

    emit signalEventCompleteLoad();
}

int  DspConnectionInfoService::addDspConnection(quint64 *seq, QString ip, quint16 port)
{
    qDebug() << "[DspConnectionInfoService::addDspConnection]";

    FileWriter fw;

    *seq =generationSeq();

    DspConnectionModel * dc = new DspConnectionModel(this);
    dc->mSeq  = *seq;
    dc->mIp   = ip  ;
    dc->mPort = port;

    if(fw.newWrite(mDspConnectionPath, QString("%1").arg(dc->mSeq), dc->toString()) == true)
    {
        if(mMaxSeq < dc->mSeq)
            mMaxSeq = dc->mSeq;

        int listIdx = 0;
        for(listIdx = 0; listIdx < mListDspConnection.size(); listIdx ++)
        {
            if(mListDspConnection.at(listIdx)->mSeq > dc->mSeq)
            {
                mListDspConnection.insert(listIdx, dc);
                break;
            }
        }

        if(listIdx == mListDspConnection.size())
            mListDspConnection.append(dc);
    }
    else
    {
        qDebug() << "[DspConnectionInfoService::addDspConnection]can not write file";
        delete dc;
        return EnumDefine::DatabaseErrorType::SQL_ERROR;
    }
    return EnumDefine::DatabaseErrorType::DB_NONE_ERROR;
}

int  DspConnectionInfoService::editDspConnection(quint64 seq, QString ip, quint16 port)
{
    qDebug() << "[DspConnectionInfoService::editDspConnection]";

    int retError = EnumDefine::DatabaseErrorType::DB_NONE_ERROR;
    FileWriter fw;
    DspConnectionModel *dc = findDspConnectionBySeq(seq);

    if(dc == nullptr)
    {
        qDebug() << "[DspConnectionInfoService::editDspConnection] can not found :" << seq;
        return EnumDefine::DatabaseErrorType::NOT_EXIST_SEQ;
    }

    DspConnectionModel * tempDc = new DspConnectionModel(this);
    tempDc->mSeq  = seq ;
    tempDc->mIp   = ip  ;
    tempDc->mPort = port;

    if(fw.newWrite(mDspConnectionPath, QString("%1").arg(tempDc->mSeq), tempDc->toString()) == true)
    {
        dc->mSeq  = seq ;
        dc->mIp   = ip  ;
        dc->mPort = port;
    }
    else
    {
        qDebug() << "[DspConnectionInfoService::editDspConnection]can not write file";
        retError = EnumDefine::DatabaseErrorType::SQL_ERROR;
    }

    delete tempDc;
    return retError;
}

int  DspConnectionInfoService::removeDspConnection(quint64 seq)
{
    qDebug() << "[DspConnectionInfoService::removeDspConnection]";

    int retError = EnumDefine::DatabaseErrorType::DB_NONE_ERROR;
    FileWriter fw;
    DspConnectionModel *ps = findDspConnectionBySeq(seq);

    if(ps == nullptr)
    {
        qDebug() << "[DspConnectionInfoService::removeDspConnection] can not found :" << seq;
        return EnumDefine::DatabaseErrorType::NOT_EXIST_SEQ;
    }

    if(fw.remove(mDspConnectionPath, QString("%1").arg(seq)) == false)
    {
        qDebug() << "[DspConnectionInfoService::editDspConnection]can not remove file";
        return EnumDefine::DatabaseErrorType::SQL_ERROR;
    }

    for(int i = 0; i < mListDspConnection.size(); i ++)
    {
        if(mListDspConnection.at(i)->mSeq == seq)
        {
            delete mListDspConnection.at(i);
            mListDspConnection.removeAt(i);
            break;
        }
    }

    return retError;
}

void DspConnectionInfoService::factoryReset()
{
    qDebug() << "[DspConnectionInfoService::factoryReset]";

    QDir(mLastSeqPath).removeRecursively();
    QDir(mDspConnectionPath).removeRecursively();
}

quint64 DspConnectionInfoService::generationSeq()
{
    mLastSeq ++;

    FileWriter fw;

    if(mMaxSeq >= mLastSeq)
        mLastSeq = mMaxSeq + 1;

    if(fw.newWrite(mLastSeqPath, mLastSeqFileName, QString("%1").arg(mLastSeq)) == false)
    {
        qDebug() << "[DspConnectionInfoService::generationSeq]can not write  file";
    }

    qDebug() << "[DspConnectionInfoService::generationSeq]" << mLastSeq;

    return mLastSeq;
}

DspConnectionModel * DspConnectionInfoService::findDspConnectionBySeq(quint64 seq)
{
    for(int i = 0; i < mListDspConnection.size(); i ++)
    {
        if(mListDspConnection.at(i)->mSeq == seq)
            return mListDspConnection.at(i);
    }

    return nullptr;
}

DspConnectionInfoService::DspConnectionInfoService(QObject *parent) : QObject(parent)
{
    qDebug() << "[DspConnectionInfoService::Create]";

    QString applicationPath = QApplication::applicationDirPath();

    mLastSeqPath        = QString("%1/database/dspconnection/last_seq"    ).arg(applicationPath);
    mLastSeqFileName    = QString("last_seq");
    mDspConnectionPath  = QString("%1/database/dspconnection/connection").arg(applicationPath);

    connect(this, SIGNAL(signalCommandLastSeqLoad      (QString, QString)), &mLastSeqFileLoad      , SLOT(onCommandLoadAll(QString, QString)));
    connect(this, SIGNAL(signalCommandDspConnectionLoad(QString, QString)), &mDspConnectionFileLoad, SLOT(onCommandLoadAll(QString, QString)));

    connect(&mLastSeqFileLoad      , SIGNAL(signalEventLoadedFile  (QString, QString)), this, SLOT(onSignalEventLoadedLastSeq            (QString, QString)));
    connect(&mLastSeqFileLoad      , SIGNAL(signalEventCompleteLoad(int             )), this, SLOT(onSignalEventCompleteLoadLastSeq      (int             )));
    connect(&mDspConnectionFileLoad, SIGNAL(signalEventLoadedFile  (QString, QString)), this, SLOT(onSignalEventLoadedDspConnection      (QString, QString)));
    connect(&mDspConnectionFileLoad, SIGNAL(signalEventCompleteLoad(int             )), this, SLOT(onSignalEventCompleteLoadDspConnection(int             )));
}

