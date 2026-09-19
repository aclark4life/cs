# CS 295 - Discrete Structures

Short C programs exploring discrete-math topics: recursion, combinatorics, finite state machines, and sorting/timing analysis.

## Programs

### compound.c
Recursively computes compound interest on a $1000 principal at 5.5% over `t` years.

### factorial.c
Recursive factorial computation, `n!`.

### fsa.c
Simulates a simple finite-state automaton, reading integer inputs and transitioning between states until an end-of-input sentinel (`-1`) is seen.

### hanoi.c
Generates the move counts for the Tower of Hanoi recurrence, `m[k] = 2*m[k-1] + 1`.

### improved_bubble.c / sort.c / time.c
Variations of an "improved" bubble sort (early exit once the array is sorted), used to benchmark sorting performance via `sys/timeb.h`/`time.h`.

### swap.c
Minimal command-line argument parsing example (`atoi` on `argv[1]`).

## Building

A `Makefile` is provided:
```bash
make
```

Or compile individually:
```bash
gcc <filename>.c -o <program_name>
```
