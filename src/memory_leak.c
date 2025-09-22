// Salve como: src/memory_leak_apresentacao.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Para a função sleep()

// --- PARÂMETROS DA DEMONSTRAÇÃO (fácil de alterar) ---
#define MB_POR_ALOCACAO 20 // Quantos MB vazar a cada passo
#define NUMERO_DE_ALOCACOES 15 // Quantas vezes vazar
#define INTERVALO_SEGUNDOS 1 // Pausa entre cada vazamento
// --- FIM DOS PARÂMETROS ---

int main() {
    long total_alocado = 0;
    
    printf("--- DEMONSTRACAO DE MEMORY LEAK PARA APRESENTACAO ---\n");
    printf("Objetivo: Alocar %d MB, %d vezes, a cada %d segundo(s).\n", MB_POR_ALOCACAO, NUMERO_DE_ALOCACOES, INTERVALO_SEGUNDOS);
    printf("Total a vazar: %d MB.\n", MB_POR_ALOCACAO * NUMERO_DE_ALOCACOES);
    printf("Por favor, inicie seu monitor de sistema (htop ou docker stats) agora.\n");
    printf("Pressione Enter para comecar...\n");
    getchar();

    // Loop principal do vazamento
    for (int i = 1; i <= NUMERO_DE_ALOCACOES; i++) {
        long bytes_a_alocar = MB_POR_ALOCACAO * 1024 * 1024;
        
        void *memoria = malloc(bytes_a_alocar);

        if (memoria == NULL) {
            printf("FALHA AO ALOCAR! O sistema ficou sem memoria.\n");
            exit(1);
        }
        
        // Preenche a memória para garantir que o SO a considere "em uso".
        memset(memoria, 0, bytes_a_alocar);
        
        // O ERRO INTENCIONAL: a chamada para free(memoria) está ausente.
        
        total_alocado += bytes_a_alocar;
        printf("Bloco #%d/%d alocado. Total vazado: %ld MB\n", i, NUMERO_DE_ALOCACOES, total_alocado / (1024 * 1024));
        fflush(stdout); // Garante que a mensagem seja impressa imediatamente

        sleep(INTERVALO_SEGUNDOS);
    }

    printf("\n--- VAZAMENTO CONCLUIDO! ---\n");
    printf("A memoria esta em seu pico de uso. O programa esta pausado.\n");
    printf("Mostre o resultado no seu monitor de sistema agora.\n");
    printf("\n>>> Pressione Enter para finalizar o programa e liberar a memoria. <<<\n");
    
    // PAUSA CLÍMAX: O programa para aqui, mantendo a memória alocada.
    getchar();

    printf("Programa finalizado. O SO ira recuperar toda a memoria vazada.\n");
    return 0;
}