all:
	cd 262; make all
	cd 295; make all
clean:
	cd 262; make clean
	cd 295; make clean
black:
	cd 262; make black
	cd 295; make black

avg:
	262/avg 3
list:
	262/list
