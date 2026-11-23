/* ============================================================
 * main.c - Programa principal (driver) do compilador JABUTI
 * ============================================================
 * Disciplina: Compiladores
 *
 * Fluxo de uma compilacao:
 *   1. le o arquivo-fonte (.jab) inteiro para a memoria;
 *   2. analise lexica + sintatica + semantica (yyparse chama yylex);
 *   3. se NAO houve erros, grava o codigo C gerado (.c);
 *   4. (opcional, -r) compila o C com o gcc e executa o programa.
 *
 * Codigos de saida: 0 = sucesso | 1 = erro(s) no programa-fonte
 *                   2 = problema de uso/arquivo
 * ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
#include <sys/wait.h>
#endif
#include "parser.tab.h"
#include "simbolos.h"
#include "diagnostico.h"
#include "gerador.h"

#define VERSAO "1.0"

int  yyparse(void);
int  yylex(void);
void lexer_definir_entrada(const char *texto);
extern int modo_tokens;

/* ------------------------------------------------------------
 * Opcao --tokens: nome de cada token para a listagem
 * ------------------------------------------------------------ */
static const char *nome_token(int t) {
    switch (t) {
        case PROGRAMA:     return "PROGRAMA";     case CONSTANTE:   return "CONSTANTE";
        case T_INTEIRO:    return "T_INTEIRO";    case T_REAL:      return "T_REAL";
        case T_TEXTO:      return "T_TEXTO";      case T_BOOLEANO:  return "T_BOOLEANO";
        case VERDADEIRO:   return "VERDADEIRO";   case FALSO:       return "FALSO";
        case SE:           return "SE";           case SENAO:       return "SENAO";
        case ENQUANTO:     return "ENQUANTO";     case PARA:        return "PARA";
        case DE:           return "DE";           case ATE:         return "ATE";
        case PASSO:        return "PASSO";        case LEIA:        return "LEIA";
        case ESCREVA:      return "ESCREVA";      case ESCREVAL:    return "ESCREVAL";
        case E:            return "E";            case OU:          return "OU";
        case NAO:          return "NAO";          case IGUAL:       return "IGUAL";
        case DIFERENTE:    return "DIFERENTE";    case MENOR_IGUAL: return "MENOR_IGUAL";
        case MAIOR_IGUAL:  return "MAIOR_IGUAL";  case ERRO_LEXICO: return "ERRO_LEXICO";
        case IDENTIFICADOR:return "IDENTIFICADOR";case LIT_INTEIRO: return "LIT_INTEIRO";
        case LIT_REAL:     return "LIT_REAL";     case LIT_CADEIA:  return "LIT_CADEIA";
        case '(':          return "ABRE_PAREN";   case ')':         return "FECHA_PAREN";
        case '{':          return "ABRE_CHAVE";   case '}':         return "FECHA_CHAVE";
        case ';':          return "PONTO_VIRGULA";case ',':         return "VIRGULA";
        case '=':          return "ATRIBUICAO";   case '+':         return "MAIS";
        case '-':          return "MENOS";        case '*':         return "ASTERISCO";
        case '/':          return "BARRA";        case '%':         return "PERCENTUAL";
        case '<':          return "MENOR";        case '>':         return "MAIOR";
        default:           return "?";
    }
}

void mostrar_token(int token, const char *lexema, int linha, int coluna) {
    printf(" %5d %6d   %-14s %s\n", linha, coluna, nome_token(token), lexema);
}

/* ------------------------------------------------------------
 * Utilitarios
 * ------------------------------------------------------------ */
