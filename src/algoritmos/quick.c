/**
 * @file quick.c
 * @brief Implementação do algoritmo Quick Sort para as listas do ranking.
 */

#include <stdio.h>
#include <stdbool.h>
#include "../../include/listas.h"


// FUNÇÕES AUXILIARES COMUNS

void troca_Jogadores(Jogador *a, Jogador *b) {
    Jogador temp = *a;
    *a = *b;
    *b = temp;
}


// QUICK SORT - LISTA ESTÁTICA

int particiona_Estatico(Jogador arr[], int baixo, int alto) {

    int pivo = arr[alto].pontuacao; 
    int i = (baixo - 1);

    for (int j = baixo; j <= alto - 1; j++) {
        if (arr[j].pontuacao > pivo) {
            i++;
            troca_Jogadores(&arr[i], &arr[j]);
        }
    }

    troca_Jogadores(&arr[i + 1], &arr[alto]);
    return (i + 1);
}

void quickSort_Estatico_Recursivo(Jogador arr[], int baixo, int alto) {
    if (baixo < alto) {
        int pi = particiona_Estatico(arr, baixo, alto);

        quickSort_Estatico_Recursivo(arr, baixo, pi - 1);
        quickSort_Estatico_Recursivo(arr, pi + 1, alto);
    }
}

void quickSort_ListaEstatica(ListaEstatica *lista) {
    if (lista == NULL || lista->n_elementos <= 1) {
        return;
    }
    quickSort_Estatico_Recursivo(lista->jogadores, 0, lista->n_elementos - 1);
}


// QUICK SORT - LISTA DINÂMICA

No* particiona_Dinamico(No *inicio, No *fim) {

    int pivo = fim->jogador.pontuacao;
    No *i = inicio;

    for (No *j = inicio; j != fim; j = j->proximo) {
        if (j->jogador.pontuacao > pivo) {
            troca_Jogadores(&(i->jogador), &(j->jogador));
            i = i->proximo;
        }
    }

    troca_Jogadores(&(i->jogador), &(fim->jogador));
    return i;
}

void quickSort_Dinamico_Recursivo(No *inicio, No *fim) {
    if (inicio != NULL && inicio != fim && inicio != fim->proximo) {

        No *pivo = particiona_Dinamico(inicio, fim);

        No *atual = inicio;
        No *anterior_ao_pivo = NULL;
        while (atual != pivo && atual != NULL) {
            anterior_ao_pivo = atual;
            atual = atual->proximo;
        }

        if (anterior_ao_pivo != NULL) {
            quickSort_Dinamico_Recursivo(inicio, anterior_ao_pivo);
        }
        
        quickSort_Dinamico_Recursivo(pivo->proximo, fim);
    }
}

No* getUltimoNo(No *inicio) {
    No *atual = inicio;
    while (atual != NULL && atual->proximo != NULL) {
        atual = atual->proximo;
    }
    return atual;
}

void quickSort_ListaDinamica(ListaDinamica *lista) {
    if (lista == NULL || lista->inicio == NULL || lista->inicio->proximo == NULL) {
        return;
    }
    No *fim = getUltimoNo(lista->inicio);
    quickSort_Dinamico_Recursivo(lista->inicio, fim);
}