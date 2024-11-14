// matriz.h
#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declarações de funções para manipulação de matrizes
void iniciarMatrizBombas(int nivel, int numBombas, int **mat);
void imprimirMatriz(int nivel, int **matX);
int matrizCompleta(int nivel, int **mat, int **matX);
void inicializarMatriz(int nivel, int valorInicial, int **mat);

#endif // MATRIZ_H
