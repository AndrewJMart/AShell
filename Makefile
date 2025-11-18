# Compiler And Flags
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

# Directories
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
OBJ_DIR = obj

# Files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
TARGET = $(BIN_DIR)/AShell

# Default Target
all: $(TARGET)

# Create Binary Folder
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

# Compile to Obj
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create Dirs
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean Build
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)/*.o $(TARGET)

# Run Shell
run: $(TARGET)
	$(TARGET)

.PHONY: all clean run

