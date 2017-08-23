#ifndef _TPB_BIN_ARCHIVE_
#define _TPB_BIN_ARCHIVE_
/*----------------------------- HEADER FILE INCLUDES ----------------------------------*/
#include <string>
#include <map>
#include <set>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "tpb_inputarchive.h"
#include "tpb_outputarchive.h"

using namespace std;
/*--------------------------------  DEFINITION ----------------------------------------*/
/*-------------------------------- ENUMERATIONS ---------------------------------------*/
/*----------------------- STRUCT/UNION/CLASS DATA TYPES -------------------------------*/
class BinArchive;
class BinDearchive;

bool serialize(BinArchive& arch, float v);
bool serialize(BinArchive& arch, double v);
bool serialize(BinArchive& arch, uint64_t v);
bool serialize(BinArchive& arch, int64_t v);
bool serialize(BinArchive& arch, uint8_t v);
bool serialize(BinArchive& arch, int8_t v);
bool serialize(BinArchive& arch, uint16_t v);
bool serialize(BinArchive& arch, int16_t v);
bool serialize(BinArchive& arch, uint32_t v);
bool serialize(BinArchive& arch, int32_t v);

bool serialize(BinArchive& arch, std::string& v, int lenSize=4, bool clear = true);
bool serialize(BinArchive& arch, const std::string& v, int lenSize=4, bool clear = true);
bool serialize(BinArchive& arch, const char*data, unsigned int dataLen, int lenSize=4);

// ��map��ϵ�л�; ��û�ж�ָ�������֧�֡�����
template <typename Key, typename Value>
bool serialize(BinArchive& arch, const std::map<Key, Value>& v, int lenSize=4, bool clear = true)
{
	if (lenSize == 1)
		serialize(arch, (unsigned char)v.size());
	else if (lenSize == 2)
		serialize(arch, (unsigned short)v.size());
	else
		serialize(arch, (unsigned)v.size());	

	for (typename std::map<Key, Value>::const_iterator i=v.begin(); i!=v.end(); ++i)
	{
		serialize(arch, i->first);
		serialize(arch, i->second);
	}

	return true;
}

// ��vector�ȵ�ϵ�л�; ��û�ж�ָ�������֧�֡�����
template <typename Arch, typename T,  template <typename ELEM, typename = std::allocator <ELEM> > class CONT> 
bool serialize(Arch& arch, CONT<T>& v, int lenSize = 4)
{
	return serialize(arch, (const CONT<T>&)v, lenSize);
}
template <typename Arch, typename T,  template <typename ELEM, typename = std::allocator <ELEM> > class CONT> 
bool serialize(Arch& arch, const CONT<T>& v, int lenSize = 4)
{
	if (lenSize == 1)
		serialize(arch, (unsigned char)v.size());
	else if (lenSize == 2)
		serialize(arch, (unsigned short)v.size());
	else
		serialize(arch, (unsigned)v.size());

	for (typename CONT<T>::const_iterator i=v.begin(); i!=v.end(); ++i)
		serialize(arch, const_cast<T&>(*i));

	return true;
}

/// for set
template <typename Arch, typename T,  template<class _Kty, class _Pr = less<_Kty>, class _Alloc = allocator<_Kty> > class CONT> 
bool serialize(Arch& arch, CONT<T>& v, int lenSize = 4)
{
	return serialize(arch, (const CONT<T>&)v, lenSize);
}
template <typename Arch, typename T,  template<class _Kty, class _Pr = less<_Kty>, class _Alloc = allocator<_Kty> > class CONT> 
bool serialize(Arch& arch, const CONT<T>& v, int lenSize = 4)
{
	if (lenSize == 1)
		serialize(arch, (unsigned char)v.size());
	else if (lenSize == 2)
		serialize(arch, (unsigned short)v.size());
	else
		serialize(arch, (unsigned)v.size());

	for (typename CONT<T>::const_iterator i=v.begin(); i!=v.end(); ++i)
		serialize(arch, const_cast<T&>(*i));

	return true;
}


