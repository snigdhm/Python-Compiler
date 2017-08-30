/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser_icg.y" /* yacc.c:339  */
 
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



#line 226 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    WHILE = 258,
    IF = 259,
    PRINT = 260,
    DEDENT = 261,
    INDENT = 262,
    END_STATEMENT = 263,
    ELSE = 264,
    ELIF = 265,
    INPUT = 266,
    BREAK = 267,
    CONTINUE = 268,
    RETURN = 269,
    DEF = 270,
    IDENTIFIER = 271,
    DECIMALINTEGER = 272,
    STRING = 273,
    AND = 274,
    OR = 275,
    IN = 276,
    NOT_IN = 277,
    GE = 278,
    LE = 279,
    EQ = 280,
    NE = 281,
    UMINUS = 282,
    NOT = 283
  };
#endif
/* Tokens.  */
#define WHILE 258
#define IF 259
#define PRINT 260
#define DEDENT 261
#define INDENT 262
#define END_STATEMENT 263
#define ELSE 264
#define ELIF 265
#define INPUT 266
#define BREAK 267
#define CONTINUE 268
#define RETURN 269
#define DEF 270
#define IDENTIFIER 271
#define DECIMALINTEGER 272
#define STRING 273
#define AND 274
#define OR 275
#define IN 276
#define NOT_IN 277
#define GE 278
#define LE 279
#define EQ 280
#define NE 281
#define UMINUS 282
#define NOT 283

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 162 "parser_icg.y" /* yacc.c:355  */

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

#line 340 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 357 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   394

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  181

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    45,     2,     2,     2,     2,     2,     2,     2,
      35,    36,    31,    29,    38,    30,     2,    32,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    37,    39,
      28,    40,    27,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    43,     2,    44,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,    42,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    33,    34
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   193,   193,   199,   202,   206,   207,   206,   220,   221,
     220,   235,   241,   244,   246,   258,   259,   266,   267,   268,
     269,   270,   274,   278,   286,   294,   297,   300,   300,   300,
     307,   312,   320,   332,   333,   333,   337,   337,   341,   342,
     344,   350,   356,   356,   358,   358,   361,   362,   366,   370,
     379,   391,   392,   393,   396,   400,   419,   420,   423,   427,
     431,   434,   437,   438,   444,   461,   478,   497,   516,   526,
     535,   544,   553,   562,   571,   577,   589,   603,   612,   624,
     630
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WHILE", "IF", "PRINT", "DEDENT",
  "INDENT", "END_STATEMENT", "ELSE", "ELIF", "INPUT", "BREAK", "CONTINUE",
  "RETURN", "DEF", "IDENTIFIER", "DECIMALINTEGER", "STRING", "AND", "OR",
  "IN", "NOT_IN", "GE", "LE", "EQ", "NE", "'>'", "'<'", "'+'", "'-'",
  "'*'", "'/'", "UMINUS", "NOT", "'('", "')'", "':'", "','", "';'", "'='",
  "'{'", "'}'", "'['", "']'", "' '", "$accept", "program", "function",
  "fdef", "$@1", "$@2", "$@3", "$@4", "parameter", "parameter_", "fcall",
  "arg", "stmt", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "list",
  "list_item", "statements", "codeblock", "expr", "list_", "list1_",
  "marker", "jump_marker", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,    62,    60,    43,
      45,    42,    47,   282,   283,    40,    41,    58,    44,    59,
      61,   123,   125,    91,    93,    32
};
# endif

#define YYPACT_NINF -103

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-103)))

