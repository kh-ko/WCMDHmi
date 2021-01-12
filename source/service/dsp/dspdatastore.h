#ifndef DSPDATASTORE_H
#define DSPDATASTORE_H

#include <QObject>
#include <QDebug>
#include "source/service/includesvcdto.h"
#include "source/service/dsp/packet/dsppacket.h"
#include "../util/byteswap.h"

#define DSP_GROUP_ID_COMMAND          1
#define DSP_GROUP_ID_DEV_COMMSETTING  2
#define DSP_GROUP_ID_DEV_WCSETTING    3
#define DSP_GROUP_ID_DEV_MDSETTING    4
#define DSP_GROUP_ID_DEV_SIZESETTING  5
#define DSP_GROUP_ID_PD_COMMSETTING   6
#define DSP_GROUP_ID_PD_WCSETTING     7
#define DSP_GROUP_ID_PD_MDSETTING     8
#define DSP_GROUP_ID_COMM_STATUS      9
#define DSP_GROUP_ID_WC_STATUS       10
#define DSP_GROUP_ID_MD_STATUS       11
#define DSP_GROUP_ID_DEV_INFO        12
#define DSP_GROUP_ID_EVENT_LIST      13
#define DSP_GROUP_ID_WC_GRAPH        14
#define DSP_GROUP_ID_MD_GRAPH        15

#define DSP_COMMANDBLOCK_STARTADDR_ZERO             ((quint64)((char *)(&(((StDspCommand *)(0x00))->mZero               ))))/2
#define DSP_COMMANDBLOCK_STARTADDR_FR               ((quint64)((char *)(&(((StDspCommand *)(0x00))->mFR                 ))))/2
#define DSP_COMMANDBLOCK_STARTADDR_WCCARIB          ((quint64)((char *)(&(((StDspCommand *)(0x00))->mWCCarib            ))))/2
#define DSP_COMMANDBLOCK_STARTADDR_RUN              ((quint64)((char *)(&(((StDspCommand *)(0x00))->mRun                ))))/2
#define DSP_COMMANDBLOCK_STARTADDR_WCGON            ((quint64)((char *)(&(((StDspCommand *)(0x00))->mWCGraphOn          ))))/2
#define DSP_COMMANDBLOCK_STARTADDR_MDGON            ((quint64)((char *)(&(((StDspCommand *)(0x00))->mMDGraphOn          ))))/2
#define DSP_COMMANDBLOCK_STARTADDR_DEVID            ((quint64)((char *)(&(((StDspCommand *)(0x00))->mDeviceID           ))))/2
#define DSP_COMMANDBLOCK_STARTADDR_GROUP_CURR_COUNT ((quint64)((char *)(&(((StDspCommand *)(0x00))->mResetGroupCurrCount))))/2

struct StDspBlockTag{
    char           mGroupID   ;
    unsigned short mWordLen   ;
    bool           mIsUpdated =false;
    char           * mDataPtr;
};

struct StDspCommandBlock{
    StDspBlockTag mTag;
    StDspCommand  mData;
};


struct StDspDevCommSettingBlock{
    StDspBlockTag       mTag ;
    StDspDevCommSetting mData;
};

struct StDspDevWCSettingBlock{
    StDspBlockTag       mTag ;
    StDspDevWCSetting   mData;
};

struct StDspDevMDSettingBlock{
    StDspBlockTag       mTag ;
    StDspDevMDSetting   mData;
};

struct StDspDevSizeSettingBlock{
    StDspBlockTag       mTag ;
    StDspDevSizeSetting mData;
};
struct StDspPDCommSettingBlock{
    StDspBlockTag       mTag ;
    StDspPDCommSetting  mData;
};

struct StDspPDWCSettingBlock{
    StDspBlockTag    mTag ;
    StDspPDWCSetting mData;
};

struct StDspPDMDSettingBlock{
    StDspBlockTag    mTag ;
    StDspPDMDSetting mData;
};

struct StDspCommStatusBlock{
    StDspBlockTag   mTag ;
    StDspCommStatus mData;
};

struct StDspWCStatusBlock{
    StDspBlockTag mTag ;
    StDspWCStatus mData;
};

struct StDspMDStatusBlock{
    StDspBlockTag mTag ;
    StDspMDStatus mData;
};

struct StDspInfoBlock{
    StDspBlockTag mTag ;
    StDspInfo  mData;
};

struct StDspEventListBlock{
    StDspBlockTag  mTag ;
    StDspEventList mData;
};

struct StDspWCGBlock{
    StDspBlockTag  mTag ;
    QByteArray     mData;
};

