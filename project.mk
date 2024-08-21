# Custom Makefile
# Add your custom makefile commands here
#
PROJECT_NAME := cs

cs:
	cd src; make
	cd src/data-structures; make


clean:
	cd src; make clean
	cd src/data-structures; make clean

tree:
	tree -P *.c

t: tree
