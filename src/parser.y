/* ============================================================
 * parser.y - Analisador Sintatico e Semantico do compilador JABUTI
 * ============================================================
 * Disciplina: Compiladores
 * Ferramenta: Bison (GNU Parser Generator)
 *
 * Define a GRAMATICA da linguagem JABUTI (veja o relatorio, secao
 * 3.2, para a versao em EBNF) e, em cada regra, as acoes que
 *   (1) fazem a ANALISE SEMANTICA: declaracao previa, compatibilidade
 *       de tipos, constantes, condicoes booleanas, divisao por zero;
 *   (2) GERAM O CODIGO C correspondente (traducao dirigida pela sintaxe).
 *
 * A precedencia dos operadores esta codificada na PROPRIA gramatica,
 * em niveis (expressao > conjuncao > igualdade > relacional > soma >
 * termo > unario > primario), sem uso de %left/%right. Por isso o
 * Bison deve acusar ZERO conflitos (%expect 0).
 *
 * Base: parser do projeto MiniLang (colega), ampliado com geracao de
 * codigo, 'para', 'constante', 'leia'/'escreva' com varios argumentos,
 * escopo de blocos, texto, resto (%) e recuperacao de erros por
 * "modo panico".
 * ============================================================ */

%code requires {
    #include "simbolos.h"
    #include "gerador.h"
}

%{
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
%}

%define parse.error verbose
%locations
%expect 0
%start programa

/* ------------------------------------------------------------
 * Tipos dos valores semanticos
 * ------------------------------------------------------------ */
%union {
    long   inteiro;     /* LIT_INTEIRO, passo do 'para'            */
    char  *texto;       /* IDENTIFICADOR, LIT_REAL, LIT_CADEIA     */
    Tipo   tipo;        /* nao-terminal 'tipo'                     */
    Expr   expr;        /* nao-terminais de expressao              */
}

/* ------------------------------------------------------------
 * Tokens. O texto entre aspas e o NOME AMIGAVEL usado nas
 * mensagens de erro sintatico (ex.: encontrado ')' esperado ';').
 * ------------------------------------------------------------ */
%token PROGRAMA    "'programa'"
%token CONSTANTE   "'constante'"
%token T_INTEIRO   "'inteiro'"
%token T_REAL      "'real'"
%token T_TEXTO     "'texto'"
%token T_BOOLEANO  "'booleano'"
%token VERDADEIRO  "'verdadeiro'"
%token FALSO       "'falso'"
%token SE          "'se'"
%token SENAO       "'senao'"
%token ENQUANTO    "'enquanto'"
%token PARA        "'para'"
%token DE          "'de'"
%token ATE         "'ate'"
%token PASSO       "'passo'"
%token LEIA        "'leia'"
%token ESCREVA     "'escreva'"
%token ESCREVAL    "'escreval'"
%token E           "'e'"
%token OU          "'ou'"
%token NAO         "'nao'"
%token IGUAL       "'=='"
%token DIFERENTE   "'!='"
%token MENOR_IGUAL "'<='"
%token MAIOR_IGUAL "'>='"
%token ERRO_LEXICO "caractere invalido"

%token <texto>   IDENTIFICADOR "identificador"
%token <texto>   LIT_REAL      "numero real"
%token <texto>   LIT_CADEIA    "texto entre aspas"
%token <inteiro> LIT_INTEIRO   "numero inteiro"

%type <tipo>    tipo
%type <texto>   nome_programa
%type <inteiro> passo_opt
%type <expr>    expressao conjuncao igualdade relacional soma termo unario primario

%%

/* ============================================================
 * ESTRUTURA DO PROGRAMA
 * ============================================================ */

programa:
    PROGRAMA nome_programa '{'
        {
            g_programa($2);
            g_emit("{");
            g_indent(1);
            escopo_entrar();
        }
    lista_comandos '}'
        {
            g_emit("return 0;");
            g_indent(-1);
            g_emit("}");
            escopo_sair();
        }
    ;

nome_programa:
      %empty            { $$ = NULL; }
    | IDENTIFICADOR     { $$ = $1; }
    ;

lista_comandos:
      %empty
    | lista_comandos comando
    ;

comando:
      declaracao
    | atribuicao
    | entrada
    | saida
    | condicional
    | repeticao
    | para
    | bloco
    /* Recuperacao de erros (modo panico): o token especial 'error' faz o
     * Bison descartar simbolos ate achar um ponto de sincronismo.
     *  - 'error ;'  : o erro foi dentro do comando; consome ate o ';'.
     *  - 'error'    : o proprio token que causou o erro ja pode iniciar
     *                 o proximo comando (ou fechar o bloco), como no caso
     *                 classico do ';' esquecido no fim da linha anterior. */
    | error ';'         { yyerrok; }
    | error
    ;

/* ============================================================
 * DECLARACOES
 * ============================================================ */

declaracao:
      tipo { tipo_corrente = $1; } lista_declaradores ';'
    | CONSTANTE tipo IDENTIFICADOR '=' expressao ';'
        { declarar_constante($2, $3, $5, LOC(@3)); }
    ;

tipo:
      T_INTEIRO         { $$ = TP_INTEIRO; }
    | T_REAL            { $$ = TP_REAL; }
    | T_TEXTO           { $$ = TP_TEXTO; }
    | T_BOOLEANO        { $$ = TP_BOOLEANO; }
    ;

lista_declaradores:
      declarador
    | lista_declaradores ',' declarador
    ;

