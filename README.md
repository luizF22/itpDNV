# Gerador de Terrenos Procedurais - Documentação Completa

## Descrição do Projeto

Este projeto implementa um gerador de terrenos procedurais utilizando o algoritmo Diamond-Square, um método clássico para geração de terrenos fractais em computação gráfica. Desenvolvido em C++ como trabalho para a disciplina de Introdução às Técnicas de Programação, o programa transforma dados de altitude em imagens PPM coloridas, aplicando técnicas de sombreamento para criar efeitos 3D realistas.

O objetivo principal é fornecer uma implementação didática e funcional do algoritmo Diamond-Square, permitindo a geração de mapas de altitude com diferentes níveis de rugosidade e a aplicação de paletas de cores personalizadas para representação visual. O projeto demonstra conceitos fundamentais de programação, estruturação de código, manipulação de arquivos e algoritmos gráficos.

## Características Técnicas

O algoritmo Diamond-Square (também conhecido como Midpoint Displacement) é implementado para gerar mapas de tamanho 2^n + 1 × 2^n + 1, onde 'n' é um parâmetro fornecido pelo usuário. A rugosidade do terreno pode ser ajustada através de um parâmetro contínuo que varia de 0.0 (terreno muito suave) a 1.0 (terreno extremamente acidentado). O programa utiliza uma semente aleatória baseada no tempo do sistema, garantindo que cada execução produza um terreno único, embora determinístico quando usando os mesmos parâmetros.

O sistema oferece uma interface de linha de comando intuitiva com validação de parâmetros, suporte a múltiplas paletas de cores em formato hexadecimal, aplicação opcional de sombreamento para efeito tridimensional, e exportação em formato PPM (Portable Pixmap), que é amplamente compatível com diversos visualizadores e editores de imagem. A arquitetura do código é modular, separando claramente as responsabilidades entre geração do terreno, manipulação de cores, processamento de imagem e interface do usuário.

## Estrutura do Projeto

A estrutura do projeto segue uma organização clara e lógica: o diretório 'bin' contém os executáveis compilados; 'data' armazena arquivos de configuração como a paleta de cores padrão; 'include' agrupa todos os cabeçalhos das classes; 'src' contém as implementações das funcionalidades; 'output' serve como destino para as imagens geradas; 'main.cpp' é o ponto de entrada do programa; e o 'Makefile' automatiza o processo de compilação. Esta organização facilita a manutenção, compilação e distribuição do projeto.

## Compilação e Execução

### Pré-requisitos

Para compilar e executar este projeto, é necessário ter instalado um compilador C++11 compatível (g++ é recomendado) em qualquer sistema operacional Windows, Linux ou macOS. Um terminal básico é suficiente para a execução, embora terminais com suporte a cores possam melhorar a experiência visual. Não são necessárias bibliotecas externas além da biblioteca padrão do C++.

### Compilação

O projeto inclui um Makefile completo para facilitar a compilação. O comando 'make' compila todos os arquivos fonte e gera o executável na pasta bin. 'make run' realiza a compilação e execução imediata do programa com parâmetros padrão. 'make clean' remove todos os arquivos objeto e executáveis gerados, permitindo uma recompilação limpa. Esta abordagem simplifica o processo de build e é portável entre diferentes sistemas.

### Execução Direta

Após a compilação, o programa pode ser executado diretamente: no Windows PowerShell utiliza-se '.\bin\gerador_terrenos' seguido dos parâmetros; no Linux ou macOS usa-se './bin/gerador_terrenos'. O programa é completamente autossuficiente e não requer instalação ou configuração adicional do sistema.



## Uso do Programa

### Sintaxe Básica

A sintaxe básica de execução é 'gerador_terrenos [opções]', onde as opções são fornecidas através de flags precedidas por hífen. O programa inclui um sistema abrangente de ajuda acessível através das opções '-h' ou '--help', que descreve detalhadamente todas as funcionalidades disponíveis.

### Opções Disponíveis

A opção '-n' define o tamanho do mapa como 2^n + 1, aceitando valores inteiros de 1 a 10, resultando em mapas de 3×3 até 1025×1025 pixels. A rugosidade é controlada pela opção '-r' com valores decimais de 0.0 a 1.0. Paletas de cores personalizadas podem ser carregadas com '-p', seguida do caminho do arquivo. O nome do arquivo de saída é especificado com '-o'. O sombreamento pode ser desativado para fins de debug com '--sem-sombra'. Todas as opções incluem validação robusta com mensagens de erro informativas.

### Tamanhos Disponíveis

O programa suporta uma gama de tamanhos: n=1 produz um mapa mínimo de 3×3 pixels para teste; n=3 gera 9×9 pixels; n=5 (padrão) cria 33×33 pixels; n=7 produz 129×129 pixels; n=10 gera o máximo de 1025×1025 pixels. Cada incremento em n quadruplica aproximadamente o número de pixels, impactando o tempo de processamento e o tamanho do arquivo de saída.

## Exemplos Práticos

