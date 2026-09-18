/* ko.c - N-way merge of an arbitrary number of sorted "run" files into
 * one sorted output file, using a knock-out tree (binary min-heap) to
 * pick the overall minimum at each step.
 *
 * CS 364, Spring 1997 - "Assignment Next" (see asn.ko / asn.ko.annotated):
 *   Merge an arbitrary number of files of runs into one large sorted
 *   file, without knowing how many files there are until the program
 *   is called, using a knock-out tree (i.e. a heap) to find the
 *   minimum of a collection of values.
 *
 * Usage: ko outfile infile1 [infile2 ... infileN]
 *
 * The original assignment says the program should discover the run
 * files by scanning the current directory (see the abandoned attempts
 * in 1.c-5.c, ko2.c, open.c/open1.c). That's fragile in a directory
 * full of unrelated files (like this repository), so this version
 * takes the file list on the command line instead - the number of
 * files (argc - 2) is still not known until the program runs, which
 * is the actual point of the exercise. The merge/heap logic below is
 * the part of the assignment that was never finished.
 *
 * Each input file holds whitespace-separated integers in ascending
 * order (a "run"), e.g. the output of 364/rng.c piped through
 * 364/split.c. Output is the fully-sorted union of all runs.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int value;
  int file_index;
} heap_entry;

static void swap_entries(heap_entry *a, heap_entry *b) {
  heap_entry tmp = *a;
  *a = *b;
  *b = tmp;
}

/* Standard binary min-heap sift-down over heap[0..size-1]. */
static void sift_down(heap_entry *heap, int size, int i) {
  for (;;) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left].value < heap[smallest].value)
      smallest = left;
    if (right < size && heap[right].value < heap[smallest].value)
      smallest = right;
    if (smallest == i)
      return;

    swap_entries(&heap[i], &heap[smallest]);
    i = smallest;
  }
}

static void heapify(heap_entry *heap, int size) {
  int i;
  for (i = size / 2 - 1; i >= 0; i--)
    sift_down(heap, size, i);
}

int main(int argc, char *argv[]) {
  int num_files, i, heap_size;
  FILE *outfile;
  FILE **infiles;
  heap_entry *heap;

  if (argc < 3) {
    fprintf(stderr, "usage: %s outfile infile1 [infile2 ... infileN]\n",
            argv[0]);
    return 1;
  }

  num_files = argc - 2;
  if (num_files > FOPEN_MAX - 1) {
    /* -1 leaves room for outfile as well. */
    fprintf(stderr, "%s: too many input files (%d), FOPEN_MAX is %d\n",
            argv[0], num_files, FOPEN_MAX);
    return 1;
  }

  outfile = fopen(argv[1], "w");
  if (outfile == NULL) {
    fprintf(stderr, "%s: unable to open output file %s\n", argv[0], argv[1]);
    return 1;
  }

  infiles = (FILE **)malloc(num_files * sizeof(FILE *));
  heap = (heap_entry *)malloc(num_files * sizeof(heap_entry));
  if (infiles == NULL || heap == NULL) {
    fprintf(stderr, "%s: out of memory\n", argv[0]);
    free(infiles);
    free(heap);
    fclose(outfile);
    return 1;
  }

  /* Open every input file and seed the heap with each one's first
   * value. A file that is missing or already empty simply never gets
   * an entry. */
  heap_size = 0;
  for (i = 0; i < num_files; i++) {
    int value;

    infiles[i] = fopen(argv[i + 2], "r");
    if (infiles[i] == NULL) {
      fprintf(stderr, "%s: unable to open input file %s, skipping\n", argv[0],
              argv[i + 2]);
      continue;
    }
    if (fscanf(infiles[i], "%d", &value) == 1) {
      heap[heap_size].value = value;
      heap[heap_size].file_index = i;
      heap_size++;
    } else {
      fclose(infiles[i]);
      infiles[i] = NULL;
    }
  }
  heapify(heap, heap_size);

  /* Repeatedly knock out the smallest value, write it, and refill
   * from the file it came from (or drop that slot if it's exhausted). */
  while (heap_size > 0) {
    int winner_file = heap[0].file_index;
    int next_value;

    fprintf(outfile, "%d\n", heap[0].value);

    if (fscanf(infiles[winner_file], "%d", &next_value) == 1) {
      heap[0].value = next_value;
    } else {
      fclose(infiles[winner_file]);
      infiles[winner_file] = NULL;
      heap_size--;
      heap[0] = heap[heap_size];
    }
    sift_down(heap, heap_size, 0);
  }

  for (i = 0; i < num_files; i++) {
    if (infiles[i] != NULL)
      fclose(infiles[i]);
  }
  free(infiles);
  free(heap);
  fclose(outfile);
  return 0;
}
