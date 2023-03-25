#include <stdio.h>
#include <stdlib.h>

int * le_vetor (int n) { 
    //recebe um vetor que contém as experiências das tropas; aloca-o dinamicamente e retorna-o.
    int * vetor = malloc (sizeof (int) * n);
    for (int i = 0; i < n; i++)
        scanf ("%d", &vetor[i]);
    return vetor;
}

int * find_subtropa (int * vetor, int n, int *tam_subtropa, int *guarda_i) {
    //função que, dado um vetor, encontra a maior soma sequencial possível dentro dele.
    int sum = 0, cont = 0, guarda_j = 0, maior = vetor[0], entrou = 0;
    int * subtropa; //vetor que irá conter a maior soma sequencial possível.
    for (int i = 0; i < n; i++) {
        sum = 0;
        for (int j = 0; j < n - i; j++) {
            sum += vetor[i + j];
            if (sum > maior)
                maior = sum, *guarda_i = i, guarda_j = j, entrou = 1;
        }
    }
    if (entrou == 0) //caso em que a maior soma sequencial é unicamente o primeiro elemento.
        *guarda_i = 0;
    *tam_subtropa = guarda_j + 1;
    subtropa = malloc(sizeof(int)*(*tam_subtropa));
    for (int k = *guarda_i; k <= *guarda_i + guarda_j; k++)
        subtropa[cont] = vetor[k], cont++;
    return subtropa; 
}

void printa_vetor (int * vetor, int n) { 
    //printa os valores de um vetor de números inteiros.
    for (int i = 0; i < n; i++)
        printf ("%d ", vetor[i]);
}

int * normalize_vetor (int * vetor, int n) {
    //função que normaliza um vetor pela média; retorna o vetor normalizado.
    int media = 0, s = 0;
    for (int i = 0; i < n; i++)
        s += vetor[i]; //soma dos valores de "vetor"
    media = s/n;
    for (int i = 0; i < n; i++)
        vetor[i] = vetor[i] - media;
    return vetor;
}

int main () {
    int Q, N, tam_sub = 0, guarda_tam = 0, save_i = 0, cont = 0;
    int * v, * sub, *possivel_elite, *normalized, * sub_normalized, * elite, * save_elite;
    scanf ("%d", &Q);
    
    for (int i = 0; i < Q; ++i) {
        scanf ("%d", &N);
        v = le_vetor(N); //vetor de todas as tropas recebidas para determinado N;
        sub = find_subtropa(v, N, &tam_sub, &save_i); //vetor das subtropas fortes de v.
        printf("Sub-tropa Forte %d: ", i + 1), printa_vetor(sub, tam_sub), printf("\n"); //printa o vetor da subtropa forte de v.
        
        if (i == 0) //aloca memória para o vetor "possivel_elite" primeiramente.
            possivel_elite = malloc(sizeof(int)*tam_sub); //vetor de todas as subtropas fortes; utilizado para encontrar a subtropa de elite.
        
        else  //realoca a memória do vetor "possivel_elite" para as próximas sequências (i > 0).
            possivel_elite = realloc(possivel_elite, sizeof(int)*(tam_sub + guarda_tam));
        
        for (int p = guarda_tam; p < guarda_tam + tam_sub; p++)
            possivel_elite[p] = sub[p - guarda_tam]; //copia as informações da subtropa forte para o vetor "possivel_elite".
        
        guarda_tam += tam_sub;
        free(v), free(sub);
    }
    save_elite = malloc(sizeof(int) * guarda_tam);
    for (int q = 0; q < guarda_tam; q++)
        save_elite[q] = possivel_elite[q]; //save_elite guarda os valores de possivel_elite, pois este será modificado ao ser passado como referência para "normalize_vetor".
    
    normalized = normalize_vetor(possivel_elite, guarda_tam); //normalized é o vetor "possivel_elite" normalizado pela média.
    tam_sub = 0, save_i = 0;
    sub_normalized = find_subtropa(normalized, guarda_tam, &tam_sub, &save_i); //subtropa dentro de "normalized".
    
    elite = malloc(sizeof(int) * tam_sub);
    for (int k = save_i; k < tam_sub + save_i; k++)
        elite[cont] = save_elite[k], cont++; //o vetor da subtropa de elite recebe seus valores a partir de "save_elite".
    
    printf("Sub-tropa Elite: "), printa_vetor(elite, tam_sub); //printa o vetor da subtropa de elite.
    free(save_elite), free(normalized), free(sub_normalized), free(elite);
    return 0;
}