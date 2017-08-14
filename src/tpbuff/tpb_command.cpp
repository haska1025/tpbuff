#include "tpb_command.h"
#include "tpb_buff.h"

Command::Command():tpb_(NULL)
{
    tpb_ = alloc_tpb(ByteSize());
}

Command::Command(struct tp_buff *tpb):tpb_(tpb){}

