#include <stdio.h>
#include <stdlib.h>
#include "cobra.h"

int main () {
    int win = 0, stop = 0;
    char mov[1];
    map M = malloc(sizeof (struct game_map));
    snake S = malloc(sizeof (struct head_tail));
    corpo no = malloc(sizeof (struct body));
    fruit F = malloc(sizeof (struct fruta));
    le_dados_ini (M, no, F);
    cria_mat(M); //seta os valores da matriz do jogo inicialmente todos com 0.
    S->tam = 1;
    cria_snake(S, no); //cria inicialmente a cobra, fazendo o ponteiro da cabeça e da cauda apontarem para o mesmo lugar inicial
    inicial_map(M, S, F); //define no mapa as posições inicias da fruta e da cobra
    print_map(M);
    /*Cada função do tipo x_die, verifica se ela irá bater nela mesma com a mov na direção x.
    Se for bater, retorna 1; se não, realiza a movimentação, atualiza o mapa e retorna 0.*/
    do {
        scanf("%s", mov);
        if (vai_comer(M, S, F, mov)) { //verifica se o movimento vai fazer a cobra comer a fruta
            aumenta_cobra(M, S, F);
            print_map(M);
            win = ganhou(M,S);
            if(win) //caso em que a cobra ganha o jogo
                break;
            recebe_fruta(M,F); //recebe os dados da nova fruta
            print_map(M);
        }
        else {
            if (mov[0] == 'w') {
                stop = w_die(M, S);
                print_map(M);
            }
            
            else if (mov[0] == 's') {
                stop = s_die(M, S);
                print_map(M);
            }
            
            else if (mov[0] == 'a') {
                stop = a_die(M, S);
                print_map(M);
            }
            else if (mov[0] == 'd') {
                stop = d_die(M, S);
                print_map(M);
            }
            win = ganhou(M,S);
        }
    } while (stop != 1 && win != 1); 
    //O loop para quando a cobra ocupa todo o mapa (win == 1) ou bate nela mesma (stop == 1).
    destroy_snake(S, S->head); //libera a memória ocupada pela cobra.
    destroy_map (M); //libera a memória ocupada pelo mapa do jogo.
    free(F); //libera a memória ocupada pela fruta.
    free(S);
    if (stop)
        printf("GAME OVER\n");
    else if (win)
        printf("YOU WIN\n");
    return 0;
}