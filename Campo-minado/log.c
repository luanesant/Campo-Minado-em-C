#include "log.h"

Log* criarArquivo(const char* nome_do_arquivo) {
    Log* log = (Log*) malloc(sizeof(Log));
    log->arquivo = fopen(nome_do_arquivo, "w");
    
    if (log->arquivo == NULL) {
        free(log);
        return NULL;
    }

    return log;
}

Log* iniciarLog(const char* nome_do_arquivo) {
    Log* log = criarArquivo(nome_do_arquivo);


    // Obtenha e registre a data e hora
    log->data_de_inicio = time(NULL);
    fprintf(log->arquivo, "Data de inicio do jogo: %s\n", ctime(&log->data_de_inicio));
    return log;
}

void registrarJogada(Log* log, int** matriz, int linhas, int colunas, int x, int y) {
    fprintf(log->arquivo, "Coordenada escolhida: [%d, %d]\n", x, y);
    fprintf(log->arquivo, "Matriz do usuario:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fprintf(log->arquivo, "%2d ", matriz[i][j]);
        }
        fprintf(log->arquivo, "\n");
    }
    fprintf(log->arquivo, "---------------------\n");
}

void finalizarLog(Log* log) {
    if (log->arquivo != NULL) {
        fecharArquivo(log);
    }
    free(log);
}


void fecharArquivo(Log* log) {
        fclose(log->arquivo);
}