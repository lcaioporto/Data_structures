typedef struct {
    //struct que representa cada processo.
    int P;
    int C;
} Item;

typedef struct {
    Item *v; //vetor de Items alocado dinamicamente
    int n, tamanho; // n: qtde de elementos , tamanho: qtde alocada
} FP;

typedef FP * p_fp;

void troca(int *a, int *b);
//recebe "a" e "b" e troca eles.

p_fp criar_filaprio(int tam);
//seta as condições iniciais para uma fila de prioridade.

void sobe_no_heap(p_fp f, int k);
//recebe uma posição "k" de um elemento do vetor f->v;
//verifica, dentro das condições de prioridade, se o processo deve subir no heap;
//se sim, realiza essa ação mantendo a ordem da fp.

void insere_heap(p_fp f);
//insere, considerando a prioridade, um novo processo na fp.

void desce_no_heap(p_fp f, int k);
//recebe uma posição "k" de um elemento do vetor f->v;
//verifica, dentro das condições de prioridade, se o processo deve descer no heap;
//se sim, realiza essa ação mantendo a ordem da fp.

void muda_prioridade(p_fp fprio, int k, int valor);
//dado um valor "p", busca o processo associado a esse valor em f->v;
//altera o valor da prioridade desse processo para "new_c".

void extrai_maximo(p_fp fprio);
//retira o valor com maior prioridade da fp.
//printa o valor P do processo a ser retirado.