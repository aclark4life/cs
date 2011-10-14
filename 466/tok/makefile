CC=gcc
CC_FLAGS=
EXTRA_FLAGS=-g
#LIBS=-lm -lsocket -lnsl
LIBS=-lsocket -lnsl
OBJS=tok.o socket.o
SRC=tok.c socket.c

.c.o:
	$(CC) $(CC_FLAGS) $(EXTRA_FLAGS) -c $*.c
   
tok: 	$(OBJS)
	$(CC) $(CC_FLAGS) $(EXTRA_FLAGS) $(OBJS) -o tok $(LIBS)
   
depend:
	makedepend $(SRC)
     
clean:
	rm *.o;

# DO NOT DELETE THIS LINE -- make depend depends on it.
				      

