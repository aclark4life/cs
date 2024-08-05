PROJECT_NAME := cs

include cs.mk


tree:
	tree -P *.c

t: tree
