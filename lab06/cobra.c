#include <stdio.h>
#include <stdlib.h>
#include "cobra.h"

void le_dados_ini (map m, corpo no, fruit f) {
    //lê todos os dados iniciais.
    char str_fruta[5], str_cobra[5];
    scanf("%d", &m->l), scanf("%d", &m->c); //lê tamanho das linhas e colunas da matriz.
    scanf("%s", str_fruta);
    scanf("%d", &f->x), scanf("%d", &f->y); //lê a posição inicial (x,y) da fruta no jogo.
    scanf("%s", str_cobra);
    scanf("%d", &no->x), scanf("%d", &no->y); //lê a posição inicial (x,y) da cobra no jogo.
}
 
void cria_mat (map m) {
    //cria a matriz do mapa - aloca memória e seta todos os seus valores iniciais como 0.
    m->mat = malloc(m->l * sizeof(int*)); //aloca espaço para cada linha
    for (int i = 0; i < m->l; i++)
        m->mat[i] = malloc(m->c * sizeof(int)); //aloca espaço para cada elemento dentro das linhas
    for (int i = 0; i < m->l; i++)
        for(int j = 0; j < m->c; j++)
            m->mat[i][j] = 0; //seta todos os valores iniciais da matriz como 0.
}
 
void inicial_map (map m, snake s, fruit f) {
    //seta as condições iniciais do mapa.
    m->mat[s->head->x][s->head->y] = 1; //define como 1 na matriz as posições que a cobra ocupa
    m->mat[f->x][f->y] = -1; //define como -1 na matriz a posição da primeira fruta.
}
 
void recebe_fruta (map m, fruit f) {
    //recebe os dados da posição nova da fruta após a anterior ter sido comida e atualiza o mapa.
    char str_fruta[5];
    scanf("%s", str_fruta);
    scanf("%d", &f->x), scanf("%d", &f->y); //lê a nova posição (x,y) da fruta.
    m->mat[f->x][f->y] = -1; //atualiza o valor no mapa.
}
 
void cria_snake (snake s, corpo no_ini) {
    //define os ponteiros iniciais da cobra.
    s->head = no_ini;
    s->tail = no_ini;
    s->tail->ant = NULL;
    s->tail->prox = NULL;
    s->head->prox = NULL;
    s->head->ant = NULL;
}
 
void aumenta_cobra(map m, snake s, fruit f) {
    //função responsável por aumentar o tamanho da cobra quando ela come uma fruta.
    //é "adicionado uma nova cabeça" na posição onde está a fruta.
    corpo new = malloc(sizeof(struct body));
    new->x = f->x;
    new->y = f->y;
    m->mat[new->x][new->y] = 1;
    new->prox = s->head;
    new->ant = NULL;
    s->head->ant = new;
    s->head = new;
    s->tam++;
}
 
int ganhou(map m, snake s) {
    //verifica se a cobra ocupa todo o espaço do mapa.
    if (m->l * m->c == s->tam)
        return 1; //cobra ocupa todo o jogo - ganhou.
    return 0;
}
 
void print_map (map m) {
    //printa o mapa com os carecteres adequadamente.
    for (int i = 0; i < m->l; i++) {
        for(int j = 0; j < m->c; j++) {
            if (m->mat[i][j] == 1)
                printf("%s ", "#"); //posição da cobra
            else if (m->mat[i][j] == -1)
                printf("%s ", "*"); //posição da fruta
            else
                printf("%s ", "_"); //posição do resto do mapa
        }
        printf("\n");
    }
    printf("\n");
}
 
