#include <stdio.h>
#include <stdlib.h>
#include "ultron.h"

void cria_matriz(pont m) {
    //aloca espaço para uma matriz.
    m->mat = malloc((m->l) * sizeof(int *)); //aloca memória para cada linha da matriz.
    for (int i = 0; i < m->l; i++)
        m->mat[i] = malloc(m->c * sizeof(int)); //aloca memória para cada elemento da matriz.
}

pont cria_aux (pont m) {
    //cria e retorna uma matriz auxiliar que será usada em outras funções.
    pont aux = malloc(sizeof(struct matriz));
    aux->l = m->l;
    aux->c = m->c;
    cria_matriz(aux);
    return aux;
}

void free_struct (pont m, int l) {
    //da free em uma struct matriz toda
    for (int i = 0; i < l; i++)
        free(m->mat[i]);
    free(m->mat);
    free(m);
}

void le_matriz(pont m) {
    //lê as propriedades "l", "c" da matriz e os elementos de uma matriz; retorna a struct matriz.
    scanf("%d", &m->l), scanf("%d", &m->c); //lê o número de linhas e colunas da matriz.
    cria_matriz(m);
    for (int i = 0; i < m->l; i++)
        for (int j = 0; j < m->c; j++)
            scanf("%d", &m->mat[i][j]); //recebe cada elemento da matriz.
}

void copiar_matriz(pont m1, pont m2, int l_aloc, int c_aloc) { 
    //copia m1 em m2, com tamanho dependendo de "l_aloc" e "c_aloc".
    for (int i = 0; i < l_aloc; i++)
        for (int j = 0; j < c_aloc; j++)
            m2->mat[i][j] = m1->mat[i][j];
}

void double_line(pont m, int l_aloc, int c_aloc) {
    //dobra o espaço alocado para as linhas.
    pont aux = cria_aux(m);
    copiar_matriz(m, aux, l_aloc, c_aloc); //copia m em aux
    //aux guarda as informações de m->mat para elas não serem perdidas no realloc

    m->l = 2 * m->l; //atualiza o número de linhas da matriz.
    m->mat = realloc(m->mat, m->l * sizeof(int *)); //duplica o espaço alocado para as linhas da matriz.
    for (int i = aux->l; i < m->l; i++)
        m->mat[i] = malloc(m->c * sizeof(int)); //aloca memória para as colunas das linhas realocadas
    
    copiar_matriz(aux, m, l_aloc, c_aloc);
    free_struct(aux, aux->l);
}

void half_line (pont m, int l_aloc, int c_aloc) {
    //diminui pela metade o espaço alocado para linhas da matriz.
    pont aux = cria_aux(m);
    copiar_matriz(m, aux, l_aloc, c_aloc); //copia m em aux
    //aux guarda as informações de m->mat para elas não serem perdidas no realloc

    m->l =  (m->l)/2; //atualiza o número de linhas da matriz.
    m->mat = realloc(m->mat, m->l * sizeof(int *)); //divide pela metade o espaço alocado para as linhas da matriz.
    for (int i = aux->l; i < m->l; i++)
        m->mat[i] = malloc(m->c * sizeof(int)); //aloca memória para cada elemento após realloc das linhas.
    
    copiar_matriz(aux, m, l_aloc, c_aloc);
    free_struct(aux, aux->l);
}

void double_column(pont m, int l_aloc, int c_aloc) {
    //dobra o espaço alocado para as colunas.
    pont aux = cria_aux(m);
    copiar_matriz(m, aux, l_aloc, c_aloc); //copia m em aux
    //aux guarda as informações de m->mat para elas não serem perdidas no realloc

    m->c = 2 * m->c; //atualiza o número de colunas da matriz.
    for (int i = 0; i < l_aloc; i++)
        m->mat[i] = realloc(m->mat[i], m->c * sizeof(int)); //duplica o espaço alocado para as colunas da matriz.
    
    copiar_matriz(aux, m, l_aloc, c_aloc);
    free_struct(aux, aux->l);
}

