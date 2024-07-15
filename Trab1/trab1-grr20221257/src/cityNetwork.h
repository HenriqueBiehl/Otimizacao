
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
routes_t *allocRoutesVector(unsigned int size);

/* Aloca um vetor de tamanho "size" do tipo packages_t */
/* Retorna NULL em caso de erro */

package_t *allocPackagesVector(unsigned int size);

/* Aloca um vetor de tamanho "size" do tipo cityConnections_t */
/* Retorna NULL em caso de erro */
cityConnections_t *allocCityConnectionsVector(unsigned int size);


/* Aloca uma lista de cidades do tipo cityList_t */
/* Retorna NULL em caso de erro */
cityList_t *allocCityList();
 
/* Aloca um nodo do tipo cityNode_t e que possui o id dado pelo paramêtro cityID*/
/* Retorna NULL em caso de erro */
cityNode *allocCityNode(unsigned int cityId);

/* Insere o id representado pelo paramêtro id na lista de cidadades 
   representado pelo paramêtro l do tipo cityList_t */
void insertEndList(cityList_t *l, unsigned int id);

/* Recebe uma lista de cidades do tipo cityList_t e destrói a lista, desalocando 
todos os nodos */
void destroyList(cityList_t *l);

/* Recebe uma conexão de cidades do tipo cityConnections_t e destrói as listas associdas*/
void destroyCityConnections(cityConnections_t c);

/* Recebe um vetor de rotas do tipo routes_t e tamanho size e o desaloca, liberando também
	os vetores de recursos associados a ele*/
void destroyRoutesVector(routes_t *v, unsigned int size);

/* Recebe um vetor de rotas do tipo packages_t e tamanho size e o desaloca, liberando também
	os vetores de recursos associados a ele*/
void destroyPackagesVector(package_t *v, unsigned int size);

/* Recebe um vetor de conexoes de cidade do tipo cityConnections_t e tamanho size e o desaloca, liberando também
	os as listas de cidade cada associadas a cada conexão do vetor*/
void destroyCityConnectionsVector(cityConnections_t *v, unsigned int size);

/* Aloca um vetor de tamanho size do tipo unsigned int */
/* Retorna NULL em caso de erro */
unsigned int *allocUnsignedIntVector(unsigned int size);