struct StDspMDGBlock{
    StDspBlockTag  mTag ;
    QByteArray     mData;
};

class DspDataStore : public QObject
{
    Q_OBJECT

public:
    quint64                  mDspSeq             = 0;
    bool                     mIsEventListInit    =false;
    int                      mAddedEventCnt      = 0;

    StDspCommandBlock        mCommandBlock       ;
    StDspDevCommSettingBlock mDevCommSettingBlock;
    StDspDevWCSettingBlock   mDevWCSettingBlock  ;
    StDspDevMDSettingBlock   mDevMDSettingBlock  ;
    StDspDevSizeSettingBlock mDevSizeSettingBlock;
    StDspPDCommSettingBlock  mPDCommSettingBlock ;
    StDspPDWCSettingBlock    mPDWCSettingBlock   ;
    StDspPDMDSettingBlock    mPDMDSettingBlock   ;
    StDspCommStatusBlock     mCommStatusBlock    ;
    StDspWCStatusBlock       mWCStatusBlock      ;
    StDspMDStatusBlock       mMDStatusBlock      ;
    StDspInfoBlock           mDevInfoBlock       ;
    StDspEventListBlock      mEventListBlock     ;
    StDspWCGBlock            mWCGBlock           ;
    StDspMDGBlock            mMDGBlock           ;

    explicit DspDataStore(QObject * parent = nullptr):QObject(parent)
    {
        mCommandBlock.mTag.mGroupID           = DSP_GROUP_ID_COMMAND;
        mCommandBlock.mTag.mWordLen           = sizeof(StDspCommand) / 2;
        mCommandBlock.mTag.mDataPtr           = (char*)&mCommandBlock.mData;
        memset(&mCommandBlock.mData, 0x00 , sizeof(StDspCommand));

        mDevCommSettingBlock.mTag.mGroupID    = DSP_GROUP_ID_DEV_COMMSETTING;
        mDevCommSettingBlock.mTag.mWordLen    = sizeof(StDspDevCommSetting) / 2;
        mDevCommSettingBlock.mTag.mDataPtr    = (char*)&mDevCommSettingBlock.mData;
        memset(&mDevCommSettingBlock.mData, 0x00 , sizeof(StDspDevCommSetting));

        mDevWCSettingBlock.mTag.mGroupID      = DSP_GROUP_ID_DEV_WCSETTING;
        mDevWCSettingBlock.mTag.mWordLen      = sizeof(StDspDevWCSetting) / 2;
        mDevWCSettingBlock.mTag.mDataPtr      = (char*)&mDevWCSettingBlock.mData;
        memset(&mDevWCSettingBlock.mData, 0x00 , sizeof(StDspDevWCSetting));

        mDevMDSettingBlock.mTag.mGroupID      = DSP_GROUP_ID_DEV_MDSETTING;
        mDevMDSettingBlock.mTag.mWordLen      = sizeof(StDspDevMDSetting) / 2;
        mDevMDSettingBlock.mTag.mDataPtr      = (char*)&mDevMDSettingBlock.mData;
        memset(&mDevMDSettingBlock.mData, 0x00 , sizeof(StDspDevMDSetting));

        mDevSizeSettingBlock.mTag.mGroupID    = DSP_GROUP_ID_DEV_SIZESETTING;
        mDevSizeSettingBlock.mTag.mWordLen    = sizeof(StDspDevSizeSetting) / 2;
        mDevSizeSettingBlock.mTag.mDataPtr     = (char*)&mDevSizeSettingBlock.mData;
        memset(&mDevSizeSettingBlock.mData, 0x00 , sizeof(StDspDevSizeSetting));

        mPDCommSettingBlock.mTag.mGroupID     = DSP_GROUP_ID_PD_COMMSETTING;
        mPDCommSettingBlock.mTag.mWordLen     = sizeof(StDspPDCommSetting) / 2;
        mPDCommSettingBlock.mTag.mDataPtr     = (char*)&mPDCommSettingBlock.mData;
        memset(&mPDCommSettingBlock.mData, 0x00 , sizeof(StDspPDCommSetting));

        mPDWCSettingBlock.mTag.mGroupID       = DSP_GROUP_ID_PD_WCSETTING;
        mPDWCSettingBlock.mTag.mWordLen       = sizeof(StDspPDWCSetting) / 2;
        mPDWCSettingBlock.mTag.mDataPtr       = (char*)&mPDWCSettingBlock.mData;
        memset(&mPDWCSettingBlock.mData, 0x00 , sizeof(StDspPDWCSetting));

        mPDMDSettingBlock.mTag.mGroupID       = DSP_GROUP_ID_PD_MDSETTING;
        mPDMDSettingBlock.mTag.mWordLen       = sizeof(StDspPDMDSetting) / 2;
        mPDMDSettingBlock.mTag.mDataPtr       = (char*)&mPDMDSettingBlock.mData;
        memset(&mPDMDSettingBlock.mData, 0x00 , sizeof(StDspPDMDSetting));

        mCommStatusBlock.mTag.mGroupID        = DSP_GROUP_ID_COMM_STATUS;
        mCommStatusBlock.mTag.mWordLen        = sizeof(StDspCommStatus) / 2;
        mCommStatusBlock.mTag.mDataPtr        = (char*)&mCommStatusBlock.mData;
        memset(&mCommStatusBlock.mData, 0x00 , sizeof(StDspCommStatus));

        mWCStatusBlock.mTag.mGroupID          = DSP_GROUP_ID_WC_STATUS;
        mWCStatusBlock.mTag.mWordLen          = sizeof(StDspWCStatus) / 2;
        mWCStatusBlock.mTag.mDataPtr          = (char*)&mWCStatusBlock.mData;
        memset(&mWCStatusBlock.mData, 0x00 , sizeof(StDspWCStatus));

        mMDStatusBlock.mTag.mGroupID          = DSP_GROUP_ID_MD_STATUS;
        mMDStatusBlock.mTag.mWordLen          = sizeof(StDspMDStatus) / 2;
        mMDStatusBlock.mTag.mDataPtr          = (char*)&mMDStatusBlock.mData;
        memset(&mMDStatusBlock.mData, 0x00 , sizeof(StDspMDStatus));

        mDevInfoBlock.mTag.mGroupID           = DSP_GROUP_ID_DEV_INFO;
        mDevInfoBlock.mTag.mWordLen           = sizeof(StDspInfo) / 2;
        mDevInfoBlock.mTag.mDataPtr           = (char*)&mDevInfoBlock.mData;
        memset(&mDevInfoBlock.mData, 0x00 , sizeof(StDspInfo));

        mEventListBlock.mTag.mGroupID         = DSP_GROUP_ID_EVENT_LIST;
        mEventListBlock.mTag.mWordLen         = sizeof(StDspEventList) / 2;
        mEventListBlock.mTag.mDataPtr         = (char*)&mEventListBlock.mData;
        memset(&mEventListBlock.mData, 0x00 , sizeof(StDspEventList));

        mWCGBlock.mTag.mGroupID               = DSP_GROUP_ID_WC_GRAPH;

        mMDGBlock.mTag.mGroupID               = DSP_GROUP_ID_WC_GRAPH;
    }