static char *ler_arquivo(const char *caminho) {
    FILE *f = (strcmp(caminho, "-") == 0) ? stdin : fopen(caminho, "rb");
    if (!f) return NULL;

    size_t cap = 4096, n = 0;
    char *buf = (char *)malloc(cap);
    if (!buf) return NULL;
    size_t lidos;
    while ((lidos = fread(buf + n, 1, cap - n - 1, f)) > 0) {
        n += lidos;
        if (n + 1 >= cap) {
            cap *= 2;
            buf = (char *)realloc(buf, cap);
            if (!buf) return NULL;
        }
    }
    buf[n] = '\0';
    if (f != stdin) fclose(f);

    /* ignora a marca BOM de arquivos UTF-8 salvos pelo Bloco de Notas */
    if (n >= 3 && (unsigned char)buf[0] == 0xEF &&
        (unsigned char)buf[1] == 0xBB && (unsigned char)buf[2] == 0xBF)
        memmove(buf, buf + 3, n - 2);
    return buf;
}

/* troca a extensao de 'caminho' por 'ext' (".c", ".exe", ...) */
static void trocar_extensao(const char *caminho, const char *ext, char *saida, size_t n) {
    snprintf(saida, n, "%s", caminho);
    char *ponto = strrchr(saida, '.');
    char *barra = strrchr(saida, '/');
    char *inv   = strrchr(saida, '\\');
    if (inv && (!barra || inv > barra)) barra = inv;
    if (ponto && (!barra || ponto > barra)) *ponto = '\0';
    size_t resto = n - strlen(saida);
    snprintf(saida + strlen(saida), resto, "%s", ext);
}

static void ajuda(void) {
    puts("JABUTI - compilador da linguagem Jabuti (Flex + Bison), versao " VERSAO "\n");
    puts("Uso: jabuti [opcoes] arquivo.jab\n");
    puts("Opcoes:");
    puts("  -o ARQ, --saida ARQ   nome do arquivo C gerado (padrao: <fonte>.c)");
    puts("  -r,     --executar    compila o C gerado com o gcc e executa o programa");
    puts("  -t,     --tokens      mostra apenas os tokens (analise lexica)");
    puts("  -s,     --tabela      mostra a tabela de simbolos ao final");
    puts("  -v,     --versao      mostra a versao");
    puts("  -h,     --ajuda       mostra esta ajuda");
    puts("\nUse '-' no lugar do arquivo para ler o programa da entrada padrao.");
}

static void com_aspas(const char *s, char *saida, size_t n) {
    if (strchr(s, ' ')) snprintf(saida, n, "\"%s\"", s);
    else                snprintf(saida, n, "%s", s);
}

/* ------------------------------------------------------------
 * Programa principal
 * ------------------------------------------------------------ */
