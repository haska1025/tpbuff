#ifndef _TANG_TPB_COMMAND_H_
#define _TANG_TPB_COMMAND_H_

#include "tang_tpb_outputarchive.h"
#include "tang_tpb_inputarchive.h"

class Command
{
public:
    virtual ~Command()=0;
    virtual bool Serialize(OutputArchive archive) = 0;
    virtual bool Deserialize(InputArchive archive) = 0;
private:
    struct tp_buff *tpb;
};
#endif//_TANG_TPB_COMMAND_H_

