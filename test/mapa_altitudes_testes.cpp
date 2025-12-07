#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "mapa_altitudes.h"
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

TEST_CASE("Testa criação de mapa 5×5 com valores default") {
    MapaAltitudes mapa(2);  // 2^2 + 1 = 5
    
    CHECK(mapa.obterLinhas() == 5);
    CHECK(mapa.obterColunas() == 5);
    
    // Verifica que todos os valores foram inicializados com 0
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 5; j++) {
            CHECK(mapa.obterAltitude(i, j) == 0.0);
        }
    }
}

TEST_CASE("Testa salvamento de mapa em arquivo") {
    MapaAltitudes mapa(2);  // 5×5
    
    // Define alguns valores manualmente para teste
    // (não usa gerar() para ter valores previsíveis)
    
    bool sucesso = mapa.salvar("teste_mapa.txt");
    CHECK(sucesso);
    
    // Verifica se arquivo foi criado
    ifstream arquivo("teste_mapa.txt");
    CHECK(arquivo.is_open());
    
    // Verifica formato do arquivo
    size_t linhas, colunas;
    arquivo >> linhas >> colunas;
    CHECK(linhas == 5);
    CHECK(colunas == 5);
    
    arquivo.close();
}

TEST_CASE("Testa leitura de mapa de arquivo") {
    // Cria arquivo de teste manualmente
    ofstream arquivo("teste_leitura.txt");
    arquivo << "3 3\n";  // Mapa 3×3
    arquivo << "1.0\n";
    arquivo << "2.0\n";
    arquivo << "3.0\n";
    arquivo << "4.0\n";
    arquivo << "5.0\n";
    arquivo << "6.0\n";
    arquivo << "7.0\n";
    arquivo << "8.0\n";
    arquivo << "9.0\n";
    arquivo.close();
    
    // Lê o arquivo
    MapaAltitudes mapa;
    bool sucesso = mapa.ler("teste_leitura.txt");
    CHECK(sucesso);
    
    CHECK(mapa.obterLinhas() == 3);
    CHECK(mapa.obterColunas() == 3);
    CHECK(mapa.obterAltitude(0, 0) == 1.0);
    CHECK(mapa.obterAltitude(0, 1) == 2.0);
    CHECK(mapa.obterAltitude(2, 2) == 9.0);
}

TEST_CASE("Testa geração com rugosidade 0 (valores devem convergir)") {
    MapaAltitudes mapa;
    mapa.gerar(3, 0.0);  // 2^3 + 1 = 9×9, sem variação
    
    CHECK(mapa.obterLinhas() == 9);
    CHECK(mapa.obterColunas() == 9);
    
    // Com rugosidade 0, após várias iterações os valores
    // tendem a convergir (não serão todos iguais por causa
    // da inicialização aleatória dos cantos)
    
    // Verifica que pelo menos gerou valores
    bool temValor = false;
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            if (mapa.obterAltitude(i, j) > 0.0) {
                temValor = true;
            }
        }
    }
    CHECK(temValor);
}

TEST_CASE("Testa geração com rugosidade normal") {
    MapaAltitudes mapa;
    mapa.gerar(3, 0.5);  // 9×9, rugosidade 0.5
    
    CHECK(mapa.obterLinhas() == 9);
    CHECK(mapa.obterColunas() == 9);
    
    // Verifica que gerou valores variados
    double minVal = mapa.obterAltitude(0, 0);
    double maxVal = mapa.obterAltitude(0, 0);
    
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            double alt = mapa.obterAltitude(i, j);
            if (alt < minVal) minVal = alt;
            if (alt > maxVal) maxVal = alt;
        }
    }
    
    // Deve haver variação
    CHECK(maxVal > minVal);
}

TEST_CASE("Testa tamanhos diferentes de mapa") {
    MapaAltitudes mapa1(1);  // 2^1 + 1 = 3×3
    CHECK(mapa1.obterLinhas() == 3);
    
    MapaAltitudes mapa2(2);  // 2^2 + 1 = 5×5
    CHECK(mapa2.obterLinhas() == 5);
    
    MapaAltitudes mapa3(4);  // 2^4 + 1 = 17×17
    CHECK(mapa3.obterLinhas() == 17);
    
    MapaAltitudes mapa4(5);  // 2^5 + 1 = 33×33
    CHECK(mapa4.obterLinhas() == 33);
}