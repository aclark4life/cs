#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

bg(char **tokenv, int *tokenc) {
  int pid;
  free(tokenv[(*tokenc) - 1]);
  tokenv[(*tokenc) - 1] = NULL;
  pid = fork();
  switch (pid) {

  case 0:
    tokenv = tokenv + (*tokenc);
    printf("case 0\n");
    execvp(tokenv[0], tokenv);
    break;

  default:
    printf("default\n");
    return (0);
    break;
  }
}
