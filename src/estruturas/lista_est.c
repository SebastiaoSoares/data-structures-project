/**
 * @file lista_est.c
 * @brief Implementação das funções para manipulação de uma lista estática de jogadores.
 *
 * Este arquivo contém a implementação detalhada das operações CRUD (Criar, Ler, Atualizar, Deletar)
 * para a estrutura de dados `ListaEstatica`, conforme definido em `listas.h`. 
 *
 */

#include "listas.h" // Inclui o cabeçalho com as definições de estruturas e protótipos
#include <stdio.h>  // Para funções de entrada/saída como printf
#include <string.h> // Para funções de manipulação de strings como strcmp e strcpy

/**
 * @brief Inicializa uma lista estática de jogadores.
 *
 * Define o número de elementos da lista para zero, indicando que a lista está vazia
 * e pronta para receber novos jogadores. Esta função deve ser chamada antes de qualquer
 * outra operação na lista.
 * *
 */

void inicializa_lista_estatica(ListaEstatica *lista) {
    if (lista != NULL) {
        lista->n_elementos = 0;
        // Não é necessário limpar a memória do array, pois os elementos serão sobrescritos.
    }
}

/**
 * @brief Insere um novo jogador na lista estática.
 *
 * O jogador é adicionado ao final da lista, se houver espaço disponível. (Visto em aula)
 * Antes da inserção, verifica-se se a lista não atingiu sua capacidade máxima.
 * @param jogador A estrutura `Jogador` a ser inserida. Os dados do jogador são copiados.
 * @return `true` se a inserção foi bem-sucedida.
 * @return `false` se a lista estiver cheia e o jogador não puder ser inserido.
 */

bool insere_lista_estatica(ListaEstatica *lista, Jogador jogador) {
    if (lista == NULL) {
        fprintf(stderr, "Erro: Lista estática não inicializada (ponteiro NULL) ao tentar inserir.\n");
        return false;
    }
    if (lista->n_elementos >= CAPACIDADE_LISTA_ESTATICA) {
        fprintf(stderr, "Erro: Lista estática cheia. Não é possível inserir mais jogadores.\n");
        return false; // Lista cheia
    }
    // Copia os dados do jogador para a próxima posição disponível no array
    strcpy(lista->jogadores[lista->n_elementos].nome, jogador.nome);
    lista->jogadores[lista->n_elementos].pontuacao = jogador.pontuacao;
    lista->jogadores[lista->n_elementos].nivel = jogador.nivel;
    lista->n_elementos++; // Incrementa o contador de elementos
    return true;
}

/**
 * @brief Imprime todos os jogadores contidos na lista estática.
 *
 * Percorre a lista do início ao fim, exibindo os detalhes (nome, pontuação, nível)
 * de cada jogador. Se a lista estiver vazia, uma mensagem apropriada é exibida.
 * 
 */

void imprime_lista_estatica(ListaEstatica *lista) {
    if (lista == NULL) {
        fprintf(stderr, "Erro: Lista estática não inicializada (ponteiro NULL) ao tentar imprimir.\n");
        return;
    }
    printf("\n--- Ranking (Lista Estática) ---\n");
    if (lista->n_elementos == 0) {
        printf("A lista está vazia.\n");
        return;
    }
    for (int i = 0; i < lista->n_elementos; i++) {
        printf("  %d. Nome: %s, Pontuação: %d, Nível: %d\n",
               i + 1,
               lista->jogadores[i].nome,
               lista->jogadores[i].pontuacao,
               lista->jogadores[i].nivel);
    }
    printf("-----------------------------------\n");
}

/**
 * @brief Busca um jogador na lista estática pelo nome.
 *
 * Realiza uma busca linear na lista para encontrar um jogador com o nome especificado.
 * @param lista Ponteiro para a `ListaEstatica` onde a busca será realizada.
 * @param nome String constante contendo o nome do jogador a ser buscado.
 * @return Ponteiro para a estrutura `Jogador` encontrada.
 * @return `NULL` se o jogador não for encontrado na lista ou se a lista for inválida.
 */

Jogador* busca_lista_estatica(ListaEstatica *lista, const char *nome) {
    if (lista == NULL || nome == NULL) {
        fprintf(stderr, "Erro: Lista ou nome inválido (ponteiro NULL) ao tentar buscar.\n");
        return NULL;
    }
    for (int i = 0; i < lista->n_elementos; i++) {
        if (strcmp(lista->jogadores[i].nome, nome) == 0) {
            return &lista->jogadores[i]; // Retorna o endereço do jogador encontrado
        }
    }
    return NULL; // Jogador não encontrado
}

/**
 * @brief Remove um jogador da lista estática pelo nome.
 *
 * Se o jogador for encontrado, ele é removido e os elementos subsequentes são deslocados
 * uma posição para trás para preencher o espaço vazio, mantendo a contiguidade da lista.
 * @param lista Ponteiro para a `ListaEstatica` onde o jogador será removido.
 * @param nome String constante contendo o nome do jogador a ser removido.
 * @return `true` se a remoção foi bem-sucedida.
 * @return `false` se o jogador não foi encontrado na lista ou se a lista for inválida.
 */

bool remove_lista_estatica(ListaEstatica *lista, const char *nome) {
    if (lista == NULL || nome == NULL) {
        fprintf(stderr, "Erro: Lista ou nome inválido (ponteiro NULL) ao tentar remover.\n");
        return false;
    }
    int i, j;
    for (i = 0; i < lista->n_elementos; i++) {
        if (strcmp(lista->jogadores[i].nome, nome) == 0) {
            // Jogador encontrado, agora remove e desloca os elementos subsequentes
            for (j = i; j < lista->n_elementos - 1; j++) {
                lista->jogadores[j] = lista->jogadores[j+1];
            }
            lista->n_elementos--; // Decrementa o contador de elementos
            return true;
        }
    }
    fprintf(stderr, "Aviso: Jogador '%s' não encontrado na lista estática para remoção.\n", nome);
    return false; // Jogador não encontrado
}

/**
 * @brief Libera os recursos associados a uma lista estática.
 *
 * Para listas estáticas, esta função redefine o contador de elementos para zero,
 * efetivamente "esvaziando" a lista.
 * 
 */

void libera_lista_estatica(ListaEstatica *lista) {
    if (lista != NULL) {
        lista->n_elementos = 0; // Simplesmente "esvazia" a lista estática
        // Não há memória alocada dinamicamente para liberar aqui.
    }
}