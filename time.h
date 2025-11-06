#ifndef TIME_H
#define TIME_H

#include <stdio.h>
#include "csv_utils.h"

// Estrutura que representa um Time (TAD Time)
typedef struct time {
    int id;
    char nome[MAX_NOME_TIME];
    int vitorias;
    int empates;
    int derrotas;
    int gols_marcados;
    int gols_sofridos;
} Time;

// Funções do TAD Time

/**
 * @brief Cria e inicializa um novo Time.
 * 
 * @param id ID do time.
 * @param nome Nome do time.
 * @return Time* Ponteiro para o novo Time alocado dinamicamente.
 */
Time* time_cria(int id, const char* nome);

/**
 * @brief Libera a memória alocada para um Time.
 * 
 * @param t Ponteiro para o Time a ser liberado.
 */
void time_libera(Time* t);

/**
 * @brief Atualiza as estatísticas do time com base no resultado de uma partida.
 * 
 * @param t Ponteiro para o Time.
 * @param gols_pro Gols marcados pelo time.
 * @param gols_contra Gols sofridos pelo time.
 */
void time_atualiza_estatisticas(Time* t, int gols_pro, int gols_contra);

/**
 * @brief Calcula e retorna os pontos ganhos do time.
 * 
 * @param t Ponteiro para o Time.
 * @return int Pontos ganhos (3V + E).
 */
int time_calcula_pontos(const Time* t);

/**
 * @brief Calcula e retorna o saldo de gols do time.
 * 
 * @param t Ponteiro para o Time.
 * @return int Saldo de gols (GM - GS).
 */
int time_calcula_saldo_gols(const Time* t);

/**
 * @brief Imprime as estatísticas detalhadas de um Time.
 * 
 * @param t Ponteiro para o Time.
 */
void time_imprime_detalhes(const Time* t);

/**
 * @brief Imprime o cabeçalho da tabela de classificação.
 */
void time_imprime_cabecalho_tabela();

/**
 * @brief Imprime uma linha da tabela de classificação para um Time.
 * 
 * @param t Ponteiro para o Time.
 */
void time_imprime_linha_tabela(const Time* t);

#endif // TIME_H
