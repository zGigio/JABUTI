/* ============================================================
 * simbolos.c - Implementacao da tabela de simbolos
 * ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simbolos.h"
#include "diagnostico.h"

static Simbolo **tab   = NULL;   /* vetor de ponteiros (os registros nao se movem) */
static int       total = 0;
static int       capac = 0;
static int       nivel = 0;      /* 0 = fora do programa; 1 = bloco principal */

const char *nome_tipo(Tipo t) {
    switch (t) {
        case TP_INTEIRO:  return "inteiro";
        case TP_REAL:     return "real";
        case TP_TEXTO:    return "texto";
        case TP_BOOLEANO: return "booleano";
        default:          return "invalido";
    }
}

void tabela_iniciar(void) {
    tab = NULL; total = capac = nivel = 0;
}

void tabela_liberar(void) {
    for (int i = 0; i < total; i++) {
        free(tab[i]->nome);
        free(tab[i]->nome_c);
        free(tab[i]);
    }
    free(tab);
    tab = NULL; total = capac = nivel = 0;
}

void escopo_entrar(void) {
    nivel++;
}

/* Ao fechar um bloco: avisa sobre simbolos nunca lidos e os desativa.
 * Os simbolos ativos ficam em ordem crescente de nivel, entao os do
 * bloco que esta sendo fechado formam um trecho contiguo no final. */
void escopo_sair(void) {
    int ini = total;
    while (ini > 0 && (!tab[ini - 1]->ativo || tab[ini - 1]->nivel >= nivel))
        ini--;

    for (int i = ini; i < total; i++) {
        Simbolo *s = tab[i];
        if (!s->ativo || s->nivel != nivel) continue;
        if (s->usos == 0) {
            int constante   = (s->categoria == CAT_CONSTANTE);
            int so_escrita  = (!constante && s->atribuicoes > 0);
            if (so_escrita)
                diag_aviso(s->linha, s->coluna,
                           "variavel '%s' recebe valor mas nunca e lida", s->nome);
            else
                diag_aviso(s->linha, s->coluna,
                           "%s '%s' declarada mas nunca utilizada",
                           constante ? "constante" : "variavel", s->nome);
        }
        s->ativo = 0;
    }
    if (nivel > 0) nivel--;
}

Simbolo *simbolo_buscar(const char *nome) {
    for (int i = total - 1; i >= 0; i--)
        if (tab[i]->ativo && strcmp(tab[i]->nome, nome) == 0)
            return tab[i];
    return NULL;
}

static char *copiar(const char *s) {
    char *p = (char *)malloc(strlen(s) + 1);
    if (!p) { fprintf(stderr, "Erro: memoria insuficiente\n"); exit(2); }
    strcpy(p, s);
    return p;
}

Simbolo *simbolo_declarar(const char *nome, Tipo tipo, Categoria cat,
                          int linha, int coluna) {
    int ocorrencias = 0;

    /* 1) redeclaracao no MESMO bloco e erro; em bloco interno e sombreamento */
    for (int i = total - 1; i >= 0; i--) {
        Simbolo *s = tab[i];
        if (s->ativo && s->nivel == nivel && strcmp(s->nome, nome) == 0) {
            diag_erro_semantico(linha, coluna,
                "'%s' ja foi declarado neste bloco (primeira declaracao na linha %d)",
                nome, s->linha);
            return NULL;
        }
    }

    /* 2) cresce o vetor, se preciso */
    if (total == capac) {
        capac = capac ? capac * 2 : 16;
        tab = (Simbolo **)realloc(tab, (size_t)capac * sizeof(Simbolo *));
        if (!tab) { fprintf(stderr, "Erro: memoria insuficiente\n"); exit(2); }
    }

    /* 3) nome unico para o C gerado: v_x, v2_x, v3_x ... (o prefixo
     *    com digito nunca colide com um identificador do usuario) */
    for (int i = 0; i < total; i++)
        if (strcmp(tab[i]->nome, nome) == 0) ocorrencias++;

    Simbolo *novo = (Simbolo *)calloc(1, sizeof(Simbolo));
    if (!novo) { fprintf(stderr, "Erro: memoria insuficiente\n"); exit(2); }

    char buf[300];
    if (ocorrencias == 0) snprintf(buf, sizeof buf, "v_%s", nome);
    else                  snprintf(buf, sizeof buf, "v%d_%s", ocorrencias + 1, nome);

    novo->nome      = copiar(nome);
    novo->nome_c    = copiar(buf);
    novo->tipo      = tipo;
    novo->categoria = cat;
    novo->linha     = linha;
    novo->coluna    = coluna;
    novo->nivel     = nivel;
    novo->ativo     = 1;
    tab[total++]    = novo;
    return novo;
}

void tabela_imprimir(FILE *f) {
    fprintf(f, "\n==================== TABELA DE SIMBOLOS ====================\n");
    fprintf(f, " %-3s %-16s %-9s %-10s %-6s %-5s %-5s %-5s\n",
            "#", "Nome", "Tipo", "Categoria", "Escopo", "Linha", "Usos", "Atrib");
    fprintf(f, " --- ---------------- --------- ---------- ------ ----- ----- -----\n");
    for (int i = 0; i < total; i++) {
        Simbolo *s = tab[i];
        fprintf(f, " %-3d %-16s %-9s %-10s %-6d %-5d %-5d %-5d\n",
                i + 1, s->nome, nome_tipo(s->tipo),
                s->categoria == CAT_CONSTANTE ? "constante" : "variavel",
                s->nivel, s->linha, s->usos, s->atribuicoes);
    }
    fprintf(f, "============================================================\n");
}
