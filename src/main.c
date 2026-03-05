/**
 * @file main.c
 * @brief Programa principal do Sistema de Ranking de Jogos.
 * Lê dados gerados, popula as estruturas e executa as ordenações.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../include/listas.h"
#include "../include/algoritmos.h"
#include "../src/desempenho/teste_desempenho.h"



// FUNÇÕES DE LEITURA

// Calcula pontuação baseada nos dados do dataset_gen.py
Jogador criar_jogador_do_csv(char *nome, int kills, int mortes, int assistencias) {
    Jogador j;
    strncpy(j.nome, nome, MAX_NOME_JOGADOR - 1);
    j.nome[MAX_NOME_JOGADOR - 1] = '\0'; 

    // Regra de negócio criada para o jogo:
    j.pontuacao = (kills * 10) + (assistencias * 5) - (mortes * 2);
    if (j.pontuacao < 0) j.pontuacao = 0;

    j.nivel = (j.pontuacao / 50) + 1; // Nível sobe a cada 50 pontos

    return j;
}

void carregar_dados_csv(const char *caminho, ListaEstatica *l_est, ListaDinamica *l_din) {
    FILE *f = fopen(caminho, "r");
    if (!f) {
        printf("Erro ao abrir o arquivo: %s\n", caminho);
        return;
    }

    char linha[256];
    // Pula o cabeçalho do CSV
    fgets(linha, sizeof(linha), f); 

    int cont = 0;
    while (fgets(linha, sizeof(linha), f)) {
        // Remove quebra de linha do final
        linha[strcspn(linha, "\n")] = 0;

        char *nome = strtok(linha, ",");
        char *kills_str = strtok(NULL, ",");
        char *mortes_str = strtok(NULL, ",");
        char *assis_str = strtok(NULL, ",");

        if (nome && kills_str && mortes_str && assis_str) {
            Jogador j = criar_jogador_do_csv(nome, atoi(kills_str), atoi(mortes_str), atoi(assis_str));
            
            // Popula ambas as listas para facilitar os testes
            insere_lista_estatica(l_est, j);
            insere_lista_dinamica(l_din, j);
            cont++;
        }
    }
    fclose(f);
    printf("Sucesso: %d jogadores carregados do arquivo %s!\n", cont, caminho);
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

int main() {
    ListaEstatica lista_est;
    ListaDinamica lista_din;

    inicializa_lista_estatica(&lista_est);
    inicializa_lista_dinamica(&lista_din);

    int opcao;
    do {
        exibir_menu();
        if (scanf("%d", &opcao) != 1) break;

        switch (opcao) {
            case 1:
                libera_lista_estatica(&lista_est);
                libera_lista_dinamica(&lista_din);
                carregar_dados_csv("data/jogadores_pequeno.csv", &lista_est, &lista_din);
                break;
            case 2:
                libera_lista_estatica(&lista_est);
                libera_lista_dinamica(&lista_din);
                carregar_dados_csv("data/jogadores_medio.csv", &lista_est, &lista_din);
                break;
            case 3:
                libera_lista_estatica(&lista_est);
                libera_lista_dinamica(&lista_din);
                carregar_dados_csv("data/jogadores_grande.csv", &lista_est, &lista_din);
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
                teste_desempenho();
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