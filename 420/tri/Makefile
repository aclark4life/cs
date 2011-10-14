CC=gcc
CC_FLAGS=
EXTRA_FLAGS=-g
LIBS=-lm
#OBJS=tri.o
#SRC=tri.c

OBJS=main.o is_triangle.o prelim_check.o my_atoi.o
SRC=main.c is_triangle.c prelim_check.c my_atoi.c

.c.o:
	$(CC) $(CC_FLAGS) $(EXTRA_FLAGS) -c $*.c

tri: $(OBJS)
	$(CC) $(CC_FLAGS) $(EXTRA_FLAGS) $(OBJS) -o tri $(LIBS)

depend:
	makedepend $(SRC)

clean:
	rm *.o; rm shell;
# DO NOT DELETE THIS LINE -- make depend depends on it.

