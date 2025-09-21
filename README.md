# emulador-de-erros

# Primeiro, compilamos tudo de uma vez com o Makefile

    make

# Depois, executamos o emulador para um erro específico

    bash emulador.sh stack_overflow
    bash emulador.sh deadlock
    bash emulador.sh memory_leak

# Para executar localmente com docker

1. **Construir a imagem:**
   ```bash
   docker build -t emulador-local .
   ```
2. **Executar um cenário direto pelo emulador:**
   ```bash
   docker run --rm emulador-local stack_overflow
   ```
   Substitua `stack_overflow` por `segmentation_fault`, `buffer_overflow`, `memory_leak`, `race_condition` ou `deadlock` para ver outros casos.
3. **Abrir um shell no container (opcional):**
   ```bash
   docker run --rm -it --entrypoint /bin/bash emulador-local
   ./bin/stack_overflow
   ```
   Útil quando você quer rodar os binários manualmente e observar mensagens como `Segmentation fault` direto no terminal.

# Para acessar o deployment GCP

    ssh admin@35.198.30.67
    sera pedido uma senha digite :admin
    apos isso acesse com docker exemplo:
    docker run --rm emulador-local stack_overflow
