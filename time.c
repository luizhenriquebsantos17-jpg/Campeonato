#include "time.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Cria e inicializa um novo Time.
 */
Time* time_cria(int id, const char* nome) {
    Time* novo_time = (Time*) malloc(sizeof(Time));
    if (novo_time == NULL) {
        perror("Erro ao alocar memoria para Time");
        exit(EXIT_FAILURE);
    }
    
    novo_time->id = id;
    strncpy(novo_time->nome, nome, MAX_NOME_TIME - 1);
    novo_time->nome[MAX_NOME_TIME - 1] = '\0';
    novo_time->vitorias = 0;
    novo_time->empates = 0;
    novo_time->derrotas = 0;
    novo_time->gols_marcados = 0;
    novo_time->gols_sofridos = 0;
    
    return novo_time;
}

/**
 * @brief Libera a memória alocada para um Time.
 */
void time_libera(Time* t) {
    free(t);
}

/**
 * @brief Atualiza as estatísticas do time com base no resultado de uma partida.
 */
void time_atualiza_estatisticas(Time* t, int gols_pro, int gols_contra) {
    t->gols_marcados += gols_pro;
    t->gols_sofridos += gols_contra;

    if (gols_pro > gols_contra) {
        t->vitorias++;
    } else if (gols_pro == gols_contra) {
        t->empates++;
    } else {
        t->derrotas++;
    }
}

/**
 * @brief Calcula e retorna os pontos ganhos do time.
 */
int time_calcula_pontos(const Time* t) {
    return (3 * t->vitorias) + t->empates;
}

/**
 * @brief Calcula e retorna o saldo de gols do time.
 */
int time_calcula_saldo_gols(const Time* t) {
    return t->gols_marcados - t->gols_sofridos;
}

/**
 * @brief Imprime as estatísticas detalhadas de um Time.
 */
void time_imprime_detalhes(const Time* t) {
    printf("ID: %d\n", t->id);
    printf("Time: %s\n", t->nome);
    printf("Vitorias (V): %d\n", t->vitorias);
    printf("Empates (E): %d\n", t->empates);
    printf("Derrotas (D): %d\n", t->derrotas);
    printf("Gols Marcados (GM): %d\n", t->gols_marcados);
    printf("Gols Sofridos (GS): %d\n", t->gols_sofridos);
    printf("Saldo de Gols (S): %d\n", time_calcula_saldo_gols(t));
    printf("Pontos Ganhos (PG): %d\n", time_calcula_pontos(t));
}

/**
 * @brief Imprime o cabeçalho da tabela de classificação.
 */
void time_imprime_cabecalho_tabela() {
    printf("ID Time         V  E  D  GM GS  S PG\n");
    printf("-------------------------------------\n");
}

/**
 * @brief Imprime uma linha da tabela de classificação para um Time.
 */
void time_imprime_linha_tabela(const Time* t) {
    printf("%-2d %-12s %-2d %-2d %-2d %-2d %-2d %-2d %-2d\n",
           t->id,
           t->nome,
           t->vitorias,
           t->empates,
           t->derrotas,
           t->gols_marcados,
           t->gols_sofridos,
           time_calcula_saldo_gols(t),
           time_calcula_pontos(t));
}
