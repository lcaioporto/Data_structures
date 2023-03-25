#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

p_grafo criar_grafo(int n) {
    //seta as condições iniciais para inicializar o grafo
    int i;
    p_grafo g = malloc(sizeof(struct grafo));
    g->n = n;
    g->adjacencia = malloc(n * sizeof(p_no));
    for (i = 0; i < n; i++)
        g->adjacencia[i] = NULL;
    return g;
}

p_no insere_na_lista(p_no lista, int v) {
    //insere um novo nó na lista ligada.
    p_no novo = malloc(sizeof(struct no));
    novo->v = v;
    novo->prox = lista;
    return novo;
}

void insere_aresta(p_grafo g, int u, int v) {
    //dados os vértices u,v e um grafo g insere uma aresta na lista de adjacencia de g.
    g->adjacencia[v] = insere_na_lista(g->adjacencia[v], u);
    g->adjacencia[u] = insere_na_lista(g->adjacencia[u], v);
}

p_no remove_da_lista(p_no lista, int v) {
    //remove um determinado nó de uma lista ligada.
    p_no proximo;
    if (lista == NULL)
        return NULL;
    else if (lista->v == v) {
        proximo = lista->prox;
        free(lista);
        return proximo;
    } 
    else {
        lista->prox = remove_da_lista(lista->prox, v);
        return lista;
    }
}

void remove_aresta(p_grafo g, int u, int v) {
    //remove uma aresta do grafo
    g->adjacencia[u] = remove_da_lista(g->adjacencia[u], v);
    g->adjacencia[v] = remove_da_lista(g->adjacencia[v], u);
}

void busca_em_profundidade(p_grafo g, int *pai, int p, int v) {
    //função recursiva que percorre o grafo buscando o "Pai" de cada vértice
    p_no t = NULL;
    pai[v] = p;
    for(t = g->adjacencia[v]; t != NULL; t = t->prox)
        if (pai[t->v] == -1)
            busca_em_profundidade(g, pai, v, t->v);
}

int * encontra_caminhos(p_grafo g, int s) {
    //cria um vetor pai que perimite determinar os caminhos possíveis que ligam os vértices de um grafo conexo.
    //o vetor pai basicamente funciona como uma árvore cuja raíz é "s".
    int i, * pai = calloc(1, g->n * sizeof(int));
    for (i = 0; i < g->n; i++)
        pai[i] = -1;
    busca_em_profundidade(g, pai, s, s);
    return pai;
}

int calc_dist(int v, int *pai) {
    /*
    Dado o vetor "pai", determinado pela função "encontra_caminhos" com u := s,
    calcula a distância entre o vértice v e a raíz da árvore (vetor pai),
    que no caso é próprio vértice u (dado na entrada "D [C] [P] X", onde [C] = u e usado como parâmetro de "encontra_caminhos").
    Assim, é capaz de calcular a distância entre um vértice u e um vértice v.
    */
    int cont = 0;
    for (;pai[v] != v; v = pai[v])
        cont++;
    return cont;
}

void ordena_aux (int *aux, int n) {
    //ordenar o vetor do menor para o maior - utiliza-se bubblesort.
    int x;
    for (int i = 0; i < n - 1; i++)
        for (int j = n - 1; j > i; j--)
            if (aux[j] < aux[j-1]) {
                x = aux[j-1];
                aux[j-1] = aux[j];
                aux[j] = x;
            }
}

void insere_C (p_grafo g, int v) {
    //insere o vértice C no caso em que d > x.
    int C = g->n, *aux = malloc(g->n * sizeof(int)), i = 1;
    //aux é uma lista com os vértices que serão ligados a C.
    for (int i = 0; i < g->n; i++)
    //inicializa todos os elementos de aux como 1000.
    //valor arbitrariamente alto para não prejudicar a ordenação.
        aux[i] = 1000; 

    g->n++;
    g->adjacencia = realloc(g->adjacencia, g->n * sizeof(p_no)); //realloca a memória para o vetor de adjacencia pelo aumento de g->n.
    g->adjacencia[g->n - 1] = NULL;
    aux[0] = v;
    p_no t = NULL;
    printf("%d ADICIONADO E CONECTADO A", C);

    for (t = g->adjacencia[v]; t != NULL; t = t->prox) {
        /*itera a lista de adjacencia de v (P), fazendo com que C 
        seja ligado a v e todos os seus vértices adjacentes */
        aux[i] = t->v, i++;
        insere_aresta(g, t->v, C);
    }
    ordena_aux(aux, g->n - 1); //ordena em ordem crescente os valores de aux
    for (int i = 0; i < g->n - 1; i++) {
        //printa os valores de aux já ordenados
        if(aux[i] != 1000) 
            printf(" %d", aux[i]);
        else
            break;
    }
    free(aux);
    printf("\n");
}

void libera_lista(p_no lista) {
    //libera a memória ocupada por uma lista ligada.
    if (lista != NULL) {
        libera_lista(lista->prox);
        free(lista);
    }
}

void destroi_grafo(p_grafo g) {
    //libera a memória ocupada pelo grafo.
    for (int i = 0; i < g->n; i++)
        libera_lista(g->adjacencia[i]);
    free(g->adjacencia);
    free(g);
}