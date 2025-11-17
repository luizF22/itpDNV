#ifndef SEQUENCIA_H
#define SEQUENCIA_H

#include <cstddef>  // Para size_t

// Template serve de forma para diferentes componentes
// O template gera código específico para cada tipo em tempo de compilação, mantendo type safety enquanto permite reuso máximo.
template <typename T> // T é um placeholder de qualquer tipo, podendo ser qualquer coisa
class Sequencia {
private:
    T* dados; // Ponteiro para QUALQUER tipo que substituir T
    size_t capacidade;
    size_t tamanho;
    void redimensionar(size_t nova_capacidade);

public:
    // Construtores
    Sequencia();
    Sequencia(size_t capacidade_inicial);
    
    // Destrutor
    ~Sequencia(); // Impede vazamento de memória
    
    // Métodos exigidos pelos testes
    size_t obterTamanho() const;
    void adicionar(const T& elemento);
    void removerUltimo();
    T& operator[](size_t indice);
    const T& operator[](size_t indice) const;
};

// Incluir implementação do template
#include "sequencia_impl.h"

#endif