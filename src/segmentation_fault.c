
#include <stdio.h>
#include <stdlib.h> // Para a macro NULL

int main() {
    // 1. Preparação
    // Criamos um ponteiro, que é uma variável que deveria "apontar" para
    // um endereço de memória válido.
    // No entanto, nós o inicializamos com NULL. NULL é um alias para o endereço 0.
    // O endereço 0 é uma área de memória superprotegida e reservada para o
    // Sistema Operacional. Nenhum programa de usuário tem permissão para ler ou escrever lá.
    int *ptr = NULL;

    printf("--- DEMONSTRACAO DE SEGMENTATION FAULT ---\n");
    printf("1. Criamos um ponteiro 'ptr' e o definimos como NULL.\n");
    printf("   O valor de 'ptr' (o endereco para onde ele aponta) eh: %p\n", (void*)ptr);
    printf("   Este endereco (0x0 ou nil) eh uma area protegida pelo SO.\n\n");

    // 2. O Ato Ilegal
    printf("2. Agora, vamos tentar cometer um ato ilegal: escrever o numero 123\n");
    printf("   no endereco de memoria para o qual 'ptr' aponta (%p).\n", (void*)ptr);
    printf("   O SO devera detectar esta invasao e encerrar o programa.\n");
    printf("   Aperte Enter para continuar...\n");
    getchar(); // Pausa para o usuário ler a explicação

    // Garantimos que todas as mensagens acima sejam impressas antes do crash.
    fflush(stdout);

    // Esta é a linha que causa o Segmentation Fault.
    // Estamos dizendo: "armazene o valor 123 no endereço de memória 0".
    // O SO irá dizer "NÃO!" e encerrar o processo.
    *ptr = 123;

    // 3. A Consequência
    // Esta linha nunca será executada, pois o programa será encerrado na linha anterior.
    printf("!!! Se voce esta lendo isso, algo muito estranho aconteceu.\n");

    return 0;
}