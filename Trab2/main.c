#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <getopt.h>

struct listaCandidatos_t *melhorLista; 
unsigned int nodosAcessados; 

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

void printLista(struct listaCandidatos_t *l);

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
    free(n->grupo);
    free(n);
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

    l->fim = n->ant;
    if(n == l->inicio)
        l->inicio = NULL; 
    else{
        n->ant->prox = NULL;
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
        printf("id: %d [ ", n->id);
        for(int i=1; i < n->grupo[0]+1; ++i)
            printf("%d ",n->grupo[i]);
        printf("]\n");
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
    int numeroGruposFaltando = 0;
    int jaTenho = 0;
    int grupos[l]; 
    struct nodoLista_t *n;

    for(int i =0; i < l; ++i)
        grupos[i] = 1;

    for(int g = 1; g <= l; ++g){
        
        possuiGrupo = 0; 
        n = E->inicio; 
        
        while(n != NULL && !possuiGrupo){
            for(int i = 1; i < n->grupo[0]+1 && !possuiGrupo; ++i){
                if(n->grupo[i] == g){
                    grupos[g-1] = 0; 
                    possuiGrupo = 1;
                    jaTenho++;
                }
            }
            n = n->prox;
        }        

        if(!possuiGrupo)
            numeroGruposFaltando++;
    }

    if(numeroGruposFaltando == 0)
        return E->tamanho;

    int candidatosNecessarios = 0; 
    int aux; 
    n = F->inicio; 
    while(n != NULL && jaTenho < l){

        for(int i = 0; i < l; ++i){
            
            aux = jaTenho; 
            candidatosNecessarios++; 

            for(int j = 1; j < n->grupo[0]+1 && !grupos[i]; ++j){
                if(n->grupo[j] == i+1){
                    grupos[j-1] = 1;
                    jaTenho++; 
                }
            }

            if(aux == jaTenho)
                candidatosNecessarios--;
        }
        n = n->prox; 
    }
    
    return E->tamanho + candidatosNecessarios;
}

void comissao_sem_viabilidade(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n, unsigned int l){
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
        comissao_sem_viabilidade(c, S, n, l+1);    
        removeUltimoElementoLista(S);    
        destroiNodo(x);
        x = removePrimeiroElemento(c);
        nodosAcessados++;

    } 
    destroiLista(c);

    if(temTodosOsGrupos(S,n)){
        if(S->tamanho < melhorLista->tamanho){
            struct listaCandidatos_t *aux; 
            aux = melhorLista;
            melhorLista = copiaLista(S);
            destroiLista(aux);
        }
    }
}

void comissao_padrao(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n, unsigned int l){
        
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
    b = funcao_bound(S, C, n);
    while(x != NULL){
        
        if(b >= melhorLista->tamanho){
            destroiNodo(x);
            destroiLista(c); 
            return;
        }
        
        insereElementoLista(S, x); 
        comissao_padrao(c, S, n, l+1);    
        removeUltimoElementoLista(S);    
        destroiNodo(x);
        x = removePrimeiroElemento(c);
        nodosAcessados++;
    } 
    destroiLista(c);
}

void comissao_branch_and_bound_professor(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n, unsigned int l){
        
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
        comissao_branch_and_bound_professor(c, S, n, l+1);    
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


int main(int argc, char *const argv[]){
    struct listaCandidatos_t *candidatos; 
    struct listaCandidatos_t *selecionados; 
    struct nodoLista_t *nodo;
    unsigned int l, n;
    unsigned int maxGrupos;
    unsigned int *grupos;  
    unsigned int opt, opt_a = 0, opt_o = 0, opt_f = 0, opt_d = 1; 

    candidatos   = criaLista();
    selecionados = criaLista();

    scanf("%d", &l);
    scanf("%d", &n); 

    for(int i = 0; i < n; ++i){
        scanf("%d", &maxGrupos); 
        grupos = malloc((maxGrupos + 1)*sizeof(unsigned int));
        grupos[0] = maxGrupos;
        for(int k = 1; k < maxGrupos + 1; ++k){
            scanf("%d", &grupos[k]); 
        }
        nodo = criaNodo(i+1, grupos); 
        insereElementoLista(candidatos, nodo);
    }

    if(!temTodosOsGrupos(candidatos, l)){ 
        printf("Problema Inviável\n");
        destroiLista(candidatos);
        destroiLista(selecionados);
        return 0;
    }

    while((opt = getopt(argc,argv,"ofa")) != -1) {
        opt_d = 0;
		switch (opt){
			case 'o':
				opt_o = 1;
				break; 
			case 'f':
				opt_f = 1;
 				break;
			case 'a':
				opt_a = 1; 
				break; 
			default:
                break;
 		}
	}

    melhorLista = copiaLista(candidatos);
    nodosAcessados = 0;

    if(opt_d)
        comissao_padrao(candidatos, selecionados, l, 0);

    if(opt_f)
        comissao_sem_viabilidade(candidatos, selecionados, l, 0);
    
    if(opt_a)
        comissao_branch_and_bound_professor(candidatos, selecionados, l, 0);
       
    if(opt_o)
        comissao_sem_otimalidade(candidatos, selecionados, l, 0);

    printLista(melhorLista);
    printf("Nodos acessados: %d\n", nodosAcessados);
    
       
    destroiLista(candidatos);
    destroiLista(selecionados);
    destroiLista(melhorLista);

    return 0;
}