#include <stdio.h>
#include <stdlib.h>
#define START 1

typedef struct routes{
	unsigned int startPoint;
	unsigned int endPoint;
	unsigned int capacity; //Float?
	unsigned int *resources;
}routes_t;

typedef struct package{
	float price;
	unsigned int *resources;
}package_t;

typedef struct cityNode{
	unsigned int cityId;
	struct cityNode *next;
}cityNode;

typedef struct cityList{
	cityNode *start;
	cityNode *end; 
}cityList_t;

typedef struct cityConnections{
	unsigned int mainCityId;
	cityList_t *entrances;
	cityList_t *exits; 
}cityConnections_t;


routes_t *allocRoutesVector(unsigned int size){
	routes_t *x;

	x = malloc(sizeof(routes_t)*size);

	if(!x)
		return NULL;
	return x;
}

package_t *allocPackagesVector(unsigned int size){
	package_t *x;

	x = malloc(sizeof(package_t)*size);

	if(!x)
		return NULL;
	return x;
}

cityConnections_t *allocCityConnectionsVector(unsigned int size){
	cityConnections_t *x;

	x = malloc(sizeof(cityConnections_t)*size);

	if(!x)
		return NULL;
	return x;
}

cityList_t *allocCityList(){
	cityList_t *x;

	x = malloc(sizeof(cityList_t));

	if(!x)
		return NULL;

	x->start      = NULL;
	x->end        = NULL;

	return x;
}
 

cityNode *allocCityNode(unsigned int cityId){
	cityNode *x;

	x = malloc(sizeof(cityNode));

	if(!x)
		return NULL;

	x->cityId = cityId;
	x->next   = NULL;

	return x;
}

void insertEndList(cityList_t *l, unsigned int id){
	cityNode *n, *aux;

	n = allocCityNode(id);

	if(l->start == NULL){
		l->start = n;
		l->end = n;
		return;
	}

	aux = l->end;
	aux->next = n;

	l->end = n;

	return;
}


void printCityList(cityList_t *l){
	cityNode *n;

	n = l->start;

	if(n == NULL){
		printf("NULL\n");
	}

	while(n != NULL){
		printf("-city: %d\n", n->cityId);
		n = n->next;
	}

	return;
}

unsigned int *allocUnsignedIntVector(unsigned int size){
	unsigned int *x;

	x = malloc(sizeof(unsigned int)*size);

	if(!x)
		return NULL;
	return x;
}


