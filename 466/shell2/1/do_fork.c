#include <stdio.h>
void do_fork(char **tokenv, int *tokenc) {
  int pid, status;
  pid = fork();
  switch (pid) {
  case 0:
    check_token(tokenv, &tokenc);
    execvp(tokenv[0], tokenv);
    perror(tokenv[0]);

    break;

  default:
    if (wait(&status) == -1) {
      perror("wait error...");
    }

    break;
  }
}
