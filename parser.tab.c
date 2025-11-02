/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 ".\\parser.y"

    #include<stdio.h>
    #include<string.h>
    #include<stdlib.h>
    #include<ctype.h>
    #include"lex.yy.c"
	struct node { 
		struct node *left; 
		struct node *right; 
		char *token; 
	};

    void yyerror(const char *s);
    int yylex();
    int yywrap();
    void add(char);
    void add_array(char*, int);
    void add_variable(char*);
    void insert_type();
    int search(char *);
	void print_tree(struct node*);
	void print_tree_util(struct node*, int);
	void print_inorder(struct node *);
    void check_declaration(char *);
	void check_is_array(char *);
	void check_return_type(char *);
	int check_types(char *, char *);
	char *get_type(char *);
	struct node* mknode(struct node *left, struct node *right, char *token);

    struct dataType {
        char * id_name;
        char * data_type;
        char * type;
        int line_no;
		int size;
	} symbol_table[40];

    int count=0;
    int q;
	char type[10];
    extern int countn;
	struct node *head;
	int sem_errors=0;
	int ic_idx=0;
	int temp_var=0;
	int label=0;
	int is_for=0;
	char buff[100];
	char errors[10][100];
	char reserved[11][10] = {"int", "float", "char", "void", "if", "else", "for", "while", "main", "return", "include"};
	char icg[1000000][100];



#line 127 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LBRACK = 3,                     /* LBRACK  */
  YYSYMBOL_RBRACK = 4,                     /* RBRACK  */
  YYSYMBOL_VOID = 5,                       /* VOID  */
  YYSYMBOL_CHARACTER = 6,                  /* CHARACTER  */
  YYSYMBOL_PRINTFF = 7,                    /* PRINTFF  */
  YYSYMBOL_SCANFF = 8,                     /* SCANFF  */
  YYSYMBOL_INT = 9,                        /* INT  */
  YYSYMBOL_FLOAT = 10,                     /* FLOAT  */
  YYSYMBOL_CHAR = 11,                      /* CHAR  */
  YYSYMBOL_FOR = 12,                       /* FOR  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_IF = 14,                        /* IF  */
  YYSYMBOL_ELSE = 15,                      /* ELSE  */
  YYSYMBOL_TRUE = 16,                      /* TRUE  */
  YYSYMBOL_FALSE = 17,                     /* FALSE  */
  YYSYMBOL_NUMBER = 18,                    /* NUMBER  */
  YYSYMBOL_FLOAT_NUM = 19,                 /* FLOAT_NUM  */
  YYSYMBOL_ID = 20,                        /* ID  */
  YYSYMBOL_LE = 21,                        /* LE  */
  YYSYMBOL_GE = 22,                        /* GE  */
  YYSYMBOL_EQ = 23,                        /* EQ  */
  YYSYMBOL_NE = 24,                        /* NE  */
  YYSYMBOL_GT = 25,                        /* GT  */
  YYSYMBOL_LT = 26,                        /* LT  */
  YYSYMBOL_AND = 27,                       /* AND  */
  YYSYMBOL_OR = 28,                        /* OR  */
  YYSYMBOL_STR = 29,                       /* STR  */
  YYSYMBOL_ADD = 30,                       /* ADD  */
  YYSYMBOL_MULTIPLY = 31,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 32,                    /* DIVIDE  */
  YYSYMBOL_SUBTRACT = 33,                  /* SUBTRACT  */
  YYSYMBOL_MODULO = 34,                    /* MODULO  */
  YYSYMBOL_UNARY = 35,                     /* UNARY  */
  YYSYMBOL_INCLUDE = 36,                   /* INCLUDE  */
  YYSYMBOL_RETURN = 37,                    /* RETURN  */
  YYSYMBOL_38_ = 38,                       /* '('  */
  YYSYMBOL_39_ = 39,                       /* ')'  */
  YYSYMBOL_40_ = 40,                       /* '{'  */
  YYSYMBOL_41_ = 41,                       /* '}'  */
  YYSYMBOL_42_ = 42,                       /* ';'  */
  YYSYMBOL_43_ = 43,                       /* ','  */
  YYSYMBOL_44_ = 44,                       /* '&'  */
  YYSYMBOL_45_ = 45,                       /* '='  */
  YYSYMBOL_YYACCEPT = 46,                  /* $accept  */
  YYSYMBOL_program = 47,                   /* program  */
  YYSYMBOL_headers = 48,                   /* headers  */
  YYSYMBOL_49_1 = 49,                      /* $@1  */
  YYSYMBOL_main = 50,                      /* main  */
  YYSYMBOL_datatype = 51,                  /* datatype  */
  YYSYMBOL_body = 52,                      /* body  */
  YYSYMBOL_stmt_list = 53,                 /* stmt_list  */
  YYSYMBOL_stmt_item = 54,                 /* stmt_item  */
  YYSYMBOL_55_2 = 55,                      /* $@2  */
  YYSYMBOL_56_3 = 56,                      /* $@3  */
  YYSYMBOL_57_4 = 57,                      /* $@4  */
  YYSYMBOL_58_5 = 58,                      /* $@5  */
  YYSYMBOL_59_6 = 59,                      /* $@6  */
  YYSYMBOL_60_7 = 60,                      /* $@7  */
  YYSYMBOL_61_8 = 61,                      /* $@8  */
  YYSYMBOL_else = 62,                      /* else  */
  YYSYMBOL_63_9 = 63,                      /* $@9  */
  YYSYMBOL_condition = 64,                 /* condition  */
  YYSYMBOL_statement = 65,                 /* statement  */
  YYSYMBOL_66_10 = 66,                     /* $@10  */
  YYSYMBOL_67_11 = 67,                     /* $@11  */
  YYSYMBOL_init = 68,                      /* init  */
  YYSYMBOL_expression = 69,                /* expression  */
  YYSYMBOL_relop = 70,                     /* relop  */
  YYSYMBOL_variable = 71,                  /* variable  */
  YYSYMBOL_value = 72,                     /* value  */
  YYSYMBOL_return = 73,                    /* return  */
  YYSYMBOL_74_12 = 74                      /* $@12  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_uint8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   159

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  132

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   292


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    44,     2,
      38,    39,     2,     2,    43,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    42,
       2,    45,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,     2,     2,     2,     2,
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
      35,    36,    37
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    92,    92,    97,    98,    98,   101,   104,   105,   106,
     107,   110,   111,   114,   115,   118,   118,   126,   126,   131,
     131,   131,   131,   136,   137,   137,   138,   138,   141,   141,
     142,   145,   192,   223,   224,   225,   228,   266,   273,   306,
     306,   307,   307,   320,   336,   337,   340,   415,   490,   565,
     640,   715,   716,   725,   726,   727,   728,   729,   730,   733,
     739,   749,   750,   751,   752,   759,   759,   760
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "LBRACK", "RBRACK",
  "VOID", "CHARACTER", "PRINTFF", "SCANFF", "INT", "FLOAT", "CHAR", "FOR",
  "WHILE", "IF", "ELSE", "TRUE", "FALSE", "NUMBER", "FLOAT_NUM", "ID",
  "LE", "GE", "EQ", "NE", "GT", "LT", "AND", "OR", "STR", "ADD",
  "MULTIPLY", "DIVIDE", "SUBTRACT", "MODULO", "UNARY", "INCLUDE", "RETURN",
  "'('", "')'", "'{'", "'}'", "';'", "','", "'&'", "'='", "$accept",
  "program", "headers", "$@1", "main", "datatype", "body", "stmt_list",
  "stmt_item", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "else",
  "$@9", "condition", "statement", "$@10", "$@11", "init", "expression",
  "relop", "variable", "value", "return", "$@12", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-74)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-60)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -13,   -74,    33,    19,   -74,   -74,   -74,   -74,   -74,   -74,
     -13,    -4,    22,     4,   -74,     5,    60,   -74,   -74,   -74,
     -74,   -74,     2,    24,    37,    21,    60,   -74,    18,    16,
      26,    38,    39,    41,    43,     1,   107,    27,   -74,     3,
     -74,    34,   -74,   -74,     1,    61,    62,    73,    -2,    -2,
     -74,   -74,   -74,    91,     1,    55,   -74,   -74,   -74,   -74,
     -74,   -74,   -74,   -74,     1,   -74,    79,     7,   -74,     7,
     -74,   104,    66,    56,    65,   -74,   -74,    71,    93,    72,
      70,   -74,     1,     1,     1,     1,     1,   104,   108,   -74,
      78,    80,    77,    -2,    99,     1,   -74,   -74,   -23,   -74,
     -74,   -23,   -74,   -74,   -74,   -74,   120,   100,    60,   104,
     101,   105,    73,   102,    60,   103,   109,   -74,   106,   -74,
     110,   -74,    60,   131,   111,   -74,   -74,   -74,   113,    60,
     114,   -74
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     4,     0,     0,     5,     1,    10,     7,     8,     9,
       3,     0,     0,     0,     6,     0,    12,    24,    26,    15,
      17,    19,    39,     0,     0,    67,    11,    14,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    43,    45,
      65,     0,    13,    23,     0,     0,     0,     0,    35,    35,
      63,    61,    62,    59,     0,     0,    64,    51,    55,    56,
      57,    58,    54,    53,     0,    42,     0,     0,    36,     0,
       2,    38,     0,     0,     0,    33,    34,     0,    32,     0,
       0,    60,     0,     0,     0,     0,     0,    40,     0,    44,
       0,     0,     0,    35,     0,     0,    20,    52,    46,    48,
      49,    47,    50,    37,    66,    25,     0,     0,    12,    31,
       0,     0,     0,     0,    12,     0,     0,    18,     0,    27,
       0,    21,    12,    30,     0,    28,    22,    16,     0,    12,
       0,    29
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -74,   -74,   149,   -74,   -74,   148,   -73,   -74,   128,   -74,
     -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -47,   -46,
     -74,   -74,   -74,   -32,    81,   -16,   -29,   -74,   -74
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,    10,     4,    11,    24,    25,    26,    27,    32,
      33,    34,   110,   123,    30,    31,   126,   128,    77,    28,
      36,    37,    68,    78,    64,    56,    57,    41,    69
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,    74,    79,    55,    50,    35,    66,    50,    83,    84,
      29,    86,    71,    50,    75,    76,    51,    52,    53,    51,
      52,    53,    80,     1,     6,    51,    52,    53,     7,     8,
       9,    29,    87,     5,    13,   113,    54,   -41,    89,    54,
      90,   118,    14,    15,    38,    16,   107,   -59,    67,   124,
      98,    99,   100,   101,   102,     1,   130,    39,    40,    81,
      43,    44,    65,   109,    45,     6,   116,    17,    18,     7,
       8,     9,    19,    20,    21,    70,    46,    47,     6,    48,
      22,    49,     7,     8,     9,    82,    83,    84,    85,    86,
      72,    73,    29,    22,    35,    23,    29,    88,    29,    92,
      82,    83,    84,    85,    86,    91,    29,    93,    23,    97,
      94,    96,   103,    29,    58,    59,    60,    61,    62,    63,
     104,   106,   105,    82,    83,    84,    85,    86,    58,    59,
      60,    61,    62,    63,    82,    83,    84,    85,    86,   108,
     111,   114,   112,   117,   115,   119,   125,   121,   120,     3,
     122,    12,   127,   129,    42,   131,     0,     0,     0,    95
};

static const yytype_int16 yycheck[] =
{
      16,    47,    49,    35,     6,     3,     3,     6,    31,    32,
      26,    34,    44,     6,    16,    17,    18,    19,    20,    18,
      19,    20,    54,    36,     5,    18,    19,    20,     9,    10,
      11,    47,    64,     0,    38,   108,    38,    35,    67,    38,
      69,   114,    20,    39,    20,    40,    93,    45,    45,   122,
      82,    83,    84,    85,    86,    36,   129,    20,    37,     4,
      42,    45,    35,    95,    38,     5,   112,     7,     8,     9,
      10,    11,    12,    13,    14,    41,    38,    38,     5,    38,
      20,    38,     9,    10,    11,    30,    31,    32,    33,    34,
      29,    29,   108,    20,     3,    35,   112,    18,   114,    43,
      30,    31,    32,    33,    34,    39,   122,    42,    35,    39,
      39,    39,     4,   129,    21,    22,    23,    24,    25,    26,
      42,    44,    42,    30,    31,    32,    33,    34,    21,    22,
      23,    24,    25,    26,    30,    31,    32,    33,    34,    40,
      20,    40,    42,    41,    39,    42,    15,    41,    39,     0,
      40,     3,    41,    40,    26,    41,    -1,    -1,    -1,    78
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    36,    47,    48,    49,     0,     5,     9,    10,    11,
      48,    50,    51,    38,    20,    39,    40,     7,     8,    12,
      13,    14,    20,    35,    51,    52,    53,    54,    65,    71,
      60,    61,    55,    56,    57,     3,    66,    67,    20,    20,
      37,    73,    54,    42,    45,    38,    38,    38,    38,    38,
       6,    18,    19,    20,    38,    69,    71,    72,    21,    22,
      23,    24,    25,    26,    70,    35,     3,    45,    68,    74,
      41,    69,    29,    29,    65,    16,    17,    64,    69,    64,
      69,     4,    30,    31,    32,    33,    34,    69,    18,    72,
      72,    39,    43,    42,    39,    70,    39,    39,    69,    69,
      69,    69,    69,     4,    42,    42,    44,    64,    40,    69,
      58,    20,    42,    52,    40,    39,    65,    41,    52,    42,
      39,    41,    40,    59,    52,    15,    62,    41,    63,    40,
      52,    41
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    46,    47,    48,    49,    48,    50,    51,    51,    51,
      51,    52,    52,    53,    53,    55,    54,    56,    54,    57,
      58,    59,    54,    54,    60,    54,    61,    54,    63,    62,
      62,    64,    64,    64,    64,    64,    65,    65,    65,    66,
      65,    67,    65,    65,    68,    68,    69,    69,    69,    69,
      69,    69,    69,    70,    70,    70,    70,    70,    70,    71,
      71,    72,    72,    72,    72,    74,    73,    73
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     8,     2,     0,     2,     2,     1,     1,     1,
       1,     1,     0,     2,     1,     0,    12,     0,     8,     0,
       0,     0,    11,     2,     0,     6,     0,     9,     0,     5,
       0,     3,     1,     1,     1,     0,     3,     5,     3,     0,
       4,     0,     3,     2,     2,     0,     3,     3,     3,     3,
       3,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       4,     1,     1,     1,     1,     0,     4,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* program: headers main '(' ')' '{' body return '}'  */
