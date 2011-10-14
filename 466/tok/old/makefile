CC=gcc
CC_FLAGS=
EXTRA_FLAGS=-g
LIBS=-lm -lnsl -lsocket
OBJS=tok.o tok_init.o sok.o
SRC=tok.c tok_init.c sok.c

.c.o:
	$(CC) $(CC_FLAGS) $(EXTRA_FLAGS) -c $*.c

ash: $(OBJS)
	$(CC) $(CC_FLAGS) $(EXTRA_FLAGS) $(OBJS) -o to $(LIBS)

depend:
	makedepend $(SRC)

clean:
	rm *.o; 
# DO NOT DELETE THIS LINE -- make depend depends on it.
