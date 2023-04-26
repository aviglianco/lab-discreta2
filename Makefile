# Compiler and linker settings
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -g -O3
LDFLAGS =

# Source file settings
SRCS = main.c APIG23.c Greedy.c Orden.c
OBJS = $(SRCS:.c=.o)

# Build targets
TARGET = grafo

# Rule for building the executable
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET)

# Rules for building object files
main.o: main.c APIG23.h EstructuraGrafo23.h APIParte2.h
APIG23.o: APIG23.c APIG23.h
Greedy.o: Greedy.c Orden.c APIParte2.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

