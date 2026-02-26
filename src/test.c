/**
 * @file main.c
 * @brief Programa para testar as operações básicas das listas e a ordenação.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/listas.h"
#include "../include/algoritmos.h"

Jogador criar_jogador(const char *nome, int pontuacao, int nivel) {
    Jogador j;
    snprintf(j.nome, MAX_NOME_JOGADOR, "%s", nome);
    j.pontuacao = pontuacao;
    j.nivel = nivel;
    return j;
}

int main() {
    printf("=========================================\n");
    printf("      TESTE DA LISTA ESTATICA\n");
    printf("=========================================\n");

    ListaEstatica lista_est;
    inicializa_lista_estatica(&lista_est);

    insere_lista_estatica(&lista_est, criar_jogador("Aisha", 1500, 10));
    insere_lista_estatica(&lista_est, criar_jogador("Sabrina", 3200, 25));
    insere_lista_estatica(&lista_est, criar_jogador("Kauan", 800, 5));
    insere_lista_estatica(&lista_est, criar_jogador("Ramona", 4500, 30));
    insere_lista_estatica(&lista_est, criar_jogador("Sebastião", 800, 5));
    insere_lista_estatica(&lista_est, criar_jogador("Ramom", 4500, 30));

    printf("\n[1] Apos Insercoes:\n");
    imprime_lista_estatica(&lista_est);

    printf("\n[2] Buscar jogador 'Ramom':\n");
    Jogador *encontrado_est = busca_lista_estatica(&lista_est, "Ramom");
    if (encontrado_est != NULL) {
        printf(" -> Encontrado! Pontuacao: %d, Nivel: %d\n", encontrado_est->pontuacao, encontrado_est->nivel);
    } else {
        printf(" -> Nao encontrado.\n");
    }

    printf("\n[3] Remover jogador 'Pedro':\n");
    if (remove_lista_estatica(&lista_est, "Pedro")) {
        printf(" -> 'Pedro' removido com sucesso.\n");
    }
    imprime_lista_estatica(&lista_est);

    printf("\n[4] Ordenar Lista Estatica (Bubble Sort - Decrescente):\n");
    bubbleSort_ListaEstatica(&lista_est);
    imprime_lista_estatica(&lista_est);

    libera_lista_estatica(&lista_est);


    printf("\n\n=========================================\n");
    printf("      TESTE DA LISTA DINAMICA\n");
    printf("=========================================\n");

    ListaDinamica lista_din;
    inicializa_lista_dinamica(&lista_din);

    insere_lista_dinamica(&lista_din, criar_jogador("Sabrina", 2100, 15));
    insere_lista_dinamica(&lista_din, criar_jogador("Sebastiao", 300, 2));
    insere_lista_dinamica(&lista_din, criar_jogador("Lucas", 5000, 40));
    insere_lista_dinamica(&lista_din, criar_jogador("Maria", 1200, 8));

    printf("\n[1] Apos Insercoes:\n");
    imprime_lista_dinamica(&lista_din);

    printf("\n[2] Buscar jogador 'Sabrina':\n");
    Jogador *encontrado_din = busca_lista_dinamica(&lista_din, "Sabrina");
    if (encontrado_din != NULL) {
        printf(" -> Encontrada! Pontuacao: %d, Nivel: %d\n", encontrado_din->pontuacao, encontrado_din->nivel);
    } else {
        printf(" -> Nao encontrada.\n");
    }

    printf("\n[3] Remover jogador 'Sebastiao':\n");
    if (remove_lista_dinamica(&lista_din, "Sebastiao")) {
        printf(" -> 'Sebastiao' removido com sucesso.\n");
    }
    imprime_lista_dinamica(&lista_din);

    printf("\n[4] Ordenar Lista Dinamica (Merge Sort - Decrescente):\n");
    mergeSort_ListaDinamica(&lista_din);
    imprime_lista_dinamica(&lista_din);

    libera_lista_dinamica(&lista_din);
    printf("\nMemoria da Lista Dinamica libertada com sucesso.\n");

    return 0;
}