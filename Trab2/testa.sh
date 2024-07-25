#!/bin/bash

count=0

pasta=$1

if [ ! -f comissao ]; then 
	make 
fi

if [ -d "resultados" ]; then
	rm -r resultados
fi

mkdir resultados
lista=$(ls -v $pasta/*)

for t in $lista; do	
	echo "Funcao Padrao" >> "res${count}.txt" 
	./comissao < "$t" >> "res${count}.txt" 2>&1
	echo "" >> "res${count}.txt"
	echo "Função Padrao Sem corte de viabilidade" >> "res${count}.txt"
	./comissao -f < "$t" >> "res${count}.txt" 2>&1
        echo "" >> "res${count}.txt" 
	echo "Funcao Professor" >>  "res${count}.txt"
	./comissao -a < "$t" >> "res${count}.txt" 2>&1
        echo "" >> "res${count}.txt"
	echo "Funcao Professor sem corte de viabilidade" >> "res${count}.txt" 
    	./comissao -a -f < "$t" >> "res${count}.txt" 2>&1
        echo "" >> "res${count}.txt"
	echo "Funcao sem corte de otimalidade" >> "res${count}.txt" 
        ./comissao -o < "$t" >> "res${count}.txt" 2>&1
        echo "" >> "res${count}.txt"	
	echo "Funcao normal" >> "res${count}.txt" 
 	./comissao -o -f < "$t" >> "res${count}.txt" 2>&1
    echo "" >> "res${count}.txt"

	mv "res${count}.txt" resultados	
    	count=$((count + 1))
done

make clean
