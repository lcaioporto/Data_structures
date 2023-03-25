#include <stdio.h>
#include <string.h>
#define M 100
int N, O, A[M][M], B[M][M];

void copia_matriz(int a[][M], int b[][M]) { //realiza a ação de copiar a matriz "a" em "b"
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            b[i][j] = a[i][j];
    }
}

void print_matriz(int a[][M]) { //realiza a ação de printar uma matriz "a"
    printf("\n");
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}

void cria_A_B() { //função que cria inicialmente as matrizes A e B
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[i][j] = 0; //cria matriz NxN toda zerada//

    for (int k = 0; k < N; k += 6) {
        for (int i = 0; i < N; i++) {
            for (int j = k; j < k + 3; j++) {
                A[i][j] = 1; //adiciona 1 onde deve ser posto na mtriz//
            }
        }
    }
    copia_matriz(A, B);
}

void transpoem_op(int a[][M], int b[][M]) { //função que transpõe "a" e guarda em "b"; printa b
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++)
            b[i][j] = a[j][i];
    }
    print_matriz(b);
}

void transposta_geral() { //função que analisa os casos possíveis e coloca "transpoem_op" em prática
    char m1[10], m2[10];
    scanf("%s", m1);
    scanf("%s", m2);

    if (strcmp(m1, "A") == 0){ 
        if (strcmp(m2, "B") == 0)
            transpoem_op(A, B);
        else
            transpoem_op(A, A);
    }

    else{
        if (strcmp(m2, "A") == 0)
            transpoem_op(B, A);
        else
            transpoem_op(B, B);
    }
}

void soma_op(int a[][M], int b[][M], int c[M][M]) { //função que soma "a" e "b" guardando o resultado em c; printa c
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            if (a[i][j] == 1 && b[i][j] == 1)
                c[i][j] = 1;
            else
                c[i][j] = a[i][j] + b[i][j];
        }
    }
    print_matriz(c);
}

void soma_geral() { //função que analisa os casos e utiliza soma_op
    char m1[10], m2[10], m3[10];
    scanf("%s", m1);
    scanf("%s", m2);
    scanf("%s", m3);

    if (strcmp(m1, "A") == 0) {
        if (strcmp(m2, "A") == 0) {
            if (strcmp(m3, "A") == 0)
                soma_op(A, A, A);
            else
               soma_op(A, A, B);
        }
        else {
            if (strcmp(m2, "A") == 0) {
                if (strcmp(m3, "A") == 0)
                    soma_op(A, B, A);
                else
                    soma_op(A, B, B);
            }
        }
    }
    else{
        if (strcmp(m2, "B") == 0) {
            if (strcmp(m3, "B") == 0)
                soma_op(B, B, B);
            else
                soma_op(B, B, A);
        }
        else{
            if (strcmp(m3, "A") == 0)
                soma_op(B, A, A);
            else
                soma_op(B, A, B);
        }
    }
}

void multi_elem_op(int a[][M], int b[][M], int c[][M]) { //função que realiza "multi_elem" entre "a" e "b" resultando em c; printa c
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            c[i][j] = a[i][j] * b[i][j];
    }
    print_matriz(c);
}

void multi_elem_geral() { //função que analisa os casos e aplica "multi_elem_op"
    char m1[10], m2[10], m3[10];
    scanf("%s", m1);
    scanf("%s", m2);
    scanf("%s", m3);

    if (strcmp(m1, "A") == 0) {
        if (strcmp(m2, "A") == 0) {
            if (strcmp(m3, "A") == 0)
                multi_elem_op(A, A, A);
            else
                multi_elem_op(A, A, B);
        }
        else {
            if (strcmp(m3, "A") == 0)
                multi_elem_op(A, B, A);
            else
                multi_elem_op(A, B, B);
        }
    }
    else{
        if (strcmp(m2, "A") == 0) {
            if (strcmp(m3, "A") == 0)
                multi_elem_op(B, A, A);
            else
                multi_elem_op(B, A, B);
        }
        else{
            if (strcmp(m3, "A") == 0)
                multi_elem_op(B, B, A);
            else
                multi_elem_op(B, B, B);
        }
    }
}

void multi_mat_op(int a[][M], int b[][M], int c[][M]) { //função que realiza a multiplicação de matrizes "a" e "b", resultando em c; printa c
    int aux[M][M], s = 0;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            aux[i][j] = 0; //cria uma matrix auxiliar zerada

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++)
                s += a[i][k] * b[k][j];
            if (s > 1)
                aux[i][j] = 1;
            else
                aux[i][j] = s;
            s = 0;
        }
    }
    copia_matriz(aux, c);
    print_matriz(c);
}

void multi_mat_geral() { //função que analisa os casos e usa "multi_mat_op"
    char m1[10], m2[10], m3[10];
    scanf("%s", m1);
    scanf("%s", m2);
    scanf("%s", m3);

    if (strcmp(m1, "A") == 0) {
        if (strcmp(m2, "A") == 0) {
            if (strcmp(m3, "A") == 0)
                multi_mat_op(A, A, A);
            else
                multi_mat_op(A, A, B);
        }
        else {
            if (strcmp(m3, "A") == 0)
                multi_mat_op(A, B, A);
            else
                multi_mat_op(A, B, B);
        }
    }
    else{
        if (strcmp(m2, "A") == 0) {
            if (strcmp(m3, "A") == 0)
                multi_mat_op(B, A, A);
            else
                multi_mat_op(B, A, B);
        }
        else{
            if (strcmp(m3, "A") == 0)
                multi_mat_op(B, B, A);
            else
                multi_mat_op(B, B, B);
        }
    }
}

void bordas_op(int a[][M], int b[][M]) { //função que realiza a ação de "bordas" em "a" e salva em "b"; printa "b"
    copia_matriz(a, b);
    for (int i = 0; i < N, i++) {
        for (int j = 0; j < N, j++) {
            if (b[i+1][j-1] == 1 && b[i+1][j] == 1 && b[i+1][j+1] == 1 && b[i][j-1] == 1 && b[i][j+1] == 1 && b[i-1][j-1] == 1 && b[i-1][j] == 1 && b[i-1][j+1] == 1)
                b[i][j] = 0;
        }
    }
    printa_matriz(b)
}

void bordas_geral() { //função que analisa os casos aplicando "bordas_op"
    char m1[10], m2[10];
    scanf("%s", m1);
    scanf("%s", m2);

    if (strcmp(m1, "A") == 0){ 
        if (strcmp(m2, "B") == 0)
            transpoem_op(A, B);
        else
            transpoem_op(A, A);
    }
    else{
        if (strcmp(m2, "A") == 0)
            transpoem_op(B, A);
        else
            transpoem_op(B, B);
    }
}

int main(void) {
    char op[10];
    scanf("%d", &N);
    scanf("%d", &O);

    cria_A_B();
    for (int i = 0; i < O; i++) {
        scanf("%s", op);
        if (strcmp(op, "TRANSPOSTA") == 0)
            transposta_geral();
        else if (strcmp(op, "SOMA") == 0)
            soma_geral();
        else if (strcmp(op, "MULTI_ELEM") == 0)
            multi_elem_geral();
        else if (strcmp(op, "MULTI_MAT") == 0)
            multi_mat_geral();
        else if (strcmp(op, "BORDAS") == 0)
            bordas_geral();
    }
    return 0;
}