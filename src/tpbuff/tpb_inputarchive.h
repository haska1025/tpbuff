#ifndef _TANG_TPB_INPUTARCHIVE_H_
#define _TANG_TPB_INPUTARCHIVE_H_

#include <string>
#include <inttypes.h>

class InputArchive
{
public:
    virtual ~InputArchive(){};

    virtual bool readStr(std::string &v) = 0;
    virtual bool readDouble(double &v) = 0;
    virtual bool readFloat(float &v) = 0;

    virtual bool readInt8(int8_t &v) = 0;
    virtual bool readInt16(int16_t &v) = 0;
    virtual bool readInt32(int32_t &v) = 0;
    virtual bool readInt64(int64_t &v) = 0;

    virtual bool readUInt8(uint8_t &v) = 0;
    virtual bool readUInt16(uint16_t &v) = 0;
    virtual bool readUInt32(uint32_t &v) = 0;
    virtual bool readUInt64(uint64_t &v) = 0;

    virtual bool readBool(bool &v) = 0;
    virtual bool readChar(char &v) = 0;
    virtual bool readShort(short &v) = 0;
    virtual bool readInt(int &v) = 0;
    virtual bool readLong(long &v) = 0;
};

#endif//_TANG_TPB_INPUTARCHIVE_H_

