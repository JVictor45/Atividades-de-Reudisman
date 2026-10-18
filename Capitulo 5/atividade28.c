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

void buscar_pares(int v[], int n, int alvo) {
    int comparacoes = 0, encontrados = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[i] + v[j] == alvo) {
                printf("Par: %d + %d = %d\n", v[i], v[j], alvo);
                encontrados++;
            }
        }
    }
    if (encontrados == 0) printf("Nenhum par encontrado.\n");
    printf("Comparacoes O(n^2): %d\n", comparacoes);
}

int busca_binaria(int v[], int n, int alvo, int *comparacoes) {
    int inicio = 0, fim = n - 1;
    *comparacoes = 0;
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        printf("Inicio: %d | Meio: %d | Fim: %d\n", inicio, meio, fim);
        (*comparacoes)++;
        if (v[meio] == alvo) return meio;
        if (v[meio] < alvo) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

int main(void) {
    int vetor[30], tamanhos[3] = {5, 10, 20};
    for (int t = 0; t < 3; t++) {
        int n = tamanhos[t];
        for (int i = 0; i < n; i++) vetor[i] = i + 1;
        printf("\n===== TAMANHO %d =====\n", n);
        acesso_direto(vetor, n, 2);
        buscar_maior(vetor, n);
        buscar_pares(vetor, n, 10);
        int comparacoes, posicao;
        posicao = busca_binaria(vetor, n, n, &comparacoes);
        printf("Presente: posicao %d | Comparacoes: %d\n", posicao, comparacoes);
        posicao = busca_binaria(vetor, n, n + 1, &comparacoes);
        printf("Ausente: posicao %d | Comparacoes: %d\n", posicao, comparacoes);
    }
    return 0;
}
