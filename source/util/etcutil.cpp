#include "etcutil.h"

#include <QDateTime>

EtcUtil::EtcUtil()
{

}

qint64 EtcUtil::getCurrentMSec()
{
    return QDateTime::currentDateTime().toMSecsSinceEpoch();
}

char * EtcUtil::toStringFromChar(QString str, int charBufferSize)
{
    const QByteArray stringData = str.toUtf8();
    char * pText;

    pText = (char *)malloc(charBufferSize);

    pText[qMin(charBufferSize - 1, stringData.size())]='\0';
    std::copy(stringData.constBegin(),stringData.constBegin()+qMin(charBufferSize - 1,stringData.size()),pText);

    return pText;
}

