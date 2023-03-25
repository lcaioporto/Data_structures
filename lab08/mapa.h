#define MAX 300
typedef struct mapa *p_mapa;
typedef struct visita *p_visita;

struct mapa {
    char cidade[MAX]; //nome da cidade
    int n_visitas; //número de visitas a essa cidade
    p_mapa esq, dir; //ponteiro pro nó da esquerda e da direita
};

struct visita {
    char data[9]; //data da visita
    char cidade[MAX]; //nome da cidade
    int pista; //indica se encontrou uma pista neste lugar ou não: se sim, vale 1, se não, vale 0.
    p_visita esq, dir; //ponteiro pro nó da esquerda e da direita
};

int compara_data (char data1[8], char data2[8]);
//Compara as datas 1 e 2. Funciona de modo análogo a função strcmp. 
//Se data1 > data2 retorna 1; se data1 == data2, retorna 0; se data1 < data2, retorna -1.

int ja_tem_no_mapa (p_mapa raiz, char nome_cidade[MAX]);
//Dada uma cidade, verifica se já há um nó na árvore mapa com essa cidade.
//Se já tiver no mapa, soma 1 na quantidade de visitas desse nó.
//Se há, retorna 1; se não, retorna 0.

p_mapa insere_visita_map (p_mapa raiz, char nome_cidade[MAX]);
//Isere um nó na árvore mapa, deixando, ainda assim, a estrutura ordenada.
//Retorna a nova raiz da árvore.

p_visita insere_visita_visita (p_visita raiz, char data_inserir[9], char cidade_inserir[MAX], int pista_inserir);
//Insere um nó na árvore visita, deixando, ainda assim, a estrutura ordenada.
//Retorna a nova raiz da árvore.

void printa_visita (int inseriu_mapa, char data_inserir[9], char cidade_inserir[MAX]);
//printa as informações necessárias da operacao insere_visita

int diminui_n_visitas (p_mapa raiz, char cidade[MAX]);
//Dada uma cidade, busca na árvore mapa o nó que contém essa cidade e diminui em 1 unidade o número de visitas dela.
//Retorna o novo número de visitas.

void remover_sucessor_visita (p_visita raiz);
//Remove o sucessor de uma dada raiz dentro da árvore de visita.
//copia o valor desse sucessor a posição que vai ser excluída

void remover_sucessor_mapa (p_mapa raiz);
//Remove o sucessor de uma dada raiz dentro da árvore mapa.
//copia o valor desse sucessor a posição que vai ser excluída

p_visita exlclui_visita_visita (p_visita raiz, char data[9], char cidade[MAX]);
//Dada uma data, exclui o nó que tem essa data na árvore de visita. 
//Mesmo com a exclusão, mantém a ordem da estrutra.
//A variável "cidade" serve para guardar o nome da cidade que foi removida.

p_mapa exlclui_visita_mapa (p_mapa raiz, char nome_cidade[MAX]);
//Dada uma cidade, exclui o nó que tem essa cidade na árvore de visita. 
//Mesmo com a exclusão, mantém a ordem da estrutra.

void printa_exclui_visita (char nome_cidade[MAX], int n);
//printa as informações necessárias da operacao exclui_visita.

void print_info_rel (p_visita raiz);
//printa as informações gerais de um relatorio - seja relatorio_data ou relatorio_pista.

void relatorio_data (p_visita raiz, char data_ini[9], char data_fim[9]);
//Dado um período (data_ini;data_fim), seleciona e printa os nós que estão nesse período da mais antiga à mais nova. 

void relatorio_pista (p_visita raiz, char data_ini[9], char data_fim[9]);
/*
Dado um período de entrada (data_ini;data_fim), todas as visitas que estão nesse período 
e em que houve pistas sobre o Sauron são impressas da mais nova à mais antiga.
*/

void destroi_mapa (p_mapa raiz);
//libera a memória ocupada pela árvore do mapa

void destroi_visita (p_visita raiz);
//libera a memória ocupada pela árvore da visita