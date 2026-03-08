#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "../../include/listas.h"
#include "../../include/algoritmos.h"

#define REPETICOES 100  // número de vezes que cada teste será repetido

// Retorna um timestamp em nanossegundos compatível com Windows e Linux.
static double get_time_ns(void) {
#ifdef _WIN32
    LARGE_INTEGER freq, counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    return ((double)counter.QuadPart * 1e9) / (double)freq.QuadPart;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec * 1e9 + (double)ts.tv_nsec;
#endif
}

// Função auxiliar para rodar cada algoritmo várias vezes e calcular média
void rodar_algoritmo(const char *nome,
                     const char *dataset,
                     const char *label,
                     const char *tipo_entrada,
                     void (*alg_est)(ListaEstatica*),
                     void (*alg_din)(ListaDinamica*),
                     FILE *out,
                     int verbose) {
    double soma_tempo;
    double tempo_ns;

    // --- TESTE COM LISTA ESTÁTICA ---
    if (alg_est) {
        soma_tempo = 0.0;
        for (int r = 0; r < REPETICOES; r++) {
            ListaEstatica lista_est;
            inicializa_lista_estatica(&lista_est);
            ListaDinamica lista_din; // Inicializa mas não usa no teste estático
            inicializa_lista_dinamica(&lista_din);

            // IMPORTANTE: Passamos '0' no verbose para não inundar o terminal durante as repetições
            carregar_dados_csv(dataset, &lista_est, &lista_din, 0);

            double inicio_ns = get_time_ns();
            alg_est(&lista_est);
            double fim_ns = get_time_ns();

            soma_tempo += (fim_ns - inicio_ns);

            libera_lista_estatica(&lista_est);
            libera_lista_dinamica(&lista_din);
        }
        double media = soma_tempo / REPETICOES;
        if (verbose) {
            printf("%s Estatica [%s - %s]: Media %.2f ns\n", nome, label, tipo_entrada, media);
        }
        fprintf(out, "%s Estatica,%s,%s,%.2f\n", nome, label, tipo_entrada, media);
    }

    // --- TESTE COM LISTA DINÂMICA ---
    if (alg_din) {
        soma_tempo = 0.0;
        for (int r = 0; r < REPETICOES; r++) {
            ListaEstatica lista_est;
            inicializa_lista_estatica(&lista_est);
            ListaDinamica lista_din;
            inicializa_lista_dinamica(&lista_din);

            // Silencioso aqui também (0)
            carregar_dados_csv(dataset, &lista_est, &lista_din, 0);

            double inicio_ns = get_time_ns();
            alg_din(&lista_din);
            double fim_ns = get_time_ns();

            soma_tempo += (fim_ns - inicio_ns);

            libera_lista_estatica(&lista_est);
            libera_lista_dinamica(&lista_din);
        }
        double media = soma_tempo / REPETICOES;
        if (verbose) {
            printf("%s Dinamica [%s - %s]: Media %.2f ns\n", nome, label, tipo_entrada, media);
        }
        fprintf(out, "%s Dinamica,%s,%s,%.2f\n", nome, label, tipo_entrada, media);
    }
}

// Função principal de teste
void teste_desempenho(int verbose) {
    typedef struct {
        const char *dataset;
        const char *tamanho;
        const char *tipo_entrada;
    } DatasetConfig;

    const DatasetConfig configs[] = {
        {"data/cenarios/aleatorio/jogadores_pequeno.csv", "Pequeno", "Aleatorio"},
        {"data/cenarios/ordenado/jogadores_pequeno.csv",  "Pequeno", "Ordenado"},
        {"data/cenarios/inverso/jogadores_pequeno.csv",   "Pequeno", "Inverso"},
        {"data/cenarios/aleatorio/jogadores_medio.csv",    "Medio",   "Aleatorio"},
        {"data/cenarios/ordenado/jogadores_medio.csv",     "Medio",   "Ordenado"},
        {"data/cenarios/inverso/jogadores_medio.csv",      "Medio",   "Inverso"},
        {"data/cenarios/aleatorio/jogadores_grande.csv",   "Grande",  "Aleatorio"},
        {"data/cenarios/ordenado/jogadores_grande.csv",    "Grande",  "Ordenado"},
        {"data/cenarios/inverso/jogadores_grande.csv",     "Grande",  "Inverso"},
    };

    FILE *out = fopen("data/results.csv", "w");
    if (!out) {
        if (verbose) printf("Erro ao criar arquivo de resultados.\n");
        return;
    }

    fprintf(out, "Algoritmo,Tamanho,TipoEntrada,Tempo(ns)\n");

    if (verbose) printf("Iniciando benchmarks (isso pode levar alguns segundos)...\n\n");

    for (size_t i = 0; i < sizeof(configs) / sizeof(configs[0]); i++) {
        rodar_algoritmo("BubbleSort",    configs[i].dataset, configs[i].tamanho, configs[i].tipo_entrada, bubbleSort_ListaEstatica, bubbleSort_ListaDinamica, out, verbose);
        rodar_algoritmo("QuickSort",     configs[i].dataset, configs[i].tamanho, configs[i].tipo_entrada, quickSort_ListaEstatica,  quickSort_ListaDinamica,  out, verbose);
        rodar_algoritmo("MergeSort",     configs[i].dataset, configs[i].tamanho, configs[i].tipo_entrada, mergeSort_ListaEstatica,  mergeSort_ListaDinamica,  out, verbose);
        rodar_algoritmo("SelectionSort", configs[i].dataset, configs[i].tamanho, configs[i].tipo_entrada, selectionSort_ListaEstatica, selectionSort_ListaDinamica, out, verbose);
        rodar_algoritmo("InsertionSort", configs[i].dataset, configs[i].tamanho, configs[i].tipo_entrada, insertionSort_ListaEstatica, insertionSort_ListaDinamica, out, verbose);
    }
    
    fclose(out);
    if (verbose) {
        printf("\nFim dos testes. Resultados salvos em data/results.csv\n");
    }
}