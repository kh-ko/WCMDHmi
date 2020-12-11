#ifndef FILEDEF_H
#define FILEDEF_H

#include <QObject>
#include <QApplication>

class FileDef: public QObject
{
    Q_OBJECT
public:
    explicit FileDef(QObject *parent = nullptr) : QObject(parent){}
    ~FileDef(){}

    static QString DSP_CONNINFO_DIR()
    {
        static QString dir = QString("%1/database/dspconnection/connection").arg(QApplication::applicationDirPath());
        return dir;
    }

    static QString DSP_CONNINFO_SEQ_DIR()
    {
        static QString dir = QString("%1/database/dspconnection/last_seq").arg(QApplication::applicationDirPath());
        return dir;
    }

    static QString DSP_CONNINFO_SEQ_FILENAME()
    {
        static QString file = "last_seq.txt";
        return file;
    }

    static QString PD_SETTING_LAST_SEQ_DIR()
    {
        static QString dir = QString("%1/database/product/last_seq").arg(QApplication::applicationDirPath());
        return dir;
    }

    static QString PD_SETTING_SEL_SEQ_DIR()
    {
        static QString dir = QString("%1/database/product/select_seq").arg(QApplication::applicationDirPath());
        return dir;
    }

    static QString PD_SETTING_DIR()
    {
        static QString dir = QString("%1/database/product/product_setting").arg(QApplication::applicationDirPath());
        return dir;
    }

    static QString PD_SETTING_LAST_SEQ_FILENAME()
    {
        static QString file = "last_seq.txt";
        return file;
    }

    static QString PD_SETTING_SEL_SEQ_FILENAME()
    {
        static QString file = "select_seq.txt";
        return file;
    }

    static QString DEFAULT_SETTING_DIR()
    {
        static QString dir = QString("%1/defaultvalue").arg(QApplication::applicationDirPath());
        return dir;
    }

    static QString DEFAULT_SETTING_FILENAME()
    {
        static QString file = "defaultvalue.txt";
        return file;
    }

    static QString HISTORY_DIR()
    {
        static QString dir = QString("%1/database/history").arg(QApplication::applicationDirPath());
        return dir;
    }

    static QString WORK_DIR()
    {
        static QString dir = QString("%1/database/work").arg(QApplication::applicationDirPath());
        return dir;
    }

    static QString WORK_FILENAME()
    {
        static QString file = "WORKING-EH.txt";
        return file;
    }

    static QString WC_GRAPH_DIR()
    {
        static QString dir = QString("%1/graph/weight").arg(QApplication::applicationDirPath());
        return dir;
    }

    static QString WC_GRAPH_FILENAME()
    {
        static QString file = "wcgraph.txt";
        return file;
    }
};

#endif // FILEDEF_H
