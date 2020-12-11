#ifndef MODBUSDATASTORE_H
#define MODBUSDATASTORE_H

#include <QObject>
#include "source/service/dto/enum/enumdef.h"

#pragma pack(push, 1)
struct ModbusWCDataStore{
    quint16 mRunState   ; // run = 1, stop = 0
    quint16 mPDNum      ;
    quint32 mNorWeight  ;
    quint32 mOverWeight ;
    quint32 mUnderWeight;
    quint32 mTradeCnt   ;
    quint32 mOverCnt    ;
    quint32 mUnderCnt   ;
    quint16 mAlarm      ; // sensor alarm = 1, photo alarm = 2, motor alarm = 4
};

struct ModbusMDDataStore{
    quint16 mRunState   ; // run = 1, stop = 0
    quint16 mPDNum      ;
    quint16 mSenstivity ;
    quint32 mTradeCnt   ;
    quint32 mNGCnt      ;
    quint16 mAlarm      ; // sensor alarm = 1, photo alarm = 2, motor alarm = 4
};
#pragma pack(pop)

#define RMODBUS_WC_RUN_ADDR       ((quint64)((char *)(&(((ModbusWCDataStore *)(8192))->mRunState   ))))/2
#define RMODBUS_WC_NUM_ADDR       ((quint64)((char *)(&(((ModbusWCDataStore *)(8192))->mPDNum      ))))/2
#define RMODBUS_WC_OK_REF_ADDR_L  ((quint64)((char *)(&(((ModbusWCDataStore *)(8192))->mNorWeight  ))))/2
#define RMODBUS_WC_OK_REF_ADDR_H  ((quint64)((char *)(&(((ModbusWCDataStore *)(8192))->mNorWeight  )))+2)/2
#define RMODBUS_WC_HNG_REF_ADDR_L ((quint64)((char *)(&(((ModbusWCDataStore *)(8192))->mOverWeight ))))/2
#define RMODBUS_WC_HNG_REF_ADDR_H ((quint64)((char *)(&(((ModbusWCDataStore *)(8192))->mOverWeight )))+2)/2
#define RMODBUS_WC_LNG_REF_ADDR_L ((quint64)((char *)(&(((ModbusWCDataStore *)(8192))->mUnderWeight))))/2
#define RMODBUS_WC_LNG_REF_ADDR_H ((quint64)((char *)(&(((ModbusWCDataStore *)(8192))->mUnderWeight)))+2)/2
#define RMODBUS_WC_OK_QTY_ADDR_L  ((quint64)((char *)(&(((ModbusWCDataStore *)(8192))->mTradeCnt   ))))/2
#define RMODBUS_WC_OK_QTY_ADDR_H  ((quint64)((char *)(&(((ModbusWCDataStore *)(8192))->mTradeCnt   )))+2)/2
#define RMODBUS_WC_HNG_QTY_ADDR_L ((quint64)((char *)(&(((ModbusWCDataStore *)(8192))->mOverCnt    ))))/2
#define RMODBUS_WC_HNG_QTY_ADDR_H ((quint64)((char *)(&(((ModbusWCDataStore *)(8192))->mOverCnt    )))+2)/2
#define RMODBUS_WC_LNG_QTY_ADDR_L ((quint64)((char *)(&(((ModbusWCDataStore *)(8192))->mUnderCnt   ))))/2
#define RMODBUS_WC_LNG_QTY_ADDR_H ((quint64)((char *)(&(((ModbusWCDataStore *)(8192))->mUnderCnt   )))+2)/2
#define RMODBUS_WC_ALARM_ADDR     ((quint64)((char *)(&(((ModbusWCDataStore *)(8192))->mAlarm      ))))/2

#define RMODBUS_MD_RUN_ADDR       ((quint64)((char *)(&(((ModbusMDDataStore *)(8704))->mRunState  ))))/2
#define RMODBUS_MD_NUM_ADDR       ((quint64)((char *)(&(((ModbusMDDataStore *)(8704))->mPDNum     ))))/2
#define RMODBUS_MD_NG_REF_ADDR    ((quint64)((char *)(&(((ModbusMDDataStore *)(8704))->mSenstivity))))/2
#define RMODBUS_MD_OK_QTY_ADDR_L  ((quint64)((char *)(&(((ModbusMDDataStore *)(8704))->mTradeCnt  ))))/2
#define RMODBUS_MD_OK_QTY_ADDR_H  ((quint64)((char *)(&(((ModbusMDDataStore *)(8704))->mTradeCnt  )))+2)/2
#define RMODBUS_MD_NG_QTY_ADDR_L  ((quint64)((char *)(&(((ModbusMDDataStore *)(8704))->mNGCnt     ))))/2
#define RMODBUS_MD_NG_QTY_ADDR_H  ((quint64)((char *)(&(((ModbusMDDataStore *)(8704))->mNGCnt     )))+2)/2
#define RMODBUS_MD_ALARM_ADDR     ((quint64)((char *)(&(((ModbusMDDataStore *)(8704))->mAlarm     ))))/2

#define LOW_WORD(x)  (((quint16 *)&x)[0])
#define HIGH_WORD(x) (((quint16 *)&x)[1])

#endif // MODBUSDATASTORE_H
