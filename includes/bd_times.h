#ifndef BD_TIMES_H
#define BD_TIMES_H

#include "time.h"

// Define o número fixo de times no campeonato
#define NUM_TIMES 10

// Estrutura que representa o Banco de Dados de Times (TAD BDTimes)
typedef struct bd_times {
    Time* times[NUM_TIMES]; // Vetor estático de ponteiros para Time
} BDTimes;

// Funções do TAD BDTimes

/**
 * @brief Cria e inicializa o Banco de Dados de Times, carregando dados do arquivo times.csv.
 * 
 * @param nome_arquivo Nome do arquivo CSV com os dados dos times.
 * @return BDTimes* Ponteiro para o novo BDTimes alocado dinamicamente.
 */
BDTimes* bd_times_cria(const char* nome_arquivo);

/**
 * @brief Libera a memória alocada para o BDTimes e todos os Times contidos.
 * 
 * @param bd Ponteiro para o BDTimes a ser liberado.
 */
void bd_times_libera(BDTimes* bd);

/**
 * @brief Busca um Time pelo seu ID.
 * 
 * @param bd Ponteiro para o BDTimes.
 * @param id ID do time a ser buscado.
 * @return Time* Ponteiro para o Time encontrado, ou NULL se não encontrado.
 */
Time* bd_times_busca_por_id(const BDTimes* bd, int id);

/**
 * @brief Busca Times cujo nome começa com um prefixo.
 * 
 * @param bd Ponteiro para o BDTimes.
 * @param prefixo Prefixo do nome a ser buscado.
 * @param resultados Vetor de ponteiros para Time onde os resultados serão armazenados.
 * @return int Número de times encontrados.
 */
int bd_times_busca_por_prefixo(const BDTimes* bd, const char* prefixo, Time* resultados[]);

/**
 * @brief Imprime a tabela de classificação completa.
 * 
 * @param bd Ponteiro para o BDTimes.
 */
void bd_times_imprime_tabela(const BDTimes* bd);

#endif // BD_TIMES_H
