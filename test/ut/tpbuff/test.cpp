#include <stdio.h>
#include <string.h>

#include "test.tpp.h"
#include "tpb_binarchive.h"

int main()
{
    CloseConf cc;
    Conf c;
    
    c.set_i8(0x78);
    cc.set_cc_ref(c);

    c.set_i8(0x79);
    cc.append_to_rcc_ref_vec(c);
    c.set_i8(0x7A);
    cc.append_to_rcc_ref_vec(c);
    c.set_i8(0x7B);
    cc.append_to_rcc_ref_vec(c);
    c.set_i8(0x7C);
    cc.append_to_rcc_ref_vec(c);

    cc.set_b1(0x1);
    cc.append_to_rb_vec(0x11);
    cc.append_to_rb_vec(0x11);
    cc.append_to_rb_vec(0x12);

    cc.set_i8(0x2);
    cc.append_to_ri8_vec(0x21);
    cc.append_to_ri8_vec(0x22);
    cc.append_to_ri8_vec(0x23);

    cc.set_ui8(0x3);
    cc.append_to_rui8_vec(0x31);
    cc.append_to_rui8_vec(0x32);
    cc.append_to_rui8_vec(0x33);

    cc.set_i16(0x4);
    cc.append_to_ri16_vec(0x41);
    cc.append_to_ri16_vec(0x42);
    cc.append_to_ri16_vec(0x43);

    cc.set_ui16(0x5);
    cc.append_to_rui16_vec(0x51);
    cc.append_to_rui16_vec(0x52);
    cc.append_to_rui16_vec(0x53);

    cc.set_i32(0x6);
    cc.append_to_ri32_vec(0x61);
    cc.append_to_ri32_vec(0x62);
    cc.append_to_ri32_vec(0x63);

    cc.set_ui32(0x7);
    cc.append_to_rui32_vec(0x71);
    cc.append_to_rui32_vec(0x72);
    cc.append_to_rui32_vec(0x73);

    cc.set_i64(0x100);
    cc.append_to_ri64_vec(0x1001);
    cc.append_to_ri64_vec(0x1002);
    cc.append_to_ri64_vec(0x1003);
    cc.append_to_ri64_vec(0x1004);

    cc.set_ui64(0x200);
    cc.append_to_rui64_vec(0x2001);
    cc.append_to_rui64_vec(0x2002);
    cc.append_to_rui64_vec(0x2003);
    cc.append_to_rui64_vec(0x2004);
    cc.append_to_rui64_vec(0x2005);

    cc.set_d(7.0);
    cc.append_to_rd_vec(8.0);

    cc.set_f(10.0);
    cc.append_to_rf_vec(11.0);

    cc.set_str("Hello my tpp compiler!!!!");
    cc.append_to_rstr_vec("Tpp1 Hah");
    cc.append_to_rstr_vec("Tpp2 Hah");

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

    fprintf(stdout, "Begin Deserialize datalen(%d)\n", ba.dataLen());
    CloseConf de_cc;
    BinDearchive dbin(buff, ba.dataLen());
    if (!de_cc.Deserialize(&dbin)){
        fprintf(stderr, "Deserialize failed!\n");
    }

    de_cc.dump();

    return 0;
}

