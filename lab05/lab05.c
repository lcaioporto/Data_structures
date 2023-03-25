#include <stdio.h>
#include <stdlib.h>
#include "ultron.h"

int main () {
    int n, l_alocado, c_alocado;
    //l_alocado: número de linhas sendo efetivamente ocupadas;
    //c_alocado: número de colunas sendo efetivamente ocupadas.
    char In_Out[4], L_C[2];
    pont M = malloc(sizeof(struct matriz));
    le_matriz(M); //lê os dados de uma matriz (linha, coluna e elementos).
    l_alocado = M->l;
    c_alocado = M->c;
    scanf("%d", &n); //número de operações a serem feitas.

    for (int i = 0; i < n; i++) {
        scanf("%s", In_Out), scanf("%s", L_C);
        double_or_half(M, l_alocado, c_alocado); //verifica se o tamanho da matriz deve ser dobrado ou reduzido pela metade; se for necessário, realiza a operação.
        if (In_Out[0] == 'I') { //caso operações do tipo "In".
            if (L_C[0] == 'L') {
                In_L(M, l_alocado, c_alocado); //operação que adiciona uma linha.
                l_alocado++;
                print_matriz(M, l_alocado, c_alocado);
            }
            else {
                In_C(M, l_alocado, c_alocado); //operação que adiciona uma coluna.
                c_alocado++;
                print_matriz(M, l_alocado, c_alocado);
            }
        }
        else { //caso operações do tipo "Out".
            if (L_C[0] == 'L') {
                Out_L(M, l_alocado, c_alocado); //operação que retira uma linha.
                l_alocado--;
                print_matriz(M, l_alocado, c_alocado);
            }
            else {
                Out_C(M, l_alocado, c_alocado); //operação que retira uma coluna.
                c_alocado--;
                print_matriz(M, l_alocado, c_alocado);
            }
        }
    }
    free_struct(M, l_alocado);
    printf("COMBINACAO MATRICIAL FINALIZADA!");
    return 0;
}