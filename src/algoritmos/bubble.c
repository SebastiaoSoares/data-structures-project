/**
 * @file bubble.c
 * @brief Implementação do algoritmo Bubble Sort para as listas do ranking.
 */

#include <stdio.h>
#include <stdbool.h>
#include "../../include/listas.h"


// BUBBLE SORT - LISTA ESTÁTICA

void bubbleSort_ListaEstatica(ListaEstatica *lista) {

    if (lista == NULL || lista->n_elementos <= 1) {
        return;
    }

    int trocou;
    int n = lista->n_elementos;

    do {
        trocou = 0;

        for (int i = 0; i < n - 1; i++) {
            if (lista->jogadores[i].pontuacao < lista->jogadores[i + 1].pontuacao) {
                
                Jogador temp = lista->jogadores[i];
                lista->jogadores[i] = lista->jogadores[i + 1];
                lista->jogadores[i + 1] = temp;
                
                trocou = 1;
            }
        }

        n--; 
    } while (trocou);
}


// BUBBLE SORT - LISTA DINÂMICA

void bubbleSort_ListaDinamica(ListaDinamica *lista) {

    if (lista == NULL || lista->inicio == NULL || lista->inicio->proximo == NULL) {
        return;
    }

    int trocou;
    No *atual;
    No *ultimo_verificado = NULL;

    do {
        trocou = 0;
        atual = lista->inicio;

        while (atual->proximo != ultimo_verificado) {
            
            if (atual->jogador.pontuacao < atual->proximo->jogador.pontuacao) {
                
                Jogador temp = atual->jogador;
                atual->jogador = atual->proximo->jogador;
                atual->proximo->jogador = temp;
                
                trocou = 1;
            }
            atual = atual->proximo;
        }

        ultimo_verificado = atual;
        
    } while (trocou);
}