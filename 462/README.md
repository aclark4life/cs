# CS 462 - Algorithm Analysis

Complexity analysis and implementations of classic algorithms: shortest paths, sorting, and combinatorial optimization.

## Projects

### tsp/
Traveling Salesman Problem solver (`tsp.c`) with matrix-based input (`matrix_input.c`), a random instance generator (`rand.c`), and numerous sample instances (`sample*.in`, `in.easy`, `in.hard`).

### etsp/
An earlier/experimental TSP variant (`main.c`), with its own `input`, `help`, and `data_manag` (data management) modules.

### floyd/
Floyd-Warshall all-pairs shortest-path algorithm (`floyd.c`), with sample output (`sample.out`).

### pasc/
Pascal's Triangle generation (`pascals_triangle.c`), with a minimal binomial-coefficient variant (`b1.c`).

### sorting/
Quicksort (`quicksort.c`) and a priority-queue implementation (`pq.cpp`/`pq.h`), with a shared timing harness (`sort_main.c`, `delcher.h`).

### qtest/
Benchmarks the standard C library `qsort` (`qtest.c`), with an alternate comparison implementation (`russo.c`).

### crap/
Scratch/experimental code (matrix and max-finding exercises, an "optsertre" data structure prototype) not part of a graded assignment.

## Building

Most subdirectories compile with a plain `gcc`/`g++` invocation, e.g.:
```bash
gcc tsp/tsp.c tsp/matrix_input.c -o tsp/tsp
```
`tsp/` includes its own `Makefile`.
