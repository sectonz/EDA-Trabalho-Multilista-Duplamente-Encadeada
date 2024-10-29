# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra $(shell pkg-config --cflags gtk+-3.0)
LDFLAGS = $(shell pkg-config --libs gtk+-3.0)

# Diretórios
LIBS_DIR = libs
BUILD_DIR = build
INCLUDE_DIR = $(LIBS_DIR)/include

# Encontra todos os arquivos .c na pasta libs
LIBS_SOURCES = $(wildcard $(LIBS_DIR)/*.c)
# Gera os nomes dos objetos correspondentes na pasta build
LIBS_OBJECTS = $(patsubst $(LIBS_DIR)/%.c,$(BUILD_DIR)/%.o,$(LIBS_SOURCES))

# Arquivos principais
MAIN_OBJECT = $(BUILD_DIR)/main.o
ESTRUTURAS_OBJECT = $(BUILD_DIR)/estruturas.o

# Nome do executável final
TARGET = programa

# Regra principal
all: setup $(TARGET)

# Cria os diretórios necessários
setup:
	@mkdir -p $(BUILD_DIR)

# Link final
$(TARGET): $(MAIN_OBJECT) $(ESTRUTURAS_OBJECT) $(LIBS_OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compilação do main.c
$(MAIN_OBJECT): main.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compilação do estruturas.c
$(ESTRUTURAS_OBJECT): estruturas.c
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
.PHONY: all clean rebuild setup

# Imprime informações de debug (útil para depuração do Makefile)
debug:
	@echo "Arquivos na pasta libs: $(LIBS_SOURCES)"
	@echo "Objetos a serem criados: $(LIBS_OBJECTS)"
	@echo "Flags de compilação: $(CFLAGS)"
	@echo "Flags de linkagem: $(LDFLAGS)"