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
                     FILE *out) {
    double soma_tempo;
    clock_t inicio, fim;
    double tempo_ms;
    // Teste com lista estática
    if (alg_est) {
        soma_tempo = 0.0;
        for (int r = 0; r < REPETICOES; r++) {
            ListaEstatica lista_est;
            inicializa_lista_estatica(&lista_est);
            ListaDinamica lista_din;
            inicializa_lista_dinamica(&lista_din);
            carregar_dados_csv(dataset, &lista_est, &lista_din);
            inicio = clock();
            alg_est(&lista_est);
            fim = clock();
            tempo_ms = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
            soma_tempo += tempo_ms;
            libera_lista_estatica(&lista_est);
            libera_lista_dinamica(&lista_din);
        }
        double media = soma_tempo / REPETICOES;
        printf("%s Estatica [%s]: Média %.2f ms (%d repetições)\n", nome, label, media, REPETICOES);
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
            carregar_dados_csv(dataset, &lista_est, &lista_din);
            inicio = clock();
            alg_din(&lista_din);
            fim = clock();
            tempo_ms = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
            soma_tempo += tempo_ms;  
            libera_lista_estatica(&lista_est);
            libera_lista_dinamica(&lista_din);
        }
        double media = soma_tempo / REPETICOES;
        printf("%s Dinamica [%s]: Média %.2f ms (%d repetições)\n", nome, label, media, REPETICOES);
        fprintf(out, "%s Dinamica,%s,%.2f\n", nome, label, media);
    }
}
// Função principal
void teste_desempenho() {
    const char *datasets[] = {
        "data/jogadores_pequeno.csv",
        "data/jogadores_medio.csv",
        "data/jogadores_grande.csv"
    };
    const char *labels[] = {"Pequeno", "Medio", "Grande"};
    FILE *out = fopen("data/results.csv", "w");
    if (!out) {
        printf("Erro ao criar arquivo de resultados.\n");
        return;
    }
    fprintf(out, "Algoritmo,Tamanho,Tempo(ms)\n");
    for (int i = 0; i < 3; i++) {
        printf("\n--- Testando dataset %s ---\n", labels[i]);
        rodar_algoritmo("BubbleSort", datasets[i], labels[i], bubbleSort_ListaEstatica, bubbleSort_ListaDinamica, out);
        rodar_algoritmo("QuickSort", datasets[i], labels[i], quickSort_ListaEstatica, quickSort_ListaDinamica, out);
        rodar_algoritmo("MergeSort", datasets[i], labels[i], mergeSort_ListaEstatica, mergeSort_ListaDinamica, out);
        rodar_algoritmo("SelectionSort", datasets[i], labels[i], selectionSort_ListaEstatica, selectionSort_ListaDinamica, out);
        rodar_algoritmo("InsertionSort", datasets[i], labels[i], insertionSort_ListaEstatica, insertionSort_ListaDinamica, out);
    }
    fclose(out);
    printf("\nResultados salvos em data/results.csv\n");
}
