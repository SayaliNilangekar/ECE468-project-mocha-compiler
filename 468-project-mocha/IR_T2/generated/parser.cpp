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
#line 13 "src/parser.yy" /* yacc.c:339  */

  #include <stdio.h>
  #include <iostream>
  #include <stack>
  #include <string>
  #include <vector>
  #include <map>
  #include <list>
  #include "../src/SymbolTable.h"

  int blockCounter = 0;
  //int it = 0;

 //global functions

  std::string genScope(){
    return "BLOCK " + std::to_string((long long)++blockCounter);
  }


  void printInOrder(ASTNode* node){
		if(node == NULL)
			return;
		printInOrder(node->leftChild);
		std::cout<<"Node token is: "<<node->token<<"        Token type is: "<<node->tokType<<std::endl;
		printInOrder(node->rightChild);
	}

 

  void yyerror(const char* str){}
  extern int yylex();
  extern char* yytext;
  SymbolTable* root; 
  VectorTable* vectRoot;
  std::stack<SymbolTable *> symtabStack;
  std::stack<VectorTable *> vectTabStack;
  std::vector<ASTNode*> FuncVect;

#line 106 "generated/parser.cpp" /* yacc.c:339  */

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
   by #include "parser.hpp".  */
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
#line 1 "src/parser.yy" /* yacc.c:355  */

  #include <stdio.h>
  #include <iostream>
  #include <stack>
  #include <string>
  #include <vector>
  #include <map>
  #include <list>
  #include <typeinfo>
  #include "../src/SymbolTable.h"


#line 149 "generated/parser.cpp" /* yacc.c:355  */

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
#line 53 "src/parser.yy" /* yacc.c:355  */

  int tok;
  std::string* sstr;
  std::list<std::string>* slist;
  ASTNode* ASTPtr;
  Arithmetic* ArithPtr;

#line 209 "generated/parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_GENERATED_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 226 "generated/parser.cpp" /* yacc.c:358  */

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   125

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  144

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    74,    74,    73,    91,    93,    95,    95,    95,    98,
     107,   114,   125,   125,   127,   128,   130,   132,   133,   136,
     136,   138,   144,   144,   147,   147,   150,   149,   167,   170,
     170,   171,   171,   171,   172,   172,   172,   172,   175,   177,
     188,   187,   241,   241,   305,   308,   322,   340,   342,   356,
     373,   375,   375,   377,   378,   378,   379,   379,   381,   382,
     411,   417,   424,   425,   426,   427,   431,   438,   430,   449,
     449,   450,   450,   450,   451,   451,   451,   451,   451,   451,
     453,   452,   468,   469
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTLITERAL", "FLOATLITERAL",
  "STRINGLITERAL", "IDENTIFIER", "PROGRAM", "SEMICOLON", "_BEGIN", "END",
  "FUNCTION", "READ", "WRITE", "IF", "ELSE", "ENDIF", "WHILE", "ENDWHILE",
  "RETURN", "INT", "VOID", "STRING", "FLOAT", "TRUE", "FALSE",
  "COLONEQUAL", "PLUS", "MINUS", "ASTERISK", "FWDSLASH", "EQUAL",
  "NOTEQUAL", "LESSTHAN", "GREATERTHAN", "OPENPARAN", "CLOSEPARAN",
  "COMMA", "LESSTHANEQUAL", "GREATERTHANEQUAL", "$accept", "program",
  "$@1", "id", "pgm_body", "decl", "string_decl", "str", "var_decl",
  "var_type", "any_type", "id_list", "id_tail", "param_decl_list",
  "param_decl", "param_decl_tail", "func_declarations", "func_decl", "$@2",
  "func_body", "stmt_list", "stmt", "base_stmt", "assign_stmt",
  "assign_expr", "read_stmt", "$@3", "write_stmt", "$@4", "return_stmt",
  "expr", "expr_prefix", "factor", "factor_prefix", "postfix_expr",
  "call_expr", "expr_list", "expr_list_tail", "primary", "addop", "mulop",
  "if_stmt", "$@5", "$@6", "else_part", "cond", "compop", "while_stmt",
  "$@7", "control_stmt", "loop_stmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

#define YYPACT_NINF -58

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-58)))

