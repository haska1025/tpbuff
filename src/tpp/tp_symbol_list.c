#include "tp.h"
#include "tp_symbol_list.h"
#include "stdlib.h"
#include "stdio.h"

#include <string.h>

extern const char *curfilename;
struct protocol *proto_tab_head = NULL;
struct protocol *proto_tab_tail = NULL;
struct inc_file *incfile_head = NULL;
struct inc_file *incfile_tail = NULL;

static struct generated_file *gfile_head = NULL;
static struct generated_file *gfile_tail = NULL;

char *g_packagename = NULL;

char *tpp_get_package_name_by_filename(const char *filename)
{
    struct generated_file *cur_gfile;

    cur_gfile = NULL;
    for (cur_gfile = gfile_head; cur_gfile != NULL;cur_gfile=cur_gfile->next){
        if (0 == strcmp(cur_gfile->filename , filename)){
            return cur_gfile->packagename;
        }
    }
    return NULL;
}
char *tpp_get_package_name(struct generated_file *gfile)
{
    return gfile->packagename;
}
void tpp_set_package_name(char *name)
{
    g_packagename = name;
}

struct generated_file * tpp_gfile_new(const char *filename)
{
    struct generated_file *gfile = (struct generated_file *)malloc(sizeof(struct generated_file));
    gfile->filename = filename;
    gfile->packagename = NULL;
    gfile->next = NULL;
    gfile->incfile_head = NULL;
    gfile->incfile_tail = NULL;
    gfile->proto_tab_head = NULL;
    gfile->proto_tab_tail = NULL;
    return gfile;
}
void tpp_gfile_add(struct generated_file *gfile)
{
    if (gfile_head == NULL){
        gfile_head = gfile;
        gfile_tail = gfile;
    }else{
        gfile_tail->next = gfile;
        gfile_tail = gfile;
    }
}

struct generated_file * tpp_gfile_get_list()
{
    return gfile_head;
}

void tpp_gfile_destroy_list()
{
    struct generated_file *gfile, *cur_gfile;

    gfile = cur_gfile = NULL;
    for (cur_gfile = gfile_head; cur_gfile != NULL;){
        tpp_protocol_tab_destroy(cur_gfile);
        tpp_destroy_inc_file(cur_gfile);
        /*
        if (cur_gfile->filename){
            free(cur_gfile->filename);
        }
        */
        if (cur_gfile->packagename){
            free(cur_gfile->packagename);
        }
        gfile = cur_gfile->next;
        free(cur_gfile);
        cur_gfile = gfile;
    }

    gfile_head = gfile_tail = NULL;
    g_packagename = NULL;
}

