/* ============================================================
 * diagnostico.c - Implementacao das mensagens de erro/aviso
 * ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "diagnostico.h"

static const char *arquivo_atual = "";
static const char *fonte         = "";
static int n_lexicos = 0, n_sintaticos = 0, n_semanticos = 0, n_avisos = 0;

void diag_iniciar(const char *arquivo, const char *texto_fonte) {
    arquivo_atual = arquivo;
    fonte = texto_fonte;
    n_lexicos = n_sintaticos = n_semanticos = n_avisos = 0;
}

/* Imprime a linha 'n' do codigo-fonte e, abaixo dela, um '^' na coluna. */
static void mostrar_contexto(int linha, int coluna) {
    const char *p = fonte;
    int atual = 1;

    if (linha < 1) return;
    while (atual < linha && *p) {
        if (*p == '\n') atual++;
        p++;
    }
    if (atual != linha) return;

    fprintf(stderr, "  %4d | ", linha);
    for (; *p && *p != '\n' && *p != '\r'; p++)
        fputc(*p == '\t' ? ' ' : *p, stderr);
    fputc('\n', stderr);

    fprintf(stderr, "       | ");
    for (int i = 1; i < coluna; i++) fputc(' ', stderr);
    fputs("^\n", stderr);
}

static void relatar(const char *rotulo, int linha, int coluna,
                    const char *fmt, va_list ap) {
    char msg[600];
    vsnprintf(msg, sizeof msg, fmt, ap);

    fflush(stdout);   /* mantem a ordem das mensagens quando a saida e redirecionada */
    fprintf(stderr, "[%s] %s:%d:%d: %s\n", rotulo, arquivo_atual, linha, coluna, msg);
    mostrar_contexto(linha, coluna);
}

void diag_erro_lexico(int linha, int coluna, const char *fmt, ...) {
    va_list ap; va_start(ap, fmt);
    relatar("ERRO LEXICO", linha, coluna, fmt, ap);
    va_end(ap);
    n_lexicos++;
}

void diag_erro_sintatico(int linha, int coluna, const char *fmt, ...) {
    va_list ap; va_start(ap, fmt);
    relatar("ERRO SINTATICO", linha, coluna, fmt, ap);
    va_end(ap);
    n_sintaticos++;
}

void diag_erro_semantico(int linha, int coluna, const char *fmt, ...) {
    va_list ap; va_start(ap, fmt);
    relatar("ERRO SEMANTICO", linha, coluna, fmt, ap);
    va_end(ap);
    n_semanticos++;
}

void diag_aviso(int linha, int coluna, const char *fmt, ...) {
    va_list ap; va_start(ap, fmt);
    relatar("AVISO", linha, coluna, fmt, ap);
    va_end(ap);
    n_avisos++;
}

int diag_total_lexicos(void)    { return n_lexicos; }
int diag_total_sintaticos(void) { return n_sintaticos; }
int diag_total_semanticos(void) { return n_semanticos; }
int diag_total_avisos(void)     { return n_avisos; }
int diag_total_erros(void)      { return n_lexicos + n_sintaticos + n_semanticos; }