#define YYTABLE_NINF -81

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -103,     5,    71,  -103,  -103,   -32,   -28,  -103,  -103,  -103,
      21,  -103,  -103,   103,   103,  -103,   181,  -103,     3,  -103,
     200,  -103,   -30,    68,  -103,   103,   103,   103,   103,    -4,
      -8,   110,    75,    16,  -103,   302,  -103,   100,  -103,  -103,
    -103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,  -103,   103,    12,    13,  -103,   316,   330,   285,   275,
       9,  -103,  -103,  -103,    17,    23,    14,    19,    19,   225,
      26,    29,    77,  -103,  -103,  -103,    -5,    -5,    -5,    -5,
      -5,    -5,    64,    64,  -103,  -103,   250,  -103,  -103,  -103,
    -103,    22,    45,    15,  -103,  -103,    84,    81,  -103,  -103,
       1,    63,    99,  -103,  -103,    69,    73,    67,    87,  -103,
    -103,   103,  -103,  -103,  -103,    94,    98,   101,   105,  -103,
    -103,    92,    46,  -103,  -103,  -103,  -103,   344,   137,   130,
     111,   112,    81,  -103,   134,  -103,   116,   181,   113,   114,
    -103,  -103,   119,  -103,  -103,   153,  -103,   115,   144,   137,
     137,  -103,   137,  -103,   125,  -103,  -103,  -103,  -103,  -103,
    -103,   128,  -103,  -103,  -103,   137,   103,  -103,  -103,  -103,
    -103,   358,   127,  -103,   137,  -103,   156,   135,  -103,   137,
    -103
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,    80,     1,    27,     0,     0,    18,    34,    80,
      60,    59,    61,     0,     0,    17,    80,    46,     0,     3,
       0,    62,     0,     0,    79,     0,     0,     0,     0,     0,
       0,    42,     0,    60,    63,     0,    57,    80,    48,    47,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    19,     0,     0,     0,    28,     0,     0,     0,     0,
       0,    15,    16,    13,     0,    60,     0,     0,     0,     0,
       0,     0,     0,    74,    33,    56,    70,    71,    73,    72,
      69,    68,    64,    65,    66,    67,     0,    41,    40,    38,
      39,     0,     0,     0,    35,    37,    12,     0,    50,    49,
       0,     0,     0,    24,    23,    76,    75,     0,     0,    26,
      25,     0,    79,    22,    21,     0,     0,     0,     0,    55,
      53,     0,     0,    43,    45,    76,    75,     0,     0,     0,
       0,     0,     0,    52,     0,    51,     0,    80,    79,     0,
       5,     8,     0,    54,    79,    80,    30,     0,     0,     0,
       0,    14,     0,    58,     0,    79,    11,     6,     9,    80,
      79,     0,    79,    79,    79,     0,     0,     7,    10,    29,
      31,     0,     0,    79,     0,    80,     0,     0,    79,     0,
      32
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,
     142,   -91,     2,  -103,  -103,  -103,  -103,  -103,  -103,   106,
    -103,    38,  -102,   -12,  -103,  -103,   -95,    -9
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    17,   149,   162,   150,   163,   116,   117,
      18,    64,    36,    24,    91,    27,    28,    67,    68,   101,
     122,    37,   138,    20,    21,    22,    55,    23
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,    34,    35,    25,    19,     3,   118,    26,    61,    62,
      52,    38,    60,    56,    57,    58,    59,   128,   119,    69,
      87,    89,    98,   113,    47,    48,    49,    50,    63,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    75,
      86,   142,    39,   146,    96,   120,   121,   157,   158,   152,
     159,    88,    90,    99,   114,    97,    30,   111,    30,    72,
     161,    31,   100,   170,    32,   165,    72,   167,   168,   169,
     105,    -2,   175,   106,     4,     5,     6,   180,   174,     7,
      53,    54,   112,   179,   134,     8,     9,    10,    11,    12,
     135,    70,    71,   107,   108,    49,    50,    61,    62,   127,
     115,    13,   123,     4,     5,     6,    14,   124,     7,   -78,
      15,   125,    16,   -77,     8,     9,    10,    11,    12,    33,
      11,    12,   -80,   -80,   154,   155,    65,    11,    12,   147,
      13,   126,   129,    13,   130,    14,   133,   131,    14,    15,
      13,    16,    74,   132,   137,    14,   139,    75,   140,   141,
     164,   143,   148,   144,   171,   151,     4,     5,     6,   153,
     156,     7,   160,   166,   173,   177,   176,     8,     9,    10,
      11,    12,   178,    66,   102,   145,     0,     0,     0,     0,
       0,     0,     0,    13,     4,     5,     6,     0,    14,     7,
       0,     0,    15,     0,    16,     8,     9,    10,    11,    12,
       0,     0,     0,     0,     0,     0,     0,     0,    40,     0,
       0,    13,     0,     0,     0,     0,    14,     0,     0,     0,
      15,     0,    16,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,   103,     0,     0,     0,     0,     0,    51,
       0,     0,     0,     0,     0,     0,     0,     0,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,   109,     0,
       0,     0,     0,     0,   104,     0,     0,     0,     0,     0,
       0,     0,     0,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    95,     0,     0,     0,     0,     0,   110,
       0,     0,     0,     0,     0,     0,     0,     0,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,     0,     0,
       0,     0,     0,     0,    94,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,     0,     0,     0,    73,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,     0,
       0,     0,    92,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,     0,     0,     0,    93,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,     0,     0,     0,
     136,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,     0,     0,     0,   172
};

