#include "cityNetwork.h"
#include <stdio.h>
#include <stdlib.h>

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

unsigned int *allocUnsignedIntVector(unsigned int size){
	unsigned int *x;

	x = malloc(sizeof(unsigned int)*size);

	if(!x)
		return NULL;
	return x;
}