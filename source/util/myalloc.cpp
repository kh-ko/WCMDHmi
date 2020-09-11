#include "myalloc.h"
#include <QDebug>

MyAlloc * MyAlloc::mSelf = nullptr;

void * MyAlloc::myAlloc(int size)
{
    mSelf->mMutext.lock();
    void * ptr = malloc(size);

    if(ptr != nullptr && ptr != NULL)
        mSelf->mListAlloc.append(ptr);

    mSelf->mMutext.unlock();

    if(ptr == nullptr || ptr == NULL)
    {
        qDebug() << "alloc failed";

        return nullptr;
    }

    return ptr;
}

void MyAlloc::myFree(void * ptr)
{
    bool ret = false;
    mSelf->mMutext.lock();
    for(int i = 0; i < mSelf->mListAlloc.size(); i ++)
    {
        if(mSelf->mListAlloc.at(i) == ptr)
        {
            mSelf->mListAlloc.removeAt(i);
            free(ptr);
            ret = true;
            break;
        }
    }

    if(ret == false)
    {
        qDebug() << "free failed";
    }
    mSelf->mMutext.unlock();
}

MyAlloc::MyAlloc()
{
    mSelf = this;
}
