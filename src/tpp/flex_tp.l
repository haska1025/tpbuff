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

"definition"    {return DEFINITION;}
"protocal"      {return PROTOCAL;}
"integer16"     {tpplval.intval = 2;return INTEGER16;}
"integer32"     {tpplval.intval = 4;return INTEGER32;}
"octets"         {tpplval.intval = 1;return OCTETS;}
"bits"           {tpplval.intval = 1;return BITS;}
"varchar"       {tpplval.intval = 1;return STRING;}
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

