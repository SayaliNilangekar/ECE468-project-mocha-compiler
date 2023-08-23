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

#ifndef YY_YY_GENERATED_PARSER_HPP_INCLUDED
# define YY_YY_GENERATED_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/parser.yy" /* yacc.c:1909  */

  #include <stdio.h>
  #include <iostream>
  #include <stack>
  #include <string>
  #include <vector>
  #include <map>
  #include <list>
  #include <typeinfo>
  #include "../src/SymbolTable.h"


#line 57 "generated/parser.hpp" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INTLITERAL = 258,
    FLOATLITERAL = 259,
    STRINGLITERAL = 260,
    IDENTIFIER = 261,
    PROGRAM = 262,
    SEMICOLON = 263,
    _BEGIN = 264,
    END = 265,
    FUNCTION = 266,
    READ = 267,
    WRITE = 268,
    IF = 269,
    ELSE = 270,
    ENDIF = 271,
    WHILE = 272,
    ENDWHILE = 273,
    RETURN = 274,
    INT = 275,
    VOID = 276,
    STRING = 277,
    FLOAT = 278,
    TRUE = 279,
    FALSE = 280,
    COLONEQUAL = 281,
    PLUS = 282,
    MINUS = 283,
    ASTERISK = 284,
    FWDSLASH = 285,
    EQUAL = 286,
    NOTEQUAL = 287,
    LESSTHAN = 288,
    GREATERTHAN = 289,
    OPENPARAN = 290,
    CLOSEPARAN = 291,
    COMMA = 292,
    LESSTHANEQUAL = 293,
    GREATERTHANEQUAL = 294
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 53 "src/parser.yy" /* yacc.c:1909  */

  int tok;
  std::string* sstr;
  std::list<std::string>* slist;
  ASTNode* ASTPtr;
  Arithmetic* ArithPtr;

#line 117 "generated/parser.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_GENERATED_PARSER_HPP_INCLUDED  */
