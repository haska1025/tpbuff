#include "tp.h"
#include "tp_symbol_list.h"
#include "stdlib.h"
#include "stdio.h"

#include <string.h>

static struct protocol *proto_tab_head = NULL;
static struct protocol *proto_tab_tail = NULL;

static struct inc_file *incfile_head = NULL;
static struct inc_file *incfile_tail = NULL;


static void tpp_add_inc_file_node(const char *filename)
{
    struct inc_file *inc = NULL;
    for (inc = incfile_head; inc != NULL; inc=inc->next){
        if (strcmp(filename, inc->filename) == 0){
            // has include
            return;
        }
    }

    inc = malloc(sizeof(struct inc_file));
    inc->filename = filename;
    inc->next = NULL;

    if (incfile_head == NULL){
        incfile_head = inc;
        incfile_tail = inc;
    }else{
        incfile_tail->next = inc;
        incfile_tail = inc;
    }
}
static void tpp_add_inc_file(int val_type)
{
    // Add inc file
    if (val_type == VALUE_TYPE_STR){
        tpp_add_inc_file_node("string");
        tpp_add_inc_file_node("string");
    }else if( val_type == VALUE_TYPE_STR_VEC){
        tpp_add_inc_file_node("string");
        tpp_add_inc_file_node("vector");
    } else if (val_type == VALUE_TYPE_STR_VEC
            || val_type == VALUE_TYPE_BYTE_VEC
            || val_type == VALUE_TYPE_INT8_VEC
            || val_type == VALUE_TYPE_INT16_VEC
            || val_type == VALUE_TYPE_UINT8_VEC
            || val_type == VALUE_TYPE_UINT16_VEC
            || val_type == VALUE_TYPE_INT32_VEC
            || val_type == VALUE_TYPE_UINT32_VEC
            || val_type == VALUE_TYPE_INT64_VEC
            || val_type == VALUE_TYPE_UINT64_VEC
            || val_type == VALUE_TYPE_DOUBLE_VEC
            || val_type == VALUE_TYPE_FLOAT_VEC
            || val_type == VALUE_TYPE_LONG_VEC
            || val_type == VALUE_TYPE_INT_VEC
            || val_type == VALUE_TYPE_SHORT_VEC
            || val_type == VALUE_TYPE_CHAR_VEC
            || val_type == VALUE_TYPE_REF_VEC
            || val_type == VALUE_TYPE_BOOL_VEC){
        tpp_add_inc_file_node("vector");
    }else{
        // No need to include header file
    }
}

struct item_node * tpp_new_node(int val_type)
{
    struct item_node *node;
    node = malloc(sizeof(struct item_node));
    if(!node)
        return node;

    node->val_type = val_type;
    node->ref_type = NULL;
    node->next = NULL;
    
    tpp_add_inc_file(val_type);
    return node;
}

struct item_node * tpp_new_ref_node(char *name, int val_type)
{
    struct item_node *node = NULL;
    struct protocol *p = tpp_protocol_get(name);
    if (!p){
        return NULL;
    }
    node = malloc(sizeof(struct item_node));
    if(!node)
        return node;

    node->val_type = val_type;
    node->ref_type = name;
    node->next = NULL;

    if (val_type == VALUE_TYPE_REF_VEC || val_type == VALUE_TYPE_REF){
        tpp_add_inc_file(val_type);
    }

    return node;
}

struct item_node * tpp_new_int_protid_node(char *name, int val)
{
    struct item_node *node = NULL;
    node = tpp_new_node(VALUE_TYPE_PROTID_INT);
    if (!node)return NULL;
    
    node->value.int_val = val;
    node->name = name;
    return node;
}

struct item_node * tpp_new_hex_protid_node(char *name, char *val)
{
    struct item_node *node = NULL;
    node = tpp_new_node(VALUE_TYPE_PROTID_HEX);
    if (!node)return NULL;

    node->value.str_val = val;
    node->name = name;
    return node;
}
struct item_node * tpp_item_node_set_name(struct item_node *node , char *name)
{
    if (!node) return NULL;
    node->name = name; 
    return node;
}

struct protocol * tpp_protocol_new(struct item_node *node)
{
    struct protocol *prtc;

    if (!node) return NULL;

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
    if (!p) return NULL;

    p->name = name;
    return p;
}

struct protocol * tpp_item_list_add_node(struct protocol *p, struct item_node *node)
{
    if (!p) return NULL;
    if (!node) return p;

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
            printf("\t%s,%d\n",h->name ,h->val_type);
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

struct protocol * tpp_protocol_tab_get()
{
    return proto_tab_head;
}
void tpp_protocol_tab_destroy()
{
    struct item_node *h, *h1;
    struct protocol *p, *p1;

    p = proto_tab_head;
    for (; p != NULL;){
        h = p->head;
        for (; h != NULL; ){
            h1 = h; 
            h = h->next;
            if (h1->name){
                free(h1->name);
            }
            free(h1);
        }
        p1 = p;
        p = p->next;
        if (p1->name){
            free(p1->name);
        }
        free(p1);
    }
    proto_tab_head = NULL;
    proto_tab_tail = NULL;
}

struct inc_file * tpp_get_inc_file()
{
    return incfile_head;
}

void tpp_destroy_inc_file()
{
    struct inc_file *inc = incfile_head;
    struct inc_file *inc2;
    for (; inc != NULL;){
        inc2 = inc;
        inc = inc->next;
        free(inc2);
    }

    incfile_head = NULL;
    incfile_tail = NULL;
}

