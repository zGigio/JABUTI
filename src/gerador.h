/* ============================================================
 * gerador.h - Gerador de codigo C do compilador JABUTI
 * ============================================================
 * O JABUTI usa TRADUCAO DIRIGIDA PELA SINTAXE: cada regra da
 * gramatica, ao ser reconhecida pelo Bison, emite o trecho de
 * codigo C correspondente. As expressoes devolvem ao parser uma
 * estrutura Expr (tipo + codigo C da subexpressao).
 * ============================================================ */
#ifndef GERADOR_H
#define GERADOR_H

#include "simbolos.h"

/* Atributo semantico de uma expressao */
typedef struct {
    Tipo  tipo;    /* tipo JABUTI da expressao                          */
    char *cod;     /* codigo C equivalente (sempre totalmente entre ()) */
    int   zero;    /* 1 se for a constante literal 0 (deteccao de /0)   */
} Expr;

typedef enum {
    OP_SOMA, OP_SUB, OP_MUL, OP_DIV, OP_MOD,
    OP_IGUAL, OP_DIF, OP_MENOR, OP_MAIOR, OP_MENIG, OP_MAIG,
    OP_E, OP_OU
} Operador;

/* Textos temporarios: alocados num "pool" liberado ao final */
char *g_dup(const char *s);
char *g_fmt(const char *fmt, ...);

/* Emissao de linhas de codigo C (com indentacao automatica) */
void  g_programa(const char *nome);
void  g_emit(const char *fmt, ...);
void  g_indent(int delta);

/* Grava o arquivo C completo (cabecalho + runtime + corpo). 0 = ok */
int   g_salvar(const char *caminho_c, const char *arquivo_fonte);
void  g_liberar(void);

#endif
