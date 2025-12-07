#ifndef MAPA_ALTITUDES_H
#define MAPA_ALTITUDES_H

#include <cstddef>
#include "paleta.h"//novos includes (agr o arquivo conhece a paleta e a imagem)
#include "imagem.h"
/**
 * @brief Classe responsável pela geração e manipulação de mapas de altitudes.
 * 
 * @details Esta classe implementa o algoritmo Diamond-Square para geração procedural
 * de terrenos. Ela gerencia uma matriz de valores de ponto flutuante (double)
 * representando as alturas, e oferece métodos para salvar/carregar em arquivo
 * e gerar imagens visualizáveis com aplicação de cores e sombreamento.
 */
class MapaAltitudes {
private:
    size_t tamanho;
    double* altitudes;
    
    // Métodos auxiliares (já existentes)
    /**
     * @brief Converte coordenadas 2D (linha, coluna) para índice linear do array.
     * @param lin Índice da linha.
     * @param col Índice da coluna.
     * @return Índice correspondente no array unidimensional.
     */
    size_t calcularIndice(size_t lin, size_t col) const;
    /**
     * @brief Libera a memória alocada para o array de altitudes.
     */
    void liberar();
    /**
     * @brief Aloca memória para um novo mapa de tamanho especificado.
     * @param tam Dimensão lateral do novo mapa.
     */
    void alocar(size_t tam);
     /**
     * @brief Executa a etapa "Diamond" (Losango) do algoritmo.
     * @details Calcula o ponto central de um quadrado baseando-se na média dos 4 cantos.
     * @param x Coordenada X (coluna) do canto superior esquerdo.
     * @param y Coordenada Y (linha) do canto superior esquerdo.
     * @param passo Tamanho do quadrado atual.
     * @param amplitude Fator de aleatoriedade atual.
     */
    void etapaDiamond(size_t x, size_t y, size_t passo, double amplitude);
    /**
     * @brief Executa a etapa "Square" (Quadrado) do algoritmo.
     * @details Calcula os pontos médios das arestas baseando-se nos vizinhos ortogonais.
     * @param x Coordenada X (coluna) do canto superior esquerdo.
     * @param y Coordenada Y (linha) do canto superior esquerdo.
     * @param passo Tamanho do quadrado atual.
     * @param amplitude Fator de aleatoriedade atual.
     */
    void etapaSquare(size_t x, size_t y, size_t passo, double amplitude);
     /**
     * @brief Obtém uma altitude tratando limites da matriz.
     * @details Útil para a etapa Square nas bordas do mapa (onde não há vizinhos).
     * @param lin Linha desejada.
     * @param col Coluna desejada.
     * @param padrao Valor a retornar caso a coordenada esteja fora do mapa.
     * @return A altitude na posição ou o valor padrão.
     */
    double obterAltitudaSegura(int lin, int col, double padrao) const;
    
    // Novos métodos auxiliares para geração de imagem
    /**
     * @brief Converte um valor de altitude [0..1] em uma Cor baseada na Paleta.
     * @param altitude Valor normalizado da altura.
     * @param paleta Referência para a paleta de cores a ser usada.
     * @return Objeto Cor correspondente à altitude.
     */
    Cor mapearAltitudeCor(double altitude, const Paleta& paleta) const;//encapsula a lógica de escolher a cor
    /**
     * @brief Calcula o fator de sombreamento para um pixel.
     * @details Simula uma luz vinda do Noroeste. Compara a altitude atual com o vizinho
     * superior esquerdo para determinar se o ponto está na sombra.
     * @param lin Linha do ponto.
     * @param col Coluna do ponto.
     * @return Fator de luminosidade entre 0.3 (sombra forte) e 1.0 (iluminado).
     */
    double calcularSombreamento(size_t lin, size_t col) const;//lógica da luz, pode ser alterada (queremos noroeste, mas poderia ser parametrizada)

public:
    // Construtores e destrutor (já existentes)
    /**
     * @brief Construtor padrão. Inicializa um mapa vazio.
     */
    MapaAltitudes();
    /**
     * @brief Construtor que inicializa um mapa de tamanho 2^N + 1.
     * @param N Expoente que define o tamanho (Ex: N=5 gera mapa 33x33).
     */
    explicit MapaAltitudes(int N);
    /**
     * @brief Destrutor. Garante a liberação de memória.
     */
    ~MapaAltitudes();
    
    // Métodos já existentes
    /**
     * @brief Gera o terreno proceduralmente usando Diamond-Square.
     * @param N Expoente de tamanho. O mapa terá dimensão (2^N + 1).
     * @param rugosidade Fator de decaimento da aleatoriedade [0.0 - 1.0].
     *        Valores maiores criam terrenos mais acidentados.
     */
    void gerar(int N, double rugosidade);
    /**
     * @brief Consulta a altitude em uma coordenada específica.
     * @param lin Linha.
     * @param col Coluna.
     * @return Valor da altitude (double).
     */
    double obterAltitude(size_t lin, size_t col) const;
    /**
     * @brief Retorna a quantidade de linhas do mapa.
     * @return Tamanho lateral da matriz.
     */
    size_t obterLinhas() const;
    /**
     * @brief Retorna a quantidade de colunas do mapa.
     * @return Tamanho lateral da matriz.
     */
    size_t obterColunas() const;
    /**
     * @brief Salva os dados brutos do mapa em um arquivo de texto.
     * @param nomeArquivo Caminho do arquivo de destino.
     * @return true se salvo com sucesso, false caso contrário.
     */

    bool salvar(const char* nomeArquivo) const;
    /**
     * @brief Lê dados de um arquivo e reconstrói o mapa.
     * @param nomeArquivo Caminho do arquivo de origem.
     * @return true se lido com sucesso, false caso contrário.
     */
    bool ler(const char* nomeArquivo);
    
    // NOVO: Método principal da Etapa 4
    /**
     * @brief Gera uma representação visual (Imagem) do mapa de altitudes.
     * @param paleta Objeto contendo as cores para mapeamento de alturas.
     * @param aplicarSombreamento Se true, aplica efeito de luz/sombra (Noroeste).
     * @return Objeto Imagem pronto para ser salvo como PPM.
     */
    //recebe a paleta por ref constante
    //o bool aplicarSombreamento é para gerar imagens flat para debug, como sugeria o pdf
    //const pq gerar a img n vai alterar as altitudes do terreno
    Imagem gerarImagem(const Paleta& paleta, bool aplicarSombreamento = true) const;
};

#endif