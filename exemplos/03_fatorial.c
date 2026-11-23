/* ============================================================
 * Codigo C gerado automaticamente pelo compilador JABUTI
 * Fonte    : exemplos/03_fatorial.jab
 * Programa : Fatorial
 * NAO EDITE: altere o arquivo .jab e compile novamente.
 * ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JAB_TEXTO 256   /* tamanho maximo de uma variavel texto */

static inline void jab_erro_exec(const char *msg) {
    fflush(stdout);
    fprintf(stderr, "Erro de execucao: %s\n", msg);
    exit(1);
}

/* ---- aritmetica protegida contra divisao por zero ---- */
static inline int jab_div_int(int a, int b) {
    if (b == 0) jab_erro_exec("divisao por zero");
    return a / b;
}
static inline double jab_div_real(double a, double b) {
    if (b == 0.0) jab_erro_exec("divisao por zero");
    return a / b;
}
static inline int jab_mod(int a, int b) {
    if (b == 0) jab_erro_exec("divisao por zero (operador %)");
    return a % b;
}

/* ---- textos ---- */
static inline const char *jab_concat(const char *a, const char *b) {
    static char pilha[8][2 * JAB_TEXTO];   /* 8 temporarios rotativos */
    static int  prox = 0;
    char *r = pilha[prox];
    prox = (prox + 1) % 8;
    snprintf(r, 2 * JAB_TEXTO, "%s%s", a, b);
    return r;
}
static inline void jab_copia(char *dest, const char *orig) {
    snprintf(dest, JAB_TEXTO, "%s", orig);
}

/* ---- saida ---- */
static inline void jab_imprime_int(int v)            { printf("%d", v); }
static inline void jab_imprime_texto(const char *s)  { fputs(s, stdout); }
static inline void jab_imprime_bool(int v)           { fputs(v ? "verdadeiro" : "falso", stdout); }
static inline void jab_nova_linha(void)              { putchar('\n'); }
static inline void jab_imprime_real(double v) {
    char buf[64];
    snprintf(buf, sizeof buf, "%.10g", v);
    fputs(buf, stdout);
    if (!strpbrk(buf, ".eEnN")) fputs(".0", stdout);   /* 5 -> 5.0 */
}

/* ---- entrada ---- */
static inline void jab_leia_int(int *v) {
    fflush(stdout);
    if (scanf("%d", v) != 1) jab_erro_exec("entrada invalida: esperado um numero inteiro");
}
static inline void jab_leia_real(double *v) {
    fflush(stdout);
    if (scanf("%lf", v) != 1) jab_erro_exec("entrada invalida: esperado um numero real");
}
static inline void jab_leia_texto(char *d) {
    fflush(stdout);
    if (scanf(" %255[^\n]", d) != 1) jab_erro_exec("entrada invalida: esperado um texto");
}
static inline void jab_leia_bool(int *v) {
    char b[32];
    fflush(stdout);
    if (scanf("%31s", b) != 1) jab_erro_exec("entrada invalida: esperado verdadeiro ou falso");
    if (!strcmp(b, "verdadeiro") || !strcmp(b, "1")) *v = 1;
    else if (!strcmp(b, "falso") || !strcmp(b, "0")) *v = 0;
    else jab_erro_exec("entrada invalida: esperado verdadeiro ou falso");
}

int main(void)
{
    int v_n = 0;
    int v_i = 0;
    int v_fat = 1;
    jab_imprime_texto("Digite um numero inteiro entre 0 e 12:");
    jab_nova_linha();
    jab_leia_int(&v_n);
    if (((v_n < 0) || (v_n > 12)))
    {
        jab_imprime_texto("Valor fora do intervalo permitido.");
        jab_nova_linha();
    }
    else
    {
        {
            int jab_lim1 = v_n;
            for (v_i = 2; v_i <= jab_lim1; v_i += 1)
            {
                v_fat = (v_fat * v_i);
            }
        }
        jab_imprime_int(v_n);
        jab_imprime_texto("! = ");
        jab_imprime_int(v_fat);
        jab_nova_linha();
    }
    return 0;
}
