typedef struct game_map *map; //struct com as informações do mapa.
 
typedef struct body *corpo; //struct com os nós da lista duplamente ligada com as informações da cobra.
 
typedef struct head_tail *snake; //struct com a cabeça, a cauda e o tamanho da cobra.
 
typedef struct fruta *fruit; //struct com a posição da fruta.
 
struct game_map{
    int l; //número de linhas do mapa - comprimeno do mapa;
    int c; //número de colunas do mapa - largura do mapa;
    int **mat; //matriz que contém os valores do mapa.
};
 
struct body {
    int x, y; //posição do nó no mapa.
    corpo ant; //ponteiro para o nó anterior.
    corpo prox; //ponteiro para o próximo nó.
};
 
struct head_tail {
    int tam; //tamanho da cobra.
    corpo head; //cabeça da cobra
    corpo tail; //cauda da cobra
};
 
struct fruta {
    int x, y; //posição da fruta no mapa do jogo
};
 
void le_dados_ini (map m, corpo no, fruit f);
//lê os dados iniciais passados pelo usuário.
 
void cria_mat (map m);
//aloca memória para o mapa do jogo (mat do game_map) e seta todos os seus valores inicialmente como 0.
 
void inicial_map (map m, snake s, fruit f);
//coloca no mapa as informações recebidas a partir de "le_dados_ini" - posição inicial da cobra (1) e da fruta (-1).
 
void recebe_fruta (map m, fruit f);
//recebe a posição nova da fruta após ela ter sido comida e já atualiza o mapa com esse novo dado.
 
void cria_snake (snake s, corpo no_ini);
//define os ponteiros da cabeça e da cauda inicialmente apontando para o mesmo nó incial.
 
void aumenta_cobra(map m, snake s, fruit f);
//aumenta o tamanho da cobra após ela ter comido uma fruta.
 
int ganhou(map m, snake s);
//verifica se a cobra ocupa todo o espaço do mapa. Se sim, retorna 1; se não, retorna 0.
 
void print_map (map m);
//printa o mapa do jogo convertendo 1 para #, -1 para * e 0 para _
 
int vai_comer (map m, snake s, fruit f, char str[1]);
//verifica se na próxima movimentação da cobra ela irá comer a fruta.
 
void mov_geral (map m, snake s, corpo no);
//função auxiliar que realiza um procedimento padrão comum a todos os movimentos.
 
int w_die (map m, snake s);
int s_die (map m, snake s);
int a_die (map m, snake s);
int d_die (map m, snake s);
/*Cada função do tipo x_die, verifica se ela irá bater nela mesma com a mov na direção x.
Se for bater, retorna 1; se não, realiza a movimentação, atualiza o mapa e retorna 0.*/
 
void destroy_snake (snake s, corpo no_atual);
//libera o espaço de memória alocado para a cobra.
 
void destroy_map (map m);
//libera o espaço de memória alocado para o mapa do jogo.