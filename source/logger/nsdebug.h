#ifndef NSDEBUG_H
#define NSDEBUG_H

#include <QObject>
#include <typeinfo>
#include <QMutex>
#include <QFile>
#include <QTextStream>

class NSDebug : public QObject
{
    Q_OBJECT
public:
    explicit NSDebug(QObject *parent = nullptr);

    static void startService();
    static void stopService();
    static void debugMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
    static void factoryReset();

private:
    static NSDebug * mpSelf;
    QMutex mutex;
    QFile mfile;
    QTextStream mOut;

};

#endif // NSDEBUG_H
