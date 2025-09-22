#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Esta função cria uma mensagem de boas-vindas e a retorna.
// Ela aloca memória para a mensagem, então quem a chama DEVE liberá-la.
char* criar_mensagem(const char* nome) {
    // Calcula o tamanho necessário para "Ola, [nome]!"
    int tamanho = strlen("Ola, ") + strlen(nome) + strlen("!") + 1;
    
    // Aloca memória para a mensagem
    char* mensagem = (char*) malloc(tamanho);
    if (mensagem == NULL) return NULL;

    // Cria a string formatada
    sprintf(mensagem, "Ola, %s!", nome);
    
    // Retorna o ponteiro para a memória alocada
    return mensagem;
}

int main() {
    printf("--- DEMONSTRACAO DE VAZAMENTO DE MEMORIA EM FUNCAO ---\n");

    // 1. Chamamos a função e recebemos a mensagem.
    // A variável 'msg_bem_vindo' agora aponta para uma memória alocada DENTRO da função.
    printf("Criando mensagem...\n");
    char *msg_bem_vindo = criar_mensagem("Icaro");

    // 2. Usamos a mensagem.
    printf("Mensagem recebida: '%s'\n", msg_bem_vindo);

    // 3. O ERRO: Esquecemos de liberar a memória que a função 'criar_mensagem' alocou para nós.
    // A linha abaixo está faltando!
    // free(msg_bem_vindo);

    printf("Programa terminou sem liberar a memoria da mensagem.\n");

    return 0;
}