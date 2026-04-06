all:
	gcc -c -g matrix_input.c && gcc matrix_input.o -o matrix_input
	gcc -c -g tsp.c && gcc tsp.o -lm -o tsp

clean:
	rm -f matrix_input tsp *.o

.PHONY: all clean
