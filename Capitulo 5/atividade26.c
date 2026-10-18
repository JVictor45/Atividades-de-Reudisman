#include <stdio.h>

void acesso_direto(int v[], int n, int indice) {
    if (indice < 0 || indice >= n) {
        printf("Indice invalido.\n");
        return;
    }
    printf("Valor: %d | Operacoes O(1): 1\n", v[indice]);
}

void buscar_maior(int v[], int n) {
    if (n <= 0) return;
    int maior = v[0], comparacoes = 0;
    for (int i = 0; i < n; i++) {
        comparacoes++;
        if (v[i] > maior) maior = v[i];
    }
    printf("Maior: %d | Comparacoes O(n): %d\n", maior, comparacoes);
}

int main(void) {
    int vetor[30], tamanhos[3] = {5, 10, 20};
    for (int t = 0; t < 3; t++) {
        int n = tamanhos[t];
        for (int i = 0; i < n; i++) vetor[i] = i + 1;
        printf("\n===== TAMANHO %d =====\n", n);
        acesso_direto(vetor, n, 2);
        buscar_maior(vetor, n);
    }
    return 0;
}
