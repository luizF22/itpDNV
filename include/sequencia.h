#ifndef SEQUENCIA_H
#define SEQUENCIA_H

#include <cstddef>  // Para size_t

/**
 * @brief Classe Template para gerenciamento de arrays dinâmicos.
 * 
 * @details Funciona como um std::vector simplificado. Permite armazenar qualquer tipo de dado (T)
 * de forma contígua na memória, com redimensionamento automático.
 * 
 * @tparam T O tipo de dado que será armazenado na sequência.
 */

// Template serve de forma para diferentes componentes
// O template gera código específico para cada tipo em tempo de compilação, mantendo type safety enquanto permite reuso máximo.
template <typename T> // T é um placeholder de qualquer tipo, podendo ser qualquer coisa

class Sequencia {
private:
    T* dados; // Ponteiro para QUALQUER tipo que substituir T
    size_t capacidade;
    size_t tamanho;
    /**
     * @brief Redimensiona o array interno quando a capacidade é excedida.
     * @param nova_capacidade O novo tamanho total a ser alocado.
     */
    void redimensionar(size_t nova_capacidade);

public:
    // Construtores
    /**
     * @brief Construtor padrão. Inicia com capacidade mínima.
     */
    Sequencia();
    /**
     * @brief Construtor com capacidade inicial definida.
     * @details Útil para evitar realocações se o tamanho final for conhecido.
     * @param capacidade_inicial Quantidade de slots a pré-alocar.
     */
    Sequencia(size_t capacidade_inicial);
    
    // Destrutor
    /**
     * @brief Destrutor. Libera a memória alocada para o array.
     */
    ~Sequencia(); // Impede vazamento de memória
    
    // Métodos exigidos pelos testes
    /**
     * @brief Retorna a quantidade de elementos armazenados.
     * @return Tamanho atual da sequência.
     */
    size_t obterTamanho() const;
    /**
     * @brief Adiciona um novo elemento ao final da sequência.
     * @details Se necessário, redimensiona o array automaticamente.
     * @param elemento O dado do tipo T a ser inserido.
     */
    void adicionar(const T& elemento);
    /**
     * @brief Remove o último elemento da sequência.
     * @details Apenas decrementa o contador de tamanho, não libera memória.
     */
    void removerUltimo();
    /**
     * @brief Acesso a elemento via índice (Leitura/Escrita).
     * @param indice Posição desejada (sem verificação de limites).
     * @return Referência ao elemento.
     */
    T& operator[](size_t indice);
    /**
     * @brief Acesso a elemento via índice (Somente Leitura).
     * @param indice Posição desejada.
     * @return Referência constante ao elemento.
     */
    const T& operator[](size_t indice) const;
};

// Incluir implementação do template
#include "sequencia_impl.h"

#endif