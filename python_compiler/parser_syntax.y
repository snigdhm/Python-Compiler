%{ 
#include <stdio.h> 
#include <string.h>
#include <stdlib.h> 
#include <stdarg.h> 
#include "calc3.h" 
/* prototypes */ 
nodeType *opr(int oper, int nops, ...); 
nodeType *opra(nodeType *oper, int nops, ...); 
nodeType *id(char i[20]); 
nodeType *st(char i[20]);
nodeType *con(int value); 
void freeNode(nodeType *p); 
int ex(nodeType *p); 
int yylex(void); 
void yyerror(char *s); 
int sym[26];  
extern int yylineno;                  /* symbol table */ 
%} 
%union { 
    int iValue;                 /* integer value */ 
    char identifier[20];                /* symbol table index */ 
    char text[20];
    nodeType *nPtr;             /* node pointer */ 
}; 
%token <iValue> DECIMALINTEGER 
%token <identifier> IDENTIFIER 
%token <text> STRING
%token WHILE IF PRINT DEDENT INDENT END_STATEMENT ELSE ELIF INPUT BREAK CONTINUE RETURN DEF 
%left AND OR IN NOT_IN
%left GE LE EQ NE '>' '<'  
%left '+' '-' 
%left '*' '/' 
%nonassoc UMINUS NOT
%type <nPtr> stmt expr codeblock statements elseif list_item arg fdef fcall function list list_

%% 
program: 
  function                {  } 
  ;   
function: 
    function stmt         { ex($2); freeNode($2); } 
  | /* NULL */ 
  ; 

fdef:
  DEF IDENTIFIER '(' IDENTIFIER ',' IDENTIFIER ',' IDENTIFIER ')' ':' codeblock { $$=opra(id("fdef"),10, id("def"),id("("), id($4),id(","), id($6),id(","), id($8),id(")"),id(":"),$11); } 
  | DEF IDENTIFIER '(' ')' ':' codeblock { $$=opra(id("fdef"),2, id("def"),$6); } 
  ; 
fcall:
  IDENTIFIER '(' ')' { $$=opra(id("fcall"),3, id($1),id("("),id(")")); } 
  | IDENTIFIER '(' arg ',' arg ',' arg ')' { $$=opra(id("fcall"),8, id($1),id("("),$3,id(","),$5,id(","),$7,id(")")); } 
  ;
arg:
  IDENTIFIER  { $$ = id($1); }
  | DECIMALINTEGER { $$ = con($1); }
  ;

stmt: 
    ';'                     { $$ = opra(id("stmt"),1,id(";")); } 
  | END_STATEMENT                 { $$ = opra(id("stmt"),1,id("end_stmt")); } 
  | expr ';'                   { $$ = opra(id("stmt"),2,$1,id(";")); } 
  | expr END_STATEMENT                   { $$ = opra(id("stmt"),2,$1,id("end_stmt")); } 
  | PRINT '(' expr ')'';'            { $$ = opra(id("stmt"),5,id("print"),id("("),$3,id(")"),id(";")); } 
  | PRINT '(' expr ')' END_STATEMENT            { $$ =opra(id("stmt"),5,id("print"),id("("),$3,id(")"),id("end_stmt")); } 
  | IDENTIFIER '=' expr ';'     { $$ = opra(id("stmt"),4,id($1),id("="),$3,id(";")); }
  | IDENTIFIER '=' expr END_STATEMENT     { $$ = opra(id("stmt"),4,id($1),id("="),$3,id("end_stmt")); }
  | list_ '=' expr ';'     { $$ = opra(id("stmt"),4,$1,id("="),$3,id(";")); }
  | list_ '=' expr END_STATEMENT     { $$ = opra(id("stmt"),4,$1,id("="),$3,id("end_stmt")); }
  | WHILE '(' expr ')' ':' codeblock { $$ = opra(id("stmt"),6,id("while"),id("("),$3,id(")"),id(":"),$6); }
  | IF '(' expr ')' ':' codeblock { $$ =  opra(id("stmt"),6,id("if"),id("("),$3,id(")"),id(":"),$6); } 
  | IF '(' expr ')' ':' codeblock elseif ELSE ':' codeblock 
                          { $$ =  opra(id("stmt"),10,id("if"),id("("),$3,id(")"),id(":"),$6,$7,id("else"),id(":"),$10); } 
  | '{' statements '}'       { $$ = opra(id("stmt"),3,id("{"),$2,id("}")); } 
  | RETURN expr ';'	    { $$ = opra(id("stmt"),3,id("return"),$2,id(";")); } 
  | RETURN expr END_STATEMENT	    { $$ = opra(id("stmt"),3,id("return"),$2,id("end_stmt")); } 
  | IDENTIFIER '=' INPUT '(' expr ')' END_STATEMENT    { $$ = opra(id("stmt"),7,id($1),id("="),id("input"),id("("),$5,id(")"),id("end_stmt"));}
  | IDENTIFIER '=' INPUT '(' expr ')' ';'    { $$ = opra(id("stmt"),7,id($1),id("="),id("input"),id("("),$5,id(")"),id(";")); } 
  | CONTINUE END_STATEMENT              { $$ = $$ = opra(id("stmt"),2,id("continue"),id("end_stmt")); } 
  | CONTINUE ';'              { $$ = opra(id("stmt"),2,id("continue"),id(";")); }
  | BREAK ';'                   { $$ = opra(id("stmt"),2,id("break"),id(";")); } 
  | BREAK END_STATEMENT                   { $$ = opra(id("stmt"),2,id("break"),id("end_stmt")); } 
  | IDENTIFIER '=' list ';'                   {$$=opra(id("stmt"),4,id($1),id("="),$3,id(";")); } 
  | IDENTIFIER '=' list END_STATEMENT                   {$$=opra(id("stmt"),4,id($1),id("="),$3,id("end_stmt"));} 
  | fdef                   { $$=opra(id("stmt"),1,$1); } 
  | fcall ';'                  { $$=opra(id("stmt"),2,$1,id(";")); }
  | fcall END_STATEMENT                  {  $$=opra(id("stmt"),2,$1,id("end_stmt")); }
  | IDENTIFIER '=' fcall ';'                  {  $$=opra(id("stmt"),4,id($1),id("="),$3,id(";")); }
  | IDENTIFIER '=' fcall END_STATEMENT                 { $$=opra(id("stmt"),4,id($1),id("="),$3,id("end_stmt")); }
  ;

