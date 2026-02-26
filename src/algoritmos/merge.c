/**
 * @file merge.c
 * @brief Implementação do algoritmo Merge Sort para as listas do ranking.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../include/listas.h"


// MERGE SORT - LISTA ESTÁTICA

void merge_Estatico(Jogador arr[], int esq, int meio, int dir) {
    int i, j, k;
    int n1 = meio - esq + 1;
    int n2 = dir - meio;

    Jogador *L = (Jogador *)malloc(n1 * sizeof(Jogador));
    Jogador *R = (Jogador *)malloc(n2 * sizeof(Jogador));

    for (i = 0; i < n1; i++)
        L[i] = arr[esq + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[meio + 1 + j];

    i = 0;
    j = 0;
    k = esq;

    while (i < n1 && j < n2) {
        if (L[i].pontuacao >= R[j].pontuacao) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort_Estatico_Recursivo(Jogador arr[], int esq, int dir) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;

        mergeSort_Estatico_Recursivo(arr, esq, meio);
        mergeSort_Estatico_Recursivo(arr, meio + 1, dir);

        merge_Estatico(arr, esq, meio, dir);
    }
}

void mergeSort_ListaEstatica(ListaEstatica *lista) {
    if (lista == NULL || lista->n_elementos <= 1) {
        return;
    }
    mergeSort_Estatico_Recursivo(lista->jogadores, 0, lista->n_elementos - 1);
}


// MERGE SORT - LISTA DINÂMICA

No* merge_Dinamico(No* a, No* b) {
    No* resultado = NULL;

    if (a == NULL) return b;
    if (b == NULL) return a;

    if (a->jogador.pontuacao >= b->jogador.pontuacao) {
        resultado = a;
        resultado->proximo = merge_Dinamico(a->proximo, b);
    } else {
        resultado = b;
        resultado->proximo = merge_Dinamico(a, b->proximo);
    }
    return resultado;
}

void split_Dinamico(No* fonte, No** frenteRef, No** trasRef) {
    No* rapido;
    No* lento;
    lento = fonte;
    rapido = fonte->proximo;

    while (rapido != NULL) {
        rapido = rapido->proximo;
        if (rapido != NULL) {
            lento = lento->proximo;
            rapido = rapido->proximo;
        }
    }

    *frenteRef = fonte;
    *trasRef = lento->proximo;
    lento->proximo = NULL;
}

void mergeSort_Dinamico_Recursivo(No** refCabeca) {
    No* cabeca = *refCabeca;
    No* a;
    No* b;

    if ((cabeca == NULL) || (cabeca->proximo == NULL)) {
        return;
    }

    split_Dinamico(cabeca, &a, &b);

    mergeSort_Dinamico_Recursivo(&a);
    mergeSort_Dinamico_Recursivo(&b);

    *refCabeca = merge_Dinamico(a, b);
}

void mergeSort_ListaDinamica(ListaDinamica *lista) {
    if (lista == NULL || lista->inicio == NULL || lista->inicio->proximo == NULL) {
        return;
    }

    mergeSort_Dinamico_Recursivo(&(lista->inicio));
}