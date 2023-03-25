#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
#include "fila.h"
#define MAX 500

void printar_info (p_fila f, p_pilha p) {
    //função que printa toda a informação da pilha e da fila adequadamente.
    printf("FILA ATUAL: ");
    printa_fila(f);
    printf("\n");
    printf("PILHA ATUAL: ");
    printa_pilha(p,p->base);
    printf("\n");
    printf("####");
}

int main () {
    int stop = 0, x = 0, j = 0, ja_printou = 0;
    char input[MAX], acao[5], num[5];
    input[0] = '\0';
    acao[0] = '\0';
    num[0] = '\0';
    p_fila F = malloc(sizeof (struct s_fila)); //ponteiro para a fila
    p_pilha P = malloc(sizeof (struct pilha)); //ponteiro para a pilha
    cria_fila(F);
    cria_pilha(P);
    do {
        for (int i = 0; i < MAX; i++)
            input[i] = '\000';
        fgets(input, MAX, stdin); //input recebe a string de entrada.
        input[strcspn(input, "\n")] = 0; //retira o "\n" da entrada

        if (strcmp(input, "EXIT") == 0) {
            //verifica se o loop deve ser encerrado.
            stop = 1;
            break;
        }

        for (int k = 0; k < 5; k++)
            num[k] = '\000';
            //variável auxiliar para guardar a string do numero associado aos comandos "EXEC num" e "DEL num"
        
        for (int i = 0; i < 4; i++) {
            acao[i] = input[i];
            acao[i + 1] = '\000';
        }
            //acao será usada para verificar se a entrada é um comando de EXEC ou DEL.

        if (strcmp(acao, "EXEC") == 0) { //operação EXEC
            j = 0;
            while (input[4+j] != '\000') {
                num[j] = input[4+j];
                j++;
            }
            x = atoi(num); //converte a string de num para um inteiro x.
            for (int i = 0; i < x; i++) {
                empilhar(P, F->v[F->ini]); //coloca na pilha o que deve sair da fila (o início)
                desenfileira(F); //retira da fila o que foi pra pilha
            }
        }
        else if (strcmp(acao, "DEL ") == 0) { //operação DEL
            j = 0;
            while (input[4+j] != '\000') {
                num[j] = input[4+j];
                j++;
            }
            x = atoi(num); //converte a string de num para um inteiro x.
            desempilhar_geral(P,x); //deleta x caracteres da pilha
        }
        else
            enfileira(F, input); //enfilera a nova string lida pelo input
        
        if (ja_printou)
            printf("\n");
        
        printar_info(F,P); //printa na tela as condições atuais da fila a da pilha
        ja_printou = 1;
    } while (stop != 1);
    free(F->v); //libera o espaço ocupado por uma fila.
    destroi_pilha(P, P->base); //libera o espaço ocupado por uma pilha.
    free(P);
    return 0;
}