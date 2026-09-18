# justfile for the CS Coursework Portfolio
# Build and run the programs for each class with `just <recipe>`.
# Run `just --list` to see all available recipes.
#
# Example runs:
#   just cs262-avg 3                              # average of 3 ints (then type them)
#   just cs262-counter 262/counter.c               # letter-frequency count of a file
#   just cs262-roach 10 10 3 3                      # roach sim: n m ibug jbug
#   just cs262-trapezoid 0 1 2 5 10 0.5             # trapezoidal-rule integration
#   just cs295-factorial 5                          # 5!
#   just cs295-hanoi                                # Towers of Hanoi (no args)
#   just run 301/gauss gauss < 301/gauss/in/sample1.in     # Gauss-Jordan elimination
#   just run 301/generic matrix < 301/generic/sample.in    # generic matrix ops
#   just run 462/tsp tsp < 462/tsp/sample.in        # travelling-salesman search
#   just run 466/shell shell                        # interactive custom Unix-like shell
#   just cs364-rng 5                                # 5 pseudo-random numbers
#   just cs364-split 364/somefile.in                # split a stream into sorted runs
#   just cs364-ko out.txt run1.txt run2.txt run3.txt # N-way knock-out-tree merge
#   just dosbox-build hello hello.asm               # assemble/link 366/hello.asm via DOSBox

subdirs := "262 295 364 301/determinant 301/gauss 301/generic 301/inverse 301/multiply 301/ortho 462/tsp 466/shell"

# Show available recipes
default:
    @just --list

# Build every program in every class
build-all:
    #!/usr/bin/env bash
    set -euo pipefail
    for d in {{subdirs}}; do
        echo "==> Building $d"
        make -C "$d"
    done

# Build all programs in one class, e.g. `just build 262`
build class:
    make -C {{class}}

# Remove build artifacts for one class, e.g. `just clean 262`
clean class:
    make -C {{class}} clean

# Remove build artifacts for every class
clean-all:
    #!/usr/bin/env bash
    set -euo pipefail
    for d in {{subdirs}}; do
        make -C "$d" clean
    done

# Build (if needed) and run a single program, e.g. `just run 262 avg 3`
run class program *args:
    @make -C {{class}}
    ./{{class}}/{{program}} {{args}}

# --- 262: Programming and Data Structures ---
cs262-avg *args: (run "262" "avg" args)
cs262-counter *args: (run "262" "counter" args)
cs262-list *args: (run "262" "list" args)
cs262-roach *args: (run "262" "roach" args)
cs262-trapezoid *args: (run "262" "trapezoid" args)

# --- 295: Discrete Structures ---
cs295-compound *args: (run "295" "compound" args)
cs295-factorial *args: (run "295" "factorial" args)
cs295-fsa *args: (run "295" "fsa" args)
cs295-hanoi *args: (run "295" "hanoi" args)
cs295-improved-bubble *args: (run "295" "improved_bubble" args)
cs295-sort *args: (run "295" "sort" args)
cs295-swap *args: (run "295" "swap" args)
cs295-time *args: (run "295" "time" args)

# --- 301: Computational Linear Algebra ---
cs301-determinant *args: (run "301/determinant" "determinant" args)
cs301-gauss *args: (run "301/gauss" "gauss" args)
cs301-generic *args: (run "301/generic" "matrix" args)
cs301-inverse *args: (run "301/inverse" "matrix_inverse" args)
cs301-multiply *args: (run "301/multiply" "matrix_multiply" args)
cs301-ortho *args: (run "301/ortho" "ortho" args)

# --- 462: Algorithm Analysis ---
cs462-tsp *args: (run "462/tsp" "tsp" args)

# --- 466: Operating Systems ---
cs466-shell *args: (run "466/shell" "shell" args)

# --- 364: File and Data Structures ---
cs364-ko *args: (run "364" "ko" args)
cs364-merge *args: (run "364" "merge" args)
cs364-rng *args: (run "364" "rng" args)
cs364-split *args: (run "364" "split" args)

# --- 366: Systems Level Programming (x86 Assembly, via DOSBox) ---
# Assemble/link one or more 366/*.asm files with the original Turbo
# Assembler/Linker, e.g. `just dosbox-build hello hello.asm` or
# `just dosbox-build rocks rocks.asm shield.asm cities.asm image.asm
# screen.asm random.asm printhex.asm` for multi-module projects.
dosbox-build output *files:
    ./366/dosbox-build.sh {{output}} {{files}}

cs366-hello: (dosbox-build "hello" "hello.asm")
