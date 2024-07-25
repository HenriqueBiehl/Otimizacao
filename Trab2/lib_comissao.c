#include "lib_comissao.h"

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


struct listaCandidatos_t *melhoresCandidatos(struct listaCandidatos_t *E, struct listaCandidatos_t *F, unsigned int k){
    struct listaCandidatos_t *m;  
    int possuiGrupo;

    if(E->tamanho == 0){
        m = copiaLista(F);
        return m;
    }
    struct nodoLista_t *n, *cp;
    int grupos[k];

    for(int i = 0; i < k; ++i)
        grupos[i] = 0; 

    m = criaLista(); 

    n = E->inicio; 
    while(n != NULL){

        for(int g = 1; g <= k; ++g){
            possuiGrupo = 0; 
            for(int i = 1; i < n->grupo[0] + 1 && !possuiGrupo; ++i){
                if(n->grupo[i] == g){
                    grupos[g-1] = 1;
                    possuiGrupo = 1;
                }
            }

        }

        n = n->prox; 
    }

    n = F->inicio;
    while(n != NULL){
        possuiGrupo = 0; 
        for(int g= 1; g <= k; ++g){
            for(int i = 1; i < n->grupo[0] + 1 && !possuiGrupo && !grupos[g-1]; ++i){
                if(n->grupo[i] == g){
                    cp = copiaNodo(n);
                    insereElementoLista(m,cp);
                    possuiGrupo = 1;
                }
            }
        }
        n = n->prox;
    }

    return m;
}


