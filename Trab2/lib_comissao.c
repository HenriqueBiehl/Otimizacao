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

    // printf("lista l em insere elemento lista\n");
    // printLista(l);
    // printf("nodo a ser inserido: %d\n", n->id);

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

    //printf("%d esta recebendo %d como anterior\n", n->id, anterior->id);


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
    // if(n->ant == NULL)
    //         printf(" Ant de %d é nulo k\n", n->id);
   
    if(n == NULL)
        return NULL; 
    
    l->fim = n->ant;
   
    if(n == l->inicio)
        l->inicio = NULL; 
    else{
        // printf("%d id \n", n->id);
        // if(n->ant == NULL){
        //     printf(" Ant de %d é nulo k\n", n->id);
        //     printf("Lista no momento: \n");
        //     printLista(l);
        // }
        l->fim->prox = NULL;
    }

    l->tamanho--;
    
    //printf(" ** removi %d **\n", n->id);
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

/*
struct listaCandidatos_t *melhoresCandidatos(struct listaCandidatos_t *l, unsigned int k){
    int grupos[k];
    struct nodoLista_t *n, *cp;
    struct listaCandidatos_t *m;  
    int possuiGrupo;

    for(int i = 0; i < k; ++i)
        grupos[i] = 0; 

    m = criaLista(); 

    n = l->inicio; 

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

    for(int g= 1; g <= k; ++g){

        n = l->inicio;
        while(n != NULL && !grupos[g-1]){
            possuiGrupo = 0; 
            for(int i = 1; i < n->grupo[0] + 1 && !possuiGrupo; ++i){
                if(n->grupo[i] == g){
                    cp = copiaNodo(n);
                    insereElementoLista(l,n);
                    possuiGrupo = 1;
                }
            }
            n = n->prox;
        }
    }

    return m;
}
*/

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
        // for(int i=1; i < n->grupo[0]+1; ++i)
        //     printf("%d ",n->grupo[i]);
        // printf("]\n");
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

int funcao_bound2(struct listaCandidatos_t *E, struct listaCandidatos_t *F, unsigned int l){
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
            return E->tamanho + 2; 
    }
    
    return E->tamanho;
}

int calculaNecessarios(struct nodoLista_t *n, int v[], int jaTenho, int l){
    int candidatosNecessarios = 0; 
    int aux; 
    int grupos[l]; 

    for(int i = 0; i < l; ++i)
        grupos[i] = v[i];
    
    //printf("antes de ver já tenho %d\n", jaTenho);
    while(n != NULL && jaTenho < l){
        
      /*  printf("Quem ja tenho: ");
        for(int i = 0; i < l; ++i)
        printf("%d:%d ", i+1, grupos[i]); */

        aux = jaTenho; 
        candidatosNecessarios++; 

        for(int i = 0; i < l; ++i){
        //    printf("vou avaliar grupo %d em %d\n", i+1, n->id);
            for(int j = 1; j < n->grupo[0]+1 && !grupos[i]; ++j){
                if(n->grupo[j] == i+1){
          //          printf("    %d tem %d\n", n->id, i+1);
                    grupos[i] = 1;
                    jaTenho++; 
            //        printf("    vou precisar de %d\n    ja tenho = %d\n     grupo %d = %d\n", n->id, jaTenho, i+1, grupos[i]);
                }
            }
        }

        if(aux == jaTenho)
            candidatosNecessarios--;
        n = n->prox; 
    }
    
    if(jaTenho < l)
        return jaTenho;
    return candidatosNecessarios;
}

int funcao_bound(struct listaCandidatos_t *E, struct listaCandidatos_t *F, unsigned int l){
    int possuiGrupo;
    int numeroGruposFaltando = 0;
    int jaTenho = 0;
    int grupos[l]; 
    struct nodoLista_t *n;

    for(int i =0; i < l; ++i)
        grupos[i] = 0;

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
            numeroGruposFaltando++;
    }

    if(numeroGruposFaltando == 0){
        return E->tamanho;

    }

    int candidatosNecessarios = 0; 
    int aux; 
    
    n = F->inicio;
    while(n != NULL && jaTenho < l){
        
        aux = jaTenho; 
        candidatosNecessarios++; 

        for(int i = 0; i < l; ++i){
            for(int j = 1; j < n->grupo[0]+1 && !grupos[i]; ++j){
                if(n->grupo[j] == i+1){
                    grupos[i] = 1;
                    jaTenho++; 
                }
            }
        }

        if(aux == jaTenho)
            candidatosNecessarios--;
        n = n->prox; 
    }
    

    return E->tamanho + F->tamanho - 1;
}

