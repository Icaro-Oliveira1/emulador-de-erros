#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Dois mutex que representam recursos compartilhados distintos.
static pthread_mutex_t recurso_a = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t recurso_b = PTHREAD_MUTEX_INITIALIZER;

// Thread 1: pega Recurso A e depois tenta pegar Recurso B.
void *tarefa_pega_a_depois_b(void *arg) {
    (void)arg; // Parâmetro não utilizado.

    printf("[Thread A] Tentando bloquear Recurso A...\n");
    pthread_mutex_lock(&recurso_a);
    printf("[Thread A] Recurso A bloqueado.\n");

    // Pausa para dar tempo da outra thread pegar o Recurso B.
    sleep(1);

    printf("[Thread A] Tentando bloquear Recurso B... (vai travar aqui)\n");
    pthread_mutex_lock(&recurso_b);

    // Estas linhas nunca são alcançadas devido ao deadlock.
    printf("[Thread A] Conseguiu Recurso B.\n");
    pthread_mutex_unlock(&recurso_b);
    pthread_mutex_unlock(&recurso_a);
    return NULL;
}

// Thread 2: pega Recurso B e depois tenta pegar Recurso A.
void *tarefa_pega_b_depois_a(void *arg) {
    (void)arg; // Parâmetro não utilizado.

    printf("[Thread B] Tentando bloquear Recurso B...\n");
    pthread_mutex_lock(&recurso_b);
    printf("[Thread B] Recurso B bloqueado.\n");

    // Pausa para garantir a inversão de ordem dos locks.
    sleep(1);

    printf("[Thread B] Tentando bloquear Recurso A... (vai travar aqui)\n");
    pthread_mutex_lock(&recurso_a);

    printf("[Thread B] Conseguiu Recurso A.\n");
    pthread_mutex_unlock(&recurso_a);
    pthread_mutex_unlock(&recurso_b);
    return NULL;
}

int main(void) {
    pthread_t thread_a, thread_b;

    // Desabilita o buffer da stdout para que as mensagens apareçam imediatamente.
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("--- DEMONSTRACAO DE DEADLOCK ---\n");
    printf("Cada thread vai bloquear um recurso e, em seguida,\n");
    printf("tentara pegar o recurso que a outra ja bloqueou.\n");
    printf("Resultado: nenhuma das duas consegue prosseguir.\n");
    printf("Finalize com Ctrl+C quando quiser encerrar o programa.\n\n");

    // Cria as duas threads que competem pelos recursos.
    pthread_create(&thread_a, NULL, tarefa_pega_a_depois_b, NULL);
    pthread_create(&thread_b, NULL, tarefa_pega_b_depois_a, NULL);

    // O join nunca retorna porque as threads ficam presas em deadlock.
    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);

    printf("Se voce esta lendo isto, o deadlock nao ocorreu.\n");
    return 0;
}
