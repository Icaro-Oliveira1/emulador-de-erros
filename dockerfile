# --- ESTÁGIO 1: A Oficina de Compilação (Builder) ---
FROM gcc:latest AS builder

WORKDIR /app

# Copia tudo (código fonte, Makefile, etc.)
COPY . .

# Roda o "make", que irá compilar tudo e criar a pasta "bin" com os executáveis.
RUN make

# --- ESTÁGIO 2: A Imagem Final de Produção ---
FROM debian:bookworm-slim

WORKDIR /app

# Instala dependências necessárias
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    bash \
    && rm -rf /var/lib/apt/lists/*

# Copiamos a pasta "bin" inteira e o script "emulador.sh"
COPY --from=builder /app/bin ./bin
COPY --from=builder /app/emulador.sh .

# Dá permissão de execução para o script e todos os executáveis
RUN chmod +x ./emulador.sh && \
    chmod +x ./bin/*

# Define o nosso script como o ponto de entrada do container.
ENTRYPOINT ["bash", "./emulador.sh"]