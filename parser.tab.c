/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

    #include "SymbolTable/symbolTable.c"
    #include "AST/ast.c"
    #include "AssemblyGenerator/assemblyGen.c"
    void yyerror (char const *s) {
        extern int yylineno;
        printf ("ERROR IN PARSER: %s Line Number: %i\n", s, yylineno);
    }
    void yywarn(char const *s) {
        extern int yylineno;
        printf("WARNING IN PARSER: %s Line Number: %i\n", s, yylineno);
    }
    static int level=0;
    static int offset=0;
    static int goffset=0;
    static int maxoffset=0;
    static int debug = 0;
    lineList returnStorage = NULL;
    int test = 0;
    hashTable hash;
    void initSymTab();
    

#line 94 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 143 "parser.tab.c"

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

#line 203 "parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   113

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  128

#define YYUNDEFTOK  2
#define YYMAXUTOK   295


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    61,    61,    72,    73,    80,    81,    85,   106,   137,
     138,   139,   143,   157,   143,   195,   198,   204,   207,   213,
     237,   264,   264,   295,   296,   307,   315,   319,   322,   328,
     334,   340,   346,   352,   358,   364,   371,   384,   403,   419,
     437,   446,   453,   461,   478,   505,   518,   527,   549,   579,
     580,   602,   603,   667,   688,   689,   794,   805,   811,   821,
     822,   823,   827,   862,   863,   868,   872,   880,   881,   885,
     886,   887,   888,   889,   890,   891,   892,   896,   897,   901,
     902
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT_P", "CHAR_P", "FLOAT_P", "ID_P",
  "CONSTANT_INT_P", "CONSTANT_CHAR_P", "CONSTANT_FLOAT_P", "NEWLINE_P",
  "IF_P", "ELSE_P", "WHILE_P", "RETURN_P", "READ_P", "WRITE_P",
  "WRITELN_P", "BREAK_P", "SEMICOLON_P", "LP_P", "RP_P", "LB_P", "RB_P",
  "LCB_P", "RCB_P", "COMMA_P", "ADD_P", "MINUS_P", "MULTIPLY_P",
  "DIVIDE_P", "AND_P", "OR_P", "NOT_P", "EQUAL_P", "EQUALTO_P",
  "NOTEQUALTO_P", "LESSTHANOREQUAL_P", "LESSTHAN_P", "GREATERTHAN_P",
  "GREATERTHANOREQUAL_P", "$accept", "Program_P", "declList_P",
  "declaration_P", "varDecl_P", "Type_P", "funcDecl_P", "$@1", "$@2",
  "paramDeclList_P", "paramDeclListTail_P", "paramDecl_P", "block_P",
  "$@3", "localDecls_P", "stmtList_P", "stmt_P", "decisionStmt_P",
  "itterStmt_P", "writeStmt_P", "readStmt_P", "returnStmt_P",
  "assignExpr_P", "exprStmt_P", "expr_P", "var_P", "simpleExpression_P",
  "addAssign_P", "multiAssign_P", "Primary_P", "call_P", "exprList_P",
  "exprListTail_P", "UnaryOp_P", "compareOP_P", "addOP_P", "multiOP_P", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295
};
# endif

#define YYPACT_NINF (-114)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      44,  -114,  -114,  -114,    20,    44,  -114,  -114,    32,  -114,
    -114,  -114,    -4,  -114,    38,    37,    29,    44,    45,    59,
    -114,  -114,    41,  -114,    46,    48,    44,    43,    57,  -114,
    -114,  -114,  -114,    44,    44,    64,    26,  -114,    -4,    31,
    -114,  -114,  -114,    62,    63,     3,    54,     3,    66,    68,
       3,  -114,  -114,  -114,    67,    26,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,    69,    55,    40,   -11,    -5,  -114,  -114,
       3,     3,     3,     3,     3,    72,  -114,    74,    75,    76,
    -114,    77,  -114,  -114,  -114,     3,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,     3,  -114,  -114,    54,  -114,  -114,
      54,   -11,    70,    78,  -114,    79,    80,    82,  -114,  -114,
    -114,    81,  -114,  -114,   -11,    -5,  -114,     3,  -114,  -114,
      26,    26,  -114,  -114,    83,  -114,    26,  -114
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     9,    10,    11,     0,     2,     3,     5,     0,     6,
       1,     4,    12,     7,     0,     0,     0,    15,     0,     0,
      13,    16,    17,     8,    19,     0,     0,     0,     0,    18,
      20,    21,    14,    23,    23,     0,    26,    24,     0,    47,
      56,    57,    58,     0,     0,     0,     0,     0,     0,     0,
       0,    67,    68,    34,     0,    26,    33,    32,    30,    31,
      29,    35,    28,     0,    61,    46,    49,    51,    54,    60,
       0,    63,     0,     0,     0,     0,    61,     0,     0,     0,
      39,     0,    22,    25,    45,     0,    75,    76,    69,    70,
      71,    72,    73,    74,     0,    77,    78,     0,    80,    79,
       0,    53,    65,     0,    64,     0,     0,     0,    43,    42,
      40,     0,    59,    44,    50,    52,    55,     0,    62,    48,
      27,    27,    41,    66,    36,    38,    27,    37
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -114,  -114,  -114,    99,    22,   -12,  -114,  -114,  -114,  -114,
      84,  -114,    85,  -114,    71,    51,  -113,  -114,  -114,  -114,
    -114,  -114,  -114,    23,   -44,   -36,  -114,   -68,    10,   -42,
    -114,  -114,    -8,  -114,  -114,  -114,  -114
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,     9,    15,    25,    20,
      21,    22,    53,    33,    36,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    76,    65,    66,    67,    68,
      69,   103,   104,    70,    94,    97,   100
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      64,    75,   101,    78,    77,    19,    81,   124,   125,    39,
      40,    41,    42,   127,    19,    13,    95,    96,    14,    64,
      10,    35,    35,    50,    98,    99,   114,   102,   105,   106,
     107,    51,    39,    40,    41,    42,    52,    43,    12,    44,
      45,    46,    47,    48,    49,    16,    50,     1,     2,     3,
      31,    71,    18,    72,    51,    34,    34,    17,   116,    52,
      39,    40,    41,    42,    23,    24,    30,    26,    27,    28,
      38,    86,    87,   102,    50,    88,    89,    90,    91,    92,
      93,    31,    73,    74,    64,    64,    79,    80,    84,    85,
      64,   108,    82,   109,   110,   126,   117,   111,   112,   118,
     122,   120,   119,   121,    11,    37,    83,   115,   113,   123,
      29,     0,     0,    32
};

