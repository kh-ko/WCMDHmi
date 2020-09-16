#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QTextStream>

class FileReader : public QObject
{
    Q_OBJECT
public:
    QFile mFile;
    QTextStream mStream;

    QStringList readAll(QString path, QString fileName);
    void close();
    explicit FileReader(QObject *parent = nullptr);
    ~FileReader();

};

#endif // FILEREADER_H
