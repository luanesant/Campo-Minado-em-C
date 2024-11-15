#include "log.h"

/* Funcao Log*:
   Responsável por criar um novo arquivo de log.
   Abre o arquivo em modo de adição (append) e retorna um ponteiro para a estrutura Log.
   Retorna NULL em caso de falha ao abrir o arquivo. */
Log* criarArquivo(const char* nome_do_arquivo) {
    Log* log = (Log*) malloc(sizeof(Log));
    log->arquivo = fopen(nome_do_arquivo, "a");
    
    if (log->arquivo == NULL) {
        free(log);
        return NULL;
    }

    return log;
}

/* Funcao Log*:
   Responsável por criar o arquivo de log e registra a data e hora de início do jogo.
   Retorna o ponteiro para a estrutura Log. */
Log* iniciarLog(const char* nome_do_arquivo) {
    Log* log = criarArquivo(nome_do_arquivo);
    log->data_de_inicio = time(NULL);
    fprintf(log->arquivo, "Data de inicio do jogo: %s\n", ctime(&log->data_de_inicio));
    return log;
}

/* Funcao VOID:
   Responsável por registrar uma jogada no arquivo de log.
   Registra a coordenada escolhida pelo usuário no formato [x, y]. */
void registrarJogada(Log* log, int x, int y) {    
    fprintf(log->arquivo, "---------------------\n");
    fprintf(log->arquivo, "Coordenada escolhida: [%d, %d]\n", x, y);
}


/* Funcao VOID:
   Responsável por registrar o estado da matriz no arquivo de log.
   Grava a matriz do jogo no arquivo de log, linha por linha. */
void registrarMatriz(Log* log, int** matriz, int linhas, int colunas){
    fprintf(log->arquivo, "Matriz do usuario:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fprintf(log->arquivo, "%2d ", matriz[i][j]);
        }
        fprintf(log->arquivo, "\n");
    }
    fprintf(log->arquivo, "\n");
}

/* Funcao VOID:
   Responsável por registrar o status final da partida.
   Indica no log se o jogo foi vencido ou perdido. */
void registrarStatus(Log* log, int ganhou) {    
    fprintf(log->arquivo, "STATUS: Partida ");
    if(ganhou){
        fprintf(log->arquivo, "Vencida");
    }else{
        fprintf(log->arquivo, "Perdida");
    }
}

/* Funcao VOID:
   Responsável por fechar o arquivo de log.
   Fecha o arquivo associado à estrutura Log. */
void finalizarLog(Log* log) {
    if (log->arquivo != NULL) {
        fprintf(log->arquivo, "\n=====\n\n");
        fecharArquivo(log);
    }
    free(log);
}



void fecharArquivo(Log* log) {
        fclose(log->arquivo);
}