static const yytype_int8 yycheck[] =
{
      36,    45,    70,    47,    46,    17,    50,   120,   121,     6,
       7,     8,     9,   126,    26,    19,    27,    28,    22,    55,
       0,    33,    34,    20,    29,    30,    94,    71,    72,    73,
      74,    28,     6,     7,     8,     9,    33,    11,     6,    13,
      14,    15,    16,    17,    18,     7,    20,     3,     4,     5,
      24,    20,    23,    22,    28,    33,    34,    20,   100,    33,
       6,     7,     8,     9,    19,     6,    23,    26,    22,    21,
       6,    31,    32,   117,    20,    35,    36,    37,    38,    39,
      40,    24,    20,    20,   120,   121,    20,    19,    19,    34,
     126,    19,    25,    19,    19,    12,    26,    21,    21,    21,
      19,    21,    23,    21,     5,    34,    55,    97,    85,   117,
      26,    -1,    -1,    28
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,    42,    43,    44,    45,    46,    47,
       0,    44,     6,    19,    22,    48,     7,    20,    23,    46,
      50,    51,    52,    19,     6,    49,    26,    22,    21,    51,
      23,    24,    53,    54,    45,    46,    55,    55,     6,     6,
       7,     8,     9,    11,    13,    14,    15,    16,    17,    18,
      20,    28,    33,    53,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      74,    20,    22,    20,    20,    65,    66,    70,    65,    20,
      19,    65,    25,    56,    19,    34,    31,    32,    35,    36,
      37,    38,    39,    40,    75,    27,    28,    76,    29,    30,
      77,    68,    65,    72,    73,    65,    65,    65,    19,    19,
      19,    21,    21,    64,    68,    69,    70,    26,    21,    23,
      21,    21,    19,    73,    57,    57,    12,    57
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    44,    45,    45,    46,
      46,    46,    48,    49,    47,    50,    50,    51,    51,    52,
      52,    54,    53,    55,    55,    56,    56,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    58,    58,    59,    59,
      60,    60,    61,    62,    63,    64,    65,    66,    66,    67,
      67,    68,    68,    68,    69,    69,    70,    70,    70,    70,
      70,    70,    71,    72,    72,    73,    73,    74,    74,    75,
      75,    75,    75,    75,    75,    75,    75,    76,    76,    77,
      77
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     6,     1,
       1,     1,     0,     0,     8,     0,     1,     1,     3,     2,
       4,     0,     5,     0,     2,     2,     0,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     7,     5,     2,
       3,     4,     3,     3,     3,     2,     1,     1,     4,     1,
       3,     1,     3,     2,     1,     3,     1,     1,     1,     3,
       1,     1,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
#line 61 "parser.y"
               { 
            if (strcmp((yyvsp[0].node)->name, "main")){
                printNode((yyvsp[0].node));
                yyerror("main function is requried and should be last declared function");
                exit(1);
            }
            prog = (yyvsp[0].node);
        }
#line 1481 "parser.tab.c"
    break;

  case 3:
#line 72 "parser.y"
                        {(yyval.node) = (yyvsp[0].node);}
#line 1487 "parser.tab.c"
    break;

  case 4:
#line 73 "parser.y"
                                   {
            (yyvsp[0].node)->left = (yyvsp[-1].node);
            (yyval.node) = (yyvsp[0].node);
        }
#line 1496 "parser.tab.c"
    break;

  case 5:
#line 80 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1502 "parser.tab.c"
    break;

  case 6:
#line 81 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1508 "parser.tab.c"
    break;

  case 7:
#line 85 "parser.y"
                                {
            if (lookup(hash, (yyvsp[-1].string))){
                printf("Variable %s Exists in Symbol Table\n", (yyvsp[-1].string));
                yyerror ("ERROR DUPLICATE VARIABLE");
                exit(1);
            }
            hashEntry entry = createHashEntry((yyvsp[-1].string),0,(yyvsp[-2].node), level, offset, NULL);
            insertEntry(hash, entry);
            (yyval.node) = createASTNode(VARDECL);
            (yyval.node)->name = (yyvsp[-1].string);
            (yyval.node)->op = (yyvsp[-2].node);
            (yyval.node)->symbol = entry;
            (yyval.node)->isType = (yyvsp[-2].node);
            offset += 1;
            if (offset > maxoffset){
                maxoffset = offset;
            }
            if (debug){
                fprintf(stderr, "Added Variable to Abstract Syntax Tree with name %s\n", (yyvsp[-1].string));
            }
        }
#line 1534 "parser.tab.c"
    break;

  case 8:
#line 106 "parser.y"
                                                         {
            if (lookup(hash, (yyvsp[-4].string))){
                printf("Variable %s Exists in Symbol Table\n", (yyvsp[-4].string));
                yyerror ("ERROR DUPLICATE VARIABLE Array");
                exit(1);
            }
            if ((yyvsp[-2].value) <= 0){
                printf("Array Size constant must be greater than 0\n");
                yyerror ((yyvsp[-2].value));
                exit(1);
            }
            hashEntry entry = createHashEntry((yyvsp[-4].string), (yyvsp[-2].value), (yyvsp[-5].node), level, offset, NULL);
            insertEntry(hash, entry);
            entry->isAFunc = 2;
            (yyval.node) = createASTNode(VARDECL);
            (yyval.node)->name = (yyvsp[-4].string);
            (yyval.node)->op = (yyvsp[-5].node);
            (yyval.node)->value = (yyvsp[-2].value);
            (yyval.node)->symbol = entry;
            (yyval.node)->isType = (yyvsp[-5].node);
            offset += (yyvsp[-2].value);
            if (offset > maxoffset){
                maxoffset = offset;
            }
            if (debug){
                fprintf(stderr, "Added Variable Array to Abstract Syntax Tree with name %s\n", (yyvsp[-4].string));
            }
        }
#line 1567 "parser.tab.c"
    break;

  case 9:
#line 137 "parser.y"
              { (yyval.node) = INTDECL; }
#line 1573 "parser.tab.c"
    break;

  case 10:
#line 138 "parser.y"
               { (yyval.node) = CHARDECL; }
#line 1579 "parser.tab.c"
    break;

  case 11:
#line 139 "parser.y"
                { (yyval.node) = FLOATDECL; }
#line 1585 "parser.tab.c"
    break;

  case 12:
#line 143 "parser.y"
                    {
             if (lookup(hash, (yyvsp[0].string))){
                printf("Name %s Already used\n", (yyvsp[0].string));
                yyerror ("DUPLICATE NAME FOR FUNCTION");
                exit(1);
            }
            hashEntry entry = createHashEntry((yyvsp[0].string), 0, (yyvsp[-1].node), level, offset, NULL);
            entry->isAFunc = 1;
            insertEntry(hash, entry);
            goffset = offset;
            offset = 2;
            if (offset > maxoffset){
                maxoffset = offset;
            }
        }
#line 1605 "parser.tab.c"
    break;

  case 13:
#line 157 "parser.y"
                              {
            // Add parameters list to the fparams pointer for later comparison.
            (lookup(hash, (yyvsp[-3].string)))->fparams = (yyvsp[0].node);
        }
#line 1614 "parser.tab.c"
    break;

  case 14:
#line 160 "parser.y"
                      {
            (yyval.node) = createASTNode(FUNCDECL);
            (yyval.node)->name = (yyvsp[-6].string);
            (yyval.node)->op = (yyvsp[-7].node);
            (yyval.node)->s1 = (yyvsp[-3].node);
            (yyval.node)->right = (yyvsp[0].node);
            (yyval.node)->symbol = lookup(hash, (yyvsp[-6].string));
            level = 0;
            (yyval.node)->value = maxoffset;
            (yyval.node)->symbol->mySize = maxoffset;
            offset = goffset;
            maxoffset = 0;
            if(returnStorage == NULL){
                yyerror("Function must return declared type\n");
                exit(1);
            }
            while(returnStorage != NULL){
                
                if (compareReturn(returnStorage->lineno, (yyvsp[-7].node)) == 0){
                    yyerror("Incompatible Return Type\n");
                    exit(1);
                }
                returnStorage = returnStorage->next;
            }
            if (debug){
                printf("Making Function with name %s\n",(yyvsp[-6].string));
                printNode((yyval.node));
                printHashTable(hash);
            }
            returnStorage = NULL;
        }
#line 1650 "parser.tab.c"
    break;

  case 15:
#line 195 "parser.y"
                    {
            (yyval.node) = NULL; 
        }
#line 1658 "parser.tab.c"
    break;

  case 16:
#line 198 "parser.y"
                            {
            (yyval.node) = (yyvsp[0].node);
        }
#line 1666 "parser.tab.c"
    break;

  case 17:
#line 204 "parser.y"
                    {
            (yyval.node) = (yyvsp[0].node);
        }
#line 1674 "parser.tab.c"
    break;

  case 18:
#line 207 "parser.y"
                                                {
            (yyvsp[-2].node)->left = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-2].node);
        }
