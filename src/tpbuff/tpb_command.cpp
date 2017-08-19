#include "tpb_command.h"
#include "tpb_tpbuff.h"

Command::Command():tpb_(NULL)
{
}

Command::~Command()
{
    if (tpb_){
        free_tpb(tpb_);
        tpb_ = NULL;
    }
}


