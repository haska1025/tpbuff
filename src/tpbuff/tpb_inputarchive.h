#ifndef _TANG_TPB_INPUTARCHIVE_H_
#define _TANG_TPB_INPUTARCHIVE_H_

class InputArchive
{
public:
    virtual ~InputArchive()=0;
    virtual uint8_t readByte() = 0;
    virtual int readInt() = 0;
};

#endif//_TANG_TPB_INPUTARCHIVE_H_

