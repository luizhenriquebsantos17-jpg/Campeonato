#include "bd_times.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Função auxiliar para comparação de strings sem distinção de maiúsculas/minúsculas
static int strncasecmp_c99(const char *s1, const char *s2, size_t n) {
    if (n == 0) return 0;
    while (n-- != 0 && *s1 != '\0' && tolower((unsigned char)*s1) == tolower((unsigned char)*s2)) {
        s1++;
        s2++;
    }
    return (n == (size_t)-1) ? 0 : tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}

/**
 * @brief Cria e inicializa o Banco de Dados de Times, carregando dados do arquivo times.csv.
 */
BDTimes* bd_times_cria(const char* nome_arquivo) {
    BDTimes* bd = (BDTimes*) malloc(sizeof(BDTimes));
    if (bd == NULL) {
        perror("Erro ao alocar memoria para BDTimes");
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(nome_arquivo, "r");
    if (fp == NULL) {
        perror("Erro ao abrir times.csv");
        bd_times_libera(bd);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;

    // Ignora o cabeçalho
    if (fgets(line, MAX_LINE_LENGTH, fp) == NULL) {
        fprintf(stderr, "Erro ao ler cabeçalho de times.csv\n");
        fclose(fp);
        bd_times_libera(bd);
        exit(EXIT_FAILURE);
    }

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL && count < NUM_TIMES) {
        int id;
        char nome[MAX_NOME_TIME];
        
        // Formato esperado: ID,Nome
        if (sscanf(line, "%d,%49[^\n]", &id, nome) == 2) {
            bd->times[count] = time_cria(id, nome);
            count++;
        } else {
            fprintf(stderr, "Aviso: Linha mal formatada em times.csv: %s", line);
        }
    }

    fclose(fp);
    
    // Inicializa os ponteiros restantes como NULL, caso o arquivo tenha menos de NUM_TIMES
    for (int i = count; i < NUM_TIMES; i++) {
        bd->times[i] = NULL;
    }

    if (count != NUM_TIMES) {
        fprintf(stderr, "Aviso: Esperado %d times, encontrado %d em times.csv\n", NUM_TIMES, count);
    }

    return bd;
}

/**
 * @brief Libera a memória alocada para o BDTimes e todos os Times contidos.
 */
void bd_times_libera(BDTimes* bd) {
    if (bd) {
        for (int i = 0; i < NUM_TIMES; i++) {
            if (bd->times[i]) {
                time_libera(bd->times[i]);
            }
        }
        free(bd);
    }
}

/**
 * @brief Busca um Time pelo seu ID.
 */
Time* bd_times_busca_por_id(const BDTimes* bd, int id) {
    if (id >= 0 && id < NUM_TIMES && bd->times[id] && bd->times[id]->id == id) {
        return bd->times[id];
    }
    // Como os IDs são sequenciais de 0 a 9, podemos usar o ID como índice.
    // A verificação adicional `bd->times[id]->id == id` garante a consistência.
    return NULL;
}

/**
 * @brief Busca Times cujo nome começa com um prefixo.
 */
int bd_times_busca_por_prefixo(const BDTimes* bd, const char* prefixo, Time* resultados[]) {
    int count = 0;
    size_t len_prefixo = strlen(prefixo);

    for (int i = 0; i < NUM_TIMES; i++) {
        if (bd->times[i] && strncasecmp_c99(bd->times[i]->nome, prefixo, len_prefixo) == 0) {
            resultados[count++] = bd->times[i];
        }
    }
    return count;
}

/**
 * @brief Imprime a tabela de classificação completa.
 */
void bd_times_imprime_tabela(const BDTimes* bd) {
    printf("\n[Sistema]\nImprimindo classificação...\n");
    time_imprime_cabecalho_tabela();
    
    // Imprime na ordem dos IDs (0 a 9)
    for (int i = 0; i < NUM_TIMES; i++) {
        if (bd->times[i]) {
            time_imprime_linha_tabela(bd->times[i]);
        }
    }
    printf("-------------------------------------\n");
}
