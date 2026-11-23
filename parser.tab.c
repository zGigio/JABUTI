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
#line 29 "src\\parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simbolos.h"       /* o prologo %{ %} vem ANTES do %code requires */
#include "gerador.h"        /* no arquivo gerado, por isso os includes se repetem */
#include "diagnostico.h"

int         yylex(void);
void        yyerror(const char *msg);
const char *lexer_ultimo_lexema(void);
void        lexer_fim_token_anterior(int *linha, int *coluna);
int         lexer_eof_por_erro(void);
extern int  yychar;                     /* token de lookahead (Bison) */

#define LOC(x)  (x).first_line, (x).first_column

static Tipo tipo_corrente;              /* tipo da declaracao em andamento   */
static int  contador_para = 0;          /* numera os limites dos lacos 'para' */

/* --- acoes semanticas (definidas no fim deste arquivo) --- */
static Expr  expr_invalida(void);
static Expr  expr_literal_inteiro(long v);
static Expr  expr_literal_real(char *texto);
static Expr  expr_texto(char *texto);
static Expr  expr_booleano(int v);
static Expr  expr_variavel(char *nome, int lin, int col);
static Expr  expr_binaria(Operador op, Expr a, Expr b, int lin, int col);
static Expr  expr_negativo(Expr e, int lin, int col);
static Expr  expr_nao(Expr e, int lin, int col);
static void  declarar_variavel(Tipo t, char *nome, Expr *inicial, int lin, int col);
static void  declarar_constante(Tipo t, char *nome, Expr inicial, int lin, int col);
static void  atribuir(char *nome, Expr e, int lin, int col);
static void  ler_variavel(char *nome, int lin, int col);
static void  imprimir_argumento(Expr e);
static void  iniciar_se(Expr c, int lin, int col);
static void  iniciar_enquanto(Expr c, int lin, int col);
static void  iniciar_para(char *nome, Expr de, Expr ate, long passo,
                          int lin, int col, int plin, int pcol);

