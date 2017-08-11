#ifndef _TP_SYMBOL_LIST_H_
#define _TP_SYMBOL_LIST_H_

#define VALUE_TYPE_INT16 (8684+1)
#define VALUE_TYPE_INT32 (8684+2)
#define VALUE_TYPE_STR (8684+3)
#define VALUE_TYPE_OCTET (8684+4)
#define VALUE_TYPE_BITS (8684+5)

struct item_node
{
    struct item_node *next;
    char *name;
    int val_type;
    int val_len;

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

extern struct item_node * tpp_new_int16_node(int val_len , short val);
extern struct item_node * tpp_new_int32_node(int val_len , int val);
extern struct item_node * tpp_new_str_node(int val_len , char * val);
//extern struct item_node * new_bytes_node(int val_len , char * val);
//extern struct item_node * new_bits_node(int val_len , char *val);

extern struct item_node * tpp_item_node_set_name(struct item_node *node, char *name);
extern struct protocol * tpp_item_list_add_node(struct protocol *p , struct item_node *node);

extern struct protocol * tpp_protocol_new(struct item_node *node);
extern struct protocol * tpp_protocol_set_name(struct protocol *p , char *name);
extern struct protocol * tpp_protocol_tab_get();
extern struct protocol * tpp_protocol_get(const char *protoname)
extern void tpp_protocol_tab_add(struct protocol *p);
extern int tpp_protocol_parse(const char *file_name);
extern void tpp_display_protocol_table();

extern struct inc_file * tpp_get_inc_file();
#endif//_TP_SYMBOL_LIST_H_

