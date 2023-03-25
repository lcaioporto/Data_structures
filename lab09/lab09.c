#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int main () {
    p_fp F = NULL;
    int T, N, K, p, c;
    char op[1]; //variável que guarda a operação a ser realizada: 'R' ou 'M'.
    scanf ("%d", &T);
    F = criar_filaprio(T); //seta as condições iniciais da fp com base no tamanho T.
    for (int i = 0; i < F->tamanho; i++)
        insere_heap(F); //recebe os dados P e Q de cada processo, e já insere na fp considerando a prioridade.
    
    scanf("%d", &N); //número de operações a serem feitas
    for (int i = 0; i < N; i++) {
        scanf("%s", op);
        if (op[0] == 'R') {
            scanf("%d", &K);
            printf("PROCESSOS REMOVIDOS: ");
            for (int z = 0; z < K; z++) {
                extrai_maximo(F); //retira da fp o processo com maior prioridade (f->v[0]), mantendo a organização; printa P do processo a ser retirado.
                if (z != K-1)
                    printf(" ");
            }
            printf("\n");
        }
        else { //operação 'M'.
            scanf("%d", &p), scanf("%d", &c); //"p": número do processo a ser alterado; "c": novo valor da prioridade deste processo.
            muda_prioridade(F, p, c); //altera a prioridade de um determinado processo (p) para c.
        }
    }
    printf("FINALIZADO!");
    free(F->v), free(F); //libera a memória ocupada pela fp.
    return 0;
}