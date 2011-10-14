CC=gcc
CC_FLAGS=
EXTRA_FLAGS=-g
LIBS=-lm
#OBJS=tri.o
#SRC=tri.c

OBJS=main.o what_kind.o 
SRC=main.c what_kind.c 

.c.o:
	$(CC) $(CC_FLAGS) $(EXTRA_FLAGS) -c $*.c

tri: $(OBJS)
	$(CC) $(CC_FLAGS) $(EXTRA_FLAGS) $(OBJS) -o tri $(LIBS)

depend:
	makedepend $(SRC)

clean:
	rm *.o; rm shell;
# DO NOT DELETE THIS LINE -- make depend depends on it.

#xmalloc.o: /usr/include/stdio.h /usr/include/ansi_compat.h
#xmalloc.o: /usr/include/sys/types.h
#read_long.o: /usr/include/stdio.h /usr/include/ansi_compat.h
#file.o: /usr/include/stdio.h /usr/include/ansi_compat.h

