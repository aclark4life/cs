/* m.c - Multiply Two mxn Matrices
 * Alex Clark - August 1998
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **A, **B, **C, m, p, n;

void get_mpn();
void get_mem();
void get_matrices();
void mul_matrices();
void print_ans();

void main(int argc) {
  if (argc != 1) {
    exit(-1);
  } else {
    get_mpn();
    get_mem();
    get_matrices();
    mul_matrices();
    print_ans();
  }
}
void get_mpn() { scanf("%d %d %d\n", &m, &n, &p); }
void get_mem() {
  int i, j;
  A = (int **)malloc((m + 1) * sizeof(int *));
  for (i = 1; i <= m; i++) {
    A[i] = (int *)malloc((p + 1) * sizeof(int));
  }
  B = (int **)malloc((p + 1) * sizeof(int *));
  for (i = 1; i <= p; i++) {
    B[i] = (int *)malloc((n + 1) * sizeof(int));
  }
  C = (int **)malloc((m + 1) * sizeof(int *));
  for (i = 1; i <= m; i++) {
    C[i] = (int *)malloc((n + 1) * sizeof(int));
  }
}
void get_matrices() {
  int i, j;
  char *string;
  char *token;
  string = (char *)malloc(1024 * sizeof(char));
  for (i = 1; i <= m; i++) {
    fgets(string, 1024, stdin);
    token = strtok(string, " ");
    for (j = 1; token != NULL; j++) {
      A[i][j] = atoi(token);
      token = strtok(NULL, " ");
    }
  }
  for (i = 1; i <= p; i++) {
    fgets(string, 1024, stdin);
    token = strtok(string, " ");
    for (j = 1; token != NULL; j++) {
      B[i][j] = atoi(token);
      token = strtok(NULL, " ");
    }
  }
}
void mul_matrices() {
  int i, j, k, s;
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= m; j++) {
      s = 0;
      for (k = 1; k <= p; k++) {
        s = s + ((A[j][k]) * (B[k][i]));
      }
      C[j][i] = s;
    }
  }
}
void print_ans() {
  int i, j;
  for (i = 1; i <= m; i++) {
    for (j = 1; j <= n; j++) {
      printf("%d ", C[i][j]);
    }
    printf("\n");
  }
}
