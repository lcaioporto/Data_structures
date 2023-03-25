#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

void cria_pilha(p_pilha pilha) {
    //define as condições iniciais da pilha
    pilha->topo = NULL, pilha->base = NULL;
    pilha->tam = 0;
}

void adiciona_no (p_pilha pilha) {
    //adiciona um novo nó a pilha
    p_no novo = calloc(1, sizeof(struct no_pilha));
    if (pilha->tam == 0)
        pilha->base = pilha->topo = novo;
    else {
        pilha->topo->prox = novo;
        pilha->topo = novo;
    }
    pilha->tam++;
}

void empilhar(p_pilha pilha, char txt) {
    //adiciona um novo caracter no topo da pilha.
    //caso necessario, aumenta o tamanho da pilha usando "adiciona no".
    if (pilha->tam == 0)
        adiciona_no (pilha);
    else if (pilha->topo->str[49]  != '\000')
        adiciona_no (pilha);
    for (int i = 0; i < 50; i++){
        if (pilha->topo->str[i]  == '\000') {
            pilha->topo->str[i] = txt;
            pilha->topo->str[i+1] = '\0';
            break;
        }
    }
}

void desempilha_topo (p_pilha pilha) {
    //remove o topo da pilha.
    p_no atual = malloc(sizeof(struct no_pilha));
    atual = pilha->base;
    while(atual->prox != pilha->topo) //encontrar o anterior do topo
        atual = atual->prox;
    atual->prox = NULL;
    free(pilha->topo);
    pilha->topo = atual;
    pilha->tam--;
}

void aux_desempilhar (p_pilha pilha, int n, int x, int para_em, int *ja_deletou) {
    /*
    função recursiva que remove caracteres do topo da pilha.
    caso necessário, remove o nó inteiro do topo 
    (caso em que deseja-se remover x maior do que o número de caracteres ocupados no topo)
    */
    int m = n;
    if (para_em != 0)
        m = 50;
    for (; m >= para_em; m--)
        pilha->topo->str[m] = '\000';
    *ja_deletou+=n;
    if (*ja_deletou < x) { 
        //caso em que já foi deletado todos os caracteres do topo e ainda deseja-se deletar mais
        desempilha_topo(pilha);
        aux_desempilhar(pilha, x-n, x, 50-(x-n),  ja_deletou);
    }
}

void desempilhar_geral(p_pilha pilha, int x) {
    //realiza toda a ação de desempilhar um número x de caracteres.
    int n = 0;
    for (n = 0; n < 50; n++) 
        if (pilha->topo->str[n] == '\000')
            break;
    //n representa a posição onde começa a ter caracter dentro do vetor de caracteres do topo
    if (n > x) //caso em que não será necessário retirar o topo da pilha
        for (int i = 0; i < x; i++) 
            pilha->topo->str[n-1-i] = '\000';
    else {
        int ja_deletou = 0;
        aux_desempilhar(pilha, n, x, 0, &ja_deletou);
    }
}

void destroi_pilha (p_pilha pilha, p_no no_atual) {
    //libera o espaço ocupado por uma pilha.
    if (no_atual != NULL && no_atual != no_atual->prox) {
        destroi_pilha(pilha, no_atual->prox);
        free(no_atual);
    }
}

void printa_pilha (p_pilha pilha, p_no atual) {
    //printa os dados da pilha
    if (atual != NULL && atual != atual->prox) {
        for (int k = 0; k < 50; k++)
            printf("%c", atual->str[k]);
        if (atual->prox != NULL)
            printa_pilha(pilha, atual->prox);
    }
}