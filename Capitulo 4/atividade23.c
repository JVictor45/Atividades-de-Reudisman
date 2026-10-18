#include <stdio.h>

typedef struct {
    int id;
    char jogador[40];
    int pontuacao;
} Partida;

void salvar_partidas(Partida partidas[], int quantidade) {
    FILE *arquivo = fopen("partidas.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir partidas.txt.\n");
        return;
    }
    for (int i = 0; i < quantidade; i++)
        fprintf(arquivo, "%d %s %d\n", partidas[i].id,
                partidas[i].jogador, partidas[i].pontuacao);
    fclose(arquivo);
}

void ler_partidas(void) {
    FILE *arquivo = fopen("partidas.txt", "r");
    Partida p;
    int total = 0, resultado;
    if (arquivo == NULL) {
        printf("Erro ao abrir o historico.\n");
        return;
    }
    printf("\nHistorico de partidas:\n");
    while ((resultado = fscanf(arquivo, "%d %39s %d",
                              &p.id, p.jogador, &p.pontuacao)) == 3) {
        printf("ID: %d | Jogador: %s | Pontos: %d\n",
               p.id, p.jogador, p.pontuacao);
        total++;
    }
    if (total == 0) printf("Historico vazio.\n");
    if (resultado != EOF) printf("Registro malformado encontrado.\n");
    printf("Total de partidas: %d\n", total);
    fclose(arquivo);
}

void processar_partidas(void) {
    FILE *origem = fopen("partidas.txt", "r");
    if (origem == NULL) {
        printf("Erro ao abrir o arquivo de origem.\n");
        return;
    }
    FILE *destino = fopen("processadas.txt", "w");
    if (destino == NULL) {
        printf("Erro ao criar o arquivo de destino.\n");
        fclose(origem);
        return;
    }
    Partida p;
    int total = 0, resultado = EOF, erro = 0;
    // Regra: adicionar 10 pontos de bonus.
    while ((resultado = fscanf(origem, "%d %39s %d",
                              &p.id, p.jogador, &p.pontuacao)) == 3) {
        p.pontuacao += 10;
        if (fprintf(destino, "%d %s %d\n",
                    p.id, p.jogador, p.pontuacao) < 0) {
            printf("Erro ao escrever no destino.\n");
            erro = 1;
            break;
        }
        total++;
    }
    if (!erro && resultado != EOF) {
        printf("Registro incompleto ou malformado.\n");
        erro = 1;
    }
    if (fclose(origem) != 0) {
        printf("Erro ao fechar a origem.\n");
        erro = 1;
    }
    if (fclose(destino) != 0) {
        printf("Erro ao fechar o destino.\n");
        erro = 1;
    }
    printf("Registros processados: %d\n", total);
    if (!erro) printf("Arquivo processadas.txt criado com sucesso.\n");
}

int main(void) {
    Partida partidas[3];
    for (int i = 0; i < 3; i++) {
        partidas[i].id = i + 1;
        printf("Jogador da partida %d: ", i + 1);
        scanf("%39s", partidas[i].jogador);
        printf("Pontuacao: ");
        scanf("%d", &partidas[i].pontuacao);
    }
    salvar_partidas(partidas, 3);
    ler_partidas();
    processar_partidas();
    return 0;
}
