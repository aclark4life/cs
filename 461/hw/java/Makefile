JAVAC = javac
CLASSES = hello.class

all: $(CLASSES)

%.class: %.java
	$(JAVAC) $<

clean:
	rm -f *.class

.PHONY: all clean
