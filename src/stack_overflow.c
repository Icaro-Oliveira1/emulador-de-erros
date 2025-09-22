#include <stdio.h>

// Uma função que chama a si mesma sem parar.
void estouro_infinito(int contador) {
    printf("Chamada da função número: %d\n", contador);

    // Não há condição de parada, então isso nunca termina.
    estouro_infinito(contador + 1);
}

int main() {
    printf("Iniciando a demonstração de Stack Overflow...\n");
    
    // Inicia a recursão infinita.
    estouro_infinito(1);
    
    // Esta linha nunca será alcançada.
    return 0;
}