class BinArchive : public OutputArchive
{
public:	
	// �ⲿ�����ݣ����������ݵ�ɾ��
	BinArchive(char* buffer, unsigned int buffer_size)
		: inner_data_(buffer)
		, inner_buffer_size_(buffer_size)
		, cur_pos_(0)
	{
		assert(!!buffer);
		assert(inner_buffer_size_ > 0);
	}

    ~BinArchive();

    void reset() { cur_pos_ = 0; }

    virtual bool writeStr(std::string &s);
    virtual bool writeInt8(int8_t i);
    virtual bool writeInt16(int16_t i);
    virtual bool writeInt32(int32_t i);
    virtual bool writeInt64(int64_t i);

    virtual bool writeUInt8(uint8_t i);
    virtual bool writeUInt16(uint16_t i);
    virtual bool writeUInt32(uint32_t i);
    virtual bool writeUInt64(uint64_t i);
    
    virtual bool writeDouble(double d);
    virtual bool writeFloat(float f);


	bool serialize(const void* data, unsigned int dataLen)
	{
		assert(inner_buffer_size_ >= cur_pos_ + dataLen);
		if (inner_buffer_size_ < cur_pos_ + dataLen){
            printf("The buffer pos error. inner_buffer_size(%u) cur_pos(%u) dataLen(%u)",
                    inner_buffer_size_,
                    cur_pos_,
                    dataLen);
			return false;
        }

		if (dataLen > 0)
		{
			memcpy(inner_data_+cur_pos_, data, dataLen);
			cur_pos_ += dataLen;
		}

		return true;
	}
	

	string toString() const { return string(inner_data_, cur_pos_); }
	void toString(char* data, unsigned int& size) const
	{
		data = inner_data_;
		size = cur_pos_;
	}

	unsigned int dataLen() const { return cur_pos_; }

private:
	char*			inner_data_;
	unsigned int	inner_buffer_size_;
	unsigned int	cur_pos_;
};


/************************************************************************/
/*                          BinDearchive                                */
/************************************************************************/
bool serialize(BinDearchive& dearch, float& v);
bool serialize(BinDearchive& dearch, double& v);
bool serialize(BinDearchive& dearch, uint64_t& v);
bool serialize(BinDearchive& dearch, int64_t& v);
bool serialize(BinDearchive& dearch, uint8_t  &v);
bool serialize(BinDearchive& dearch, int8_t  &v);
bool serialize(BinDearchive& dearch, uint16_t  &v);
bool serialize(BinDearchive& dearch, int16_t  &v);
bool serialize(BinDearchive& dearch, uint32_t  &v);
bool serialize(BinDearchive& dearch, int32_t  &v);

/// data, should provide memory and release by caller
bool serialize(BinDearchive& dearch, char* data, unsigned int& dataLen, int lenSize=4);
bool serialize(BinDearchive& dearch, std::string& v, int lenSize=4, bool clear = true);

template <typename T,  template <typename ELEM, typename = std::allocator <ELEM> > class CONT> 
bool serialize(BinDearchive& dearch, CONT<T>& v, int lenSize = 4, bool clear=true)
{
	if (clear)
		v.clear();

	typename CONT<T>::size_type size = 0;
	if (lenSize == 1) {
		unsigned char s = 0;
		serialize(dearch, s);
		size = s;
	} else if (lenSize == 2) {
		unsigned short s = 0;
		serialize(dearch, s);
		size = s;
	} else {
		unsigned s = 0;
		serialize(dearch, s);
		size = s;
	}

	T c;
	for (typename CONT<T>::size_type i=0; i<size; ++i)
	{
		if (!serialize(dearch, c))
			return false;
		v.push_back(c);
	}

	return true;
}


