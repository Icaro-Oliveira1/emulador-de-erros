#!/bin/bash

# Diretório onde os executáveis estão
BIN_DIR="bin"

# Verifica se um argumento foi passado
if [ -z "$1" ]; then
    echo "Uso: $0 <tipo_de_erro>"
    echo "Tipos disponíveis: stack_overflow, segmentation_fault, buffer_overflow, memory_leak, race_condition, deadlock"
    exit 1
fi

# Pega o nome do erro do primeiro argumento
ERROR_TYPE=$1
EXECUTABLE="$BIN_DIR/$ERROR_TYPE"

# Verifica se o programa compilado para aquele erro existe
if [ ! -f "$EXECUTABLE" ]; then
    echo "Erro: Executável para '$ERROR_TYPE' não encontrado."
    echo "Você compilou o projeto com 'make'?"
    echo "Arquivos disponíveis em $BIN_DIR:"
    ls -la "$BIN_DIR/" 2>/dev/null || echo "Diretório $BIN_DIR não encontrado"
    exit 1
fi

# Verifica se o executável tem permissão de execução
if [ ! -x "$EXECUTABLE" ]; then
    echo "Dando permissão de execução para $EXECUTABLE"
    chmod +x "$EXECUTABLE"
fi

# Executa o programa correspondente
echo "--- Emulando Erro: $ERROR_TYPE ---"
echo "Executando: $EXECUTABLE"
"$EXECUTABLE"
echo "--- Execução Concluída ---"