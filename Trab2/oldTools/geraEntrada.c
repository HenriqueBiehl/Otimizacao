#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

#define MAX_L 25
#define MAX_N 10

int randomNumber(int range){
    return rand() % range + 1;
}

int main(int argc, char *const argv[]){
    int l_max; 
    int n_max;

    srand(time(NULL));

    scanf("%d", &l_max); 
    scanf("%d", &n_max);

    int tam;  
    int *cjt;
    int x; 
    printf("%d %d\n", l_max, n_max);

    for(int i=0; i < n_max; ++i){
        tam = randomNumber(l_max); 
        cjt = malloc(tam*sizeof(int));
        x = randomNumber(l_max);
        printf("%d ", tam);
        cjt[0] = x;
        printf("%d", x);
        for(int j=1; j < tam; ++j){
            int ok = 0; 
            while(!ok){
                x = randomNumber(l_max);
                int naoRepete = 1;
                
                for(int k=0; k <= j && naoRepete; ++k){
                    if(x == cjt[k]){
                        naoRepete = 0;
                    }
                }

                if(naoRepete)
                    ok = 1;
            }
            cjt[j] = x;
            printf(" %d", x); 
        }
        printf("\n");
    }

    free(cjt);

    return 0;
}