#include "tp.h"
#include "tp_symbol_list.h"
#include "stdlib.h"
#include "stdio.h"

#include <string.h>

static struct protocal *proto_tab_head = NULL;
static struct protocal *proto_tab_tail = NULL;

struct item_node * tang_new_int16_node(int val_len , short val)
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

struct item_node * tang_new_int32_node(int val_len , int val)
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

struct item_node * tang_new_str_node(int val_len , char * val)
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
struct item_node * tang_item_node_set_name(struct item_node *node , char *name)
{
    node->name = name; 
    return node;
}

struct protocal * tang_new_protocal(struct item_node *node)
{
    struct protocal *prtc;

    prtc = malloc(sizeof(struct protocal));
    if(!prtc)
        return NULL;

    prtc->head = node;
    prtc->tail = node;
    prtc->next = NULL;

    return prtc;
}

struct protocal * tang_protocal_set_name(struct protocal *p , char *name)
{
    p->name = name;
    return p;
}

struct protocal * tang_item_list_add_node(struct protocal *p, struct item_node *node)
{
    p->tail->next = node;
    p->tail = node;

    return p;
}
void tang_protocal_tab_add( struct protocal *p)
{
    if (proto_tab_head == NULL){
        proto_tab_head = p;
        proto_tab_tail = p;
    }else{
        proto_tab_tail->next = p;
        proto_tab_tail = p;
    }
}

void tang_display_protocal_table()
{
    struct item_node *h;
    struct protocal *p;

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

//the tang cmd
static struct tang_cmd *s_cmd;

struct key_val * tang_new_key_val(char *key , char *val)
{
    struct key_val *kv;

    kv = malloc(sizeof(struct key_val));

    kv->key = key;
    kv->val = val;
    kv->next = NULL;

    return kv;
}
struct tang_cmd *tang_new_tang_cmd( struct key_val *kv)
{

    struct tang_cmd *tc;
    tc = malloc(sizeof(struct tang_cmd));
    tc->kv_head = kv;

    return tc;
}
struct tang_cmd *tang_cmd_set_name(struct tang_cmd *cmd , char *name)
{
    cmd->name = name;
    return cmd;
}

struct tang_cmd *tang_cmd_add(struct tang_cmd *cmd , struct key_val *kv)
{
    kv->next = cmd->kv_head;
    cmd->kv_head = kv;

    return cmd;
}

void tang_cmd_save(struct tang_cmd *cmd)
{
    s_cmd = cmd;
}

//provide the interface for the external call
typedef struct yy_buffer_state *YY_BUFFER_STATE;
YY_BUFFER_STATE tpp_scan_bytes(const char *str , int len);
void tpp_switch_to_buffer  (YY_BUFFER_STATE  new_buffer );
void tpp_delete_buffer  (YY_BUFFER_STATE  new_buffer );

extern FILE *tppin;
int tppparse();

int tang_load_cmd_tab(const char *file_name)
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
    tang_display_protocal_table();
#endif

    fclose(tppin);

    return 0;
}

struct protocal * tang_get_protocal(struct tang_cmd *tc)
{
    struct protocal *p;

    if (!tc)
        return NULL;

    p = proto_tab_head;
    for (; p != NULL; p = p->next){
        if (strcmp(tc->name , p->name) == 0)
            return p;
    }

    return p;
}

int tang_protocal_get_int16_value(struct protocal *p , const char *key , int *val)
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
int tang_protocal_get_int32_value(struct protocal *p , const char *key , int *val)
{
    return 0;
}
int tang_protocal_get_str_value(struct protocal *p , const char *key , char **val)
{
    return 0;
}

char * tang_cmd_get_value(struct tang_cmd *tc , const char *key)
{
    struct key_val *kv;

    if (!tc)
        return NULL;

    kv = tc->kv_head;
    for(; kv != NULL; kv = kv->next){
        if (strcmp(kv->key, key) == 0)
            return kv->val;
    }

    return NULL;
}

char * tang_cmd_get_name(struct tang_cmd *tc)
{
    return tc->name;
}

struct tang_cmd * get_tang_cmd(const char *cmdstr , int len)
{
    struct tang_cmd *cmd;
    struct key_val *kv;
    YY_BUFFER_STATE bp;

    cmd = NULL;

    printf("enter get_tang_cmd\n");

    bp = tpp_scan_bytes(cmdstr , len);
    tpp_switch_to_buffer(bp);

    if(!tppparse()){
        printf("parse work!\n");
        cmd = s_cmd;
    }else{
        printf("parse failed!\n");
    }

    tpp_delete_buffer(bp);

#ifdef DEBUG
    if (cmd != NULL){
        printf("cmd name = %s\n",cmd->name);

        for (kv = cmd->kv_head; kv != NULL; kv = kv->next){
            printf("key=%s,val=%s\n",kv->key , kv->val);
        }
    }
#endif

    return cmd;
}

int free_tang_cmd(struct tang_cmd *cmd)
{
    if (!cmd)
        return -1;

    struct key_val *kv , *next_kv;

    free(cmd->name);
    
    for(kv = cmd->kv_head; kv != NULL; kv = next_kv){
        free(kv->key);
        free(kv->val);
        next_kv = kv->next;
        free(kv);
    }

    free(cmd);
    s_cmd = NULL;

    return 0;
}

