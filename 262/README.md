# CS 262 - Introduction to Programming

Basic C programming exercises covering fundamental concepts.

## Programs

### avg.c
Calculate mean and standard deviation of integers.

**Usage:**
```bash
gcc avg.c -lm -o avg
./avg 3
# Enter 3 integers: 1 3 3
# Mean: 2.333333
# Standard Deviation: 1.154701
```

**Features:**
- Reads from stdin or file
- Calculates sample standard deviation
- Proper error handling

### counter.c
Basic counter program.

### list.c
Linked list implementation.

### roach.c
Roach simulation program.

### trapezoid.c
Trapezoid area calculation using numerical integration.

## Building

All programs can be compiled with:
```bash
gcc <filename>.c -o <program_name>
```

For programs using math functions (like avg.c):
```bash
gcc <filename>.c -lm -o <program_name>
```

## Notes
- All programs include proper error handling
- Memory is properly managed (no leaks)
- Follow ANSI C standards

