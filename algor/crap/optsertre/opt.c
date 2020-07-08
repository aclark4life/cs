#include <stdio.h>
#define N 100

sum() {}
min() {}
void optsearchtree(int n, int p[N], int minavg, int R[N][N]) {
  int i, j, k, diagonal;
  int A[N][N];

  for (i = 1; i < n; i++) {
    A[i][i - 1] = 0;
    A[i][i] = p[i];
    R[i][i] = i;
    R[i][i - 1] = 0;
  }
  A[n + 1][n] = 0;
  R[n + 1][n] = 0;
  for (diagonal = 1; diagonal < n - 1; diagonal++) {
    for (i = 1; i < n - diagonal; i++) {
      j = i + diagonal;
      A[i][j] = min(A[i][k - 1] + A[k + 1][j]) + sum(p);
      //			R[i][j]= a value of k that gave the minimum.
    }
  }
  minavg = A[1, n];
}

void main() {

  int n = N;
  int p[N];
  int minavg;
  int R[N][N];

  optsearchtree(n, p, minavg, R);
}
