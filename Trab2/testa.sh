#!/bin/bash

count=0

if [ -d "resultados" ]; then
	rm -r resultados
fi

mkdir resultados
lista=$(ls -v testes/t*.txt)

for t in $lista; do	
	echo "Funcao Padrao"
	echo "Funcao Padrao" >> "res${count}.txt" 
	./comissao < "$t" >> "res${count}.txt"
	echo "" >> "res${count}.txt"
	echo "Funcao PSCV ${count}"
	echo "Função Padrao Sem corte de viabilidade" >> "res${count}.txt"
	./comissao -f < "$t" >> "res${count}.txt"
        echo "" >> "res${count}.txt"
	echo "Funcao PF"
	echo "Funcao Professor" >>  "res${count}.txt"
	./comissao -a < "$t" >> "res${count}.txt"
        echo "" >> "res${count}.txt"
	echo "Funcao PFSCV"
	echo "Funcao Professor sem corte de viabilidade" >> "res${count}.txt" 
    	./comissao -a -f < "$t" >> "res${count}.txt" 
        echo "" >> "res${count}.txt"
	echo "Funcao SCO"
	echo "Funcao sem corte de otimalidade" >> "res${count}.txt" 
        ./comissao -o < "$t" >> "res${count}.txt"
        echo "" >> "res${count}.txt"	
	echo "Funcao N"
	echo "Funcao normal" >> "res${count}.txt"
 	./comissao -o -f < "$t" >> "res${count}.txt"
        echo "" >> "res${count}.txt"

	mv "res${count}.txt" resultados	
    	count=$((count + 1))
done
		