    unsigned short getCmdWCGraphOn()
    {
        return mCommandBlock.mData.mWCGraphOn;
    }

    unsigned short getCmdMDGraphOn()
    {
        return mCommandBlock.mData.mMDGraphOn;
    }

    DspDevSettingDto getDevSettingDto()
    {
        DspDevSettingDto ret;
        ret.setValue(&mDevCommSettingBlock.mData, &mDevWCSettingBlock.mData, &mDevMDSettingBlock.mData, &mDevSizeSettingBlock.mData);
        return ret;
    }

    DspPDSettingDto getPDSettingDto()
    {
        DspPDSettingDto ret;
        ret.setValue(&mPDCommSettingBlock.mData, &mPDWCSettingBlock.mData, &mPDMDSettingBlock.mData);
        return ret;
    }

    DspStatusDto getStatusDto()
    {
        DspStatusDto ret;
        ret.setValue(&mCommStatusBlock.mData, &mWCStatusBlock.mData, &mMDStatusBlock.mData);
        return ret;
    }

    DspInfoDto getInfoDto()
    {
        DspInfoDto ret;
        ret.setValue(&mDevInfoBlock.mData);
        return ret;
    }

    DspEventDto getEventDto(int idx)
    {
        DspEventDto ret;
        ret.setValue(&mEventListBlock.mData.mListEvent[idx]);
        return ret;
    }

    DspWCGDto getWCGDto()
    {
        DspWCGDto ret;
        ret.mGraphData = mWCGBlock.mData;
        return ret;
    }

    DspMDGDto getMDGDto()
    {
        DspMDGDto ret;
        ret.mGraphData = mMDGBlock.mData;
        return ret;
    }

