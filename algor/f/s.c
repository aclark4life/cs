#include <limits.h>
#include <stdio.h>

long input[100];
long T = 0;
int c = 0;

echo_input() {
  int i;
  printf("I=\n");
  for (i = 0; i < c; i++) {
    printf("%d\n", input[i]);
  }
  printf("T=\n%d\n", T);
}

read_input() {
  while (fscanf(stdin, "%d", &input[c]) != EOF) {
    // printf ( "%s\n", input[c]);
    c++;
  }
  T = input[0];
}

int partition(int lo, int hi) {
  long pivot = input[lo];
  while (lo < hi) {
    while (pivot < input[hi])
      hi--;
    if (lo < hi)
      input[lo++] = input[hi];
    while (lo < hi && input[lo] <= pivot)
      lo++;
    if (lo < hi)
      input[hi--] = input[lo];
  }
  input[lo] = pivot;
  return lo;
}

void quicksort(int lo, int hi) {
  int position;
  int i;

  if (lo < hi) {
    position = partition(lo, hi);
    quicksort(lo, position - 1);
    quicksort(position + 1, hi);
  }
}

main() {
  int i;
  read_input();
  echo_input();
  quicksort(0, c - 1);
  for (i = 0; i < c; i++) {
    printf("%d\n", input[i]);
  }
}
