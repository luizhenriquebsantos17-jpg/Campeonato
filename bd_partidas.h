#ifndef BD_PARTIDAS_H
#define BD_PARTIDAS_H

#include "partida.h"
#include "bd_times.h"

// Define o tamanho máximo do vetor estático de partidas
#define MAX_PARTIDAS 90 // 10 times, todos contra todos (9 jogos por time), 1 turno: (10*9)/2 = 45

// Estrutura que representa o Banco de Dados de Partidas (TAD BDPartidas)
typedef struct bd_partidas {
    Partida* partidas[MAX_PARTIDAS]; // Vetor estático de ponteiros para Partida
    int num_partidas;
} BDPartidas;

// Funções do TAD BDPartidas

/**
 * @brief Cria e inicializa o Banco de Dados de Partidas, carregando dados do arquivo CSV.
 * 
 * @param nome_arquivo Nome do arquivo CSV com os dados das partidas.
 * @param bd_times Ponteiro para o BDTimes para processar os resultados.
 * @return BDPartidas* Ponteiro para o novo BDPartidas alocado dinamicamente.
 */
BDPartidas* bd_partidas_cria(const char* nome_arquivo, BDTimes* bd_times);

/**
 * @brief Libera a memória alocada para o BDPartidas e todas as Partidas contidas.
 * 
 * @param bd Ponteiro para o BDPartidas a ser liberado.
 */
void bd_partidas_libera(BDPartidas* bd);

/**
 * @brief Busca partidas com base no nome ou prefixo do time mandante, visitante ou ambos.
 * 
 * @param bd Ponteiro para o BDPartidas.
 * @param bd_times Ponteiro para o BDTimes.
 * @param prefixo Prefixo do nome do time a ser buscado.
 * @param modo Modo de busca (1: Mandante, 2: Visitante, 3: Ambos).
 */
void bd_partidas_consulta(const BDPartidas* bd, const BDTimes* bd_times, const char* prefixo, int modo);

#endif // BD_PARTIDAS_H
