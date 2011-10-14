CC=gcc
CC_FLAGS=
EXTRA_FLAGS=-g
LIBS=-lm
OBJS=main.o read_long.o tokenize.o prompt.o bust_a_fork.o check_for_exit.o find_crazy_tokens.o do_pipe.o bg.o dump_tokens.o
SRC=main.c read_long.c tokenize.c prompt.c bust_a_fork.c check_for_exit.c find_crazy_tokens.c do_pipe.c bg.c dump_tokens.c

.c.o:
	$(CC) $(CC_FLAGS) $(EXTRA_FLAGS) -c $*.c

ash: $(OBJS)
	$(CC) $(CC_FLAGS) $(EXTRA_FLAGS) $(OBJS) -o ash $(LIBS)

depend:
	makedepend $(SRC)

clean:
	rm *.o; 
# DO NOT DELETE THIS LINE -- make depend depends on it.
