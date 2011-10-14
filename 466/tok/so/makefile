CC=gcc
CC_FLAGS=
EXTRA_FLAGS=-g
#LIBS=-lm -lsocket -lnsl
LIBS=-lsocket -lnsl
OBJS=so.o socket.o

SRC=so.c socket.c

.c.o:
	$(CC) $(CC_FLAGS) $(EXTRA_FLAGS) -c $*.c
   
so: 	$(OBJS)
	$(CC) $(CC_FLAGS) $(EXTRA_FLAGS) $(OBJS) -o so $(LIBS)

op.o:
	gcc -c op.c

op:  	op.o socket.o	
	gcc op.o socket.o -o op -lnsl -socket
   
depend:
	makedepend $(SRC)
     
clean:
	rm *.o;

# DO NOT DELETE THIS LINE -- make depend depends on it.
				      

