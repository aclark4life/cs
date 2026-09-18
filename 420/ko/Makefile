# Makefile for CS 420/ko - N-way knock-out (heap) merge

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic

TARGET = ko

all: $(TARGET)

$(TARGET): ko.c
	$(CC) $(CFLAGS) $< -o $(TARGET)

clean:
	rm -f $(TARGET) *.o

rebuild: clean all

.PHONY: all clean rebuild
