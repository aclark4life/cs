CFLAGS	= -O -w
LFLAGS	=
CC	= gcc
GCC	= g++

SRC     = scan.l main.c
OBJ     = scan.o main.o

a.out   : $(OBJ)
	g++ $(OBJ)

main.o  :
	g++ -O -c -g main.c

clean	:
	rm -f a.out main.o scan.o core *.*~

