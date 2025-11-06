#include "bd_partidas.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief Cria e inicializa o Banco de Dados de Partidas, carregando dados do arquivo CSV.
 */
BDPartidas* bd_partidas_cria(const char* nome_arquivo, BDTimes* bd_times) {
    BDPartidas* bd = (BDPartidas*) malloc(sizeof(BDPartidas));
    if (bd == NULL) {
        perror("Erro ao alocar memoria para BDPartidas");
        exit(EXIT_FAILURE);
    }
    bd->num_partidas = 0;

    FILE *fp = fopen(nome_arquivo, "r");
    if (fp == NULL) {
        perror("Erro ao abrir arquivo de partidas");
        free(bd);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    
    // Ignora o cabeçalho
    if (fgets(line, MAX_LINE_LENGTH, fp) == NULL) {
        // Arquivo vazio ou erro de leitura
        fclose(fp);
        return bd;
    }

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL && bd->num_partidas < MAX_PARTIDAS) {
        int id, time1_id, time2_id, gols_time1, gols_time2;
        
        // Formato esperado: ID,Time1,Time2,GolsTime1,GolsTime2
        if (sscanf(line, "%d,%d,%d,%d,%d", &id, &time1_id, &time2_id, &gols_time1, &gols_time2) == 5) {
            Partida* p = partida_cria(id, time1_id, time2_id, gols_time1, gols_time2);
            bd->partidas[bd->num_partidas++] = p;
            
            // Processa o resultado para atualizar as estatísticas dos times
            partida_processa_resultado(p, bd_times);
        } else {
            fprintf(stderr, "Aviso: Linha mal formatada em partidas.csv: %s", line);
        }
    }

    fclose(fp);
    return bd;
}

/**
 * @brief Libera a memória alocada para o BDPartidas e todas as Partidas contidas.
 */
void bd_partidas_libera(BDPartidas* bd) {
    if (bd) {
        for (int i = 0; i < bd->num_partidas; i++) {
            if (bd->partidas[i]) {
                partida_libera(bd->partidas[i]);
            }
        }
        free(bd);
    }
}

/**
 * @brief Função auxiliar para verificar se o nome de um time corresponde ao prefixo (case-insensitive).
 */
static int time_corresponde_prefixo(const BDTimes* bd_times, int time_id, const char* prefixo) {
    const Time* t = bd_times_busca_por_id(bd_times, time_id);
    if (!t) return 0;

    size_t len_prefixo = strlen(prefixo);
    if (len_prefixo == 0) return 1; // Se o prefixo for vazio, corresponde a todos

    // strncasecmp não é padrão C99, implementando manualmente
    for (size_t i = 0; i < len_prefixo; i++) {
        if (tolower((unsigned char)t->nome[i]) != tolower((unsigned char)prefixo[i])) {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Busca partidas com base no nome ou prefixo do time mandante, visitante ou ambos.
 */
void bd_partidas_consulta(const BDPartidas* bd, const BDTimes* bd_times, const char* prefixo, int modo) {
    int encontradas = 0;
    
    printf("\n[Sistema]\n");
    printf("ID Time1       Time2        Placar\n");
    printf("-----------------------------------\n");

    for (int i = 0; i < bd->num_partidas; i++) {
        const Partida* p = bd->partidas[i];
        int time1_corresponde = time_corresponde_prefixo(bd_times, p->time1_id, prefixo);
        int time2_corresponde = time_corresponde_prefixo(bd_times, p->time2_id, prefixo);

        int deve_imprimir = 0;

        switch (modo) {
            case 1: // Por time mandante
                if (time1_corresponde) deve_imprimir = 1;
                break;
            case 2: // Por time visitante
                if (time2_corresponde) deve_imprimir = 1;
                break;
            case 3: // Por time mandante ou visitante
                if (time1_corresponde || time2_corresponde) deve_imprimir = 1;
                break;
            default:
                break;
        }

        if (deve_imprimir) {
            partida_imprime_detalhes(p, bd_times);
            encontradas++;
        }
    }
    
    printf("-----------------------------------\n");

    if (encontradas == 0) {
        printf("Nenhuma partida encontrada para o prefixo '%s' no modo de busca %d.\n", prefixo, modo);
    } else {
        printf("%d partidas encontradas.\n", encontradas);
    }
}
