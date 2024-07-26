#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

struct nodoLista_t{
    unsigned int id; 
    unsigned int *grupo;
    struct nodoLista_t *ant;    
    struct nodoLista_t *prox; 
};

struct listaCandidatos_t{
    unsigned int tamanho;
    struct nodoLista_t *inicio; 
    struct nodoLista_t *fim;  
};

/*
    Função que cria um nodo do tipo struct nodoLista_t, recebendo como 
    parâmetro seu id e o vetor de unsigned int *g;
    Retorna o ponteiro do vetor em caso de sucesso e NULL em caso de falha;
*/
struct nodoLista_t *criaNodo(unsigned int id, unsigned int *g);

/*
    Função que libera toda memória associada ao vetor struct nodoLista_t n; 
    Retorna NULL; 
*/
struct nodoLista_t *destroiNodo(struct nodoLista_t *n);

/*
    Função que cria uma lista do tipo struct listaCandidatos_t;
    Retorna o ponteiro do vetor em caso de sucesso e NULL em caso de falha;
*/
struct listaCandidatos_t *criaLista();

/*
    Função que libera toda memória associada a lista struct listaCandidatos_t l; 
    Retorna NULL; 
*/
struct listaCandidatos_t *destroiLista(struct listaCandidatos_t *l);

/*
    Insere o elemento struct nodoLista_t n no fim da lista struct listaCandidatos_t l; 
*/
void insereElementoFimLista(struct listaCandidatos_t *l, struct nodoLista_t *n);

/*
    Insere o elemento struct nodoLista_t n ordenadamente na lista struct listaCandidatos_t l; 
    Retorna 1 em caso de sucesso e 0 caso contrário.
*/
int insereElementoLista(struct listaCandidatos_t *l, struct nodoLista_t *n);

/*
    Remove o último elemento da listaCandidatos_t l e retorna seu ponteiro;
*/
struct nodoLista_t *removeUltimoElementoLista(struct listaCandidatos_t *l);

/*
    Remove o primeiro elemento da listaCandidatos_t l e retorna seu ponteiro;
*/
struct nodoLista_t *removePrimeiroElemento(struct listaCandidatos_t *l);

/*
    Copia todas as informações associadas ao nodo 
    struct nodoLista_t n em um novo nodo; 
    Retorna o ponteiro para essa cópia;
*/
struct nodoLista_t *copiaNodo(struct nodoLista_t *n);

/*
    Copia todas as informações associadas a lista 
    struct listaCandidatos_t l em uma nova lista; 
    Retorna o ponteiro para essa cópia;
*/
struct listaCandidatos_t *copiaLista(struct listaCandidatos_t *l);

/*
    Imprime os id's de todo elemento presente na struct listaCandidatos_t l; 
*/
void printLista(struct listaCandidatos_t *l);
