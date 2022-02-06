#include <stdio.h>
#include <stdlib.h>

// typedef struct lista{
//     int valor;
//     struct lista *ponteiro;//aponta pra uma região da memória do tipo e
// } no;

typedef struct no{
    int value;
    struct no *proximo;
} No;
typedef struct Lista{
    No *inicio;
    int size;
} Lista;

void makeList(Lista *lista){
    lista->inicio = NULL;
    lista->size = 0;
}

void inputStart(Lista *lista, int num){
    No *new = malloc(sizeof(No));
    if(new){
        new->value = num;
        new->proximo = lista->inicio;//o proximo no aponta pro inicio da lista
        lista->inicio = new;
        lista->size++;
    }else{
        printf("Erro ao alocar memoria\n");
    }   
}

void inputEnd(Lista *lista, int num){
    No *aux, *new = malloc(sizeof(No));
    if(new){
        new->value = num;
        new->proximo = NULL;
        if(lista->inicio == NULL){
            lista->inicio = new;
        }else{
            aux = lista->inicio;
            while(aux->proximo){
                aux = aux->proximo;
            }
            aux->proximo = new;
        }
        lista->size++;
    }else{
        printf("Erro ao alocar memoria\n");
    }
}

void inputHalf(Lista *lista, int num, int ant){
    No *aux, *new = malloc(sizeof(No));

    if(new){
        new->value = num;
        if(lista->inicio == NULL){
            new->proximo = NULL;
            lista->inicio = new;
        }else{
            aux = lista->inicio;
            while(aux->value != ant && aux->proximo != NULL){
                aux = aux->proximo;
            }
            new->proximo = aux->proximo;
            aux->proximo = new;
        }
        lista->size++;
    }else{
        printf("Erro ao alocar memoria\n");
    }
}

void inserirOrdenado(Lista *lista, int num){
    No *aux, *new = malloc(sizeof(No));

    if(new){
        new->value = num;
        if(lista->inicio == NULL){
            new->proximo = NULL;
            lista->inicio = new;
        }else if(new->value < lista->inicio->value){
            new->proximo = lista->inicio;
            lista->inicio = new;
        }else{
            aux = lista->inicio;
            while(aux->proximo && new->value > aux->proximo->value){
                aux = aux->proximo;
            }
            new->proximo = aux->proximo;
            aux->proximo = new;
        }
        lista->size++;
    }else{
        printf("Erro ao alocar memoria\n");
    }
}

No* remover(Lista *lista, int num){
    No *aux, *remover = NULL;

    if(lista->inicio){
        if(lista->inicio->value == num){
            remover = lista->inicio;
            lista->inicio = remover->proximo;
            lista->size--;
        }else{
            aux = lista->inicio;
            while(aux->proximo && aux->proximo->value != num){
                aux = aux->proximo;
            }
            if(aux->proximo){
                remover = aux->proximo;
                aux->proximo = remover->proximo;
                lista->size--;
            }
        }
    }
    return remover;
}

void ordenado(Lista *lista){
    No *aux, *no = lista->inicio;
    aux = no;
    int i = 0;
    if(no){
        while(no){
            if(no->value < aux->value){
                printf("A lista nao esta ordenada\n");
                i++;
                break;
            }
            aux = no;
            no = no->proximo;
        }
        if(i == 0){
            printf("A lista esta ordenada\n");
        }
    }else{
        printf("A lista esta vazia\n");
    }
}

void menor(Lista *lista){
    No *aux, *no = NULL;
    aux = lista->inicio;
    no = aux;
    while(aux){
        if(aux->value < no->value){
            no = aux;
        }
        aux = aux->proximo;
    }
    printf("O menor termo e %d\n\n", no->value);
}

No* buscar(Lista *lista, int num){
    No *aux, *no = NULL;

    aux = lista->inicio;
    while(aux && aux->value != num){
        aux = aux->proximo;
    }
    if(aux){
        no = aux;
    }
    return no;
}

void printPosition(Lista *lista, int num){
    No *aux = lista->inicio;
    int i = 0;
    if(lista){
        while(aux && aux->value != num){
            i++;
            aux = aux->proximo;
        }
        if(i == 0){
            printf("Elemento nao encontrado\n\n");
        }else{
            printf("Elemento %d na posicao %d\n\n", num, i + 1);
        }
    }else{
        printf("Lista vazia\n\n");
    }
}

void print(Lista *lista){
    No *start = lista->inicio;
    printf("Lista tamanho %d: \n", lista->size);
    while(start != NULL){
        printf("%d ", start->value);
        start = start->proximo;
    }
    printf("\n\n");
}

int main(){
    int opcao, valor, anterior;
    Lista *lista;
    No *removido;
    makeList(&lista);
    do{
        printf("0 - sair\n1 - inserir no inicio\n2 - inserir no final\n3 - inserir no meio\n4 - inserir ordenado\n5 - excluir\n6 - buscar\n7 - menor\n8 - print position\n9 - ordenado\n10 - imprimir\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                printf("Digite o numero: ");
                scanf("%d", &valor);
                inputStart(&lista, valor);
                break;
            case 2:
               printf("Digite o numero: ");
                scanf("%d", &valor);
                inputEnd(&lista, valor);
                break;
            case 3:
                printf("Digite o numero e o valor de referencia: ");
                scanf("%d %d", &valor, &anterior);
                inputHalf(&lista, valor, anterior);            
                break;
            case 4:
                printf("Digite o numero: ");
                scanf("%d", &valor);
                inserirOrdenado(&lista, valor);
                break;
            case 5:
                printf("Digite o numero para ser removido: ");
                scanf("%d", &valor);
                removido = remover(&lista, valor);
                if(removido){
                    printf("Elemento removido: %d\n", removido->value);
                }
                break;
            case 6:
                printf("Digite o numero buscado: ");
                scanf("%d", &valor);
                removido = buscar(&lista, valor);
                if(removido){
                    printf("Valor %d encontrado\n", removido->value);
                }else{
                    printf("valor nao encontrado\n");
                }
                break;
            case 7:
                menor(&lista);
                break;
            case 8:
                printf("Digite o numero: ");
                scanf("%d", &valor);
                printPosition(&lista, valor);
                break;
            case 9:
                ordenado(&lista);
                break;
            case 10:
                print(&lista);
                break;
            default:
                if(opcao != 0){
                    printf("Opcao invalida\n");
                }
        }
    }while(opcao != 0);
}