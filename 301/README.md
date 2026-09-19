# CS 301 - Computational Linear Algebra

Implementations of numerical methods for solving and manipulating matrices, written in C.

## Projects

### gauss/
Gauss-Jordan elimination (`gauss_jordan.c`/`.h`) for solving M×N linear systems, including sample homogeneous (`.hom`), inconsistent (`.nosol`), and edge-case (`.choke`) test inputs. Includes correspondence with the professor discussing the algorithm's edge cases.

### determinant/
Computes the determinant of a matrix (`determinant.c`) via cofactor/row-reduction, with numbered sample inputs (`1`-`4`) and `sample.in`.

### inverse/
Computes the inverse of a matrix (`matrix_inverse.c`).

### multiply/
Matrix multiplication (`matrix_multiply.c`) with sample input files.

### ortho/
Gram-Schmidt-style orthogonalization of a matrix's rows/columns (`ortho.c`).

### generic/
A general-purpose matrix utility (`matrix.c`) used across the other assignments.

### asn/
Assignment write-ups/specifications for the course.

### misc/
Miscellaneous scratch code, including a C++ array test (`test_array.cpp`).

## Building

Each subdirectory has its own `Makefile`:
```bash
cd gauss && make
```
