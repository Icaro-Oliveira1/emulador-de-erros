#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <sched.h>

// Configuramos várias threads que disputam um contador compartilhado.
#define TOTAL_DE_THREADS 4
#define ITERACOES_POR_THREAD 100000

// Contador global acessado sem proteção.
static long contador_compartilhado = 0;

// Cada thread incrementa o contador, mas de forma não atômica.
static void *incrementa_sem_sincronizacao(void *arg) {
    intptr_t id = (intptr_t)arg;

    printf("[Thread %ld] Iniciando incrementos.\n", (long)id);

    for (int i = 0; i < ITERACOES_POR_THREAD; ++i) {
        long valor_lido = contador_compartilhado; // Leitura separada da escrita expõe a janela crítica.

        sched_yield(); // Cede a CPU para outra thread e maximiza o entrelaçamento.

        contador_compartilhado = valor_lido + 1; // Escreve com base em dados possivelmente desatualizados.
    }

    printf("[Thread %ld] Terminou os incrementos.\n", (long)id);
    return NULL;
}

int main(void) {
    pthread_t threads[TOTAL_DE_THREADS];
    long esperado;

    // Desabilita o buffer da stdout para mostrar os logs imediatamente.
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("--- DEMONSTRACAO DE RACE CONDITION ---\n");
    printf("Quatro threads vao tentar incrementar o mesmo contador ao mesmo tempo.\n");
    printf("Cada incremento e feito sem nenhuma forma de protecao.\n");
    printf("O resultado final deve ser %d, mas sera diferente devido a perdas de atualizacao.\n\n",
           TOTAL_DE_THREADS * ITERACOES_POR_THREAD);

    // Cria as threads.
    for (intptr_t i = 0; i < TOTAL_DE_THREADS; ++i) {
        pthread_create(&threads[i], NULL, incrementa_sem_sincronizacao, (void *)(i + 1));
    }

    // Aguarda todas as threads terminarem.
    for (int i = 0; i < TOTAL_DE_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    esperado = TOTAL_DE_THREADS * ITERACOES_POR_THREAD;
    printf("\nValor esperado sem perda de dados: %ld\n", esperado);
    printf("Valor obtido neste experimento: %ld\n", contador_compartilhado);

    if (contador_compartilhado != esperado) {
        printf("Resultado inferior ao esperado = evidencia de race condition!\n");
    } else {
        printf("Surpreendentemente bateu. Rode novamente e o valor deve variar.\n");
    }

    printf("Reexecute o programa algumas vezes para ver valores diferentes surgirem.\n");
    return 0;
}
