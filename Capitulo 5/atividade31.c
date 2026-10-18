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

int busca_linear(int v[], int n, int alvo, int *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n; i++) {
        (*comparacoes)++;
        if (v[i] == alvo) return i;
    }
    return -1;
}

void comparar_buscas(int v[], int n, int alvo) {
    int c1, c2;
    int p1 = busca_linear(v, n, alvo, &c1);
    int p2 = busca_binaria(v, n, alvo, &c2);
    printf("Alvo: %d | Linear: %d (%d comparacoes)\n", alvo, p1, c1);
    printf("Binaria: %d (%d comparacoes)\n", p2, c2);
}

int fatorial_recursivo(int n, int *chamadas) {
    (*chamadas)++;
    if (n <= 1) return 1;
    return n * fatorial_recursivo(n - 1, chamadas);
}

int fatorial_iterativo(int n, int *operacoes) {
    int resultado = 1;
    *operacoes = 0;
    for (int i = 2; i <= n; i++) {
        resultado *= i;
        (*operacoes)++;
    }
    return resultado;
}

int soma_recursiva(int v[], int n, int *chamadas) {
    (*chamadas)++;
    if (n == 0) return 0;
    return v[n - 1] + soma_recursiva(v, n - 1, chamadas);
}

int soma_iterativa(int v[], int n, int *operacoes) {
    int soma = 0;
    *operacoes = 0;
    for (int i = 0; i < n; i++) {
        soma += v[i];
        (*operacoes)++;
    }
    return soma;
}

int fibonacci(int n, int *chamadas) {
    (*chamadas)++;
    if (n <= 1) return n;
    return fibonacci(n - 1, chamadas) + fibonacci(n - 2, chamadas);
}

int busca_binaria_recursiva(int v[], int inicio, int fim,
                           int alvo, int *chamadas) {
    (*chamadas)++;
    if (inicio > fim) return -1;
    int meio = inicio + (fim - inicio) / 2;
    printf("Inicio: %d | Meio: %d | Fim: %d\n", inicio, meio, fim);
    if (v[meio] == alvo) return meio;
    if (v[meio] < alvo)
        return busca_binaria_recursiva(v, meio + 1, fim, alvo, chamadas);
    return busca_binaria_recursiva(v, inicio, meio - 1, alvo, chamadas);
}

int main(void) {
    int opcao;
    do {
        printf("\n===== LABORATORIO =====\n");
        printf("1 - Comparar complexidades e buscas\n");
        printf("2 - Busca linear em vetor desordenado\n");
        printf("3 - Soma e fatorial recursivos\n");
        printf("4 - Fibonacci recursivo\n");
        printf("5 - Busca binaria recursiva\n");
        printf("0 - Sair\nEscolha: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida.\n");
            break;
        }
        switch (opcao) {
            case 1: {
                int vetor[30], tamanhos[3] = {5, 10, 20};
                for (int t = 0; t < 3; t++) {
                    int n = tamanhos[t];
                    for (int i = 0; i < n; i++) vetor[i] = i + 1;
                    printf("\n===== TAMANHO %d =====\n", n);
                    acesso_direto(vetor, n, 2);
                    buscar_maior(vetor, n);
                    buscar_pares(vetor, n, 10);
                    comparar_buscas(vetor, n, 1);
                    comparar_buscas(vetor, n, n / 2);
                    comparar_buscas(vetor, n, n);
                    comparar_buscas(vetor, n, n + 1);
                }
                break;
            }
            case 2: {
                int v[5] = {9, 2, 7, 1, 5}, comparacoes;
                int posicao = busca_linear(v, 5, 7, &comparacoes);
                printf("Posicao: %d | Comparacoes: %d\n", posicao, comparacoes);
                printf("Busca binaria exige vetor ordenado.\n");
                break;
            }
            case 3: {
                int v[5] = {1, 2, 3, 4, 5};
                int chamadas = 0, operacoes = 0;
                int sr = soma_recursiva(v, 5, &chamadas);
                int si = soma_iterativa(v, 5, &operacoes);
                printf("Soma recursiva: %d | Chamadas: %d\n", sr, chamadas);
                printf("Soma iterativa: %d | Operacoes: %d\n", si, operacoes);
                chamadas = 0;
                operacoes = 0;
                int fr = fatorial_recursivo(5, &chamadas);
                int fi = fatorial_iterativo(5, &operacoes);
                printf("Fatorial recursivo: %d | Chamadas: %d\n", fr, chamadas);
                printf("Fatorial iterativo: %d | Operacoes: %d\n", fi, operacoes);
                break;
            }
            case 4: {
                int n, chamadas = 0;
                printf("Digite n (0 a 20): ");
                if (scanf("%d", &n) != 1) {
                    printf("Entrada invalida.\n");
                    break;
                }
                if (n < 0 || n > 20) {
                    printf("Valor fora do limite.\n");
                    break;
                }
                printf("Fibonacci(%d) = %d\n", n, fibonacci(n, &chamadas));
                printf("Chamadas recursivas: %d\n", chamadas);
                break;
            }
            case 5: {
                int v[20], alvo, chamadas = 0, comparacoes = 0;
                for (int i = 0; i < 20; i++) v[i] = i + 1;
                printf("Digite o valor procurado: ");
                if (scanf("%d", &alvo) != 1) {
                    printf("Entrada invalida.\n");
                    break;
                }
                int p1 = busca_binaria(v, 20, alvo, &comparacoes);
                int p2 = busca_binaria_recursiva(v, 0, 19, alvo, &chamadas);
                printf("Iterativa: posicao %d | Comparacoes: %d\n", p1, comparacoes);
                printf("Recursiva: posicao %d | Chamadas: %d\n", p2, chamadas);
                break;
            }
            case 0: printf("Encerrando.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
    return 0;
}
