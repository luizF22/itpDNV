#ifndef SEQUENCIA_IMPL_H
#define SEQUENCIA_IMPL_H

#include "sequencia.h"
#include <stdexcept>  // Para std::out_of_range

template <typename T>
Sequencia<T>::Sequencia() : capacidade(10), tamanho(0) {
    dados = new T[capacidade];
}

template <typename T>
Sequencia<T>::Sequencia(size_t capacidade_inicial) 
    : capacidade(capacidade_inicial), tamanho(0) {
    dados = new T[capacidade];
}

template <typename T>
Sequencia<T>::~Sequencia() {
    delete[] dados;
}

template <typename T>
size_t Sequencia<T>::obterTamanho() const {
    return tamanho;
}

template <typename T>
void Sequencia<T>::adicionar(const T& elemento) {
    if (tamanho >= capacidade) {
        redimensionar(capacidade * 2);  // Dobra a capacidade -> complexidade O(n), ao invés de O(n²)
        /*
        A complexidade O(n²) aconteceria porque toda vez que a capacidade fosse alterada, ela iria redimensionar e copiar.
        Se isso fosse feito todas as vezes para n entradas diferentes, executaríamos n*n passos.
        No estado atual, toda vez que a entrada é excedida, ela é duplicada, reduzindo o número de passos à duplicação.
        */
    }
    dados[tamanho] = elemento;
    tamanho++;
}

template <typename T>
void Sequencia<T>::removerUltimo() {
    if (tamanho > 0) {
        tamanho--;
    }
}

template <typename T>
T& Sequencia<T>::operator[](size_t indice) {
    if (indice >= tamanho) {
        throw std::out_of_range("Índice fora do intervalo");
    }
    return dados[indice];
}

template <typename T>
const T& Sequencia<T>::operator[](size_t indice) const {
    /*
    T& Retorna uma REFERÊNCIA ao elemento (permite modificação)
    operator[]: Sobrecarga do operador de índice
    Lança mensagem de erro
    */
    if (indice >= tamanho) {
        throw std::out_of_range("Índice fora do intervalo");
    }
    return dados[indice];
}

template <typename T>
void Sequencia<T>::redimensionar(size_t nova_capacidade) {
    T* novos_dados = new T[nova_capacidade];
    
    // Copiar elementos antigos
    for (size_t i = 0; i < tamanho; i++) {
        novos_dados[i] = dados[i];
    }
    
    // Liberar array antigo e atualizar
    delete[] dados;
    dados = novos_dados;
    capacidade = nova_capacidade;
}

#endif