list:
  '[' list_item']'     { $$=opra(id("list"),3,id("["),$2,id("]")); } 
  | '['' '']'                 { $$ = opra(id("list"),2,id("["),id("]")); } 
  | '[' ']'                 { $$ = opra(id("list"),2,id("["),id("]")); } 
  ;
list_item:
   list_item ',' DECIMALINTEGER  { $$ = opra(id("list_item"),3,$1,id(","),con($3)); }
  | DECIMALINTEGER { $$ = con($1); }
  ;
elseif:
  ELIF '(' expr ')' ':' codeblock elseif  { $$ = opra(id("elseif"),7, id("elif"),id("("),$3,id(")"),id(":"),$6,$7); }
  |    {$$=NULL;}                             
  ;
statements:
  statements stmt    { $$ =opra(id("statements"),2,$1,$2);  }
  | stmt                    { $$ =opra(id("statements"),1,$1);  } 
  ;
codeblock:
  INDENT statements DEDENT          { $$ = opra(id("codeblock"),3,id("indent"),$2,id("dedent")); } 
  ;

expr: 
    DECIMALINTEGER               { $$ = con($1); } 
  | IDENTIFIER              { $$ = id($1); } 
  | STRING                  { $$ = st($1); }
  | list_                    { $$ =$1; }
  | '-' expr %prec UMINUS { $$ = opra(id("expr"),2,id("-"),$2); } 
  | expr '+' expr         { $$ = opra(id("expr"),3,$1,id("+"),$3);  }
  | expr IN expr         { $$ = opra(id("expr"),3,$1,id("in"),$3);  } 
  | expr NOT_IN expr        { $$ =opra(id("expr"),3,$1,id("not_in"),$3);  }
  | expr '-' expr         { $$ = opra(id("expr"),3,$1,id("-"),$3);  } 
  | expr '*' expr         { $$ = opra(id("expr"),3,$1,id("*"),$3);  } 
  | expr '/' expr         { $$ = opra(id("expr"),3,$1,id("/"),$3);  } 
  | expr '<' expr         { $$ = opra(id("expr"),3,$1,id("<"),$3);  } 
  | expr '>' expr         { $$ = opra(id("expr"),3,$1,id(">"),$3);  } 
  | NOT expr %prec NOT    { $$ = opra(id("expr"),2,id("Not"),$2);  }
  | expr GE expr          { $$ = opra(id("expr"),3,$1,id(">="),$3);  } 
  | expr LE expr          { $$ =opra(id("expr"),3,$1,id("<="),$3); } 
  | expr NE expr          { $$ = opra(id("expr"),3,$1,id("!="),$3);  } 
  | expr EQ expr          { $$ = opra(id("expr"),3,$1,id("=="),$3);  } 
  | '(' expr ')'          { $$ = opra(id("expr"),3,id("("),$2,id(")"));  } 
  | expr AND expr         { $$ =opra(id("expr"),3,$1,id("and"),$3);  } 
  | expr OR expr         { $$ = opra(id("expr"),3,$1,id("or"),$3);  } 
  ;  

list_:
 IDENTIFIER '[' DECIMALINTEGER ']' {$$=opra(id("list_"),4,id($1),id("["),con($3),id("]"));} 
  | IDENTIFIER'[' IDENTIFIER ']' {$$=opra(id("list_"),4,id($1),id("["),id($3),id("]"));}
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
nodeType *id(char i[20]) { 
    nodeType *p; 
    /* allocate node */ 
    if ((p = malloc(sizeof(nodeType))) == NULL) 
        yyerror("out of memory"); 
    /* copy information */ 
    p->type = typeId; 
    strcpy(p->id.i,i); 
    return p; 
} 

nodeType *st(char i[20]) { 
    nodeType *p; 
    /* allocate node */ 
    if ((p = malloc(sizeof(nodeType))) == NULL) 
        yyerror("out of memory"); 
    /* copy information */ 
    p->type = typeStr; 
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
    p->opr.opr = oper; 
    p->opr.nops = nops; 
    va_start(ap, nops); 
    for (i = 0; i < nops; i++) 
        p->opr.op[i] = va_arg(ap, nodeType*); 
    va_end(ap); 
    return p; 
} 
nodeType *opra(nodeType *oper, int nops, ...) {
    va_list ap; 
    nodeType *p; 
    int i; 
    /* allocate node, extending op array 
*/ 
    if ((p = malloc(sizeof(nodeType) + (nops-1) * sizeof(nodeType *))) == NULL) 
        yyerror("out of memory"); 
    /* copy information */ 
    p->type = typeOpr; 
    strcpy(p->opr.opa,oper->id.i); 
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
    fprintf(stdout, "%s at line no %d\n", s,yylineno); 
} 
/*
int main(void) { 
    yyparse(); 
    return 0; 
} */
