#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

int main () {
    int qntd_P, qntd_C, n_arestas, n_operacoes, u, v, x;
    /*Para as operações "D" e "R", considere [C] = u e [P] = v*/
    int * pai = NULL;
    char operacao[2];
    operacao[0] = '\n', operacao[1] = '\n'; //inicializa o char
    scanf ("%d", &qntd_P), scanf ("%d", &qntd_C);
    int N = qntd_P + qntd_C; //quantidade de vértices do grafo.
    p_grafo g = criar_grafo(N);
    scanf("%d", &n_arestas);
    for (int i = 0; i < n_arestas; i++) {
        //recebe e insere na lista de adj os pares de vértices (u,v) que descrevem uma aresta
        scanf("%d", &u), scanf("%d", &v);
        insere_aresta(g, u, v);
    }
    printf("GRAFO AMZ CONSTRUIDO!\n");

    scanf("%d", &n_operacoes);
    for (int i = 0; i < n_operacoes; i++) {
        scanf("%s", operacao);
        operacao[1] = '\n';
        
        if (operacao[0] == 'D') {
            //operação para calcular a distância entre dois vértices.
            scanf("%d", &u), scanf("%d", &v), scanf("%d", &x);
            pai = encontra_caminhos(g, u); //encontra caminhos pensando o grafo como uma árvore com raiz "u"
            int d = calc_dist(v, pai); //calcula a menor distancia entre u e v.
            printf("DISTANCIA %d -> %d = %d\n", u, v, d);
            free(pai);
            if (d > x)
                insere_C (g, v);
        }
        
        else if (operacao[0] ==  'R') {
            //operação para remover uma aresta
            scanf("%d", &u), scanf("%d", &v);
            remove_aresta (g, u, v);
            printf("ARESTA %d -> %d REMOVIDO\n", u, v);
        }
    }
    destroi_grafo(g); //libera a memória ocupada pelo grafo.
    return 0;
}