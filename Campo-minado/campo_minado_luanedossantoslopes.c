#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matriz.h"
#include "log.h"

#define BOMBAS -1
#define USERX -2
#define FACIL 10
#define MEDIO 20
#define DIFICIL 30
#define FACIL_NUM_BOMBAS 15
#define MEDIO_NUM_BOMBAS 60
#define DIFICIL_NUM_BOMBAS 135
void mostrarFraseDeNivel(int *opcao, int nivel);
void limparTela();
void liberarCoordenada(int nivel, int cordUserX, int cordUserY, int **mat, int **matX);
void iniciarJogo(int *opcao, int nivel, int **mat, int **matX);
void menu(int *opcao, int *nivel, int *numBombas);


/*Na funcao main() instanciamos todo o nosso campo e fazemos a logica do loop de tentar novamente.*/
int main(){
    srand(time(NULL));

        int op, nivel, numBombas;
        menu(&op, &nivel, &numBombas);
         int **mat = NULL,**matX = NULL;
        if (op != 4){
            mat = alocar_matriz(nivel, nivel);
            matX = alocar_matriz(nivel, nivel);

            inicializarMatriz(nivel, USERX, matX);
            iniciarMatrizBombas(nivel, numBombas, mat);
            // imprimirMatriz(nivel, mat);
            iniciarJogo(&op, nivel, mat, matX);

            liberar_matriz(mat, nivel);
            liberar_matriz(matX, nivel);
        }else{
            printf("\033[1;32mObrigado por jogar!!\n Ate a proxima\033[0m\n");
            if (mat != NULL || matX != NULL){
                for(int i = 0; i < nivel; i++){
                    liberar_matriz(mat, nivel);
                    liberar_matriz(matX, nivel);
                }
            }
            return 1;
        }

     printf("\033[1;32mObrigado por jogar!!\n Ate a proxima\033[0m\n");
    return 0;
}

/*Funcao VOID;
Responsavel por mostrar o menu de niveis para o usuario
    - Parametros:
        - opcao: variavel do tipo ponteiro para inteiro que indica a opcao de nivel de dificuldade escolhida pelo usuario.
        - nivel: variavel do tipo inteiro usada para especificar o tamanho da matriz que representa o campo de jogo.
        - numBombas: variavel do tipo ponteiro para inteiro que indica a quantidade de bombas para o usuario.
*/
void menu(int *opcao, int *nivel, int *numBombas){
    limparTela();
    int op;
    printf("Escolha o nivel do Jogo:");
    printf("\n1 - Facil\n2 - Normal\n3 - Dificil\n4 - Sair\n");
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

    case 4:
        *opcao = op;
        break;

    default:
        printf("\n\nOpcao INVALIDA!\nTente Novamente\n\n");
        system("pause");
        while (getchar() != '\n');
        menu(opcao, nivel, numBombas);
        break;
    }

    limparTela();
}


/*Funcao VOID;
Limpa a tela do terminal dependendo do SO usado
*/
void limparTela() {
    #ifdef _WIN32
        system("cls");  
    #else
        system("clear");  
    #endif
}


