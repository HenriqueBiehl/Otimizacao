#include <stdio.h>
#include <stdlib.h>
#include "cityNetwork.h"
#define START 1

/* Gera a equação a ser maximizada */
void maximizationEquation(cityConnections_t *c, package_t *r, unsigned int q, unsigned int p){
	cityNode *nodo;
	nodo = c[0].exits->start;
 	
 	printf("max:");

	printf("%dx0%d0%d", p , START, nodo->cityId);
	nodo = nodo->next;
	while(nodo != NULL){
 		printf(" + ");
		printf("%dx0%d0%d", p , START, nodo->cityId);

 		nodo = nodo->next;
 	}

 	printf(" - %dq0%d", r[0].price , 1);
 	for(unsigned int i = 1; i < q; ++i){
 		printf(" - ");
		printf("%dq0%d", r[i].price , i+1);
 	}
 	printf(";\n");
}

/* Gera desigualdades referentes as capacidades da rota e seus fluxos */
void routesIntervals(routes_t *r, unsigned int m){

  	for(unsigned int i=0; i < m; i++){ 
 		printf("-%d <= x0%d0%d <= %d;\n", r[i].capacity, r[i].startPoint, r[i].endPoint, r[i].capacity);
 	}
 	printf("\n");
}

/* Gera equação das rotas */
void routesEquations(cityConnections_t *c, unsigned int n){
	cityNode *nodo;

	for(unsigned int i=1; i < n-1; i++){
 		
 		nodo = c[i].entrances->start;

 		if(nodo == NULL){
 			printf("0");
 		}
 		else {
			printf("x0%d0%d", nodo->cityId, c[i].mainCityId);
 			nodo = nodo->next;
 			while(nodo != NULL){
 				printf(" + ");
 				printf("x0%d0%d", nodo->cityId, c[i].mainCityId);
 				nodo = nodo->next;
 			}
  		}
 
  		printf(" = ");

 		nodo = c[i].exits->start;
 		if(nodo == NULL){
 			printf("0");
 		}
 		else{
			printf("x0%d0%d", c[i].mainCityId, nodo->cityId);
 			nodo = nodo->next;
 			while(nodo != NULL){
 				printf(" + ");
 				printf("x0%d0%d", c[i].mainCityId, nodo->cityId);
 				nodo = nodo->next;
 			}
 		}

 		printf(";\n"); 		 
 	}

 	printf("\n");
}

/* Gera equações de desigualdades entre as rotas e os pacotes */
void packagesInnequalities(routes_t *r, package_t *p, unsigned int k, unsigned int m, unsigned int q){
	for(unsigned int i=0; i < k; ++i){
 		
 		for(unsigned int j = 0; j < m - 1; ++j){
 			printf("%dy0%d0%d + %dz0%d0%d + ", r[j].resources[i], r[j].startPoint, r[j].endPoint, r[j].resources[i], r[j].startPoint, r[j].endPoint);
 		}
 		printf("%dy0%d0%d + %dz0%d0%d", r[m-1].resources[i], r[m-1].startPoint, r[m-1].endPoint,  r[m-1].resources[i], r[m-1].startPoint, r[m-1].endPoint);
 		
 		printf(" <= ");

 		for(unsigned int j = 0; j < q - 1; ++j){
 			printf("%dq0%d + ", p[j].resources[i], j+1);
 		}
 		printf("%dq0%d;", p[q-1].resources[i], q);

 		printf("\n");
 	}
 	printf("\n");
}

/* Gera as equações para linearização dos módulos */
void absoluteValuesEquations(routes_t *r, unsigned int m){

		for(unsigned int i=0; i < m; ++i){
 		printf("y0%d0%d - z0%d0%d = x0%d0%d;\n", r[i].startPoint, r[i].endPoint, r[i].startPoint, r[i].endPoint, r[i].startPoint, r[i].endPoint);

 	}
 	printf("\n");
}

/* Gera as limitações das váriavies */
void varibleLimitations(routes_t *r, unsigned int m, unsigned int q){

	for(unsigned int i=0; i < m; ++i){
 		printf("y0%d0%d >= 0;\n", r[i].startPoint, r[i].endPoint);
 		printf("z0%d0%d >= 0;\n", r[i].startPoint, r[i].endPoint);
 	}

 	for(unsigned int i=0; i < q; ++i){
 		printf("q0%d >= 0;\n", i+1);
 	}

 	printf("\n");
}

int main(int argc, char const *argv[])
{

 	unsigned int n;
 	unsigned int m;
 	unsigned int k;
 	unsigned int q; 
 	unsigned int p; 
 	routes_t *routes;
 	package_t *packages;

 	scanf("%d\n", &n);
 	scanf("%d\n", &m);
 	scanf("%d\n", &k);
 	scanf("%d\n", &q);
 	scanf("%d\n", &p);

 	routes   = allocRoutesVector(m);
 	packages = allocPackagesVector(q);

 	unsigned int startPoint;
 	unsigned int endPoint;
 	unsigned int capacity;
 	unsigned int *v;
 	unsigned int resource;

 	/* Aloca o vetor de rotas e seus respectivos valores */ 
 	for(unsigned int i = 0; i < m; i++){
 		scanf("%d\n", &startPoint);
 		scanf("%d\n", &endPoint);
 		scanf("%d\n", &capacity);

 		v = allocUnsignedIntVector(k);
 		for(unsigned int j = 0; j < k; j++){
 			scanf("%d\n", &resource);
 			v[j] = resource;
 		}

 		routes[i].startPoint = startPoint;
 		routes[i].endPoint 	= endPoint;
 		routes[i].capacity   = capacity;
 		routes[i].resources  = v;
 	}

 	unsigned int *r;
 	unsigned int price;
 	
 	/* Aloca o vetor de pacotes e seus respectivos valores */ 
 	for(unsigned int i = 0; i < q; i++){
 		scanf("%d\n", &price);

 		r = allocUnsignedIntVector(k);
 		for(unsigned int j = 0; j < k; j++){
 			scanf("%d\n", &resource);
 			r[j] = resource;
 		}

 		packages[i].price 	 = price;
 		packages[i].resources = r;

 	}

 	cityConnections_t *cities;

 	/* Não alocaremos valores da lista para a cidade final */
 	cities = allocCityConnectionsVector(n-1);

 	/* Criação das conexões de cidades*/
 	for(unsigned int i=0; i < n-1; i++){
 		
 		/* Porque estamos pulando 2 cidades a primeira (0) e a última (n-1)*/
 		/* Estamos dizendo que o id da cidade dessa lista é o próprio valor i*/
 		cities[i].mainCityId = i+1; 
 		cities[i].entrances  = allocCityList();
		cities[i].exits      = allocCityList();

		for(unsigned int j=0; j < m; j++){

			if(routes[j].startPoint == cities[i].mainCityId){
				insertEndList(cities[i].exits, routes[j].endPoint);
			}
			
			if(routes[j].endPoint == cities[i].mainCityId){
				insertEndList(cities[i].entrances, routes[j].startPoint);
			}

		} 

 	}

 	maximizationEquation(cities,packages, q, p);

 	routesIntervals(routes, m);

 	routesEquations(cities, n);

 	packagesInnequalities(routes, packages, k, m, q);

 	absoluteValuesEquations(routes, m);

 	varibleLimitations(routes, m, q);

 	destroyCityConnectionsVector(cities, n-1);

 	destroyRoutesVector(routes, m);
 	
 	destroyPackagesVector(packages, q);

	return 0;
}