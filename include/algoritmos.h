/**
 * @file algoritmos.h
 * @brief Declaração das funções de ordenação para o sistema de ranking de jogadores.
 *
 * Centralização dos protótipos de todos os algoritmos de ordenação
 * exigidos para o projeto (Bubble, Quick, Merge, Selection e Insertion Sort).
 */

#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "listas.h"


// BUBBLE SORT

/**
 * @brief Ordena a lista estática em ordem decrescente de pontuação usando Bubble Sort.
 */
void bubbleSort_ListaEstatica(ListaEstatica *lista);

/**
 * @brief Ordena a lista dinâmica em ordem decrescente de pontuação usando Bubble Sort.
 */
void bubbleSort_ListaDinamica(ListaDinamica *lista);


// QUICK SORT

/**
 * @brief Ordena a lista estática em ordem decrescente de pontuação usando Quick Sort.
 */
void quickSort_ListaEstatica(ListaEstatica *lista);

/**
 * @brief Ordena a lista dinâmica em ordem decrescente de pontuação usando Quick Sort.
 */
void quickSort_ListaDinamica(ListaDinamica *lista);


// MERGE SORT

/**
 * @brief Ordena a lista estática em ordem decrescente de pontuação usando Merge Sort.
 */
void mergeSort_ListaEstatica(ListaEstatica *lista);

/**
 * @brief Ordena a lista dinâmica em ordem decrescente de pontuação usando Merge Sort.
 */
void mergeSort_ListaDinamica(ListaDinamica *lista);


// SELECTION SORT

/**
 * @brief Ordena a lista estática em ordem decrescente de pontuação usando Selection Sort.
 */
void selectionSort_ListaEstatica(ListaEstatica *lista);

/**
 * @brief Ordena a lista dinâmica em ordem decrescente de pontuação usando Selection Sort.
 */
void selectionSort_ListaDinamica(ListaDinamica *lista);


// INSERTION SORT

/**
 * @brief Ordena a lista estática em ordem decrescente de pontuação usando Insertion Sort.
 */
void insertionSort_ListaEstatica(ListaEstatica *lista);

/**
 * @brief Ordena a lista dinâmica em ordem decrescente de pontuação usando Insertion Sort.
 */
void insertionSort_ListaDinamica(ListaDinamica *lista);

#endif // ALGORITMOS_H