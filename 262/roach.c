#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])

{
  int move, imove[7], jmove[7];
  int **count;
  int ibug, jbug;
  int i, n, m, j;
  float counter = 0;
  int imaybe = 0, jmaybe = 0;
  int iteration = 0;

  imove[0] = -1; /*declare array of possible moves*/
  imove[1] = 0;
  imove[2] = 1;
  imove[3] = 1;
  imove[4] = 1;
  imove[5] = 0;
  imove[6] = -1;
  // imove[7] = -1;

  jmove[0] = 1;
  jmove[1] = 1;
  jmove[2] = 1;
  jmove[3] = 0;
  jmove[4] = -1;
  jmove[5] = -1;
  jmove[6] = -1;
  // jmove[7] = 0;

  if (argc != 5) {
    printf("usage: %s n m ibug jbug\n", argv[0]);

    exit(-1);

  } else {             /*create multi-dimensional array*/
    n = atoi(argv[1]); /*columns*/
    m = atoi(argv[2]); /*rows*/
    ibug = atoi(argv[3]);
    jbug = atoi(argv[4]);

    if (((ibug < 0) || (ibug >= n)) || ((jbug < 0) || (jbug >= m)))
      exit(-1); /*if entry not valid then exit*/
    else {
      count = (int **)malloc(n * sizeof(int));
      /*malloc array*/
      for (i = 0; i < n; i++)
        count[i] = (int *)malloc(m * sizeof(int));

      for (i = 0; i < n; i++) { /*initialize array*/
        for (j = 0; j < m; j++) {
          count[i][j] = 0;
        }
      }

      count[ibug][jbug] = 1;
      counter = 1; /*increment counter and array for first move*/

      while ((counter != n * m) && (iteration < 50000)) { /*begin while*/
        move = random() % 8;
        imaybe = ibug + imove[move]; /*choose random move*/
        jmaybe = jbug + jmove[move];
        if ((imaybe >= 0) && (imaybe < n) && (jmaybe >= 0) &&
            (jmaybe < m)) { /*check validity*/

          ibug = imaybe;
          jbug = jmaybe; /*if valid do these things*/
          if (count[ibug][jbug] == 0)
            counter = counter + 1;
          count[ibug][jbug]++;
        }
        iteration++; /*increment iteration*/
      } /*end while*/
      for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
          printf("count[%d][%d] = %d\n", i, j, count[i][j]);
        }
      }
      printf("LEGAL MOVES: %d\n", iteration); /*print total legal moves*/

    } /*end else*/
  } /*end else*/
  free(count);
} /*end main*/