#line 92 ".\\parser.y"
                                                  { (yyvsp[-6].nd_obj).nd = mknode((yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj).nd, "main"); (yyval.nd_obj).nd = mknode((yyvsp[-7].nd_obj).nd, (yyvsp[-6].nd_obj).nd, "program"); 
	head = (yyval.nd_obj).nd;
}
#line 1279 "parser.tab.c"
    break;

  case 3: /* headers: headers headers  */
#line 97 ".\\parser.y"
                         { (yyval.nd_obj).nd = mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, "headers"); }
#line 1285 "parser.tab.c"
    break;

  case 4: /* $@1: %empty  */
#line 98 ".\\parser.y"
          { add('H'); }
#line 1291 "parser.tab.c"
    break;

  case 5: /* headers: INCLUDE $@1  */
#line 98 ".\\parser.y"
                        { (yyval.nd_obj).nd = mknode(NULL, NULL, (yyvsp[-1].nd_obj).name); }
#line 1297 "parser.tab.c"
    break;

  case 6: /* main: datatype ID  */
#line 101 ".\\parser.y"
                  { add('F'); }
#line 1303 "parser.tab.c"
    break;

  case 7: /* datatype: INT  */
#line 104 ".\\parser.y"
              { strcpy(type, (yyvsp[0].nd_obj).name); }
#line 1309 "parser.tab.c"
    break;

  case 8: /* datatype: FLOAT  */
#line 105 ".\\parser.y"
        { strcpy(type, (yyvsp[0].nd_obj).name); }
#line 1315 "parser.tab.c"
    break;

  case 9: /* datatype: CHAR  */
#line 106 ".\\parser.y"
       { strcpy(type, (yyvsp[0].nd_obj).name); }
#line 1321 "parser.tab.c"
    break;

  case 10: /* datatype: VOID  */
#line 107 ".\\parser.y"
       { strcpy(type, (yyvsp[0].nd_obj).name); }
#line 1327 "parser.tab.c"
    break;

  case 11: /* body: stmt_list  */
#line 110 ".\\parser.y"
                { (yyval.nd_obj).nd = (yyvsp[0].nd_obj).nd; }
#line 1333 "parser.tab.c"
    break;

  case 12: /* body: %empty  */
#line 111 ".\\parser.y"
         { (yyval.nd_obj).nd = NULL; }
#line 1339 "parser.tab.c"
    break;

  case 13: /* stmt_list: stmt_list stmt_item  */
#line 114 ".\\parser.y"
                               { (yyval.nd_obj).nd = mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, "statements"); }
#line 1345 "parser.tab.c"
    break;

  case 14: /* stmt_list: stmt_item  */
#line 115 ".\\parser.y"
            { (yyval.nd_obj).nd = (yyvsp[0].nd_obj).nd; }
#line 1351 "parser.tab.c"
    break;

  case 15: /* $@2: %empty  */
#line 118 ".\\parser.y"
               { add('K'); is_for = 1; }
#line 1357 "parser.tab.c"
    break;

  case 16: /* stmt_item: FOR $@2 '(' statement ';' condition ';' statement ')' '{' body '}'  */
#line 118 ".\\parser.y"
                                                                                                    { 
	struct node *temp = mknode((yyvsp[-6].nd_obj3).nd, (yyvsp[-4].nd_obj).nd, "CONDITION"); 
	struct node *temp2 = mknode((yyvsp[-8].nd_obj).nd, temp, "CONDITION"); 
	(yyval.nd_obj).nd = mknode(temp2, (yyvsp[-1].nd_obj).nd, (yyvsp[-11].nd_obj).name); 
	sprintf(icg[ic_idx++], buff);
	sprintf(icg[ic_idx++], "JUMP to %s\n", (yyvsp[-6].nd_obj3).if_body);
	sprintf(icg[ic_idx++], "\nLABEL %s:\n", (yyvsp[-6].nd_obj3).else_body);
}
#line 1370 "parser.tab.c"
    break;

  case 17: /* $@3: %empty  */
