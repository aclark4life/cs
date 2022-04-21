all:
	cd 262; make all
	cd 295; make all
	cd 364/buffer; make
	cd 364/ko; make
clean:
	cd 262; make clean
	cd 295; make clean
	cd 364/buffer; make clean
	cd 364/ko; make clean
black:
	cd 262; make black
	cd 295; make black
	cd 364; make black

avg:
	262/avg 3
list:
	262/list

buffer:
	cd 364/buffer; ./buffer input.txt
ko:
	364/ko/ko