    void setDspSeq(quint64 seq)
    {
        mDspSeq = seq;
    }
    void setCmdZero(unsigned short value)
    {
        mCommandBlock.mData.mZero = value;
    }
    void setCmdFR(unsigned short value)
    {
        mCommandBlock.mData.mFR = value;
    }
    void setCmdWCCarib(unsigned short value)
    {
        mCommandBlock.mData.mWCCarib = value;
    }
    void setCmdRun(unsigned short value)
    {
        mCommandBlock.mData.mRun = value;
    }
    void setCmdWCGraphOn(unsigned short value)
    {
        mCommandBlock.mData.mWCGraphOn = value;
    }
    void setCmdMDGraphOn(unsigned short value)
    {
        mCommandBlock.mData.mMDGraphOn = value;
    }
    void setCmdDeviceID(unsigned int value)
    {
        mCommandBlock.mData.mDeviceID = value;
    }
    void setCmdResetGroupCurrCount(unsigned short value)
    {
        mCommandBlock.mData.mResetGroupCurrCount = value;
    }
    void setDevCommSetting(StDspDevCommSetting * commSetting)
    {
        memcpy(&mDevCommSettingBlock.mData, commSetting, sizeof(StDspDevCommSetting));
    }
    void setDevWCSetting(StDspDevWCSetting * wcSetting)
    {
        memcpy(&mDevWCSettingBlock.mData, wcSetting, sizeof(StDspDevWCSetting));
    }
    void setDevMDSetting(StDspDevMDSetting * mdSetting)
    {
        memcpy(&mDevMDSettingBlock.mData, mdSetting, sizeof(StDspDevMDSetting));
    }
    void setDevSizeSetting(StDspDevSizeSetting * sizeSetting)
    {
        memcpy(&mDevSizeSettingBlock.mData, sizeSetting, sizeof(StDspDevSizeSetting));
    }
    void setPDCommSetting(StDspPDCommSetting * commSetting)
    {
        memcpy(&mPDCommSettingBlock.mData, commSetting, sizeof(StDspPDCommSetting));
    }
    void setPDWCSetting(StDspPDWCSetting * wcSetting)
    {
        memcpy(&mPDWCSettingBlock.mData, wcSetting, sizeof(StDspPDWCSetting));
    }
    void setPDMDSetting(StDspPDMDSetting * mdSetting)
    {
        memcpy(&mPDMDSettingBlock.mData, mdSetting, sizeof(StDspPDMDSetting));
    }
    bool setDataFromPacket(DspPacket * pPacket)
    {
        unsigned int lastEventcnt = 0;
        int          numOfBlock   = pPacket->getBlockCount();

        resetUpdatedStatus();

        lastEventcnt = mEventListBlock.mData.mEventCnt;

        for(int i = 0; i < numOfBlock; i++)
        {
            StDspBlockTag * pDataStoreBlock = findDataStoreBlock(pPacket->getBlockHeader(i)->mGroupID);
            pDataStoreBlock->mIsUpdated     = copyBlock(pDataStoreBlock, pPacket->getBlockHeader(i), pPacket->getBlockData(i));

            if(pPacket->getBlockHeader(i)->mGroupID == DSP_GROUP_ID_EVENT_LIST)
            {
                if(mIsEventListInit == true)
                {
                    mAddedEventCnt = mEventListBlock.mData.mEventCnt - lastEventcnt;
                }
                else
                    mIsEventListInit = true;
            }
        }
        return true;
    }

