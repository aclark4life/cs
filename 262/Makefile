objects = avg.o

clean:
	rm -f avg.o avg

all: avg list roach

avg: $(objects)
	gcc -o avg $(objects) -lm

counter:
	gcc counter.c -o counter

list:
	gcc list.c -o list

roach:
	gcc roach.c -o roach

trapezoid:
	gcc trapezoid.c -o trapezoid

clean:
	rm *.o avg list roach

format:
	clang-format -i *.c
tidy:
	/opt/homebrew/Cellar/llvm/17.0.6_1/bin/clang-tidy avg.c
