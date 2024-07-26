#include "lib_lista.h"

struct nodoLista_t *criaNodo(unsigned int id, unsigned int *g){
    struct nodoLista_t *n; 

    n = malloc(sizeof(struct nodoLista_t));

    if(!n)
        return NULL;
    
    n->id    = id;   
    n->grupo = g;
    n->ant   = NULL;
    n->prox  = NULL;

    return n; 
}

struct nodoLista_t *destroiNodo(struct nodoLista_t *n){
    
    if(n != NULL){
        free(n->grupo);
        free(n);
    }
    
    return NULL; 
}

struct listaCandidatos_t *criaLista(){
    struct listaCandidatos_t *l; 

    l = malloc(sizeof(struct listaCandidatos_t)); 

    if(!l)
        return NULL;

    l->inicio  = NULL;
    l->fim     = NULL;
    l->tamanho = 0; 

    return l; 
}

struct listaCandidatos_t *destroiLista(struct listaCandidatos_t *l){
    struct nodoLista_t *n, *aux; 

    n = l->inicio;
    while(n != NULL){
        aux = n; 
        n = n->prox; 
        destroiNodo(aux);
    }

    free(l);

    return NULL;
}

void insereElementoFimLista(struct listaCandidatos_t *l, struct nodoLista_t *n){
    struct nodoLista_t *aux; 

    n->prox = NULL; 
    aux = l->fim; 
    
    if(l->fim == NULL){
        l->inicio = n; 
        n->ant = NULL; 
    }
    else{
        aux->prox = n; 
        n->ant = aux; 
    }

    l->fim = n; 
    l->tamanho++;
}

int insereElementoLista(struct listaCandidatos_t *l, struct nodoLista_t *n){
    struct nodoLista_t *aux, *anterior;
    unsigned int acheiMaximo = 0;

    if(n == NULL)
        return 0;

    n->ant = NULL;
    n->prox = NULL;

    /* Checa se n será inserido em uma lista vazia*/
    if(l->inicio == NULL){
        l->inicio = n; 
        l->fim    = n; 
        l->tamanho++;
        return 1;
    }

    aux = l->inicio; 
    anterior = NULL;

    while(aux != NULL && !acheiMaximo){
       
        if(aux->id == n->id)
            return 0;
       
        if(aux->id < n->id){
            anterior = aux;             
            aux = aux->prox; 
        }
        else 
            acheiMaximo = 1;
    }

    n->ant  = anterior;
    
    /* Checa se o elemento não deve ser inserido no inicio da lista em uma lista sem elementos*/
    if(anterior == NULL){
        l->inicio = n; 
        aux->ant = n; 
        n->prox = aux;
        l->tamanho++;
        return 1;
    }
    else {
        n->prox = anterior->prox; 
        anterior->prox = n;
    }

    /* Checa se o elemento n é final na lista */
    if(n->prox == NULL)        
        l->fim = n; 
    else 
        anterior->prox->ant = n ;

    l->tamanho++;

    return 1;
}

int insereElementoListaPorGrupo(struct listaCandidatos_t *l, struct nodoLista_t *n){
    struct nodoLista_t *aux, *anterior;
    unsigned int acheiMaximo = 0;

    if(n == NULL)
        return 0;

    n->ant = NULL;
    n->prox = NULL;

    /* Checa se n será inserido em uma lista vazia*/
    if(l->inicio == NULL){
        l->inicio = n; 
        l->fim    = n; 
        l->tamanho++;
        return 1;
    }

    aux = l->inicio; 
    anterior = NULL;

    while(aux != NULL && !acheiMaximo){
       
        if(aux->id == n->id)
            return 0;
       
        if(aux->grupo[0] > n->grupo[0]){
            printf("Aux grupo tem %d e n grupo tem %d\n", aux->grupo[0], n->grupo[0]);
            anterior = aux;             
            aux = aux->prox; 
        }
        else 
            acheiMaximo = 1;
    }

    n->ant  = anterior;
    
    /* Checa se o elemento não deve ser inserido no inicio da lista em uma lista sem elementos*/
    if(anterior == NULL){
        l->inicio = n; 
        aux->ant = n; 
        n->prox = aux;
        l->tamanho++;
        return 1;
    }
    else {
        n->prox = anterior->prox; 
        anterior->prox = n;
    }

    /* Checa se o elemento n é final na lista */
    if(n->prox == NULL)        
        l->fim = n; 
    else 
        anterior->prox->ant = n ;

    l->tamanho++;

    return 1;
}

struct nodoLista_t *removeUltimoElementoLista(struct listaCandidatos_t *l){
    struct nodoLista_t *n; 

    n = l->fim; 
   
    if(n == NULL)
        return NULL; 
    
    l->fim = n->ant;
   
    if(n == l->inicio)
        l->inicio = NULL; 
    else{
        l->fim->prox = NULL;
    }

    l->tamanho--;
    
    return n;
}

struct nodoLista_t *removePrimeiroElemento(struct listaCandidatos_t *l){
    struct nodoLista_t *n; 

    if(l->inicio == NULL)
        return NULL; 

    n = l->inicio; 

    l->inicio = n->prox; 
    
    if(l->inicio == NULL)
        l->fim = NULL;
    else
        l->inicio->ant = NULL;

    l->tamanho--;

    return n; 
}

struct nodoLista_t *copiaNodo(struct nodoLista_t *n){
    struct nodoLista_t *c; 
    unsigned int maxSize; 
    unsigned int *g; 

    c = malloc(sizeof(struct nodoLista_t));
    if(!c)
        return NULL; 
    
    c->id = n->id; 
    maxSize = n->grupo[0] + 1;
    g = malloc(maxSize*sizeof(unsigned int));

    for(int i=0; i < maxSize; ++i)
        g[i] = n->grupo[i]; 
    c->grupo = g;
    c->ant = NULL;
    c->prox= NULL;

    return c;
}

struct listaCandidatos_t *copiaLista(struct listaCandidatos_t *l){
    struct listaCandidatos_t *c; 
    struct nodoLista_t *n, *nc; 

    c = criaLista(); 

    n = l->inicio; 
    while(n != NULL){
        nc = copiaNodo(n); 
        insereElementoLista(c, nc);
        n = n->prox;
    }

    return c;
}

void printLista(struct listaCandidatos_t *l){
    struct nodoLista_t *n; 

    n = l->inicio;
    while(n != NULL){
        printf("%d ", n->id);
        n = n->prox;
    }
    printf("\n");

}