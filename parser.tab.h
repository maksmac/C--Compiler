/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 25 "parser.y"

    #include "SymbolTable/symbolTable.h"
    #include "AST/ast.h"
    #include "AssemblyGenerator/assemblyGen.h"

#line 54 "parser.tab.h"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT_P = 258,
    CHAR_P = 259,
    FLOAT_P = 260,
    ID_P = 261,
    CONSTANT_INT_P = 262,
    CONSTANT_CHAR_P = 263,
    CONSTANT_FLOAT_P = 264,
    NEWLINE_P = 265,
    IF_P = 266,
    ELSE_P = 267,
    WHILE_P = 268,
    RETURN_P = 269,
    READ_P = 270,
    WRITE_P = 271,
    WRITELN_P = 272,
    BREAK_P = 273,
    SEMICOLON_P = 274,
    LP_P = 275,
    RP_P = 276,
    LB_P = 277,
    RB_P = 278,
    LCB_P = 279,
    RCB_P = 280,
    COMMA_P = 281,
    ADD_P = 282,
    MINUS_P = 283,
    MULTIPLY_P = 284,
    DIVIDE_P = 285,
    AND_P = 286,
    OR_P = 287,
    NOT_P = 288,
    EQUAL_P = 289,
    EQUALTO_P = 290,
    NOTEQUALTO_P = 291,
    LESSTHANOREQUAL_P = 292,
    LESSTHAN_P = 293,
    GREATERTHAN_P = 294,
    GREATERTHANOREQUAL_P = 295
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 33 "parser.y"

    int value;
    float fvalue;
    char * string;
    ASTNode * node;
    enum operatorType op;

#line 114 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
