CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
LDFLAGS =

SRC = main.c tokenize.c dump_tokens.c handle_tokens.c handle_greater_than.c \
      handle_less_than.c handle_pipe.c prompt.c read_long.c
OBJ = $(SRC:.c=.o)
TARGET = shell

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
