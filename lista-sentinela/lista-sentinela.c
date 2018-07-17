#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio_ext.h>

#define TAM 20

typedef struct _produto{
    int codigo;
    char nome[TAM];
    float preco;
} tp_produto;

typedef struct _nodo{
    tp_produto info;
    struct _nodo *next;
    struct _nodo *prev;
} tp_nodo;

typedef struct _lista{
    int n_itens;
    tp_nodo *first;
    tp_nodo *last;
} tp_lista;


void printfproduto(tp_nodo * node) {
    printf("\nNome: %s", node->info.nome);
    printf("Codigo: %d", node->info.codigo);
    printf("\nPreco: %.2f\n", node->info.preco);
}

tp_produto cria_produto(){
    int codigo;
    float preco;
    char nome[TAM];
    tp_produto produtovisk;

    printf("\n\n---- Cadastro de Produto ----\n");

    getchar();
    printf("Informe o nome: ");
    fgets(produtovisk.nome, TAM, stdin);
    strtok("\n", produtovisk.nome);

    printf("Informe o codigo: ");
    scanf("%d", &codigo);
    produtovisk.codigo = codigo;

    printf("Informe o preco: ");
    scanf("%f", &preco);
    produtovisk.preco = preco;

    return produtovisk;
}

void adicionar_nodo(tp_lista *lista){
	tp_nodo * novo_node = (tp_nodo*) malloc(sizeof(tp_nodo));

    novo_node->info = cria_produto();
    novo_node->prev = lista->last;
    novo_node->next = NULL;
    lista->n_itens++;

    // lista sem valor
    if(lista->first == NULL) lista->first = novo_node;
    if(lista->last != NULL) lista->last->next = novo_node;
    lista->last = novo_node;
}

void remover_nodo(tp_lista *lista){
    if(lista->first == NULL){
        printf("\n\nNão há produtos na lista.");
    } else {
        int codigo;
        int produto_removido = 0;

        printf("\n\n---- Excluir Produto ----\n");
        printf("Informe o codigo do produto a ser removido: ");
        scanf("%d", &codigo);

        tp_nodo * tmp = lista->first;
        while(tmp != NULL){
            if(tmp->info.codigo == codigo){
                if(tmp->prev == NULL){
                    // Removento o primeiro elemento
                    lista->first = tmp->next;
                    if(tmp->next != NULL) tmp->next->prev = NULL;
                }
                
                if(tmp->next == NULL){
                    // Removendo ultimo elemento
                    lista->last = tmp->prev;
                    if(tmp->prev != NULL) tmp->prev->next = NULL;
                } 
                
                if(tmp->prev != NULL && tmp->next != NULL) {
                    // Removendo elemento do meio
                    tmp->prev->next = tmp->next;
                    tmp->next->prev = tmp->prev;
                }
                produto_removido = 1;
                free(tmp);
                break;
            }
            tmp = tmp->next;
        }
        
        if(produto_removido == 0) {
            printf("Nenhum produto encontrado.");
        } else {
            printf("Produto removido com sucesso.");
            lista->n_itens--;
        }
    }
}

void destrinchar(tp_lista * lista) {
    printf("\n\n---- Listando Produtos ----\n");

    if(lista->first == NULL){
        printf("Não há produtos na lista.");
    } else {
        tp_nodo * temp = lista->first;
        while(temp != NULL) {
            printfproduto(temp);
            temp = temp->next;
        }

        printf("\nTotal de Produtos: %d", lista->n_itens);
    }
}

void liberausmininu(tp_lista *lista){
    tp_nodo *proximo_node;
    tp_nodo *tmp = lista->first;

    while(tmp != NULL){
        proximo_node = tmp->next;
        free(tmp);
        tmp = proximo_node;
    }
}

int main(){
    int opcao = 0;
    tp_lista *lista = (tp_lista*)malloc(sizeof(tp_lista)); 
    lista->first = NULL;
    lista->last = NULL;
    lista->n_itens = 0;

    do {
	 	printf("---- MENU ----\n\n");
	 	printf("1 - Inserir um produto na lista\n");
	 	printf("2 - Excluir um produto da lista\n");
	 	printf("3 - Listar todos produto da lista\n");
	 	printf("0 - Sair\n");

        printf("Opcao: ");
	 	scanf("%d", &opcao);

	 	switch(opcao) {
            case 1:
                adicionar_nodo(lista);
                break;

            case 2:
                remover_nodo(lista);
                break;

            case 3:
                destrinchar(lista);
                break;

            case 0:
                liberausmininu(lista);
                printf("\nFALO VALEU!\n");
                break;

            default :
                printf("\nERRRROOOOO!!!");
                break;
        }

        printf("\n\n");
    } while(opcao != 0);
}
