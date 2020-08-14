#ifndef MYALLOC_H
#define MYALLOC_H

#include <QObject>
#include <QMutex>

class MyAlloc : public QObject
{
    Q_OBJECT
public:
    static MyAlloc * mSelf;
    static void * alloc(int size);
    static void free(void * ptr);

    QList<void *> mListAlloc;
    QMutex        mMutext;
    MyAlloc();
};

#endif // MYALLOC_H
