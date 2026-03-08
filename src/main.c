/**
 * @file main.c
 * @brief Programa principal do Sistema de Ranking de Jogos.
 * Le dados gerados, popula as estruturas e executa as ordenacoes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../include/listas.h"
#include "../include/algoritmos.h"
#include "../src/desempenho/teste_desempenho.h"


// FUNCOES DE LEITURA

// Calcula pontuacao baseada nos dados do dataset_gen.py
Jogador criar_jogador_do_csv(char *nome, int kills, int mortes, int assistencias) {
    Jogador j;
    strncpy(j.nome, nome, MAX_NOME_JOGADOR - 1);
    j.nome[MAX_NOME_JOGADOR - 1] = '\0';

    // Regra de negocio criada para o jogo.
    j.pontuacao = (kills * 10) + (assistencias * 5) - (mortes * 2);
    if (j.pontuacao < 0) {
        j.pontuacao = 0;
    }

    j.nivel = (j.pontuacao / 50) + 1;

    return j;
}

void carregar_dados_csv(const char *caminho, ListaEstatica *l_est, ListaDinamica *l_din, bool verbose) {
    FILE *f = fopen(caminho, "r");
    if (!f) {
        if (verbose) {
            printf("Erro ao abrir o arquivo: %s\n", caminho);
        }
        return;
    }

    char linha[256];
    fgets(linha, sizeof(linha), f); // Pula cabecalho.

    int cont = 0;
    while (fgets(linha, sizeof(linha), f)) {
        linha[strcspn(linha, "\n")] = 0;

        char *nome = strtok(linha, ",");
        char *kills_str = strtok(NULL, ",");
        char *mortes_str = strtok(NULL, ",");
        char *assis_str = strtok(NULL, ",");

        if (nome && kills_str && mortes_str && assis_str) {
            Jogador j = criar_jogador_do_csv(nome, atoi(kills_str), atoi(mortes_str), atoi(assis_str));

            insere_lista_estatica(l_est, j);
            insere_lista_dinamica(l_din, j);
            cont++;
        }
    }

    fclose(f);
    if (verbose) {
        printf("Sucesso: %d jogadores carregados do arquivo %s!\n", cont, caminho);
    }
}

static void limpar_buffer_entrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static const char *obter_label_tamanho(int opcao_tamanho) {
    switch (opcao_tamanho) {
        case 1:
            return "pequeno";
        case 2:
            return "medio";
        case 3:
            return "grande";
        default:
            return NULL;
    }
}

static const char *obter_pasta_tipo_entrada(int tipo_entrada) {
    switch (tipo_entrada) {
        case 1:
            return "aleatorio";
        case 2:
            return "ordenado";
        case 3:
            return "inverso";
        default:
            return NULL;
    }
}

static int solicitar_tipo_entrada(void) {
    int tipo_entrada;

    while (1) {
        printf("\nTipo de entrada:\n");
        printf("[1] Aleatorio\n");
        printf("[2] Ordenado\n");
        printf("[3] Inverso (pior caso)\n");
        printf("Escolha: ");

        if (scanf("%d", &tipo_entrada) != 1) {
            limpar_buffer_entrada();
            printf("Opcao invalida.\n");
            continue;
        }

        if (tipo_entrada >= 1 && tipo_entrada <= 3) {
            return tipo_entrada;
        }

        printf("Opcao invalida.\n");
    }
}

static void carregar_dataset_por_menu(int opcao_tamanho, ListaEstatica *lista_est, ListaDinamica *lista_din, bool verbose) {
    const char *tamanho = obter_label_tamanho(opcao_tamanho);
    if (!tamanho) {
        if (verbose) {
            printf("Opcao de tamanho invalida.\n");
        }
        return;
    }

    int tipo_entrada = solicitar_tipo_entrada();
    const char *pasta_tipo = obter_pasta_tipo_entrada(tipo_entrada);
    if (!pasta_tipo) {
        if (verbose) {
            printf("Tipo de entrada invalido.\n");
        }
        return;
    }

    char caminho[128];
    snprintf(caminho, sizeof(caminho), "data/cenarios/%s/jogadores_%s.csv", pasta_tipo, tamanho);

    libera_lista_estatica(lista_est);
    libera_lista_dinamica(lista_din);
    carregar_dados_csv(caminho, lista_est, lista_din, verbose);
}


// MENU PRINCIPAL

void exibir_menu() {
    printf("\n============================================\n");
    printf("       RANKING DE JOGOS - ESTRUTURAS\n");
    printf("============================================\n");
    printf("[1] Carregar dados (Pequeno - 100)\n");
    printf("[2] Carregar dados (Medio - 1000)\n");
    printf("[3] Carregar dados (Grande - 10000)\n");
    printf("[4] Imprimir Lista Estatica\n");
    printf("[5] Imprimir Lista Dinamica\n");
    printf("[6] Ordenar Lista Estatica (Quick Sort)\n");
    printf("[7] Ordenar Lista Dinamica (Merge Sort)\n");
    printf("[8] Teste de Desempenho\n");
    printf("[0] Sair\n");
    printf("============================================\n");
    printf("Escolha uma opcao: ");
}

int main(int argc, char *argv[]) {
    bool verbose = true;
    if (argc > 1 && strcmp(argv[1], "-q") == 0) {
        verbose = false;
    }

    if (!verbose) {
        teste_desempenho(0);
        return 0;
    }

    ListaEstatica lista_est;
    ListaDinamica lista_din;

    inicializa_lista_estatica(&lista_est);
    inicializa_lista_dinamica(&lista_din);

    int opcao;
    do {
        exibir_menu();
        if (scanf("%d", &opcao) != 1) {
            break;
        }

        switch (opcao) {
            case 1:
                carregar_dataset_por_menu(1, &lista_est, &lista_din, verbose);
                break;
            case 2:
                carregar_dataset_por_menu(2, &lista_est, &lista_din, verbose);
                break;
            case 3:
                carregar_dataset_por_menu(3, &lista_est, &lista_din, verbose);
                break;
            case 4:
                imprime_lista_estatica(&lista_est);
                break;
            case 5:
                imprime_lista_dinamica(&lista_din);
                break;
            case 6:
                printf("\nOrdenando Lista Estatica com Quick Sort...\n");
                quickSort_ListaEstatica(&lista_est);
                printf("Ordenacao concluida!\n");
                break;
            case 7:
                printf("\nOrdenando Lista Dinamica com Merge Sort...\n");
                mergeSort_ListaDinamica(&lista_din);
                printf("Ordenacao concluida!\n");
                break;
            case 8:
                printf("\nTestes de desempenho automatizados medindo o tempo em ms.\n");
                teste_desempenho(verbose);
                break;
            case 0:
                printf("\nEncerrando o sistema e liberando memoria...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);

    libera_lista_estatica(&lista_est);
    libera_lista_dinamica(&lista_din);

    return 0;
}