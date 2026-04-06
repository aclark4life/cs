# Makefile for CS 295 - Algorithms
# Algorithm implementations and exercises

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
LDFLAGS = -lm

# Programs
PROGRAMS = compound factorial fsa hanoi improved_bubble sort swap time

# Default target
all: $(PROGRAMS)

# Individual targets
compound: compound.c
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

factorial: factorial.c
	$(CC) $(CFLAGS) $< -o $@

fsa: fsa.c
	$(CC) $(CFLAGS) $< -o $@

hanoi: hanoi.c
	$(CC) $(CFLAGS) $< -o $@

improved_bubble: improved_bubble.c
	$(CC) $(CFLAGS) $< -o $@

sort: sort.c
	$(CC) $(CFLAGS) $< -o $@

swap: swap.c
	$(CC) $(CFLAGS) $< -o $@

time: time.c
	$(CC) $(CFLAGS) $< -o $@

# Clean
clean:
	rm -f $(PROGRAMS) *.o

# Rebuild
rebuild: clean all

# Test
test: factorial
	@echo "Testing factorial..."
	./factorial 5
	./factorial 10

.PHONY: all clean rebuild test