void comissao_padrao_sem_viabilidade(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n, unsigned int l){
    struct nodoLista_t *x; 
    struct listaCandidatos_t *c; 
    int b; 

    c = copiaLista(C); 
    x = removePrimeiroElemento(c);
    nodosAcessados++;
    b = funcao_bound2(S, C, n);
    while(x != NULL){
        
        if(b > melhorLista->tamanho){
             destroiNodo(x);
             destroiLista(c); 
             return;
        }
        
        insereElementoLista(S, x); 
        comissao_padrao_sem_viabilidade(c, S, n, l+1);    
        removeUltimoElementoLista(S);    
        destroiNodo(x);
        x = removePrimeiroElemento(c);
        nodosAcessados++;

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

void comissao_padrao(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n, unsigned int l){

    printf("***** Chamada %d *****\n",l);
    printf("Lista Candidatos: \n");
    printLista(C);
    printf("Lista Selecionados: \n");
    printLista(S);
    printf("**********************\n");

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

    struct nodoLista_t *x, *aux; 
    struct listaCandidatos_t *c; 
    int b; 

    c = copiaLista(C);
    x = removePrimeiroElemento(c);
    nodosAcessados++;
    b = funcao_bound2(S, c, n);
    while(x != NULL){
        printf("** Montando lista para nodo %d na chamada %d **\n", x->id, l);
        printf("Bound é %d\n", b);
        if(b > melhorLista->tamanho){
            printf("    Voltando por causa do bound %d e o maior grupo tem %d no total\n", b, melhorLista->tamanho);
            destroiNodo(x);
            destroiLista(c); 
            return;
        }

        insereElementoLista(S, x); 
        comissao_padrao(c, S, n, l+1);    
        aux = removeUltimoElementoLista(S);
        if(aux != NULL)
            //printf("Removi %d na chamada %d\n", aux->id, l); 

        destroiNodo(x);
        x = removePrimeiroElemento(c);
        nodosAcessados++;
    } 
    destroiLista(c);
    //printf("Cheguei no fim\n");
}

void comissao_professor_sem_viabilidade(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n, unsigned int l){

    struct nodoLista_t *x; 
    struct listaCandidatos_t *c; 
    int b; 

    c = copiaLista(C); 
    x = removePrimeiroElemento(c);
    nodosAcessados++;
    b = funcao_bound_professor(S, C, n);
    while(x != NULL){
        
        if(b > melhorLista->tamanho){
            destroiNodo(x);
            destroiLista(c); 
            return;
        }
        
        insereElementoLista(S, x); 
        comissao_professor_sem_viabilidade(c, S, n, l+1);    
        removeUltimoElementoLista(S);    
        destroiNodo(x);
        x = removePrimeiroElemento(c);
        nodosAcessados++;

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

void comissao_professor(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n, unsigned int l){
        
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

    c = copiaLista(C); 
    x = removePrimeiroElemento(c);
    nodosAcessados++;
    b = funcao_bound_professor(S, C, n);
    while(x != NULL){
        
        if(b >= melhorLista->tamanho){
            destroiNodo(x);
            destroiLista(c); 
            return;
        }
        
        insereElementoLista(S, x); 
        comissao_professor(c, S, n, l+1);    
        removeUltimoElementoLista(S);    
        destroiNodo(x);
        x = removePrimeiroElemento(c);
        nodosAcessados++;

    } 
    destroiLista(c);
}



void comissao_sem_otimalidade(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n, unsigned int l){
        
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

    c = copiaLista(C);
    x = removePrimeiroElemento(c);
    nodosAcessados++;

    while(x != NULL){
        insereElementoLista(S, x); 
        comissao_sem_otimalidade(c, S, n, l+1);    
        removeUltimoElementoLista(S);    
        destroiNodo(x);
        x = removePrimeiroElemento(c);
        nodosAcessados++;
    } 
    destroiLista(c);
}

void comissao_normal(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n, unsigned int l){
    struct nodoLista_t *x; 
    struct listaCandidatos_t *c; 

    c = copiaLista(C); 
    x = removePrimeiroElemento(c);
    nodosAcessados++;
    while(x != NULL){
        
        insereElementoLista(S, x); 
        comissao_normal(c, S, n, l+1);    
        removeUltimoElementoLista(S);    
        destroiNodo(x);
        x = removePrimeiroElemento(c);
        nodosAcessados++;
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