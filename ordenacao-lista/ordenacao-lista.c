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

void merge_sort_split(tp_nodo *ref, tp_nodo ** left, tp_nodo ** right);
tp_nodo * merge_sort_merge(tp_nodo * left, tp_nodo * right);
tp_nodo * merge_sort(tp_nodo * nodo);
void sort_by_merge(tp_lista *lista);

void view_product(tp_nodo * node) {
    printf("\nNome: %s", node->info.nome);
    printf("Codigo: %d", node->info.codigo);
    printf("\nPreco: %.2f\n", node->info.preco);
}

tp_produto instance_product(){
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

void insert_node(tp_lista *lista){
	tp_nodo * novo_node = (tp_nodo*) malloc(sizeof(tp_nodo));

    novo_node->info = instance_product();
    novo_node->prev = lista->last;
    novo_node->next = NULL;
    lista->n_itens++;

    // lista sem valor
    if(lista->first == NULL) lista->first = novo_node;
    if(lista->last != NULL) lista->last->next = novo_node;
    lista->last = novo_node;
}

void remove_node(tp_lista *lista){
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
            if(tmp->info.codigo == codigo) break;
            tmp = tmp->next;
        }

        if(tmp != NULL) {
            if(tmp->prev == NULL){
                lista->first = tmp->next;
                if(tmp->next != NULL) tmp->next->prev = NULL;
            }
            
            if(tmp->next == NULL){
                lista->last = tmp->prev;
                if(tmp->prev != NULL) tmp->prev->next = NULL;
            } 
            
            if(tmp->prev != NULL && tmp->next != NULL) {
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
            }
            lista->n_itens--;
            
            printf("Produto removido com sucesso.");
        } else {
            printf("Nenhum produto encontrado.");
        }

        free(tmp);
    }
}

void view_list(tp_lista * lista) {
    printf("\n\n---- Listando Produtos ----\n");

    if(lista->first == NULL){
        printf("Não há produtos na lista.");
    } else {
        tp_nodo * temp = lista->first;
        while(temp != NULL) {
            view_product(temp);
            temp = temp->next;
        }

        printf("\nTotal de Produtos: %d", lista->n_itens);
    }
}

void clearlist(tp_lista *lista){
    tp_nodo *proximo_node;
    tp_nodo *tmp = lista->first;

    while(tmp != NULL){
        proximo_node = tmp->next;
        free(tmp);
        tmp = proximo_node;
    }
}

void switch_nodos(tp_nodo *left, tp_nodo *right, tp_lista *lista){
    // Define a sequencia de reaponteramento de nodos vizinhos
    int nextto_switch = 0;
    if(right->prev == left) nextto_switch = 1;
    
    if(left->prev == NULL)  lista->first = right;
    if(right->next == NULL) lista->last = left;

    tp_nodo * left_of_left = left->prev;
    tp_nodo * right_of_left = left->next;
    left->prev = NULL;
    left->next = NULL;
    
    tp_nodo * left_of_right = right->prev;
    tp_nodo * right_of_right = right->next;
    right->prev = NULL;
    right->next = NULL;


    if(left_of_left != NULL) left_of_left->next = right;
    if(right_of_left != NULL) right_of_left->prev = right;
    right->prev = left_of_left;
    right->next = right_of_left;

    if(left_of_right != NULL) left_of_right->next = left;
    if(right_of_right != NULL) right_of_right->prev = left;
    left->prev = left_of_right;
    left->next = right_of_right;
    
    if(nextto_switch == 1){
        left->prev = right;
        right->next = left;
    }
}

void merge_sort_split(tp_nodo *ref, tp_nodo ** left, tp_nodo ** right){
    tp_nodo *normal = ref;
    tp_nodo *jump_nodo = ref->next;

    while (jump_nodo != NULL) {  
        jump_nodo = jump_nodo->next;
        if (jump_nodo != NULL) {
            normal = normal->next;
            jump_nodo = jump_nodo->next;
        }
    }
    
    *left = ref;
    *right = normal->next;

    normal->next = NULL;
}

