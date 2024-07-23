#include "lib_comissao.h"
#include <stdio.h>
#include <stdlib.h> 
#include <getopt.h>
#include <time.h>

struct listaCandidatos_t *melhorLista; 
unsigned int nodosAcessados; 


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
        comissao_normal(candidatos, selecionados, l, 0);
    }
    else if(opt_o){
        comissao_sem_otimalidade(candidatos, selecionados,l, 0);
    }
    else if(opt_f){    
        if(opt_a)
            comissao_professor_sem_viabilidade(candidatos, selecionados, l, 0);
        else 
            comissao_padrao_sem_viabilidade(candidatos, selecionados, l, 0);
    }
    else{
        if(opt_a)
            comissao_professor(candidatos, selecionados, l, 0);
        else 
            comissao_padrao(candidatos, selecionados,l, 0);
    }
    end = clock();

    double time = (double)(end - start)/CLOCKS_PER_SEC;
    printLista(melhorLista);
    printf("Nodos acessados: %d\n", nodosAcessados);
    printf("Tempo gasto: %lf\n", time);
    
       
    destroiLista(candidatos);
    destroiLista(selecionados);
    destroiLista(melhorLista);

    return 0;
}