Para gerar um terreno suave com 65×65 pixels, utiliza-se 'gerador_terrenos -n 6 -r 0.2 -o suave.ppm'. Para criar montanhas acidentadas com 129×129 pixels e uma paleta específica, emprega-se 'gerador_terrenos -n 7 -r 0.8 -p data/cores_montanha.hex -o montanhas.ppm'. O modo debug, que desativa o sombreamento, é ativado com 'gerador_terrenos -n 4 -r 0.3 --sem-sombra -o debug.ppm'. Para mapas de alta resolução, 'gerador_terrenos -n 9 -r 0.6 -o grande.ppm' gera 513×513 pixels. Cada exemplo demonstra combinações diferentes dos parâmetros disponíveis.

## Formato dos Arquivos

### Paleta de Cores (.hex)

As paletas de cores são arquivos de texto simples com extensão .hex contendo códigos hexadecimais RGB, um por linha. Linhas iniciadas com '#' são tratadas como comentários e ignoradas. A ordem das cores define a transição da altitude baixa (primeira cor) para alta (última cor). O programa interpola linearmente entre as cores adjacentes baseado na altitude normalizada de cada ponto do terreno.

### Imagem de Saída (.ppm)

As imagens são salvas no formato PPM (Portable Pixmap) em modo ASCII (P3), que é um formato não-comprimido e legível por humanos. O cabeçalho inclui o tipo 'P3', dimensões largura×altura, valor máximo de cor (255), seguido pelos valores RGB de cada pixel. Este formato é amplamente suportado e pode ser convertido facilmente para PNG, JPEG ou outros formatos usando ferramentas como ImageMagick ou GIMP.

## Documentação das Classes

### Classe MapaAltitudes

Esta classe é o núcleo do algoritmo Diamond-Square. O método 'gerar(int n, double rugosidade)' implementa o algoritmo recursivo: inicializa os quatro cantos com valores aleatórios, então alterna entre as fases diamond (calcular centro do quadrado como média dos cantos mais ruído) e square (calcular pontos médios das arestas). A rugosidade controla a amplitude do ruído adicionado em cada nível de recursão. O método 'gerarImagem()' converte a matriz de altitudes em uma imagem aplicando a paleta de cores e sombreamento.

### Classe Paleta

Responsável pelo carregamento e gerenciamento das paletas de cores. O método 'carregarArquivo(string caminho)' lê o arquivo .hex e valida seu formato. 'obterCor(double valor)' recebe um valor normalizado entre 0 e 1 e retorna a cor interpolada da paleta. A classe inclui tratamento de erros para arquivos ausentes ou mal formatados, e fornece informações sobre o número de cores carregadas.

### Classe Imagem

Gerencia a imagem final em memória. 'salvarPPM(string caminho)' escreve a imagem no disco no formato correto. 'aplicarSombra()' percorre a imagem calculando um fator de sombreamento baseado nas diferenças de altitude com os pixels vizinhos, criando ilusão de relevo. A classe utiliza uma matriz bidimensional de objetos Cor para armazenar os pixels.

### Classe Cor

Representa uma cor no espaço RGB com componentes inteiros de 0 a 255. Oferece métodos para operações básicas como clarear, escurecer e interpolar entre cores. A interpolação é linear em cada componente RGB, essencial para transições suaves na paleta.

## Análise de Complexidade

### Complexidade Temporal

O algoritmo Diamond-Square tem complexidade O(N²) onde N = 2^n + 1, pois cada nível de recursão processa aproximadamente N²/4 pontos, e a soma sobre todos os níveis resulta em O(N²). O carregamento da paleta é O(M) onde M é o número de cores. A geração da imagem também é O(N²) devido à necessidade de processar cada pixel. Assim, a complexidade total domina em O(N²) para mapas grandes.

### Complexidade Espacial

O armazenamento do mapa de altitudes requer O(N²) em memória. A paleta ocupa O(M). A imagem final também requer O(N²). Portanto, a complexidade espacial total é O(N²), o que significa que mapas muito grandes (n > 10) podem exigir quantidades significativas de memória.

### Performance Esperada

Para n=5 (33×33), a execução completa leva menos de 1 segundo e usa aproximadamente 10KB de memória. Para n=7 (129×129), o tempo aumenta para 1-2 segundos com 170KB de memória. Para n=9 (513×513), são necessários 10-20 segundos e 2.6MB. Para n=10 (1025×1025), a execução pode levar 40-60 segundos e consumir 10MB. Estas estimativas assumem hardware moderno e podem variar conforme o sistema.


## Considerações Didáticas

Esta implementação demonstra conceitos importantes de programação: modularidade através de classes bem definidas; tratamento de erros com mensagens informativas; uso de estruturas de dados eficientes; implementação de algoritmos complexos; manipulação de arquivos; e interface de linha de comando. Em computação gráfica, aborda geração procedural, interpolação de cores, mapeamento de dados, e técnicas básicas de sombreamento. O código serve como base para entender como algoritmos fractais podem criar padrões complexos a partir de regras simples.

\bin\gerador_terrenos -n n -r r