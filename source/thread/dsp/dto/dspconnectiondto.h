#ifndef DSPCONNECTIONDTO_H
#define DSPCONNECTIONDTO_H

#include <QObject>
#include "source/model/dspconnectionmodel.h"

class DspConnectionDto
{
public:
    quint64 mDspSeq;
    QString mIp    ;
    quint16 mPort  ;

    DspConnectionDto(){}
    DspConnectionDto(const DspConnectionDto& copy):
                                                    mDspSeq(copy.mDspSeq),
                                                    mIp    (copy.mIp    ),
                                                    mPort  (copy.mPort  ){}
    DspConnectionDto(DspConnectionModel* copy):
                                                mDspSeq(copy->mSeq   ),
                                                mIp    (copy->mIp    ),
                                                mPort  (copy->mPort  ){}
    ~DspConnectionDto(){}

    DspConnectionDto& operator=(const DspConnectionDto& other)
    {
        mDspSeq= other.mDspSeq;
        mIp    = other.mIp    ;
        mPort  = other.mPort  ;

        return *this;
    }

    DspConnectionDto& operator=(DspConnectionModel* other)
    {
        mDspSeq= other->mSeq   ;
        mIp    = other->mIp    ;
        mPort  = other->mPort  ;

        return *this;
    }
};

Q_DECLARE_METATYPE(DspConnectionDto);
#endif // DSPCONNECTIONDTO_H
