#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio_ext.h>

#define TAM 50

typedef struct _produto{
    int cod;
    char nome[TAM];
    float preco;
} tp_produto;

typedef struct _pilha{
    tp_produto * info;
    int topo;
} tp_pilha;

void cria(tp_pilha *p, int tamanho){
    tp_produto * var = (tp_produto*)malloc(tamanho * sizeof(tp_produto));

    p->info = var;
    p->topo = -1;
}

void pushme(tp_pilha *satisfaction){
    int codigo;
    float preco;
    char nome[TAM];
    tp_produto produtinho;

    printf("\n\nCadastro de Produto:\n");

    getchar();
    printf("Informe o nome: ");
    fgets(produtinho.nome, TAM, stdin);

    printf("Informe o codigo: ");
    scanf("%d", &codigo);
    produtinho.cod = codigo;

    printf("Informe o preco: ");
    scanf("%f", &preco);
    produtinho.preco = preco;

    satisfaction->topo++;
    *(satisfaction->info + satisfaction->topo) = produtinho;
}

tp_produto papapop(tp_pilha *engenheiros){
    tp_produto produtojogadofora = *(engenheiros->info + engenheiros->topo);
    engenheiros->topo--;

    return produtojogadofora;
}

void printfproduto(tp_produto prd) {
    printf("\nNome: %s", prd.nome);
    printf("Codigo: %d", prd.cod);
    printf("\nPreco: %.2f\n", prd.preco);
}

void destrinchar(tp_pilha * rayovac) {
    int i;

    if(rayovac->topo < 0){
        printf("\n\nNenhum produto para listar");
    } else {
        printf("\n\nListagem de Produto:");
        for(i = rayovac->topo; i >= 0; i--){
            printf("\n\n");
            printfproduto(*(rayovac->info + i));
        }
	}
}

int main(){
    int capacidadePilha = 0;
    int opcao = -1;
    tp_pilha *duracell = (tp_pilha*)malloc(sizeof(tp_pilha)); 
    tp_produto prodremovido;

    printf("Informe o tamanho da pilha: ");
    scanf("%d", &capacidadePilha);
    cria(duracell, capacidadePilha);

    while(opcao != 0){
	 	printf("\n\n---- MENU ----\n\n");
	 	printf("1 - Inserir um produto na pilha\n");
	 	printf("2 - Excluir um produto da pilha\n");
	 	printf("3 - Listar todos produto da pilha\n");
	 	printf("0 - Sair\n");

        printf("Opcao: ");
	 	scanf("%d", &opcao);

	 	switch(opcao) {
            case 1:
                if(duracell->topo < (capacidadePilha - 1))
                    pushme(duracell);
                else
                    printf("\nA lista está mais cheia que a gorda da sua mãe\n");
                break;

            case 2:
                if(duracell->topo < 0)
                    printf("A lista está vazia\n");
                else {
                    prodremovido = papapop(duracell);
                    printf("\n\nProduto Removido:");
                    printfproduto(prodremovido);
                }
                break;

            case 3:
                destrinchar(duracell);
                break;

            case 0:
                printf("\nFALO VALEU!");
                break;

            default :
                printf("\nERRRROOOOO!!!");
                break;
        }
    }

}
