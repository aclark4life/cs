CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = -lm

TARGET = gauss

all: $(TARGET)

$(TARGET): gauss_jordan.c
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
