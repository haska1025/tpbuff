%option noyywrap nodefault yylineno case-insensitive prefix="tpp"
%{
#include "stdio.h"
#include "bison_tp.h"
%}

%%
"{"             {tpplval.intval = 1;return yytext[0];}
"}"             {tpplval.intval = 2;return yytext[0];}
"("             {tpplval.intval = 3;return yytext[0];}
")"             {tpplval.intval = 4;return yytext[0];}
";"             {tpplval.intval = 5;return yytext[0];}
":"             {tpplval.intval = 6;return yytext[0];}
"="             {tpplval.intval = 7;return yytext[0];}
","             {tpplval.intval = 8;return yytext[0];}

"protocol"      {return PROTOCOL;}
"repeat"    {return REPEAT;}

"byte"     {tpplval.intval = 1;return BYTE;}
"int8"     {tpplval.intval = 1;return INTEGER8;}
"uint8"     {tpplval.intval = 1;return UINTEGER8;}
"int16"     {tpplval.intval = 2;return INTEGER16;}
"uint16"     {tpplval.intval = 2;return UINTEGER16;}
"int32"     {tpplval.intval = 4;return INTEGER32;}
"uint32"     {tpplval.intval = 4;return UINTEGER32;}
"int64"     {tpplval.longval = 8;return INTEGER64;}
"uint64"     {tpplval.longval = 8;return UINTEGER64;}
"string"       {tpplval.intval = 1;return STRING;}
"char"     {tpplval.intval = 1;return CHAR;}
"int"     {tpplval.intval = 4;return INT;}
"short"     {tpplval.intval = 2;return SHORT;}
"long"     {tpplval.longval = 8;return LONG;}
"double"     {tpplval.doubleval= 8;return DOUBLE;}
"float"     {tpplval.doubleval= 4;return FLOAT;}

[0-9]+          {tpplval.intval = atoi(yytext); return NUM;}
([a-zA-Z_]+)([a-zA-Z_0-9]*)       {tpplval.strval = strdup(yytext);return ID;}

\'([^'\\]|\\['"?\\abfnrtv]|\\[0-7]{1,3}|\\[Xx][0-9a-fA-F]+)+\' {
int len = strlen(yytext);
tpplval.strval = malloc(len - 1);
strncpy(tpplval.strval , yytext+1 , len - 2); 
tpplval.strval[len - 2] = '\0';

return STRINGVAL;
} 
"//".*
[ \t\n]
<<EOF>>         {return 0;}
.               {printf("mistery char\n");}

