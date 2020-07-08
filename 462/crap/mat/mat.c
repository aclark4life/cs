#include <stdio.h>
// didn't get to spend too much time on this one.
// it goes a little something like this...

void func() {
  int i, j, n, diagonal;
  i = 0;
  j = 0;
  n = 0;
  diagonal = 0;

  for (i = 0; i < n; i++) {
    // M[i,i] = 0 ;
  }
  for (diagonal = 1; diagonal < n - 1; diagonal++) {
    for (i = 1; i < n - diagonal; i++) {
      j = i + diagonal;
      // M[i,j] = min ( M [i,k] + M[k+ 1,j] + d[i-1]*d[k]*d[j]);
      // P[i,j] = a value of k that gave the min
    }
  }
  //	minmult = M[1,n];
}
void print() {
  int i, j;

  i = 0;
  j = 0;
  if (i == j)
    printf("A %d", i);
  else {
    //		k = P[i,j];
    printf("(");
    //		order(i,k);
    //		order(k+1,j);
    printf(")");
  }
  printf("\n");
}

void main() {

  func();
  print();
}
