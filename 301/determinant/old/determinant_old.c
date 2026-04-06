/* d.c - Find the Determinant of an n x n Matrix.
   (for n <=3 )
   Alex Clark - August 1998  */

#include <assert.h>
#include <stdio.h>
#include <string.h>

int **M;
int n;

void read_matrx();
void easy_cases();
double find_determ(double *A, int N);
int **mem_chores(int **arg);

void main() {
  double *A;
  int N;
  read_matrx();
  find_determ(A, n);
}
void easy_cases() {
  if ((n == 1) || (n == 2) || (n == 3)) {
    switch (n) {
    case 1:
      printf("%d\n", M[1][1]); // if A=[a11] is a 1x1 matrix, then det (A) =
                               // a11.
      break;
    case 2:
      printf("%d\n", (M[1][1] * M[2][2]) - (M[1][2] * M[2][1]));
      // if A=[a22] is a 2x2 matrix, then det(A) = a11*a22 - a12*a21 .
      break;
    case 3:
      printf("%d\n",
             ((M[1][1] * M[2][2] * M[3][3]) + (M[1][2] * M[2][3] * M[3][1]) +
              (M[1][3] * M[2][1] * M[3][2]) - (M[1][1] * M[2][3] * M[3][2]) -
              (M[1][2] * M[2][1] * M[3][3]) - (M[1][3] * M[2][2] * M[3][1])));
      break;
    }
  } else {
  }
}
void read_matrx() {
  int i, j;
  char *line = (char *)malloc(1024 * sizeof(char));
  char *tok;

  fgets(line, 1024, stdin);
  n = atoi(line);
  M = mem_chores(M);
  for (i = 1; i <= n; i++) {
    fgets(line, 1024, stdin);
    tok = strtok(line, " ");
    for (j = 1; tok != NULL; j++) {
      M[i][j] = atoi(tok);
      // printf ("%d ",atoi(tok));
      tok = strtok(NULL, " ");
    } // printf ("\n");
  }
}
double find_determ(double *A, int N) {
  double *B = NULL;
  double Ans;
  int ct, i, k, j;
  int Power;
  if (N <= 3) {
    easy_cases();
  } else {
    B = (double *)malloc((N - 1) * (N - 1) * sizeof(double));
    assert(B != NULL);
    Ans = 0.0;
    for (i = 0; i < N; i++) {

      ct = 0;
      for (j = 0; j < N; j++) {
        for (k = 0; k < N; j++) {
          if (k != i)
            // B[ct++] = A[???];
            ;
        }
      }
    }
    Ans += A[i] * Power * find_determ(B, N - 1);
  }
  free(B);
  return Ans;
}
int **mem_chores(int **arg) {
  int i;
  arg = (int **)malloc((n + 1) * sizeof(int *));
  for (i = 1; i <= (n + 1); i++) {
    arg[i] = (int *)malloc((n + 1) * sizeof(int));
  }
  return (arg);
}
