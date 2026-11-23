/* ============================================================
 * simbolos.h - Tabela de simbolos do compilador JABUTI
 * ============================================================
 * Disciplina: Compiladores
 *
 * A tabela de simbolos e um vetor dinamico PERSISTENTE de
 * registros (Simbolo). Cada declaracao de variavel ou constante
 * acrescenta um registro ao final do vetor. Os blocos do
 * programa ({ ... }) formam uma PILHA DE ESCOPOS: ao entrar em
 * um bloco o nivel aumenta; ao sair, todos os simbolos daquele
 * nivel deixam de ser "ativos" (mas continuam registrados, para
 * que a tabela completa possa ser exibida com a opcao -s).
 * ============================================================ */
#ifndef SIMBOLOS_H
#define SIMBOLOS_H

#include <stdio.h>

/* Tipos basicos da linguagem JABUTI */
typedef enum {
    TP_INTEIRO,
    TP_REAL,
    TP_TEXTO,
    TP_BOOLEANO,
    TP_INVALIDO      /* tipo "de erro": evita erros em cascata */
} Tipo;

typedef enum {
    CAT_VARIAVEL,
    CAT_CONSTANTE
} Categoria;

typedef struct {
    char      *nome;         /* nome no codigo JABUTI                    */
    char      *nome_c;       /* nome unico usado no C gerado (v_x, v2_x) */
    Tipo       tipo;
    Categoria  categoria;
    int        linha;        /* posicao da declaracao                    */
    int        coluna;
    int        nivel;        /* profundidade do bloco (1 = programa)     */
    int        ativo;        /* 1 enquanto o bloco estiver aberto        */
    int        usos;         /* quantas vezes o valor foi LIDO           */
    int        atribuicoes;  /* quantas vezes recebeu valor              */
} Simbolo;

const char *nome_tipo(Tipo t);

void     tabela_iniciar(void);
void     tabela_liberar(void);
void     tabela_imprimir(FILE *saida);

void     escopo_entrar(void);
void     escopo_sair(void);

/* Retorna NULL (e reporta erro semantico) se o nome ja existir no
 * bloco corrente. */
Simbolo *simbolo_declarar(const char *nome, Tipo tipo, Categoria cat,
                          int linha, int coluna);

/* Procura do escopo mais interno para o mais externo. NULL se nao achar. */
Simbolo *simbolo_buscar(const char *nome);

#endif
