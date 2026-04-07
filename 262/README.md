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
Reads a text file and counts the frequency of each letter (A–Z), then prints each letter and its percentage share of total letters, sorted from most to least frequent.

**Usage:**
```bash
gcc counter.c -o counter
./counter somefile.txt
```

### list.c
Interactive sparse matrix tool backed by a doubly-linked circular list (one list per row, one per column). Supports creating two matrices, inserting nodes by row/col/value, and printing by row or column order.

**Usage:**
```bash
gcc list.c -o list
./list
```

### roach.c
Simulates a cockroach performing a random walk on a `cols×rows` grid. Runs until every cell has been visited or 50,000 moves have elapsed, then prints the visit count for each cell and the total number of moves made.

**Usage:**
```bash
gcc roach.c -o roach
./roach <cols> <rows> <start_col> <start_row>
# E.g.: ./roach 5 5 2 2
```

### trapezoid.c
Approximates the definite integral of `ax² + bx + c` over `[lower_bound, upper_bound]` using the trapezoidal rule with a given number of intervals.

**Usage:**
```bash
gcc trapezoid.c -lm -o trapezoid
./trapezoid <a> <b> <c> <lower_bound> <upper_bound> <num_intervals>
# E.g.: ./trapezoid 1 0 0 0 1 1000
```

## Building

A `Makefile` is provided — just run:
```bash
make
```

Or compile individually:
```bash
gcc <filename>.c -o <program_name>          # most programs
gcc <filename>.c -lm -o <program_name>      # avg.c and trapezoid.c require -lm
```

## Notes
- All programs include proper error handling
- Memory is properly managed (no leaks)
- Follow ANSI C standards