#line 126 ".\\parser.y"
        { add('K'); is_for = 1; }
#line 1376 "parser.tab.c"
    break;

  case 18: /* stmt_item: WHILE $@3 '(' condition ')' '{' body '}'  */
#line 126 ".\\parser.y"
                                                                 { 
	(yyval.nd_obj).nd = mknode((yyvsp[-4].nd_obj3).nd, (yyvsp[-1].nd_obj).nd, (yyvsp[-7].nd_obj).name); 
	sprintf(icg[ic_idx++], "JUMP to %s\n", (yyvsp[-4].nd_obj3).if_body);
	sprintf(icg[ic_idx++], "\nLABEL %s:\n", (yyvsp[-4].nd_obj3).else_body);
}
#line 1386 "parser.tab.c"
    break;

  case 19: /* $@4: %empty  */
#line 131 ".\\parser.y"
     { add('K'); is_for = 0; }
#line 1392 "parser.tab.c"
    break;

  case 20: /* $@5: %empty  */
#line 131 ".\\parser.y"
                                                 { sprintf(icg[ic_idx++], "\nLABEL %s:\n", (yyvsp[-1].nd_obj3).if_body); }
#line 1398 "parser.tab.c"
    break;

  case 21: /* $@6: %empty  */
#line 131 ".\\parser.y"
                                                                                                                       { sprintf(icg[ic_idx++], "GOTO L%d\n", label); sprintf(icg[ic_idx++], "\nLABEL %s:\n", (yyvsp[-5].nd_obj3).else_body); }
#line 1404 "parser.tab.c"
    break;

  case 22: /* stmt_item: IF $@4 '(' condition ')' $@5 '{' body '}' $@6 else  */
#line 131 ".\\parser.y"
                                                                                                                                                                                                                                    { 
	struct node *iff = mknode((yyvsp[-7].nd_obj3).nd, (yyvsp[-3].nd_obj).nd, (yyvsp[-10].nd_obj).name); 
	(yyval.nd_obj).nd = mknode(iff, (yyvsp[0].nd_obj).nd, "if-else"); 
	sprintf(icg[ic_idx++], "\nLABEL L%d:\n", label++);
}
#line 1414 "parser.tab.c"
    break;

  case 23: /* stmt_item: statement ';'  */
#line 136 ".\\parser.y"
                { (yyval.nd_obj).nd = (yyvsp[-1].nd_obj).nd; }
#line 1420 "parser.tab.c"
    break;

  case 24: /* $@7: %empty  */
#line 137 ".\\parser.y"
          { add('K'); }
#line 1426 "parser.tab.c"
    break;

  case 25: /* stmt_item: PRINTFF $@7 '(' STR ')' ';'  */
#line 137 ".\\parser.y"
                                        { (yyval.nd_obj).nd = mknode(NULL, NULL, "printf"); }
#line 1432 "parser.tab.c"
    break;

  case 26: /* $@8: %empty  */
#line 138 ".\\parser.y"
         { add('K'); }
#line 1438 "parser.tab.c"
    break;

  case 27: /* stmt_item: SCANFF $@8 '(' STR ',' '&' ID ')' ';'  */
#line 138 ".\\parser.y"
                                                  { (yyval.nd_obj).nd = mknode(NULL, NULL, "scanf"); }
#line 1444 "parser.tab.c"
    break;

  case 28: /* $@9: %empty  */
#line 141 ".\\parser.y"
           { add('K'); }
#line 1450 "parser.tab.c"
    break;

  case 29: /* else: ELSE $@9 '{' body '}'  */
#line 141 ".\\parser.y"
                                      { (yyval.nd_obj).nd = mknode(NULL, (yyvsp[-1].nd_obj).nd, (yyvsp[-4].nd_obj).name); }
#line 1456 "parser.tab.c"
    break;

  case 30: /* else: %empty  */
#line 142 ".\\parser.y"
         { (yyval.nd_obj).nd = NULL; }
#line 1462 "parser.tab.c"
    break;

  case 31: /* condition: expression relop expression  */
#line 145 ".\\parser.y"
                                       { 
	(yyval.nd_obj3).nd = mknode((yyvsp[-2].nd_obj2).nd, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).name); 
	
	// Handle array access in left operand
	char left_operand[100], right_operand[100];
	if(strstr((yyvsp[-2].nd_obj2).name, "[") != NULL && strstr((yyvsp[-2].nd_obj2).name, "]") != NULL) {
		char array_name[100], index_name[100];
		sscanf((yyvsp[-2].nd_obj2).name, "%[^[][%[^]]", array_name, index_name);
		sprintf(icg[ic_idx++], "t%d = %s * 4\n", temp_var, index_name);
		int offset_temp1 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = &%s\n", temp_var, array_name);
		int base_temp1 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = t%d + t%d\n", temp_var, base_temp1, offset_temp1);
		int addr_temp1 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = *t%d\n", temp_var, addr_temp1);
		sprintf(left_operand, "t%d", temp_var++);
	} else {
		strcpy(left_operand, (yyvsp[-2].nd_obj2).name);
	}
	
	// Handle array access in right operand
	if(strstr((yyvsp[0].nd_obj2).name, "[") != NULL && strstr((yyvsp[0].nd_obj2).name, "]") != NULL) {
		char array_name[100], index_name[100];
		sscanf((yyvsp[0].nd_obj2).name, "%[^[][%[^]]", array_name, index_name);
		sprintf(icg[ic_idx++], "t%d = %s * 4\n", temp_var, index_name);
		int offset_temp2 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = &%s\n", temp_var, array_name);
		int base_temp2 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = t%d + t%d\n", temp_var, base_temp2, offset_temp2);
		int addr_temp2 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = *t%d\n", temp_var, addr_temp2);
		sprintf(right_operand, "t%d", temp_var++);
	} else {
		strcpy(right_operand, (yyvsp[0].nd_obj2).name);
	}
	
	if(is_for) {
		sprintf((yyval.nd_obj3).if_body, "L%d", label++);
		sprintf(icg[ic_idx++], "\nLABEL %s:\n", (yyval.nd_obj3).if_body);
		sprintf(icg[ic_idx++], "\nif NOT (%s %s %s) GOTO L%d\n", left_operand, (yyvsp[-1].nd_obj).name, right_operand, label);
		sprintf((yyval.nd_obj3).else_body, "L%d", label++);
	} else {
		sprintf(icg[ic_idx++], "\nif (%s %s %s) GOTO L%d else GOTO L%d\n", left_operand, (yyvsp[-1].nd_obj).name, right_operand, label, label+1);
		sprintf((yyval.nd_obj3).if_body, "L%d", label++);
		sprintf((yyval.nd_obj3).else_body, "L%d", label++);
	}
}
#line 1514 "parser.tab.c"
    break;

  case 32: /* condition: expression  */
#line 192 ".\\parser.y"
             {
	(yyval.nd_obj3).nd = mknode(NULL, NULL, (yyvsp[0].nd_obj2).name);
	
	// Handle array access in single expression condition
	char operand[100];
	if(strstr((yyvsp[0].nd_obj2).name, "[") != NULL && strstr((yyvsp[0].nd_obj2).name, "]") != NULL) {
		char array_name[100], index_name[100];
		sscanf((yyvsp[0].nd_obj2).name, "%[^[][%[^]]", array_name, index_name);
		sprintf(icg[ic_idx++], "t%d = %s * 4\n", temp_var, index_name);
		int offset_temp = temp_var++;
		sprintf(icg[ic_idx++], "t%d = &%s\n", temp_var, array_name);
		int base_temp = temp_var++;
		sprintf(icg[ic_idx++], "t%d = t%d + t%d\n", temp_var, base_temp, offset_temp);
		int addr_temp = temp_var++;
		sprintf(icg[ic_idx++], "t%d = *t%d\n", temp_var, addr_temp);
		sprintf(operand, "t%d", temp_var++);
	} else {
		strcpy(operand, (yyvsp[0].nd_obj2).name);
	}
	
	if(is_for) {
		sprintf((yyval.nd_obj3).if_body, "L%d", label++);
		sprintf(icg[ic_idx++], "\nLABEL %s:\n", (yyval.nd_obj3).if_body);
		sprintf(icg[ic_idx++], "\nif NOT (%s) GOTO L%d\n", operand, label);
		sprintf((yyval.nd_obj3).else_body, "L%d", label++);
	} else {
		sprintf(icg[ic_idx++], "\nif (%s) GOTO L%d else GOTO L%d\n", operand, label, label+1);
		sprintf((yyval.nd_obj3).if_body, "L%d", label++);
		sprintf((yyval.nd_obj3).else_body, "L%d", label++);
	}
}
#line 1550 "parser.tab.c"
    break;

  case 33: /* condition: TRUE  */
#line 223 ".\\parser.y"
       { add('K'); (yyval.nd_obj3).nd = NULL; }
#line 1556 "parser.tab.c"
    break;

  case 34: /* condition: FALSE  */
#line 224 ".\\parser.y"
        { add('K'); (yyval.nd_obj3).nd = NULL; }
#line 1562 "parser.tab.c"
    break;

  case 35: /* condition: %empty  */