#line 1683 "parser.tab.c"
    break;

  case 19:
#line 213 "parser.y"
                    {
            if(lookup(hash, (yyvsp[0].string))){
                printf("Duplicate Variable Name\n");
                yyerror((yyvsp[0].string));
                yyerror("Change Argument Name\n");
                exit(1);
            }
            (yyval.node) = createASTNode(PARAMDECL);
            (yyval.node)->name = (yyvsp[0].string);
            (yyval.node)->op = (yyvsp[-1].node);
            (yyval.node)->value = 0;
            (yyval.node)->isType = (yyvsp[-1].node);
            hashEntry entry = createHashEntry((yyvsp[0].string), 1, (yyvsp[-1].node), level+1, offset, NULL);
            insertEntry(hash, entry);
            (yyval.node)->symbol = entry;
            offset += 1;
            if (offset>maxoffset)
                maxoffset = offset;
            if (debug){
                printf("Adding Parameter with name %s\n",(yyvsp[0].string));
                printNode((yyval.node));
                printHashTable(hash);
            }
        }
#line 1712 "parser.tab.c"
    break;

  case 20:
#line 237 "parser.y"
                              {
            if(lookup(hash, (yyvsp[-2].string))){
                printf("Duplicate Variable Name\n");
                yyerror((yyvsp[-2].string));
                yyerror("Change Argument Name\n");
                exit(1);
            }
            (yyval.node) = createASTNode(PARAMDECL);
            (yyval.node)->name = (yyvsp[-2].string);
            (yyval.node)->op = (yyvsp[-3].node);
            (yyval.node)->value = 1;
            (yyval.node)->isType = (yyvsp[-3].node);
            hashEntry entry = createHashEntry((yyvsp[-2].string), 1, (yyvsp[-3].node), level+1, offset, NULL);
            insertEntry(hash, entry);
            (yyval.node)->symbol = entry;
            offset += 1;
            if (offset>maxoffset)
                maxoffset = offset;
            if (debug){
                printf("Adding Array Parameter with name %s\n",(yyvsp[-2].string));
                printNode((yyval.node));
                printHashTable(hash);
            }
        }