#define YYTABLE_NINF -56

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       0,     3,    30,   -58,    23,   -58,   -58,    -8,   -58,     3,
     -58,    24,    25,    -8,    -8,     3,    14,   -58,    33,   -58,
      25,   -58,   -58,    15,    49,    53,   -58,   -58,     3,   -58,
       3,   -58,   -58,   -58,    51,    26,    15,   -58,   -58,   -58,
      18,     3,    27,    28,   -58,    55,    18,   -58,    -8,    28,
       7,    50,   -58,    32,    35,    36,    37,   -58,    52,   -58,
       7,   -58,   -58,    54,   -58,   -58,   -58,   -58,   -58,   -58,
     -58,   -58,     3,     3,    -2,    -2,    67,   -58,   -58,   -58,
     -58,   -58,   -58,   -58,   -58,    12,    40,    41,   -58,   -10,
       2,   -58,    44,    45,   -58,   -58,   -58,   -58,   -58,   -58,
     -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,    47,
      19,   -58,   -58,    75,    77,   -58,    -8,    -8,    56,    57,
     -58,   -58,   -58,   -58,   -58,     7,     7,   -58,    58,    60,
     -58,    68,   -58,   -58,   -58,    72,   -58,    58,    -8,    73,
     -58,     7,   -58,   -58
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     4,     0,     1,     2,     8,    13,     0,
      12,     0,    25,     8,     8,     0,     0,     3,     0,     5,
      25,     6,     7,    18,     0,     0,    15,    14,     0,    24,
       0,    16,    11,    10,     0,     0,    18,     9,    26,    17,
      20,     0,     0,    23,    21,     0,     0,    19,     8,    23,
      30,     0,    22,     0,     0,     0,     0,    47,     0,    28,
      30,    31,    34,     0,    35,    36,    82,    32,    83,    37,
      33,    27,     0,     0,    47,    47,     0,    50,    47,    29,
      38,    40,    42,    72,    73,     0,     0,     0,    44,    45,
       0,    39,     0,     0,    76,    77,    74,    75,    78,    79,
      47,    66,    80,    62,    63,    46,    60,    61,    47,    59,
      48,    52,    51,     0,     0,    71,     8,     8,     0,    47,
      64,    65,    49,    41,    43,    30,    30,    58,    57,     0,
      67,     0,    47,    54,    53,    70,    81,    57,     8,     0,
      56,    30,    68,    69
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -58,   -58,   -58,     1,   -58,   -13,   -58,   -58,   -58,    -7,
     -58,   -45,    61,   -58,    42,    59,    70,   -58,   -58,   -58,
     -57,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,
     -53,   -58,   -58,   -58,   -58,   -58,   -58,   -43,   -58,   -58,
     -58,   -58,   -58,   -58,   -58,    31,   -58,   -58,   -58,   -58,
     -58
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     7,    58,    11,    12,    13,    34,    14,    15,
      28,    24,    31,    42,    43,    47,    19,    20,    40,    51,
      59,    60,    61,    62,    63,    64,    92,    65,    93,    66,
      85,    77,    89,    90,   110,   111,   129,   133,   112,   105,
     122,    67,   116,   135,   139,    86,   100,    68,   117,    69,
      70
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      21,    22,     4,    79,    76,   106,   107,     1,     3,     3,
      16,    27,     8,     3,     9,    10,    23,   103,   104,    53,
      54,    55,    83,    84,    56,    91,    57,    81,    82,    35,
       5,    36,     6,    41,    17,    50,    18,   108,     8,    41,
      25,    10,    44,    94,    95,    96,    97,   115,   120,   121,
      98,    99,    30,     8,    26,   118,    10,    32,    33,    37,
      71,    38,    80,    45,    48,    46,   128,    72,   130,   131,
      73,    74,    75,    23,    23,    88,   101,   102,    78,   137,
     113,   114,   119,   123,   143,   124,   136,   138,    49,   142,
      29,   109,   127,   -55,   140,   132,   134,    39,     0,     0,
       0,     0,     0,   125,   126,     0,    87,     0,    52,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   141
};