    bool setNotiDataFromPacket(DspPacket * pPacket)
    {
        int          numOfBlock   = pPacket->getBlockCount(); //pPacket->mNumOfBlock;

        resetUpdatedStatus();

        for(int i = 0; i < numOfBlock; i++)
        {
            StDspBlock * pPacketBlock = pPacket->getBlockHeader(i);

            if(pPacketBlock->mGroupID == DSP_GROUP_ID_WC_GRAPH)
            {
                unsigned short pointCnt;
                StDspWCG * pPacketBlockData = (StDspWCG *)pPacket->getBlockData(i);

                pointCnt = pPacketBlockData->mPointCnt;

                if((pPacketBlock->mWordLen * 2) != (sizeof(StDspWCG) + pointCnt * sizeof(StDspWCGPoint)))
                {
                    qDebug() << "[DspDataStore::setNotiDataFromPacket]invaild wcg point cnt : " << pPacket->mBlkData.toHex();
                    return false;
                }

                mWCGBlock.mData.clear();
                mWCGBlock.mData.append(pPacket->getBlockData(i), pPacketBlock->mWordLen * 2);

                mWCGBlock.mTag.mIsUpdated = true;
            }
            else if(pPacketBlock->mGroupID == DSP_GROUP_ID_MD_GRAPH)
            {
                int totalPointCnt;
                StDspMDG * packetData = (StDspMDG *)pPacket->getBlockData(i);

                totalPointCnt = packetData->mPointCnt * packetData->mSensorCnt * 2;

                if((pPacketBlock->mWordLen * 2) != ( (totalPointCnt * sizeof(short)) + sizeof(StDspMDG)))
                {
                    qDebug() << "[DspDataStore::setNotiDataFromPacket]invaild mdg point cnt : " << pPacket->mBlkData.toHex();
                    return false;
                }

                mMDGBlock.mData.clear();
                mMDGBlock.mData.append(pPacket->getBlockData(i), pPacketBlock->mWordLen * 2);

                mMDGBlock.mTag.mIsUpdated = true;
            }
        }

        return true;
    }

private:
    StDspBlockTag * findDataStoreBlock(unsigned short groupID)
    {
        switch(groupID)
        {
        case DSP_GROUP_ID_COMMAND        : return &mCommandBlock       .mTag;
        case DSP_GROUP_ID_DEV_COMMSETTING: return &mDevCommSettingBlock.mTag;
        case DSP_GROUP_ID_DEV_WCSETTING  : return &mDevWCSettingBlock  .mTag;
        case DSP_GROUP_ID_DEV_MDSETTING  : return &mDevMDSettingBlock  .mTag;
        case DSP_GROUP_ID_DEV_SIZESETTING: return &mDevSizeSettingBlock.mTag;
        case DSP_GROUP_ID_PD_COMMSETTING : return &mPDCommSettingBlock .mTag;
        case DSP_GROUP_ID_PD_WCSETTING   : return &mPDWCSettingBlock   .mTag;
        case DSP_GROUP_ID_PD_MDSETTING   : return &mPDMDSettingBlock   .mTag;
        case DSP_GROUP_ID_COMM_STATUS    : return &mCommStatusBlock    .mTag;
        case DSP_GROUP_ID_WC_STATUS      : return &mWCStatusBlock      .mTag;
        case DSP_GROUP_ID_MD_STATUS      : return &mMDStatusBlock      .mTag;
        case DSP_GROUP_ID_DEV_INFO       : return &mDevInfoBlock       .mTag;
        case DSP_GROUP_ID_EVENT_LIST     : return &mEventListBlock     .mTag;
        default: return nullptr;
        }
    }

    bool copyBlock(StDspBlockTag * dstBlock, StDspBlock * srcBlockHeader, const char * data)
    {
        bool isUpdate = false;
        int copySize = ((srcBlockHeader->mStartAddr * 2) + (srcBlockHeader->mWordLen * 2)) < (dstBlock->mWordLen * 2) ?
                       ((srcBlockHeader->mStartAddr * 2) + (srcBlockHeader->mWordLen * 2)) : ((dstBlock->mWordLen * 2) - (srcBlockHeader->mStartAddr * 2));

        if(copySize < 0)
        {
            qDebug() << "[DspDataStore::copyBlock] copy size error : " << copySize;
            return isUpdate;
        }

        if(memcmp(dstBlock->mDataPtr + (srcBlockHeader->mStartAddr * 2), data, copySize) != 0)
        {
            memcpy(dstBlock->mDataPtr + (srcBlockHeader->mStartAddr * 2), data, copySize);
            isUpdate = true;
        }

        return isUpdate;
    }
    void resetUpdatedStatus()
    {
        mCommandBlock       .mTag.mIsUpdated = false;
        mDevCommSettingBlock.mTag.mIsUpdated = false;
        mDevWCSettingBlock  .mTag.mIsUpdated = false;
        mDevMDSettingBlock  .mTag.mIsUpdated = false;
        mDevSizeSettingBlock.mTag.mIsUpdated = false;
        mPDCommSettingBlock .mTag.mIsUpdated = false;
        mPDWCSettingBlock   .mTag.mIsUpdated = false;
        mPDMDSettingBlock   .mTag.mIsUpdated = false;
        mCommStatusBlock    .mTag.mIsUpdated = false;
        mWCStatusBlock      .mTag.mIsUpdated = false;
        mMDStatusBlock      .mTag.mIsUpdated = false;
        mDevInfoBlock       .mTag.mIsUpdated = false;
        mEventListBlock     .mTag.mIsUpdated = false;
        mWCGBlock           .mTag.mIsUpdated = false;
        mMDGBlock           .mTag.mIsUpdated = false;
        mAddedEventCnt      = 0;
    }
};

#endif // DSPDATASTORE_H