#line 1741 "parser.tab.c"
    break;

  case 21:
#line 264 "parser.y"
              {
            level++;
            addScopeLevel(hash);
        }
#line 1750 "parser.tab.c"
    break;

  case 22:
#line 267 "parser.y"
                                       {
            (yyval.node) = createASTNode(BLOCK);
            (yyval.node)->name = "B";
            //if localDecls_P is null then theres only statements
            if((yyvsp[-2].node) == NULL){
                (yyval.node)->right = (yyvsp[-1].node);
            }
            //if not then attach right
            else {
                attatchLeft((yyvsp[-2].node), (yyvsp[-1].node));
                (yyval.node)->right = (yyvsp[-2].node);
            }
            if(debug) {
                fprintf(stderr,"\ntable before deleting\n");
                printHashTable(hash);
            }
            removeScopeLevel(hash);
            offset -= 1;
            level--;
            if (debug) {
                fprintf(stderr,"\nEnd of Block, deleting symbols\n");
                fprintf(stderr,"     current table...\n");
                printHashTable(hash);/*Display after*/
            }
        }
#line 1780 "parser.tab.c"
    break;

  case 23:
#line 295 "parser.y"
                    { (yyval.node) = NULL; }
#line 1786 "parser.tab.c"
    break;

  case 24:
#line 296 "parser.y"
                                {
        if((yyvsp[-1].node) != NULL){
            (yyvsp[-1].node)->left=(yyvsp[0].node);
            (yyval.node)=(yyvsp[-1].node);
        }
        else
            (yyval.node)=(yyvsp[0].node);
    }
#line 1799 "parser.tab.c"
    break;

  case 25:
#line 307 "parser.y"
                          {
            if((yyvsp[-1].node) != NULL){
                (yyvsp[-1].node)->left=(yyvsp[0].node);
                (yyval.node)=(yyvsp[-1].node);
            }
            else
                (yyval.node)=(yyvsp[0].node);
        }
#line 1812 "parser.tab.c"
    break;

  case 26:
#line 315 "parser.y"
                    { (yyval.node) = NULL; }
#line 1818 "parser.tab.c"
    break;

  case 27:
#line 319 "parser.y"
                    {
            (yyval.node) = NULL;
        }
#line 1826 "parser.tab.c"
    break;

  case 28:
#line 322 "parser.y"
                   {
            (yyval.node) = (yyvsp[0].node);
            if (debug){
                fprintf(stderr, "Converting a expression Statement\n");
            }
        }
#line 1837 "parser.tab.c"
    break;

  case 29:
#line 328 "parser.y"
                     {
            (yyval.node) = (yyvsp[0].node);
            if (debug){
                fprintf(stderr, "Converting a Return Statement\n");
            }
        }
#line 1848 "parser.tab.c"
    break;

  case 30:
#line 334 "parser.y"
                    {
            (yyval.node) = (yyvsp[0].node);
            if (debug){
                fprintf(stderr, "Converting a Write Statement\n");
            }
        }
#line 1859 "parser.tab.c"
    break;

  case 31:
#line 340 "parser.y"
                   {
            (yyval.node) = (yyvsp[0].node);
            if (debug){
                fprintf(stderr, "Converting a Read Statement\n");
            }
        }
#line 1870 "parser.tab.c"
    break;

  case 32:
#line 346 "parser.y"
                    {
            (yyval.node) = (yyvsp[0].node);
            if (debug){
                fprintf(stderr, "Converting a Itteration Statement\n");
            }
        }
#line 1881 "parser.tab.c"
    break;

  case 33:
#line 352 "parser.y"
                       {
            (yyval.node) = (yyvsp[0].node);
            if (debug){
                fprintf(stderr, "Converting a Decision Statement\n");
            }
        }
#line 1892 "parser.tab.c"
    break;

  case 34:
#line 358 "parser.y"
                {
            (yyval.node) = (yyvsp[0].node);
            if (debug){
                fprintf(stderr, "Converting a Block Statement\n");
            }
        }
#line 1903 "parser.tab.c"
    break;

  case 35:
#line 364 "parser.y"
                     { 
            (yyval.node) = (yyvsp[0].node); 
            printf("Converting an Assign Statement\n");
        }
#line 1912 "parser.tab.c"
    break;

  case 36:
#line 371 "parser.y"
                                     {
            printf("if statement found\n");
            (yyval.node) = createASTNode(DECISIONSTMT);
            if (checkExprType((yyvsp[-2].node)) != 1){
                printf("Error, non binary comparison operators\n");
                yyerror((yyvsp[-2].node));
                exit(1);
            }
            (yyval.node)->name = "IF";
            //set right to the expression in if stmt
            (yyval.node)->right = (yyvsp[-2].node);
            (yyval.node)->s1 = (yyvsp[0].node);
        }
