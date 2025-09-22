FROM gcc:latest AS builder

WORKDIR /app

COPY . .

RUN make

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