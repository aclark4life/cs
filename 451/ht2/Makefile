#
# -g debug flag -O%d optimize
#
.c.o:
	gcc -c -g $*.c -o $*.o

st:	main2.o  util.o st.o ht.o symbol.o
	gcc -o st main2.o    util.o st.o ht.o symbol.o

ht.o:	../assignment1/ht.c ../assignment1/ht.h
	gcc -c -g ../assignment.1/ht.c -o ht.o

clean:
	@-/bin/rm hash *.o a.out core xx &> /dev/null

# DO NOT DELETE THIS LINE -- make depend depends on it.

main2.o: /usr/include/stdio.h /usr/include/ansi_compat.h st.h
main2.o: ../assignment1/ht.h symbol.h
st.o: /usr/include/stdio.h /usr/include/ansi_compat.h stP.h
st.o: ../assignment1/ht.h
symbol.o: symbolP.h symbol.h util.h
util.o: /usr/include/stdio.h /usr/include/ansi_compat.h