#line 1930 "parser.tab.c"
    break;

  case 37:
#line 384 "parser.y"
                                                   {
            printf("if else statement\n");
            (yyval.node) = createASTNode(DECISIONSTMT);
            (yyval.node)->name = "IFE";
            if (checkExprType((yyvsp[-4].node)) != 1){
                printf("Error, non binary comparison operators\n");
                yyerror((yyvsp[-4].node));
                exit(1);
            }
            //set right to the expression in if stmt
            (yyval.node)->right = (yyvsp[-4].node);
            //set the if child pointer to the if stmt
            (yyval.node)->s1 = (yyvsp[-2].node);
            //set the else child pointer to the else stmt
            (yyval.node)->s2 = (yyvsp[0].node);
        }
#line 1951 "parser.tab.c"
    break;

  case 38:
#line 403 "parser.y"
                                        {
            (yyval.node) = createASTNode(ITTERSTMT);
            if (checkExprType((yyvsp[-2].node)) != 1){
                printf("Error, non binary comparison operators\n");
                yyerror((yyvsp[-2].node));
                exit(1);
            }
            (yyval.node)->right = (yyvsp[-2].node);
            printf("%d", checkForBreak((yyvsp[0].node)));
            (yyval.node)->s1 = (yyvsp[0].node);
            /*
                need to check $5 for a break statement, since $5 can be a block
                this means we may need to recursively check the block for a break
                statement. or 
            */
        }
#line 1972 "parser.tab.c"
    break;

  case 39:
#line 419 "parser.y"
                            {
            printf("break statement\n");
            (yyval.node) = createASTNode(BREAKSTMT);
            if (level <= 1){
                yyerror("Break statment not in while loop\n");
                exit(1);
            }
            /*
                The break statement must be in a scope that is greater than 1
                this is because 0 is global and 1 is a function, anything greater
                than that indicates a scope within a function. once we verify the
                scope then we can verify the node is a while node and therefore 
                the break statement will be valid.
            */
        }
#line 1992 "parser.tab.c"
    break;

  case 40:
#line 437 "parser.y"
                                   {
            printf("write statement\n");
            (yyval.node) = createASTNode(WRITESTMT);
            (yyval.node)->name = "W";
            (yyval.node)->right = (yyvsp[-1].node);
            if ((yyvsp[-1].node)->type == IDENTIFIER){
                (yyvsp[-1].node)->symbol->isUsed = 1;
            }
        }
#line 2006 "parser.tab.c"
    break;

  case 41:
#line 446 "parser.y"
                                        {
            printf("write line statement");
            (yyval.node) = createASTNode(WRITELN);
        }
#line 2015 "parser.tab.c"
    break;

  case 42:
#line 453 "parser.y"
                                     {
            printf("read statement\n");
            (yyval.node) = createASTNode(READSTMT);
            (yyval.node)->right = (yyvsp[-1].node);
        }
#line 2025 "parser.tab.c"
    break;

  case 43:
#line 461 "parser.y"
                                    {
            test++;
            printf("%d RETURN", test);
            (yyval.node) = createASTNode(RETURNSTMT);
            (yyval.node)->name = "RETURN";
            (yyval.node)->s2 = (yyvsp[-1].node);
            if ((yyvsp[-1].node)->type == IDENTIFIER){
                (yyvsp[-1].node)->symbol->isUsed = 1;
            }
            if (returnStorage != NULL)
                addLineToReturn(returnStorage, (yyvsp[-1].node)->isType);
            else 
                returnStorage = createLineListRec((yyvsp[-1].node)->isType);
        }
#line 2044 "parser.tab.c"
    break;

  case 44:
#line 478 "parser.y"
                                 {
            if ((yyvsp[-2].node)->isType != (yyvsp[0].node)->isType){
                yyerror("Type Mismatch\n");
                exit(1);
            }
            (yyval.node) = createASTNode(ASSIGNSTMT);
            (yyval.node)->name = (yyvsp[-2].node)->name;
            (yyval.node)->right = (yyvsp[-2].node);
            (yyval.node)->s1 = (yyvsp[0].node);
            (yyval.node)->s1->name = (yyvsp[-2].node)->name;
            (yyval.node)->isType = (yyvsp[-2].node)->isType;
            (yyval.node)->name = CreateTemp();
            hashEntry entry = createHashEntry((yyval.node)->name, 1, (yyval.node)->isType, level, offset, NULL);
            entry->value->charval = (yyvsp[0].node)->name;
            insertEntry(hash, entry);
            (yyval.node)->symbol = entry;
            offset+=1;
            if(offset>maxoffset)
                maxoffset = offset;
            if(debug){
                printNode((yyval.node));
                printf("%d operator\n", (yyval.node)->op);
                printf("%s = %s\n", (yyvsp[-2].node)->name, (yyvsp[0].node)->name);
            }
        }
#line 2074 "parser.tab.c"
    break;

  case 45:
#line 505 "parser.y"
                           {
            (yyval.node) = createASTNode(EXPRSTMT);
            (yyval.node)->name = (yyvsp[-1].node)->name;
            (yyval.node)->right = (yyvsp[-1].node);
            (yyval.node)->isType = (yyvsp[-1].node)->isType;
            if (debug){
                printNode((yyvsp[-1].node));
                fprintf(stderr, "Finished creating an expression Statement\n");
            }
        }
#line 2089 "parser.tab.c"
    break;

  case 46:
#line 518 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2095 "parser.tab.c"
    break;

  case 47:
#line 527 "parser.y"
             {
            hashEntry s;
            if (debug)
                printf("Searching for variable named %s\n", (yyvsp[0].string));
                if ((s = lookup(hash, (yyvsp[0].string))) != NULL){
                    if (s->isAFunc == 2){
                    yyerror((yyvsp[0].string));
                    yyerror("Variable is an array, syntax error");
                }
                if (debug)
                    printf("%s found in symbol table\n", (yyvsp[0].string));
                (yyval.node) = createASTNode(IDENTIFIER);
                (yyval.node)->name = (yyvsp[0].string);
                (yyval.node)->symbol = s;
                (yyval.node)->isType = s->type;
            }
            else {
                yyerror((yyvsp[0].string));
                printf("Variable is Undeclared\n");
                exit(1);
            }
        }
#line 2122 "parser.tab.c"
    break;

  case 48:
#line 549 "parser.y"
                              {
            hashEntry s;
            if((s = lookup(hash, (yyvsp[-3].string))) != NULL){
                if(s->isAFunc != 2){
                    yyerror((yyvsp[-3].string));
                    yyerror("Variable is not an array, syntax error");
                }
                (yyval.node) = createASTNode(IDENTIFIER);
                (yyval.node)->name = (yyvsp[-3].string);
                switch(s->type){
                    case FLOATDECL:
                        (yyvsp[-1].node)->type = FLOATNUMBER;
                        break;
                    default:
                        (yyvsp[-1].node)->type = NUMBER;
                        break;
                }
                (yyval.node)->right = (yyvsp[-1].node);
                (yyval.node)->symbol = s;
                (yyval.node)->isType = s->type;
            }
            else {
                printf("Undeclared variable used\n");
                yyerror((yyvsp[-3].string));
                exit(1);
            }
        }
#line 2154 "parser.tab.c"
    break;

  case 49:
#line 579 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2160 "parser.tab.c"
    break;

  case 50:
#line 580 "parser.y"
                                                   {
            if ((yyvsp[-2].node)->isType != (yyvsp[0].node)->isType) {
                printf("Type Mismatch\n");
                yyerror(" ");
                exit(1);
            }
            (yyval.node) = createASTNode(EXPR);
            (yyval.node)->op = (yyvsp[-1].op);
            (yyval.node)->left = (yyvsp[-2].node);
            (yyval.node)->right = (yyvsp[0].node);
            (yyval.node)->isType = (yyvsp[-2].node)->isType;
            (yyval.node)->name = CreateTemp();
            hashEntry entry = createHashEntry((yyval.node)->name, 0, (yyval.node)->isType, level, offset+1, NULL);
            insertEntry(hash, entry);
            (yyval.node)->symbol = entry;
            offset+=1;
            if(offset>maxoffset)
                maxoffset = offset;
        }
#line 2184 "parser.tab.c"
    break;

  case 51:
#line 602 "parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 2190 "parser.tab.c"
    break;

  case 52:
#line 603 "parser.y"
                                          {
            if ((yyvsp[-2].node)->isType != (yyvsp[0].node)->isType) {
                printf("Type Mismatch\n");
                yyerror(" ");
                exit(1);
            }
            if ((yyvsp[-2].node)->type == IDENTIFIER){
                (yyvsp[-2].node)->symbol->isUsed = 1;
            }
            if ((yyvsp[0].node)->type == IDENTIFIER){
                (yyvsp[0].node)->symbol->isUsed = 1;
            }
            /*

                Constant Folding:
                    We need to check both sides of the expression for a Number
                    If the expression is a number on both sides
                        then we can perform constant Folding
                        In here we have to check the operator type
                        if plus
                            node type shouldnt be expression anymore and instead should be an assignment
                            if we get all the way up to the top and both are numbers we know the whole equation
                            contained numbers and therefore are an assignment node and not an expression node
                            do addition
                        else
                            do subtraction
                    Else 
                        we can just do the normal process

            */
            if ((yyvsp[-2].node)->type == NUMBER && (yyvsp[0].node)->type == NUMBER){
                if(debug){
                    printf("Attempting Constant Fold\n");
                    printf("%d ", (yyvsp[-2].node)->value);
                    printOperator((yyvsp[-1].op));
                    printf(" %d\n", (yyvsp[0].node)->value);
                }
                switch((yyvsp[-1].op)){
                    case ADD:
                        (yyvsp[-2].node)->value = (yyvsp[-2].node)->value + (yyvsp[0].node)->value;
                        (yyval.node) = (yyvsp[-2].node);
                        break;
                    case MINUS:
                        (yyvsp[-2].node)->value = (yyvsp[-2].node)->value - (yyvsp[0].node)->value;
                        (yyval.node) = (yyvsp[-2].node);
                        break;
                }
            }
            else{
                (yyval.node) = createASTNode(EXPR);
                (yyval.node)->op = (yyvsp[-1].op);
                (yyval.node)->right = (yyvsp[0].node);
                (yyval.node)->left = (yyvsp[-2].node);
                (yyval.node)->isType = (yyvsp[-2].node)->isType;
                (yyval.node)->name = CreateTemp();
                hashEntry entry = createHashEntry((yyval.node)->name, 0, (yyval.node)->isType, level, offset, NULL);
                insertEntry(hash, entry);
                (yyval.node)->symbol = entry;
                offset+=1;
                if(offset>maxoffset)
                    maxoffset = offset;
            }
            
        }
#line 2259 "parser.tab.c"
    break;

  case 53:
