#ifndef PRODUCTSPROVIDER_H
#define PRODUCTSPROVIDER_H

#include <QObject>
#include <QDateTime>
#include <QApplication>
#include "source/service/def/filedef.h"
#include "source/service/util/exceptionutil.h"
#include "source/service/includesvcdto.h"
#include "source/service/util/filefolderreader.h"
#include "source/service/util/filewriterex.h"
#include "source/service/util/filereaderex.h"

#define pProductSP ProductSProvider::getInstance()

class ProductSProvider : public QObject
{
    Q_OBJECT

public:
    static ProductSProvider * getInstance()
    {
        static ProductSProvider *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new ProductSProvider();
        }

        return mpSelf;
    }

    bool                       mIsRunning      = false;
    QList<PDSettingDto *>      mPDList         ;
    PDSettingDto               mCurrPD         ;
    quint64                    mLastSeq        = 0;

    explicit ProductSProvider(QObject * parent = nullptr):QObject(parent)
    {
    }
    ~ProductSProvider()
    {
        stop();
    }

    void start()
    {
        qDebug() << "[ProductSProvider::start]";

        mCurrPD.setDefaultValue();

        loadPDFolder();

        if(getPDCount() < 1)
        {
            PDSettingDto setting;
            setting.setDefaultValue();
            internalAddPD(setting);
        }

        if(mCurrPD.mSeq == 0 && getPD(0) != nullptr)
        {
            internalSelectPD(getPD(0)->mSeq);
        }

        mIsRunning = true;

        qDebug() << "[ProductSProvider::started]";

        emit signalEventStarted();
    }

    void stop()
    {
        mIsRunning = false;

        foreach(PDSettingDto * ptr, mPDList)
        {
            delete ptr;
        }
        mPDList.clear();

        emit signalEventStopped();
    }

    void factoryReset()
    {
        CHECK_FALSE_RETURN(mIsRunning)

        QDir(FileDef::PD_SETTING_LAST_SEQ_DIR()).removeRecursively();
        QDir(FileDef::PD_SETTING_SEL_SEQ_DIR()).removeRecursively();
        QDir(FileDef::PD_SETTING_DIR()).removeRecursively();

        mLastSeq = 0;

        stop();
    }

    int getPDCount()
    {
        return mPDList.size();
    }

    PDSettingDto * getPD(int idx)
    {
        if(idx < mPDList.size())
        {
            return mPDList[idx];
        }

        return nullptr;
    }

    PDSettingDto * findPD(quint64 seq)
    {
        foreach(PDSettingDto * ptr, mPDList)
        {
            if(ptr->mSeq == seq)
                return ptr;
        }

        return nullptr;
    }

    PDSettingDto * findPDByNum(quint16 num)
    {
        foreach(PDSettingDto * ptr, mPDList)
        {
            if(ptr->mDspForm.mCommSetting.mProductNum == num)
                return ptr;
        }

        return nullptr;
    }

    EnumDef::ePDError addPD(PDSettingDto& setting)
    {
        if(mIsRunning == false)
            return EnumDef::PDERR_FILE_WRITE;

        EnumDef::ePDError ret = internalAddPD(setting);

        if(ret == EnumDef::PDERR_NONE)
            emit signalEventAddedPDSetting(setting);

        return ret;
    }

    EnumDef::ePDError editPD(PDSettingDto setting)
    {
        if(mIsRunning == false)
            return EnumDef::PDERR_FILE_WRITE;

        PDSettingDto * editPd = findPD(setting.mSeq);

        if(editPd == nullptr)
        {
            return EnumDef::PDERR_NOT_EXIST;
        }

        PDSettingDto * checkSameNum = findPDByNum(setting.mDspForm.mCommSetting.mProductNum);

        if(checkSameNum != nullptr && checkSameNum->mSeq != setting.mSeq)
        {
            return EnumDef::PDERR_SAME_PD_NUM;
        }

        if(FileWriterEx::newWrite(FileDef::PD_SETTING_DIR(), QString("%1.txt").arg(setting.mSeq), setting.toString("\n")) == false)
            return EnumDef::PDERR_FILE_WRITE;

        *editPd = setting;

        emit signalEventChangedPDSetting(setting);

        if(setting.mSeq == mCurrPD.mSeq)
        {
            mCurrPD = setting;
            emit signalEventChangedCurrPDSetting(setting);
        }

        return EnumDef::PDERR_NONE;
    }

    EnumDef::ePDError removePD(quint64 seq)
    {
        if(mIsRunning == false)
            return EnumDef::PDERR_FILE_WRITE;

        if(seq == mCurrPD.mSeq)
            return EnumDef::PDERR_SELECTED;

        for(int i = 0; i < mPDList.size(); i ++)
        {
            if(mPDList[i]->mSeq == seq)
            {
                if(QFile::remove(QString("%1/%2.txt").arg(FileDef::PD_SETTING_DIR()).arg(seq)) == false)
                    return EnumDef::PDERR_FILE_WRITE;

                delete mPDList[i];
                mPDList.removeAt(i);

                emit signalEventRemovedPDSetting(seq);
                return EnumDef::PDERR_NONE;
            }
        }

        return EnumDef::PDERR_NOT_EXIST;
    }

    EnumDef::ePDError selectPD(quint64 seq)
    {
        if(mIsRunning == false)
            return EnumDef::PDERR_FILE_WRITE;

        if(mCurrPD.mSeq == seq)
            return EnumDef::PDERR_NONE;

        EnumDef::ePDError ret = internalSelectPD(seq);

        if(ret == EnumDef::PDERR_NONE)
            emit signalEventChangedCurrPDSetting(mCurrPD);

        return ret;
    }

    PDSettingDto getDummyPD()
    {
        unsigned short pdNewNum;
        PDSettingDto dummy;

        for(pdNewNum = 1; pdNewNum <= mPDList.size(); pdNewNum ++)
        {
            if(findPDByNum(pdNewNum) == nullptr)
                break;
        }

        //if(mPDList.size() > 0)
        dummy = mCurrPD;//*mPDList[mPDList.size() -1];

        dummy.mSeq = 0;
        dummy.mName = " ";
        dummy.mDspForm.mCommSetting.mProductNum = pdNewNum;
        dummy.mDspForm.mWCSetting.mDynamicFactor = 10000000;
        return dummy;
    }

