#ifndef DSPPACKET_H
#define DSPPACKET_H

#include <QObject>
#include <QDebug>
#include "source/service/util/byteswap.h"
#include "source/service/dsp/packet/dsppacketstruct.h"

class DspPacket : QObject
{
    Q_OBJECT
public:
    QByteArray  mHeader;
    QByteArray  mBlkHeader;
    QByteArray  mBlkData;

    QList<int>  mBlkDataOffsetList;

    explicit DspPacket(QObject *parent = nullptr) : QObject(parent){
        mHeader.resize(sizeof(StDspPacket));
        StDspPacket* pPacket = (StDspPacket* )mHeader.constData();
        pPacket->mMBAP.mProtocolID = DSP_MODBUS_TCP_PROTOCOL_ID;
        pPacket->mUnitID           = DSP_MODBUS_TCP_UNIT_ID;
        pPacket->mNumOfBlock       = 0;
    }
    ~DspPacket(){}

    bool isEqual(const DspPacket& other)
    {
        StDspPacket * cmp01 = (StDspPacket *)mHeader.constData();
        StDspPacket * cmp02 = (StDspPacket *)other.mHeader.constData();

        if(cmp01->mMBAP.mLength != cmp02->mMBAP.mLength)
            return false;

        if(mBlkHeader.size() != other.mBlkHeader.size())
            return false;

        if(mBlkData.size() != other.mBlkData.size())
            return false;

        if(memcmp(mBlkHeader.constData(), other.mBlkHeader.constData(), mBlkHeader.size()) != 0)
            return false;

        if(memcmp(mBlkData.constData(), other.mBlkData.constData(), mBlkData.size()) != 0)
            return false;

        return true;
    }

    unsigned short getTransactionID()
    {
        StDspPacket * pPacket = (StDspPacket *)mHeader.constData();

        return pPacket->mMBAP.mTransactionID;
    }

    void setTransactionID(unsigned short id)
    {
        StDspPacket * pPacket = (StDspPacket *)mHeader.constData();
        pPacket->mMBAP.mTransactionID = id;
    }

    char getFuncCode()
    {
        StDspPacket * pPacket = (StDspPacket *)mHeader.constData();

        return pPacket->mFuncCode;
    }

    void setFuncCode(char code)
    {
        StDspPacket * pPacket = (StDspPacket *)mHeader.constData();
        pPacket->mFuncCode = code;
    }

    int getBlockCount()
    {
        return mBlkHeader.size() / sizeof(StDspBlock);
    }

    StDspBlock * getBlockHeader(int idx)
    {
        return (StDspBlock *)(mBlkHeader.constData() + (idx * sizeof(StDspBlock)));
    }

    const char * getBlockData(int idx)
    {
        return mBlkData.constData() + mBlkDataOffsetList[idx];
    }

    void addReadBlock(unsigned short groupId, unsigned short wordLen)
    {
        unsigned short newLen = 0;
        StDspBlock newBlock;
        newBlock.mGroupID = groupId;
        newBlock.mStartAddr = 0;
        newBlock.mWordLen = wordLen;

        mBlkDataOffsetList.append(mBlkData.size());

        mBlkHeader.append((char *)&newBlock, sizeof(StDspBlock));
        newLen = mHeader.size() + mBlkHeader.size() + mBlkData.size() + - sizeof(StMBAPHeader);

        StDspPacket * pPacket = (StDspPacket *)mHeader.constData();
        pPacket->mNumOfBlock++;
        pPacket->mMBAP.mLength = newLen;
    }

    void addWriteBlock(unsigned short groupId, unsigned short wordLen, char * dataPtr)
    {
        unsigned short newLen = 0;
        StDspBlock newBlock;
        newBlock.mGroupID = groupId;
        newBlock.mStartAddr = 0;
        newBlock.mWordLen = wordLen;

        mBlkDataOffsetList.append(mBlkData.size());

        mBlkHeader.append((char *)&newBlock, sizeof(StDspBlock));
        mBlkData.append(dataPtr, wordLen * 2);
        newLen = mHeader.size() + mBlkHeader.size() + mBlkData.size() + - sizeof(StMBAPHeader);

        StDspPacket * pPacket = (StDspPacket *)mHeader.constData();
        pPacket->mNumOfBlock++;
        pPacket->mMBAP.mLength = newLen;
    }

    void addWriteBlock(unsigned short groupId, unsigned short startAddr, unsigned short wordLen, char * dataPtr, bool useStartAddrOffset = true)
    {
        unsigned short newLen = 0;
        StDspBlock newBlock;
        newBlock.mGroupID = groupId;
        newBlock.mStartAddr = startAddr;
        newBlock.mWordLen = wordLen;

        mBlkDataOffsetList.append(mBlkData.size());

        mBlkHeader.append((char *)&newBlock, sizeof(StDspBlock));
        if(useStartAddrOffset)
            mBlkData.append(dataPtr + (startAddr * 2), wordLen * 2);
        else
            mBlkData.append(dataPtr, wordLen * 2);

        newLen = mHeader.size() + mBlkHeader.size() + mBlkData.size() + - sizeof(StMBAPHeader);

        StDspPacket * pPacket = (StDspPacket *)mHeader.constData();
        pPacket->mNumOfBlock++;
        pPacket->mMBAP.mLength = newLen;
    }

