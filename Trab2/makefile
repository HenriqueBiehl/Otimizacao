CFLAGS=-std=c2x -g -Wall 

OBJECTS=lib_comissao.o

comissao: main.c lib_comissao.o
	gcc lib_comissao.o main.c -o comissao $(CFLAGS)

lib_comissao.o: lib_comissao.c 
	gcc -c lib_comissao.c -o lib_comissao.o $(CFLAGS)

clean:
	rm -rf comissao lib_comissao.o