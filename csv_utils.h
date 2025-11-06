#ifndef CSV_UTILS_H
#define CSV_UTILS_H

#include <stdio.h>

// Define o tamanho máximo de uma linha no arquivo CSV
#define MAX_LINE_LENGTH 256

// Define o tamanho máximo para o nome de um time
#define MAX_NOME_TIME 50

// Função para ler uma linha do arquivo, ignorando o cabeçalho
char* read_line(FILE *fp, char *buffer, int max_len);

#endif // CSV_UTILS_H
