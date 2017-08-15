#include "tp.h"
#include "tp_symbol_list.h"
#include "stdlib.h"
#include "stdio.h"

#include <string.h>

static struct protocol *proto_tab_head = NULL;
static struct protocol *proto_tab_tail = NULL;

static struct inc_file *incfile_head = NULL;
static struct inc_file *incfile_tail = NULL;

struct item_node * tpp_new_node(int val_type)
{
    struct item_node *node;
    node = malloc(sizeof(struct item_node));
    if(!node)
        return node;

    node->val_type = val_type;
    node->ref_type = NULL;
    node->next = NULL;

    return node;
}

struct item_node * tpp_new_ref_node(const char *name, int val_type)
{
    struct protocol *p = tpp_protocol_get(name);
    if (!p){
        return NULL;
    }
    struct item_node *node;
    node = malloc(sizeof(struct item_node));
    if(!node)
        return node;

    node->val_type = val_type;
    node->ref_type = name;
    node->next = NULL;

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
            free(h1);
        }
        p1 = p;
        p = p->next;
        free(p1);
    }
    proto_tab_head = NULL;
    proto_tab_tail = NULL;
}

struct inc_file * tpp_get_inc_file()
{
    return incfile_head;
}

