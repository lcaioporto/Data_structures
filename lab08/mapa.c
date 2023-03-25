#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"
#define MAX 300

int compara_data (char data1[8], char data2[8]) {
    //Compara as datas 1 e 2. Funciona de modo análogo a função strcmp. 
    //Se data1 > data2 retorna 1; se data1 == data2, retorna 0; se data1 < data2, retorna -1.
    char ano1[5], ano2[5], mes1[3], mes2[3], dia1[3], dia2[3];
    ano1[4] = '\0', ano2[4] = '\0', mes1[2] = '\0', mes2[2] = '\0', dia1[2] = '\0', dia2[2] = '\0';
    for (int i = 0; i < 4; i++)
        ano1[i] = data1[i], ano2[i] = data2[i];
    if (strcmp(ano1, ano2) > 0)
        return 1;
    else if (strcmp(ano1, ano2) < 0)
        return -1;
    else {
        for (int i = 4; i < 6; i++)
            mes1[i-4] = data1[i], mes2[i-4] = data2[i];
        if (strcmp(mes1, mes2) > 0)
            return 1;
        else if (strcmp(mes1, mes2) < 0)
            return -1;
        else {
            for (int i = 6; i < 8; i++)
                dia1[i-6] = data1[i], dia2[i-6] = data2[i];
            if (strcmp(dia1, dia2) > 0)
                return 1;
            else if (strcmp(dia1, dia2) < 0)
                return -1;
            else
                return 0;
        }
    }
    return 0;
}

int ja_tem_no_mapa (p_mapa raiz, char nome_cidade[MAX]) {
    //Dada uma cidade, verifica se já há um nó na árvore mapa com essa cidade.
    //Se há, retorna 1; se não, retorna 0.
    while (raiz != NULL && strcmp(nome_cidade, raiz->cidade) != 0)
        if (strcmp(nome_cidade, raiz->cidade) < 0)
            raiz = raiz->esq;
        else
            raiz = raiz->dir;
    if (raiz == NULL)
        return 0;
    else {
        raiz->n_visitas++;
        return 1;
    }
}

p_mapa insere_visita_map (p_mapa raiz, char nome_cidade[MAX]) {
    //insere um nó na árvore mapa, deixando, ainda assim, a estrutura ordenada.
    //Retorna a nova raiz da árvore.
    p_mapa new;
    if (raiz == NULL) {
        new = malloc(sizeof(struct mapa));
        new->esq = new->dir = NULL;
        strcpy(new->cidade, nome_cidade);
        new->n_visitas = 1;
        return new;
    }
    if (strcmp(nome_cidade, raiz->cidade) < 0)
        raiz->esq = insere_visita_map(raiz->esq, nome_cidade);
    else
        raiz->dir = insere_visita_map(raiz->dir, nome_cidade);
    return raiz;
}

p_visita insere_visita_visita (p_visita raiz, char data_inserir[9], char cidade_inserir[MAX], int pista_inserir) {
    //insere um nó na árvore visita, deixando, ainda assim, a estrutura ordenada.
    //Retorna a nova raiz da árvore.
    p_visita new;
    if (raiz == NULL) {
        new = malloc(sizeof(struct visita));
        new->esq = new->dir = NULL;
        strcpy(new->data, data_inserir);
        strcpy(new->cidade, cidade_inserir);
        new->pista = pista_inserir;
        return new;
    }
    if (compara_data(data_inserir, raiz->data) < 0)
        raiz->esq = insere_visita_visita(raiz->esq, data_inserir, cidade_inserir, pista_inserir);
    else
        raiz->dir = insere_visita_visita(raiz->dir, data_inserir, cidade_inserir, pista_inserir);
    return raiz;
}

void printa_visita (int inseriu_mapa, char data_inserir[9], char cidade_inserir[MAX]) {
    //printa as informações necessárias da operacao insere_visita
    //verifica, pela variável "inseriu_mapa", se a cidade é nova ou não.
    if (inseriu_mapa) {
        printf("ARVORE: MAPA\n");
        printf("CIDADE: ");
        printf("%s", cidade_inserir);
        printf("\nINSERIDO COM SUCESSO!\n");
        printf("####\n");
    }
    printf("ARVORE: VISITA\n");
    printf("DATA: ");
    printf("%s", data_inserir);
    printf("\nCIDADE: ");
    printf("%s", cidade_inserir);
    printf("\nINSERIDO COM SUCESSO!\n");
    printf("####\n");
}

int diminui_n_visitas (p_mapa raiz, char cidade[MAX]) {
    //Dada uma cidade, busca na árvore mapa o nó que contém essa cidade e diminui em 1 unidade o número de visitas dela.
    //Retorna o novo número de visitas.
    while (raiz != NULL && strcmp(cidade, raiz->cidade) != 0)
        if (strcmp(cidade, raiz->cidade) < 0)
            raiz = raiz->esq;
        else
            raiz = raiz->dir;
    if (raiz == NULL)
        return -1;
    else {
        raiz->n_visitas--;
        return raiz->n_visitas;
    }
}

