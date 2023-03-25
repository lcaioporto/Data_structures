/*
Ideia para o vetor:

O vetor do hash será um vetor de ponteiros para uma struct "processo". 
A struct irá conter os dados de um processo (ID, nome_proc, tempo).

Ideia para a função hash:

Utilizar o método da divisão. Problema - escolher o tamanho do vetor (M).
A ideia foi analisar as potências de 2 que resultam em valores os mais próximos possíveis do valor
máximo de N (2000). As potências são: 2**11 = 2048 e 2**12 = 4096.
Analisando os primos entre esses números, calculei a média entre o maior e o menor primo:
(2053 + 4093)/2 = 3073.
Como 3073 não é primo, foi escolhido o número primo mais próximo dele, resultando em:
MÁX := M = 3083.

OBS.: No vetor:
    Posição vazia: NULL; 
    Posição removida: ponteiro para um processo com id = -1 (dummy).

OBS2.: Foi utilizado um vetor estático (v[MAX]) inicializado na main() como o vetor de hash.
*/
#define MAX 3083

typedef struct processo *p_no;

struct processo {
    int id;
    char nome[100];
    int tempo;
};

int hash (int id);
/*
Calcula uma função hash h(x) utilizando o método da multiplicação;
O id do processo é usado como parâmetro parâmetro - calcula-se h(id).
*/

void inserir(p_no v[MAX], int id, char nome[100], int tempo);
//inserir um processo no vetor do hash.
//imprime “PROCESSO [id do processo] INSERIDO!”.

void remover (p_no v[MAX], int id);
//remove um determinado processo do vetor
//altera o id desse processo para -1, fazendo-o virar um dummy.
//imprime “PROCESSO [id do processo] REMOVIDO!”.

void consultar (char op[2], p_no v[MAX], int id);
/*
Caso em que op[0] == 'C' (operação de consultar o nome)
    Dado um id, procura um nome associado a este id; imprime “PROCESSO [id do processo]: [nome do processo]”;
    Caso não tenha, imprime “PROCESSO [id do processo] NAO ENCONTRADO!”.

Caso em que op[0] == 'T' (operação de consultar o tempo)
    Dado um id, procura um tempo associado a este id; 
    Imprime “TEMPO DO PROCESSO [id do processo]: [valor do tempo do processo] DIAS.”.
*/

void libera_hash (p_no v[MAX]);
//libera a memória alocada pelo vetor de hash.