# CS 364 - File and Data Structures

External-storage algorithms for sorting and merging large files of records that don't fit in memory.

## Programs

### split.c
Splits an input file into sorted "runs," writing each run to a temporary output file (via `mkstemp`).

### merge.c
Performs a pairwise (2-way) merge of two sorted run files into one sorted output file.

### ko.c
The "knock-out tree" (N-way merge) assignment: merges an arbitrary number of sorted run files into a single sorted output using a binary min-heap to select the minimum at each step.
```bash
gcc ko.c -o ko
./ko outfile infile1 [infile2 ... infileN]
```
See `asn.ko` / `asn.ko.annotated` for the original assignment text and notes on the final approach.

### buffer.c
Double-buffered file I/O experiment (raw `read`/`write` with alternating buffers).

### rng.c / tmpnam.c
Small utilities used while developing the run-generation and temp-file logic above.

## Building

A `Makefile` is provided:
```bash
make
```
