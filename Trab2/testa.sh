#!/bin/bash

count=0

if [ ! -d "resultados" ]; then
	mkdir resultados
fi

for t in testes/t*.txt; do	
	echo "Funcao Padrao" >> "res${count}.txt" 
	./main < "$t" >> "res${count}.txt"
	echo "" >> "res${count}.txt"
	echo "Função Padrao Sem corte de viabilidade" >> "res${count}.txt"
	./main -f < "$t" >> "res${count}.txt"
        echo "" >> "res${count}.txt"
	echo "Funcao Professor\n" >>  "res${count}.txt"
	./main -a < "$t" >> "res${count}.txt"
        echo "" >> "res${count}.txt"
	echo "Funcao Professor sem corte de viabilidade" >> "res${count}.txt" 
    	./main -a -f < "$t" >> "res${count}.txt" 
        echo "" >> "res${count}.txt"
	echo "Funcao sem corte de otimalidade" >> "res${count}.txt" 
        ./main -o < "$t" >> "res${count}.txt"
        echo "" >> "res${count}.txt"	
	echo "Funcao normal" >> "res${count}.txt"
 	./main -o -f < "$t" >> "res${count}.txt"
        echo "" >> "res${count}.txt"

	mv "res${count}.txt" resultados	
    	count=$((count + 1))
done
		
