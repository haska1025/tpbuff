package tpp_cxx;

import conf_common.tpp;

protocol Conf
{ 
    // the i8
    // comment2
    int8 i8; 
    conference_info ci;
};

// comment
// comment
protocol CloseConf
{
    protid CMD_CLOSE_CONFERENCE = 0x22;

    Conf cc_ref;
    repeat Conf rcc_ref;

    byte b1;
    repeat byte rb;

    int8 i8;
    repeat int8 ri8;

    uint8 ui8;
    repeat uint8 rui8;

    int16 i16;
    repeat int16 ri16;

    uint16 ui16;
    repeat uint16 rui16;

    int32 i32;
    repeat int32 ri32;

    uint32 ui32;
    repeat uint32 rui32;

    int64 i64;
    repeat int64 ri64;

    uint64 ui64;
    repeat uint64 rui64;
    
    double d;
    repeat double rd;
   
    float f;
    repeat float rf;

    string str;
    repeat string rstr;

    char c;
    repeat char rc;

    short s;
    repeat short rs;

    int ivalue;
    repeat int ri;

    long lvalue;
    repeat long rl;
    repeat(1) int onei;
    repeat(2) int twoi;
    repeat(4) int fouri;
    repeat(8) int eighti;
};

protocol PageInfo{
    uint16 pageNo;
    uint16 roate;
    string url;
};
