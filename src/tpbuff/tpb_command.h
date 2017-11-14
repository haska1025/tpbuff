#ifndef _TANG_TPB_COMMAND_H_
#define _TANG_TPB_COMMAND_H_

#include <inttypes.h>

class OutputArchive;
class InputArchive;

// The tang control message header
struct CommandHeader
{ 
    uint32_t version; 
    uint32_t message_type; 
    uint32_t userID; 
    uint32_t sequenceNo;    /// not timestamp 
};

class Command
{
public:
    Command();
    virtual ~Command()=0;
    virtual bool Serialize(OutputArchive *oa) = 0;
    virtual bool Deserialize(InputArchive *ia) = 0;
    // Return the size of the object
    virtual int ByteSize()=0;

    uint32_t getServiceType() const {return header.message_type>>16; }
    void setServiceType(uint32_t st) { header.message_type = (header.message_type & 0xffff) | (st<<16); }

    uint32_t getMsgId() const {return header.message_type & 0xffff; }
    void setMsgId(uint32_t id) { header.message_type = (header.message_type & 0xffff0000) | id; }

    uint32_t cmdID() const { return header.message_type; }
	void setCmdID(uint32_t id) { header.message_type = id; }

    // Keep public property 
    CommandHeader   header;
    uint32_t s_confID;    
    uint32_t s_from;
};
#endif//_TANG_TPB_COMMAND_H_