int main(int argc, char const *argv[])
{

 	unsigned int n;
 	unsigned int m;
 	unsigned int k;
 	unsigned int q; 
 	float p; 
 	routes_t *routes;
 	package_t *packages;

 	scanf("%d\n", &n);
 	scanf("%d\n", &m);
 	scanf("%d\n", &k);
 	scanf("%d\n", &q);
 	scanf("%f\n", &p);

 	routes   = allocRoutesVector(m);
 	packages = allocPackagesVector(q);

 	unsigned int startPoint;
 	unsigned int endPoint;
 	unsigned int capacity;
 	unsigned int *v;
 	unsigned int resource;

 	for(int i = 0; i < m; i++){
 		scanf("%d\n", &startPoint);
 		scanf("%d\n", &endPoint);
 		scanf("%d\n", &capacity);

 		v = allocUnsignedIntVector(k);
 		for(int j = 0; j < k; j++){
 			scanf("%d\n", &resource);
 			v[j] = resource;
 		}

 		routes[i].startPoint = startPoint;
 		routes[i].endPoint 	= endPoint;
 		routes[i].capacity   = capacity;
 		routes[i].resources  = v;
 	}

 	float price;
 	unsigned int *r;
 	
 	for(int i = 0; i < q; i++){
 		scanf("%f\n", &price);

 		r = allocUnsignedIntVector(k);
 		for(int j = 0; j < k; j++){
 			scanf("%d\n", &resource);
 			r[j] = resource;
 		}

 		packages[i].price 	  = price;
 		packages[i].resources = r;

 	}

 	printf(" n = %d\n m = %d\n k = %d\n q = %d\n p = %f\n", n, m, k , q, p);

 	for(int i = 0; i < m; i++){

 		printf(" %d %d %d ", routes[i].startPoint, routes[i].endPoint, routes[i].capacity);
		for(int j = 0; j < k; j++){
			printf("%d ", routes[i].resources[j]);
		} 		
		printf("\n");
 	}

 	for(int i = 0; i < q; i++){
 		printf(" %.2f ", packages[i].price);
		for(int j = 0; j < k; j++){
			printf("%d ", packages[i].resources[j]);
		} 		
		printf("\n");
 	}
	printf("\n");

 	cityConnections_t *cities;

 	/* Não alocaremos valores da lista para a cidade final */
 	cities = allocCityConnectionsVector(n-1);

 	for(int i=0; i < n-1; i++){
 		
 		/* Porque estamos pulando 2 cidades a primeira (0) e a última (n-1)*/
 		/* Estamos dizendo que o id da cidade dessa lista é o próprio valor i*/
 		cities[i].mainCityId = i+1; 
 		cities[i].entrances  = allocCityList();
		cities[i].exits      = allocCityList();

		for(int j=0; j < m; j++){

			if(routes[j].startPoint == cities[i].mainCityId){
				insertEndList(cities[i].exits, routes[j].endPoint);
			}
			
			if(routes[j].endPoint == cities[i].mainCityId){
				insertEndList(cities[i].entrances, routes[j].startPoint);
			}

		} 

 	}

 	/*PERGUNTAR SE AS ROTAS ESTARÃO SEMPRE EM ORDEM*/
  	cityNode *nodo;
	nodo = cities[0].exits->start;

 	printf("max:");
 	printf("%.2fx0%d0%d", p , START, nodo->cityId);
	nodo = nodo->next;
	while(nodo != NULL){
 		printf(" + ");
		printf("%.2fx0%d0%d", p , START, nodo->cityId);

 		nodo = nodo->next;

 	}

	printf(" - %.2fq0%d", packages[0].price , 1);
 	for(int i = 1; i < q; ++i){
 		printf(" - ");
		printf("%.2fq0%d", packages[i].price , i+1);
 	}
 	printf(";\n");
 	printf("\n");


 	//Gera desigualdades referentes as capacidades da rota e seus fluxos//
 	for(int i=0; i < m; i++){
 		printf("-%d <= x0%d0%d <= %d;\n", routes[i].capacity, routes[i].startPoint, routes[i].endPoint, routes[i].capacity);
 	}
 	printf("\n");

 	/* Gera equações Das rotas */
 	/* Pulamos a cidade 1 por que sua equação é dada pelas outras cidades */
 	for(int i=1; i < n-1; i++){
 		
 		nodo = cities[i].entrances->start;

 		printf("x0%d0%d", nodo->cityId, cities[i].mainCityId);
 		nodo = nodo->next;
 		while(nodo != NULL){
 			printf(" + ");
 			printf("x0%d0%d", nodo->cityId, cities[i].mainCityId);
 			nodo = nodo->next;
 		}
 		printf(" = ");

 		nodo = cities[i].exits->start;

 		printf("x0%d0%d", cities[i].mainCityId, nodo->cityId);
 		nodo = nodo->next;
 		while(nodo != NULL){
 			printf(" + ");
 			printf("x0%d0%d", cities[i].mainCityId, nodo->cityId);
 			nodo = nodo->next;
 		}
 		printf(";\n");
 	}
 	printf("\n");

 	for(int i=0; i < k; ++i){
 		
 		for(int j = 0; j < m - 1; ++j){
 			printf("%dy0%d0%d + %dz0%d0%d + ", routes[j].resources[i], routes[j].startPoint, routes[j].endPoint,  routes[j].resources[i], routes[j].startPoint, routes[j].endPoint);
 		}
 		printf("%dy0%d0%d + %dz0%d0%d", routes[m-1].resources[i], routes[m-1].startPoint, routes[m-1].endPoint,  routes[m-1].resources[i], routes[m-1].startPoint, routes[m-1].endPoint);
 		
 		printf(" <= ");

 		for(int j = 0; j < q - 1; ++j){
 			printf("%dq0%d + ", packages[j].resources[i], j+1);
 		}
 		printf("%dq0%d;", packages[q-1].resources[i], q);

 		printf("\n");
 	}
 	printf("\n");

 	for(int i=0; i < m; ++i){
 		printf("y0%d0%d - z0%d0%d = x0%d0%d;\n", routes[i].startPoint, routes[i].endPoint, routes[i].startPoint, routes[i].endPoint, routes[i].startPoint, routes[i].endPoint);

 	}
 	printf("\n");

 	for(int i=0; i < m; ++i){
 		printf("y0%d0%d >= 0;\n", routes[i].startPoint, routes[i].endPoint);
 		printf("z0%d0%d >= 0;\n", routes[i].startPoint, routes[i].endPoint);
 	}

 	for(int i=0; i < q; ++i){
 		printf("q0%d >= 0;\n", i+1);
 	}


 	/*for(int i=0; i < n - 1; ++i){
 		printf("city: %d\n", cities[i].mainCityId);
 		printf("entrances:\n");
 		printCityList(cities[i].entrances);
 		printf("exits:\n");
 		printCityList(cities[i].exits);
 		printf("\n\n");
 	}*/




	return 0;
}

/* Estrutura de dados que representa uma rota entre 2 cidades */
/* Possui 2 inteiros que indicam a cidade de partida e de chegada, um inteiro que 
representa a capacidade de transporte da rota e um array de inteiros que representa 
os recursos onde, para cada elemento i do array, se tem a informação da quantidade de 
recurso do tipo i+1 requerido na rota */
typedef struct routes{
	unsigned int startPoint;
	unsigned int endPoint;
	unsigned int capacity; 
	unsigned int *resources;
}routes_t;

