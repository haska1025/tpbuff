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

struct protocal
{
    char *name;
    struct item_node *head;
    struct item_node *tail;
    struct protocal *next;
};

struct key_val
{
    struct key_val *next;
    char *key;
    char *val;
};

struct tang_cmd
{
    char *name;
    struct key_val *kv_head;
};


extern struct item_node * tang_new_int16_node(int val_len , short val);
extern struct item_node * tang_new_int32_node(int val_len , int val);
extern struct item_node * tang_new_str_node(int val_len , char * val);
//extern struct item_node * new_bytes_node(int val_len , char * val);
//extern struct item_node * new_bits_node(int val_len , char *val);

extern struct item_node * tang_item_node_set_name(struct item_node *node, char *name);

extern struct protocal * tang_new_protocal(struct item_node *node);
extern struct protocal * tang_protocal_set_name(struct protocal *p , char *name);
extern struct protocal * tang_item_list_add_node(struct protocal *p , struct item_node *node);
extern void tang_protocal_tab_add( struct protocal *p);
extern void tang_display_protocal_table();

extern struct key_val * tang_new_key_val(char *key , char *val);
extern struct tang_cmd *tang_new_tang_cmd(struct key_val *kv);
extern struct tang_cmd *tang_cmd_set_name(struct tang_cmd *cmd , char *name);
extern struct tang_cmd *tang_cmd_add(struct tang_cmd *cmd , struct key_val *kv);
extern void tang_cmd_save(struct tang_cmd *cmd);


#endif//_TP_SYMBOL_LIST_H_

