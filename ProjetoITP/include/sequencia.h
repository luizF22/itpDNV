#ifndef SEQUENCIA_H
#define SEQUENCIA_H

#include <cstddef>  // Para size_t

template <typename T>
class Sequencia {
private:
    T* dados;
    size_t capacidade;
    size_t tamanho;
    void redimensionar(size_t nova_capacidade);

public:
    // Construtores
    Sequencia();
    Sequencia(size_t capacidade_inicial);
    
    // Destrutor
    ~Sequencia();
    
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