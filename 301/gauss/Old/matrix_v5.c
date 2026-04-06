/* m.c - Solve an m x (n+1) system of equations
 * using Gauss-Jordan elimination .
 * Alex Clark - September 1998  .
 */

/*  The algorithm should be something like:
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NL printf("\n")
#define NewLine printf("\n")

double **A;
int m, n;
void get_mn();
void get_mem();
void get_mtrx();
void get_nonZero_col();
void divide_by_nonZero(int r);
void swap_rows(int i);
void prn_matrx();

void main(int argc) {
  if (argc != 1) {
    exit(-1);
  } else {
    get_mn();
    get_mem();
    get_mtrx();
    get_nonZero_col();
    //	prn_matrx();
    //	divide_by_nonZero(1);
  }
}
void divide_by_nonZero(int r) {
  int i, j;
  for (i = 1, j = 1; i <= n; i++) {
    printf("%f ", A[r][i] / A[r][j]);
  }
  NewLine;
}
void swap_rows(int r) {
  int i, j, *t = (int *)malloc((n + 1) * sizeof(int));
  for (i = 1; i <= n; i++) {
    t[i] = A[r - 1][i];
  }
  for (i = 1; i <= n; i++) {
    A[r - 1][i] = A[r][i];
  }
  for (i = 1; i <= n; i++) {
    A[r][i] = t[i];
  }
}

void get_nonZero_col() {
  int i, j, k;
  for (i = j = 1; i <= m && j <= n; j++) {
    for (k = i; k <= m && A[k][j] == 0; k++) {
      printf("swap row %d \n", k);
      //     			if  (k == m) {
      // none found
      // mark as free
      //				printf ("col %d is free\n",j);
      //			}
      // else {
      // swap rows i and k if i != k
      //	if (i!=k) {
      // swap_rows(k);
      //	}
      //	else {
      // printf ("%d ",A[k][j]);
      //	}
      //			}
    }
  }
}
void prn_matrx() {
  int i, j;
  for (i = 1; i <= m; i++) {
    for (j = 1; j <= n; j++) {
      printf("%d ", A[i][j]);
    }
    NL;
  }
}
void get_mn() {
  int i, j;
  scanf("%d %d\n", &m, &n);
}
void get_mem() {
  int i, j;
  A = (double **)malloc((m + 1) * sizeof(double *));
  for (i = 1; i <= m; i++) {
    A[i] = (double *)malloc((n + 1) * sizeof(double));
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
