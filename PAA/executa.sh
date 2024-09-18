#!/bin/bash

# Nome do arquivo de saída
OUTPUT_FILE="resultados.txt"

# Compilar o código
g++ insertionsort.cpp -o insertionsort

# Verificar se a compilação foi bem-sucedida
if [ $? -ne 0 ]; then
    echo "Erro na compilação do código."
    exit 1
fi

# Limpar o arquivo de saída
echo "" > $OUTPUT_FILE

# Executar o programa com argumentos multiplicados de 10 em 10
for ((i=10; i<=1000000000; i*=10)); do
    ./insertionsort $i >> $OUTPUT_FILE
done

echo "Execuções concluídas. Resultados salvos em $OUTPUT_FILE."