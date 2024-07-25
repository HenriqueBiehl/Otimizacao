#!/bin/bash

# Número máximo de valores de l e n


# Função para gerar um número aleatório entre 1 e MAX_L
generate_random_l() {
    echo $(( (RANDOM % MAX_L) + 1 ))
}

# Função para gerar um número aleatório entre 1 e MAX_N
generate_random_n() {
    echo $(( (RANDOM % MAX_N) + 1 ))
}

# Função para gerar um número aleatório único dentro do intervalo [1, $l]
# Evita repetições dentro do mesmo conjunto


if [ -d "testes_script" ]; then
    rm -r testes_script
fi

mkdir testes_script

gcc geraEntrada.c -o geraEntrada -Wall -std=c99 -g

MAX_N=$1
MAX_L=$2
for (( i=1; i<=$MAX_N; i++ )); do
    n=$(generate_random_n)
    l=$(generate_random_l)
    echo "$n $l" > temp
    ./geraEntrada < temp  > "testes_script/t${i}.txt"
done

rm temp
rm geraEntrada
