#ifndef _TP_SYMBOL_LIST_H_
#define _TP_SYMBOL_LIST_H_

enum value_type{
    VALUE_TYPE_BASE=8684,
    VALUE_TYPE_BYTE,//8685
    VALUE_TYPE_BYTE_VEC,//8686
    VALUE_TYPE_INT8,//8687
    VALUE_TYPE_INT8_VEC,//8688
    VALUE_TYPE_UINT8,//8689
    VALUE_TYPE_UINT8_VEC,//8690
    VALUE_TYPE_INT16,//8691
    VALUE_TYPE_INT16_VEC,//8692
    VALUE_TYPE_UINT16,//8693
    VALUE_TYPE_UINT16_VEC,//8694
    VALUE_TYPE_INT32,//8695
    VALUE_TYPE_INT32_VEC,//8696
    VALUE_TYPE_UINT32,//8697
    VALUE_TYPE_UINT32_VEC,//8698
    VALUE_TYPE_INT64,//8699
    VALUE_TYPE_INT64_VEC,//8700
    VALUE_TYPE_UINT64,//8701
    VALUE_TYPE_UINT64_VEC,//8702
    VALUE_TYPE_DOUBLE,//8703
    VALUE_TYPE_DOUBLE_VEC,//8704
    VALUE_TYPE_FLOAT,//8705
    VALUE_TYPE_FLOAT_VEC,//8706
    VALUE_TYPE_LONG,//8707
    VALUE_TYPE_LONG_VEC,//8708
    VALUE_TYPE_INT,//8709
    VALUE_TYPE_INT_VEC,//8710
    VALUE_TYPE_SHORT,//8711
    VALUE_TYPE_SHORT_VEC,//8712
    VALUE_TYPE_CHAR,//8713
    VALUE_TYPE_CHAR_VEC,//8714
    VALUE_TYPE_STR,//8715
    VALUE_TYPE_STR_VEC,//8716
    VALUE_TYPE_REF,//8717
    VALUE_TYPE_REF_VEC,//8718
    VALUE_TYPE_BOOL, //8719
    VALUE_TYPE_BOOL_VEC, //8720
};

struct item_node
{
    struct item_node *next;
    char *name;
    int val_type;
    int val_len;
    char *ref_type;

    union{
        char *str_val;
        short short_val;
        int int_val;
        unsigned char * octets;
        unsigned long * bits;
    }value;
};

struct protocol
{
    char *name;
    struct item_node *head;
    struct item_node *tail;
    struct protocol *next;
};

struct key_val
{
    struct key_val *next;
    char *key;
    char *val;
};

struct inc_file
{
    struct inc_file *next;
    char *file_name;
};

extern struct item_node * tpp_new_node(int val_type);
extern struct item_node * tpp_new_ref_node(const char *name, int val_type);

extern struct item_node * tpp_item_node_set_name(struct item_node *node, char *name);
extern struct protocol * tpp_item_list_add_node(struct protocol *p , struct item_node *node);

extern struct protocol * tpp_protocol_new(struct item_node *node);
extern struct protocol * tpp_protocol_set_name(struct protocol *p , char *name);
extern struct protocol * tpp_protocol_tab_get();
extern struct protocol * tpp_protocol_get(const char *protoname);
extern void tpp_protocol_tab_add(struct protocol *p);
extern int tpp_protocol_parse(const char *file_name);
extern void tpp_display_protocol_table();
extern void tpp_protocol_tab_destroy();

extern struct inc_file * tpp_get_inc_file();
#endif//_TP_SYMBOL_LIST_H_

