/*
    Arquivo.hex → Parser → Validação → Conversão → Sequencia<Cor> → Interface Paleta
     Parser lida com texto, a Cor encapsula o conceito de cor, e a Paleta fornece uma interface semântica para esquemas
     de cores, que será crucial para mapear altitudes para cores visualmente significativas.
*/

#ifndef PALETA_H
#define PALETA_H

#include "cor.h"
#include "sequencia.h"

/**
 * @brief Gerencia um conjunto de cores (esquema de cores).
 * 
 * @details Implementa o conceito de Paleta através de COMPOSIÇÃO:
 * Uma Paleta TEM uma Sequencia<Cor>.
 * 
 * Decisões de Design:
 * - Controle: Paleta controla QUAIS operações da Sequencia são expostas.
 * - Semântica: Adiciona significado (esquema de cores) à coleção bruta.
 * - Flexibilidade: A implementação interna pode mudar sem quebrar o código cliente.
 * 
 * Níveis de Abstração:
 * 1. Hex ("71abd8") -> Texto bruto.
 * 2. Cor(113,171,216) -> Objeto de cor.
 * 3. Paleta -> Coleção semântica (gradiente).
 */
class Paleta {
private:
    Sequencia<Cor> cores; // Uma paleta TEM uma sequência de cores (diferente de É uma paleta de cores)
    /*
    Por que Composição?

    Controle: Paleta controla QUAIS operações da Sequencia são expostas
    Semântica: Paleta adiciona significado (esquema de cores) à coleção bruta
    Flexibilidade: Podemos mudar implementação interna sem afetar usuários

    Cada Nível Adiciona Significado:
    Nível 1 (Hex): "71abd8" → Apenas texto, sem significado
    Nível 2 (Cor): Cor(113,171,216) → Conceito de "cor azul clara"
    Nível 3 (Paleta): [azul clara, azul média, azul escura] → "Gradiente de azuis"
    Nível 4 (Uso): Mapeamento altitude→cor → "Mapa topográfico"

    */

public:
    // Construtores
    /**
     * @brief Construtor padrão. Cria uma paleta vazia.
     */
    Paleta();
    /**
     * @brief Construtor que carrega a paleta de um arquivo.
     * @details O arquivo deve conter códigos hexadecimais (ex: #RRGGBB) separados por quebra de linha.
     * @param nomeArquivo Caminho para o arquivo .hex ou .txt.
     */
    explicit Paleta(const char* nomeArquivo);
    
    // Métodos da interface
    /**
     * @brief Adiciona uma cor manualmente à paleta.
     * @param cor Objeto Cor a ser adicionado.
     */
    void adicionarCor(Cor cor);
    /**
     * @brief Retorna a quantidade de cores disponíveis na paleta.
     * @return Número inteiro de cores.
     */
    int obterTamanho() const;
    /**
     * @brief Obtém uma cor específica pelo índice.
     * @param indice Posição da cor (0 a tamanho-1).
     * @return Cópia da Cor desejada.
     */
    Cor obterCor(int indice) const;
    
private:
    // Método auxiliar para converter hexadecimal para Cor
    /**
     * @brief Helper para converter string Hexadecimal em objeto Cor.
     * @param hex String contendo o código (ex: "#FF0000" ou "FF0000").
     * @param cor Referência onde o resultado será armazenado.
     * @return true se a conversão foi bem sucedida.
     */
    bool lerCorDoHex(const std::string& hex, Cor& cor) const;
};

#endif