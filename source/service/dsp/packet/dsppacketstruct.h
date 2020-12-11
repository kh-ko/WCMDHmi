#ifndef DSPPACKETFORM_H
#define DSPPACKETFORM_H

#define DSP_FUNCCODE_MULTIBLOCK_READ  101
#define DSP_FUNCCODE_MULTIBLOCK_WRITE 102
#define DSP_FUNCCODE_MULTIBLOCK_NOTI  103
#define DSP_MODBUS_TCP_UNIT_ID        1
#define DSP_MODBUS_TCP_PROTOCOL_ID    0

#pragma pack(push, 1)
struct StMBAPHeader{
    unsigned short mTransactionID;
    unsigned short mProtocolID   = DSP_MODBUS_TCP_PROTOCOL_ID;
    unsigned short mLength       ;       // byte length

};
struct StDspBlock{
    char           mStartAddr=0;
    char           mGroupID  ;
    unsigned short mWordLen  ;
};
struct StDspPacket{
    StMBAPHeader      mMBAP      ;
    char              mUnitID    = DSP_MODBUS_TCP_UNIT_ID;
    char              mFuncCode  ;
    char              mNumOfBlock;
    unsigned short    mData[0]   ;
};
#pragma pack(pop)
#endif // DSPPACKETFORM_H
