#ifndef MYALLOC_H
#define MYALLOC_H

#include <QObject>
#include <QMutex>

class MyAlloc : public QObject
{
    Q_OBJECT
public:
    static MyAlloc * mSelf;
    static void * myAlloc(int size);
    static void myFree(void * ptr);

    QList<void *> mListAlloc;
    QMutex        mMutext;
    MyAlloc();
};

#endif // MYALLOC_H