#line 112 "parser.tab.c"

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
  YYSYMBOL_PROGRAMA = 3,                   /* "'programa'"  */
  YYSYMBOL_CONSTANTE = 4,                  /* "'constante'"  */
  YYSYMBOL_T_INTEIRO = 5,                  /* "'inteiro'"  */
  YYSYMBOL_T_REAL = 6,                     /* "'real'"  */
  YYSYMBOL_T_TEXTO = 7,                    /* "'texto'"  */
  YYSYMBOL_T_BOOLEANO = 8,                 /* "'booleano'"  */
  YYSYMBOL_VERDADEIRO = 9,                 /* "'verdadeiro'"  */
  YYSYMBOL_FALSO = 10,                     /* "'falso'"  */
  YYSYMBOL_SE = 11,                        /* "'se'"  */
  YYSYMBOL_SENAO = 12,                     /* "'senao'"  */
  YYSYMBOL_ENQUANTO = 13,                  /* "'enquanto'"  */
  YYSYMBOL_PARA = 14,                      /* "'para'"  */
  YYSYMBOL_DE = 15,                        /* "'de'"  */
  YYSYMBOL_ATE = 16,                       /* "'ate'"  */
  YYSYMBOL_PASSO = 17,                     /* "'passo'"  */
  YYSYMBOL_LEIA = 18,                      /* "'leia'"  */
  YYSYMBOL_ESCREVA = 19,                   /* "'escreva'"  */
  YYSYMBOL_ESCREVAL = 20,                  /* "'escreval'"  */
  YYSYMBOL_E = 21,                         /* "'e'"  */
  YYSYMBOL_OU = 22,                        /* "'ou'"  */
  YYSYMBOL_NAO = 23,                       /* "'nao'"  */
  YYSYMBOL_IGUAL = 24,                     /* "'=='"  */
  YYSYMBOL_DIFERENTE = 25,                 /* "'!='"  */
  YYSYMBOL_MENOR_IGUAL = 26,               /* "'<='"  */
  YYSYMBOL_MAIOR_IGUAL = 27,               /* "'>='"  */
  YYSYMBOL_ERRO_LEXICO = 28,               /* "caractere invalido"  */
  YYSYMBOL_IDENTIFICADOR = 29,             /* "identificador"  */
  YYSYMBOL_LIT_REAL = 30,                  /* "numero real"  */
  YYSYMBOL_LIT_CADEIA = 31,                /* "texto entre aspas"  */
  YYSYMBOL_LIT_INTEIRO = 32,               /* "numero inteiro"  */
  YYSYMBOL_33_ = 33,                       /* '{'  */
  YYSYMBOL_34_ = 34,                       /* '}'  */
  YYSYMBOL_35_ = 35,                       /* ';'  */
  YYSYMBOL_36_ = 36,                       /* '='  */
  YYSYMBOL_37_ = 37,                       /* ','  */
  YYSYMBOL_38_ = 38,                       /* '('  */
  YYSYMBOL_39_ = 39,                       /* ')'  */
  YYSYMBOL_40_ = 40,                       /* '-'  */
  YYSYMBOL_41_ = 41,                       /* '<'  */
  YYSYMBOL_42_ = 42,                       /* '>'  */
  YYSYMBOL_43_ = 43,                       /* '+'  */
  YYSYMBOL_44_ = 44,                       /* '*'  */
  YYSYMBOL_45_ = 45,                       /* '/'  */
  YYSYMBOL_46_ = 46,                       /* '%'  */
  YYSYMBOL_YYACCEPT = 47,                  /* $accept  */
  YYSYMBOL_programa = 48,                  /* programa  */
  YYSYMBOL_49_1 = 49,                      /* $@1  */
  YYSYMBOL_nome_programa = 50,             /* nome_programa  */
  YYSYMBOL_lista_comandos = 51,            /* lista_comandos  */
  YYSYMBOL_comando = 52,                   /* comando  */
  YYSYMBOL_declaracao = 53,                /* declaracao  */
  YYSYMBOL_54_2 = 54,                      /* $@2  */
  YYSYMBOL_tipo = 55,                      /* tipo  */
  YYSYMBOL_lista_declaradores = 56,        /* lista_declaradores  */
  YYSYMBOL_declarador = 57,                /* declarador  */
  YYSYMBOL_atribuicao = 58,                /* atribuicao  */
  YYSYMBOL_entrada = 59,                   /* entrada  */
  YYSYMBOL_lista_leitura = 60,             /* lista_leitura  */
  YYSYMBOL_saida = 61,                     /* saida  */
  YYSYMBOL_lista_argumentos = 62,          /* lista_argumentos  */
  YYSYMBOL_condicional = 63,               /* condicional  */
  YYSYMBOL_64_3 = 64,                      /* $@3  */
  YYSYMBOL_senao_opt = 65,                 /* senao_opt  */
  YYSYMBOL_66_4 = 66,                      /* $@4  */
  YYSYMBOL_senao_corpo = 67,               /* senao_corpo  */
  YYSYMBOL_repeticao = 68,                 /* repeticao  */
  YYSYMBOL_69_5 = 69,                      /* $@5  */
  YYSYMBOL_para = 70,                      /* para  */
  YYSYMBOL_71_6 = 71,                      /* $@6  */
  YYSYMBOL_passo_opt = 72,                 /* passo_opt  */
  YYSYMBOL_bloco = 73,                     /* bloco  */
  YYSYMBOL_74_7 = 74,                      /* $@7  */
  YYSYMBOL_expressao = 75,                 /* expressao  */
  YYSYMBOL_conjuncao = 76,                 /* conjuncao  */
  YYSYMBOL_igualdade = 77,                 /* igualdade  */
  YYSYMBOL_relacional = 78,                /* relacional  */
  YYSYMBOL_soma = 79,                      /* soma  */
  YYSYMBOL_termo = 80,                     /* termo  */
  YYSYMBOL_unario = 81,                    /* unario  */
  YYSYMBOL_primario = 82                   /* primario  */
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

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYLAST   154

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  82
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  151

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   287


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
       2,     2,     2,     2,     2,     2,     2,    46,     2,     2,
      38,    39,    44,    43,    37,    40,     2,    45,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    35,
      41,    36,    42,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    33,     2,    34,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   134,   134,   133,   150,   151,   155,   156,   160,   161,
     162,   163,   164,   165,   166,   167,   174,   175,   183,   183,
     184,   189,   190,   191,   192,   196,   197,   201,   203,   212,
     217,   221,   222,   226,   227,   228,   232,   233,   249,   249,
     254,   255,   255,   259,   260,   264,   264,   270,   269,   276,
     277,   278,   283,   282,   293,   294,   298,   299,   303,   304,
     305,   309,   310,   311,   312,   313,   317,   318,   319,   323,
     324,   325,   326,   330,   331,   332,   336,   337,   338,   339,
     340,   341,   342
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "\"'programa'\"",
  "\"'constante'\"", "\"'inteiro'\"", "\"'real'\"", "\"'texto'\"",
  "\"'booleano'\"", "\"'verdadeiro'\"", "\"'falso'\"", "\"'se'\"",
  "\"'senao'\"", "\"'enquanto'\"", "\"'para'\"", "\"'de'\"", "\"'ate'\"",
  "\"'passo'\"", "\"'leia'\"", "\"'escreva'\"", "\"'escreval'\"",
  "\"'e'\"", "\"'ou'\"", "\"'nao'\"", "\"'=='\"", "\"'!='\"", "\"'<='\"",
  "\"'>='\"", "\"caractere invalido\"", "\"identificador\"",
  "\"numero real\"", "\"texto entre aspas\"", "\"numero inteiro\"", "'{'",
  "'}'", "';'", "'='", "','", "'('", "')'", "'-'", "'<'", "'>'", "'+'",
  "'*'", "'/'", "'%'", "$accept", "programa", "$@1", "nome_programa",
  "lista_comandos", "comando", "declaracao", "$@2", "tipo",
  "lista_declaradores", "declarador", "atribuicao", "entrada",
  "lista_leitura", "saida", "lista_argumentos", "condicional", "$@3",
  "senao_opt", "$@4", "senao_corpo", "repeticao", "$@5", "para", "$@6",
  "passo_opt", "bloco", "$@7", "expressao", "conjuncao", "igualdade",
  "relacional", "soma", "termo", "unario", "primario", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-108)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      16,    40,    70,  -108,    45,  -108,  -108,  -108,    47,    52,
      95,  -108,  -108,  -108,  -108,    55,    71,    72,    75,    88,
      89,    69,  -108,  -108,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,    99,    85,    85,   100,   101,
      85,    -5,    85,  -108,   102,    96,  -108,  -108,    85,  -108,
    -108,  -108,  -108,    85,    85,   -11,   112,    25,    30,    34,
      -7,  -108,  -108,    -9,   119,  -108,    36,    51,   113,   103,
      67,   -13,    78,   104,    87,  -108,    85,  -108,    -8,  -108,
      85,  -108,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,  -108,    85,   107,   106,    85,   108,
    -108,   109,  -108,  -108,    85,  -108,   102,   -12,  -108,   112,
     114,    25,    30,    30,    34,    34,    34,    34,    -7,    -7,
    -108,  -108,  -108,   114,    -1,  -108,  -108,   113,  -108,  -108,
     113,  -108,  -108,   125,  -108,    85,  -108,  -108,    19,    -4,
     -20,   110,  -108,  -108,  -108,  -108,   116,  -108,  -108,   114,
    -108
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     4,     0,     5,     0,     1,     2,     6,     0,    17,
       0,    21,    22,    23,    24,     0,     0,     0,     0,     0,
       0,     0,    52,     3,     7,     8,    18,     9,    10,    11,
      12,    13,    14,    15,    16,     0,     0,     0,     0,     0,
       0,     0,     0,     6,     0,     0,    79,    80,     0,    81,
      77,    78,    76,     0,     0,     0,    55,    57,    60,    65,
      68,    72,    75,     0,     0,    31,     0,     0,    36,     0,
       0,     0,     0,    27,     0,    25,     0,    74,     0,    73,
       0,    38,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    45,     0,     0,     0,     0,     0,
      35,     0,    29,    53,     0,    19,     0,     0,    82,    54,
       0,    56,    58,    59,    63,    64,    61,    62,    67,    66,
      69,    70,    71,     0,     0,    32,    30,    37,    33,    34,
      28,    26,    20,    40,    46,     0,    41,    39,    49,     0,
       0,     0,    44,    42,    43,    50,     0,    47,    51,     0,
      48
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -108,  -108,  -108,  -108,   111,  -108,  -108,  -108,   129,  -108,
      39,  -108,  -108,  -108,  -108,   105,     3,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,  -108,  -107,  -108,   -36,    73,
      68,   -40,    33,   -26,   -46,  -108
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     7,     4,     8,    24,    25,    44,    26,    74,
      75,    27,    28,    66,    29,    67,    30,   110,   137,   139,
     143,    31,   123,    32,   149,   141,    33,    43,    68,    56,
      57,    58,    59,    60,    61,    62
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      55,    63,    77,   133,    46,    47,    71,    15,    79,    80,
      80,    80,   145,    80,    80,   135,   134,    78,    48,     1,
     146,    80,   102,   132,    49,    50,    51,    52,    81,    22,
      94,   108,   144,    53,    69,    54,   140,    91,    92,    93,
     107,    80,   150,   112,   113,   120,   121,   122,     9,    83,
      84,    10,    11,    12,    13,    14,    85,    86,    15,   124,
      16,    17,   127,   118,   119,    18,    19,    20,   130,     3,
       5,    87,    88,    96,    89,    97,    21,    90,     6,     9,
      22,    23,    10,    11,    12,    13,    14,    34,    98,    15,
      99,    16,    17,    36,    46,    47,    18,    19,    20,   138,
      11,    12,    13,    14,    98,    42,   101,    21,    48,    37,
      38,    22,   103,    39,    49,    50,    51,    52,   114,   115,
     116,   117,   105,    53,   106,    54,    40,    41,    45,    64,
      65,    73,    76,    82,    95,    80,   125,   136,   100,    35,
     104,   126,   142,   128,   129,   131,    70,    22,   148,   147,
     111,     0,     0,   109,    72
};

