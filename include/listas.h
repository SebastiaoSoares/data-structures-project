/**
 * @file listas.h
 * @brief Definições de estruturas de dados e protótipos de funções para o sistema de ranking de jogadores.
 *
 * Este arquivo centraliza as declarações necessárias para a manipulação de jogadores
 * em diferentes tipos de listas (estática e dinâmica). Inclui a definição da estrutura
 * `Jogador` e os protótipos de funções para operações CRUD (Criar, Ler, Atualizar, Deletar)
 * e gerenciamento de memória para ambas as implementações de lista.
 *
 */

#ifndef LISTAS_H
#define LISTAS_H

#include <stdbool.h> // Para o tipo booleano

/**
 * @brief Define o tamanho máximo para o nome do jogador.
 */

#define MAX_NOME_JOGADOR 50

/**
 * @brief Define a capacidade máxima da lista estática.
 * Esta constante é usada para pré-alocar memória para a lista estática.
 * 
 */

#define CAPACIDADE_LISTA_ESTATICA 10000

/**
 * @brief Estrutura que representa um jogador no sistema de ranking.
 *
 * Cada jogador possui um nome único, uma pontuação e um nível.
 * Estas informações são fundamentais para a ordenação e exibição no ranking.
 */

typedef struct {
    char nome[MAX_NOME_JOGADOR]; /**< Nome do jogador (string, máx. 49 caracteres + '\0'). */
    int pontuacao;               /**< Pontuação atual do jogador. */
    int nivel;                   /**< Nível atual do jogador. */
} Jogador;

// ===============================
// Declarações para Lista Estática
// ===============================

/**
 * @brief Estrutura para a lista estática de jogadores.
 *
 * Utiliza um array de tamanho fixo para armazenar os jogadores.
 * `n_elementos` controla o número de jogadores atualmente na lista.
 * 
 */

typedef struct {
    Jogador jogadores[CAPACIDADE_LISTA_ESTATICA]; /**< Array de jogadores. */
    int n_elementos;                              /**< Número de elementos atualmente na lista. */
} ListaEstatica;

/**
 * @brief Inicializa uma lista estática de jogadores.
 *
 * Define o contador de elementos da lista para zero, indicando que a lista está vazia.
 * @param lista Ponteiro para a estrutura `ListaEstatica` a ser inicializada.
 * *
 */

void inicializa_lista_estatica(ListaEstatica *lista);

/**
 * @brief Insere um novo jogador na lista estática.
 *
 * O jogador é adicionado ao final da lista, se houver espaço disponível.
 * 
 */

bool insere_lista_estatica(ListaEstatica *lista, Jogador jogador);

/**
 * @brief Imprime todos os jogadores contidos na lista estática.
 *
 * Percorre a lista do início ao fim, exibindo os detalhes de cada jogador.
 * 
 */

void imprime_lista_estatica(ListaEstatica *lista);

/**
 * @brief Busca um jogador na lista estática pelo nome.
 *
 * Realiza uma busca linear na lista para encontrar um jogador com o nome especificado.
 * 
*/

Jogador* busca_lista_estatica(ListaEstatica *lista, const char *nome);

/**
 * @brief Remove um jogador da lista estática pelo nome.
 *
 * Se o jogador for encontrado, ele é removido e os elementos subsequentes são deslocados
 * para preencher o espaço vazio, mantendo a integridade da lista.
 * 
 */

bool remove_lista_estatica(ListaEstatica *lista, const char *nome);

/**
 * @brief Libera os recursos associados a uma lista estática.
 *
 * Para listas estáticas, esta operação geralmente envolve apenas redefinir o contador
 * de elementos para zero, pois a memória é pré-alocada e não precisa ser liberada
 * explicitamente pelo programador.
 * 
 */

void libera_lista_estatica(ListaEstatica *lista);

// ===============================
// Declarações para Lista Dinâmica
// ===============================

/**
 * @brief Estrutura para um nó individual da lista dinâmica.
 *
 * Cada nó contém os dados de um `Jogador` e um ponteiro para o próximo nó na sequência,
 * formando uma lista encadeada.
 */

typedef struct No {
    Jogador jogador;    /**< Dados do jogador armazenados neste nó. */
    struct No *proximo; /**< Ponteiro para o próximo nó na lista. */
} No;

/**
 * @brief Estrutura para a lista dinâmica de jogadores.
 *
 * Contém um ponteiro para o primeiro nó (`inicio`) da lista e um contador
 * para o número total de elementos (`n_elementos`).
 * 
 */

typedef struct {
    No *inicio;       /**< Ponteiro para o primeiro nó da lista (cabeça da lista). */
    int n_elementos;  /**< Número de elementos atualmente na lista. */
} ListaDinamica;

/**
 * @brief Inicializa uma lista dinâmica de jogadores.
 *
 * Define o ponteiro de início da lista como `NULL` e o contador de elementos para zero,
 * indicando uma lista vazia.
 * 
 */

void inicializa_lista_dinamica(ListaDinamica *lista);

/**
 * @brief Insere um novo jogador na lista dinâmica.
 *
 * Um novo nó é alocado dinamicamente e o jogador é inserido no início da lista.
 * 
 */

bool insere_lista_dinamica(ListaDinamica *lista, Jogador jogador);

/**
 * @brief Imprime todos os jogadores contidos na lista dinâmica.
 *
 * Percorre a lista encadeada do início ao fim, exibindo os detalhes de cada jogador.
 * Se a lista estiver vazia, uma mensagem apropriada é exibida.
 * 
 */

void imprime_lista_dinamica(ListaDinamica *lista);

/**
 * @brief Busca um jogador na lista dinâmica pelo nome.
 *
 * Realiza uma busca linear na lista encadeada para encontrar um jogador com o nome especificado.
 * 
 */

Jogador* busca_lista_dinamica(ListaDinamica *lista, const char *nome);

/**
 * @brief Remove um jogador da lista dinâmica pelo nome.
 *
 * Se o jogador for encontrado, o nó correspondente é liberado da memória e os ponteiros
 * da lista são ajustados para manter a sequência.
 */

bool remove_lista_dinamica(ListaDinamica *lista, const char *nome);

/**
 * @brief Libera todos os nós de uma lista dinâmica.
 *
 * Percorre a lista encadeada, liberando a memória alocada para cada nó e redefinindo
 * a lista para um estado vazio (`inicio` = `NULL`, `n_elementos` = 0).
 * 
 */

void libera_lista_dinamica(ListaDinamica *lista);

#endif // LISTAS_H
