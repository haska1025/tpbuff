package com.haska.tpp;

import common.tpp;
import common1.tpp;

// c++ comment

/**** ================+++++++++++++++++++++
 **
 * multiple line comment 
 */
protocol Conf {
    protid ConfCMD=0XAfe8;
    prefix key string conf_prefix='conf';
    primary key int confid;
    foreign key int fid1;
    foreign key int fid2;

    common_message cm;
    common1_message cm1;
    int8 i8;
};

protocol CloseConf
{
    protid CloseConfCMD=0x22;
    Conf cc_ref;

    prefix key string closeconf_prefix='close_conf';
    primary key int closeconfid;

    repeat Conf r_cc_ref;

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

    long l;
    repeat long rl;

    int i;
    repeat int ri;

    short s;
    repeat short rs;

    char c;
    repeat char rc;

    string str;
    repeat string rstr;

    repeat(1) int one_bytes_vec;
    repeat(2) int two_bytes_vec;
    repeat(4) int four_bytes_vec;
    repeat(8) int eigth_bytes_vec;

    set Conf confs;
    set prefix key string confs_rlt;
    set key int confid;
};