int temTodosOsGrupos(struct listaCandidatos_t *l, unsigned int totalGrupos){
    struct nodoLista_t *n;
    int possuiGrupo;

    for(int g = 1; g <= totalGrupos; ++g){
        
        possuiGrupo = 0; 
        n = l->inicio; 
        
        while(n != NULL && !possuiGrupo){
            for(int i = 1; i < n->grupo[0]+1 && !possuiGrupo; ++i){
                if(n->grupo[i] == g){
                    possuiGrupo = 1;
                }
            }
            n = n->prox;
        }

        if(!possuiGrupo){
            return 0; 
        }
        
    }
    
    return 1;
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

int funcao_bound_professor(struct listaCandidatos_t *E, struct listaCandidatos_t *F, unsigned int l){
    int possuiGrupo;
    struct nodoLista_t *n;

    for(int g = 1; g <= l; ++g){
        
        possuiGrupo = 0; 
        n = E->inicio; 
        
        while(n != NULL && !possuiGrupo){
            for(int i = 1; i < n->grupo[0]+1 && !possuiGrupo; ++i){
                if(n->grupo[i] == g){
                    possuiGrupo = 1;
                }
            }
            n = n->prox;
        }        

        if(!possuiGrupo)
            return E->tamanho + 1; 
    }
    
    return E->tamanho;
}

int funcao_bound(struct listaCandidatos_t *E, struct listaCandidatos_t *F, unsigned int l){
    int possuiGrupo;
    struct nodoLista_t *n;
    int grupos[l]; 
    int jaTenho = 0;

    if(E->tamanho == 0)
        return 1;

    for(int g = 1; g <= l; ++g){
        
        possuiGrupo = 0; 
        n = E->inicio; 
        
        while(n != NULL && !possuiGrupo){
            for(int i = 1; i < n->grupo[0]+1 && !possuiGrupo; ++i){
                if(n->grupo[i] == g){
                    grupos[g-1] = 1; 
                    possuiGrupo = 1;
                    jaTenho++;
                }
            }
            n = n->prox;
        }        

        if(!possuiGrupo)
            grupos[g-1] = 0;
    }
    //1   2 4 7
    n = F->inicio; 
    int  checkpoint = jaTenho; 
    int nodosAteMelhor = 0;
    while(n != NULL){
        
        jaTenho = checkpoint; 
        
        for(int g = 0; g < l; ++g){
            for(int i = 1; i < n->grupo[0]+1  && !grupos[g]; ++i){
                if(n->grupo[i] == g+1)
                    jaTenho++;
            }
        }

        if(jaTenho == l){
            /*if(nodosAteMelhor > 0)
                return E->tamanho + nodosAteMelhor;
            else*/ 
                return E->tamanho + 1; 
        }

        nodosAteMelhor++;
        n = n->prox;
    }


    return E->tamanho + 2;
}


void comissao_padrao_sem_viabilidade(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n){
    struct nodoLista_t *x; 
    struct listaCandidatos_t *c; 
    int b; 

    c = melhoresCandidatos(S, C, n); 
    b = funcao_bound(S, C, n);
    int tam = c->tamanho;
    for(int i = 0; i < tam; ++i){

        if(b > melhorLista->tamanho){
            destroiLista(c); 
            return;
        }

        x = removePrimeiroElemento(c);
        nodosAcessados++;
        insereElementoLista(S, x); 
        comissao_padrao_sem_viabilidade(c, S, n);    
        removeUltimoElementoLista(S);    
        destroiNodo(x);
    } 

    if(temTodosOsGrupos(S,n)){
        if(S->tamanho < melhorLista->tamanho){
            struct listaCandidatos_t *aux; 
            aux = melhorLista;
            melhorLista = copiaLista(S);
            destroiLista(aux);
        }
    }

    destroiLista(c);
}

void comissao_padrao(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n){

    // printLista(C);

    if(temTodosOsGrupos(S,n)){
        if(S->tamanho < melhorLista->tamanho){
            struct listaCandidatos_t *aux; 
            aux = melhorLista;
            melhorLista = copiaLista(S);
            destroiLista(aux);
        }
        else 
            return;
    }

    struct nodoLista_t *x; 
    struct listaCandidatos_t *c; 
    int b; 

    c = melhoresCandidatos(S, C, n);
    b = funcao_bound(S, c, n);
    int tam = c->tamanho;
    for(int i = 0; i < tam; ++i){
        if(b >= melhorLista->tamanho){
            destroiLista(c); 
            return;
        }

        x = removePrimeiroElemento(c);
        nodosAcessados++;
        insereElementoLista(S, x); 
        comissao_padrao(c, S, n);    
        removeUltimoElementoLista(S);    
        destroiNodo(x);
    } 

    destroiLista(c);
}

void comissao_professor_sem_viabilidade(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n){

    struct nodoLista_t *x; 
    struct listaCandidatos_t *c; 
    int b; 

    c = melhoresCandidatos(S, C, n); 
    b = funcao_bound_professor(S, C, n);
    int tam = c->tamanho;
    for(int i = 0; i < tam; ++i){

        if(b > melhorLista->tamanho){
            destroiLista(c); 
            return;
        }

        x = removePrimeiroElemento(c);
        nodosAcessados++;
        insereElementoLista(S, x); 
        comissao_professor(c, S, n);    
        removeUltimoElementoLista(S);    
        destroiNodo(x);
    } 
        
    if(temTodosOsGrupos(S,n)){
        if(S->tamanho < melhorLista->tamanho){
            struct listaCandidatos_t *aux; 
            aux = melhorLista;
            melhorLista = copiaLista(S);
            destroiLista(aux);
        }
    }

    destroiLista(c);
}

void comissao_professor(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n){
        
    if(temTodosOsGrupos(S,n)){
        if(S->tamanho < melhorLista->tamanho){
            struct listaCandidatos_t *aux; 
            aux = melhorLista;
            melhorLista = copiaLista(S);
            destroiLista(aux);
        }
        else
            return;
    }

    struct nodoLista_t *x; 
    struct listaCandidatos_t *c; 
    int b; 

    c = melhoresCandidatos(S, C, n); 
    b = funcao_bound_professor(S, C, n);
    int tam = c->tamanho;
    for(int i = 0; i < tam; ++i){

        if(b >= melhorLista->tamanho){
            destroiLista(c); 
            return;
        }

        x = removePrimeiroElemento(c);
        nodosAcessados++;
        insereElementoLista(S, x); 
        comissao_professor(c, S, n);    
        removeUltimoElementoLista(S);    
        destroiNodo(x);
    } 
    destroiLista(c);
}



void comissao_sem_otimalidade(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n){
        
    if(temTodosOsGrupos(S,n)){
        if(S->tamanho < melhorLista->tamanho){
            struct listaCandidatos_t *aux; 
            aux = melhorLista;
            melhorLista = copiaLista(S);
            destroiLista(aux);
        }
        else
            return;
    }

    struct nodoLista_t *x; 
    struct listaCandidatos_t *c; 

    c = melhoresCandidatos(S, C, n);
    int tam = c->tamanho;
    for(int i = 0; i < tam; ++i){
        x = removePrimeiroElemento(c);
        nodosAcessados++;
        insereElementoLista(S, x); 
        comissao_sem_otimalidade(c, S, n);    
        removeUltimoElementoLista(S);    
        destroiNodo(x);
    } 

    destroiLista(c);
}

void comissao_normal(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n){
    struct nodoLista_t *x; 
    struct listaCandidatos_t *c; 
    
    c = melhoresCandidatos(S,C, n); 
    int tam = c->tamanho;
    for(int i = 0; i < tam; ++i){
        x = removePrimeiroElemento(c);
        nodosAcessados++;
        insereElementoLista(S, x); 
        comissao_normal(c, S, n);    
        removeUltimoElementoLista(S);    
        destroiNodo(x);
    } 
    
    if(temTodosOsGrupos(S,n)){
        if(S->tamanho < melhorLista->tamanho){
            struct listaCandidatos_t *aux; 
            aux = melhorLista;
            melhorLista = copiaLista(S);
            destroiLista(aux);
        }
    }

    destroiLista(c);
}