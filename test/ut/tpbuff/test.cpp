#include <stdio.h>
#include <string.h>

#include "test.tpp.h"
#include "tpb_binarchive.h"

int main()
{
    tpp::CloseConf cc;
    cc.b1(1);
    cc.append_to_rb_vec(11);
    cc.append_to_rb_vec(12);

    cc.i8(2);
    cc.append_to_ri8_vec(21);
    cc.append_to_ri8_vec(22);
    cc.append_to_ri8_vec(23);

    char buff[4096];
    BinArchive ba(buff, 4096);
    if (!cc.Serialize(&ba)){
        fprintf(stderr, "Serialize failed!\n");
    }

    for (unsigned int i=0; i < ba.dataLen();){
        fprintf(stdout, "%02x ", (unsigned char)buff[i]);
        i++;
        if (i%4 == 0)
            fprintf(stdout, "\n");
    }

    return 0;
}

