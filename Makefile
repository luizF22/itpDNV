# Makefile para o Gerador de Terrenos
# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude
LDFLAGS =

# Diretórios
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = test

# Arquivos
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXECUTABLE = $(BIN_DIR)/gerador_terrenos

# Arquivos de teste
TEST_SOURCES = $(wildcard $(TEST_DIR)/*_testes.cpp)
TEST_EXECUTABLES = $(TEST_SOURCES:$(TEST_DIR)/%.cpp=$(BIN_DIR)/%)

# Regra padrão
all: directories $(EXECUTABLE)

# Criar diretórios necessários
directories:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR) output

# Compilar o executável principal
$(EXECUTABLE): $(OBJECTS) main.cpp
	@echo "Linkando $(EXECUTABLE)..."
	$(CXX) $(CXXFLAGS) -o $@ main.cpp $(OBJECTS) $(LDFLAGS)
	@echo "✓ Executável criado: $(EXECUTABLE)"

# Compilar arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compilando $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilar testes
test: directories $(TEST_EXECUTABLES)

$(BIN_DIR)/%: $(TEST_DIR)/%.cpp $(OBJECTS)
	@echo "Compilando teste $@..."
	$(CXX) $(CXXFLAGS) -o $@ $< $(OBJECTS) $(LDFLAGS)

# Executar todos os testes
run-tests: test
	@echo "Executando testes..."
	@for test in $(TEST_EXECUTABLES); do \
		echo "\n=== Executando $$test ==="; \
		./$$test; \
	done

# Limpar arquivos gerados
clean:
	@echo "Limpando arquivos gerados..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "✓ Limpeza concluída"

# Limpar tudo (incluindo imagens geradas)
cleanall: clean
	rm -rf output/*
	@echo "✓ Limpeza total concluída"

# Executar o programa com parâmetros padrão
run: all
	./$(EXECUTABLE) -n 5 -r 0.5

# Ajuda
help:
	@echo "Comandos disponíveis:"
	@echo "  make          - Compila o projeto"
	@echo "  make test     - Compila os testes"
	@echo "  make run-tests - Executa todos os testes"
	@echo "  make run      - Compila e executa com parâmetros padrão"
	@echo "  make clean    - Remove arquivos compilados"
	@echo "  make cleanall - Remove tudo (incluindo imagens)"
	@echo "  make help     - Mostra esta ajuda"

.PHONY: all directories test run-tests clean cleanall run help