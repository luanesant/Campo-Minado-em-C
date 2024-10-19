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
void iniciarJogo(int *opcao, int nivel, int **mat, int **matX);
void liberarCoordenada(int nivel, int cordUserX, int cordUserY, int **mat, int **matX);
void mostrarFraseDeNivel(int *opcao, int nivel);
int campoCompleto(int nivel, int **mat, int **matX);
void inicializarMatriz(int nivel, int valorInicial, int **mat);
void limparTela();

/*Na funcao main() instanciamos todo o nosso campo e fazemos a logica do loop de tentar novamente.*/
int main(){
    srand(time(NULL));
    char tryAgain;
    do {
        int op, nivel, numBombas;
        menu(&op, &nivel, &numBombas);
         int **mat,**matX;
        if (op != 4){
            mat = (int**) malloc(nivel * sizeof(int*));
            matX = (int**) malloc(nivel * sizeof(int*));

        if (mat == NULL || matX == NULL) {
                printf("Erro ao alocar memória para o jogo.\n");
                free(mat);
                free(matX);
                return 1;
            }

            for(int i = 0; i < nivel; i++){
                mat[i] = (int*) malloc(nivel * sizeof(int));
                matX[i] = (int*) malloc(nivel * sizeof(int));
                
            if (mat[i] == NULL || matX[i] == NULL) {
                    printf("Erro ao alocar memória para o jogo.\n");
                    free(mat[i]);
                    free(matX[i]);
                    free(mat);
                    free(matX);
                    return 1;
                }
            }

            inicializarMatriz(nivel, USERX, matX);
            iniciarMatrizBombas(nivel, numBombas, mat);
            // imprimirMatriz(nivel, mat);
            iniciarJogo(&op, nivel, mat, matX);

            printf("Tentar novamente? (s/n): ");
            scanf(" %c", &tryAgain);
            while (tryAgain != 's' && tryAgain != 'n') {
                printf("\nOpcao invalida. Deseja tentar novamente? (s/n): ");
                scanf(" %c", &tryAgain);
            }

            for(int i = 0; i < nivel; i++){
                free(mat[i]);
                free(matX[i]);
            }
            free(mat);
            free(matX);
        }else{
            printf("\033[1;32mObrigado por jogar!!\n Ate a proxima\033[0m\n");
            tryAgain = 'n';
            if (mat != NULL || matX != NULL){
                for(int i = 0; i < nivel; i++){
                    free(mat[i]);
                    free(matX[i]);
                }
            }
            
            free(mat);
            free(matX);

            return 1;
        }
    } while (tryAgain == 's');

     printf("\033[1;32mObrigado por jogar!!\n Ate a proxima\033[0m\n");
    return 0;
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
int campoCompleto(int nivel, int **mat, int **matX){
    int continuarJogo = 1;
    for(int i = 0; i < nivel; i++){
        for(int j = 0; j < nivel; j++){
           if(matX[i][j] == USERX && mat[i][j] != BOMBAS){
                continuarJogo = 0;
            }
        }
    }

    return continuarJogo;
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
    mostrarFraseDeNivel(opcao, nivel);

    int win = 0, gameOver = 0;
    int cordUserX, cordUserY, coordenadas;
    imprimirMatriz(nivel, matX);
    printf("\n\033[1;32mDigite as cordenadas x,y: \033[0m");


    while(gameOver == 0){
        coordenadas = scanf("%d,%d", &cordUserX, &cordUserY);
        if(coordenadas == 2){
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
                        if(campoCompleto(nivel, mat, matX)){
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
        printf("___");
    }
    printf("\n");
    for(int i = 0; i < nivel; i++){
        printf("%2d |", i+1);
        for(int j = 0; j < nivel; j++){
            if (matX[i][j] == USERX  ){
                 printf("\033[0;33m X \033[0m");
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
