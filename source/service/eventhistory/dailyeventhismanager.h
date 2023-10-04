#ifndef EVENTHISMANAGER_H
#define EVENTHISMANAGER_H

#include <QObject>
#include <QProcess>
#include <QDateTime>
#include <QApplication>
#include "source/service/productsetting/productsprovider.h"
#include "source/service/def/filedef.h"
#include "source/service/def/datetimeform.h"
#include "source/service/util/filereaderex.h"
#include "source/service/util/filewriterex.h"

class DailyEventHisManager : public QObject
{
    Q_OBJECT

public:
    FileWriterEx       * mpWriter       = nullptr;

    explicit DailyEventHisManager(QObject * parent = nullptr):QObject(parent)
    {
    }
    ~DailyEventHisManager()
    {
        close();
    }

    void open(QDate today)
    {
        close();

        mpWriter = new FileWriterEx(this);
        mpWriter->open(FileDef::HISTORY_DIR(), QString("%1-EH.txt").arg(today.toString(DATE_FILE_NAME_FMT)), FileWriterEx::FILE_OPEN_APPENDWRITE);
    }

    void close()
    {
        if(mpWriter != nullptr)
        {
            mpWriter->close();
            delete mpWriter;
            mpWriter = nullptr;
        }
    }

    void addAppExitEventHis(QDateTime dateTime)
    {
        FileWriterEx fw;
        EventDto event;

        event.mDateTime = dateTime;
        event.mDspSeq = 0;
        event.mPDSeq = 0;
        event.mPDHisIdx = 0;
        event.mEType = EnumDef::ET_APP_EXIT;
        event.mEValue = 0;

        FileWriterEx::appendLine(FileDef::HISTORY_DIR(), QString("%1-EH.txt").arg(dateTime.toString(DATE_FILE_NAME_FMT)), event.toString());
    }

    void addAppStartEventHis(QDateTime dateTime)
    {
        FileWriterEx fw;
        EventDto event;

        event.mDateTime = dateTime;
        event.mDspSeq = 0;
        event.mPDSeq = 0;
        event.mPDHisIdx = 0;
        event.mEType = EnumDef::ET_APP_START;
        event.mEValue = 0;

        FileWriterEx::appendLine(FileDef::HISTORY_DIR(), QString("%1-EH.txt").arg(dateTime.toString(DATE_FILE_NAME_FMT)), event.toString());
    }


    void addEventHis(EventDto event)
    {
        CHECK_FALSE_RETURN((mpWriter != nullptr));

        mpWriter->appendLine(event.toString());
    }
};

#endif // EVENTHISMANAGER_H
