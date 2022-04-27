all: buffer
buffer:
	gcc -ggdb buffer.c -o buffer
clean: 
	rm -f buffer *.out
format:
	clang-format -i *.c
tidy:
	clang-tidy *.c
