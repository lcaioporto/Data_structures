#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#define MAX 3083

int main () {
    p_no v[MAX]; //vetor de ponteiros - vetor do hash.
    for (int i = 0; i < MAX; i++)
        v[i] = NULL; //inicializa o vetor
    int N = 0, id = 0, tempo = 0;
    char op[2], nome[100];
    scanf ("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%s", op); //recebe a operação a ser realizada
        op[1] = '\0';
        if (op[0] == 'I') {
            for (int k = 0; k < 100; k++)
                nome[k] = '\0'; //seta toda a string como '\0' (inicializa a string)
            scanf("%d", &id), scanf("%s", nome), scanf("%d", &tempo);
            inserir(v, id, nome, tempo);
        }
        else if (op[0] == 'R') {
            scanf("%d", &id);
            remover(v, id);
        }
        else if (op[0] == 'C') {
            scanf("%d", &id);
            consultar (op, v, id);
        }
        else if (op[0] == 'T') {
            scanf("%d", &id);
            consultar(op, v, id);
        }
    }
    printf("FINALIZADO!");
    libera_hash(v);
    return 0;
}