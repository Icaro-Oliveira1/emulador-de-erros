# Emulador de Erros de Execução

## Sobre o Projeto

Este projeto,é um emulador projetado para simular e analisar uma variedade de erros comuns de execução em programas C. O objetivo principal é criar um ambiente seguro e isolado, utilizando containers Docker, para deliberadamente provocar falhas como `Segmentation Fault`, `Buffer Overflow`, `Memory Leak` e etc.

Através desta ferramenta, é possível observar na prática como o Sistema Operacional lida com processos que se comportam mal, gerenciando a memória e aplicando mecanismos de proteção para garantir a estabilidade do sistema, além de observar também como funciona o gerenciamento de threads e processos

## Tecnologias Utilizadas

- **Linguagem:** C
- **Containerização:** Docker
- **Automação de Build:** Makefile
- **Interface:** Shell Script (Bash)
- **CI/CD:** GitHub Actions

## Pré-requisitos

Para executar este projeto, você precisará ter as seguintes ferramentas instaladas em seu ambiente:

- **Git:** Para clonar o repositório.
- **Docker:** Essencial para construir e executar o projeto no ambiente de container isolado.
- **Shell Script(WSL caso use windows)** Para Executar os comandos.
- **GCC e Make:** Necessários apenas se você desejar compilar e executar o projeto localmente, fora de um container.
- **Valgrind (Opcional):** Necessário apenas para a análise avançada de memória se executando **localmente**.

## Como Usar

Primeiro, clone o repositório para sua máquina local:

````bash
git clone [https://github.com/Icaro-Oliveira1/emulador-de-erros.git](https://github.com/Icaro-Oliveira1/emulador-de-erros.git)
cd emulador-de-erros

# Primeiro, compilamos tudo de uma vez com o Makefile

    make

# Depois, executamos o emulador para um erro específico

    bash emulador.sh stack_overflow
    bash emulador.sh deadlock
    bash emulador.sh memory_leak
    bash emulador.sh buffer_overflow
    bash emulador.sh race_condition
    bash emulador.sh segmentation_fault


Para executar localmente com docker

1. **Construir a imagem:**
   ```bash
   docker build -t emulador-local .
````

2. **Executar um cenário direto pelo emulador:**
   ```bash
   docker run --rm emulador-local "TIPO_DE_ERRO"
   ```
   Erros disponiveis: stack_overflow ,deadlock ,memory_leak,buffer_overflow,race_condition,segmentation_fault
3. **Abrir um shell no container (opcional):**
   ```bash
   docker run --rm -it --entrypoint /bin/bash emulador-local
   ./bin/stack_overflow
   ```
   Útil quando você quer rodar os binários manualmente e observar mensagens como `Segmentation fault` direto no terminal.

Responsabilidades do desenvolvimento:

Arquitetura, github actions , docker, demonstração stack_overflow : Erik Freire Ramos
Demonstração deadlock e race_condition: Mateus Fonseca
Demonstração buffer_overflow, segmentation fault , memory leak , core dumped: Icaro Oliveira
