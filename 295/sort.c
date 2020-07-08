#include </usr/sys/h/timeb.h>
#include <stdio.h>

#define number 1000
int ImprovedBubble(int a[], int n) {
  int i, pass = 1, sorted = 0;
  int temp;
  while (sorted == 0) {
    sorted = 1;
    for (i = 0; i < n - pass; i++)
      if (a[i] > a[i + 1]) {
        temp = a[i];
        a[i] = a[i + 1];
        a[i + 1] = temp;
        sorted = 0;
      }
    pass++;
  }
}

int main() {

  int a[number];
  int i;
  int j;
  int r;
  struct timeb t1, t2;
  double difftime;

  for (i = 0; i < number; i++) {
    r = rand();
    a[i] = r;
  }

  ftime(&t1);
  printf("thousandths of a second: %d\n", t1.millitm);

  ImprovedBubble(a, number);

  ftime(&t2);
  /* for(i=0;i<number;i++)
     fprintf(stderr,"a[%d] = %d\n",i,a[i]);
   */
  printf("thousandths of a second: %d\n", t1.millitm);
  difftime = (double)t2.time - t1.time + (t2.millitm - t1.millitm) / 1000.0;
  printf("elapsed time = %.3f seconds\n", difftime);
}
