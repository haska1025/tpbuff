protocol Conf { int8 i8; };
protocol CloseConf
{
    Conf cc_ref;

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
};

