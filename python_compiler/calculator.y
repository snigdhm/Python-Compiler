%{ 
#include <stdio.h> 
#include <string.h>
#include <stdlib.h> 
#include <stdarg.h> 
#include "calc3.h" 
/* prototypes */ 
nodeType *opr(int oper, int nops, ...); 
nodeType *id(int i); 
nodeType *con(int value); 
void freeNode(nodeType *p); 
int ex(nodeType *p); 
int yylex(void); 
void yyerror(char *s); 
int sym[26];                    /* symbol table */ 
%} 
%union { 
    int iValue;                 /* integer value */ 
    char identifier[20];                /* symbol table index */ 
    nodeType *nPtr;             /* node pointer */ 
}; 
%token <iValue> DECIMALINTEGER 
%token <identifier> IDENTIFIER 
%token WHILE IF PRINT DEDENT INDENT END_STATEMENT ELSE ELIF INPUT BREAK CONTINUE RETURN DEF STRING 
%left AND OR IN
%left GE LE EQ NE '>' '<'  
%left '+' '-' 
%left '*' '/' 
%nonassoc UMINUS NOT
%type <nPtr> stmt expr stmt_list ',' codeblock statements elseif ' ' list_item arg fdef fcall STRING function list

%% 
program: 
  function                { exit(0); } 
  ;   
function: 
    function stmt         { ex($2); freeNode($2); } 
  | fdef                  { $$=$1; }
  | /* NULL */ 
  ; 

fdef:
  DEF IDENTIFIER '(' IDENTIFIER ',' IDENTIFIER ',' IDENTIFIER ')' ':' codeblock { $$=opr(DEF,4, $2, $4, $6, $8); } 
  | DEF IDENTIFIER '(' IDENTIFIER ')' ':' codeblock { $$=opr(DEF,2, $2, $4); } 
  ; 
fcall:
  IDENTIFIER '(' arg ')' { $$=opr(id($1),1, $3); } 
  | IDENTIFIER '(' arg ',' arg ',' arg ')' { $$=opr(id($1),3, $3, $5, $7); } 
  ;
arg:
  IDENTIFIER  { $$ = $1; }
  | DECIMALINTEGER { $$ = $1; }
  ;

stmt: 
    ';'                     { $$ = opr(';', 2, NULL, NULL); } 
  | expr ';'                   { $$ = $1; } 
  | PRINT expr ';'            { $$ = opr(PRINT, 1, $2); } 
  | IDENTIFIER '=' expr ';'    { $$ = opr('=', 2, id($1), $3); } 
  | WHILE '(' expr ')' codeblock { $$ = opr(WHILE, 2, $3, $5); } 
  | IF '(' expr ')' codeblock { $$ = opr(IF, 2, $3, $5); } 
  | IF '(' expr ')' ':' codeblock elseif ELSE ':' codeblock 
                          { $$ = opr(IF, 3, $3, $6, $10); } 
  | '{' stmt_list '}'       { $$ = $2; } 
  | RETURN expr ';'	    { $$ = opr(RETURN, 1, $2); } 
  | INPUT '(' STRING ')'    { $$ = opr(INPUT, 1, $3); } 
  | CONTINUE                { $$ = opr(CONTINUE, 1, NULL); } 
  | BREAK                   { $$ = opr(BREAK, 1, NULL); } 
  | list                    { $$ = $1; } 
  | fcall                   { $$ = $1; } 
  ;
stmt_list:   
  stmt END_STATEMENT                 { $$ = $1; } 
  | stmt_list stmt        { $$ = opr(';', 2, $1, $2); } 
  ; 
list:
  '[' list_item ']'     { $$ = opr(';', 1, $2); } 
  | '['' '']'                 { $$ = opr(';', 2, NULL, NULL); } 
  | '[' ']'                 { $$ = opr(';', 2, NULL, NULL); } 
  ;
list_item:
   list_item ',' DECIMALINTEGER  { $$ = opr(';', 2, $1,con($3)); }
  | DECIMALINTEGER { $$ = con($1); }
  ;
elseif:
  ELIF '(' expr ')' ':' codeblock elseif  { $$ = opr(ELIF, 2, $3, $6); }
  |                                 
  ;
statements:
  stmt_list END_STATEMENT   { $$ = $1; } 
  | stmt                    { $$ = $1; } 
  ;
codeblock:
  INDENT statements DEDENT          { $$ = $2; } 
  ;

expr: 
    DECIMALINTEGER               { $$ = con($1); } 
  | IDENTIFIER              { $$ = id($1); } 
  | '-' expr %prec UMINUS { $$ = opr(UMINUS, 1, $2); } 
  | expr '+' expr         { $$ = opr('+', 2, $1, $3); }
  | expr IN expr         { $$ = opr(IN, 2, $1, $3); } 
  | expr NOT IN expr %prec NOT        { $$ = opr(NOT IN, 2, $1, $4); }
  | expr '-' expr         { $$ = opr('-', 2, $1, $3); } 
  | expr '*' expr         { $$ = opr('*', 2, $1, $3); } 
  | expr '/' expr         { $$ = opr('/', 2, $1, $3); } 
  | expr '<' expr         { $$ = opr('<', 2, $1, $3); } 
  | expr '>' expr         { $$ = opr('>', 2, $1, $3); } 
  | NOT expr %prec NOT    { $$ = opr(NOT, 1, $2); }
  | expr GE expr          { $$ = opr(GE, 2, $1, $3); } 
  | expr LE expr          { $$ = opr(LE, 2, $1, $3); } 
  | expr NE expr          { $$ = opr(NE, 2, $1, $3); } 
  | expr EQ expr          { $$ = opr(EQ, 2, $1, $3); } 
  | '(' expr ')'          { $$ = $2; } 
  | expr AND expr         { $$ = opr(AND, 2, $1, $3); } 
  | expr OR expr         { $$ = opr(OR, 2, $1, $3); } 
  ;   

%% 
#define SIZEOF_NODETYPE ((char *)&p->con - (char *)p) 
nodeType *con(int value) { 
    nodeType *p; 
    /* allocate node */ 
    if ((p = malloc(sizeof(nodeType))) == NULL) 
        yyerror("out of memory"); 
    /* copy information */ 
    p->type = typeCon; 
    p->con.value = value; 
    return p; 
} 
nodeType *id(char[20] i) { 
    nodeType *p; 
    /* allocate node */ 
    if ((p = malloc(sizeof(nodeType))) == NULL) 
        yyerror("out of memory"); 
    /* copy information */ 
    p->type = typeId; 
    strcpy(p->id.i,i); 
    return p; 
} 

nodeType *opr(int oper, int nops, ...) {
    va_list ap; 
    nodeType *p; 
    int i; 
    /* allocate node, extending op array 
*/ 
    if ((p = malloc(sizeof(nodeType) + (nops-1) * sizeof(nodeType *))) == NULL) 
        yyerror("out of memory"); 
    /* copy information */ 
    p->type = typeOpr; 
    p->opr.oper = oper; 
    p->opr.nops = nops; 
    va_start(ap, nops); 
    for (i = 0; i < nops; i++) 
        p->opr.op[i] = va_arg(ap, nodeType*); 
    va_end(ap); 
    return p; 
} 
void freeNode(nodeType *p) { 
    int i; 
    if (!p) return; 
    if (p->type == typeOpr) { 
        for (i = 0; i < p->opr.nops; i++) 
            freeNode(p->opr.op[i]); 
    }
    free (p); 
} 
void yyerror(char *s) { 
    fprintf(stdout, "%s\n", s); 
} 
int main(void) { 
    yyparse(); 
    return 0; 
} 
