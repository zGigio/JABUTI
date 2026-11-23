/* ============================================================
 * Codigo C gerado automaticamente pelo compilador JABUTI
 * Fonte    : exemplos/06_completo.jab
 * Programa : Completo
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
    char v_SAUDACAO[JAB_TEXTO] = "";
    jab_copia(v_SAUDACAO, "Ola, ");
    double v_LIMITE_IMC = 25.0;
    char v_nome[JAB_TEXTO] = "";
    int v_idade = 0;
    int v_anos_para_100 = 0;
    double v_peso = 0.0;
    double v_altura = 0.0;
    double v_imc = 0.0;
    int v_maior_de_idade = 0;
    int v_tem_nome = 0;
    int v_acima_do_peso = 0;
    jab_imprime_texto("Qual o seu nome?");
    jab_nova_linha();
    jab_leia_texto(v_nome);
    jab_imprime_texto("Qual a sua idade?");
    jab_nova_linha();
    jab_leia_int(&v_idade);
    jab_imprime_texto("Qual o seu peso (kg)?");
    jab_nova_linha();
    jab_leia_real(&v_peso);
    jab_imprime_texto("Qual a sua altura (m)?");
    jab_nova_linha();
    jab_leia_real(&v_altura);
    v_tem_nome = (strcmp(v_nome, "") != 0);
    v_maior_de_idade = (v_idade >= 18);
    v_imc = jab_div_real(v_peso, (v_altura * v_altura));
    v_acima_do_peso = (v_imc > v_LIMITE_IMC);
    jab_imprime_texto(jab_concat(jab_concat(v_SAUDACAO, v_nome), "!"));
    jab_nova_linha();
    if ((v_tem_nome && v_maior_de_idade))
    {
        jab_imprime_texto("Voce e maior de idade.");
        jab_nova_linha();
    }
    else
    if ((!v_maior_de_idade))
    {
        jab_imprime_texto("Voce e menor de idade.");
        jab_nova_linha();
    }
    jab_imprime_texto("Seu IMC e ");
    jab_imprime_real(v_imc);
    jab_nova_linha();
    if ((v_acima_do_peso || (v_imc < 18.5)))
    {
        jab_imprime_texto("Atencao: IMC fora da faixa ideal.");
        jab_nova_linha();
    }
    else
    {
        jab_imprime_texto("IMC dentro da faixa ideal.");
        jab_nova_linha();
    }
    {
        int v2_idade = 100;
        jab_imprime_texto("Idade dentro do bloco: ");
        jab_imprime_int(v2_idade);
        jab_nova_linha();
    }
    jab_imprime_texto("Idade fora do bloco: ");
    jab_imprime_int(v_idade);
    jab_nova_linha();
    v_anos_para_100 = 0;
    while (((v_idade + v_anos_para_100) < 100))
    {
        v_anos_para_100 = (v_anos_para_100 + 1);
    }
    jab_imprime_texto("Faltam ");
    jab_imprime_int(v_anos_para_100);
    jab_imprime_texto(" anos para voce fazer 100.");
    jab_nova_linha();
    jab_imprime_texto("Divisao inteira 17 / 5 = ");
    jab_imprime_int(jab_div_int(17, 5));
    jab_imprime_texto(" e resto ");
    jab_imprime_int(jab_mod(17, 5));
    jab_nova_linha();
    jab_imprime_texto("Divisao real   17 / 5.0 = ");
    jab_imprime_real(jab_div_real(17, 5.0));
    jab_nova_linha();
    return 0;
}
