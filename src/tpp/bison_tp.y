%{
#include "stdlib.h"
#include "stdio.h"
#include "stdarg.h"
#include "tp_symbol_list.h"

void tpperror(char *s, ...);

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
%token  REPEAT
%token <intval> '{' '}' ';' '(' ')'

%type <node_ptr> col_definition 
%type <prtc_ptr> def_col_list
%type <prtc_ptr> def_cmd_stmt
%type <node_ptr> def_type

%start stmt_list

%%
stmt_list:stmt ';'
| stmt_list stmt ';'
;

stmt: def_cmd_stmt {tpp_protocol_tab_add($1);}
;

def_cmd_stmt:PROTOCOL ID '{' def_col_list '}'    { $$ = tpp_protocol_set_name($4,$2); }
;
def_col_list:col_definition   { $$ = tpp_protocol_new($1);}
| def_col_list col_definition { $$ = tpp_item_list_add_node($1 , $2);}
;

col_definition: def_type ID ';'   { $$ = tpp_item_node_set_name($1 , $2);}
;

def_type: BYTE                       {$$ = tpp_new_node(VALUE_TYPE_BYTE);}
| REPEAT BYTE                        {$$ = tpp_new_node(VALUE_TYPE_BYTE_VEC);}
| BOOL                               {$$ = tpp_new_node(VALUE_TYPE_BOOL);}
| REPEAT BOOL                        {$$ = tpp_new_node(VALUE_TYPE_BOOL_VEC);}
| INTEGER8                           {$$ = tpp_new_node(VALUE_TYPE_INT8);}
| REPEAT INTEGER8                    {$$ = tpp_new_node(VALUE_TYPE_INT8_VEC);}
| UINTEGER8                          {$$ = tpp_new_node(VALUE_TYPE_UINT8);}
| REPEAT UINTEGER8                   {$$ = tpp_new_node(VALUE_TYPE_UINT8_VEC);}
| INTEGER16                          {$$ = tpp_new_node(VALUE_TYPE_INT16);}
| REPEAT INTEGER16                   {$$ = tpp_new_node(VALUE_TYPE_INT16_VEC);}
| UINTEGER16                         {$$ = tpp_new_node(VALUE_TYPE_UINT16);}
| REPEAT UINTEGER16                  {$$ = tpp_new_node(VALUE_TYPE_UINT16_VEC);}
| INTEGER32                          {$$ = tpp_new_node(VALUE_TYPE_INT32);}
| REPEAT INTEGER32                   {$$ = tpp_new_node(VALUE_TYPE_INT32_VEC);}
| UINTEGER32                         {$$ = tpp_new_node(VALUE_TYPE_UINT32);}
| REPEAT UINTEGER32                  {$$ = tpp_new_node(VALUE_TYPE_UINT32_VEC);}
| INTEGER64                          {$$ = tpp_new_node(VALUE_TYPE_INT64);}
| REPEAT INTEGER64                   {$$ = tpp_new_node(VALUE_TYPE_INT64_VEC);}
| UINTEGER64                         {$$ = tpp_new_node(VALUE_TYPE_UINT64);}
| REPEAT UINTEGER64                  {$$ = tpp_new_node(VALUE_TYPE_UINT64_VEC);}
| DOUBLE                             {$$ = tpp_new_node(VALUE_TYPE_DOUBLE);}
| REPEAT DOUBLE                      {$$ = tpp_new_node(VALUE_TYPE_DOUBLE_VEC);}
| FLOAT                              {$$ = tpp_new_node(VALUE_TYPE_FLOAT);}
| REPEAT FLOAT                       {$$ = tpp_new_node(VALUE_TYPE_FLOAT_VEC);}
| LONG                               {$$ = tpp_new_node(VALUE_TYPE_LONG);}
| REPEAT LONG                        {$$ = tpp_new_node(VALUE_TYPE_LONG_VEC);}
| INT                                {$$ = tpp_new_node(VALUE_TYPE_INT);}
| REPEAT INT                         {$$ = tpp_new_node(VALUE_TYPE_INT_VEC);}
| SHORT                              {$$ = tpp_new_node(VALUE_TYPE_SHORT);}
| REPEAT SHORT                       {$$ = tpp_new_node(VALUE_TYPE_SHORT_VEC);}
| CHAR                               {$$ = tpp_new_node(VALUE_TYPE_CHAR);}
| REPEAT CHAR                        {$$ = tpp_new_node(VALUE_TYPE_CHAR_VEC);}
| STRING                             {$$ = tpp_new_node(VALUE_TYPE_STR);}
| REPEAT STRING                      {$$ = tpp_new_node(VALUE_TYPE_STR_VEC);}
| ID                                 {$$ = tpp_new_ref_node($1, VALUE_TYPE_REF); if (!$$) tpperror("The type %s doesn't declared", $1);}
| REPEAT ID                          {$$ = tpp_new_ref_node($2, VALUE_TYPE_REF_VEC); if (!$$) tpperror("The type %s doesn't declared", $2);}
;

%%
void
tpperror(char *s, ...)
{
    extern int tpplineno;
    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d:  error: ", tpplineno);
    //if(yylloc.first_line)
    //    fprintf(stderr, "%d.%d-%d.%d: error: ", yylloc.first_line, yylloc.first_column,
    //            yylloc.last_line, yylloc.last_column);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

