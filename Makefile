# Top-level Makefile for CS Coursework Portfolio

SUBDIRS = \
	262 \
	295 \
	301/determinant \
	301/gauss \
	301/generic \
	301/inverse \
	301/multiply \
	301/ortho \
	462/tsp \
	466/shell

all:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done

docs:
	$(MAKE) -C docs html

docs-clean:
	$(MAKE) -C docs clean

rebuild: clean all

.PHONY: all clean rebuild docs docs-clean
