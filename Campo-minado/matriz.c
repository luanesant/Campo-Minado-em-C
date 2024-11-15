#include "matriz.h"

/*Funcao VOID;
Inicializa uma matriz qualquer que seja quadrada, com um valor pre-definido.
    - Parametros:
        - nivel : variavel do tipo inteiro usada para dizer o tamanho da matriz;
        - valorInicial : variavel do tipo inteiro usada para iniciar os elementos da matriz;
        - mat : variavel do tipo ponteiro de ponteiro usada de molde, ou seja, e uma matriz generica que recebe um endereco de outra matriz para altera-la;
*/
void inicializarMatriz(int nivel, int valorInicial, int **mat){
    for(int i = 0; i < nivel; i++){
        for(int j = 0; j < nivel; j++){
            mat[i][j] = valorInicial;
        }
    }
}

/*Funcao Int;
Retorna a verificacao se o campo da matriz principal esta completo ou nao para o usuario continuar o jogo.
    - Parametros:
        - nivel : variavel do tipo inteiro usada para dizer o tamanho da matriz;
        - mat : variavel do tipo ponteiro de ponteiro usada de molde para a matriz principal do campo, recebe um endereco de outra matriz para altera-la;
        - mat : variavel do tipo ponteiro de ponteiro usada de molde para a matriz principal do usuario, recebe um endereco de outra matriz para altera-la;
*/
int matrizCompleta(int nivel, int **mat, int **matX){
    int continuarJogo = 1;
    for(int i = 0; i < nivel; i++){
        for(int j = 0; j < nivel; j++){
           if(matX[i][j] == -2 && mat[i][j] != -1){
                continuarJogo = 0;
            }
        }
    }

    return continuarJogo;
}


/*Funcao VOID;
Responsavel por iniciar as bombas em posicao aleatoria e a quantidade ao seu redor
    - Parametros:
        - nivel: variavel do tipo inteiro usada para especificar o tamanho da matriz que representa o campo de jogo.
        - numBombas: variavel do tipo ponteiro para inteiro que indica a quantidade de bombas para o usuario.
        - mat: variavel do tipo ponteiro de ponteiro que representa a matriz que o usuario ira visualizar.
*/
void iniciarMatrizBombas(int nivel, int numBombas, int **mat){
    int x, y;
    inicializarMatriz(nivel, 0, mat);
    while((x = rand()%nivel, y = rand()%nivel), numBombas > 0){
        if(mat[x][y] != -1){
            mat[x][y] = -1;
            numBombas--;
            for(int i = -1; i <= 1; i++) {
                for(int j = -1; j <= 1; j++) {
                    int aoRedorX = x + i;
                    int aoRedorY = y + j;
                    if(aoRedorX >= 0 && aoRedorX < nivel && aoRedorY >= 0 && aoRedorY < nivel && mat[aoRedorX][aoRedorY] != -1) {
                        mat[aoRedorX][aoRedorY]++;
                    }
                }
            }
        }
    }
}

/*Funcao VOID;
Responsavel por imprimir o campo minado para o usuario
    - Parametros:
        - nivel: variavel do tipo inteiro usada para especificar o tamanho da matriz que representa o campo de jogo.
        - matX: variavel do tipo ponteiro de ponteiro que representa a matriz que o usuario ira visualizar.
*/
void imprimirMatriz(int nivel, int **matX){
    printf("    ");
    for (int j = 0; j < nivel; j++) {
        printf("%2d ", j+1);
    }
    printf("\n");
    printf("    ");
    for (int j = 0; j < nivel; j++) {
        printf("___");
    }
    printf("\n");
    for(int i = 0; i < nivel; i++){
        printf("%2d |", i+1);
        for(int j = 0; j < nivel; j++){
            if (matX[i][j] == -2  ){
                 printf("\033[0;33m X \033[0m");
            }else{
                switch(matX[i][j]){
                    case -1:
                        printf("\033[1;35m%2d \033[0m", matX[i][j]);
                        break;
                    case 0:
                        printf("%2d ", matX[i][j]);
                        break;
                    case 1:
                        printf("\033[1;34m%2d \033[0m", matX[i][j]);
                        break;
                    case 2:
                        printf("\033[1;32m%2d \033[0m", matX[i][j]);
                        break;
                    default:
                        printf("\033[1;31m%2d \033[0m", matX[i][j]);
                        break;
                    }
            }
        }
        printf("\n");
    }
}

/*Funcao VOID;
Responsavel por liberar a matriz
    - Parametros:
        - mat: variavel do tipo ponteiro de ponteiro que representa a matriz que o usuario ira liberar.
        - qtd_linhas: variavel do tipo inteiro usada para especificar a quantidade de linhas da matriz.
*/
void liberar_matriz(int **mat, int qtd_linhas){
  for(int i = 0; i < qtd_linhas; i++){
    free(mat[i]);
  }
  free(mat);
}

/*Funcao **Int;
Responsavel por alocar a matriz
    - Parametros:
        - linhas: variavel do tipo inteiro usada para especificar a quantidade de linhas da matriz.
        - colunas: variavel do tipo inteiro usada para especificar a quantidade de colunas da matriz.
*/
int **alocar_matriz(int linhas, int colunas){
  int **mat = (int **) malloc(linhas * sizeof(int *));

    if (mat == NULL) {
        printf("Erro ao alocar memória para o jogo.\n");
        free(mat);
        return NULL;
    }

  for(int i = 0; i < linhas; i++){
    mat[i] = (int *) malloc(colunas * sizeof(int));
    if (mat[i] == NULL) {
        printf("Erro ao alocar memória para o jogo.\n");
        free(mat[i]);
        free(mat);
        return NULL;
    }
  }
  

  return mat;
}