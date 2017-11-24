#ifndef _TANG_TPB_COMMAND_H_
#define _TANG_TPB_COMMAND_H_

#include <inttypes.h>

class OutputArchive;
class InputArchive;

// The tang control message header
struct CommandHeader
{ 
    uint32_t version; 
    uint32_t cmdID; 
    uint32_t userID; 
    uint32_t timestamp;    /// not timestamp 
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

    //retain for business
    uint32_t getServiceType() const {return header.cmdID>>16; }
    void setServiceType(uint32_t st) { header.cmdID = (header.cmdID & 0xffff) | (st<<16); }

    uint32_t getMsgId() const {return header.cmdID & 0xffff; }
    void setMsgId(uint32_t id) { header.cmdID = (header.cmdID & 0xffff0000) | id; }

    uint32_t cmdID() const { return header.cmdID; }
	void setCmdID(uint32_t id) { header.cmdID = id; }

    //read and write command header
    uint32_t GetVersion() const { return header.version; }
    void SetVersion(uint32_t version) { header.version = version; }

    uint32_t GetCommandID() const { return header.cmdID; }
    void SetCommandID(uint32_t cmd_id) { header.cmdID = cmd_id; }

    uint32_t GetUserID() const { return header.userID; }
    void SetUserID(uint32_t user_id) { header.userID = user_id; }

    uint32_t GetTimestamp() const { return header.timestamp; }
    void SetTimestamp(uint32_t timestamp) { header.timestamp = timestamp; }

    // Keep public property 
    CommandHeader   header;
    uint32_t s_confID;    
    uint32_t s_from;
};
#endif//_TANG_TPB_COMMAND_H_

