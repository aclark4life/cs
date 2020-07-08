/* m.c - Perform Gauss-Jordan Elimination on an mxn matrix .
 * Alex Clark - September 1998  .
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NL printf("\n")

int **A, m, n, f = 0, Free = 0;
void get_mn();
void get_mem();
void get_mtrx();
void get_nonzero();
void set_nonzero();
void swap_rows(int i);
void prn_mtrx();
void main(int argc) {
  if (argc != 1) {
    exit(-1);
  } else {
    get_mn();
    get_mem();
    get_mtrx();
    get_nonzero();
  }
}
void set_nonzero(int i) { f = i; }
void prn_mtrx() {
  int i, j;
  for (i = 1; i <= m; i++) {
    for (j = 1; j <= n; j++) {
      printf("%d ", A[i][j]);
    }
    NL;
  }
}
void swap_rows(int ROW) {
  int i, j;
  int *t = (int *)malloc(n * sizeof(int));
  // printf ("row %d\n",ROW);
  for (i = 0; i < n; i++) {
    t[i] = A[ROW - 1][i];
  }
  for (i = 0; i < n; i++) {
    A[ROW - 1][i] = A[ROW][i];
  }
  for (i = 0; i < n; i++) {
    A[ROW][i] = t[i];
  }
}
void get_nonzero() {
  int i, j;
  int c = 0;
  for (i = 1; i <= m; i++) {
    for (j = 1; j <= n; j++) {
      if (A[i][j] != 0) {
        c++; // printf("%d ",A[i][j]);
        if (c == n)
          set_nonzero(i);
      }
    }
    c = 0;
  }
  if (f != 0) {
    if (f != 1)
      swap_rows(f);
  } else
    Free = j;
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
      // printf ("%d ",A[i][j]);
    }
    // NL;
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
           i++;
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

/*
  No.  Something like the following is more appropriate:

       for  (k = i;  k < M && A [k] [j] == 0;  k ++)
         ;
       if  (k == M)
           // none found
         else
           // swap rows i and k if i != k


 No.  A [i] [j] is the first non-zero element in the row.
    This makes the first entry == 1.

                                                -- ALD
*/