/* Estrutura de daso que representa um pacote de recursos */
/* Possui preços e um array de recursos, onde, para cada elemento i do array, se tem a informação
da quantidade de recursos do tipo i+1 que o pacote possui */
typedef struct package{
	unsigned int price;
	unsigned int *resources;
}package_t;

/* Nodo da lista de cidades */
/* Possui o id da cidade em cityId e um ponteiro para o próximo nodo da lista */
typedef struct cityNode{
	unsigned int cityId;
	struct cityNode *next;
}cityNode;

/* Estrutura de Dados que representa uma lista de cidades */
/* Possui um nodo de ínicio e um de fim */
typedef struct cityList{
	cityNode *start;
	cityNode *end; 
}cityList_t;

/* Estrutura de Dados que serve para mostrar as conexões que a cidade de id mainCityID */ 
/* Possui duas listas: uma para cidades que entram e outra para as que saem */
typedef struct cityConnections{
	unsigned int mainCityId;
	cityList_t *entrances;
	cityList_t *exits; 
}cityConnections_t;

/* Aloca um vetor de tamanho "size" do tipo routes_t */
/* Retorna NULL em caso de erro */
routes_t *allocRoutesVector(unsigned int size){
	routes_t *x;

	x = malloc(sizeof(routes_t)*size);

	if(!x)
		return NULL;
	return x;
}

/* Aloca um vetor de tamanho "size" do tipo packages_t */
/* Retorna NULL em caso de erro */

package_t *allocPackagesVector(unsigned int size){
	package_t *x;

	x = malloc(sizeof(package_t)*size);

	if(!x)
		return NULL;
	return x;
}

/* Aloca um vetor de tamanho "size" do tipo cityConnections_t */
/* Retorna NULL em caso de erro */
cityConnections_t *allocCityConnectionsVector(unsigned int size){
	cityConnections_t *x;

	x = malloc(sizeof(cityConnections_t)*size);

	if(!x)
		return NULL;
	return x;
}

/* Aloca uma lista de cidades do tipo cityList_t */
/* Retorna NULL em caso de erro */
cityList_t *allocCityList(){
	cityList_t *x;

	x = malloc(sizeof(cityList_t));

	if(!x)
		return NULL;

	x->start      = NULL;
	x->end        = NULL;

	return x;
}
 
/* Aloca um nodo do tipo cityNode_t e que possui o id dado pelo paramêtro cityID*/
/* Retorna NULL em caso de erro */
cityNode *allocCityNode(unsigned int cityId){
	cityNode *x;

	x = malloc(sizeof(cityNode));

	if(!x)
		return NULL;

	x->cityId = cityId;
	x->next   = NULL;

	return x;
}

/* Insere o id representado pelo paramêtro id na lista de cidadades 
   representado pelo paramêtro l do tipo cityList_t */
void insertEndList(cityList_t *l, unsigned int id){
	cityNode *n, *aux;

	n = allocCityNode(id);

	if(l->start == NULL){
		l->start = n;
		l->end = n;
		return;
	}

	aux = l->end;
	aux->next = n;

	l->end = n;

	return;
}
;

void destroyList(cityList_t *l){
	cityNode *n, *aux; 

	n = l->start;

	while(n != NULL){
		aux = n;
		n = n->next; 
		free(aux);
	}

	free(l);
}

void destroyCityConnections(cityConnections_t c){
	cityList_t *l; 

	l = c.entrances; 
	destroyList(l); 

	l = c.exits;
	destroyList(l); 
}

void destroyRoutesVector(routes_t *v, unsigned int size){

	for(unsigned int i=0; i < size; i++){
		free(v[i].resources);
	}

	free(v);
}

void destroyPackagesVector(package_t *v, unsigned int size){

	for(unsigned int i=0; i < size; i++){
		free(v[i].resources);
	}

	free(v);
}

void destroyCityConnectionsVector(cityConnections_t *v, unsigned int size){

	for(unsigned int i=0; i < size; ++i){
		destroyCityConnections(v[i]);
	}

	free(v);
}


void printCityList(cityList_t *l){
	cityNode *n;

	n = l->start;

	if(n == NULL){
		printf("NULL\n");
	}

	while(n != NULL){
		printf("-city: %d\n", n->cityId);
		n = n->next;
	}
}
/* Aloca um vetor de tamanho size do tipo unsigned int */
/* Retorna NULL em caso de erro */
unsigned int *allocUnsignedIntVector(unsigned int size){
	unsigned int *x;

	x = malloc(sizeof(unsigned int)*size);

	if(!x)
		return NULL;
	return x;
}