    bool setDatagram(QByteArray datagram)
    {
        QByteArray temp;

        if(datagram.size() < (int)sizeof(StMBAPHeader) + 2)
        {
            qDebug() << "[DspPacket::setDatagram]Datagram size error";
            qDebug() << "[ERROR PACKET] : "<< datagram.toHex();

            return false;
        }

        temp = swapByteOder(datagram);

        StDspPacket * pPacket = (StDspPacket *)temp.constData();

        if((pPacket->mFuncCode != DSP_FUNCCODE_MULTIBLOCK_WRITE &&
            pPacket->mFuncCode != DSP_FUNCCODE_MULTIBLOCK_READ  &&
            pPacket->mFuncCode != DSP_FUNCCODE_MULTIBLOCK_NOTI))
        {
            qDebug() << "[DspPacketDto::setDatagram]Function code error";
            qDebug() << "[ERROR PACKET] : "<< datagram.toHex();
            return false;
        }

        if(pPacket->mMBAP.mLength != (temp.size() - sizeof(StMBAPHeader)))
        {
            qDebug() << "[DspPacketDto::setDatagram]Packet length error";
            qDebug() << "[ERROR PACKET] : "<< datagram.toHex();
            return false;
        }

        if(pPacket->mFuncCode == DSP_FUNCCODE_MULTIBLOCK_WRITE)
        {
            mHeader.clear();
            mHeader.append(temp.constData(), temp.size());

            return true;
        }

        int headerSize = sizeof(StDspPacket);
        if(temp.size() < headerSize)
        {
            qDebug() << "[DspPacketDto::setDatagram]Packet size error : none write ack";
            qDebug() << "[ERROR PACKET] : "<< datagram.toHex();
            return false;
        }


        mHeader.clear();
        mHeader.append(temp.constData(), headerSize);

        int blkHeaderSize = pPacket->mNumOfBlock * sizeof(StDspBlock);
        if((blkHeaderSize + headerSize) > temp.size())
        {
            qDebug() << "[DspPacketDto::setValueFromDatagram]invaild block header size : " << datagram.toHex();
            return false;
        }

        mBlkHeader.clear();
        mBlkHeader.append(temp.constData() + headerSize, blkHeaderSize);


        int blkSumSize = 0;

        for(int i = 0; i < pPacket->mNumOfBlock; i ++)
        {
            StDspBlock * pBlock    = getBlockHeader(i);

            int          blockSize = (pBlock->mWordLen * 2);

            if((blkHeaderSize + headerSize + blkSumSize + blockSize) > temp.size())
            {
                qDebug() << "[DspPacketDto::setValueFromDatagram]invaild block size : " << datagram.toHex();
                return false;
            }

            mBlkDataOffsetList.append(mBlkData.size());
            mBlkData.append(temp.constData() + blkHeaderSize + headerSize + blkSumSize,  blockSize);
            blkSumSize += blockSize;
        }

        return true;
    }

    QByteArray swapByteOder(QByteArray buffer)
    {
        int dataWLen = 0;
        QByteArray swappedBuffer;

        swappedBuffer.resize(buffer.size());

        StDspPacket * pOri = (StDspPacket *)buffer.constData();
        StDspPacket * pSwap = (StDspPacket *)swappedBuffer.constData();

        pSwap->mMBAP.mTransactionID = SWAP_SHORT_RETURN(pOri->mMBAP.mTransactionID);
        pSwap->mMBAP.mProtocolID    = SWAP_SHORT_RETURN(pOri->mMBAP.mProtocolID   );
        pSwap->mMBAP.mLength        = SWAP_SHORT_RETURN(pOri->mMBAP.mLength       );
        pSwap->mUnitID              = pOri->mUnitID                                ;
        pSwap->mFuncCode            = pOri->mFuncCode                              ;

        if(pSwap->mMBAP.mLength > 2)
        {
            pSwap->mNumOfBlock = pOri->mNumOfBlock;

            dataWLen = (buffer.size() - sizeof(StDspPacket)) / 2;

            for(int i = 0; i < dataWLen; i ++)
            {
                pSwap->mData[i] = SWAP_SHORT_RETURN(pOri->mData[i]);
            }
        }

        return swappedBuffer;
    }

    QByteArray createSendBuffer()
    {
        QByteArray temp;
        temp.append(mHeader);
        temp.append(mBlkHeader);
        temp.append(mBlkData);
        return swapByteOder(temp);
    }
};
#endif // DSPPACKET_H
