/* g.c - Solve an m x (n+1) system of equations
 * with Gauss-Jordan elimination .
 * Alex Clark - September 1998  .
 */

#include "fun.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void chkCol(int c) {
  int i;
  printf("col %d\n", c);
  for (i = c; i <= m; i++) {
    printf("%f\n", A[i][c]);
  }
}
void elim_nonZero(int r, int c) {
  int i;
  float sum;

  for (i = r + 1; i <= m; i++) {
    // printf ( "A[%d][%d] * A[%d][%d]=%f\n",r,c,i,c,A[r][c]*A[i][c] ) ;
    sum = (A[r][c] * -A[i][c]) + A[i][c];
    printf("A[%d][%d] * A[%d][%d] + A[%d][%d]=%f\n", r, c, i, c, i, c, sum);
    // printf ( "A[%d][%d] =%f\n",i,c,A[i][c]) ;
  }
  echo_inp();
}
void get_nonZero() {
  int i, j, k;
  for (i = j = 1; i <= m && j <= n; j++) {
    for (k = i; k <= m && A[k][j] == 0; k++) {
      printf("A[%d][%d]=%f\n", k, j, A[k][j]);
      // if (k==m){IMH;}
      // if (i!=k){IMH;}
    }
    elim_nonZero(k, j);
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

void echo_inp() {
  int r, c;
  for (r = 1; r <= m; r++) {
    for (c = 1; c <= n; c++) {
      printf("%f ", A[r][c]);
    }
    NL;
  }
}
void get_mn() {
  int i, j;
  scanf("%d %d\n", &m, &n);
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
      // printf ("%f ",A[i][j]);
    }
    // NL;
  }
}
void get_mem() {
  int i, j;
  A = (double **)malloc((m + 1) * sizeof(double *));
  for (i = 1; i <= m; i++) {
    A[i] = (double *)malloc((n + 1) * sizeof(double));
  }
}
void main(int argc) {
  if (argc != 1) {
    exit(-1);
  } else {
    get_mn();
    get_mem();
    get_mtrx();
    echo_inp();
    get_nonZero();
  }
}

/*    Suppose A is an Mx(N+1) matrix representing the system
      of equations.
        for (i = j = 0;  i < M && j < N;  j ++)
        {
                Search for a row between i and M-1
                that is non-zero in column j;
                for  (k = i;  k < M && A [k] [j] == 0;  k ++)
                {
                        if (k == M) none found
                        if (there is none)
                        {
                                Mark j as a free variable;
                                continue;
                        }
                        else swap rows i and k if i != k
                        Swap that row with row i;

                        Divide every entry in row i by A [i] [j];
                }
                for  (k = 0;  k < M;  k ++)
                {
                        if  (k != i)
                        {
                                subtract A[k][j] times row i from row k;
                                i++;
                        }
                }
        }
        if  (i < M and any of the entries A [i .. M-1] [N] are not zero)
        {
                there are no solutions;
        }
        else
        {
                for (each row)
                the variable repesented by the first non-zero entry
                in that row is equal to the last column minus all
                the other non-zero entries in that row times their
                corresponding free variable.
        }
*/