tp_nodo * merge_sort_merge(tp_nodo * left, tp_nodo * right){
    if (left == NULL) {
        return right;
    }
    else if (right == NULL) {
        return left;
    }

    if (left->info.codigo <= right->info.codigo){
        left->next = merge_sort_merge(left->next, right);
        left->next->prev = left;
        left->prev = NULL;
        
        return left;
    } else {
        right->next = merge_sort_merge(left, right->next);
        right->next->prev = right;
        right->prev = NULL;

        return right;
    }
}

tp_nodo * merge_sort(tp_nodo * nodo){
    if (nodo == NULL || nodo->next == NULL) {
        return nodo;
    }
    
    tp_nodo *left;
    tp_nodo *right;
    
    merge_sort_split(nodo, &left, &right);

    left = merge_sort(left);
    right = merge_sort(right);

    return merge_sort_merge(left, right);
}

tp_lista* initialize(){
    tp_lista * lista = (tp_lista*)malloc(sizeof(tp_lista)); 

    lista->first = NULL;
    lista->last = NULL;
    lista->n_itens = 0;

    return lista;
}

void sort_by_insertion(tp_lista *lista) {
    if(lista->n_itens > 1){
        // Controla comparacoes a esquerda
        tp_nodo * testing;

        // Controla nodo em evidencia
        tp_nodo * evidence = lista->first->next;
        // E nessa loucura de dizer que não te quero
        // Vou negando as aparências
        // Disfarçando as evidências
        // Mas pra que viver fingindo
        // Se eu não posso enganar meu coração

        while(evidence != NULL) {
            testing = evidence->prev;
            
            while(testing != NULL){
                if(evidence->info.codigo < testing->info.codigo) 
                    switch_nodos(testing, evidence, lista);
                
                testing = testing->prev;
            }
            evidence = evidence->next;
        }
    }
}

void sort_by_selection(tp_lista *lista) {
    if(lista->n_itens > 1){
        // Controla menor elemento
        tp_nodo * testing;
        
        // Menor Nodo
        tp_nodo * minorvalue;

        // Controla nodo em evidencia
        tp_nodo * evidence = lista->first;

        while(evidence != NULL) {
            testing = evidence->next;
            minorvalue = NULL;
            
            while(testing != NULL){
                if(testing->info.codigo < evidence->info.codigo){
                    if(minorvalue == NULL || testing->info.codigo < minorvalue->info.codigo)
                        minorvalue = testing;
                }
                testing = testing->next;
            }

            if(minorvalue != NULL) {
                switch_nodos(evidence, minorvalue, lista);
                evidence = minorvalue;
            }
            
            evidence = evidence->next;
        }
    }
}

void sort_by_merge(tp_lista *lista){
    if(lista->n_itens > 1){
        tp_nodo * first = merge_sort(lista->first); 
        tp_nodo * last;
        for(last = first; last->next != NULL; last = last->next){}
        
        lista->first = first;
        lista->last = last;
    }
}

int main(){
    int opcao = 0;
    tp_lista *lista = initialize(); 

    do {
	 	printf("---- MENU ----\n\n");
	 	printf("1 - Inserir um produto na lista\n");
	 	printf("2 - Excluir um produto da lista\n");
	 	printf("3 - Listar todos produto da lista\n");
	 	printf("4 - Ordenar via Insertion Sort\n");
	 	printf("5 - Ordenar via Selection Sort\n");
	 	printf("6 - Ordenar via Merge Sort\n");
	 	printf("0 - Sair\n");

        printf("Opcao: ");
	 	scanf("%d", &opcao);

	 	switch(opcao) {
            case 1:
                insert_node(lista);
                break;

            case 2:
                remove_node(lista);
                break;

            case 3:
                view_list(lista);
                break;

            case 4:
                sort_by_insertion(lista);
                break;

            case 5:
                sort_by_selection(lista);
                break;

            case 6:
                sort_by_merge(lista);
                break;

            case 0:
                clearlist(lista);
                printf("\nVoce optou por sair desse programa MA-RA-VILHOOWZO!\n");
                break;

            default :
                printf("\nERRRROOOOO!!!");
                break;
        }

        printf("\n\n");
    } while(opcao != 0);
}
