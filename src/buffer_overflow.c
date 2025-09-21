
#include <stdio.h>
#include <string.h>

int main() {
    // Na pilha de memória (stack), as variáveis são tipicamente alocadas
    // em ordem inversa. Então, declaramos a 'vitima' primeiro para que
    // ela fique "depois" do buffer na memória.
    int variavel_vitima = 0xCAFEFACE; // Um valor mágico e fácil de reconhecer em hexadecimal.
    char buffer[10];
    
    char string_longa[] = "AAAAAAAAAAAAAAAAAAAA"; // 20 'A's. Irá estourar o buffer e atingir a vítima.

    printf("--- ANTES DO OVERFLOW ---\n");
    printf("Endereco do buffer: \t%p\n", (void*)buffer);
    printf("Endereco da vitima: \t%p\n", (void*)&variavel_vitima);
    printf("Valor da vitima: \t%d (ou 0x%X em hexadecimal)\n\n", variavel_vitima, variavel_vitima);

    // --- O ATAQUE ---
    printf("--- REALIZANDO O OVERFLOW COM strcpy ---\n");
    strcpy(buffer, string_longa);
    printf("Overflow realizado!\n\n");

    // --- RESULTADO ---
    printf("--- DEPOIS DO OVERFLOW ---\n");
    printf("Conteudo do buffer: \t'%s'\n", buffer);
    printf("Valor da vitima AGORA: \t%d (ou 0x%X em hexadecimal)\n", variavel_vitima, variavel_vitima);
    
    // O valor da 'variavel_vitima' foi corrompido! Os 'A's (cujo valor em ASCII é 65 ou 0x41)
    // foram escritos sobre os bytes da nossa variável. O novo valor será 0x41414141.
    // Isso PROVA que o buffer estourou e corrompeu a memória adjacente.
    
    if (variavel_vitima != 0xCAFEFACE) {
        printf("\nPROVA IRREFUTAVEL: A memoria da 'variavel_vitima' foi corrompida!\n");
    }

    // O crash (Segmentation Fault) geralmente não acontece aqui.
    // Ele acontece quando a função 'main' tenta retornar, pois o endereço de retorno
    // na pilha também foi sobrescrito pelos 'A's, fazendo o programa pular
    // para um endereço de memória inválido (0x41414141...).
    
    printf("O programa vai quebrar ao tentar retornar da funcao main...\n");
    
    return 0;
}