signals:
    void signalEventStarted                         ();
    void signalEventStopped                         ();
    void signalEventAddedPDSetting                  (PDSettingDto dto);
    void signalEventChangedPDSetting                (PDSettingDto dto);
    void signalEventRemovedPDSetting                (quint64      seq);
    void signalEventChangedCurrPDSetting            (PDSettingDto dto);

private:
    void loadPDFolder()
    {
        quint64 maxSeq = 0;

        FileFolderReader folder;

        folder.open(FileDef::PD_SETTING_DIR(), "*.txt");

        for(int i = 0; i < folder.fileCount(); i ++)
        {
            PDSettingDto * pd = new PDSettingDto();

            if(pd->setValue(folder.readFile(i), "\n") == true)
            {
                qDebug() << "[ProductSProvider::loadPDFolder]" << pd->toString("\n");

                if(maxSeq < pd->mSeq)
                    maxSeq = pd->mSeq;

                mPDList.append(pd);
            }
            else
            {
                qDebug() << "[ProductSProvider::loadPDFolder]invaild value";
                delete pd;
            }
        }

        mLastSeq = FileReaderEx::readAll(FileDef::PD_SETTING_LAST_SEQ_DIR(), FileDef::PD_SETTING_LAST_SEQ_FILENAME()).toULongLong();

        if(mLastSeq < maxSeq)
        {
            mLastSeq = maxSeq;
        }

        quint64 selSeq = FileReaderEx::readAll(FileDef::PD_SETTING_SEL_SEQ_DIR(), FileDef::PD_SETTING_SEL_SEQ_FILENAME()).toULongLong();

        PDSettingDto * pSelPD =  findPD(selSeq);

        if(pSelPD != nullptr)
            mCurrPD = *pSelPD;
    }

    EnumDef::ePDError internalAddPD(PDSettingDto& setting)
    {
        if(findPDByNum(setting.mDspForm.mCommSetting.mProductNum) != nullptr)
        {
            return EnumDef::PDERR_SAME_PD_NUM;
        }

        mLastSeq++;
        setting.mSeq = mLastSeq;

        if(FileWriterEx::newWrite(FileDef::PD_SETTING_DIR(), QString("%1.txt").arg(mLastSeq), setting.toString("\n")) == false)
        {
            return EnumDef::PDERR_FILE_WRITE;
        }

        FileWriterEx::newWrite(FileDef::PD_SETTING_LAST_SEQ_DIR(), FileDef::PD_SETTING_LAST_SEQ_FILENAME(), QString("%1").arg(mLastSeq));

        PDSettingDto * newPD = new PDSettingDto(setting);
        mPDList.append(newPD);

        return EnumDef::PDERR_NONE;
    }

    EnumDef::ePDError internalSelectPD(quint64 seq)
    {
        if(mCurrPD.mSeq == seq)
            return EnumDef::PDERR_NONE;

        PDSettingDto * oldSelPd  = findPD(mCurrPD.mSeq);
        PDSettingDto * newSelPd  = findPD(seq);

        if(newSelPd == nullptr)
            return EnumDef::PDERR_NOT_EXIST;

        if(FileWriterEx::newWrite(FileDef::PD_SETTING_SEL_SEQ_DIR(), FileDef::PD_SETTING_SEL_SEQ_FILENAME(), QString("%1").arg(seq)) == false)
            return EnumDef::PDERR_FILE_WRITE;

        if(oldSelPd != nullptr)
            * oldSelPd = mCurrPD;

        mCurrPD    = * newSelPd;

        return EnumDef::PDERR_NONE;
    }
};

#endif // PRODUCTSPROVIDER_H
