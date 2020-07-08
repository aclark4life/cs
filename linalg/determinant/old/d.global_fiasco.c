/* d.c - Find the Determinant of an n x n Matrix.
   Alex Clark - August 1998  */

#include <assert.h>
#include <stdio.h>
#include <string.h>

void mem();
void read();
void find();
void easy();

int N;
double **A;

void main() {
  double ans;

  read(A, N);
  mem(A, N);
  ans = find(a, n);
}
double **read(double *A, int N) {
  int i, j;
  char *line = (char *)malloc(1024 * sizeof(char));
  char *tok;

  fgets(line, 1024, stdin);
  N = atoi(line);
  for (i = 1; i <= N; i++) {
    fgets(line, 1024, stdin);
    tok = strtok(line, " ");
    for (j = 1; tok != NULL; j++) {
      A[i][j] = atoi(tok);
      // printf ("%d ",atoi(tok));
      tok = strtok(NULL, " ");
    } // printf ("\n");
  }
}

double **mem(double **A, int N);
{
  int i;
  A = (double **)malloc((N + 1) * sizeof(double *));
  for (i = 1; i <= (N + 1); i++) {
    A[i] = (double *)malloc((n + 1) * sizeof(double));
  }
  return (A);
}

void easy(double **A, int N) {
  switch (N) {
  case 1:
    printf("%d\n", A[1][1]); // if A=[a11] is a 1x1 matrix, then det (A) = a11.
    break;
  case 2:
    printf(
        "%d\n",
        (A[1][1] * M[2][2]) -
            (A[1][2] * A[2][1])); // if A=[a22] is a 2x2
                                  //   matrix, then det(A) = a11*a22 - a12*a21 .
    break;
  case 3:
    printf("%d\n",
           ((A[1][1] * A[2][2] * A[3][3]) + (A[1][2] * A[2][3] * A[3][1]) +
            (A[1][3] * A[2][1] * A[3][2]) - (A[1][1] * A[2][3] * A[3][2]) -
            (A[1][2] * A[2][1] * A[3][3]) - (A[1][3] * A[2][2] * A[3][1])));
    break;
  }
}
double find(double *A, int N) {
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
    Ans += A[i] * Power * find(B, N - 1);
  }
  free(B);
  return Ans;
}
