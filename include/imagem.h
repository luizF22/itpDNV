#ifndef IMAGEM_H
#define IMAGEM_H

#include <cstddef>

/**
 * @brief Estrutura auxiliar para representar um pixel RGB dentro da imagem.
 */
// Tipo Pixel - estrutura para representar um pixel RGB
struct Pixel {
    unsigned char r, g, b;
    
    // Construtor padrão - pixel preto
    /**
     * @brief Construtor padrão (Pixel Preto).
     */
    Pixel() : r(0), g(0), b(0) {}
    
    // Construtor com valores RGB
    /**
     * @brief Construtor com valores RGB definidos.
     * @param r Vermelho.
     * @param g Verde.
     * @param b Azul.
     */
    Pixel(unsigned char r, unsigned char g, unsigned char b) 
        : r(r), g(g), b(b) {}
};
/**
 * @brief Classe responsável pela manipulação de imagens digitais.
 * 
 * @details Gerencia uma matriz de pixels alocada dinamicamente. Oferece abstração
 * para acesso via coordenadas (x,y) e suporte a leitura/escrita no formato PPM.
 */
class Imagem {
private:
    size_t largura;
    size_t altura;
    Pixel* pixels;  // Array único para armazenar todos os pixels
    
    // Método auxiliar para calcular índice no array
    /**
     * @brief Converte coordenadas 2D (x, y) para índice linear do array.
     * @param x Coordenada da coluna.
     * @param y Coordenada da linha.
     * @return Índice correspondente no vetor de pixels.
     */
    size_t calcularIndice(size_t x, size_t y) const;
    
    // Método auxiliar para liberar memória
    /**
     * @brief Libera a memória alocada para os pixels.
     */
    void liberar();
    
    // Método auxiliar para alocar memória
    /**
     * @brief Aloca o buffer de pixels com as dimensões especificadas.
     * @param larg Largura desejada.
     * @param alt Altura desejada.
     */
    void alocar(size_t larg, size_t alt);

public:
    // Construtores
    /**
     * @brief Construtor padrão. Cria uma imagem vazia (0x0).
     */
    Imagem();  // Construtor padrão - imagem vazia
    /**
     * @brief Construtor principal. Cria uma imagem preta com tamanho definido.
     * @param largura Largura em pixels.
     * @param altura Altura em pixels.
     */
    Imagem(size_t largura, size_t altura);  // Construtor com dimensões
    
    // Destrutor
    /**
     * @brief Destrutor. Garante a liberação da memória dos pixels.
     */
    ~Imagem();
    
    // Métodos de consulta
    /**
     * @brief Retorna a largura da imagem.
     * @return Largura em pixels.
     */
    size_t obterLargura() const;
    /**
     * @brief Retorna a altura da imagem.
     * @return Altura em pixels.
     */
    size_t obterAltura() const;
    
    // Operador de acesso aos pixels (x=coluna, y=linha)
    /**
     * @brief Operador de acesso ao pixel (Leitura/Escrita).
     * @param x Coordenada da coluna (0 a largura-1).
     * @param y Coordenada da linha (0 a altura-1).
     * @return Referência modificável ao Pixel.
     */
    Pixel& operator()(size_t x, size_t y);
    /**
     * @brief Operador de acesso ao pixel (Somente Leitura).
     * @param x Coordenada da coluna.
     * @param y Coordenada da linha.
     * @return Referência constante ao Pixel.
     */
    const Pixel& operator()(size_t x, size_t y) const;
    
    // Métodos de I/O
    /**
     * @brief Lê uma imagem de um arquivo PPM (formato P3).
     * @param nomeArquivo Caminho do arquivo a ser lido.
     * @return true se a leitura foi bem sucedida, false caso contrário.
     */
    bool lerPPM(const char* nomeArquivo);
    /**
     * @brief Salva a imagem atual em um arquivo PPM (formato P3).
     * @param nomeArquivo Caminho onde o arquivo será salvo.
     * @return true se a gravação foi bem sucedida, false caso contrário.
     */
    bool salvarPPM(const char* nomeArquivo) const;
};

#endif