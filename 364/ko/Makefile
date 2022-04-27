all: ko
clean:
	rm -f ko
ko:
	gcc -ggdb ko.c -o ko -lm
format:
	clang-format -i *.c
tidy:
	clang-tidy *.c
