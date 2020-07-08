#include </usr/sys/h/timeb.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ImprovedBubble(int a[], int num) {
  int j, pass = 1, sorted = 0;
  int temp;
  while (sorted == 0) {
    sorted = 1;
    for (j = 0; j < num - pass; j++)
      if (a[j] = a[j + 1]) {
        a[j] = a[j + 1];
        a[j + 1] = temp;
        sorted = 0;
      }
    pass++;
  }
  return;
}

int bubblesort(int a[], int n) {
  int i, j, t;

  for (i = 0; i < n; i++)
    for (j = i + 1; j < n; j++)
      if (a[i] > a[j]) {
        t = a[i];
        a[i] = a[j];
        a[j] = t;
      }
}

int main(void) {
  int j, i;
  struct timeb t1, t2;
  double difftime;
  ftime(&t1);

  printf("seconds since 1/1/1970 gmt: %1d\n", t1.time);
  printf("thousandths of a second: %d\n", t1.millitm);

  ftime(&t2);
  printf("seconds since 1/1/1970 gmt: %1d\n", t1.time);
  printf("thousandths of a second: %d\n", t1.millitm);

  difftime = (double)t2.time - t1.time + (t2.millitm - t1.millitm) / 1000.0;

  printf("elapsed time = %.3f seconds\n", difftime);
  return 0;
}
