#ifndef COR_H
#define COR_H
/**
 * @brief Representa uma cor no sistema RGB (Red, Green, Blue).
 * 
 * @details Esta classe é a unidade básica de cor utilizada na Paleta e na Imagem.
 * Armazena componentes de 8 bits (0-255) para cada canal de cor.
 */
class Cor {
public:
    unsigned char r, g, b;

    // Construtores
    /**
     * @brief Construtor padrão. Inicializa a cor como Preto (0, 0, 0).
     */
    Cor(); // Preto;
    /**
     * @brief Construtor parametrizado.
     * @param r Componente vermelho.
     * @param g Componente verde.
     * @param b Componente azul.
     */
    Cor(unsigned char r, unsigned char g, unsigned char b); // RGB específico;
    
    // Método para verificar se é preta
    /**
     * @brief Verifica se a cor é puramente preta.
     * @return true se (r,g,b) forem todos 0, false caso contrário.
     */
    bool ehPreta() const;
};

#endif