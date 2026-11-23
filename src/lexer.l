/* ============================================================
 * lexer.l - Analisador Lexico (Scanner) do compilador JABUTI
 * ============================================================
 * Disciplina: Compiladores
 * Ferramenta: Flex (Fast Lexical Analyzer Generator)
 *
 * Define, por EXPRESSOES REGULARES, os tokens da linguagem
 * JABUTI: palavras reservadas em portugues, identificadores,
 * numeros, textos entre aspas, operadores e delimitadores.
 *
 * Alem de reconhecer tokens, o scanner:
 *   - controla linha e coluna de cada token (yylloc), usadas
 *     pelo Bison nas mensagens de erro;
 *   - relata erros lexicos SEM abortar: devolve o token especial
 *     ERRO_LEXICO e a analise continua;
 *   - ignora espacos, comentarios de linha (//) e de bloco.
 *
 * Base: lexer do projeto MiniLang (colega), ampliado com
 * posicao (linha/coluna), comentarios de bloco, textos com
 * escapes, novos operadores e deteccao de varios erros lexicos.
 * ============================================================ */

%option noyywrap nounput noinput

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "parser.tab.h"      /* gerado pelo Bison: tokens, YYSTYPE, YYLTYPE */
#include "diagnostico.h"
#include "gerador.h"

/* Definida em main.c: usada pela opcao --tokens */
void mostrar_token(int token, const char *lexema, int linha, int coluna);

int modo_tokens = 0;                 /* 1 = imprime cada token reconhecido */

static int  lin = 1, col = 1;        /* posicao do proximo caractere       */
static char ultimo[128] = "";        /* texto do ultimo token lido         */
static int  com_lin, com_col;        /* onde comecou um comentario de bloco */
static int  eof_por_erro = 0;        /* 1 = arquivo acabou dentro de comentario */
static int  fim_lin = 0, fim_col = 0;       /* fim do ultimo token lido          */
static int  ant_lin = 0, ant_col = 0;       /* fim do token ANTERIOR a ele       */

/* Atualiza yylloc para o token recem casado e avanca linha/coluna.
 * A coluna conta CARACTERES (e nao bytes), para acentos em UTF-8. */
static void atualizar_posicao(const char *txt, int tam) {
    yylloc.first_line   = lin;
    yylloc.first_column = col;
    for (int i = 0; i < tam; i++) {
        if (txt[i] == '\n')                  { lin++; col = 1; }
        else if (((unsigned char)txt[i] & 0xC0) != 0x80) col++;
    }
    yylloc.last_line   = lin;
    yylloc.last_column = col;
}

static int tok_(int t, const char *txt) {
    ant_lin = fim_lin;  ant_col = fim_col;
    fim_lin = yylloc.last_line;  fim_col = yylloc.last_column;
    snprintf(ultimo, sizeof ultimo, "%s", txt);
    if (modo_tokens)
        mostrar_token(t, txt, yylloc.first_line, yylloc.first_column);
    return t;
}

#define YY_USER_ACTION  atualizar_posicao(yytext, yyleng);
#define TOK(t)          return tok_((t), yytext)

/* Texto do ultimo token lido (usado nas mensagens de erro sintatico) */
const char *lexer_ultimo_lexema(void) { return ultimo; }

/* 1 se o fim do arquivo foi provocado por um erro lexico ja relatado */
int lexer_eof_por_erro(void) { return eof_por_erro; }

/* Posicao logo depois do token que antecede o ultimo token lido */
void lexer_fim_token_anterior(int *linha, int *coluna) {
    *linha = ant_lin;
    *coluna = ant_col;
}

/* Verifica as sequencias de escape de um texto: \n \t \r \\ \" */
static void validar_escapes(const char *s) {
    int c = yylloc.first_column;
    for (int i = 0; s[i]; i++) {
        if (s[i] == '\\') {
            char e = s[i + 1];
            if (e != 'n' && e != 't' && e != 'r' && e != '\\' && e != '"')
                diag_erro_lexico(yylloc.first_line, c,
                    "sequencia de escape invalida '\\%c' no texto "
                    "(validas: \\n \\t \\r \\\\ \\\")", e);
            i++;
            c++;
        }
        if (((unsigned char)s[i] & 0xC0) != 0x80) c++;
    }
}
%}

DIGITO      [0-9]
LETRA       [a-zA-Z_]
ID          {LETRA}({LETRA}|{DIGITO})*
INTEIRO     {DIGITO}+
REAL        {DIGITO}+"."{DIGITO}+
CADEIA      \"([^\"\\\n]|\\.)*\"
CADEIA_ABERTA \"([^\"\\\n]|\\.)*
UTF8        [\xC2-\xF4][\x80-\xBF]*
ACENTUADO   ({LETRA}|{DIGITO}|{UTF8})*{UTF8}({LETRA}|{DIGITO}|{UTF8})*

%x COMENTARIO

%%

 /* ---------- espacos, quebras de linha e comentarios ---------- */
[ \t\r]+            { /* ignora */ }
\n                  { /* ignora (a linha ja foi contada) */ }
"//".*              { /* comentario de linha */ }

"/*"                { com_lin = yylloc.first_line;
                      com_col = yylloc.first_column;
                      BEGIN(COMENTARIO); }
