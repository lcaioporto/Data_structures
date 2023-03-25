#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#define MAX 500

void cria_fila (p_fila f) {
    //define as condições iniciais da fila 
    f->ini = 0, f->fim = 0;
    f->tam_aloc = 0, f->tam_total = MAX;
    f->v[0] = '\000';
}

void enfileira(p_fila f, char x[MAX]) {
    //adiciona uma nova string a partir do final da fila
    int i = f->fim;
    int j = 0;
    while (x[j] != '\000') {
        if (i == 500)
            i = 0;
        f->v[i] = x[j]; //faz cada caracter de x virar um elemento de f->v
        i++, j++;
    }
    f->fim = (f->fim + strlen(x)) % f->tam_total;
    f->tam_aloc+= strlen(x);
}

void desenfileira(p_fila f) {
    //retira um caracter da fila (o que está no início)
    f->v[f->ini] = '\000';
    f->ini = (f->ini + 1) % f->tam_total;
    f->tam_aloc --;
}

void printa_fila (p_fila f) {
    //printa os dados da fila.
    for (int i = f->ini; i != f->fim; i= (i + 1)%f->tam_total)
        printf("%c", f->v[i]);
}