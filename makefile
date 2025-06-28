# Makefile para Goblin Jump Game
# Compilador e flags
CXX = g++
CXXFLAGS = -fdiagnostics-color=always -g
TARGET = main.exe
SOURCE = main.cpp

# Caminhos do SFML
SFML_INCLUDE = -I"C:/Users/alons/SFML/SFML-3.0.0/include"
SFML_LIB = -L"C:/Users/alons/SFML/SFML-3.0.0/lib"
SFML_LINKS = -lsfml-graphics -lsfml-window -lsfml-system

# Comando completo de compilação
COMPILE_CMD = $(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET) $(SFML_INCLUDE) $(SFML_LIB) $(SFML_LINKS)

# Comando padrão (apenas compilar)
all: $(TARGET)

# Regra para compilar
$(TARGET): $(SOURCE)
	@echo "Compilando $(SOURCE)..."
	$(COMPILE_CMD)
	@echo "Compilação concluída! Executável: $(TARGET)"

# Comando para compilar e executar
run: $(TARGET)
	@echo "Executando $(TARGET)..."
	./$(TARGET)

# Comando para compilar e executar em uma única etapa
build-run: clean $(TARGET)
	@echo "Executando $(TARGET)..."
	./$(TARGET)

# Limpar arquivos compilados
clean:
	@if exist $(TARGET) del $(TARGET)
	@echo "Arquivos limpos!"

# Mostrar informações
info:
	@echo "=== Makefile do Goblin Jump ==="
	@echo "Comandos disponíveis:"
	@echo "  make         - Apenas compilar"
	@echo "  make run     - Compilar e executar"
	@echo "  make build-run - Limpar, compilar e executar"
	@echo "  make clean   - Limpar arquivos compilados"
	@echo "  make info    - Mostrar esta ajuda"
	@echo ""
	@echo "Arquivo fonte: $(SOURCE)"
	@echo "Executável: $(TARGET)"

# Declarar que estes não são arquivos
.PHONY: all run build-run clean info