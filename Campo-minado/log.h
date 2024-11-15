#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct do LOG
typedef struct {
    FILE *arquivo; ;;
    time_t data_de_inicio; // data de inicio do jogo
} Log;

// Funções para o TAD Log
Log* criarArquivo(const char* nome_do_arquivo);
Log* iniciarLog(const char* nome_do_arquivo);
void registrarJogada(Log* log, int x, int y);
void registrarMatriz(Log* log, int** matriz, int linhas, int colunas);
void finalizarLog(Log* log);
void fecharArquivo(Log* log);
void registrarStatus(Log* log, int ganhou);

#endif // LOG_H