int main(int argc, char **argv) {
    const char *entrada = NULL, *saida_c = NULL;
    int executar = 0, so_tokens = 0, mostrar_tabela = 0;

    setvbuf(stdout, NULL, _IONBF, 0);       /* mensagens na ordem certa em logs */

    for (int i = 1; i < argc; i++) {
        const char *a = argv[i];
        if      (!strcmp(a, "-h") || !strcmp(a, "--ajuda"))    { ajuda(); return 0; }
        else if (!strcmp(a, "-v") || !strcmp(a, "--versao"))   { puts("JABUTI " VERSAO); return 0; }
        else if (!strcmp(a, "-r") || !strcmp(a, "--executar")) executar = 1;
        else if (!strcmp(a, "-t") || !strcmp(a, "--tokens"))   so_tokens = 1;
        else if (!strcmp(a, "-s") || !strcmp(a, "--tabela"))   mostrar_tabela = 1;
        else if (!strcmp(a, "-o") || !strcmp(a, "--saida")) {
            if (++i >= argc) { fprintf(stderr, "Erro: faltou o nome do arquivo apos %s\n", a); return 2; }
            saida_c = argv[i];
        }
        else if (a[0] == '-' && a[1] != '\0') {
            fprintf(stderr, "Erro: opcao desconhecida '%s' (use --ajuda)\n", a);
            return 2;
        }
        else entrada = a;
    }
    if (!entrada) { ajuda(); return 2; }

    char *fonte = ler_arquivo(entrada);
    if (!fonte) {
        fprintf(stderr, "Erro: nao foi possivel abrir o arquivo '%s'\n", entrada);
        return 2;
    }

    if (!so_tokens) {          /* no modo --tokens a saida e so a listagem (cabe numa tela) */
        printf("=============================================\n");
        printf("   JABUTI - compilador (Flex + Bison) v" VERSAO "\n");
        printf("=============================================\n");
    }
    printf("Fonte: %s\n\n", entrada);

    diag_iniciar(entrada, fonte);
    tabela_iniciar();
    lexer_definir_entrada(fonte);

    /* ---------- modo --tokens: somente analise lexica ---------- */
    if (so_tokens) {
        modo_tokens = 1;
        printf(" %5s %6s   %-14s %s\n", "LINHA", "COLUNA", "TOKEN", "LEXEMA");
        printf(" ----- ------   -------------- ----------------\n");
        while (yylex() != 0) { }
        printf("\nAnalise lexica concluida: %d erro(s) lexico(s).\n", diag_total_lexicos());
        int rc = diag_total_lexicos() ? 1 : 0;
        g_liberar(); tabela_liberar(); free(fonte);
        return rc;
    }

    /* ---------- compilacao completa ---------- */
    yyparse();

    int erros = diag_total_erros();

    if (mostrar_tabela) tabela_imprimir(stdout);

    printf("\n---------------------------------------------\n");
    printf(" Erros lexicos    : %d\n", diag_total_lexicos());
    printf(" Erros sintaticos : %d\n", diag_total_sintaticos());
    printf(" Erros semanticos : %d\n", diag_total_semanticos());
    printf(" Avisos           : %d\n", diag_total_avisos());
    printf("---------------------------------------------\n");

    int rc = 0;
    char c_gerado[512];

    if (erros > 0) {
        printf("Compilacao INTERROMPIDA: nenhum codigo foi gerado.\n");
        rc = 1;
    } else {
        if (saida_c) snprintf(c_gerado, sizeof c_gerado, "%s", saida_c);
        else         trocar_extensao(entrada, ".c", c_gerado, sizeof c_gerado);

        if (g_salvar(c_gerado, entrada) != 0) {
            fprintf(stderr, "Erro: nao foi possivel gravar '%s'\n", c_gerado);
            rc = 2;
        } else {
            printf("Compilacao concluida com sucesso.\n");
            printf("Codigo C gerado em: %s\n", c_gerado);

            if (executar) {
                char exe[1100], cmd[1800], q_c[600], q_exe[1110];
#ifdef _WIN32
                trocar_extensao(c_gerado, ".exe", exe, 1000);
#else
                trocar_extensao(c_gerado, "", exe, 1000);
                if (!strchr(exe, '/')) {                  /* garante "./nome" */
                    memmove(exe + 2, exe, strlen(exe) + 1);
                    exe[0] = '.'; exe[1] = '/';
                }
#endif
                com_aspas(c_gerado, q_c, sizeof q_c);
                com_aspas(exe, q_exe, sizeof q_exe);

                snprintf(cmd, sizeof cmd, "gcc -o %s %s", q_exe, q_c);
                printf("\n[gcc] %s\n", cmd);
                if (system(cmd) != 0) {
                    fprintf(stderr, "Erro: o gcc nao conseguiu compilar o codigo C gerado.\n");
                    rc = 2;
                } else {
                    printf("[exec] %s\n", q_exe);
                    printf("--------------- saida do programa ---------------\n");
                    int r = system(q_exe);
#ifndef _WIN32
                    if (WIFEXITED(r)) r = WEXITSTATUS(r);   /* codigo de saida real */
#endif
                    printf("\n-------------------------------------------------\n");
                    printf("Programa finalizado (codigo de saida %d).\n", r);
                }
            }
        }
    }

    g_liberar();
    tabela_liberar();
    free(fonte);
    return rc;
}
