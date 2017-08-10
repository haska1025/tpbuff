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
    struct protocal *prtc_ptr;
    struct key_val *kv_node;
    struct tang_cmd *cmd;
}

%token <strval> ID 
%token <strval> STRINGVAL
%token <intval> INTEGER16 INTEGER32 OCTETS NUM BITS STRING
%token DEFINITION 
%token PROTOCAL 
%token <intval> '{' '}' ';' '(' ')'

%type <node_ptr> col_definition 
%type <prtc_ptr> def_col_list
%type <prtc_ptr> def_cmd_stmt
%type <node_ptr> def_type
%type <strval> default_val
%type <cmd> cmd_stmt
%type <cmd> key_val_list
%type <kv_node> key_val_pair

%start stmt_list

%%
stmt_list:stmt ';'
| stmt_list stmt ';'
;

stmt:cmd_stmt { tang_cmd_save($1);}
| def_cmd_stmt {tang_protocal_tab_add($1);}
;

def_cmd_stmt:DEFINITION PROTOCAL ID '{' def_col_list '}'    { $$ = tang_protocal_set_name($5,$3); }
;
def_col_list:col_definition   { $$ = tang_new_protocal( $1);}
| def_col_list col_definition { $$ = tang_item_list_add_node($1 , $2);}
;

col_definition:ID def_type ';'   { $$ = tang_item_node_set_name($2 , $1);}
;

def_type:INTEGER16 NUM               {$$ = tang_new_int16_node($1 , $2);}
| INTEGER16                          {$$ = tang_new_int16_node($1 , 0);}
| INTEGER32  NUM                     {$$ = tang_new_int32_node($1 , $2);}
| INTEGER32                          {$$ = tang_new_int32_node($1 , 0);}
| OCTETS  '(' NUM ')' default_val    {/*$$ = tang_new_bytes_node($1 * $3 , $5);*/}
| BITS  '(' NUM ')' default_val      {/*$$ = tang_new_bits_node($1 * $3 , $5);*/}
| STRING '(' NUM ')' default_val     {$$ = tang_new_str_node($1 *$3  , $5);}
;

default_val:  {$$ = NULL;}
| STRINGVAL      {$$ = $1;}
;

cmd_stmt:ID ':' key_val_list {$$=tang_cmd_set_name($3,$1);}
;

key_val_list:key_val_pair {$$=tang_new_tang_cmd($1);}
| key_val_list ',' key_val_pair {$$=tang_cmd_add($1,$3);}
;

key_val_pair: ID '=' STRINGVAL {$$=tang_new_key_val($1,$3);}
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

