CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = -lm

TARGET = gauss

all: $(TARGET)

$(TARGET): g.c
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
