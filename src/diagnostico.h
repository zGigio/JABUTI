/* ============================================================
 * diagnostico.h - Mensagens de erro e aviso do JABUTI
 * ============================================================
 * Centraliza o relato de erros lexicos, sintaticos e semanticos,
 * com linha, coluna e o trecho do codigo-fonte com um '^'
 * apontando o ponto exato do problema.
 * ============================================================ */
#ifndef DIAGNOSTICO_H
#define DIAGNOSTICO_H

void diag_iniciar(const char *arquivo, const char *texto_fonte);

void diag_erro_lexico   (int linha, int coluna, const char *fmt, ...);
void diag_erro_sintatico(int linha, int coluna, const char *fmt, ...);
void diag_erro_semantico(int linha, int coluna, const char *fmt, ...);
void diag_aviso         (int linha, int coluna, const char *fmt, ...);

int  diag_total_lexicos(void);
int  diag_total_sintaticos(void);
int  diag_total_semanticos(void);
int  diag_total_avisos(void);
int  diag_total_erros(void);

#endif
