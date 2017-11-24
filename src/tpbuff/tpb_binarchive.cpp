#include "tpb_binarchive.h"

/************************************************************************/
/*                         BinArchive                                   */
/************************************************************************/
#define Arch_Serialize_Def(Type)				\
bool serialize(BinArchive& arch, Type v)	{ return arch.serialize(&v, sizeof(Type)); }

Arch_Serialize_Def(float);
Arch_Serialize_Def(double);
Arch_Serialize_Def(uint64_t);
Arch_Serialize_Def(int64_t);
Arch_Serialize_Def(uint8_t);
Arch_Serialize_Def(int8_t);
Arch_Serialize_Def(bool);
Arch_Serialize_Def(uint16_t);
Arch_Serialize_Def(int16_t);
Arch_Serialize_Def(uint32_t);
Arch_Serialize_Def(int32_t);


bool serialize(BinArchive& arch, std::string& v, int lenSize, bool clear)
{
	return serialize(arch, v.data(), v.size(), lenSize);
}
bool serialize(BinArchive& arch, const std::string& v, int lenSize, bool clear)
{
	return serialize(arch, v.data(), v.size(), lenSize);
}

bool serialize(BinArchive& arch, const char*data, unsigned int dataLen, int lenSize)
{
	if (lenSize >= 4) {
		serialize(arch, dataLen);
	} else if (lenSize >= 2) {
		unsigned short l = (unsigned short)dataLen;
		serialize(arch, l);
	} else if (lenSize == 1) {
		unsigned char l = (unsigned char)dataLen;
		serialize(arch, l);
	}

	return arch.serialize(data, dataLen);
}

BinArchive::~BinArchive(){}
bool BinArchive::writeInt8(int8_t i)
{
    return ::serialize(*this, i);
}
bool BinArchive::writeInt16(int16_t i)
{
    return ::serialize(*this, i);
}
bool BinArchive::writeInt32(int32_t i)
{
    return ::serialize(*this, i);
}
bool BinArchive::writeInt64(int64_t i)
{
    return ::serialize(*this, i);
}

bool BinArchive::writeUInt8(uint8_t i)
{
    return ::serialize(*this, i);
}
bool BinArchive::writeUInt16(uint16_t i)
{
    return ::serialize(*this, i);
}
bool BinArchive::writeUInt32(uint32_t i)
{
    return ::serialize(*this, i);
}
bool BinArchive::writeUInt64(uint64_t i)
{
    return ::serialize(*this, i);
}

bool BinArchive::writeDouble(double d)
{
    return ::serialize(*this, d);
}
bool BinArchive::writeFloat(float f)
{
    return ::serialize(*this, f);
}

bool BinArchive::writeStr(std::string &s)
{
    return ::serialize(*this, s);
}
bool BinArchive::writeBool(bool i)
{
    return ::serialize(*this, i);
}
bool BinArchive::writeChar(char c)
{
    return ::serialize(*this, c);
}
bool BinArchive::writeShort(short s)
{
    return ::serialize(*this, s);
}
bool BinArchive::writeInt(int i)
{
    return ::serialize(*this, i);
}
bool BinArchive::writeLong(long l)
{
    return ::serialize(*this, l);
}

/************************************************************************/
/*                         BinDearchive                                 */
/************************************************************************/
#define Dearch_Serialize_Def(Type)\
bool serialize(BinDearchive& dearch, Type& v) {	return dearch.serialize(&v, sizeof(Type)); }

Dearch_Serialize_Def(float);
Dearch_Serialize_Def(double);
Dearch_Serialize_Def(bool);
Dearch_Serialize_Def(uint64_t);
Dearch_Serialize_Def(int64_t);
Dearch_Serialize_Def(uint8_t);
Dearch_Serialize_Def(int8_t);
Dearch_Serialize_Def(uint16_t);
Dearch_Serialize_Def(int16_t);
Dearch_Serialize_Def(uint32_t);
Dearch_Serialize_Def(int32_t);


bool serialize(BinDearchive& dearch, char* data, unsigned int& dataLen, int lenSize)
{
	if (lenSize >= 4) {
		serialize(dearch, dataLen);
	} else if (lenSize >= 2) {
		unsigned short l = 0;
		if (serialize(dearch, l))
			dataLen = l;
	} else if (lenSize == 1) {
		unsigned char l = 0;
		if (serialize(dearch, l))
			dataLen = l;
	} 

	return dearch.serialize(data, dataLen);
}

bool serialize(BinDearchive& dearch, std::string& v, int lenSize, bool clear)
{
	return dearch.serialize(v, lenSize, clear);
}

// BinDearchive implemetation
BinDearchive::~BinDearchive(){}
bool BinDearchive::readStr(std::string &v)
{
    return ::serialize(*this, v);
}

bool BinDearchive::readDouble(double &v)
{
    return ::serialize(*this, v);
}
bool BinDearchive::readFloat(float &v)
{
    return ::serialize(*this, v);
}
bool BinDearchive::readInt8(int8_t &v)
{
    return ::serialize(*this, v);
}
bool BinDearchive::readInt16(int16_t &v)
{
    return ::serialize(*this, v);
}
bool BinDearchive::readInt32(int32_t &v)
{
    return ::serialize(*this, v);
}
bool BinDearchive::readInt64(int64_t &v)
{
    return ::serialize(*this, v);
}

bool BinDearchive::readUInt8(uint8_t &v)
{
    return ::serialize(*this, v);
}
bool BinDearchive::readUInt16(uint16_t &v)
{
    return ::serialize(*this, v);
}
bool BinDearchive::readUInt32(uint32_t &v)
{
    return ::serialize(*this, v);
}
bool BinDearchive::readUInt64(uint64_t &v)
{
    return ::serialize(*this, v);
}
bool BinDearchive::readBool(bool &v)
{
    return ::serialize(*this, v);
}
bool BinDearchive::readChar(char &v)
{
    int8_t i;
    bool rc = ::serialize(*this, i);
    v = (char)i;
    return rc;
}
bool BinDearchive::readShort(short &v)
{
    int16_t i;
    bool rc = ::serialize(*this, i);
    v = (short)i;
    return rc;
}
bool BinDearchive::readInt(int &v)
{
    int32_t i;
    bool rc = ::serialize(*this, i);
    v = (int)i;
    return rc;
}
bool BinDearchive::readLong(long &v)
{
    int64_t i;
    bool rc = ::serialize(*this, i);
    v = (long)i;

    return rc;
}

