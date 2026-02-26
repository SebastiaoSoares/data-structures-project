/**
 * @file insertion.c
 * @brief Implementação do algoritmo Insertion Sort para as listas do ranking.
 */

#include <stdio.h>
#include <stdbool.h>
#include "../../include/listas.h"


// INSERTION SORT - LISTA ESTÁTICA

void insertionSort_ListaEstatica(ListaEstatica *lista) {

    if (lista == NULL || lista->n_elementos <= 1) {
        return;
    }

    int n = lista->n_elementos;

    for (int i = 1; i < n; i++) {
        Jogador chave = lista->jogadores[i];
        int j = i - 1;

        while (j >= 0 && lista->jogadores[j].pontuacao < chave.pontuacao) {
            lista->jogadores[j + 1] = lista->jogadores[j];
            j = j - 1;
        }
        
        lista->jogadores[j + 1] = chave;
    }
}


// INSERTION SORT - LISTA DINÂMICA

void inserirOrdenado(No **cabeca_ordenada, No *novo_no) {

    if (*cabeca_ordenada == NULL || (*cabeca_ordenada)->jogador.pontuacao <= novo_no->jogador.pontuacao) {
        novo_no->proximo = *cabeca_ordenada;
        *cabeca_ordenada = novo_no;
    } else {
        No *atual = *cabeca_ordenada;
        while (atual->proximo != NULL && atual->proximo->jogador.pontuacao > novo_no->jogador.pontuacao) {
            atual = atual->proximo;
        }
        
        novo_no->proximo = atual->proximo;
        atual->proximo = novo_no;
    }
}

void insertionSort_ListaDinamica(ListaDinamica *lista) {

    if (lista == NULL || lista->inicio == NULL || lista->inicio->proximo == NULL) {
        return;
    }

    No *ordenada = NULL;

    No *atual = lista->inicio;

    while (atual != NULL) {
        No *proximo = atual->proximo;

        inserirOrdenado(&ordenada, atual);

        atual = proximo;
    }

    lista->inicio = ordenada;
}