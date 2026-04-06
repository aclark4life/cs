# Top-level Makefile for CS Coursework Portfolio

SUBDIRS = 262 301/gauss 466/shell

all:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done

rebuild: clean all

# Run specific project tests
test-262:
	$(MAKE) -C 262 test

docs:
	$(MAKE) -C docs html

docs-clean:
	$(MAKE) -C docs clean

.PHONY: all clean rebuild test-262 docs docs-clean