static const yytype_int16 yycheck[] =
{
       9,    13,    14,    35,     2,     0,    97,    35,    16,    17,
      40,     8,    16,    25,    26,    27,    28,   112,    17,    31,
       8,     8,     8,     8,    29,    30,    31,    32,    36,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    37,
      52,   132,    39,   138,    35,    44,    45,   149,   150,   144,
     152,    39,    39,    39,    39,    38,    35,    35,    35,    43,
     155,    40,    43,   165,    43,   160,    43,   162,   163,   164,
      44,     0,   174,    44,     3,     4,     5,   179,   173,     8,
      12,    13,    37,   178,    38,    14,    15,    16,    17,    18,
      44,    16,    17,    16,    17,    31,    32,    16,    17,   111,
      16,    30,    39,     3,     4,     5,    35,     8,     8,    40,
      39,    44,    41,    40,    14,    15,    16,    17,    18,    16,
      17,    18,     9,    10,     9,    10,    16,    17,    18,   138,
      30,    44,    38,    30,    36,    35,    44,    36,    35,    39,
      30,    41,    42,    38,     7,    35,    16,   145,    37,    37,
     159,    17,    38,    37,   166,    36,     3,     4,     5,     6,
      16,     8,    37,    35,    37,     9,   175,    14,    15,    16,
      17,    18,    37,    31,    68,   137,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,     3,     4,     5,    -1,    35,     8,
      -1,    -1,    39,    -1,    41,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,    -1,
      -1,    30,    -1,    -1,    -1,    -1,    35,    -1,    -1,    -1,
      39,    -1,    41,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,     8,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,     8,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,     8,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    -1,    -1,    36,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      -1,    -1,    36,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    -1,    -1,    36,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    -1,    -1,
      36,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    -1,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    47,    48,     0,     3,     4,     5,     8,    14,    15,
      16,    17,    18,    30,    35,    39,    41,    49,    56,    58,
      69,    70,    71,    73,    59,    35,    35,    61,    62,    73,
      35,    40,    43,    16,    69,    69,    58,    67,     8,    39,
       8,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    39,    40,    12,    13,    72,    69,    69,    69,    69,
      16,    16,    17,    36,    57,    16,    56,    63,    64,    69,
      16,    17,    43,    36,    42,    58,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,     8,    39,     8,
      39,    60,    36,    36,    39,     8,    35,    38,     8,    39,
      43,    65,    65,     8,    39,    44,    44,    16,    17,     8,
      39,    35,    37,     8,    39,    16,    54,    55,    57,    17,
      44,    45,    66,    39,     8,    44,    44,    69,    72,    38,
      36,    36,    38,    44,    38,    44,    36,     7,    68,    16,
      37,    37,    57,    17,    37,    67,    72,    73,    38,    50,
      52,    36,    72,     6,     9,    10,    16,    68,    68,    68,
      37,    72,    51,    53,    73,    72,    35,    72,    72,    72,
      68,    69,    36,    37,    72,    68,    73,     9,    37,    72,
      68
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    48,    48,    50,    51,    49,    52,    53,
      49,    54,    55,    56,    56,    57,    57,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    59,    60,    58,
      58,    58,    58,    58,    61,    58,    62,    58,    58,    58,
      58,    58,    63,    58,    64,    58,    58,    58,    58,    58,
      58,    65,    65,    65,    66,    66,    67,    67,    68,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    70,    70,    71,    71,    72,
      73
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     0,     0,    11,     0,     0,
      11,     5,     0,     3,     8,     1,     1,     1,     1,     2,
       2,     5,     5,     4,     4,     4,     4,     0,     0,    12,
       8,    12,    21,     3,     0,     4,     0,     4,     3,     3,
       3,     3,     0,     5,     0,     5,     1,     2,     2,     4,
       4,     3,     3,     2,     3,     1,     2,     1,     3,     1,
       1,     1,     1,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     4,     4,     4,     0,
       0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 193 "parser_icg.y" /* yacc.c:1646  */
    {printSymbol_table(&symbolstk,ofile);backpatch((yyvsp[0].expr).nextList,1);
		 
		    printCode(ofile);
		}
#line 1600 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 199 "parser_icg.y" /* yacc.c:1646  */
    {
				    backpatch((yyvsp[0].expr).nextList, nextquad());
				  }
#line 1608 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 206 "parser_icg.y" /* yacc.c:1646  */
    {sprintf(quadBuffer,"%s ()",strdup((yyvsp[-4].expr).value));
		    				genquad(quadBuffer); }
#line 1615 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 207 "parser_icg.y" /* yacc.c:1646  */
    {if(return_done)
						return_done=0;
						else
						{
						sprintf(quadBuffer,"RETURN");
						genquad(quadBuffer);
						}}
#line 1627 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 214 "parser_icg.y" /* yacc.c:1646  */
    {init();
				
					   addId(&symbolstk,strdup((yyvsp[-8].expr).value),"Function",1,1,0,3,pointer);
					   (yyval.expr).nextList = (yyvsp[-2].expr).nextList;
					   backpatch((yyvsp[-9].mark).nextList,(yyvsp[0].mark).quad);
					    }
#line 1638 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 220 "parser_icg.y" /* yacc.c:1646  */
    {sprintf(quadBuffer,"%s ()",strdup((yyvsp[-4].expr).value));
		    				genquad(quadBuffer);}
#line 1645 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 221 "parser_icg.y" /* yacc.c:1646  */
    {if(return_done)
						return_done=0;
						else
						{
						sprintf(quadBuffer,"RETURN");
						genquad(quadBuffer);
						}}
#line 1657 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 227 "parser_icg.y" /* yacc.c:1646  */
    {init();
				
					addId(&symbolstk,strdup((yyvsp[-8].expr).value),"Function",1,1,0,0,pointer);
					(yyval.expr).nextList = (yyvsp[-2].expr).nextList;
					backpatch((yyvsp[-9].mark).nextList,(yyvsp[0].mark).quad);
						}
#line 1668 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 235 "parser_icg.y" /* yacc.c:1646  */
    {init();enterScope(&symbolstk);
						addId(&symbolstk,(yyvsp[-4].expr).value,"identifier",1,-1,0,-1,pointer);
						addId(&symbolstk,(yyvsp[-2].expr).value,"identifier",1,-1,0,-1,pointer);
						addId(&symbolstk,(yyvsp[0].expr).value,"identifier",1,-1,0,-1,pointer);}
#line 1677 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 241 "parser_icg.y" /* yacc.c:1646  */
    {init();enterScope(&symbolstk);}
#line 1683 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 244 "parser_icg.y" /* yacc.c:1646  */
    {init();(yyval.expr).type=context_check_func((yyvsp[-2].expr).value);check_no_of_param((yyvsp[-2].expr).value,0);(yyval.expr).value=strdup((yyvsp[-2].expr).value);
			}
#line 1690 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 246 "parser_icg.y" /* yacc.c:1646  */
    {init();(yyval.expr).type=context_check_func((yyvsp[-7].expr).value);check_no_of_param((yyvsp[-7].expr).value,3);
						(yyval.expr).value=strdup((yyvsp[-7].expr).value);
						(yyval.expr).nextList = NULL;
						sprintf(quadBuffer,"param %s",strdup((yyvsp[-5].expr).value));
						genquad(quadBuffer);
						sprintf(quadBuffer,"param %s",strdup((yyvsp[-3].expr).value));
						genquad(quadBuffer);
						sprintf(quadBuffer,"param %s",strdup((yyvsp[-1].expr).value));
						genquad(quadBuffer);
						}
#line 1705 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 258 "parser_icg.y" /* yacc.c:1646  */
    {init();(yyval.expr).type=context_check((yyvsp[0].expr).value);(yyval.expr).value=(yyvsp[0].expr).value;}
#line 1711 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 259 "parser_icg.y" /* yacc.c:1646  */
    {init();sprintf(buff,"%s",(yyvsp[0].expr).value);
			(yyval.expr).type=1;
			(yyval.expr).value=(yyvsp[0].expr).value;
                   }
#line 1720 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 266 "parser_icg.y" /* yacc.c:1646  */
    { init(); }
#line 1726 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 267 "parser_icg.y" /* yacc.c:1646  */
    { init(); }
#line 1732 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 268 "parser_icg.y" /* yacc.c:1646  */
    { init(); }
#line 1738 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 269 "parser_icg.y" /* yacc.c:1646  */
    { init(); }
#line 1744 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 270 "parser_icg.y" /* yacc.c:1646  */
    { init();
					sprintf(quadBuffer,"print %s",strdup((yyvsp[-2].expr).value));
					genquad(quadBuffer);
					}
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 274 "parser_icg.y" /* yacc.c:1646  */
    { init(); 
					sprintf(quadBuffer,"print %s",strdup((yyvsp[-2].expr).value));
					genquad(quadBuffer);
					}
#line 1762 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 278 "parser_icg.y" /* yacc.c:1646  */
    { init();addId(&symbolstk,(yyvsp[-3].expr).value,"identifier",(yyvsp[-1].expr).type,-1,offset,-1,pointer);offset+=4;
				  fprintf(icgf,"%d\t%s := %s\n",funcLineNumber++,(yyvsp[-3].expr).value,(yyvsp[-1].expr).value); 
				    sprintf(quadBuffer,"%s := %s",(yyvsp[-3].expr).value,(yyvsp[-1].expr).value);
				    genquad(quadBuffer);
				    (yyval.expr).type = (yyvsp[-1].expr).type;
				    (yyval.expr).trueList = (yyvsp[-1].expr).trueList;
				    (yyval.expr).value = (yyvsp[-3].expr).value;
				   }
#line 1775 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 286 "parser_icg.y" /* yacc.c:1646  */
    { init();addId(&symbolstk,(yyvsp[-3].expr).value,"identifier",(yyvsp[-1].expr).type,-1,offset,-1,pointer);offset+=4;
				 	  fprintf(icgf,"%d\t%s := %s\n",funcLineNumber++,(yyvsp[-3].expr).value,(yyvsp[-1].expr).value); 
				    sprintf(quadBuffer,"%s := %s",(yyvsp[-3].expr).value,(yyvsp[-1].expr).value);
				    genquad(quadBuffer);
				    (yyval.expr).type = (yyvsp[-1].expr).type;
				    (yyval.expr).trueList = (yyvsp[-1].expr).trueList;
				    (yyval.expr).value = (yyvsp[-3].expr).value;
				   }
#line 1788 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 294 "parser_icg.y" /* yacc.c:1646  */
    {init();type_err((yyvsp[-1].expr).type,1); sprintf(quadBuffer1," := %s",strdup((yyvsp[-1].expr).value));
                                   strcat(quadBuffer2,quadBuffer1);
				    genquad(quadBuffer2);*quadBuffer1=NULL;*quadBuffer2=NULL; }
#line 1796 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 297 "parser_icg.y" /* yacc.c:1646  */
    { init();type_err((yyvsp[-1].expr).type,1);sprintf(quadBuffer1," := %s",strdup((yyvsp[-1].expr).value));
				    strcat(quadBuffer2,quadBuffer1);
					genquad(quadBuffer2);*quadBuffer1=NULL;*quadBuffer2=NULL; }
#line 1804 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 300 "parser_icg.y" /* yacc.c:1646  */
    {while_entered=1;}
#line 1810 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 300 "parser_icg.y" /* yacc.c:1646  */
    {whilecont=(yyvsp[0].mark).quad;}
#line 1816 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 300 "parser_icg.y" /* yacc.c:1646  */
    {  while_entered=0;init();
										backpatch((yyvsp[-6].expr).trueList,(yyvsp[-3].mark).quad);
										backpatch(whilenext,(yyvsp[0].mark).quad);
										(yyval.expr).nextList = (yyvsp[-6].expr).falseList;
										backpatch((yyvsp[-2].expr).nextList,(yyvsp[-9].mark).quad);
										backpatch((yyvsp[-1].mark).nextList,(yyvsp[-9].mark).quad);
										}
#line 1828 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 307 "parser_icg.y" /* yacc.c:1646  */
    { init();
					backpatch((yyvsp[-5].expr).trueList,(yyvsp[-2].mark).quad);
				        backpatch((yyvsp[-5].expr).falseList,(yyvsp[0].mark).quad);
					(yyval.expr).nextList = mergelists((yyvsp[-5].expr).falseList,(yyvsp[-1].expr).nextList);
					}
#line 1838 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 312 "parser_icg.y" /* yacc.c:1646  */
    {
				init();
				backpatch((yyvsp[-9].expr).trueList,(yyvsp[-6].mark).quad);
				backpatch((yyvsp[-9].expr).falseList,(yyvsp[-1].mark).quad);
				(yyval.expr).nextList = mergelists((yyvsp[-4].mark).nextList,(yyvsp[-1].mark).nextList);
				(yyval.expr).nextList = mergelists((yyval.expr).nextList,(yyvsp[-5].expr).nextList);
				}
#line 1850 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 321 "parser_icg.y" /* yacc.c:1646  */
    { init();
				backpatch((yyvsp[-18].expr).trueList,(yyvsp[-15].mark).quad);
				backpatch((yyvsp[-18].expr).falseList,(yyvsp[-11].mark).quad);
				backpatch((yyvsp[-9].expr).trueList,(yyvsp[-6].mark).quad);
				backpatch((yyvsp[-9].expr).falseList,(yyvsp[-1].mark).quad);
				(yyval.expr).nextList = mergelists((yyvsp[-4].mark).nextList,(yyvsp[0].expr).nextList);
				(yyval.expr).nextList = mergelists((yyval.expr).nextList,(yyvsp[-5].expr).nextList);
				(yyval.expr).nextList = mergelists((yyval.expr).nextList,(yyvsp[-13].mark).nextList);
				(yyval.expr).nextList = mergelists((yyval.expr).nextList,(yyvsp[-5].expr).nextList);
				(yyval.expr).nextList = mergelists((yyval.expr).nextList,(yyvsp[-14].expr).nextList);
				}
#line 1866 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 332 "parser_icg.y" /* yacc.c:1646  */
    { init(); (yyval.expr).nextList = (yyvsp[-1].expr).nextList;}
#line 1872 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 333 "parser_icg.y" /* yacc.c:1646  */
    {return_inside();}
#line 1878 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 333 "parser_icg.y" /* yacc.c:1646  */
    {  init();return_done=1;
						(yyval.expr).nextList=NULL;
						sprintf(quadBuffer,"RETURN %s",(yyvsp[-1].expr).value);
						genquad(quadBuffer);}
#line 1887 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 337 "parser_icg.y" /* yacc.c:1646  */
    {return_inside();}
#line 1893 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 337 "parser_icg.y" /* yacc.c:1646  */
    { init();return_done=1;
						(yyval.expr).nextList=NULL;
						sprintf(quadBuffer,"RETURN %s",(yyvsp[-1].expr).value);
						genquad(quadBuffer);}
#line 1902 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 341 "parser_icg.y" /* yacc.c:1646  */
    { jump_check("continue");init(); }
#line 1908 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 342 "parser_icg.y" /* yacc.c:1646  */
    { jump_check("continue");init();
					backpatch((yyvsp[-2].mark).nextList,whilecont);  }
#line 1915 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 344 "parser_icg.y" /* yacc.c:1646  */
    {jump_check("break");init();
					whilenext=(yyvsp[-2].mark).nextList;
					//backpatch($1.nextList,whilenext);
					//sprintf(quadBuffer,"BREAK");
					//genquad(quadBuffer);
				}
#line 1926 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 350 "parser_icg.y" /* yacc.c:1646  */
    {jump_check("break");init();
						//backpatch($1.nextList,whilenext);
						whilenext=(yyvsp[-2].mark).nextList;
						//sprintf(quadBuffer,"BREAK");
						//genquad(quadBuffer);
				}
#line 1937 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 356 "parser_icg.y" /* yacc.c:1646  */
    {list_name=strdup((yyvsp[-1].expr).value);}
#line 1943 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 356 "parser_icg.y" /* yacc.c:1646  */
    {init();addId(&symbolstk,(yyvsp[-4].expr).value,"l_identifier",1,-1,offset,list_counter,pointer);offset+=(list_counter*4);
						list_counter=0;}
#line 1950 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 358 "parser_icg.y" /* yacc.c:1646  */
    {list_name=strdup((yyvsp[-1].expr).value);}
#line 1956 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 358 "parser_icg.y" /* yacc.c:1646  */
    {init();
							addId(&symbolstk,(yyvsp[-4].expr).value,"l_identifier",1,-1,offset,list_counter,pointer);
							list_counter=0;offset+=(list_counter*4);}
#line 1964 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 361 "parser_icg.y" /* yacc.c:1646  */
    { init(); }
#line 1970 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 362 "parser_icg.y" /* yacc.c:1646  */
    { init();
				sprintf(quadBuffer,"(null) := CALL %s, %d",strdup((yyvsp[-1].expr).value),(yyvsp[-1].expr).type);
				genquad(quadBuffer);
				}
#line 1979 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 366 "parser_icg.y" /* yacc.c:1646  */
    { init();
					sprintf(quadBuffer,"(null) := CALL %s, %d",strdup((yyvsp[-1].expr).value),(yyvsp[-1].expr).type);
					genquad(quadBuffer);
					}
#line 1988 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 370 "parser_icg.y" /* yacc.c:1646  */
    {  init();
						addId(&symbolstk,(yyvsp[-3].expr).value,"identifier",1,-1,offset,-1,pointer); offset+=4;
						char* var = NULL;
						var = nextIntVar();
						sprintf(quadBuffer,"%s := CALL %s, %d",var,strdup((yyvsp[-1].expr).value),(yyvsp[-1].expr).type);
						genquad(quadBuffer);
						sprintf(quadBuffer,"%s := %s",strdup((yyvsp[-3].expr).value),var);
						genquad(quadBuffer);
						}
#line 2002 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 379 "parser_icg.y" /* yacc.c:1646  */
    { init();
						addId(&symbolstk,(yyvsp[-3].expr).value,"identifier",1,-1,offset,-1,pointer); offset+=4;
						char* var = NULL;
						var = nextIntVar();
						sprintf(quadBuffer,"%s := CALL %s, %d",var,strdup((yyvsp[-1].expr).value),(yyvsp[-1].expr).type);
						genquad(quadBuffer);
						sprintf(quadBuffer,"%s := %s",strdup((yyvsp[-3].expr).value),var);
						genquad(quadBuffer);	
						}
#line 2016 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 391 "parser_icg.y" /* yacc.c:1646  */
    {init();(yyval.expr).value=(yyvsp[-1].expr).value;(yyval.expr).type=1;}
#line 2022 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 396 "parser_icg.y" /* yacc.c:1646  */
    {init();list_counter++;
				sprintf(quadBuffer,"%s [ %d ] = %s",strdup(list_name),(list_counter-1)*4,strdup((yyvsp[0].expr).value));
				genquad(quadBuffer);				 
				(yyval.expr).type=1;}
#line 2031 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 400 "parser_icg.y" /* yacc.c:1646  */
    {init();list_counter++;
				sprintf(quadBuffer,"%s [ %d ] = %s",strdup(list_name),(list_counter-1)*4,strdup((yyvsp[0].expr).value));
				genquad(quadBuffer);				 
				(yyval.expr).type=1;(yyval.expr).value=strdup((yyvsp[0].expr).value);

				}
#line 2042 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 427 "parser_icg.y" /* yacc.c:1646  */
    { init();sprintf(buff,"%s",(yyvsp[0].expr).value);
		
                         (yyval.expr).type=1;(yyval.expr).value=strdup((yyvsp[0].expr).value);
                       }
#line 2051 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 431 "parser_icg.y" /* yacc.c:1646  */
    { init();(yyval.expr).type=context_check((yyvsp[0].expr).value);
			  (yyval.expr).value=(yyvsp[0].expr).value;
			}
#line 2059 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 434 "parser_icg.y" /* yacc.c:1646  */
    {init();
                         (yyval.expr).type=2;(yyval.expr).value=(yyvsp[0].expr).value;
                         }
#line 2067 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 437 "parser_icg.y" /* yacc.c:1646  */
    {init();(yyval.expr).type=1;(yyval.expr).value=(yyvsp[0].expr).value;}
#line 2073 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 438 "parser_icg.y" /* yacc.c:1646  */
    { init();type_err((yyvsp[0].expr).type,1);
			    (yyval.expr) = (yyvsp[0].expr);
		            (yyval.expr).value = nextIntVar();
			    sprintf(quadBuffer, "%s := -%s", (yyval.expr).value, (yyvsp[0].expr).value);
			    genquad(quadBuffer);
    			  }
#line 2084 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 444 "parser_icg.y" /* yacc.c:1646  */
    { init();type_err((yyvsp[-2].expr).type,(yyvsp[0].expr).type);
                          (yyval.expr).type=(yyvsp[-2].expr).type;
			char* var = NULL;
			if((yyvsp[-2].expr).type==1)            
			 var = nextIntVar();
			else
			var = nextStringVar();

		    char buffer[50];
		    fprintf(icgf,"%d\t%s := %s + %s\n",funcLineNumber++,var,(yyvsp[-2].expr).value,(yyvsp[0].expr).value);
		    sprintf(quadBuffer,"%s := %s + %s",var,(yyvsp[-2].expr).value,(yyvsp[0].expr).value);
		    genquad(quadBuffer);
		    (yyval.expr).value = var;
		    (yyval.expr).type = (yyvsp[-2].expr).type;
		    (yyval.expr).trueList = NULL;
		    (yyval.expr).falseList = NULL;
                     }
#line 2106 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 461 "parser_icg.y" /* yacc.c:1646  */
    { init();type_err((yyvsp[-2].expr).type,(yyvsp[0].expr).type);if((yyvsp[-2].expr).type==2)type_err((yyvsp[-2].expr).type,2);
			    
                             (yyval.expr).type=(yyvsp[-2].expr).type;
			char* var = NULL;
			if((yyvsp[-2].expr).type==1)            
			 var = nextIntVar();
			else
			var = nextStringVar();
		    char buffer[50];
		    fprintf(icgf,"%d\t%s := %s - %s\n",funcLineNumber++,var,(yyvsp[-2].expr).value,(yyvsp[0].expr).value);
		    sprintf(quadBuffer,"%s := %s - %s",var,(yyvsp[-2].expr).value,(yyvsp[0].expr).value);
		    genquad(quadBuffer);
		    (yyval.expr).value = var;
		    (yyval.expr).type = (yyvsp[-2].expr).type;
		    (yyval.expr).trueList = NULL;
		    (yyval.expr).falseList = NULL;
                  }
#line 2128 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 478 "parser_icg.y" /* yacc.c:1646  */
    {init(); 
				if((yyvsp[-2].expr).type==2 || (yyvsp[0].expr).type==2) 
				(yyval.expr).type=2;
				(yyval.expr).type=1;
			char* var = NULL;
			if((yyvsp[-2].expr).type==1)            
			 var = nextIntVar();
			else
			var = nextStringVar();

		    char buffer[50];
		    fprintf(icgf,"%d\t%s := %s * %s\n",funcLineNumber++,var,(yyvsp[-2].expr).value,(yyvsp[0].expr).value);
		    sprintf(quadBuffer,"%s := %s * %s",var,(yyvsp[-2].expr).value,(yyvsp[0].expr).value);
		    genquad(quadBuffer);
		    (yyval.expr).value = var;
		    (yyval.expr).type = (yyvsp[-2].expr).type;
		    (yyval.expr).trueList = NULL;
		    (yyval.expr).falseList = NULL;
			}
#line 2152 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 497 "parser_icg.y" /* yacc.c:1646  */
    { init();type_err((yyvsp[-2].expr).type,(yyvsp[0].expr).type);if((yyvsp[-2].expr).type==2)type_err((yyvsp[-2].expr).type,2);
				if((yyvsp[0].expr).type==2)type_err((yyvsp[0].expr).type,2);
			
				(yyval.expr).type=(yyvsp[-2].expr).type;
                    char* var = NULL;
			if((yyvsp[-2].expr).type==1)            
			 var = nextIntVar();
			else
			var = nextStringVar();

		    char buffer[50];
		    fprintf(icgf,"%d\t%s := %s + %s\n",funcLineNumber++,var,(yyvsp[-2].expr).value,(yyvsp[0].expr).value);
		    sprintf(quadBuffer,"%s := %s / %s",var,(yyvsp[-2].expr).value,(yyvsp[0].expr).value);
		    genquad(quadBuffer);
		    (yyval.expr).value = var;
		    (yyval.expr).type = (yyvsp[-2].expr).type;
		    (yyval.expr).trueList = NULL;
		    (yyval.expr).falseList = NULL;
                   }
#line 2176 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 516 "parser_icg.y" /* yacc.c:1646  */
    { init();
			     (yyval.expr).type=1;
		           fprintf(icgf,"%s < %s",(yyvsp[-2].expr).value,(yyvsp[0].expr).value);
			    sprintf(quadBuffer,"IF (%s < %s) GOTO",(yyvsp[-2].expr).value,(yyvsp[0].expr).value);
			    (yyval.expr).trueList = addToList(NULL, genquad(quadBuffer));
			    sprintf(quadBuffer,"GOTO");
			    (yyval.expr).falseList = addToList(NULL, genquad(quadBuffer));
			    (yyval.expr).value = "TrueFalse Only!";
			    (yyval.expr).type = 1;
                           }
#line 2191 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 526 "parser_icg.y" /* yacc.c:1646  */
    { init();(yyval.expr).type=1;
		           fprintf(icgf,"%s > %s",(yyvsp[-2].expr).value,(yyvsp[0].expr).value);
			    sprintf(quadBuffer,"IF (%s > %s) GOTO",(yyvsp[-2].expr).value,(yyvsp[0].expr).value);
			    (yyval.expr).trueList = addToList(NULL, genquad(quadBuffer));
			    sprintf(quadBuffer,"GOTO");
			    (yyval.expr).falseList = addToList(NULL, genquad(quadBuffer));
			    (yyval.expr).value = "TrueFalse Only!";
			    (yyval.expr).type = 1;
			  }
#line 2205 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 535 "parser_icg.y" /* yacc.c:1646  */
    { init();(yyval.expr).type=1;
		           fprintf(icgf,"%s >= %s",(yyvsp[-2].expr).value,(yyvsp[0].expr).value);
			    sprintf(quadBuffer,"IF (%s >= %s) GOTO",(yyvsp[-2].expr).value,(yyvsp[0].expr).value);
			    (yyval.expr).trueList = addToList(NULL, genquad(quadBuffer));
			    sprintf(quadBuffer,"GOTO");
			    (yyval.expr).falseList = addToList(NULL, genquad(quadBuffer));
			    (yyval.expr).value = "TrueFalse Only!";
			    (yyval.expr).type = 1;
			  }
#line 2219 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 544 "parser_icg.y" /* yacc.c:1646  */
    { init();(yyval.expr).type=1;
		           fprintf(icgf,"%s <= %s",(yyvsp[-2].expr).value,(yyvsp[0].expr).value);
			    sprintf(quadBuffer,"IF (%s <= %s) GOTO",(yyvsp[-2].expr).value,(yyvsp[0].expr).value);
			    (yyval.expr).trueList = addToList(NULL, genquad(quadBuffer));
			    sprintf(quadBuffer,"GOTO");
			    (yyval.expr).falseList = addToList(NULL, genquad(quadBuffer));
			    (yyval.expr).value = "TrueFalse Only!";
			    (yyval.expr).type = 1;
			  }
#line 2233 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 553 "parser_icg.y" /* yacc.c:1646  */
    {init(); (yyval.expr).type=1;
		           fprintf(icgf,"%s != %s",(yyvsp[-2].expr).value,(yyvsp[0].expr).value);
			    sprintf(quadBuffer,"IF (%s != %s) GOTO",(yyvsp[-2].expr).value,(yyvsp[0].expr).value);
			    (yyval.expr).trueList = addToList(NULL, genquad(quadBuffer));
			    sprintf(quadBuffer,"GOTO");
			    (yyval.expr).falseList = addToList(NULL, genquad(quadBuffer));
			    (yyval.expr).value = "TrueFalse Only!";
			    (yyval.expr).type = 1;
			  }
#line 2247 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 562 "parser_icg.y" /* yacc.c:1646  */
    { init();(yyval.expr).type=1;
		           fprintf(icgf,"%s == %s",(yyvsp[-2].expr).value,(yyvsp[0].expr).value);
			    sprintf(quadBuffer,"IF (%s == %s) GOTO",(yyvsp[-2].expr).value,(yyvsp[0].expr).value);
			    (yyval.expr).trueList = addToList(NULL, genquad(quadBuffer));
			    sprintf(quadBuffer,"GOTO");
			    (yyval.expr).falseList = addToList(NULL, genquad(quadBuffer));
			    (yyval.expr).value = "TrueFalse Only!";
			    (yyval.expr).type = 1;
			  }
#line 2261 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 571 "parser_icg.y" /* yacc.c:1646  */
    {init();(yyval.expr)=(yyvsp[-1].expr);
		           fprintf(icgf,"( %s )",(yyvsp[-1].expr).value);
			  }
#line 2269 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 577 "parser_icg.y" /* yacc.c:1646  */
    {init();sprintf(buff,"%s",(yyvsp[-3].expr).value);(yyval.expr).type=1;
					boundcheck((yyvsp[-3].expr).value,(yyvsp[-1].expr).value);
					char* var = NULL;
					var = nextIntVar();
					sprintf(quadBuffer,"%s := %s * %d",var,strdup((yyvsp[-1].expr).value),4);
					genquad(quadBuffer);
					char* var1 = NULL;
					var1 = nextIntVar();
					sprintf(quadBuffer,"%s := %s [ %s ]",var1,strdup((yyvsp[-3].expr).value),var);
					genquad(quadBuffer);
					(yyval.expr).value=var1;
					}
#line 2286 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 589 "parser_icg.y" /* yacc.c:1646  */
    {init();int type=probe(&symbolstk,(yyvsp[-1].expr).value,pointer);type_err(1,type);(yyval.expr).type=1;
					//boundcheck($3.value);
					char* var = NULL;
					var = nextIntVar();
					sprintf(quadBuffer,"%s := %s * %d",var,strdup((yyvsp[-1].expr).value),4);
					genquad(quadBuffer);
					char* var1 = NULL;
					var1 = nextIntVar();
					sprintf(quadBuffer,"%s := %s [ %d ]",var1,strdup((yyvsp[-3].expr).value),var);
					genquad(quadBuffer);
					(yyval.expr).value=var1;
					}
#line 2303 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 603 "parser_icg.y" /* yacc.c:1646  */
    {init();sprintf(buff,"%s",(yyvsp[-3].expr).value);(yyval.expr).type=1;
					boundcheck((yyvsp[-3].expr).value,(yyvsp[-1].expr).value);
					char* var = NULL;
					var = nextIntVar();
					sprintf(quadBuffer,"%s := %s * %d",var,strdup((yyvsp[-1].expr).value),4);
					genquad(quadBuffer);
					sprintf(quadBuffer2,"%s [ %s ]",strdup((yyvsp[-3].expr).value),var);
					(yyval.expr).value=(yyvsp[-3].expr).value;
					}
#line 2317 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 612 "parser_icg.y" /* yacc.c:1646  */
    {init();int type=probe(&symbolstk,(yyvsp[-1].expr).value,pointer);type_err(1,type);(yyval.expr).type=1;
					//boundcheck($3.value);
					char* var = NULL;
					var = nextIntVar();
					sprintf(quadBuffer,"%s := %s * %d",var,strdup((yyvsp[-1].expr).value),4);
					genquad(quadBuffer);
					sprintf(quadBuffer2,"%s [ %s ]",strdup((yyvsp[-3].expr).value),var);
					(yyval.expr).value=(yyvsp[-3].expr).value;
					}
#line 2331 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 624 "parser_icg.y" /* yacc.c:1646  */
    {	
	     
	      (yyval.mark).quad = nextquad();
	     
	}
#line 2341 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 630 "parser_icg.y" /* yacc.c:1646  */
    {
	      
	      (yyval.mark).quad = nextquad();
	      sprintf(quadBuffer,"GOTO");
	      (yyval.mark).nextList = addToList(NULL, genquad(quadBuffer));
	      
   }
#line 2353 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2357 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 638 "parser_icg.y" /* yacc.c:1906  */
 
 

void yyerror(char *s) { 
    fprintf(stdout, "%s at line no %d\n", s,yylineno); 
} 
/*
int main(void) { 
    yyparse(); 
    return 0; 
} */
