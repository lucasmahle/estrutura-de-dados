#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio_ext.h>

#define TAMANHO_TABELA 8


typedef struct _nodo{
    int data;
    struct _nodo *next;
} tp_nodo;


int hash_calc(int key){
    return key % TAMANHO_TABELA;
}

tp_nodo * create_node(){
	tp_nodo * novo_node = (tp_nodo*) malloc(sizeof(tp_nodo));

    int data = 0;

    printf("\n\n---- Adicionando Item ----\n");

    printf("Informe o item: ");
    scanf("%d", &data);

    novo_node->data = data;
    novo_node->next = NULL;

    return novo_node;
}

void insert_node(tp_nodo **tabela){
    tp_nodo * table_value;
    tp_nodo * novo_nodo;

    int hash;

    novo_nodo = create_node();

    hash = hash_calc(novo_nodo->data);
    table_value = tabela[hash];

    novo_nodo->next = table_value;

    tabela[hash] = novo_nodo;

    printf("\n-- Hash: %d", hash);
}

void hash_search(tp_nodo **tabela){
    int data, hash, i;
    tp_nodo * aux, * nodo_busca;

    printf("\n\n---- Busca Na Tabela ----\n");

    printf("Diga-me quem procuras: ");
    scanf("%d", &data);

    hash = hash_calc(data);

    aux = tabela[hash];
    nodo_busca = NULL;
    i = 1;
    while(aux != NULL){
        if(aux->data == data) {
            nodo_busca = aux;
            break;
        }
        i++;  
        aux = aux->next;
    }

    if(nodo_busca == NULL){
        printf("\nNao foi encontrado o valor informado.");
    } else {
        printf("\nHash do item: %d", hash);
        printf("\nO item era o %dº da lista", i);
    }
}

void exibir_tabela(tp_nodo **tabela){
    printf("\n\n---- Exibindo Tabela ----\n");

    for(int i = 0; i < TAMANHO_TABELA; i++){
        if(tabela[i] != NULL){
            tp_nodo * aux = tabela[i];
            int first_value = 0;

            printf("\nHash: %d Valores: (", (i + 1));

            while(aux != NULL){
                if(first_value == 0) first_value = 1;
                else printf(", ");
                
                printf("%d", aux->data);
                aux = aux->next;
            }
            printf(")");
        } else {
            printf("\nHash: %d Valores: NULL", (i + 1));
        }
    }
}

int main(){
    int opcao = 0;
    tp_nodo * tabela[TAMANHO_TABELA] = {NULL}; 

    do {
	 	printf("---- MENU ----\n\n");
	 	printf("1 - Inserir um item na tabela\n");
	 	printf("2 - Buscar item na tabela\n");
	 	printf("3 - Exibir tabela\n");
	 	printf("0 - Sair\n");

        printf("Opcao: ");
	 	scanf("%d", &opcao);

	 	switch(opcao) {
            case 1:
                insert_node(tabela);
                break;

            case 2:
                hash_search(tabela);
                break;

            case 3:
                exibir_tabela(tabela);
                break;
            
            case 0:
                printf("\nVoce optou por sair desse programa MA-RA-VILHOOWZO!\n");
                break;

            default :
                printf("\nERRRROOOOO!!!");
                break;
        }

        printf("\n\n");
    } while(opcao != 0);
}
