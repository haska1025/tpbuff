#ifndef _TANG_TPB_INPUTARCHIVE_H_
#define _TANG_TPB_INPUTARCHIVE_H_

#include <string>
#include <inttypes.h>

class InputArchive
{
public:
    virtual ~InputArchive()=0;

    virtual std::string readStr() = 0;
    virtual double readDouble() = 0;
    virtual float readFloat() = 0;

    virtual int8_t readInt8() = 0;
    virtual int16_t readInt16() = 0;
    virtual int32_t readInt32() = 0;
    virtual int64_t readInt64() = 0;

    virtual uint8_t readUInt8() = 0;
    virtual uint16_t readUInt16() = 0;
    virtual uint32_t readUInt32() = 0;
    virtual uint64_t readUInt64() = 0;
};

#endif//_TANG_TPB_INPUTARCHIVE_H_

