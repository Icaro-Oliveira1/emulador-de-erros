// Salve como: src/memory_leak_visual.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Para a função sleep()

// Define quantos bytes vamos alocar a cada iteração. 10 MB.
#define TAMANHO_ALOCACAO (10 * 1024 * 1024)

int main() {
    long total_alocado = 0;
    int i = 1;

    printf("--- DEMONSTRACAO DE VAZAMENTO DE MEMORIA (MEMORY LEAK) ---\n");
    printf("A cada segundo, este programa alocara %d MB de memoria sem libera-la.\n", TAMANHO_ALOCACAO / (1024 * 1024));
    printf("Use o comando 'docker stats' em outro terminal para observar o consumo de memoria deste container crescer.\n");
    printf("------------------------------------------------------------------\n");
    fflush(stdout);

    // Loop infinito para alocar memória continuamente.
    while (1) {
        // 1. Solicitamos um grande bloco de memória ao SO.
        void *memoria = malloc(TAMANHO_ALOCACAO);

        if (memoria == NULL) {
            // Se malloc retorna NULL, significa que o sistema não tem mais
            // memória disponível para nos dar.
            printf("FALHA AO ALOCAR! O sistema (ou o container) ficou sem memoria apos vazar %ld MB.\n", total_alocado / (1024*1024));
            // O OOM (Out Of Memory) Killer do Linux provavelmente encerrará o processo em breve.
            exit(1);
        }

        // 2. Preenchemos a memória para garantir que o SO realmente a aloque.
        memset(memoria, 0, TAMANHO_ALOCACAO);

        // 3. O ERRO: Esquecemos de chamar free(memoria);
        // Em um programa correto, a linha "free(memoria);" estaria aqui.
        // Sem ela, a cada loop, perdemos a referência ao bloco anterior,
        // criando um vazamento.

        total_alocado += TAMANHO_ALOCACAO;
        printf("Bloco #%d alocado. Total vazado: %ld MB\n", i++, total_alocado / (1024 * 1024));
        fflush(stdout);

        sleep(1); // Pausa de 1 segundo para que possamos observar o crescimento.
    }

    return 0;
}