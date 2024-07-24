#!/bin/bash

# Número máximo de valores de l e n
MAX_L=25
MAX_N=50

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
generate_unique_random() {
    local l=$1
    local used=()
    local rand

    while true; do
        rand=$(( (RANDOM % l) + 1 ))
        if [[ ! " ${used[@]} " =~ " ${rand} " ]]; then
            used+=($rand)
            echo $rand
            return
        fi
    done
}

if [ -d "testes_script" ]; then
    rm -r testes_script
fi

mkdir testes_script

# Loop para gerar até 50 entradas para n
for (( i=1; i<=$MAX_N; i++ )); do
    n=$(generate_random_n)
    l=$(generate_random_l)
    
    # Imprime l e n
    echo "$l $n" >> "testes_script/t${i}.txt"
    
    # Loop para gerar conjuntos de números para cada n
    for (( j=1; j<=$n; j++ )); do
        # Gera um número aleatório para o tamanho do conjunto
        tam_cjt=$(generate_unique_random $l)
        
        # Gera números aleatórios únicos para o conjunto
        conjunto=""
        for (( k=1; k<=$tam_cjt; k++ )); do
            valor=$(generate_unique_random $l)
            conjunto="$conjunto ${valor}"
        done
        
        # Imprime o tamanho do conjunto e seus elementos
        echo "$tam_cjt$conjunto" >> "testes_script/t${i}.txt"
    done
done