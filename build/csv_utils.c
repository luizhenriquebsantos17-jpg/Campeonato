#include "csv_utils.h"
#include <string.h>
#include <stdlib.h>

/**
 * @brief Lê uma linha do arquivo, ignorando o cabeçalho na primeira chamada.
 * 
 * @param fp Ponteiro para o arquivo.
 * @param buffer Buffer para armazenar a linha lida.
 * @param max_len Tamanho máximo do buffer.
 * @return char* Retorna o ponteiro para o buffer em caso de sucesso, ou NULL em caso de EOF ou erro.
 */
char* read_line(FILE *fp, char *buffer, int max_len) {
    static int first_call = 1;
    
    if (fgets(buffer, max_len, fp) == NULL) {
        return NULL; // EOF ou erro
    }

    if (first_call) {
        // Ignora o cabeçalho na primeira chamada
        first_call = 0;
        if (fgets(buffer, max_len, fp) == NULL) {
            return NULL; // EOF ou erro após ignorar cabeçalho
        }
    }

    // Remove o caractere de nova linha, se presente
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    return buffer;
}
