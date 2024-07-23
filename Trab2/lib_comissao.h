#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

extern struct listaCandidatos_t *melhorLista; 
extern unsigned int nodosAcessados; 

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

struct nodoLista_t *criaNodo(unsigned int id, unsigned int *g);

struct nodoLista_t *destroiNodo(struct nodoLista_t *n);

struct listaCandidatos_t *criaLista();

struct listaCandidatos_t *destroiLista(struct listaCandidatos_t *l);

void insereElementoFimLista(struct listaCandidatos_t *l, struct nodoLista_t *n);

int insereElementoLista(struct listaCandidatos_t *l, struct nodoLista_t *n);

struct nodoLista_t *removeUltimoElementoLista(struct listaCandidatos_t *l);

struct nodoLista_t *removePrimeiroElemento(struct listaCandidatos_t *l);

struct nodoLista_t *copiaNodo(struct nodoLista_t *n);

struct listaCandidatos_t *copiaLista(struct listaCandidatos_t *l);

int temTodosOsGrupos(struct listaCandidatos_t *l, unsigned int totalGrupos);

void printLista(struct listaCandidatos_t *l);

int funcao_bound_professor(struct listaCandidatos_t *E, struct listaCandidatos_t *F, unsigned int l);

int calculaNecessarios(struct nodoLista_t *n, int v[], int jaTenho, int l);

int funcao_bound(struct listaCandidatos_t *E, struct listaCandidatos_t *F, unsigned int l);

void comissao_padrao_sem_viabilidade(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n, unsigned int l);

void comissao_padrao(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n, unsigned int l);

void comissao_professor_sem_viabilidade(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n, unsigned int l);

void comissao_professor(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n, unsigned int l);

void comissao_sem_otimalidade(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n, unsigned int l);

void comissao_normal(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n, unsigned int l);