declarador:
      IDENTIFICADOR
        { declarar_variavel(tipo_corrente, $1, NULL, LOC(@1)); }
    | IDENTIFICADOR '=' expressao
        { declarar_variavel(tipo_corrente, $1, &$3, LOC(@1)); }
    ;

/* ============================================================
 * COMANDOS SIMPLES
 * ============================================================ */

atribuicao:
    IDENTIFICADOR '=' expressao ';'
        { atribuir($1, $3, LOC(@1)); }
    ;

entrada:
    LEIA '(' lista_leitura ')' ';'
    ;

lista_leitura:
      IDENTIFICADOR                      { ler_variavel($1, LOC(@1)); }
    | lista_leitura ',' IDENTIFICADOR    { ler_variavel($3, LOC(@3)); }
    ;

saida:
      ESCREVA  '(' lista_argumentos ')' ';'
    | ESCREVAL '(' lista_argumentos ')' ';'   { g_emit("jab_nova_linha();"); }
    | ESCREVAL '(' ')' ';'                    { g_emit("jab_nova_linha();"); }
    ;

lista_argumentos:
      expressao                          { imprimir_argumento($1); }
    | lista_argumentos ',' expressao     { imprimir_argumento($3); }
    ;

/* ============================================================
 * ESTRUTURAS DE CONTROLE
 * ============================================================
 * Os blocos sao obrigatoriamente delimitados por chaves; por isso a
 * gramatica NAO sofre do problema do "else pendente".
 *
 * Nao ha regras 'error' dentro dos parenteses de se/enquanto: se um
 * ')' esquecido fosse tratado ali, o Bison descartaria o corpo do
 * bloco ate achar outro ')'. Com a recuperacao generica ('comando:
 * error'), o '{' que vem depois do erro simplesmente abre um bloco e
 * a analise segue normalmente. */

condicional:
      SE '(' expressao ')'  { iniciar_se($3, LOC(@3)); }
        bloco senao_opt
    ;

senao_opt:
      %empty
    | SENAO { g_emit("else"); } senao_corpo
    ;

senao_corpo:
      bloco
    | condicional                               /* senao se (...) { } */
    ;

repeticao:
      ENQUANTO '(' expressao ')'  { iniciar_enquanto($3, LOC(@3)); }
        bloco
    ;

para:
    PARA '(' IDENTIFICADOR DE expressao ATE expressao passo_opt ')'
        { iniciar_para($3, $5, $7, $8, LOC(@3), LOC(@8)); }
      bloco
        { g_indent(-1); g_emit("}"); }          /* fecha o bloco do limite */
    ;

passo_opt:
      %empty                        { $$ = 1; }
    | PASSO LIT_INTEIRO             { $$ = $2; }
    | PASSO '-' LIT_INTEIRO         { $$ = -$3; }
    ;

bloco:
    '{'
        { escopo_entrar(); g_emit("{"); g_indent(1); }
    lista_comandos '}'
        { escopo_sair();   g_indent(-1); g_emit("}"); }
    ;

/* ============================================================
 * EXPRESSOES (um nivel por precedencia, do menor para o maior)
 * ============================================================ */

expressao:
      expressao OU conjuncao        { $$ = expr_binaria(OP_OU, $1, $3, LOC(@2)); }
    | conjuncao
    ;

conjuncao:
      conjuncao E igualdade         { $$ = expr_binaria(OP_E, $1, $3, LOC(@2)); }
    | igualdade
    ;

igualdade:
      igualdade IGUAL relacional      { $$ = expr_binaria(OP_IGUAL, $1, $3, LOC(@2)); }
    | igualdade DIFERENTE relacional  { $$ = expr_binaria(OP_DIF,   $1, $3, LOC(@2)); }
    | relacional
    ;

relacional:
      relacional '<' soma             { $$ = expr_binaria(OP_MENOR, $1, $3, LOC(@2)); }
    | relacional '>' soma             { $$ = expr_binaria(OP_MAIOR, $1, $3, LOC(@2)); }
    | relacional MENOR_IGUAL soma     { $$ = expr_binaria(OP_MENIG, $1, $3, LOC(@2)); }
    | relacional MAIOR_IGUAL soma     { $$ = expr_binaria(OP_MAIG,  $1, $3, LOC(@2)); }
    | soma
    ;

soma:
      soma '+' termo                  { $$ = expr_binaria(OP_SOMA, $1, $3, LOC(@2)); }
    | soma '-' termo                  { $$ = expr_binaria(OP_SUB,  $1, $3, LOC(@2)); }
    | termo
    ;

termo:
      termo '*' unario                { $$ = expr_binaria(OP_MUL, $1, $3, LOC(@2)); }
    | termo '/' unario                { $$ = expr_binaria(OP_DIV, $1, $3, LOC(@2)); }
    | termo '%' unario                { $$ = expr_binaria(OP_MOD, $1, $3, LOC(@2)); }
    | unario
    ;

unario:
      '-' unario                      { $$ = expr_negativo($2, LOC(@1)); }
    | NAO unario                      { $$ = expr_nao($2, LOC(@1)); }
    | primario
    ;

primario:
      LIT_INTEIRO                     { $$ = expr_literal_inteiro($1); }
    | LIT_REAL                        { $$ = expr_literal_real($1); }
    | LIT_CADEIA                      { $$ = expr_texto($1); }
    | VERDADEIRO                      { $$ = expr_booleano(1); }
    | FALSO                           { $$ = expr_booleano(0); }
    | IDENTIFICADOR                   { $$ = expr_variavel($1, LOC(@1)); }
    | '(' expressao ')'               { $$ = $2; }
    ;

%%

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
