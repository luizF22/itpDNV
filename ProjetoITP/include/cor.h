#ifndef COR_H
#define COR_H

class Cor {
public:
    unsigned char r, g, b;

    // Construtores
    Cor();
    Cor(unsigned char r, unsigned char g, unsigned char b);
    
    // Método para verificar se é preta
    bool ehPreta() const;
};

#endif