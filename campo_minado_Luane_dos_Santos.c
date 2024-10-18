#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define BOMBAS -1
#define USERX -2
#define FACIL 10
#define MEDIO 20
#define DIFICIL 30
#define FACIL_NUM_BOMBAS 3
#define MEDIO_NUM_BOMBAS 6
#define DIFICIL_NUM_BOMBAS 9

//Declarando as funcoes para serem usadas depois da funcao main();
void menu(int *opcao, int *nivel, int *numBombas);
void iniciarMatrizBombas(int nivel, int numBombas, int **mat);
void imprimirMatriz(int nivel, int **matX);

int main(){
    srand(time(NULL));
    char tryAgain;
    do {
        int op, nivel, numBombas;
        menu(&op, &nivel, &numBombas);

        int **mat = (int**) malloc(nivel * sizeof(int*));
        int **matX = (int**) malloc(nivel * sizeof(int*));

        for(int i = 0; i < nivel; i++){
            mat[i] = (int*) malloc(nivel * sizeof(int));
            matX[i] = (int*) malloc(nivel * sizeof(int));
        }

        printf("Tentar novamente? (s/n): ");
        scanf(" %c", &tryAgain);
        while (tryAgain != 's' && tryAgain != 'n') {
            printf("Opcao invalida. Deseja tentar novamente? (s/n): ");
            scanf(" %c", &tryAgain);
        }

        for(int i = 0; i < nivel; i++){
            free(mat[i]);
            free(matX[i]);
        }
        free(mat);
        free(matX);

    } while (tryAgain == 's');
    return 0;
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
        if(mat[x][y] != BOMBAS){
            mat[x][y] = BOMBAS;
            numBombas--;
            for(int i = -1; i <= 1; i++) {
                for(int j = -1; j <= 1; j++) {
                    int aoRedorX = x + i;
                    int aoRedorY = y + j;
                    if(aoRedorX >= 0 && aoRedorX < nivel && aoRedorY >= 0 && aoRedorY < nivel && mat[aoRedorX][aoRedorY] != BOMBAS) {
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
        printf("___", j+1);
    }
    printf("\n");
    for(int i = 0; i < nivel; i++){
        printf("%2d |", i+1);
        for(int j = 0; j < nivel; j++){
            if (matX[i][j] == USERX  ){
                 printf("\033[1;32m X \033[0m");
            }else{
                switch(matX[i][j]){
                    case BOMBAS:
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
Responsavel por mostrar o menu de niveis para o usuario
    - Parametros:
        - opcao: variavel do tipo ponteiro para inteiro que indica a opcao de nivel de dificuldade escolhida pelo usuario.
        - nivel: variavel do tipo inteiro usada para especificar o tamanho da matriz que representa o campo de jogo.
        - numBombas: variavel do tipo ponteiro para inteiro que indica a quantidade de bombas para o usuario.
*/
void menu(int *opcao, int *nivel, int *numBombas){
    system("cls");
    int op;
    printf("Escolha o nivel do Jogo:");
    printf("\n1 - Facil\n2 - Normal\n3 - Dificil\n");
    printf("Opcao: ");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
        *opcao = op;
        *nivel = FACIL;
        *numBombas = FACIL_NUM_BOMBAS;
        break;
    case 2:
        *opcao = op;
        *nivel = MEDIO;
        *numBombas = MEDIO_NUM_BOMBAS;
        break;

    case 3:
        *opcao = op;
        *nivel = DIFICIL;
        *numBombas = DIFICIL_NUM_BOMBAS;
        break;
    default:
        printf("\n\nOpcao INVALIDA!\nTente Novamente\n\n");
        system("pause");
        system("cls");
        menu(opcao, nivel, numBombas);
        break;
    }

    system("cls");
}
