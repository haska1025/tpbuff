#ifndef _TP_SYMBOL_LIST_H_
#define _TP_SYMBOL_LIST_H_

#include <string.h>
#include <stdlib.h>

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
    VALUE_TYPE_PROTID_INT, //8721
    VALUE_TYPE_PROTID_HEX, //8722
    VALUE_TYPE_PREFIX_KEY_STR, //8723
    VALUE_TYPE_PRIMARY_KEY_STR, //8724
    VALUE_TYPE_PRIMARY_KEY_INT, //8725
    VALUE_TYPE_FOREIGN_KEY_INT, //8726
    VALUE_TYPE_FOREIGN_KEY_STR, //8727
    VALUE_TYPE_SET_KEY_INT, //8728
    VALUE_TYPE_SET_PREFIX_KEY_STR, //8729
    VALUE_TYPE_SET_REF, //8730
    VALUE_TYPE_SET_KEY_STR, //8731
};

struct symbol {
    const char *name;
    struct ref *reflist;
};
/* a word */
struct ref {
    struct ref *next;
    const char *filename;
    int flags;
    int lineno;
};

struct symbol *lookup(char*);
void addref(int, const char*, char*,int);
void printrefs();

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
    const char *filename;
    int is_quote;
};

struct generated_file
{
    char *packagename;
    const char *filename;
    struct generated_file *next;

    /** link the include file */
    struct inc_file *incfile_head;
    struct inc_file *incfile_tail;
    /** link the protocol */
    struct protocol *proto_tab_head;
    struct protocol *proto_tab_tail;
};

static char * tp_replace_x_with_y(char *s, char x, char y)
{
    char *ns1, *ns2;
    
    ns1 = s;
    ns2 = ns1;
    while (*ns1){
        if (*ns1 == x){
            *ns1=y;
        }
        ns1++;
    }

    return ns2;
}
static char * tp_toupper(char *s)
{
    char *ns1, *ns2;
    
    ns1 = s;
    ns2 = ns1;
    while (*ns1){
        *ns1 = toupper(*ns1);
        ns1++;
    }

    return ns2;
}

static char * tp_concat_path(const char *dir, const char *filename)
{
    char *tmp_dir = NULL;
    int path_len, dir_len, filename_len;
    
    dir_len = strlen(dir);
    filename_len = strlen(filename);

    path_len = dir_len + filename_len + 2;
    tmp_dir = malloc(path_len);
    strncpy(tmp_dir, dir, dir_len);
    if (dir[dir_len-1] != '/'){
        tmp_dir[dir_len] = '/';
        dir_len++;
    }

    strncpy(tmp_dir+dir_len, filename, filename_len);
    tmp_dir[dir_len+filename_len] = '\0';
    
    return tmp_dir;
}

extern struct item_node * tpp_new_node(int val_type);
extern struct item_node * tpp_new_vec_node(int val_type, int veclenbytes);
extern struct item_node * tpp_new_ref_node(char *name, int val_type);
extern struct item_node * tpp_new_int_node(int val_type, char *name, int val);
extern struct item_node * tpp_new_str_node(int val_type, char *name, char *val);

extern struct item_node * tpp_item_node_set_name(struct item_node *node, char *name);
extern struct protocol * tpp_item_list_add_node(struct protocol *p , struct item_node *node);

extern struct protocol * tpp_protocol_new(struct item_node *node);
extern struct protocol * tpp_protocol_set_name(struct protocol *p , char *name);

extern int tpp_protocol_parse(const char *file_name);

extern struct protocol * tpp_protocol_get(const char *protoname);
extern void tpp_protocol_tab_add(struct protocol *p);

extern char *tpp_protocol_get_key_name(const char *prot_name);
extern struct protocol * tpp_protocol_tab_get(struct generated_file *gfile);
extern void tpp_display_protocol_table(struct generated_file *gfile);
extern void tpp_protocol_tab_destroy(struct generated_file *gfile);

extern struct inc_file * tpp_get_inc_file(struct generated_file *gfile);
extern void tpp_destroy_inc_file(struct generated_file *gfile);
extern void tpp_add_inc_file_node(const char *filename, int is_quote);

extern void tpp_set_package_name(char *name);

extern char *tpp_get_package_name_by_filename(const char *filename);
extern char * tpp_get_package_name(struct generated_file *gfile);
extern struct generated_file * tpp_gfile_new(const char *filename);
extern void tpp_gfile_add(struct generated_file *gfile);
extern struct generated_file * tpp_gfile_get_list();
extern void tpp_gfile_destroy_list();
#endif//_TP_SYMBOL_LIST_H_