#line 225 ".\\parser.y"
         { (yyval.nd_obj3).nd = NULL; }
#line 1568 "parser.tab.c"
    break;

  case 36: /* statement: datatype ID init  */
#line 228 ".\\parser.y"
                            { 
	add_variable((yyvsp[-1].nd_obj).name);
	(yyvsp[-1].nd_obj).nd = mknode(NULL, NULL, (yyvsp[-1].nd_obj).name); 
	int t = check_types((yyvsp[-2].nd_obj).name, (yyvsp[0].nd_obj2).type); 
	if(t>0) { 
		if(t == 1) {
			struct node *temp = mknode(NULL, (yyvsp[0].nd_obj2).nd, "floattoint"); 
			(yyval.nd_obj).nd = mknode((yyvsp[-1].nd_obj).nd, temp, "declaration"); 
		} 
		else if(t == 2) { 
			struct node *temp = mknode(NULL, (yyvsp[0].nd_obj2).nd, "inttofloat"); 
			(yyval.nd_obj).nd = mknode((yyvsp[-1].nd_obj).nd, temp, "declaration"); 
		} 
		else if(t == 3) { 
			struct node *temp = mknode(NULL, (yyvsp[0].nd_obj2).nd, "chartoint"); 
			(yyval.nd_obj).nd = mknode((yyvsp[-1].nd_obj).nd, temp, "declaration"); 
		} 
		else if(t == 4) { 
			struct node *temp = mknode(NULL, (yyvsp[0].nd_obj2).nd, "inttochar"); 
			(yyval.nd_obj).nd = mknode((yyvsp[-1].nd_obj).nd, temp, "declaration"); 
		} 
		else if(t == 5) { 
			struct node *temp = mknode(NULL, (yyvsp[0].nd_obj2).nd, "chartofloat"); 
			(yyval.nd_obj).nd = mknode((yyvsp[-1].nd_obj).nd, temp, "declaration"); 
		} 
		else{
			struct node *temp = mknode(NULL, (yyvsp[0].nd_obj2).nd, "floattochar"); 
			(yyval.nd_obj).nd = mknode((yyvsp[-1].nd_obj).nd, temp, "declaration"); 
		}
	} 
	else { 
		(yyval.nd_obj).nd = mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj2).nd, "declaration"); 
	} 
	// Only generate IR for actual initialization, not for NULL (uninitialized)
	if(strcmp((yyvsp[0].nd_obj2).name, "NULL") != 0) {
		sprintf(icg[ic_idx++], "%s = %s\n", (yyvsp[-1].nd_obj).name, (yyvsp[0].nd_obj2).name);
	}
}
#line 1611 "parser.tab.c"
    break;

  case 37: /* statement: datatype ID LBRACK NUMBER RBRACK  */
#line 266 ".\\parser.y"
                                   { 
	add_array((yyvsp[-3].nd_obj).name, atoi((yyvsp[-1].nd_obj).name)); 
	struct node* size_node = mknode(NULL, NULL, (yyvsp[-1].nd_obj).name);
	struct node* id_node = mknode(NULL, NULL, (yyvsp[-3].nd_obj).name);
	(yyval.nd_obj).nd = mknode(id_node, size_node, "ARRAY_DECL");
	sprintf(icg[ic_idx++], "alloc %s, %d\n", (yyvsp[-3].nd_obj).name, atoi((yyvsp[-1].nd_obj).name) * 4); 
}
#line 1623 "parser.tab.c"
    break;

  case 38: /* statement: variable '=' expression  */
#line 273 ".\\parser.y"
                          { 
	(yyval.nd_obj).nd = mknode((yyvsp[-2].nd_obj2).nd, (yyvsp[0].nd_obj2).nd, "=");
    
    if(strstr((yyvsp[-2].nd_obj2).name, "[") != NULL && strstr((yyvsp[-2].nd_obj2).name, "]") != NULL) {
        char array_name[100], index_name[100];
        sscanf((yyvsp[-2].nd_obj2).name, "%[^[][%[^]]", array_name, index_name);
        
        sprintf(icg[ic_idx++], "t%d = %s * 4\n", temp_var, index_name);
        int offset_temp = temp_var++;
        sprintf(icg[ic_idx++], "t%d = &%s\n", temp_var, array_name);
        int base_temp = temp_var++;
        sprintf(icg[ic_idx++], "t%d = t%d + t%d\n", temp_var, base_temp, offset_temp);
        int addr_temp = temp_var++;
        sprintf(icg[ic_idx++], "*t%d = %s\n", addr_temp, (yyvsp[0].nd_obj2).name);
    } else {
        if(strstr((yyvsp[0].nd_obj2).name, "[") != NULL && strstr((yyvsp[0].nd_obj2).name, "]") != NULL) {
            char array_name[100], index_name[100];
            sscanf((yyvsp[0].nd_obj2).name, "%[^[][%[^]]", array_name, index_name);
            
            sprintf(icg[ic_idx++], "t%d = %s * 4\n", temp_var, index_name);
            int offset_temp = temp_var++;
            sprintf(icg[ic_idx++], "t%d = &%s\n", temp_var, array_name);
            int base_temp = temp_var++;
            sprintf(icg[ic_idx++], "t%d = t%d + t%d\n", temp_var, base_temp, offset_temp);
            int addr_temp = temp_var++;
            sprintf(icg[ic_idx++], "t%d = *t%d\n", temp_var, addr_temp);
            int value_temp = temp_var++;
            sprintf(icg[ic_idx++], "%s = t%d\n", (yyvsp[-2].nd_obj2).name, value_temp);
        } else {
            sprintf(icg[ic_idx++], "%s = %s\n", (yyvsp[-2].nd_obj2).name, (yyvsp[0].nd_obj2).name);
        }
    }
}
#line 1661 "parser.tab.c"
    break;

  case 39: /* $@10: %empty  */
#line 306 ".\\parser.y"
     { check_declaration((yyvsp[0].nd_obj).name); }
#line 1667 "parser.tab.c"
    break;

  case 40: /* statement: ID $@10 relop expression  */
#line 306 ".\\parser.y"
                                                      { (yyvsp[-3].nd_obj).nd = mknode(NULL, NULL, (yyvsp[-3].nd_obj).name); (yyval.nd_obj).nd = mknode((yyvsp[-3].nd_obj).nd, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).name); }
#line 1673 "parser.tab.c"
    break;

  case 41: /* $@11: %empty  */
#line 307 ".\\parser.y"
     { check_declaration((yyvsp[0].nd_obj).name); }
#line 1679 "parser.tab.c"
    break;

  case 42: /* statement: ID $@11 UNARY  */
#line 307 ".\\parser.y"
                                           { 
	(yyvsp[-2].nd_obj).nd = mknode(NULL, NULL, (yyvsp[-2].nd_obj).name); 
	(yyvsp[0].nd_obj).nd = mknode(NULL, NULL, (yyvsp[0].nd_obj).name); 
	(yyval.nd_obj).nd = mknode((yyvsp[-2].nd_obj).nd, (yyvsp[0].nd_obj).nd, "ITERATOR");  
	if(!strcmp((yyvsp[0].nd_obj).name, "++")) {
		sprintf(buff, "t%d = %s + 1\n%s = t%d\n", temp_var, (yyvsp[-2].nd_obj).name, (yyvsp[-2].nd_obj).name, temp_var);
		temp_var++;
	}
	else {
		sprintf(buff, "t%d = %s - 1\n%s = t%d\n", temp_var, (yyvsp[-2].nd_obj).name, (yyvsp[-2].nd_obj).name, temp_var);
		temp_var++;
	}
}
#line 1697 "parser.tab.c"
    break;

  case 43: /* statement: UNARY ID  */
