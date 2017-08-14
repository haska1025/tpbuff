#ifndef _TANG_TPB_OUTPUTARCHIVE_H_
#define _TANG_TPB_OUTPUTARCHIVE_H_

#include <string>

struct tp_buff;
class OutputArchive
{
public:
    virtual ~OutputArchive()=0;
    
    virtual bool writeChar(struct tp_buff *tpb, char c) = 0;
    virtual bool writeStr(struct tp_buff *tpb, std::string &s) = 0;
    virtual bool writeShort(struct tp_buff *tpb, short b) = 0;
    virtual bool writeInt(struct tp_buff *tpb, int i) = 0;
    virtual bool writeLong(struct tp_buff *tpb, long i) = 0;

    virtual bool writeInt8(struct tp_buff *tpb, int8_t i) = 0;
    virtual bool writeInt16(struct tp_buff *tpb, int16_t i) = 0;
    virtual bool writeInt32(struct tp_buff *tpb, int32_t i) = 0;
    virtual bool writeInt64(struct tp_buff *tpb, int64_t i) = 0;

    virtual bool writeUInt8(struct tp_buff *tpb, uint8_t i) = 0;
    virtual bool writeUInt16(struct tp_buff *tpb, uint16_t i) = 0;
    virtual bool writeUInt32(struct tp_buff *tpb, uint32_t i) = 0;
    virtual bool writeUInt64(struct tp_buff *tpb, uint64_t i) = 0;
    
    virtual bool writeDouble(struct tp_buff *tpb, double d) = 0;
    virtual bool writeFloat(struct tp_buff *tpb, float f) = 0;
};
#endif//_TANG_TPB_OUTPUTARCHIVE_H_

