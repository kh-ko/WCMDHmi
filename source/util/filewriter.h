#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QTextStream>

class FileWriter : public QObject
{
    Q_OBJECT
public:
    QFile mFile;
    QTextStream mStream;

    bool appendLine(QString path, QString fileName, QString content);
    bool overWriteLine(QString path, QString fileName, QString content, qint64 startOffset, int len);
    bool newWrite(QString path, QString fileName, QString content);
    bool remove(QString path, QString fileName);
    void close();
    void mkdirRecursively(QString path);
    explicit FileWriter(QObject *parent = nullptr);
    ~FileWriter();
signals:

};

#endif // FILEWRITER_H
