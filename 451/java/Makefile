JAVAC = javac
CLASSES = MyApplet.class point.class shape.class

all: $(CLASSES)

%.class: %.java
	$(JAVAC) $<

clean:
	rm -f *.class

.PHONY: all clean
