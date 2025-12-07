// main.cpp - Programa principal do gerador de terrenos
#include <iostream>
#include <cstring>//para o strcmp (comparar strings C)
#include <iomanip>//formatar saida (tabelas, casas decimais) | deixa o console mais bonito
#include "mapa_altitudes.h"
#include "paleta.h"
#include "imagem.h"

using namespace std;

// Função para centralizar texto em uma largura fixa
string centralizar(const string& texto, int largura) {
    if (texto.length() >= largura) return texto;
    int espacos = largura - texto.length();
    int esquerda = espacos / 2;
    int direita = espacos - esquerda;
    return string(esquerda, ' ') + texto + string(direita, ' ');
}

// Função para alinhar à esquerda com preenchimento
string alinharEsquerda(const string& texto, int largura) {
    if (texto.length() >= largura) return texto;
    return texto + string(largura - texto.length(), ' ');
}

void mostrarAjuda() {
    const int LARGURA = 60;
    
    cout << "\n" << string(LARGURA, '=') << "\n";
    cout << centralizar("GERADOR DE TERRENOS PROCEDURAIS", LARGURA) << "\n";
    cout << centralizar("Algoritmo: Diamond-Square", LARGURA) << "\n";
    cout << string(LARGURA, '=') << "\n\n";
    
    cout << "USO:\n";
    cout << "  gerador_terrenos [opcoes]\n\n";
    
    cout << "OPCOES:\n";
    cout << "  -n <numero>     Tamanho do mapa: 2^n + 1\n";
    cout << "                  Exemplos: n=3 -> 9x9, n=5 -> 33x33, n=7 -> 129x129\n";
    cout << "  -r <decimal>    Rugosidade do terreno [0.0 - 1.0]\n";
    cout << "                  0.0 = muito suave, 1.0 = muito acidentado\n";
    cout << "  -p <arquivo>    Arquivo da paleta de cores (padrao: cores.hex)\n";
    cout << "  -o <arquivo>    Nome do arquivo de saida (padrao: terreno.ppm)\n";
    cout << "  --sem-sombra    Desativa sombreamento (debug)\n";
    cout << "  -h, --help      Mostra esta ajuda\n\n";
    
    cout << "EXEMPLOS:\n";
    cout << "  gerador_terrenos -n 5 -r 0.5\n";
    cout << "  gerador_terrenos -n 7 -r 0.8 -o montanhas.ppm\n";
    cout << "  gerador_terrenos -n 4 -r 0.2 --sem-sombra\n\n";
    
    cout << string(LARGURA, '=') << "\n";
}

int main(int argc, char* argv[]) {
    const int LARGURA = 60;
    
    // PASSO 1: Configurar parâmetros padrão
    int N = 5;
    double rugosidade = 0.5;
    const char* arquivoPaleta = "data/cores.hex";
    const char* arquivoSaida = "output/terreno.ppm";
    bool aplicarSombra = true;
    
    // PASSO 2: Processar argumentos da linha de comando
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            N = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-r") == 0 && i + 1 < argc) {
            rugosidade = atof(argv[++i]);
        }
        else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            arquivoPaleta = argv[++i];
        }
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            arquivoSaida = argv[++i];
        }
        else if (strcmp(argv[i], "--sem-sombra") == 0) {
            aplicarSombra = false;
        }
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            mostrarAjuda();
            return 0;
        }
        else {
            cerr << "Opcao desconhecida: " << argv[i] << "\n";
            mostrarAjuda();
            return 1;
        }
    }
    
    // PASSO 3: Validar parâmetros
    if (N < 1 || N > 10) {
        cerr << "ERRO: N deve estar entre 1 e 10\n";
        cerr << "       (mapas de 3x3 ate 1025x1025)\n";
        return 1;
    }
    
    if (rugosidade < 0.0 || rugosidade > 1.0) {
        cerr << "ERRO: Rugosidade deve estar entre 0.0 e 1.0\n";
        return 1;
    }
    
    // PASSO 4: Exibir configuração
    int tamanho = (1 << N) + 1;
    
    cout << "\n" << string(LARGURA, '=') << "\n";
    cout << centralizar("CONFIGURACAO", LARGURA) << "\n";
    cout << string(LARGURA, '=') << "\n";
    
    cout << left << setw(25) << "  Tamanho do mapa:" 
         << right << setw(10) << tamanho << "x" << tamanho << "\n";
    
    cout << left << setw(25) << "  Rugosidade:" 
         << right << setw(10) << fixed << setprecision(2) << rugosidade << "\n";
    
    cout << left << setw(25) << "  Paleta:" 
         << right << setw(10) << arquivoPaleta << "\n";
    
    cout << left << setw(25) << "  Saida:" 
         << right << setw(10) << arquivoSaida << "\n";
    
    cout << left << setw(25) << "  Sombreamento:" 
         << right << setw(10) << (aplicarSombra ? "Sim" : "Nao") << "\n";
    
    cout << string(LARGURA, '=') << "\n\n";
    
    // PASSO 5: Gerar mapa de altitudes
    cout << "[1/4] Gerando mapa de altitudes...";
    MapaAltitudes mapa;
    mapa.gerar(N, rugosidade);
    cout << " [OK]\n";
    
    // PASSO 6: Carregar paleta de cores
    cout << "[2/4] Carregando paleta de cores...";
    Paleta paleta(arquivoPaleta);
    
    if (paleta.obterTamanho() == 0) {
        cout << " [ERRO]\n";
        cerr << "ERRO: Nao foi possivel carregar a paleta: " << arquivoPaleta << "\n";
        cerr << "      Verifique se o arquivo existe e esta no formato correto.\n";
        return 1;
    }
    cout << " [OK] (" << paleta.obterTamanho() << " cores)\n";
    
    // PASSO 7: Gerar imagem
    cout << "[3/4] Convertendo mapa em imagem...";
    Imagem img = mapa.gerarImagem(paleta, aplicarSombra);
    cout << " [OK]\n";
    
    // PASSO 8: Salvar imagem
    cout << "[4/4] Salvando imagem...";
    if (img.salvarPPM(arquivoSaida)) {
        cout << " [OK]\n\n";
        
        cout << string(LARGURA, '=') << "\n";
        cout << centralizar("SUCESSO!", LARGURA) << "\n";
        cout << string(LARGURA, '=') << "\n";
        
        cout << left << setw(20) << "  Imagem gerada:" << arquivoSaida << "\n";
        cout << left << setw(20) << "  Dimensoes:" 
             << img.obterLargura() << "x" << img.obterAltura() << "\n";
        
        cout << string(LARGURA, '=') << "\n";
        return 0;
    } else {
        cout << " [ERRO]\n";
        cerr << "ERRO: Nao foi possivel salvar a imagem.\n";
        cerr << "      Verifique permissoes e espaco em disco.\n";
        return 1;
    }
}