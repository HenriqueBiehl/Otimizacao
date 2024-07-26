CFLAGS=-std=c2x -g -Wall 

OBJECTS=lib_lista.o

comissao: main.c lib_lista.o
	gcc lib_lista.o main.c -o comissao $(CFLAGS)

lib_lista.o: lib_lista.c 
	gcc -c lib_lista.c -o lib_lista.o $(CFLAGS)

clean:
	rm -rf comissao lib_lista.o