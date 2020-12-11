#ifndef DAILYPDHISMANAGER_H
#define DAILYPDHISMANAGER_H

#include <QObject>
#include <QDateTime>
#include <QApplication>
#include "source/service/productsetting/productsprovider.h"
#include "source/service/def/filedef.h"
#include "source/service/def/datetimeform.h"
#include "source/service/util/filereaderex.h"
#include "source/service/util/filewriterex.h"

class DailyPDHisManager : public QObject
{
    Q_OBJECT

public:
    int                  mEventCnt      = 0;
    FileWriterEx       * mpWriter       = nullptr;

    PDSettingDto         mLastPDSetting ;

    explicit DailyPDHisManager(QObject * parent = nullptr):QObject(parent)
    {
    }
    ~DailyPDHisManager()
    {
        close();
    }

    void open(QDate today)
    {
        QString line;

        close();

        FileReaderEx reader;

        if(reader.open(FileDef::HISTORY_DIR(), QString("%1-PH.txt").arg(today.toString(DATE_FILE_NAME_FMT))) == true)
        {
            while(reader.readLine(line))
            {
                mEventCnt++;
            }
        }

        reader.close();

        mpWriter = new FileWriterEx(this);
        mpWriter->open(FileDef::HISTORY_DIR(), QString("%1-PH.txt").arg(today.toString(DATE_FILE_NAME_FMT)), FileWriterEx::FILE_OPEN_APPENDWRITE);

        addPDHis(pProductSP->mCurrPD);
    }

    void close()
    {
        if(mpWriter != nullptr)
        {
            mpWriter->close();
            delete mpWriter;
            mpWriter = nullptr;
        }

        mEventCnt = 0;
    }

    void writePDHis(PDSettingDto setting)
    {
        CHECK_FALSE_RETURN((mpWriter != nullptr));

        mpWriter->appendLine(setting.toString(","));
    }

    void addPDHis(PDSettingDto setting)
    {
        CHECK_FALSE_RETURN((mpWriter != nullptr));

        mLastPDSetting = setting;
        mEventCnt++;
        writePDHis(setting);
    }
};

#endif // DAILYPDHISMANAGER_H