/*Funcao VOID;
Responsavel por fazer a iniciacao do jogo e exibicao do campo minado para o usuarip
    - Parametros:
        - opcao: variavel do tipo ponteiro para inteiro que indica a opcao de nivel de dificuldade escolhida pelo usuario.
        - nivel: variavel do tipo inteiro usada para especificar o tamanho da matriz que representa o campo de jogo.
        - mat: variavel do tipo ponteiro de ponteiro que representa a matriz principal do campo, contendo a posicao das bombas e o numero de bombas adjacentes.
        - matX: variavel do tipo ponteiro de ponteiro que representa a matriz do usuario, que armazena as coordenadas que o usuario ja abriu durante o jogo.
*/
void iniciarJogo(int *opcao, int nivel, int **mat, int **matX){
    Log* log = iniciarLog("log.txt");
    if (log == NULL) {
        printf("Erro ao iniciar o log do jogo.\n");
        return;
    }

    mostrarFraseDeNivel(opcao, nivel);

    int win = 0, gameOver = 0;
    int cordUserX, cordUserY, coordenadas;
    imprimirMatriz(nivel, matX);
    printf("\n\033[1;32mDigite as cordenadas x,y: \033[0m");

    while(gameOver == 0){
        coordenadas = scanf("%d,%d", &cordUserX, &cordUserY);
        if(coordenadas == 2){
            registrarJogada(log, mat, nivel, nivel, cordUserX, cordUserY);
            if(cordUserX-1 >= 0 && cordUserX-1 < nivel && cordUserY-1 >= 0 && cordUserY-1 < nivel){
                if(matX[cordUserX-1][cordUserY-1] == USERX){
                    limparTela();
                    mostrarFraseDeNivel(opcao, nivel);
                    if(mat[cordUserX-1][cordUserY-1] == BOMBAS){
                        matX[cordUserX-1][cordUserY-1] = BOMBAS;
                        imprimirMatriz(nivel, matX);
                        win = 0;
                        gameOver = 1;
                    }else{
                        liberarCoordenada(nivel, cordUserX-1, cordUserY-1, mat, matX);
                        imprimirMatriz(nivel, matX);
                        if(matrizCompleta(nivel, mat, matX)){
                            win = 1;
                            gameOver = 1;
                        }else {
                            printf("\n\033[1;32mDigite as cordenadas x,y: \033[0m");
                        }
                    }
                }else{
                    printf("\n\033[1;31mOPS! Voce ja tentou essas danadinho!\033[0m");
                    printf("\n\033[1;32mDigite as novas cordenadas x,y: \033[0m");
                }

            }else{
                printf("\n\033[1;31mOPS!! Coordenadas inexistentes \(-_-)/\033[0m");
                printf("\n\033[1;32mDigite as novas cordenadas x,y: \033[0m");
            }
        }else{
            printf("\n\033[1;31mOPS!! Entrada invalida. \(-_-)/\033[0m");
            printf("\n\033[1;32mDigite as cordenadas x,y: \033[0m");
            while (getchar() != '\n');
        }
    }

    if(win){
        printf("\n\n\033[1;35m(=^.^=) Parabens, vc eh fera\033[0m\n\n");
        printf("\033[1;31mCampo Minado do Jogo\033[0m\n");
        imprimirMatriz(nivel, matX);
        printf("\n\033[1;31mCampo Minado Final\033[0m\n");
        imprimirMatriz(nivel, mat);
    }else{
        printf("\t\n\n\033[1;31mGAME OVER :-(\033[0m\n\n");
        printf("\033[1;31mCampo Minado Resultado Final\033[0m\n");
        imprimirMatriz(nivel, mat);
    }

    // Finaliza o log no final do jogo
    finalizarLog(log);
}


/*Funcao VOID;
Responsavel por fazer liberacao das coordenadas na matriz do usuario;
    - Parametros:
        - nivel: variavel do tipo inteiro que indica o tamanho da matriz, determinando o numero de linhas e colunas no campo de jogo.
        - cordUserX: variavel do tipo inteiro que representa a coordenada X  que e a linha escolhida pelo usuario para abrir uma posicao no campo.
        - cordUserY: variavel do tipo inteiro que representa a coordenada Y que e a coluna escolhida pelo usuario para abrir uma posicao no campo.
        - mat: variavel do tipo ponteiro de ponteiro que representa a matriz principal do campo, contendo a posicao das bombas e o numero de bombas adjacentes.
        - matX: variavel do tipo ponteiro de ponteiro que representa a matriz do usuario, que armazena as coordenadas que o usuario ja abriu.
*/
void liberarCoordenada(int nivel, int cordUserX, int cordUserY, int **mat, int **matX){
    int contMinas = 0;
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
                int aoRedorX = cordUserX + i;
                int aoRedorY = cordUserY + j;
                if(aoRedorX >= 0 && aoRedorX < nivel && aoRedorY >= 0 && aoRedorY < nivel && mat[aoRedorX][aoRedorY] == BOMBAS) {
                    contMinas++;
                }
        }
    }

    matX[cordUserX][cordUserY] = contMinas;
        // int contMinas = 0;
    if(contMinas == 0){
            for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
                int aoRedorX = cordUserX + i;
                int aoRedorY = cordUserY + j;
                if(aoRedorX >= 0 && aoRedorX < nivel && aoRedorY >= 0 && aoRedorY < nivel && !(aoRedorX == cordUserX && aoRedorY == cordUserY) && matX[aoRedorX][aoRedorY] == -2) {
                    liberarCoordenada(nivel,aoRedorX, aoRedorY, mat, matX);
                }
        }
    }
    }
}

/*Funcao VOID;
REsponsavel por mostrar o titulo do campo minado durante o jogo
    - Parametros:
        - opcao: variavel do tipo ponteiro para inteiro que indica a opcao de nivel de dificuldade escolhida pelo usuario.
        - nivel: variavel do tipo inteiro usada para especificar o tamanho da matriz que representa o campo de jogo.
*/
void mostrarFraseDeNivel(int *opcao, int nivel){
    switch (*opcao){
    case 1:
        printf("\033[1;32mCAMPO MINADO NIVEL FACIL (%dx%d)\033[0m\n",nivel,nivel);
        break;
    case 2:
        printf("\033[1;32mCAMPO MINADO NIVEL MEDIO (%dx%d)\033[0m\n",nivel,nivel);
        break;
    case 3:
        printf("\033[1;32mCAMPO MINADO NIVEL DIFICIL (%dx%d)\033[0m\n",nivel,nivel);
        break;
    default:
        break;
    }
}