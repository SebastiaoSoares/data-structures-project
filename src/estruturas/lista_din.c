/**
 * @file lista_din.c
 * @brief Implementação das funções para manipulação de uma lista dinâmica de jogadores.
 *
 * Este arquivo contém a implementação detalhada das operações CRUD (Criar, Ler, Atualizar, Deletar)
 * para a estrutura de dados `ListaDinamica`, conforme definido em `listas.h`. 
 *
 */

#include "listas.h" // Inclui o cabeçalho com as definições de estruturas e protótipos
#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 

/**
 * @brief Inicializa uma lista dinâmica de jogadores.
 *
 * Define o ponteiro de início da lista como `NULL` e o contador de elementos para zero,
 * indicando que a lista está vazia e pronta para receber novos jogadores. 
 * OBS: DEVE SER CHAMADA ANTES DE QUALQUER FUNÇÃO DA LISTA
 * @param lista Ponteiro para a estrutura `ListaDinamica` a ser inicializada.
 *
 */

void inicializa_lista_dinamica(ListaDinamica *lista) {
    if (lista != NULL) {
        lista->inicio = NULL;
        lista->n_elementos = 0;
    }
}

/**
 * @brief Insere um novo jogador na lista dinâmica.
 *
 * @param lista Ponteiro para a `ListaDinamica` onde o jogador será inserido.
 * @param jogador A estrutura `Jogador` a ser inserida. Os dados do jogador são copiados.
 * @return `true` se a inserção foi bem-sucedida.
 * @return `false` se houver falha na alocação de memória para o novo nó.
 *
 */

bool insere_lista_dinamica(ListaDinamica *lista, Jogador jogador) {
    if (lista == NULL) {
        fprintf(stderr, "Erro: Lista dinâmica não inicializada (ponteiro NULL) ao tentar inserir.\n");
        return false;
    }
    No *novoNo = (No*) malloc(sizeof(No));
    if (novoNo == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória para novo nó na lista dinâmica.\n");
        return false; // Falha na alocação de memória
    }
    
    // Copia os dados do jogador para o novo nó
    strcpy(novoNo->jogador.nome, jogador.nome);
    novoNo->jogador.pontuacao = jogador.pontuacao;
    novoNo->jogador.nivel = jogador.nivel;

    novoNo->proximo = lista->inicio; 
    lista->inicio = novoNo;         
    lista->n_elementos++;          
    return true;
}

/**
 * @brief Imprime todos os jogadores contidos na lista dinâmica.
 *
 * Percorre a lista encadeada do início ao fim, exibindo os detalhes (nome, pontuação, nível)
 * de cada jogador. Se a lista estiver vazia, uma mensagem apropriada é exibida.
 * @param lista Ponteiro para a `ListaDinamica` a ser impressa.
 *
 */

void imprime_lista_dinamica(ListaDinamica *lista) {
    if (lista == NULL) {
        fprintf(stderr, "Erro: Lista dinâmica não inicializada (ponteiro NULL) ao tentar imprimir.\n");
        return;
    }
    printf("\n--- Ranking (Lista Dinâmica) ---\n");
    if (lista->inicio == NULL) {
        printf("A lista está vazia.\n");
        return;
    }
    No *atual = lista->inicio;
    int contador = 1;
    while (atual != NULL) {
        printf("  %d. Nome: %s, Pontuação: %d, Nível: %d\n",
               contador,
               atual->jogador.nome,
               atual->jogador.pontuacao,
               atual->jogador.nivel);
        atual = atual->proximo;
        contador++;
    }
    printf("-------------------------------------\n");
}

/**
 * @brief Busca um jogador na lista dinâmica pelo nome.
 *
 * Realiza uma busca linear na lista encadeada para encontrar um jogador com o nome especificado.
 * @param lista Ponteiro para a `ListaDinamica` onde a busca será realizada.
 * @param nome String constante contendo o nome do jogador a ser buscado.
 * @return Ponteiro para a estrutura `Jogador` encontrada.
 * @return `NULL` se o jogador não for encontrado na lista ou se a lista for inválida.
 *
 */
Jogador* busca_lista_dinamica(ListaDinamica *lista, const char *nome) {
    if (lista == NULL || nome == NULL) {
        fprintf(stderr, "Erro: Lista ou nome inválido (ponteiro NULL) ao tentar buscar.\n");
        return NULL;
    }
    No *atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->jogador.nome, nome) == 0) {
            return &atual->jogador; 
        }
        atual = atual->proximo;
    }
    return NULL; // Jogador não encontrado
}

/**
 * @brief Remove um jogador da lista dinâmica pelo nome.
 *
 * Se o jogador for encontrado, o nó correspondente é liberado da memória e os ponteiros
 * da lista são ajustados para manter a sequência. 
 *
 * @param lista Ponteiro para a `ListaDinamica` onde o jogador será removido.
 * @param nome String constante contendo o nome do jogador a ser removido.
 * @return `true` se a remoção foi bem-sucedida.
 * @return `false` se o jogador não foi encontrado na lista ou se a lista for inválida.
 *
 */
bool remove_lista_dinamica(ListaDinamica *lista, const char *nome) {
    if (lista == NULL || nome == NULL) {
        fprintf(stderr, "Erro: Lista ou nome inválido (ponteiro NULL) ao tentar remover.\n");
        return false;
    }
    No *atual = lista->inicio;
    No *anterior = NULL;

    // Percorre a lista para encontrar o jogador e manter o ponteiro para o nó anterior
    while (atual != NULL && strcmp(atual->jogador.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        fprintf(stderr, "Aviso: Jogador \'%s\' não encontrado na lista dinâmica para remoção.\n", nome);
        return false; // Jogador não encontrado
    }

    // Se o jogador a ser removido é o primeiro nó (anterior é NULL)
    if (anterior == NULL) {
        lista->inicio = atual->proximo; 
    } else {
        anterior->proximo = atual->proximo; 
    }

    free(atual); // Libera a memória do nó removido
    lista->n_elementos--; 
    return true;
}

/**
 * @brief Libera todos os nós de uma lista dinâmica.
 *
 * Percorre a lista encadeada do início ao fim, liberando a memória alocada para cada nó.
 * Após a liberação, a lista é redefinida para um estado vazio (`inicio` = `NULL`, `n_elementos` = 0).
 * Evita vazamentos de memória na lista.
 *
 */
void libera_lista_dinamica(ListaDinamica *lista) {
    if (lista == NULL) {
        fprintf(stderr, "Erro: Lista dinâmica não inicializada (ponteiro NULL) ao tentar liberar.\n");
        return;
    }
    No *atual = lista->inicio;
    No *proximo;
    while (atual != NULL) {
        proximo = atual->proximo; 
        free(atual);              
        atual = proximo;          
    }
    lista->inicio = NULL;       // Garante que a lista esteja vazia
    lista->n_elementos = 0;      // Reseta o contador de elementos
}
