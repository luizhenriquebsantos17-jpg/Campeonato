#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "bd_times.h"
#include "bd_partidas.h"
#include "time.h"

// Protótipos das funções de menu
void menu_principal(BDTimes* bd_times, BDPartidas* bd_partidas);
void funcionalidade_consultar_time(const BDTimes* bd_times);
void funcionalidade_consultar_partidas(const BDPartidas* bd_partidas, const BDTimes* bd_times);

/**
 * @brief Função principal do programa.
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <arquivo_partidas.csv>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // 1. Carregar Times
    BDTimes* bd_times = bd_times_cria("times.csv");
    if (!bd_times) {
        return EXIT_FAILURE;
    }

    // 2. Carregar Partidas e processar resultados
    BDPartidas* bd_partidas = bd_partidas_cria(argv[1], bd_times);
    if (!bd_partidas) {
        bd_times_libera(bd_times);
        return EXIT_FAILURE;
    }

    // 3. Executar Menu Principal
    menu_principal(bd_times, bd_partidas);

    // 4. Liberar memória
    bd_partidas_libera(bd_partidas);
    bd_times_libera(bd_times);

    return EXIT_SUCCESS;
}

/**
 * @brief Exibe o menu principal e gerencia as opções do usuário.
 */
void menu_principal(BDTimes* bd_times, BDPartidas* bd_partidas) {
    char opcao;
    
    do {
        printf("\nSistema de Gerenciamento de Partidas\n");
        printf("1 - Consultar time\n");
        printf("2 - Consultar partidas\n");
        printf("3 - Atualizar partida (Desabilitado)\n");
        printf("4 - Remover partida ID (Desabilitado)\n");
        printf("5 - Inserir partida (Desabilitado)\n");
        printf("6 - Imprimir tabela de classificação\n");
        printf("Q - Sair\n");
        printf("Escolha uma opção: ");
        
        if (scanf(" %c", &opcao) != 1) {
            // Limpa o buffer de entrada em caso de erro
            while (getchar() != '\n');
            opcao = ' ';
        }
        
        // Converte para maiúscula para facilitar a comparação
        opcao = toupper(opcao);

        switch (opcao) {
            case '1':
                funcionalidade_consultar_time(bd_times);
                break;
            case '2':
                funcionalidade_consultar_partidas(bd_partidas, bd_times);
                break;
            case '6':
                bd_times_imprime_tabela(bd_times);
                break;
            case 'Q':
                printf("\nEncerrando o sistema. Até mais!\n");
                break;
            case '3':
            case '4':
            case '5':
                printf("\n[Sistema] Funcionalidade desabilitada nesta fase do trabalho.\n");
                break;
            default:
                printf("\n[Sistema] Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 'Q');
}

/**
 * @brief Implementa a funcionalidade "Consultar time".
 */
void funcionalidade_consultar_time(const BDTimes* bd_times) {
    char prefixo[MAX_NOME_TIME];
    Time* resultados[NUM_TIMES];
    
    printf("\n[Sistema]\n");
    printf("Digite o nome ou prefixo do time: ");
    
    // Limpa o buffer de entrada antes de ler a string
    while (getchar() != '\n');
    if (fgets(prefixo, MAX_NOME_TIME, stdin) == NULL) {
        return;
    }
    
    // Remove o newline se presente
    prefixo[strcspn(prefixo, "\n")] = 0;

    int num_encontrados = bd_times_busca_por_prefixo(bd_times, prefixo, resultados);

    if (num_encontrados > 0) {
        printf("\n[Sistema]\n");
        time_imprime_cabecalho_tabela();
        for (int i = 0; i < num_encontrados; i++) {
            time_imprime_linha_tabela(resultados[i]);
        }
        printf("-------------------------------------\n");
        printf("%d time(s) encontrado(s).\n", num_encontrados);
    } else {
        printf("\n[Sistema] Nenhum time encontrado com o prefixo '%s'.\n", prefixo);
    }
}

/**
 * @brief Implementa a funcionalidade "Consultar partidas".
 */
void funcionalidade_consultar_partidas(const BDPartidas* bd_partidas, const BDTimes* bd_times) {
    int modo;
    char prefixo[MAX_NOME_TIME];
    
    printf("\n[Sistema]\n");
    printf("Escolha o modo de consulta:\n");
    printf("1 - Por time mandante\n");
    printf("2 - Por time visitante\n");
    printf("3 - Por time mandante ou visitante\n");
    printf("4 - Retornar ao menu principal\n");
    printf("Opção: ");
    
    if (scanf("%d", &modo) != 1) {
        printf("\n[Sistema] Opção inválida.\n");
        while (getchar() != '\n'); // Limpa o buffer
        return;
    }
    
    if (modo == 4) {
        return;
    }
    
    if (modo < 1 || modo > 3) {
        printf("\n[Sistema] Modo de consulta inválido.\n");
        return;
    }

    printf("Digite o nome ou prefixo do time: ");
    
    // Limpa o buffer de entrada antes de ler a string
    while (getchar() != '\n');
    if (fgets(prefixo, MAX_NOME_TIME, stdin) == NULL) {
        return;
    }
    
    // Remove o newline se presente
    prefixo[strcspn(prefixo, "\n")] = 0;

    bd_partidas_consulta(bd_partidas, bd_times, prefixo, modo);
}
