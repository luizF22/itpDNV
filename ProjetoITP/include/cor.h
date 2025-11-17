#ifndef COR_H
#define COR_H

class Cor {
public:
    unsigned char r, g, b;

    // Construtores
    Cor(); // Preto;
    Cor(unsigned char r, unsigned char g, unsigned char b); // RGB específico;
    
    // Método para verificar se é preta
    bool ehPreta() const;
};

#endif