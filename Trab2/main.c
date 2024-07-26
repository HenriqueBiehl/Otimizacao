#include "lib_lista.h"
#include <stdio.h>
#include <stdlib.h> 
#include <getopt.h>
#include <time.h>

struct listaCandidatos_t *melhorLista; 
unsigned int nodosAcessados; 

/*
    Seleciona, dentre a lista de candidatos F, os melhores candidatos em relação aos já selecionados E. 
    É inserido na lista caso haja um candidato em F que possua um grupo que nenhum outro selecionado de E possua. 
*/
struct listaCandidatos_t *melhoresCandidatos(struct listaCandidatos_t *E, struct listaCandidatos_t *F, unsigned int k){
    struct listaCandidatos_t *m;  
    int possuiGrupo;

    //Caso E seja vazia, retorna uma cópia de F
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

/*
    Checa se a listaCandidatos_t l possui todos os grupos do total dado por totalGrupos
    Retorna 1 se possui e 0 caso contrário
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

/*
    Função bound dada pelo professor. Analisa se E possui todos os grupos possíveis (em um total de l grupos). 
    Se possui retorna que o limite é o prórprio tamanho de E. Caso contrário, retorna tamanho de E + 1.
*/
int funcao_bound_professor(struct listaCandidatos_t *E, unsigned int l){
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

/*
    Função bound do aluno. Analisa se E possui todos os grupos possíveis (em um total de l grupos). 
    Se possui retorna que o limite é o prórprio tamanho de E. Caso contrário, analisa se existe
    algum elemento em F que resolva o problema de forma imediata. Retorna tamanho de E + 1 caso exista esse elemento.
    Caso contrário, retorna tamanho de E + 2;
*/
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

    if(jaTenho == l)
        return E->tamanho;

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
            return E->tamanho + 1; 
        }

        nodosAteMelhor++;
        n = n->prox;
    }


    return E->tamanho + 2;
}

/*
    Resolução do problema da comissão utilizando a função_bound e sem corte por viabilidade.
*/
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

/*
    Resolução do problema da comissão utilizando a função_bound. 
*/
void comissao_padrao(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n){

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
        if(b > melhorLista->tamanho){
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

/*
    Resolução do problema da comissão utilizando a função_bound_professor e sem corte por viabilidade.
*/
void comissao_professor_sem_viabilidade(struct listaCandidatos_t *C, struct listaCandidatos_t *S, unsigned int n){

    struct nodoLista_t *x; 
    struct listaCandidatos_t *c; 
    int b; 

    c = melhoresCandidatos(S, C, n); 
    b = funcao_bound_professor(S, n);
    int tam = c->tamanho;
    for(int i = 0; i < tam; ++i){

        if(b > melhorLista->tamanho){
            destroiLista(c); 
            return;
        }

        x = removePrimeiroElemento(c);
        nodosAcessados++;
        insereElementoLista(S, x); 
        comissao_professor_sem_viabilidade(c, S, n);    
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

/*
    Resolução do problema da comissão utilizando a função_bound_professor.
*/
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
    b = funcao_bound_professor(S, n);
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
    destroiLista(c);
}

/*
    Resolução do problema da comissão sem cortes de otimalidade.
*/
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

/*
    Resolução do problema da comissão sem utilizar de cortes de viabilidade e otimalidade.
*/
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


int main(int argc, char *const argv[]){
    struct listaCandidatos_t *candidatos; 
    struct listaCandidatos_t *selecionados; 
    struct nodoLista_t *nodo;
    clock_t start, end;
    unsigned int l, n;
    unsigned int maxGrupos;
    unsigned int *grupos;  
    unsigned int opt, opt_a = 0, opt_o = 0, opt_f = 0; 

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

    start = clock();
    if(opt_f && opt_o){
        comissao_normal(candidatos, selecionados, l);
    }
    else if(opt_o){
        comissao_sem_otimalidade(candidatos, selecionados,l);
    }
    else if(opt_f){    
        if(opt_a)
            comissao_professor_sem_viabilidade(candidatos, selecionados, l);
        else 
            comissao_padrao_sem_viabilidade(candidatos, selecionados, l);
    }
    else{
        if(opt_a)
            comissao_professor(candidatos, selecionados, l);
        else 
            comissao_padrao(candidatos, selecionados,l);
    }
    end = clock();

    double time = (double)(end - start)/CLOCKS_PER_SEC;
    printLista(melhorLista);
    fprintf(stderr, "Nodos acessados: %d\n", nodosAcessados);
    fprintf(stderr, "Tempo gasto: %lf (s)\n", time);
    
       
    destroiLista(candidatos);
    destroiLista(selecionados);
    destroiLista(melhorLista);

    return 0;
}