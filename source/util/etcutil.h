#ifndef ETCUTIL_H
#define ETCUTIL_H

#include <QObject>

#define ABS(a) ((a) < 0 ? -1 * (a) : (a))

class EtcUtil
{
public:
    EtcUtil();
    static qint64 getCurrentMSec();
    static char * toStringFromChar(QString str, int charBufferSize);
};

#endif // ETCUTIL_H
