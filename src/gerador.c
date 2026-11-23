/* ============================================================
 * gerador.c - Implementacao do gerador de codigo C
 * ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "gerador.h"

/* ------------------------------------------------------------
 * Pool de textos temporarios (evita free() espalhado nas acoes)
 * ------------------------------------------------------------ */
typedef struct No { struct No *prox; char dados[1]; } No;
static No *pool = NULL;

static char *alocar(size_t n) {
    No *no = (No *)malloc(sizeof(No) + n);
    if (!no) { fprintf(stderr, "Erro: memoria insuficiente\n"); exit(2); }
    no->prox = pool;
    pool = no;
    return no->dados;
}

char *g_dup(const char *s) {
    char *p = alocar(strlen(s) + 1);
    strcpy(p, s);
    return p;
}

char *g_fmt(const char *fmt, ...) {
    va_list ap, ap2;
    va_start(ap, fmt);
    va_copy(ap2, ap);
    int n = vsnprintf(NULL, 0, fmt, ap);
    va_end(ap);
    char *p = alocar((size_t)n + 1);
    vsnprintf(p, (size_t)n + 1, fmt, ap2);
    va_end(ap2);
    return p;
}

/* ------------------------------------------------------------
 * Buffer do corpo do programa (a funcao main gerada)
 * ------------------------------------------------------------ */
static char  *corpo = NULL;
static size_t tam = 0, cap = 0;
static int    nivel_indent = 0;
static char   nome_programa[128] = "";

static void anexar(const char *s, size_t n) {
    if (tam + n + 1 > cap) {
        cap = (tam + n + 1) * 2;
        corpo = (char *)realloc(corpo, cap);
        if (!corpo) { fprintf(stderr, "Erro: memoria insuficiente\n"); exit(2); }
    }
    memcpy(corpo + tam, s, n);
    tam += n;
    corpo[tam] = '\0';
}

void g_programa(const char *nome) {
    if (nome) snprintf(nome_programa, sizeof nome_programa, "%s", nome);
}

void g_indent(int delta) { nivel_indent += delta; }

void g_emit(const char *fmt, ...) {
    char linha[2048];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(linha, sizeof linha, fmt, ap);
    va_end(ap);

    for (int i = 0; i < nivel_indent; i++) anexar("    ", 4);
    anexar(linha, strlen(linha));
    anexar("\n", 1);
}

/* ------------------------------------------------------------
 * "Runtime" do JABUTI: funcoes auxiliares copiadas para o
 * inicio de todo programa C gerado. Assim o resultado e um
 * unico arquivo .c, que compila em qualquer lugar com o gcc.
 * ------------------------------------------------------------ */
static const char RUNTIME[] =
"#include <stdio.h>\n"
"#include <stdlib.h>\n"
"#include <string.h>\n"
"\n"
"#define JAB_TEXTO 256   /* tamanho maximo de uma variavel texto */\n"
"\n"
"static inline void jab_erro_exec(const char *msg) {\n"
"    fflush(stdout);\n"
"    fprintf(stderr, \"Erro de execucao: %s\\n\", msg);\n"
"    exit(1);\n"
"}\n"
"\n"
"/* ---- aritmetica protegida contra divisao por zero ---- */\n"
"static inline int jab_div_int(int a, int b) {\n"
"    if (b == 0) jab_erro_exec(\"divisao por zero\");\n"
"    return a / b;\n"
"}\n"
"static inline double jab_div_real(double a, double b) {\n"
"    if (b == 0.0) jab_erro_exec(\"divisao por zero\");\n"
"    return a / b;\n"
"}\n"
"static inline int jab_mod(int a, int b) {\n"
"    if (b == 0) jab_erro_exec(\"divisao por zero (operador %)\");\n"
"    return a % b;\n"
"}\n"
"\n"
"/* ---- textos ---- */\n"
"static inline const char *jab_concat(const char *a, const char *b) {\n"
"    static char pilha[8][2 * JAB_TEXTO];   /* 8 temporarios rotativos */\n"
"    static int  prox = 0;\n"
"    char *r = pilha[prox];\n"
"    prox = (prox + 1) % 8;\n"
"    snprintf(r, 2 * JAB_TEXTO, \"%s%s\", a, b);\n"
"    return r;\n"
"}\n"
"static inline void jab_copia(char *dest, const char *orig) {\n"
"    snprintf(dest, JAB_TEXTO, \"%s\", orig);\n"
"}\n"
"\n"
"/* ---- saida ---- */\n"
"static inline void jab_imprime_int(int v)            { printf(\"%d\", v); }\n"
"static inline void jab_imprime_texto(const char *s)  { fputs(s, stdout); }\n"
"static inline void jab_imprime_bool(int v)           { fputs(v ? \"verdadeiro\" : \"falso\", stdout); }\n"
"static inline void jab_nova_linha(void)              { putchar('\\n'); }\n"
"static inline void jab_imprime_real(double v) {\n"
"    char buf[64];\n"
"    snprintf(buf, sizeof buf, \"%.10g\", v);\n"
"    fputs(buf, stdout);\n"
"    if (!strpbrk(buf, \".eEnN\")) fputs(\".0\", stdout);   /* 5 -> 5.0 */\n"
"}\n"
"\n"
"/* ---- entrada ---- */\n"
"static inline void jab_leia_int(int *v) {\n"
"    fflush(stdout);\n"
"    if (scanf(\"%d\", v) != 1) jab_erro_exec(\"entrada invalida: esperado um numero inteiro\");\n"
"}\n"
"static inline void jab_leia_real(double *v) {\n"
"    fflush(stdout);\n"
"    if (scanf(\"%lf\", v) != 1) jab_erro_exec(\"entrada invalida: esperado um numero real\");\n"
"}\n"
"static inline void jab_leia_texto(char *d) {\n"
"    fflush(stdout);\n"
"    if (scanf(\" %255[^\\n]\", d) != 1) jab_erro_exec(\"entrada invalida: esperado um texto\");\n"
"}\n"
"static inline void jab_leia_bool(int *v) {\n"
"    char b[32];\n"
"    fflush(stdout);\n"
"    if (scanf(\"%31s\", b) != 1) jab_erro_exec(\"entrada invalida: esperado verdadeiro ou falso\");\n"
"    if (!strcmp(b, \"verdadeiro\") || !strcmp(b, \"1\")) *v = 1;\n"
"    else if (!strcmp(b, \"falso\") || !strcmp(b, \"0\")) *v = 0;\n"
"    else jab_erro_exec(\"entrada invalida: esperado verdadeiro ou falso\");\n"
"}\n";

int g_salvar(const char *caminho_c, const char *arquivo_fonte) {
    FILE *f = fopen(caminho_c, "wb");
    if (!f) return 1;

    fprintf(f, "/* ============================================================\n");
    fprintf(f, " * Codigo C gerado automaticamente pelo compilador JABUTI\n");
    fprintf(f, " * Fonte    : %s\n", arquivo_fonte);
    if (nome_programa[0])
        fprintf(f, " * Programa : %s\n", nome_programa);
    fprintf(f, " * NAO EDITE: altere o arquivo .jab e compile novamente.\n");
    fprintf(f, " * ============================================================ */\n\n");
    fputs(RUNTIME, f);
    fputs("\nint main(void)\n", f);
    if (corpo) fputs(corpo, f);
    fclose(f);
    return 0;
}

void g_liberar(void) {
    while (pool) {
        No *prox = pool->prox;
        free(pool);
        pool = prox;
    }
    free(corpo);
    corpo = NULL; tam = cap = 0; nivel_indent = 0;
}
