/*
    Arquivo.hex → Parser → Validação → Conversão → Sequencia<Cor> → Interface Paleta
     Parser lida com texto, a Cor encapsula o conceito de cor, e a Paleta fornece uma interface semântica para esquemas
     de cores, que será crucial para mapear altitudes para cores visualmente significativas.
*/

#ifndef PALETA_H
#define PALETA_H

#include "cor.h"
#include "sequencia.h"

class Paleta {
private:
    Sequencia<Cor> cores; // Uma paleta TEM uma sequência de cores (diferente de É uma paleta de cores)
    /*
    Por que Composição?

    Controle: Paleta controla QUAIS operações da Sequencia são expostas
    Semântica: Paleta adiciona significado (esquema de cores) à coleção bruta
    Flexibilidade: Podemos mudar implementação interna sem afetar usuários

    Cada Nível Adiciona Significado:
    Nível 1 (Hex): "71abd8" → Apenas texto, sem significado
    Nível 2 (Cor): Cor(113,171,216) → Conceito de "cor azul clara"
    Nível 3 (Paleta): [azul clara, azul média, azul escura] → "Gradiente de azuis"
    Nível 4 (Uso): Mapeamento altitude→cor → "Mapa topográfico"

    */

public:
    // Construtores
    Paleta();
    explicit Paleta(const char* nomeArquivo);
    
    // Métodos da interface
    void adicionarCor(Cor cor);
    int obterTamanho() const;
    Cor obterCor(int indice) const;
    
private:
    // Método auxiliar para converter hexadecimal para Cor
    bool lerCorDoHex(const std::string& hex, Cor& cor) const;
};

#endif