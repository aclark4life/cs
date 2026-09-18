# Makefile for CS 364 - File and Data Structures
# Assignment 2: run-splitting and merging (splitter, merge, ko), plus
# supporting utilities (rng, buffer, tmpnam).

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic

PROGRAMS = buffer ko merge rng split tmpnam

all: $(PROGRAMS)

buffer: buffer.c
	$(CC) $(CFLAGS) $< -o $@

ko: ko.c
	$(CC) $(CFLAGS) $< -o $@

merge: merge.c
	$(CC) $(CFLAGS) $< -o $@

rng: rng.c
	$(CC) $(CFLAGS) $< -o $@

split: split.c
	$(CC) $(CFLAGS) $< -o $@

tmpnam: tmpnam.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(PROGRAMS) *.o

rebuild: clean all

.PHONY: all clean rebuild
