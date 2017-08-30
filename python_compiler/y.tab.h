/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 162 "parser_icg.y" /* yacc.c:1909  */

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

#line 128 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
