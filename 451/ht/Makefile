#
# -g debug flag
#
hash:	main.o ht.o util.o
	gcc -o hash main.o ht.o util.o

main.o:	main.c ht.h
	gcc -c -O main.c -o main.o

ht.o:	ht.c ht.h
	gcc -c -O ht.c -o ht.o

util.o:	util.c 
	gcc -c -O util.c -o util.o

clean:
	@-/bin/rm hash *.o a.out core xx &> /dev/null

# DO NOT DELETE THIS LINE -- make depend depends on it.

ht.o: /usr/include/stdio.h /usr/include/ansi_compat.h htP.h util.h
ht_hand-out.o: /usr/include/stdio.h /usr/include/ansi_compat.h htP.h util.h
main.o: /usr/include/stdio.h /usr/include/ansi_compat.h ht.h util.h
util.o: /usr/include/stdio.h /usr/include/ansi_compat.h
