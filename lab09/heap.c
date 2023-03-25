#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#define PAI(i) ((i-1)/2) //Pai de i
#define F_ESQ(i) (2*i+1) //Filho esquerdo de i
#define F_DIR(i) (2*i+2) //Filho direito de i

void troca(int *a, int *b) {
    //recebe "a" e "b" e troca eles.
    int t = *a;
    *a = *b;
    *b = t;
}

p_fp criar_filaprio(int tam) {
    //seta as condições iniciais para uma fila de prioridade.
    p_fp f = malloc(sizeof(FP));
    f->v = malloc(tam * sizeof(Item));
    f->n = 0;
    f->tamanho = tam;
    return f;
}

void sobe_no_heap(p_fp f, int k) {
    //recebe uma posição "k" de um elemento do vetor f->v;
    //verifica, dentro das condições de prioridade, se o processo deve subir no heap;
    //se sim, realiza essa ação mantendo a ordem da fp.
    if (k > 0 && f->v[PAI(k)].C > f->v[k].C) {
        //caso em que o pai tem menor prioridade.
        troca(&f->v[k].C, &f->v[PAI(k)].C);
        troca(&f->v[k].P, &f->v[PAI(k)].P);
        sobe_no_heap(f, PAI(k));
    }
    else if (f->v[PAI(k)].C == f->v[k].C && f->v[PAI(k)].P < f->v[k].P) {
        //caso em que o pai tem menor prioridade.
        troca(&f->v[k].P, &f->v[PAI(k)].P);
        sobe_no_heap(f, PAI(k));
    }
}

void insere_heap (p_fp f) {
    //insere, considerando a prioridade, um novo processo na fp.
    scanf("%d", &f->v[f->n].P);
    scanf("%d", &f->v[f->n].C);
    f->n++;
    sobe_no_heap(f, f->n - 1);
}


void desce_no_heap(p_fp f, int k) {
    //recebe uma posição "k" de um elemento do vetor f->v;
    //verifica, dentro das condições de prioridade, se o processo deve descer no heap;
    //se sim, realiza essa ação mantendo a ordem da fp.

    int maior_filho; //variável que irá conter a posição do filho com maior prioridade.
    if (F_ESQ(k) < f->n) {
        maior_filho = F_ESQ(k);

        if (F_DIR(k) < f->n && f->v[F_ESQ(k)].C > f->v[F_DIR(k)].C)
            maior_filho = F_DIR(k);
        else if (f->v[F_ESQ(k)].C == f->v[F_DIR(k)].C && f->v[F_ESQ(k)].P < f->v[F_DIR(k)].P)
            maior_filho = F_DIR(k);
        
        if (f->v[k].C > f->v[maior_filho].C) {
            //caso em que o pai f->v[k] tem menor prioridade que um dos filhos: deve descer no heap.
            troca(&f->v[k].C, &f->v[maior_filho].C);
            troca(&f->v[k].P, &f->v[maior_filho].P);
            desce_no_heap(f, maior_filho);
        }
        else if (f->v[k].C == f->v[maior_filho].C && f->v[maior_filho].P > f->v[k].P) {
                //caso em que o pai f->v[k] tem menor prioridade que um dos filhos: deve descer no heap.
                troca(&f->v[k].P, &f->v[maior_filho].P);
                desce_no_heap(f, maior_filho);
        }
    }
}

void muda_prioridade(p_fp f, int p, int new_c) {
    //dado um valor "p", busca o processo associado a esse valor em f->v;
    //altera o valor da prioridade desse processo para "new_c".
    int k;
    for (int i = 0; i < f->tamanho; i++) {
        if (f->v[i].P == p) {
            k = i;
            break;
        }
    }
    if (f->v[k].C > new_c) {
        f->v[k].C = new_c;
        sobe_no_heap(f, k);
    }
    else {
        f->v[k].C = new_c;
        desce_no_heap(f, k);
    }
}

void extrai_maximo(p_fp f) {
    //retira o valor com maior prioridade da fp.
    //printa o valor P do processo a ser retirado.
    printf("%d", f->v[0].P);
    troca(&f->v[0].C, &f->v[f->n - 1].C);
    troca(&f->v[0].P, &f->v[f->n - 1].P);
    f->n--;
    desce_no_heap(f, 0);
}