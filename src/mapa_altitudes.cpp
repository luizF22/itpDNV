#include "mapa_altitudes.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// ═══════════════════════════════════════════════════════════
// CONSTRUTORES E DESTRUTOR
// ═══════════════════════════════════════════════════════════

MapaAltitudes::MapaAltitudes() : tamanho(0), altitudes(nullptr) {}

MapaAltitudes::MapaAltitudes(int N) : tamanho(0), altitudes(nullptr) {
    size_t tam = static_cast<size_t>(pow(2, N)) + 1;
    alocar(tam);
}

MapaAltitudes::~MapaAltitudes() {
    liberar();
}

// ═══════════════════════════════════════════════════════════
// MÉTODOS AUXILIARES PRIVADOS
// ═══════════════════════════════════════════════════════════

size_t MapaAltitudes::calcularIndice(size_t lin, size_t col) const {
    return lin * tamanho + col;
}

void MapaAltitudes::liberar() {
    if (altitudes != nullptr) {
        delete[] altitudes;
        altitudes = nullptr;
    }
    tamanho = 0;
}

void MapaAltitudes::alocar(size_t tam) {
    liberar();
    tamanho = tam;
    
    if (tamanho > 0) {
        altitudes = new double[tamanho * tamanho];
        // Inicializa com zeros
        for (size_t i = 0; i < tamanho * tamanho; i++) {
            altitudes[i] = 0.0;
        }
    }
}

// Obtém altitude com verificação de limites (retorna valor padrão se fora)
double MapaAltitudes::obterAltitudaSegura(int lin, int col, double padrao) const {
    if (lin < 0 || col < 0 || 
        lin >= static_cast<int>(tamanho) || 
        col >= static_cast<int>(tamanho)) {
        return padrao;
    }
    return altitudes[calcularIndice(lin, col)];
}

// ═══════════════════════════════════════════════════════════
// ALGORITMO DIAMOND-SQUARE
// ═══════════════════════════════════════════════════════════

void MapaAltitudes::etapaDiamond(size_t x, size_t y, size_t passo, double amplitude) {
    // Calcula o centro do quadrado
    size_t meio = passo / 2;
    size_t centroX = x + meio;
    size_t centroY = y + meio;
    
    // Obtém os 4 cantos
    double cantoA = altitudes[calcularIndice(y, x)];              // Superior esquerdo
    double cantoB = altitudes[calcularIndice(y, x + passo)];     // Superior direito
    double cantoC = altitudes[calcularIndice(y + passo, x)];     // Inferior esquerdo
    double cantoD = altitudes[calcularIndice(y + passo, x + passo)]; // Inferior direito
    
    // Média dos 4 cantos + deslocamento aleatório
    double media = (cantoA + cantoB + cantoC + cantoD) / 4.0;
    double deslocamento = ((double)rand() / RAND_MAX * 2.0 - 1.0) * amplitude;
    
    altitudes[calcularIndice(centroY, centroX)] = media + deslocamento;
}

void MapaAltitudes::etapaSquare(size_t x, size_t y, size_t passo, double amplitude) {
    size_t meio = passo / 2;
    size_t centroX = x + meio;
    size_t centroY = y + meio;
    
    double centro = altitudes[calcularIndice(centroY, centroX)];
    
    // Calcula os 4 pontos médios das bordas (cima, esquerda, direita, baixo)
    
    // Ponto superior (y, centroX)
    if (y > 0 || x == 0) {  // Garante que não recalcula pontos já feitos
        double soma = centro;
        int cont = 1;
        
        soma += obterAltitudaSegura(y, x, centro);              // Esquerda
        cont++;
        soma += obterAltitudaSegura(y, x + passo, centro);      // Direita
        cont++;
        soma += obterAltitudaSegura(y - meio, centroX, centro); // Cima
        cont++;
        
        double media = soma / cont;
        double deslocamento = ((double)rand() / RAND_MAX * 2.0 - 1.0) * amplitude;
        altitudes[calcularIndice(y, centroX)] = media + deslocamento;
    }
    
    // Ponto esquerdo (centroY, x)
    if (x > 0 || y == 0) {
        double soma = centro;
        int cont = 1;
        
        soma += obterAltitudaSegura(y, x, centro);              // Cima
        cont++;
        soma += obterAltitudaSegura(y + passo, x, centro);      // Baixo
        cont++;
        soma += obterAltitudaSegura(centroY, x - meio, centro); // Esquerda
        cont++;
        
        double media = soma / cont;
        double deslocamento = ((double)rand() / RAND_MAX * 2.0 - 1.0) * amplitude;
        altitudes[calcularIndice(centroY, x)] = media + deslocamento;
    }
    
    // Ponto direito (centroY, x + passo)
    {
        double soma = centro;
        int cont = 1;
        
        soma += obterAltitudaSegura(y, x + passo, centro);          // Cima
        cont++;
        soma += obterAltitudaSegura(y + passo, x + passo, centro);  // Baixo
        cont++;
        soma += obterAltitudaSegura(centroY, x + passo + meio, centro); // Direita
        cont++;
        
        double media = soma / cont;
        double deslocamento = ((double)rand() / RAND_MAX * 2.0 - 1.0) * amplitude;
        altitudes[calcularIndice(centroY, x + passo)] = media + deslocamento;
    }
    
    // Ponto inferior (y + passo, centroX)
    {
        double soma = centro;
        int cont = 1;
        
        soma += obterAltitudaSegura(y + passo, x, centro);          // Esquerda
        cont++;
        soma += obterAltitudaSegura(y + passo, x + passo, centro);  // Direita
        cont++;
        soma += obterAltitudaSegura(y + passo + meio, centroX, centro); // Baixo
        cont++;
        
        double media = soma / cont;
        double deslocamento = ((double)rand() / RAND_MAX * 2.0 - 1.0) * amplitude;
        altitudes[calcularIndice(y + passo, centroX)] = media + deslocamento;
    }
}

void MapaAltitudes::gerar(int N, double rugosidade) {
    // Calcula tamanho: 2^N + 1
    size_t tam = static_cast<size_t>(pow(2, N)) + 1;
    alocar(tam);
    
    // Inicializa gerador de números aleatórios
    srand(static_cast<unsigned int>(time(nullptr)));
    
    // Define alturas aleatórias para os 4 cantos [0, 1]
    altitudes[calcularIndice(0, 0)] = (double)rand() / RAND_MAX;
    altitudes[calcularIndice(0, tamanho - 1)] = (double)rand() / RAND_MAX;
    altitudes[calcularIndice(tamanho - 1, 0)] = (double)rand() / RAND_MAX;
    altitudes[calcularIndice(tamanho - 1, tamanho - 1)] = (double)rand() / RAND_MAX;
    
    // Amplitude inicial
    double amplitude = 1.0;
    
    // Loop principal: reduz o passo pela metade a cada iteração
    for (size_t passo = tamanho - 1; passo > 1; passo /= 2) {
        // Para cada quadrado neste nível
        for (size_t y = 0; y < tamanho - 1; y += passo) {
            for (size_t x = 0; x < tamanho - 1; x += passo) {
                etapaDiamond(x, y, passo, amplitude);
            }
        }
        
        // Para cada losango neste nível
        for (size_t y = 0; y < tamanho - 1; y += passo) {
            for (size_t x = 0; x < tamanho - 1; x += passo) {
                etapaSquare(x, y, passo, amplitude);
            }
        }
        
        // Reduz amplitude pela rugosidade
        amplitude *= rugosidade;
    }
}

// ═══════════════════════════════════════════════════════════
// MÉTODOS DE CONSULTA
// ═══════════════════════════════════════════════════════════

double MapaAltitudes::obterAltitude(size_t lin, size_t col) const {
    return altitudes[calcularIndice(lin, col)];
}

size_t MapaAltitudes::obterLinhas() const {
    return tamanho;
}

size_t MapaAltitudes::obterColunas() const {
    return tamanho;
}

// ═══════════════════════════════════════════════════════════
// I/O DE ARQUIVOS
// ═══════════════════════════════════════════════════════════

bool MapaAltitudes::salvar(const char* nomeArquivo) const {
    ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao criar arquivo: " << nomeArquivo << "\n";
        return false;
    }
    
    // Escreve dimensões
    arquivo << tamanho << " " << tamanho << "\n";
    
    // Escreve altitudes (uma por linha para facilitar leitura)
    for (size_t i = 0; i < tamanho * tamanho; i++) {
        arquivo << altitudes[i] << "\n";
    }
    
    arquivo.close();
    return true;
}

bool MapaAltitudes::ler(const char* nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir arquivo: " << nomeArquivo << "\n";
        return false;
    }
    
    // Lê dimensões
    size_t linhas, colunas;
    arquivo >> linhas >> colunas;
    
    if (linhas != colunas) {
        cerr << "Erro: mapa deve ser quadrado\n";
        return false;
    }
    
    // Aloca memória
    alocar(linhas);
    
    // Lê altitudes
    for (size_t i = 0; i < tamanho * tamanho; i++) {
        arquivo >> altitudes[i];
        if (arquivo.fail()) {
            cerr << "Erro ao ler altitude " << i << "\n";
            return false;
        }
    }
    
    arquivo.close();
    return true;
}

