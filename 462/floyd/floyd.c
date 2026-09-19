#include <stdio.h>
#define N 5
#define INT_MAX 99999
#define LIM N + 1
#define LIMM N + 1

int W[N + 1][N + 1];
int D[N + 1][N + 1];
int P[N + 1][N + 1];

void print()

{
  int i, j;
  printf("W:\n");

  for (i = 0; i < LIM; i++) {
    for (j = 0; j < LIM; j++) {
      printf("%d ", W[i][j]);
    }
    printf("\n");
  }

  printf("D:\n");
  for (i = 0; i < LIM; i++) {
    for (j = 0; j < LIM; j++) {
      printf("%d ", D[i][j]);
    }
    printf("\n");
  }

  printf("P:\n");
  for (i = 0; i < LIM; i++) {
    for (j = 0; j < LIM; j++) {
      printf("%d ", P[i][j]);
    }
    printf("\n");
  }
}
void floyd2() {
  int i, j, k;
  for (k = 1; k < LIMM; k++) {
    for (i = 1; i < LIMM; i++) {
      for (j = 1; j < LIMM; j++) {
        //		printf ( "D[i][k]=D[%d][%d]=%d\n",i,k,W[i][k] );
        //		printf ( "D[k][j]=D[%d][%d]=%d\n",k,j,W[k][j] );
        //		printf ( "D[i][j]=D[%d][%d]=%d\n",i,j,W[i][j] );

        if ((D[i][k] + D[k][j]) < D[i][j]) {
          P[i][j] = k;
          D[i][j] = D[i][k] + D[k][j];
        }
      }
    }
  }
}
fill() {
  int i, j;
  for (i = 0; i < LIM; i++) {
    for (j = 0; j < LIM; j++) {
      if (i == 0)
        W[i][j] = -1;
      if (j == 0)
        W[i][j] = -1;
      //			if(i==j) W[i][j] = -1;
      // W[0][0] = -1;

      if (i == 0)
        D[i][j] = -1;
      if (j == 0)
        D[i][j] = -1;
      //			if(i==j) D[i][j] = -1;
      // D[0][0] = -1;

      if (i == 0)
        P[i][j] = -1;
      if (j == 0)
        P[i][j] = -1;
      //			if(i==j) P[i][j] = 0;
      // P[0][0] = -1;

      if ((i == 1) && (j == 2))
        W[i][j] = 1;
      if ((i == 1) && (j == 3))
        W[i][j] = INT_MAX;
      if ((i == 1) && (j == 4))
        W[i][j] = 1;
      if ((i == 1) && (j == 5))
        W[i][j] = 5;

      if ((i == 2) && (j == 1))
        W[i][j] = 9;
      if ((i == 2) && (j == 3))
        W[i][j] = 3;
      if ((i == 2) && (j == 4))
        W[i][j] = 2;
      if ((i == 2) && (j == 5))
        W[i][j] = INT_MAX;

      if ((i == 3) && (j == 1))
        W[i][j] = INT_MAX;
      if ((i == 3) && (j == 2))
        W[i][j] = INT_MAX;
      if ((i == 3) && (j == 4))
        W[i][j] = 4;
      if ((i == 3) && (j == 5))
        W[i][j] = INT_MAX;

      if ((i == 4) && (j == 1))
        W[i][j] = INT_MAX;
      if ((i == 4) && (j == 2))
        W[i][j] = INT_MAX;
      if ((i == 4) && (j == 3))
        W[i][j] = 2;
      if ((i == 4) && (j == 5))
        W[i][j] = 3;

      if ((i == 5) && (j == 1))
        W[i][j] = 3;
      if ((i == 5) && (j == 2))
        W[i][j] = INT_MAX;
      if ((i == 5) && (j == 3))
        W[i][j] = INT_MAX;
      if ((i == 5) && (j == 4))
        W[i][j] = INT_MAX;

      if ((i == 1) && (j == 2))
        D[i][j] = 1;
      if ((i == 1) && (j == 3))
        D[i][j] = INT_MAX;
      if ((i == 1) && (j == 4))
        D[i][j] = 1;
      if ((i == 1) && (j == 5))
        D[i][j] = 5;

      if ((i == 2) && (j == 1))
        D[i][j] = 9;
      if ((i == 2) && (j == 3))
        D[i][j] = 3;
      if ((i == 2) && (j == 4))
        D[i][j] = 2;
      if ((i == 2) && (j == 5))
        D[i][j] = INT_MAX;

      if ((i == 3) && (j == 1))
        D[i][j] = INT_MAX;
      if ((i == 3) && (j == 2))
        D[i][j] = INT_MAX;
      if ((i == 3) && (j == 4))
        D[i][j] = 4;
      if ((i == 3) && (j == 5))
        D[i][j] = INT_MAX;

      if ((i == 4) && (j == 1))
        D[i][j] = INT_MAX;
      if ((i == 4) && (j == 2))
        D[i][j] = INT_MAX;
      if ((i == 4) && (j == 3))
        D[i][j] = 2;
      if ((i == 4) && (j == 5))
        D[i][j] = 3;

      if ((i == 5) && (j == 1))
        D[i][j] = 3;
      if ((i == 5) && (j == 2))
        D[i][j] = INT_MAX;
      if ((i == 5) && (j == 3))
        D[i][j] = INT_MAX;
      if ((i == 5) && (j == 4))
        D[i][j] = INT_MAX;
    }
  }
}

init() {
  int i, j;
  for (i = 0; i < LIM; i++) {
    for (j = 0; j < LIM; j++) {
      W[i][j] = 0;
      D[i][j] = 0;
      P[i][j] = 0;
    }
  }
}

void main() {

  init();
  fill();
  floyd2();
  print();
}
