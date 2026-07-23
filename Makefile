# Compiler & Flags
CC      := gcc
CFLAGS  := -Wall -Wextra -std=c99 -g -Isrc

# Directories
SRC_DIR := src

# Target executable name
TARGET  := parable

# Source, Header, and Object files
SRCS    := $(SRC_DIR)/main.c $(SRC_DIR)/lexer.c
HEADERS := $(SRC_DIR)/lexer.h
OBJS    := $(SRCS:.c=.o)

# Default rule
all: $(TARGET)

# Link object files into final executable at the project root
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Compile individual source files from src/ into .o files inside src/
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
