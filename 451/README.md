# CS 451 - Programming Languages

Comparative survey of programming-language paradigms: imperative (C), object-oriented (Java, Smalltalk), functional (ML, Scheme), and logic (Prolog).

## Subdirectories

### ht/ and st/
C implementations of a hash table (`ht.c`/`.h`) and a symbol table (`st.c`/`symbol.c`), used as scaffolding for a "review" (`review/ht.c`) and later the scanner/symbol-table project below. See `st/README.md` for details on the symbol table.

### java/
Java projects, including `JuggleAnim.java` (an applet-based juggling animation, based on Jack Boyce's `JugglingLab`), a font demo (`font.java`), and shape/point classes (`shape.java`, `point.java`).

### ml/
Standard ML exercises: quicksort (`qsort.ml`) and the Sieve of Eratosthenes (`sieve.ml`), with example session transcripts (`example.ml.run`/`.output`).

### pl/
Prolog exercises: list permutation/append (`ms.pl`) and other logic-programming examples (`examples.pl`), plus a Tower of Hanoi solver (`hanoi`) and a prolog puzzle solver.

### scheme/
Scheme exercises: a postfix-expression calculator (`postfix.scm`) and the Sieve of Eratosthenes (`sieve.scm`), with example session output (`scheme.output`).

### scanner/
A Smalltalk lexical scanner (`simple-scanner.st`, `myscanner.st`) and a reserved-word variant (`reserved-word-scanner.st`), with a companion test script (`simple-scanner-test.st`).

## Building

C projects (`ht/`, `st/`) build with a standard `gcc` invocation or the `Makefile` in `java/`; ML/Scheme/Prolog/Smalltalk files are run with their respective interpreters (`sml`, `scheme`, `swipl`/`prolog`, `gst`).
