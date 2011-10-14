CC=gcc
CC_FLAGS=
EXTRA_FLAGS=-g
LIBS=-lm
OBJS=main.o fread_long.o read_long.c

SRC=main.c fread_long.c read_long.c

.c.o:
	$(CC) $(CC_FLAGS) $(EXTRA_FLAGS) -c $*.c

s: $(OBJS)
	$(CC) $(CC_FLAGS) $(EXTRA_FLAGS) $(OBJS) -o s $(LIBS)

depend:
	makedepend $(SRC)

clean:
	rm *.o; 
# DO NOT DELETE THIS LINE -- make depend depends on it.
