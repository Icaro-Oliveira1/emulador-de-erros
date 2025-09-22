#include <stdio.h>
#include <string.h>

// Agrupamos os dados de autenticação em uma struct.
// O compilador irá alocar memória para esta estrutura como um bloco único.
struct DadosDeAutenticacao {
    char input_usuario[16];   // Buffer para a senha que o usuário digita.
    int acesso_concedido;     // Flag de autorização (nossa vítima).
};

int main() {
    char senha_secreta[] = "S3NH4_D1F1C1L";
    
    // Criamos uma instância da nossa struct.
    struct DadosDeAutenticacao auth;

    // --- A VULNERABILIDADE ---
    // Inicializamos a flag de acesso como 0 (Negado).
    auth.acesso_concedido = 0;

    // --- O "EXPLOIT" ---
    // O input malicioso agora só precisa de 16 'A's para encher o buffer
    // e mais alguns bytes para sobrescrever o inteiro. Usamos 'B's de novo.
    char input_malicioso[] = "AAAAAAAAAAAAAAAA" "BBBB";

    printf("--- DEMONSTRACAO DE EXPLOIT VIA BUFFER OVERFLOW (COM STRUCT) ---\n");
    printf("--- ESTADO INICIAL ---\n");
    printf("Valor da flag 'acesso_concedido': %d (0 = Negado)\n\n", auth.acesso_concedido);
    
    printf("Atacante inserindo senha maliciosa de %zu bytes...\n", strlen(input_malicioso));
    // O strcpy agora opera dentro da struct, mas a vulnerabilidade é a mesma.
    strcpy(auth.input_usuario, input_malicioso);
    printf("Overflow realizado!\n\n");

    // --- ANÁLISE PÓS-ATAQUE ---
    printf("--- ESTADO APOS O ATAQUE ---\n");
    printf("Valor da flag 'acesso_concedido' AGORA: %d (ou 0x%X em hexadecimal)\n\n", auth.acesso_concedido, auth.acesso_concedido);

    if (auth.acesso_concedido != 0) {
        printf("PROVA DO EXPLOIT: A flag de acesso foi alterada pelo overflow!\n\n");
    }

    // --- A FALHA NA LÓGICA DE SEGURANÇA ---
    printf("--- VERIFICANDO AUTENTICACAO ---\n");
    
    if (strcmp(senha_secreta, auth.input_usuario) == 0) {
        printf("Resultado da comparacao de senha: SUCESSO\n");
    } else {
        printf("Resultado da comparacao de senha: FALHA! As senhas sao diferentes.\n");
    }

    if (auth.acesso_concedido != 0) {
        printf("Verificacao da flag de acesso: Acesso AUTORIZADO (flag != 0)\n");
        printf("\n\n>>> FALHA DE SEGURANCA CRITICA: ACESSO CONCEDIDO! <<<\n");
    } else {
        printf("Verificacao da flag de acesso: Acesso NEGADO (flag == 0)\n");
    }

    return 0;
}