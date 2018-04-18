%{
#include "stdlib.h"
#include "stdio.h"
#include "stdarg.h"
#include "tp_symbol_list.h"

void tpperror(char *s, ...);
void addref(int, const char*, char*,int);
extern const char *curfilename;
extern int tpplineno;
//#define YYDEBUG 1
//int yydebug = 1;
%}

%define api.prefix {tpp}

%union{
    char *strval;
    int intval;
    long longval;
    double doubleval;
    struct item_node * node_ptr;
    struct protocol *prtc_ptr;
}

%token <strval> ID 
%token <strval> STRINGVAL
%token <intval> INTEGER8 UINTEGER8 INTEGER16 UINTEGER16 INTEGER32 UINTEGER32 NUM STRING BYTE
%token <intval> INT SHORT CHAR BOOL
%token <longval> LONG INTEGER64 UINTEGER64
%token <doubleval> DOUBLE FLOAT
%token PROTOCOL
%token REPEAT
%token PROTID
%token IMPORT
%token PACKAGE
%token PREFIX
%token KEY
%token PRIMARY
%token FOREIGN
%token SET
%token <intval> '{' '}' ';' '(' ')' '=' '.'

%type <node_ptr> col_definition 
%type <prtc_ptr> def_col_list
%type <prtc_ptr> def_cmd_stmt
%type <node_ptr> def_type
%type <node_ptr> def_key_type
%type <strval> pkg_name
%type <strval> iddot_list 
%type <strval> iddot
%type <intval> vec_len_bytes

%start stmt_list

%%
stmt_list:stmt ';'
| stmt_list stmt ';'
;

stmt: pkg_stmt
;

pkg_stmt: PACKAGE pkg_name{ tpp_set_package_name($2);}
;

pkg_name: ID { $$ = $1;}
| iddot_list ID {
    char *pkgname = malloc(strlen($1) + strlen($2)+ 1);
    strcpy(pkgname, $1);
    strcat(pkgname, $2);
    free($1);
    free($2);
    $$ = pkgname;
}
;

iddot_list: iddot {$$ = $1;}
| iddot_list iddot {
    char *pkgname = malloc(strlen($1) + strlen($2) + 1);
    strcpy(pkgname, $1);
    strcat(pkgname, $2);
    free($1);
    free($2);
    $$ = pkgname;
}
;

iddot: ID '.' {
           char *pkgname = malloc(strlen($1) + 2);
           strcpy(pkgname, $1);
           strcat(pkgname, ".");
           free($1);
           $$ = pkgname;
       }
;

stmt: def_cmd_stmt {tpp_protocol_tab_add($1);}
;

def_cmd_stmt:PROTOCOL ID '{' def_col_list '}'    { addref(tpplineno, curfilename, $2, 1); $$ = tpp_protocol_set_name($4,$2); }
;
def_col_list:col_definition   { $$ = tpp_protocol_new($1);}
| def_col_list col_definition { $$ = tpp_item_list_add_node($1 , $2);}
;

col_definition: def_type ID ';'   { $$ = tpp_item_node_set_name($1 , $2);}
| def_key_type ID ';'        { $$ = tpp_item_node_set_name($1, $2);}
| PROTID ID '=' NUM ';'      { $$ = tpp_new_int_node(VALUE_TYPE_PROTID_INT, $2 , $4);}
| PROTID ID '=' STRINGVAL ';'   { $$ = tpp_new_str_node(VALUE_TYPE_PROTID_INT, $2 , $4);}
| PREFIX KEY STRING ID '=' STRINGVAL ';'  { $$ = tpp_new_str_node(VALUE_TYPE_PREFIX_KEY_STR, $4, $6);}
;

