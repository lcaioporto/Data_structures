#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"
#define MAX 300

int main () {
    int N, pista;
    char operacao[20], cidade[MAX], data[9], data_ini[9], data_fim[9];
    //abaixo serão inicializadas os vetores de char
    data[8] = '\0';
    data_ini[8] = '\0';
    data_fim[8] = '\0';
    for (int i = 0; i < MAX; i++) {
        cidade[i] = '\0';
        if (i < 20)
            operacao[i] = '\0';
    }
    p_mapa M = NULL; //ponteiro para a raiz da árvore do mapa
    p_visita V = NULL; //ponteiro para a raiz da árvore da visita
    scanf("%d", &N);

    for (int z = 0; z < N; z++) {
        scanf("%s", operacao);
        if (strcmp(operacao, "insere_visita") == 0) {
            scanf("%s", cidade), scanf("%s", data), scanf("%d", &pista);
            if (ja_tem_no_mapa(M, cidade)) { //verifica se deseja-se adicionar um nó que já está no mapa
                //se já tiver no mapa, já adiciona 1 no número de visitas desse nó
                V = insere_visita_visita (V, data, cidade, pista); //insere o nó na árvore da visita
                printa_visita (0, data, cidade);
            }
            else {
                //caso em que o nó a ser adicionado é novo, e, portanto, tem que ser colocado no mapa
                M = insere_visita_map (M, cidade);
                V = insere_visita_visita (V, data, cidade, pista);
                printa_visita (1, data, cidade);
            }
        }
        if (strcmp(operacao, "exclui_visita") == 0) {
            scanf("%s", data);
            for (int i = 0; i < MAX; i++)
                cidade[i] = '\0'; //seta todos os valores da cidade como '\0'
            
            V = exlclui_visita_visita(V, data, cidade); //exclui o nó desejado da árvore da visita
            int n = diminui_n_visitas(M, cidade); //diminui o número de visitas do nó e guarda o novo número em "n".
            if (n == 0)
                M = exlclui_visita_mapa(M, cidade); //caso em que deve-se excluir o nó da árvore mapa
            printa_exclui_visita (cidade, n); //printa as informações da operacao "exclui_visita"
        }
        else if (strcmp(operacao, "relatorio_data") == 0) {
            scanf("%s", data_ini), scanf("%s", data_fim);
            printf("--VISITAS--\n");
            relatorio_data(V, data_ini, data_fim); //printa as informações dessa operacao
        }
        else if (strcmp(operacao, "relatorio_pista") == 0) {
            scanf("%s", data_ini), scanf("%s", data_fim);
            printf("--PISTAS--\n");
            relatorio_pista(V, data_ini, data_fim); //printa as informações dessa operacao
        }
    }
    destroi_mapa(M); //libera a memória ocupada pela árvore do mapa
    destroi_visita(V); //libera a memória ocupada pela árvore da visita
    return 0;
}