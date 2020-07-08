jinclude<stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
    void bust_a_fork(char **tokenv, int *tokenc) {
  int pid;
  int stat_loc;

  pid = fork();
  switch (pid) {
  case 0:
    if (find_crazy_tokens(tokenv, &tokenc) == 0) {
      printf("bust_a_fork execing %s.\n", tokenv[0]);
      execvp(tokenv[0], tokenv);
      perror(tokenv[0]);
      exit(0);
    }

    break;

  default:
    if (wait(&stat_loc) == -1) {
      perror(tokenv[0]);
    }
    break;
  }
}