void remover_sucessor_mapa (p_mapa raiz) {
    //Remove o sucessor de uma dada raiz dentro da árvore de mapa.
    //copia o valor desse sucessor a posição que vai ser excluída
    p_mapa min =  malloc(sizeof(struct mapa));
    min = raiz->dir;
    p_mapa pai = malloc(sizeof(struct mapa));
    pai = raiz;
    while (min->esq != NULL) {
        pai = min;
        min = min->esq;
    }
    if (pai->esq == min)
        pai->esq = min->dir;
    else
        pai->dir = min->dir;
    raiz->n_visitas = min->n_visitas;
    strcpy(raiz->cidade, min->cidade);
}

void remover_sucessor_visita (p_visita raiz) {
    //Remove o sucessor de uma dada raiz dentro da árvore de visita.
    //copia o valor desse sucessor a posição que vai ser excluída
    p_visita min =  malloc(sizeof(struct visita));
    min = raiz->dir;
    p_visita pai = malloc(sizeof(struct visita));
    pai = raiz;
    while (min->esq != NULL) {
        pai = min;
        min = min->esq;
    }
    if (pai->esq == min)
        pai->esq = min->dir;
    else
        pai->dir = min->dir;
    raiz->pista = min->pista;
    strcpy(raiz->data, min->data);
    strcpy(raiz->cidade, min->cidade);
    free(min);
}

p_visita exlclui_visita_visita (p_visita raiz, char data[9], char cidade[MAX]) {
    //Dada uma data, exclui o nó que tem essa data na árvore de visita. 
    //Mesmo com a exclusão, mantém a ordem da estrutra.
    //A variável "cidade" serve para guardar o nome da cidade que foi removida.
    if (raiz == NULL)
        return NULL;
    if (compara_data(data, raiz->data) < 0)
        raiz->esq = exlclui_visita_visita(raiz->esq, data, cidade);
    else if (compara_data(data, raiz->data) > 0)
        raiz->dir = exlclui_visita_visita(raiz->dir, data, cidade);
    
    else if (compara_data(data, raiz->data) == 0) {
        strcpy(cidade, raiz->cidade);
        if (raiz->esq == NULL) {
            p_visita aux = raiz->dir;
            free(raiz);
            return aux;
        }
        else if (raiz->dir == NULL) {
            p_visita aux = raiz->esq;
            free(raiz);
            return aux;
        }
        else
            remover_sucessor_visita(raiz);
    }
    return raiz;
}

p_mapa exlclui_visita_mapa (p_mapa raiz, char nome_cidade[MAX]) {
    //Dada uma cidade, exclui o nó que tem essa cidade na árvore de visita. 
    //Mesmo com a exclusão, mantém a ordem da estrutra.
    if (raiz == NULL)
        return NULL;
    
    if (strcmp(nome_cidade, raiz->cidade) < 0)
        raiz->esq = exlclui_visita_mapa(raiz->esq, nome_cidade);
    else if (strcmp(nome_cidade, raiz->cidade) > 0)
        raiz->dir = exlclui_visita_mapa(raiz->dir, nome_cidade);
    
    else if (raiz->esq == NULL)
        return raiz->dir;
    else if (raiz->dir == NULL)
        return raiz->esq;
    else
        remover_sucessor_mapa(raiz);
    return raiz;
}

void printa_exclui_visita (char nome_cidade[MAX], int n) {
    //printa as informações necessárias da operacao exclui_visita.
    printf("CIDADE: ");
    printf("%s", nome_cidade);
    printf("\nQUANTIDADE DE VISITAS RESTANTES: ");
    printf("%d", n);
    printf("\n####\n");
}

void print_info_rel (p_visita raiz) {
    //printa as informações gerais de um relatorio - seja relatorio_data ou relatorio_pista.
    printf("DATA: ");
    printf("%s", raiz->data);
    printf("\nCIDADE: ");
    printf("%s", raiz->cidade);
    printf("\n####\n");
}

void relatorio_data (p_visita raiz, char data_ini[9], char data_fim[9]) {
    //Dado um período (data_ini;data_fim), seleciona e printa os nós que estão nesse período da mais antiga à mais nova.
    if (raiz != NULL) {
        relatorio_data(raiz->esq, data_ini, data_fim);
        if (compara_data(raiz->data, data_ini) >= 0 && compara_data(raiz->data, data_fim) <= 0)
            print_info_rel(raiz);
        relatorio_data(raiz->dir, data_ini, data_fim);    
    }
}

void relatorio_pista (p_visita raiz, char data_ini[9], char data_fim[9]) {
    /*
    Dado um período de entrada (data_ini;data_fim), todas as visitas que estão nesse período 
    e em que houve pistas sobre o Sauron são impressas da mais nova à mais antiga.
    */
    if (raiz != NULL) {
        relatorio_pista(raiz->dir, data_ini, data_fim);
        if (raiz->pista == 1 && compara_data(raiz->data, data_ini) >= 0 && compara_data(raiz->data, data_fim) <= 0)
            print_info_rel(raiz);
        relatorio_pista(raiz->esq, data_ini, data_fim);    
    }
}

void destroi_mapa (p_mapa raiz) {
    //libera a memória ocupada pela árvore do mapa
    if (raiz != NULL) {
        destroi_mapa(raiz->esq);
        destroi_mapa(raiz->dir);
        free(raiz);
    }
}

void destroi_visita (p_visita raiz) {
    //libera a memória ocupada pela árvore do visita
    if (raiz != NULL) {
        destroi_visita(raiz->esq);
        destroi_visita(raiz->dir);
        free(raiz);
    }
}