static const yytype_int16 yycheck[] =
{
      36,    37,    48,   110,     9,    10,    42,    11,    54,    22,
      22,    22,    32,    22,    22,    16,   123,    53,    23,     3,
      40,    22,    35,    35,    29,    30,    31,    32,    39,    33,
      39,    39,   139,    38,    39,    40,    17,    44,    45,    46,
      76,    22,   149,    83,    84,    91,    92,    93,     1,    24,
      25,     4,     5,     6,     7,     8,    26,    27,    11,    95,
      13,    14,    98,    89,    90,    18,    19,    20,   104,    29,
       0,    41,    42,    37,    40,    39,    29,    43,    33,     1,
      33,    34,     4,     5,     6,     7,     8,    35,    37,    11,
      39,    13,    14,    38,     9,    10,    18,    19,    20,   135,
       5,     6,     7,     8,    37,    36,    39,    29,    23,    38,
      38,    33,    34,    38,    29,    30,    31,    32,    85,    86,
      87,    88,    35,    38,    37,    40,    38,    38,    29,    29,
      29,    29,    36,    21,    15,    22,    29,    12,    35,    10,
      36,    35,   139,    35,    35,   106,    41,    33,    32,    39,
      82,    -1,    -1,    80,    43
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    48,    29,    50,     0,    33,    49,    51,     1,
       4,     5,     6,     7,     8,    11,    13,    14,    18,    19,
      20,    29,    33,    34,    52,    53,    55,    58,    59,    61,
      63,    68,    70,    73,    35,    55,    38,    38,    38,    38,
      38,    38,    36,    74,    54,    29,     9,    10,    23,    29,
      30,    31,    32,    38,    40,    75,    76,    77,    78,    79,
      80,    81,    82,    75,    29,    29,    60,    62,    75,    39,
      62,    75,    51,    29,    56,    57,    36,    81,    75,    81,
      22,    39,    21,    24,    25,    26,    27,    41,    42,    40,
      43,    44,    45,    46,    39,    15,    37,    39,    37,    39,
      35,    39,    35,    34,    36,    35,    37,    75,    39,    76,
      64,    77,    78,    78,    79,    79,    79,    79,    80,    80,
      81,    81,    81,    69,    75,    29,    35,    75,    35,    35,
      75,    57,    35,    73,    73,    16,    12,    65,    75,    66,
      17,    72,    63,    67,    73,    32,    40,    39,    32,    71,
      73
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    49,    48,    50,    50,    51,    51,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    54,    53,
      53,    55,    55,    55,    55,    56,    56,    57,    57,    58,
      59,    60,    60,    61,    61,    61,    62,    62,    64,    63,
      65,    66,    65,    67,    67,    69,    68,    71,    70,    72,
      72,    72,    74,    73,    75,    75,    76,    76,    77,    77,
      77,    78,    78,    78,    78,    78,    79,    79,    79,    80,
      80,    80,    80,    81,    81,    81,    82,    82,    82,    82,
      82,    82,    82
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     6,     0,     1,     0,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     0,     4,
       6,     1,     1,     1,     1,     1,     3,     1,     3,     4,
       5,     1,     3,     5,     5,     4,     1,     3,     0,     7,
       0,     0,     3,     1,     1,     0,     6,     0,    11,     0,
       2,     3,     0,     4,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     1,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     3
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

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
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
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
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
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
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


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 134 "src\\parser.y"
        {
            g_programa((yyvsp[-1].texto));
            g_emit("{");
            g_indent(1);
            escopo_entrar();
        }
#line 1681 "parser.tab.c"
    break;

  case 3: /* programa: "'programa'" nome_programa '{' $@1 lista_comandos '}'  */
#line 141 "src\\parser.y"
        {
            g_emit("return 0;");
            g_indent(-1);
            g_emit("}");
            escopo_sair();
        }
#line 1692 "parser.tab.c"
    break;

  case 4: /* nome_programa: %empty  */
#line 150 "src\\parser.y"
                        { (yyval.texto) = NULL; }
#line 1698 "parser.tab.c"
    break;

  case 5: /* nome_programa: "identificador"  */
#line 151 "src\\parser.y"
                        { (yyval.texto) = (yyvsp[0].texto); }
#line 1704 "parser.tab.c"
    break;

  case 16: /* comando: error ';'  */
#line 174 "src\\parser.y"
                        { yyerrok; }
#line 1710 "parser.tab.c"
    break;

  case 18: /* $@2: %empty  */
#line 183 "src\\parser.y"
           { tipo_corrente = (yyvsp[0].tipo); }
#line 1716 "parser.tab.c"
    break;

  case 20: /* declaracao: "'constante'" tipo "identificador" '=' expressao ';'  */
#line 185 "src\\parser.y"
        { declarar_constante((yyvsp[-4].tipo), (yyvsp[-3].texto), (yyvsp[-1].expr), LOC((yylsp[-3]))); }
#line 1722 "parser.tab.c"
    break;

  case 21: /* tipo: "'inteiro'"  */
#line 189 "src\\parser.y"
                        { (yyval.tipo) = TP_INTEIRO; }
#line 1728 "parser.tab.c"
    break;

  case 22: /* tipo: "'real'"  */
#line 190 "src\\parser.y"
                        { (yyval.tipo) = TP_REAL; }
#line 1734 "parser.tab.c"
    break;

  case 23: /* tipo: "'texto'"  */
#line 191 "src\\parser.y"
                        { (yyval.tipo) = TP_TEXTO; }
#line 1740 "parser.tab.c"
    break;

  case 24: /* tipo: "'booleano'"  */
#line 192 "src\\parser.y"
                        { (yyval.tipo) = TP_BOOLEANO; }
#line 1746 "parser.tab.c"
    break;

  case 27: /* declarador: "identificador"  */
#line 202 "src\\parser.y"
        { declarar_variavel(tipo_corrente, (yyvsp[0].texto), NULL, LOC((yylsp[0]))); }
#line 1752 "parser.tab.c"
    break;

  case 28: /* declarador: "identificador" '=' expressao  */
#line 204 "src\\parser.y"
        { declarar_variavel(tipo_corrente, (yyvsp[-2].texto), &(yyvsp[0].expr), LOC((yylsp[-2]))); }
#line 1758 "parser.tab.c"
    break;

  case 29: /* atribuicao: "identificador" '=' expressao ';'  */
#line 213 "src\\parser.y"
        { atribuir((yyvsp[-3].texto), (yyvsp[-1].expr), LOC((yylsp[-3]))); }
#line 1764 "parser.tab.c"
    break;

  case 31: /* lista_leitura: "identificador"  */
#line 221 "src\\parser.y"
                                         { ler_variavel((yyvsp[0].texto), LOC((yylsp[0]))); }
#line 1770 "parser.tab.c"
    break;

  case 32: /* lista_leitura: lista_leitura ',' "identificador"  */
#line 222 "src\\parser.y"
                                         { ler_variavel((yyvsp[0].texto), LOC((yylsp[0]))); }
#line 1776 "parser.tab.c"
    break;

  case 34: /* saida: "'escreval'" '(' lista_argumentos ')' ';'  */
#line 227 "src\\parser.y"
                                              { g_emit("jab_nova_linha();"); }
#line 1782 "parser.tab.c"
    break;

  case 35: /* saida: "'escreval'" '(' ')' ';'  */
#line 228 "src\\parser.y"
                                              { g_emit("jab_nova_linha();"); }
#line 1788 "parser.tab.c"
    break;

  case 36: /* lista_argumentos: expressao  */
#line 232 "src\\parser.y"
                                         { imprimir_argumento((yyvsp[0].expr)); }
#line 1794 "parser.tab.c"
    break;

  case 37: /* lista_argumentos: lista_argumentos ',' expressao  */
#line 233 "src\\parser.y"
                                         { imprimir_argumento((yyvsp[0].expr)); }
#line 1800 "parser.tab.c"
    break;

  case 38: /* $@3: %empty  */
#line 249 "src\\parser.y"
                            { iniciar_se((yyvsp[-1].expr), LOC((yylsp[-1]))); }
#line 1806 "parser.tab.c"
    break;

  case 41: /* $@4: %empty  */
#line 255 "src\\parser.y"
            { g_emit("else"); }
#line 1812 "parser.tab.c"
    break;

  case 45: /* $@5: %empty  */
#line 264 "src\\parser.y"
                                  { iniciar_enquanto((yyvsp[-1].expr), LOC((yylsp[-1]))); }
#line 1818 "parser.tab.c"
    break;

  case 47: /* $@6: %empty  */
#line 270 "src\\parser.y"
        { iniciar_para((yyvsp[-6].texto), (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[-1].inteiro), LOC((yylsp[-6])), LOC((yylsp[-1]))); }
#line 1824 "parser.tab.c"
    break;

  case 48: /* para: "'para'" '(' "identificador" "'de'" expressao "'ate'" expressao passo_opt ')' $@6 bloco  */
#line 272 "src\\parser.y"
        { g_indent(-1); g_emit("}"); }
#line 1830 "parser.tab.c"
    break;

  case 49: /* passo_opt: %empty  */
#line 276 "src\\parser.y"
                                    { (yyval.inteiro) = 1; }
#line 1836 "parser.tab.c"
    break;

  case 50: /* passo_opt: "'passo'" "numero inteiro"  */
#line 277 "src\\parser.y"
                                    { (yyval.inteiro) = (yyvsp[0].inteiro); }
#line 1842 "parser.tab.c"
    break;

  case 51: /* passo_opt: "'passo'" '-' "numero inteiro"  */
#line 278 "src\\parser.y"
                                    { (yyval.inteiro) = -(yyvsp[0].inteiro); }
#line 1848 "parser.tab.c"
    break;

  case 52: /* $@7: %empty  */
#line 283 "src\\parser.y"
        { escopo_entrar(); g_emit("{"); g_indent(1); }
#line 1854 "parser.tab.c"
    break;

  case 53: /* bloco: '{' $@7 lista_comandos '}'  */
#line 285 "src\\parser.y"
        { escopo_sair();   g_indent(-1); g_emit("}"); }
#line 1860 "parser.tab.c"
    break;

  case 54: /* expressao: expressao "'ou'" conjuncao  */
#line 293 "src\\parser.y"
                                    { (yyval.expr) = expr_binaria(OP_OU, (yyvsp[-2].expr), (yyvsp[0].expr), LOC((yylsp[-1]))); }
#line 1866 "parser.tab.c"
    break;

  case 56: /* conjuncao: conjuncao "'e'" igualdade  */
#line 298 "src\\parser.y"
                                    { (yyval.expr) = expr_binaria(OP_E, (yyvsp[-2].expr), (yyvsp[0].expr), LOC((yylsp[-1]))); }
#line 1872 "parser.tab.c"
    break;

  case 58: /* igualdade: igualdade "'=='" relacional  */
#line 303 "src\\parser.y"
                                      { (yyval.expr) = expr_binaria(OP_IGUAL, (yyvsp[-2].expr), (yyvsp[0].expr), LOC((yylsp[-1]))); }
#line 1878 "parser.tab.c"
    break;

  case 59: /* igualdade: igualdade "'!='" relacional  */
#line 304 "src\\parser.y"
                                      { (yyval.expr) = expr_binaria(OP_DIF,   (yyvsp[-2].expr), (yyvsp[0].expr), LOC((yylsp[-1]))); }
#line 1884 "parser.tab.c"
    break;

  case 61: /* relacional: relacional '<' soma  */
#line 309 "src\\parser.y"
                                      { (yyval.expr) = expr_binaria(OP_MENOR, (yyvsp[-2].expr), (yyvsp[0].expr), LOC((yylsp[-1]))); }
#line 1890 "parser.tab.c"
    break;

  case 62: /* relacional: relacional '>' soma  */
#line 310 "src\\parser.y"
                                      { (yyval.expr) = expr_binaria(OP_MAIOR, (yyvsp[-2].expr), (yyvsp[0].expr), LOC((yylsp[-1]))); }
#line 1896 "parser.tab.c"
    break;

  case 63: /* relacional: relacional "'<='" soma  */
#line 311 "src\\parser.y"
                                      { (yyval.expr) = expr_binaria(OP_MENIG, (yyvsp[-2].expr), (yyvsp[0].expr), LOC((yylsp[-1]))); }
#line 1902 "parser.tab.c"
    break;

  case 64: /* relacional: relacional "'>='" soma  */
#line 312 "src\\parser.y"
                                      { (yyval.expr) = expr_binaria(OP_MAIG,  (yyvsp[-2].expr), (yyvsp[0].expr), LOC((yylsp[-1]))); }
#line 1908 "parser.tab.c"
    break;

  case 66: /* soma: soma '+' termo  */
#line 317 "src\\parser.y"
                                      { (yyval.expr) = expr_binaria(OP_SOMA, (yyvsp[-2].expr), (yyvsp[0].expr), LOC((yylsp[-1]))); }
#line 1914 "parser.tab.c"
    break;

  case 67: /* soma: soma '-' termo  */
#line 318 "src\\parser.y"
                                      { (yyval.expr) = expr_binaria(OP_SUB,  (yyvsp[-2].expr), (yyvsp[0].expr), LOC((yylsp[-1]))); }
#line 1920 "parser.tab.c"
    break;

  case 69: /* termo: termo '*' unario  */
#line 323 "src\\parser.y"
                                      { (yyval.expr) = expr_binaria(OP_MUL, (yyvsp[-2].expr), (yyvsp[0].expr), LOC((yylsp[-1]))); }
#line 1926 "parser.tab.c"
    break;

  case 70: /* termo: termo '/' unario  */
#line 324 "src\\parser.y"
                                      { (yyval.expr) = expr_binaria(OP_DIV, (yyvsp[-2].expr), (yyvsp[0].expr), LOC((yylsp[-1]))); }
#line 1932 "parser.tab.c"
    break;

  case 71: /* termo: termo '%' unario  */
#line 325 "src\\parser.y"
                                      { (yyval.expr) = expr_binaria(OP_MOD, (yyvsp[-2].expr), (yyvsp[0].expr), LOC((yylsp[-1]))); }
#line 1938 "parser.tab.c"
    break;

  case 73: /* unario: '-' unario  */
#line 330 "src\\parser.y"
                                      { (yyval.expr) = expr_negativo((yyvsp[0].expr), LOC((yylsp[-1]))); }
#line 1944 "parser.tab.c"
    break;

  case 74: /* unario: "'nao'" unario  */
#line 331 "src\\parser.y"
                                      { (yyval.expr) = expr_nao((yyvsp[0].expr), LOC((yylsp[-1]))); }
#line 1950 "parser.tab.c"
    break;

  case 76: /* primario: "numero inteiro"  */
#line 336 "src\\parser.y"
                                      { (yyval.expr) = expr_literal_inteiro((yyvsp[0].inteiro)); }
#line 1956 "parser.tab.c"
    break;

  case 77: /* primario: "numero real"  */
#line 337 "src\\parser.y"
                                      { (yyval.expr) = expr_literal_real((yyvsp[0].texto)); }
#line 1962 "parser.tab.c"
    break;

  case 78: /* primario: "texto entre aspas"  */
#line 338 "src\\parser.y"
                                      { (yyval.expr) = expr_texto((yyvsp[0].texto)); }
#line 1968 "parser.tab.c"
    break;

  case 79: /* primario: "'verdadeiro'"  */
#line 339 "src\\parser.y"
                                      { (yyval.expr) = expr_booleano(1); }
#line 1974 "parser.tab.c"
    break;

  case 80: /* primario: "'falso'"  */
#line 340 "src\\parser.y"
                                      { (yyval.expr) = expr_booleano(0); }
#line 1980 "parser.tab.c"
    break;

  case 81: /* primario: "identificador"  */
#line 341 "src\\parser.y"
                                      { (yyval.expr) = expr_variavel((yyvsp[0].texto), LOC((yylsp[0]))); }
#line 1986 "parser.tab.c"
    break;

  case 82: /* primario: '(' expressao ')'  */
#line 342 "src\\parser.y"
                                      { (yyval.expr) = (yyvsp[-1].expr); }
#line 1992 "parser.tab.c"
    break;


#line 1996 "parser.tab.c"

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
  *++yylsp = yyloc;

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 345 "src\\parser.y"


/* ============================================================
 * ANALISE SEMANTICA E GERACAO DE CODIGO
 * ============================================================ */

static int numerico(Tipo t) { return t == TP_INTEIRO || t == TP_REAL; }

/* inteiro pode ser guardado em real; o contrario nao */
static int compativel(Tipo destino, Tipo origem) {
    return destino == origem || (destino == TP_REAL && origem == TP_INTEIRO);
}

static const char *simbolo_op(Operador op) {
    switch (op) {
        case OP_SOMA:  return "+";   case OP_SUB:   return "-";
        case OP_MUL:   return "*";   case OP_DIV:   return "/";
        case OP_MOD:   return "%";   case OP_IGUAL: return "==";
        case OP_DIF:   return "!=";  case OP_MENOR: return "<";
        case OP_MAIOR: return ">";   case OP_MENIG: return "<=";
        case OP_MAIG:  return ">=";  case OP_E:     return "e";
        default:       return "ou";
    }
}

/* ---------- construcao de expressoes ---------- */

static Expr expr_invalida(void) {
    Expr r; r.tipo = TP_INVALIDO; r.cod = g_dup("0"); r.zero = 0;
    return r;
}

static Expr expr_literal_inteiro(long v) {
    Expr r; r.tipo = TP_INTEIRO; r.cod = g_fmt("%ld", v); r.zero = (v == 0);
    return r;
}

static Expr expr_literal_real(char *texto) {
    Expr r; r.tipo = TP_REAL; r.cod = texto; r.zero = (strtod(texto, NULL) == 0.0);
    return r;
}

static Expr expr_texto(char *texto) {
    Expr r; r.tipo = TP_TEXTO; r.cod = texto; r.zero = 0;
    return r;
}

static Expr expr_booleano(int v) {
    Expr r; r.tipo = TP_BOOLEANO; r.cod = g_dup(v ? "1" : "0"); r.zero = 0;
    return r;
}

static Expr expr_variavel(char *nome, int lin, int col) {
    Simbolo *s = simbolo_buscar(nome);
    if (!s) {
        diag_erro_semantico(lin, col, "variavel '%s' nao foi declarada", nome);
        return expr_invalida();
    }
    s->usos++;
    Expr r; r.tipo = s->tipo; r.cod = s->nome_c; r.zero = 0;
    return r;
}

static Expr expr_negativo(Expr e, int lin, int col) {
    if (e.tipo == TP_INVALIDO) return e;
    if (!numerico(e.tipo)) {
        diag_erro_semantico(lin, col,
            "o sinal '-' exige valor numerico, mas recebeu %s", nome_tipo(e.tipo));
        return expr_invalida();
    }
    Expr r; r.tipo = e.tipo; r.cod = g_fmt("(-%s)", e.cod); r.zero = e.zero;
    return r;
}

static Expr expr_nao(Expr e, int lin, int col) {
    if (e.tipo == TP_INVALIDO) return e;
    if (e.tipo != TP_BOOLEANO) {
        diag_erro_semantico(lin, col,
            "o operador 'nao' exige valor booleano, mas recebeu %s", nome_tipo(e.tipo));
        return expr_invalida();
    }
    Expr r; r.tipo = TP_BOOLEANO; r.cod = g_fmt("(!%s)", e.cod); r.zero = 0;
    return r;
}

static Expr expr_binaria(Operador op, Expr a, Expr b, int lin, int col) {
    Expr r = expr_invalida();

    /* um operando ja invalido: o erro foi relatado, nao repete */
    if (a.tipo == TP_INVALIDO || b.tipo == TP_INVALIDO) return r;

    switch (op) {

    case OP_SOMA:
        if (a.tipo == TP_TEXTO && b.tipo == TP_TEXTO) {          /* concatenacao */
            r.tipo = TP_TEXTO;
            r.cod  = g_fmt("jab_concat(%s, %s)", a.cod, b.cod);
            return r;
        }
        /* fallthrough */
    case OP_SUB:
    case OP_MUL:
        if (!numerico(a.tipo) || !numerico(b.tipo)) {
            diag_erro_semantico(lin, col,
                "o operador '%s' exige operandos numericos%s, mas recebeu %s e %s",
                simbolo_op(op), op == OP_SOMA ? " (ou dois textos)" : "",
                nome_tipo(a.tipo), nome_tipo(b.tipo));
            return r;
        }
        r.tipo = (a.tipo == TP_REAL || b.tipo == TP_REAL) ? TP_REAL : TP_INTEIRO;
        r.cod  = g_fmt("(%s %s %s)", a.cod, simbolo_op(op), b.cod);
        return r;

    case OP_DIV:
        if (!numerico(a.tipo) || !numerico(b.tipo)) {
            diag_erro_semantico(lin, col,
                "o operador '/' exige operandos numericos, mas recebeu %s e %s",
                nome_tipo(a.tipo), nome_tipo(b.tipo));
            return r;
        }
        if (b.zero) {
            diag_erro_semantico(lin, col, "divisao por zero: o divisor e a constante 0");
            return r;
        }
        if (a.tipo == TP_INTEIRO && b.tipo == TP_INTEIRO) {      /* divisao inteira */
            r.tipo = TP_INTEIRO;
            r.cod  = g_fmt("jab_div_int(%s, %s)", a.cod, b.cod);
        } else {
            r.tipo = TP_REAL;
            r.cod  = g_fmt("jab_div_real(%s, %s)", a.cod, b.cod);
        }
        return r;

    case OP_MOD:
        if (a.tipo != TP_INTEIRO || b.tipo != TP_INTEIRO) {
            diag_erro_semantico(lin, col,
                "o operador '%%' exige operandos inteiros, mas recebeu %s e %s",
                nome_tipo(a.tipo), nome_tipo(b.tipo));
            return r;
        }
        if (b.zero) {
            diag_erro_semantico(lin, col, "divisao por zero: o divisor e a constante 0");
            return r;
        }
        r.tipo = TP_INTEIRO;
        r.cod  = g_fmt("jab_mod(%s, %s)", a.cod, b.cod);
        return r;

    case OP_MENOR: case OP_MAIOR: case OP_MENIG: case OP_MAIG:
        if (!numerico(a.tipo) || !numerico(b.tipo)) {
            diag_erro_semantico(lin, col,
                "o operador '%s' compara apenas numeros, mas recebeu %s e %s",
                simbolo_op(op), nome_tipo(a.tipo), nome_tipo(b.tipo));
            return r;
        }
        r.tipo = TP_BOOLEANO;
        r.cod  = g_fmt("(%s %s %s)", a.cod, simbolo_op(op), b.cod);
        return r;

    case OP_IGUAL: case OP_DIF:
        if (numerico(a.tipo) && numerico(b.tipo)) {
            r.cod = g_fmt("(%s %s %s)", a.cod, simbolo_op(op), b.cod);
        } else if (a.tipo == TP_TEXTO && b.tipo == TP_TEXTO) {
            r.cod = g_fmt("(strcmp(%s, %s) %s 0)", a.cod, b.cod, simbolo_op(op));
        } else if (a.tipo == TP_BOOLEANO && b.tipo == TP_BOOLEANO) {
            r.cod = g_fmt("(%s %s %s)", a.cod, simbolo_op(op), b.cod);
        } else {
            diag_erro_semantico(lin, col,
                "comparacao '%s' entre tipos incompativeis: %s e %s",
                simbolo_op(op), nome_tipo(a.tipo), nome_tipo(b.tipo));
            return expr_invalida();
        }
        r.tipo = TP_BOOLEANO;
        return r;

    case OP_E: case OP_OU:
        if (a.tipo != TP_BOOLEANO || b.tipo != TP_BOOLEANO) {
            diag_erro_semantico(lin, col,
                "o operador '%s' exige operandos booleanos, mas recebeu %s e %s",
                simbolo_op(op), nome_tipo(a.tipo), nome_tipo(b.tipo));
            return r;
        }
        r.tipo = TP_BOOLEANO;
        r.cod  = g_fmt("(%s %s %s)", a.cod, op == OP_E ? "&&" : "||", b.cod);
        return r;
    }
    return r;
}

/* ---------- declaracoes ---------- */

static const char *tipo_c(Tipo t) {
    return t == TP_REAL ? "double" : "int";    /* inteiro e booleano usam int */
}

/* Emite a declaracao em C, ja com o valor inicial (zero por padrao). */
static void emitir_declaracao(Simbolo *s, const char *valor_inicial) {
    if (s->tipo == TP_TEXTO) {
        g_emit("char %s[JAB_TEXTO] = \"\";", s->nome_c);
        if (valor_inicial) g_emit("jab_copia(%s, %s);", s->nome_c, valor_inicial);
    } else {
        g_emit("%s %s = %s;", tipo_c(s->tipo), s->nome_c,
               valor_inicial ? valor_inicial : (s->tipo == TP_REAL ? "0.0" : "0"));
    }
}

/* Valida o valor inicial: devolve o codigo C ou NULL (se invalido/ausente) */
static const char *validar_inicial(Tipo t, const char *nome, Expr *e, int lin, int col) {
    if (!e || e->tipo == TP_INVALIDO) return NULL;
    if (!compativel(t, e->tipo)) {
        diag_erro_semantico(lin, col,
            "valor inicial incompativel para '%s': esperado %s, recebido %s",
            nome, nome_tipo(t), nome_tipo(e->tipo));
        return NULL;
    }
    return e->cod;
}

static void declarar_variavel(Tipo t, char *nome, Expr *inicial, int lin, int col) {
    const char *valor = validar_inicial(t, nome, inicial, lin, col);
    Simbolo *s = simbolo_declarar(nome, t, CAT_VARIAVEL, lin, col);
    if (!s) return;
    if (valor) s->atribuicoes++;
    emitir_declaracao(s, valor);
}

static void declarar_constante(Tipo t, char *nome, Expr inicial, int lin, int col) {
    const char *valor = validar_inicial(t, nome, &inicial, lin, col);
    Simbolo *s = simbolo_declarar(nome, t, CAT_CONSTANTE, lin, col);
    if (!s) return;
    s->atribuicoes++;
    emitir_declaracao(s, valor);
}

/* ---------- comandos ---------- */

static void atribuir(char *nome, Expr e, int lin, int col) {
    Simbolo *s = simbolo_buscar(nome);
    if (!s) {
        diag_erro_semantico(lin, col, "variavel '%s' nao foi declarada", nome);
        return;
    }
    if (s->categoria == CAT_CONSTANTE) {
        diag_erro_semantico(lin, col,
            "nao e possivel alterar a constante '%s' (declarada na linha %d)",
            nome, s->linha);
        return;
    }
    s->atribuicoes++;
    if (e.tipo == TP_INVALIDO) return;
    if (!compativel(s->tipo, e.tipo)) {
        diag_erro_semantico(lin, col,
            "tipo incompativel na atribuicao a '%s': esperado %s, recebido %s",
            nome, nome_tipo(s->tipo), nome_tipo(e.tipo));
        return;
    }
    if (s->tipo == TP_TEXTO) g_emit("jab_copia(%s, %s);", s->nome_c, e.cod);
    else                     g_emit("%s = %s;", s->nome_c, e.cod);
}

static void ler_variavel(char *nome, int lin, int col) {
    Simbolo *s = simbolo_buscar(nome);
    if (!s) {
        diag_erro_semantico(lin, col, "variavel '%s' nao foi declarada", nome);
        return;
    }
    if (s->categoria == CAT_CONSTANTE) {
        diag_erro_semantico(lin, col,
            "nao e possivel ler um valor para a constante '%s'", nome);
        return;
    }
    s->atribuicoes++;
    switch (s->tipo) {
        case TP_INTEIRO:  g_emit("jab_leia_int(&%s);",   s->nome_c); break;
        case TP_REAL:     g_emit("jab_leia_real(&%s);",  s->nome_c); break;
        case TP_BOOLEANO: g_emit("jab_leia_bool(&%s);",  s->nome_c); break;
        default:          g_emit("jab_leia_texto(%s);",  s->nome_c); break;
    }
}

static void imprimir_argumento(Expr e) {
    switch (e.tipo) {
        case TP_REAL:     g_emit("jab_imprime_real(%s);",  e.cod); break;
        case TP_TEXTO:    g_emit("jab_imprime_texto(%s);", e.cod); break;
        case TP_BOOLEANO: g_emit("jab_imprime_bool(%s);",  e.cod); break;
        default:          g_emit("jab_imprime_int(%s);",   e.cod); break;
    }
}

static int condicao_valida(Expr c, const char *comando, int lin, int col) {
    if (c.tipo == TP_INVALIDO) return 0;
    if (c.tipo != TP_BOOLEANO) {
        diag_erro_semantico(lin, col,
            "a condicao do '%s' deve ser booleana, mas a expressao e do tipo %s",
            comando, nome_tipo(c.tipo));
        return 0;
    }
    return 1;
}

static void iniciar_se(Expr c, int lin, int col) {
    condicao_valida(c, "se", lin, col);
    g_emit("if (%s)", c.cod);
}

static void iniciar_enquanto(Expr c, int lin, int col) {
    condicao_valida(c, "enquanto", lin, col);
    g_emit("while (%s)", c.cod);
}

static void iniciar_para(char *nome, Expr de, Expr ate, long passo,
                         int lin, int col, int plin, int pcol) {
    Simbolo *s = simbolo_buscar(nome);
    int ok = 1;

    if (!s) {
        diag_erro_semantico(lin, col, "variavel '%s' nao foi declarada", nome);
        ok = 0;
    } else if (s->categoria == CAT_CONSTANTE) {
        diag_erro_semantico(lin, col,
            "a constante '%s' nao pode ser a variavel de controle do 'para'", nome);
        ok = 0;
    } else if (s->tipo != TP_INTEIRO) {
        diag_erro_semantico(lin, col,
            "a variavel de controle do 'para' deve ser inteira, mas '%s' e %s",
            nome, nome_tipo(s->tipo));
        ok = 0;
    } else {
        s->atribuicoes++;
        s->usos++;                 /* a variavel de controle conta como usada */
    }

    if (de.tipo != TP_INVALIDO && de.tipo != TP_INTEIRO) {
        diag_erro_semantico(lin, col,
            "o valor inicial do 'para' deve ser inteiro, mas e %s", nome_tipo(de.tipo));
        ok = 0;
    }
    if (ate.tipo != TP_INVALIDO && ate.tipo != TP_INTEIRO) {
        diag_erro_semantico(lin, col,
            "o limite do 'para' deve ser inteiro, mas e %s", nome_tipo(ate.tipo));
        ok = 0;
    }
    if (de.tipo == TP_INVALIDO || ate.tipo == TP_INVALIDO) ok = 0;
    if (passo == 0) {
        diag_erro_semantico(plin, pcol, "o passo do 'para' nao pode ser zero");
        ok = 0;
    }

    /* O limite e calculado UMA vez, num bloco C proprio (fechado depois
     * do corpo do laco, na regra 'para'). */
    int id = ++contador_para;
    g_emit("{");
    g_indent(1);
    if (ok) {
        g_emit("int jab_lim%d = %s;", id, ate.cod);
        g_emit("for (%s = %s; %s %s jab_lim%d; %s += %ld)",
               s->nome_c, de.cod, s->nome_c, passo > 0 ? "<=" : ">=", id,
               s->nome_c, passo);
    } else {
        g_emit("for (;;)   /* 'para' invalido: sem codigo (ha erros) */");
    }
}

/* ============================================================
 * TRATAMENTO DE ERROS SINTATICOS
 * ============================================================
 * O Bison monta mensagens em ingles ("syntax error, unexpected X,
 * expecting A or B"). Esta funcao as traduz para portugues. */

static char g_esperado[340];     /* lista de tokens esperados (traduzida) */

static void traduzir(const char *msg, char *saida, size_t n) {
    g_esperado[0] = '\0';
    char encontrado[160] = "", esperado[320] = "";
    const char *p = strstr(msg, "unexpected ");
    const char *q = strstr(msg, ", expecting ");

    if (p) {
        p += strlen("unexpected ");
        size_t tam = q ? (size_t)(q - p) : strlen(p);
        if (tam >= sizeof encontrado) tam = sizeof encontrado - 1;
        memcpy(encontrado, p, tam);
        encontrado[tam] = '\0';
    }
    if (q) snprintf(esperado, sizeof esperado, "%s", q + strlen(", expecting "));

    /* remove as aspas duplas que o Bison coloca nos nomes amigaveis */
    for (char *s = encontrado; *s; s++) if (*s == '"') memmove(s, s + 1, strlen(s));
    for (char *s = esperado;   *s; s++) if (*s == '"') memmove(s, s + 1, strlen(s));

    if (!strcmp(encontrado, "end of file")) snprintf(encontrado, sizeof encontrado, "fim do arquivo");
    {   /* "end of file" tambem pode aparecer na lista de esperados */
        char *eof = strstr(esperado, "end of file");
        if (eof) {
            char resto[320];
            snprintf(resto, sizeof resto, "%s", eof + strlen("end of file"));
            snprintf(eof, sizeof esperado - (size_t)(eof - esperado), "fim do arquivo%s", resto);
        }
    }

    /* Monta a lista de esperados em portugues ("A ou B ou C").
     * Operadores logicos 'e'/'ou' sao possiveis depois de qualquer
     * expressao; quando ha outras opcoes (')' ';' ','), eles so poluem
     * a mensagem e sao omitidos. */
    char final[340] = ""; size_t k = 0;
    char copia[320]; snprintf(copia, sizeof copia, "%s", esperado);
    int outros = 0;
    for (char *t = copia, *fim; t; t = fim ? fim + 4 : NULL) {
        fim = strstr(t, " or ");
        size_t len = fim ? (size_t)(fim - t) : strlen(t);
        if (!(len == 3 && !strncmp(t, "'e'", 3)) && !(len == 4 && !strncmp(t, "'ou'", 4))) outros++;
    }
    for (char *t = copia, *fim; t; t = fim ? fim + 4 : NULL) {
        fim = strstr(t, " or ");
        size_t len = fim ? (size_t)(fim - t) : strlen(t);
        int logico = (len == 3 && !strncmp(t, "'e'", 3)) || (len == 4 && !strncmp(t, "'ou'", 4));
        if (logico && outros) continue;
        if (k && k + 5 < sizeof final) { memcpy(final + k, " ou ", 4); k += 4; }
        if (k + len + 1 < sizeof final) { memcpy(final + k, t, len); k += len; }
    }
    final[k] = '\0';
    snprintf(g_esperado, sizeof g_esperado, "%s", final);

    /* se o token inesperado e um identificador/numero/texto, mostra o lexema */
    char detalhe[200] = "";
    if (yychar > 0 && (!strncmp(encontrado, "identificador", 13) ||
                       !strncmp(encontrado, "numero", 6) ||
                       !strncmp(encontrado, "texto", 5)))
        snprintf(detalhe, sizeof detalhe, " '%s'", lexer_ultimo_lexema());

    if (!p)              snprintf(saida, n, "erro de sintaxe");
    else if (yychar == 0 && !final[0])
                         snprintf(saida, n, "fim do arquivo inesperado: "
                                  "provavelmente falta fechar um bloco com '}'");
    else if (final[0])   snprintf(saida, n, "encontrado %s%s, mas o esperado era %s",
                                  encontrado, detalhe, final);
    else                 snprintf(saida, n, "encontrado %s%s em posicao inesperada",
                                  encontrado, detalhe);
}

void yyerror(const char *msg) {
    char texto[800];

    /* Se o token que causou o erro ja foi condenado pelo analisador lexico
     * (ERRO_LEXICO), o problema ja foi relatado: evita mensagem duplicada. */
    if (yychar == ERRO_LEXICO) return;
    if (yychar == 0 && lexer_eof_por_erro()) return;   /* ex.: comentario nao fechado */

    traduzir(msg, texto, sizeof texto);

    /* Caso classico: o ';' foi esquecido no fim de uma linha. O Bison so
     * percebe quando le o PRIMEIRO token da linha seguinte; o erro e entao
     * apontado para o fim da linha anterior, onde o programador deve
     * corrigir. */
    int lin_ant, col_ant;
    lexer_fim_token_anterior(&lin_ant, &col_ant);
    if (strstr(g_esperado, "';'") && lin_ant > 0 && yylloc.first_line > lin_ant) {
        diag_erro_sintatico(lin_ant, col_ant,
            yychar == 0 ? "faltou ';' no final do comando (antes do fim do arquivo)"
                        : "faltou ';' no final do comando (o proximo comando comeca na linha %d)",
            yylloc.first_line);
        return;
    }
    diag_erro_sintatico(yylloc.first_line, yylloc.first_column, "%s", texto);
}
