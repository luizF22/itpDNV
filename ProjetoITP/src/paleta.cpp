#include "paleta.h"
#include <fstream>
#include <string>
#include <cctype>
#include <iostream>
#include <sstream>

// Construtor padrão
Paleta::Paleta() {
    // Sequencia já é inicializada vazia automaticamente
}

// Construtor que carrega de arquivo
Paleta::Paleta(const char* nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    
    if (!arquivo.is_open()) {
        std::cerr << "Aviso: Não foi possível abrir o arquivo '" << nomeArquivo << "'" << std::endl;
        return;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        // Remove espaços em branco do início e fim
        size_t inicio = linha.find_first_not_of(" \t");
        size_t fim = linha.find_last_not_of(" \t");
        
        if (inicio == std::string::npos) continue; // Linha vazia
        linha = linha.substr(inicio, fim - inicio + 1);

        // Ignora linhas de comentário e que não começam com '#'
        if (linha.empty() || linha[0] != '#') {
            continue;
        }

        // Remove o '#' e verifica comprimento
        std::string hex = linha.substr(1);
        if (hex.length() != 6) {
            continue;
        }

        // Converte hexadecimal para Cor
        Cor novaCor;
        if (lerCorDoHex(hex, novaCor)) {
            adicionarCor(novaCor);
        }
    }
}

// Adiciona uma cor à paleta
void Paleta::adicionarCor(Cor cor) {
    cores.adicionar(cor);
}

// Retorna o número de cores na paleta
int Paleta::obterTamanho() const {
    return static_cast<int>(cores.obterTamanho());
}

// Obtém uma cor por índice (retorna preto se índice inválido) -> Possui tratamento defensivo / Diferente para sequência
Cor Paleta::obterCor(int indice) const {
    if (indice < 0 || indice >= obterTamanho()) {
        return Cor(); // Retorna preto para índice inválido -> valor seguro 
        /*
        Indice inválido pode ser caso de uso válido (buscar cor inexistente) → Comportamento definido
        */
    }
    return cores[indice];
}

// Método auxiliar para converter hexadecimal para Cor
bool Paleta::lerCorDoHex(const std::string& hex, Cor& cor) const {
    // Verifica se todos os caracteres são hexadecimais
    for (char c : hex) {
        if (!std::isxdigit(c)) {
            return false;
        }
    }

    // Converte usando stringstream (mais seguro que sscanf)
    std::stringstream ss;
    unsigned int r, g, b;
    
    ss << std::hex << hex.substr(0, 2);
    ss >> r;
    ss.clear();
    
    ss << std::hex << hex.substr(2, 2);
    ss >> g;
    ss.clear();
    
    ss << std::hex << hex.substr(4, 2);
    ss >> b;

    cor = Cor(static_cast<unsigned char>(r),
              static_cast<unsigned char>(g),
              static_cast<unsigned char>(b));
    
    return true;
}