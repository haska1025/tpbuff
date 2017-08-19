
#include "BinArchive.h"

/************************************************************************/
/*                         BinArchive                                   */
/************************************************************************/
#define Arch_Serialize_Def(Type)				\
bool serialize(BinArchive& arch, const Type v)	{ return arch.serialize(&v, sizeof(Type)); }

Arch_Serialize_Def(char);
Arch_Serialize_Def(unsigned char);
Arch_Serialize_Def(short);
Arch_Serialize_Def(unsigned short);
Arch_Serialize_Def(int);
Arch_Serialize_Def(unsigned int);
Arch_Serialize_Def(long);
Arch_Serialize_Def(unsigned long);
Arch_Serialize_Def(float);
Arch_Serialize_Def(double);
Arch_Serialize_Def(UINT64_t);
Arch_Serialize_Def(INT64_t);


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


/************************************************************************/
/*                         BinDearchive                                 */
/************************************************************************/
#define Dearch_Serialize_Def(Type)\
bool serialize(BinDearchive& dearch, Type& v) {	return dearch.serialize(&v, sizeof(Type)); }

Dearch_Serialize_Def(char);
Dearch_Serialize_Def(unsigned char);
Dearch_Serialize_Def(short);
Dearch_Serialize_Def(unsigned short);
Dearch_Serialize_Def(int);
Dearch_Serialize_Def(unsigned int);
Dearch_Serialize_Def(long);
Dearch_Serialize_Def(unsigned long);
Dearch_Serialize_Def(float);
Dearch_Serialize_Def(double);
Dearch_Serialize_Def(UINT64_t);
Dearch_Serialize_Def(INT64_t);

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