int vai_comer (map m, snake s, fruit f, char str[1]) {
    //verifica se com a movimentação mov da cobra ela irá ou não comer a fruta
    if (str[0] == 'w')  {
        if (s->head->x == 0 && f->x == m->l - 1 && f->y == s->head->y)
            return 1;
        if (s->head->x == 0)
            return 0;
        if (m->mat[s->head->x - 1][s->head->y] == -1)
            return 1;
    }
    else if (str[0] == 's') {
        if (s->head->x == m->l - 1 && f->x == 0 && f->y == s->head->y)
            return 1;
        if (s->head->x == m->l - 1)
            return 0;
        if (m->mat[s->head->x + 1][s->head->y] == -1)
            return 1;
    }
    else if (str[0] == 'a') {
        if (s->head->y == 0 && f->x == s->head->x && f->y == m->c - 1)
            return 1;
        if (s->head->y == 0)
            return 0;
        if (m->mat[s->head->x][s->head->y - 1] == -1)
            return 1;
    }
    else if (str[0] == 'd') {
        if (s->head->y == m->c - 1 && f->x == s->head->x && f->y == 0)
            return 1;
        if (s->head->y == m->c - 1)
            return 0;
        if (m->mat[s->head->x][s->head->y + 1] == -1)
            return 1;
    }
    return 0;
}
 
void mov_geral (map m, snake s, corpo no_x) {
    //função "auxiliar" que realiza um procedimento padrão para todas as movimentações.
    /*basicamente faz o ponteiro da cabeça apontar para o novo nó;
    retira a cauda e faz o pont da cauda apontar para o anterior dela.*/
    no_x->prox = s->head;
    no_x->ant = NULL;
    s->head->ant = no_x;
    s->head = no_x;

    m->mat[s->tail->x][s->tail->y] = 0;
    s->tail = s->tail->ant;
    free(s->tail->prox);
    s->tail->prox = NULL;
    m->mat[no_x->x][no_x->y] = 1;
}

int w_die (map m, snake s) {
    //Mov a cobra para cima. Se ela for bater, retorna 1, se não, move e retorna 0.
    corpo no1;
    no1 = malloc(sizeof(struct body));
    if (s->head->x == 0)
        no1->x = m->l - 1;
    else
        no1->x = s->head->x - 1;
    no1->y = s->head->y;

    if (m->mat[no1->x][no1->y] == 1) {
        free(no1);
        return 1; //caso em que a cobra irá "bater nela mesma"
    }
    mov_geral (m, s, no1);
    return 0;
}

int s_die (map m, snake s) {
    //Mov a cobra para baixo. Se ela for bater, retorna 1, se não, move e retorna 0.
    corpo no2;
    no2 = malloc(sizeof(struct body));
    if (s->head->x == m->l - 1)
        no2->x = 0;
    else
        no2->x = s->head->x + 1;
    no2->y = s->head->y;

    if (m->mat[no2->x][no2->y] == 1) {
        free(no2);
        return 1; //caso em que a cobra irá "bater nela mesma"
    }
    mov_geral (m, s, no2);
    return 0;
}

int a_die (map m, snake s) {
    //Mov a cobra para a esquerda. Se ela for bater, retorna 1, se não, move e retorna 0.
    corpo no3;
    no3 = malloc(sizeof(struct body));
    if (s->head->y == 0)
        no3->y = m->c - 1;
    else
        no3->y = s->head->y - 1;
    no3->x = s->head->x;

    if (m->mat[no3->x][no3->y] == 1) {
        free(no3);
        return 1; //caso em que a cobra irá "bater nela mesma"
    }
    mov_geral (m, s, no3);
    return 0;
}

int d_die (map m, snake s) {
    //Mov a cobra para a direita. Se ela for bater, retorna 1, se não, move e retorna 0.
    corpo no4;
    no4 = malloc(sizeof(struct body));
    if (s->head->y == m->c - 1)
        no4->y = 0;
    else
        no4->y = s->head->y + 1;
    no4->x = s->head->x;

    if (m->mat[no4->x][no4->y] == 1) {
        free(no4);
        return 1; //caso em que a cobra irá "bater nela mesma"
    }
    mov_geral (m, s, no4);
    return 0;
}

void destroy_snake (snake s, corpo no_atual) {
    //libera a memória ocupada pela cobra.
    if (no_atual != NULL) {
        destroy_snake(s, no_atual->prox);
        free(no_atual);
    }
}

void destroy_map (map m) {
    //libera a memória ocupada pelo mapa do jogo.
    for (int i = 0; i < m->l; i++)
        free(m->mat[i]);
    free(m->mat);
    free(m);
}