#ifndef _TANG_TPB_OUTPUTARCHIVE_H_
#define _TANG_TPB_OUTPUTARCHIVE_H_

#include <string>
#include <inttypes.h>

class OutputArchive
{
public:
    virtual ~OutputArchive()=0;
    
    virtual bool writeStr(std::string &s) = 0;

    virtual bool writeInt8(int8_t i) = 0;
    virtual bool writeInt16(int16_t i) = 0;
    virtual bool writeInt32(int32_t i) = 0;
    virtual bool writeInt64(int64_t i) = 0;

    virtual bool writeUInt8(uint8_t i) = 0;
    virtual bool writeUInt16(uint16_t i) = 0;
    virtual bool writeUInt32(uint32_t i) = 0;
    virtual bool writeUInt64(uint64_t i) = 0;
    
    virtual bool writeDouble(double d) = 0;
    virtual bool writeFloat(float f) = 0;
};
#endif//_TANG_TPB_OUTPUTARCHIVE_H_

