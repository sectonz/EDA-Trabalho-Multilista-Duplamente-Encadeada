# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra $(shell pkg-config --cflags gtk+-3.0)
LDFLAGS = $(shell pkg-config --libs gtk+-3.0)

# Diretórios
LIBS_DIR = libs
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = $(LIBS_DIR)/include

# Encontra todos os arquivos .c na pasta libs
LIBS_SOURCES = $(wildcard $(LIBS_DIR)/*.c)
# Gera os nomes dos objetos correspondentes na pasta build
LIBS_OBJECTS = $(patsubst $(LIBS_DIR)/%.c,$(BUILD_DIR)/%.o,$(LIBS_SOURCES))

# Procura os arquivos principais em diferentes locais possíveis
MAIN_SOURCE = $(if $(wildcard main.c),main.c,$(if $(wildcard $(SRC_DIR)/main.c),$(SRC_DIR)/main.c,))
ESTRUTURAS_SOURCE = $(if $(wildcard estruturas.c),estruturas.c,$(if $(wildcard $(SRC_DIR)/estruturas.c),$(SRC_DIR)/estruturas.c,))

# Verifica se os arquivos fonte existem
ifeq ($(MAIN_SOURCE),)
$(error Arquivo main.c não encontrado nem no diretório atual nem em src/)
endif

ifeq ($(ESTRUTURAS_SOURCE),)
$(error Arquivo estruturas.c não encontrado nem no diretório atual nem em src/)
endif

# Objetos principais
MAIN_OBJECT = $(BUILD_DIR)/main.o
ESTRUTURAS_OBJECT = $(BUILD_DIR)/estruturas.o

# Nome do executável final
TARGET = programa

# Regra principal
all: check_deps setup $(TARGET)

# Verifica dependências necessárias
check_deps:
	@which pkg-config >/dev/null || (echo "Error: pkg-config não está instalado" && exit 1)
	@pkg-config --exists gtk+-3.0 || (echo "Error: GTK3 desenvolvimento não está instalado" && exit 1)

# Cria os diretórios necessários
setup:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(SRC_DIR)

# Link final
$(TARGET): $(MAIN_OBJECT) $(ESTRUTURAS_OBJECT) $(LIBS_OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compilação do main.c
$(MAIN_OBJECT): $(MAIN_SOURCE)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compilação do estruturas.c
$(ESTRUTURAS_OBJECT): $(ESTRUTURAS_SOURCE)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compilação dos arquivos da pasta libs
$(BUILD_DIR)/%.o: $(LIBS_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Limpa os arquivos compilados
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Recompila tudo
rebuild: clean all

# Marca alguns targets como não sendo arquivos
.PHONY: all clean rebuild setup check_deps

# Imprime informações de debug
debug:
	@echo "Main source: $(MAIN_SOURCE)"
	@echo "Estruturas source: $(ESTRUTURAS_SOURCE)"
	@echo "Arquivos na pasta libs: $(LIBS_SOURCES)"
	@echo "Objetos a serem criados: $(LIBS_OBJECTS)"
	@echo "Flags de compilação: $(CFLAGS)"
	@echo "Flags de linkagem: $(LDFLAGS)"