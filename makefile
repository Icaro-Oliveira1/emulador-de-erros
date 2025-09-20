# Compilador a ser usado (gcc para C, g++ para C++)
CC=gcc
# Diretório dos fontes
SRC_DIR=src
# Diretório dos executáveis
BIN_DIR=bin
# Flags de compilação. -pthread é essencial para race condition e deadlock.
CFLAGS=-Wall -pthread -fno-stack-protector


# Encontra todos os arquivos .c no diretório de fontes
SOURCES=$(wildcard $(SRC_DIR)/*.c)
# Gera o nome dos executáveis correspondentes no diretório bin
TARGETS=$(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%, $(SOURCES))

# Regra principal: compila tudo
all: $(TARGETS)

# Regra para criar cada executável
$(BIN_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(BIN_DIR) # Cria o diretório bin se não existir
	$(CC) $(CFLAGS) $< -o $@

# Regra para limpar os arquivos compilados
clean:
	rm -rf $(BIN_DIR)