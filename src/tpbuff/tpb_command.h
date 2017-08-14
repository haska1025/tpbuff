#ifndef _TANG_TPB_COMMAND_H_
#define _TANG_TPB_COMMAND_H_

class OutputArchive;
class InputArchive;
struct tp_buff;
class Command
{
public:
    Command();
    Command(struct tp_buff *tpb);
    virtual ~Command()=0;
    virtual bool Serialize(OutputArchive *oa) = 0;
    virtual bool Deserialize(InputArchive *ia) = 0;
    // Return the size of the object
    virtual int ByteSize()=0;

    struct tp_buff tpb(){return tpb_;}
private:
    struct tp_buff *tpb_;
};
#endif//_TANG_TPB_COMMAND_H_

