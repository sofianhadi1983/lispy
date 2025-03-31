# Compiler settings
CC = cc
CFLAGS = -std=c99 -Wall
LIBS = -ledit -lm

# Source files
SRC = parsing.c mpc.c

# Output executable
TARGET = parsing.out

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LIBS) -o $(TARGET)

# Clean build files
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean