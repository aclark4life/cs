/*aclark*/

#include <math.h>
#include <stdio.h>

main() {
  int state = 0;
  int input;
  printf("A Finite-State Automaton!\n");
  while (input != -1) {
    scanf("%d", &input);
    if (state == 0) {
      if (input == 0) {
        printf("state = 1\n");
        state = 1;
      } else {
        if (input == 1) {
          printf("state = 0\n");
          state = 0;
        } else {
          printf("state unchanged\n");
          state = 0;
        }
      }
    } else {
      if (state == 1) {
        if (input == 0) {
          printf("state = 2\n");
          state = 2;
        } else {
          if (input == 1) {
            printf("state = 0\n");
            state = 0;
          } else {
            printf("state unchanged\n");
          }
        }
      } else {
        if (state == 2) {
          if (input == 0) {
            printf("state = 2\n");
            state = 2;
          } else {
            if (input = 1) {
              printf("state = 0\n");
              state = 0;
            } else {
              printf("state unchanged\n");
            }
          }
        }
      }
    }
  }

  printf("state: %d\n", state);
}
