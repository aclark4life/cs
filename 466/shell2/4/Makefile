CC=gcc
CC_FLAGS=
EXTRA_FLAGS=-g
LIBS=-lm
OBJS=main.o read_long.o tokenize.o handle_tokens.o handle_greater_than.o dump_tokens.o prompt.o

SRC=main.c read_long.c tokenize.c handle_tokens.c handle_greater_than.c dump_tokens.c prompt.c

.c.o:
	$(CC) $(CC_FLAGS) $(EXTRA_FLAGS) -c $*.c

ash: $(OBJS)
	$(CC) $(CC_FLAGS) $(EXTRA_FLAGS) $(OBJS) -o ash $(LIBS)

depend:
	makedepend $(SRC)

clean:
	rm *.o; 
# DO NOT DELETE THIS LINE -- make depend depends on it.
