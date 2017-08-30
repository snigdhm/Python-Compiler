%{ 
#include <stdio.h> 
#include <string.h>
#include <stdlib.h> 
#include <stdarg.h> 
#include<ctype.h>
#include "calc3.h" 

#include "symboltfunc.c"
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
extern char *yytext;
extern int yylineno; 
extern int pointer; 
extern int counter;
int while_entered=0;
int err1=0; 
int initialized=0;
 char buff[10];              /* symbol table */ 
STACK1 symbolstk;

void return_check(){
if(pointer==0)
 {
printf("'return' outside function");printSymbol_table(&symbolstk);exit(0);
 }
}

int context_check(char a[])
{
        int s;//printf("pointer1:%d",pointer1);
	s=probe(&symbolstk,a,pointer);
//printf("s:%d",s);
	if (s!=1 && s!=2)
	{
	        s= probe(&symbolstk,a,0);
	        if(s!=1 && s!=2)
		  {
		    printf( "\nERROR: Semantic error at line : %d : undeclared identifier\n",yylineno);//exit(0);
		    err1=1;printSymbol_table(&symbolstk);
		    exit(0);
		  }
	         return s;
		
	}
	else
	{
        return s;
        }
}

int context_check_func(char a[])
{
        int s;//printf("pointer1:%d",pointer1);
	s=probe(&symbolstk,a,pointer);
//printf("s:%d",s);
	if (s!=3 && s!=0)
	{
	        s= probe(&symbolstk,a,0);
	        if(s!=3 && s!=0)
		  {
		    printf( "\nERROR: Semantic error at line : %d : undefined function\n",yylineno);//exit(0);
		    err1=1;
		    exit(0);
		  }
	         return s;
		
	}
	else
	{
        return s;
        }
}

void check_no_of_param(char a[],int no)
{
int s;//printf("pointer1:%d",pointer1);
	s=probe(&symbolstk,a,0);
//printf("s:%d",s);
	if (s>no)
	{
		    printf( "\nERROR: Too less arguments at line : %d\n",yylineno);//exit(0);
		    err1=1;printSymbol_table(&symbolstk);
		    exit(0);
		
	}
	else if(s<no)
	{
		    printf( "\nERROR: Too many arguments at line : %d\n",yylineno);//exit(0);
		    err1=1;printSymbol_table(&symbolstk);
		    exit(0);
	}

}

void jump_check(char a[]){
if(while_entered==0)
 {
   printf("\nERROR: %s outside loop : %d\n",a,yylineno);printSymbol_table(&symbolstk);
   err1=1;exit(0);
 }
}
type_err(int t1,int t2)
{
	
	if(t1!=t2)
	{
		printf( "\nERROR: Semantic error at line : %d : Type mismatch!\n",yylineno);
		err1=1;printSymbol_table(&symbolstk);
		exit(0);
	}
	
}
init(){
if(initialized==0){initStack1(&symbolstk,10);
                       
   		enterScope(&symbolstk);
		initialized=1;}
}

%} 
%union { 
    int iValue;                 /* integer value */ 
    char identifier[20];                /* symbol table index */ 
    char text[20];
    nodeType *nPtr;             /* node pointer1 */ 
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
%start program

%% 
program: 
  function   {printSymbol_table(&symbolstk);}            
  ;   
function: 
    function stmt         
  | /* NULL */ 
  ; 

fdef:
  DEF IDENTIFIER '(' parameter ')' ':' codeblock {init();
						addId(&symbolstk,"def","KEYWORD",-1,pointer);
					addId(&symbolstk,$2,"identifier",3,pointer);}
  |  DEF IDENTIFIER '(' parameter_ ')' ':' codeblock {init();printf("\npointer:%d\n",pointer);
					addId(&symbolstk,"def","KEYWORD",-1,pointer);
					addId(&symbolstk,$2,"identifier",0,pointer);}
  ; 
parameter:
  IDENTIFIER ',' IDENTIFIER ',' IDENTIFIER {init();enterScope(&symbolstk);
						addId(&symbolstk,$1,"identifier",1,pointer);
						addId(&symbolstk,$3,"identifier",1,pointer);
						addId(&symbolstk,$5,"identifier",1,pointer);}
  ;
parameter_:
    {init();enterScope(&symbolstk);}
  ;
fcall:
  IDENTIFIER '(' ')' {init();$$=context_check_func($1);check_no_of_param($1,0);}
  | IDENTIFIER '(' arg ',' arg ',' arg ')' {init();$$=context_check_func($1);check_no_of_param($1,3);}
  ;
arg:
  IDENTIFIER     {init();$$=context_check($1);}  
  | DECIMALINTEGER {init();sprintf(buff,"%d",$1);addId(&symbolstk,buff,"decimalint",1,pointer);$$=1;}
  ;

stmt: 
    ';'                     { init(); } 
  | END_STATEMENT                 { init(); } 
  | expr ';'                   { init(); } 
  | expr END_STATEMENT                   { init(); } 
  | PRINT '(' expr ')'';'            { init();addId(&symbolstk,"print","KEYWORD",-1,pointer); } 
  | PRINT '(' expr ')' END_STATEMENT            { init();addId(&symbolstk,"print","KEYWORD",-1,pointer); } 
  | IDENTIFIER '=' expr ';'     { init();addId(&symbolstk,$1,"identifier",(int)$3,pointer); }
  | IDENTIFIER '=' expr END_STATEMENT     { init();addId(&symbolstk,$1,"identifier",(int)$3,pointer);}
  | list_ '=' expr ';'     {init();type_err($3,1);  }
  | list_ '=' expr END_STATEMENT     { init();type_err($3,1); }
  | WHILE{while_entered=1;} '(' expr ')' ':' codeblock {  while_entered=0;init();addId(&symbolstk,"while","KEYWORD",-1,pointer);}
  | IF '(' expr ')' ':' codeblock { init();addId(&symbolstk,"if","KEYWORD",-1,pointer); } 
  | IF '(' expr ')' ':' codeblock elseif ELSE ':' codeblock 
                          { init();addId(&symbolstk,"if","KEYWORD",-1,pointer);addId(&symbolstk,"else","KEYWORD",-1,pointer); } 
  | '{' statements '}'       { init(); } 
  | RETURN{return_check();} expr ';'	    {  init();addId(&symbolstk,"return","KEYWORD",(int)$2,pointer);} 
  | RETURN{return_check();} expr END_STATEMENT	    { init();addId(&symbolstk,"return","KEYWORD",(int)$2,pointer);} 
  | IDENTIFIER '=' INPUT '(' expr ')' END_STATEMENT    {init();
							addId(&symbolstk,$1,"identifier",(int)$5,pointer);
							addId(&symbolstk,"input","KEYWORD",-1,pointer);}
  | IDENTIFIER '=' INPUT '(' expr ')' ';'    {  init();addId(&symbolstk,$1,"identifier",(int)$5,pointer);
							addId(&symbolstk,"input","KEYWORD",-1,pointer);} 
  | CONTINUE END_STATEMENT              { jump_check("continue");init();addId(&symbolstk,"continue","KEYWORD",-1,pointer); } 
  | CONTINUE ';'              { jump_check("continue");init();addId(&symbolstk,"continue","KEYWORD",-1,pointer); }
  | BREAK ';'                   {jump_check("break");init(); addId(&symbolstk,"break","KEYWORD",-1,pointer); } 
  | BREAK END_STATEMENT                   { jump_check("break");init();addId(&symbolstk,"break","KEYWORD",-1,pointer); } 
  | IDENTIFIER '=' list ';'                   {init();addId(&symbolstk,$1,"identifier",(int)$3,pointer); } 
  | IDENTIFIER '=' list END_STATEMENT                   {init();addId(&symbolstk,$1,"identifier",(int)$3,pointer);} 
  | fdef                   { init(); } 
  | fcall ';'                  { init();}
  | fcall END_STATEMENT                  { init();  }
  | IDENTIFIER '=' fcall ';'                  {  init();addId(&symbolstk,$1,"identifier",1,pointer); }
  | IDENTIFIER '=' fcall END_STATEMENT           { init();addId(&symbolstk,$1,"identifier",1,pointer); }
  ;

list:
  '[' list_item']'   {init();$$=$2;} 
  | '['' '']'                
  | '[' ']'                
  ;
list_item:
   list_item ',' DECIMALINTEGER  {init();sprintf(buff,"%d",$1);addId(&symbolstk,buff,"decimalint",1,pointer);$$=1;}
  | DECIMALINTEGER {init();sprintf(buff,"%d",$1);addId(&symbolstk,buff,"decimalint",1,pointer);$$=1;}
  ;
elseif:
  ELIF '(' expr ')' ':' codeblock elseif  {init();addId(&symbolstk,"elif","KEYWORD",-1,pointer); }
  |                              
  ;
statements:
  statements stmt   
  | stmt                  
  ;
codeblock:
  INDENT statements DEDENT          
  ;

expr: 
    DECIMALINTEGER     { init();sprintf(buff,"%d",$1);addId(&symbolstk,buff,"decimalint",1,pointer);$$=1;}          
  | IDENTIFIER          { init();$$=context_check($1);}   
  | STRING               {init();addId(&symbolstk,$1,"string",2,pointer);$$=2;}  
  | list_                 {init();$$=1;}   
  | '-' expr %prec UMINUS { init();addId(&symbolstk,"-","operators",-1,pointer);type_err($2,1);$$=$2;}
  | expr '+' expr       { init();type_err($1,$3);addId(&symbolstk,"+","operators",-1,pointer);$$=$1;}
  | expr '-' expr          { init();type_err($1,$3);if($1==2)type_err($1,2);addId(&symbolstk,"-","operators",-1,pointer);$$=$1;}
  | expr '*' expr        {init(); addId(&symbolstk,"*","operators",-1,pointer);
				if($1==2 || $3==2) 
				$$=2;
				$$=1;
			}
  | expr '/' expr          { init();type_err($1,$3);if($1==2)type_err($1,2);if($3==2)type_err($3,2);
					addId(&symbolstk,"/","operators",-1,pointer);$$=$1;}
  | expr '<' expr          { init();addId(&symbolstk,"<","operators",-1,pointer);$$=1;}
  | expr '>' expr         { init();addId(&symbolstk,">","operators",-1,pointer);$$=1;}
  | expr GE expr          { init();addId(&symbolstk,">=","operators",-1,pointer);$$=1;} 
  | expr LE expr         { init();addId(&symbolstk,"<=","operators",-1,pointer);$$=1;}
  | expr NE expr         {init(); addId(&symbolstk,"!=","operators",-1,pointer);$$=1;}
  | expr EQ expr        { init();addId(&symbolstk,"==","operators",-1,pointer);$$=1;}
  | '(' expr ')'        {init();$$=$2;}  
  | expr AND expr      { init();addId(&symbolstk,"and","operators",-1,pointer);
				if($1==2 || $3==2) 
				$$=2;
				$$=1;
				}  
  | expr OR expr       { init();addId(&symbolstk,"or","operators",-1,pointer);
				$$=1;}  
  ;  

list_:
 IDENTIFIER '[' DECIMALINTEGER ']' {init();sprintf(buff,"%d",$1);addId(&symbolstk,buff,"decimalint",1,pointer);$$=1;}
  | IDENTIFIER'[' IDENTIFIER ']' {init();int type=probe(&symbolstk,$3,pointer);type_err(1,type);$$=1;}
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