void half_column (pont m, int l_aloc, int c_aloc) {
    //diminui pela metade o espaço alocado para colunas da matriz.
    pont aux = cria_aux(m);
    copiar_matriz(m, aux, l_aloc, c_aloc);
    //aux guarda as informações de m->mat para elas não serem perdidas no realloc

    m->c = (m->c)/2; //atualiza o número de colunas da matriz.
    for (int i = 0; i < l_aloc; i++)
        m->mat[i] = realloc(m->mat[i], m->c * sizeof(int)); //divide pela metade o espaço alocado para as colunas.
    
    copiar_matriz(aux, m, l_aloc, c_aloc);
    free_struct(aux, aux->l);
}

void double_or_half(pont m, int l_aloc, int c_aloc) {
    //verifica se é necessario dobrar ou dividir ao meio o espaço alocado para uma matriz.
    //se for necessario, realiza as ações usando outras funções.

    if (l_aloc == m->l)//caso em que todas as linhas da matriz estão alocadas.
        double_line(m, l_aloc, c_aloc); //dobra o número de linhas alocadas
    else if (l_aloc <= (m->l)/4) //caso em que o número de linhas alocadas é 1/4 ou menos do total
        half_line(m, l_aloc, c_aloc); //divide pela metade o número de linhas alocadas
    
    if (c_aloc == m->c)//caso em que todas as colunas da matriz estão alocadas.
        double_column(m, l_aloc, c_aloc); //dobra o número de colunas da matriz.
    else if (c_aloc <= (m->c)/4) //caso em que 1/4 ou menos das colunas da matriz estão alocadas.
        half_column(m, l_aloc, c_aloc); //divide pela metade o número de colunas alocadas
}

void In_L (pont m, int l_aloc, int c_aloc) {
    //insere uma linha no final da matriz
    for(int i = 0; i < c_aloc; i++)
        scanf("%d", &(m->mat[l_aloc][i]));
}

void In_C(pont m, int l_aloc, int c_aloc) {
    //insere uma coluna na matrix mantendo as linhas ordenadas.
    int valor, entrou;
    for (int i = 0; i < l_aloc; i++) {
        entrou = 0;
        scanf("%d", &valor);
        for (int j = 0; j < c_aloc; j++) {
            if (m->mat[i][j] >= valor) {
                for (int k = c_aloc - 1; k >= j; k--)
                    m->mat[i][k + 1] = m->mat[i][k]; //realoca certos valores um "passo" para o lado, para "abrir espaço" para inserir "valor".
                m->mat[i][j] = valor;
                entrou = 1; //variável de controle
                break;
            }
        }
        if (entrou == 0)
            m->mat[i][c_aloc] = valor; //caso em que "valor" é maior do que todos os outros elementos da linha
    }
}

void Out_L (pont m, int l_aloc, int c_aloc) {
    //remove a linha da posição x.
    int x;
    scanf("%d", &x); //posição da linha que será removida
    for (int i = x; i < l_aloc - 1; i++)
        for(int j = 0; j < c_aloc; j++)
            m->mat[i][j] = m->mat[i+1][j]; //copia cada elemento a elemento da linha a frente para a linha anterior
}

void Out_C (pont m, int l_aloc, int c_aloc) {
    //remove a coluna da posição y.
    int y;
    scanf("%d", &y);
    for (int i = 0; i < l_aloc; i++)
        for (int j = y; j < c_aloc - 1; j++)
            m->mat[i][j] = m->mat[i][j+1]; //reorganiza a posição dos demais elementos
}

void print_matriz (pont m, int l_aloc, int c_aloc) { 
    //printa os valores de uma matriz.
    for (int i = 0; i < l_aloc; i++){
        for (int j = 0; j < c_aloc; j++)
            printf("%d ", m->mat[i][j]);
        printf("\n");
    }
    printf("###\n");
} 