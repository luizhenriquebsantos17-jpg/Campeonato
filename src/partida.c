#include "partida.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Cria e inicializa uma nova Partida.
 */
Partida* partida_cria(int id, int time1_id, int time2_id, int gols_time1, int gols_time2) {
    Partida* nova_partida = (Partida*) malloc(sizeof(Partida));
    if (nova_partida == NULL) {
        perror("Erro ao alocar memoria para Partida");
        exit(EXIT_FAILURE);
    }
    
    nova_partida->id = id;
    nova_partida->time1_id = time1_id;
    nova_partida->time2_id = time2_id;
    nova_partida->gols_time1 = gols_time1;
    nova_partida->gols_time2 = gols_time2;
    
    return nova_partida;
}

/**
 * @brief Libera a memória alocada para uma Partida.
 */
void partida_libera(Partida* p) {
    free(p);
}

/**
 * @brief Processa o resultado da partida, atualizando as estatísticas dos times envolvidos.
 */
void partida_processa_resultado(const Partida* p, BDTimes* bd_times) {
    Time* time1 = bd_times_busca_por_id(bd_times, p->time1_id);
    Time* time2 = bd_times_busca_por_id(bd_times, p->time2_id);

    if (time1 && time2) {
        // Atualiza estatísticas do Time 1 (Mandante)
        time_atualiza_estatisticas(time1, p->gols_time1, p->gols_time2);
        
        // Atualiza estatísticas do Time 2 (Visitante)
        time_atualiza_estatisticas(time2, p->gols_time2, p->gols_time1);
    } else {
        fprintf(stderr, "Aviso: Times não encontrados para a Partida ID %d\n", p->id);
    }
}

/**
 * @brief Imprime os detalhes de uma partida.
 */
void partida_imprime_detalhes(const Partida* p, const BDTimes* bd_times) {
    const Time* time1 = bd_times_busca_por_id(bd_times, p->time1_id);
    const Time* time2 = bd_times_busca_por_id(bd_times, p->time2_id);

    if (time1 && time2) {
        printf("%-2d %-12s %-12s %d x %d\n",
               p->id,
               time1->nome,
               time2->nome,
               p->gols_time1,
               p->gols_time2);
    } else {
        printf("%-2d ID %d vs ID %d: %d x %d (Times não encontrados)\n",
               p->id,
               p->time1_id,
               p->time2_id,
               p->gols_time1,
               p->gols_time2);
    }
}
