%option noyywrap nodefault yylineno prefix="tpp"

%{
#include "stdio.h"
#include "bison_tp.h"
#include "tp_symbol_list.h"

    struct bufstack {
        struct bufstack *prev;/* previous entry */
        YY_BUFFER_STATE bs; /* saved buffer */
        int lineno;/* saved line number */
        const char *filename;/* name of this file */
        FILE *f; /* current file */
        struct generated_file *gfile;
    } *curbs = 0; 

    int newfile(const char *fn);
    int popfile(void);

    const char *curfilename = NULL; /* name of current input file */

    extern struct protocol *proto_tab_head;
    extern struct protocol *proto_tab_tail;
    extern struct inc_file *incfile_head;
    extern struct inc_file *incfile_tail;
    extern struct generated_file *current_gfile;
    extern char *g_packagename;
%}

%x ifile
%x COMMENT

%%
"{"             {tpplval.intval = 1;return yytext[0];}
"}"             {tpplval.intval = 2;return yytext[0];}
"("             {tpplval.intval = 3;return yytext[0];}
")"             {tpplval.intval = 4;return yytext[0];}
";"             {tpplval.intval = 5;return yytext[0];}
":"             {tpplval.intval = 6;return yytext[0];}
"="             {tpplval.intval = 7;return yytext[0];}
","             {tpplval.intval = 8;return yytext[0];}
"."             {tpplval.intval = 9;return yytext[0];}

"protocol"      {return PROTOCOL;}
"repeat"    {return REPEAT;}
"import"    {return IMPORT;}
"package"   {return PACKAGE;}
"key"       {return KEY;}
"primary"   {return PRIMARY;}
"foreign"   {return FOREIGN;}
"prefix"    {return PREFIX;}

"bool"     {tpplval.intval = 1;return BOOL;}
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
"protid"    {tpplval.intval=4;return PROTID;}

-?[0-9]+          {tpplval.intval = atoi(yytext); return NUM;}
([a-zA-Z_]+)([a-zA-Z_0-9]*)       {tpplval.strval = strdup(yytext); return ID;}
0[xX]+[0-9A-Fa-f]+          {tpplval.strval = strdup(yytext);return STRINGVAL;}

\'([^'\\]|\\['"?\\abfnrtv]|\\[0-7]{1,3}|\\[Xx][0-9a-fA-F]+)+\' {
int len = strlen(yytext);
tpplval.strval = malloc(len - 1);
strncpy(tpplval.strval , yytext+1 , len - 2); 
tpplval.strval[len - 2] = '\0';

return STRINGVAL;
} 

"//".*\n

"/*" { BEGIN(COMMENT); }
<COMMENT>"*/" { BEGIN(INITIAL); }
<COMMENT>([^*]|\n)+|.
<COMMENT><<EOF>> { printf("%s:%d: Unterminated comment\n",
        curfilename, yylineno); return 0; }

[ \t\n]

^[ \t]*import[ \t]* {BEGIN ifile;}

<ifile>[^ ;\t\n]+ {
    {
        int c;
        while((c = input()) && c != '\n') ;
    }
    
    newfile(strdup(yytext));
    BEGIN(INITIAL);
}

<<EOF>> {
    if ( !popfile()) {
        yyterminate();
    }
}

.               {printf("mistery char\n");}


%%

int newfile(const char *fn)
{
    FILE *f = fopen(fn, "r");
    struct bufstack *bs = malloc(sizeof(struct bufstack));
    /* die if no file or no room */
    if(!f) { perror(fn); return -1; }
    if(!bs) { perror("malloc"); return -1; }
    /* remember state */
    if(curbs){
        curbs->lineno = yylineno;
        curbs->gfile->packagename = g_packagename;
    }

    bs->gfile = tpp_gfile_new(fn);
    bs->prev = curbs;
    /* set up current entry */
    bs->bs = yy_create_buffer(f, YY_BUF_SIZE);
    bs->f = f;
    bs->filename = fn;
    yy_switch_to_buffer(bs->bs);
    curbs = bs;
    yylineno = 1;
    curfilename = fn;

    return 0;
}
int popfile(void)
{
    struct bufstack *bs = curbs;
    if(!bs) return 0;
    /* get rid of current entry */
    fclose(bs->f);
    yy_delete_buffer(bs->bs);

    /* save the gfile */
    struct generated_file *gfile = bs->gfile;
    if (gfile->packagename == NULL){
        gfile->packagename = g_packagename;
    }
    gfile->incfile_head = incfile_head;
    gfile->incfile_tail = incfile_tail;
    gfile->proto_tab_head = proto_tab_head;
    gfile->proto_tab_tail = proto_tab_tail;

    incfile_head = incfile_tail = NULL;
    proto_tab_head = proto_tab_tail = NULL;

    tpp_gfile_add(gfile);
    gfile= NULL;

    /* switch back to previous */
    curbs = bs->prev;

    free(bs);
    bs = NULL;

    if(!curbs) return 0;
    yy_switch_to_buffer(curbs->bs);
    yylineno = curbs->lineno;
    curfilename = curbs->filename;
    g_packagename = curbs->gfile->packagename;

    return 1;
}

