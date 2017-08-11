%{
#include "stdlib.h"
#include "stdio.h"
#include "stdarg.h"
#include "tp_symbol_list.h"

void tpperror(char *s, ...);

//#define YYDEBUG 1
//int yydebug = 1;
%}

%define api.prefix tpp 

%union{
    char *strval;
    int intval;
    struct item_node * node_ptr;
    struct protocol *prtc_ptr;
}

%token <strval> ID 
%token <strval> STRINGVAL
%token <intval> INTEGER16 INTEGER32 OCTETS NUM BITS STRING
%token PROTOCOL 
%token <intval> '{' '}' ';' '(' ')'

%type <node_ptr> col_definition 
%type <prtc_ptr> def_col_list
%type <prtc_ptr> def_cmd_stmt
%type <node_ptr> def_type
%type <strval> default_val

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

def_type:INTEGER16 NUM               {$$ = tpp_new_int16_node($1 , $2);}
| INTEGER16                          {$$ = tpp_new_int16_node($1 , 0);}
| INTEGER32  NUM                     {$$ = tpp_new_int32_node($1 , $2);}
| INTEGER32                          {$$ = tpp_new_int32_node($1 , 0);}
| OCTETS  '(' NUM ')' default_val    {/*$$ = tpp_new_bytes_node($1 * $3 , $5);*/}
| BITS  '(' NUM ')' default_val      {/*$$ = tpp_new_bits_node($1 * $3 , $5);*/}
| STRING '(' NUM ')' default_val     {$$ = tpp_new_str_node($1 *$3  , $5);}
;

default_val:  {$$ = NULL;}
| STRINGVAL      {$$ = $1;}
;

%%
void
tpperror(char *s, ...)
{
    extern int tpplineno;
    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d:  error: ", tpplineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

