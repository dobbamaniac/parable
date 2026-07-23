# Compiler & Flags
CC      := gcc
CFLAGS  := -Wall -Wextra -std=c99 -g -Isrc

# Directories
SRC_DIR := src
OUT_DIR := out

# Target executable name
TARGET  := parabl

# Source, Header, and Object files
SRCS    := $(SRC_DIR)/main.c $(SRC_DIR)/lexer.c
HEADERS := $(SRC_DIR)/lexer.h
OBJS    := $(patsubst $(SRC_DIR)/%.c, $(OUT_DIR)/%.o, $(SRCS))

# Default target
all: $(TARGET)

# Link object files into final executable at project root
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Create output directory if it doesn't exist
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# Compile .c files into .o files into out/
$(OUT_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files and out/ directory
clean:
	rm -rf $(OUT_DIR) $(TARGET)

.PHONY: all clean
