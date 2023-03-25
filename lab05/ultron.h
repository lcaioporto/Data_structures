typedef struct matriz *pont; //permite "chamar" a struct a partir de um ponteiro.

struct matriz{
    int **mat; //matriz com os elementos.
    int l; //número de linhas da matriz.
    int c; //número de colunas da matriz.
};

void cria_matriz (pont k); //aloca memória para uma matriz

pont cria_aux (pont m); //cria uma variável aux usada nas funções para realocar memória da matriz

void le_matriz(pont k); //recebe as linhas/colunas iniciais e os elementos da matriz;

void copiar_matriz(pont mat1, pont mat2, int l_aloc, int c_aloc); //copia mat1 em mat2.

void double_line (pont k, int l_aloc, int c_aloc); //dobra o número de linhas de uma matriz.

void half_line (pont k, int l_aloc, int c_aloc); //divide pela metade o número de linhas de uma matriz.

void double_column (pont k, int l_aloc, int c_aloc); //dobra o número de colunas de uma matriz.

void half_column (pont k, int l_aloc, int c_aloc); //divide pela metade o número de colunas de uma matriz.

void double_or_half(pont k, int l_aloc, int c_aloc); //verifica se o tamanho da matriz deve ser modificado; caso precise, usa as funções "double_half_line" e/ou "double_half_column"

void In_L (pont k, int l_aloc, int c_aloc); //inserção de linha no final da matriz;

void Out_L (pont k, int l_aloc, int c_aloc); //remoção de uma linha x da matriz e reorganização da posição dos demais elementos;

void In_C (pont k, int l_aloc, int c_aloc); //inserção de coluna na matriz, mantendo as linhas ordenadas;

void Out_C (pont k, int l_aloc, int c_aloc); //remoção de uma coluna y da matriz e reorganização da posição dos demais elementos;

void print_matriz(pont k, int l_aloc, int c_aloc); //printa os valores de uma matriz.

void free_struct (pont k, int l); //da free no espaço alocado por uma struct matriz toda.