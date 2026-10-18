#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    int id;
    char jogador[40];
    int pontuacao;
} Partida;

void listar(Partida partidas[], int quantidade) {
    if (quantidade == 0) {
        printf("Nenhuma partida cadastrada.\n");
        return;
    }
    for (int i = 0; i < quantidade; i++)
        printf("ID: %d | Jogador: %s | Pontos: %d\n",
               partidas[i].id, partidas[i].jogador,
               partidas[i].pontuacao);
}

void cadastrar(Partida **partidas, int *quantidade) {
    if (*quantidade == INT_MAX) {
        printf("Limite de partidas atingido.\n");
        return;
    }
    size_t novoTotal = (size_t)*quantidade + 1;
    if (novoTotal > ((size_t)-1) / sizeof(Partida)) {
        printf("Quantidade muito grande.\n");
        return;
    }
    Partida *novo = realloc(*partidas, novoTotal * sizeof(Partida));
    if (novo == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }
    *partidas = novo;
    Partida *p = &(*partidas)[*quantidade];
    memset(p, 0, sizeof(Partida));
    p->id = *quantidade + 1;
    printf("Nome do jogador (sem espacos): ");
    if (scanf("%39s", p->jogador) != 1) {
        printf("Erro ao ler nome.\n");
        return;
    }
    printf("Pontuacao: ");
    if (scanf("%d", &p->pontuacao) != 1) {
        printf("Pontuacao invalida.\n");
        return;
    }
    (*quantidade)++;
    printf("Partida cadastrada.\n");
}

void salvar_texto(Partida partidas[], int quantidade) {
    FILE *arquivo = fopen("partidas.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir historico.\n");
        return;
    }
    int total = 0;
    for (int i = 0; i < quantidade; i++) {
        if (fprintf(arquivo, "%d %s %d\n", partidas[i].id,
                    partidas[i].jogador, partidas[i].pontuacao) < 0) {
            printf("Erro ao escrever historico.\n");
            break;
        }
        total++;
    }
    if (fclose(arquivo) != 0)
        printf("Erro ao fechar historico.\n");
    printf("Registros adicionados: %d\n", total);
}

void ler_texto(void) {
    FILE *arquivo = fopen("partidas.txt", "r");
    if (arquivo == NULL) {
        printf("Historico inexistente.\n");
        return;
    }
    Partida p;
    int total = 0, resultado;
    printf("\nHistorico:\n");
    while ((resultado = fscanf(arquivo, "%d %39s %d",
                              &p.id, p.jogador, &p.pontuacao)) == 3) {
        printf("%d | %s | %d\n", p.id, p.jogador, p.pontuacao);
        total++;
    }
    if (total == 0) printf("Historico vazio.\n");
    if (resultado != EOF) printf("Registro malformado.\n");
    printf("Total lido: %d\n", total);
    fclose(arquivo);
}

void processar_texto(void) {
    FILE *origem = fopen("partidas.txt", "r");
    if (origem == NULL) {
        printf("Erro ao abrir origem.\n");
        return;
    }
    FILE *destino = fopen("processadas.txt", "w");
    if (destino == NULL) {
        printf("Erro ao abrir destino.\n");
        fclose(origem);
        return;
    }
    Partida p;
    int total = 0, resultado = EOF, erro = 0;
    // Bonus de 10 pontos por partida.
    while ((resultado = fscanf(origem, "%d %39s %d",
                              &p.id, p.jogador, &p.pontuacao)) == 3) {
        p.pontuacao += 10;
        if (fprintf(destino, "%d %s %d\n",
                    p.id, p.jogador, p.pontuacao) < 0) {
            printf("Erro ao escrever destino.\n");
            erro = 1;
            break;
        }
        total++;
    }
    if (!erro && resultado != EOF) {
        printf("Registro malformado na origem.\n");
        erro = 1;
    }
    if (fclose(origem) != 0) {
        printf("Erro ao fechar origem.\n");
        erro = 1;
    }
    if (fclose(destino) != 0) {
        printf("Erro ao fechar destino.\n");
        erro = 1;
    }
    printf("Registros processados: %d\n", total);
    if (!erro) printf("Relatorio processado com sucesso.\n");
}

void salvar_binario(Partida partidas[], int quantidade) {
    FILE *arquivo = fopen("temporada.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao criar arquivo binario.\n");
        return;
    }
    int erro = 0;
    if (fwrite(&quantidade, sizeof(int), 1, arquivo) != 1)
        erro = 1;
    if (!erro && quantidade > 0) {
        size_t escritos = fwrite(partidas, sizeof(Partida),
                                (size_t)quantidade, arquivo);
        if (escritos != (size_t)quantidade) erro = 1;
    }
    if (fclose(arquivo) != 0) erro = 1;
    if (erro)
        printf("Erro ao salvar temporada.\n");
    else
        printf("Temporada salva: %d partidas.\n", quantidade);
}

void carregar_binario(Partida **partidas, int *quantidade) {
    FILE *arquivo = fopen("temporada.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir temporada.bin.\n");
        return;
    }
    int total;
    if (fread(&total, sizeof(int), 1, arquivo) != 1) {
        printf("Arquivo vazio ou cabecalho incompleto.\n");
        fclose(arquivo);
        return;
    }
    if (total < 0 ||
        (size_t)total > ((size_t)-1) / sizeof(Partida)) {
        printf("Quantidade invalida no arquivo.\n");
        fclose(arquivo);
        return;
    }
    Partida *novo = NULL;
    if (total > 0) {
        novo = malloc((size_t)total * sizeof(Partida));
        if (novo == NULL) {
            printf("Erro ao alocar memoria.\n");
            fclose(arquivo);
            return;
        }
        size_t lidos = fread(novo, sizeof(Partida),
                            (size_t)total, arquivo);
        if (lidos != (size_t)total) {
            printf("Arquivo incompleto ou erro de leitura.\n");
            free(novo);
            fclose(arquivo);
            return;
        }
        for (int i = 0; i < total; i++)
            novo[i].jogador[39] = '\0';
    }
    if (fgetc(arquivo) != EOF || ferror(arquivo)) {
        printf("Arquivo com dados extras ou erro de leitura.\n");
        free(novo);
        fclose(arquivo);
        return;
    }
    if (fclose(arquivo) != 0) {
        printf("Erro ao fechar arquivo.\n");
        free(novo);
        return;
    }
    free(*partidas);
    *partidas = novo;
    *quantidade = total;
    printf("Temporada carregada: %d partidas.\n", total);
}

int main(void) {
    Partida *partidas = NULL;
    int quantidade = 0, opcao;
    do {
        printf("\n===== MENU DE PARTIDAS =====\n");
        printf("1 - Cadastrar partida\n");
        printf("2 - Listar partidas\n");
        printf("3 - Salvar temporada binaria\n");
        printf("4 - Carregar temporada binaria\n");
        printf("5 - Adicionar ao historico de texto\n");
        printf("6 - Ler historico de texto\n");
        printf("7 - Processar historico com bonus\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida.\n");
            break;
        }
        switch (opcao) {
            case 1: cadastrar(&partidas, &quantidade); break;
            case 2: listar(partidas, quantidade); break;
            case 3: salvar_binario(partidas, quantidade); break;
            case 4: carregar_binario(&partidas, &quantidade); break;
            case 5: salvar_texto(partidas, quantidade); break;
            case 6: ler_texto(); break;
            case 7: processar_texto(); break;
            case 0: printf("Encerrando programa.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
    free(partidas);
    return 0;
}
