#include "filereader.h"

#include <QDebug>

FileReader::FileReader(QObject *parent) : QObject(parent)
{

}

FileReader::~FileReader()
{
    if(mFile.isOpen())
        mFile.close();
}

QStringList FileReader::readAll(QString path, QString fileName)
{
    QStringList lines;
    mFile.setFileName(QString("%1/%2.txt").arg(path).arg(fileName));
    mFile.open(QIODevice::ReadOnly | QIODevice::Text );

    if(mFile.isOpen() == false)
    {
        qDebug() << "[readAll] file name =" << QString("%1/%2").arg(path).arg(fileName) << ",occured exception, file name = " <<  mFile.errorString();
        return lines;
    }

    mStream.setDevice(&mFile);

    while(mStream.atEnd() == false)
    {
        lines.append(mStream.readLine());
    }

    close();
    return lines;
}

void FileReader::close()
{
    if(mFile.isOpen())
        mFile.close();
}

