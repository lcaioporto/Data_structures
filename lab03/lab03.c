#include <stdio.h>
#include "represa.h"

int main () {
    int T; //quantidade de represas a serem analisadas.
    scanf ("%d", &T);
    for(int i = 0; i < T; i++) {
        Represa r;
        r = le_dados();
        print_dados(r); //printa os dados formatados da represa r.
        if (i != T - 1)
            printf("\n");
    }
    return 0;
}