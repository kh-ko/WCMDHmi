#include "myalloc.h"
#include <QDebug>

MyAlloc * MyAlloc::mSelf = nullptr;

void * MyAlloc::alloc(int size)
{
    bool doubleAlloc = false;

    mSelf->mMutext.lock();

    void * ptr = malloc(size);

    if(ptr != nullptr && ptr != NULL)
    {
        if(mSelf->mListAlloc.contains(ptr) == false)
            mSelf->mListAlloc.append(ptr);
        else
            doubleAlloc = true;
    }
    mSelf->mMutext.unlock();

    if(ptr == nullptr || ptr == NULL)
    {
        qDebug() << "alloc failed-------------------------- : double = " << doubleAlloc;

        return nullptr;
    }

    return ptr;
}

void MyAlloc::free(void * ptr)
{
    bool ret = false;
    mSelf->mMutext.lock();
    ret = mSelf->mListAlloc.removeOne(ptr);
    mSelf->mMutext.unlock();

    if( ret == false)
        qDebug() << "free failed--------------------------";
}

MyAlloc::MyAlloc()
{
    mSelf = this;
}
