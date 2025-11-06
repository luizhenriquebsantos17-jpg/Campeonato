#ifndef PARTIDA_H
#define PARTIDA_H

#include "bd_times.h"

// Estrutura que representa uma Partida (TAD Partida)
typedef struct partida {
    int id;
    int time1_id;
    int time2_id;
    int gols_time1;
    int gols_time2;
} Partida;

// Funções do TAD Partida

/**
 * @brief Cria e inicializa uma nova Partida.
 * 
 * @param id ID da partida.
 * @param time1_id ID do time 1 (mandante).
 * @param time2_id ID do time 2 (visitante).
 * @param gols_time1 Gols do time 1.
 * @param gols_time2 Gols do time 2.
 * @return Partida* Ponteiro para a nova Partida alocada dinamicamente.
 */
Partida* partida_cria(int id, int time1_id, int time2_id, int gols_time1, int gols_time2);

/**
 * @brief Libera a memória alocada para uma Partida.
 * 
 * @param p Ponteiro para a Partida a ser liberada.
 */
void partida_libera(Partida* p);

/**
 * @brief Processa o resultado da partida, atualizando as estatísticas dos times envolvidos.
 * 
 * @param p Ponteiro para a Partida.
 * @param bd_times Ponteiro para o BDTimes para buscar e atualizar os times.
 */
void partida_processa_resultado(const Partida* p, BDTimes* bd_times);

/**
 * @brief Imprime os detalhes de uma partida.
 * 
 * @param p Ponteiro para a Partida.
 * @param bd_times Ponteiro para o BDTimes para obter os nomes dos times.
 */
void partida_imprime_detalhes(const Partida* p, const BDTimes* bd_times);

#endif // PARTIDA_H
