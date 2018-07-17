#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio_ext.h>

#define TAM 100

typedef struct _produto {
    int cod;
    char nome[TAM];
    float preco;
} tp_produto;

typedef struct nodo {
    tp_produto produto;
    struct nodo *prox;
} tp_nodo;

void liberausmininu(tp_nodo *lista){
    tp_nodo *proximo_node;
    tp_nodo *tmp = lista;

    while(tmp != NULL){
        proximo_node = tmp->prox;
        free(tmp);
        tmp = proximo_node;
    }
}

tp_nodo* adicionar_nodo(tp_nodo *lista){
    int codigo;
    float preco;
    char nome[TAM];
    tp_produto produtovisk;

	tp_nodo * novo_node = (tp_nodo*) malloc(sizeof(tp_nodo));

    printf("\n\n---- Cadastro de Produto ----\n");

    getchar();
    printf("Informe o nome: ");
    fgets(produtovisk.nome, TAM, stdin);
    strtok("\n", produtovisk.nome);

    printf("Informe o codigo: ");
    scanf("%d", &codigo);
    produtovisk.cod = codigo;

    printf("Informe o preco: ");
    scanf("%f", &preco);
    produtovisk.preco = preco;

    novo_node->prox = lista;
    novo_node->produto = produtovisk;

    return novo_node;
}

void printfproduto(tp_nodo * lista) {
    printf("\nNome: %s", lista->produto.nome);
    printf("Codigo: %d", lista->produto.cod);
    printf("\nPreco: %.2f\n", lista->produto.preco);
}

void destrinchar(tp_nodo * lista) {
    printf("\n\n---- Listando Produtos ----\n");

    if(lista == NULL){
        printf("Não há produtos na lista.");
    } else {
        tp_nodo * temp = lista;
        while(temp != NULL) {
            printfproduto(temp);
            temp = temp->prox;
        }
    }
}

tp_nodo* remover_nodo(tp_nodo *lista){
    tp_nodo *retorno = lista;
    if(lista == NULL){
        printf("\n\nNão há produtos na lista.");
    } else {
        int codigo;
        int produto_removido = 0;

        printf("\n\n---- Excluir Produto ----\n");
        printf("Informe o codigo do produto a ser removido: ");
        scanf("%d", &codigo);

        tp_nodo * tmp = lista;
        tp_nodo * anterior = NULL;
        while(tmp != NULL){
            if(tmp->produto.cod == codigo){
                if(anterior == NULL)
                    retorno = tmp->prox;
                else
                    anterior->prox = tmp->prox;
                produto_removido = 1;
                free(tmp);
                break;
            }
            anterior = tmp; 
            tmp = tmp->prox;
        }
        
        if(produto_removido == 0)
            printf("Nenhum produto encontrado.");
        else
            printf("Produto removido com sucesso.");
    }

    return retorno;
}

int main(){
    int opcao = 0;
    tp_nodo *genesis = (tp_nodo*)malloc(sizeof(tp_nodo)); // Nodo inicial
    genesis = NULL;

    do {
	 	printf("---- MENU ----\n\n");
	 	printf("1 - Inserir um produto na pilha\n");
	 	printf("2 - Excluir um produto da pilha\n");
	 	printf("3 - Listar todos produto da pilha\n");
	 	printf("0 - Sair\n");

        printf("Opcao: ");
	 	scanf("%d", &opcao);

	 	switch(opcao) {
            case 1:
                genesis = adicionar_nodo(genesis);
                break;

            case 2:
                genesis = remover_nodo(genesis);
                break;

            case 3:
                destrinchar(genesis);
                break;

            case 0:
                liberausmininu(genesis);
                printf("\nFALO VALEU!\n");
                break;

            default :
                printf("\nERRRROOOOO!!!");
                break;
        }

        printf("\n\n");
    } while(opcao != 0);
}
