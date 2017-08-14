#ifndef _TANG_TPB_INPUTARCHIVE_H_
#define _TANG_TPB_INPUTARCHIVE_H_

#include <string>

struct tp_buff;
class InputArchive
{
public:
    virtual ~InputArchive()=0;

    virtual char readChar(struct tp_buff *tpb) = 0;
    virtual std::string readStr(struct tp_buff *tpb) = 0;
    virtual short readShort(struct tp_buff *tpb) = 0;
    virtual int readInt(struct tp_buff *tpb) = 0;
    virtual long readLong(struct tp_buff *tpb) = 0;
    virtual double readDouble(struct tp_buff *tpb) = 0;
    virtual float readFloat(struct tp_buff *tpb) = 0;

    virtual int8_t readInt8(struct tp_buff *tpb) = 0;
    virtual int16_t readInt16(struct tp_buff *tpb) = 0;
    virtual int32_t readInt32(struct tp_buff *tpb) = 0;
    virtual int64_t readInt64(struct tp_buff *tpb) = 0;

    virtual uint8_t readUInt8(struct tp_buff *tpb) = 0;
    virtual uint16_t readUInt16(struct tp_buff *tpb) = 0;
    virtual uint32_t readUInt32(struct tp_buff *tpb) = 0;
    virtual uint64_t readUInt64(struct tp_buff *tpb) = 0;
};

#endif//_TANG_TPB_INPUTARCHIVE_H_

