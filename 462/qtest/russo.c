
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int int_compare(a, b) int *a, *b;
{
  if (*a < *b)
    return -1;
  if (*a > *b)
    return 1;
  return 0;
}

int main(int argc, char *argv[]) {

  int *A;
  long i, n;
  clock_t start, stop;

  if (argc != 2) {
    fprintf(stderr, "Usage is %s [integer].\n", argv[0]);
    exit(-1);
  }

  n = atol(argv[1]);

  printf("%ld\n", n);

  A = (int *)malloc(sizeof(int) * n);

  if (A == NULL) {

    fprintf(stderr, "No space\n");

    exit(-1);
  }

  for (i = 0; i < n; i++)
    A[i] = rand();

  /* time qsort */

  start = ((clock()) / CLOCKS_PER_SEC);
  qsort(A, n, sizeof(int), (*int_compare));
  stop = ((clock()) / CLOCKS_PER_SEC);
  printf("%ld\n", stop - start);

  /* time qsort on presorted data */

  start = ((clock()) / CLOCKS_PER_SEC);
  qsort(A, n, sizeof(int), (*int_compare));
  stop = ((clock()) / CLOCKS_PER_SEC);
  printf("%ld\n", stop - start);
}
