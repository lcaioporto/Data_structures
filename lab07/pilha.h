#ifndef _pilha_h
#define _pilha_h

typedef struct no_pilha *p_no;
typedef struct pilha *p_pilha;

struct no_pilha {
    char str[51]; //conteúdo do nó
    p_no prox; //ponteiro para o próximo nó
};

struct pilha {
    p_no topo; //ponteiro que indica o topo (cabeça) da pilha
    p_no base; //ponteiro que indica a base (cauda) da pilha
    int tam; //inteiro que representa a quantidade de nós da pilha
};

//OBS.: A pilha será pensada como uma lista ligada apontando de baixo (base) para cima, até o topo.

void cria_pilha(p_pilha pilha);
//define as condições iniciais da pilha

void adiciona_no (p_pilha pilha);
//adiciona um novo nó a pilha

void empilhar(p_pilha pilha, char txt);
//adiciona um novo caracter no topo da pilha.
//caso necessario, aumenta o tamanho da pilha usando "adiciona no".

p_no encontra_ant_topo (p_pilha pilha, p_no atual);

void desempilha_topo (p_pilha pilha);
//remove o topo da pilha.

void aux_desempilhar (p_pilha pilha, int n, int x, int para_em, int *ja_deletou);
/*
função recursiva que remove caracteres do topo da pilha.
caso necessário, remove o nó inteiro do topo 
(caso em que deseja-se remover x maior do que o número de caracteres ocupados no topo)
*/

void desempilhar_geral(p_pilha pilha, int x);
//realiza toda a ação de desempilhar um número x de caracteres.

void destroi_pilha (p_pilha pilha, p_no no_atual);
//libera o espaço ocupado por uma pilha.

void printa_pilha (p_pilha pilha, p_no atual);
//printa os dados da pilha

#endif