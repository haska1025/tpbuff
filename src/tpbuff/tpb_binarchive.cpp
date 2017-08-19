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



/************************************************************************/
/*                         BinDearchive                                 */
/************************************************************************/
#define Dearch_Serialize_Def(Type)\
bool serialize(BinDearchive& dearch, Type& v) {	return dearch.serialize(&v, sizeof(Type)); }

Dearch_Serialize_Def(float);
Dearch_Serialize_Def(double);
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
std::string BinDearchive::readStr()
{
    std::string s;
    ::serialize(*this, s);
    return s;
}

double BinDearchive::readDouble()
{
    double d;
    ::serialize(*this, d);
    return d;
}
float BinDearchive::readFloat()
{
    float f;
    ::serialize(*this, f);
    return f;
}
int8_t BinDearchive::readInt8()
{
    int8_t i;
    ::serialize(*this, i);
    return i;
}
int16_t BinDearchive::readInt16()
{
    int16_t i;
    ::serialize(*this, i);
    return i;
}
int32_t BinDearchive::readInt32()
{
    int32_t i;
    ::serialize(*this, i);
    return i;
}
int64_t BinDearchive::readInt64()
{
    int64_t i;
    ::serialize(*this, i);
    return i;
}

uint8_t BinDearchive::readUInt8()
{
    uint8_t i;
    ::serialize(*this, i);
    return i;
}
uint16_t BinDearchive::readUInt16()
{
    uint16_t i;
    ::serialize(*this, i);
    return i;
}
uint32_t BinDearchive::readUInt32()
{
    uint32_t i;
    ::serialize(*this, i);
    return i;
}
uint64_t BinDearchive::readUInt64()
{
    uint64_t i;
    ::serialize(*this, i);
    return i;
}

