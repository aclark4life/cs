/* m.c - Find the inverse of an m x n matrix.
   Alex Clark - August 1998 */

#include <stdio.h>
#include <string.h>

int **A, **ID, **ANS, n;
int **get_mem(int **A);
int **get_mem2(int **A);
void get_matrx();
void setup_ident();
void gauss_jord();

void main(int argc) {
  if (argc != 1) {
    exit(-1);
  } else {
    get_matrx();
    setup_ident();
    gauss_jord();
  }
}

void gauss_jord() {
  int i, j, k;
  ANS = get_mem2(ANS);
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= (n * 2); j++) {
      if (j <= n) {
        ANS[i][j] = A[i][j];
        printf("%d ", ANS[i][j]);
      } else {
        if ((i + 4) == j) {
          ANS[i][j] = 1;
        } else
          ANS[i][j] = 0;

        printf("%d ", ANS[i][j]);
        // printf ("[%d %d]",i,j);
      }
    }
    printf("\n");
  }
}
void setup_ident() {
  int i, j;
  ID = get_mem(ID);
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      ID[i][j] = 0;
      if (i == j)
        ID[i][j] = 1;
      printf("%d ", ID[i][j]);
    }
    printf("\n");
  }
}
void get_matrx() {
  int i, j;
  char *line = (char *)malloc(1024 * sizeof(char));
  char *tok;

  scanf("%d\n", &n);
  printf("%d\n", n);
  A = get_mem(A);
  for (i = 1; i <= n; i++) {
    fgets(line, 1024, stdin);
    tok = strtok(line, " ");
    for (j = 1; tok != NULL; j++) {
      A[i][j] = atoi(tok);
      printf("%d ", atoi(tok));
      tok = strtok(NULL, " ");
    }
    printf("\n");
  }
}
int **get_mem(int **arg) {
  int i;
  arg = (int **)malloc((n + 1) * sizeof(int *));
  for (i = 1; i <= (n + 1); i++) {
    arg[i] = (int *)malloc((n + 1) * sizeof(int));
  }
  return (arg);
}
int **get_mem2(int **arg) {
  int i;
  arg = (int **)malloc((n + 1) * sizeof(int *));
  for (i = 1; i <= (n + 1); i++) {
    arg[i] = (int *)malloc(((n + 1) * 2) * sizeof(int));
  }
  return (arg);
}