#line 667 "parser.y"
                             {
            if ( (yyvsp[0].node)->isType != INTDECL ) {
                printf("Type Mismatch\n");
                yyerror(" ");
                exit(1);
            }
            (yyval.node) = createASTNode(EXPR);
            (yyval.node)->op = (yyvsp[-1].op);
            (yyval.node)->right = (yyvsp[0].node);
            (yyval.node)->isType = (yyvsp[0].node)->isType;
            (yyval.node)->name = CreateTemp();
            hashEntry entry = createHashEntry((yyval.node)->name, 0, (yyval.node)->isType, level, offset, NULL);
            insertEntry(hash, entry);
            (yyval.node)->symbol = entry;
            offset+=1;
            if(offset>maxoffset)
                maxoffset = offset;
        }
#line 2282 "parser.tab.c"
    break;

  case 54:
#line 688 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2288 "parser.tab.c"
    break;

  case 55:
#line 689 "parser.y"
                                          {
            if ((yyvsp[-2].node)->isType != (yyvsp[0].node)->isType) {
                printf("Type Mismatch\n");
                yyerror(" ");
                exit(1);
            }
            if ((yyvsp[-2].node)->type == IDENTIFIER){
                (yyvsp[-2].node)->symbol->isUsed = 1;
            }
            if ((yyvsp[0].node)->type == IDENTIFIER){
                (yyvsp[0].node)->symbol->isUsed = 1;
            }
            /*

                Constant Folding:
                    We need to check both sides of the expression for a Number
                    If the expression is a number on both sides
                        then we can perform constant Folding
                        In here we have to check the operator type
                        if multiply
                            node type shouldnt be expression anymore and instead should be an assignment
                            if we get all the way up to the top and both are numbers we know the whole equation
                            contained numbers and therefore are an assignment node and not an expression node
                            do addition
                        else
                            do division
                            Note: Since we are only handling Ints then we will just take the rounding that C does
                    Else 
                        we can just do the normal process

            */
            if ((yyvsp[-1].op) == DIVIDE && (yyvsp[-2].node)->isType == INTDECL){
                yywarn("Divison on INT can cause FLOAT. Consider changing variable type to float.");
            }
            if ((yyvsp[-2].node)->type == NUMBER && (yyvsp[0].node)->type == NUMBER){
                if(debug){
                    printf("Attempting Constant Fold\n");
                    printf("%d ", (yyvsp[-2].node)->value);
                    printOperator((yyvsp[-1].op));
                    printf(" %d\n", (yyvsp[0].node)->value);
                }
                switch((yyvsp[-1].op)){
                    case MULTIPLY:
                        (yyvsp[-2].node)->value = (yyvsp[-2].node)->value * (yyvsp[0].node)->value;
                        (yyval.node) = (yyvsp[-2].node);
                        break;
                    case DIVIDE:
                        yywarn("Dividing Two Integers will result in a rounded value");
                        (yyvsp[-2].node)->value = (yyvsp[-2].node)->value / (yyvsp[0].node)->value;
                        (yyval.node) = (yyvsp[-2].node);
                        break;
                }
            }
            /*
                Strenght Reduction:
                    check if left is variable and right is a number
                        switch to check for multiplication operator
                            if it is then just make it add variable to itself
                            will only work if the number is 2
            */
            if ((yyvsp[-2].node)->type == IDENTIFIER && (yyvsp[0].node)->type == NUMBER && (yyvsp[-1].op) == MULTIPLY && (yyvsp[0].node)->value == 2){
                (yyval.node) = createASTNode(EXPR);
                (yyval.node)->op = ADD;
                (yyval.node)->right = (yyvsp[-2].node);
                (yyval.node)->left = (yyvsp[-2].node);
                (yyval.node)->isType = (yyvsp[-2].node)->isType;
                (yyval.node)->name = CreateTemp();
                hashEntry entry = createHashEntry((yyval.node)->name, 0, (yyval.node)->isType, level, offset, NULL);
                insertEntry(hash, entry);
                (yyval.node)->symbol = entry;
                offset+=1;
                if(offset>maxoffset)
                    maxoffset = offset;
            }
            if ((yyvsp[0].node)->type == IDENTIFIER && (yyvsp[-2].node)->type == NUMBER && (yyvsp[-1].op) == MULTIPLY && (yyvsp[-2].node)->value == 2){
                (yyval.node) = createASTNode(EXPR);
                (yyval.node)->op = ADD;
                (yyval.node)->right = (yyvsp[0].node);
                (yyval.node)->left = (yyvsp[0].node);
                (yyval.node)->isType = (yyvsp[0].node)->isType;
                (yyval.node)->name = CreateTemp();
                hashEntry entry = createHashEntry((yyval.node)->name, 0, (yyval.node)->isType, level, offset, NULL);
                insertEntry(hash, entry);
                (yyval.node)->symbol = entry;
                offset+=1;
                if(offset>maxoffset)
                    maxoffset = offset;
            }
            else {
                (yyval.node) = createASTNode(EXPR);
                (yyval.node)->op = (yyvsp[-1].op);
                (yyval.node)->right = (yyvsp[0].node);
                (yyval.node)->left = (yyvsp[-2].node);
                (yyval.node)->isType = (yyvsp[-2].node)->isType;
                (yyval.node)->name = CreateTemp();
                hashEntry entry = createHashEntry((yyval.node)->name, 0, (yyval.node)->isType, level, offset, NULL);
                insertEntry(hash, entry);
                (yyval.node)->symbol = entry;
                offset+=1;
                if(offset>maxoffset)
                    maxoffset = offset;
            }
        }
#line 2396 "parser.tab.c"
    break;

  case 56:
