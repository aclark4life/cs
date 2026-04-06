all:
	gcc -c -g m.c && gcc m.o -o m
	gcc -c -g t.c && gcc t.o -lm -o t

clean:
	rm -f m t *.o

.PHONY: all clean
