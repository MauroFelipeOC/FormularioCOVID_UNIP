#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

//typedef int bool;
typedef long long int TIPOCHAVE;

typedef struct 
{
    char nome[255];
    long long int cpf;
    int telefone;
    char endereco[50];
    int numero;
    char bairro[50];
    char cidade[50];
    char estado[50];
    char cep[10];
    int diaN, mesN, anoN;
    char email[50];
    char diagnostico[8];
    char comorbidade;
    int idade;
    char doencas[255];
    int anoatual;
}REGISTRO;

typedef struct aux{
    REGISTRO reg;
    struct aux* prox; 
} ELEMENTO;

typedef ELEMENTO* PONT; //  PONT: ponteiro para uma estrutura do tipo ELEMENTO

typedef struct{
    PONT inicio;
} LISTA;

void inicializarLista (LISTA* l){
    l->inicio = NULL;   // Nao aponta para ninguem
}

void exibirLista (LISTA* l){
    PONT end = l->inicio;
    printf("\n");
    while (end != NULL)
    {
        printf("CPF:%011lld\t Nome:%s\n", end->reg.cpf, end->reg.nome);
        end = end->prox;
    }
    printf("\n");
}

PONT buscaSequencialExc(LISTA* l, TIPOCHAVE ch, PONT* ant){ // Retorna o PONT do valor buscado, e o PONT do anterior, usando *ant
    *ant = NULL;
    PONT atual = l->inicio;
    while ((atual != NULL) && (atual->reg.cpf < ch))  // Ultimo PONT da lista é NULL
    {
        *ant = atual;
        atual = atual->prox;
    }
    if((atual != NULL) && (atual->reg.cpf == ch)) return atual;   // Se encontrar um elemento com a mesma chave, retorna o ponteira deste
    return NULL;
}

bool inserirElemento(LISTA* l, REGISTRO reg){
    TIPOCHAVE ch = reg.cpf;
    PONT ant, i;
    i = buscaSequencialExc(l, ch, &ant);
    if (i != NULL) return false;    // Foi encontrado elemento com a mesma chave
    i = (PONT) malloc(sizeof(ELEMENTO));
    i->reg = reg;
    if(ant == NULL){    //  Se for o inicio da lista
        i->prox = l->inicio; // Ultimo elemento da lista deve apontar para um elemento NULL
        l->inicio = i;
    }   else{
        i->prox= ant->prox;
        ant->prox = i;
    }
    return true;
}

bool excluirElemLista (LISTA* l, TIPOCHAVE ch){
    PONT ant, i;
    i = buscaSequencialExc(l, ch, &ant);
    if(i == NULL) return false; //  Se o elemento não for encontrado
    if (ant == NULL) l->inicio = i->prox;   // Se o elemento encontrado for o inicio da lista
    else ant->prox = i->prox;
    free(i); // Libera a memoria do elemento i
    return true;
}

void reinicializarLista (LISTA* l){
    PONT end = l->inicio;
    while (end != NULL)    {    // enquanto não chegar no fim da lista
        PONT apagar = end;
        end = end->prox;
        free(apagar);
    }
    l->inicio = NULL;
}

int exibeMenu(void){
	int i;
	printf("CADASTRO DE PESSOAS\n");
	printf("1. Incluir\n");
	printf("2. Excluir \n");
	printf("3. Exibir \n");
	printf("Selecione a opcao desejada: ");
	scanf("%i", &i);
	printf("\n");
	return i;
}

bool menuInserir(LISTA* l)
{
	REGISTRO reg;
	printf("Digite o valor a ser inserido:\n");
	scanf("%i", &reg.cpf);
	printf("\n");
	return inserirElemento(l, reg);
}