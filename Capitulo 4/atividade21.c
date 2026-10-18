#include <stdio.h>

typedef struct {
    int id;
    char jogador[40];
    int pontuacao;
} Partida;

void salvar_partidas(Partida partidas[], int quantidade) {
    FILE *arquivo = fopen("partidas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d %s %d\n", partidas[i].id,
                partidas[i].jogador, partidas[i].pontuacao);
    }
    fclose(arquivo);
}

void ler_partidas(void) {
    FILE *arquivo = fopen("partidas.txt", "r");
    Partida partida;
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }
    printf("\nPartidas recuperadas:\n");
    while (fscanf(arquivo, "%d %39s %d", &partida.id,
                  partida.jogador, &partida.pontuacao) == 3) {
        printf("ID: %d | Jogador: %s | Pontos: %d\n",
               partida.id, partida.jogador, partida.pontuacao);
    }
    fclose(arquivo);
}

int main(void) {
    Partida partidas[3];
    for (int i = 0; i < 3; i++) {
        partidas[i].id = i + 1;
        printf("Nome do jogador da partida %d (sem espacos): ", i + 1);
        scanf("%39s", partidas[i].jogador);
        printf("Pontuacao: ");
        scanf("%d", &partidas[i].pontuacao);
    }
    salvar_partidas(partidas, 3);
    ler_partidas();
    return 0;
}
