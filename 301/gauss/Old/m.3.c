/* m.c - Perform Gauss-Jordan Elimination on an mxn matrix .
 * Alex Clark - September 1998  .
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **A, m, n;
void get_mn();
void get_mem();
void get_mtrx();
void get_nonzero1();
void get_nonzero2();

void main(int argc) {
  if (argc != 1) {
    exit(-1);
  } else {
    get_mn();
    get_mem();
    get_mtrx();
    get_nonzero1();
  }
}
void get_nonzero1() {
  int i, j;
  for (i = 1; i <= m; i++) {
    for (j = 1; j <= n; j++) {
      if (A[i][j] != 0 && j == n)
        printf("row %d\n", i);
    }
  }
}
void get_nonzero2() {
  int i, j, k;
  for (i = j = 1; i <= m && j <= n; j++) {
    if (A[i][j] != 0) {
      // printf ("%d %d %d %d\n",m,n,i,j);
      printf("%d ", A[i][j]);
    } else {
      i++;
      printf("%d %d %d %d\n", m, n, i, j);
    }
  }
  printf("\n");
}
void get_mn() {
  int i, j;
  scanf("%d %d\n", &m, &n);
}
void get_mem() {
  int i, j;
  A = (int **)malloc((m + 1) * sizeof(int *));
  for (i = 1; i <= m; i++) {
    A[i] = (int *)malloc((n + 1) * sizeof(int));
  }
}
void get_mtrx() {
  int i, j;
  char *tok, *line = (char *)malloc(1024 * sizeof(char));
  for (i = 1; i <= m; i++) {
    fgets(line, 1024, stdin);
    tok = strtok(line, " ");
    for (j = 1; tok != NULL; j++) {
      A[i][j] = atoi(tok);
      tok = strtok(NULL, " ");
    }
  }
}
/*
  The algorithm should be something like:
      Suppose A is an Mx(N+1) matrix representing the system
      of equations.
      for (i = j = 0;  i < M && j < N;  j ++)
        {
         Search for a row between i and M-1 that is non-zero in
               column j;
         if  (there is none)
             {
              Mark j as a free variable;
              continue;
             }
         Swap that row with row i;
         Divide every entry in row i by A [i] [j];
         for  (k = 0;  k < M;  k ++)
           if  (k != i)
               subtract A [k] [j] times row i from row k;
         i ++;
        }
     if  (i < M and any of the entries A [i .. M-1] [N] are not zero)
         there are no solutions;
       else
         for (each row)
             the variable repesented by the first non-zero entry
             in that row is equal to the last column minus all
             the other non-zero entries in that row times their
             corresponding free variable.
*/