#line 320 ".\\parser.y"
           { 
	check_declaration((yyvsp[0].nd_obj).name); 
	(yyvsp[-1].nd_obj).nd = mknode(NULL, NULL, (yyvsp[-1].nd_obj).name); 
	(yyvsp[0].nd_obj).nd = mknode(NULL, NULL, (yyvsp[0].nd_obj).name); 
	(yyval.nd_obj).nd = mknode((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, "ITERATOR"); 
	if(!strcmp((yyvsp[-1].nd_obj).name, "++")) {
		sprintf(buff, "t%d = %s + 1\n%s = t%d\n", temp_var, (yyvsp[0].nd_obj).name, (yyvsp[0].nd_obj).name, temp_var);
		temp_var++;
	}
	else {
		sprintf(buff, "t%d = %s - 1\n%s = t%d\n", temp_var, (yyvsp[0].nd_obj).name, (yyvsp[0].nd_obj).name, temp_var);
		temp_var++;
	}
}
#line 1716 "parser.tab.c"
    break;

  case 44: /* init: '=' value  */
#line 336 ".\\parser.y"
                { (yyval.nd_obj2).nd = (yyvsp[0].nd_obj2).nd; sprintf((yyval.nd_obj2).type, (yyvsp[0].nd_obj2).type); strcpy((yyval.nd_obj2).name, (yyvsp[0].nd_obj2).name); }
#line 1722 "parser.tab.c"
    break;

  case 45: /* init: %empty  */
#line 337 ".\\parser.y"
         { sprintf((yyval.nd_obj2).type, "null"); (yyval.nd_obj2).nd = mknode(NULL, NULL, "NULL"); strcpy((yyval.nd_obj2).name, "NULL"); }
#line 1728 "parser.tab.c"
    break;

  case 46: /* expression: expression ADD expression  */
#line 340 ".\\parser.y"
                                                { 
	if(!strcmp((yyvsp[-2].nd_obj2).type, (yyvsp[0].nd_obj2).type)) {
		sprintf((yyval.nd_obj2).type, (yyvsp[-2].nd_obj2).type);
		(yyval.nd_obj2).nd = mknode((yyvsp[-2].nd_obj2).nd, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).name); 
	}
	else {
		if(!strcmp((yyvsp[-2].nd_obj2).type, "int") && !strcmp((yyvsp[0].nd_obj2).type, "float")) {
			struct node *temp = mknode(NULL, (yyvsp[-2].nd_obj2).nd, "inttofloat");
			sprintf((yyval.nd_obj2).type, (yyvsp[0].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode(temp, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).name);
		}
		else if(!strcmp((yyvsp[-2].nd_obj2).type, "float") && !strcmp((yyvsp[0].nd_obj2).type, "int")) {
			struct node *temp = mknode(NULL, (yyvsp[0].nd_obj2).nd, "inttofloat");
			sprintf((yyval.nd_obj2).type, (yyvsp[-2].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode((yyvsp[-2].nd_obj2).nd, temp, (yyvsp[-1].nd_obj).name);
		}
		else if(!strcmp((yyvsp[-2].nd_obj2).type, "int") && !strcmp((yyvsp[0].nd_obj2).type, "char")) {
			struct node *temp = mknode(NULL, (yyvsp[0].nd_obj2).nd, "chartoint");
			sprintf((yyval.nd_obj2).type, (yyvsp[-2].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode((yyvsp[-2].nd_obj2).nd, temp, (yyvsp[-1].nd_obj).name);
		}
		else if(!strcmp((yyvsp[-2].nd_obj2).type, "char") && !strcmp((yyvsp[0].nd_obj2).type, "int")) {
			struct node *temp = mknode(NULL, (yyvsp[-2].nd_obj2).nd, "chartoint");
			sprintf((yyval.nd_obj2).type, (yyvsp[0].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode(temp, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).name);
		}
		else if(!strcmp((yyvsp[-2].nd_obj2).type, "float") && !strcmp((yyvsp[0].nd_obj2).type, "char")) {
			struct node *temp = mknode(NULL, (yyvsp[0].nd_obj2).nd, "chartofloat");
			sprintf((yyval.nd_obj2).type, (yyvsp[-2].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode((yyvsp[-2].nd_obj2).nd, temp, (yyvsp[-1].nd_obj).name);
		}
		else {
			struct node *temp = mknode(NULL, (yyvsp[-2].nd_obj2).nd, "chartofloat");
			sprintf((yyval.nd_obj2).type, (yyvsp[0].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode(temp, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).name);
		}
	}
	sprintf((yyval.nd_obj2).name, "t%d", temp_var);
	temp_var++;
	
	// Handle array access in left operand
	char left_operand[100], right_operand[100];
	if(strstr((yyvsp[-2].nd_obj2).name, "[") != NULL && strstr((yyvsp[-2].nd_obj2).name, "]") != NULL) {
		char array_name[100], index_name[100];
		sscanf((yyvsp[-2].nd_obj2).name, "%[^[][%[^]]", array_name, index_name);
		sprintf(icg[ic_idx++], "t%d = %s * 4\n", temp_var, index_name);
		int offset_temp1 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = &%s\n", temp_var, array_name);
		int base_temp1 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = t%d + t%d\n", temp_var, base_temp1, offset_temp1);
		int addr_temp1 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = *t%d\n", temp_var, addr_temp1);
		sprintf(left_operand, "t%d", temp_var++);
	} else {
		strcpy(left_operand, (yyvsp[-2].nd_obj2).name);
	}
	
	// Handle array access in right operand
	if(strstr((yyvsp[0].nd_obj2).name, "[") != NULL && strstr((yyvsp[0].nd_obj2).name, "]") != NULL) {
		char array_name[100], index_name[100];
		sscanf((yyvsp[0].nd_obj2).name, "%[^[][%[^]]", array_name, index_name);
		sprintf(icg[ic_idx++], "t%d = %s * 4\n", temp_var, index_name);
		int offset_temp2 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = &%s\n", temp_var, array_name);
		int base_temp2 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = t%d + t%d\n", temp_var, base_temp2, offset_temp2);
		int addr_temp2 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = *t%d\n", temp_var, addr_temp2);
		sprintf(right_operand, "t%d", temp_var++);
	} else {
		strcpy(right_operand, (yyvsp[0].nd_obj2).name);
	}
	
	sprintf(icg[ic_idx++], "%s = %s %s %s\n", (yyval.nd_obj2).name, left_operand, "+", right_operand);
}
#line 1808 "parser.tab.c"
    break;

  case 47: /* expression: expression SUBTRACT expression  */
#line 415 ".\\parser.y"
                                                { 
	if(!strcmp((yyvsp[-2].nd_obj2).type, (yyvsp[0].nd_obj2).type)) {
		sprintf((yyval.nd_obj2).type, (yyvsp[-2].nd_obj2).type);
		(yyval.nd_obj2).nd = mknode((yyvsp[-2].nd_obj2).nd, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).name); 
	}
	else {
		if(!strcmp((yyvsp[-2].nd_obj2).type, "int") && !strcmp((yyvsp[0].nd_obj2).type, "float")) {
			struct node *temp = mknode(NULL, (yyvsp[-2].nd_obj2).nd, "inttofloat");
			sprintf((yyval.nd_obj2).type, (yyvsp[0].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode(temp, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).name);
		}
		else if(!strcmp((yyvsp[-2].nd_obj2).type, "float") && !strcmp((yyvsp[0].nd_obj2).type, "int")) {
			struct node *temp = mknode(NULL, (yyvsp[0].nd_obj2).nd, "inttofloat");
			sprintf((yyval.nd_obj2).type, (yyvsp[-2].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode((yyvsp[-2].nd_obj2).nd, temp, (yyvsp[-1].nd_obj).name);
		}
		else if(!strcmp((yyvsp[-2].nd_obj2).type, "int") && !strcmp((yyvsp[0].nd_obj2).type, "char")) {
			struct node *temp = mknode(NULL, (yyvsp[0].nd_obj2).nd, "chartoint");
			sprintf((yyval.nd_obj2).type, (yyvsp[-2].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode((yyvsp[-2].nd_obj2).nd, temp, (yyvsp[-1].nd_obj).name);
		}
		else if(!strcmp((yyvsp[-2].nd_obj2).type, "char") && !strcmp((yyvsp[0].nd_obj2).type, "int")) {
			struct node *temp = mknode(NULL, (yyvsp[-2].nd_obj2).nd, "chartoint");
			sprintf((yyval.nd_obj2).type, (yyvsp[0].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode(temp, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).name);
		}
		else if(!strcmp((yyvsp[-2].nd_obj2).type, "float") && !strcmp((yyvsp[0].nd_obj2).type, "char")) {
			struct node *temp = mknode(NULL, (yyvsp[0].nd_obj2).nd, "chartofloat");
			sprintf((yyval.nd_obj2).type, (yyvsp[-2].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode((yyvsp[-2].nd_obj2).nd, temp, (yyvsp[-1].nd_obj).name);
		}
		else {
			struct node *temp = mknode(NULL, (yyvsp[-2].nd_obj2).nd, "chartofloat");
			sprintf((yyval.nd_obj2).type, (yyvsp[0].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode(temp, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).name);
		}
	}
	sprintf((yyval.nd_obj2).name, "t%d", temp_var);
	temp_var++;
	
	// Handle array access in left operand
	char left_operand[100], right_operand[100];
	if(strstr((yyvsp[-2].nd_obj2).name, "[") != NULL && strstr((yyvsp[-2].nd_obj2).name, "]") != NULL) {
		char array_name[100], index_name[100];
		sscanf((yyvsp[-2].nd_obj2).name, "%[^[][%[^]]", array_name, index_name);
		sprintf(icg[ic_idx++], "t%d = %s * 4\n", temp_var, index_name);
		int offset_temp1 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = &%s\n", temp_var, array_name);
		int base_temp1 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = t%d + t%d\n", temp_var, base_temp1, offset_temp1);
		int addr_temp1 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = *t%d\n", temp_var, addr_temp1);
		sprintf(left_operand, "t%d", temp_var++);
	} else {
		strcpy(left_operand, (yyvsp[-2].nd_obj2).name);
	}
	
	// Handle array access in right operand
	if(strstr((yyvsp[0].nd_obj2).name, "[") != NULL && strstr((yyvsp[0].nd_obj2).name, "]") != NULL) {
		char array_name[100], index_name[100];
		sscanf((yyvsp[0].nd_obj2).name, "%[^[][%[^]]", array_name, index_name);
		sprintf(icg[ic_idx++], "t%d = %s * 4\n", temp_var, index_name);
		int offset_temp2 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = &%s\n", temp_var, array_name);
		int base_temp2 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = t%d + t%d\n", temp_var, base_temp2, offset_temp2);
		int addr_temp2 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = *t%d\n", temp_var, addr_temp2);
		sprintf(right_operand, "t%d", temp_var++);
	} else {
		strcpy(right_operand, (yyvsp[0].nd_obj2).name);
	}
	
	sprintf(icg[ic_idx++], "%s = %s %s %s\n", (yyval.nd_obj2).name, left_operand, "-", right_operand);
}
#line 1888 "parser.tab.c"
    break;

  case 48: /* expression: expression MULTIPLY expression  */
#line 490 ".\\parser.y"
                                                { 
	if(!strcmp((yyvsp[-2].nd_obj2).type, (yyvsp[0].nd_obj2).type)) {
		sprintf((yyval.nd_obj2).type, (yyvsp[-2].nd_obj2).type);
		(yyval.nd_obj2).nd = mknode((yyvsp[-2].nd_obj2).nd, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).name); 
	}
	else {
		if(!strcmp((yyvsp[-2].nd_obj2).type, "int") && !strcmp((yyvsp[0].nd_obj2).type, "float")) {
			struct node *temp = mknode(NULL, (yyvsp[-2].nd_obj2).nd, "inttofloat");
			sprintf((yyval.nd_obj2).type, (yyvsp[0].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode(temp, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).name);
		}
		else if(!strcmp((yyvsp[-2].nd_obj2).type, "float") && !strcmp((yyvsp[0].nd_obj2).type, "int")) {
			struct node *temp = mknode(NULL, (yyvsp[0].nd_obj2).nd, "inttofloat");
			sprintf((yyval.nd_obj2).type, (yyvsp[-2].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode((yyvsp[-2].nd_obj2).nd, temp, (yyvsp[-1].nd_obj).name);
		}
		else if(!strcmp((yyvsp[-2].nd_obj2).type, "int") && !strcmp((yyvsp[0].nd_obj2).type, "char")) {
			struct node *temp = mknode(NULL, (yyvsp[0].nd_obj2).nd, "chartoint");
			sprintf((yyval.nd_obj2).type, (yyvsp[-2].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode((yyvsp[-2].nd_obj2).nd, temp, (yyvsp[-1].nd_obj).name);
		}
		else if(!strcmp((yyvsp[-2].nd_obj2).type, "char") && !strcmp((yyvsp[0].nd_obj2).type, "int")) {
			struct node *temp = mknode(NULL, (yyvsp[-2].nd_obj2).nd, "chartoint");
			sprintf((yyval.nd_obj2).type, (yyvsp[0].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode(temp, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).name);
		}
		else if(!strcmp((yyvsp[-2].nd_obj2).type, "float") && !strcmp((yyvsp[0].nd_obj2).type, "char")) {
			struct node *temp = mknode(NULL, (yyvsp[0].nd_obj2).nd, "chartofloat");
			sprintf((yyval.nd_obj2).type, (yyvsp[-2].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode((yyvsp[-2].nd_obj2).nd, temp, (yyvsp[-1].nd_obj).name);
		}
		else {
			struct node *temp = mknode(NULL, (yyvsp[-2].nd_obj2).nd, "chartofloat");
			sprintf((yyval.nd_obj2).type, (yyvsp[0].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode(temp, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).name);
		}
	}
	sprintf((yyval.nd_obj2).name, "t%d", temp_var);
	temp_var++;
	
	// Handle array access in left operand
	char left_operand[100], right_operand[100];
	if(strstr((yyvsp[-2].nd_obj2).name, "[") != NULL && strstr((yyvsp[-2].nd_obj2).name, "]") != NULL) {
		char array_name[100], index_name[100];
		sscanf((yyvsp[-2].nd_obj2).name, "%[^[][%[^]]", array_name, index_name);
		sprintf(icg[ic_idx++], "t%d = %s * 4\n", temp_var, index_name);
		int offset_temp1 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = &%s\n", temp_var, array_name);
		int base_temp1 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = t%d + t%d\n", temp_var, base_temp1, offset_temp1);
		int addr_temp1 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = *t%d\n", temp_var, addr_temp1);
		sprintf(left_operand, "t%d", temp_var++);
	} else {
		strcpy(left_operand, (yyvsp[-2].nd_obj2).name);
	}
	
	// Handle array access in right operand
	if(strstr((yyvsp[0].nd_obj2).name, "[") != NULL && strstr((yyvsp[0].nd_obj2).name, "]") != NULL) {
		char array_name[100], index_name[100];
		sscanf((yyvsp[0].nd_obj2).name, "%[^[][%[^]]", array_name, index_name);
		sprintf(icg[ic_idx++], "t%d = %s * 4\n", temp_var, index_name);
		int offset_temp2 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = &%s\n", temp_var, array_name);
		int base_temp2 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = t%d + t%d\n", temp_var, base_temp2, offset_temp2);
		int addr_temp2 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = *t%d\n", temp_var, addr_temp2);
		sprintf(right_operand, "t%d", temp_var++);
	} else {
		strcpy(right_operand, (yyvsp[0].nd_obj2).name);
	}
	
	sprintf(icg[ic_idx++], "%s = %s %s %s\n", (yyval.nd_obj2).name, left_operand, "*", right_operand);
}
#line 1968 "parser.tab.c"
    break;

  case 49: /* expression: expression DIVIDE expression  */
#line 565 ".\\parser.y"
                                            { 
	if(!strcmp((yyvsp[-2].nd_obj2).type, (yyvsp[0].nd_obj2).type)) {
		sprintf((yyval.nd_obj2).type, (yyvsp[-2].nd_obj2).type);
		(yyval.nd_obj2).nd = mknode((yyvsp[-2].nd_obj2).nd, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).name); 
	}
	else {
		if(!strcmp((yyvsp[-2].nd_obj2).type, "int") && !strcmp((yyvsp[0].nd_obj2).type, "float")) {
			struct node *temp = mknode(NULL, (yyvsp[-2].nd_obj2).nd, "inttofloat");
			sprintf((yyval.nd_obj2).type, (yyvsp[0].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode(temp, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).name);
		}
		else if(!strcmp((yyvsp[-2].nd_obj2).type, "float") && !strcmp((yyvsp[0].nd_obj2).type, "int")) {
			struct node *temp = mknode(NULL, (yyvsp[0].nd_obj2).nd, "inttofloat");
			sprintf((yyval.nd_obj2).type, (yyvsp[-2].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode((yyvsp[-2].nd_obj2).nd, temp, (yyvsp[-1].nd_obj).name);
		}
		else if(!strcmp((yyvsp[-2].nd_obj2).type, "int") && !strcmp((yyvsp[0].nd_obj2).type, "char")) {
			struct node *temp = mknode(NULL, (yyvsp[0].nd_obj2).nd, "chartoint");
			sprintf((yyval.nd_obj2).type, (yyvsp[-2].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode((yyvsp[-2].nd_obj2).nd, temp, (yyvsp[-1].nd_obj).name);
		}
		else if(!strcmp((yyvsp[-2].nd_obj2).type, "char") && !strcmp((yyvsp[0].nd_obj2).type, "int")) {
			struct node *temp = mknode(NULL, (yyvsp[-2].nd_obj2).nd, "chartoint");
			sprintf((yyval.nd_obj2).type, (yyvsp[0].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode(temp, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).name);
		}
		else if(!strcmp((yyvsp[-2].nd_obj2).type, "float") && !strcmp((yyvsp[0].nd_obj2).type, "char")) {
			struct node *temp = mknode(NULL, (yyvsp[0].nd_obj2).nd, "chartofloat");
			sprintf((yyval.nd_obj2).type, (yyvsp[-2].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode((yyvsp[-2].nd_obj2).nd, temp, (yyvsp[-1].nd_obj).name);
		}
		else {
			struct node *temp = mknode(NULL, (yyvsp[-2].nd_obj2).nd, "chartofloat");
			sprintf((yyval.nd_obj2).type, (yyvsp[0].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode(temp, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).name);
		}
	}
	sprintf((yyval.nd_obj2).name, "t%d", temp_var);
	temp_var++;
	
	// Handle array access in left operand
	char left_operand[100], right_operand[100];
	if(strstr((yyvsp[-2].nd_obj2).name, "[") != NULL && strstr((yyvsp[-2].nd_obj2).name, "]") != NULL) {
		char array_name[100], index_name[100];
		sscanf((yyvsp[-2].nd_obj2).name, "%[^[][%[^]]", array_name, index_name);
		sprintf(icg[ic_idx++], "t%d = %s * 4\n", temp_var, index_name);
		int offset_temp1 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = &%s\n", temp_var, array_name);
		int base_temp1 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = t%d + t%d\n", temp_var, base_temp1, offset_temp1);
		int addr_temp1 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = *t%d\n", temp_var, addr_temp1);
		sprintf(left_operand, "t%d", temp_var++);
	} else {
		strcpy(left_operand, (yyvsp[-2].nd_obj2).name);
	}
	
	// Handle array access in right operand
	if(strstr((yyvsp[0].nd_obj2).name, "[") != NULL && strstr((yyvsp[0].nd_obj2).name, "]") != NULL) {
		char array_name[100], index_name[100];
		sscanf((yyvsp[0].nd_obj2).name, "%[^[][%[^]]", array_name, index_name);
		sprintf(icg[ic_idx++], "t%d = %s * 4\n", temp_var, index_name);
		int offset_temp2 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = &%s\n", temp_var, array_name);
		int base_temp2 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = t%d + t%d\n", temp_var, base_temp2, offset_temp2);
		int addr_temp2 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = *t%d\n", temp_var, addr_temp2);
		sprintf(right_operand, "t%d", temp_var++);
	} else {
		strcpy(right_operand, (yyvsp[0].nd_obj2).name);
	}
	
	sprintf(icg[ic_idx++], "%s = %s %s %s\n", (yyval.nd_obj2).name, left_operand, "/", right_operand);
}
#line 2048 "parser.tab.c"
    break;

  case 50: /* expression: expression MODULO expression  */
#line 640 ".\\parser.y"
                                            { 
	if(!strcmp((yyvsp[-2].nd_obj2).type, (yyvsp[0].nd_obj2).type)) {
		sprintf((yyval.nd_obj2).type, (yyvsp[-2].nd_obj2).type);
		(yyval.nd_obj2).nd = mknode((yyvsp[-2].nd_obj2).nd, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).name); 
	}
	else {
		if(!strcmp((yyvsp[-2].nd_obj2).type, "int") && !strcmp((yyvsp[0].nd_obj2).type, "float")) {
			struct node *temp = mknode(NULL, (yyvsp[-2].nd_obj2).nd, "inttofloat");
			sprintf((yyval.nd_obj2).type, (yyvsp[0].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode(temp, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).name);
		}
		else if(!strcmp((yyvsp[-2].nd_obj2).type, "float") && !strcmp((yyvsp[0].nd_obj2).type, "int")) {
			struct node *temp = mknode(NULL, (yyvsp[0].nd_obj2).nd, "inttofloat");
			sprintf((yyval.nd_obj2).type, (yyvsp[-2].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode((yyvsp[-2].nd_obj2).nd, temp, (yyvsp[-1].nd_obj).name);
		}
		else if(!strcmp((yyvsp[-2].nd_obj2).type, "int") && !strcmp((yyvsp[0].nd_obj2).type, "char")) {
			struct node *temp = mknode(NULL, (yyvsp[0].nd_obj2).nd, "chartoint");
			sprintf((yyval.nd_obj2).type, (yyvsp[-2].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode((yyvsp[-2].nd_obj2).nd, temp, (yyvsp[-1].nd_obj).name);
		}
		else if(!strcmp((yyvsp[-2].nd_obj2).type, "char") && !strcmp((yyvsp[0].nd_obj2).type, "int")) {
			struct node *temp = mknode(NULL, (yyvsp[-2].nd_obj2).nd, "chartoint");
			sprintf((yyval.nd_obj2).type, (yyvsp[0].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode(temp, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).name);
		}
		else if(!strcmp((yyvsp[-2].nd_obj2).type, "float") && !strcmp((yyvsp[0].nd_obj2).type, "char")) {
			struct node *temp = mknode(NULL, (yyvsp[0].nd_obj2).nd, "chartofloat");
			sprintf((yyval.nd_obj2).type, (yyvsp[-2].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode((yyvsp[-2].nd_obj2).nd, temp, (yyvsp[-1].nd_obj).name);
		}
		else {
			struct node *temp = mknode(NULL, (yyvsp[-2].nd_obj2).nd, "chartofloat");
			sprintf((yyval.nd_obj2).type, (yyvsp[0].nd_obj2).type);
			(yyval.nd_obj2).nd = mknode(temp, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).name);
		}
	}
	sprintf((yyval.nd_obj2).name, "t%d", temp_var);
	temp_var++;
	
	// Handle array access in left operand
	char left_operand[100], right_operand[100];
	if(strstr((yyvsp[-2].nd_obj2).name, "[") != NULL && strstr((yyvsp[-2].nd_obj2).name, "]") != NULL) {
		char array_name[100], index_name[100];
		sscanf((yyvsp[-2].nd_obj2).name, "%[^[][%[^]]", array_name, index_name);
		sprintf(icg[ic_idx++], "t%d = %s * 4\n", temp_var, index_name);
		int offset_temp1 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = &%s\n", temp_var, array_name);
		int base_temp1 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = t%d + t%d\n", temp_var, base_temp1, offset_temp1);
		int addr_temp1 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = *t%d\n", temp_var, addr_temp1);
		sprintf(left_operand, "t%d", temp_var++);
	} else {
		strcpy(left_operand, (yyvsp[-2].nd_obj2).name);
	}
	
	// Handle array access in right operand
	if(strstr((yyvsp[0].nd_obj2).name, "[") != NULL && strstr((yyvsp[0].nd_obj2).name, "]") != NULL) {
		char array_name[100], index_name[100];
		sscanf((yyvsp[0].nd_obj2).name, "%[^[][%[^]]", array_name, index_name);
		sprintf(icg[ic_idx++], "t%d = %s * 4\n", temp_var, index_name);
		int offset_temp2 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = &%s\n", temp_var, array_name);
		int base_temp2 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = t%d + t%d\n", temp_var, base_temp2, offset_temp2);
		int addr_temp2 = temp_var++;
		sprintf(icg[ic_idx++], "t%d = *t%d\n", temp_var, addr_temp2);
		sprintf(right_operand, "t%d", temp_var++);
	} else {
		strcpy(right_operand, (yyvsp[0].nd_obj2).name);
	}
	
	sprintf(icg[ic_idx++], "%s = %s %s %s\n", (yyval.nd_obj2).name, left_operand, "%", right_operand);
}
#line 2128 "parser.tab.c"
    break;

  case 51: /* expression: value  */
#line 715 ".\\parser.y"
        { strcpy((yyval.nd_obj2).name, (yyvsp[0].nd_obj2).name); sprintf((yyval.nd_obj2).type, (yyvsp[0].nd_obj2).type); (yyval.nd_obj2).nd = (yyvsp[0].nd_obj2).nd; }
#line 2134 "parser.tab.c"
    break;

  case 52: /* expression: '(' expression ')'  */
#line 716 ".\\parser.y"
                     { 
	strcpy((yyval.nd_obj2).name, (yyvsp[-1].nd_obj2).name); 
	sprintf((yyval.nd_obj2).type, (yyvsp[-1].nd_obj2).type); 
	(yyval.nd_obj2).nd = (yyvsp[-1].nd_obj2).nd; 
}
#line 2144 "parser.tab.c"
    break;

  case 59: /* variable: ID  */
#line 733 ".\\parser.y"
             {
    check_declaration((yyvsp[0].nd_obj).name);
    strcpy((yyval.nd_obj2).name, (yyvsp[0].nd_obj).name);
    sprintf((yyval.nd_obj2).type, get_type((yyvsp[0].nd_obj).name));
    (yyval.nd_obj2).nd = mknode(NULL, NULL, (yyvsp[0].nd_obj).name);
}
#line 2155 "parser.tab.c"
    break;

  case 60: /* variable: ID LBRACK expression RBRACK  */
#line 739 ".\\parser.y"
                              {
    check_is_array((yyvsp[-3].nd_obj).name); 
    sprintf((yyval.nd_obj2).type, get_type((yyvsp[-3].nd_obj).name)); 
    
    sprintf((yyval.nd_obj2).name, "%s[%s]", (yyvsp[-3].nd_obj).name, (yyvsp[-1].nd_obj2).name); 
    struct node* id_node = mknode(NULL, NULL, (yyvsp[-3].nd_obj).name);
    (yyval.nd_obj2).nd = mknode(id_node, (yyvsp[-1].nd_obj2).nd, "ARR_ACCESS");
}
#line 2168 "parser.tab.c"
    break;

  case 61: /* value: NUMBER  */
#line 749 ".\\parser.y"
              { strcpy((yyval.nd_obj2).name, (yyvsp[0].nd_obj).name); sprintf((yyval.nd_obj2).type, "int"); add('C'); (yyval.nd_obj2).nd = mknode(NULL, NULL, (yyvsp[0].nd_obj).name); }
#line 2174 "parser.tab.c"
    break;

  case 62: /* value: FLOAT_NUM  */
#line 750 ".\\parser.y"
            { strcpy((yyval.nd_obj2).name, (yyvsp[0].nd_obj).name); sprintf((yyval.nd_obj2).type, "float"); add('C'); (yyval.nd_obj2).nd = mknode(NULL, NULL, (yyvsp[0].nd_obj).name); }
#line 2180 "parser.tab.c"
    break;

  case 63: /* value: CHARACTER  */
#line 751 ".\\parser.y"
            { strcpy((yyval.nd_obj2).name, (yyvsp[0].nd_obj).name); sprintf((yyval.nd_obj2).type, "char"); add('C'); (yyval.nd_obj2).nd = mknode(NULL, NULL, (yyvsp[0].nd_obj).name); }
#line 2186 "parser.tab.c"
    break;

  case 64: /* value: variable  */
#line 752 ".\\parser.y"
           { 
	strcpy((yyval.nd_obj2).name, (yyvsp[0].nd_obj2).name);
	sprintf((yyval.nd_obj2).type, (yyvsp[0].nd_obj2).type);
	(yyval.nd_obj2).nd = (yyvsp[0].nd_obj2).nd;
}
#line 2196 "parser.tab.c"
    break;

  case 65: /* $@12: %empty  */
#line 759 ".\\parser.y"
               { add('K'); }
#line 2202 "parser.tab.c"
    break;

  case 66: /* return: RETURN $@12 value ';'  */
#line 759 ".\\parser.y"
                                       { check_return_type((yyvsp[-1].nd_obj2).name); (yyvsp[-3].nd_obj).nd = mknode(NULL, NULL, "return"); (yyval.nd_obj).nd = mknode((yyvsp[-3].nd_obj).nd, (yyvsp[-1].nd_obj2).nd, "RETURN"); }
#line 2208 "parser.tab.c"
    break;

  case 67: /* return: %empty  */
#line 760 ".\\parser.y"
         { (yyval.nd_obj).nd = NULL; }
#line 2214 "parser.tab.c"
    break;


#line 2218 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 763 ".\\parser.y"


int main() {
    yyparse();
    printf("\n\n");
	printf("\t\t\t\t\t\t\t\t PHASE 1: LEXICAL ANALYSIS \n\n");
	printf("\nSYMBOL   DATATYPE   TYPE   LINE NUMBER \n");
	printf("_______________________________________\n\n");
	int i=0;
	for(i=0; i<count; i++) {
		printf("%s\t%s\t%s\t%d\t\n", symbol_table[i].id_name, symbol_table[i].data_type, symbol_table[i].type, symbol_table[i].line_no);
	}
	for(i=0;i<count;i++) {
		free(symbol_table[i].id_name);
		free(symbol_table[i].type);
	}
	printf("\n\n");
	printf("\t\t\t\t\t\t\t\t PHASE 2: SYNTAX ANALYSIS \n\n");
	print_tree(head); 
	printf("\n\n\n\n");
	printf("\t\t\t\t\t\t\t\t PHASE 3: SEMANTIC ANALYSIS \n\n");
	if(sem_errors>0) {
		printf("Semantic analysis completed with %d errors\n", sem_errors);
		for(int i=0; i<sem_errors; i++){
			printf("\t - %s", errors[i]);
		}
	} else {
		printf("Semantic analysis completed with no errors");
	}
	printf("\n\n");
	printf("\t\t\t\t\t\t\t   PHASE 4: INTERMEDIATE CODE GENERATION \n\n");
	for(int i=0; i<ic_idx; i++){
		printf("%s", icg[i]);
	}
	printf("\n\n");
}

int search(char *type) {
	int i;
	for(i=count-1; i>=0; i--) {
		if(strcmp(symbol_table[i].id_name, type)==0) {
			return -1;
			break;
		}
	}
	return 0;
}

void check_is_array(char *c) {
    int i;
    for(i=0; i<count; i++) {
        if(strcmp(symbol_table[i].id_name, c) == 0) {
            if(strcmp(symbol_table[i].type, "Array") != 0) {
                sprintf(errors[sem_errors], "Line %d: Variable \"%s\" is not an array and cannot be indexed!\n", countn+1, c);
                sem_errors++;
            }
            return;
        }
    }
    sprintf(errors[sem_errors], "Line %d: Array \"%s\" not declared before usage!\n", countn+1, c);
    sem_errors++;
}

void check_declaration(char *c) {
    q = search(c);
    if(!q) {
        sprintf(errors[sem_errors], "Line %d: Variable \"%s\" not declared before usage!\n", countn+1, c);
		sem_errors++;
    }
}

void check_return_type(char *value) {
	char *main_datatype = get_type("main");
	char *return_datatype = get_type(value);
	if((!strcmp(main_datatype, "int") && !strcmp(return_datatype, "CONST")) || !strcmp(main_datatype, return_datatype)){
		return ;
	}
	else {
		sprintf(errors[sem_errors], "Line %d: Return type mismatch\n", countn+1);
		sem_errors++;
	}
}

int check_types(char *type1, char *type2){
	if(!strcmp(type2, "null"))
		return -1;
	if(!strcmp(type1, type2))
		return 0;
	if(!strcmp(type1, "int") && !strcmp(type2, "float"))
		return 1;
	if(!strcmp(type1, "float") && !strcmp(type2, "int"))
		return 2;
	if(!strcmp(type1, "int") && !strcmp(type2, "char"))
		return 3;
	if(!strcmp(type1, "char") && !strcmp(type2, "int"))
		return 4;
	if(!strcmp(type1, "float") && !strcmp(type2, "char"))
		return 5;
	if(!strcmp(type1, "char") && !strcmp(type2, "float"))
		return 6;
}

char *get_type(char *var){
	for(int i=0; i<count; i++) {
		if(!strcmp(symbol_table[i].id_name, var)) {
			return symbol_table[i].data_type;
		}
	}
}

void add(char c) {
	if(c == 'V'){
		for(int i=0; i<10; i++){
			if(!strcmp(reserved[i], strdup(yytext))){
        		sprintf(errors[sem_errors], "Line %d: Variable name \"%s\" is a reserved keyword!\n", countn+1, yytext);
				sem_errors++;
				return;
			}
		}
	}
    q=search(yytext);
	if(!q) {
		if(c == 'H') {
			symbol_table[count].id_name=strdup(yytext);
			symbol_table[count].data_type=strdup(type);
			symbol_table[count].line_no=countn;
			symbol_table[count].type=strdup("Header");
			symbol_table[count].size = -1;
			count++;
		}
		else if(c == 'K') {
			symbol_table[count].id_name=strdup(yytext);
			symbol_table[count].data_type=strdup("N/A");
			symbol_table[count].line_no=countn;
			symbol_table[count].type=strdup("Keyword\t");
			symbol_table[count].size = -1;
			count++;
		}
		else if(c == 'V') {
			symbol_table[count].id_name=strdup(yytext);
			symbol_table[count].data_type=strdup(type);
			symbol_table[count].line_no=countn;
			symbol_table[count].type=strdup("Variable");
			symbol_table[count].size = -1;
			count++;
		}
		else if(c == 'C') {
			symbol_table[count].id_name=strdup(yytext);
			symbol_table[count].data_type=strdup("CONST");
			symbol_table[count].line_no=countn;
			symbol_table[count].type=strdup("Constant");
			symbol_table[count].size = -1;
			count++;
		}
		else if(c == 'F') {
			symbol_table[count].id_name=strdup(yytext);
			symbol_table[count].data_type=strdup(type);
			symbol_table[count].line_no=countn;
			symbol_table[count].type=strdup("Function");
			symbol_table[count].size = -1;
			count++;
		}
    }
    else if(c == 'V' && q) {
        sprintf(errors[sem_errors], "Line %d: Multiple declarations of \"%s\" not allowed!\n", countn+1, yytext);
		sem_errors++;
    }
}

void add_array(char* name, int size) {
	for(int i=0; i<10; i++){
		if(!strcmp(reserved[i], name)){
			sprintf(errors[sem_errors], "Line %d: Variable name \"%s\" is a reserved keyword!\n", countn+1, name);
			sem_errors++;
			return;
		}
	}
    q=search(name);
	if(!q) {
		symbol_table[count].id_name = strdup(name);
		symbol_table[count].data_type = strdup(type);
		symbol_table[count].line_no = countn;
		symbol_table[count].type = strdup("Array");
		symbol_table[count].size = size;
		count++;
	} else {
		sprintf(errors[sem_errors], "Line %d: Multiple declarations of \"%s\" not allowed!\n", countn+1, name);
		sem_errors++;
	}
}

void add_variable(char* name) {
	for(int i=0; i<10; i++){
		if(!strcmp(reserved[i], name)){
			sprintf(errors[sem_errors], "Line %d: Variable name \"%s\" is a reserved keyword!\n", countn+1, name);
			sem_errors++;
			return;
		}
	}
    q=search(name);
	if(!q) {
		symbol_table[count].id_name = strdup(name);
		symbol_table[count].data_type = strdup(type);
		symbol_table[count].line_no = countn;
		symbol_table[count].type = strdup("Variable");
		symbol_table[count].size = -1;
		count++;
	} else {
		sprintf(errors[sem_errors], "Line %d: Multiple declarations of \"%s\" not allowed!\n", countn+1, name);
		sem_errors++;
	}
}

struct node* mknode(struct node *left, struct node *right, char *token) {	
	struct node *newnode = (struct node *)malloc(sizeof(struct node));
	char *newstr = (char *)malloc(strlen(token)+1);
	strcpy(newstr, token);
	newnode->left = left;
	newnode->right = right;
	newnode->token = newstr;
	return(newnode);
}

void print_tree(struct node* tree) {
	printf("\n\nInorder traversal of the Parse Tree is: \n\n");
	print_inorder(tree);
}

void print_inorder(struct node *tree) {
	int i;
	if (tree->left) {
		print_inorder(tree->left);
	}
	printf("%s, ", tree->token);
	if (tree->right) {
		print_inorder(tree->right);
	}
}

void print_tree_util(struct node *root, int space) {
    if(root == NULL)
        return;
    space += 7;
    print_tree_util(root->right, space);
    for (int i = 7; i < space; i++)
        printf(" ");
	printf("%s\n", root->token);
    print_tree_util(root->left, space);
}

void insert_type() {
	strcpy(type, yytext);
}

void yyerror(const char* msg) {
    fprintf(stderr, "%s\n", msg);
}
