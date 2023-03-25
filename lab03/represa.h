typedef struct {
    char name[100]; //Nome da represa;
    float M; //Valor do nível máximo da represa;
    int N; //Valor que representa a quantidade de medidas no vetor de níveis;
    int v[1000]; //Vetor contendo as medidas de nível;
    int media; //Valor que armazena o nível médio da represa.
} Represa;

Represa le_dados(); //lê dados de uma represa, retorna um dado do tipo Represa;
int cap_max(Represa rep); //compara a capacidade máxima de uma represa com os dados recebidos;
int calc_media(Represa rep); //calcula a média aritimetica dos valores do vetor v de uma represa;
int len_name(Represa rep); //calcula o tamanho n do vetor name de uma represa; retorna n;
void process_name(char name[100], int n); //faz o pré-processamento dos nomes das represas;
void print_dados(Represa rep); //imprime na tela informações sobre uma represa;