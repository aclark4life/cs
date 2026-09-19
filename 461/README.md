# CS 461 - Compiler Construction

Theory and practice of compiler front-ends, built with Flex/Lex.

## Contents

### project/
The main compiler project.
- `scan/scan.l` and `prac/scan.l` — Lex specifications defining the lexical grammar (identifiers, numeric/character/escape literals) for the language being compiled.
- `first/first.l` — an earlier lexer iteration, with its generated scanner (`first.yy.c`).
- `prac/main.c` — driver program that runs the generated scanner (`lex.yy.c`) over a sample input (`sample.in`).
- `structs.h` / `table.h` — shared token/symbol-table structures.
- `tok/` — token-list definitions (`tokens.h`, `list1`, `list2`) used by the scanner.

```bash
flex scan.l
gcc lex.yy.c main.c -o scan -ll
./scan < sample.in
```

### hw/
Homework exercises: variable-length stack allocation (`alloca/alloca.c`) vs. heap allocation (`alloca/malloc.c`), a minimal Java program (`java/hello.java`), and string statistics utilities (`stat/`).

### hw.text / hw.ps
Homework assignment write-ups (plain text and PostScript).

### fixprivs-email.txt / rcs-email.txt
Archived course-administration emails (file permissions fix, RCS usage).