template <typename T,  template<class _Kty, class _Pr = less<_Kty>, class _Alloc = allocator<_Kty> > class CONT> 
bool serialize(BinDearchive& dearch, CONT<T>& v, int lenSize = 4, bool clear=true)
{
	if (clear)
		v.clear();

	typename CONT<T>::size_type size = 0;
	if (lenSize == 1) {
		unsigned char s = 0;
		serialize(dearch, s);
		size = s;
	} else if (lenSize == 2) {
		unsigned short s = 0;
		serialize(dearch, s);
		size = s;
	} else {
		unsigned s = 0;
		serialize(dearch, s);
		size = s;
	}

	T c;
	for (typename CONT<T>::size_type i=0; i<size; ++i)
	{
		if (!serialize(dearch, c))
			return false;
		v.insert(c);
	}

	return true;
}

/**v was not to clear!*/
template <typename Key, typename Value>
bool serialize(BinDearchive& dearch, std::map<Key, Value>& v, int lenSize=4, bool clear=true)
{
	if (clear)
		v.clear();

	typename std::map<Key, Value>::size_type size = 0;
	if (lenSize == 1) {
		unsigned char s = 0;
		serialize(dearch, s);
		size = s;
	} else if (lenSize == 2) {
		unsigned short s = 0;
		serialize(dearch, s);
		size = s;
	} else {
		unsigned s = 0;
		serialize(dearch, s);
		size = s;
	}	

	Key k;
	Value c;
	for (typename std::map<Key, Value>::size_type i=0; i<size; ++i)
	{
		if (!serialize(dearch, k))
			return false;
		if (!serialize(dearch, c))
			return false;
		v.insert(typename std::map<Key, Value>::value_type(k, c));
	}

	return true;
}

class BinDearchive : public InputArchive
{
public:
	/// data_size: the size of data, not the buffer size!
	BinDearchive(const char* data, unsigned int data_size)
		: inner_data_(data)
		, inner_data_size_(data_size)
		, cur_pos_(0)
	{
		if (inner_data_size_ > 0)
			assert(!!data);
		assert(inner_data_size_ >= 0);
	}

	BinDearchive()
		: inner_data_(NULL)
		, inner_data_size_(0)
		, cur_pos_(0)
	{}

    ~BinDearchive();

    // Outputarchive functions
    virtual std::string readStr();
    virtual double readDouble();
    virtual float readFloat();

    virtual int8_t readInt8();
    virtual int16_t readInt16();
    virtual int32_t readInt32();
    virtual int64_t readInt64();

    virtual uint8_t readUInt8();
    virtual uint16_t readUInt16();
    virtual uint32_t readUInt32();
    virtual uint64_t readUInt64();


	
	bool serialize(void* d, unsigned int len)
	{
		if (len == 0)
			return true;

		assert(inner_data_size_ >= cur_pos_ + len);
		if (inner_data_size_ < cur_pos_ + len)
			return false;

		memcpy(d, inner_data_ + cur_pos_, len);
		cur_pos_ += len;

		return true;
	}

	bool getTheRest(void* d, unsigned int& len)
	{			
		assert(inner_data_size_ >= cur_pos_);
		len = inner_data_size_ - cur_pos_;
		if (len == 0) {			
			return true;
		}

		memcpy(d, inner_data_ + cur_pos_, len);
		cur_pos_ += len;

		return true;
	}

	bool serialize(std::string& v, char lenSize=4, bool clear = true)
	{
		string::size_type size = 0;
		if (lenSize >= 4) {			
			lenSize = 4;
		} else if (lenSize >= 2) {
			lenSize = 2;
		}

		if (lenSize == 0)
			size = inner_data_size_ - cur_pos_;
		else {			
			serialize(&size, lenSize);
		}

		assert(inner_data_size_ >= cur_pos_ + size);
		if (inner_data_size_ < cur_pos_ + size)
			return false;

		if (size > 0)
		{
			if (clear)
				v.assign(inner_data_+cur_pos_, size);
			else
				v.append(inner_data_+cur_pos_, size); 
			cur_pos_ += size;
		}

		return true;
	}

	unsigned int curPosition() const { return cur_pos_; }

private:
	const char*		inner_data_;
	unsigned int	inner_data_size_;
	unsigned int	cur_pos_;
};
#endif//_TPB_BIN_ARCHIVE_

