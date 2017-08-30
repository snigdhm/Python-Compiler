%{ 
#include <stdio.h> 
#include <string.h>
#include <stdlib.h> 
#include <stdarg.h> 
#include<ctype.h>
//#include "calc3.h" 

#include "symboltfunc.c"
#include "icgen.h"

unsigned short parameter_count;
char quadBuffer[50];
char quadBuffer1[50];
char quadBuffer2[50];
int funcLineNumber = 0;
int offset=0;
/* prototypes */ 

int yylex(void); 
void yyerror(char *s); 
int sym[26];  
extern char *yytext;
extern int yylineno; 
extern int pointer; 
extern int counter;
int while_entered=0;
int list_counter=0;
int err1=0; 
int initialized=0;
int return_done=0;
 char buff[10];              /* symbol table */ 
STACK1 symbolstk;
extern FILE* icgf;
extern FILE* ofile;
char *list_name;
struct BackpatchList* whilenext;
int whilecont;

void return_inside(){
if(pointer==0)
 {
printf("'return' outside function");printSymbol_table(&symbolstk,ofile);exit(0);
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
		    err1=1;printSymbol_table(&symbolstk,ofile);
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
	s=probetype(&symbolstk,a,"Function",pointer);
       // printf("s:%d",s);
	if (s!=1)
	{
	        s= probetype(&symbolstk,a,"Function",0);
	        if(s!=1)
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
	s=probe_num(&symbolstk,a,"Function",0);
//printf("s:%d",s);
	if (s>no)
	{
		    printf( "\nERROR: Too less arguments at line : %d\n",yylineno);//exit(0);
		    err1=1;printSymbol_table(&symbolstk,ofile);
		    exit(0);
		
	}
	else if(s<no)
	{
		    printf( "\nERROR: Too many arguments at line : %d\n",yylineno);//exit(0);
		    err1=1;printSymbol_table(&symbolstk,ofile);
		    exit(0);
	}

}

void jump_check(char a[]){
if(while_entered==0)
 {
   printf("\nERROR: %s outside loop : %d\n",a,yylineno);printSymbol_table(&symbolstk,ofile);
   err1=1;exit(0);
 }
}
type_err(int t1,int t2)
{
	
	if(t1!=t2)
	{
		printf( "\nERROR: Semantic error at line : %d : Type mismatch!\n",yylineno);
		err1=1;printSymbol_table(&symbolstk,ofile);
		exit(0);
	}
	
}
init(){
if(initialized==0){initStack1(&symbolstk,10);
                       
   		enterScope(&symbolstk);
		initialized=1;}
}

void boundcheck(char* a,char* b){
int s;
s=probe_num(&symbolstk,a,"l_identifier",pointer);
if(s==-1)
	{
		s=probe_num(&symbolstk,a,"l_identifier",0);
	   if(s==-1)
		{printf( "\nERROR: Semantic error at line : %d : undeclared list!\n",yylineno);
		err1=1;printSymbol_table(&symbolstk,ofile);
		exit(0);}
	}
if(s<=atoi(b))
	{    
	     printf( "\nERROR: Semantic error at line : %d : index out of bound!\n",yylineno);
	     err1=1;printSymbol_table(&symbolstk,ofile);
	     exit(0);
	}
}


%} 

%union
{
    char         	*str;
    int           	type;
	struct
	{
	    char                 	*value;
	    int   			type;
	    struct BackpatchList* 	trueList;
	    struct BackpatchList* 	falseList;
	    struct BackpatchList* 	nextList;
	} expr;
	struct
	{
	  int				quad;
	  struct BackpatchList* 	nextList;
	} mark;
}


%token WHILE IF PRINT DEDENT INDENT END_STATEMENT ELSE ELIF INPUT BREAK CONTINUE RETURN DEF IDENTIFIER DECIMALINTEGER STRING
%left AND OR IN NOT_IN
%left GE LE EQ NE '>' '<'  
%left '+' '-' 
%left '*' '/' 
%nonassoc UMINUS NOT
%type <expr> IDENTIFIER DECIMALINTEGER STRING list list_ list1_ list_item arg stmt codeblock elseif fdef fcall function expr statements
%type <mark> marker jump_marker
%start program

%% 
program: 
  function   {printSymbol_table(&symbolstk,ofile);backpatch($1.nextList,1);
		 
		    printCode(ofile);
		}            
  ;   
function: 
    function stmt     {
				    backpatch($2.nextList, nextquad());
				  }     
  | /* NULL */ 
  ; 

fdef:
  DEF jump_marker IDENTIFIER '(' parameter ')' ':' {sprintf(quadBuffer,"%s ()",strdup($3.value));
		    				genquad(quadBuffer); } codeblock {if(return_done)
						return_done=0;
						else
						{
						sprintf(quadBuffer,"RETURN");
						genquad(quadBuffer);
						}} marker
		    				 {init();
				
					   addId(&symbolstk,strdup($3.value),"Function",1,1,0,3,pointer);
					   $$.nextList = $9.nextList;
					   backpatch($2.nextList,$11.quad);
					    }
  |  DEF jump_marker IDENTIFIER '(' parameter_ ')' ':'{sprintf(quadBuffer,"%s ()",strdup($3.value));
		    				genquad(quadBuffer);} codeblock {if(return_done)
						return_done=0;
						else
						{
						sprintf(quadBuffer,"RETURN");
						genquad(quadBuffer);
						}} marker {init();
				
					addId(&symbolstk,strdup($3.value),"Function",1,1,0,0,pointer);
					$$.nextList = $9.nextList;
					backpatch($2.nextList,$11.quad);
						}
  ; 
parameter:
  IDENTIFIER ',' IDENTIFIER ',' IDENTIFIER {init();enterScope(&symbolstk);
						addId(&symbolstk,$1.value,"identifier",1,-1,0,-1,pointer);
						addId(&symbolstk,$3.value,"identifier",1,-1,0,-1,pointer);
						addId(&symbolstk,$5.value,"identifier",1,-1,0,-1,pointer);}
  ;
parameter_:
    {init();enterScope(&symbolstk);}
  ;
fcall:
  IDENTIFIER '(' ')' {init();$$.type=context_check_func($1.value);check_no_of_param($1.value,0);$$.value=strdup($1.value);
			}
  | IDENTIFIER '(' arg ',' arg ',' arg ')' {init();$$.type=context_check_func($1.value);check_no_of_param($1.value,3);
						$$.value=strdup($1.value);
						$$.nextList = NULL;
						sprintf(quadBuffer,"param %s",strdup($3.value));
						genquad(quadBuffer);
						sprintf(quadBuffer,"param %s",strdup($5.value));
						genquad(quadBuffer);
						sprintf(quadBuffer,"param %s",strdup($7.value));
						genquad(quadBuffer);
						}
  ;
arg:
  IDENTIFIER     {init();$$.type=context_check($1.value);$$.value=$1.value;}  
  | DECIMALINTEGER {init();sprintf(buff,"%s",$1.value);
			$$.type=1;
			$$.value=$1.value;
                   }
  ;

stmt: 
    ';'                     { init(); } 
  | END_STATEMENT                 { init(); } 
  | expr ';'                   { init(); } 
  | expr END_STATEMENT                   { init(); } 
  | PRINT '(' expr ')'';'               { init();
					sprintf(quadBuffer,"print %s",strdup($3.value));
					genquad(quadBuffer);
					} 
  | PRINT '(' expr ')' END_STATEMENT    { init(); 
					sprintf(quadBuffer,"print %s",strdup($3.value));
					genquad(quadBuffer);
					}  
  | IDENTIFIER '=' expr ';'     { init();addId(&symbolstk,$1.value,"identifier",$3.type,-1,offset,-1,pointer);offset+=4;
				  fprintf(icgf,"%d\t%s := %s\n",funcLineNumber++,$1.value,$3.value); 
				    sprintf(quadBuffer,"%s := %s",$1.value,$3.value);
				    genquad(quadBuffer);
				    $$.type = $3.type;
				    $$.trueList = $3.trueList;
				    $$.value = $1.value;
				   }
  | IDENTIFIER '=' expr END_STATEMENT     { init();addId(&symbolstk,$1.value,"identifier",$3.type,-1,offset,-1,pointer);offset+=4;
				 	  fprintf(icgf,"%d\t%s := %s\n",funcLineNumber++,$1.value,$3.value); 
				    sprintf(quadBuffer,"%s := %s",$1.value,$3.value);
				    genquad(quadBuffer);
				    $$.type = $3.type;
				    $$.trueList = $3.trueList;
				    $$.value = $1.value;
				   }
  | list1_ '=' expr ';'     {init();type_err($3.type,1); sprintf(quadBuffer1," := %s",strdup($3.value));
                                   strcat(quadBuffer2,quadBuffer1);
				    genquad(quadBuffer2);*quadBuffer1=NULL;*quadBuffer2=NULL; }
  | list1_ '=' expr END_STATEMENT     { init();type_err($3.type,1);sprintf(quadBuffer1," := %s",strdup($3.value));
				    strcat(quadBuffer2,quadBuffer1);
					genquad(quadBuffer2);*quadBuffer1=NULL;*quadBuffer2=NULL; }
  | WHILE {while_entered=1;} marker{whilecont=$3.quad;} '(' expr ')' ':' marker codeblock jump_marker marker  											{  while_entered=0;init();
										backpatch($6.trueList,$9.quad);
										backpatch(whilenext,$12.quad);
										$$.nextList = $6.falseList;
										backpatch($10.nextList,$3.quad);
										backpatch($11.nextList,$3.quad);
										}
  |IF '(' expr ')' ':' marker codeblock marker{ init();
					backpatch($3.trueList,$6.quad);
				        backpatch($3.falseList,$8.quad);
					$$.nextList = mergelists($3.falseList,$7.nextList);
					}
  |IF '(' expr ')' ':' marker codeblock jump_marker  ELSE ':' marker codeblock {
				init();
				backpatch($3.trueList,$6.quad);
				backpatch($3.falseList,$11.quad);
				$$.nextList = mergelists($8.nextList,$11.nextList);
				$$.nextList = mergelists($$.nextList,$7.nextList);
				}
					
  | IF '(' expr ')' ':' marker codeblock jump_marker ELIF marker '(' expr ')' ':' marker codeblock jump_marker ELSE ':' marker codeblock 
                          { init();
				backpatch($3.trueList,$6.quad);
				backpatch($3.falseList,$10.quad);
				backpatch($12.trueList,$15.quad);
				backpatch($12.falseList,$20.quad);
				$$.nextList = mergelists($17.nextList,$21.nextList);
				$$.nextList = mergelists($$.nextList,$16.nextList);
				$$.nextList = mergelists($$.nextList,$8.nextList);
				$$.nextList = mergelists($$.nextList,$16.nextList);
				$$.nextList = mergelists($$.nextList,$7.nextList);
				} 
  | '{' statements '}'       { init(); $$.nextList = $2.nextList;} 
  | RETURN{return_inside();} expr ';'   {  init();return_done=1;
						$$.nextList=NULL;
						sprintf(quadBuffer,"RETURN %s",$3.value);
						genquad(quadBuffer);} 
  | RETURN{return_inside();} expr END_STATEMENT	    { init();return_done=1;
						$$.nextList=NULL;
						sprintf(quadBuffer,"RETURN %s",$3.value);
						genquad(quadBuffer);} 
  | jump_marker CONTINUE END_STATEMENT         { jump_check("continue");init(); } 
  | jump_marker CONTINUE ';'              { jump_check("continue");init();
					backpatch($1.nextList,whilecont);  }
  | jump_marker BREAK ';'        {jump_check("break");init();
					whilenext=$1.nextList;
					//backpatch($1.nextList,whilenext);
					//sprintf(quadBuffer,"BREAK");
					//genquad(quadBuffer);
				} 
  | jump_marker BREAK END_STATEMENT         {jump_check("break");init();
						//backpatch($1.nextList,whilenext);
						whilenext=$1.nextList;
						//sprintf(quadBuffer,"BREAK");
						//genquad(quadBuffer);
				}  
  | IDENTIFIER '=' {list_name=strdup($1.value);} list ';'    {init();addId(&symbolstk,$1.value,"l_identifier",1,-1,offset,list_counter,pointer);offset+=(list_counter*4);
						list_counter=0;} 
  | IDENTIFIER '=' {list_name=strdup($1.value);} list END_STATEMENT {init();
							addId(&symbolstk,$1.value,"l_identifier",1,-1,offset,list_counter,pointer);
							list_counter=0;offset+=(list_counter*4);} 
  | fdef                   { init(); } 
  | fcall ';'                  { init();
				sprintf(quadBuffer,"(null) := CALL %s, %d",strdup($1.value),$1.type);
				genquad(quadBuffer);
				}
  | fcall END_STATEMENT                  { init();
					sprintf(quadBuffer,"(null) := CALL %s, %d",strdup($1.value),$1.type);
					genquad(quadBuffer);
					}
  | IDENTIFIER '=' fcall ';'                  {  init();
						addId(&symbolstk,$1.value,"identifier",1,-1,offset,-1,pointer); offset+=4;
						char* var = NULL;
						var = nextIntVar();
						sprintf(quadBuffer,"%s := CALL %s, %d",var,strdup($3.value),$3.type);
						genquad(quadBuffer);
						sprintf(quadBuffer,"%s := %s",strdup($1.value),var);
						genquad(quadBuffer);
						}
  | IDENTIFIER '=' fcall END_STATEMENT           { init();
						addId(&symbolstk,$1.value,"identifier",1,-1,offset,-1,pointer); offset+=4;
						char* var = NULL;
						var = nextIntVar();
						sprintf(quadBuffer,"%s := CALL %s, %d",var,strdup($3.value),$3.type);
						genquad(quadBuffer);
						sprintf(quadBuffer,"%s := %s",strdup($1.value),var);
						genquad(quadBuffer);	
						}
  ;

list:
  '[' list_item']'   {init();$$.value=$2.value;$$.type=1;} 
  | '['' '']'                
  | '[' ']'                
  ;
list_item:
   list_item ',' DECIMALINTEGER  {init();list_counter++;
				sprintf(quadBuffer,"%s [ %d ] = %s",strdup(list_name),(list_counter-1)*4,strdup($3.value));
				genquad(quadBuffer);				 
				$$.type=1;}
  | DECIMALINTEGER {init();list_counter++;
				sprintf(quadBuffer,"%s [ %d ] = %s",strdup(list_name),(list_counter-1)*4,strdup($1.value));
				genquad(quadBuffer);				 
				$$.type=1;$$.value=strdup($1.value);

				}
  ;
/*
elseif:
  ELIF '(' expr ')' ':' marker codeblock jump_marker elseif  {init();addId(&symbolstk,"elif","KEYWORD",-1,pointer); 
								backpatch($3.trueList,$6.quad);
								backpatch($3.falseList,$9.quad);
								$$.nextList = mergelists($8.nextList,$9.nextList);
								$$.nextList = mergelists($$.nextList,$7.nextList);
								}
  |                              
  ;
*/
statements:
  statements stmt   
  | stmt                  
  ;
codeblock:
  INDENT statements DEDENT          
  ;

expr: 
    DECIMALINTEGER     { init();sprintf(buff,"%s",$1.value);
		
                         $$.type=1;$$.value=strdup($1.value);
                       }          
  | IDENTIFIER          { init();$$.type=context_check($1.value);
			  $$.value=$1.value;
			}   
  | STRING               {init();
                         $$.type=2;$$.value=$1.value;
                         }  
  | list_                 {init();$$.type=1;$$.value=$1.value;}   
  | '-' expr %prec UMINUS { init();type_err($2.type,1);
			    $$ = $2;
		            $$.value = nextIntVar();
			    sprintf(quadBuffer, "%s := -%s", $$.value, $2.value);
			    genquad(quadBuffer);
    			  }
  | expr '+' expr       { init();type_err($1.type,$3.type);
                          $$.type=$1.type;
			char* var = NULL;
			if($1.type==1)            
			 var = nextIntVar();
			else
			var = nextStringVar();

		    char buffer[50];
		    fprintf(icgf,"%d\t%s := %s + %s\n",funcLineNumber++,var,$1.value,$3.value);
		    sprintf(quadBuffer,"%s := %s + %s",var,$1.value,$3.value);
		    genquad(quadBuffer);
		    $$.value = var;
		    $$.type = $1.type;
		    $$.trueList = NULL;
		    $$.falseList = NULL;
                     }
  | expr '-' expr          { init();type_err($1.type,$3.type);if($1.type==2)type_err($1.type,2);
			    
                             $$.type=$1.type;
			char* var = NULL;
			if($1.type==1)            
			 var = nextIntVar();
			else
			var = nextStringVar();
		    char buffer[50];
		    fprintf(icgf,"%d\t%s := %s - %s\n",funcLineNumber++,var,$1.value,$3.value);
		    sprintf(quadBuffer,"%s := %s - %s",var,$1.value,$3.value);
		    genquad(quadBuffer);
		    $$.value = var;
		    $$.type = $1.type;
		    $$.trueList = NULL;
		    $$.falseList = NULL;
                  }
  | expr '*' expr        {init(); 
				if($1.type==2 || $3.type==2) 
				$$.type=2;
				$$.type=1;
			char* var = NULL;
			if($1.type==1)            
			 var = nextIntVar();
			else
			var = nextStringVar();

		    char buffer[50];
		    fprintf(icgf,"%d\t%s := %s * %s\n",funcLineNumber++,var,$1.value,$3.value);
		    sprintf(quadBuffer,"%s := %s * %s",var,$1.value,$3.value);
		    genquad(quadBuffer);
		    $$.value = var;
		    $$.type = $1.type;
		    $$.trueList = NULL;
		    $$.falseList = NULL;
			}
  | expr '/' expr          { init();type_err($1.type,$3.type);if($1.type==2)type_err($1.type,2);
				if($3.type==2)type_err($3.type,2);
			
				$$.type=$1.type;
                    char* var = NULL;
			if($1.type==1)            
			 var = nextIntVar();
			else
			var = nextStringVar();

		    char buffer[50];
		    fprintf(icgf,"%d\t%s := %s + %s\n",funcLineNumber++,var,$1.value,$3.value);
		    sprintf(quadBuffer,"%s := %s / %s",var,$1.value,$3.value);
		    genquad(quadBuffer);
		    $$.value = var;
		    $$.type = $1.type;
		    $$.trueList = NULL;
		    $$.falseList = NULL;
                   }
  | expr '<' expr          { init();
			     $$.type=1;
		           fprintf(icgf,"%s < %s",$1.value,$3.value);
			    sprintf(quadBuffer,"IF (%s < %s) GOTO",$1.value,$3.value);
			    $$.trueList = addToList(NULL, genquad(quadBuffer));
			    sprintf(quadBuffer,"GOTO");
			    $$.falseList = addToList(NULL, genquad(quadBuffer));
			    $$.value = "TrueFalse Only!";
			    $$.type = 1;
                           }
  | expr '>' expr         { init();$$.type=1;
		           fprintf(icgf,"%s > %s",$1.value,$3.value);
			    sprintf(quadBuffer,"IF (%s > %s) GOTO",$1.value,$3.value);
			    $$.trueList = addToList(NULL, genquad(quadBuffer));
			    sprintf(quadBuffer,"GOTO");
			    $$.falseList = addToList(NULL, genquad(quadBuffer));
			    $$.value = "TrueFalse Only!";
			    $$.type = 1;
			  }
  | expr GE expr          { init();$$.type=1;
		           fprintf(icgf,"%s >= %s",$1.value,$3.value);
			    sprintf(quadBuffer,"IF (%s >= %s) GOTO",$1.value,$3.value);
			    $$.trueList = addToList(NULL, genquad(quadBuffer));
			    sprintf(quadBuffer,"GOTO");
			    $$.falseList = addToList(NULL, genquad(quadBuffer));
			    $$.value = "TrueFalse Only!";
			    $$.type = 1;
			  } 
  | expr LE expr         { init();$$.type=1;
		           fprintf(icgf,"%s <= %s",$1.value,$3.value);
			    sprintf(quadBuffer,"IF (%s <= %s) GOTO",$1.value,$3.value);
			    $$.trueList = addToList(NULL, genquad(quadBuffer));
			    sprintf(quadBuffer,"GOTO");
			    $$.falseList = addToList(NULL, genquad(quadBuffer));
			    $$.value = "TrueFalse Only!";
			    $$.type = 1;
			  } 
  | expr NE expr         {init(); $$.type=1;
		           fprintf(icgf,"%s != %s",$1.value,$3.value);
			    sprintf(quadBuffer,"IF (%s != %s) GOTO",$1.value,$3.value);
			    $$.trueList = addToList(NULL, genquad(quadBuffer));
			    sprintf(quadBuffer,"GOTO");
			    $$.falseList = addToList(NULL, genquad(quadBuffer));
			    $$.value = "TrueFalse Only!";
			    $$.type = 1;
			  } 
  | expr EQ expr        { init();$$.type=1;
		           fprintf(icgf,"%s == %s",$1.value,$3.value);
			    sprintf(quadBuffer,"IF (%s == %s) GOTO",$1.value,$3.value);
			    $$.trueList = addToList(NULL, genquad(quadBuffer));
			    sprintf(quadBuffer,"GOTO");
			    $$.falseList = addToList(NULL, genquad(quadBuffer));
			    $$.value = "TrueFalse Only!";
			    $$.type = 1;
			  } 
  | '(' expr ')'        {init();$$=$2;
		           fprintf(icgf,"( %s )",$2.value);
			  }   
  ;  

list_:
 IDENTIFIER '[' DECIMALINTEGER ']' {init();sprintf(buff,"%s",$1.value);$$.type=1;
					boundcheck($1.value,$3.value);
					char* var = NULL;
					var = nextIntVar();
					sprintf(quadBuffer,"%s := %s * %d",var,strdup($3.value),4);
					genquad(quadBuffer);
					char* var1 = NULL;
					var1 = nextIntVar();
					sprintf(quadBuffer,"%s := %s [ %s ]",var1,strdup($1.value),var);
					genquad(quadBuffer);
					$$.value=var1;
					}
  | IDENTIFIER'[' IDENTIFIER ']' {init();int type=probe(&symbolstk,$3.value,pointer);type_err(1,type);$$.type=1;
					//boundcheck($3.value);
					char* var = NULL;
					var = nextIntVar();
					sprintf(quadBuffer,"%s := %s * %d",var,strdup($3.value),4);
					genquad(quadBuffer);
					char* var1 = NULL;
					var1 = nextIntVar();
					sprintf(quadBuffer,"%s := %s [ %d ]",var1,strdup($1.value),var);
					genquad(quadBuffer);
					$$.value=var1;
					}
  ;
list1_:
 IDENTIFIER '[' DECIMALINTEGER ']' {init();sprintf(buff,"%s",$1.value);$$.type=1;
					boundcheck($1.value,$3.value);
					char* var = NULL;
					var = nextIntVar();
					sprintf(quadBuffer,"%s := %s * %d",var,strdup($3.value),4);
					genquad(quadBuffer);
					sprintf(quadBuffer2,"%s [ %s ]",strdup($1.value),var);
					$$.value=$1.value;
					}
  | IDENTIFIER'[' IDENTIFIER ']' {init();int type=probe(&symbolstk,$3.value,pointer);type_err(1,type);$$.type=1;
					//boundcheck($3.value);
					char* var = NULL;
					var = nextIntVar();
					sprintf(quadBuffer,"%s := %s * %d",var,strdup($3.value),4);
					genquad(quadBuffer);
					sprintf(quadBuffer2,"%s [ %s ]",strdup($1.value),var);
					$$.value=$1.value;
					}
  ;

marker
	: {	
	     
	      $$.quad = nextquad();
	     
	};
jump_marker
	: {
	      
	      $$.quad = nextquad();
	      sprintf(quadBuffer,"GOTO");
	      $$.nextList = addToList(NULL, genquad(quadBuffer));
	      
   };

%% 
 

void yyerror(char *s) { 
    fprintf(stdout, "%s at line no %d\n", s,yylineno); 
} 
/*
int main(void) { 
    yyparse(); 
    return 0; 
} */
