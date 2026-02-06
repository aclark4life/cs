# Makefile for Data Structures
# Basic data structure implementations in C

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic

# Programs
PROGRAMS = array list stack queue tree

# Default target
all: $(PROGRAMS)

# Individual targets
array: array.c
	$(CC) $(CFLAGS) $< -o $@

list: list.c
	$(CC) $(CFLAGS) $< -o $@

stack: stack.c
	$(CC) $(CFLAGS) $< -o $@

queue: queue.c
	$(CC) $(CFLAGS) $< -o $@

tree: tree.c
	$(CC) $(CFLAGS) $< -o $@

# Clean
clean:
	rm -f $(PROGRAMS) *.o

# Rebuild
rebuild: clean all

# Run all programs
run: all
	@echo "=== Array ==="
	./array
	@echo "\n=== List ==="
	./list
	@echo "\n=== Stack ==="
	./stack
	@echo "\n=== Queue ==="
	./queue
	@echo "\n=== Tree ==="
	./tree

# Test
test: run

.PHONY: all clean rebuild run test

