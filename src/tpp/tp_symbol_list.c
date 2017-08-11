#include "tp.h"
#include "tp_symbol_list.h"
#include "stdlib.h"
#include "stdio.h"

#include <string.h>

static struct protocol *proto_tab_head = NULL;
static struct protocol *proto_tab_tail = NULL;

static struct inc_file *incfile_head = NULL;
static struct inc_file *incfile_tail = NULL;

struct item_node * tpp_new_int16_node(int val_len , short val)
{
    struct item_node *node;
    node = malloc(sizeof(struct item_node));
    if(!node)
        return node;

    node->val_type = VALUE_TYPE_INT16;
    node->value.short_val = val;
    node->val_len = val_len;
    node->next = NULL;

    return node;
}

struct item_node * tpp_new_int32_node(int val_len , int val)
{
    struct item_node *node;
    node = malloc(sizeof(struct item_node));
    if(!node)
        return node;

    node->val_type = VALUE_TYPE_INT32;
    node->value.int_val = val;
    node->val_len = val_len;
    node->next = NULL;

    return node;
}

struct item_node * tpp_new_str_node(int val_len , char * val)
{
    struct item_node *node;

    node = malloc(sizeof(struct item_node));
    if(!node)
        return node;

    node->val_type = VALUE_TYPE_STR;
    node->value.str_val = val;
    node->val_len = val_len;
    node->next = NULL;

    return node;
}
/*
struct item_node * new_bytes_node(int val_len , char * val)
{
    struct item_node *node;

    int slen;
    int i;
    char *pval_start, *pval_end;

    slen = strlen(val);
    if (slen % 2 != 0)
        return NULL;

    node = malloc(sizeof(struct item_node));
    if(!node)
        return NULL;

    node->value.octets = malloc(slen/2);

    i = 0;
    pval_end = val + slen;
    pval_start = val; 
    for (; pval_start < pval_end;){
        char c;
        int low , high;

        c = *pval_start++;
        high = naive_atoi(c);
        c = *pval_start++;
        low = naive_atoi(c);

        node->value.octets[i++] = (high << 4) + low; 
    }

    node->val_type = VALUE_TYPE_OCTET;
    node->val_len = val_len;
    node->next = NULL;

    return node;
}

struct item_node * new_bits_node(int val_len , char *val)
{
    int slen;
    struct item_node *node;

    node = malloc(sizeof(struct item_node));
    if(!node)
        return node;

    slen = strlen(val);
    node->val_type = VALUE_TYPE_BITS;
    node->val_len = val_len;

    return node;
}
*/
struct item_node * tpp_item_node_set_name(struct item_node *node , char *name)
{
    node->name = name; 
    return node;
}

struct protocol * tpp_new_protocol(struct item_node *node)
{
    struct protocol *prtc;

    prtc = malloc(sizeof(struct protocol));
    if(!prtc)
        return NULL;

    prtc->head = node;
    prtc->tail = node;
    prtc->next = NULL;

    return prtc;
}

struct protocol * tpp_protocol_set_name(struct protocol *p , char *name)
{
    p->name = name;
    return p;
}

struct protocol * tpp_item_list_add_node(struct protocol *p, struct item_node *node)
{
    p->tail->next = node;
    p->tail = node;

    return p;
}
void tpp_protocol_tab_add( struct protocol *p)
{
    if (proto_tab_head == NULL){
        proto_tab_head = p;
        proto_tab_tail = p;
    }else{
        proto_tab_tail->next = p;
        proto_tab_tail = p;
    }
}

void tpp_display_protocol_table()
{
    struct item_node *h;
    struct protocol *p;

    p = proto_tab_head;
    for (; p != NULL; p = p->next){
        printf("%s\n{\n" , p->name);

        h = p->head;

        for (; h != NULL; h = h->next){
            if (h->val_type == VALUE_TYPE_INT16 ){
                printf("\t%s,%d,%d,%d\n",h->name ,h->val_type, h->val_len , h->value.short_val);
            }else if(h->val_type == VALUE_TYPE_INT32){
                printf("\t%s,%d,%d,%d\n",h->name ,h->val_type, h->val_len , h->value.int_val);
            }else if(h->val_type == VALUE_TYPE_STR){
                printf("\t%s,%d,%d,%s\n",h->name ,h->val_type, h->val_len , h->value.str_val);
            }
        }
        printf("}\n");
    }
}

//provide the interface for the external call
typedef struct yy_buffer_state *YY_BUFFER_STATE;
YY_BUFFER_STATE tpp_scan_bytes(const char *str , int len);
void tpp_switch_to_buffer  (YY_BUFFER_STATE  new_buffer );
void tpp_delete_buffer  (YY_BUFFER_STATE  new_buffer );

extern FILE *tppin;
int tppparse();

int tpp_protocol_parse(const char *file_name)
{
    tppin = fopen(file_name , "r");
    if(!tppin){
        printf("open file %s failed\n" , file_name);
        return -1;
    }

    if(!tppparse()){
        printf("parse work finished!\n");
    }else{
        printf("parse failed!\n");
    }
#ifdef DEBUG
    tpp_display_protocol_table();
#endif

    fclose(tppin);

    return 0;
}

struct protocol * tpp_protocol_get(const char *protoname)
{
    struct protocol *p;

    if (!protoname)
        return NULL;

    p = proto_tab_head;
    for (; p != NULL; p = p->next){
        if (strcmp(protoname , p->name) == 0)
            return p;
    }

    return p;
}

int tpp_protocol_get_int16_value(struct protocol *p , const char *key , int *val)
{
    /*
    struct item_node *node;

    if (!p)
        return NULL;

    node = p->head;
    for (; node != NULL; node = node->next){
        if (strcmp(node->name , key
    }
    */
    return 0;
}
int tpp_protocol_get_int32_value(struct protocol *p , const char *key , int *val)
{
    return 0;
}
int tpp_protocol_get_str_value(struct protocol *p , const char *key , char **val)
{
    return 0;
}

struct inc_file * tpp_get_inc_file()
{
    return incfile_head;
}

