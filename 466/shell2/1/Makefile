CC=gcc
CC_FLAGS=
EXTRA_FLAGS=-g
LIBS=-lm
OBJS=main.o read_long.o tokenize.o prompt.o no_token.o do_fork.o check_for_exit.o check_token.o my_pipe.o
SRC=main.c read_long.c tokenize.c prompt.c no_token.c do_fork.c check_for_exit.c check_token.c my_pipe.c

.c.o:
	$(CC) $(CC_FLAGS) $(EXTRA_FLAGS) -c $*.c

ash: $(OBJS)
	$(CC) $(CC_FLAGS) $(EXTRA_FLAGS) $(OBJS) -o ash $(LIBS)

depend:
	makedepend $(SRC)

clean:
	rm *.o; 
# DO NOT DELETE THIS LINE -- make depend depends on it.
