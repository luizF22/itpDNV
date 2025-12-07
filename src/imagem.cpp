/*
O destrutor sempre é chamado ao sair do escopo. Isso permite que a memória sempre seja utilizada de forma otimizada.
Ótimo ao redimensionar, pois apaga a memória antiga e aloca a nova.
*/

#include "imagem.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

// Construtor padrão - imagem vazia
Imagem::Imagem() : largura(0), altura(0), pixels(nullptr) {}

// Construtor com dimensões
Imagem::Imagem(size_t largura, size_t altura) 
    : largura(largura), altura(altura), pixels(nullptr) {
    alocar(largura, altura);
}

// Destrutor
Imagem::~Imagem() {
    liberar();
}

// Métodos auxiliares privados
void Imagem::liberar() {
    if (pixels != nullptr) { //  Se há memória alocada ...
        delete[] pixels; // ... Então llibere. Se Pixel* pixels = new Pixel[100];  // Aloca espaço para 100 Pixels + metadados, então delete[] pixels chama ~Pixel() 100 vezes. 
        pixels = nullptr;
    }
    largura = 0;
    altura = 0;
}

void Imagem::alocar(size_t larg, size_t alt) {
    liberar();  // Libera memória antiga existente, se houver
    
    largura = larg;
    altura = alt;
    
    if (largura > 0 && altura > 0) {
        pixels = new Pixel[largura * altura];
        // Inicializa todos os pixels como preto (0, 0, 0)
        for (size_t i = 0; i < largura * altura; i++) {
            pixels[i] = Pixel(0, 0, 0);
        }
    }
}

size_t Imagem::calcularIndice(size_t x, size_t y) const {
    // x é coluna, y é linha
    // Índice = y * largura + x
    return y * largura + x;
}

// Métodos de consulta
size_t Imagem::obterLargura() const {
    return largura;
}

size_t Imagem::obterAltura() const {
    return altura;
}

// Operadores de acesso
Pixel& Imagem::operator()(size_t x, size_t y) {
    return pixels[calcularIndice(x, y)];
}

const Pixel& Imagem::operator()(size_t x, size_t y) const {
    return pixels[calcularIndice(x, y)];
}

// Leitura de arquivo PPM
bool Imagem::lerPPM(const char* nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir arquivo: " << nomeArquivo << std::endl;
        return false;
    }
    
    std::string linha;
    
    // Lê o identificador (P3)
    std::getline(arquivo, linha);
    if (linha != "P3") {
        std::cerr << "Formato inválido. Esperado P3, encontrado: " << linha << std::endl;
        return false;
    }
    
    // Lê dimensões (largura e altura)
    size_t novaLargura, novaAltura;
    arquivo >> novaLargura >> novaAltura;
    
    // Lê o valor máximo (255)
    int maxVal;
    arquivo >> maxVal;
    
    if (maxVal != 255) {
        std::cerr << "Valor máximo inválido: " << maxVal << std::endl;
        return false;
    }
    
    // Aloca memória com as novas dimensões
    alocar(novaLargura, novaAltura);
    
    // Lê os pixels
    for (size_t y = 0; y < altura; y++) {
        for (size_t x = 0; x < largura; x++) {
            int r, g, b;
            arquivo >> r >> g >> b;
            
            if (arquivo.fail()) {
                std::cerr << "Erro ao ler pixel (" << x << ", " << y << ")" << std::endl;
                return false;
            }
            
            pixels[calcularIndice(x, y)] = Pixel(
                static_cast<unsigned char>(r),
                static_cast<unsigned char>(g),
                static_cast<unsigned char>(b)
            );
        }
    }
    
    arquivo.close();
    return true;
}

// Salvamento em arquivo PPM
bool Imagem::salvarPPM(const char* nomeArquivo) const {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao criar arquivo: " << nomeArquivo << std::endl;
        return false;
    }
    
    // Escreve cabeçalho
    arquivo << "P3" << std::endl;
    arquivo << largura << " " << altura << std::endl;
    arquivo << "255" << std::endl;
    
    // Escreve pixels linha por linha
    for (size_t y = 0; y < altura; y++) {
        for (size_t x = 0; x < largura; x++) {
            const Pixel& p = pixels[calcularIndice(x, y)];
            arquivo << static_cast<int>(p.r) << " " 
                   << static_cast<int>(p.g) << " " 
                   << static_cast<int>(p.b) << std::endl;
        }
    }
    
    arquivo.close();
    return true;
}