void tpp_add_inc_file_node(const char *filename, int is_quote)
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
    inc->is_quote = is_quote;
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
        tpp_add_inc_file_node("string", 0);
        tpp_add_inc_file_node("string", 0);
    }else if( val_type == VALUE_TYPE_STR_VEC){
        tpp_add_inc_file_node("string", 0);
        tpp_add_inc_file_node("vector", 0);
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
        tpp_add_inc_file_node("vector", 0);
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

struct item_node * tpp_new_vec_node(int val_type, int veclenbytes)
{
    struct item_node *node = NULL;
    node = tpp_new_node(val_type);
    if (node){
        node->val_len = veclenbytes;
    }
    return node;
}
struct item_node * tpp_new_ref_node(char *name, int val_type)
{
    struct item_node *node = NULL;
    struct symbol *s = NULL;
    if (!(s=lookup(name))){
        return NULL;
    }
    node = malloc(sizeof(struct item_node));
    if(!node)
        return node;

    node->val_type = val_type;
    node->ref_type = name;
    node->next = NULL;

    if (!s->reflist || !s->reflist->filename)
        return NULL;

    if (strcmp(curfilename, s->reflist->filename)){
        tpp_add_inc_file_node(s->reflist->filename, 1);
    }

    if (val_type == VALUE_TYPE_REF_VEC){
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
void tpp_protocol_tab_add(struct protocol *p)
{
    if (proto_tab_head == NULL){
        proto_tab_head = p;
        proto_tab_tail = p;
    }else{
        proto_tab_tail->next = p;
        proto_tab_tail = p;
    }
}

void tpp_display_protocol_table(struct generated_file *gfile)
{
    struct item_node *h;
    struct protocol *p;

    p = gfile->proto_tab_head;
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

void tpp_switch_to_buffer (YY_BUFFER_STATE new_buffer  );
YY_BUFFER_STATE tpp_create_buffer (FILE *file,int size  );
void tpp_delete_buffer (YY_BUFFER_STATE b  );
void tpp_flush_buffer (YY_BUFFER_STATE b  );
void tpppush_buffer_state (YY_BUFFER_STATE new_buffer  );
void tpppop_buffer_state (void );


extern FILE *tppin;
int tppparse();
int newfile(const char *fn);

int tpp_protocol_parse(const char *file_name)
{
    /*
    tppin = fopen(file_name , "r");
    if(!tppin){
        printf("open file %s failed\n" , file_name);
        return -1;
    }
    */
    if (newfile(file_name) != 0){
        printf("open file %s failed\n" , file_name);
    }

    if(!tppparse()){
        printf("parse work finished!\n");
    }else{
        printf("parse failed!\n");
    }
#ifdef DEBUG
    tpp_display_protocol_table();
#endif

    //fclose(tppin);

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

struct protocol * tpp_protocol_tab_get(struct generated_file *gfile)
{
    return gfile->proto_tab_head;
}
void tpp_protocol_tab_destroy(struct generated_file *gfile)
{
    struct item_node *h, *h1;
    struct protocol *p, *p1;

    p = gfile->proto_tab_head;
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
    gfile->proto_tab_head = NULL;
    gfile->proto_tab_tail = NULL;
}

struct inc_file * tpp_get_inc_file(struct generated_file *gfile)
{
    return gfile->incfile_head;
}

void tpp_destroy_inc_file(struct generated_file *gfile)
{
    struct inc_file *inc = gfile->incfile_head;
    struct inc_file *inc2;
    for (; inc != NULL;){
        inc2 = inc;
        inc = inc->next;
        free(inc2);
    }

    gfile->incfile_head = NULL;
    gfile->incfile_tail = NULL;
}

/* simple symtab of fixed size */
#define NHASH 9997
struct symbol symtab[NHASH];
/* hash a symbol */
static unsigned symhash(char *sym)
{
    unsigned int hash = 0;
    unsigned c;
    while(c = *sym++) hash = hash*9 ^ c;
    return hash;
}
struct symbol * lookup(char* sym)
{
    struct symbol *sp = &symtab[symhash(sym)%NHASH];
    int scount = NHASH;
    /* how many have we looked at */
    while(--scount >= 0) {
        if(sp->name && !strcmp(sp->name, sym)) return sp;
        if(!sp->name) {
            sp->name = strdup(sym);
            sp->reflist = 0;
            return sp;
        }
        /* new entry */
        if(++sp >= symtab+NHASH) sp = symtab; /* try the next entry */
    }
    fputs("symbol table overflow\n", stderr);
    abort(); /* tried them all, table is full */
}

void addref(int lineno, const char *filename, char *word, int flags)
{
    struct ref *r;
    struct symbol *sp = lookup(word);
    /* don't do dups of same line and file */
    if(sp->reflist &&
            sp->reflist->lineno == lineno &&
            sp->reflist->filename == filename) return;
    r = malloc(sizeof(struct ref));
    if(!r) {fputs("out of space\n", stderr); abort(); }
    r->next = sp->reflist;
    r->filename = filename;
    r->lineno = lineno;
    r->flags = flags;
    sp->reflist = r;
}

static int symcompare(const void *xa, const void *xb)
{
    const struct symbol *a = xa;
    const struct symbol *b = xb;
    if(!a->name) {
        if(!b->name) return 0; /* both empty */
        return 1; /* put empties at the end */
    }
    if(!b->name) return -1;
    return strcmp(a->name, b->name);
}

void printrefs()
{
    struct symbol *sp;
    qsort(symtab, NHASH, sizeof(struct symbol), symcompare); /* sort the symbol table */
    for(sp = symtab; sp->name && sp < symtab+NHASH; sp++) {
        const char *prevfn = NULL; /* last printed filename, to skip dups */
        /* reverse the list of references */
        struct ref *rp = sp->reflist;
        struct ref *rpp = 0; /* previous ref */
        struct ref *rpn; /* next ref */
        do {
            rpn = rp->next;
            rp->next = rpp;
            rpp = rp;
            rp = rpn;
        } while(rp);
        /* now print the word and its references */
        printf("%10s", sp->name);
        for(rp = rpp; rp; rp = rp->next) {
            if(rp->filename == prevfn) {
                printf(" %d", rp->lineno);
            } else {
                printf(" %s:%d", rp->filename, rp->lineno);
                prevfn = rp->filename;
            }
            if(rp->flags & 01) printf("*");
        }
        printf("\n");
    }
}

