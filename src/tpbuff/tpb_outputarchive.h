#ifndef _TANG_TPB_OUTPUTARCHIVE_H_
#define _TANG_TPB_OUTPUTARCHIVE_H_

class OutputArchive
{
public:
    virtual ~OutputArchive()=0;
    virtual bool writeByte(uint8_t b) = 0;
    virtual bool writeInt(int i) = 0;
};
#endif//_TANG_TPB_OUTPUTARCHIVE_H_

