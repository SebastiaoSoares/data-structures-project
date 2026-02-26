/**
 * @file selection.c
 * @brief Implementação do algoritmo Selection Sort para as listas do ranking.
 */

#include <stdio.h>
#include <stdbool.h>
#include "../../include/listas.h"


// SELECTION SORT - LISTA ESTÁTICA

void selectionSort_ListaEstatica(ListaEstatica *lista) {

    if (lista == NULL || lista->n_elementos <= 1) {
        return;
    }

    int n = lista->n_elementos;

    for (int i = 0; i < n - 1; i++) {

        int max_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (lista->jogadores[j].pontuacao > lista->jogadores[max_idx].pontuacao) {
                max_idx = j;
            }
        }

        if (max_idx != i) {
            Jogador temp = lista->jogadores[i];
            lista->jogadores[i] = lista->jogadores[max_idx];
            lista->jogadores[max_idx] = temp;
        }
    }
}


// SELECTION SORT - LISTA DINÂMICA

void selectionSort_ListaDinamica(ListaDinamica *lista) {
    if (lista == NULL || lista->inicio == NULL || lista->inicio->proximo == NULL) {
        return;
    }

    for (No *atual = lista->inicio; atual->proximo != NULL; atual = atual->proximo) {
        
        No *max_no = atual;

        for (No *seguinte = atual->proximo; seguinte != NULL; seguinte = seguinte->proximo) {
            if (seguinte->jogador.pontuacao > max_no->jogador.pontuacao) {
                max_no = seguinte;
            }
        }

        if (max_no != atual) {
            Jogador temp = atual->jogador;
            atual->jogador = max_no->jogador;
            max_no->jogador = temp;
        }
    }
}