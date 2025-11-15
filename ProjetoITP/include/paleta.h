#ifndef PALETA_H
#define PALETA_H

#include "cor.h"
#include "sequencia.h"

class Paleta {
private:
    Sequencia<Cor> cores;

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