#include <stdio.h>
int T, n, op, B, M, P, k;
int u[1000], cB[1000], V_aux[1000];

void printa_vetor (int v[]) { /* função que printa o vetor u - usada após cada operação */
  for (int s = 0; s < T; s++)
    printf("%d ", v[s]);
  printf("\n");
}

void copia_vetor (int v1[], int v2[]) { /* função que copia um vetor em outro */
  for (int i = 0; i < T; i++)
    v1[i] = v2[i];
}

void op1 () { /* caso da operação 1 - Conjunto Banner */
  scanf("%d", &B);
  for (int s = 0; s < B; s++)
    scanf("%d", &cB[s]); /* cB[] é um vetor com os números do Conjunto Banner */

  for (int i = 0; i < T; i++){
    k = 0; /* variável auxiliar */
    for (int s = 0; s < B; s++) {
      if (u[i] == cB[s]) {
        k = 1;
        break;
      }
    }
    if (k == 0)
      u[i] = 0;
  }
  printa_vetor(u);
}

void op2 () { /* caso da operação 2 - Multiplicação de Mobius */
  scanf("%d", &M);      
  for (int s = 1; s <= T; s += 2)
    u[s] *= M;
  printa_vetor(u);
}

void op3 () { /* caso operação 3 - Movimento cíclico */
  scanf("%d", &P);
        
  for (int s = 0; s < P; s++) {
    copia_vetor(V_aux, u); /* V_aux[] é um vetor auxiliar para a realização de op3() e op4() */
    for (int i = 0; i <= T; i++) {
      if (i == 0)
        u[0] = V_aux[T - 1];
      else
        u[i] = V_aux[i - 1];  
    }
  }
  printa_vetor(u);
}

void op4 () { /* caso operação 4 - Inversão de vetor */
  copia_vetor(V_aux, u);
  for (int s = 0; s < T; s++)
    u[s] = V_aux[T - s - 1];
  printa_vetor(u);
}

int main() {
  scanf("%d", &T);
  
  for (int s = 0; s < T; s++)
    scanf("%d", &u[s]);
  
  scanf("%d", &n);
  
  for (int s = 0; s < n; s++){ /* loop para receber os dados de todas as operações */
    scanf("%d", &op); /* op é uma variável que recebe o valor da operação */
    if (op == 1) 
      op1();
    else if (op == 2)
      op2();
    else if (op == 3)
      op3();
    else
      op4();
  }
  return 0;
}