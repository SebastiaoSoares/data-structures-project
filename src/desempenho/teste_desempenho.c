#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../include/listas.h"
#include "../../include/algoritmos.h"

#define REPETICOES 100  // número de vezes que cada teste será repetido

// Função auxiliar para rodar cada algoritmo várias vezes e calcular média
void rodar_algoritmo(const char *nome,
                     const char *dataset,
                     const char *label,
                     void (*alg_est)(ListaEstatica*),
                     void (*alg_din)(ListaDinamica*),
                     FILE *out,
                     int verbose) {
    double soma_tempo;
    struct timespec inicio, fim; // Estrutura para capturar segundos e nanossegundos
    double tempo_ns;

    // Teste com lista estática
    if (alg_est) {
        soma_tempo = 0.0;
        for (int r = 0; r < REPETICOES; r++) {
            ListaEstatica lista_est;
            inicializa_lista_estatica(&lista_est);
            ListaDinamica lista_din;
            inicializa_lista_dinamica(&lista_din);
            carregar_dados_csv(dataset, &lista_est, &lista_din, verbose);

            // Captura o tempo inicial em nanossegundos
            clock_gettime(CLOCK_MONOTONIC, &inicio);
            alg_est(&lista_est);
            // Captura o tempo final
            clock_gettime(CLOCK_MONOTONIC, &fim);

            // Calcula a diferença de tempo: (segundos * 10^9) + nanossegundos
            tempo_ns = (fim.tv_sec - inicio.tv_sec) * 1e9 + (fim.tv_nsec - inicio.tv_nsec);
            soma_tempo += tempo_ns;

            libera_lista_estatica(&lista_est);
            libera_lista_dinamica(&lista_din);
        }
        double media = soma_tempo / REPETICOES;
        if (verbose) {
            printf("%s Estatica [%s]: Média %.2f ns (%d repetições)\n", nome, label, media, REPETICOES);
        }
        fprintf(out, "%s Estatica,%s,%.2f\n", nome, label, media);
    }

    // Teste com lista dinâmica
    if (alg_din) {
        soma_tempo = 0.0;
        for (int r = 0; r < REPETICOES; r++) {
            ListaEstatica lista_est;
            inicializa_lista_estatica(&lista_est);
            ListaDinamica lista_din;
            inicializa_lista_dinamica(&lista_din);
            carregar_dados_csv(dataset, &lista_est, &lista_din, verbose);

            // Captura o tempo inicial em nanossegundos
            clock_gettime(CLOCK_MONOTONIC, &inicio);
            alg_din(&lista_din);
            // Captura o tempo final
            clock_gettime(CLOCK_MONOTONIC, &fim);

            // Calcula a diferença de tempo: (segundos * 10^9) + nanossegundos
            tempo_ns = (fim.tv_sec - inicio.tv_sec) * 1e9 + (fim.tv_nsec - inicio.tv_nsec);
            soma_tempo += tempo_ns;  

            libera_lista_estatica(&lista_est);
            libera_lista_dinamica(&lista_din);
        }
        double media = soma_tempo / REPETICOES;
        if (verbose) {
            printf("%s Dinamica [%s]: Média %.2f ns (%d repetições)\n", nome, label, media, REPETICOES);
        }
        fprintf(out, "%s Dinamica,%s,%.2f\n", nome, label, media);
    }
}

// Função principal
void teste_desempenho(int verbose) {
    const char *datasets[] = {
        "data/jogadores_pequeno.csv",
        "data/jogadores_medio.csv",
        "data/jogadores_grande.csv"
    };
    const char *labels[] = {"Pequeno", "Medio", "Grande"};
    FILE *out = fopen("data/results.csv", "w");
    if (!out) {
        if (verbose) {
            printf("Erro ao criar arquivo de resultados.\n");
        }
        return;
    }

    // Cabeçalho do CSV atualizado para exibir (ns)
    fprintf(out, "Algoritmo,Tamanho,Tempo(ns)\n");

    for (int i = 0; i < 3; i++) {
        rodar_algoritmo("BubbleSort", datasets[i], labels[i], bubbleSort_ListaEstatica, bubbleSort_ListaDinamica, out, verbose);
        rodar_algoritmo("QuickSort", datasets[i], labels[i], quickSort_ListaEstatica, quickSort_ListaDinamica, out, verbose);
        rodar_algoritmo("MergeSort", datasets[i], labels[i], mergeSort_ListaEstatica, mergeSort_ListaDinamica, out, verbose);
        rodar_algoritmo("SelectionSort", datasets[i], labels[i], selectionSort_ListaEstatica, selectionSort_ListaDinamica, out, verbose);
        rodar_algoritmo("InsertionSort", datasets[i], labels[i], insertionSort_ListaEstatica, insertionSort_ListaDinamica, out, verbose);
    }
    
    fclose(out);
    if (verbose) {
        printf("Resultados salvos em data/results.csv\n");
    }
}