def_type: BYTE                       {$$ = tpp_new_node(VALUE_TYPE_BYTE);}
| REPEAT vec_len_bytes BYTE          {$$ = tpp_new_vec_node(VALUE_TYPE_BYTE_VEC, $2);}
| BOOL                               {$$ = tpp_new_node(VALUE_TYPE_BOOL);}
| REPEAT vec_len_bytes BOOL          {$$ = tpp_new_vec_node(VALUE_TYPE_BOOL_VEC, $2);}
| INTEGER8                           {$$ = tpp_new_node(VALUE_TYPE_INT8);}
| REPEAT vec_len_bytes INTEGER8      {$$ = tpp_new_vec_node(VALUE_TYPE_INT8_VEC, $2);}
| UINTEGER8                          {$$ = tpp_new_node(VALUE_TYPE_UINT8);}
| REPEAT vec_len_bytes UINTEGER8     {$$ = tpp_new_vec_node(VALUE_TYPE_UINT8_VEC, $2);}
| INTEGER16                          {$$ = tpp_new_node(VALUE_TYPE_INT16);}
| REPEAT vec_len_bytes INTEGER16     {$$ = tpp_new_vec_node(VALUE_TYPE_INT16_VEC, $2);}
| UINTEGER16                         {$$ = tpp_new_node(VALUE_TYPE_UINT16);}
| REPEAT vec_len_bytes UINTEGER16    {$$ = tpp_new_vec_node(VALUE_TYPE_UINT16_VEC, $2);}
| INTEGER32                          {$$ = tpp_new_node(VALUE_TYPE_INT32);}
| REPEAT vec_len_bytes INTEGER32     {$$ = tpp_new_vec_node(VALUE_TYPE_INT32_VEC, $2);}
| UINTEGER32                         {$$ = tpp_new_node(VALUE_TYPE_UINT32);}
| REPEAT vec_len_bytes UINTEGER32    {$$ = tpp_new_vec_node(VALUE_TYPE_UINT32_VEC, $2);}
| INTEGER64                          {$$ = tpp_new_node(VALUE_TYPE_INT64);}
| REPEAT vec_len_bytes INTEGER64     {$$ = tpp_new_vec_node(VALUE_TYPE_INT64_VEC, $2);}
| UINTEGER64                         {$$ = tpp_new_node(VALUE_TYPE_UINT64);}
| REPEAT vec_len_bytes UINTEGER64    {$$ = tpp_new_vec_node(VALUE_TYPE_UINT64_VEC, $2);}
| DOUBLE                             {$$ = tpp_new_node(VALUE_TYPE_DOUBLE);}
| REPEAT vec_len_bytes DOUBLE        {$$ = tpp_new_vec_node(VALUE_TYPE_DOUBLE_VEC, $2);}
| FLOAT                              {$$ = tpp_new_node(VALUE_TYPE_FLOAT);}
| REPEAT vec_len_bytes FLOAT         {$$ = tpp_new_vec_node(VALUE_TYPE_FLOAT_VEC, $2);}
| LONG                               {$$ = tpp_new_node(VALUE_TYPE_LONG);}
| REPEAT vec_len_bytes LONG          {$$ = tpp_new_vec_node(VALUE_TYPE_LONG_VEC, $2);}
| INT                                {$$ = tpp_new_node(VALUE_TYPE_INT);}
| REPEAT vec_len_bytes INT           {$$ = tpp_new_vec_node(VALUE_TYPE_INT_VEC, $2);}
| SHORT                              {$$ = tpp_new_node(VALUE_TYPE_SHORT);}
| REPEAT vec_len_bytes SHORT         {$$ = tpp_new_vec_node(VALUE_TYPE_SHORT_VEC, $2);}
| CHAR                               {$$ = tpp_new_node(VALUE_TYPE_CHAR);}
| REPEAT vec_len_bytes CHAR          {$$ = tpp_new_vec_node(VALUE_TYPE_CHAR_VEC, $2);}
| STRING                             {$$ = tpp_new_node(VALUE_TYPE_STR);}
| REPEAT vec_len_bytes STRING        {$$ = tpp_new_vec_node(VALUE_TYPE_STR_VEC, $2);}
| ID                                 {$$ = tpp_new_ref_node($1, VALUE_TYPE_REF); if (!$$) tpperror("The type %s doesn't declared", $1);}
| REPEAT vec_len_bytes ID            {$$ = tpp_new_ref_node($3, VALUE_TYPE_REF_VEC); if (!$$) tpperror("The type %s doesn't declared", $3);}
| SET ID                             {$$ = tpp_new_ref_node($2, VALUE_TYPE_SET_REF); if (!$$) tpperror("The type %s doesn't declared", $2);}
;

vec_len_bytes: {$$ = 4;}
| '(' NUM ')' {$$ = $2;}

def_key_type: PRIMARY KEY INT    { $$ = tpp_new_node(VALUE_TYPE_PRIMARY_KEY_INT);}
| PRIMARY KEY STRING             { $$ = tpp_new_node(VALUE_TYPE_PRIMARY_KEY_STR);}
| FOREIGN KEY INT                { $$ = tpp_new_node(VALUE_TYPE_FOREIGN_KEY_INT);}
| FOREIGN KEY STRING             { $$ = tpp_new_node(VALUE_TYPE_FOREIGN_KEY_STR);}
| SET KEY INT                    { $$ = tpp_new_node(VALUE_TYPE_SET_KEY_INT);}
| SET KEY STRING                 { $$ = tpp_new_node(VALUE_TYPE_SET_KEY_STR);}
| SET PREFIX KEY STRING          { $$ = tpp_new_node(VALUE_TYPE_SET_PREFIX_KEY_STR);}
%%
void
tpperror(char *s, ...)
{
    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d:  error: ", tpplineno);
    //if(yylloc.first_line)
    //    fprintf(stderr, "%d.%d-%d.%d: error: ", yylloc.first_line, yylloc.first_column,
    //            yylloc.last_line, yylloc.last_column);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

