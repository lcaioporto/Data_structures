#ifndef _fila_h
#define _fila_h
#define MAX 500
typedef struct s_fila *p_fila;

struct s_fila {
    char v[MAX]; //vetor com a fila
    int ini; //indica onde está o início da fila (o próximo a ser chamado)
    int fim; //indica onde está o final da fila (a partir de onde será adicionado um novo elemento)
    int tam_total, tam_aloc;
};

//OBS.: A fila será pensada como um vetor circular.

void cria_fila(p_fila f);
//define as condições iniciais da fila 

void enfileira(p_fila f, char x[MAX]);
//adiciona uma nova string a partir do final da fila

void desenfileira(p_fila f);
//retira um caracter da fila (o que está no início)

void printa_fila (p_fila f);
//printa os dados da fila.

#endif