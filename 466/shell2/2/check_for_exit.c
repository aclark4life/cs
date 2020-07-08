#include <stdio.h>

int check_for_exit(char **tokenv) {
  if ((!strcmp(tokenv[0], "exit")) || (!strcmp(tokenv[0], "late"))) {

    printf("exit\n");
    exit(0);
  } else {
    return (0);
  }
}
