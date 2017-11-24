package tpp_common;

import base.tpp;

protocol common_message
{
    int8 xxx1;
    int16 xxx2;
    string xxx3;
};

protocol common_message2
{
    repeat int iii;
    repeat long xxxx;
    base_message bm;
};
