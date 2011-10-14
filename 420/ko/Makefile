CC=gcc
#CC_FLAGS=
EXTRA_FLAGS=-g
#LIBS=-lm
OBJS=ko.o do.o 
SRC=ko.c do.c


.c.o:
	$(CC) $(CC_FLAGS) $(EXTRA_FLAGS) -c $*.c

ko: 	$(OBJS)
	$(CC) $(CC_FLAGS) $(EXTRA_FLAGS) $(OBJS) -o ko $(LIBS)

depend:
	makedepend $(SRC)
clean:
	rm *.o 

# DO NOT DELETE THIS LINE -- make depend depends on it.

main.o: /usr/include/stdio.h /usr/include/sys/feature_tests.h
main.o: /usr/include/sys/va_list.h
make_array_o_fp.o: /usr/include/stdio.h /usr/include/sys/feature_tests.h
make_array_o_fp.o: /usr/include/sys/va_list.h