<COMENTARIO>"*/"    { BEGIN(INITIAL); }
<COMENTARIO>[^*\n]+ { /* corpo do comentario */ }
<COMENTARIO>"*"     { /* asterisco solto */ }
<COMENTARIO>\n      { /* quebra de linha dentro do comentario */ }
<COMENTARIO><<EOF>> { diag_erro_lexico(com_lin, com_col,
                          "comentario de bloco nao terminado (faltou fechar com */)");
                      BEGIN(INITIAL);
                      eof_por_erro = 1;
                      return 0; }

 /* ---------- palavras reservadas ---------- */
"programa"          { TOK(PROGRAMA); }
"constante"         { TOK(CONSTANTE); }
"inteiro"           { TOK(T_INTEIRO); }
"real"              { TOK(T_REAL); }
"texto"             { TOK(T_TEXTO); }
"booleano"          { TOK(T_BOOLEANO); }
"verdadeiro"        { TOK(VERDADEIRO); }
"falso"             { TOK(FALSO); }
"se"                { TOK(SE); }
"senao"             { TOK(SENAO); }
"enquanto"          { TOK(ENQUANTO); }
"para"              { TOK(PARA); }
"de"                { TOK(DE); }
"ate"               { TOK(ATE); }
"passo"             { TOK(PASSO); }
"leia"              { TOK(LEIA); }
"escreva"           { TOK(ESCREVA); }
"escreval"          { TOK(ESCREVAL); }

 /* ---------- operadores logicos (palavra OU simbolo) ---------- */
"e"|"&&"            { TOK(E); }
"ou"|"||"           { TOK(OU); }
"nao"|"!"           { TOK(NAO); }

 /* ---------- operadores relacionais ---------- */
"=="                { TOK(IGUAL); }
"!="                { TOK(DIFERENTE); }
"<="                { TOK(MENOR_IGUAL); }
">="                { TOK(MAIOR_IGUAL); }

 /* ---------- numeros ---------- */
{REAL}              { yylval.texto = g_dup(yytext);
                      TOK(LIT_REAL); }

{INTEIRO}           { long v = strtol(yytext, NULL, 10);
                      if (strlen(yytext) > 10 || v > INT_MAX) {
                          diag_erro_lexico(yylloc.first_line, yylloc.first_column,
                              "inteiro '%s' fora do intervalo permitido (maximo %d)",
                              yytext, INT_MAX);
                          v = 0;
                      }
                      yylval.inteiro = v;
                      TOK(LIT_INTEIRO); }

{DIGITO}+{LETRA}({LETRA}|{DIGITO})* {
                      diag_erro_lexico(yylloc.first_line, yylloc.first_column,
                          "identificador invalido '%s': nao pode comecar com digito",
                          yytext);
                      TOK(ERRO_LEXICO); }

{DIGITO}+"."        { diag_erro_lexico(yylloc.first_line, yylloc.first_column,
                          "numero real mal formado '%s': falta digito depois do ponto",
                          yytext);
                      TOK(ERRO_LEXICO); }

 /* ---------- textos entre aspas ---------- */
{CADEIA}            { validar_escapes(yytext);
                      yylval.texto = g_dup(yytext);
                      TOK(LIT_CADEIA); }

{CADEIA_ABERTA}     { diag_erro_lexico(yylloc.first_line, yylloc.first_column,
                          "texto nao terminado (faltou fechar as aspas)");
                      TOK(ERRO_LEXICO); }

 /* ---------- identificadores ---------- */
{ID}                { yylval.texto = g_dup(yytext);
                      TOK(IDENTIFICADOR); }

 /* ---------- delimitadores e operadores de um caractere ---------- */
[(){};,=+*/%<>-]    { TOK(yytext[0]); }

 /* ---------- erros lexicos ---------- */
"&"|"|"             { diag_erro_lexico(yylloc.first_line, yylloc.first_column,
                          "operador incompleto '%s' (use '&&'/'e' ou '||'/'ou')", yytext);
                      TOK(ERRO_LEXICO); }

{ACENTUADO}         { /* palavra com acento: o nome INTEIRO vira um unico erro,
                       * em vez de se partir em varios tokens (m + e' + dia) */
                      int so_acento = 1;
                      for (const char *p = yytext; *p; p++)
                          if ((unsigned char)*p < 0x80) so_acento = 0;
                      if (so_acento)
                          diag_erro_lexico(yylloc.first_line, yylloc.first_column,
                              "caractere '%s' nao e permitido aqui (acentos so valem "
                              "dentro de textos e comentarios)", yytext);
                      else
                          diag_erro_lexico(yylloc.first_line, yylloc.first_column,
                              "nome invalido '%s': acentos so valem dentro de textos "
                              "e comentarios (escreva sem acento)", yytext);
                      TOK(ERRO_LEXICO); }

.                   { diag_erro_lexico(yylloc.first_line, yylloc.first_column,
                          "caractere invalido '%s'", yytext);
                      TOK(ERRO_LEXICO); }

%%

/* Prepara o scanner para ler de um texto em memoria (todo o arquivo
 * ja foi carregado por main.c, o que permite mostrar a linha do erro). */
void lexer_definir_entrada(const char *texto) {
    yy_scan_string(texto);
    lin = 1;
    col = 1;
}
