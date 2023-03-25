#include <stdio.h>
#include "represa.h"

Represa le_dados() { //le todos os dados de uma represa guradando em um tipo Represa (rep); retorna rep;
    Represa rep;
    scanf("%s", rep.name);
    scanf("%f", &rep.M);
    scanf("%d", &rep.N);
    for(int i = 0; i < rep.N; i++)
        scanf("%d", &rep.v[i]);
    return rep;
}

int cap_max(Represa rep){ //função que avalia a capacidade máx. da represa; 
    float limit = (rep.M) * 0.9;
    for(int i = 0; i < rep.N; i++){
        if (rep.v[i] >= limit)
            return 1; //retorna 1 se algum dos valores for maior que 90% da cap. máx.;
    }
    return 0; //retorna 0 se nenhum dos valores for maior que 90% da cap. máx.;
}

int calc_media(Represa rep) { //calcula e retorna a média dos valores de rep.v;
    int s = 0;
    for (int i = 0; i < rep.N; i++)
        s += rep.v[i];
    return s/(rep.N);
}

int len_name (Represa rep){ //calcula o tamanho n do vetor name de uma represa; retorna n;
    int n = 0;
    for (int i = 0; i < 100; i++){
        if (rep.name[i] == 0)
            break;
        n++;
    }
    return n;
}

void process_name (char name[100], int n){ //realiza ações para adequar o nome da represa; printa o nome;
    char new[100];
    if (name[0] == 'r' && name[1] == 'e'){
        for (int i = 0; i < n - 11; i++)
            new[i] = name[11 + i]; //nova variável "new" que não contém a parte "represa_de_"
        n -= 11;
    }
    else
        for (int i = 0; i < n; i++)
            new[i] = name[i]; //nova variável "new" igual a "name"
    new[n] = '\0';
    
    if (new[n - 2] < 'A' && new[n - 1] < 'A'){ //verifica se há 2 números no final do nome;
        new[n - 2] = '\0';
        new[n - 1] = '\0';
        n -= 2;
    }
    else if (new[n - 1] < 'A'){ //verifica se há algum número no final do nome;
        new[n - 1] = '\0';
        n--;
    }
    
    for (int i = 0; i < n; i++){
        if (new[i] == '_')
            new[i] = ' '; //troca "_" por " ";
        else if (new[i] >= 'A' && new[i] <= 'Z')
            new[i] += 32; //troca letras maiúsculas por minúsculas;
    }
    printf("NOME: %s\n", new);
}

void print_dados(Represa rep) { //função que printa todos os dados de uma represa
    process_name(rep.name, len_name(rep));
    printf("QTD NIVEIS: %d\n", rep.N);
    rep.media = calc_media(rep);
    printf("MEDIA: %d\n", rep.media);
    if (cap_max(rep) == 1)
        printf("CAPACIDADE ACIMA DE 90%% DA MAXIMA!\n");
    printf("#####");
}