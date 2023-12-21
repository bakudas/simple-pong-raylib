# Nome do seu programa
PROG_NAME = game

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Arquivos fonte e objetos
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Flags de compilação
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/Cellar/raylib/5.0/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

# Regra principal
$(BIN_DIR)/$(PROG_NAME): $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

# Regra para arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/$(PROG_NAME)

# Phony targets
.PHONY: clean