#line 794 "parser.y"
                       {
            (yyval.node) = createASTNode(NUMBER);
            (yyval.node)->name = CreateTemp();
            (yyval.node)->value = (yyvsp[0].value);
            (yyval.node)->op = INTDECL;
            (yyval.node)->isType = INTDECL;
            printf("%d", (yyvsp[0].value));
            if (debug){
                fprintf(stderr, "The Number is: %d\n",(yyvsp[0].value));
            }
        }
#line 2412 "parser.tab.c"
    break;

  case 57:
#line 805 "parser.y"
                        {
            (yyval.node) = createASTNode(CHARACTER);
            (yyval.node)->name = CreateTemp();
            (yyval.node)->isType = CHARDECL;
            (yyval.node)->str = (yyvsp[0].string);
        }
#line 2423 "parser.tab.c"
    break;

  case 58:
#line 811 "parser.y"
                         {
            (yyval.node) = createASTNode(FLOATNUMBER);
            (yyval.node)->name = CreateTemp();
            (yyval.node)->fvalue = (yyvsp[0].fvalue);
            (yyval.node)->op = FLOATDECL;
            (yyval.node)->isType = FLOATDECL;
            if (debug){
                fprintf(stderr, "The Float is: %f\n",(yyvsp[0].fvalue));
            }
        }
#line 2438 "parser.tab.c"
    break;

  case 59:
#line 821 "parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 2444 "parser.tab.c"
    break;

  case 60:
#line 822 "parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 2450 "parser.tab.c"
    break;

  case 61:
#line 823 "parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2456 "parser.tab.c"
    break;

  case 62:
#line 827 "parser.y"
                                  {
            hashEntry s;
            if ((s = lookup(hash, (yyvsp[-3].string))) != NULL){
                //Add if statment to check type to make sure we are calling a function and not a variable.
                if (s->isAFunc != 1){
                    printf("Error: %s is not a function\n", s->name);
                    yyerror(s->name);
                    exit(1);
                }
                if (compareFormals(s->fparams, (yyvsp[-1].node)) != 1){
                    printf("Variables in call dont match function\n");
                    yyerror((yyvsp[-1].node));
                    exit(1);
                }

                (yyval.node) = createASTNode(CALL);
                (yyval.node)->right = (yyvsp[-1].node);
                (yyval.node)->name = (yyvsp[-3].string);
                (yyval.node)->symbol = s;
                (yyval.node)->value = s->value;
                (yyval.node)->isType = s->type;

                if(debug){
                    printNode((yyval.node));
                    printf("Added Call to Function to AST\n");
                }
            }
            else{
                    yyerror((yyvsp[-3].string));
                    yyerror("Function not defined in symbol table");
                    exit(1);
            }
        }
#line 2494 "parser.tab.c"
    break;

  case 63:
#line 862 "parser.y"
                    { (yyval.node) = NULL; }
#line 2500 "parser.tab.c"
    break;

  case 64:
#line 863 "parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2506 "parser.tab.c"
    break;

  case 65:
#line 868 "parser.y"
               {
            (yyval.node) = createASTNode(ARGLIST);
            (yyval.node)->right = (yyvsp[0].node);
        }
#line 2515 "parser.tab.c"
    break;

  case 66:
#line 872 "parser.y"
                                      {
            (yyval.node) = createASTNode(ARGLIST);
            (yyval.node)->left = (yyvsp[0].node);
            (yyval.node)->right = (yyvsp[-2].node);
        }
#line 2525 "parser.tab.c"
    break;

  case 67:
#line 880 "parser.y"
                { (yyval.op) = MINUS; }
#line 2531 "parser.tab.c"
    break;

  case 68:
#line 881 "parser.y"
              { (yyval.op) = NOT; }
#line 2537 "parser.tab.c"
    break;

  case 69:
#line 885 "parser.y"
                  { (yyval.op) = EQUALTO; }
#line 2543 "parser.tab.c"
    break;

  case 70:
#line 886 "parser.y"
                     { (yyval.op) = NOTEQUALTO; }
#line 2549 "parser.tab.c"
    break;

  case 71:
#line 887 "parser.y"
                          { (yyval.op) = LESSTHANOREQUAL; }
#line 2555 "parser.tab.c"
    break;

  case 72:
#line 888 "parser.y"
                   { (yyval.op) = LESSTHAN;}
#line 2561 "parser.tab.c"
    break;

  case 73:
#line 889 "parser.y"
                      { (yyval.op) = GREATERTHAN;}
#line 2567 "parser.tab.c"
    break;

  case 74:
#line 890 "parser.y"
                             { (yyval.op) = GREATERTHANOREQUAL;}
#line 2573 "parser.tab.c"
    break;

  case 75:
#line 891 "parser.y"
              { (yyval.op) = AND;}
#line 2579 "parser.tab.c"
    break;

  case 76:
#line 892 "parser.y"
             { (yyval.op) = OR;}
#line 2585 "parser.tab.c"
    break;

  case 77:
#line 896 "parser.y"
              { (yyval.op) = ADD; }
#line 2591 "parser.tab.c"
    break;

  case 78:
#line 897 "parser.y"
                { (yyval.op) = MINUS; }
#line 2597 "parser.tab.c"
    break;

  case 79:
#line 901 "parser.y"
                 { (yyval.op) = DIVIDE; }
#line 2603 "parser.tab.c"
    break;

  case 80:
#line 902 "parser.y"
                   { (yyval.op) = MULTIPLY; }
#line 2609 "parser.tab.c"
    break;


#line 2613 "parser.tab.c"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 911 "parser.y"

void initSymTab(){
    hash = createHashTable();
    printf("Hash Table Created Successfully\n");
}
