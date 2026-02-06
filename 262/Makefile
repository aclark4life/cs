# Makefile for CS 262 Programs
# Basic C programming exercises

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
LDFLAGS = -lm

# Programs
PROGRAMS = avg counter list roach trapezoid

# Default target
all: $(PROGRAMS)

# Individual targets
avg: avg.c
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

counter: counter.c
	$(CC) $(CFLAGS) $< -o $@

list: list.c
	$(CC) $(CFLAGS) $< -o $@

roach: roach.c
	$(CC) $(CFLAGS) $< -o $@

trapezoid: trapezoid.c
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

# Clean
clean:
	rm -f $(PROGRAMS) *.o

# Rebuild
rebuild: clean all

# Test (if test files exist)
test: all
	@echo "Running tests..."
	@echo "Test avg with sample input:"
	@echo "1 2 3" | ./avg 3

.PHONY: all clean rebuild test