static const yytype_int16 yycheck[] =
{
      13,    14,     1,    60,    57,     3,     4,     7,     6,     6,
       9,    18,    20,     6,    22,    23,    15,    27,    28,    12,
      13,    14,    24,    25,    17,    78,    19,    72,    73,    28,
       0,    30,     9,    40,    10,    48,    11,    35,    20,    46,
      26,    23,    41,    31,    32,    33,    34,   100,    29,    30,
      38,    39,    37,    20,    21,   108,    23,     8,     5,     8,
      10,    35,     8,    36,     9,    37,   119,    35,   125,   126,
      35,    35,    35,    72,    73,     8,    36,    36,    26,   132,
      36,    36,    35,     8,   141,     8,    18,    15,    46,    16,
      20,    90,    36,    36,   137,    37,    36,    36,    -1,    -1,
      -1,    -1,    -1,   116,   117,    -1,    75,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   138
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    41,     6,    43,     0,     9,    42,    20,    22,
      23,    44,    45,    46,    48,    49,    43,    10,    11,    56,
      57,    45,    45,    43,    51,    26,    21,    49,    50,    56,
      37,    52,     8,     5,    47,    43,    43,     8,    35,    52,
      58,    49,    53,    54,    43,    36,    37,    55,     9,    54,
      45,    59,    55,    12,    13,    14,    17,    19,    43,    60,
      61,    62,    63,    64,    65,    67,    69,    81,    87,    89,
      90,    10,    35,    35,    35,    35,    70,    71,    26,    60,
       8,    51,    51,    24,    25,    70,    85,    85,     8,    72,
      73,    70,    66,    68,    31,    32,    33,    34,    38,    39,
      86,    36,    36,    27,    28,    79,     3,     4,    35,    43,
      74,    75,    78,    36,    36,    70,    82,    88,    70,    35,
      29,    30,    80,     8,     8,    45,    45,    36,    70,    76,
      60,    60,    37,    77,    36,    83,    18,    70,    15,    84,
      77,    45,    16,    60
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    42,    41,    43,    44,    45,    45,    45,    46,
      47,    48,    49,    49,    50,    50,    51,    52,    52,    53,
      53,    54,    55,    55,    56,    56,    58,    57,    59,    60,
      60,    61,    61,    61,    62,    62,    62,    62,    63,    64,
      66,    65,    68,    67,    69,    70,    71,    71,    72,    73,
      73,    74,    74,    75,    76,    76,    77,    77,    78,    78,
      78,    78,    79,    79,    80,    80,    82,    83,    81,    84,
      84,    85,    85,    85,    86,    86,    86,    86,    86,    86,
      88,    87,    89,    90
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     6,     1,     2,     2,     2,     0,     5,
       1,     3,     1,     1,     1,     1,     2,     3,     0,     2,
       0,     2,     3,     0,     2,     0,     0,    10,     2,     2,
       0,     1,     1,     1,     1,     1,     1,     1,     2,     3,
       0,     6,     0,     6,     3,     2,     3,     0,     2,     3,
       0,     1,     1,     4,     2,     0,     3,     0,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     0,    10,     3,
       0,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     8,     1,     1
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
#line 74 "src/parser.yy" /* yacc.c:1646  */
    {
                    //Symbol Table
		    root = new SymbolTable("GLOBAL", NULL); 
                    symtabStack.push(root);
		    
		    //Vector Table
		    vectRoot = new VectorTable(NULL);
		    vectTabStack.push(vectRoot);
			 
                  }
#line 1421 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 85 "src/parser.yy" /* yacc.c:1646  */
    {
                    root->PrintSymbolTables();
		    vectRoot->printStack();
                    delete((yyvsp[-4].sstr));
                  }
#line 1431 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 91 "src/parser.yy" /* yacc.c:1646  */
    {(yyval.sstr) = new std::string(yytext);}
#line 1437 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 99 "src/parser.yy" /* yacc.c:1646  */
    { 
                    Symbol * tmp = new Symbol(STRING, *(yyvsp[-3].sstr), *(yyvsp[-1].sstr));
                    symtabStack.top()->addDecl(tmp);
                    delete((yyvsp[-3].sstr));
                    delete((yyvsp[-1].sstr));

                  }
#line 1449 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 108 "src/parser.yy" /* yacc.c:1646  */
    {
                    (yyval.sstr) = new std::string(yytext);

                  }
#line 1458 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 115 "src/parser.yy" /* yacc.c:1646  */
    {
		    
		    for(std::list<std::string>::iterator it=(*(yyvsp[-1].slist)).begin();it!=(*(yyvsp[-1].slist)).end();++it){  
		      //Symbol* tmp = new Symbol($1, id);  //CHRIS
		      Symbol* tmp = new Symbol((yyvsp[-2].tok), *it);
                      symtabStack.top()->addDecl(tmp);
                    }
                    delete((yyvsp[-1].slist));//delete list now we don't need it
                  }
#line 1472 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 125 "src/parser.yy" /* yacc.c:1646  */
    {(yyval.tok) = FLOAT;}
#line 1478 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 125 "src/parser.yy" /* yacc.c:1646  */
    {(yyval.tok) = INT;}
#line 1484 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 127 "src/parser.yy" /* yacc.c:1646  */
    {(yyval.tok) = (yyvsp[0].tok);}
#line 1490 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 128 "src/parser.yy" /* yacc.c:1646  */
    {(yyval.tok)= VOID;}
#line 1496 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 130 "src/parser.yy" /* yacc.c:1646  */
    {(yyval.slist) = (yyvsp[0].slist); (yyval.slist)->push_front(*(yyvsp[-1].sstr)); delete((yyvsp[-1].sstr));}
#line 1502 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 132 "src/parser.yy" /* yacc.c:1646  */
    {(yyval.slist) = (yyvsp[0].slist); (yyval.slist)->push_front(*(yyvsp[-1].sstr)); delete((yyvsp[-1].sstr));}
#line 1508 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 133 "src/parser.yy" /* yacc.c:1646  */
    {(yyval.slist) = new std::list<std::string>;}
#line 1514 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 139 "src/parser.yy" /* yacc.c:1646  */
    {
                    Symbol *tmp = new Symbol((yyvsp[-1].tok), *(yyvsp[0].sstr));
                    symtabStack.top()->addDecl(tmp);
                  }
#line 1523 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 150 "src/parser.yy" /* yacc.c:1646  */
    {
		    //Symbol Table
                    SymbolTable *func = new SymbolTable(*(yyvsp[-1].sstr), symtabStack.top());
                    symtabStack.top()->children.push_back(func);
                    symtabStack.push(func);

		    //Vector Table
		    VectorTable *vectFunc = new VectorTable(vectTabStack.top());
		    vectTabStack.top()->vectChildren.push_back(vectFunc);
		    vectTabStack.push(vectFunc);
                  }
#line 1539 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 162 "src/parser.yy" /* yacc.c:1646  */
    {
                    symtabStack.pop(); //Symbol Table		    
		    vectTabStack.pop(); //Vector Table
                  }
#line 1548 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 177 "src/parser.yy" /* yacc.c:1646  */
    {
					printInOrder((yyvsp[0].ASTPtr)); 
					AssignNode* asnTempo = new AssignNode(*(yyvsp[-2].sstr), (yyvsp[0].ASTPtr)); 
					ASTNode* AsnAST = dynamic_cast<ASTNode*>(asnTempo); 

					VectorTable* currVectTabTop = vectTabStack.top();
					(currVectTabTop->stmtVect).push_back(AsnAST);					
					}
#line 1561 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 188 "src/parser.yy" /* yacc.c:1646  */
    {
			 
			for(std::list<std::string>::iterator it=(*(yyvsp[0].slist)).begin();it!=(*(yyvsp[0].slist)).end();++it) 
			{
			   if(*it == "newline"){
				IONode *tempo = new IONode (NULL, "READ"); //IONode creation
		                ASTNode *ASTtempo = dynamic_cast<ASTNode*>(tempo);

				VectorTable* currVectTabTop = vectTabStack.top();
				(currVectTabTop->stmtVect).push_back(ASTtempo);
				
				} //end of if - newline
			   else{
			      //if stmt to check for newline
			      SymbolTable* currentTab;
		              currentTab = symtabStack.top();
		              while(currentTab != NULL){

		                if(currentTab->table.find(*it) == currentTab->table.end()){
		                  if(currentTab->scope == "GLOBAL"){
		                    std::cout<<"EXPRESSION ERROR"<<"\n"; //needs help
		              exit(1);
		                  }

		                } //end of if
		                else{

		                  for (int i = 0; i< currentTab->ordered_table.size(); i++){
		                    if (currentTab->ordered_table[i]->var_name == *it){
				     
		                      IONode *tempo = new IONode (currentTab->ordered_table[i], "READ"); //IONode creation
		                      ASTNode *ASTtempo = dynamic_cast<ASTNode*>(tempo);

				      VectorTable* currVectTabTop = vectTabStack.top();
				      (currVectTabTop->stmtVect).push_back(ASTtempo);		      
				     
		                    }
		                  }
		                  break;    
                      
		                } //end of else

		                currentTab = currentTab->parent;

		              } //end of while
			} //end of else - newline
		     }//end of for
		   
		    }
#line 1615 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 241 "src/parser.yy" /* yacc.c:1646  */
    { 
			for(std::list<std::string>::iterator it=(*(yyvsp[0].slist)).begin();it!=(*(yyvsp[0].slist)).end();++it) 
			{
			   if(*it == "newline"){
				IONode *tempo = new IONode (NULL, "WRITE"); //IONode creation
		                ASTNode *ASTtempo = dynamic_cast<ASTNode*>(tempo);

				VectorTable* currVectTabTop = vectTabStack.top();
				(currVectTabTop->stmtVect).push_back(ASTtempo);
				
				} //end of if - newline
			   else{
			      //if stmt to check for newline
			      SymbolTable* currentTab;
		              currentTab = symtabStack.top();
		              while(currentTab != NULL){

		                if(currentTab->table.find(*it) == currentTab->table.end()){
		                  if(currentTab->scope == "GLOBAL"){
		                    std::cout<<"EXPRESSION ERROR"<<"\n"; //needs help
		              exit(1);
		                  }

		                } //end of if
		                else{
		                  std::cout<<currentTab->scope<<std::endl;
		                  for (int i = 0; i< currentTab->ordered_table.size(); i++){
		                    if (currentTab->ordered_table[i]->var_name == *it){
				      std::cout<<"Var type of "<<currentTab->ordered_table[i]->var_name<<" is "<<currentTab->ordered_table[i]->var_type<<std::endl; //Remove
		                      IONode *tempo = new IONode (currentTab->ordered_table[i], "WRITE"); //IONode creation
		                      ASTNode *ASTtempo = dynamic_cast<ASTNode*>(tempo);

				      VectorTable* currVectTabTop = vectTabStack.top();
				      (currVectTabTop->stmtVect).push_back(ASTtempo);
				      
				     
		                    }
		                  }
		                  break;                          
		                } //end of else
		                currentTab = currentTab->parent;
		              } //end of while
			} //end of else - newline
		     }//end of for
		   }
#line 1665 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 309 "src/parser.yy" /* yacc.c:1646  */
    {
			(yyval.ASTPtr) = (yyvsp[-1].ASTPtr);
			if((yyvsp[-1].ASTPtr) == NULL)
			{
				(yyval.ASTPtr) = (yyvsp[0].ASTPtr);
			
			}
			else
			{
				//$$->leftChild = $1;
				(yyval.ASTPtr)->rightChild = (yyvsp[0].ASTPtr);
			}
		}
#line 1683 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 323 "src/parser.yy" /* yacc.c:1646  */
    {
			(yyval.ASTPtr) = dynamic_cast<ASTNode*>(yyvsp[0].ArithPtr);
			if((yyvsp[-2].ASTPtr) == NULL)
			{
				(yyval.ASTPtr)->leftChild = (yyvsp[-1].ASTPtr);
				(yyval.ASTPtr)->rightChild = NULL;
			
			}
			else
			{
				(yyval.ASTPtr)->leftChild = (yyvsp[-2].ASTPtr);
				(yyval.ASTPtr)->leftChild->rightChild = (yyvsp[-1].ASTPtr);
				(yyval.ASTPtr)->rightChild = NULL;
			}
			
		     }
#line 1704 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 340 "src/parser.yy" /* yacc.c:1646  */
    { (yyval.ASTPtr) = NULL; }
#line 1710 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 343 "src/parser.yy" /* yacc.c:1646  */
    {
			(yyval.ASTPtr) = (yyvsp[-1].ASTPtr);
			if((yyvsp[-1].ASTPtr) == NULL)
			{
				(yyval.ASTPtr) = (yyvsp[0].ASTPtr);
			
			}
			else
			{
				//$$->leftChild = $1;
				(yyval.ASTPtr)->rightChild = (yyvsp[0].ASTPtr);
			}
		}
#line 1728 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 357 "src/parser.yy" /* yacc.c:1646  */
    {
			(yyval.ASTPtr) = dynamic_cast<ASTNode*>(yyvsp[0].ArithPtr);
			if((yyvsp[-2].ASTPtr) == NULL)
			{
				(yyval.ASTPtr)->leftChild = (yyvsp[-1].ASTPtr);
				(yyval.ASTPtr)->rightChild = NULL;
			
			}
			else
			{
				(yyval.ASTPtr)->leftChild = (yyvsp[-2].ASTPtr);
				(yyval.ASTPtr)->leftChild->rightChild = (yyvsp[-1].ASTPtr);
				(yyval.ASTPtr)->rightChild = NULL;
			}
			
		     }
#line 1749 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 373 "src/parser.yy" /* yacc.c:1646  */
    { (yyval.ASTPtr) = NULL; }
#line 1755 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 375 "src/parser.yy" /* yacc.c:1646  */
    {(yyval.ASTPtr) = (yyvsp[0].ASTPtr);}
#line 1761 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 375 "src/parser.yy" /* yacc.c:1646  */
    {(yyval.ASTPtr) = (yyvsp[0].ASTPtr);}
#line 1767 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 381 "src/parser.yy" /* yacc.c:1646  */
    {(yyval.ASTPtr) = (yyvsp[-1].ASTPtr);}
#line 1773 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 382 "src/parser.yy" /* yacc.c:1646  */
    {
			
                      SymbolTable* currentTab;
                      currentTab = symtabStack.top();
                      while(currentTab != NULL){
                        if(currentTab->table.find(*(yyvsp[0].sstr)) == currentTab->table.end()){
                          if(currentTab->scope == "GLOBAL"){
                            std::cout<<"EXPRESSION ERROR"<<"\n"; //needs help
                      exit(1);
                          }

                        }
                        else{
                          std::cout<<currentTab->scope<<std::endl;
                          for (int i = 0; i< currentTab->ordered_table.size(); i++){
                            if (currentTab->ordered_table[i]->var_name == *(yyvsp[0].sstr)){

                              VarRef *tempo = new VarRef (currentTab->ordered_table[i]);
                              ASTNode *ASTtempo = dynamic_cast<ASTNode*>(tempo);
                              (yyval.ASTPtr) = ASTtempo;

                            }
                          }
                          break;                          
                        }
                        currentTab = currentTab->parent;
                      }
                    }
#line 1806 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 411 "src/parser.yy" /* yacc.c:1646  */
    {
			LitNode *tempo = new LitNode(std::string(yytext), 5);
			ASTNode *ASTtempo = dynamic_cast<ASTNode*>(tempo);			
			(yyval.ASTPtr) = ASTtempo;
			
			}
#line 1817 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 417 "src/parser.yy" /* yacc.c:1646  */
    {
			LitNode *tempo = new LitNode(std::string(yytext), 6);
			ASTNode *ASTtempo = dynamic_cast<ASTNode*>(tempo);			
			(yyval.ASTPtr) = ASTtempo;
			
			}
#line 1828 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 424 "src/parser.yy" /* yacc.c:1646  */
    {Arithmetic* op = new Arithmetic("+"); (yyval.ArithPtr) = op; }
#line 1834 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 425 "src/parser.yy" /* yacc.c:1646  */
    {Arithmetic* op = new Arithmetic("-"); (yyval.ArithPtr) = op; }
#line 1840 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 426 "src/parser.yy" /* yacc.c:1646  */
    {Arithmetic* op = new Arithmetic("*"); (yyval.ArithPtr) = op; }
#line 1846 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 427 "src/parser.yy" /* yacc.c:1646  */
    {Arithmetic* op = new Arithmetic("/"); (yyval.ArithPtr) = op; }
#line 1852 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 431 "src/parser.yy" /* yacc.c:1646  */
    { 
		    
                    SymbolTable *block = new SymbolTable(genScope(), symtabStack.top());
                    symtabStack.top()->children.push_back(block);
                    symtabStack.push(block);
                    /*Create */
                  }
#line 1864 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 438 "src/parser.yy" /* yacc.c:1646  */
    {
                    symtabStack.pop();//pop off the if block
		    
                    SymbolTable *block = new SymbolTable(genScope(), symtabStack.top());
                    symtabStack.top()->children.push_back(block);
                    symtabStack.push(block);
                    /*Pop, Create */
                  }
#line 1877 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 446 "src/parser.yy" /* yacc.c:1646  */
    {
                    symtabStack.pop();
                  }
#line 1885 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 453 "src/parser.yy" /* yacc.c:1646  */
    {
                    symtabStack.pop();//pop off the if block
		    
                    SymbolTable *block = new SymbolTable(genScope(), symtabStack.top());
                    symtabStack.top()->children.push_back(block);
                    symtabStack.push(block);
                    /*Pop, Create */
                  }
#line 1898 "generated/parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 462 "src/parser.yy" /* yacc.c:1646  */
    {
                    symtabStack.pop();
                  }
#line 1906 "generated/parser.cpp" /* yacc.c:1646  */
    break;


#line 1910 "generated/parser.cpp" /* yacc.c:1646  */
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
#line 473 "src/parser.yy" /* yacc.c:1906  */