// ═══════════════════════════════════════════════════════════
// MÉTODO AUXILIAR 1: Mapear altitude para cor
// ═══════════════════════════════════════════════════════════

Cor MapaAltitudes::mapearAltitudeCor(double altitude, const Paleta& paleta) const {
    // Normaliza altitude para índice da paleta
    // altitude está em [0, 1]
    // Precisamos mapear para [0, paleta.obterTamanho()-1]
    
    int numCores = paleta.obterTamanho();
    
    // Caso especial: paleta vazia
    if (numCores == 0) {
        return Cor(0, 0, 0);  // Preto
    }
    
    // Caso especial: apenas uma cor
    if (numCores == 1) {
        return paleta.obterCor(0);
    }
    
    // Calcula índice na paleta
    // Exemplo: altitude=0.5, numCores=10
    // indice = 0.5 × (10-1) = 0.5 × 9 = 4.5
    double indiceContinuo = altitude * (numCores - 1);
    
    // Converte para inteiro (trunca)
    int indice = static_cast<int>(indiceContinuo);
    
    // Garante que está no range válido [0, numCores-1]
    if (indice < 0) indice = 0;
    if (indice >= numCores) indice = numCores - 1;
    
    return paleta.obterCor(indice);
}

// ═══════════════════════════════════════════════════════════
// MÉTODO AUXILIAR 2: Calcular sombreamento
// ═══════════════════════════════════════════════════════════

double MapaAltitudes::calcularSombreamento(size_t lin, size_t col) const {
    // Simula iluminação vinda do noroeste (canto superior esquerdo)
    // Pontos que estão "na sombra" (mais baixos que vizinho NO) são escurecidos
    
    double altitudeAtual = obterAltitude(lin, col);
    
    // Verifica vizinho noroeste (diagonal superior-esquerda)
    // Se não existir (bordas), considera mesma altura (sem sombra)
    double altitudeNoroeste = altitudeAtual;
    
    if (lin > 0 && col > 0) {
        altitudeNoroeste = obterAltitude(lin - 1, col - 1);
    }
    
    // Calcula diferença de altura
    double diferenca = altitudeNoroeste - altitudeAtual;
    
    // Se vizinho NO é mais alto, este ponto está "na sombra"
    if (diferenca > 0) {
        // Fator de escurecimento proporcional à diferença
        // diferenca = 0.1 → fator = 0.5 (escurece 50%)
        // diferenca = 0.3 → fator = 0.1 (escurece 90%)
        double fator = 1.0 - (diferenca * 5.0);
        
        // Garante que fator está em [0.3, 1.0]
        // (nunca escurece mais que 70%)
        if (fator < 0.3) fator = 0.3;
        if (fator > 1.0) fator = 1.0;
        
        return fator;
    }
    
    // Sem sombra (ou iluminado)
    return 1.0;
}

// ═══════════════════════════════════════════════════════════
// MÉTODO PRINCIPAL: Gerar imagem a partir do mapa
// ═══════════════════════════════════════════════════════════

Imagem MapaAltitudes::gerarImagem(const Paleta& paleta, bool aplicarSombreamento) const {
    // Cria imagem com mesmas dimensões do mapa
    Imagem img(tamanho, tamanho);
    
    // Para cada ponto do mapa
    for (size_t lin = 0; lin < tamanho; lin++) {
        for (size_t col = 0; col < tamanho; col++) {
            // PASSO 1: Obter altitude do ponto
            double altitude = obterAltitude(lin, col);
            
            // PASSO 2: Mapear altitude para cor base
            Cor corBase = mapearAltitudeCor(altitude, paleta);
            
            // PASSO 3: Aplicar sombreamento (se solicitado)
            if (aplicarSombreamento) {
                double fatorSombra = calcularSombreamento(lin, col);
                
                // Escurece a cor multiplicando componentes RGB pelo fator
                corBase.r = static_cast<unsigned char>(corBase.r * fatorSombra);
                corBase.g = static_cast<unsigned char>(corBase.g * fatorSombra);
                corBase.b = static_cast<unsigned char>(corBase.b * fatorSombra);
            }
            
            // PASSO 4: Definir pixel na imagem
            // Converte Cor para Pixel
            Pixel p;
            p.r = corBase.r;
            p.g = corBase.g;
            p.b = corBase.b;
            
            img(col, lin) = p;
        }
    }
    
    return img;
}