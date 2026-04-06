/* n.c - Multiply Two nxn Matrices
 * Alex Clark - August 1998
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int m, n, o, p;
int **A, **B, **C;
void get_n();
void get_matrices();
void print_em_out();
void multiply_em();

void main(int argc, char *argv[]) {
  if (argc != 1) {
    printf("Sorry, I don't take command line arguments.\n");
    exit(-1);
  } else {
    // get_m();
    get_n();
    get_matrices();
    multiply_em();
    print_em_out();
  }
}
void multiply_em() {
  int i, j, k, s;
  s = 0;
  for (k = 1; k <= n; k++) {
    for (i = 1; i <= n; i++) {
      for (j = 1; j <= n; j++) {
        s = s + ((A[k][j]) * (B[j][i]));
        if (j == n) {
          C[k][i] = s;
        }
      }
      s = 0;
    }
  }
}
void get_n() {
  char *string = (char *)malloc(1024 * sizeof(char));
  fgets(string, 1024, stdin);
  n = atoi(string);
}
void get_matrices() {
  int i, j;
  char *string = (char *)malloc(1024 * sizeof(char));
  char *tokenPtr;
  int counter = 1;
  A = (int **)malloc(n * sizeof(int *));
  B = (int **)malloc(n * sizeof(int *));
  C = (int **)malloc(n * sizeof(int *));
  for (i = 1; i <= n; i++) {
    A[i] = (int *)malloc(n * sizeof(int));
    B[i] = (int *)malloc(n * sizeof(int));
    C[i] = (int *)malloc(n * sizeof(int));
  }
  for (i = 1; i <= n; i++) {
    fgets(string, 1024, stdin);
    tokenPtr = strtok(string, " ");
    while (tokenPtr != NULL) {
      A[i][counter] = atoi(tokenPtr);
      tokenPtr = strtok(NULL, " ");
      counter++;
    }
    counter = 1;
  }
  counter = 1;
  for (i = 1; i <= n; i++) {
    fgets(string, 1024, stdin);
    tokenPtr = strtok(string, " ");
    while (tokenPtr != NULL) {
      B[i][counter] = atoi(tokenPtr);
      tokenPtr = strtok(NULL, " ");
      counter++;
    }
    counter = 1;
  }
  counter = 1;
}
void print_em_out() {
  int i, j;
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      printf("%d ", C[i][j]);
    }
    printf("\n");
  }
}
