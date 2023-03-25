#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#define MAX 3083

int hash (int id) {
    //cálculo da função de hash h(x) utilizando o método da divisão.
    return id % MAX;
}

void inserir(p_no v[MAX], int id, char nome[100], int tempo) {
    //Dados as informações, insere um ponteiro para um nó (um processo) no vetor v;
    int h = hash(id);
    for (int i = h; i < MAX; i++) {
        //busca, a partir de h, uma posição vazia ou com processo removido (dummy) para inserir.
        if (v[i] == NULL) { //posição vazia;
            p_no new = malloc(sizeof(struct processo));
            new->id = id, strcpy(new->nome, nome), new->tempo = tempo;
            v[i] = new;
            break;
        }
        else if (v[i]->id == -1) { //posição de um processo removido (dummy).
            p_no new = malloc(sizeof(struct processo));
            new->id = id, strcpy(new->nome, nome), new->tempo = tempo;
            v[i] = new;
            break;
        }
    }
    printf("PROCESSO %d INSERIDO!\n", id);
}

void remover (p_no v[MAX], int id) {
    //dado um id, remove o processo com este determinado id.
    int h = hash(id);
    for (int i = h; i < MAX; i++) {
        if (v[i] != NULL && v[i]->id == id) {
            v[i]->id = -1; //altera o id do processo para ele passar a indicar um dummy.
            break;
        }
    }
    printf("PROCESSO %d REMOVIDO!\n", id);
}

void consultar (char op[2], p_no v[MAX], int id) {
    //utilizada para as operações 'C' e 'T' - consultar nome e tempo, respectivamente.
    //dado um id, realiza uma busca no vetor de hash.
    //printa o que for necessário, dependendo da operação.
    int h = hash(id);
    for (int i = h; i < MAX; i++) {
        if (v[i] != NULL && v[i]->id == id) { //verifica se v[i] é o processo procurado;
            if (op[0] == 'C')
                printf("PROCESSO %d: %s\n", id, v[i]->nome); //caso consultar nome;
            else
                printf("TEMPO DO PROCESSO %d: %d DIAS.\n", id, v[i]->tempo); //caso consultar tempo;
            break;
        }
        else if (op[0] == 'C' && v[i] == NULL) { //caso pra operação de "consultar nome" em que não foi achado o id correspondente.
            printf("PROCESSO %d NAO ENCONTRADO!\n", id);
            break;
        }
    }
}

void libera_hash (p_no v[MAX]) {
    //libera a memória ocupada pelo vetor de hash.
    for (int i = 0; i < MAX; i++) {
        if (v[i] != NULL)
            free(v[i]);
    }
}