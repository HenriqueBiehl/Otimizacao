parametrosCompilacao=-Wall -g  #-Wshadow
compiler=-std=c2x
nomePrograma=transporte

all: $(nomePrograma)

$(nomePrograma): main.o cityNetwork.o
	gcc -o $(nomePrograma) main.o cityNetwork.o $(parametrosCompilacao)

main.o: ./src/main.c
	gcc -c ./src/main.c $(parametrosCompilacao)

cityNetwork.o: ./src/cityNetwork.h ./src/cityNetwork.c
	gcc -c ./src/cityNetwork.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)
