typedef struct no *p_no; //p_no é um ponteiro para um nó da lista ligada.

struct no { //struct para uma lista ligada que irá compor a lista de adjacencia
    int v; //valor armazenado no nó da lista ligada
    p_no prox; //ponteiro para o próximo nó
};

typedef struct grafo *p_grafo;

struct grafo { //struct para o grafo
    p_no *adjacencia; //lista de adjacencia - vetor de ponteiros que identificam uma lista ligada.
    int n; //número de vértices do grafo
};

p_grafo criar_grafo(int n);
//seta as condições iniciais para inicializar o grafo;
//aloca memória e define o tamanho do grafo (g->n = n).

p_no insere_na_lista(p_no lista, int v);
//aloca memória para um novo nó e o insere na lista ligada.

void insere_aresta(p_grafo g, int u, int v);
//dados os vértices u,v e um grafo g insere uma aresta na lista de adjacencia de g;
//utiliza a função "insere_na_lista".

p_no remove_da_lista(p_no lista, int v);
//remove um determinado nó de uma lista ligada.

void remove_aresta(p_grafo g, int u, int v);
//dados os vértices u,v remove a aresta entre eles.
//utiliza a função "remove_da_lista" para remover um nó de uma determinada lista ligada da lista de adjacencia.

void busca_em_profundidade(p_grafo g, int *pai, int p, int v);
//função recursiva que percorre o grafo buscando o "Pai" de cada vértice.

int * encontra_caminhos(p_grafo g, int s);
//cria e retorna um vetor pai que determina os caminhos possíveis que ligam os vértices de um grafo conexo.
//o vetor pai basicamente funciona como uma árvore cuja raíz é "s".
//utiliza a função "busca_em_profundidade".

int calc_dist(int v, int *pai);
/*
Dado o vetor "pai", determinado pela função "encontra_caminhos" com u := s,
calcula a distância entre o vértice v e a raíz da árvore (vetor pai),
que no caso é próprio vértice u (dado na entrada "D [C] [P] X", onde [C] = u e usado como parâmetro de "encontra_caminhos").
Assim, é capaz de calcular a distância entre um vértice u e um vértice v, resolvendo a operação "D".
*/

void ordena_aux (int *aux, int n);
//ordena um dado vetor de inteiros aux de tamanho n do menor para o maior;
//utiliza-se bubblesort.

void insere_C (p_grafo g, int v);
/*
No caso em que d > x para a operação "D", insere um novo vértice C no grafo;
C terá ligação com v e todos os vértices adjacentes a v;
Utiliza um vetor auxilixar aux para armazenar os vértices adjacentes a v;
Utiliza "ordena_aux" para ordenar o vetor aux e printa o que for necesario, na ordem crescente;
Realloca a memória da lista de adjacencia, pois o número de vértices do grafo aumenta em uma unidade (g->n++).
*/

void libera_lista(p_no lista);
//libera a memória ocupada por uma lista ligada.

void destroi_grafo(p_grafo g);
//libera a memória ocupada pelo grafo g;
//utiliza a função "libera_lista" para desalocar a memória ocupada pela lista de adjacencia.